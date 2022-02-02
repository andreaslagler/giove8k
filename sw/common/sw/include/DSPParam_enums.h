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

#ifndef DSP_PARAM_ENUMS_H
#define DSP_PARAM_ENUMS_H

#include "PatchParam_enums.h"
#include "SceneParam_enums.h"
#include "ControllerParam_enums.h"
#include <stdint.h>

#if __cplusplus

// For the controller C++ project, DSP parameter is defined as enum class 
enum class DSPParam : uint8_t
{
    // Patch parameters start at 0x00
    PATCH_PARAM_BASE = 0x00,
    
    // Scene parameters
    SCENE_PARAM_BASE = PATCH_PARAM_BASE + static_cast<uint8_t>(PatchParam::NOFENTRIES),
    
    // Controller parameters
    CONTROLLER_PARAM_BASE = SCENE_PARAM_BASE + static_cast<uint8_t>(SceneParam::NOFENTRIES),
    
    NOFENTRIES = CONTROLLER_PARAM_BASE + static_cast<uint8_t>(ControllerParam::NOFENTRIES),
    
    // Notes start at 0xC0
    NOTE_BASE = 0xC0,
};

#else

// For the DSP C project, DSP parameter is defined as plain untyped enum
typedef enum
// This is the actual enum definition part
{
    // Patch parameters start at 0x00
    EDSP_PARAM_PATCH_PARAM_BASE = 0x00,
    
    // Scene parameters
    EDSP_PARAM_SCENE_PARAM_BASE = EDSP_PARAM_PATCH_PARAM_BASE + EPATCH_PARAM_NOFENTRIES,
    
    // Controller parameters
    EDSP_PARAM_CONTROLLER_PARAM_BASE = EDSP_PARAM_SCENE_PARAM_BASE + ESCENE_PARAM_NOFENTRIES,
    
    EDSP_PARAM_NOFENTRIES = EDSP_PARAM_CONTROLLER_PARAM_BASE + ECONTROLLER_PARAM_NOFENTRIES,
    
    // Notes start at 0xC0
    EDSP_PARAM_NOTE_BASE = 0xC0,
} EDSP_PARAM;

#endif

#endif