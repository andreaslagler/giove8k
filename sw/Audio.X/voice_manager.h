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
 * @file voice_manager.h
 * @brief Function prototypes for voice manager
 * 
 * This file is part of the Audio/FX module
 */

#ifndef VOICEMANAGER_H
#define	VOICEMANAGER_H

#include "voice_manager_types.h"
#include <stdint.h>
#include <stdbool.h>

/**
 * @brief Get raw voice parameters for selected DSP
 * @param dspIdx zero-based DSP index (0 ... NOF_DSPS-1)
 * @return Pointer to voice parameters for selected DSP
 */
VoiceParams * getVoiceParams(uint16_t dspIdx);

/**
 * @brief Callback function for received note message
 * @param noteMessage Note message of currently played note
 * @param layerMode Layer mode Single/Dual/Split
 * @todo legato Flag indicating legato is enabled
 */
void onNoteMessage(
        uint16_t noteMessage,
        uint16_t layerMode,
        bool legato);

/**
 * @brief Release all notes
 */
void allNotesOff();

#endif
