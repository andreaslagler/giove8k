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

#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <stdint.h>
#include "Hardware_def.h"
#include "Arpeggiator.h"
#include "PatchManager.h"
#include "Subject.h"
#include "UIParam_enums.h"
#include "ControllerParam_enums.h"
#include "ControllerParam_def.h"

/**
@brief Central controller class encapsulating all functionality
*/
class Controller
{
    public:
    
    /**
    @brief Constructor
    */
    Controller()
    {}

    /**
    @brief Initialization
    */
    void init()
    {
        m_patchManager.init();
    }

    /**
    @brief Callback for MIDI note-on message
    @param note MIDI note index (0..127)
    @param velocity MIDI note velocity (0..127)
    */
    void onNoteOn(const uint8_t note, const uint8_t velocity)
    {
        // Dispatch note-on message
        if (m_arpeggiator.isActive())
        {
            m_arpeggiator.addNote(note);
        }
        else
        {
            m_subjectNoteOn.notifiyObserver(note, velocity);
        }
    }
    
    /**
    @brief Callback for MIDI note-off message
    @param note MIDI note index (0..127)
    */
    void onNoteOff(const uint8_t note)
    {
        // Dispatch note-off message
        if (m_arpeggiator.isActive())
        {
            m_arpeggiator.removeNote(note);
        }
        else
        {
            m_subjectNoteOff.notifiyObserver(note);
        }
    }
    
    /**
    @brief Callback for MIDI control change message
    @param controller Identifier of the selected controller
    @param value controller value
    */
    void onControlChange(const uint8_t controller, const uint8_t value)
    {
        // Dispatch controller index
        switch (controller)
        {
            case ECONTROLCHANGE_MODULATION_MSB: m_subjectControllerParam.notifiyObserver(ControllerParam::MODULATION_MSB, value); break;
            case ECONTROLCHANGE_MODULATION_LSB: m_subjectControllerParam.notifiyObserver(ControllerParam::MODULATION_LSB, value); break;
            
            default:
            break;
        }            
    }

    /**
    @brief Set a UI parameter to a given value
    @param param Identifier of the selected parameter
    @param value Parameter value
    */
    void setUIParam(const UIParam param, const uint8_t value)
    {
        // Dispatch UI paramer
        switch (param)
        {
            case UIParam::OSC1_PITCH: m_patchManager.setPatchParam(PatchParam::OSC1_PITCH, value); break;
            case UIParam::OSC1_DETUNE: m_patchManager.setPatchParam(PatchParam::OSC1_DETUNE, value); break;
            case UIParam::OSC1_SHAPE1: m_patchManager.setPatchParam(PatchParam::OSC1_SHAPE1, value); break;
            case UIParam::OSC1_SHAPE2: m_patchManager.setPatchParam(PatchParam::OSC1_SHAPE2, value); break;
            case UIParam::OSC2_PITCH: m_patchManager.setPatchParam(PatchParam::OSC2_PITCH, value); break;
            case UIParam::OSC2_DETUNE: m_patchManager.setPatchParam(PatchParam::OSC2_DETUNE, value); break;
            case UIParam::OSC2_SHAPE: m_patchManager.setPatchParam(PatchParam::OSC2_SHAPE, value); break;
            case UIParam::OSC_SYNC_PHASE: m_patchManager.setPatchParam(PatchParam::OSC_SYNC_PHASE, value); break;
            case UIParam::OSC_CROSSMOD: m_patchManager.setPatchParam(PatchParam::OSC_CROSSMOD, value); break;
            case UIParam::OSC_RINGMOD: m_patchManager.setPatchParam(PatchParam::OSC_RINGMOD, value); break;
            case UIParam::OSC_BALANCE: m_patchManager.setPatchParam(PatchParam::OSC_BALANCE, value); break;
            case UIParam::GLIDE_TIME: m_patchManager.setPatchParam(PatchParam::GLIDE_TIME, value); break;
            case UIParam::FILTER_FREQ: m_patchManager.setPatchParam(PatchParam::FILTER_FREQ, value); break;
            case UIParam::FILTER_SHAPE: m_patchManager.setPatchParam(PatchParam::FILTER_SHAPE, value); break;
            case UIParam::FILTER_KEYTRACK: m_patchManager.setPatchParam(PatchParam::FILTER_KEYTRACK, value); break;
            case UIParam::FILTER_ENV_AMOUNT: m_patchManager.setPatchParam(PatchParam::FILTER_ENV_AMOUNT, value); break;
            case UIParam::FILTER_ENV_A: m_patchManager.setPatchParam(PatchParam::FILTER_ENV_A, value); break;
            case UIParam::FILTER_ENV_D: m_patchManager.setPatchParam(PatchParam::FILTER_ENV_D, value); break;
            case UIParam::FILTER_ENV_S: m_patchManager.setPatchParam(PatchParam::FILTER_ENV_S, value); break;
            case UIParam::FILTER_ENV_R: m_patchManager.setPatchParam(PatchParam::FILTER_ENV_R, value); break;
            case UIParam::LEVEL: m_patchManager.setPatchParam(PatchParam::LEVEL, value); break;
            case UIParam::AMP_ENV_A: m_patchManager.setPatchParam(PatchParam::AMP_ENV_A, value); break;
            case UIParam::AMP_ENV_D: m_patchManager.setPatchParam(PatchParam::AMP_ENV_D, value); break;
            case UIParam::AMP_ENV_S: m_patchManager.setPatchParam(PatchParam::AMP_ENV_S, value); break;
            case UIParam::AMP_ENV_R: m_patchManager.setPatchParam(PatchParam::AMP_ENV_R, value); break;
            case UIParam::PAN: m_patchManager.setPatchParam(PatchParam::PAN, value); break;
            case UIParam::LFO1_RATE: m_patchManager.setPatchParam(PatchParam::LFO1_RATE, value); break;
            case UIParam::LFO2_RATE: m_patchManager.setPatchParam(PatchParam::LFO2_RATE, value); break;
            case UIParam::LFO_SYNC_PHASE: m_patchManager.setPatchParam(PatchParam::LFO_SYNC_PHASE, value); break;
            case UIParam::AUX_ENV_A: m_patchManager.setPatchParam(PatchParam::AUX_ENV_A, value); break;
            case UIParam::AUX_ENV_D: m_patchManager.setPatchParam(PatchParam::AUX_ENV_D, value); break;
            case UIParam::AUX_ENV_S: m_patchManager.setPatchParam(PatchParam::AUX_ENV_S, value); break;
            case UIParam::AUX_ENV_R: m_patchManager.setPatchParam(PatchParam::AUX_ENV_R, value); break;
            case UIParam::FX_PARAM_VALUE: m_patchManager.setFXParam(value); break;
            case UIParam::MOD_AMOUNT: m_patchManager.setModAmount(value); break;
            case UIParam::BASS: m_patchManager.setPatchParam(PatchParam::BASS, value); break;
            case UIParam::TREBLE: m_patchManager.setPatchParam(PatchParam::TREBLE, value); break;
            case UIParam::ARP_SPEED: m_arpeggiator.setParam(ArpeggiatorParam::SPEED, value); break;
            default: break;
        }
        
        resetHomeScreenTimer();
    }
    
    /**
    @brief Increment a UI parameter
    @param param Identifier of the selected parameter
    */
    void incUIParam(const UIParam param)
    {
        // Dispatch UI paramer
        switch (param)
        {
            case UIParam::MOD_SRC: m_patchManager.incModSrc(); break;
            case UIParam::MOD_DST: m_patchManager.incModDst(); break;
            case UIParam::FX_PARAM: m_patchManager.incFXParam(); break;
            case UIParam::ARP_PATTERN: m_arpeggiator.incParam(ArpeggiatorParam::PATTERN); break;
            default: break;
        }
        
        resetHomeScreenTimer();
    }
    
    /**
    @brief Decrement a UI parameter
    @param param Identifier of the selected parameter
    */
    void decUIParam(const UIParam param)
    {
        // Dispatch UI paramer
        switch (param)
        {
            case UIParam::MOD_SRC: m_patchManager.decModSrc(); break;
            case UIParam::MOD_DST: m_patchManager.decModDst(); break;
            case UIParam::FX_PARAM: m_patchManager.decFXParam(); break;
            case UIParam::ARP_PATTERN: m_arpeggiator.decParam(ArpeggiatorParam::PATTERN); break;
            default: break;
        }
        
        resetHomeScreenTimer();
    }
    
    /**
    @brief Toggle a UI parameter
    @param param Identifier of the selected parameter
    */
    void toggleUIParam(const UIParam param)
    {
        // Dispatch UI paramer
        switch (param)
        {
            case UIParam::OSC1_WAVEFORM : m_patchManager.togglePatchParam(PatchParam::OSC1_WAVEFORM); break;
            case UIParam::OSC2_WAVEFORM : m_patchManager.togglePatchParam(PatchParam::OSC2_WAVEFORM); break;
            case UIParam::OSC_SYNC : m_patchManager.togglePatchParam(PatchParam::OSC_SYNC); break;
            case UIParam::LEGATO : m_patchManager.togglePatchParam(PatchParam::LEGATO); break;
            case UIParam::FILTER_TYPE : m_patchManager.togglePatchParam(PatchParam::FILTER_TYPE); break;
            case UIParam::LFO1_WAVEFORM : m_patchManager.togglePatchParam(PatchParam::LFO1_WAVEFORM); break;
            case UIParam::LFO2_WAVEFORM : m_patchManager.togglePatchParam(PatchParam::LFO2_WAVEFORM); break;
            case UIParam::LFO_SYNC : m_patchManager.togglePatchParam(PatchParam::LFO_SYNC); break;
            case UIParam::SELECTED_LAYER : m_patchManager.toggleSelectedLayer(); break;
            case UIParam::LAYER_MODE : m_patchManager.toggleSceneParam(SceneParam::LAYER_MODE); break;
            case UIParam::ARP_MODE : m_arpeggiator.toggleParam(ArpeggiatorParam::MODE); break;
            default: break;
        }
        
        resetHomeScreenTimer();
    }

    /**
    @brief Callback for UI event "Up", e.g. push-button
    */
    void onUp()
    {
        m_patchManager.onUp();
    }

    /**
    @brief Callback for UI event "Down", e.g. push-button
    */
    void onDown()
    {
        m_patchManager.onDown();
    }

    /**
    @brief Callback for UI event "Load Patch", e.g. push-button
    */
    void onLoadPatch()
    {
        m_patchManager.onLoadPatch();
    }

    /**
    @brief Callback for UI event "Save Patch", e.g. push-button
    */
    void onSavePatch()
    {
        m_patchManager.onSavePatch();
    }

    /**
    @brief Callback for UI event "Load Scene", e.g. push-button
    @result Updated patch manager state
    */
    void onLoadScene()
    {
        m_arpeggiator.clear();
        m_patchManager.onLoadScene();
    }

    /**
    @brief Callback for UI event "Save Scene", e.g. push-button
    */
    void onSaveScene()
    {
        m_patchManager.onSaveScene();
    }

    /**
    @brief Callback for UI event "Enter/Next", e.g. push-button
    */
    void onEnterNext()
    {
        m_patchManager.onEnterNext();
    }

    /**
    @brief Callback for UI event "Cancel/Back", e.g. push-button
    */
    void onCancelBack()
    {
        m_patchManager.onCancelBack();
    }
    
    /**
    @brief Get arpeggiator state
    @result Flag indicating if arpeggiator is active
    */
    bool getArpeggiatorState() const
    {
        return m_arpeggiator.isActive();
    }
    
    /**
    @brief Get arpeggiator clock
    @result Arpeggiator clock interval in milliseconds
    */
    uint16_t getArpeggiatorClock() const
    {
        return m_arpeggiator.getClock();
    }

    /**
    @brief Clock arpeggiator, i.e. increment arpeggiator clock by one clock interval
    */
    void clockArpeggiator()
    {
        m_arpeggiator.clock();
    }
    
    /**
    @brief Request homescreen
    This method is supposed to be called periodically. Whenever a parameter has been changed by a UI control, a timer is set.
    When this timer has expired, the home screen is displayed
    */   
    void requestHomeScreen()
    {
        if (m_homeScreenTimer != 0)
        {
            if (--m_homeScreenTimer == 0)
            {
                m_patchManager.requestHomeScreen();
            }
        }
    }

    /**
    @brief Register an observer for arpeggiator parameter change event
    @param observer Event observer
    */
    void registerArpParamObserver(const typename Subject<ArpeggiatorParam, uint8_t>::Observer& observer)
    {
        m_arpeggiator.registerParamObserver(observer);
    }
    
    /**
    @brief Register an observer for patch parameter change event
    @param observer Event observer
    */
    void registerPatchParamObserver(const typename Subject<PatchParam, uint8_t>::Observer& observer)
    {
        m_patchManager.registerPatchParamObserver(observer);
    }
    
    /**
    @brief Register an observer for scene parameter change event
    @param observer Event observer
    */
    void registerSceneParamObserver(const typename Subject<SceneParam, uint8_t>::Observer& observer)
    {
        m_patchManager.registerSceneParamObserver(observer);
    }
    
    /**
    @brief Register an observer for selected layer change event
    @param observer Event observer
    */
    void registerSelectedLayerObserver(const typename Subject<uint8_t>::Observer& observer)
    {
        m_patchManager.registerSelectedLayerObserver(observer);
    }
    
    /**
    @brief Register an observer for silent patch parameter change event
    "silent" means that a patch parameter has not been changed directly but indirectly by changing a different parameter
    @param observer Event observer
    */
    void registerPatchParamSilentObserver(const typename Subject<PatchParam, uint8_t>::Observer& observer)
    {
        m_patchManager.registerPatchParamSilentObserver(observer);
    }
    
    /**
    @brief Register an observer for silent scene parameter change event
    "silent" means that a scene parameter has not been changed directly but indirectly by changing a different parameter
    @param observer Event observer
    */
    void registerSceneParamSilentObserver(const typename Subject<SceneParam, uint8_t>::Observer& observer)
    {
        m_patchManager.registerSceneParamSilentObserver(observer);
    }
    
    /**
    @brief Register an observer for silent selected layer change event
    "silent" means that selected layer has not been changed directly but indirectly by changing a different parameter
    @param observer Event observer
    */
    void registerSelectedLayerSilentObserver(const typename Subject<uint8_t>::Observer& observer)
    {
        m_patchManager.registerSelectedLayerSilentObserver(observer);
    }
    
    /**
    @brief Register an observer for load patch event
    @param observer Event observer
    */
    void registerLoadPatchObserver(const typename Subject<uint8_t, const String<10>&>::Observer& observer)
    {
        m_patchManager.registerLoadPatchObserver(observer);
    }

    /**
    @brief Register an observer for save patch event
    @param observer Event observer
    */
    void registerSavePatchObserver(const typename Subject<uint8_t, const UIEditableString<10>&>::Observer& observer)
    {
        m_patchManager.registerSavePatchObserver(observer);
    }
    
    /**
    @brief Register an observer for load scene event
    @param observer Event observer
    */
    void registerLoadSceneObserver(const typename Subject<uint8_t, const String<10>&>::Observer& observer)
    {
        m_patchManager.registerLoadSceneObserver(observer);
    }
    
    /**
    @brief Register an observer for save scene event
    @param observer Event observer
    */
    void registerSaveSceneObserver(const typename Subject<uint8_t, const UIEditableString<10>&>::Observer& observer)
    {
        m_patchManager.registerSaveSceneObserver(observer);
    }
    
    /**
    @brief Register an observer for save patch/scene rename event
    @param observer Event observer
    */
    void registerSaveRenameObserver(const typename Subject<uint8_t, const UIEditableString<10>&>::Observer& observer)
    {
        m_patchManager.registerSaveRenameObserver(observer);
    }
    
    /**
    @brief Register an observer for save patch/scene confirmation event
    @param observer Event observer
    */
    void registerSaveConfirmObserver(const typename Subject<uint8_t, const UIEditableString<10>&>::Observer& observer)
    {
        m_patchManager.registerSaveConfirmObserver(observer);
    }
    
    /**
    @brief Register an observer for note-on events
    @param observer Event observer
    */
    void registerNoteOnObserver(const typename Subject<uint8_t, uint8_t>::Observer& observer)
    {
        m_subjectNoteOn.registerObserver(observer);
        m_arpeggiator.registerNoteOnObserver(observer);
    }
    
    /**
    @brief Register an observer for note-off events
    @param observer Event observer
    */
    void registerNoteOffObserver(const typename Subject<uint8_t>::Observer& observer)
    {
        m_subjectNoteOff.registerObserver(observer);
        m_arpeggiator.registerNoteOffObserver(observer);
    }
    
    /**
    @brief Register an observer for MIDI controller event
    @param observer Event observer
    */
    void registerControllerParamObserver(const typename Subject<ControllerParam, uint8_t>::Observer& observer)
    {
        m_subjectControllerParam.registerObserver(observer);
    }
    
    /**
    @brief Register an observer for home screen display event
    @param observer Event observer
    */
    void registerHomeScreenObserver(const typename Subject<uint8_t, const String<10>&, uint8_t, const String<10>&>::Observer& observer)
    {
        m_patchManager.registerHomeScreenObserver(observer);
    }

    private:
    
    //////////////////////////////////////////////////////////////////////////
    // Home screen timer
    
    // Timer value for home screen display
    uint8_t m_homeScreenTimer {0};
    
    // Reset the home screen timer
    void resetHomeScreenTimer()
    {
        // Show home screen after 30 * screen updates (= 3 seconds)
        m_homeScreenTimer = 30;
    }

    //////////////////////////////////////////////////////////////////////////
    // Controller state

    enum class State : uint8_t {
        IDLE = 0, // Idle, show homescreen
        PARAM_EDITOR, //
        PATCH_MANAGER, // Show patch manager dialog
        MENU // Show settings menu dialog
    };
    
    State m_state;
    
    //////////////////////////////////////////////////////////////////////////
    // Controller components
    
    Arpeggiator m_arpeggiator;
    PatchManager<Hardware::PatchMemory, Hardware::SceneMemory> m_patchManager;

    //////////////////////////////////////////////////////////////////////////
    // Subject/Observer interface
    
    // Arpeggiator events
    Subject<bool> m_subjectArpeggiatorStateUpdate;
    Subject<ArpeggiatorPattern> m_subjectArpeggiatorPatternUpdate;
    Subject<uint8_t> m_subjectArpeggiatorSpeedUpdate;
    
    // MIDI events
    Subject<uint8_t, uint8_t> m_subjectNoteOn;
    Subject<uint8_t> m_subjectNoteOff;
    Subject<ControllerParam, uint8_t> m_subjectControllerParam;
};

# endif