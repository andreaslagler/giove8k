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

#ifndef FILTER_H
#define	FILTER_H

#include "filter_types.h"
#include "fp_lib_types.h"

// Filter calculation function pointer type
typedef void (* T_CALC_FILTER) (const FilterParams *, FilterState *, _Q15 *, _Q15 *);

// Jump Table
extern const T_CALC_FILTER apfCalcFilter[];

//

inline static void calcFilter(
                              const FilterParams * const params,
                              FilterState * const state,
                              _Q15 * const coeffs, // work buffer for 4 coefficients allocated in .ydata
                              _Q15 * const data)
{
    // By default, xc16 won't compile a switch statement into a jump table
    const EFILTER_TYPE filterType = params->type;
    if (filterType < EFILTER_TYPE_NOFENTRIES)
    {
        apfCalcFilter[filterType](
                params,
                state,
                coeffs,
                data);
    }
}

#endif
