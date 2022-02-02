#ifndef PARAM_TYPE_ENUMS_H
#define PARAM_TYPE_ENUMS_H

#include <stdint.h>
#include "type_traits.h"
#include "Osc_enums.h"
#include "Filter_enums.h"
#include "LFO_enums.h"

enum class ParamType : uint8_t
{
    NONE = 0, // 0..255
    MSBLSB, // MSB/LSB pair
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
    BPM, // Beats per minute
    SCALE, // Note scale (e.g. quarter note)
    ARP_PATTERN, // Arpeggiator pattern
    LAYER_MODE, // Layer mode
    NOFENTRIES
};

enum class OnOff : uint8_t
{
    OFF = 0,
    ON,
    NOFENTRIES,
    MIN = 0,
    MAX = NOFENTRIES - 1
};

inline OnOff& operator++(OnOff & arg)
{
    return arg = static_cast<OnOff>(static_cast<uint8_t>(arg)+1);
}

inline OnOff& operator--(OnOff & arg)
{
    return arg = static_cast<OnOff>(static_cast<uint8_t>(arg)-1);
}


/**
@brief Numeric limits of OnOff
*/
template <>
struct numeric_limits <OnOff>
{
    /**
    @brief Maximum value
    @result Maximum value of OnOff
    */
    static constexpr OnOff max()
    {
        return OnOff::MAX;
    }
    
    /**
    @brief Minimum value
    @result Minimum value of OnOff
    */
    static constexpr OnOff min()
    {
        return OnOff::MIN;
    }
};

enum class ModSource : uint8_t
{
    MODWHEEL = 0,
    LFO1,
    LFO2,
    AUXENV,
    NOFENTRIES,
    MIN = 0,
    MAX = NOFENTRIES-1
};

inline ModSource& operator++(ModSource & arg)
{
    return arg = static_cast<ModSource>(static_cast<uint8_t>(arg)+1);
}

inline ModSource& operator--(ModSource & arg)
{
    return arg = static_cast<ModSource>(static_cast<uint8_t>(arg)-1);
}

/**
@brief Numeric limits of ModSource
*/
template <>
struct numeric_limits <ModSource>
{
    /**
    @brief Maximum value
    @result Maximum value of ModSource
    */
    static constexpr ModSource max()
    {
        return ModSource::MAX;
    }
    
    /**
    @brief Minimum value
    @result Minimum value of ModSource
    */
    static constexpr ModSource min()
    {
        return ModSource::MIN;
    }
};

enum class ModWheelDst: uint8_t
{
    OSC1_PITCH = 0,
    OSC1_SHAPE1,
    OSC1_SHAPE2,
    OSC2_PITCH ,
    OSC2_SHAPE,
    OSC_SYNC_PHASE,
    OSC_CROSSMOD,
    OSC_RINGMOD,
    OSC_BALANCE,
    FILTER_FREQ,
    FILTER_SHAPE,
    LEVEL,
    PAN,
    LFO2_RATE,
    NOFENTRIES,
    MIN = 0,
    MAX = NOFENTRIES-1
};

enum class LFO1Dst : uint8_t
{
    OSC1_PITCH = 0,
    OSC1_SHAPE1,
    OSC1_SHAPE2,
    OSC2_PITCH ,
    OSC2_SHAPE,
    OSC_SYNC_PHASE,
    OSC_CROSSMOD,
    OSC_RINGMOD,
    OSC_BALANCE,
    FILTER_FREQ,
    FILTER_SHAPE,
    LEVEL,
    PAN,
    LFO2_RATE,
    NOFENTRIES,
    MIN = 0,
    MAX = NOFENTRIES-1
};

enum class LFO2Dst : uint8_t
{
    OSC1_PITCH = 0,
    OSC1_SHAPE1,
    OSC1_SHAPE2,
    OSC2_PITCH ,
    OSC2_SHAPE,
    OSC_SYNC_PHASE,
    OSC_CROSSMOD,
    OSC_RINGMOD,
    OSC_BALANCE,
    FILTER_FREQ,
    FILTER_SHAPE,
    LEVEL,
    PAN,
    NOFENTRIES,
    MIN = 0,
    MAX = NOFENTRIES-1
};

enum class AuxEnvDst : uint8_t
{
    OSC1_PITCH = 0,
    OSC1_SHAPE1,
    OSC1_SHAPE2,
    OSC2_PITCH ,
    OSC2_SHAPE,
    OSC_SYNC_PHASE,
    OSC_CROSSMOD,
    OSC_RINGMOD,
    OSC_BALANCE,
    FILTER_SHAPE,
    PAN,
    LFO2_RATE,
    NOFENTRIES,
    MIN = 0,
    MAX = NOFENTRIES-1
};

/// @brief FX parameter
enum class FXParam : uint8_t
{
    CHORUS_DEPTH = 0,
    CHORUS_RATE,
    CHORUS_MODDEPTH,
    CHORUS_SPREAD,
    CHORUS_MIX,
    ECHO_DELAY,
    ECHO_FEEDBACK,
    ECHO_SPREAD,
    ECHO_BRIGHTNESS,
    ECHO_MIX,
    BITCRUSHER_SAMPLERATE,
    BITCRUSHER_QUANTIZATION,
    BITCRUSHER_MIX,
    DISTORTION_DRIVE,
    DISTORTION_SHAPE,
    DISTORTION_MIX,
    NOFENTRIES,
    MIN = 0,
    MAX = NOFENTRIES-1
};



inline FXParam& operator++(FXParam & arg)
{
    return arg = static_cast<FXParam>(static_cast<uint8_t>(arg)+1);
}

inline FXParam& operator--(FXParam & arg)
{
    return arg = static_cast<FXParam>(static_cast<uint8_t>(arg)-1);
}

/**
@brief Numeric limits of FXParam
*/
template <>
struct numeric_limits <FXParam>
{
    /**
    @brief Maximum value
    @result Maximum value of FXParam
    */
    static constexpr FXParam max()
    {
        return FXParam::MAX;
    }
    
    /**
    @brief Minimum value
    @result Minimum value of FXParam
    */
    static constexpr FXParam min()
    {
        return FXParam::MIN;
    }
};

/// @brief Scale
enum class Scale: uint8_t
{
    _1_1 = 0, // 1/1 Note
    _1_2, // half note
    _1_4, // quarter note
    _1_8, // 1/8th note
    _1_16, // 1/16th note
    _1_32, // 1/32nd note
    NOFENTRIES,
    MIN = 0,
    MAX = NOFENTRIES-1
};

inline Scale& operator++(Scale & arg)
{
    return arg = static_cast<Scale>(static_cast<uint8_t>(arg)+1);
}

inline Scale& operator--(Scale & arg)
{
    return arg = static_cast<Scale>(static_cast<uint8_t>(arg)-1);
}

/**
@brief Numeric limits of Scale
*/
template <>
struct numeric_limits <Scale>
{
    /**
    @brief Maximum value
    @result Maximum value of Scale
    */
    static constexpr Scale max()
    {
        return Scale::MAX;
    }
    
    /**
    @brief Minimum value
    @result Minimum value of Scale
    */
    static constexpr Scale min()
    {
        return Scale::MIN;
    }
};

#endif