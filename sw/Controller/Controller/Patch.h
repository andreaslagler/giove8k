#ifndef PATCH_H
#define PATCH_H

#include "PatchParam_enums.h"
#include "PatchParamType.h"
#include "Param.h"
#include "string.h"
#include "lookup_table.h"

#include <stdint.h>

template <uint8_t t_nofParams, const uint8_t t_nameSize>
class PatchData
{
    public:
    
    constexpr const String<t_nameSize> & getName() const
    {
        return m_name;
    }
    
    constexpr String<t_nameSize> & getName()
    {
        return m_name;
    }
    
    void setParam(const uint8_t param, const uint8_t value)
    {
        m_Params[param] = value;
    }

    uint8_t incParam(const uint8_t param, const uint8_t maxValue = numeric_limits<uint8_t>::max())
    {
        return m_Params[param].increment(maxValue);
    }

    uint8_t decParam(const uint8_t param, const uint8_t minValue = numeric_limits<uint8_t>::min())
    {
        return m_Params[param].decrement(minValue);
    }

    // Increment parameter and roll-over (e.g. on push button event)
    uint8_t toggleParam(const uint8_t param, const uint8_t minValue = numeric_limits<uint8_t>::min(), const uint8_t maxValue = numeric_limits<uint8_t>::max())
    {
        return m_Params[param].incrementRollover(minValue, maxValue);
    }

    uint8_t getParam(const uint8_t param) const
    {
        return m_Params[param];
    }

    private:

    String<t_nameSize> m_name;

    Param<uint8_t> m_Params[t_nofParams];
};


class Patch : public PatchData<static_cast<uint8_t>(PatchParam::NOFENTRIES), 10>
{
    public:
    
    typedef PatchData<static_cast<uint8_t>(PatchParam::NOFENTRIES), 10> Data;
    
    void notifyAllSilent()
    {
        for (PatchParam param = PatchParam::MIN; param <= PatchParam::MAX; ++param)
        {
            m_subjectParamSilentUpdate.notifiyObserver(param, getParam(param));
        }
    }
    
    void setParam(const PatchParam param, const uint8_t value)
    {
        Base::setParam(static_cast<uint8_t>(param), value);
        notify(param);
    }

    void incParam(const PatchParam param)
    {
        // Get parameter type
        const PatchParamType paramType = getParamType(param);

        // Perform the actual increment operation considering the parameter limits
        const uint8_t maxValue = getMaxValue(paramType);
        Base::incParam(static_cast<uint8_t>(param), maxValue);
        notify(param);
    }

    void decParam(const PatchParam param)
    {
        // Get parameter type
        const PatchParamType paramType = getParamType(param);

        // Perform the actual increment operation considering the parameter limits
        const uint8_t minValue = getMinValue(paramType);

        Base::decParam(static_cast<uint8_t>(param), minValue);
        notify(param);
    }

    // Increment parameter and roll-over (e.g. on push button event)
    void toggleParam(const PatchParam param)
    {
        // Get parameter type
        const PatchParamType paramType = getParamType(param);

        // Perform the actual increment operation considering the parameter limits
        const uint8_t minValue = getMinValue(paramType);
        const uint8_t maxValue = getMaxValue(paramType);
        Base::toggleParam(static_cast<uint8_t>(param), minValue, maxValue);
        notify(param);
    }

    uint8_t getParam(const PatchParam param) const
    {
        return Base::getParam(static_cast<uint8_t>(param));
    }
    
    Patch()
    {
        init();
    }
    
    void init()
    {
        for (PatchParam param = PatchParam::MIN; param <= PatchParam::MAX; ++param)
        {
            Base::setParam(static_cast<uint8_t>(param), getDefaultValue(getParamType(param)));
            m_subjectParamSilentUpdate.notifiyObserver(param, getParam(param));
        }
    }

    void incModSrc()
    {
        m_selectedModSrc.increment();
        const PatchParam param = getSelectedModParam();
        notify(param);
    }

    void decModSrc()
    {
        // Perform the actual increment operation considering the parameter limits
        m_selectedModSrc.decrement();
        const PatchParam param = getSelectedModParam();
        notify(param);
    }

    void incModDst()
    {
        // Perform the actual increment operation considering the parameter limits
        const uint8_t uiParamMax = getMaxModDst(m_selectedModSrc);
        m_selectedModDst[static_cast<uint8_t>(m_selectedModSrc.getValue())].increment(uiParamMax);
        const PatchParam param = getSelectedModParam();
        notify(param);
    }

    void decModDst()
    {
        // Perform the actual increment operation considering the parameter limits
        m_selectedModDst[static_cast<uint8_t>(m_selectedModSrc.getValue())].decrement();
        const PatchParam param = getSelectedModParam();
        notify(param);
    }

    void incFXParam()
    {
        // Perform the actual increment/decrement operation considering the parameter limits
        m_selectedFXParam.increment();
        const PatchParam param = getSelectedFXParam();
        notify(param);
    }

    void decFXParam()
    {
        // Perform the actual increment/decrement operation considering the parameter limits
        m_selectedFXParam.decrement();
        const PatchParam param = getSelectedFXParam();
        notify(param);
    }

    void setModAmount(const uint8_t value)
    {
        const PatchParam param = getSelectedModParam();
        setParam(param, value);
        notify(param);
    }

    void setFXParam(const uint8_t value)
    {
        const PatchParam param = getSelectedFXParam();
        setParam(param, value);
        notify(param);
    }

    void registerParamObserver(const typename Subject<PatchParam, uint8_t>::Observer& observer)
    {
        m_subjectParamUpdate.registerObserver(observer);
    }
    
    void registerParamSilentObserver(const typename Subject<PatchParam, uint8_t>::Observer& observer)
    {
        m_subjectParamSilentUpdate.registerObserver(observer);
    }
    
    private:

    Subject<PatchParam, uint8_t> m_subjectParamUpdate;
    Subject<PatchParam, uint8_t> m_subjectParamSilentUpdate;
    
    void notify(const PatchParam param)
    {
        m_subjectParamUpdate.notifiyObserver(param, getParam(param));
    }
    
    typedef PatchData<static_cast<uint8_t>(PatchParam::NOFENTRIES), 10> Base;
    
    Param<FXParam> m_selectedFXParam;
    Param<ModSource> m_selectedModSrc;
    Param<uint8_t> m_selectedModDst[static_cast<uint8_t>(ModSource::NOFENTRIES)]; // TODO consider making this only one variable
    
    // Assign modulation parameter to patch parameter
    PatchParam getSelectedModParam()
    {
        const uint8_t selectedModDst = m_selectedModDst[static_cast<uint8_t>(m_selectedModSrc.getValue())];
        switch (m_selectedModSrc)
        {
            case ModSource::MODWHEEL:
            return modWheelDstToPatchParam(static_cast<ModWheelDst>(selectedModDst));
            
            case ModSource::LFO1:
            return lfo1DstToPatchParam(static_cast<LFO1Dst>(selectedModDst));
            
            case ModSource::LFO2:
            return lfo2DstToPatchParam(static_cast<LFO2Dst>(selectedModDst));
            
            case ModSource::AUXENV:
            return auxEnvDstToPatchParam(static_cast<AuxEnvDst>(selectedModDst));
            
            default:
            return PatchParam::DUMMY;
        }
    }

    // Mapping of Modulation wheel destination to parameter
    PatchParam modWheelDstToPatchParam(const ModWheelDst modWheelDst)
    {
        typedef SparseLUT<PatchParam, uint8_t, static_cast<uint8_t>(ModWheelDst::NOFENTRIES)> Table;
        
        #define ENTRY(Controller) (Table::Entry(static_cast<uint8_t>(ModWheelDst::Controller), PatchParam::MODWHEEL_AMOUNT_##Controller))

        static const PROGMEM Table LUT(
        PatchParam::DUMMY,
        ENTRY(OSC1_PITCH),
        ENTRY(OSC1_SHAPE1),
        ENTRY(OSC1_SHAPE2),
        ENTRY(OSC2_PITCH),
        ENTRY(OSC2_SHAPE),
        ENTRY(OSC_SYNC_PHASE),
        ENTRY(OSC_CROSSMOD),
        ENTRY(OSC_RINGMOD),
        ENTRY(OSC_BALANCE),
        ENTRY(FILTER_FREQ),
        ENTRY(FILTER_SHAPE),
        ENTRY(LEVEL),
        ENTRY(PAN),
        ENTRY(LFO2_RATE)
        );
        
        #undef ENTRY

        return LUT.getP(static_cast<uint8_t>(modWheelDst));
    }

    // Mapping of LFO1 destination to parameter
    PatchParam lfo1DstToPatchParam(const LFO1Dst lfo1Dst)
    {
        typedef SparseLUT<PatchParam, uint8_t, static_cast<uint8_t>(LFO1Dst::NOFENTRIES)> Table;
        
        #define ENTRY(Controller) (Table::Entry(static_cast<uint8_t>(LFO1Dst::Controller), PatchParam::LFO1_AMOUNT_##Controller))

        static const PROGMEM Table LUT(
        PatchParam::DUMMY,
        ENTRY(OSC1_PITCH),
        ENTRY(OSC1_SHAPE1),
        ENTRY(OSC1_SHAPE2),
        ENTRY(OSC2_PITCH),
        ENTRY(OSC2_SHAPE),
        ENTRY(OSC_SYNC_PHASE),
        ENTRY(OSC_CROSSMOD),
        ENTRY(OSC_RINGMOD),
        ENTRY(OSC_BALANCE),
        ENTRY(FILTER_FREQ),
        ENTRY(FILTER_SHAPE),
        ENTRY(LEVEL),
        ENTRY(PAN),
        ENTRY(LFO2_RATE)
        );

        #undef ENTRY
        
        return LUT.getP(static_cast<uint8_t>(lfo1Dst));
    }

    // Mapping of LFO2 destination to parameter
    PatchParam lfo2DstToPatchParam(const LFO2Dst lfo2Dst)
    {
        typedef SparseLUT<PatchParam, uint8_t, static_cast<uint8_t>(LFO2Dst::NOFENTRIES)> Table;
        
        #define ENTRY(Controller) (Table::Entry(static_cast<uint8_t>(LFO2Dst::Controller), PatchParam::LFO2_AMOUNT_##Controller))

        static const PROGMEM Table LUT(
        PatchParam::DUMMY,
        ENTRY(OSC1_PITCH),
        ENTRY(OSC1_SHAPE1),
        ENTRY(OSC1_SHAPE2),
        ENTRY(OSC2_PITCH),
        ENTRY(OSC2_SHAPE),
        ENTRY(OSC_SYNC_PHASE),
        ENTRY(OSC_CROSSMOD),
        ENTRY(OSC_RINGMOD),
        ENTRY(OSC_BALANCE),
        ENTRY(FILTER_FREQ),
        ENTRY(FILTER_SHAPE),
        ENTRY(LEVEL),
        ENTRY(PAN)
        );
        
        #undef ENTRY

        return LUT.getP(static_cast<uint8_t>(lfo2Dst));
    }

    // Mapping of Aux Env destination to parameter
    PatchParam auxEnvDstToPatchParam(const AuxEnvDst auxEnvDst)
    {
        typedef SparseLUT<PatchParam, uint8_t, static_cast<uint8_t>(AuxEnvDst::NOFENTRIES)> Table;
        
        #define ENTRY(Controller) (Table::Entry(static_cast<uint8_t>(AuxEnvDst::Controller), PatchParam::AUXENV_AMOUNT_##Controller))

        static const PROGMEM Table LUT(
        PatchParam::DUMMY,
        ENTRY(OSC1_PITCH),
        ENTRY(OSC1_SHAPE1),
        ENTRY(OSC1_SHAPE2),
        ENTRY(OSC2_PITCH),
        ENTRY(OSC2_SHAPE),
        ENTRY(OSC_SYNC_PHASE),
        ENTRY(OSC_CROSSMOD),
        ENTRY(OSC_RINGMOD),
        ENTRY(OSC_BALANCE),
        ENTRY(FILTER_SHAPE),
        ENTRY(PAN),
        ENTRY(LFO2_RATE)
        );
        
        #undef ENTRY
        
        return LUT.getP(static_cast<uint8_t>(auxEnvDst));
    }

    // Mapping of FX Param to parameter
    PatchParam getSelectedFXParam()
    {
        typedef SparseLUT<PatchParam, uint8_t, static_cast<uint8_t>(FXParam::NOFENTRIES)> Table;
        
        static const PROGMEM Table LUT(
        PatchParam::DUMMY,
        Table::Entry(static_cast<uint8_t>(FXParam::CHORUS_DEPTH), PatchParam::CHORUS_DEPTH),
        Table::Entry(static_cast<uint8_t>(FXParam::CHORUS_RATE), PatchParam::CHORUS_RATE),
        Table::Entry(static_cast<uint8_t>(FXParam::CHORUS_MODDEPTH), PatchParam::CHORUS_MODDEPTH),
        Table::Entry(static_cast<uint8_t>(FXParam::CHORUS_SPREAD), PatchParam::CHORUS_SPREAD),
        Table::Entry(static_cast<uint8_t>(FXParam::CHORUS_MIX), PatchParam::CHORUS_MIX),
        Table::Entry(static_cast<uint8_t>(FXParam::ECHO_DELAY), PatchParam::ECHO_DELAY),
        Table::Entry(static_cast<uint8_t>(FXParam::ECHO_FEEDBACK), PatchParam::ECHO_FEEDBACK),
        Table::Entry(static_cast<uint8_t>(FXParam::ECHO_SPREAD), PatchParam::ECHO_SPREAD),
        Table::Entry(static_cast<uint8_t>(FXParam::ECHO_BRIGHTNESS), PatchParam::ECHO_BRIGHTNESS),
        Table::Entry(static_cast<uint8_t>(FXParam::ECHO_MIX), PatchParam::ECHO_MIX),
        Table::Entry(static_cast<uint8_t>(FXParam::BITCRUSHER_SAMPLERATE), PatchParam::BITCRUSHER_SAMPLERATE),
        Table::Entry(static_cast<uint8_t>(FXParam::BITCRUSHER_QUANTIZATION), PatchParam::BITCRUSHER_QUANTIZATION),
        Table::Entry(static_cast<uint8_t>(FXParam::BITCRUSHER_MIX), PatchParam::BITCRUSHER_MIX),
        Table::Entry(static_cast<uint8_t>(FXParam::DISTORTION_DRIVE), PatchParam::DISTORTION_DRIVE),
        Table::Entry(static_cast<uint8_t>(FXParam::DISTORTION_SHAPE), PatchParam::DISTORTION_SHAPE),
        Table::Entry(static_cast<uint8_t>(FXParam::DISTORTION_MIX), PatchParam::DISTORTION_MIX)
        );
        
        return LUT.getP(static_cast<uint8_t>(m_selectedFXParam.getValue()));
    }


    // Get maximum modulation destination index for selected modulation source
    uint8_t getMaxModDst(const ModSource modSrc)
    {
        typedef SparseLUT<uint8_t, uint8_t, static_cast<uint8_t>(ModSource::NOFENTRIES)> Table;
        
        constexpr static const PROGMEM Table MaxModDest(
        0,
        Table::Entry {static_cast<uint8_t>(ModSource::MODWHEEL), static_cast<uint8_t>(ModWheelDst::MAX)},
        Table::Entry {static_cast<uint8_t>(ModSource::LFO1), static_cast<uint8_t>(LFO1Dst::MAX)},
        Table::Entry {static_cast<uint8_t>(ModSource::LFO2), static_cast<uint8_t>(LFO2Dst::MAX)},
        Table::Entry {static_cast<uint8_t>(ModSource::AUXENV), static_cast<uint8_t>(AuxEnvDst::MAX)});
        return MaxModDest.getP(static_cast<uint8_t>(modSrc));
    }
};

#endif