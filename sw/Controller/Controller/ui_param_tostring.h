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

#ifndef UI_PARAM_TOSTRING_H
#define UI_PARAM_TOSTRING_H

#include "ui_param_def.h"

#include <lookup_table.h>
#include <string.h>
#include <pgm_string.h>

inline uint8_t toString(const UnsignedParam& value)
{
    return value;
}

inline int8_t toString(const SignedParam& value)
{
    return value;
}

inline bool toString(const BooleanParam& value)
{
    return value;
}

inline String<> toString(const NameParam& value)
{
    PgmString characters("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+&$!?"_pgm);
    char buffer[16];
    for (uint8_t cnt = 0; cnt < 16; ++cnt)
    {
        buffer[cnt] = characters[value.m_value[cnt]];
    }
    return String<>(buffer, 16);
}

inline PgmString toString(const OnOff& value)
{
    return value ? "On"_pgm : "Off"_pgm;
}

inline PgmString toString(const LFO1Waveform value)
{
    using Table = SparseLUT<PgmString, LFO1Waveform, LFO1Waveform::NOFENTRIES>;

    constexpr static const PROGMEM Table table
    (
    ""_pgm,
    Table::Entry(LFO1Waveform::TRI, "TRI"_pgm),
    Table::Entry(LFO1Waveform::SAW, "SAW"_pgm),
    Table::Entry(LFO1Waveform::SQR, "SQR"_pgm),
    Table::Entry(LFO1Waveform::S_H, "S&H"_pgm)
    );

    return table.getP(value);
}

inline PgmString toString(const LFO2DepthSelect value)
{
    using Table = SparseLUT<PgmString, LFO2DepthSelect, LFO2DepthSelect::NOFENTRIES>;

    constexpr static const PROGMEM Table table
    (
    ""_pgm,
    Table::Entry(LFO2DepthSelect::PITCH, "PITCH"_pgm),
    Table::Entry(LFO2DepthSelect::FILTER, "FILTER"_pgm),
    Table::Entry(LFO2DepthSelect::AMP, "AMP"_pgm)
    );

    return table.getP(value);
}

inline PgmString toString(const OSC1Waveform value)
{
    using Table = SparseLUT<PgmString, OSC1Waveform, OSC1Waveform::NOFENTRIES>;

    constexpr static const PROGMEM Table table
    (
    ""_pgm,
    Table::Entry(OSC1Waveform::SUPER_SAW, "SUPER SAW"_pgm),
    Table::Entry(OSC1Waveform::TRIANGLE_MOD, "TRIANGLE MOD"_pgm),
    Table::Entry(OSC1Waveform::NOISE, "NOISE"_pgm),
    Table::Entry(OSC1Waveform::FEEDBACK_OSC, "FEEDBACK OSC"_pgm),
    Table::Entry(OSC1Waveform::SQR, "SQR"_pgm),
    Table::Entry(OSC1Waveform::SAW, "SAW"_pgm),
    Table::Entry(OSC1Waveform::TRI, "TRI"_pgm)
    );

    return table.getP(value);
}

inline PgmString toString(const OSC2Waveform value)
{
    using Table = SparseLUT<PgmString, OSC2Waveform, OSC2Waveform::NOFENTRIES>;

    constexpr static const PROGMEM Table table
    (
    ""_pgm,
    Table::Entry(OSC2Waveform::NOISE, "NOISE"_pgm),
    Table::Entry(OSC2Waveform::SQR, "SQR"_pgm),
    Table::Entry(OSC2Waveform::SAW, "SAW"_pgm),
    Table::Entry(OSC2Waveform::TRI, "TRI"_pgm)
    );

    return table.getP(value);
}

inline PgmString toString(const OSCLFO1EnvDest value)
{
    using Table = SparseLUT<PgmString, OSCLFO1EnvDest, OSCLFO1EnvDest::NOFENTRIES>;

    constexpr static const PROGMEM Table table
    (
    ""_pgm,
    Table::Entry(OSCLFO1EnvDest::OSC1_2, "OSC 1&2"_pgm),
    Table::Entry(OSCLFO1EnvDest::OSC2, "OSC 2"_pgm),
    Table::Entry(OSCLFO1EnvDest::X_MOD, "X-MOD"_pgm)
    );

    return table.getP(value);
}

inline PgmString toString(const FilterType value)
{
    using Table = SparseLUT<PgmString, FilterType, FilterType::NOFENTRIES>;

    constexpr static const PROGMEM Table table
    (
    ""_pgm,
    Table::Entry(FilterType::HPF, "HPF"_pgm),
    Table::Entry(FilterType::BPF, "BPF"_pgm),
    Table::Entry(FilterType::LPF, "LPF"_pgm)
    );

    return table.getP(value);
}

inline PgmString toString(const FilterSlope value)
{
    using Table = SparseLUT<PgmString, FilterSlope, FilterSlope::NOFENTRIES>;

    constexpr static const PROGMEM Table table
    (
    ""_pgm,
    Table::Entry(FilterSlope::_12DB, "12 DB"_pgm),
    Table::Entry(FilterSlope::_24DB, "24 DB"_pgm)
    );

    return table.getP(value);
}

inline PgmString toString(const AmpPan value)
{
    using Table = SparseLUT<PgmString, AmpPan, AmpPan::NOFENTRIES>;

    constexpr static const PROGMEM Table table
    (
    ""_pgm,
    Table::Entry(AmpPan::OFF, "OFF"_pgm),
    Table::Entry(AmpPan::AUTO, "AUTO"_pgm),
    Table::Entry(AmpPan::MANUAL, "MANUAL"_pgm)
    );

    return table.getP(value);
}

inline PgmString toString(const Range_127_100_50 value)
{
    using Table = SparseLUT<PgmString, Range_127_100_50, Range_127_100_50::NOFENTRIES>;

    constexpr static const PROGMEM Table table
    (
    ""_pgm,
    Table::Entry(Range_127_100_50::_127, "-127 - +127"_pgm),
    Table::Entry(Range_127_100_50::_100, "-100 - +100"_pgm),
    Table::Entry(Range_127_100_50::_50, "-50 - +50"_pgm)
    );

    return table.getP(value);
}

inline PgmString toString(const PartSelect value)
{
    using Table = SparseLUT<PgmString, PartSelect, PartSelect::NOFENTRIES>;

    constexpr static const PROGMEM Table table
    (
    ""_pgm,
    Table::Entry(PartSelect::LOWER, "LOWER"_pgm),
    Table::Entry(PartSelect::UPPER, "UPPER"_pgm),
    Table::Entry(PartSelect::LOWER_UPPER, "LOWER & UPPER"_pgm),
    Table::Entry(PartSelect::VOICE_MOD, "VOICE MOD"_pgm)
    );

    return table.getP(value);
}

inline PgmString toString(const KeyMode value)
{
    using Table = SparseLUT<PgmString, KeyMode, KeyMode::NOFENTRIES>;

    constexpr static const PROGMEM Table table
    (
    ""_pgm,
    Table::Entry(KeyMode::SINGLE, "SINGLE"_pgm),
    Table::Entry(KeyMode::DUAL, "DUAL"_pgm),
    Table::Entry(KeyMode::SPLIT, "SPLIT"_pgm)
    );

    return table.getP(value);
}

inline PgmString toString(const OutputAssign value)
{
    using Table = SparseLUT<PgmString, OutputAssign, OutputAssign::NOFENTRIES>;

    constexpr static const PROGMEM Table table
    (
    ""_pgm,
    Table::Entry(OutputAssign::MIX_OUT, "MIX OUT"_pgm),
    Table::Entry(OutputAssign::PARALLEL_OUT, "PARALLEL OUT"_pgm)
    );

    return table.getP(value);
}

inline PgmString toString(const VoiceAssign value)
{
    using Table = SparseLUT<PgmString, VoiceAssign, VoiceAssign::NOFENTRIES>;

    constexpr static const PROGMEM Table table
    (
    ""_pgm,
    Table::Entry(VoiceAssign::_8_2, "8-2"_pgm),
    Table::Entry(VoiceAssign::_7_3, "7-3"_pgm),
    Table::Entry(VoiceAssign::_6_4, "6-4"_pgm),
    Table::Entry(VoiceAssign::_5_5, "5-5"_pgm),
    Table::Entry(VoiceAssign::_4_6, "4-6"_pgm),
    Table::Entry(VoiceAssign::_3_7, "3-7"_pgm),
    Table::Entry(VoiceAssign::_2_8, "2-8"_pgm)
    );

    return table.getP(value);
}

inline PgmString toString(const ArpDestination value)
{
    using Table = SparseLUT<PgmString, ArpDestination, ArpDestination::NOFENTRIES>;

    constexpr static const PROGMEM Table table
    (
    ""_pgm,
    Table::Entry(ArpDestination::LOWER_UPPER, "LOWER & UPPER"_pgm),
    Table::Entry(ArpDestination::LOWER, "LOWER"_pgm),
    Table::Entry(ArpDestination::UPPER, "UPPER"_pgm)
    );

    return table.getP(value);
}

inline PgmString toString(const ArpMode value)
{
    using Table = SparseLUT<PgmString, ArpMode, ArpMode::NOFENTRIES>;

    constexpr static const PROGMEM Table table
    (
    ""_pgm,
    Table::Entry(ArpMode::UP, "UP"_pgm),
    Table::Entry(ArpMode::DOWN, "DOWN"_pgm),
    Table::Entry(ArpMode::UP_DOWN, "UP & DOWN"_pgm),
    Table::Entry(ArpMode::RANDOM, "RANDOM"_pgm),
    Table::Entry(ArpMode::RPS, "RPS"_pgm)
    );

    return table.getP(value);
}

inline PgmString toString(const ArpBeatPattern value)
{
    using Table = SparseLUT<PgmString, ArpBeatPattern, ArpBeatPattern::NOFENTRIES>;

    constexpr static const PROGMEM Table table
    (
    ""_pgm,
    Table::Entry(ArpBeatPattern::_1_4, "1/4"_pgm),
    Table::Entry(ArpBeatPattern::_1_6, "1/6"_pgm),
    Table::Entry(ArpBeatPattern::_1_8, "1/8"_pgm),
    Table::Entry(ArpBeatPattern::_1_12, "1/12"_pgm),
    Table::Entry(ArpBeatPattern::_1_16, "1/16"_pgm),
    Table::Entry(ArpBeatPattern::_1_32, "1/32"_pgm)
    );

    return table.getP(value);
}


inline PgmString toString(const TrigDestination value)
{
    using Table = SparseLUT<PgmString, TrigDestination, TrigDestination::NOFENTRIES>;

    constexpr static const PROGMEM Table table
    (
    ""_pgm,
    Table::Entry(TrigDestination::FILTER_AMP, "FILTER & AMP"_pgm),
    Table::Entry(TrigDestination::FILTER, "FILTER"_pgm),
    Table::Entry(TrigDestination::AMP, "AMP"_pgm)
    );

    return table.getP(value);
}

// Voice Mod Bank[2]

// Algorithm
inline PgmString toString(const Algorithm value)
{
    using Table = SparseLUT<PgmString, Algorithm, Algorithm::NOFENTRIES>;

    constexpr static const PROGMEM Table table
    (
    ""_pgm,
    Table::Entry(Algorithm::SOLID, "SOLID"_pgm),
    Table::Entry(Algorithm::SMOOTH, "SMOOTH"_pgm),
    Table::Entry(Algorithm::WIDE, "WIDE"_pgm),
    Table::Entry(Algorithm::FILTER_BANK_WIDE, "FLT BANK WIDE"_pgm),
    Table::Entry(Algorithm::FILTER_BANK_NARROW, "FLT BANK NARROW"_pgm)
    );

    return table.getP(value);
}

// Control Assign
inline PgmString toString(const ControlAssign value)
{
    using Table = SparseLUT<PgmString, ControlAssign, ControlAssign::NOFENTRIES>;

    constexpr static const PROGMEM Table table
    (
    ""_pgm,
    Table::Entry(ControlAssign::ENSEMBLE_LEVEL, "ENSEMBLE LEVEL"_pgm),
    Table::Entry(ControlAssign::VOCAL_DELAY_TIME, "V DELAY TIME"_pgm),
    Table::Entry(ControlAssign::VOCAL_DELAY_FEEDBACK, "V DELAY FEEDBCK"_pgm),
    Table::Entry(ControlAssign::VOCAL_DELAY_LEVEL, "V DELAY LEVEL"_pgm),
    Table::Entry(ControlAssign::VOCAL_MIX, "VOCAL MIX"_pgm),
    Table::Entry(ControlAssign::VOCAL_RESONANCE, "V RESONANCE"_pgm),
    Table::Entry(ControlAssign::VOCAL_RELEASE, "V RELEASE"_pgm),
    Table::Entry(ControlAssign::VOCAL_PAN, "V PAN"_pgm),
    Table::Entry(ControlAssign::VOCAL_LEVEL, "V LEVEL"_pgm),
    Table::Entry(ControlAssign::VOCAL_NOISE_CUTOFF, "V NOISE CUTOFF"_pgm),
    Table::Entry(ControlAssign::VOCAL_NOISE_LEVEL, "V NOISE LEVEL"_pgm),
    Table::Entry(ControlAssign::GATE_THRESHOLD, "GATE THRESHOLD"_pgm),
    Table::Entry(ControlAssign::ROBOT_PITCH, "ROBOT PITCH"_pgm),
    Table::Entry(ControlAssign::ROBOT_CONTROL, "ROBOT CONTROL"_pgm),
    Table::Entry(ControlAssign::ROBOT_LEVEL, "ROBOT LEVEL"_pgm),
    Table::Entry(ControlAssign::CHARACTER_1, "CHARACTER 1"_pgm),
    Table::Entry(ControlAssign::CHARACTER_2, "CHARACTER 2"_pgm),
    Table::Entry(ControlAssign::CHARACTER_3, "CHARACTER 3"_pgm),
    Table::Entry(ControlAssign::CHARACTER_4, "CHARACTER 4"_pgm),
    Table::Entry(ControlAssign::CHARACTER_5, "CHARACTER 5"_pgm),
    Table::Entry(ControlAssign::CHARACTER_6, "CHARACTER 6"_pgm),
    Table::Entry(ControlAssign::CHARACTER_7, "CHARACTER 7"_pgm),
    Table::Entry(ControlAssign::CHARACTER_8, "CHARACTER 8"_pgm),
    Table::Entry(ControlAssign::CHARACTER_9, "CHARACTER 9"_pgm),
    Table::Entry(ControlAssign::CHARACTER_10, "CHARACTER 10"_pgm),
    Table::Entry(ControlAssign::CHARACTER_11, "CHARACTER 11"_pgm),
    Table::Entry(ControlAssign::CHARACTER_12, "CHARACTER 12"_pgm)
    );

    return table.getP(value);
}

// Delay type
inline PgmString toString(const DelayType value)
{
    using Table = SparseLUT<PgmString, DelayType, DelayType::NOFENTRIES>;

    constexpr static const PROGMEM Table table
    (
    ""_pgm,
    Table::Entry(DelayType::PANNING_L_R, "PANNING L->R"_pgm),
    Table::Entry(DelayType::PANNING_R_L, "PANNING R->L"_pgm),
    Table::Entry(DelayType::PANNING_SHORT, "PANNING SHORT"_pgm),
    Table::Entry(DelayType::MONO_SHORT, "MONO SHORT"_pgm),
    Table::Entry(DelayType::MONO_LONG, "MONO LONG"_pgm)
    );

    return table.getP(value);
}

// Delay sync
inline PgmString toString(const DelaySync value)
{
    using Table = SparseLUT<PgmString, DelaySync, DelaySync::NOFENTRIES>;

    constexpr static const PROGMEM Table table
    (
    ""_pgm,
    Table::Entry(DelaySync::OFF, "OFF"_pgm),
    Table::Entry(DelaySync::_1_16, "1/16"_pgm),
    Table::Entry(DelaySync::_1_8_3, "1/8 (3.)"_pgm),
    Table::Entry(DelaySync::_1_16_1, "1/16 (.)"_pgm),
    Table::Entry(DelaySync::_1_8, "1/8"_pgm),
    Table::Entry(DelaySync::_1_4_3, "1/4 (3.)"_pgm),
    Table::Entry(DelaySync::_1_8_1, "1/8 (.)"_pgm),
    Table::Entry(DelaySync::_1_4, "1/4"_pgm),
    Table::Entry(DelaySync::_1_2_3, "1/2 (3.)"_pgm),
    Table::Entry(DelaySync::_1_4_1, "1/4 (.)"_pgm),
    Table::Entry(DelaySync::_1_2, "1/2"_pgm)
    );

    return table.getP(value);
}

// Ensemble type
inline PgmString toString(const EnsembleType value)
{
    using Table = SparseLUT<PgmString, EnsembleType, EnsembleType::NOFENTRIES>;

    constexpr static const PROGMEM Table table
    (
    ""_pgm,
    Table::Entry(EnsembleType::ENSEMBLE_MILD, "ENSEMBLE MILD"_pgm),
    Table::Entry(EnsembleType::ENSEMBLE_CLEAN, "ENSEMBLE_CLEAN"_pgm),
    Table::Entry(EnsembleType::ENSEMBLE_FAST, "ENSEMBLE FAST"_pgm),
    Table::Entry(EnsembleType::SUPER_CHORUS_SLOW, "SUPER CHORUS SLW"_pgm),
    Table::Entry(EnsembleType::SUPER_CHORUS_MID, "SUPER CHORUS MID"_pgm),
    Table::Entry(EnsembleType::SUPER_CHORUS_FAST, "SUPER CHORUS FST"_pgm),
    Table::Entry(EnsembleType::SUPER_CHORUS_CLEAR, "SUPER CHORUS CLR"_pgm),
    Table::Entry(EnsembleType::FLANGER_SLOW, "FLANGER SLOW"_pgm),
    Table::Entry(EnsembleType::FLANGER_DEEP, "FLANGER DEEP"_pgm),
    Table::Entry(EnsembleType::FLANGER_FAST, "FLANGER FAST"_pgm),
    Table::Entry(EnsembleType::DEEP_PHASING_SLOW, "DEEP PHASING SLW"_pgm),
    Table::Entry(EnsembleType::JET_PHASING, "JET PHASING"_pgm),
    Table::Entry(EnsembleType::TWISTING, "TWISTING"_pgm),
    Table::Entry(EnsembleType::FREEZE_PHASE_1_2, "FREEZE PHASE 1/2"_pgm)
    );

    return table.getP(value);
}

// Ensemble sync
inline PgmString toString(const EnsembleSync value)
{
    using Table = SparseLUT<PgmString, EnsembleSync, EnsembleSync::NOFENTRIES>;

    constexpr static const PROGMEM Table table
    (
    ""_pgm,
    Table::Entry(EnsembleSync::OFF, "OFF"_pgm),
    Table::Entry(EnsembleSync::_1_16, "1/16"_pgm),
    Table::Entry(EnsembleSync::_1_8_3, "1/8 (3.)"_pgm),
    Table::Entry(EnsembleSync::_1_16_1, "1/16 (.)"_pgm),
    Table::Entry(EnsembleSync::_1_8, "1/8"_pgm),
    Table::Entry(EnsembleSync::_1_4_3, "1/4 (3.)"_pgm),
    Table::Entry(EnsembleSync::_1_8_1, "1/8 (.)"_pgm),
    Table::Entry(EnsembleSync::_1_4, "1/4"_pgm),
    Table::Entry(EnsembleSync::_1_2_3, "1/2 (3.)"_pgm),
    Table::Entry(EnsembleSync::_1_4_1, "1/4 (.)"_pgm),
    Table::Entry(EnsembleSync::_1_2, "1/2"_pgm),
    Table::Entry(EnsembleSync::_1_1_3, "1/1 (3.)"_pgm),
    Table::Entry(EnsembleSync::_1_2_1, "1/2 (.)"_pgm),
    Table::Entry(EnsembleSync::_1_1, "1/1"_pgm),
    Table::Entry(EnsembleSync::_2_1_3, "2/1 (3.)"_pgm),
    Table::Entry(EnsembleSync::_1_1_1, "1/1 (.)"_pgm),
    Table::Entry(EnsembleSync::_2_1, "2/1"_pgm),
    Table::Entry(EnsembleSync::_3_MEASURES, "3 MEASURES"_pgm),
    Table::Entry(EnsembleSync::_4_MEASURES, "4 MEASURES"_pgm),
    Table::Entry(EnsembleSync::_5_MEASURES, "5 MEASURES"_pgm),
    Table::Entry(EnsembleSync::_6_MEASURES, "6 MEASURES"_pgm),
    Table::Entry(EnsembleSync::_7_MEASURES, "7 MEASURES"_pgm),
    Table::Entry(EnsembleSync::_8_MEASURES, "8 MEASURES"_pgm)
    );

    return table.getP(value);
}

// Delay sync
inline PgmString toString(const PartMidiChannel value)
{
    using Table = SparseLUT<PgmString, PartMidiChannel, PartMidiChannel::NOFENTRIES>;

    constexpr static const PROGMEM Table table
    (
    ""_pgm,
    Table::Entry(PartMidiChannel::OFF, "OFF"_pgm),
    Table::Entry(PartMidiChannel::_1, "1"_pgm),
    Table::Entry(PartMidiChannel::_2, "2"_pgm),
    Table::Entry(PartMidiChannel::_3, "3"_pgm),
    Table::Entry(PartMidiChannel::_4, "4"_pgm),
    Table::Entry(PartMidiChannel::_5, "5"_pgm),
    Table::Entry(PartMidiChannel::_6, "6"_pgm),
    Table::Entry(PartMidiChannel::_7, "7"_pgm),
    Table::Entry(PartMidiChannel::_8, "8"_pgm),
    Table::Entry(PartMidiChannel::_9, "9"_pgm),
    Table::Entry(PartMidiChannel::_10, "10"_pgm),
    Table::Entry(PartMidiChannel::_11, "11"_pgm),
    Table::Entry(PartMidiChannel::_12, "12"_pgm),
    Table::Entry(PartMidiChannel::_13, "13"_pgm),
    Table::Entry(PartMidiChannel::_14, "14"_pgm),
    Table::Entry(PartMidiChannel::_15, "15"_pgm),
    Table::Entry(PartMidiChannel::_16, "16"_pgm)
    );

    return table.getP(value);
}

// Chorus sync
inline PgmString toString(const ChorusSync value)
{
    using Table = SparseLUT<PgmString, ChorusSync, ChorusSync::NOFENTRIES>;

    constexpr static const PROGMEM Table table
    (
    ""_pgm,
    Table::Entry(ChorusSync::OFF, "OFF"_pgm),
    Table::Entry(ChorusSync::_1_16, "1/16"_pgm),
    Table::Entry(ChorusSync::_1_8_3, "1/8 (3.)"_pgm),
    Table::Entry(ChorusSync::_1_16_1, "1/16 (.)"_pgm),
    Table::Entry(ChorusSync::_1_8, "1/8"_pgm),
    Table::Entry(ChorusSync::_1_4_3, "1/4 (3.)"_pgm),
    Table::Entry(ChorusSync::_1_8_1, "1/8 (.)"_pgm),
    Table::Entry(ChorusSync::_1_4, "1/4"_pgm),
    Table::Entry(ChorusSync::_1_2_3, "1/2 (3.)"_pgm),
    Table::Entry(ChorusSync::_1_4_1, "1/4 (.)"_pgm),
    Table::Entry(ChorusSync::_1_2, "1/2"_pgm),
    Table::Entry(ChorusSync::_1_1_3, "1/1 (3.)"_pgm),
    Table::Entry(ChorusSync::_1_2_1, "1/2 (.)"_pgm),
    Table::Entry(ChorusSync::_1_1, "1/1"_pgm),
    Table::Entry(ChorusSync::_2_1_3, "2/1 (3.)"_pgm),
    Table::Entry(ChorusSync::_1_1_1, "1/1 (.)"_pgm),
    Table::Entry(ChorusSync::_2_1, "2/1"_pgm),
    Table::Entry(ChorusSync::_3_MEASURES, "3 MEASURES"_pgm),
    Table::Entry(ChorusSync::_4_MEASURES, "4 MEASURES"_pgm),
    Table::Entry(ChorusSync::_5_MEASURES, "5 MEASURES"_pgm),
    Table::Entry(ChorusSync::_6_MEASURES, "6 MEASURES"_pgm),
    Table::Entry(ChorusSync::_7_MEASURES, "7 MEASURES"_pgm),
    Table::Entry(ChorusSync::_8_MEASURES, "8 MEASURES"_pgm),
    Table::Entry(ChorusSync::LFO1, "LFO1"_pgm)
    );

    return table.getP(value);
}

// Mulit-FX type
inline PgmString toString(const MultiFXType value)
{
    using Table = SparseLUT<PgmString, MultiFXType, MultiFXType::NOFENTRIES>;

    constexpr static const PROGMEM Table table
    (
    ""_pgm,
    Table::Entry(MultiFXType::SUPER_CHORUS_SLOW, "SUPER CHORUS SLW"_pgm),
    Table::Entry(MultiFXType::SUPER_CHORUS_MID, "SUPER CHORUS MID"_pgm),
    Table::Entry(MultiFXType::SUPER_CHORUS_FAST, "SUPER CHORUS FST"_pgm),
    Table::Entry(MultiFXType::SUPER_CHORUS_CLEAR, "SUPER CHORUS CLR"_pgm),
    Table::Entry(MultiFXType::FLANGER_SLOW, "FLANGER SLOW"_pgm),
    Table::Entry(MultiFXType::FLANGER_DEEP, "FLANGER DEEP"_pgm),
    Table::Entry(MultiFXType::FLANGER_FAST, "FLANGER FAST"_pgm),
    Table::Entry(MultiFXType::DEEP_PHASING_SLOW, "DEEP PHASING SLW"_pgm),
    Table::Entry(MultiFXType::JET_PHASING, "JET PHASING"_pgm),
    Table::Entry(MultiFXType::TWISTING, "TWISTING"_pgm),
    Table::Entry(MultiFXType::FREEZE_PHASE_1_2, "FREEZE PHASE 1/2"_pgm),
    Table::Entry(MultiFXType::DISTORTION, "DISTORTION"_pgm)
    );

    return table.getP(value);
}

// Envelope Type in Solo
inline PgmString toString(const EnvTypeSolo value)
{
    using Table = SparseLUT<PgmString, EnvTypeSolo, EnvTypeSolo::NOFENTRIES>;

    constexpr static const PROGMEM Table table
    (
    ""_pgm,
    Table::Entry(EnvTypeSolo::STANDARD, "STANDARD"_pgm),
    Table::Entry(EnvTypeSolo::ANALOG, "ANALOG"_pgm)
    );

    return table.getP(value);
}

// Envelope Type in Solo
inline PgmString toString(const PatchGain value)
{
    using Table = SparseLUT<PgmString, PatchGain, PatchGain::NOFENTRIES>;

    constexpr static const PROGMEM Table table
    (
    ""_pgm,
    Table::Entry(PatchGain::_0DB, "0 DB"_pgm),
    Table::Entry(PatchGain::_6DB, "+6 DB"_pgm),
    Table::Entry(PatchGain::_12DB, "+12 DB"_pgm)
    );

    return table.getP(value);
}

// MIDI Sync
inline PgmString toString(const MidiSync value)
{
    using Table = SparseLUT<PgmString, MidiSync, MidiSync::NOFENTRIES>;

    constexpr static const PROGMEM Table table
    (
    ""_pgm,
    Table::Entry(MidiSync::OFF, "OFF"_pgm),
    Table::Entry(MidiSync::MIDI_IN, "MIDI IN"_pgm),
    Table::Entry(MidiSync::REMOTE_KBD_IN, "REMOTE KBD IN"_pgm)
    );

    return table.getP(value);
}

// Remote Keyboard Channel
inline PgmString toString(const RemoteKeyboardChannel value)
{
    using Table = SparseLUT<PgmString, RemoteKeyboardChannel, RemoteKeyboardChannel::NOFENTRIES>;

    constexpr static const PROGMEM Table table
    (
    ""_pgm,
    Table::Entry(RemoteKeyboardChannel::ALL, "ALL"_pgm),
    Table::Entry(RemoteKeyboardChannel::_1, "1"_pgm),
    Table::Entry(RemoteKeyboardChannel::_2, "2"_pgm),
    Table::Entry(RemoteKeyboardChannel::_3, "3"_pgm),
    Table::Entry(RemoteKeyboardChannel::_4, "4"_pgm),
    Table::Entry(RemoteKeyboardChannel::_5, "5"_pgm),
    Table::Entry(RemoteKeyboardChannel::_6, "6"_pgm),
    Table::Entry(RemoteKeyboardChannel::_7, "7"_pgm),
    Table::Entry(RemoteKeyboardChannel::_8, "8"_pgm),
    Table::Entry(RemoteKeyboardChannel::_9, "9"_pgm),
    Table::Entry(RemoteKeyboardChannel::_10, "10"_pgm),
    Table::Entry(RemoteKeyboardChannel::_11, "11"_pgm),
    Table::Entry(RemoteKeyboardChannel::_12, "12"_pgm),
    Table::Entry(RemoteKeyboardChannel::_13, "13"_pgm),
    Table::Entry(RemoteKeyboardChannel::_14, "14"_pgm),
    Table::Entry(RemoteKeyboardChannel::_15, "15"_pgm),
    Table::Entry(RemoteKeyboardChannel::_16, "16"_pgm)
    );

    return table.getP(value);
}

// MIDI Thru
inline PgmString toString(const MidiThru value)
{
    using Table = SparseLUT<PgmString, MidiThru, MidiThru::NOFENTRIES>;

    constexpr static const PROGMEM Table table
    (
    ""_pgm,
    Table::Entry(MidiThru::OFF, "OFF"_pgm),
    Table::Entry(MidiThru::ON_W_O_SYSEX, "ON (W/O SYSEX)"_pgm),
    Table::Entry(MidiThru::ON_ALL, "ON (ALL)"_pgm)
    );

    return table.getP(value);
}

// Tx/Rx Edit Mode
inline PgmString toString(const TxRxEditMode value)
{
    using Table = SparseLUT<PgmString, TxRxEditMode, TxRxEditMode::NOFENTRIES>;

    constexpr static const PROGMEM Table table
    (
    ""_pgm,
    Table::Entry(TxRxEditMode::MODE1, "MODE1"_pgm),
    Table::Entry(TxRxEditMode::MODE2, "MODE2"_pgm)
    );

    return table.getP(value);
}

// Tx/Rx Program Change
inline PgmString toString(const TxRxProgramChange value)
{
    using Table = SparseLUT<PgmString, TxRxProgramChange, TxRxProgramChange::NOFENTRIES>;

    constexpr static const PROGMEM Table table
    (
    ""_pgm,
    Table::Entry(TxRxProgramChange::OFF, "MOFFODE1"_pgm),
    Table::Entry(TxRxProgramChange::PC, "PC"_pgm),
    Table::Entry(TxRxProgramChange::BANK_SEL_PC, "BANK SEL + PC"_pgm)
    );

    return table.getP(value);
}

// Pattern Trigger Quantize
inline PgmString toString(const PatternTriggerQuantize value)
{
    using Table = SparseLUT<PgmString, PatternTriggerQuantize, PatternTriggerQuantize::NOFENTRIES>;

    constexpr static const PROGMEM Table table
    (
    ""_pgm,
    Table::Entry(PatternTriggerQuantize::OFF, "OFF"_pgm),
    Table::Entry(PatternTriggerQuantize::BEAT, "BEAT"_pgm),
    Table::Entry(PatternTriggerQuantize::MEASURE, "MEASURE"_pgm)
    );

    return table.getP(value);
}

// Midi Note
inline String<> toString(const MidiNote value)
{
    typedef SparseLUT<PgmString, uint8_t, 12> Table;
    constexpr static const PROGMEM Table table
    (
    ""_pgm,
    Table::Entry(0, "C"_pgm),
    Table::Entry(1, "C#"_pgm),
    Table::Entry(2, "D"_pgm),
    Table::Entry(3, "D#"_pgm),
    Table::Entry(4, "E"_pgm),
    Table::Entry(5, "F"_pgm),
    Table::Entry(6, "F#"_pgm),
    Table::Entry(7, "G"_pgm),
    Table::Entry(8, "G#"_pgm),
    Table::Entry(9, "A"_pgm),
    Table::Entry(10, "Bb"_pgm),
    Table::Entry(11, "B"_pgm)
    );
    
    // separate semitone and octave
    uint8_t octave = value;
    const uint8_t semiTone = mod<12>(octave);
    octave -= 1; // Lowest MIDI note is C-1
    
    String<> ret;
    StringStream<String<>>(ret) << table.getP(semiTone) << static_cast<int8_t>(octave);
    return ret;
}

// Individual Trigger Source Note
inline String<> toString(const IndivTrigSrcNote value)
{
    if (value == 128)
    {
        return "ALL";
    }        
    else
    {
        return toString(static_cast<MidiNote>(value));
    }        
}

#endif