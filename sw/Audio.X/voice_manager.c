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
 * @file voice_manager.c
 * @brief Impementation of voice manager
 * 
 * This file is part of the Audio/FX module
 */

#include "voice_manager.h"
//#include "voice_manager_types.h"
#include "synth_def.h"
#include "scene_enums.h"
#include <stdint.h>
#include <stdbool.h>

/// Raw voice parameters
static volatile VoiceParams voiceParams[NOF_VOICES_TOTAL];

/// Priority for voice assignment (0 - lowest priority ... 255 - highest priority)
static uint8_t voicePriority[NOF_VOICES_TOTAL]; // Should only be changed inside ISR
/**
 * @brief Get raw voice parameters for selected DSP
 * @param dspIdx
 * @return 
 */
VoiceParams * getVoiceParams(const uint16_t dspIdx)
{
    return (VoiceParams *) (&voiceParams[dspIdx * NOF_VOICES_DSP]);
}
/**
 * @brief Increment the assignment priority of all voices
 */
static inline void incVoicePriority()
{
    for (uint8_t cntVoice = 0; cntVoice < NOF_VOICES_TOTAL; ++cntVoice)
    {
        if (255 != voicePriority[cntVoice])
        {
            ++voicePriority[cntVoice];
        }
    }
}
/**
 * @brief Find a voice to play the given note
 * 
 * Find voice which either \n
 * - is already playing the note  -or- \n
 * - has lowest assignment priority
 * @param note MIDI note index
 * @param firstVoiceIdx Index of first voice available for assignment
 * @param nofVoices Number of voices available for assignment
 * @return Index of assigned voice
 */
static inline uint8_t getVoice(
        const uint8_t note,
        const uint8_t firstVoiceIdx,
        const uint8_t nofVoices)
{
    uint8_t uiMaxPriority = 0;
    uint8_t voice = 0;

    for (uint8_t cntVoice = firstVoiceIdx; cntVoice < firstVoiceIdx + nofVoices; ++cntVoice)
    {
        // If the note is already assigned to a voice, return that voice immediately
        if (note == voiceParams[cntVoice].note)
        {
            voice = cntVoice;
            break;
        }

        // Find voice with highest priority
        const uint8_t uiPriority = voicePriority[cntVoice];
        if (uiPriority > uiMaxPriority)
        {
            uiMaxPriority = uiPriority;
            voice = cntVoice;
        }
    }

    // If note is not already assigned to a voice, return voice with highest priority
    return voice;
}
/**
 * @brief Get a voice to play a given note in single layer mode
 * @param currentVoiceParams Parameters of current note to be played
 */
static inline void NoteOnSingleLayer(VoiceParams currentVoiceParams, const bool legato)
{
    // Both DSPs use the same patch data, so the notes can be assigned to any available voice accross DSPs
    const uint8_t voice = legato ? 0 : getVoice(currentVoiceParams.note, 0, NOF_VOICES_TOTAL);

    // Overwrite voice params
    currentVoiceParams.trigger = legato ? (!voiceParams[voice].gate) : true;
    currentVoiceParams.gate = true;

    // Assign params to currently used voice
    voiceParams[voice] = currentVoiceParams;

    // Currently assigned voice has lowest priority
    voicePriority[voice] = 0;

    // Increment the priority of all voices
    incVoicePriority();
}
/**
 * @brief Get a voice to play a given note in 1x4 layer mode
 * @param currentVoiceParams Parameters of current note to be played
 */
static inline void NoteOn1x4Layer(VoiceParams currentVoiceParams, const bool legato)
{
    // Every DSs uses different patch but same note data, so the note can be assigned to any available voice of one DSP
    const uint8_t voice = legato ? 0 : getVoice(currentVoiceParams.note, 0, NOF_VOICES_DSP);

    // Overwrite voice params
    currentVoiceParams.trigger = legato ? (!voiceParams[voice].gate) : true;
    currentVoiceParams.gate = true;

    for (uint16_t cntDSP = 0; cntDSP < NOF_DSPS; ++cntDSP)
    {
        // Assign params to currently used voice
        voiceParams[voice + NOF_VOICES_DSP * cntDSP] = currentVoiceParams;

        // Currently assigned voices have lowest priority
        voicePriority[voice + NOF_VOICES_DSP * cntDSP] = 0;
    }

    // Increment the priority of all voices
    incVoicePriority();
}
/**
 * @brief Get a voice to play a given note in 4x1 layer mode
 * @param currentVoiceParams Parameters of current note to be played
 */
static inline void NoteOn4x1Layer(VoiceParams currentVoiceParams, const bool legato)
{
    // Both DSPs use different patch and note data, the note will be assigned to DSPs depending on the note value
//    const uint8_t voice = legato ? 0 : getVoice(currentVoiceParams.note, currentVoiceParams.layer * NOF_VOICES_DSP, NOF_VOICES_DSP);
    const uint8_t voice = legato ? 0 : getVoice(currentVoiceParams.note, 0 * NOF_VOICES_DSP, NOF_VOICES_DSP);

    // Overwrite voice params
    currentVoiceParams.trigger = legato ? (!voiceParams[voice].gate) : true;
    currentVoiceParams.gate = true;

    // Assign params to currently used voice
    voiceParams[voice] = currentVoiceParams;

    // Currently assigned voice has lowest priority
    voicePriority[voice] = 0;

    // Increment the priority of all voices
    incVoicePriority();
}
/**
 * @brief Get a voice to play a given note in unison mode
 * @param currentVoiceParams Parameters of current note to be played
 */
static inline void NoteOnUnison(VoiceParams currentVoiceParams, const bool legato)
{
    // Overwrite voice params
    currentVoiceParams.trigger = legato ? (!voiceParams[0].gate) : true;
    currentVoiceParams.gate = true;

    for (uint16_t cntVoice = 0; cntVoice < NOF_VOICES_TOTAL; ++cntVoice)
    {
        // Assign params to currently used voice
        voiceParams[cntVoice] = currentVoiceParams;

        // Currently assigned voices have lowest priority
        voicePriority[cntVoice] = 0;
    }

    // Increment the priority of all voices
    incVoicePriority();
}
/**
 * @brief Get a voice to play a given note
 * @param currentVoiceParams 
 * @param layerMode Layer mode Single/Dual/Split
 */
static inline void NoteOn(
        VoiceParams currentVoiceParams,
        const uint16_t layerMode,
        const bool legato)
{
    switch (layerMode)
    {
        case LAYER_MODE_SINGLE:
            NoteOnSingleLayer(currentVoiceParams, legato);
            break;

        case LAYER_MODE_MULTI_1X4:
            NoteOn1x4Layer(currentVoiceParams, legato);
            break;

        case LAYER_MODE_MULTI_4X1:
            NoteOn4x1Layer(currentVoiceParams, legato);
            break;

        case LAYER_MODE_UNISON:
            NoteOnUnison(currentVoiceParams, legato);
            break;

        default:
            break;
    }
}
/**
 * @brief Release the voice playing a given note
 * @param note MIDI note index
 */
static inline void NoteOff(const uint8_t note)
{
    // Loop through all voices
    for (uint8_t cntVoice = 0; cntVoice < NOF_VOICES_TOTAL; ++cntVoice)
    {
        if (note == voiceParams[cntVoice].note)
        {
            // Clear gate, but keep played note and velocity, so the note release sounds properly
            voiceParams[cntVoice].gate = false;
        }
    }
}
/**
 * @brief Callback function for received note message
 * @param noteMessage Note message of currently played note
 * @param layerMode Layer mode
 */
void onNoteMessage(
        const uint16_t noteMessage,
        const uint16_t layerMode,
        const bool legato)
{
    const VoiceParams currentVoiceParams = {.data = noteMessage};

    // Note on/off event
    if (currentVoiceParams.velocity != 0) // velocity is unsigned, so a check against inequality is sufficient and can be realized by
    {
        // Note ON
        NoteOn(currentVoiceParams, layerMode, legato);
    }
    else
    {
        // Note OFF
        NoteOff(currentVoiceParams.note);
    }
}
/**
 * @brief Release all notes
 */
void allNotesOff()
{
    // Clear gate for all voices
    for (uint8_t cntVoice = 0; cntVoice < NOF_VOICES_TOTAL; ++cntVoice)
    {
        voiceParams[cntVoice].gate = false;
    }
}
