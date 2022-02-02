#ifndef USER_INTERFACE_LED_H
#define USER_INTERFACE_LED_H

#include <stdint.h>
#include "bitfield.h"
#include "Hardware_def.h"
#include "Scene_enums.h"


/**
@brief User Interface
*/
class UserInterfaceLED
{
    public:

    static void AllOff()
    {
        for (uint8_t & byte : s_ledBuffer.bytes)
        {
            byte = 0;
        }

        Update();
    }

    static void AllOn()
    {
        for (uint8_t & byte : s_ledBuffer.bytes)
        {
            byte = 0xFF;
        }

        Update();
    }

    static void onPatchParamUpdate(const PatchParam patchParam, const uint8_t value)
    {
        switch (patchParam)
        {
            case PatchParam::OSC1_WAVEFORM:
            s_ledBuffer.osc1Waveform = setBit<uint8_t>(value);
            break;

            case PatchParam::OSC2_WAVEFORM:
            s_ledBuffer.osc2Waveform = setBit<uint8_t>(value);
            break;

            case PatchParam::OSC_SYNC:
            s_ledBuffer.oscSync = value > 0 ? 1 : 0;
            break;

            case PatchParam::LEGATO:
            s_ledBuffer.legato = value > 0 ? 1 : 0;
            break;

            case PatchParam::FILTER_TYPE:
            s_ledBuffer.filterType = setBit<uint8_t>(value);
            break;

            case PatchParam::LFO1_WAVEFORM:
            s_ledBuffer.lfo1Waveform = setBit<uint8_t>(value);
            break;

            case PatchParam::LFO2_WAVEFORM:
            s_ledBuffer.lfo2Waveform = setBit<uint8_t>(value);
            break;

            case PatchParam::LFO_SYNC:
            s_ledBuffer.lfoSync = setBit<uint8_t>(value);
            break;

            default:
            break;
        }

        Update();
    }

    static void onSelectedLayerUpdate(const uint8_t layerIdx)
    {
        s_ledBuffer.selectedLayer = setBit<uint8_t>(NOF_LAYERS-1-layerIdx);
        Update();
    }
    
    static void onSceneParamUpdate(const SceneParam param, const uint8_t value)
    {
        switch (param)
        {
            case SceneParam::LAYER_MODE:
            s_ledBuffer.layerMode = setBit<uint8_t>(value);
            break;
            
            default:
            break;
        }
        
        Update();
   }

    static void onArpParamUpdate(const ArpeggiatorParam param, const uint8_t value)
    {
        switch (param)
        {
            case ArpeggiatorParam::MODE:
            s_ledBuffer.arpeggiatorMode = setBit<uint8_t>(value);
            break;
            
            default:
            break;
        }
        
        Update();
    }

    private:

    typedef union
    {
        uint8_t bytes[Hardware::LED::getNofDevices()];

        struct
        {
            // Byte 5
            uint8_t layerMode:static_cast<uint8_t>(LayerMode::NOFENTRIES); // 4
            uint8_t selectedLayer:4; // 4 LEDs regardless

            // Byte 4
            uint8_t lfoSync:static_cast<uint8_t>(LFOSync::NOFENTRIES)-1; // 3 because of LFO sync OFF
            uint8_t :(8-static_cast<uint8_t>(LFOSync::NOFENTRIES)+1-4); // 1
            uint8_t lfo2Waveform:static_cast<uint8_t>(LFOWaveform::NOFENTRIES)-2; // 4
            
            // Byte 3
            uint8_t :2;
            uint8_t lfo1Waveform:static_cast<uint8_t>(LFOWaveform::NOFENTRIES); // 6
            
            // Byte 2
            uint8_t osc1Waveform:static_cast<uint8_t>(Osc1Waveform::NOFENTRIES); // 8
            
            // Byte 1
            uint8_t arpeggiatorMode:static_cast<uint8_t>(ArpeggiatorMode::NOFENTRIES)-1; // 2 because of arpeggiator mode OFF
            uint8_t oscSync:1;
            uint8_t osc2Waveform:static_cast<uint8_t>(Osc2Waveform::NOFENTRIES); // 5
            
            // Byte 0
            uint8_t legato:1;
            uint8_t filterType:static_cast<uint8_t>(FilterType::NOFENTRIES)-1; // 7 because of filter type noneNONE
        };
    } LedBuffer;

    static LedBuffer s_ledBuffer;

    static void Update()
    {
        // Make sure LED bitmap is consistent
        static_assert(sizeof(LedBuffer) == Hardware::LED::getNofDevices(), "Invalid LED bitmap");
        
        Hardware::LED::put(s_ledBuffer.bytes);
    }
};

UserInterfaceLED::LedBuffer UserInterfaceLED::s_ledBuffer = {.bytes = {0}};

# endif