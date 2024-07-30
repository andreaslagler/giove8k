/*
Copyright (C) 2022 Andreas Lagler

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

#include "application.h"
#include "hardware_event.h"
#include "application_event.h"
//#include "ui_param_enums.h"


Application::Application() : m_menu(m_params, m_eventHandler)
{}

void Application::handleEvent(const UiClockEvent&)
{
    m_menu.clock();
}

void Application::handleEvent(const BpmClockEvent&)
{

}

void Application::handleEvent(const MidiNoteOff&) {}
void Application::handleEvent(const MidiNoteOn&) {}
void Application::handleEvent(const MidiPolyAfterTouch&) {}
void Application::handleEvent(const MidiControlChange&) {}
void Application::handleEvent(const MidiProgramChange&) {}
void Application::handleEvent(const MidiChannelAfterTouch&) {}
void Application::handleEvent(const MidiPitchBend&){}
void Application::handleEvent(const MidiSysExMessage&) {}
void Application::handleEvent(const MidiSysEx&) {}


void Application::handleEvent(const ToneControlBassPotentiometerEvent&){}
void Application::handleEvent(const ToneControlTreblePotentiometerEvent&){}
void Application::handleEvent(const MultiFxLevelPotentiometerEvent&){}
void Application::handleEvent(const DelayTimePotentiometerEvent&){}
void Application::handleEvent(const DelayFeedbackPotentiometerEvent&){}
void Application::handleEvent(const DelayLevelPotentiometerEvent&){}
void Application::handleEvent(const LFO1RatePotentiometerEvent&){}
void Application::handleEvent(const LFO1FadePotentiometerEvent&){}
void Application::handleEvent(const LFO2RatePotentiometerEvent&){}
void Application::handleEvent(const LFO2DepthPotentiometerEvent&){}
void Application::handleEvent(const PortamentoTimePotentiometerEvent&){}
void Application::handleEvent(const OSC1Control1PotentiometerEvent&){}
void Application::handleEvent(const OSC1Control2PotentiometerEvent&){}
void Application::handleEvent(const OSC2RangePotentiometerEvent&){}
void Application::handleEvent(const OSC2FineWidePotentiometerEvent&){}
void Application::handleEvent(const OSC2Control1PotentiometerEvent&){}
void Application::handleEvent(const OSC2Control2PotentiometerEvent&){}
void Application::handleEvent(const OSCBalancePotentiometerEvent&){}
void Application::handleEvent(const OSCXModDepthPotentiometerEvent&){}
void Application::handleEvent(const OSCLFO1DepthPotentiometerEvent&){}
void Application::handleEvent(const PitchEnvelopeDepthPotentiometerEvent&){}
void Application::handleEvent(const PitchEnvelopeAPotentiometerEvent&){}
void Application::handleEvent(const PitchEnvelopeDPotentiometerEvent&){}
void Application::handleEvent(const FilterCutoffFreqPotentiometerEvent&){}
void Application::handleEvent(const FilterResonancePotentiometerEvent&){}
void Application::handleEvent(const FilterKeyFollowPotentiometerEvent&){}
void Application::handleEvent(const FilterLFO1DepthPotentiometerEvent&){}
void Application::handleEvent(const FilterEnvelopeDepthPotentiometerEvent&){}
void Application::handleEvent(const FilterEnvelopeAPotentiometerEvent&){}
void Application::handleEvent(const FilterEnvelopeDPotentiometerEvent&){}
void Application::handleEvent(const FilterEnvelopeSPotentiometerEvent&){}
void Application::handleEvent(const FilterEnvelopeRPotentiometerEvent&){}
void Application::handleEvent(const AmpLevelPotentiometerEvent&){}
void Application::handleEvent(const AmpLFO1DepthPotentiometerEvent&){}
void Application::handleEvent(const AmpEnvelopeAPotentiometerEvent&){}
void Application::handleEvent(const AmpEnvelopeDPotentiometerEvent&){}
void Application::handleEvent(const AmpEnvelopeSPotentiometerEvent&){}
void Application::handleEvent(const AmpEnvelopeRPotentiometerEvent&){}
void Application::handleEvent(const ArpeggiatorRPSTempoPotentiometerEvent&){}



void Application::handleEvent(const EditButtonEvent&)
{
    m_menu.onEditButton();
//    (*m_eventHandler)(ApplicationEvent(in_place_type_t<EditMenuEvent>(), state));
}

void Application::handleEvent(const ExitButtonEvent&)
{
    m_menu.onExitButton();
//    (*m_eventHandler)(ApplicationEvent(in_place_type_t<EditMenuEvent>(), state));
}

void Application::handleEvent(const Bank1ButtonEvent&)
{
    m_menu.onBank1Button();
//    (*m_eventHandler)(ApplicationEvent(in_place_type_t<EditMenuEvent>(), state));
}

void Application::handleEvent(const Bank2ButtonEvent&)
{
    m_menu.onBank2Button();
//    (*m_eventHandler)(ApplicationEvent(in_place_type_t<EditMenuEvent>(), state));
}

void Application::handleEvent(const Bank3ButtonEvent&)
{
    m_menu.onBank3Button();
//    (*m_eventHandler)(ApplicationEvent(in_place_type_t<EditMenuEvent>(), state));
}

void Application::handleEvent(const Bank4ButtonEvent&)
{
    m_menu.onBank4Button();
//    (*m_eventHandler)(ApplicationEvent(in_place_type_t<EditMenuEvent>(), state));
}

void Application::handleEvent(const Bank5ButtonEvent&)
{
    m_menu.onBank5Button();
//    (*m_eventHandler)(ApplicationEvent(in_place_type_t<EditMenuEvent>(), state));
}

void Application::handleEvent(const Bank6ButtonEvent&)
{
    m_menu.onBank6Button();
//    (*m_eventHandler)(ApplicationEvent(in_place_type_t<EditMenuEvent>(), state));
}

void Application::handleEvent(const Bank7ButtonEvent&)
{
    m_menu.onBank7Button();
//    (*m_eventHandler)(ApplicationEvent(in_place_type_t<EditMenuEvent>(), state));
}

void Application::handleEvent(const Bank8ButtonEvent&)
{
    m_menu.onBank8Button();
//    (*m_eventHandler)(ApplicationEvent(in_place_type_t<EditMenuEvent>(), state));
}

void Application::handleEvent(const UpButtonEvent& event)
{
    m_menu.onUpButton(event.value);
}

void Application::handleEvent(const DownButtonEvent& event)
{
    m_menu.onDownButton(event.value);
}

void Application::handleEvent(const GroupUpButtonEvent&)
{
    //if(auto paramOpt = m_menu.getCurrentParam())
    //{
        //auto& param = getParamValue(*paramOpt);
        //if (holdsAlternative<NameParam>(param))
        //{
            //get<NameParam>(param).incSelectedChar();
        //}
    //}
}

void Application::handleEvent(const GroupDownButtonEvent&)
{
    //if(auto paramOpt = m_menu.getCurrentParam())
    //{
        //auto& param = getParamValue(*paramOpt);
        //if (holdsAlternative<NameParam>(param))
        //{
            //get<NameParam>(param).decSelectedChar();
        //}
    //}
}

