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
 * @file wave_interface.h
 * @brief Function prototypes for wave interface
 * 
 * This file is part of the Audio/FX module
 */

#ifndef WAVEINTERFACE_H
#define	WAVEINTERFACE_H

#include <stdint.h>

/// SPI slaves assigned to 3-8 line multiplexer outputs according to actual slave select wiring
typedef enum
{
    /// External SRAM 0
    SPI_SLAVE_SRAM0 = 0,

    /// External SRAM 0
    SPI_SLAVE_SRAM1 = 1,

    /// External SRAM 0
    SPI_SLAVE_SRAM2 = 2,

    /// External SRAM 0
    SPI_SLAVE_SRAM3 = 3,

    /// DSP 0
    SPI_SLAVE_DSP0 = 4,

    /// DSP 1
    SPI_SLAVE_DSP1 = 5,

    /// DSP 2
    SPI_SLAVE_DSP2 = 6,

    /// DSP 3
    SPI_SLAVE_DSP3 = 7
} SPISlave;

/**
 * @brief Configure the wave/DSP interface
 */
void configureWaveInterface();

/**
 * @brief Start wave transfer
 * @param slave Selected slave for wave transfer
 * @param txData Tx data buffer in DMA RAM
 * @param rxData Rx data buffer in DMA RAM
 * @param count Number of elements to be transferred
 */
void startWaveTransfer(
        const SPISlave slave,
        int16_t * const txData,
        int16_t * const rxData,
        const uint16_t count);

/**
 * @brief Wait until current wave transfer is complete
 */
void waitWaveTransfer();

#endif
