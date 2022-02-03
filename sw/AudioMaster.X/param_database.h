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
 * @file param_database.h
 * @brief Function prototypes for parameter database
 * 
 * This file is part of the Audio/FX module
 */

#ifndef PARAM_DATABASE_H
#define	PARAM_DATABASE_H

#include "synth_Types.h"
#include "stereo_chorus_types.h"
#include "stereo_delay_types.h"
#include "tone_control_2band_types.h"
#include "bitcrusher_types.h"
#include <stdint.h>

/**
 * @brief Update DSP parameters from from raw parameters
 * 
 * @param patchParams Raw patch parameters for current DSP in unsigned 8-bit integer format
 * @param sceneParams Raw scene parameters in unsigned 8-bit integer format 
 * @param controllerParams Raw controller parameters in unsigned 8-bit integer format
 * @param voiceParams Voice parameters for current DSP
 * @param dspBuffer Wave/DSP parameters for current DSP
 */
void updateWaveDSPParams(
        const uint8_t * patchParams,
        const uint8_t * sceneParams,
        const uint8_t * controllerParams,
        VoiceParams * voiceParams,
        DSPBuffer * dspBuffer);


void updateBitcrusherParams(
        const uint8_t * patchParams,
        BitcrusherParams * params);

#endif