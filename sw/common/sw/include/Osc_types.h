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

#ifndef OSC_TYPES_H
#define	OSC_TYPES_H

#include "Osc_enums.h"
#include "osc_stacked_saw_types.h"
#include "osc_feedback_types.h"
#include "osc_lowpass_noise_types.h"
#include "osc_colored_noise_types.h"

#include "fp_lib_types.h"
#include <stdint.h>
#include <stdbool.h>

//
typedef struct
{
    OscType type;
    int16_t pitch1; // Pitch on MIDI scale given in half-cents (including detune)
    int16_t pitch2; // Pitch on MIDI scale given in half-cents (including detune)
    _Q16 shape1;
    _Q16 shape2;
    _Q16 shape3;
    _Q16 crossModAmount;
    _Q16 ringModAmount;
    _Q16 syncPhase;
    _Q15 balance; // Has to be signed so it can be used with DSP Acc
} OscParams;

//
typedef struct
{
    union
    {    
        _Q32 phase;
        OscStackedSawState stackedSawState;
        OscFeedbackState feedbackState;
        OscLowPassNoiseState lowPassNoiseState;
    } osc1;
    
    union
    {
        _Q32 phase;
        OscColoredNoiseState coloredNoiseState;
    } osc2;
    
    _Q15 lastOsc2Output;
} OscState;

#endif
