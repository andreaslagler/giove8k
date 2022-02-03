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
 * @file param_database.c
 * @brief Implementation of parameter database
 * 
 * This file is part of the Audio/FX module
 */

#include "param_database.h"
#include "DSPParam_enums.h"
#include "synth_def.h"
#include "synth_types.h"
#include "lfo_types.h"
#include "lfo.h"
#include "fp_lib_types.h"
#include "fp_lib_typeconv.h"
#include "fp_lib_mul.h"

/// LFO 1 state
static LFOState lfo1State;

/// LFO 2 state
static LFOState lfo2State;

/**
 * @brief Multiply-Add of two Q0.15 signed fractional numbers to Q15.16 accumulator
 * 
 * @param sum Accumulated sum of products in Q15.16 format
 * @param arg1 Factor in Q0.15 format
 * @param arg2 Factor in Q0.15 format
 * @return Accumulated sum of products in Q15.16 format
 */
inline static _Q1516 mac_Q15_Q15(
        const _Q1516 sum,
        const _Q15 arg1,
        const _Q15 arg2)
{
    // Calculate product
    const _Q15 prod = mul_Q15_Q15(arg1, arg2);
    
    // Add product twice because of decimal point shift
    return (sum + prod) + prod;
}

/**
 * @brief Conversion of raw parameter to unsigned 16-bit integer
 * 
 * Raw parameter is interpreted as unsigned 8-bit integer and converted to unsigned 16-bit integer format
 * @param rawParam Raw parameter in unsigned 8-bit integer format
 * @return Parameter in unsigned 16-bit integer format
 */
static inline uint16_t convertRawParamUInt8ToUInt16(const uint8_t rawParam)
{
    return (uint16_t) rawParam; // This should invoke ze instruction
}

/**
 * @brief Conversion of raw parameter to Q0.16 format
 * 
 * Raw parameter is interpreted as Q0.8 number and converted to Q0.16 format
 * @param rawParam Raw parameter in unsigned 8-bit integer format
 * @return Parameter in Q0.16 format
 */
static inline _Q16 convertRawParamUInt8ToQ16(const uint8_t rawParam)
{
    return convertRawParamUInt8ToUInt16(rawParam) * 0x101; // This should invoke mulw.uu instruction
}

/**
 * @brief Conversion of raw parameter to signed 16-bit integer
 * 
 * Raw parameter is interpreted as signed 8-bit integer and converted to signed 16-bit integer format
 * @param rawParam Raw parameter in unsigned 8-bit integer format
 * @return Parameter in signed 16-bit integer format
 */
static inline int16_t convertRawParamInt8ToInt16(const uint8_t rawParam)
{
    return (int16_t) ((int8_t) rawParam); // This should invoke se instruction;
}

/**
 * @brief Conversion of raw parameter to Q0.15 format
 * 
 * Raw parameter is interpreted as Q0.7 number and converted to Q0.15 format
 * @param rawParam Raw parameter in unsigned 8-bit integer format
 * @return Parameter in Q0.15 format
 */
static inline _Q15 convertRawParamInt8ToQ15(const uint8_t rawParam)
{
    // TODO geht vielleicht auch mit 16 x 32 bit multiplikation
    const int16_t iResult = convertRawParamInt8ToInt16(rawParam);
    _Q15 qResult = iResult << 8;
    const int16_t iPositiveMask = ~(iResult >> 15); // 0 for negative param, 0xFFFF for positive param
    qResult += (iPositiveMask & (((uint16_t) (iResult * 0x204)) >> 8));
    return qResult;
}

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
        const uint8_t * const patchParams,
        const uint8_t * const sceneParams,
        const uint8_t * const controllerParams,
        VoiceParams * const voiceParams,
        DSPBuffer * const dspBuffer)
{
    ////////////////////////////////////////////////////////////////////////////
    // Voices
    for (uint8_t cntVoice = 0; cntVoice < NOF_VOICES_DSP; ++cntVoice)
    {
        dspBuffer->voiceParams[cntVoice] = voiceParams[cntVoice];

        // Clear trigger flag
        voiceParams[cntVoice].trigger = false; // TODO außerhalb dieser Funktion machen
    }

    ////////////////////////////////////////////////////////////////////////////
    // Modulation wheel (Convert unsigned 7-bit MSB and LSB to one Q0.15 value)
    const uint16_t modulationMSB = convertRawParamUInt8ToUInt16(controllerParams[ECONTROLLER_PARAM_MODULATION_MSB]);
    const uint16_t modulationLSB = convertRawParamUInt8ToUInt16(controllerParams[ECONTROLLER_PARAM_MODULATION_LSB]);
    dspBuffer->patchParams.modulation = (modulationMSB << 8) + (modulationLSB << 1) + (modulationMSB >> 6); // Map 0..16383 to 0..32767

    ////////////////////////////////////////////////////////////////////////////
    // Pitch bend (Convert unsigned 7-bit MSB and LSB to one Q0.15 value)
    const uint16_t pitchBendMSB = convertRawParamUInt8ToUInt16(controllerParams[ECONTROLLER_PARAM_PITCHBEND_MSB]);
    const uint16_t pitchBendLSB = convertRawParamUInt8ToUInt16(controllerParams[ECONTROLLER_PARAM_PITCHBEND_LSB]);
    _Q15 pitchBend = (pitchBendMSB << 9) + (pitchBendLSB << 2) + (pitchBendMSB >> 5) - 32768;
    const uint16_t pitchBendSensitivity = 12 * 100 * 2 * 2;
    pitchBend = mul_Q15_Q16(pitchBend, pitchBendSensitivity);

    ////////////////////////////////////////////////////////////////////////////
    // LFO 2 params
    dspBuffer->patchParams.lfo2Params.waveform = patchParams[EPATCH_PARAM_LFO2_WAVEFORM];
    dspBuffer->patchParams.lfo2Params.rate = convertRawParamUInt8ToQ16(patchParams[EPATCH_PARAM_LFO2_RATE]);

    ////////////////////////////////////////////////////////////////////////////
    // LFO sync params
    dspBuffer->patchParams.lfoSync = patchParams[EPATCH_PARAM_LFO_SYNC];
    dspBuffer->patchParams.lfoSyncPhase = convertRawParamUInt8ToQ16(patchParams[EPATCH_PARAM_LFO_SYNC_PHASE]);

    ////////////////////////////////////////////////////////////////////////////
    // LFO 1 params
    const LFOParams lfo1Params = {
        .waveform = patchParams[EPATCH_PARAM_LFO1_WAVEFORM],
        .rate = convertRawParamUInt8ToQ16(patchParams[EPATCH_PARAM_LFO1_RATE])
    };

    ////////////////////////////////////////////////////////////////////////////
    // LFO 1 value
    dspBuffer->patchParams.lfo1Value = updateLFO(
            &lfo1Params,
            &lfo1State);

    ////////////////////////////////////////////////////////////////////////////
    // LFO 2 value

    // TODO mod matrix verwenden

    // Initial LFO rate
    _Q1516 lfo2Rate = convert_Q16_Q1516(dspBuffer->patchParams.lfo2Params.rate);

    // Modwheel modulation amount
    lfo2Rate = mac_Q15_Q15(lfo2Rate, dspBuffer->patchParams.modAmountLFO2Rate.modWheelAmount, dspBuffer->patchParams.modulation);

    // LFO 1 modulation amount
    lfo2Rate = mac_Q15_Q15(lfo2Rate, dspBuffer->patchParams.modAmountLFO2Rate.lfo1Amount, dspBuffer->patchParams.lfo1Value);

    // Modified LFO params
    const LFOParams lfo2Params = {
        .waveform = dspBuffer->patchParams.lfo2Params.waveform,
        .rate = convert_Q1516_Q16(lfo2Rate)
    };

    // Check for LFO sync
    if (dspBuffer->patchParams.lfoSync == ELFO_SYNC_LFO1 && lfo1State.sync)
    {
        // Sync LFO 2 to LFO 1
        dspBuffer->patchParams.lfo2Value = updateLFOSync(
                &lfo2Params,
                &lfo2State,
                lfo1Params.rate,
                lfo1State.phase,
                dspBuffer->patchParams.lfoSyncPhase);
    }
    else
    {
        // LFO 2 in free run
        dspBuffer->patchParams.lfo2Value = updateLFO(
                &lfo2Params,
                &lfo2State);
    }

    ////////////////////////////////////////////////////////////////////////////
    // Oscillator parameters

    // Osc pitch
    dspBuffer->patchParams.oscParams.pitch1 =
            convertRawParamInt8ToInt16(patchParams[EPATCH_PARAM_OSC1_PITCH]) * 200 + // Convert semitones to half-cents
            convertRawParamInt8ToInt16(patchParams[EPATCH_PARAM_OSC1_DETUNE]) * 2 + // Convert cents to half-cents
            pitchBend;
    dspBuffer->patchParams.oscParams.pitch2 =
            convertRawParamInt8ToInt16(patchParams[EPATCH_PARAM_OSC2_PITCH]) * 200 + // Convert semitones to half-cents
            convertRawParamInt8ToInt16(patchParams[EPATCH_PARAM_OSC2_DETUNE]) * 2 + // Convert cents to half-cents
            pitchBend;

    // Osc waveform
    dspBuffer->patchParams.oscParams.type = OSC_TYPE(patchParams[EPATCH_PARAM_OSC1_WAVEFORM], patchParams[EPATCH_PARAM_OSC2_WAVEFORM], patchParams[EPATCH_PARAM_OSC_SYNC]);

    // Osc shape
    dspBuffer->patchParams.oscParams.shape1 = convertRawParamUInt8ToQ16(patchParams[EPATCH_PARAM_OSC1_SHAPE1]);
    dspBuffer->patchParams.oscParams.shape2 = convertRawParamUInt8ToQ16(patchParams[EPATCH_PARAM_OSC1_SHAPE2]);
    dspBuffer->patchParams.oscParams.shape3 = convertRawParamUInt8ToQ16(patchParams[EPATCH_PARAM_OSC2_SHAPE]);

    // Osc sync phase
    dspBuffer->patchParams.oscParams.syncPhase = convertRawParamUInt8ToQ16(patchParams[EPATCH_PARAM_OSC_SYNC_PHASE]);

    // Osc modulation
    dspBuffer->patchParams.oscParams.crossModAmount = convertRawParamUInt8ToQ16(patchParams[EPATCH_PARAM_OSC_CROSSMOD]) >> 4;
    dspBuffer->patchParams.oscParams.ringModAmount = convertRawParamUInt8ToQ16(patchParams[EPATCH_PARAM_OSC_RINGMOD]);

    // Osc 1 <--> 2 balance
    dspBuffer->patchParams.oscParams.balance = (convertRawParamInt8ToQ15(patchParams[EPATCH_PARAM_OSC_BALANCE]) >> 1) + 0x4000;

    ////////////////////////////////////////////////////////////////////////////
    // Glide params
    dspBuffer->patchParams.glideParams.rate = ~convertRawParamUInt8ToQ16(patchParams[EPATCH_PARAM_GLIDE_TIME]);

    ////////////////////////////////////////////////////////////////////////////
    // Filter params
    dspBuffer->patchParams.filterParams.type = patchParams[EPATCH_PARAM_FILTER_TYPE];
    dspBuffer->patchParams.filterParams.freq = convert_Q16_Q15(convertRawParamUInt8ToQ16(patchParams[EPATCH_PARAM_FILTER_FREQ]));
    dspBuffer->patchParams.filterParams.shape = convertRawParamUInt8ToQ16(patchParams[EPATCH_PARAM_FILTER_SHAPE]);

    ////////////////////////////////////////////////////////////////////////////
    // Filter envelope params
    dspBuffer->patchParams.filterEnvParams.attack = patchParams[EPATCH_PARAM_FILTER_ENV_A];
    dspBuffer->patchParams.filterEnvParams.decay = patchParams[EPATCH_PARAM_FILTER_ENV_D];
    dspBuffer->patchParams.filterEnvParams.sustain = convertRawParamUInt8ToQ16(patchParams[EPATCH_PARAM_FILTER_ENV_S]);
    dspBuffer->patchParams.filterEnvParams.release = patchParams[EPATCH_PARAM_FILTER_ENV_R];

    ////////////////////////////////////////////////////////////////////////////
    // Amp envelope params
    dspBuffer->patchParams.ampParams.gain = convertRawParamUInt8ToQ16(patchParams[EPATCH_PARAM_LEVEL]);
    dspBuffer->patchParams.ampParams.pan = convertRawParamInt8ToQ15(patchParams[EPATCH_PARAM_PAN]);
    dspBuffer->patchParams.ampEnvParams.attack = patchParams[EPATCH_PARAM_AMP_ENV_A];
    dspBuffer->patchParams.ampEnvParams.decay = patchParams[EPATCH_PARAM_AMP_ENV_D];
    dspBuffer->patchParams.ampEnvParams.sustain = convertRawParamUInt8ToQ16(patchParams[EPATCH_PARAM_AMP_ENV_S]);
    dspBuffer->patchParams.ampEnvParams.release = patchParams[EPATCH_PARAM_AMP_ENV_R];

    ////////////////////////////////////////////////////////////////////////////
    // Modulation matrix Osc 1 Pitch
    // TODO Pitch Mod Depth gleich mit Raw Param multiplizieren
    const uint16_t pitchModDepth = 12 * 200; // +/- 1 Octave given in half-cents
    dspBuffer->patchParams.modAmountOsc1Pitch.modWheelAmount = mul_Q15_Q16(convertRawParamInt8ToQ15(patchParams[EPATCH_PARAM_MODWHEEL_AMOUNT_OSC1_PITCH]), pitchModDepth);
    dspBuffer->patchParams.modAmountOsc1Pitch.auxEnvAmount = mul_Q15_Q16(convertRawParamInt8ToQ15(patchParams[EPATCH_PARAM_AUXENV_AMOUNT_OSC1_PITCH]), pitchModDepth);
    dspBuffer->patchParams.modAmountOsc1Pitch.lfo1Amount = mul_Q15_Q16(convertRawParamInt8ToQ15(patchParams[EPATCH_PARAM_LFO1_AMOUNT_OSC1_PITCH]), pitchModDepth);
    dspBuffer->patchParams.modAmountOsc1Pitch.lfo2Amount = mul_Q15_Q16(convertRawParamInt8ToQ15(patchParams[EPATCH_PARAM_LFO2_AMOUNT_OSC1_PITCH]), pitchModDepth);

    ////////////////////////////////////////////////////////////////////////////
    // Modulation matrix Osc 2 Pitch
    dspBuffer->patchParams.modAmountOsc2Pitch.modWheelAmount = mul_Q15_Q16(convertRawParamInt8ToQ15(patchParams[EPATCH_PARAM_MODWHEEL_AMOUNT_OSC2_PITCH]), pitchModDepth);
    dspBuffer->patchParams.modAmountOsc2Pitch.auxEnvAmount = mul_Q15_Q16(convertRawParamInt8ToQ15(patchParams[EPATCH_PARAM_AUXENV_AMOUNT_OSC2_PITCH]), pitchModDepth);
    dspBuffer->patchParams.modAmountOsc2Pitch.lfo1Amount = mul_Q15_Q16(convertRawParamInt8ToQ15(patchParams[EPATCH_PARAM_LFO1_AMOUNT_OSC2_PITCH]), pitchModDepth);
    dspBuffer->patchParams.modAmountOsc2Pitch.lfo2Amount = mul_Q15_Q16(convertRawParamInt8ToQ15(patchParams[EPATCH_PARAM_LFO2_AMOUNT_OSC2_PITCH]), pitchModDepth);

    ////////////////////////////////////////////////////////////////////////////
    // Modulation matrix Osc 1 Shape
    dspBuffer->patchParams.modAmountOsc1Shape1.modWheelAmount = convertRawParamInt8ToQ15(patchParams[EPATCH_PARAM_MODWHEEL_AMOUNT_OSC1_SHAPE1]);
    dspBuffer->patchParams.modAmountOsc1Shape1.auxEnvAmount = convertRawParamInt8ToQ15(patchParams[EPATCH_PARAM_AUXENV_AMOUNT_OSC1_SHAPE1]);
    dspBuffer->patchParams.modAmountOsc1Shape1.lfo1Amount = convertRawParamInt8ToQ15(patchParams[EPATCH_PARAM_LFO1_AMOUNT_OSC1_SHAPE1]);
    dspBuffer->patchParams.modAmountOsc1Shape1.lfo2Amount = convertRawParamInt8ToQ15(patchParams[EPATCH_PARAM_LFO2_AMOUNT_OSC1_SHAPE1]);

    dspBuffer->patchParams.modAmountOsc1Shape2.modWheelAmount = convertRawParamInt8ToQ15(patchParams[EPATCH_PARAM_MODWHEEL_AMOUNT_OSC1_SHAPE2]);
    dspBuffer->patchParams.modAmountOsc1Shape2.auxEnvAmount = convertRawParamInt8ToQ15(patchParams[EPATCH_PARAM_AUXENV_AMOUNT_OSC1_SHAPE2]);
    dspBuffer->patchParams.modAmountOsc1Shape2.lfo1Amount = convertRawParamInt8ToQ15(patchParams[EPATCH_PARAM_LFO1_AMOUNT_OSC1_SHAPE2]);
    dspBuffer->patchParams.modAmountOsc1Shape2.lfo2Amount = convertRawParamInt8ToQ15(patchParams[EPATCH_PARAM_LFO2_AMOUNT_OSC1_SHAPE2]);

    ////////////////////////////////////////////////////////////////////////////
    // Modulation matrix Osc 2 Shape
    dspBuffer->patchParams.modAmountOsc2Shape.modWheelAmount = convertRawParamInt8ToQ15(patchParams[EPATCH_PARAM_MODWHEEL_AMOUNT_OSC2_SHAPE]);
    dspBuffer->patchParams.modAmountOsc2Shape.auxEnvAmount = convertRawParamInt8ToQ15(patchParams[EPATCH_PARAM_AUXENV_AMOUNT_OSC2_SHAPE]);
    dspBuffer->patchParams.modAmountOsc2Shape.lfo1Amount = convertRawParamInt8ToQ15(patchParams[EPATCH_PARAM_LFO1_AMOUNT_OSC2_SHAPE]);
    dspBuffer->patchParams.modAmountOsc2Shape.lfo2Amount = convertRawParamInt8ToQ15(patchParams[EPATCH_PARAM_LFO2_AMOUNT_OSC2_SHAPE]);

    ////////////////////////////////////////////////////////////////////////////
    // Modulation matrix Osc Sync Phase
    dspBuffer->patchParams.modAmountOscSyncPhase.modWheelAmount = convertRawParamInt8ToQ15(patchParams[EPATCH_PARAM_MODWHEEL_AMOUNT_OSC_SYNC_PHASE]);
    dspBuffer->patchParams.modAmountOscSyncPhase.auxEnvAmount = convertRawParamInt8ToQ15(patchParams[EPATCH_PARAM_AUXENV_AMOUNT_OSC_SYNC_PHASE]);
    dspBuffer->patchParams.modAmountOscSyncPhase.lfo1Amount = convertRawParamInt8ToQ15(patchParams[EPATCH_PARAM_LFO1_AMOUNT_OSC_SYNC_PHASE]);
    dspBuffer->patchParams.modAmountOscSyncPhase.lfo2Amount = convertRawParamInt8ToQ15(patchParams[EPATCH_PARAM_LFO2_AMOUNT_OSC_SYNC_PHASE]);

    ////////////////////////////////////////////////////////////////////////////
    // Modulation matrix Cross Mod Amount
    dspBuffer->patchParams.modAmountCrossModAmount.modWheelAmount = convertRawParamInt8ToQ15(patchParams[EPATCH_PARAM_MODWHEEL_AMOUNT_OSC_CROSSMOD]);
    dspBuffer->patchParams.modAmountCrossModAmount.auxEnvAmount = convertRawParamInt8ToQ15(patchParams[EPATCH_PARAM_AUXENV_AMOUNT_OSC_CROSSMOD]);
    dspBuffer->patchParams.modAmountCrossModAmount.lfo1Amount = convertRawParamInt8ToQ15(patchParams[EPATCH_PARAM_LFO1_AMOUNT_OSC_CROSSMOD]);
    dspBuffer->patchParams.modAmountCrossModAmount.lfo2Amount = convertRawParamInt8ToQ15(patchParams[EPATCH_PARAM_LFO2_AMOUNT_OSC_CROSSMOD]);

    ////////////////////////////////////////////////////////////////////////////
    // Modulation matrix Ring Mod Amount
    dspBuffer->patchParams.modAmountRingModAmount.modWheelAmount = convertRawParamInt8ToQ15(patchParams[EPATCH_PARAM_MODWHEEL_AMOUNT_OSC_RINGMOD]);
    dspBuffer->patchParams.modAmountRingModAmount.auxEnvAmount = convertRawParamInt8ToQ15(patchParams[EPATCH_PARAM_AUXENV_AMOUNT_OSC_RINGMOD]);
    dspBuffer->patchParams.modAmountRingModAmount.lfo1Amount = convertRawParamInt8ToQ15(patchParams[EPATCH_PARAM_LFO1_AMOUNT_OSC_RINGMOD]);
    dspBuffer->patchParams.modAmountRingModAmount.lfo2Amount = convertRawParamInt8ToQ15(patchParams[EPATCH_PARAM_LFO2_AMOUNT_OSC_RINGMOD]);

    ////////////////////////////////////////////////////////////////////////////
    // Modulation matrix Osc Balance
    dspBuffer->patchParams.modAmountOscBalance.modWheelAmount = convertRawParamInt8ToQ15(patchParams[EPATCH_PARAM_MODWHEEL_AMOUNT_OSC_BALANCE]);
    dspBuffer->patchParams.modAmountOscBalance.auxEnvAmount = convertRawParamInt8ToQ15(patchParams[EPATCH_PARAM_AUXENV_AMOUNT_OSC_BALANCE]);
    dspBuffer->patchParams.modAmountOscBalance.lfo1Amount = convertRawParamInt8ToQ15(patchParams[EPATCH_PARAM_LFO1_AMOUNT_OSC_BALANCE]);
    dspBuffer->patchParams.modAmountOscBalance.lfo2Amount = convertRawParamInt8ToQ15(patchParams[EPATCH_PARAM_LFO2_AMOUNT_OSC_BALANCE]);

    ////////////////////////////////////////////////////////////////////////////
    // Modulation matrix Filter Freq
    dspBuffer->patchParams.modAmountFilterFreq.envAmount = convertRawParamInt8ToQ15(patchParams[EPATCH_PARAM_FILTER_ENV_AMOUNT]);
    dspBuffer->patchParams.modAmountFilterFreq.keyTrack = convertRawParamInt8ToQ15(patchParams[EPATCH_PARAM_FILTER_KEYTRACK]);
    dspBuffer->patchParams.modAmountFilterFreq.modAmount.modWheelAmount = convertRawParamInt8ToQ15(patchParams[EPATCH_PARAM_MODWHEEL_AMOUNT_FILTER_FREQ]);
    dspBuffer->patchParams.modAmountFilterFreq.modAmount.auxEnvAmount = 0;
    dspBuffer->patchParams.modAmountFilterFreq.modAmount.lfo1Amount = convertRawParamInt8ToQ15(patchParams[EPATCH_PARAM_LFO1_AMOUNT_FILTER_FREQ]);
    dspBuffer->patchParams.modAmountFilterFreq.modAmount.lfo2Amount = convertRawParamInt8ToQ15(patchParams[EPATCH_PARAM_LFO2_AMOUNT_FILTER_FREQ]);

    ////////////////////////////////////////////////////////////////////////////
    // Modulation matrix Filter Shape
    dspBuffer->patchParams.modAmountFilterShape.modWheelAmount = convertRawParamInt8ToQ15(patchParams[EPATCH_PARAM_MODWHEEL_AMOUNT_FILTER_SHAPE]);
    dspBuffer->patchParams.modAmountFilterShape.auxEnvAmount = convertRawParamInt8ToQ15(patchParams[EPATCH_PARAM_AUXENV_AMOUNT_FILTER_SHAPE]);
    dspBuffer->patchParams.modAmountFilterShape.lfo1Amount = convertRawParamInt8ToQ15(patchParams[EPATCH_PARAM_LFO1_AMOUNT_FILTER_SHAPE]);
    dspBuffer->patchParams.modAmountFilterShape.lfo2Amount = convertRawParamInt8ToQ15(patchParams[EPATCH_PARAM_LFO2_AMOUNT_FILTER_SHAPE]);

    ////////////////////////////////////////////////////////////////////////////
    // Modulation matrix Amp Level
    dspBuffer->patchParams.modAmountAmpLevel.modWheelAmount = convertRawParamInt8ToQ15(patchParams[EPATCH_PARAM_MODWHEEL_AMOUNT_LEVEL]);
    dspBuffer->patchParams.modAmountAmpLevel.auxEnvAmount = 0;
    dspBuffer->patchParams.modAmountAmpLevel.lfo1Amount = convertRawParamInt8ToQ15(patchParams[EPATCH_PARAM_LFO1_AMOUNT_LEVEL]);
    dspBuffer->patchParams.modAmountAmpLevel.lfo2Amount = convertRawParamInt8ToQ15(patchParams[EPATCH_PARAM_LFO2_AMOUNT_LEVEL]);

    ////////////////////////////////////////////////////////////////////////////
    // Modulation matrix Amp Pan
    dspBuffer->patchParams.modAmountAmpPan.modWheelAmount = convertRawParamInt8ToQ15(patchParams[EPATCH_PARAM_MODWHEEL_AMOUNT_PAN]);
    dspBuffer->patchParams.modAmountAmpPan.auxEnvAmount = convertRawParamInt8ToQ15(patchParams[EPATCH_PARAM_AUXENV_AMOUNT_PAN]);
    dspBuffer->patchParams.modAmountAmpPan.lfo1Amount = convertRawParamInt8ToQ15(patchParams[EPATCH_PARAM_LFO1_AMOUNT_PAN]);
    dspBuffer->patchParams.modAmountAmpPan.lfo2Amount = convertRawParamInt8ToQ15(patchParams[EPATCH_PARAM_LFO2_AMOUNT_PAN]);

    ////////////////////////////////////////////////////////////////////////////
    // Modulation matrix LFO 2 Rate
    dspBuffer->patchParams.modAmountLFO2Rate.modWheelAmount = convertRawParamInt8ToQ15(patchParams[EPATCH_PARAM_MODWHEEL_AMOUNT_LFO2_RATE]);
    dspBuffer->patchParams.modAmountLFO2Rate.auxEnvAmount = convertRawParamInt8ToQ15(patchParams[EPATCH_PARAM_AUXENV_AMOUNT_LFO2_RATE]);
    dspBuffer->patchParams.modAmountLFO2Rate.lfo1Amount = convertRawParamInt8ToQ15(patchParams[EPATCH_PARAM_LFO1_AMOUNT_LFO2_RATE]);

    ////////////////////////////////////////////////////////////////////////////
    // Aux envelope params
    dspBuffer->patchParams.auxEnvParams.attack = patchParams[EPATCH_PARAM_AUX_ENV_A];
    dspBuffer->patchParams.auxEnvParams.decay = patchParams[EPATCH_PARAM_AUX_ENV_D];
    dspBuffer->patchParams.auxEnvParams.sustain = convertRawParamUInt8ToQ16(patchParams[EPATCH_PARAM_AUX_ENV_S]);
    dspBuffer->patchParams.auxEnvParams.release = patchParams[EPATCH_PARAM_AUX_ENV_R];
    
    
    // Chorus parameters
    dspBuffer->patchParams.chorusParams.depth = convertRawParamUInt8ToUInt16(patchParams[EPATCH_PARAM_CHORUS_DEPTH]);
    dspBuffer->patchParams.chorusParams.rate = convertRawParamUInt8ToQ16(patchParams[EPATCH_PARAM_CHORUS_RATE]);
    dspBuffer->patchParams.chorusParams.modDepth = convertRawParamUInt8ToQ16(patchParams[EPATCH_PARAM_CHORUS_MODDEPTH]);
    dspBuffer->patchParams.chorusParams.spread = convertRawParamUInt8ToQ16(patchParams[EPATCH_PARAM_CHORUS_SPREAD]);
    dspBuffer->patchParams.chorusParams.mix = convert_Q16_Q15(convertRawParamUInt8ToQ16(patchParams[EPATCH_PARAM_CHORUS_MIX]));

    // Delay parameters
    dspBuffer->patchParams.delayParams.time = convertRawParamUInt8ToQ16(patchParams[EPATCH_PARAM_ECHO_DELAY]);
    dspBuffer->patchParams.delayParams.feedback = convert_Q16_Q15(convertRawParamUInt8ToQ16(patchParams[EPATCH_PARAM_ECHO_FEEDBACK]));
    dspBuffer->patchParams.delayParams.spread = convert_Q16_Q15(convertRawParamUInt8ToQ16(patchParams[EPATCH_PARAM_ECHO_SPREAD]));
    dspBuffer->patchParams.delayParams.brightness = convertRawParamUInt8ToQ16(patchParams[EPATCH_PARAM_ECHO_BRIGHTNESS]);
    dspBuffer->patchParams.delayParams.mix = convert_Q16_Q15(convertRawParamUInt8ToQ16(patchParams[EPATCH_PARAM_ECHO_MIX]));
    
    // Tone control parameters
    dspBuffer->patchParams.toneControlParams.bass = convertRawParamInt8ToQ15(patchParams[EPATCH_PARAM_BASS]);
    dspBuffer->patchParams.toneControlParams.treble = convertRawParamInt8ToQ15(patchParams[EPATCH_PARAM_TREBLE]);
    
    // Bit crusher parameters
    dspBuffer->patchParams.bitcrusherParams.sampleRate = 32767 - convert_Q16_Q15(convertRawParamUInt8ToQ16(patchParams[EPATCH_PARAM_BITCRUSHER_SAMPLERATE]));
    dspBuffer->patchParams.bitcrusherParams.quantization = 32767 - convert_Q16_Q15(convertRawParamUInt8ToQ16(patchParams[EPATCH_PARAM_BITCRUSHER_QUANTIZATION]));
    dspBuffer->patchParams.bitcrusherParams.mix = convert_Q16_Q15(convertRawParamUInt8ToQ16(patchParams[EPATCH_PARAM_BITCRUSHER_MIX]));
    
    // Distortion parameters
    dspBuffer->patchParams.distortionParams.drive = convert_Q16_Q15(convertRawParamUInt8ToQ16(patchParams[EPATCH_PARAM_DISTORTION_DRIVE]));
    dspBuffer->patchParams.distortionParams.shape = convert_Q16_Q15(convertRawParamUInt8ToQ16(patchParams[EPATCH_PARAM_DISTORTION_SHAPE]));
    dspBuffer->patchParams.distortionParams.mix = convert_Q16_Q15(convertRawParamUInt8ToQ16(patchParams[EPATCH_PARAM_DISTORTION_MIX]));
}