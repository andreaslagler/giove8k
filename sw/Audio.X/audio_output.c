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
 * @file audio output.c
 * @brief Implementation of audio output
 * 
 * This file is part of the Audio/FX module
 */

#include "audio_output.h"
#include "block_len_def.h"
#include <stdbool.h>
#include <xc.h>

/// DMA Buffer for DCI DMA channel
static int16_t dciDMABufferA[2 * BLOCK_LEN] __attribute__((space(dma)));
static int16_t dciDMABufferB[2 * BLOCK_LEN] __attribute__((space(dma)));

/**
 * @brief Configure audio output
 * 
 * Configure the audio stereo DAC module and DMA channels 0/1 for right/left DAC channels
 */
void configureAudioOutput()
{
    // Initialize DCI with DMA

    ////////////////////////////////////////////////////////////////////////////
    // DMA Channel 0 set to DAC1RDAT

    // Set addressing mode to register indirect with post-increment
    DMA0CONbits.AMODE = 0;

    // Set DMA Mode to continuous with ping-pong enabled
    DMA0CONbits.MODE = 2;

    // Set data direction to Ram-to-Peripheral
    DMA0CONbits.DIR = 1;

    // Set peripheral address and interrupt source to DCI Tx
    DMA0PAD = (volatile unsigned int) &TXBUF0;
    DMA0REQ = 0x3C;

    // Set DMA buffer pointer and length
    DMA0STA = __builtin_dmaoffset(dciDMABufferA);
    DMA0STB = __builtin_dmaoffset(dciDMABufferB);
    DMA0CNT = 2 * BLOCK_LEN - 1;

    // Disable DMA 0 interrupt (not needed in ping-pong mode)
    IFS0bits.DMA0IF = 0;
    IEC0bits.DMA0IE = 0;

    // Enable DMA channels 0/1
    DMA0CONbits.CHEN = 1;

    ////////////////////////////////////////////////////////////////////////////
    // DCI Configuration

    DCICON1 = 0;
    DCICON1bits.DCIEN = 1; /* Module is enabled */
    DCICON1bits.DCISIDL = 0; /* Continue operation in idle */
    DCICON1bits.DLOOP = 0; /* Loopback mode is disabled */
    DCICON1bits.CSCKD = 0; /* DCI is master - CSCK is output */
    DCICON1bits.CSCKE = 1; /* Data is sampled on rising edge */
    DCICON1bits.COFSD = 0; /* DCI is master - COFS is output */
    DCICON1bits.UNFM = 0; /* Transmit zeroes on TX underflow */
    DCICON1bits.CSDOM = 0; /* Transmit 0 on disabled time slots */
    DCICON1bits.DJST = 0; /* COFS and CSDO start together */
    DCICON1bits.COFSM = 1; /* DCI mode is I²S FS mode */

    DCICON2 = 0;
    DCICON2bits.BLEN = 0; /* Using DMA */
    DCICON2bits.COFSG = 0; /* Data frame has one word */
    DCICON2bits.WS = 0b1111; /* Word size is 16 bits */

    DCICON3 = 0;
    DCICON3bits.BCG = 12; /* fs ~ 48 kHz */

    TSCON = 3; /* One transmit time slot */
    RSCON = 0; /* No receive time slot */

    _DCIIF = 0; /* Clear Interrupt flag */
    _DCIIE = 0; /* Disabled since DMA is used */
}

/**
 * @brief Start DMA transfer to DCI
 * 
 * Copy BLOCK_LEN values for each stereo channel to DMA buffer and start DMA transfer to DCI
 * @param dacLeftData
 * @param dacRightData
 */
void startAudioOutputTransfer(
        const int16_t * dacLeftData,
        const int16_t * dacRightData)
{
    // Wait while current ping-pong buffer is still in use
    const uint16_t bufferIdx = DMACS1bits.PPST0;
    while (DMACS1bits.PPST0 == bufferIdx);    
    
    // Copy data block to DMA buffer
    int16_t * const dciDMABuffer[2] = {dciDMABufferA, dciDMABufferB};
    int16_t * dst = dciDMABuffer[bufferIdx];
    for (uint16_t cnt = 0; cnt < BLOCK_LEN; ++cnt)
    {
        *dst++ = *dacLeftData++;
        *dst++ = *dacRightData++;
    }
}