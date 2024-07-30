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

#ifndef HARDWARE_H
#define HARDWARE_H

// ATMega1284P is running at 20 MHz
#define F_CPU 20000000UL

#define TEST_BOARD

#include "m1284p_ADC.h"
#include "m1284p_Int0.h"
#include "m1284p_SPI.h"
#include "m1284p_Timer0.h"
#include "m1284p_Timer1.h"
#include "m1284p_USART0.h"
#include "m1284p_USART1.h"

#include "analog_multiplexer.h"
#include "buffered_leds.h"
#include "buffered_lcd.h"
#include "buffered_usart.h"
#include "dsp.h"
#include "HD44780.h"
#include "internal_clock.h"
#include "line_decoder.h"
#include "line_encoder.h"
#include "MCP23S17.h"
#include "midi_input.h"
#include "mux_adc_pin.h"
#include "mux_interrupt_pin.h"
#include "mux_output_pin.h"
#include "potentiometer.h"
#include "potentiometer_scanner.h"
#include "rotary_encoder.h"
#include "shift_register.h"
#include "spi_master.h"
//#include "static_buttons.h"

#include <scheduler.h>

// Alias for the used device
namespace device = m1284p;

class Hardware
{
    protected:
    
    static void init();
    static bool s_init;
    static Scheduler<function<void()>, uint8_t> s_scheduler;
    
    static void doEvents()
    {
        // Check for tasks to execute
        s_scheduler.execute();
    }
    
    static function<void()> s_uiClockCallback;
    static function<void()> s_bpmClockCallback;

    static Queue<uint8_t, StaticDeque<uint8_t, 32>> s_midiInputBuffer;
    static Queue<uint8_t, StaticDeque<uint8_t, 32>> s_midiKeyboardBuffer;
    
    static void refreshUI();
    
    //static constexpr void handleClockEvent()
    //{
    //HardwareEvent event;
    //event.type = HardwareEventType::Clock;
    //s_eventQueue.push(event);
    //}
    
    //////////////////////////////////////////////////////////////////////////
    // On-chip peripherals
    //////////////////////////////////////////////////////////////////////////
    
    // USART
    friend class device::USART0;
    using MidiIO = BufferedUSART<device::USART0, 6>;
    
    friend class device::USART1;
    using MidiKB = BufferedUSART<device::USART1, 6>;
    
    // ADC
    friend class device::ADConverter;
    using ADConverter = device::ADConverter;

    // SPI
    using SPIMaster = SPIMasterSync<device::SPI>;

    // Timer 0 for task scheduling
    friend class device::Timer0;
    using SchedulerTimer = device::Timer0;

    // Timer 1 for internal clock generation
    friend class device::Timer1;
    using InternalClockTimer = device::Timer1;

    // External interrupt
    friend class device::Int0;
    using ExtInt = device::Int0;
    
    //////////////////////////////////////////////////////////////////////////
    // Externally connected devices
    //////////////////////////////////////////////////////////////////////////
    
    // Analog multiplexer(s) hooked to PC6:4. In total, 64 analog input pins are available
    using AnalogMux = AnalogMultiplexer<device::GPIOSubPort<device::Port::C, 4, 6>>;

    // Line Decoder for SPI Slave Select pin hooked to PD7:4
    using SSMux = LineDecoder<device::GPIOSubPort<device::Port::D, 4, 7>>;
    using SSLCDPin = MuxPin<SSMux, SPIMaster::SS_Pin, 0>;
    using SSButtons0Pin = MuxPin<SSMux, SPIMaster::SS_Pin, 1>;
    using SSButtons1Pin = MuxPin<SSMux, SPIMaster::SS_Pin, 2>;
    using SSButtons2Pin = MuxPin<SSMux, SPIMaster::SS_Pin, 3>;
    using SSButtons3Pin = MuxPin<SSMux, SPIMaster::SS_Pin, 4>;
    using SSOptionButtonsPin = MuxPin<SSMux, SPIMaster::SS_Pin, 5>;
    using SSLEDsPin = MuxPin<SSMux, SPIMaster::SS_Pin, 6>;
    using SSDSPPin = MuxPin<SSMux, SPIMaster::SS_Pin, 7>;

    // Interrupt multiplexer for ExtInt hooked to PC2:0
    using IntMuxDevice = LineEncoder<device::GPIOSubPort<device::Port::C, 0, 2>>;
    using IntMux = InterruptMux <IntMuxDevice, 0, 1, 2, 3>;
    using Button0InterruptPin = MuxInterruptPin<IntMux, 0>;
    using Button1InterruptPin = MuxInterruptPin<IntMux, 1>;
    using Button2InterruptPin = MuxInterruptPin<IntMux, 2>;
    using Button3InterruptPin = MuxInterruptPin<IntMux, 3>;
    
    //////////////////////////////////////////////////////////////////////////
    // UI input
    //////////////////////////////////////////////////////////////////////////
    
    // Potentiometers connected to ADC pin 0 via octal analog multiplexer
    using ADC0_Pin = ADConverter::Pin<0>;
    using Potentiometer00 = Potentiometer<MuxADCPin<ADC0_Pin, AnalogMux, 0>>;
    using Potentiometer01 = Potentiometer<MuxADCPin<ADC0_Pin, AnalogMux, 1>>;
    using Potentiometer02 = Potentiometer<MuxADCPin<ADC0_Pin, AnalogMux, 2>>;
    using Potentiometer03 = Potentiometer<MuxADCPin<ADC0_Pin, AnalogMux, 3>>;
    using Potentiometer04 = Potentiometer<MuxADCPin<ADC0_Pin, AnalogMux, 4>>;
    using Potentiometer05 = Potentiometer<MuxADCPin<ADC0_Pin, AnalogMux, 5>>;
    using Potentiometer06 = Potentiometer<MuxADCPin<ADC0_Pin, AnalogMux, 6>>;
    using Potentiometer07 = Potentiometer<MuxADCPin<ADC0_Pin, AnalogMux, 7>>;

    // Potentiometers connected to ADC pin 1 via octal analog multiplexer
    using ADC1_Pin = ADConverter::Pin<1>;
    using Potentiometer10 = Potentiometer<MuxADCPin<ADC1_Pin, AnalogMux, 0>>;
    using Potentiometer11 = Potentiometer<MuxADCPin<ADC1_Pin, AnalogMux, 1>>;
    using Potentiometer12 = Potentiometer<MuxADCPin<ADC1_Pin, AnalogMux, 2>>;
    using Potentiometer13 = Potentiometer<MuxADCPin<ADC1_Pin, AnalogMux, 3>>;
    using Potentiometer14 = Potentiometer<MuxADCPin<ADC1_Pin, AnalogMux, 4>>;
    using Potentiometer15 = Potentiometer<MuxADCPin<ADC1_Pin, AnalogMux, 5>>;
    using Potentiometer16 = Potentiometer<MuxADCPin<ADC1_Pin, AnalogMux, 6>>;
    using Potentiometer17 = Potentiometer<MuxADCPin<ADC1_Pin, AnalogMux, 7>>;

    // Potentiometers connected to ADC pin 2 via octal analog multiplexer
    using ADC2_Pin = ADConverter::Pin<2>;
    using Potentiometer20 = Potentiometer<MuxADCPin<ADC2_Pin, AnalogMux, 0>>;
    using Potentiometer21 = Potentiometer<MuxADCPin<ADC2_Pin, AnalogMux, 1>>;
    using Potentiometer22 = Potentiometer<MuxADCPin<ADC2_Pin, AnalogMux, 2>>;
    using Potentiometer23 = Potentiometer<MuxADCPin<ADC2_Pin, AnalogMux, 3>>;
    using Potentiometer24 = Potentiometer<MuxADCPin<ADC2_Pin, AnalogMux, 4>>;
    using Potentiometer25 = Potentiometer<MuxADCPin<ADC2_Pin, AnalogMux, 5>>;
    using Potentiometer26 = Potentiometer<MuxADCPin<ADC2_Pin, AnalogMux, 6>>;
    using Potentiometer27 = Potentiometer<MuxADCPin<ADC2_Pin, AnalogMux, 7>>;

    // Potentiometers connected to ADC pin 3 via octal analog multiplexer
    using ADC3_Pin = ADConverter::Pin<3>;
    using Potentiometer30 = Potentiometer<MuxADCPin<ADC3_Pin, AnalogMux, 0>>;
    using Potentiometer31 = Potentiometer<MuxADCPin<ADC3_Pin, AnalogMux, 1>>;
    using Potentiometer32 = Potentiometer<MuxADCPin<ADC3_Pin, AnalogMux, 2>>;
    using Potentiometer33 = Potentiometer<MuxADCPin<ADC3_Pin, AnalogMux, 3>>;
    using Potentiometer34 = Potentiometer<MuxADCPin<ADC3_Pin, AnalogMux, 4>>;
    using Potentiometer35 = Potentiometer<MuxADCPin<ADC3_Pin, AnalogMux, 5>>;
    using Potentiometer36 = Potentiometer<MuxADCPin<ADC3_Pin, AnalogMux, 6>>;
    using Potentiometer37 = Potentiometer<MuxADCPin<ADC3_Pin, AnalogMux, 7>>;

    // Potentiometers connected to ADC pin 4 via octal analog multiplexer
    using ADC4_Pin = ADConverter::Pin<4>;
    using Potentiometer40 = Potentiometer<MuxADCPin<ADC4_Pin, AnalogMux, 0>>;
    using Potentiometer41 = Potentiometer<MuxADCPin<ADC4_Pin, AnalogMux, 1>>;
    using Potentiometer42 = Potentiometer<MuxADCPin<ADC4_Pin, AnalogMux, 2>>;
    using Potentiometer43 = Potentiometer<MuxADCPin<ADC4_Pin, AnalogMux, 3>>;
    using Potentiometer44 = Potentiometer<MuxADCPin<ADC4_Pin, AnalogMux, 4>>;
    using Potentiometer45 = Potentiometer<MuxADCPin<ADC4_Pin, AnalogMux, 5>>;
    using Potentiometer46 = Potentiometer<MuxADCPin<ADC4_Pin, AnalogMux, 6>>;
    using Potentiometer47 = Potentiometer<MuxADCPin<ADC4_Pin, AnalogMux, 7>>;


    // All potentiometers are read out by a potentiometer scanner
    using PotentiometerScanner = PotentiometerScannerAsync<
    Potentiometer00,
    Potentiometer01,
    Potentiometer02,
    Potentiometer03,
    Potentiometer04,
    Potentiometer05,
    Potentiometer06,
    Potentiometer07,
    Potentiometer10,
    Potentiometer11,
    Potentiometer12,
    Potentiometer13,
    Potentiometer14,
    Potentiometer15,
    Potentiometer16,
    Potentiometer17,
    Potentiometer20,
    Potentiometer21,
    Potentiometer22,
    Potentiometer23,
    Potentiometer24,
    Potentiometer25,
    Potentiometer26,
    Potentiometer27,
    Potentiometer30,
    Potentiometer31,
    Potentiometer32,
    Potentiometer33,
    Potentiometer34,
    Potentiometer35,
    Potentiometer36,
    Potentiometer37,
    Potentiometer40,
    Potentiometer41,
    Potentiometer42,
    Potentiometer43,
    Potentiometer44,
    Potentiometer45,
    Potentiometer46,
    Potentiometer47
    >;
    
    // 16 Step buttons connected to MCP23S17 port expander
    using Buttons0 = MCP23S17<
    SPIMaster,
    SSButtons0Pin,
    MCP23S17PinConfig<MCP23S17PinIdx::A0, MCP23xxxPinType::SWITCH>,
    MCP23S17PinConfig<MCP23S17PinIdx::A1, MCP23xxxPinType::SWITCH>,
    MCP23S17PinConfig<MCP23S17PinIdx::A2, MCP23xxxPinType::SWITCH>,
    MCP23S17PinConfig<MCP23S17PinIdx::A3, MCP23xxxPinType::SWITCH>,
    MCP23S17PinConfig<MCP23S17PinIdx::A4, MCP23xxxPinType::SWITCH>,
    MCP23S17PinConfig<MCP23S17PinIdx::A5, MCP23xxxPinType::SWITCH>,
    MCP23S17PinConfig<MCP23S17PinIdx::A6, MCP23xxxPinType::SWITCH>,
    MCP23S17PinConfig<MCP23S17PinIdx::A7, MCP23xxxPinType::SWITCH>,
    MCP23S17PinConfig<MCP23S17PinIdx::B0, MCP23xxxPinType::SWITCH>,
    MCP23S17PinConfig<MCP23S17PinIdx::B1, MCP23xxxPinType::SWITCH>,
    MCP23S17PinConfig<MCP23S17PinIdx::B2, MCP23xxxPinType::SWITCH_TOGGLE>,
    MCP23S17PinConfig<MCP23S17PinIdx::B3, MCP23xxxPinType::SWITCH_TOGGLE>,
    MCP23S17PinConfig<MCP23S17PinIdx::B4, MCP23xxxPinType::SWITCH>,
    MCP23S17PinConfig<MCP23S17PinIdx::B5, MCP23xxxPinType::SWITCH>,
    MCP23S17PinConfig<MCP23S17PinIdx::B6, MCP23xxxPinType::SWITCH>,
    MCP23S17PinConfig<MCP23S17PinIdx::B7, MCP23xxxPinType::SWITCH>
    >;

    using Button000 = Buttons0::Pin<MCP23S17PinIdx::A0>;
    using Button001 = Buttons0::Pin<MCP23S17PinIdx::A1>;
    using Button002 = Buttons0::Pin<MCP23S17PinIdx::A2>;
    using Button003 = Buttons0::Pin<MCP23S17PinIdx::A3>;
    using Button004 = Buttons0::Pin<MCP23S17PinIdx::A4>;
    using Button005 = Buttons0::Pin<MCP23S17PinIdx::A5>;
    using Button006 = Buttons0::Pin<MCP23S17PinIdx::A6>;
    using Button007 = Buttons0::Pin<MCP23S17PinIdx::A7>;
    using Button008 = Buttons0::Pin<MCP23S17PinIdx::B0>;
    using Button009 = Buttons0::Pin<MCP23S17PinIdx::B1>;
    using Button010 = Buttons0::Pin<MCP23S17PinIdx::B2>;
    using Button011 = Buttons0::Pin<MCP23S17PinIdx::B3>;
    using Button012 = Buttons0::Pin<MCP23S17PinIdx::B4>;
    using Button013 = Buttons0::Pin<MCP23S17PinIdx::B5>;
    using Button014 = Buttons0::Pin<MCP23S17PinIdx::B6>;
    using Button015 = Buttons0::Pin<MCP23S17PinIdx::B7>;
    

    // 16 Step buttons connected to MCP23S17 port expander
    using Buttons1 = MCP23S17<
    SPIMaster,
    SSButtons1Pin,
    MCP23S17PinConfig<MCP23S17PinIdx::A0, MCP23xxxPinType::SWITCH>,
    MCP23S17PinConfig<MCP23S17PinIdx::A1, MCP23xxxPinType::SWITCH>,
    MCP23S17PinConfig<MCP23S17PinIdx::A2, MCP23xxxPinType::SWITCH>,
    MCP23S17PinConfig<MCP23S17PinIdx::A3, MCP23xxxPinType::SWITCH>,
    MCP23S17PinConfig<MCP23S17PinIdx::A4, MCP23xxxPinType::SWITCH>,
    MCP23S17PinConfig<MCP23S17PinIdx::A5, MCP23xxxPinType::SWITCH>,
    MCP23S17PinConfig<MCP23S17PinIdx::A6, MCP23xxxPinType::SWITCH>,
    MCP23S17PinConfig<MCP23S17PinIdx::A7, MCP23xxxPinType::SWITCH>,
    MCP23S17PinConfig<MCP23S17PinIdx::B0, MCP23xxxPinType::SWITCH>,
    MCP23S17PinConfig<MCP23S17PinIdx::B1, MCP23xxxPinType::SWITCH>,
    MCP23S17PinConfig<MCP23S17PinIdx::B2, MCP23xxxPinType::SWITCH>,
    MCP23S17PinConfig<MCP23S17PinIdx::B3, MCP23xxxPinType::SWITCH>,
    MCP23S17PinConfig<MCP23S17PinIdx::B4, MCP23xxxPinType::SWITCH>,
    MCP23S17PinConfig<MCP23S17PinIdx::B5, MCP23xxxPinType::SWITCH>,
    MCP23S17PinConfig<MCP23S17PinIdx::B6, MCP23xxxPinType::SWITCH>,
    MCP23S17PinConfig<MCP23S17PinIdx::B7, MCP23xxxPinType::SWITCH>
    >;

    using Button100 = Buttons1::Pin<MCP23S17PinIdx::A0>;
    using Button101 = Buttons1::Pin<MCP23S17PinIdx::A1>;
    using Button102 = Buttons1::Pin<MCP23S17PinIdx::A2>;
    using Button103 = Buttons1::Pin<MCP23S17PinIdx::A3>;
    using Button104 = Buttons1::Pin<MCP23S17PinIdx::A4>;
    using Button105 = Buttons1::Pin<MCP23S17PinIdx::A5>;
    using Button106 = Buttons1::Pin<MCP23S17PinIdx::A6>;
    using Button107 = Buttons1::Pin<MCP23S17PinIdx::A7>;
    using Button108 = Buttons1::Pin<MCP23S17PinIdx::B0>;
    using Button109 = Buttons1::Pin<MCP23S17PinIdx::B1>;
    using Button110 = Buttons1::Pin<MCP23S17PinIdx::B2>;
    using Button111 = Buttons1::Pin<MCP23S17PinIdx::B3>;
    using Button112 = Buttons1::Pin<MCP23S17PinIdx::B4>;
    using Button113 = Buttons1::Pin<MCP23S17PinIdx::B5>;
    using Button114 = Buttons1::Pin<MCP23S17PinIdx::B6>;
    using Button115 = Buttons1::Pin<MCP23S17PinIdx::B7>;

    // 16 Step buttons connected to MCP23S17 port expander
    using Buttons2 = MCP23S17<
    SPIMaster,
    SSButtons2Pin,
    MCP23S17PinConfig<MCP23S17PinIdx::A0, MCP23xxxPinType::SWITCH>,
    MCP23S17PinConfig<MCP23S17PinIdx::A1, MCP23xxxPinType::SWITCH>,
    MCP23S17PinConfig<MCP23S17PinIdx::A2, MCP23xxxPinType::SWITCH>,
    MCP23S17PinConfig<MCP23S17PinIdx::A3, MCP23xxxPinType::SWITCH>,
    MCP23S17PinConfig<MCP23S17PinIdx::A4, MCP23xxxPinType::SWITCH>,
    MCP23S17PinConfig<MCP23S17PinIdx::A5, MCP23xxxPinType::SWITCH>,
    MCP23S17PinConfig<MCP23S17PinIdx::A6, MCP23xxxPinType::SWITCH>,
    MCP23S17PinConfig<MCP23S17PinIdx::A7, MCP23xxxPinType::SWITCH>,
    MCP23S17PinConfig<MCP23S17PinIdx::B0, MCP23xxxPinType::SWITCH>,
    MCP23S17PinConfig<MCP23S17PinIdx::B1, MCP23xxxPinType::SWITCH>,
    MCP23S17PinConfig<MCP23S17PinIdx::B2, MCP23xxxPinType::SWITCH>,
    MCP23S17PinConfig<MCP23S17PinIdx::B3, MCP23xxxPinType::SWITCH>,
    MCP23S17PinConfig<MCP23S17PinIdx::B4, MCP23xxxPinType::SWITCH>,
    MCP23S17PinConfig<MCP23S17PinIdx::B5, MCP23xxxPinType::SWITCH>,
    MCP23S17PinConfig<MCP23S17PinIdx::B6, MCP23xxxPinType::SWITCH>,
    MCP23S17PinConfig<MCP23S17PinIdx::B7, MCP23xxxPinType::SWITCH>
    >;

    using Button200 = Buttons2::Pin<MCP23S17PinIdx::A0>;
    using Button201 = Buttons2::Pin<MCP23S17PinIdx::A1>;
    using Button202 = Buttons2::Pin<MCP23S17PinIdx::A2>;
    using Button203 = Buttons2::Pin<MCP23S17PinIdx::A3>;
    using Button204 = Buttons2::Pin<MCP23S17PinIdx::A4>;
    using Button205 = Buttons2::Pin<MCP23S17PinIdx::A5>;
    using Button206 = Buttons2::Pin<MCP23S17PinIdx::A6>;
    using Button207 = Buttons2::Pin<MCP23S17PinIdx::A7>;
    using Button208 = Buttons2::Pin<MCP23S17PinIdx::B0>;
    using Button209 = Buttons2::Pin<MCP23S17PinIdx::B1>;
    using Button210 = Buttons2::Pin<MCP23S17PinIdx::B2>;
    using Button211 = Buttons2::Pin<MCP23S17PinIdx::B3>;
    using Button212 = Buttons2::Pin<MCP23S17PinIdx::B4>;
    using Button213 = Buttons2::Pin<MCP23S17PinIdx::B5>;
    using Button214 = Buttons2::Pin<MCP23S17PinIdx::B6>;
    using Button215 = Buttons2::Pin<MCP23S17PinIdx::B7>;


    // 14 buttons and 1 rotary encoder connected to MCP23S17 port expander
    using Buttons3 = MCP23S17<
    SPIMaster,
    SSButtons3Pin,
    MCP23S17PinConfig<MCP23S17PinIdx::A0, MCP23xxxPinType::SWITCH>,
    MCP23S17PinConfig<MCP23S17PinIdx::A1, MCP23xxxPinType::SWITCH>,
    MCP23S17PinConfig<MCP23S17PinIdx::A2, MCP23xxxPinType::SWITCH>,
    MCP23S17PinConfig<MCP23S17PinIdx::A3, MCP23xxxPinType::SWITCH>,
    MCP23S17PinConfig<MCP23S17PinIdx::A4, MCP23xxxPinType::SWITCH>,
    MCP23S17PinConfig<MCP23S17PinIdx::A5, MCP23xxxPinType::SWITCH>,
    MCP23S17PinConfig<MCP23S17PinIdx::A6, MCP23xxxPinType::SWITCH>,
    MCP23S17PinConfig<MCP23S17PinIdx::A7, MCP23xxxPinType::SWITCH>,
    MCP23S17PinConfig<MCP23S17PinIdx::B0, MCP23xxxPinType::ROTENC_PHASE_A>,
    MCP23S17PinConfig<MCP23S17PinIdx::B1, MCP23xxxPinType::SWITCH>,
    MCP23S17PinConfig<MCP23S17PinIdx::B2, MCP23xxxPinType::SWITCH>,
    MCP23S17PinConfig<MCP23S17PinIdx::B3, MCP23xxxPinType::SWITCH>,
    MCP23S17PinConfig<MCP23S17PinIdx::B7, MCP23xxxPinType::ROTENC_PHASE_B>,
    MCP23S17PinConfig<MCP23S17PinIdx::B6, MCP23xxxPinType::SWITCH>,
    MCP23S17PinConfig<MCP23S17PinIdx::B5, MCP23xxxPinType::SWITCH>,
    MCP23S17PinConfig<MCP23S17PinIdx::B4, MCP23xxxPinType::SWITCH>
    >;
    
    using Button300 = Buttons3::Pin<MCP23S17PinIdx::A0>;
    using Button301 = Buttons3::Pin<MCP23S17PinIdx::A1>;
    using Button302 = Buttons3::Pin<MCP23S17PinIdx::A2>;
    using Button303 = Buttons3::Pin<MCP23S17PinIdx::A3>;
    using Button304 = Buttons3::Pin<MCP23S17PinIdx::A4>;
    using Button305 = Buttons3::Pin<MCP23S17PinIdx::A5>;
    using Button306 = Buttons3::Pin<MCP23S17PinIdx::A6>;
    using Button307 = Buttons3::Pin<MCP23S17PinIdx::A7>;
    using Button308 = Buttons3::Pin<MCP23S17PinIdx::B1>;
    using Button309 = Buttons3::Pin<MCP23S17PinIdx::B2>;
    using Button310 = Buttons3::Pin<MCP23S17PinIdx::B3>;
    using Button311 = Buttons3::Pin<MCP23S17PinIdx::B4>;
    using Button312 = Buttons3::Pin<MCP23S17PinIdx::B5>;
    using Button313 = Buttons3::Pin<MCP23S17PinIdx::B6>;


    //////////////////////////////////////////////////////////////////////////
    // UI output
    //////////////////////////////////////////////////////////////////////////
    
    // 2x16 alphanumeric LCD connected to shift register driven via SPI
    using LCDPort = HD44780_Configuration_74HC595<SPIMaster, SSLCDPin>;
    using LCD = LCDAlphanumericBuffered<HD44780<HD44780_NofCharacters::_2x16, LCDPort>>;

    // 64 LEDs connected to shift registers driven via SPI
    static constexpr uint8_t nofLEDs = 75;
    static constexpr uint8_t s_nofLEDBytes = nofLEDs / 8 + (((nofLEDs % 8) > 0) ? 1 : 0);
    using LEDPort = ShiftRegister<SPIMaster, SSLEDsPin, s_nofLEDBytes>;
    using LEDs = BufferedLeds<LEDPort, nofLEDs>;
    
    //////////////////////////////////////////////////////////////////////////
    // Sound output
    //////////////////////////////////////////////////////////////////////////
    
    // WaveBlaster device connected to SPI via SPI bridge
    using SoundDevice = DSP<SPIMaster, SSDSPPin>;
};

#endif