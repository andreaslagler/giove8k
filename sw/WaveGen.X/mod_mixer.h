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

#ifndef MOD_MIXER_H
#define MOD_MIXER_H

#include "modMixer_types.h"
#include "fp_lib_types.h"

// Calc mod
static inline _Q15 calcMod_Q15(
        const _Q15 init,
        const ModSource * const modSource,
        const ModAmount * const modAmount)
{
    // Cache pointers for use with DSP instructions
    const _Q15 * modSrc = modSource->modSource;
    const _Q15 * modAmt = modAmount->modAmount;

    // Calculate the modulation result as sum of initial value and all modulation sources weighted with their corresponding modulation amount
    _Q15 result;
    __asm__ volatile("\
        lac     %[Init], #0, A                                                  ;1C load initial value to AccA \n \
        movsac  A, [%[Amt]]+=2, w4, [%[Src]]+=2, w5                             ;1C prefetch first Mod Amount and Source \n \
        repeat  #%[NofSrc]-1                                                    ;1C repeat for all modulation sources \n \
        mac     w4 * w5, A, [%[Amt]]+=2, w4, [%[Src]]+=2, w5                    ;1C add Amt * Src to AccA, prefetch next Mod Amount and Source \n \
        sac.r   A, #0, %[Res]                                                   ;1C store result \n \
        ; 4+NOF_MOD_SOURCE cycles total"
            : [Res]"=r"(result), [Amt]"+x"(modAmt), [Src]"+y"(modSrc) /*out*/
            : [Init]"r"(init), [NofSrc]"i"(NOF_MOD_SOURCES) /*in*/
            : "w4", "w5"/*clobbered*/
            );

    return result;
}

// Calc mod
static inline _Q16 calcMod_Q16(
        const _Q16 init,
        const ModSource * const modSource,
        const ModAmount * const modAmount)
{
    const _Q15 result = calcMod_Q15(
            convert_Q16_Q15(init),
            modSource,
            modAmount);

    return convert_Q15_Q16(result);
}

////////////////////////////////////////////////////////////////////////////////
// Calc oscillator frequency from all modulation sources
static inline int16_t calcOscPitch(
        const int16_t note,
        const int16_t pitch,
        const ModSource * const modSource,
        const ModAmount * const modAmount)
{
    // Cache pointers for use with DSP instructions
    const _Q15 * modAmt = modAmount->modAmount;
    const _Q15 * modSrc = modSource->modSource;

    // Perform calculation steps as in calcMod_Q15, but don't store the accumulator result yet
    __asm__ volatile("\
        lac     %[Init], #0, A                                                  ;Load initial value to AccA \n \
        movsac  A, [%[Amt]]+=2, w4, [%[Src]]+=2, w5                             ;Prefetch first Mod Amount and Source \n \
        repeat  #%[NofSrc]-1                                                    ;Repeat for all modulation sources \n \
        mac     w4 * w5, A, [%[Amt]]+=2, w4, [%[Src]]+=2, w5                    ;Add Amt * Src to AccA, prefetch next Mod Amount and Source \n \
        ; 3+NOF_MOD_SOURCE cycles total"
            : [Amt]"+x"(modAmt), [Src]"+y"(modSrc) /*out*/
            : [Init]"r"(pitch), [NofSrc]"i"(NOF_MOD_SOURCES) /*in*/
            : "w4", "w5"/*clobbered*/
            );

    // Add note       
    __asm__ volatile("add %[Note], #0, A"
            : /*out*/
            : [Note]"r"(note) /*in*/
            : /*clobbered*/
            );

    // Read modified pitch
    int16_t modPitch;
    __asm__ volatile("sac.r A, #0, %[Res]"
            : [Res]"=r"(modPitch) /*out*/
            : /*in*/
            : /*clobbered*/
            );

    return modPitch;
}

////////////////////////////////////////////////////////////////////////////////
// Calc filter frequency from all modulation sources
static inline int16_t calcFilterFreq(
        const int16_t freq,
        const ModSourceFilterFreq * const modSource,
        const ModAmountFilterFreq * const modAmount)
{
    // Cache pointers
    const _Q15 * modSrc = modSource->modSource.modSource;
    const _Q15 * modAmt = modAmount->modAmount.modAmount;

    // Perform calculation steps as in calcMod_Q15, but don't store the accumulator result yet
    __asm__ volatile("\
        lac     %[Init], #0, A                                                  ;1C load initial value to AccA \n \
        movsac  A, [%[Amt]]+=2, w4, [%[Src]]+=2, w5                             ;1C prefetch first Mod Amount and Source \n \
        repeat  #%[NofSrc]-1                                                    ;1C repeat for all modulation sources \n \
        mac     w4 * w5, A, [%[Amt]]+=2, w4, [%[Src]]+=2, w5                    ;1C add Amt * Src to AccA, prefetch next Mod Amount and Source \n \
        ; 3+NOF_MOD_SOURCE cycles total"
            : [Amt]"+x"(modAmt), [Src]"+y"(modSrc) /*out*/
            : [Init]"r"(freq), [NofSrc]"i"(NOF_MOD_SOURCES) /*in*/
            : "w4", "w5"/*clobbered*/
            );

    // Add filter-specific modulation

    // Filter envelope        
    __asm__ volatile("mac %[Src] * %[Amt], A"
            : /*out*/
            : [Src]"z"(modSource->envValue), [Amt]"z"(modAmount->envAmount) /*in*/
            : /*clobbered*/
            );

    // Filter keytrack
    // TODO normalize Note to maximum possible cutoff (as given by the SVF design)
    __asm__ volatile("mac %[Src] * %[Amt], A"
            : /*out*/
            : [Src]"z"(modSource->note), [Amt]"z"(modAmount->keyTrack) /*in*/
            : /*clobbered*/
            );

    // Read modified cutoff
    int16_t modFreq;
    __asm__ volatile("sac.r A, #0, %[Res]"
            : [Res]"=r"(modFreq) /*out*/
            : /*in*/
            : /*clobbered*/
            );

    return modFreq;
}

////////////////////////////////////////////////////////////////////////////////
// Calc FO rate from all modulation sources
static inline _Q15 calcLFORate(
        const _Q15 rate,
        const ModSource * const modSource,
        const ModAmountLFORate * const modAmount)
{
    _Q15 modRate;
    const _Q15 * modSrc = modSource->modSource;
    const _Q15 * modAmt = modAmount->modAmount;

    __asm__ volatile("\
        lac     %[Init], #0, A                                                  ;1C load initial value to AccA, Q0.16 --> Q0.15 \n \
        movsac  A, [%[Amt]]+=2, w4, [%[Src]]+=2, w5                             ;1C prefetch first Mod Amount and Source \n \
        repeat  #%[NofSrc]-1                                                    ;1C repeat for all modulation sources \n \
        mac     w4 * w5, A, [%[Amt]]+=2, w4, [%[Src]]+=2, w5                    ;1C add Amt * Src to AccA, prefetch next Mod Amount and Source \n \
        sac.r   A, #0, %[Res]                                                   ;1C store result \n \
        ; 4+NOF_MOD_SOURCE cycles total"
            : [Res]"=r"(modRate), [Amt]"+x"(modAmt), [Src]"+y"(modSrc) /*out*/
            : [Init]"r"(rate), [NofSrc]"i"(NOF_MOD_SOURCES - 1) /*in*/
            : "w4", "w5"/*clobbered*/
            );

    return modRate;
}

#endif