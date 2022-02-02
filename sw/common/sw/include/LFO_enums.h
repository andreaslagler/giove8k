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

#ifndef LFO_ENUMS_H
#define	LFO_ENUMS_H

#if __cplusplus

#include <stdint.h>

// For the controller C++ project, patch parameter is implemented as enum class
#define DEFINE_LFO_WAVEFORM(param) param
enum class LFOWaveform : uint8_t

#else

#define DEFINE_LFO_WAVEFORM(param) ELFO_WAVEFORM_##param
typedef enum

#endif

// This is the actual enum definition part
{
    DEFINE_LFO_WAVEFORM(SQUARE) = 0,
    DEFINE_LFO_WAVEFORM(SAW),
    DEFINE_LFO_WAVEFORM(TRI),
    DEFINE_LFO_WAVEFORM(SINE),
    DEFINE_LFO_WAVEFORM(RANDOM),
    DEFINE_LFO_WAVEFORM(SAMPLEHOLD),
    DEFINE_LFO_WAVEFORM(NOFENTRIES),
    DEFINE_LFO_WAVEFORM(MIN) = 0,
    DEFINE_LFO_WAVEFORM(MAX) = DEFINE_LFO_WAVEFORM(NOFENTRIES)-1,
}

#if __cplusplus

;

#else

// end of typedef
LFOWaveform;

#endif

#undef DEFINE_LFO_WAVEFORM

// LFO Synchronization

#if __cplusplus

#include <stdint.h>

// For the controller C++ project, patch parameter is implemented as enum class
#define DEFINE_LFO_SYNC(param) param
enum class LFOSync : uint8_t

#else

#define DEFINE_LFO_SYNC(param) ELFO_SYNC_##param

typedef enum

#endif

// This is the actual enum definition part
{
    DEFINE_LFO_SYNC(LFO1) = 0,
    DEFINE_LFO_SYNC(KEY),
    DEFINE_LFO_SYNC(BPM),
    DEFINE_LFO_SYNC(OFF),
    DEFINE_LFO_SYNC(NOFENTRIES),
    DEFINE_LFO_SYNC(MIN = 0),
    DEFINE_LFO_SYNC(MAX) = DEFINE_LFO_SYNC(NOFENTRIES)-1,
}

#if __cplusplus

;

#else

// end of typedef
LFOSync;

#endif

#undef DEFINE_LFO_SYNC

#endif
