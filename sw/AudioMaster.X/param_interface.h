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
 * @file param_interface.h
 * @brief Function prototypes for parameter interface
 * 
 * This file is part of the Audio/FX module
 */

#ifndef PARAMINTERFACE_H
#define	PARAMINTERFACE_H

#include <stdint.h>

/**
 * @brief Get patch parameters
 * 
 * Get read-only access to patch parameters for selected DSP
 * @param dspIdx DSP Index 0/1
 * @return Pointer to patch parameter buffer
 */
const uint8_t * getPatchParams(uint16_t dspIdx);

/**
 * @brief Get scene parameters
 * 
 * Get read-only access to scene parameters
 * @return Pointer to scene parameters
 */
const uint8_t * getSceneParams();

/**
 * @brief Get controller parameters
 * 
 * Get read-only access to controller parameters
 * @return Pointer to controller parameters
 */
const uint8_t * getControllerParams();

/**
 * @brief Callback function for parameter reception
 * 
 * Parameter data is evaluated and the corresponding parameter is updated
 * @param Received parameter data
 */
void onParamReceive (uint16_t param);

#endif
