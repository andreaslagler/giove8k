/*
Copyright (C) 2021 Andreas Lagler

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program. If not, see <https://www.gnu.org/licenses/>.
 */

/**
 * @file main.c
 * @brief main function for Audio/FX module
 * 
 * This file is part of the Audio/FX module
 */

/// Configuration bits

/// FBS
#pragma config BWRP = WRPROTECT_OFF     // Boot Segment Write Protect (Boot Segment may be written)
#pragma config BSS = NO_FLASH           // Boot Segment Program Flash Code Protection (No Boot program Flash segment)
#pragma config RBS = NO_RAM             // Boot Segment RAM Protection (No Boot RAM)

/// FSS
#pragma config SWRP = WRPROTECT_OFF     // Secure Segment Program Write Protect (Secure segment may be written)
#pragma config SSS = NO_FLASH           // Secure Segment Program Flash Code Protection (No Secure Segment)
#pragma config RSS = NO_RAM             // Secure Segment Data RAM Protection (No Secure RAM)

/// FGS
#pragma config GWRP = OFF               // General Code Segment Write Protect (User program memory is not write-protected)
#pragma config GSS = OFF                // General Segment Code Protection (User program memory is not code-protected)

/// FOSCSEL
#pragma config FNOSC = PRIPLL           // Oscillator Mode (Primary Oscillator (XT, HS, EC) w/ PLL)
#pragma config IESO = ON                // Internal External Switch Over Mode (Start-up device with FRC, then automatically switch to user-selected oscillator source when ready)

/// FOSC
#pragma config POSCMD = XT              // Primary Oscillator Source (XT Oscillator Mode)
#pragma config OSCIOFNC = OFF           // OSC2 Pin Function (OSC2 pin has clock out function)
#pragma config IOL1WAY = ON             // Peripheral Pin Select Configuration (Allow Only One Re-configuration)
#pragma config FCKSM = CSDCMD           // Clock Switching and Monitor (Both Clock Switching and Fail-Safe Clock Monitor are disabled)

/// FWDT
#pragma config WDTPOST = PS32768        // Watchdog Timer Postscaler (1:32,768)
#pragma config WDTPRE = PR128           // WDT Prescaler (1:128)
#pragma config WINDIS = OFF             // Watchdog Timer Window (Watchdog Timer in Non-Window mode)
#pragma config FWDTEN = OFF             // Watchdog Timer Enable (Watchdog timer enabled/disabled by user software)

/// FPOR
#pragma config FPWRT = PWR128           // POR Timer Value (128ms)
#pragma config ALTI2C = OFF             // Alternate I2C  pins (I2C mapped to SDA1/SCL1 pins)

/// FICD
#pragma config ICS = PGD2               // Comm Channel Select (Communicate on PGC2/EMUC2 and PGD2/EMUD2)
#pragma config JTAGEN = OFF             // JTAG Port Enable (JTAG is Disabled)

#include <xc.h>
#include "audio_output.h"
#include "param_interface.h"
#include "wave_interface.h"
#include "param_database.h"
#include "voice_manager.h"
#include "block_len_def.h"
#include "dspParam_enums.h"
#include "scene_enums.h"
#include "synth_types.h"
/**
 * @brief Clock configuration
 */
void configureClock()
{
    // Instruction clock FCY = FOSC / 2;
    // System clock FOSC = FIN * M / ( N1 * N2 ) 
    // N1 = PLLPRE + 2
    // N2 = 2 x (PLLPOST + 1)
    // M = PLLFBD + 2

    // Requirements:
    // Primary Oscillator in XT Mode supports: 3 MHz to 10 MHz crystal (FIN))
    // The PFD input frequency (FREF = FIN / N1) must be in the range of 0.8 to 8.0 MHz
    // The VCO output frequency (FVCO = FREF * M) must be in the range of 100 to 200 MHz
    // The divider output frequency (FOSC = FVCO / N2) must be in the range of 12.5 to 80 MHz

    // Configure PLL prescaler, PLL postscaler, and PLL divider

    // FIN = 10 MHz
    CLKDIVbits.PLLPRE = 0; // N1 = 2
    // --> FREF = 10 MHz / 2 = 5 MHz

    PLLFBD = 30; // M = 32
    // --> FVCO = 10 MHz / 2 * 32 = 160 MHz

    CLKDIVbits.PLLPOST = 0; // N2 = 2
    // --> FOSC = 10 MHz / 2 * 32 / 2 = 80 MHz
    // --> FCY = 10 MHz / 2 * 32 / 2 / 2 = 40 MHz

    // Initiate clock switch to primary oscillator with PLL (NOSC = 0b011)
    __builtin_write_OSCCONH(0x03);
    __builtin_write_OSCCONL(0x01);

    // Wait for clock switch to occur
    while (OSCCONbits.COSC != 0b011);

    // Wait for PLL to lock
    while (OSCCONbits.LOCK != 1);

    // Configure DAC clock source
    // DAC sample rate is 48 kHz
    // --> DACCLK is 256 * 48 kHz = 12.288 MHz
    // Use a 12.288 MHz crystal as secondary oscillator and make it the source of the aux clock
    ACLKCONbits.AOSCMD = 0b01; // Select high speed oscillator on SOSC pins as PLL input
    ACLKCONbits.ASRCSEL = 0; // Select AOSCCLK
    ACLKCONbits.SELACLK = 1; // Select AOSCCLK
    ACLKCONbits.APSTSCLR = 0b111; // Post Scaler = 1
}
/**
 * @brief Pin programming, ie. assign phasical pins to peripherals via PPS
 */
void configurePins()
{
    // Unlock PPS
    __builtin_write_OSCCONL(OSCCON & ~(1 << 6));

    // SPI1 is configured as SPI master

    // SCK1 --> RB13 / RP13 / AN11 (output)
    RPOR6bits.RP13R = 0b01000;
    AD1PCFGLbits.PCFG11 = 1;
    TRISBbits.TRISB13 = 0;

    // SD11 --> RB14 / RP14 / AN10 (input)
    RPINR20bits.SDI1R = 14;
    AD1PCFGLbits.PCFG10 = 1;
    TRISBbits.TRISB14 = 1;

    // SDO1 --> RB15 / RP15 (output)
    RPOR7bits.RP15R = 0b00111;
    TRISBbits.TRISB15 = 0;

    // /SS1 --> RB12 / RP12 / AN12 (output)
    RPOR6bits.RP12R = 0b01001;
    AD1PCFGLbits.PCFG12 = 1;
    TRISBbits.TRISB12 = 0;
    LATBbits.LATB12 = 1;

    // SPI2 is configered as 5V-tolerant SPI slave

    // SCK2 --> RB6 / RP6 (input)
    RPINR22bits.SCK2R = 6;
    TRISBbits.TRISB6 = 1;

    // SDI2 --> RB7 / RP7 (input)
    RPINR22bits.SDI2R = 7;
    TRISBbits.TRISB7 = 1;

    // SDO2 --> RB8 / RP (output)
    RPOR4bits.RP8R = 0b01010;
    TRISBbits.TRISB8 = 0;

    // /SS2 --> RB9 / RP9 (input)
    RPINR23bits.SS2R = 9;
    TRISBbits.TRISB9 = 1;

    // DCI is configured as master (output only))

    // CSDO --> RB1 / RP1 / AN3 (output)
    RPOR0bits.RP1R = 0b01101;
    AD1PCFGLbits.PCFG3 = 1;
    TRISBbits.TRISB1 = 0;

    // COFS --> RB2 / RP2 / AN4 (output)
    RPOR1bits.RP2R = 0b01111;
    AD1PCFGLbits.PCFG4 = 1;
    TRISBbits.TRISB2 = 0;

    // CSCK --> RB3 / RP3 / AN5 (output)
    RPOR1bits.RP3R = 0b01110;
    AD1PCFGLbits.PCFG5 = 1;
    TRISBbits.TRISB3 = 0;

    // Lock PPS
    __builtin_write_OSCCONL(OSCCON | (1 << 6));

    // Pin I/O direction

    // MUX0 --> RB10 (Output)
    TRISBbits.TRISB10 = 0;

    // MUX1 --> RB11 (Output)
    TRISBbits.TRISB11 = 0;
}
/**
 * @brief Configuration of parameter interface
 * 
 * The parameter interface is the interfce between the Audio/FX module and the Controller/UI module.
 * The physical connection uses the SPI2 on the Audio/FX module in 16 bit slave mode
 */
void configureParamInterface()
{
    // Configure SPI2 for slave mode (assuming all configuration registers are in POR state)
    IFS2bits.SPI2IF = 0; // Clear the Interrupt flag
    IEC2bits.SPI2IE = 0; // Disable the interrupt
    SPI2BUF = 0; // clear SPI buffer

    // SPI2CON1 Register Settings
    SPI2CON1bits.DISSCK = 0; // Internal Serial Clock is Enabled
    SPI2CON1bits.DISSDO = 0; // SDO2 pin is controlled by the module
    SPI2CON1bits.MODE16 = 1; // Communication is word-wide (16 bits)
    SPI2CON1bits.SMP = 0; // SMP bit must be cleared when SPIx module is used in Slave mode.
    SPI2CON1bits.CKE = 1; // Serial output data changes on transition from Idle clock state to active clock state
    SPI2CON1bits.CKP = 0; // Idle state for clock is a low level; active state is a high level
    SPI2CON1bits.SSEN = 1; // SS2 pin is used for Slave mode
    SPI2CON1bits.MSTEN = 0; // Master mode disabled

    SPI2STATbits.SPIROV = 0; // No Receive Overflow has occurred
    SPI2STATbits.SPIEN = 1; // Enable SPI module

    // Interrupt Controller Settings
    IFS2bits.SPI2IF = 0; // Clear the Interrupt flag
    IEC2bits.SPI2IE = 1; // Enable the interrupt
}

/**
 * @brief Main function
 */
int main()
{
    static DSPBuffer dspBuffer[NOF_DSPS] __attribute__((space(dma)));

    configureClock();
    configurePins();
    configureAudioOutput();
    configureParamInterface();
    configureWaveInterface();

    while (1)
    {
        for (int cntDSP = 0; cntDSP < NOF_DSPS; ++cntDSP)
        {
            ////////////////////////////////////////////////////////////////////////
            // Query DSP waveform data
            updateWaveDSPParams(
                    getPatchParams(cntDSP),
                    getSceneParams(),
                    getControllerParams(),
                    getVoiceParams(cntDSP),
                    &dspBuffer[cntDSP]);

            startWaveTransfer(
                    cntDSP,
                    dspBuffer[cntDSP].buffer,
                    dspBuffer[cntDSP].buffer,
                    BLOCK_LEN * 2);
        }

        waitWaveTransfer();

        ////////////////////////////////////////////////////////////////////////
        // Add stereo signals from all DSPs
        for (uint8_t cntSample = 0; cntSample < BLOCK_LEN * 2; ++cntSample)
        {
            // Use the accumulator register to accumulate all DSPs into one wave buffer and get implicit single-cycle saturation of the sum
            // Prefer built-in functions over inline asm here - Compiler will unroll the for-loop across all voices
            // Hardware for-loop across all samples has to be sacrificed, though.
            
            // Load sample of first voice into accumulator
            volatile register int acc asm("A");
            acc = __builtin_lac(dspBuffer[0].buffer[cntSample], 0);

            // The iteration count of this for-loop is compile-time constant, so the compiler can unroll it (and does for nummber of voices = 4)
            for (uint8_t cntDSP = 1; cntDSP < NOF_DSPS; ++cntDSP)
            {
                // Add sample of remaining voices
                acc = __builtin_add(acc, dspBuffer[cntDSP].buffer[cntSample], 0);
            }

            // Clip sum of samples to int16 and write to output buffer
            dspBuffer[0].buffer[cntSample] = __builtin_sacr(acc, 0);
        }

        ////////////////////////////////////////////////////////////////////////
        // Immediately fill DAC DMA buffers and restart DMA transfer
        startAudioOutputTransfer(dspBuffer[0].bufferLeft, dspBuffer[0].bufferRight);
    }

    return 0;
}
/**
 * @brief Interrupt service routine for SPI2 interrupt
 */
void __attribute__((interrupt, no_auto_psv)) _SPI2Interrupt(void)
{
    // Store received data
    const uint16_t rxData = SPI2BUF;

    // Callback
    onParamReceive(rxData);

    // Clear interrupt flag
    IFS2bits.SPI2IF = 0;
}