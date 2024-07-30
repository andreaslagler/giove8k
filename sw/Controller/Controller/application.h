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

#ifndef APPLICATION_H
#define APPLICATION_H

#include "hardware_event.h"
#include "application_event.h"

#include "edit_menu.h"
#include "param_database.h"

#include <functional.h>
#include <array.h>
#include <optional.h>
#include <variant.h>
#include <memory.h>


/**
@brief Central application class encapsulating all functionality
*/
class Application
{
    public:

    /**
    @brief Constructor
    */
    Application();

    constexpr void setEventHandler(auto& eventHandler)
    {
        m_eventHandler = eventHandler;
    }

    void handleEvent(const HardwareEvent& event)
    {
        visit([this](const auto& data){handleEvent(data);}, event);
    }

    private:

    void handleEvent(const UiClockEvent& event);
    void handleEvent(const BpmClockEvent& event);

    // MIDI event dipatcher
    void handleEvent(const MidiEvent& event)
    {
        //
        visit([this](const auto& data){handleEvent(data);}, event.message);
    };

    // MIDI event handlers
    void handleEvent(const MidiNoteOff& event);
    void handleEvent(const MidiNoteOn& event);
    void handleEvent(const MidiPolyAfterTouch& event);
    void handleEvent(const MidiControlChange& event);
    void handleEvent(const MidiProgramChange& event);
    void handleEvent(const MidiChannelAfterTouch& event);
    void handleEvent(const MidiPitchBend& event);
    void handleEvent(const MidiSysExMessage& event);
    void handleEvent(const MidiSysEx& event);

    void handleEvent(const ToneControlBassPotentiometerEvent& event);
    void handleEvent(const ToneControlTreblePotentiometerEvent& event);
    void handleEvent(const MultiFxLevelPotentiometerEvent& event);
    void handleEvent(const DelayTimePotentiometerEvent& event);
    void handleEvent(const DelayFeedbackPotentiometerEvent& event);
    void handleEvent(const DelayLevelPotentiometerEvent& event);
    void handleEvent(const LFO1RatePotentiometerEvent& event);
    void handleEvent(const LFO1FadePotentiometerEvent& event);
    void handleEvent(const LFO2RatePotentiometerEvent& event);
    void handleEvent(const LFO2DepthPotentiometerEvent& event);
    void handleEvent(const PortamentoTimePotentiometerEvent& event);
    void handleEvent(const OSC1Control1PotentiometerEvent& event);
    void handleEvent(const OSC1Control2PotentiometerEvent& event);
    void handleEvent(const OSC2RangePotentiometerEvent& event);
    void handleEvent(const OSC2FineWidePotentiometerEvent& event);
    void handleEvent(const OSC2Control1PotentiometerEvent& event);
    void handleEvent(const OSC2Control2PotentiometerEvent& event);
    void handleEvent(const OSCBalancePotentiometerEvent& event);
    void handleEvent(const OSCXModDepthPotentiometerEvent& event);
    void handleEvent(const OSCLFO1DepthPotentiometerEvent& event);
    void handleEvent(const PitchEnvelopeDepthPotentiometerEvent& event);
    void handleEvent(const PitchEnvelopeAPotentiometerEvent& event);
    void handleEvent(const PitchEnvelopeDPotentiometerEvent& event);
    void handleEvent(const FilterCutoffFreqPotentiometerEvent& event);
    void handleEvent(const FilterResonancePotentiometerEvent& event);
    void handleEvent(const FilterKeyFollowPotentiometerEvent& event);
    void handleEvent(const FilterLFO1DepthPotentiometerEvent& event);
    void handleEvent(const FilterEnvelopeDepthPotentiometerEvent& event);
    void handleEvent(const FilterEnvelopeAPotentiometerEvent& event);
    void handleEvent(const FilterEnvelopeDPotentiometerEvent& event);
    void handleEvent(const FilterEnvelopeSPotentiometerEvent& event);
    void handleEvent(const FilterEnvelopeRPotentiometerEvent& event);
    void handleEvent(const AmpLevelPotentiometerEvent& event);
    void handleEvent(const AmpLFO1DepthPotentiometerEvent& event);
    void handleEvent(const AmpEnvelopeAPotentiometerEvent& event);
    void handleEvent(const AmpEnvelopeDPotentiometerEvent& event);
    void handleEvent(const AmpEnvelopeSPotentiometerEvent& event);
    void handleEvent(const AmpEnvelopeRPotentiometerEvent& event);
    void handleEvent(const ArpeggiatorRPSTempoPotentiometerEvent& event);
    void handleEvent(const PotentiometerDummyEvent&)
    {}

    void handleEvent(const EditButtonEvent& event);
    void handleEvent(const ExitButtonEvent& event);
    void handleEvent(const Bank1ButtonEvent& event);
    void handleEvent(const Bank2ButtonEvent& event);
    void handleEvent(const Bank3ButtonEvent& event);
    void handleEvent(const Bank4ButtonEvent& event);
    void handleEvent(const Bank5ButtonEvent& event);
    void handleEvent(const Bank6ButtonEvent& event);
    void handleEvent(const Bank7ButtonEvent& event);
    void handleEvent(const Bank8ButtonEvent& event);
    void handleEvent(const UpButtonEvent& event);
    void handleEvent(const DownButtonEvent& event);
    void handleEvent(const GroupUpButtonEvent& event);
    void handleEvent(const GroupDownButtonEvent& event);
    void handleEvent(const ButtonDummyEvent&)
    {}

    void handleUIClockEvent();
    void handleBPMClockEvent();
    

    constexpr void setUiParam(const auto& param)
    {
        //m_eventHandler(ApplicationEvent(in_place_type_t<UiParamChangeEvent>(), param, m_params->getParamValue(param)));
    }

    constexpr void showUiParam(const auto& param)
    {
        //m_eventHandler(ApplicationEvent(in_place_type_t<UiParamShowEvent>(), param, m_params->getParamValue(param)));
    }



    uint8_t m_homeScreenTimer = 0;
    void resetHomeScreenTimer()
    {
        m_homeScreenTimer = 30; // Show home screen after UI was inactive for 3 seconds
    }

    void updateHomeScreen()
    {
    }

    // Registered event handler for all possible application events
    function<void(const ApplicationEvent&)> m_eventHandler;
    ParamDatabase m_params;
    EditMenu m_menu;
};

# endif