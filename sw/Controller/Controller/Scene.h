#ifndef SCENE_H
#define SCENE_H

#include "Param.h"
#include "Scene_enums.h"
#include "SceneParam_enums.h"
#include "SceneParamType.h"
#include "Arpeggiator.h"
#include "string.h"
#include <stdint.h>

/**
@brief Numeric limits of LayerMode
*/
template <>
struct numeric_limits <LayerMode>
{
    /**
    @brief Maximum value
    @result Maximum value of LayerMode
    */
    static constexpr LayerMode max()
    {
        return LayerMode::MAX;
    }
    
    /**
    @brief Minimum value
    @result Minimum value of LayerMode
    */
    static constexpr LayerMode min()
    {
        return LayerMode::MIN;
    }
};

template <uint8_t t_nofLayers, uint8_t t_nofParams>
class SceneParams
{
    public:
    
    SceneParams()
    {}
    
    void setParam(const uint8_t param, const uint8_t value)
    {
        m_params[param] = value;
    }

    uint8_t incParam(const uint8_t param, const uint8_t maxValue = numeric_limits<uint8_t>::max())
    {
        return m_params[param].increment(maxValue);
    }

    uint8_t decParam(const uint8_t param, const uint8_t minValue = numeric_limits<uint8_t>::min())
    {
        return m_params[param].decrement(minValue);
    }

    // Increment parameter and roll-over (e.g. on push button event)
    uint8_t toggleParam(const uint8_t param, const uint8_t minValue = numeric_limits<uint8_t>::min(), const uint8_t maxValue = numeric_limits<uint8_t>::max())
    {
        return m_params[param].incrementRollover(minValue, maxValue);
    }

    uint8_t getParam(const uint8_t param) const
    {
        return m_params[param];
    }
    
    uint8_t getPatchIdx(const uint8_t layerIdx) const
    {
        return m_patchIdx[layerIdx];
    }

    void setPatchIdx(const uint8_t layerIdx, const uint8_t patchIdx)
    {
        m_patchIdx[layerIdx] = patchIdx;
    }

    const String<10> & getName() const
    {
        return m_name;
    }

    String<10> & getName()
    {
        return m_name;
    }

    private:
    
    String<10> m_name;
    
    Param<uint8_t> m_params[t_nofParams] = {0};
    
    Param<uint8_t> m_patchIdx[t_nofLayers];
};




template <uint8_t t_nofLayers>
class Scene
{
    public:
    
    typedef SceneParams<t_nofLayers, static_cast<uint8_t>(SceneParam::NOFENTRIES)> Params;
    
    // Non-standard constructor
    // Arpeggiator settings are part of a scene, but need to be accessible by the actual Arpeggiator
    Scene(Params & params)
    :
    m_params(params)
    {}
    
    void init()
    {
        for (SceneParam param = SceneParam::MIN; param <= SceneParam::MAX; ++param)
        {
            setParam(param, getDefaultValue(getParamType(param)));
            notifySilent(param);
        }
    }

    void notifyAllSilent()
    {
        for (SceneParam param = SceneParam::MIN; param <= SceneParam::MAX; ++param)
        {
            m_subjectParamSilentUpdate.notifiyObserver(param, getParam(param));
        }
    }
    
    // Increment parameter and roll-over (e.g. on push button event)
    void toggleParam(const SceneParam param)
    {
        // Get parameter type
        const SceneParamType paramType = getParamType(param);

        // Perform the actual increment operation considering the parameter limits
        const uint8_t minValue = getMinValue(paramType);
        const uint8_t maxValue = getMaxValue(paramType);
        m_params.toggleParam(static_cast<uint8_t>(param), minValue, maxValue);
        notify(param);
    }
    
        void setParam(const SceneParam param, const uint8_t value)
        {
            m_params.setParam(static_cast<uint8_t>(param), value);
        }

    uint8_t getParam(const SceneParam param) const
    {
        return m_params.getParam(static_cast<uint8_t>(param));
    }

    const String<10> & getName() const
    {
        return m_params.getName();
    }

    String<10> & getName()
    {
        return m_params.getName();
    }

    uint8_t getPatchIdx(const uint8_t layerIdx) const
    {
        return m_params.getPatchIdx(layerIdx);
    }

    void setPatchIdx(const uint8_t layerIdx, const uint8_t patchIdx)
    {
        m_params.setPatchIdx(layerIdx, patchIdx);
    }

    void registerParamObserver(const typename Subject<SceneParam, uint8_t>::Observer& observer)
    {
        m_subjectParamUpdate.registerObserver(observer);
    }
    
    void registerParamSilentObserver(const typename Subject<SceneParam, uint8_t>::Observer& observer)
    {
        m_subjectParamSilentUpdate.registerObserver(observer);
    }
    
    private:
    
    Subject<SceneParam, uint8_t> m_subjectParamUpdate;
    Subject<SceneParam, uint8_t> m_subjectParamSilentUpdate;
     
    Params & m_params;

    void notify(const SceneParam param)
    {
        m_subjectParamUpdate.notifiyObserver(param, getParam(param));
    }

    void notifySilent(const SceneParam param)
    {
        m_subjectParamSilentUpdate.notifiyObserver(param, getParam(param));
    }
};

#endif