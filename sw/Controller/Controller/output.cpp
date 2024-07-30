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

#include "output.h"
#include "ui_param_def.h"
#include "ui_param_tostring.h"
#include <variant.h>

void Output::handleEvent(const NoteOnEvent& event)
{
}

static constexpr uint8_t voiceModSendLED = 0; // On / Off
static constexpr uint8_t voiceModulatorOnLED = 1; // On / Off
static constexpr uint8_t externalInputLED = 2; // On / Off
static constexpr uint8_t lfo1WaveformLED = 3; // 4 waveforms
static constexpr uint8_t osc1WaveformLED = 7; // 7 waveforms
static constexpr uint8_t oscRingLED = 14; // on / off
static constexpr uint8_t osc2SyncLED = 15; // on / off
static constexpr uint8_t osc2ExtLED = 16; // on / off
static constexpr uint8_t osc2WaveformLED = 17; // 4 waveforms
static constexpr uint8_t filterSlopeLED = 21; // 24dB On / Off
static constexpr uint8_t filterTypeLED = 22; // 3 filter types
static constexpr uint8_t ampAutoManualLED = 25; // auto / manual
static constexpr uint8_t lfo2DepthSelectLED = 27; // 3 modulation destinations
static constexpr uint8_t portamentoLED = 30;
static constexpr uint8_t oscShiftLED = 31; // +/- indicators
static constexpr uint8_t lfo1EnvDestinationLED = 33; // 3 destinations
static constexpr uint8_t monoLED = 36; // on / off
static constexpr uint8_t legatoLED = 37; // on / off
static constexpr uint8_t unisonLED = 38; // on / off
static constexpr uint8_t velocityLED = 39; // on / off
static constexpr uint8_t velocityAssignLED = 40; // on / off
static constexpr uint8_t controlAssignLED = 41; // on / off
static constexpr uint8_t keyModeLED = 42; // 3 key modes
static constexpr uint8_t arpOnLED = 45; // on / off
static constexpr uint8_t arpHoldLED = 46; // on / off
static constexpr uint8_t arpRecLED = 47; // on / off
static constexpr uint8_t arpModeLED = 48; // 4 modes
static constexpr uint8_t arpRangeLED = 52; // 4 octaves
static constexpr uint8_t previewLED = 56; // on / off
static constexpr uint8_t selectLED = 57; // on / off
static constexpr uint8_t bankLED = 58; // Bank 1-8
static constexpr uint8_t numberLED = 66; // Number 1-8
static constexpr uint8_t editLED = 74; // on / off


void Output::handleEvent(const EditMenuEvent& event)
{
    switch (event.state)
    {
        case EditMenuState::IDLE:
        // Switch off EDIT and BANK 1-8 LEDs
        LEDs::set(editLED, LedState::OFF);
        LEDs::set(bankLED, 8, LedState::OFF);
        break;
        
        case EditMenuState::EDIT:
        // Switch on EDIT and blink BANK 1-8 LEDs
        LEDs::set(editLED, LedState::ON);
        LEDs::set(bankLED, 8, LedState::BLINKING);
        break;
        
        case EditMenuState::BANK1:
        // Switch on EDIT and BANK 1 LED
        LEDs::set(editLED, LedState::ON);
        LEDs::set(bankLED, 8, LedState::OFF);
        LEDs::set(bankLED + 0, LedState::ON);
        break;
        
        case EditMenuState::BANK2:
        // Switch on EDIT and BANK 2 LED
        LEDs::set(editLED, LedState::ON);
        LEDs::set(bankLED, 8, LedState::OFF);
        LEDs::set(bankLED + 1, LedState::ON);
        break;
        
        case EditMenuState::BANK3:
        // Switch on EDIT and BANK 3 LED
        LEDs::set(editLED, LedState::ON);
        LEDs::set(bankLED, 8, LedState::OFF);
        LEDs::set(bankLED + 2, LedState::ON);
        break;
        
        case EditMenuState::BANK4:
        // Switch on EDIT and BANK 4 LED
        LEDs::set(editLED, LedState::ON);
        LEDs::set(bankLED, 8, LedState::OFF);
        LEDs::set(bankLED + 3, LedState::ON);
        break;
        
        case EditMenuState::BANK5:
        // Switch on EDIT and BANK 5 LED
        LEDs::set(editLED, LedState::ON);
        LEDs::set(bankLED, 8, LedState::OFF);
        LEDs::set(bankLED + 4, LedState::ON);
        break;
        
        case EditMenuState::BANK6:
        // Switch on EDIT and BANK 6 LED
        LEDs::set(editLED, LedState::ON);
        LEDs::set(bankLED, 8, LedState::OFF);
        LEDs::set(bankLED + 5, LedState::ON);
        break;
        
        case EditMenuState::BANK7:
        // Switch on EDIT and BANK 7 LED
        LEDs::set(editLED, LedState::ON);
        LEDs::set(bankLED, 8, LedState::OFF);
        LEDs::set(bankLED + 6, LedState::ON);
        break;
        
        case EditMenuState::BANK8:
        // Switch on EDIT and BANK 8 LED
        LEDs::set(editLED, LedState::ON);
        LEDs::set(bankLED, 8, LedState::OFF);
        LEDs::set(bankLED + 7, LedState::ON);
        break;
        
        default:
        // Switch off EDIT and BANK 1-8 LEDs
        LEDs::set(editLED, LedState::OFF);
        LEDs::set(bankLED, 8, LedState::OFF);
        break;
    }
}





void Output::handleEvent(const UiParamShowEvent& event)
{
    m_lcdStream.clear();

    visit(
    [this](const auto& param)
    {
        m_lcdStream << toString(param) << "\n"_pgm;
    },
    event.paramIdx);
    
    //m_lcdStream << showPos;
    visit(
    [this](const auto& value)
    {
        m_lcdStream << toString(value);
    },
    event.paramValue);
}

void Output::handleEvent(const UiParamChangeEvent& event)
{

}

void Output::handleEvent(const HomeScreenEvent& event)
{
}

//void Output::handleEvent(const BPMChangeEvent& data)
//{
//const uint16_t trueBpm = static_cast<uint16_t>(data.bpm) + 45;
//m_lcdStream.clear();
//m_lcdStream << "BPM "_pgm << setWidth(3) << trueBpm;
//
//// BPM clock is divided by 24 ppqn internally, i.e. BPM clock has to be trueBpm * 24 pulses/minute or (trueBpm * 24 / 60) = (trueBpm * 2 / 5) Hz
//// see datasheet for OCR1A calcuation:
//// OCR1A = (F_CPU / (2 * prescaler * F_OC1A)) - 1 = (F_CPU / (4/5 * prescaler * trueBpm)) - 1
//const uint16_t divider = static_cast<uint16_t>(static_cast<uint32_t>(F_CPU) / (256 * 4)) / trueBpm;
////InternalClockTimer::writeOCRA(5 * divider-1);
//}
