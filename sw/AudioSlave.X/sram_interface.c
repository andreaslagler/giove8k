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

#include "sram_interface.h"

#include "block_len_def.h"
#include <xc.h>
#include <stdint.h>

static void(*nextTransfer)() = 0;

static uint16_t writePosition = 0;
static uint16_t readPosition = 0;

static int16_t buffer0[BLOCK_LEN + 2] __attribute__((space(xmemory)));
static int16_t buffer1[BLOCK_LEN + 2] __attribute__((space(xmemory)));

int16_t * getSRAM0Buffer()
{
    return buffer0 + 2;
}

int16_t * getSRAM1Buffer()
{
    return buffer1 + 2;
}


/// Slave select pin
#define SS_SRAM0 (LATBbits.LATB6)
#define SS_SRAM1 (LATBbits.LATB11)

void setDMABuffer0()
{
            // Set buffer to Tx channel
    DMA2STAL = (unsigned int) __builtin_dmaoffset(&buffer0);
    DMA2STAH = (unsigned int) __builtin_dmapage(&buffer0);

    DMA3STAL = (unsigned int) __builtin_dmaoffset(&buffer0);
    DMA3STAH = (unsigned int) __builtin_dmapage(&buffer0);
}

void setDMABuffer1()
{
            // Set buffer to Tx channel
    DMA2STAL = (unsigned int) __builtin_dmaoffset(&buffer1);
    DMA2STAH = (unsigned int) __builtin_dmapage(&buffer1);

    DMA3STAL = (unsigned int) __builtin_dmaoffset(&buffer1);
    DMA3STAH = (unsigned int) __builtin_dmapage(&buffer1);
}


/**
 * @brief Start actual DMA transfer after slave has been selected
 */
inline static void startDMATransfer()
{
    // Enable Tx channel
    DMA2CONbits.CHEN = 1;
    
    // Enable Rx channel
    DMA3CONbits.CHEN = 1;

    // Start transmission
    // Force first DMA transfer, here: load first data word into SPI buffer
    DMA2REQbits.FORCE = 1;
    while (DMA2REQbits.FORCE);
}


////////////////////////////////////////////////////////////////////////////////
// Wait for transfer to complete
////////////////////////////////////////////////////////////////////////////////
void waitSRAMTransfer()
{
    // Wait while next transfer has not been reset
    while (nextTransfer != 0);
}

static void readSRAM1()
{
    SS_SRAM1 = 0;
    buffer1[0] = (3 << 8) + (readPosition >> 15);
    buffer1[1] = (readPosition << 1);
    setDMABuffer1();
    startDMATransfer();
    nextTransfer = 0;
}

static void readSRAM0()
{
    SS_SRAM0 = 0;
    buffer0[0] = (3 << 8) + (readPosition >> 15);
    buffer0[1] = (readPosition << 1);
    setDMABuffer0();
    startDMATransfer();
    nextTransfer = &readSRAM1;
}

static void writeSRAM1()
{
    SS_SRAM1 = 0;
    buffer1[0] = (2 << 8) + (writePosition >> 15);
    buffer1[1] = (writePosition << 1);
    setDMABuffer1();
    startDMATransfer();
    nextTransfer = &readSRAM0;
}

static void writeSRAM0()
{
    SS_SRAM0 = 0;
    buffer0[0] = (2 << 8) + (writePosition >> 15);
    buffer0[1] = (writePosition << 1);
    setDMABuffer0();
    startDMATransfer();
    nextTransfer = &writeSRAM1;
}

void startSRAMTransfer(
const uint16_t writePos,
const uint16_t readPos)
{
    writePosition = writePos;
    readPosition = readPos;
    
    writeSRAM0();
}

static inline void startNextTransfer()
{
            // Stop transmission by raising /SS
        SS_SRAM0 = 1;
        SS_SRAM1 = 1;
        
    if (nextTransfer)
    {
        nextTransfer();
    }
}


////////////////////////////////////////////////////////////////////////////////
// Configure SPI1 for SRAM transfer
////////////////////////////////////////////////////////////////////////////////
void configureSRAMInterface(void)
{
    // Interrupt Controller Settings
    IFS0bits.SPI1IF = 0;

    // SPI2CON1 Register Settings
    SPI1CON1bits.DISSDO = 0; // SDOx pin is controlled by the module
    SPI1CON1bits.MODE16 = 1; // Communication is word-wide (16 bits)
    SPI1CON1bits.SSEN = 0; // SSx pin is disable
    SPI1CON1bits.MSTEN = 1; // Master mode enabled
    
    SPI1CON1bits.SMP = 0; // Input data is sampled at the middle of data output time.
    SPI1CON1bits.CKE = 1; // Serial output data changes on transition from Idle clock state to active clock state
    SPI1CON1bits.CKP = 0; // Idle state for clock is a low level; active state is a high level
    
    // Max clock for SPI1 is 10 MHz in full-duplex mode
    // --> Divide CPU clock of 70 MHz by 7
    SPI1CON1bits.PPRE = 0b11; // Primary Prescaler = 1:1
    SPI1CON1bits.SPRE = 0b001; // Secondary Prescaler = 7:1

    // SPI1CON2 Register Settings
    SPI1CON2 = 0; // non-framed mode

    // SPI1STAT Register Settings
    SPI1STATbits.SPIEN = 1; // Enable SPI module

    // DMA2 channel for SPI Tx
    DMA2PAD = (volatile unsigned int) &SPI1BUF; // Point DMA to SPI1BUF
    DMA2CNT = BLOCK_LEN + 1;
    DMA2REQ = 0b00001010; // SPI1 transfer done
    DMA2CONbits.AMODE = 0; // Register Indirect with Post Increment
    DMA2CONbits.DIR = 1; // Ram-to-Peripheral Data Transfer
    DMA2CONbits.MODE = 1; // One-Shot Mode with Ping-Pong Disabled
    IFS1bits.DMA2IF = 0;
    IEC1bits.DMA2IE = 1;

    // DMA3 channel for SPI Rx
    DMA3PAD = (volatile unsigned int) &SPI1BUF; // Point DMA to SPI12BUF
    DMA3CNT = BLOCK_LEN + 1;
    DMA3REQ = 0b00001010; // SPI1 transfer done
    DMA3CONbits.AMODE = 0; // Register Indirect with Post Increment
    DMA3CONbits.DIR = 0; // Peripheral-to-Ram Data Transfer
    DMA3CONbits.MODE = 1; // One-Shot Mode with Ping-Pong Disabled
    IFS2bits.DMA3IF = 0;
    IEC2bits.DMA3IE = 1;
}

////////////////////////////////////////////////////////////////////////////////
// SRAM interface Tx interrupt
////////////////////////////////////////////////////////////////////////////////
void __attribute__((__interrupt__, no_auto_psv)) _DMA2Interrupt(void)
{
    // Clear the DMA2 Interrupt flag
    IFS1bits.DMA2IF = 0;
    
        // Finish transmission if Rx is also done
    if (!DMA3CONbits.CHEN)
    {
    // Start next transfer
    startNextTransfer();
    }

}

////////////////////////////////////////////////////////////////////////////////
// SRAM interface Rx interrupt
////////////////////////////////////////////////////////////////////////////////
void __attribute__((__interrupt__, no_auto_psv)) _DMA3Interrupt(void)
{
    // Clear the DMA3 Interrupt flag            
    IFS2bits.DMA3IF = 0;
    
        // Finish transmission if Tx is also done
    if (!DMA2CONbits.CHEN)
    {
    // Start next transfer
    startNextTransfer();    
    }
}
