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

#ifndef SCENE_ENUMS_H
#define	SCENE_ENUMS_H

#if __cplusplus

#include <stdint.h>

// For the controller C++ project, patch parameter is implemented as enum class
#define DEFINE_ELAYER_MODE(param) param
enum class LayerMode : uint8_t

#else

#define DEFINE_ELAYER_MODE(param) LAYER_MODE_##param
typedef enum

#endif

// This is the actual enum definition part
{
    DEFINE_ELAYER_MODE(SINGLE) = 0,
    DEFINE_ELAYER_MODE(MULTI_1X4),
    DEFINE_ELAYER_MODE(MULTI_4X1),
    DEFINE_ELAYER_MODE(UNISON),
    DEFINE_ELAYER_MODE(NOFENTRIES),
    DEFINE_ELAYER_MODE(MIN) = 0,
    DEFINE_ELAYER_MODE(MAX) = DEFINE_ELAYER_MODE(NOFENTRIES)-1
}

#if __cplusplus

;

inline LayerMode& operator++(LayerMode & arg)
{
    return arg = static_cast<LayerMode>(static_cast<uint8_t>(arg)+1);
}

inline LayerMode& operator--(LayerMode & arg)
{
    return arg = static_cast<LayerMode>(static_cast<uint8_t>(arg)-1);
}

#else

// end of typedef
LayerMode;

#endif

#undef DEFINE_ELAYER_MODE

#endif
