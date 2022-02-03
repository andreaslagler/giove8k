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

#ifndef DSP_H
#define DSP_H

#include "fp_lib.h"
#include "Synth_types.h"
#include "Voice.h"
#include <stdint.h>

//inline static void calcWaveform(
//
//        WaveBuffer * waveBufferAcc
//
//)
//{
//        // Calculate and Update all voices
//        WaveBuffer waveBufferVoice[NOF_VOICES_DSP];
//        for (uint8_t cntVoice = 0; cntVoice < NOF_VOICES_DSP; ++cntVoice)
//        {
//            // Calc waveform data
//            calcVoice(
//                    getPatchParams(),
//                    getVoiceParams(cntVoice),
//                    &voiceState[cntVoice],
//                    &waveBufferVoice[cntVoice]);
//        }
//
//        // Accumulate all voices
//        for (uint8_t cntSample = 0; cntSample < BLOCK_LEN * 2; ++cntSample)
//        {
//            // Use the accumulator register to accumulate all voices into one wave buffer and get implicit single-cycle saturation of the sum
//            // Prefer built-in functions over inline asm here - Compiler will unroll the for-loop across all voices
//            // Hardware for-loop across all samples has to be sacrificed, though.
//            
//            // Load sample of first voice into accumulator
//            volatile register int acc asm("A");
//            acc = __builtin_lac(waveBufferVoice[0].aiBuffer[cntSample], 0);
//
//            // The iteration count of this for-loop is compile-time constant, so the compiler can unroll it (and does for nummber of voices = 4)
//            for (uint8_t cntVoice = 1; cntVoice < NOF_VOICES_DSP; ++cntVoice)
//            {
//                // Add sample of remaining voices
//                acc = __builtin_add(acc, waveBufferVoice[cntVoice].aiBuffer[cntSample], 0);
//            }
//
//            // Clip sum of samples to int16 and write to output buffer
//            waveBufferAcc->aiBuffer[cntSample] = __builtin_sacr(acc, 0);
//        }
//}

#endif
