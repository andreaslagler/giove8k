#ifndef PATCH_MANAGER_H
#define PATCH_MANAGER_H

#include <stdint.h>
#include "patch.h"
#include "scene.h"
#include "synth_def.h"

#include "storage.h"
#include "param.h"
#include "ui_editable_string.h"

#define min(a,b) ((a < b) ? a : b)

/**
@brief Patch manager
@tparam PatchMemory Memory driver class implementing static methods
*/
template <typename PatchMemory, typename SceneMemory>
class PatchManager
{
    public:
    
    enum class State : uint8_t
    {
        IDLE,
        LOAD_PATCH,
        SAVE_PATCH,
        SAVE_RENAME_PATCH,
        SAVE_CONFIRM_PATCH,
        LOAD_SCENE,
        SAVE_SCENE,
        SAVE_RENAME_SCENE,
        SAVE_CONFIRM_SCENE
    };

    PatchManager()
    :
    m_scene(m_sceneData.m_sceneParams)
    {}
    
    void init()
    {
        //loadSelectedScene();
        for (uint8_t layer = 0; layer < NOF_LAYERS; ++layer)
        {
            m_subjectSelectedLayerSilentUpdate.notifiyObserver(layer);
            m_patch[layer].init();
        }
        
        m_scene.init();
        
        m_subjectSelectedLayerSilentUpdate.notifiyObserver(m_selectedLayerIdx);
        notifyState();
    }

    /**
    @brief Get parameter from current patch on selected layer
    @param param Patch parameter identifier of selected parameter
    @resultPatch parameter value
    */
    uint8_t getPatchParam(const PatchParam param) const
    {
        return m_patch[m_selectedLayerIdx].getParam(param);
    }
    
    /**
    @brief Set parameter in current patch on selected layer
    @param param Patch parameter identifier of selected parameter
    @param value Patch parameter value
    */
    void setPatchParam(const PatchParam param, const uint8_t value)
    {
        if (State::IDLE == m_state)
        {
            // Set patch param in currently selected layer
            m_patch[m_selectedLayerIdx].setParam(param, value);
        }
    }

    /**
    @brief Increment a patch parameter
    @param param Identifier of the selected patch parameter
    */
    void incPatchParam(const PatchParam param)
    {
        if (State::IDLE == m_state)
        {
            m_patch[m_selectedLayerIdx].incParam(param);
        }
    }
    
    /**
    @brief Decrement a patch parameter
    @param param Identifier of the selected patch parameter
    */
    void decPatchParam(const PatchParam param)
    {
        if (State::IDLE == m_state)
        {
            m_patch[m_selectedLayerIdx].decParam(param);
        }
    }
    
    /**
    @brief Toggle a patch parameter (increment with roll-over)
    @param param Identifier of the selected patch parameter
    */
    void togglePatchParam(const PatchParam param)
    {
        if (State::IDLE == m_state)
        {
            m_patch[m_selectedLayerIdx].toggleParam(param);
        }
    }
    
    
    void incModSrc()
    {
        if (State::IDLE == m_state)
        {
            m_patch[m_selectedLayerIdx].incModSrc();
        }
    }

    void decModSrc()
    {
        if (State::IDLE == m_state)
        {
            m_patch[m_selectedLayerIdx].decModSrc();
        }
    }

    void incModDst()
    {
        if (State::IDLE == m_state)
        {
            m_patch[m_selectedLayerIdx].incModDst();
        }
    }

    void decModDst()
    {
        if (State::IDLE == m_state)
        {
            m_patch[m_selectedLayerIdx].decModDst();
        }
    }

    void incFXParam()
    {
        if (State::IDLE == m_state)
        {
            m_patch[m_selectedLayerIdx].incFXParam();
        }
    }

    void decFXParam()
    {
        if (State::IDLE == m_state)
        {
            m_patch[m_selectedLayerIdx].decFXParam();
        }
    }
    
    /**
    @brief Set modulation amount to a given value
    @param value Modulation amount
    */
    void setModAmount(const uint8_t value)
    {
        if (State::IDLE == m_state)
        {
            m_patch[m_selectedLayerIdx].setModAmount(value);
        }
    }

    /**
    @brief Set selected FX parameter to a given value
    @param value FX parameter value
    */
    void setFXParam(const uint8_t value)
    {
        if (State::IDLE == m_state)
        {
            m_patch[m_selectedLayerIdx].setFXParam(value);
        }
    }

    /**
    @brief Callback for UI event "Enter/Next"
    @result Updated patch manager state
    */
    void onEnterNext()
    {
        switch (m_state)
        {
            case State::SAVE_PATCH:
            // Rename the selected scene
            m_state = State::SAVE_RENAME_PATCH;
            break;

            case State::SAVE_SCENE:
            // Rename the selected scene
            m_state = State::SAVE_RENAME_SCENE;
            break;
            
            case State::SAVE_RENAME_PATCH:
            // Move to next character
            if (m_uiName.toggleCurrentCharIdx())
            {
                m_state = State::SAVE_CONFIRM_PATCH;
            }
            break;

            case State::SAVE_RENAME_SCENE:
            // Move to next character
            if (m_uiName.toggleCurrentCharIdx())
            {
                m_state = State::SAVE_CONFIRM_SCENE;
            }
            break;

            case State::SAVE_CONFIRM_PATCH:
            // Save the selected patch
            saveSelectedPatch();
            m_state = State::IDLE;
            break;

            case State::SAVE_CONFIRM_SCENE:
            // Save the selected scene
            saveSelectedScene();
            m_state = State::IDLE;
            break;

            default:
            break;
        }
        
        notifyState();
    }

    /**
    @brief Callback for UI event "Cancel/Back"
    @result Updated patch manager state
    */
    void onCancelBack()
    {
        switch (m_state)
        {
            case State::LOAD_PATCH:
            cancelSelectedPatch();
            m_state = State::IDLE;
            break;

            case State::LOAD_SCENE:
            cancelSelectedScene();
            m_state = State::IDLE;
            break;

            default:
            m_state = State::IDLE;
            break;
        }
        
        notifyState();
    }
    
    /**
    @brief Callback for UI event "Load Patch"
    @result Updated patch manager state
    */
    void onLoadPatch()
    {
        switch (m_state)
        {
            case State::IDLE:
            // Bring the patch selection menu on screen
            m_state = State::LOAD_PATCH;
            break;

            case State::LOAD_PATCH:
            // Load the selected patch and go to home screen
            loadSelectedPatch();
            m_state = State::IDLE;
            break;

            default:
            break;
        }
        
        notifyState();
    }

    /**
    @brief Callback for UI event "Save Patch"
    @result Updated patch manager state
    */
    void onSavePatch()
    {
        switch (m_state)
        {
            case State::IDLE:
            // Bring the patch selection menu on screen
            m_uiName.init(m_patch[m_selectedLayerIdx].getName());
            m_state = State::SAVE_PATCH;
            break;

            case State::SAVE_PATCH:
            // Rename the selected patch
            m_state = State::SAVE_RENAME_PATCH;
            break;

            case State::SAVE_RENAME_PATCH:
            // Confirm patch name
            m_state = State::SAVE_CONFIRM_PATCH;
            break;

            case State::SAVE_CONFIRM_PATCH:
            // Save the selected patch
            saveSelectedPatch();
            m_state = State::IDLE;
            break;

            default:
            break;
        }
        
        notifyState();
    }

    /**
    @brief Callback for UI event "Load Scene"
    @result Updated patch manager state
    */
    void onLoadScene()
    {
        switch (m_state)
        {
            case State::IDLE:
            // Enter load scene mode
            m_state = State::LOAD_SCENE;
            break;

            case State::LOAD_SCENE:
            // Load the selected scene
            loadSelectedScene();
            m_state = State::IDLE;
            break;

            default:
            break;
        }
        
        notifyState();
    }

    /**
    @brief Callback for UI event "Save Scene"
    @result Updated patch manager state
    */
    void onSaveScene()
    {
        switch (m_state)
        {
            case State::IDLE:
            // Enter save scene mode
            m_uiName.init(m_scene.getName());
            m_state = State::SAVE_SCENE;
            break;

            case State::SAVE_SCENE:
            // Rename the selected scene
            m_state = State::SAVE_RENAME_SCENE;
            break;

            case State::SAVE_RENAME_SCENE:
            // Confirm scene name
            m_state = State::SAVE_CONFIRM_SCENE;
            break;

            case State::SAVE_CONFIRM_SCENE:
            // Save the selected scene
            saveSelectedScene();
            m_state = State::IDLE;
            break;

            default:
            break;
        }
        
        notifyState();
    }

    /**
    @brief Callback for UI event "Up"
    @result Updated patch manager state
    */
    void onUp()
    {
        switch (m_state)
        {
            case State::LOAD_PATCH:
            // Increment the selected patch
            m_selectedPatchIdx.increment(min(255U, PatchStorage::capacity()-1));
            previewSelectedPatch();
            break;

            case State::SAVE_PATCH:
            // Increment the selected patch
            m_selectedPatchIdx.increment(min(255U, PatchStorage::capacity()-1));
            break;

            case State::LOAD_SCENE:
            // Increment the selected scene
            m_selectedSceneIdx.increment(min(255U, SceneStorage::capacity()-1));
            previewSelectedScene();
            break;

            case State::SAVE_SCENE:
            // Increment the selected scene
            m_selectedSceneIdx.increment(min(255U, SceneStorage::capacity()-1));
            break;

            case State::SAVE_RENAME_PATCH:
            case State::SAVE_RENAME_SCENE:
            // Increment the selected character
            m_uiName.incCurrentChar();
            break;

            default:
            break;
        }
        
        notifyState();
    }

    /**
    @brief Callback for UI event "Down"
    @result Updated patch manager state
    */
    void onDown()
    {
        switch (m_state)
        {
            case State::LOAD_PATCH:
            // Decrement the selected patch
            m_selectedPatchIdx.decrement();
            previewSelectedPatch();
            break;

            case State::SAVE_PATCH:
            // Decrement the selected patch
            m_selectedPatchIdx.decrement();
            break;

            case State::LOAD_SCENE:
            // Decrement the selected scene
            m_selectedSceneIdx.decrement();
            previewSelectedScene();
            break;

            case State::SAVE_SCENE:
            // Decrement the selected scene
            m_selectedSceneIdx.decrement();
            break;

            case State::SAVE_RENAME_PATCH:
            case State::SAVE_RENAME_SCENE:
            // Decrement the selected character
            m_uiName.decCurrentChar();
            break;

            default:
            break;
        }
        
        notifyState();
    }
    
    void toggleSelectedLayer()
    {
        m_selectedLayerIdx.incrementRollover(0, NOF_LAYERS-1);
        updateSelectedLayer(m_scene.getParam(SceneParam::LAYER_MODE));
        m_subjectSelectedLayerUpdate.notifiyObserver(m_selectedLayerIdx);
        m_patch[m_selectedLayerIdx].notifyAllSilent();
    }
    
    uint8_t getSelectedLayerIdx() const
    {
        return m_selectedLayerIdx;
    }

    void toggleSceneParam(const SceneParam param)
    {
        m_scene.toggleParam(param);
        if (param == SceneParam::LAYER_MODE)
        {
            updateSelectedLayer(m_scene.getParam(SceneParam::LAYER_MODE));
        }
    }

    void requestHomeScreen()
    {
        // Show home screen if in IDLE state
        notifyState();
    }
    
    void registerPatchParamObserver(const typename Subject<PatchParam, uint8_t>::Observer& observer)
    {
        for (Patch& patch : m_patch)
        {
            patch.registerParamObserver(observer);
        }
    }
    
    void registerSceneParamObserver(const typename Subject<SceneParam, uint8_t>::Observer& observer)
    {
        m_scene.registerParamObserver(observer);
    }

    void registerSelectedLayerObserver(const typename Subject<uint8_t>::Observer& observer)
    {
        m_subjectSelectedLayerUpdate.registerObserver(observer);
    }
    
    void registerPatchParamSilentObserver(const typename Subject<PatchParam, uint8_t>::Observer& observer)
    {
        for (Patch& patch : m_patch)
        {
            patch.registerParamSilentObserver(observer);
        }
    }

    void registerSceneParamSilentObserver(const typename Subject<SceneParam, uint8_t>::Observer& observer)
    {
        m_scene.registerParamSilentObserver(observer);
    }

    void registerSelectedLayerSilentObserver(const typename Subject<uint8_t>::Observer& observer)
    {
        m_subjectSelectedLayerSilentUpdate.registerObserver(observer);
    }
    
    void registerLoadPatchObserver(const typename Subject<uint8_t, const String<10>&>::Observer& observer)
    {
        m_subjectLoadPatch.registerObserver(observer);
    }

    void registerSavePatchObserver(const typename Subject<uint8_t, const UIEditableString<10>&>::Observer& observer)
    {
        m_subjectSavePatch.registerObserver(observer);
    }
    
    void registerLoadSceneObserver(const typename Subject<uint8_t, const String<10>&>::Observer& observer)
    {
        m_subjectLoadScene.registerObserver(observer);
    }
    
    void registerSaveSceneObserver(const typename Subject<uint8_t, const UIEditableString<10>&>::Observer& observer)
    {
        m_subjectSaveScene.registerObserver(observer);
    }
    
    void registerSaveRenameObserver(const typename Subject<uint8_t, const UIEditableString<10>&>::Observer& observer)
    {
        m_subjectSaveRename.registerObserver(observer);
    }
    
    void registerSaveConfirmObserver(const typename Subject<uint8_t, const UIEditableString<10>&>::Observer& observer)
    {
        m_subjectSaveConfirm.registerObserver(observer);
    }
    
    void registerHomeScreenObserver(const typename Subject<uint8_t, const String<10>&, uint8_t, const String<10>&>::Observer& observer)
    {
        m_subjectHomeScreen.registerObserver(observer);
    }
    
    private:
        
    Subject<uint8_t> m_subjectSelectedLayerUpdate;
    Subject<uint8_t> m_subjectSelectedLayerSilentUpdate;
    Subject<uint8_t, const UIEditableString<10>&> m_subjectSaveRename;
    Subject<uint8_t, const UIEditableString<10>&> m_subjectSaveConfirm;
    Subject<uint8_t, const String<10>&> m_subjectLoadPatch;
    Subject<uint8_t, const UIEditableString<10>&> m_subjectSavePatch;
    Subject<uint8_t, const String<10>&> m_subjectLoadScene;
    Subject<uint8_t, const UIEditableString<10>&> m_subjectSaveScene;
    Subject<uint8_t, const String<10>&, uint8_t, const String<10>&> m_subjectHomeScreen;

    struct SceneData
    {
        constexpr const String<10> & getName() const
        {
            return m_name;
        }
        
        constexpr String<10> & getName()
        {
            return m_name;
        }
        
        String<10> m_name;
        
        SceneParams<NOF_LAYERS, static_cast<uint8_t>(SceneParam::NOFENTRIES)> m_sceneParams;

        // Arp Settings
        ArpeggiatorParams m_arpeggiatorParams;
    };
    
    SceneData m_sceneData;
    
    Patch m_patch[NOF_LAYERS];
    
    Scene<NOF_LAYERS> m_scene;

    Param<uint8_t> m_selectedLayerIdx {0};
    Param<uint8_t> m_selectedSceneIdx {0};

    Param<uint8_t> m_selectedPatchIdx {0};
    
    uint8_t m_loadedSceneIdx {0};
    
    UIEditableString<10> m_uiName;

    typedef Storage<Patch::Data, PatchMemory> PatchStorage;
    typedef Storage<SceneData, SceneMemory> SceneStorage;
    
    State m_state {State::IDLE};
    
    inline void previewSelectedPatch()
    {
        // Load selected patch
        PatchStorage::load(m_selectedPatchIdx, m_patch[m_selectedLayerIdx]);

        // Silent update of all patch parameters
        m_patch[m_selectedLayerIdx].notifyAllSilent();
    }

    inline void cancelSelectedPatch()
    {
        // Restore the loaded patch
        m_selectedPatchIdx = m_scene.getPatchIdx(m_selectedLayerIdx);
        previewSelectedPatch();
    }

    inline void loadSelectedPatch()
    {
        // Update selected patch in scene
        m_scene.setPatchIdx(m_selectedLayerIdx, m_selectedPatchIdx);
    }

    inline void saveSelectedPatch()
    {
        // Update the patch name
        m_uiName.toString(m_patch[m_selectedLayerIdx].getName());
        PatchStorage::save(m_scene.getPatchIdx(m_selectedLayerIdx), m_patch[m_selectedLayerIdx]);
    }
    
    inline void previewSelectedScene()
    {
        // Load selected scene
        SceneStorage::load(m_selectedSceneIdx, m_sceneData);
        
        updateSelectedLayer(m_scene.getParam(SceneParam::LAYER_MODE));
        
        // Silent update of all scene parameters
        m_scene.notifyAllSilent();
        
        // Load patches
        for (uint8_t cnt = 0; cnt < NOF_LAYERS; ++cnt)
        {
            m_subjectSelectedLayerSilentUpdate.notifiyObserver(cnt);
            PatchStorage::load(m_scene.getPatchIdx(cnt), m_patch[cnt]);
            
            // Silent update of all patch parameters
            m_patch[cnt].notifyAllSilent();
        }
    }

    inline void cancelSelectedScene()
    {
        // Restore the loaded scene
        m_selectedSceneIdx = m_loadedSceneIdx;
        previewSelectedScene();
    }

    inline void loadSelectedScene()
    {
        m_loadedSceneIdx = m_selectedSceneIdx;
        m_selectedPatchIdx = m_scene.getPatchIdx(m_selectedLayerIdx);
    }

    inline void saveSelectedScene()
    {
        // Update the scene name
        m_uiName.toString(m_scene.getName());
        SceneStorage::save(m_selectedSceneIdx, m_sceneData);
    }

    inline void updateSelectedLayer(const uint8_t layerMode)
    {
        switch (static_cast<LayerMode>(layerMode))
        {
            case LayerMode::SINGLE:
            case LayerMode::MULTI_4X1:
            case LayerMode::UNISON:
            m_selectedLayerIdx = 0;
            m_subjectSelectedLayerSilentUpdate.notifiyObserver(0);
            m_patch[0].notifyAllSilent();
            break;
            
            default:
            break;
        }        
    }

    void notifyState()
    {
        switch (m_state)
        {
            case State::IDLE:
            m_subjectHomeScreen.notifiyObserver(m_selectedSceneIdx, m_scene.getName(), m_scene.getPatchIdx(m_selectedLayerIdx), m_patch[m_selectedLayerIdx].getName());
            break;
            
            case State::LOAD_PATCH:
            m_subjectLoadPatch.notifiyObserver(m_selectedPatchIdx, m_patch[m_selectedLayerIdx].getName());
            break;

            case State::SAVE_PATCH:
            m_subjectSavePatch.notifiyObserver(m_selectedPatchIdx, m_uiName);
            break;

            case State::SAVE_RENAME_PATCH:
            m_subjectSaveRename.notifiyObserver(m_selectedPatchIdx, m_uiName);
            break;

            case State::SAVE_CONFIRM_PATCH:
            m_subjectSaveConfirm.notifiyObserver(m_selectedPatchIdx, m_uiName);
            break;

            case State::LOAD_SCENE:
            m_subjectLoadScene.notifiyObserver(m_selectedSceneIdx, m_scene.getName());
            break;

            case State::SAVE_SCENE:
            m_subjectSaveScene.notifiyObserver(m_selectedSceneIdx, m_uiName);
            break;

            case State::SAVE_RENAME_SCENE:
            m_subjectSaveRename.notifiyObserver(m_selectedSceneIdx, m_uiName);
            break;

            case State::SAVE_CONFIRM_SCENE:
            m_subjectSaveConfirm.notifiyObserver(m_selectedSceneIdx, m_uiName);
            break;

            default:
            break;
        }
    }
};

# endif