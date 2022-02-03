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
 * @file audio output.h
 * @brief Function prototypes for audio output
 * 
 * This file is part of the Audio/FX module
 */

#ifndef AUDIO_OUTPUT_H
#define	AUDIO_OUTPUT_H

#include <stdint.h>

/**
 * @brief Configure audio output
 * 
 * Configure the audio stereo DAC module and DMA channels 0/1 for right/left DAC channels
 */
void configureAudioOutput();

/**
 * @brief Start DMA transfer to audio DAC
 * 
 * Copy BLOCK_LEN values for each stereo channel to DMA buffers and start DMA transfer to audio DAC
 * @param dacLeftData
 * @param dacRightData
 */
void startAudioOutputTransfer(
        const int16_t * dacLeftData,
        const int16_t * dacRightData);

#endif
