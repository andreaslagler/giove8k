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

#ifndef SCENE_PARAM_ENUMS_H
#define SCENE_PARAM_ENUMS_H

#if __cplusplus

#include <stdint.h>

// For the controller C++ project, patch parameter is implemented as enum class 
#define DEFINE_SCENE_PARAM(param) param
enum class SceneParam : uint8_t

#else

#define DEFINE_SCENE_PARAM(param) ESCENE_PARAM_##param
typedef enum

#endif

// This is the actual enum definition part
{
    DEFINE_SCENE_PARAM(LAYER_MODE) = 0,

    DEFINE_SCENE_PARAM(NOFENTRIES),
    DEFINE_SCENE_PARAM(MIN) = 0,
    DEFINE_SCENE_PARAM(MAX) = DEFINE_SCENE_PARAM(NOFENTRIES)-1
}


#if __cplusplus

;

inline SceneParam& operator++(SceneParam & arg)
{
    return arg = static_cast<SceneParam>(static_cast<uint8_t>(arg)+1);
}

inline SceneParam& operator--(SceneParam & arg)
{
    return arg = static_cast<SceneParam>(static_cast<uint8_t>(arg)-1);
}

#else

// end of typedef
ESCENE_PARAM;

#endif

#undef DEFINE_SCENE_PARAM


#endif