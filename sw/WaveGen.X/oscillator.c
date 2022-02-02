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

#include "oscillator.h"
#include "osc_saw.h"
#include "osc_rect.h"
#include "osc_tri.h"
#include "osc_stacked_saw.h"
#include "osc_feedback.h"
#include "osc_tri_mod.h"
#include "osc_lowpass_noise.h"
#include "osc_colored_noise.h"
#include "rand.h"
#include "note_to_freq.h"
#include "fp_lib_types.h"
#include "fp_lib_trig.h"
#include "fp_lib_div.h"
#include "block_len_def.h"
#include <stdint.h>

////////////////////////////////////////////////////////////////////////////////
// Oscillator 1/2 architecture:
// - Oscillator 1 can be Cross/FM modulated by oscillator 2
// - Oscillator 2 can be Ring/AM modulated by oscillator 1
// - Oscillator 2 can be hard-synced by oscillator 1
//
// Since branches cost lots of CPU cycles on DSPI33E devices, all oscillator
// calculation functions are constructed using macros and stored in a jump table
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Macros for oscillator initialisation
////////////////////////////////////////////////////////////////////////////////

// Oscillator free-run
#define INIT_OSC_NOSYNC \

// Oscillator hard sync
#define INIT_OSC_SYNC \
        const _Q1616 relFreq = div_Q16_Q16(((ULong) freq2).high, ((ULong) freq1).high);

// Initialisation of oscillator 1 for stacked saw
#define INIT_OSC1_SSAW \
        static OscStackedSawParams params1 __attribute__((space(ymemory), far)); \
        calcOscStackedSawParams(params->pitch1, freq1, params->shape1, params->shape2, &params1);

// Initialisation of oscillator 1 for mod triangle
#define INIT_OSC1_TRI_MOD \

// Initialisation of oscillator 1 for feedback oscillator
#define INIT_OSC1_FEEDBACK \
        OscFeedbackParams params1; \
        calcOscFeedbackParams(params->shape1, params->shape2, &params1);

// Initialisation of oscillator 1 for noise
#define INIT_OSC1_NOISE \
        static OscLowPassNoiseParams params1 __attribute__((space(ymemory), far)); \
        calcOscLowPassNoiseParams(params->pitch1, params->shape1, params->shape2, &params1);

// Initialisation of oscillator 1 for rectangle
#define INIT_OSC1_RECT \
        const _Q16 pulseWidth1 = params->shape1;

// Initialisation of oscillator 1 for saw
#define INIT_OSC1_SAW \
        static _Q15 scaling1[2] __attribute__((space(ymemory), far)); \
        calcOscSawShape(params->shape1, scaling1);

// Initialisation of oscillator 1 for triangle
#define INIT_OSC1_TRI \
        const _Q15 scaling1 = calcTriOscShape(params->shape1);

// Initialisation of oscillator 1 for sine
#define INIT_OSC1_SINE \

// Initialisation of oscillator 2 for rectangle
#define INIT_OSC2_RECT \
        const _Q16 pulseWidth2 = params->shape3; \

// Initialisation of oscillator 2 for saw
#define INIT_OSC2_SAW \
        static _Q15 scaling2[2] __attribute__((space(ymemory), far)); \
        calcOscSawShape(params->shape3, scaling2);        

// Initialisation of oscillator 2 for triangle
#define INIT_OSC2_TRI \
        const _Q15 scaling2 = calcTriOscShape(params->shape3);

// Initialisation of oscillator 2 for sine
#define INIT_OSC2_SINE \

// Initialisation of oscillator 2 for noise
#define INIT_OSC2_NOISE \
        OscColoredNoiseParams params2; \
        calcOscColoredNoiseParams(params->shape3, &params2); \
        if (state->osc2.coloredNoiseState.filterState.stateScaling > 16) state->osc2.coloredNoiseState.filterState.stateScaling = 16; \
        if (state->osc2.coloredNoiseState.filterState.stateScaling < -16) state->osc2.coloredNoiseState.filterState.stateScaling = -16;    

////////////////////////////////////////////////////////////////////////////////
// Macros for oscillator output calculation
////////////////////////////////////////////////////////////////////////////////

// Oscillator free-run
#define CALC_OSC_NOSYNC \
        phase1 += freq1; \
        phase2 += freq2;

// Oscillator hard sync
#define CALC_OSC_SYNC \
        ULong syncPhase = {.value = mul_Q1616_Q1616(phase1, relFreq)}; \
        syncPhase.high += params->syncPhase; \
        _Q16 syncMask; \
        __asm__ volatile("add %[Phase], %[Freq], %[Phase] \n addc %d[Phase], %d[Freq], %d[Phase] \n rrc %[Mask], %[Mask] \n asr %[Mask], #15, %[Mask]" : [Phase] "+r"(phase1), [Mask] "=r" (syncMask) : [Freq] "r"(freq1) : ); \
        syncPhase.high &= syncMask; \
        syncPhase.low &= syncMask; \
        phase2 += freq2; \
        syncMask = ~syncMask; \
        ULong uPhase = {.high = syncPhase.high + (((ULong) phase2).high & syncMask), .low = syncPhase.low + (((ULong) phase2).low & syncMask) }; \
        phase2 = uPhase.value;

// Output of oscillator 1 for stacked saw
#define CALC_OSC1_SSAW \
        state->osc1.phase = phase1; \
        const _Q15 output1 = calcOscStackedSaw(&params1, &state->osc1.stackedSawState);

// Output of oscillator 1 for mod triangle
#define CALC_OSC1_TRI_MOD \
        const uint32_t crossMod = __builtin_mulsu(output2, params->crossModAmount); \
        phase1 += crossMod; \
        const _Q15 output1 = calcTriMod(((ULong) phase1).high, params->shape1, params->shape2);

// Output of oscillator 1 for feedback oscillator
#define CALC_OSC1_FEEDBACK \
        const uint32_t crossMod = __builtin_mulsu(output2, params->crossModAmount); \
        phase1 += crossMod; \
        const _Q15 output1 = calcOscFeedback(((ULong) phase1).high, &params1, &state->osc1.feedbackState);

// Output of oscillator 1 for noise
#define CALC_OSC1_NOISE \
        const _Q15 output1 = calcOscLowPassNoiseSample(&params1, &state->osc1.lowPassNoiseState);

// Output of oscillator 1 for rectangle
#define CALC_OSC1_RECT \
        const uint32_t crossMod = __builtin_mulsu(output2, params->crossModAmount); \
        phase1 += crossMod; \
        const _Q15 output1 = calcNaiveRect(((ULong) phase1).high, pulseWidth1) >> 1;

// Output of oscillator 1 for saw
#define CALC_OSC1_SAW \
        const uint32_t crossMod = __builtin_mulsu(output2, params->crossModAmount); \
        phase1 += crossMod; \
        const _Q15 output1 = calcOscSaw(((ULong) phase1).high, scaling1);

// Output of oscillator 1 for triangle
#define CALC_OSC1_TRI \
        const uint32_t crossMod = __builtin_mulsu(output2, params->crossModAmount); \
        phase1 += crossMod; \
        const _Q15 output1 = calcOscTri(((ULong) phase1).high, scaling1);

// Output of oscillator 1 for sine
#define CALC_OSC1_SINE \
        const uint32_t crossMod = __builtin_mulsu(output2, params->crossModAmount); \
        phase1 += crossMod; \
        const _Q15 output1 = sin_Q15(((ULong) phase1).high);

// Output of oscillator 2 for rectangle
#define CALC_OSC2_RECT \
        output2 = calcNaiveRect(((ULong) phase2).high, pulseWidth2);

// Output of oscillator 2 for saw
#define CALC_OSC2_SAW \
        output2 = calcOscSaw(((ULong) phase2).high, scaling2);

// Output of oscillator 2 for triangle
#define CALC_OSC2_TRI \
        output2 = calcOscTri(((ULong) phase2).high, scaling2);

// Output of oscillator 2 for sine
#define CALC_OSC2_SINE \
        output2 = sin_Q15(((ULong) phase2).high);

// Output of oscillator 2 for noise
#define CALC_OSC2_NOISE \
        output2 = calcOscColoredNoiseSample(&params2, &state->osc2.coloredNoiseState);

////////////////////////////////////////////////////////////////////////////////
// Helper macros
////////////////////////////////////////////////////////////////////////////////

#define CALC_OSC_NAME(WAVEFORM1,WAVEFORM2,SYNC_MODE) \
CalcOsc_ ## WAVEFORM1 ## _ ## WAVEFORM2 ## _ ## SYNC_MODE

////////////////////////////////////////////////////////////////////////////////
// Final Oscillator calculation macro
////////////////////////////////////////////////////////////////////////////////

#define CALC_OSC(WAVEFORM1,WAVEFORM2,SYNC_MODE) \
static void CALC_OSC_NAME(WAVEFORM1,WAVEFORM2,SYNC_MODE) ( \
       const OscParams * params, \
       OscState * state, \
       _Q15 * output) \
{ \
_Q32 phase1 = state->osc1.phase; \
const _Q32 freq1 = noteToFreq(params->pitch1); \
_Q32 phase2 = state->osc2.phase; \
const _Q32 freq2 = noteToFreq(params->pitch2); \
_Q15 output2 = state->lastOsc2Output; \
INIT_OSC1_## WAVEFORM1 \
INIT_OSC2_## WAVEFORM2 \
INIT_OSC_ ## SYNC_MODE \
uint8_t uiNofSamples = BLOCK_LEN; \
do \
{ \
CALC_OSC1_## WAVEFORM1 \
CALC_OSC2_ ## WAVEFORM2 \
CALC_OSC_ ## SYNC_MODE \
const _Q15 ringMod = mul_Q15_Q15(output1, output2); \
_Q15 ringModOutput; \
__asm__ volatile("lac %[In1], #0, A \n msc %[In1] * %[Amt], A \n mac %[In2] * %[Amt], A \n sac.r A, #0, %[Out]" : [Out]"=r"(ringModOutput) : [In1]"z"(output2), [In2]"z"(ringMod), [Amt]"z"(params->ringModAmount) : ); \
__asm__ volatile("lac %[In1], #0, A \n msc %[In1] * %[Bal], A \n mac %[In2] * %[Bal], A \n sac.r A, #1, [%[Out]++]" : [Out]"+r"(output) : [In1]"z"(output1), [In2]"z"(ringModOutput), [Bal]"z"(params->balance) : ); \
} \
while (--uiNofSamples); \
state->osc1.phase = phase1; \
state->osc2.phase = phase2; \
state->lastOsc2Output = output2; \
}

////////////////////////////////////////////////////////////////////////////////
// Definitions of all oscillator calculation functions
////////////////////////////////////////////////////////////////////////////////

CALC_OSC(SSAW, RECT, NOSYNC)
CALC_OSC(SSAW, RECT, SYNC)
CALC_OSC(SSAW, SAW, NOSYNC)
CALC_OSC(SSAW, SAW, SYNC)
CALC_OSC(SSAW, TRI, NOSYNC)
CALC_OSC(SSAW, TRI, SYNC)
CALC_OSC(SSAW, SINE, NOSYNC)
CALC_OSC(SSAW, SINE, SYNC)
CALC_OSC(SSAW, NOISE, NOSYNC)
CALC_OSC(SSAW, NOISE, SYNC)

CALC_OSC(TRI_MOD, RECT, NOSYNC)
CALC_OSC(TRI_MOD, RECT, SYNC)
CALC_OSC(TRI_MOD, SAW, NOSYNC)
CALC_OSC(TRI_MOD, SAW, SYNC)
CALC_OSC(TRI_MOD, TRI, NOSYNC)
CALC_OSC(TRI_MOD, TRI, SYNC)
CALC_OSC(TRI_MOD, SINE, NOSYNC)
CALC_OSC(TRI_MOD, SINE, SYNC)
CALC_OSC(TRI_MOD, NOISE, NOSYNC)
CALC_OSC(TRI_MOD, NOISE, SYNC)

CALC_OSC(FEEDBACK, RECT, NOSYNC)
CALC_OSC(FEEDBACK, RECT, SYNC)
CALC_OSC(FEEDBACK, SAW, NOSYNC)
CALC_OSC(FEEDBACK, SAW, SYNC)
CALC_OSC(FEEDBACK, TRI, NOSYNC)
CALC_OSC(FEEDBACK, TRI, SYNC)
CALC_OSC(FEEDBACK, SINE, NOSYNC)
CALC_OSC(FEEDBACK, SINE, SYNC)
CALC_OSC(FEEDBACK, NOISE, NOSYNC)
CALC_OSC(FEEDBACK, NOISE, SYNC)

CALC_OSC(NOISE, RECT, NOSYNC)
CALC_OSC(NOISE, RECT, SYNC)
CALC_OSC(NOISE, SAW, NOSYNC)
CALC_OSC(NOISE, SAW, SYNC)
CALC_OSC(NOISE, TRI, NOSYNC)
CALC_OSC(NOISE, TRI, SYNC)
CALC_OSC(NOISE, SINE, NOSYNC)
CALC_OSC(NOISE, SINE, SYNC)
CALC_OSC(NOISE, NOISE, NOSYNC)
CALC_OSC(NOISE, NOISE, SYNC)

CALC_OSC(RECT, RECT, NOSYNC)
CALC_OSC(RECT, RECT, SYNC)
CALC_OSC(RECT, SAW, NOSYNC)
CALC_OSC(RECT, SAW, SYNC)
CALC_OSC(RECT, TRI, NOSYNC)
CALC_OSC(RECT, TRI, SYNC)
CALC_OSC(RECT, SINE, NOSYNC)
CALC_OSC(RECT, SINE, SYNC)
CALC_OSC(RECT, NOISE, NOSYNC)
CALC_OSC(RECT, NOISE, SYNC)

CALC_OSC(SAW, RECT, NOSYNC)
CALC_OSC(SAW, RECT, SYNC)
CALC_OSC(SAW, SAW, NOSYNC)
CALC_OSC(SAW, SAW, SYNC)
CALC_OSC(SAW, TRI, NOSYNC)
CALC_OSC(SAW, TRI, SYNC)
CALC_OSC(SAW, SINE, NOSYNC)
CALC_OSC(SAW, SINE, SYNC)
CALC_OSC(SAW, NOISE, NOSYNC)
CALC_OSC(SAW, NOISE, SYNC)

CALC_OSC(TRI, RECT, NOSYNC)
CALC_OSC(TRI, RECT, SYNC)
CALC_OSC(TRI, SAW, NOSYNC)
CALC_OSC(TRI, SAW, SYNC)
CALC_OSC(TRI, TRI, NOSYNC)
CALC_OSC(TRI, TRI, SYNC)
CALC_OSC(TRI, SINE, NOSYNC)
CALC_OSC(TRI, SINE, SYNC)
CALC_OSC(TRI, NOISE, NOSYNC)
CALC_OSC(TRI, NOISE, SYNC)

CALC_OSC(SINE, RECT, NOSYNC)
CALC_OSC(SINE, RECT, SYNC)
CALC_OSC(SINE, SAW, NOSYNC)
CALC_OSC(SINE, SAW, SYNC)
CALC_OSC(SINE, TRI, NOSYNC)
CALC_OSC(SINE, TRI, SYNC)
CALC_OSC(SINE, SINE, NOSYNC)
CALC_OSC(SINE, SINE, SYNC)
CALC_OSC(SINE, NOISE, NOSYNC)
CALC_OSC(SINE, NOISE, SYNC)


////////////////////////////////////////////////////////////////////////////////
// Definition of the actual jump table
////////////////////////////////////////////////////////////////////////////////

        
        
const CalcOsc calcOscJumpTable[] = {
    &CALC_OSC_NAME(SSAW, RECT, NOSYNC),
    &CALC_OSC_NAME(SSAW, RECT, SYNC),
    &CALC_OSC_NAME(SSAW, SAW, NOSYNC),
    &CALC_OSC_NAME(SSAW, SAW, SYNC),
    &CALC_OSC_NAME(SSAW, TRI, NOSYNC),
    &CALC_OSC_NAME(SSAW, TRI, SYNC),
    &CALC_OSC_NAME(SSAW, SINE, NOSYNC),
    &CALC_OSC_NAME(SSAW, SINE, SYNC),
    &CALC_OSC_NAME(SSAW, NOISE, NOSYNC),
    &CALC_OSC_NAME(SSAW, NOISE, SYNC),

    &CALC_OSC_NAME(TRI_MOD, RECT, NOSYNC),
    &CALC_OSC_NAME(TRI_MOD, RECT, SYNC),
    &CALC_OSC_NAME(TRI_MOD, SAW, NOSYNC),
    &CALC_OSC_NAME(TRI_MOD, SAW, SYNC),
    &CALC_OSC_NAME(TRI_MOD, TRI, NOSYNC),
    &CALC_OSC_NAME(TRI_MOD, TRI, SYNC),
    &CALC_OSC_NAME(TRI_MOD, SINE, NOSYNC),
    &CALC_OSC_NAME(TRI_MOD, SINE, SYNC),
    &CALC_OSC_NAME(TRI_MOD, NOISE, NOSYNC),
    &CALC_OSC_NAME(TRI_MOD, NOISE, SYNC),

    &CALC_OSC_NAME(FEEDBACK, RECT, NOSYNC),
    &CALC_OSC_NAME(FEEDBACK, RECT, SYNC),
    &CALC_OSC_NAME(FEEDBACK, SAW, NOSYNC),
    &CALC_OSC_NAME(FEEDBACK, SAW, SYNC),
    &CALC_OSC_NAME(FEEDBACK, TRI, NOSYNC),
    &CALC_OSC_NAME(FEEDBACK, TRI, SYNC),
    &CALC_OSC_NAME(FEEDBACK, SINE, NOSYNC),
    &CALC_OSC_NAME(FEEDBACK, SINE, SYNC),
    &CALC_OSC_NAME(FEEDBACK, NOISE, NOSYNC),
    &CALC_OSC_NAME(FEEDBACK, NOISE, SYNC),

    &CALC_OSC_NAME(RECT, RECT, NOSYNC),
    &CALC_OSC_NAME(RECT, RECT, SYNC),
    &CALC_OSC_NAME(RECT, SAW, NOSYNC),
    &CALC_OSC_NAME(RECT, SAW, SYNC),
    &CALC_OSC_NAME(RECT, TRI, NOSYNC),
    &CALC_OSC_NAME(RECT, TRI, SYNC),
    &CALC_OSC_NAME(RECT, SINE, NOSYNC),
    &CALC_OSC_NAME(RECT, SINE, SYNC),
    &CALC_OSC_NAME(RECT, NOISE, NOSYNC),
    &CALC_OSC_NAME(RECT, NOISE, SYNC),

    &CALC_OSC_NAME(SAW, RECT, NOSYNC),
    &CALC_OSC_NAME(SAW, RECT, SYNC),
    &CALC_OSC_NAME(SAW, SAW, NOSYNC),
    &CALC_OSC_NAME(SAW, SAW, SYNC),
    &CALC_OSC_NAME(SAW, TRI, NOSYNC),
    &CALC_OSC_NAME(SAW, TRI, SYNC),
    &CALC_OSC_NAME(SAW, SINE, NOSYNC),
    &CALC_OSC_NAME(SAW, SINE, SYNC),
    &CALC_OSC_NAME(SAW, NOISE, NOSYNC),
    &CALC_OSC_NAME(SAW, NOISE, SYNC),

    &CALC_OSC_NAME(TRI, RECT, NOSYNC),
    &CALC_OSC_NAME(TRI, RECT, SYNC),
    &CALC_OSC_NAME(TRI, SAW, NOSYNC),
    &CALC_OSC_NAME(TRI, SAW, SYNC),
    &CALC_OSC_NAME(TRI, TRI, NOSYNC),
    &CALC_OSC_NAME(TRI, TRI, SYNC),
    &CALC_OSC_NAME(TRI, SINE, NOSYNC),
    &CALC_OSC_NAME(TRI, SINE, SYNC),
    &CALC_OSC_NAME(TRI, NOISE, NOSYNC),
    &CALC_OSC_NAME(TRI, NOISE, SYNC),

    &CALC_OSC_NAME(SINE, RECT, NOSYNC),
    &CALC_OSC_NAME(SINE, RECT, SYNC),
    &CALC_OSC_NAME(SINE, SAW, NOSYNC),
    &CALC_OSC_NAME(SINE, SAW, SYNC),
    &CALC_OSC_NAME(SINE, TRI, NOSYNC),
    &CALC_OSC_NAME(SINE, TRI, SYNC),
    &CALC_OSC_NAME(SINE, SINE, NOSYNC),
    &CALC_OSC_NAME(SINE, SINE, SYNC),
    &CALC_OSC_NAME(SINE, NOISE, NOSYNC),
    &CALC_OSC_NAME(SINE, NOISE, SYNC),
    
    &CALC_OSC_NAME(NOISE, RECT, NOSYNC),
    &CALC_OSC_NAME(NOISE, RECT, SYNC),
    &CALC_OSC_NAME(NOISE, SAW, NOSYNC),
    &CALC_OSC_NAME(NOISE, SAW, SYNC),
    &CALC_OSC_NAME(NOISE, TRI, NOSYNC),
    &CALC_OSC_NAME(NOISE, TRI, SYNC),
    &CALC_OSC_NAME(NOISE, SINE, NOSYNC),
    &CALC_OSC_NAME(NOISE, SINE, SYNC),
    &CALC_OSC_NAME(NOISE, NOISE, NOSYNC),
    &CALC_OSC_NAME(NOISE, NOISE, SYNC)
};
