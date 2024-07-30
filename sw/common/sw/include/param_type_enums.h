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

#ifndef PARAM_TYPE_ENUMS_H
#define PARAM_TYPE_ENUMS_H

#include "common_enum_def.h"

// LFO 1 Section

// LFO1 Waveform
DEFINE_ENUM(
LFO1Waveform,
TRI,
SAW,
SQR,
S_H)

// MODULATION (LFO 2) Section

// LFO2 Depth Select
DEFINE_ENUM(
LFO2DepthSelect,
PITCH,
FILTER,
AMP)

// OSC 1 Section

// OSC1 Waveform
DEFINE_ENUM(
OSC1Waveform,
SUPER_SAW,
TRIANGLE_MOD,
NOISE,
FEEDBACK_OSC,
SQR,
SAW,
TRI)

// OSC 2 Section

// OSC2 Waveform
DEFINE_ENUM(
OSC2Waveform,
SQR,
SAW,
TRI,
NOISE)

// OSC COMMON Section

// OSC LFO1 & Env Destination
DEFINE_ENUM(
OSCLFO1EnvDest,
OSC1_2,
OSC2,
X_MOD)

// FILTER Section

// Filter Type
DEFINE_ENUM(
FilterType,
HPF,
BPF,
LPF)

// Filter Slope
DEFINE_ENUM(
FilterSlope,
_12DB,
_24DB)

// AMP Section

// Amp Pan
DEFINE_ENUM(
AmpPan,
OFF,
AUTO,
MANUAL)

// CONTROL Section

// Range 127/100/50
DEFINE_ENUM(
Range_127_100_50,
_127,
_100,
_50)

// PANEL SELECT Section

// Part Select
DEFINE_ENUM(
PartSelect,
LOWER,
UPPER,
LOWER_UPPER,
VOICE_MOD)

// KEY MODE Section

// Key Mode Select
DEFINE_ENUM(
KeyMode,
SINGLE,
DUAL,
SPLIT)

// ARPEGGIATOR/RPS Section

// Arpeggiator Mode
DEFINE_ENUM(
ArpMode,
UP,
DOWN,
UP_DOWN,
RANDOM,
RPS)

// Output assign
DEFINE_ENUM(
OutputAssign,
MIX_OUT,
PARALLEL_OUT)

// Voice assign
DEFINE_ENUM(
VoiceAssign,
_8_2,
_7_3,
_6_4,
_5_5,
_4_6,
_3_7,
_2_8)

// Arpeggio destimation
DEFINE_ENUM(
ArpDestination,
LOWER_UPPER,
LOWER,
UPPER)

// Arpeggio beat pattern
DEFINE_ENUM(
ArpBeatPattern,
_1_4,
_1_6,
_1_8,
_1_12,
_1_16,
_1_32)

// Trigger destination
DEFINE_ENUM(
TrigDestination,
FILTER,
AMP,
FILTER_AMP)

// Voice Mod Bank[2]

// Algorithm
DEFINE_ENUM(
Algorithm,
SOLID,
SMOOTH,
WIDE,
FILTER_BANK_WIDE,
FILTER_BANK_NARROW)

// Control Assign
DEFINE_ENUM(
ControlAssign,
ENSEMBLE_LEVEL,
VOCAL_DELAY_TIME,
VOCAL_DELAY_FEEDBACK,
VOCAL_DELAY_LEVEL,
VOCAL_MIX,
VOCAL_RESONANCE,
VOCAL_RELEASE,
VOCAL_PAN,
VOCAL_LEVEL,
VOCAL_NOISE_CUTOFF,
VOCAL_NOISE_LEVEL,
GATE_THRESHOLD,
ROBOT_PITCH,
ROBOT_CONTROL,
ROBOT_LEVEL,
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

// Delay type
DEFINE_ENUM(
DelayType,
PANNING_L_R,
PANNING_R_L,
PANNING_SHORT,
MONO_SHORT,
MONO_LONG)

// Delay sync
DEFINE_ENUM(
DelaySync,
OFF,
_1_16,
_1_8_3,
_1_16_1,
_1_8,
_1_4_3,
_1_8_1,
_1_4,
_1_2_3,
_1_4_1,
_1_2)

// Ensemble type
DEFINE_ENUM(
EnsembleType,
ENSEMBLE_MILD,
ENSEMBLE_CLEAN,
ENSEMBLE_FAST,
SUPER_CHORUS_SLOW,
SUPER_CHORUS_MID,
SUPER_CHORUS_FAST,
SUPER_CHORUS_CLEAR,
FLANGER_SLOW,
FLANGER_DEEP,
FLANGER_FAST,
DEEP_PHASING_SLOW,
JET_PHASING,
TWISTING,
FREEZE_PHASE_1_2)

// Ensemble sync
DEFINE_ENUM(
EnsembleSync,
OFF,
_1_16,
_1_8_3,
_1_16_1,
_1_8,
_1_4_3,
_1_8_1,
_1_4,
_1_2_3,
_1_4_1,
_1_2,
_1_1_3,
_1_2_1,
_1_1,
_2_1_3,
_1_1_1,
_2_1,
_3_MEASURES,
_4_MEASURES,
_5_MEASURES,
_6_MEASURES,
_7_MEASURES,
_8_MEASURES)

// Performance Part Bank[3]

// Part MIDI Channel
DEFINE_ENUM(
PartMidiChannel,
OFF,
_1,
_2,
_3,
_4,
_5,
_6,
_7,
_8,
_9,
_10,
_11,
_12,
_13,
_14,
_15,
_16)

// Chorus sync
DEFINE_ENUM(
ChorusSync,
OFF,
_1_16,
_1_8_3,
_1_16_1,
_1_8,
_1_4_3,
_1_8_1,
_1_4,
_1_2_3,
_1_4_1,
_1_2,
_1_1_3,
_1_2_1,
_1_1,
_2_1_3,
_1_1_1,
_2_1,
_3_MEASURES,
_4_MEASURES,
_5_MEASURES,
_6_MEASURES,
_7_MEASURES,
_8_MEASURES,
LFO1)

// PATCH (Bank 4)

// Multi-FX type
DEFINE_ENUM(
MultiFXType,
SUPER_CHORUS_SLOW,
SUPER_CHORUS_MID,
SUPER_CHORUS_FAST,
SUPER_CHORUS_CLEAR,
FLANGER_SLOW,
FLANGER_DEEP,
FLANGER_FAST,
DEEP_PHASING_SLOW,
JET_PHASING,
TWISTING,
FREEZE_PHASE_1_2,
DISTORTION)

DEFINE_ENUM(
EnvTypeSolo,
STANDARD,
ANALOG)

DEFINE_ENUM(
PatchGain,
_0DB,
_6DB,
_12DB)

// MIDI (Bank 5)

// MIDI Sync
DEFINE_ENUM(
MidiSync,
OFF,
MIDI_IN,
REMOTE_KBD_IN)

// Remote Keyboard Channel
DEFINE_ENUM(
RemoteKeyboardChannel,
ALL,
_1,
_2,
_3,
_4,
_5,
_6,
_7,
_8,
_9,
_10,
_11,
_12,
_13,
_14,
_15,
_16)

// Remote Keyboard Channel
DEFINE_ENUM(
MidiThru,
OFF,
ON_W_O_SYSEX,
ON_ALL)

// Tx/Rx Edit Mode
DEFINE_ENUM(
TxRxEditMode,
MODE1,
MODE2)

// Tx/Rx Program Change
DEFINE_ENUM(
TxRxProgramChange,
OFF,
PC,
BANK_SEL_PC)

// Pattern Trigger Quantize
DEFINE_ENUM(
PatternTriggerQuantize,
OFF,
BEAT,
MEASURE)


#endif