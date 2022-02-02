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

#ifndef OSC_H
#define	OSC_H

#include "osc_types.h"
#include "fp_lib_types.h"

// Oscillator calculation function pointer type
typedef void (* CalcOsc) (const OscParams *, OscState *, _Q15 *);

// Jump Table
extern const CalcOsc calcOscJumpTable[EOSC_TYPE_NOFENTRIES];

// Top-level osc calculate function

inline static void calcOsc(
                           const OscParams * const params,
                           OscState * const state,
                           _Q15 * const output)
{
    // Dispatch
    const OscType oscType = params->type;
    if (oscType < EOSC_TYPE_NOFENTRIES)
    {
        calcOscJumpTable[oscType](
                params,
                state,
                output);
    }
}

#endif
