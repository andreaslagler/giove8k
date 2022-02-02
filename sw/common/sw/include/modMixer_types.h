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

#ifndef MOD_MIXER_TYPES_H
#define MOD_MIXER_TYPES_H

#include "fp_lib_types.h"

//
#define NOF_MOD_SOURCES 4

typedef union
{
    struct
    {
        _Q15 modWheelValue;
        _Q15 auxEnvValue;
        _Q15 lfo1Value;
        _Q15 lfo2Value;
    };

    _Q15 modSource[NOF_MOD_SOURCES];
} ModSource;

//
typedef struct
{
    int16_t note;
    _Q16 envValue;
    ModSource modSource;
} ModSourceFilterFreq;

//
typedef union
{
    struct
    {
        _Q15 modWheelAmount;
        _Q15 auxEnvAmount;
        _Q15 lfo1Amount;
        _Q15 lfo2Amount;
    };

    _Q15 modAmount[NOF_MOD_SOURCES];
} ModAmount;

//
typedef struct
{
    _Q15 keyTrack;
    _Q15 envAmount;
    ModAmount modAmount;
} ModAmountFilterFreq;

//
typedef union
{
    struct
    {
        _Q15 modWheelAmount;
        _Q15 auxEnvAmount;
        _Q15 lfo1Amount;
    };

    _Q15 modAmount[NOF_MOD_SOURCES-1]; // LFO doesn't modulate itself
} ModAmountLFORate;

#endif