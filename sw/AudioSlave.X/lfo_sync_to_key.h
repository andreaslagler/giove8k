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

#ifndef LFO_SYNC_TO_KEY_H
#define LFO_SYNC_TO_KEY_H

#include "lfo.h"
#include "fp_lib_types.h"
#include "fp_lib_typeconv.h"
#include "mod_mixer.h"

//
static inline _Q15 updateLFOSyncToKey(
        const LFOParams * const lfoParams,
        const bool trigger,
        const _Q16 lfoSyncPhase,
        const ModSource * const modSource,
        const ModAmountLFORate * const modAmount,
        LFOState * const lfoState)
{
    _Q15 lfo2Value;

        if (trigger)
        {
            // Trigger --> reset to sync phase
            lfo2Value = updateLFOReset(
                    lfoParams->waveform,
                    lfoState,
                    lfoSyncPhase);
        }
        else
        {
            // No trigger --> normal update

            // Calculate the LFO rate
            const _Q15 qLFORate = calcLFORate(
                    convert_Q16_Q15(lfoParams->rate),
                    modSource,
                    modAmount);

            // Modify params
            const LFOParams params = {
                .rate = convert_Q15_Q16(qLFORate),
                .waveform = lfoParams->waveform};
            
            lfo2Value = updateLFO(
                    &params,
                    lfoState);
        }

    return lfo2Value;
}

#endif