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

#ifndef UI_PARAM_ENUMS_H
#define UI_PARAM_ENUMS_H

#include <stdint.h>

enum class UIParam : uint8_t
{
    // Potentiometer params
    OSC1_PITCH = 0,
    OSC1_DETUNE,
    OSC1_SHAPE1,
    OSC1_SHAPE2,
    OSC2_PITCH,
    OSC2_DETUNE,
    OSC2_SHAPE,
    OSC_SYNC_PHASE,
    OSC_CROSSMOD,
    OSC_RINGMOD,
    OSC_BALANCE,
    GLIDE_TIME,
    FILTER_FREQ,
    FILTER_SHAPE,
    FILTER_KEYTRACK,
    FILTER_ENV_AMOUNT,
    FILTER_ENV_A,
    FILTER_ENV_D,
    FILTER_ENV_S,
    FILTER_ENV_R,
    LEVEL,
    AMP_ENV_A,
    AMP_ENV_D,
    AMP_ENV_S,
    AMP_ENV_R,
    PAN,
    LFO1_RATE,
    LFO2_RATE,
    LFO_SYNC_PHASE,    
    AUX_ENV_A,
    AUX_ENV_D,
    AUX_ENV_S,
    AUX_ENV_R,
    FX_PARAM_VALUE,
    MOD_AMOUNT,
    BASS,
    TREBLE,
    ARP_SPEED,
    
    // Encoder params
    MOD_SRC,
    MOD_DST,
    FX_PARAM,
    ARP_PATTERN,
    
    // Push-button params
    OSC1_WAVEFORM,
    OSC2_WAVEFORM,
    OSC_SYNC,
    LEGATO,
    FILTER_TYPE,
    LFO1_WAVEFORM,
    LFO2_WAVEFORM,
    LFO_SYNC,
    SELECTED_LAYER,
    LAYER_MODE,
    ARP_MODE,
    NOFENTRIES,
    MIN = 0,
    MAX = NOFENTRIES-1
};

#endif