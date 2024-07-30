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

#include "input.h"
#include "type_map.h"


Input::Input()
{
    // Make sure hardware is initialized
    Hardware::init();
    
    // Callback for UI clock. This lambda expression needs to be static in order to not go out of scope
    static auto uiClockCallback = [&]()
    {
        HardwareEvent event{in_place_type_t<UiClockEvent>()};
        m_eventQueue.push(move(event));
    };
    s_uiClockCallback = uiClockCallback;
    
    // Callback for BPM clock. This lambda expression needs to be static in order to not go out of scope
    static auto bpmClockCallback = [&]()
    {
        HardwareEvent event{in_place_type_t<BpmClockEvent>()};
        m_eventQueue.push(move(event));
    };
    s_bpmClockCallback = bpmClockCallback;
    
    // Callback for buttons. This lambda expression needs to be static in order to not go out of scope
    static auto buttonCallback = [this]<uint8_t id>()
    {
        using ButtonEvent = TypeMap<16, ButtonDummyEvent,
        TypeMapElem<0, EditButtonEvent>,
        TypeMapElem<1, Bank1ButtonEvent>,
        TypeMapElem<2, Bank2ButtonEvent>,
        TypeMapElem<3, Bank3ButtonEvent>,
        TypeMapElem<4, Bank4ButtonEvent>,
        TypeMapElem<5, Bank5ButtonEvent>,
        TypeMapElem<6, Bank6ButtonEvent>,
        TypeMapElem<7, Bank7ButtonEvent>,
        TypeMapElem<8, Bank8ButtonEvent>,
        TypeMapElem<9, ExitButtonEvent>,
        TypeMapElem<10, GroupUpButtonEvent>,
        TypeMapElem<11, GroupDownButtonEvent>
        >::IndexToTypeT<id>;
        m_eventQueue.push(HardwareEvent{in_place_type_t<ButtonEvent>()});
    };
    
    // Callback for buttons  with toggle logic. This lambda expression needs to be static in order to not go out of scope
    static auto toggleButtonCallback = [this]<uint8_t id>(const bool value)
    {
        using ButtonEvent = TypeMap<16, ButtonDummyEvent,
        TypeMapElem<0, UpButtonEvent>,
        TypeMapElem<1, DownButtonEvent>
        >::IndexToTypeT<id>;
        m_eventQueue.push(HardwareEvent{in_place_type_t<ButtonEvent>(), value});
    };
    
    // Register step button callbacks
    Button000::registerCallback([]{ buttonCallback.template operator()<0>(); });
    Button001::registerCallback([]{ buttonCallback.template operator()<1>(); });
    Button002::registerCallback([]{ buttonCallback.template operator()<2>(); });
    Button003::registerCallback([]{ buttonCallback.template operator()<3>(); });
    Button004::registerCallback([]{ buttonCallback.template operator()<4>(); });
    Button005::registerCallback([]{ buttonCallback.template operator()<5>(); });
    Button006::registerCallback([]{ buttonCallback.template operator()<6>(); });
    Button007::registerCallback([]{ buttonCallback.template operator()<7>(); });
    Button008::registerCallback([]{ buttonCallback.template operator()<8>(); });
    Button009::registerCallback([]{ buttonCallback.template operator()<9>(); });
    Button010::registerCallback([](const bool value){ toggleButtonCallback.template operator()<0>(value); });
    Button011::registerCallback([](const bool value){ toggleButtonCallback.template operator()<1>(value); });
    Button012::registerCallback([]{ buttonCallback.template operator()<10>(); });
    Button013::registerCallback([]{ buttonCallback.template operator()<11>(); });
    Button014::registerCallback([]{ buttonCallback.template operator()<14>(); });
    Button015::registerCallback([]{ buttonCallback.template operator()<15>(); });

    //// Callback for option buttons. This lambda expression needs to be static in order to not go out of scope
    //static auto optionButtonCallback = [&](const uint16_t buttonData)
    //{
    //OptionButtonEventData data {static_cast<uint8_t>(buttonData)};
    //HardwareEvent event
    //{
    //HardwareEventType::BUTTON,
    //HardwareEventData(in_place_type_t<OptionButtonEventData>(), move(data))
    //};
    //
    //m_eventQueue.push(move(event));
    //};
    //
    //OptionButtons::registerCallback(optionButtonCallback);
    
    #if false

    // Callback for potentiometers. This lambda expression needs to be static in order to not go out of scope
    static auto potentiometerCallback = [this]<uint8_t id>(const uint8_t value)
    {
        using PotentiometerEvent = TypeMap<39, PotentiometerDummyEvent,
        TypeMapElem<0, ToneControlBassPotentiometerEvent>,
        TypeMapElem<1, ToneControlTreblePotentiometerEvent>,
        TypeMapElem<2, MultiFxLevelPotentiometerEvent>,
        TypeMapElem<3, DelayTimePotentiometerEvent>,
        TypeMapElem<4, DelayFeedbackPotentiometerEvent>,
        TypeMapElem<5, DelayLevelPotentiometerEvent>,
        TypeMapElem<6, LFO1RatePotentiometerEvent>,
        TypeMapElem<7, LFO1FadePotentiometerEvent>,
        TypeMapElem<8, LFO2RatePotentiometerEvent>,
        TypeMapElem<9, LFO2DepthPotentiometerEvent>,
        TypeMapElem<10, PortamentoTimePotentiometerEvent>,
        TypeMapElem<11, OSC1Control1PotentiometerEvent>,
        TypeMapElem<12, OSC1Control2PotentiometerEvent>,
        TypeMapElem<13, OSC2RangePotentiometerEvent>,
        TypeMapElem<14, OSC2FineWidePotentiometerEvent>,
        TypeMapElem<15, OSC2Control1PotentiometerEvent>,
        TypeMapElem<16, OSC2Control2PotentiometerEvent>,
        TypeMapElem<17, OSCBalancePotentiometerEvent>,
        TypeMapElem<18, OSCXModDepthPotentiometerEvent>,
        TypeMapElem<19, OSCLFO1DepthPotentiometerEvent>,
        TypeMapElem<20, PitchEnvelopeDepthPotentiometerEvent>,
        TypeMapElem<21, PitchEnvelopeAPotentiometerEvent>,
        TypeMapElem<22, PitchEnvelopeDPotentiometerEvent>,
        TypeMapElem<23, FilterCutoffFreqPotentiometerEvent>,
        TypeMapElem<24, FilterResonancePotentiometerEvent>,
        TypeMapElem<25, FilterKeyFollowPotentiometerEvent>,
        TypeMapElem<26, FilterLFO1DepthPotentiometerEvent>,
        TypeMapElem<27, FilterEnvelopeDepthPotentiometerEvent>,
        TypeMapElem<28, FilterEnvelopeAPotentiometerEvent>,
        TypeMapElem<29, FilterEnvelopeDPotentiometerEvent>,
        TypeMapElem<30, FilterEnvelopeSPotentiometerEvent>,
        TypeMapElem<31, FilterEnvelopeRPotentiometerEvent>,
        TypeMapElem<32, AmpLevelPotentiometerEvent>,
        TypeMapElem<33, AmpLFO1DepthPotentiometerEvent>,
        TypeMapElem<34, AmpEnvelopeAPotentiometerEvent>,
        TypeMapElem<35, AmpEnvelopeDPotentiometerEvent>,
        TypeMapElem<36, AmpEnvelopeSPotentiometerEvent>,
        TypeMapElem<37, AmpEnvelopeRPotentiometerEvent>,
        TypeMapElem<38, ArpeggiatorRPSTempoPotentiometerEvent>
        >::IndexToTypeT<id>;
        m_eventQueue.push(HardwareEvent{in_place_type_t<PotentiometerEvent>(), value});
    };
    
    Hardware::Potentiometer00::registerCallback([&](const uint8_t value){ potentiometerCallback.template operator()<0>(value); });
    Hardware::Potentiometer01::registerCallback([&](const uint8_t value){ potentiometerCallback.template operator()<1>(value); });
    Hardware::Potentiometer02::registerCallback([&](const uint8_t value){ potentiometerCallback.template operator()<2>(value); });
    Hardware::Potentiometer03::registerCallback([&](const uint8_t value){ potentiometerCallback.template operator()<3>(value); });
    Hardware::Potentiometer04::registerCallback([&](const uint8_t value){ potentiometerCallback.template operator()<4>(value); });
    Hardware::Potentiometer05::registerCallback([&](const uint8_t value){ potentiometerCallback.template operator()<5>(value); });
    Hardware::Potentiometer06::registerCallback([&](const uint8_t value){ potentiometerCallback.template operator()<6>(value); });
    Hardware::Potentiometer07::registerCallback([&](const uint8_t value){ potentiometerCallback.template operator()<7>(value); });

    Hardware::Potentiometer10::registerCallback([&](const uint8_t value){ potentiometerCallback.template operator()<8>(value); });
    Hardware::Potentiometer11::registerCallback([&](const uint8_t value){ potentiometerCallback.template operator()<9>(value); });
    Hardware::Potentiometer12::registerCallback([&](const uint8_t value){ potentiometerCallback.template operator()<10>(value); });
    Hardware::Potentiometer13::registerCallback([&](const uint8_t value){ potentiometerCallback.template operator()<11>(value); });
    Hardware::Potentiometer14::registerCallback([&](const uint8_t value){ potentiometerCallback.template operator()<12>(value); });
    Hardware::Potentiometer15::registerCallback([&](const uint8_t value){ potentiometerCallback.template operator()<13>(value); });
    Hardware::Potentiometer16::registerCallback([&](const uint8_t value){ potentiometerCallback.template operator()<14>(value); });
    Hardware::Potentiometer17::registerCallback([&](const uint8_t value){ potentiometerCallback.template operator()<15>(value); });

    Hardware::Potentiometer20::registerCallback([&](const uint8_t value){ potentiometerCallback.template operator()<16>(value); });
    Hardware::Potentiometer21::registerCallback([&](const uint8_t value){ potentiometerCallback.template operator()<17>(value); });
    Hardware::Potentiometer22::registerCallback([&](const uint8_t value){ potentiometerCallback.template operator()<18>(value); });
    Hardware::Potentiometer23::registerCallback([&](const uint8_t value){ potentiometerCallback.template operator()<19>(value); });
    Hardware::Potentiometer24::registerCallback([&](const uint8_t value){ potentiometerCallback.template operator()<20>(value); });
    Hardware::Potentiometer25::registerCallback([&](const uint8_t value){ potentiometerCallback.template operator()<21>(value); });
    Hardware::Potentiometer26::registerCallback([&](const uint8_t value){ potentiometerCallback.template operator()<22>(value); });
    Hardware::Potentiometer27::registerCallback([&](const uint8_t value){ potentiometerCallback.template operator()<23>(value); });

    Hardware::Potentiometer30::registerCallback([&](const uint8_t value){ potentiometerCallback.template operator()<24>(value); });
    Hardware::Potentiometer31::registerCallback([&](const uint8_t value){ potentiometerCallback.template operator()<25>(value); });
    Hardware::Potentiometer32::registerCallback([&](const uint8_t value){ potentiometerCallback.template operator()<26>(value); });
    Hardware::Potentiometer33::registerCallback([&](const uint8_t value){ potentiometerCallback.template operator()<27>(value); });
    Hardware::Potentiometer34::registerCallback([&](const uint8_t value){ potentiometerCallback.template operator()<28>(value); });
    Hardware::Potentiometer35::registerCallback([&](const uint8_t value){ potentiometerCallback.template operator()<29>(value); });
    Hardware::Potentiometer36::registerCallback([&](const uint8_t value){ potentiometerCallback.template operator()<30>(value); });
    Hardware::Potentiometer37::registerCallback([&](const uint8_t value){ potentiometerCallback.template operator()<31>(value); });

    Hardware::Potentiometer40::registerCallback([&](const uint8_t value){ potentiometerCallback.template operator()<32>(value); });
    Hardware::Potentiometer41::registerCallback([&](const uint8_t value){ potentiometerCallback.template operator()<33>(value); });
    Hardware::Potentiometer42::registerCallback([&](const uint8_t value){ potentiometerCallback.template operator()<34>(value); });
    Hardware::Potentiometer43::registerCallback([&](const uint8_t value){ potentiometerCallback.template operator()<35>(value); });
    Hardware::Potentiometer44::registerCallback([&](const uint8_t value){ potentiometerCallback.template operator()<36>(value); });
    Hardware::Potentiometer45::registerCallback([&](const uint8_t value){ potentiometerCallback.template operator()<37>(value); });
    Hardware::Potentiometer46::registerCallback([&](const uint8_t value){ potentiometerCallback.template operator()<38>(value); });
    Hardware::Potentiometer47::registerCallback([&](const uint8_t value){ potentiometerCallback.template operator()<39>(value); });

    #endif

    // Register MIDI event callbacks
    
    // Control change, program change and system exclusive messages are forwarded to application
    //midiInput.registerObserver([](const MidiControlChange & message) {application.onMidiMessage(message);});
    //midiInput.registerObserver([](const MidiProgramChange & message) {application.onMidiMessage(message);});
    //midiInput.registerObserver([](const MidiSysEx & message) {application.onMidiMessage(message);});
    
    // Note on/off, pitch bend and after touch messages are forwarded to waveblaster output directly
    //s_midiInput.registerObserver([](const MidiNoteOff & message) {MidiOutput<WaveBlasterOutput>::write(message);});
    //s_midiInput.registerObserver([](const MidiNoteOn & message) {MidiOutput<WaveBlasterOutput>::write(message);});
    //s_midiInput.registerObserver([](const MidiPitchBend & message) {MidiOutput<WaveBlasterOutput>::write(message);});
    //s_midiInput.registerObserver([](const MidiPolyAfterTouch & message) {MidiOutput<WaveBlasterOutput>::write(message);});
    //s_midiInput.registerObserver([](const MidiChannelAfterTouch & message) {MidiOutput<WaveBlasterOutput>::write(message);});
}

void Input::doEvents()
{
    // Check for queued events to handle
    while (true)
    {
        bool queueEmpty = false;
        ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
        {
            queueEmpty = m_eventQueue.empty();
        }
        
        if (queueEmpty)
        {
            break;
        }
        else
        {
            HardwareEvent event;
            ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
            {
                event = m_eventQueue.top();
                m_eventQueue.pop();
            }
            m_eventHandler(event);
        }
    }

    //Check for received Midi data to process
    while (true)
    {
        uint8_t data = 0;
        
        bool dataAvailable = false;
        ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
        {
            if (!s_midiInputBuffer.empty())
            {
                dataAvailable = true;
                data = s_midiInputBuffer.front();
                s_midiInputBuffer.pop();
            }
        }
        
        if (dataAvailable)
        {
            if (auto event = m_midiInputParser.parse(data))
            {
                ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
                {
                    m_eventQueue.push(HardwareEvent{in_place_type_t<MidiEvent>(), *event, MidiEvent::Source::MIDI_IN});
                }
            }
        }
        else
        {
            break;
        }
    }

    //Check for received Midi data to process
    while (true)
    {
        uint8_t data = 0;
        
        bool dataAvailable = false;
        ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
        {
            if (!s_midiKeyboardBuffer.empty())
            {
                dataAvailable = true;
                data = s_midiKeyboardBuffer.front();
                s_midiKeyboardBuffer.pop();
            }
        }
        
        if (dataAvailable)
        {
            if (auto event = m_midiKeyboardParser.parse(data))
            {
                ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
                {
                    m_eventQueue.push(HardwareEvent{in_place_type_t<MidiEvent>(), *event, MidiEvent::Source::MIDI_KEYBOARD});
                }
            }
        }
        else
        {
            break;
        }
    }
    
    Hardware::doEvents();
}
