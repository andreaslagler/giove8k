/*
Copyright (C) 2020 Andreas Lagler

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

#ifndef MAIN_BOARD_H
#define MAIN_BOARD_H

// ATMega328P is running at 20 MHz
#define F_CPU 20000000UL

#include "m328p_GPIO.h"
#include "m328p_SPI.h"
#include "m328p_ADC.h"
#include "m328p_USART0.h"
#include "m328p_Int0.h"
#include "m328p_Int1.h"
#include "m328p_Timer0.h"
#include "m328p_EEPROM.h"
#include "m328p_Atomic.h"

#include "74HC138.h"
#include "mux_output_pin.h"
#include "spi_master.h"

/**
@brief Hardware specifics of ATmega328p mainboard rev 1.
This board is running an ATmega328p-PU @20MHz/5VDC and has connectivity for following peripherals
- 8x SPI output with multiplexed SS pins via on-board 74HC138 multiplexer
- 6x Analog input with 8x multiplexer channel selection pins connected to pin headers allowing a total of 48 potentiometers
- USART Rx/Tx
- 2x External interrupt pins
- External clock via GP I/O pin
- 2x Auxiliary I/O pins
*/
class MainBoard
{
    public:

    // USART 0 Tx and Rx pins are available
    typedef m328p::USART0 USART;

    private:

    // 3 to 8 Line Multiplexer for SPI Slave Select pin hooked to PD7:5
    typedef _74HC138<m328p::GPIOSubPort<m328p::Port::D, PORTD5, PORTD7>> SSMux;

    protected:
    
    // SPI can only be used in master mode because of the connected SS pin multiplexer
    typedef SPIMasterSync<m328p::SPI> SPIMaster;

    // Multiplexed SS pins
    typedef MuxPin<SSMux, SPIMaster::SS_Pin, 0> SS0Pin;
    typedef MuxPin<SSMux, SPIMaster::SS_Pin, 1> SS1Pin;
    typedef MuxPin<SSMux, SPIMaster::SS_Pin, 2> SS2Pin;
    typedef MuxPin<SSMux, SPIMaster::SS_Pin, 3> SS3Pin;
    typedef MuxPin<SSMux, SPIMaster::SS_Pin, 4> SS4Pin;
    typedef MuxPin<SSMux, SPIMaster::SS_Pin, 5> SS5Pin;
    typedef MuxPin<SSMux, SPIMaster::SS_Pin, 6> SS6Pin;
    typedef MuxPin<SSMux, SPIMaster::SS_Pin, 7> SS7Pin;

    // ADC
    typedef m328p::ADConverter ADConverter;
    typedef ADConverter::Pin<0> ADC0_Pin;
    typedef ADConverter::Pin<1> ADC1_Pin;
    typedef ADConverter::Pin<2> ADC2_Pin;
    typedef ADConverter::Pin<3> ADC3_Pin;
    typedef ADConverter::Pin<4> ADC4_Pin;
    typedef ADConverter::Pin<5> ADC5_Pin;
    
    // Analog multiplexer(s) also hooked to PD7:5. In total, 48 analog input pins are available
    // Note: ADC and SPI cannot be used at the same time, because analog mux and SS mux are driven by the same GP I/O pins
    typedef m328p::GPIOSubPort<m328p::Port::D, PORTD5, PORTD7> AnalogMuxPort;

    // Two AUX pins hooked to PB1:0
    typedef m328p::GPIOPin<m328p::Port::B, PORTB0> SyncOutClk_Pin;
    typedef m328p::GPIOPin<m328p::Port::B, PORTB1> SyncOutStart_Pin;

    // Third AUX pin hooked to PD4
    typedef m328p::GPIOPin<m328p::Port::D, PORTD4> SyncInClk_Pin;

    // External interrupts
    typedef m328p::Int0 Int0;
    typedef m328p::Int1 Int1;
    
    // Timer
    typedef m328p::Timer0 Timer0;

    // EEPROM
    typedef m328p::EEPROM EEPROM;

    // Atomic class
    typedef m328p::Atomic Atomic;
    
    static void init()
    {
        SyncOutClk_Pin::setAsOutput();
        SyncOutStart_Pin::setAsOutput();
        SyncInClk_Pin::setAsInput();
        
        SSMux::init();
    }
};

#endif