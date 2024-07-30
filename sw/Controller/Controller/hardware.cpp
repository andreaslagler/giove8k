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

//#include "hardware_def.h"

#include "hardware.h"

// Static initialization
Scheduler<function<void()>, uint8_t> Hardware::s_scheduler;
Queue<uint8_t, StaticDeque<uint8_t, 32>> Hardware::s_midiInputBuffer;
Queue<uint8_t, StaticDeque<uint8_t, 32>> Hardware::s_midiKeyboardBuffer;
//InternalClock Hardware::s_internalClock;

// ISR for ADC
void Hardware::ADConverter::handleADCInterrupt()
{
    Hardware::PotentiometerScanner::onADCInterrupt();
}

// ISR for external interrupt
void Hardware::ExtInt::handleInterrupt()
{
    disableInterrupt();
    Hardware::IntMux::onInterrupt();
}

// ISR for Rx Complete interrupt
void Hardware::MidiIO::USART::handleRXComplete()
{
    // Push received byte to Rx queue
    Hardware::s_midiInputBuffer.push(Hardware::MidiIO::get());
}

// ISR for Rx Complete interrupt
void Hardware::MidiKB::USART::handleRXComplete()
{
    // Push received byte to Rx queue
    Hardware::s_midiKeyboardBuffer.push(Hardware::MidiKB::get());
}

// ISR for scheduler timer
void Hardware::SchedulerTimer::handleOVF()
{
    Hardware::s_scheduler.clock();
}

// ISR for internal clock timer
void Hardware::InternalClockTimer::handleCOMPA()
{
    Hardware::s_bpmClockCallback();
}


void Hardware::refreshUI()
{
    // Read potentiometer values
    PotentiometerScanner::startOnce();
       
    // Refresh LEDs
    LEDs::refresh();
    
    // Refresh LCD display
    LCD::refresh();
    
    // Refresh option push buttons
    //OptionButtons::refresh();
    
    //// Clock rotary encoder
    //Encoder0::clock();

    // external UI clock callback
    s_uiClockCallback();
    
    // Re-schedule this task after 100 ms
    s_scheduler.schedule(refreshUI, 100);
}


void Hardware::init()
{   
    //////////////////////////////////////////////////////////////////////////
    // Initialize on-chip peripherals
    //////////////////////////////////////////////////////////////////////////
    
    // Initialize on-chip ADC for pot scanner use
    ADConverter::init(
    ADConverter::ReferenceSelection::AVCC, // Reference voltage = 5V
    ADConverter::PrescalerSelect::DIV_32, // Prescaler 32 is a good speed/accuracy compromise
    true, // Interrupt enabled
    false, // auto trigger off
    ADConverter::AutoTriggerSource::FREE_RUN,
    true, // ADC0 enabled
    true, // ADC1 enabled
    true, // ADC2 enabled
    true, // ADC3 enabled
    true); // ADC4 enabled

    // Initialize USART for MIDI Input/Output
    // 8n1 @ 31.25 kBaud, Rx/Tx enabled, Rx/UDRE interrupts enabled
    MidiIO::USART::init(
    F_CPU,
    31250, // MIDI baudrate 31.25 kBaud
    true,
    false,
    false,
    true,
    true,
    MidiIO::USART::Mode::ASYNC,
    MidiIO::USART::CharacterSize::_8,
    MidiIO::USART::Parity::NONE,
    MidiIO::USART::StopBits::_1,
    MidiIO::USART::ClockPolarity::OUT_RISING_IN_FALLING);
    
    // Initialize USART for MIDI Keyboard (Rx only)
    // 8n1 @ 31.25 kBaud, Rx/Tx enabled, Rx/UDRE interrupts enabled
    MidiKB::USART::init(
    F_CPU,
    31250, // MIDI baudrate 31.25 kBaud
    false,
    false,
    false,
    true,
    true,
    MidiKB::USART::Mode::ASYNC,
    MidiKB::USART::CharacterSize::_8,
    MidiKB::USART::Parity::NONE,
    MidiKB::USART::StopBits::_1,
    MidiKB::USART::ClockPolarity::OUT_RISING_IN_FALLING);
    
    // Init external interrupt to pin low since interrupt multiplexer is using inverted logic
    // Interrupt on pin low makes sure that no interrupt on the multiplexer is missed
    ExtInt::init(ExtInt::InterruptSenseControl::PIN_LOW);

    // Initialize SPI master to the maximum speed supported by all connected SPI slaves
    SPIMaster::init(
    device::SPI::ClockRate::FOSC_4,
    device::SPI::DataOrder::MSB_FIRST,
    device::SPI::ClockPolarity::LOW,
    device::SPI::ClockPhase::LEADING);
    
    // Timer for task scheduling
    SchedulerTimer::init(
    SchedulerTimer::WaveformGenerationMode::NORMAL, // Normal timer operation, i.e. PWM disabled
    SchedulerTimer::ClockSelect::PRESCALER_64, // Use a prescaler to get a suitable scheduler delay range
    SchedulerTimer::CompareOutputMode::DISCONNECTED, // PWM disabled
    SchedulerTimer::CompareOutputMode::DISCONNECTED); // PWM disabled
    SchedulerTimer::enableOverflowInterrupt(); // Enable interrupt here, so scheduler can start working immediately


    // Initialize timer for internal clock generation
    InternalClockTimer::init(
    InternalClockTimer::WaveformGenerationMode::CTC_1, // CTC timer operation with clear on OCRA match
    InternalClockTimer::ClockSelect::PRESCALER_256, // Prescaler = 64
    InternalClockTimer::CompareOutputMode::DISCONNECTED, // PWM disabled
    InternalClockTimer::CompareOutputMode::DISCONNECTED); // PWM disabled
    //InternalClockTimer::enableOutputCompareAInterrupt();
    
        //const uint16_t divider = static_cast<uint16_t>(static_cast<uint32_t>(F_CPU) / (64 * 5)) / 120;
        //InternalClockTimer::OCRA::write(divider);
        
    //////////////////////////////////////////////////////////////////////////
    // Initialize externally connected devices
    //////////////////////////////////////////////////////////////////////////

    // Slave-select multiplexer
    SSMux::init();

    // Analog multiplexer    
    AnalogMux::init();

    // Interrupt multiplexer    
    IntMuxDevice::init();

    //////////////////////////////////////////////////////////////////////////
    // Initialize UI input
    //////////////////////////////////////////////////////////////////////////
    
    // Initialize potentiometers
    PotentiometerScanner::init();

    // Port expander for step buttons
    Buttons0::init(false);
    Buttons1::init(false);
    Buttons2::init(false);
    Buttons3::init(false);

    // Port expander for option buttons
    //OptionButtons::init();
    
    // Rotary encoders
    //Encoder0::init();
            
    //////////////////////////////////////////////////////////////////////////
    // Initialize UI output
    //////////////////////////////////////////////////////////////////////////
    
    // LCD
    LCD::init();
    
    // LEDs
    LEDs::init();
    
    //////////////////////////////////////////////////////////////////////////
    // Initialize sound device
    //////////////////////////////////////////////////////////////////////////
    
    SoundDevice::init();
            
    //////////////////////////////////////////////////////////////////////////
    // Register interrupt handlers
    //////////////////////////////////////////////////////////////////////////

    // Button 0 interrupt handler uses SPI master to read MCP23XXX registers.
    // Since hardware access is not allowed inside the ISR, a corresponding task is scheduled with zero latency
    Button0InterruptPin::registerObserver(
    []{
        s_scheduler.schedule(
        [] {
            // Execute interrupt callback
            Buttons0::onInterrupt();
            
            // Re-arm after 10ms
            s_scheduler.schedule([]{Buttons0::reArmInterrupt(); ExtInt::enableInterrupt();}, 10);
        }, 0);
    });
        
    // Button 1 interrupt handler uses SPI master to read MCP23XXX registers.
    // Since hardware access is not allowed inside the ISR, a corresponding task is scheduled with zero latency
    Button1InterruptPin::registerObserver(
    []{
        s_scheduler.schedule(
        [] {
            // Execute interrupt callback
            Buttons1::onInterrupt();
            
            // Re-arm after 10ms
            s_scheduler.schedule([]{Buttons1::reArmInterrupt(); ExtInt::enableInterrupt();}, 10);
        }, 0);
    });
    
    // Button 2 interrupt handler uses SPI master to read MCP23XXX registers.
    // Since hardware access is not allowed inside the ISR, a corresponding task is scheduled with zero latency
    Button2InterruptPin::registerObserver(
    []{
        s_scheduler.schedule(
        [] {
            // Execute interrupt callback
            Buttons2::onInterrupt();
            
            // Re-arm after 10ms
            s_scheduler.schedule([]{Buttons2::reArmInterrupt(); ExtInt::enableInterrupt();}, 10);
        }, 0);
    });
    
    // Button 3 interrupt handler uses SPI master to read MCP23XXX registers.
    // Since hardware access is not allowed inside the ISR, a corresponding task is scheduled with zero latency
    Button3InterruptPin::registerObserver(
    []{
        s_scheduler.schedule(
        [] {
            // Execute interrupt callback
            Buttons3::onInterrupt();
            
            // Re-arm after 10ms
            s_scheduler.schedule([]{Buttons3::reArmInterrupt(); ExtInt::enableInterrupt();}, 10);
        }, 0);
    });
    
    
    // When everything is set up, refresh the user interface. This will also initiate the refresh cycle
    refreshUI();    
}


function<void()> Hardware::s_uiClockCallback;
function<void()> Hardware::s_bpmClockCallback;