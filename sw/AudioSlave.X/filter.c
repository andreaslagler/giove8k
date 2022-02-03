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

#include "filter.h"
#include "svf_2pole.h"
#include "formant_filter.h"
#include "fp_lib_types.h"
#include <stdint.h>

// Bypass
static void calcFilter_None(
        const FilterParams * params,
        FilterState * state,
        _Q15 * const coeffs,
        _Q15 * const data)
{
    // In-place calculation --> don't do anything for filter type NONE
}

// 12 dB Lowpass Filter
static void calcFilter_LP2Pole(
        const FilterParams * params,
        FilterState * state,
        _Q15 * const coeffs, // work buffer for 4 coefficients allocated in .ydata
        _Q15 * const data)
{
    // Calculate derived filter coefficients
    calcCoeffs(
            params->freq,
            params->shape,
            coeffs);

    calcLP2PoleBlockInplace(
            coeffs,
            &state->state2Pole,
            data);
}

// 12 dB Bandpass Filter
static void calcFilter_BP2Pole(
        const FilterParams * params,
        FilterState * state,
        _Q15 * const coeffs, // work buffer for 4 coefficients allocated in .ydata
        _Q15 * const data)
{
    // Calculate derived filter coefficients
    calcCoeffs(
            params->freq,
            params->shape,
            coeffs);

    calcBP2PoleBlockInplace(
            coeffs,
            &state->state2Pole,
            data);
}

// 12 dB Highpass Filter
static void calcFilter_HP2Pole(
        const FilterParams * params,
        FilterState * state,
        _Q15 * const coeffs, // work buffer for 4 coefficients allocated in .ydata
        _Q15 * const data)
{
    // Calculate derived filter coefficients
    calcCoeffs(
            params->freq,
            params->shape,
            coeffs);

    calcHP2PoleBlockInplace(
            coeffs,
            &state->state2Pole,
            data);
}

// 24 dB Lowpass Filter
static void calcFilter_LP4Pole(
        const FilterParams * params,
        FilterState * state,
        _Q15 * const coeffs, // work buffer for 4 coefficients allocated in .ydata
        _Q15 * const data)
{
    // Calculate derived filter coefficients
    calcCoeffs(
            params->freq,
            params->shape,
            coeffs);

    // First stage
    calcLP2PoleBlockInplace(
            coeffs,
            &state->state4Pole.stage1,
            data);

    // Second stage
    calcLP2PoleBlockInplace(
            coeffs,
            &state->state4Pole.stage2,
            data);
}

// 24 dB Bandpass Filter
static void calcFilter_BP4Pole(
        const FilterParams * params,
        FilterState * state,
        _Q15 * const coeffs, // work buffer for 4 coefficients allocated in .ydata
        _Q15 * const data)
{
    // Calculate derived filter coefficients
    calcCoeffs(
            params->freq,
            params->shape,
            coeffs);

    // First stage
    calcBP2PoleBlockInplace(
            coeffs,
            &state->state4Pole.stage1,
            data);

    // Second stage
    calcBP2PoleBlockInplace(
            coeffs,
            &state->state4Pole.stage2,
            data);
}

// 24 dB Highpass Filter
static void calcFilter_HP4Pole(
        const FilterParams * params,
        FilterState * state,
        _Q15 * const coeffs, // work buffer for 4 coefficients allocated in .ydata
        _Q15 * const data)
{
    // Calculate derived filter coefficients
    calcCoeffs(
            params->freq,
            params->shape,
            coeffs);

    // First stage
    calcHP2PoleBlockInplace(
            coeffs,
            &state->state4Pole.stage1,
            data);

    // Second stage
    calcHP2PoleBlockInplace(
            coeffs,
            &state->state4Pole.stage2,
            data);
}

// 4-stage Formant Filter
static void calcFilter_Formant(
        const FilterParams * params,
        FilterState * state,
        _Q15 * const coeffs, // work buffer for 4 coefficients allocated in .ydata
        _Q15 * const data)
{
    for (uint8_t cntFilterStage = 0; cntFilterStage < NOF_FORMANT_FILTER_STAGES; ++cntFilterStage)
    {
        // Calculate derived filter coefficients
        const uint16_t freq = ((~(params->freq >> 15)) & (params->freq << 1)) + calcFreq(cntFilterStage, params->shape);
        const _Q16 resonance = calcResonance(cntFilterStage, params->shape);
        calcCoeffs(
                freq,
                resonance,
                coeffs);

        calcLP2PoleBlockInplace(
                coeffs,
                &state->stateFormant.stages[cntFilterStage],
                data);
    }
}

// Definition of the actual jump table
const T_CALC_FILTER apfCalcFilter[EFILTER_TYPE_NOFENTRIES] = {
    &calcFilter_LP2Pole,
    &calcFilter_LP4Pole,
    &calcFilter_BP2Pole,
    &calcFilter_BP4Pole,
    &calcFilter_HP2Pole,
    &calcFilter_HP4Pole,
    &calcFilter_Formant,
    &calcFilter_None
};