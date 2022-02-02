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

#ifndef WAVE_INTERFACE_H
#define	WAVE_INTERFACE_H

#include "Synth_types.h"
#include <stdint.h>

void configureWaveInterface(void);
void transferWaveBuffer(const int16_t *);

const PatchParams * getPatchParams();
const VoiceParams * getVoiceParams(uint8_t);

#endif
