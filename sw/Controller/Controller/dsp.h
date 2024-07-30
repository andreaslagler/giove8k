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

#ifndef DSP_H
#define DSP_H

//#include "DSPParam_enums.h"

template <typename SPIMaster, typename SSPin>
class DSP
{
    public:

    static void init()
    {
        allNotesOff();
        //for (PatchParam param = PatchParam::MIN; param <= PatchParam::MAX; ++param)
        //{
            //updatePatchParam(param, 0);
        //}
    }

    //static void updatePatchParam(const PatchParam param, const uint8_t value)
    //{
        //const uint8_t address = getAddress(param);
        //const uint8_t paramValue = convertValue(param, value);
        //write(address, paramValue);
    //}
    //
    //static void updatePerformanceParam(const PerformanceParam sceneParam, const uint8_t value)
    //{
        //const uint8_t address = getAddress(sceneParam);
        //const uint8_t paramValue = value;
        ////const uint8_t paramValue = convertValue(sceneParam, value);
        //write(address, paramValue);
    //}
    //
    //static void updateControllerParam(const ControllerParam param, const uint8_t value)
    //{
        //const uint8_t address = getAddress(param);
        //const uint8_t paramValue = value;
        ////const uint8_t paramValue = convertValue(sceneParam, value);
        //write(address, paramValue);
    //}
    
    static void noteOn(const uint8_t note, const uint8_t velocity)
    {
        // Wrap note and velocity in a 16bit note-on command indicated by 0b11 prefix
        const NoteParam noteParam = {{
            .velocity = velocity,
            .note = note,
        .prefix = 0b11}};
        
        write(noteParam.byte2, noteParam.byte1);
    }

    static void noteOff(const uint8_t note)
    {
        // Wrap note and velocity in a 16bit note-on command indicated by 0b11 prefix
        const NoteParam noteParam = {{
            .velocity = 0,
            .note = note,
        .prefix = 0b11}};
        
        write(noteParam.byte2, noteParam.byte1);
    }

    static void allNotesOff()
    {
        for (uint8_t note = 0; note < 128; ++note)
        {
            noteOff(note);
        }
    }

    private:
    
    static void write(const uint8_t address, const uint8_t value)
    {
        SSPin::low();
        SPIMaster::put(address);
        SPIMaster::put(value);
        SSPin::high();
    }        
       
    typedef union
    {
        struct
        {
            uint8_t velocity : 7;
            uint8_t note : 7;
            uint8_t prefix : 2;
        };
        
        struct
        {
            uint8_t byte1;
            uint8_t byte2;
        };
    } NoteParam;

    //static constexpr uint8_t getAddress(const PatchParam param)
    //{
        //static_assert(static_cast<uint8_t>(DSPParam::NOFENTRIES) <= static_cast<uint8_t>(DSPParam::NOTE_BASE), "DSPParam is ambiguous");
        //return static_cast<uint8_t>(param) + static_cast<uint8_t>(DSPParam::PATCH_PARAM_BASE);
    //}
    //
    //static constexpr uint8_t getAddress(const PerformanceParam sceneParam)
    //{
        //static_assert(static_cast<uint8_t>(DSPParam::NOFENTRIES) <= static_cast<uint8_t>(DSPParam::NOTE_BASE), "DSPParam is ambiguous");
        //return static_cast<uint8_t>(sceneParam) + static_cast<uint8_t>(DSPParam::PERFORMANCE_PARAM_BASE);
    //}
    //
    //static constexpr uint8_t getAddress(const ControllerParam param)
    //{
        //static_assert(static_cast<uint8_t>(DSPParam::NOFENTRIES) <= static_cast<uint8_t>(DSPParam::NOTE_BASE), "DSPParam is ambiguous");
        //return static_cast<uint8_t>(param) + static_cast<uint8_t>(DSPParam::CONTROLLER_PARAM_BASE);
    //}
    //
    //static uint8_t convertValue(const PatchParam param, const uint8_t value)
    //{
        //switch (getParamType(param))
        //{
            //case PatchParamType::PERC_100_100:
            //// -100..100 percent
            ////case PatchParamType::PERC_50_50:
            //// -50..50 percent
//
            //// Map 0..255 to -128..127
            //return value - 128;
//
            ////case PatchParamType::CENT:
            ////// -50..50 cents
////
            ////// Map 0..255 to -50..50
            ////return uint8_t((uint16_t(101 * value)) >> 8) - 50;
////
            ////case PatchParamType::SEMITONE:
            ////// -24..24 semitones
            ////
            ////// Map 0..255 to -24..24
            ////return uint8_t((uint16_t(49 * value)) >> 8) - 24;
//
            //default:
            //// Don't change parameter value
            //return value;
        //}
    //}
    //
    //static uint8_t convertValue(const PerformanceParam param, const uint8_t value)
    //{
        //switch (getParamType(param))
        //{
            //default:
            //// Don't change parameter value
            //return value;
        //}
    //}
    //
    //static uint8_t convertValue(const ControllerParam param, const uint8_t value)
    //{
        //switch (getParamType(param))
        //{
            //default:
            //// Don't change parameter value
            //return value;
        //}
    //}
};

#endif