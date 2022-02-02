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

#ifndef VOICE_TYPES_H
#define	VOICE_TYPES_H

#include "glide_types.h"
#include "osc_types.h"
#include "filter_types.h"
#include "lfo_types.h"
#include "env_adsr_types.h"
#include "tone_control_2band_types.h"

// State of a synthesizer voice to be stored between two sample-generating periods
typedef struct
{
    GlideState glideState;
    OscState oscState;
    FilterState filterState;
    LFOState lfo2State;
    ADSRState auxEnvState;
    ADSRState filterEnvState;
    ADSRState ampEnvState;
} VoiceState;

#endif
