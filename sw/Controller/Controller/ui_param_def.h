/*
Copyright (C) 2023 Andreas Lagler

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

#ifndef UI_PARAM_TYPES_H
#define UI_PARAM_TYPES_H

#include <stdint.h>
#include <variant.h>
#include <array.h>

#include "param_type_enums.h"
#include "patch_param_enums.h"
#include "part_param_enums.h"
#include "performance_param_enums.h"
#include "system_param_enums.h"

using UiParamIdx = Variant<
PatchParam,
PartParam,
PerformanceParam,
SystemParam>;


// Generic unsigned parameter 0..127
// The struct is needed to specify MIN and MAX value like for all the enum parameters
// Constructor and cast operators are needed for the static casts as part of the inc/dec logic
struct UnsignedParam
{
    constexpr UnsignedParam(const uint8_t value = 0)  : m_value(value) {}    
    operator const uint8_t&() const {return m_value;}
    operator uint8_t&()  {return m_value;}
    uint8_t m_value = 0;
    static constexpr uint8_t MIN = 0;
    static constexpr uint8_t MAX = 127;
    
        bool increment()
        {
            if (m_value < MAX)
            {
                ++m_value;
                return true;
            }
            return false;
        }
        
        bool decrement()
        {
            if (m_value > MIN)
            {
                --m_value;
                return true;
            }
            return false;
        }
};

// Generic signed parameter -64..+63
// The struct is needed to specify MIN and MAX value like for all the enum parameters
// Constructor and cast operators are needed for the static casts as part of the inc/dec logic
struct SignedParam
{
    constexpr SignedParam(const int8_t value = 0)  : m_value(value) {}
    operator const int8_t&() const {return m_value;}
    operator int8_t&()  {return m_value;}
    int8_t m_value = 0;
    static constexpr int8_t MIN = -64;
    static constexpr int8_t MAX = 63;

    bool increment()
    {
        if (m_value < MAX)
        {
            ++m_value;
            return true;
        }
        return false;
    }
    
    bool decrement()
    {
        if (m_value > MIN)
        {
            --m_value;
            return true;
        }
        return false;
    }
    
};

// Generic boolean parameter 0/1
// The struct is needed to specify MIN and MAX value like for all the enum parameters
// Constructor and cast operators are needed for the static casts as part of the inc/dec logic
struct BooleanParam
{
    constexpr BooleanParam(const bool value = false)  : m_value(value) {}
    operator const bool&() const {return m_value;}
    operator bool&()  {return m_value;}
    operator uint8_t() const {return m_value ? MAX : MIN;}
    bool m_value = false;
    static constexpr uint8_t MIN = 0;
    static constexpr uint8_t MAX = 1;

    bool increment()
    {
        if (!m_value)
        {
            m_value = true;
            return true;
        }
        return false;
    }
    
    bool decrement()
    {
        if (m_value)
        {
            m_value = false;
            return true;
        }
        return false;
    }
};

// On/Off
struct OnOff : public BooleanParam
{
    constexpr OnOff(const bool value = false)  : BooleanParam(value) {}
};

struct NameParam
{
    constexpr NameParam(const  Array<uint8_t, 16>& value) : m_value(value)
    {}

    Array<uint8_t, 16> m_value;
    uint8_t m_selectedChar = 0;
    
    void incSelectedChar()
    {
        if (m_selectedChar < 15)
        {
            ++m_selectedChar;
        }
    }
    
    void decSelectedChar()
    {
        if (m_selectedChar > 0)
        {
            --m_selectedChar;
        }
    }
    
    bool increment()
    {
        if (m_value[m_selectedChar] < MAX)
        {
            ++m_value[m_selectedChar];
            return true;
        }
        return false;
    }
    
    bool decrement()
    {
        if (m_value[m_selectedChar] > MIN)
        {
            --m_value[m_selectedChar];
            return true;
        }
        return false;
    }
    

    operator const uint8_t&() const {return m_value[m_selectedChar];}
    operator uint8_t&() {return m_value[m_selectedChar];}
    
    static constexpr uint8_t MIN = 0;
    static constexpr uint8_t MAX = 100;
};



// Part detune
struct PartDetune : public SignedParam
{
    static constexpr int8_t MIN = -50;
    static constexpr int8_t MAX = 50;
};

// OSC2 Range
struct OSC2Range : public SignedParam
{
    static constexpr int8_t MIN = -25; // 0..-24 semitones, -25 indicating -WIDE
    static constexpr int8_t MAX = 25; // 0..+24 semitones, +25 indicating +WIDE
};

// OSC Shift
struct OSCShift : public SignedParam
{
    static constexpr int8_t MIN = -2; // 0..-2 octaves
    static constexpr int8_t MAX = 2; // 0..+2 octaves
};

// Arpeggiator Range
struct ArpRange : public UnsignedParam
{
    constexpr ArpRange(const uint8_t value = MIN) : UnsignedParam(value) {}
    static constexpr uint8_t MIN = 1;
    static constexpr uint8_t MAX = 4;
};

// Arpeggiator Tempo
struct ArpTempo : public UnsignedParam
{
    constexpr ArpTempo(const uint8_t value = MIN) : UnsignedParam(value) {}
    static constexpr uint8_t MIN = 20;
    static constexpr uint8_t MAX = 250;
};

// Split Point




// Individual trigger source channel
struct IndivTrigSrcChannel : public UnsignedParam
{
    constexpr IndivTrigSrcChannel(const uint8_t value = MIN) : UnsignedParam(value) {}
    static constexpr uint8_t MIN = 1;
    static constexpr uint8_t MAX = 16;
};

// Voice Mod Bank[2]

// Performance Part Bank[3]

// Part detune
struct PartTranspose : public SignedParam
{
    static constexpr int8_t MIN = -24;
    static constexpr int8_t MAX = 24;
};

// Patch Bank[4]

// Bend Range Up
struct BendRangeUp : public SignedParam
{
    static constexpr int8_t MIN = 0;
    static constexpr int8_t MAX = 24;
};

// Bend Range Down
struct BendRangeDown : public SignedParam
{
    static constexpr int8_t MIN = -24;
    static constexpr int8_t MAX = 0;
};

// Unison Detune
struct UnisonDetune : public SignedParam
{
    static constexpr int8_t MIN = 0;
    static constexpr int8_t MAX = 50;
};

// Device ID
struct DeviceId : public UnsignedParam
{
    constexpr DeviceId(const uint8_t value = MIN) : UnsignedParam(value) {}
    static constexpr uint8_t MIN = 17;
    static constexpr uint8_t MAX = 32;
};

// LCD Contrast
struct LcdContrast : public UnsignedParam
{
    constexpr LcdContrast(const uint8_t value = MIN) : UnsignedParam(value) {}
    static constexpr uint8_t MIN = 1;
    static constexpr uint8_t MAX = 8;
};

// Master Tune
struct MasterTune : public UnsignedParam
{
    constexpr MasterTune(const uint8_t value = MIN) : UnsignedParam(value) {}
    static constexpr uint8_t MIN = 0;
    static constexpr uint8_t MAX = 255;
};

// MIDI Note
struct MidiNote : public UnsignedParam
{
    constexpr MidiNote(const uint8_t value = MIN) : UnsignedParam(value) {}
    static constexpr uint8_t MIN = 0;
    static constexpr uint8_t MAX = 127;
};

// MIDI Note
struct IndivTrigSrcNote : public MidiNote
{
    constexpr IndivTrigSrcNote(const uint8_t value = MIN) : MidiNote(value) {}
    static constexpr uint8_t MIN = 0;
    static constexpr uint8_t MAX = 128; // ALL NOTES corresponds to note value 128
};




// The compound UI parameter type
using UiParamValue = Variant<
UnsignedParam,
SignedParam,
OnOff,
NameParam,
MidiNote,
LFO1Waveform,
LFO2DepthSelect,
OSC1Waveform,
OSC2Waveform,
OSC2Range,
OSCLFO1EnvDest,
OSCShift,
FilterType,
FilterSlope,
AmpPan,
Range_127_100_50,
PartDetune,
OutputAssign,
VoiceAssign,
PartSelect,
KeyMode,
ArpMode,
ArpRange,
ArpTempo,
ArpDestination,
ArpBeatPattern,
TrigDestination,
IndivTrigSrcChannel,
IndivTrigSrcNote,
Algorithm,
ControlAssign,
DelayType,
DelaySync,
EnsembleType,
EnsembleSync,
PartTranspose,
PartMidiChannel,
ChorusSync,
MultiFXType,
BendRangeUp,
BendRangeDown,
UnisonDetune,
EnvTypeSolo,
PatchGain,
MidiSync,
DeviceId,
RemoteKeyboardChannel,
MidiThru,
TxRxEditMode,
TxRxProgramChange,
LcdContrast,
MasterTune,
PatternTriggerQuantize>;


#endif