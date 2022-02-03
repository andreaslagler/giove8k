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
 * @file wave_interface.c
 * @brief Implementation of wave interface
 * 
 * The wave interface uses SPI1 in master mode to transfer parameters to and 
 * waveform data from multiple DSPs and waveform data from and to multiple
 * serial SRAMs. The transfer uses DMA channels 2 and 3 for SPI Tx and Rx,
 * respectively.\n
 * This file is part of the Audio/FX module
 */

#include <xc.h>
#include <stdint.h>
#include <stdbool.h>

#include "wave_interface.h"
#include "block_len_def.h"

/// Base address of DMA memory address space
extern void * _DMA_BASE;

/// Slave select pin
#define SLAVE_SELECT LATBbits.LATB12

/// Octal line multiplexer pins
#define SS_MUX0 (LATBbits.LATB10)
#define SS_MUX1 (LATBbits.LATB11)

/**
 * @brief Set DMA Tx buffer pointer
 * @param buffer
 */
inline static void setTxBuffer(int16_t * buffer)
{
    // Consider DMA offset
    DMA2STA = (uint16_t) buffer + (uint16_t) &_DMA_BASE;
}

/**
 * @brief Set DMA Rx buffer pointer
 * @param buffer
 */
inline static void setRxBuffer(int16_t * buffer)
{
    // Consider DMA offset
    DMA3STA = (uint16_t) buffer + (uint16_t) &_DMA_BASE;
}

/**
 * @brief Re-Enable Tx
 */
inline static void enableTx()
{
    DMA2CONbits.CHEN = 1;
}

/**
 * @brief Re-Enable Rx
 */
inline static void enableRx()
{
    DMA3CONbits.CHEN = 1;
}

/**
 * @brief Disable Rx
 */
inline static void disableRx()
{
    DMA3CONbits.CHEN = 0;
}

/**
 * @brief Set DMA count for Tx/Rx
 * @param count
 */
inline static void setDMACount(const uint16_t count)
{
    // Set DMA count for Tx
    DMA2CNT = count;

    // Set DMA count for Rx
    DMA3CNT = count;
}

/**
 * @brief Select slave for wave transfer
 * @param line
 */
static inline void selectSlave(const uint16_t slaveIdx)
{
    // Select line on octal multiplexer
    SS_MUX0 = slaveIdx & 0b1;
    SS_MUX1 = (slaveIdx >> 1) & 0b1;

    // Clear /SS 
    // NB.
    // Chip select setup time is 25ns for 23LC1024 (1 cycle @ 40 MHz)
    // Chip select setup time is 120ns for dspic33ep (5 cycles @ 40 MHz)
    SLAVE_SELECT = 0;
}

/**
 * @brief Configure the wave/DSP interface
 */
void configureWaveInterface()
{
    // NB: Assuming SPI1 module and DMA channel are in default POR state
    // Interrupt Controller Settings
    IFS0bits.SPI1IF = 0;

    // SPI1CON1 Register Settings
    SPI1CON1bits.MODE16 = 1; // Communication is word-wide (16 bits)
    SPI1CON1bits.MSTEN = 1; // Master mode Enabled
    SPI1CON1bits.CKE = 1; // see 23LC1024 spec
    SPI1CON1bits.CKP = 0; // see 23LC1024 spec

    SPI1CON1bits.SMP = 0; // see 23LC1024 spec
    SPI1CON1bits.PPRE = 0b10; // Primary Prescaler = 4:1
    SPI1CON1bits.SPRE = 0b111; // Secondary Prescaler = 1:1

    // SPI1CON2 Register Settings
    SPI1CON2bits.FRMEN = 0; // Framed mode Disabled

    // SPI1STAT Register Settings
    SPI1STATbits.SPISIDL = 0; // Continue module operation in Idle mode
    SPI1STATbits.SPIROV = 0; // No Receive Overflow has occurred
    SPI1STATbits.SPIEN = 1; // Enable SPI module

    // Setup DMA channel 2 for SPI1 Tx
    IFS1bits.DMA2IF = 0;
    IEC1bits.DMA2IE = 1;

    DMA2CONbits.AMODE = 0; /* Register Indirect with Post Increment */
    DMA2CONbits.MODE = 0b01; /* One-Shot Mode with Ping-Pong Disabled */
    DMA2CONbits.DIR = 1; /* Ram-to-Peripheral Data Transfer */
    DMA2PAD = (volatile uint16_t) & SPI1BUF; /* Point DMA to SPI1BUF */
    DMA2REQ = 0x000A; // SPI1 transfer done


    // Setup DMA channel 3 for SPI1 Rx
    IFS2bits.DMA3IF = 0;
    IEC2bits.DMA3IE = 1;

    DMA3CONbits.AMODE = 0; /* Register Indirect with Post Increment */
    DMA3CONbits.MODE = 1; /* One-Shot Mode with Ping-Pong Disabled */
    DMA3CONbits.DIR = 0; /* Peripheral-To-Ram Data Transfer */
    DMA3PAD = (volatile uint16_t) & SPI1BUF; /* Point DMA to SPI1BUF */
    DMA3REQ = 0x000A; // SPI1 transfer done
}

/**
 * @brief Wait until current wave transfer is complete
 */
void waitWaveTransfer()
{
    while (DMA2CONbits.CHEN);
    while (DMA3CONbits.CHEN);
}

/**
 * @brief Start actual DMA transfer after slave has been selected
 */
inline static void startDMATransfer()
{
    // Start transmission
    // Force first DMA transfer, here: load first data word into SPI buffer
    DMA2REQbits.FORCE = 1;
    while (DMA2REQbits.FORCE);
}

/**
 * @brief Start wave transfer
 * @param slave Selected slave for wave transfer
 * @param txData Tx data buffer in DMA RAM
 * @param rxData Rx data buffer in DMA RAM
 * @param count Number of elements to be transferred
 */
void startWaveTransfer(
        const uint16_t dsp,
        int16_t * const txData,
        int16_t * const rxData,
        const uint16_t count)
{
    // Wait for current transfer to complete
    waitWaveTransfer();
    
    // Select slave
    selectSlave(dsp);
    
    // Set up DMA
    setDMACount(count - 1);
    
    // Configure Tx
    setTxBuffer(txData);
    enableTx();
    
    // Configure Rx (if needed))
    if (0 != rxData)
    {
        setRxBuffer(rxData);
        enableRx();
    }
    else
    {
        disableRx();
    }
    
    // Start transfer
    startDMATransfer();
}

/**
 * Interrupt service routine for DMA channel 2
 */
void __attribute__((interrupt, no_auto_psv)) _DMA2Interrupt(void)
{
    // Clear the Interrupt Flag
    IFS1bits.DMA2IF = 0;

    // Finish transmission if Rx is also done
    if (!DMA3CONbits.CHEN)
    {
        // Stop transmission by raising /SS
        SLAVE_SELECT = 1;
    }
}

/**
 * Interrupt service routine for DMA channel 3 
 */
void __attribute__((interrupt, no_auto_psv)) _DMA3Interrupt(void)
{
    // Clear the DMA3 Interrupt Flag
    IFS2bits.DMA3IF = 0;

    // Finish transmission if Tx is also done
    if (!DMA2CONbits.CHEN)
    {
        // Stop transmission by raising /SS
        SLAVE_SELECT = 1;
    }
}

