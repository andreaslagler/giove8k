#ifndef HARDWARE_DEF_H
#define HARDWARE_DEF_H

// ATMega328P is running at 20 MHz
#define F_CPU 20000000UL

// This header defines the use of peripherals and devices connected to the ATMega328P brain
#include "m328p_GPIO.h"
#include "m328p_SPI.h"
#include "m328p_ADC.h"
#include "m328p_USART0.h"
#include "m328p_Int0.h"
#include "m328p_Int1.h"
#include "m328p_Timer0.h"
#include "m328p_EEPROM.h"
#include "m328p_Atomic.h"
#include "HD44780.h"
#include "MCP23S17.h"
#include "74HC138.h"
#include "74HC595.h"
#include "74HC4051.h"
#include "DSPIC33.h"
#include "25LC512.h"
#include "spi_master.h"
#include "mux_output_pin.h"
#include "mux_analog_pin.h"
#include "potentiometer.h"
#include "potentiometer_scanner.h"
#include "rotary_encoder.h"
#include "buffered_lcd.h"
#include "buffered_usart.h"
#include "memory_slice.h"
#include "tic_toc.h"

class Hardware
{
    // Analog multiplexer(s) also hooked to PD7:5. In total, 48 analog input pins are available
    // Note: ADC and SPI cannot be used at the same time, because analog mux and SS mux are driven by the same GP I/O pins
    typedef _74HC4051<m328p::GPIOSubPort<m328p::Port::D, PORTD5, PORTD7>> AnalogMux;

    // ADC
    typedef m328p::ADConverter ADConverter;
    typedef ADConverter::Pin<0> ADC0_Pin;
    typedef ADConverter::Pin<1> ADC1_Pin;
    typedef ADConverter::Pin<2> ADC2_Pin;
    typedef ADConverter::Pin<3> ADC3_Pin;
    typedef ADConverter::Pin<4> ADC4_Pin;

    // SPI can only be used in master mode because of the connected SS pin multiplexer
    typedef SPIMasterSync<m328p::SPI> SPIMaster;

    // 3 to 8 Line Multiplexer for SPI Slave Select pin hooked to PD7:5
    // Note: ADC and SPI cannot be used at the same time, because analog mux and SS mux are driven by the same GP I/O pins
    typedef _74HC138<m328p::GPIOSubPort<m328p::Port::D, PORTD5, PORTD7>> SSMux;

    // Multiplexed SS pins
    typedef MuxPin<SSMux, SPIMaster::SS_Pin, 0> SSLCDPin;
    typedef MuxPin<SSMux, SPIMaster::SS_Pin, 1> SSLEDPin;
    typedef MuxPin<SSMux, SPIMaster::SS_Pin, 2> SSSerialIO0Pin;
    typedef MuxPin<SSMux, SPIMaster::SS_Pin, 3> SSSerialIO1Pin;
    typedef MuxPin<SSMux, SPIMaster::SS_Pin, 4> SSDSPPin;
    typedef MuxPin<SSMux, SPIMaster::SS_Pin, 5> SSMemory0Pin;
    typedef MuxPin<SSMux, SPIMaster::SS_Pin, 6> SSMemory1Pin;
    typedef MuxPin<SSMux, SPIMaster::SS_Pin, 7> SSMemory2Pin;

    // LCD Port
    typedef HD44780_Configuration_74HC595<
    SPIMaster, // LCD uses SPI
    SSLCDPin // connected to Slave Select 0
    > LCDPort;

    public:

    // USART
    typedef BufferedUSART<m328p::USART0, 6> MidiIO;

    // LCD
    typedef LCDAlphanumericBuffered<HD44780<HD44780_NofCharacters::_2x16, LCDPort>> LCD; // 2x16 display using LCD port defined above

    // LEDs
    typedef _74HC595<SPIMaster, SSLEDPin, 6> LED;

    // Potentiometers
    typedef Potentiometer<MuxAnalogPin<MainBoard::ADC0_Pin, AnalogMux, 0>, Detent::DETENT_CENTER> PotentiometerOsc1Pitch;
    typedef Potentiometer<MuxAnalogPin<MainBoard::ADC0_Pin, AnalogMux, 1>, Detent::DETENT_CENTER> PotentiometerOsc1Detune;
    typedef Potentiometer<MuxAnalogPin<MainBoard::ADC0_Pin, AnalogMux, 2>> PotentiometerOsc1Shape1;
    typedef Potentiometer<MuxAnalogPin<MainBoard::ADC0_Pin, AnalogMux, 3>> PotentiometerOsc1Shape2;
    typedef Potentiometer<MuxAnalogPin<MainBoard::ADC0_Pin, AnalogMux, 4>, Detent::DETENT_CENTER> PotentiometerOsc2Pitch;
    typedef Potentiometer<MuxAnalogPin<MainBoard::ADC0_Pin, AnalogMux, 5>, Detent::DETENT_CENTER> PotentiometerOsc2Detune;
    typedef Potentiometer<MuxAnalogPin<MainBoard::ADC0_Pin, AnalogMux, 6>> PotentiometerOsc2Shape;
    typedef Potentiometer<MuxAnalogPin<MainBoard::ADC0_Pin, AnalogMux, 7>> PotentiometerOscSyncPhase;
    typedef Potentiometer<MuxAnalogPin<MainBoard::ADC1_Pin, AnalogMux, 0>, Detent::DETENT_CENTER> PotentiometerOscBalance;
    typedef Potentiometer<MuxAnalogPin<MainBoard::ADC1_Pin, AnalogMux, 1>> PotentiometerOscRingModAmount;
    typedef Potentiometer<MuxAnalogPin<MainBoard::ADC1_Pin, AnalogMux, 2>> PotentiometerOscCrossModAmount;
    typedef Potentiometer<MuxAnalogPin<MainBoard::ADC1_Pin, AnalogMux, 3>> PotentiometerFilterFreq;
    typedef Potentiometer<MuxAnalogPin<MainBoard::ADC1_Pin, AnalogMux, 4>> PotentiometerFilterShape;
    typedef Potentiometer<MuxAnalogPin<MainBoard::ADC1_Pin, AnalogMux, 5>, Detent::DETENT_CENTER> PotentiometerFilterEnvAmount;
    typedef Potentiometer<MuxAnalogPin<MainBoard::ADC1_Pin, AnalogMux, 6>, Detent::DETENT_CENTER> PotentiometerFilterKeyTrack;
    typedef Potentiometer<MuxAnalogPin<MainBoard::ADC1_Pin, AnalogMux, 7>> PotentiometerFilterEnvAttack;
    typedef Potentiometer<MuxAnalogPin<MainBoard::ADC2_Pin, AnalogMux, 0>> PotentiometerFilterEnvDecay;
    typedef Potentiometer<MuxAnalogPin<MainBoard::ADC2_Pin, AnalogMux, 1>> PotentiometerFilterEnvSustain;
    typedef Potentiometer<MuxAnalogPin<MainBoard::ADC2_Pin, AnalogMux, 2>> PotentiometerFilterEnvRelease;
    typedef Potentiometer<MuxAnalogPin<MainBoard::ADC2_Pin, AnalogMux, 3>, Detent::DETENT_CENTER> PotentiometerAmpBalance;
    typedef Potentiometer<MuxAnalogPin<MainBoard::ADC2_Pin, AnalogMux, 4>> PotentiometerAmpLevel;
    typedef Potentiometer<MuxAnalogPin<MainBoard::ADC2_Pin, AnalogMux, 5>> PotentiometerAmpEnvAttack;
    typedef Potentiometer<MuxAnalogPin<MainBoard::ADC2_Pin, AnalogMux, 6>> PotentiometerAmpEnvDecay;
    typedef Potentiometer<MuxAnalogPin<MainBoard::ADC2_Pin, AnalogMux, 7>> PotentiometerAmpEnvSustain;
    typedef Potentiometer<MuxAnalogPin<MainBoard::ADC3_Pin, AnalogMux, 0>> PotentiometerAmpEnvRelease;
    typedef Potentiometer<MuxAnalogPin<MainBoard::ADC3_Pin, AnalogMux, 1>> PotentiometerAuxEnvAttack;
    typedef Potentiometer<MuxAnalogPin<MainBoard::ADC3_Pin, AnalogMux, 2>> PotentiometerAuxEnvDecay;
    typedef Potentiometer<MuxAnalogPin<MainBoard::ADC3_Pin, AnalogMux, 3>> PotentiometerAuxEnvSustain;
    typedef Potentiometer<MuxAnalogPin<MainBoard::ADC3_Pin, AnalogMux, 4>> PotentiometerAuxEnvRelease;
    typedef Potentiometer<MuxAnalogPin<MainBoard::ADC3_Pin, AnalogMux, 5>> PotentiometerLFO1Rate;
    typedef Potentiometer<MuxAnalogPin<MainBoard::ADC3_Pin, AnalogMux, 6>> PotentiometerLFO2Rate;
    typedef Potentiometer<MuxAnalogPin<MainBoard::ADC3_Pin, AnalogMux, 7>> PotentiometerLFOSyncPhase;
    typedef Potentiometer<MuxAnalogPin<MainBoard::ADC4_Pin, AnalogMux, 0>, Detent::DETENT_CENTER> PotentiometerModAmount;
    typedef Potentiometer<MuxAnalogPin<MainBoard::ADC4_Pin, AnalogMux, 1>> PotentiometerPortamentoTime;
    typedef Potentiometer<MuxAnalogPin<MainBoard::ADC4_Pin, AnalogMux, 2>> PotentiometerFXParamValue;
    typedef Potentiometer<MuxAnalogPin<MainBoard::ADC4_Pin, AnalogMux, 3>> PotentiometerArpSpeed;
    typedef Potentiometer<MuxAnalogPin<MainBoard::ADC4_Pin, AnalogMux, 4>> PotentiometerBass;
    typedef Potentiometer<MuxAnalogPin<MainBoard::ADC4_Pin, AnalogMux, 5>> PotentiometerTreble;

    //Potentiometer scanner
    typedef PotentiometerScannerSync<
    PotentiometerOsc1Pitch,
    PotentiometerOsc1Detune,
    PotentiometerOsc1Shape1,
    PotentiometerOsc1Shape2,
    PotentiometerOsc2Pitch,
    PotentiometerOsc2Detune,
    PotentiometerOsc2Shape,
    PotentiometerOscSyncPhase,
    PotentiometerOscBalance,
    PotentiometerOscRingModAmount,
    PotentiometerOscCrossModAmount,
    PotentiometerFilterFreq,
    PotentiometerFilterShape,
    PotentiometerFilterEnvAmount,
    PotentiometerFilterKeyTrack,
    PotentiometerFilterEnvAttack,
    PotentiometerFilterEnvDecay,
    PotentiometerFilterEnvSustain,
    PotentiometerFilterEnvRelease,
    PotentiometerAmpBalance,
    PotentiometerAmpLevel,
    PotentiometerAmpEnvAttack,
    PotentiometerAmpEnvDecay,
    PotentiometerAmpEnvSustain,
    PotentiometerAmpEnvRelease,
    PotentiometerAuxEnvAttack,
    PotentiometerAuxEnvDecay,
    PotentiometerAuxEnvSustain,
    PotentiometerAuxEnvRelease,
    PotentiometerLFO1Rate,
    PotentiometerLFO2Rate,
    PotentiometerLFOSyncPhase,
    PotentiometerModAmount,
    PotentiometerPortamentoTime,
    PotentiometerFXParamValue,
    PotentiometerArpSpeed,
    PotentiometerBass,
    PotentiometerTreble> PotentiometerScanner;

    // Serial IO 0 definition
    typedef MCP23S17<
    SPIMaster,
    SSSerialIO1Pin,
    MCP23S17PinConfig<MCP23S17PinIdx::A7, MCP23xxxPinType::SWITCH>,
    MCP23S17PinConfig<MCP23S17PinIdx::A6, MCP23xxxPinType::SWITCH>,
    MCP23S17PinConfig<MCP23S17PinIdx::A5, MCP23xxxPinType::SWITCH>,
    MCP23S17PinConfig<MCP23S17PinIdx::A4, MCP23xxxPinType::SWITCH>,
    MCP23S17PinConfig<MCP23S17PinIdx::A3, MCP23xxxPinType::SWITCH>,
    MCP23S17PinConfig<MCP23S17PinIdx::A2, MCP23xxxPinType::SWITCH>,
    MCP23S17PinConfig<MCP23S17PinIdx::A1, MCP23xxxPinType::SWITCH>,
    MCP23S17PinConfig<MCP23S17PinIdx::A0, MCP23xxxPinType::SWITCH>,
    MCP23S17PinConfig<MCP23S17PinIdx::B0, MCP23xxxPinType::ROTENC_PHASE_A>,
    MCP23S17PinConfig<MCP23S17PinIdx::B7, MCP23xxxPinType::ROTENC_PHASE_B>,
    MCP23S17PinConfig<MCP23S17PinIdx::B3, MCP23xxxPinType::SWITCH>,
    MCP23S17PinConfig<MCP23S17PinIdx::B4, MCP23xxxPinType::SWITCH>
    > SerialIO_1;
    
    typedef SerialIO_1::Pin<MCP23S17PinIdx::A2> Button_Arp_Mode;
    typedef SerialIO_1::Pin<MCP23S17PinIdx::A3> Button_OSC2_Waveform;
    typedef SerialIO_1::Pin<MCP23S17PinIdx::A4> Button_OSC1_Waveform;
    typedef SerialIO_1::Pin<MCP23S17PinIdx::A5> Button_LFO1_Waveform;
    typedef SerialIO_1::Pin<MCP23S17PinIdx::A6> Button_LFO2_Waveform;
    typedef SerialIO_1::Pin<MCP23S17PinIdx::A7> Button_LFO_Sync;
    typedef SerialIO_1::Pin<MCP23S17PinIdx::B0> Button_LayerSelect;
    typedef SerialIO_1::Pin<MCP23S17PinIdx::B1> Button_LayerMode;

    // Serial IO 1 definition
    typedef MCP23S17<
    SPIMaster,
    SSSerialIO0Pin,
    MCP23S17PinConfig<MCP23S17PinIdx::A0, MCP23xxxPinType::SWITCH>,
    MCP23S17PinConfig<MCP23S17PinIdx::A1, MCP23xxxPinType::SWITCH>,
    MCP23S17PinConfig<MCP23S17PinIdx::A2, MCP23xxxPinType::SWITCH>,
    MCP23S17PinConfig<MCP23S17PinIdx::A3, MCP23xxxPinType::SWITCH>,
    MCP23S17PinConfig<MCP23S17PinIdx::A4, MCP23xxxPinType::SWITCH>,
    MCP23S17PinConfig<MCP23S17PinIdx::A5, MCP23xxxPinType::SWITCH>,
    MCP23S17PinConfig<MCP23S17PinIdx::A6, MCP23xxxPinType::SWITCH>,
    MCP23S17PinConfig<MCP23S17PinIdx::A7, MCP23xxxPinType::SWITCH>,
    MCP23S17PinConfig<MCP23S17PinIdx::B0, MCP23xxxPinType::ROTENC_PHASE_A>,
    MCP23S17PinConfig<MCP23S17PinIdx::B1, MCP23xxxPinType::ROTENC_PHASE_A>,
    MCP23S17PinConfig<MCP23S17PinIdx::B2, MCP23xxxPinType::ROTENC_PHASE_A>,
    MCP23S17PinConfig<MCP23S17PinIdx::B3, MCP23xxxPinType::ROTENC_PHASE_A>,
    MCP23S17PinConfig<MCP23S17PinIdx::B7, MCP23xxxPinType::ROTENC_PHASE_B>,
    MCP23S17PinConfig<MCP23S17PinIdx::B6, MCP23xxxPinType::ROTENC_PHASE_B>,
    MCP23S17PinConfig<MCP23S17PinIdx::B5, MCP23xxxPinType::ROTENC_PHASE_B>,
    MCP23S17PinConfig<MCP23S17PinIdx::B4, MCP23xxxPinType::ROTENC_PHASE_B>
    > SerialIO_0;
    
    typedef SerialIO_0::Pin<MCP23S17PinIdx::A0> Button_OSC1_Waveform;
    typedef SerialIO_0::Pin<MCP23S17PinIdx::A1> Button_OSC2_Waveform;
    typedef SerialIO_0::Pin<MCP23S17PinIdx::A2> Button_OSC_Sync;
    typedef SerialIO_0::Pin<MCP23S17PinIdx::A3> Button_Portamento;
    typedef SerialIO_0::Pin<MCP23S17PinIdx::A4> Button_Filter_Type;
    typedef SerialIO_0::Pin<MCP23S17PinIdx::A5> Button_LFO1_Waveform;
    typedef SerialIO_0::Pin<MCP23S17PinIdx::A6> Button_LFO2_Waveform;
    typedef SerialIO_0::Pin<MCP23S17PinIdx::A7> Button_LFO_Sync;

    typedef RotaryEncoder<SerialIO_0::Pin<MCP23S17PinIdx::B0>, SerialIO_0::Pin<MCP23S17PinIdx::B7>> Encoder_ModSrc;
    typedef RotaryEncoder<SerialIO_0::Pin<MCP23S17PinIdx::B1>, SerialIO_0::Pin<MCP23S17PinIdx::B6>> Encoder_ModDst;
    typedef RotaryEncoder<SerialIO_0::Pin<MCP23S17PinIdx::B2>, SerialIO_0::Pin<MCP23S17PinIdx::B5>> Encoder_ArpPattern;
    typedef RotaryEncoder<SerialIO_0::Pin<MCP23S17PinIdx::B3>, SerialIO_0::Pin<MCP23S17PinIdx::B4>> Encoder_FXParam;
    typedef RotaryEncoder<SerialIO_1::Pin<MCP23S17PinIdx::B0>, SerialIO_1::Pin<MCP23S17PinIdx::B7>> Encoder_UpDown;

    // External memory 0
    typedef _25LC512<SPIMaster, SSMemory0Pin> Memory0;

    // Patch memory
    typedef MemorySlice<Memory0, 0, 50000ULL> PatchMemory;
    
    // Scene memory
    typedef MemorySlice<Memory0, 50000ULL, 10000ULL> SceneMemory;

    //typedef MainBoard::EEPROM SceneMemory;
    
    // DSP output
    typedef DSPIC33<
    SPIMaster,
    SSDSPPin
    > DSPOutput;

    // Sync pins
    typedef m328p::GPIOPin<m328p::Port::B, PORTB0> SyncOutClk_Pin;
    typedef m328p::GPIOPin<m328p::Port::B, PORTB1> SyncOutStart_Pin;
    typedef m328p::GPIOPin<m328p::Port::D, PORTD4> SyncInClk_Pin;

    // External interrupts
    typedef m328p::Int0 Int0;
    typedef m328p::Int1 Int1;
    
    // Timer for scheduler
    typedef m328p::Timer0 SchedulerTimer;

    // EEPROM
    typedef m328p::EEPROM EEPROM;

    // Atomic class
    typedef m328p::Atomic Atomic;


    // Initialization
    static void init()
    {
        // Initialize on-chip peripherials
        SPIMaster::init(
        m328p::SPI::ClockRate::FOSC_2,
        m328p::SPI::DataOrder::MSB_FIRST,
        m328p::SPI::ClockPolarity::LOW,
        m328p::SPI::ClockPhase::LEADING);

        ADConverter::init(
        ADConverter::ReferenceSelection::AVCC, // Reference voltage = 5V
        ADConverter::PrescalerSelect::DIV_32, // Prescaler 32 is a good speed/accuracy compromise
        false, // Interrupt disabled
        false, // auto trigger off
        ADConverter::AutoTriggerSource::FREE_RUN,
        true, // ADC0 enabled
        true, // ADC1 enabled
        true, // ADC2 enabled
        true, // ADC3 enabled
        true, // ADC4 enabled
        false); // ADC5 disabled
        
        Int0::init();
        Int1::init();
        
        SchedulerTimer::Init(
        SchedulerTimer::WaveformGenerationMode::NORMAL, // Normal timer operation, i.e. PWM disabled
        SchedulerTimer::ClockSelect::PRESCALER_64, // Use a prescaler to get a suitable scheduler delay range
        SchedulerTimer::CompareOutputMode::DISCONNECTED, // PWM disabled
        SchedulerTimer::CompareOutputMode::DISCONNECTED); // PWM disabled
        SchedulerTimer::enableOverflowInterrupt();
        
        // Initialize USART for MIDI
        // 8n1 @ 31.25 kBaud, Rx/Tx enabled, Rx/UDRE interrupts enabled
        MidiIO::USART::init(
        F_CPU,
        31250, // MIDI baudrate 31.25 kBaud
        true,
        false,
        true,
        true,
        true,
        MidiIO::USART::Mode::ASYNC,
        MidiIO::USART::CharacterSize::_8,
        MidiIO::USART::Parity::NONE,
        MidiIO::USART::StopBits::_1,
        MidiIO::USART::ClockPolarity::OUT_RISING_IN_FALLING);

        SyncOutClk_Pin::setAsOutput();
        SyncOutStart_Pin::setAsOutput();
        SyncInClk_Pin::setAsInput();
        
        // Initialize all connected modules
        
        //AnalogMux::init();
        SSMux::init();

        LCD::init();
        
        Memory0::init();
        
        SerialIO_1::init();
        SerialIO_0::init();
        
        Encoder_ModSrc::init();
        Encoder_ModDst::init();
        Encoder_ArpPattern::init();
        Encoder_FXParam::init();
        Encoder_UpDown::init();
    }

    
    // TicToc
    typedef TicToc<SyncOutStart_Pin> TICTOC;
    
    
    private:
    

};

#endif