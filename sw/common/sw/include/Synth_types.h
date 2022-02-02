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

#ifndef SYNTH_TYPES_H
#define	SYNTH_TYPES_H

#include "fp_lib_types.h"
#include "synth_def.h"
#include "voice_manager_types.h"
#include "env_adsr_types.h"
#include "lfo_types.h"
#include "modMixer_types.h"
#include "filter_types.h"
#include "amp_types.h"
#include "osc_types.h"
#include "glide_types.h"
#include "stereo_chorus_types.h"
#include "tone_control_2band_types.h"
#include "bitcrusher_types.h"
#include "stereo_distortion_types.h"
#include "stereo_delay_types.h"
#include "block_len_def.h"

#include <stdint.h>
#include <stdbool.h>


//
typedef struct
{
    OscParams oscParams;
    
    GlideParams glideParams;

    FilterParams filterParams;
    
    AmpParams ampParams;

    _Q15 modulation;
    _Q15 lfo1Value;
    _Q15 lfo2Value;

    LFOParams lfo2Params;
    LFOSync lfoSync;
    _Q16 lfoSyncPhase;

    ADSRParams auxEnvParams;
    ADSRParams filterEnvParams;
    ADSRParams ampEnvParams;

    ModAmount modAmountOsc1Pitch;
    ModAmount modAmountOsc2Pitch;

    ModAmount modAmountOsc1Shape1;
    ModAmount modAmountOsc1Shape2;
    ModAmount modAmountOsc2Shape;

    ModAmount modAmountOscBalance;

    ModAmount modAmountOscSyncPhase;

    ModAmount modAmountCrossModAmount;
    ModAmount modAmountRingModAmount;

    ModAmount modAmountFilterShape;

    ModAmountFilterFreq modAmountFilterFreq;

    ModAmount modAmountAmpLevel;
    ModAmount modAmountAmpPan;

    ModAmountLFORate modAmountLFO2Rate;
    
    ToneControl2BandParams toneControlParams;
    ChorusParams chorusParams;
    BitcrusherParams bitcrusherParams;
    DistortionParams distortionParams;
    StereoDelayParams delayParams;
} PatchParams;

// Buffer type for data transfer between Audio/Fx and Wave DSPs
typedef union
{   
    // Waveform data representation
    int16_t buffer[BLOCK_LEN * 2];
    struct
    {
        int16_t bufferLeft[BLOCK_LEN];
        int16_t bufferRight[BLOCK_LEN];
    };
    
    // Parameter representation
    struct
    {
        VoiceParams voiceParams[NOF_VOICES_DSP];
        PatchParams patchParams;
    };
 } DSPBuffer;


#endif
