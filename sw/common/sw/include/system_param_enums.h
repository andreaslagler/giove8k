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

#ifndef SYSTEM_PARAM_ENUMS_H
#define SYSTEM_PARAM_ENUMS_H

#include "common_enum_def.h"

DEFINE_ENUM(
SystemParam,

// MIDI section (Bank[5])
LOCAL_SWITCH,
MIDI_SYNC,
DEVICE_ID,
RX_EXCLUSIVE,
PERFORMANCE_CONTROL_CHANNEL,
REMOTE_KEYBOARD_CHANNEL,
MIDI_THRU,
TX_RX_EDIT,
TX_RX_EDIT_MODE,
TX_RX_SETTING,
TX_RX_PROGRAM_CHANGE,
CONTROL_UP,
CONTROL_DOWN,

// Setup (Bank[6])
LCD_CONTRAST,
MASTER_TUNE,
POWER_UP_MODE,
PATTERN_TRIGGER_QUANTIZE,
MOTION_RESTART)

#if __cplusplus

inline PgmString toString(const SystemParam param)
{
    using Table = SparseLUT<PgmString, SystemParam, SystemParam::NOFENTRIES>;

    constexpr static const PROGMEM Table table
    (
    ""_pgm,
    // MIDI section (Bank[5])
    Table::Entry(SystemParam::LOCAL_SWITCH, "Local Switch"_pgm),
    Table::Entry(SystemParam::MIDI_SYNC, "MIDI Sync"_pgm),
    Table::Entry(SystemParam::DEVICE_ID, "Device ID"_pgm),
    Table::Entry(SystemParam::RX_EXCLUSIVE, "Rx Exclusive SW"_pgm),
    Table::Entry(SystemParam::PERFORMANCE_CONTROL_CHANNEL, "Perform Ctrl CH"_pgm),
    Table::Entry(SystemParam::REMOTE_KEYBOARD_CHANNEL, "Remote KBD CH"_pgm),
    Table::Entry(SystemParam::MIDI_THRU, "MIDI Thru"_pgm),
    Table::Entry(SystemParam::TX_RX_EDIT, "Tx/Rx Edit SW"_pgm),
    Table::Entry(SystemParam::TX_RX_EDIT_MODE, "Tx/Rx Edit Mode"_pgm),
    Table::Entry(SystemParam::TX_RX_SETTING, "Tx/Rx Setting"_pgm),
    Table::Entry(SystemParam::TX_RX_PROGRAM_CHANGE, "Tx/Rx ProgChg SW"_pgm),
    Table::Entry(SystemParam::CONTROL_UP, "Control Up"_pgm),
    Table::Entry(SystemParam::CONTROL_DOWN, "Control Down"_pgm),

    // Setup (Bank[6])
    Table::Entry(SystemParam::LCD_CONTRAST, "LCD Contrast"_pgm),
    Table::Entry(SystemParam::MASTER_TUNE, "Master Tune"_pgm),
    Table::Entry(SystemParam::POWER_UP_MODE, "Power Up Mode"_pgm),
    Table::Entry(SystemParam::PATTERN_TRIGGER_QUANTIZE, "Pattern Trig Qtz"_pgm),
    Table::Entry(SystemParam::MOTION_RESTART, "Motion Restart"_pgm)
    );

    return table.getP(param);
}

#endif

#endif