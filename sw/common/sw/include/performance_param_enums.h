/*
Copyright (C) 2024 Andreas Lagler

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

#ifndef PERFORMANCE_PARAM_ENUMS_H
#define PERFORMANCE_PARAM_ENUMS_H

#if __cplusplus

#include <stdint.h>
#include <numeric_limits.h>
#include <pgm_string.h>
#include <lookup_table.h>

#endif

#include "common_enum_def.h"

DEFINE_ENUM(
PerformanceParam,

// Panel Select section
PART_SELECT,

// Key Mode section
KEY_MODE,

// Arpeggiator/RPS section
ARP_STATE,
ARP_MODE,
ARP_RANGE,
ARP_HOLD,
ARP_TEMPO,

// Voice modulator section
VOICE_MODULATOR_STATE,

// External input section
VOCAL_INPUT_SELECT,

// Performance Common section (Bank[1])
PERFORMANCE_NAME,
PART_DETUNE,
OUTPUT_ASSIGN,
VOICE_ASSIGN,
SPLIT_POINT,
ARP_DESTINATION,
ARP_BEAT_PATTERN,
INDIVIDUAL_TRIG_STATE,
INDIVIDUAL_TRIG_DESTINATION,
INDIVIDUAL_TRIG_SOURCE_CHANNEL,
INDIVIDUAL_TRIG_SOURCE_NOTE,

// Voice modulator (Bank[2])
ALGORITHM,
CONTROL1_ASSIGN,
CONTROL2_ASSIGN,
EXT_INST_SEND,
EXT_VOCAL_SEND,
VOICE_MODULATOR_DELAY_TYPE,
VOICE_MODULATOR_DELAY_SYNC,
ENSEMBLE_TYPE,
ENSEMBLE_SYNC,
VOCAL_MORPH_CONTROL,
VOCAL_MORPH_SENS,
VOCAL_MORPH_THRESHOLD,

// Voice modulator panel
ENSEMBLE_LEVEL,
VOICE_MODULATOR_DELAY_LEVEL,
VOICE_MODULATOR_DELAY_TIME,
VOICE_MODULATOR_DELAY_FEEDBACK,
VOCAL_MIX,
VOICE_MODULATOR_RESONANCE,
VOICE_MODULATOR_ENV_RELEASE,
VOCAL_HOLD,
VOICE_MODULATOR_PAN,
VOICE_MODULATOR_LEVEL,
VOICE_MODULATOR_NOISE_LEVEL,
VOICE_MODULATOR_NOISE_CUTOFF,
GATE_THRESHOLD,
ROBOT_OSCILLATOR_LEVEL,
ROBOT_OSCILLATOR_PITCH,
ROBOT_OSCILLATOR_CONTROL,
CHARACTER_1,
CHARACTER_2,
CHARACTER_3,
CHARACTER_4,
CHARACTER_5,
CHARACTER_6,
CHARACTER_7,
CHARACTER_8,
CHARACTER_9,
CHARACTER_10,
CHARACTER_11,
CHARACTER_12)

#if __cplusplus

inline PgmString toString(const PerformanceParam param)
{
    using Table = SparseLUT<PgmString, PerformanceParam, PerformanceParam::NOFENTRIES>;

    constexpr static const PROGMEM Table table
    (
    ""_pgm,
    // Panel Select section
    Table::Entry(PerformanceParam::PART_SELECT, "Part Select"_pgm),
    
    // Key Mode section
    Table::Entry(PerformanceParam::KEY_MODE, "Key Mode"_pgm),
    
    // Arpeggiator/RPS section
    Table::Entry(PerformanceParam::ARP_STATE, "Arp/RPS State"_pgm),
    Table::Entry(PerformanceParam::ARP_MODE, "Arpeggio Mode"_pgm),
    Table::Entry(PerformanceParam::ARP_RANGE, "Arpeggio Range"_pgm),
    Table::Entry(PerformanceParam::ARP_HOLD, "Arp/RPS Hold"_pgm),
    Table::Entry(PerformanceParam::ARP_TEMPO, "Arp/RPS Tempo"_pgm),
    
    // Voice modulator section
    Table::Entry(PerformanceParam::VOICE_MODULATOR_STATE, ""_pgm),
    
    // External input section
    Table::Entry(PerformanceParam::VOCAL_INPUT_SELECT, ""_pgm),

    // Performance Common section (Bank[1])
    Table::Entry(PerformanceParam::PERFORMANCE_NAME, "Performance Name"_pgm),
    Table::Entry(PerformanceParam::PART_DETUNE, "Part Detune"_pgm),
    Table::Entry(PerformanceParam::OUTPUT_ASSIGN, "Output Assign"_pgm),
    Table::Entry(PerformanceParam::VOICE_ASSIGN, "Voice Assign"_pgm),
    Table::Entry(PerformanceParam::SPLIT_POINT, "Split Point"_pgm),
    Table::Entry(PerformanceParam::ARP_DESTINATION, "Arpeggio Dest"_pgm),
    Table::Entry(PerformanceParam::ARP_BEAT_PATTERN, "Arp Beat Pattern"_pgm),
    Table::Entry(PerformanceParam::INDIVIDUAL_TRIG_STATE, "Indv Trig Switch"_pgm),
    Table::Entry(PerformanceParam::INDIVIDUAL_TRIG_DESTINATION, "Indv Trig Dest"_pgm),
    Table::Entry(PerformanceParam::INDIVIDUAL_TRIG_SOURCE_CHANNEL, "Indv Trig Src CH"_pgm),
    Table::Entry(PerformanceParam::INDIVIDUAL_TRIG_SOURCE_NOTE, "IndvTrgSrc Note"_pgm),
    
    // Voice modulator (Bank[2])
    Table::Entry(PerformanceParam::ALGORITHM, "Algorithm"_pgm),
    Table::Entry(PerformanceParam::CONTROL1_ASSIGN, "Control1 Assign"_pgm),
    Table::Entry(PerformanceParam::CONTROL2_ASSIGN, "Control2 Assign"_pgm),
    Table::Entry(PerformanceParam::EXT_INST_SEND, "Ext->Inst Send"_pgm),
    Table::Entry(PerformanceParam::EXT_VOCAL_SEND, "Ext->Vocal Send"_pgm),
    Table::Entry(PerformanceParam::VOICE_MODULATOR_DELAY_TYPE, "V Delay Type"_pgm),
    Table::Entry(PerformanceParam::VOICE_MODULATOR_DELAY_SYNC, "V Delay Sync"_pgm),
    Table::Entry(PerformanceParam::ENSEMBLE_TYPE, "Ensemble Type"_pgm),
    Table::Entry(PerformanceParam::ENSEMBLE_SYNC, "Ensemble Sync"_pgm),
    Table::Entry(PerformanceParam::VOCAL_MORPH_CONTROL, "Vocal Morph Ctrl"_pgm),
    Table::Entry(PerformanceParam::VOCAL_MORPH_SENS, "Vocal Morph Sens"_pgm),
    Table::Entry(PerformanceParam::VOCAL_MORPH_THRESHOLD, "Vocal Morph Thrs"_pgm)
    );

    return table.getP(param);
}

#endif

#endif