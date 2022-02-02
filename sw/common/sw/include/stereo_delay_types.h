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
 * @file stereo_delay_types.h
 * @brief Type definitions for stereo delay effect
 * 
 * This file is part of Synth-Lib fixed-point synthesizer library for dsPIC33 family of Microchip dsPIC® digital signal controllers
 */

#ifndef STEREO_DELAY_TYPES_H
#define	STEREO_DELAY_TYPES_H

#include <stdint.h>
#include "fp_lib_types.h"
#include "iir_1pole_types.h"

/// Stereo delay parameters
typedef struct
{
    /// Delay time in samples
    uint16_t time;
    
    /// Delay feedback
    _Q15 feedback;
    
    /// Delay stereo spread (pind-pong amount)
    _Q15 spread;
    
    /// Delay brightness (0 = darkest ... 1 = brightest)
    _Q16 brightness;
    
    /// Delay Dry/Wet mix
    _Q15 mix;
} StereoDelayParams;

/// Stereo delay parameters
typedef struct
{
    /// Delay line write position
    uint16_t writePos;
    
    /// Delay line read position
    uint16_t readPos;
    
    /// Filter state for left channel
    IIROnePoleState filterStateLeft;
    
    /// Filter state for right channel
    IIROnePoleState filterStateRight;
} StereoDelayState;

#endif