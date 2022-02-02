#ifndef SCENE_PARAM_TYPE_H
#define SCENE_PARAM_TYPE_H

#include "SceneParam_enums.h"
#include "lookup_table.h"
#include <stdint.h>

#define ZERO_PERCENT 128

enum class SceneParamType : uint8_t
{
    NONE,
    LAYER_MODE, // Layer mode
    NOFENTRIES
};

// Assign parameter type to parameter indices using a lookup-table stored in progmem.
// Default value is "no type", i.e. a bare unsigned char
inline SceneParamType getParamType(const SceneParam param)
{
    typedef SparseLUT<SceneParamType, uint8_t, static_cast<uint8_t>(SceneParam::NOFENTRIES)>::Entry Entry;

    constexpr static const PROGMEM SparseLUT<SceneParamType, uint8_t, static_cast<uint8_t>(SceneParam::NOFENTRIES)> paramType(
    SceneParamType::NONE,
    Entry{static_cast<uint8_t>(SceneParam::LAYER_MODE), SceneParamType::LAYER_MODE}
    );

    return paramType.getP(static_cast<uint8_t>(param));
}

// Assign min value to parameter types using a lookup-table stored in progmem.
// Default value is 0
inline uint8_t getMinValue(const SceneParamType /*patchParamType*/)
{
    //static const PROGMEM SparseLUT<uint8_t, uint8_t, static_cast<uint8_t>(SceneParamType::NOFENTRIES)> LUT(
    //0);
    //
    //return LUT.getP(static_cast<uint8_t>(patchParamType));
    
    return 0;
}

// Assign max value to parameter types using a lookup-table stored in progmem.
// Default value is 255
inline uint8_t getMaxValue(const SceneParamType paramType)
{
    typedef SparseLUT<uint8_t, uint8_t, static_cast<uint8_t>(SceneParamType::NOFENTRIES)>::Entry Entry;

    static const PROGMEM SparseLUT<uint8_t, uint8_t, static_cast<uint8_t>(SceneParamType::NOFENTRIES)> LUT(
    255,
    Entry{static_cast<uint8_t>(SceneParamType::LAYER_MODE), static_cast<uint8_t>(LayerMode::MAX)});

    return LUT.getP(static_cast<uint8_t>(paramType));
}

// Assign default value to parameter types using a lookup-table stored in progmem.
// Default value is 128
inline uint8_t getDefaultValue(const SceneParamType paramType)
{
    typedef SparseLUT<uint8_t, uint8_t, static_cast<uint8_t>(SceneParamType::NOFENTRIES)>::Entry Entry;

    static const PROGMEM SparseLUT<uint8_t, uint8_t, static_cast<uint8_t>(SceneParamType::NOFENTRIES)> LUT(
    0,
    Entry{static_cast<uint8_t>(SceneParamType::LAYER_MODE), static_cast<uint8_t>(LayerMode::MIN)});

    return LUT.getP(static_cast<uint8_t>(paramType));
}


#endif