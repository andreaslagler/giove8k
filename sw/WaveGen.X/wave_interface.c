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

#include <xc.h>
#include "wave_interface.h"
#include "block_len_def.h"
#include <stdint.h>

////////////////////////////////////////////////////////////////////////////////
// DMA buffer definitions
////////////////////////////////////////////////////////////////////////////////

static DSPBuffer txBuffer __attribute__((space(xmemory)));
static DSPBuffer rxBuffer __attribute__((space(xmemory)));


    // Mem copy implementation for fixed block length
    inline static void copyBlock(
        const int16_t * piSrc,
        int16_t * piDst)
{
    // Copy one block 
    __asm__ volatile(
            "\
        repeat  #%[Len]-1                  ;1 C \n \
        mov     [%[Src]++], [%[Dst]++]     ;1 C \n \
        ; 1 + N cycles total"
            : [Dst] "+r"(piDst), [Src] "+r"(piSrc) /*out*/
            : [Len] "i"(BLOCK_LEN * 2) /*in*/
            : /*clobbered*/
            );
}


//
const PatchParams * getPatchParams()
{
    return &(rxBuffer.patchParams);
}

//
const VoiceParams * getVoiceParams(const uint8_t uiVoice)
{
    // Cache voice parameters
    return &rxBuffer.voiceParams[uiVoice];
}

////////////////////////////////////////////////////////////////////////////////
// Wait for transfer to complete
////////////////////////////////////////////////////////////////////////////////
inline static void waitForWaveTransfer()
{
    // Wait while /SS is low
    while (!PORTBbits.RB12);
    
    // Wait while DMA channels are active (CHEN flag will be cleared on DMA interrupt)
    while (DMA1CONbits.CHEN);
    while (DMA0CONbits.CHEN);
}

////////////////////////////////////////////////////////////////////////////////
// Initiate Transfer of given data block
////////////////////////////////////////////////////////////////////////////////
void transferWaveBuffer(const int16_t * const piTxData)
{
    waitForWaveTransfer();
    
    // Copy data to DMA buffer
    copyBlock(piTxData, txBuffer.buffer);

    // Enable DMA channels
    DMA1CONbits.CHEN = 1;
    DMA0CONbits.CHEN = 1;
    
    // Force SPI transfer
    DMA0REQbits.FORCE = 1;
    while (DMA0REQbits.FORCE == 1);
}

////////////////////////////////////////////////////////////////////////////////
// Configure SPI2 for wave transfer
////////////////////////////////////////////////////////////////////////////////
void configureWaveInterface(void)
{
    // Interrupt Controller Settings
    IFS2bits.SPI2IF = 0;

    // SPI2CON1 Register Settings
    SPI2CON1bits.DISSDO = 0; // SDOx pin is controlled by the module
    SPI2CON1bits.MODE16 = 1; // Communication is word-wide (16 bits)
    SPI2CON1bits.SMP = 0; // Input data is sampled at the middle of data output time.
    SPI2CON1bits.CKE = 1; // Serial output data changes on transition from Idle clock state to active clock state
    SPI2CON1bits.CKP = 0; // Idle state for clock is a low level; active state is a high level
    SPI2CON1bits.SSEN = 1; // SSx pin is used for Slave mode
    SPI2CON1bits.MSTEN = 0; // Master mode disabled

    // SPI2CON2 Register Settings
    SPI2CON2 = 0; // non-framed mode

    // SPI2STAT Register Settings
    SPI2STATbits.SPIEN = 1; // Enable SPI module

    // DMA0 channel for SPI Tx
    DMA0STAL = (unsigned int) __builtin_dmaoffset(&txBuffer.buffer);
    DMA0STAH = (unsigned int) __builtin_dmapage(&txBuffer.buffer);
    DMA0PAD = (volatile unsigned int) &SPI2BUF; // Point DMA to SPI2BUF
    DMA0CNT = BLOCK_LEN * 2 - 1;
    DMA0REQ = 0x0021; // SPI2 transfer done
    DMA0CONbits.AMODE = 0; // Register Indirect with Post Increment
    DMA0CONbits.DIR = 1; // Ram-to-Peripheral Data Transfer
    DMA0CONbits.MODE = 1; // One-Shot Mode with Ping-Pong Disabled
    IFS0bits.DMA0IF = 0;
    IEC0bits.DMA0IE = 1;

    // DMA1 channel for SPI Rx
    DMA1STAL = (unsigned int) __builtin_dmaoffset(&rxBuffer.buffer);
    DMA1STAH = (unsigned int) __builtin_dmapage(&rxBuffer.buffer);
    DMA1PAD = (volatile unsigned int) &SPI2BUF; // Point DMA to SPI2BUF
    DMA1CNT = BLOCK_LEN * 2 - 1;
    DMA1REQ = 0x0021; // SPI2 transfer done
    DMA1CONbits.AMODE = 0; // Register Indirect with Post Increment
    DMA1CONbits.DIR = 0; // Peripheral-to-Ram Data Transfer
    DMA1CONbits.MODE = 1; // One-Shot Mode with Ping-Pong Disabled
    IFS0bits.DMA1IF = 0;
    IEC0bits.DMA1IE = 1;
}

////////////////////////////////////////////////////////////////////////////////
// Wave interface Tx interrupt
////////////////////////////////////////////////////////////////////////////////
void __attribute__((__interrupt__, no_auto_psv)) _DMA0Interrupt(void)
{
    // Clear the DMA0 Interrupt flag
    IFS0bits.DMA0IF = 0;
}

////////////////////////////////////////////////////////////////////////////////
// Wave interface Tx interrupt
////////////////////////////////////////////////////////////////////////////////
void __attribute__((__interrupt__, no_auto_psv)) _DMA1Interrupt(void)
{
    // Clear the DMA1 Interrupt flag            
    IFS0bits.DMA1IF = 0;
}
