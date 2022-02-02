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

#ifndef FILTER_TYPES_H
#define	FILTER_TYPES_H

#include "Filter_enums.h"
#include "SVF_2Pole_types.h"

#include "fp_lib_types.h"
#include <stdint.h>
#include <stdbool.h>


typedef struct
{
    EFILTER_TYPE type;
    int16_t freq;
    _Q16 shape;
} FilterParams;


//
typedef union
{
    SVF2PoleState state2Pole;
    
    struct
    {
        SVF2PoleState stage1;
        SVF2PoleState stage2;
    } state4Pole;    

    struct
    {
        SVF2PoleState stages[4];
    } stateFormant;    
} FilterState;

#endif
