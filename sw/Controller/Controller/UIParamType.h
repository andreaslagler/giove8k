#ifndef UI_PARAM_TYPE_H
#define UI_PARAM_TYPE_H

#include "PatchParam_enums.h"
#include "PatchParamType.h"
#include "lookup_table.h"
#include <stdint.h>

#define ZERO_PERCENT 128

enum class PatchParamType : uint8_t
{
    NONE = 0, // 0..255
    ONOFF, // on/off param
    PERC_0_100, // 0..100 percent
    PERC_100_100, // -100..100 percent
    PERC_50_50, // -50..50 percent
    CENT, // -50..50 cents
    SEMITONE, // -12..12 semitones
    FILTERTYPE, // Filter type
    OSC1_WAVEFORM, // OSC 1 Waveform
    OSC2_WAVEFORM, // OSC 2 Waveform
    LFO_WAVEFORM, // LFO Waveform
    LFO_SYNC, // LFO sync
    FX_PARAM, // Parameter of effects section
    NOFENTRIES
};

// Assign parameter type to parameter indices using a lookup-table stored in progmem.
// Default value is "no type", i.e. a bare unsigned char
inline PatchParamType getParamType(const PatchParam param)
{
    typedef SparseLUT<PatchParamType, uint8_t, static_cast<uint8_t>(PatchParam::NOFENTRIES)>::Entry Entry;

    constexpr static const PROGMEM SparseLUT<PatchParamType, uint8_t, static_cast<uint8_t>(PatchParam::NOFENTRIES)> paramType(
    PatchParamType::NONE,
    //Entry{static_cast<uint8_t>(PatchParam::MODULATION_MSB), PatchParamType::MSBLSB},
    //Entry{static_cast<uint8_t>(PatchParam::MODULATION_LSB), PatchParamType::MSBLSB},
    //Entry{static_cast<uint8_t>(PatchParam::PITCHBEND_MSB), PatchParamType::MSBLSB},
    //Entry{static_cast<uint8_t>(PatchParam::PITCHBEND_LSB), PatchParamType::MSBLSB},
    Entry{static_cast<uint8_t>(PatchParam::OSC1_WAVEFORM), PatchParamType::OSC1_WAVEFORM},
    Entry{static_cast<uint8_t>(PatchParam::OSC1_SHAPE1), PatchParamType::PERC_0_100},
    Entry{static_cast<uint8_t>(PatchParam::OSC1_SHAPE2), PatchParamType::PERC_0_100},
    Entry{static_cast<uint8_t>(PatchParam::OSC2_WAVEFORM), PatchParamType::OSC2_WAVEFORM},
    Entry{static_cast<uint8_t>(PatchParam::OSC2_PITCH), PatchParamType::SEMITONE},
    Entry{static_cast<uint8_t>(PatchParam::OSC2_DETUNE), PatchParamType::CENT},
    Entry{static_cast<uint8_t>(PatchParam::OSC2_SHAPE), PatchParamType::PERC_0_100},
    Entry{static_cast<uint8_t>(PatchParam::OSC_SYNC), PatchParamType::ONOFF},
    Entry{static_cast<uint8_t>(PatchParam::OSC_CROSSMOD), PatchParamType::PERC_0_100},
    Entry{static_cast<uint8_t>(PatchParam::OSC_RINGMOD), PatchParamType::PERC_0_100},
    Entry{static_cast<uint8_t>(PatchParam::OSC_BALANCE), PatchParamType::PERC_100_100},
    Entry{static_cast<uint8_t>(PatchParam::PORTAMENTO), PatchParamType::ONOFF},
    Entry{static_cast<uint8_t>(PatchParam::PORTAMENTO_TIME), PatchParamType::PERC_0_100},
    Entry{static_cast<uint8_t>(PatchParam::FILTER_TYPE), PatchParamType::FILTERTYPE},
    Entry{static_cast<uint8_t>(PatchParam::FILTER_ENV_S), PatchParamType::PERC_0_100},
    Entry{static_cast<uint8_t>(PatchParam::FILTER_ENV_AMOUNT), PatchParamType::PERC_100_100},
    Entry{static_cast<uint8_t>(PatchParam::FILTER_KEYTRACK), PatchParamType::PERC_100_100},
    Entry{static_cast<uint8_t>(PatchParam::AMP_ENV_S), PatchParamType::PERC_0_100},
    Entry{static_cast<uint8_t>(PatchParam::LEVEL), PatchParamType::PERC_0_100},
    Entry{static_cast<uint8_t>(PatchParam::PAN), PatchParamType::PERC_100_100},
    Entry{static_cast<uint8_t>(PatchParam::MODWHEEL_AMOUNT_OSC1_PITCH), PatchParamType::PERC_100_100},
    Entry{static_cast<uint8_t>(PatchParam::MODWHEEL_AMOUNT_OSC1_SHAPE1), PatchParamType::PERC_100_100},
    Entry{static_cast<uint8_t>(PatchParam::MODWHEEL_AMOUNT_OSC1_SHAPE2), PatchParamType::PERC_100_100},
    Entry{static_cast<uint8_t>(PatchParam::MODWHEEL_AMOUNT_OSC2_PITCH ), PatchParamType::PERC_100_100},
    Entry{static_cast<uint8_t>(PatchParam::MODWHEEL_AMOUNT_OSC2_SHAPE), PatchParamType::PERC_100_100},
    Entry{static_cast<uint8_t>(PatchParam::MODWHEEL_AMOUNT_OSC_SYNC_PHASE), PatchParamType::PERC_100_100},
    Entry{static_cast<uint8_t>(PatchParam::MODWHEEL_AMOUNT_OSC_CROSSMOD), PatchParamType::PERC_100_100},
    Entry{static_cast<uint8_t>(PatchParam::MODWHEEL_AMOUNT_OSC_RINGMOD), PatchParamType::PERC_100_100},
    Entry{static_cast<uint8_t>(PatchParam::MODWHEEL_AMOUNT_OSC_BALANCE), PatchParamType::PERC_100_100},
    Entry{static_cast<uint8_t>(PatchParam::MODWHEEL_AMOUNT_FILTER_FREQ), PatchParamType::PERC_100_100},
    Entry{static_cast<uint8_t>(PatchParam::MODWHEEL_AMOUNT_FILTER_SHAPE), PatchParamType::PERC_100_100},
    Entry{static_cast<uint8_t>(PatchParam::MODWHEEL_AMOUNT_LEVEL), PatchParamType::PERC_100_100},
    Entry{static_cast<uint8_t>(PatchParam::MODWHEEL_AMOUNT_PAN), PatchParamType::PERC_100_100},
    Entry{static_cast<uint8_t>(PatchParam::MODWHEEL_AMOUNT_LFO2_RATE), PatchParamType::PERC_100_100},
    Entry{static_cast<uint8_t>(PatchParam::LFO_SYNC), PatchParamType::LFO_SYNC},
    Entry{static_cast<uint8_t>(PatchParam::LFO1_WAVEFORM), PatchParamType::LFO_WAVEFORM},
    Entry{static_cast<uint8_t>(PatchParam::LFO1_AMOUNT_OSC1_PITCH), PatchParamType::PERC_100_100},
    Entry{static_cast<uint8_t>(PatchParam::LFO1_AMOUNT_OSC1_SHAPE1), PatchParamType::PERC_100_100},
    Entry{static_cast<uint8_t>(PatchParam::LFO1_AMOUNT_OSC1_SHAPE2), PatchParamType::PERC_100_100},
    Entry{static_cast<uint8_t>(PatchParam::LFO1_AMOUNT_OSC2_PITCH ), PatchParamType::PERC_100_100},
    Entry{static_cast<uint8_t>(PatchParam::LFO1_AMOUNT_OSC2_SHAPE), PatchParamType::PERC_100_100},
    Entry{static_cast<uint8_t>(PatchParam::LFO1_AMOUNT_OSC_SYNC_PHASE), PatchParamType::PERC_100_100},
    Entry{static_cast<uint8_t>(PatchParam::LFO1_AMOUNT_OSC_CROSSMOD), PatchParamType::PERC_100_100},
    Entry{static_cast<uint8_t>(PatchParam::LFO1_AMOUNT_OSC_RINGMOD), PatchParamType::PERC_100_100},
    Entry{static_cast<uint8_t>(PatchParam::LFO1_AMOUNT_OSC_BALANCE), PatchParamType::PERC_100_100},
    Entry{static_cast<uint8_t>(PatchParam::LFO1_AMOUNT_FILTER_FREQ), PatchParamType::PERC_100_100},
    Entry{static_cast<uint8_t>(PatchParam::LFO1_AMOUNT_FILTER_SHAPE), PatchParamType::PERC_100_100},
    Entry{static_cast<uint8_t>(PatchParam::LFO1_AMOUNT_LEVEL), PatchParamType::PERC_100_100},
    Entry{static_cast<uint8_t>(PatchParam::LFO1_AMOUNT_PAN), PatchParamType::PERC_100_100},
    Entry{static_cast<uint8_t>(PatchParam::LFO1_AMOUNT_LFO2_RATE), PatchParamType::PERC_100_100},
    Entry{static_cast<uint8_t>(PatchParam::LFO2_WAVEFORM), PatchParamType::LFO_WAVEFORM},
    Entry{static_cast<uint8_t>(PatchParam::LFO2_AMOUNT_OSC1_PITCH), PatchParamType::PERC_100_100},
    Entry{static_cast<uint8_t>(PatchParam::LFO2_AMOUNT_OSC1_SHAPE1), PatchParamType::PERC_100_100},
    Entry{static_cast<uint8_t>(PatchParam::LFO2_AMOUNT_OSC1_SHAPE2), PatchParamType::PERC_100_100},
    Entry{static_cast<uint8_t>(PatchParam::LFO2_AMOUNT_OSC2_PITCH ), PatchParamType::PERC_100_100},
    Entry{static_cast<uint8_t>(PatchParam::LFO2_AMOUNT_OSC2_SHAPE), PatchParamType::PERC_100_100},
    Entry{static_cast<uint8_t>(PatchParam::LFO2_AMOUNT_OSC_SYNC_PHASE), PatchParamType::PERC_100_100},
    Entry{static_cast<uint8_t>(PatchParam::LFO2_AMOUNT_OSC_CROSSMOD), PatchParamType::PERC_100_100},
    Entry{static_cast<uint8_t>(PatchParam::LFO2_AMOUNT_OSC_RINGMOD), PatchParamType::PERC_100_100},
    Entry{static_cast<uint8_t>(PatchParam::LFO2_AMOUNT_OSC_BALANCE), PatchParamType::PERC_100_100},
    Entry{static_cast<uint8_t>(PatchParam::LFO2_AMOUNT_FILTER_FREQ), PatchParamType::PERC_100_100},
    Entry{static_cast<uint8_t>(PatchParam::LFO2_AMOUNT_FILTER_SHAPE), PatchParamType::PERC_100_100},
    Entry{static_cast<uint8_t>(PatchParam::LFO2_AMOUNT_LEVEL), PatchParamType::PERC_100_100},
    Entry{static_cast<uint8_t>(PatchParam::AUX_ENV_S), PatchParamType::PERC_0_100},
    Entry{static_cast<uint8_t>(PatchParam::AUXENV_AMOUNT_OSC1_PITCH), PatchParamType::PERC_100_100},
    Entry{static_cast<uint8_t>(PatchParam::AUXENV_AMOUNT_OSC1_SHAPE1), PatchParamType::PERC_100_100},
    Entry{static_cast<uint8_t>(PatchParam::AUXENV_AMOUNT_OSC1_SHAPE2), PatchParamType::PERC_100_100},
    Entry{static_cast<uint8_t>(PatchParam::AUXENV_AMOUNT_OSC2_PITCH ), PatchParamType::PERC_100_100},
    Entry{static_cast<uint8_t>(PatchParam::AUXENV_AMOUNT_OSC2_SHAPE), PatchParamType::PERC_100_100},
    Entry{static_cast<uint8_t>(PatchParam::AUXENV_AMOUNT_OSC_SYNC_PHASE), PatchParamType::PERC_100_100},
    Entry{static_cast<uint8_t>(PatchParam::AUXENV_AMOUNT_OSC_CROSSMOD), PatchParamType::PERC_100_100},
    Entry{static_cast<uint8_t>(PatchParam::AUXENV_AMOUNT_OSC_RINGMOD), PatchParamType::PERC_100_100},
    Entry{static_cast<uint8_t>(PatchParam::AUXENV_AMOUNT_OSC_BALANCE), PatchParamType::PERC_100_100},
    Entry{static_cast<uint8_t>(PatchParam::AUXENV_AMOUNT_FILTER_SHAPE), PatchParamType::PERC_100_100},
    Entry{static_cast<uint8_t>(PatchParam::AUXENV_AMOUNT_LFO2_RATE), PatchParamType::PERC_100_100},
    Entry{static_cast<uint8_t>(PatchParam::BASS), PatchParamType::PERC_100_100},
    Entry{static_cast<uint8_t>(PatchParam::TREBLE), PatchParamType::PERC_100_100},
    Entry{static_cast<uint8_t>(PatchParam::CHORUS_DEPTH), PatchParamType::PERC_0_100},
    Entry{static_cast<uint8_t>(PatchParam::CHORUS_MODDEPTH), PatchParamType::PERC_0_100},
    Entry{static_cast<uint8_t>(PatchParam::CHORUS_SPREAD), PatchParamType::PERC_0_100},
    Entry{static_cast<uint8_t>(PatchParam::CHORUS_MIX), PatchParamType::PERC_0_100},
    Entry{static_cast<uint8_t>(PatchParam::ECHO_FEEDBACK), PatchParamType::PERC_0_100},
    Entry{static_cast<uint8_t>(PatchParam::ECHO_SPREAD), PatchParamType::PERC_0_100},
    Entry{static_cast<uint8_t>(PatchParam::ECHO_BRIGHTNESS), PatchParamType::PERC_100_100},
    Entry{static_cast<uint8_t>(PatchParam::ECHO_MIX), PatchParamType::PERC_0_100}
    );

    return paramType.getP(static_cast<uint8_t>(param));
}

// Assign default value to parameter indices using a lookup-table stored in progmem.
// Default value is 0
inline uint8_t getDefaultValue(const PatchParam param)
{
    typedef SparseLUT<uint8_t, uint8_t, static_cast<uint8_t>(PatchParam::NOFENTRIES)>::Entry Entry;

    constexpr static const PROGMEM SparseLUT<uint8_t, uint8_t, static_cast<uint8_t>(PatchParam::NOFENTRIES)> defaultValue(
    0, // This is the default for all other parameters
    Entry{static_cast<uint8_t>(PatchParam::OSC1_WAVEFORM), static_cast<uint8_t>(Osc1Waveform::MIN)},
    Entry{static_cast<uint8_t>(PatchParam::OSC1_SHAPE1), 127},
    Entry{static_cast<uint8_t>(PatchParam::OSC1_SHAPE2), 0},
    Entry{static_cast<uint8_t>(PatchParam::OSC2_WAVEFORM), static_cast<uint8_t>(Osc2Waveform::MIN)},
    Entry{static_cast<uint8_t>(PatchParam::OSC2_SHAPE), 127},
    Entry{static_cast<uint8_t>(PatchParam::OSC_SYNC), static_cast<uint8_t>(OnOff::OFF)},
    Entry{static_cast<uint8_t>(PatchParam::FILTER_TYPE), static_cast<uint8_t>(FilterType::MIN)},
    Entry{static_cast<uint8_t>(PatchParam::FILTER_FREQ), 128},
    Entry{static_cast<uint8_t>(PatchParam::FILTER_KEYTRACK), ZERO_PERCENT},
    Entry{static_cast<uint8_t>(PatchParam::FILTER_ENV_S), 255},
    Entry{static_cast<uint8_t>(PatchParam::AMP_ENV_S), 255},
    Entry{static_cast<uint8_t>(PatchParam::LEVEL), 255},
    Entry{static_cast<uint8_t>(PatchParam::PAN), ZERO_PERCENT},
    Entry{static_cast<uint8_t>(PatchParam::BASS), ZERO_PERCENT},
    Entry{static_cast<uint8_t>(PatchParam::TREBLE), ZERO_PERCENT},
    //Entry{static_cast<uint8_t>(PatchParam::PITCHBEND_MSB), 0x20}, // Mid position = 16384 / 2 = 8192 = 0x2000
    Entry{static_cast<uint8_t>(PatchParam::MODWHEEL_AMOUNT_OSC1_PITCH), ZERO_PERCENT},
    Entry{static_cast<uint8_t>(PatchParam::MODWHEEL_AMOUNT_OSC1_SHAPE1), ZERO_PERCENT},
    Entry{static_cast<uint8_t>(PatchParam::MODWHEEL_AMOUNT_OSC1_SHAPE2), ZERO_PERCENT},
    Entry{static_cast<uint8_t>(PatchParam::MODWHEEL_AMOUNT_OSC2_PITCH), ZERO_PERCENT},
    Entry{static_cast<uint8_t>(PatchParam::MODWHEEL_AMOUNT_OSC2_SHAPE), ZERO_PERCENT},
    Entry{static_cast<uint8_t>(PatchParam::MODWHEEL_AMOUNT_OSC_SYNC_PHASE), ZERO_PERCENT},
    Entry{static_cast<uint8_t>(PatchParam::MODWHEEL_AMOUNT_OSC_RINGMOD), ZERO_PERCENT},
    Entry{static_cast<uint8_t>(PatchParam::MODWHEEL_AMOUNT_OSC_CROSSMOD), ZERO_PERCENT},
    Entry{static_cast<uint8_t>(PatchParam::MODWHEEL_AMOUNT_OSC_RINGMOD), ZERO_PERCENT},
    Entry{static_cast<uint8_t>(PatchParam::MODWHEEL_AMOUNT_OSC_BALANCE), ZERO_PERCENT},
    Entry{static_cast<uint8_t>(PatchParam::MODWHEEL_AMOUNT_FILTER_FREQ), ZERO_PERCENT},
    Entry{static_cast<uint8_t>(PatchParam::MODWHEEL_AMOUNT_FILTER_SHAPE), ZERO_PERCENT},
    Entry{static_cast<uint8_t>(PatchParam::MODWHEEL_AMOUNT_LEVEL), ZERO_PERCENT},
    Entry{static_cast<uint8_t>(PatchParam::MODWHEEL_AMOUNT_PAN), ZERO_PERCENT},
    Entry{static_cast<uint8_t>(PatchParam::MODWHEEL_AMOUNT_LFO2_RATE), ZERO_PERCENT},
    Entry{static_cast<uint8_t>(PatchParam::LFO1_WAVEFORM), static_cast<uint8_t>(LFOWaveform::MIN)},
    Entry{static_cast<uint8_t>(PatchParam::LFO1_AMOUNT_OSC1_PITCH), ZERO_PERCENT},
    Entry{static_cast<uint8_t>(PatchParam::LFO1_AMOUNT_OSC1_SHAPE1), ZERO_PERCENT},
    Entry{static_cast<uint8_t>(PatchParam::LFO1_AMOUNT_OSC1_SHAPE2), ZERO_PERCENT},
    Entry{static_cast<uint8_t>(PatchParam::LFO1_AMOUNT_OSC2_PITCH), ZERO_PERCENT},
    Entry{static_cast<uint8_t>(PatchParam::LFO1_AMOUNT_OSC2_SHAPE), ZERO_PERCENT},
    Entry{static_cast<uint8_t>(PatchParam::LFO1_AMOUNT_OSC_SYNC_PHASE), ZERO_PERCENT},
    Entry{static_cast<uint8_t>(PatchParam::LFO1_AMOUNT_OSC_RINGMOD), ZERO_PERCENT},
    Entry{static_cast<uint8_t>(PatchParam::LFO1_AMOUNT_OSC_CROSSMOD), ZERO_PERCENT},
    Entry{static_cast<uint8_t>(PatchParam::LFO1_AMOUNT_OSC_RINGMOD), ZERO_PERCENT},
    Entry{static_cast<uint8_t>(PatchParam::LFO1_AMOUNT_OSC_BALANCE), ZERO_PERCENT},
    Entry{static_cast<uint8_t>(PatchParam::LFO1_AMOUNT_FILTER_FREQ), ZERO_PERCENT},
    Entry{static_cast<uint8_t>(PatchParam::LFO1_AMOUNT_FILTER_SHAPE), ZERO_PERCENT},
    Entry{static_cast<uint8_t>(PatchParam::LFO1_AMOUNT_LEVEL), ZERO_PERCENT},
    Entry{static_cast<uint8_t>(PatchParam::LFO1_AMOUNT_PAN), ZERO_PERCENT},
    Entry{static_cast<uint8_t>(PatchParam::LFO1_AMOUNT_LFO2_RATE), ZERO_PERCENT},
    Entry{static_cast<uint8_t>(PatchParam::LFO2_WAVEFORM), static_cast<uint8_t>(LFOWaveform::MIN)},
    Entry{static_cast<uint8_t>(PatchParam::LFO2_AMOUNT_OSC1_PITCH), ZERO_PERCENT},
    Entry{static_cast<uint8_t>(PatchParam::LFO2_AMOUNT_OSC1_SHAPE1), ZERO_PERCENT},
    Entry{static_cast<uint8_t>(PatchParam::LFO2_AMOUNT_OSC1_SHAPE2), ZERO_PERCENT},
    Entry{static_cast<uint8_t>(PatchParam::LFO2_AMOUNT_OSC2_PITCH), ZERO_PERCENT},
    Entry{static_cast<uint8_t>(PatchParam::LFO2_AMOUNT_OSC2_SHAPE), ZERO_PERCENT},
    Entry{static_cast<uint8_t>(PatchParam::LFO2_AMOUNT_OSC_SYNC_PHASE), ZERO_PERCENT},
    Entry{static_cast<uint8_t>(PatchParam::LFO2_AMOUNT_OSC_RINGMOD), ZERO_PERCENT},
    Entry{static_cast<uint8_t>(PatchParam::LFO2_AMOUNT_OSC_CROSSMOD), ZERO_PERCENT},
    Entry{static_cast<uint8_t>(PatchParam::LFO2_AMOUNT_OSC_RINGMOD), ZERO_PERCENT},
    Entry{static_cast<uint8_t>(PatchParam::LFO2_AMOUNT_OSC_BALANCE), ZERO_PERCENT},
    Entry{static_cast<uint8_t>(PatchParam::LFO2_AMOUNT_FILTER_FREQ), ZERO_PERCENT},
    Entry{static_cast<uint8_t>(PatchParam::LFO2_AMOUNT_FILTER_SHAPE), ZERO_PERCENT},
    Entry{static_cast<uint8_t>(PatchParam::LFO2_AMOUNT_LEVEL), ZERO_PERCENT},
    Entry{static_cast<uint8_t>(PatchParam::LFO_SYNC), static_cast<uint8_t>(LFOSync::MIN)},
    Entry{static_cast<uint8_t>(PatchParam::AUX_ENV_S), 255},
    Entry{static_cast<uint8_t>(PatchParam::AUXENV_AMOUNT_OSC1_PITCH), ZERO_PERCENT},
    Entry{static_cast<uint8_t>(PatchParam::AUXENV_AMOUNT_OSC1_SHAPE1), ZERO_PERCENT},
    Entry{static_cast<uint8_t>(PatchParam::AUXENV_AMOUNT_OSC1_SHAPE2), ZERO_PERCENT},
    Entry{static_cast<uint8_t>(PatchParam::AUXENV_AMOUNT_OSC2_PITCH), ZERO_PERCENT},
    Entry{static_cast<uint8_t>(PatchParam::AUXENV_AMOUNT_OSC2_SHAPE), ZERO_PERCENT},
    Entry{static_cast<uint8_t>(PatchParam::AUXENV_AMOUNT_OSC_SYNC_PHASE), ZERO_PERCENT},
    Entry{static_cast<uint8_t>(PatchParam::AUXENV_AMOUNT_OSC_RINGMOD), ZERO_PERCENT},
    Entry{static_cast<uint8_t>(PatchParam::AUXENV_AMOUNT_OSC_CROSSMOD), ZERO_PERCENT},
    Entry{static_cast<uint8_t>(PatchParam::AUXENV_AMOUNT_OSC_RINGMOD), ZERO_PERCENT},
    Entry{static_cast<uint8_t>(PatchParam::AUXENV_AMOUNT_OSC_BALANCE), ZERO_PERCENT},
    Entry{static_cast<uint8_t>(PatchParam::AUXENV_AMOUNT_FILTER_SHAPE), ZERO_PERCENT},
    Entry{static_cast<uint8_t>(PatchParam::AUXENV_AMOUNT_LFO2_RATE), ZERO_PERCENT}
    );

    return defaultValue.getP(static_cast<uint8_t>(param));
}


// Assign min value to parameter types using a lookup-table stored in progmem.
// Default value is 0
inline uint8_t getMinValue(const PatchParamType /*patchParamType*/)
{
    //static const PROGMEM SparseLUT<uint8_t, uint8_t, static_cast<uint8_t>(PatchParamType::NOFENTRIES)> LUT(
    //0);
    //
    //return LUT.getP(static_cast<uint8_t>(patchParamType));
    
    return 0;
}

// Assign max value to parameter types using a lookup-table stored in progmem.
// Default value is 255
inline uint8_t getMaxValue(const PatchParamType paramType)
{
    typedef SparseLUT<uint8_t, uint8_t, static_cast<uint8_t>(PatchParamType::NOFENTRIES)>::Entry Entry;

    static const PROGMEM SparseLUT<uint8_t, uint8_t, static_cast<uint8_t>(PatchParamType::NOFENTRIES)> LUT(
    255,
    Entry{static_cast<uint8_t>(PatchParamType::ONOFF), static_cast<uint8_t>(OnOff::MAX)},
    Entry{static_cast<uint8_t>(PatchParamType::OSC1_WAVEFORM), static_cast<uint8_t>(Osc1Waveform::MAX)},
    Entry{static_cast<uint8_t>(PatchParamType::OSC2_WAVEFORM), static_cast<uint8_t>(Osc2Waveform::MAX)},
    Entry{static_cast<uint8_t>(PatchParamType::LFO_WAVEFORM), static_cast<uint8_t>(LFOWaveform::MAX)},
    Entry{static_cast<uint8_t>(PatchParamType::LFO_SYNC), static_cast<uint8_t>(LFOSync::MAX)},
    Entry{static_cast<uint8_t>(PatchParamType::FX_PARAM), static_cast<uint8_t>(FXParam::MAX)},
    Entry{static_cast<uint8_t>(PatchParamType::FILTERTYPE), static_cast<uint8_t>(FilterType::MAX)});

    return LUT.getP(static_cast<uint8_t>(paramType));
}

#endif