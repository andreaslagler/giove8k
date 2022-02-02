#ifndef CONTROLLER_PARAM_TYPE_H
#define CONTROLLER_PARAM_TYPE_H

#include "ControllerParam_enums.h"
#include "lookup_table.h"
#include <stdint.h>


enum class ControllerParamType : uint8_t
{
    NONE,
    NOFENTRIES
};

// Assign parameter type to parameter indices using a lookup-table stored in progmem.
// Default value is "no type", i.e. a bare unsigned char
inline ControllerParamType getParamType(const ControllerParam param)
{
    //typedef SparseLUT<ControllerParamType, uint8_t, static_cast<uint8_t>(ControllerParam::NOFENTRIES)>::Entry Entry;

    constexpr static const PROGMEM SparseLUT<ControllerParamType, uint8_t, static_cast<uint8_t>(ControllerParam::NOFENTRIES)> paramType(
    ControllerParamType::NONE
    );

    return paramType.getP(static_cast<uint8_t>(param));
}

// Assign min value to parameter types using a lookup-table stored in progmem.
// Default value is 0
inline uint8_t getMinValue(const ControllerParamType /*patchParamType*/)
{
    //static const PROGMEM SparseLUT<uint8_t, uint8_t, static_cast<uint8_t>(ControllerParamType::NOFENTRIES)> LUT(
    //0);
    //
    //return LUT.getP(static_cast<uint8_t>(patchParamType));
    
    return 0;
}

// Assign max value to parameter types using a lookup-table stored in progmem.
// Default value is 255
inline uint8_t getMaxValue(const ControllerParamType paramType)
{
    //typedef SparseLUT<uint8_t, uint8_t, static_cast<uint8_t>(ControllerParamType::NOFENTRIES)>::Entry Entry;

    static const PROGMEM SparseLUT<uint8_t, uint8_t, static_cast<uint8_t>(ControllerParamType::NOFENTRIES)> LUT(
    255);

    return LUT.getP(static_cast<uint8_t>(paramType));
}

#endif