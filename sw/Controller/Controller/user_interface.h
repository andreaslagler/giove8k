#ifndef USER_INTERFACE_H
#define USER_INTERFACE_H

#include <stdint.h>

#include "user_interface_LCD.h"
#include "user_interface_LED.h"
#include "Hardware_def.h"

/**
@brief User Interface
*/
class UserInterface
{
    public:
    
    static void onLoadPatch(const uint8_t idx, const String<10>& name)
    {
        UserInterfaceLCD::onLoadPatch(idx, name);
    }
    
    static void onSavePatch(const uint8_t idx, const UIEditableString<10>& name)
    {
        UserInterfaceLCD::onSavePatch(idx, name);
    }
    
    static void onLoadScene(const uint8_t idx, const String<10>& name)
    {
        UserInterfaceLCD::onLoadScene(idx, name);
    }
    
    static void onSaveScene(const uint8_t idx, const UIEditableString<10>& name)
    {
        UserInterfaceLCD::onSaveScene(idx, name);
    }
    
    static void onSaveRename(const uint8_t idx, const UIEditableString<10>& name)
    {
        UserInterfaceLCD::onSaveRename(idx, name);
    }
    
    static void onSaveConfirm(const uint8_t idx, const UIEditableString<10>& name)
    {
        UserInterfaceLCD::onSaveConfirm(idx, name);
    }

    static void onSelectedLayerUpdate(const uint8_t layerIdx)
    {
        UserInterfaceLCD::onSelectedLayerUpdate(layerIdx);
        UserInterfaceLED::onSelectedLayerUpdate(layerIdx);
    }

    static void onPatchParamUpdate(const PatchParam param, const uint8_t value)
    {
        UserInterfaceLCD::onPatchParamUpdate(param, value);
        UserInterfaceLED::onPatchParamUpdate(param, value);
    }

    static void onSceneParamUpdate(const SceneParam param, const uint8_t value)
    {
        UserInterfaceLCD::onSceneParamUpdate(param, value);
        UserInterfaceLED::onSceneParamUpdate(param, value);        
    }

    static void onArpParamUpdate(const ArpeggiatorParam param, const uint8_t value)
    {
        UserInterfaceLCD::onArpParamUpdate(param, value);
        UserInterfaceLED::onArpParamUpdate(param, value);
    }
};

# endif