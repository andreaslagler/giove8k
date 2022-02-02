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

#ifndef CONTROLLER_PARAM_ENUMS_H
#define CONTROLLER_PARAM_ENUMS_H

#if __cplusplus

#include <stdint.h>

// For the controller C++ project, patch parameter is implemented as enum class 
#define DEFINE_CONTROLLER_PARAM(param) param
enum class ControllerParam : uint8_t

#else

#define DEFINE_CONTROLLER_PARAM(param) ECONTROLLER_PARAM_##param
typedef enum

#endif

// This is the actual enum definition part
{
    DEFINE_CONTROLLER_PARAM(SELECTED_LAYER) = 0,
    DEFINE_CONTROLLER_PARAM(MODULATION_MSB),
    DEFINE_CONTROLLER_PARAM(MODULATION_LSB),
    DEFINE_CONTROLLER_PARAM(PITCHBEND_MSB),
    DEFINE_CONTROLLER_PARAM(PITCHBEND_LSB),

    DEFINE_CONTROLLER_PARAM(NOFENTRIES),
    DEFINE_CONTROLLER_PARAM(MIN) = 0,
    DEFINE_CONTROLLER_PARAM(MAX) = DEFINE_CONTROLLER_PARAM(NOFENTRIES)-1
}


#if __cplusplus

;

#else

// end of typedef
ECONTROLLER_PARAM;

#endif

#undef DEFINE_CONTROLLER_PARAM


#endif