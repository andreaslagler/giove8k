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
 * @file param_interface.c
 * @brief Impementation of parameter interface
 * 
 * This file is part of the Audio/FX module
 */

#include "param_interface.h"
#include "voice_manager.h"
#include "synth_def.h"
#include "DSPParam_enums.h"
#include "Scene_enums.h"
#include "env_adsr_types.h"
#include <stdint.h>
#include <xc.h>

/// Raw patch parameters
static volatile uint8_t patchParams[NOF_LAYERS][EPATCH_PARAM_NOFENTRIES] = {{0}, {0}};

/// Raw scene parameters
static volatile uint8_t sceneParams[ESCENE_PARAM_NOFENTRIES] = {0};

/// Raw controller parameters
static volatile uint8_t controllerParams[ECONTROLLER_PARAM_NOFENTRIES] = {0};

/**
 * @brief Get patch parameters
 * 
 * Get read-only access to patch parameters for selected DSP
 * @param dspIdx DSP Index 0/1
 * @return Pointer to patch parameter buffer
 */
const uint8_t * getPatchParams(const uint16_t dspIdx)
{
    // Parameters for both layers are available regardless of actual layer mode.
    // --> return parameters for layer 0 in single layer mode for all DSPs
    const uint16_t layer = (LAYER_MODE_SINGLE == sceneParams[ESCENE_PARAM_LAYER_MODE]) ? 0 : dspIdx;
    return (const uint8_t *) patchParams[layer];
}

/**
 * @brief Get scene parameters
 * 
 * Get read-only access to scene parameters
 * @return Pointer to scene parameters
 */
const uint8_t * getSceneParams()
{
    return (const uint8_t *) sceneParams;
}

/**
 * @brief Get controller parameters
 * 
 * Get read-only access to controller parameters
 * @return Pointer to controller parameters
 */
const uint8_t * getControllerParams()
{
    return (const uint8_t *) controllerParams;
}

/**
 * @brief Callback function for parameter reception
 * 
 * Parameter data is evaluated and the corresponding parameter is updated
 * @param Received parameter data
 */
void onParamReceive (const uint16_t param)
{
    // Split up 16-bit parameter data into parameter value and index
    const uint8_t paramValue = param;
    const uint16_t paramIndex = param >> 8;
    
    if (paramIndex >= EDSP_PARAM_NOTE_BASE)
    {
        const uint16_t selectedLayer = controllerParams[ECONTROLLER_PARAM_SELECTED_LAYER];
        onNoteMessage(param, sceneParams[ESCENE_PARAM_LAYER_MODE], patchParams[selectedLayer][EPATCH_PARAM_LEGATO] == 1);
    }
    else if (paramIndex >= EDSP_PARAM_CONTROLLER_PARAM_BASE)
    {
        // Controller parameter
        controllerParams[paramIndex - EDSP_PARAM_CONTROLLER_PARAM_BASE] = paramValue;
    }
    else if (paramIndex >= EDSP_PARAM_SCENE_PARAM_BASE)
    {
        // Scene parameter
        sceneParams[paramIndex - EDSP_PARAM_SCENE_PARAM_BASE] = paramValue;
    }
    else if (paramIndex >= EDSP_PARAM_PATCH_PARAM_BASE)
    {
        // Patch parameter
        const uint16_t selectedLayer = controllerParams[ECONTROLLER_PARAM_SELECTED_LAYER];
        patchParams[selectedLayer][paramIndex-EDSP_PARAM_PATCH_PARAM_BASE] = paramValue;
    }    
}