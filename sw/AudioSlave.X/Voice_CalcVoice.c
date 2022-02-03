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

#include "voice.h"
#include "fp_lib_types.h"
#include "fp_lib_typeconv.h"
#include "fp_lib_mul.h"
#include "voice_types.h"
#include "block_len_def.h"
#include "oscillator.h"
#include "filter.h"
#include "amp.h"
#include "lfo.h"
#include "env_adsr.h"
#include "mod_mixer.h"
#include "glide.h"
#include "synth_types.h"
#include "lfo_sync_to_key.h"


#include <stdlib.h> // max()


////////////////////////////////////////////////////////////////////////////////
// Calculate output signal for given voice state
void calcVoice(
        const PatchParams * const patchParams,
        const VoiceParams * const voiceParams,
        VoiceState * const voiceState,
        _Q15 * const xWorkBuffer, // Has to be allocated in .xdata, size = BLOCK_LEN
        _Q15 * const yWorkBuffer, // Has to be allocated in .ydata, size = 6
        DSPBuffer * buffer)
{
    ////////////////////////////////////////////////////////////////////////////
    // work buffers

    ////////////////////////////////////////////////////////////////////////////
    // Unpack voice parameters from bitfield

    // Expand 7-bit Velocity to Q0.16 number
    const _Q16 velocity = voiceParams->velocity * 0x204 + (voiceParams->velocity >> 5);

    // Set trigger flag
    const bool trigger = voiceParams->trigger;

    // Set gate flag
    const bool gate = voiceParams->gate;

    // Convert note from semitone to half-cent
    int16_t note = voiceParams->note * 200;
    
    ////////////////////////////////////////////////////////////////////////////
    // Glide
    const GlideParams glideParams = {
        .rate = patchParams->glideParams.rate,
        .note = note
    };

    // Calculate glide output
    note = updateGlide(
            &glideParams,
            &voiceState->glideState);

    ////////////////////////////////////////////////////////////////////////////
    // Modulation sources

    ModSourceFilterFreq * const modSourceFilterFreq = (ModSourceFilterFreq *)(yWorkBuffer); // Has to be allocated in .ydata
    ModSource * const modSource = &modSourceFilterFreq->modSource; // Has to be allocated in .ydata
    
    // Common modulation sources
    
    // Modulation wheel
    modSource->modWheelValue = patchParams->modulation;

    // Aux envelope
    modSource->auxEnvValue = convert_Q16_Q15(updateEnvADSR(
            &patchParams->auxEnvParams,
            gate,
            trigger,
            &voiceState->auxEnvState));

    // LFO 1
    modSource->lfo1Value = patchParams->lfo1Value;

    // LFO 2 may depend on other modulation sources and is updated last
    modSource->lfo2Value = (patchParams->lfoSync == ELFO_SYNC_KEY) ?
            updateLFOSyncToKey(
            &patchParams->lfo2Params,
            trigger,
            patchParams->lfoSyncPhase,
            modSource,
            &patchParams->modAmountLFO2Rate,
            &voiceState->lfo2State) // Calculate updated LFO 2 value if synced to key
            :
            patchParams->lfo2Value; // Use global value

    // Additional filter cutoff modulation sources
 
    // Note played by this voice
    modSourceFilterFreq->note = note;

    // Filter envelope
    modSourceFilterFreq->envValue = convert_Q16_Q15(updateEnvADSR(
            &patchParams->filterEnvParams,
            gate,
            trigger,
            &voiceState->filterEnvState));

    ////////////////////////////////////////////////////////////////////////////
    // Oscillator 1 + 2
    ////////////////////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////////////////////
    // Calculate modified oscillator parameters
    const OscParams oscParams = {

        // Combined oscillator 1 + 2 type
        .type = patchParams->oscParams.type,

        // Oscillator 1 pitch
        .pitch1 = calcOscPitch(
        note,
        patchParams->oscParams.pitch1,
        modSource,
        &patchParams->modAmountOsc1Pitch),

        // Oscillator 2 pitch
        .pitch2 = calcOscPitch(
        note,
        patchParams->oscParams.pitch2,
        modSource,
        &patchParams->modAmountOsc2Pitch),

        // Oscillator 1 shape parameter 1
        .shape1 = calcMod_Q15(
        patchParams->oscParams.shape1,
        modSource,
        &patchParams->modAmountOsc1Shape1),

        // Oscillator 1 shape parameter 2
        .shape2 = calcMod_Q15(
        patchParams->oscParams.shape2,
        modSource,
        &patchParams->modAmountOsc1Shape2),

        // Oscillator 2 shape parameter
        .shape3 = calcMod_Q15(
        patchParams->oscParams.shape3,
        modSource,
        &patchParams->modAmountOsc2Shape),

        // Cross modulation amount       
        .crossModAmount = calcMod_Q16(
        patchParams->oscParams.crossModAmount,
        modSource,
        &patchParams->modAmountCrossModAmount),

        // Ring modulation amount
        .ringModAmount = calcMod_Q16(
        patchParams->oscParams.ringModAmount,
        modSource,
        &patchParams->modAmountRingModAmount),

        // Oscillator sync phase
        .syncPhase = calcMod_Q16(
        patchParams->oscParams.syncPhase,
        modSource,
        &patchParams->modAmountOscSyncPhase),

        // Oscillator 1/2 balance
        .balance = calcMod_Q16(
        patchParams->oscParams.balance,
        modSource,
        &patchParams->modAmountOscBalance)
    };

    ////////////////////////////////////////////////////////////////////////////
    // Calculate actual oscillator output
    calcOsc(
            &oscParams,
            &voiceState->oscState,
            xWorkBuffer);

    ////////////////////////////////////////////////////////////////////////////
    // Filter
    ////////////////////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////////////////////
    // Calculate modified filter parameter
    const FilterParams filterParams = {
        // No modification of filter type 
        .type = patchParams->filterParams.type,

        // Modified filter freq
        .freq = calcFilterFreq(
        patchParams->filterParams.freq, // filterFreq, //
        modSourceFilterFreq,
        &patchParams->modAmountFilterFreq),

        // Modified filter shape
        .shape = calcMod_Q16(
        patchParams->filterParams.shape,
        modSource,
        &patchParams->modAmountFilterShape)
    };

    ////////////////////////////////////////////////////////////////////////////
    // Calculate actual filter output (in-place))
    _Q15 * const filterCoeffs = (_Q15 *)(yWorkBuffer); // Has to be allocated in .ydata
    calcFilter(
            &filterParams,
            &voiceState->filterState,
            filterCoeffs,
            xWorkBuffer);

    ////////////////////////////////////////////////////////////////////////////
    // Amplifier
    ////////////////////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////////////////////
    // Amp envelope amount
    const _Q16 ampEnvValue = updateEnvADSR(
            &patchParams->ampEnvParams,
            gate,
            trigger,
            &voiceState->ampEnvState);

    // Calculate modified gain
    const _Q16 gain = calcMod_Q16(
            patchParams->ampParams.gain,
            modSource,
            &patchParams->modAmountAmpLevel);

    const AmpParams ampParams = {
        // Modified gain
        .gain = mul_Q16_Q16(velocity, mul_Q16_Q16(ampEnvValue, gain)),

        // Modified pan
        .pan = calcMod_Q15(
        patchParams->ampParams.pan,
        modSource,
        &patchParams->modAmountAmpPan)
    };

    // Calculate actual amplifier output into stereo output buffer
    calcAmp(
            &ampParams,
            xWorkBuffer,
            buffer->bufferLeft,
            buffer->bufferRight);
}