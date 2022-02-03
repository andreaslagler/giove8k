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

#ifndef VOICE_H
#define	VOICE_H

#include "Synth_types.h"
#include "Voice_types.h"

//
void calcVoice(
               const PatchParams *,
               const VoiceParams *,
               VoiceState *,
       _Q15 * const xWorkBuffer, // Has to be allocated in .xdata, size = BLOCK_LEN
       _Q15 * const yWorkBuffer, // Has to be allocated in .ydata, size = 6
               DSPBuffer *);

//
void initVoice(VoiceState *);

#endif
