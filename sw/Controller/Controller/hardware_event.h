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

#ifndef HARDWARE_EVENT_H
#define HARDWARE_EVENT_H

#include <stdint.h>
#include <stdbool.h>
#include <variant.h>

#include "midi_types.h"


// Enumeration of all hardware event types
// NB. Event types are ordered by priority!
enum class HardwareEventType : uint8_t
{
    BPM_CLOCK,
    MIDI,
    BUTTON,
    POTENTIOMETER,
    ENCODER,
    OPTION_BUTTON,
    UI_CLOCK,
    NOF_ENTRIES
};

struct UiClockEvent {};
struct BpmClockEvent {};

struct MidiEvent
{
    MidiMessage message;
    
    enum class Source
    {
        MIDI_IN,
        MIDI_KEYBOARD
    };
    
    Source source = Source::MIDI_IN;
};

struct EditButtonEvent {};
struct ExitButtonEvent {};
struct Bank1ButtonEvent {};
struct Bank2ButtonEvent {};
struct Bank3ButtonEvent {};
struct Bank4ButtonEvent {};
struct Bank5ButtonEvent {};
struct Bank6ButtonEvent {};
struct Bank7ButtonEvent {};
struct Bank8ButtonEvent {};
struct GroupUpButtonEvent {};
struct GroupDownButtonEvent {};
struct UpButtonEvent { bool value; };
struct DownButtonEvent { bool value; };
struct ButtonDummyEvent {};


struct ToneControlBassPotentiometerEvent { uint8_t value; };
struct ToneControlTreblePotentiometerEvent { uint8_t value; };
struct MultiFxLevelPotentiometerEvent { uint8_t value; };
struct DelayTimePotentiometerEvent { uint8_t value; };
struct DelayFeedbackPotentiometerEvent { uint8_t value; };
struct DelayLevelPotentiometerEvent { uint8_t value; };
struct LFO1RatePotentiometerEvent { uint8_t value; };
struct LFO1FadePotentiometerEvent { uint8_t value; };
struct LFO2RatePotentiometerEvent { uint8_t value; };
struct LFO2DepthPotentiometerEvent { uint8_t value; };
struct PortamentoTimePotentiometerEvent { uint8_t value; };
struct OSC1Control1PotentiometerEvent { uint8_t value; };
struct OSC1Control2PotentiometerEvent { uint8_t value; };
struct OSC2RangePotentiometerEvent { uint8_t value; };
struct OSC2FineWidePotentiometerEvent { uint8_t value; };
struct OSC2Control1PotentiometerEvent { uint8_t value; };
struct OSC2Control2PotentiometerEvent { uint8_t value; };
struct OSCBalancePotentiometerEvent { uint8_t value; };
struct OSCXModDepthPotentiometerEvent { uint8_t value; };
struct OSCLFO1DepthPotentiometerEvent { uint8_t value; };
struct PitchEnvelopeDepthPotentiometerEvent { uint8_t value; };
struct PitchEnvelopeAPotentiometerEvent { uint8_t value; };
struct PitchEnvelopeDPotentiometerEvent { uint8_t value; };
struct FilterCutoffFreqPotentiometerEvent { uint8_t value; };
struct FilterResonancePotentiometerEvent { uint8_t value; };
struct FilterKeyFollowPotentiometerEvent { uint8_t value; };
struct FilterLFO1DepthPotentiometerEvent { uint8_t value; };
struct FilterEnvelopeDepthPotentiometerEvent { uint8_t value; };
struct FilterEnvelopeAPotentiometerEvent { uint8_t value; };
struct FilterEnvelopeDPotentiometerEvent { uint8_t value; };
struct FilterEnvelopeSPotentiometerEvent { uint8_t value; };
struct FilterEnvelopeRPotentiometerEvent { uint8_t value; };
struct AmpLevelPotentiometerEvent { uint8_t value; };
struct AmpLFO1DepthPotentiometerEvent { uint8_t value; };
struct AmpEnvelopeAPotentiometerEvent { uint8_t value; };
struct AmpEnvelopeDPotentiometerEvent { uint8_t value; };
struct AmpEnvelopeSPotentiometerEvent { uint8_t value; };
struct AmpEnvelopeRPotentiometerEvent { uint8_t value; };
struct ArpeggiatorRPSTempoPotentiometerEvent { uint8_t value; };
struct PotentiometerDummyEvent { uint8_t value; };


// Hardware event data is stored as a variant
using HardwareEvent = Variant<
BpmClockEvent,
MidiEvent,

UpButtonEvent,
DownButtonEvent,
EditButtonEvent,
ExitButtonEvent,
Bank1ButtonEvent,
Bank2ButtonEvent,
Bank3ButtonEvent,
Bank4ButtonEvent,
Bank5ButtonEvent,
Bank6ButtonEvent,
Bank7ButtonEvent,
Bank8ButtonEvent,
GroupUpButtonEvent,
GroupDownButtonEvent,
ButtonDummyEvent,

ToneControlBassPotentiometerEvent,
ToneControlTreblePotentiometerEvent,
MultiFxLevelPotentiometerEvent,
DelayTimePotentiometerEvent,
DelayFeedbackPotentiometerEvent,
DelayLevelPotentiometerEvent,
LFO1RatePotentiometerEvent,
LFO1FadePotentiometerEvent,
LFO2RatePotentiometerEvent,
LFO2DepthPotentiometerEvent,
PortamentoTimePotentiometerEvent,
OSC1Control1PotentiometerEvent,
OSC1Control2PotentiometerEvent,
OSC2RangePotentiometerEvent,
OSC2FineWidePotentiometerEvent,
OSC2Control1PotentiometerEvent,
OSC2Control2PotentiometerEvent,
OSCBalancePotentiometerEvent,
OSCXModDepthPotentiometerEvent,
OSCLFO1DepthPotentiometerEvent,
PitchEnvelopeDepthPotentiometerEvent,
PitchEnvelopeAPotentiometerEvent,
PitchEnvelopeDPotentiometerEvent,
FilterCutoffFreqPotentiometerEvent,
FilterResonancePotentiometerEvent,
FilterKeyFollowPotentiometerEvent,
FilterLFO1DepthPotentiometerEvent,
FilterEnvelopeDepthPotentiometerEvent,
FilterEnvelopeAPotentiometerEvent,
FilterEnvelopeDPotentiometerEvent,
FilterEnvelopeSPotentiometerEvent,
FilterEnvelopeRPotentiometerEvent,
AmpLevelPotentiometerEvent,
AmpLFO1DepthPotentiometerEvent,
AmpEnvelopeAPotentiometerEvent,
AmpEnvelopeDPotentiometerEvent,
AmpEnvelopeSPotentiometerEvent,
AmpEnvelopeRPotentiometerEvent,
ArpeggiatorRPSTempoPotentiometerEvent,
PotentiometerDummyEvent,

UiClockEvent>;

// Comparison operator (needed by priority queue)
constexpr inline bool operator<(const HardwareEvent& a, const HardwareEvent& b)
{
    return a.index() < b.index();
}




#endif