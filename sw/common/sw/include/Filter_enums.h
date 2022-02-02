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

#ifndef FILTER_ENUMS_H
#define	FILTER_ENUMS_H

#if __cplusplus

#include <stdint.h>

// For the controller C++ project, patch parameter is implemented as enum class
#define DEFINE_FILTER_TYPE(param) param
enum class FilterType : uint8_t

#else

#define DEFINE_FILTER_TYPE(param) EFILTER_TYPE_##param
typedef enum

#endif

// This is the actual enum definition part
{
    DEFINE_FILTER_TYPE(LOWPASS_2P) = 0,
    DEFINE_FILTER_TYPE(LOWPASS_4P),
    DEFINE_FILTER_TYPE(BANDPASS_2P),
    DEFINE_FILTER_TYPE(BANDPASS_4P),
    DEFINE_FILTER_TYPE(HIGHPASS_2P),
    DEFINE_FILTER_TYPE(HIGHPASS_4P),
    DEFINE_FILTER_TYPE(VOCAL),
    DEFINE_FILTER_TYPE(NONE),
    DEFINE_FILTER_TYPE(NOFENTRIES),
    DEFINE_FILTER_TYPE(MIN) = 0,
    DEFINE_FILTER_TYPE(MAX) = DEFINE_FILTER_TYPE(NOFENTRIES)-1    
}

#if __cplusplus

;

#else

// end of typedef
EFILTER_TYPE;

#endif

#undef DEFINE_FILTER_TYPE

#endif
