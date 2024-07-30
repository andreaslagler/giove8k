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

#ifndef PATCH_PARAM_ENUMS_H
#define PATCH_PARAM_ENUMS_H

#if __cplusplus

#include <stdint.h>
#include <numeric_limits.h>
#include <pgm_string.h>
#include <lookup_table.h>

#endif

#include "common_enum_def.h"

DEFINE_ENUM(
PatchParam,

// Effects section
TONE_CONTROL_BASS,
TONE_CONTROL_TREBLE,
MULTI_FX_LEVEL,
DELAY_TIME,
DELAY_FEEDBACK,
DELAY_LEVEL,
VOICE_MOD_SEND,

// LFO 1 section
LFO1_WAVEFORM,
LFO1_RATE,
LFO1_FADE,

// Modulation (LFO2 section
LFO2_RATE,
LFO2_DEPTH_SELECT,
LFO2_DEPTH_PITCH,
LFO2_DEPTH_FILTER,
LFO2_DEPTH_AMP,

// Portamento section
PORTAMENTO_ON,
PORTAMENTO_TIME,

// Osc 1 section
OSC1_WAVEFORM,
OSC1_CONTROL1,
OSC1_CONTROL2,

// Osc 2 section
OSC2_WAVEFORM,
OSC2_EXT,
OSC2_SYNC,
OSC2_RANGE,
OSC2_FINE_WIDE,
OSC2_CONTROL1,
OSC2_CONTROL2,
OSC2_RING,

// Osc common section
OSC_BALANCE,
OSC_XMOD_DEPTH,
OSC_LFO1_ENV_DESTINATION,
OSC_LFO1_DEPTH,
OSC_SHIFT,

// Pitch envelope section
PITCH_ENVELOPE_DEPTH,
PITCH_ENVELOPE_A,
PITCH_ENVELOPE_D,

// Filter section
FILTER_TYPE,
FILTER_12DB_24DB,
FILTER_CUTOFF_FREQ,
FILTER_RESONANCE,
FILTER_KEY_FOLLOW,
FILTER_LFO1_DEPTH,

// Filter envelope section
FILTER_ENVELOPE_DEPTH,
FILTER_ENVELOPE_A,
FILTER_ENVELOPE_D,
FILTER_ENVELOPE_S,
FILTER_ENVELOPE_R,

// Amp section
AMP_LEVEL,
AMP_PAN,
AMP_LFO1_DEPTH,

// Amp envelope section
AMP_ENVELOPE_A,
AMP_ENVELOPE_D,
AMP_ENVELOPE_S,
AMP_ENVELOPE_R,

// Control section
MONO,
LEGATO,
UNSON,
VELOCITY,
VELOCITY_ASSIGN,
CONTROL_ASSIGN,

// Patch parameters (Bank[4])
PATCH_NAME,
MULTI_FX_TYPE,
DELAY_TYPE,
BEND_RANGE_UP,
BEND_RANGE_DOWN,
MORPH_BEND_ASSIGN,
UNISON_DETUNE,
ENV_TYPE_SOLO,
PATCH_GAIN,
EXT_TRIG_SWITCH,
EXT_TRIG_DEST)


#if __cplusplus

inline PgmString toString(const PatchParam param)
{
    using Table = SparseLUT<PgmString, PatchParam, PatchParam::NOFENTRIES>;

    constexpr static const PROGMEM Table table
    (
    ""_pgm,
    
    // Effects section
    Table::Entry(PatchParam::TONE_CONTROL_BASS, "Bass"_pgm),
    Table::Entry(PatchParam::TONE_CONTROL_TREBLE, "Treble"_pgm),
    Table::Entry(PatchParam::MULTI_FX_LEVEL, "Multi-FX Level"_pgm),
    Table::Entry(PatchParam::DELAY_TIME, "Delay Time"_pgm),
    Table::Entry(PatchParam::DELAY_FEEDBACK, "Delay Feedback"_pgm),
    Table::Entry(PatchParam::DELAY_LEVEL, "Delay Level"_pgm),
    Table::Entry(PatchParam::VOICE_MOD_SEND, "Voice Mod Send"_pgm),
    
    // LFO 1 section
    Table::Entry(PatchParam::LFO1_WAVEFORM, "LFO1 Waveform"_pgm),
    Table::Entry(PatchParam::LFO1_RATE, "LFO1 Rate"_pgm),
    Table::Entry(PatchParam::LFO1_FADE, "LFO1 Fade"_pgm),
    
    // Modulation (LFO2) section
    Table::Entry(PatchParam::LFO2_RATE, "LFO2 Rate"_pgm),
    Table::Entry(PatchParam::LFO2_DEPTH_SELECT, "LFO2 Depth Select"_pgm),
    Table::Entry(PatchParam::LFO2_DEPTH_PITCH, "LFO2 Depth Pitch"_pgm),
    Table::Entry(PatchParam::LFO2_DEPTH_FILTER, "LFO2 Depth Filter"_pgm),
    Table::Entry(PatchParam::LFO2_DEPTH_AMP, "LFO2 Depth Amp"_pgm),
    
    // Portamento section
    Table::Entry(PatchParam::PORTAMENTO_ON, "Portamento"_pgm),
    Table::Entry(PatchParam::PORTAMENTO_TIME, "Portamento Time"_pgm),

    // Osc 1 section
    Table::Entry(PatchParam::OSC1_WAVEFORM, "OSC1 Waveform"_pgm),
    Table::Entry(PatchParam::OSC1_CONTROL1, "OSC1 Control1"_pgm),
    Table::Entry(PatchParam::OSC1_CONTROL2, "OSC1 Control2"_pgm),

    // Osc 2 section
    Table::Entry(PatchParam::OSC2_WAVEFORM, "OSC2 Waveform"_pgm),
    Table::Entry(PatchParam::OSC2_EXT, "OSC2 Ext"_pgm),
    Table::Entry(PatchParam::OSC2_SYNC, "OSC2 Sync"_pgm),
    Table::Entry(PatchParam::OSC2_RANGE, "OSC2 Range"_pgm),
    Table::Entry(PatchParam::OSC2_FINE_WIDE, "OSC2 Fine/Wide"_pgm),
    Table::Entry(PatchParam::OSC2_CONTROL1, "OSC2 Control1"_pgm),
    Table::Entry(PatchParam::OSC2_CONTROL2, "OSC2 Control2"_pgm),
    Table::Entry(PatchParam::OSC2_RING, "OSC2 Ring"_pgm),

    // Osc common section
    Table::Entry(PatchParam::OSC_BALANCE, "OSC Balance"_pgm),
    Table::Entry(PatchParam::OSC_XMOD_DEPTH, "OSC X-Mod Depth"_pgm),
    Table::Entry(PatchParam::OSC_LFO1_ENV_DESTINATION, "OSC LFO1 Env Dest"_pgm),
    Table::Entry(PatchParam::OSC_LFO1_DEPTH, "OSC LFO1 Depth"_pgm),
    Table::Entry(PatchParam::OSC_SHIFT, "OSC Shift"_pgm),
    
    // Pitch envelope section
    Table::Entry(PatchParam::PITCH_ENVELOPE_DEPTH, "Pitch Env Depth"_pgm),
    Table::Entry(PatchParam::PITCH_ENVELOPE_A, "Pitch Env A"_pgm),
    Table::Entry(PatchParam::PITCH_ENVELOPE_D, "Pitch Env D"_pgm),

    // Filter section
    Table::Entry(PatchParam::FILTER_TYPE, "Filter Type"_pgm),
    Table::Entry(PatchParam::FILTER_12DB_24DB, "Filter Slope"_pgm),
    Table::Entry(PatchParam::FILTER_CUTOFF_FREQ, "Filter Cutoff"_pgm),
    Table::Entry(PatchParam::FILTER_RESONANCE, "Filter Resonance"_pgm),
    Table::Entry(PatchParam::FILTER_KEY_FOLLOW, "Filt Key Follow"_pgm),
    Table::Entry(PatchParam::FILTER_LFO1_DEPTH, "Filt LFO1 Depth"_pgm),
    
    // Filter envelope section
    Table::Entry(PatchParam::FILTER_ENVELOPE_DEPTH, "Filter Env Depth"_pgm),
    Table::Entry(PatchParam::FILTER_ENVELOPE_A, "Filter Env A"_pgm),
    Table::Entry(PatchParam::FILTER_ENVELOPE_D, "Filter Env D"_pgm),
    Table::Entry(PatchParam::FILTER_ENVELOPE_S, "Filter Env S"_pgm),
    Table::Entry(PatchParam::FILTER_ENVELOPE_R, "Filter Env R"_pgm),
    
    // Amp section
    Table::Entry(PatchParam::AMP_LEVEL, "Amp Level"_pgm),
    Table::Entry(PatchParam::AMP_PAN, "Amp Pan"_pgm),
    Table::Entry(PatchParam::AMP_LFO1_DEPTH, "Amp LFO1 Depth"_pgm),
    
    // Amp envelope section
    Table::Entry(PatchParam::AMP_ENVELOPE_A, "Amp Env A"_pgm),
    Table::Entry(PatchParam::AMP_ENVELOPE_D, "Amp Env D"_pgm),
    Table::Entry(PatchParam::AMP_ENVELOPE_S, "Amp Env S"_pgm),
    Table::Entry(PatchParam::AMP_ENVELOPE_R, "Amp Env R"_pgm),

    // Control section
    Table::Entry(PatchParam::MONO, "Mono"_pgm),
    Table::Entry(PatchParam::LEGATO, "Legato"_pgm),
    Table::Entry(PatchParam::UNSON, "Unison"_pgm),
    Table::Entry(PatchParam::VELOCITY, "Velocity"_pgm),
    Table::Entry(PatchParam::VELOCITY_ASSIGN, "Velocity Assign"_pgm),
    Table::Entry(PatchParam::CONTROL_ASSIGN, "Control Assign"_pgm),
    
    // Patch parameters (Bank[4])
    Table::Entry(PatchParam::PATCH_NAME, "Patch Name"_pgm),
    Table::Entry(PatchParam::MULTI_FX_TYPE, "Multi-FX Type"_pgm),
    Table::Entry(PatchParam::DELAY_TYPE, "Delay Type"_pgm),
    Table::Entry(PatchParam::BEND_RANGE_UP, "Bend Range Up"_pgm),
    Table::Entry(PatchParam::BEND_RANGE_DOWN, "Bend Range Down"_pgm),
    Table::Entry(PatchParam::MORPH_BEND_ASSIGN, "Morph Bend Assgn"_pgm),
    Table::Entry(PatchParam::UNISON_DETUNE, "Unison Detune"_pgm),
    Table::Entry(PatchParam::ENV_TYPE_SOLO, "Env Type in Solo"_pgm),
    Table::Entry(PatchParam::PATCH_GAIN, "Patch Gain"_pgm),
    Table::Entry(PatchParam::EXT_TRIG_SWITCH, "Ext Trig Switch"_pgm),
    Table::Entry(PatchParam::EXT_TRIG_DEST, "Ext Trig Dest"_pgm)
    );

    return table.getP(param);
}

#endif



#endif