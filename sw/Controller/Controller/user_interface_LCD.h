#ifndef USER_INTERFACE_LCD_H
#define USER_INTERFACE_LCD_H

#include <stdint.h>
#include "PatchParam_enums.h"
#include "ParamType.h"
#include "lookup_table.h"
#include "pgm_string.h"
#include "Hardware_def.h"

/**
@brief User Interface LCD
*/
class UserInterfaceLCD
{
    public:
    
    static void onLoadPatch(const uint8_t idx, const String<10>& name)
    {
        LCD::clear();
        LCD::home();
        LCD::putsP("Load Patch:"_pgm);
        LCD::setCursor(1,0);
        LCD::putNum(idx);
        LCD::putsP(" - "_pgm);
        LCD::puts(name);
    }
    
    static void onSavePatch(const uint8_t idx, const UIEditableString<10>& name)
    {
        LCD::clear();
        LCD::home();
        LCD::putsP("Save Patch:"_pgm);
        LCD::setCursor(1,0);
        LCD::putNum(idx);
        LCD::putsP(" - "_pgm);
        LCD::puts(name.toString());
    }
    
    static void onLoadScene(const uint8_t idx, const String<10>& name)
    {
        LCD::clear();
        LCD::home();
        LCD::putsP("Load Scene:"_pgm);
        LCD::setCursor(1,0);
        LCD::putNum(idx);
        LCD::putsP(" - "_pgm);
        LCD::puts(name);
    }
    
    static void onSaveScene(const uint8_t idx, const UIEditableString<10>& name)
    {
        LCD::clear();
        LCD::home();
        LCD::putsP("Save Scene:"_pgm);
        LCD::setCursor(1,0);
        LCD::putNum(idx);
        LCD::putsP(" - "_pgm);
        LCD::puts(name.toString());
    }
    
    static void onSaveRename(const uint8_t idx, const UIEditableString<10>& name)
    {
        LCD::clear();
        LCD::home();
        LCD::putsP("name: "_pgm);
        LCD::setCursor(0,6 + name.getCurrentCharacterIdx());
        LCD::putc('v');
        LCD::setCursor(1,0);
        LCD::putNum(idx);
        LCD::putsP(" - "_pgm);
        LCD::puts(name.toString());
    }
    
    static void onSaveConfirm(const uint8_t idx, const UIEditableString<10>& name)
    {
        LCD::clear();
        LCD::home();
        LCD::putsP("Confirm:"_pgm);
        LCD::setCursor(1,0);
        LCD::putNum(idx);
        LCD::putsP(" - "_pgm);
        LCD::puts(name.toString());
    }
    
    static void onSelectedLayerUpdate(const uint8_t LayerIdx)
    {
        LCD::clear();
        LCD::home();
        LCD::putsP("Selected"_pgm);
        LCD::setCursor(1,0);
        LCD::putsP("Layer"_pgm);
        LCD::setCursor(0,LCD::getNofColumns()-3);
        LCD::putNum(LayerIdx);
    }
    
    static void onPatchParamUpdate(const PatchParam param, const uint8_t value)
    {
        LCD::clear();
        printParamName(param);
        printParamValue(param, value);
    }

    static void onSceneParamUpdate(const SceneParam param, const uint8_t value)
    {
        LCD::clear();
        printParamName(param);
        printParamValue(param, value);
    }
    
    static void onArpParamUpdate(const ArpeggiatorParam param, const uint8_t value)
    {
        LCD::clear();
        printParamName(param);
        printParamValue(param, value);
    }
    
    static void ShowHomeScreen(const uint8_t sceneIdx, const String<10>& sceneName, const uint8_t patchIdx, const String<10>& patchName)
    {
        LCD::clear();
        LCD::home();
        
        LCD::putsP("S-"_pgm);
        LCD::putNum(sceneIdx, '0');
        LCD::putsP(":"_pgm);
        LCD::puts(sceneName);
        
        LCD::setCursor(1, 0);
        LCD::putsP("P-"_pgm);
        LCD::putNum(patchIdx, '0');
        LCD::putsP(":"_pgm);
        LCD::puts(patchName);
    }
    
    private:
    
    typedef typename Hardware::LCD LCD;

    static void printParamName(const PatchParam param)
    {
        const ParamName paramName = GetParamName(param);
        // Align left
        LCD::clear();
        LCD::home();
        LCD::putsP(paramName.m_s1);
        LCD::setCursor(1,0);
        LCD::putsP(paramName.m_s2);
    }

    static void printParamValue(const PatchParam param, uint8_t value)
    {
        switch (getParamType(param))
        {
            case PatchParamType::ONOFF:
            // on/off param
            PrintOnOff(value);
            break;

            case PatchParamType::PERC_0_100:
            // 0..100 percent
            Print0_100Percent(value);
            break;

            case PatchParamType::PERC_100_100:
            // -100..100 percent
            Print100_100Percent(value);
            break;

            case PatchParamType::PERC_50_50:
            // -50..50 percent
            Print50_50Percent(value);
            break;

            case PatchParamType::CENT:
            // -50..50 cents
            PrintCent(value);
            break;

            case PatchParamType::SEMITONE:
            // -24..24 semitones
            PrintSemitone(value);
            break;

            case PatchParamType::FILTERTYPE:
            // Filter type
            PrintFilterType(value);
            break;

            case PatchParamType::OSC1_WAVEFORM:
            // OSC Waveform
            PrintOSC1Waveform(value);
            break;

            case PatchParamType::OSC2_WAVEFORM:
            // OSC Waveform
            PrintOSC2Waveform(value);
            break;

            case PatchParamType::LFO1_WAVEFORM:
            case PatchParamType::LFO2_WAVEFORM:
            // LFO Waveform
            PrintLFOWaveform(value);
            break;

            case PatchParamType::LFO_SYNC:
            // LFO sync
            PrintLFOSync(value);
            break;

            default:
            LCD::setCursor(0,13);
            LCD::putNum(value);
            break;
        }
    }
    
    static void printParamName(const SceneParam param)
    {
        const ParamName paramName = GetParamName(param);
        // Align left
        LCD::clear();
        LCD::home();
        LCD::putsP(paramName.m_s1);
        LCD::setCursor(1,0);
        LCD::putsP(paramName.m_s2);
    }

    static void printParamValue(const SceneParam param, uint8_t value)
    {
        switch (getParamType(param))
        {
            case SceneParamType::LAYER_MODE:
            // Layer mode
            printLayerMode(value);
            break;

            default:
            LCD::setCursor(0,13);
            LCD::putNum(value);
            break;
        }
    }
    
    static void printParamName(const ArpeggiatorParam param)
    {
        const ParamName paramName = GetParamName(param);
        // Align left
        LCD::clear();
        LCD::home();
        LCD::putsP(paramName.m_s1);
        LCD::setCursor(1,0);
        LCD::putsP(paramName.m_s2);
    }

    static void printParamValue(const ArpeggiatorParam param, uint8_t value)
    {
        switch (getParamType(param))
        {
            case ArpeggiatorParamType::MODE:
            // Arpeggiator mode
            PrintArpMode(value);
            break;

            case ArpeggiatorParamType::PATTERN:
            // Arpeggiator pattern
            PrintArpPattern(value);
            break;

            //case ArpeggiatorParamType::BPM:
            //// beats per minute
            //PrintBPM(value);
            //break;

            //case ArpeggiatorParamType::SCALE:
            //// Scale
            //PrintScale(value);
            //break;

            default:
            LCD::setCursor(0,13);
            LCD::putNum(value);
            break;
        }
    }
    
    static void PrintOnOff(const uint8_t value)
    {
        LCD::setCursor(0,LCD::getNofColumns()-3);
        LCD::putsP(value > 0 ? " On"_pgm : "Off"_pgm);
    }

    static void Print0_100Percent(const uint8_t value)
    {
        // Map 0..255 to 0..100
        const uint8_t uiPercent = (uint16_t(101 * value)) >> 8;

        LCD::setCursor(0,LCD::getNofColumns()-4);
        LCD::putNum(uiPercent);
        LCD::putc('%');
    }

    static void Print100_100Percent(const uint8_t value)
    {
        // Map 0..255 to 0..200
        const uint8_t uiPercent = (uint16_t(201 * value)) >> 8;

        // Map 0..200 to -100..100
        const int8_t iPercent = uiPercent - 100;

        LCD::setCursor(0,LCD::getNofColumns()-5);
        LCD::putNum(iPercent);
        LCD::putc('%');
    }

    static void Print50_50Percent(const uint8_t value)
    {
        // Map 0..255 to 0..100
        const uint8_t uiPercent = (uint16_t(101 * value)) >> 8;

        // Map 0..200 to -50..50
        const int8_t iPercent = uiPercent - 50;

        LCD::setCursor(0,LCD::getNofColumns()-5);
        LCD::putNum(iPercent);
        LCD::putc('%');
    }

    static void PrintCent(const uint8_t value)
    {
        // Map 0..255 to 0..100
        const uint8_t uiCent = (uint16_t(101 * value)) >> 8;

        // Map 0..100 to -50..50
        const int8_t iCent = uiCent - 50;

        LCD::setCursor(0,LCD::getNofColumns()-10);
        LCD::putNum(iCent);
        LCD::putsP(" cents"_pgm);
    }

    static void PrintSemitone(const uint8_t value)
    {
        // Map 0..255 to 0..48
        const uint8_t uiSemitone = (uint16_t(49 * value)) >> 8;

        // Map 0..48 to -24..24
        const int8_t iSemitone = uiSemitone - 24;

        LCD::setCursor(0,LCD::getNofColumns()-10);
        LCD::putNum(iSemitone);
        LCD::putsP(" semis"_pgm);
    }

    static void PrintFilterType(const uint8_t value)
    {
        typedef SparseLUT<const char *, uint8_t, static_cast<uint8_t>(FilterType::NOFENTRIES)> Table;

        constexpr static const PROGMEM Table LUT
        (
        "n/a"_pgm,
        Table::Entry(static_cast<uint8_t>(FilterType::NONE), "    None"_pgm),
        Table::Entry(static_cast<uint8_t>(FilterType::LOWPASS_2P), "LP 2Pole"_pgm),
        Table::Entry(static_cast<uint8_t>(FilterType::HIGHPASS_2P), "HP 2Pole"_pgm),
        Table::Entry(static_cast<uint8_t>(FilterType::BANDPASS_2P), "BP 2Pole"_pgm),
        Table::Entry(static_cast<uint8_t>(FilterType::LOWPASS_4P), "LP 4Pole"_pgm),
        Table::Entry(static_cast<uint8_t>(FilterType::HIGHPASS_4P), "HP 4Pole"_pgm),
        Table::Entry(static_cast<uint8_t>(FilterType::BANDPASS_4P), "BP 4Pole"_pgm),
        Table::Entry(static_cast<uint8_t>(FilterType::VOCAL), "   Vocal"_pgm)
        );

        // Align right
        LCD::setCursor(0,LCD::getNofColumns()-8);
        LCD::putsP(LUT.getP(value));
    }

    static void PrintOSC1Waveform(const uint8_t value)
    {
        typedef SparseLUT<const char *, uint8_t, static_cast<uint8_t>(Osc1Waveform::NOFENTRIES)> Table;

        constexpr static const PROGMEM Table LUT
        (
        "n/a"_pgm,
        Table::Entry(static_cast<uint8_t>(Osc1Waveform::SSAW), "   S Saw"_pgm),
        Table::Entry(static_cast<uint8_t>(Osc1Waveform::TRIMOD), " Mod Tri"_pgm),
        Table::Entry(static_cast<uint8_t>(Osc1Waveform::FEEDBACK), "Feedback"_pgm),
        Table::Entry(static_cast<uint8_t>(Osc1Waveform::RECT), "    Rect"_pgm),
        Table::Entry(static_cast<uint8_t>(Osc1Waveform::SAW), "     Saw"_pgm),
        Table::Entry(static_cast<uint8_t>(Osc1Waveform::TRI), "     Tri"_pgm),
        Table::Entry(static_cast<uint8_t>(Osc1Waveform::SINE), "    Sine"_pgm),
        Table::Entry(static_cast<uint8_t>(Osc1Waveform::NOISE), "   Noise"_pgm)
        );

        // Align right
        LCD::setCursor(0,LCD::getNofColumns()-8);
        LCD::putsP(LUT.getP(value));
    }

    static void PrintOSC2Waveform(const uint8_t value)
    {
        typedef SparseLUT<const char *, uint8_t, static_cast<uint8_t>(Osc2Waveform::NOFENTRIES)> Table;
        
        constexpr static const PROGMEM Table LUT
        (
        "n/a"_pgm,
        Table::Entry(static_cast<uint8_t>(Osc2Waveform::RECT), " Rect"_pgm),
        Table::Entry(static_cast<uint8_t>(Osc2Waveform::SAW), "  Saw"_pgm),
        Table::Entry(static_cast<uint8_t>(Osc2Waveform::TRI), "  Tri"_pgm),
        Table::Entry(static_cast<uint8_t>(Osc2Waveform::SINE), " Sine"_pgm),
        Table::Entry(static_cast<uint8_t>(Osc2Waveform::NOISE), "Noise"_pgm)
        );

        // Align right
        LCD::setCursor(0,LCD::getNofColumns()-5);
        LCD::putsP(LUT.getP(value));
    }

    static void PrintLFOWaveform(const uint8_t value)
    {
        typedef SparseLUT<const char *, uint8_t, static_cast<uint8_t>(LFOWaveform::NOFENTRIES)> Table;
        
        constexpr static const PROGMEM Table LUT
        (
        "n/a"_pgm,
        Table::Entry(static_cast<uint8_t>(LFOWaveform::SQUARE), "Square"_pgm),
        Table::Entry(static_cast<uint8_t>(LFOWaveform::TRI), "   Tri"_pgm),
        Table::Entry(static_cast<uint8_t>(LFOWaveform::SAW), "   Saw"_pgm),
        Table::Entry(static_cast<uint8_t>(LFOWaveform::SINE), "  Sine"_pgm),
        Table::Entry(static_cast<uint8_t>(LFOWaveform::RANDOM), "Random"_pgm),
        Table::Entry(static_cast<uint8_t>(LFOWaveform::SAMPLEHOLD), "   S&H"_pgm)
        );

        // Align right
        LCD::setCursor(0,LCD::getNofColumns()-6);
        LCD::putsP(LUT.getP(value));
    }

    static void PrintLFOSync(const uint8_t value)
    {
        typedef SparseLUT<const char *, uint8_t, static_cast<uint8_t>(LFOSync::NOFENTRIES)> Table;
        
        constexpr static const PROGMEM Table LUT
        (
        "n/a"_pgm,
        Table::Entry(static_cast<uint8_t>(LFOSync::OFF), " Off"_pgm),
        Table::Entry(static_cast<uint8_t>(LFOSync::LFO1), "LFO1"_pgm),
        Table::Entry(static_cast<uint8_t>(LFOSync::KEY), " Key"_pgm)
        );

        // Align right
        LCD::setCursor(0,LCD::getNofColumns()-4);
        LCD::putsP(LUT.getP(value));
    }

    static void PrintArpMode(const uint8_t value)
    {
        typedef SparseLUT<const char *, uint8_t, static_cast<uint8_t>(ArpeggiatorMode::NOFENTRIES)> Table;
        
        constexpr static const PROGMEM Table LUT
        (
        "n/a"_pgm,
        Table::Entry(static_cast<uint8_t>(ArpeggiatorMode::OFF), "   Off"_pgm),
        Table::Entry(static_cast<uint8_t>(ArpeggiatorMode::NORMAL), "Normal"_pgm),
        Table::Entry(static_cast<uint8_t>(ArpeggiatorMode::HOLD), "  Hold"_pgm)
        );

        // Align right
        LCD::setCursor(0,LCD::getNofColumns()-6);
        LCD::putsP(LUT.getP(value));
    }

    static void PrintArpPattern(const uint8_t value)
    {
        using Table = SparseLUT<const char *, uint8_t, static_cast<uint8_t>(ArpeggiatorPattern::NOFENTRIES)>;
        
        constexpr static const PROGMEM Table LUT
        (
        "n/a"_pgm,
        Table::Entry(static_cast<uint8_t>(ArpeggiatorPattern::UP), "      Up"_pgm),
        Table::Entry(static_cast<uint8_t>(ArpeggiatorPattern::DOWN), "    Down"_pgm),
        Table::Entry(static_cast<uint8_t>(ArpeggiatorPattern::UPDOWN), "  UpDown"_pgm),
        Table::Entry(static_cast<uint8_t>(ArpeggiatorPattern::UPDOWN_HOLD), "UpDnHold"_pgm),
        Table::Entry(static_cast<uint8_t>(ArpeggiatorPattern::RANDOM), "  Random"_pgm)
        );

        // Align right
        LCD::setCursor(0,LCD::getNofColumns()-8);
        LCD::putsP(LUT.getP(value));
    }

    static void printBPM(const uint8_t value)
    {
        LCD::setCursor(0,LCD::getNofColumns()-7);
        LCD::putNum(value);
        LCD::putsP(" BPM"_pgm);
    }
    
    static void printLayerMode(const uint8_t value)
    {
        typedef SparseLUT<const char *, uint8_t, static_cast<uint8_t>(LayerMode::NOFENTRIES)> Table;
        
        constexpr static const PROGMEM Table LUT
        (
        "n/a"_pgm,
        Table::Entry(static_cast<uint8_t>(LayerMode::SINGLE), "Single"_pgm),
        Table::Entry(static_cast<uint8_t>(LayerMode::MULTI_1X4), "   1x4"_pgm),
        Table::Entry(static_cast<uint8_t>(LayerMode::MULTI_4X1), "   4x1"_pgm),
        Table::Entry(static_cast<uint8_t>(LayerMode::UNISON), "Unison"_pgm)
        );
        
        #undef ENTRY

        LCD::setCursor(0,LCD::getNofColumns()-6);
        LCD::putsP(LUT.getP(value));
    }
    
    

    struct ParamName
    {
        const char * m_s1;
        const char * m_s2;
        
        constexpr ParamName(
        const char * s1 = nullptr,
        const char * s2 = nullptr)
        :
        m_s1(s1),
        m_s2(s2) {}
    };

    // Param name (first line)
    // NB: this function returns a ParamName object in PROGMEM !
    static const ParamName GetParamName(const PatchParam param)
    {
        typedef SparseLUT<ParamName, uint8_t, static_cast<uint8_t>(PatchParam::NOFENTRIES)> Table;
        
        constexpr static const PROGMEM Table LUT(
        ParamName("Unknown"_pgm, ""_pgm),
        typename Table::Entry(static_cast<uint8_t>(PatchParam::OSC1_PITCH), ParamName("Osc1"_pgm, "Pitch"_pgm)),
        typename Table::Entry(static_cast<uint8_t>(PatchParam::OSC1_DETUNE), ParamName("Osc1"_pgm, "Detune"_pgm)),
        typename Table::Entry(static_cast<uint8_t>(PatchParam::OSC1_WAVEFORM), ParamName("Osc1"_pgm, "Waveform"_pgm)),
        typename Table::Entry(static_cast<uint8_t>(PatchParam::OSC1_SHAPE1), ParamName("Osc1"_pgm, "Shape 1"_pgm)),
        typename Table::Entry(static_cast<uint8_t>(PatchParam::OSC1_SHAPE2), ParamName("Osc1"_pgm, "Shape 2"_pgm)),
        typename Table::Entry(static_cast<uint8_t>(PatchParam::OSC2_PITCH), ParamName("Osc2"_pgm, "Pitch"_pgm)),
        typename Table::Entry(static_cast<uint8_t>(PatchParam::OSC2_DETUNE), ParamName("Osc2"_pgm, "Detune"_pgm)),
        typename Table::Entry(static_cast<uint8_t>(PatchParam::OSC2_WAVEFORM), ParamName("Osc2"_pgm, "Waveform"_pgm)),
        typename Table::Entry(static_cast<uint8_t>(PatchParam::OSC2_SHAPE), ParamName("Osc2"_pgm, "Shape"_pgm)),
        typename Table::Entry(static_cast<uint8_t>(PatchParam::OSC_SYNC), ParamName("Osc"_pgm, "Sync"_pgm)),
        typename Table::Entry(static_cast<uint8_t>(PatchParam::OSC_SYNC_PHASE), ParamName("Osc"_pgm, "Sync Phase"_pgm)),
        typename Table::Entry(static_cast<uint8_t>(PatchParam::OSC_CROSSMOD), ParamName("Osc"_pgm, "Cross Mod"_pgm)),
        typename Table::Entry(static_cast<uint8_t>(PatchParam::OSC_RINGMOD), ParamName("Osc"_pgm, "Ring Mod"_pgm)),
        typename Table::Entry(static_cast<uint8_t>(PatchParam::OSC_BALANCE), ParamName("Osc"_pgm, "Balance"_pgm)),
        typename Table::Entry(static_cast<uint8_t>(PatchParam::LEGATO), ParamName("Legato"_pgm, ""_pgm)),
        typename Table::Entry(static_cast<uint8_t>(PatchParam::GLIDE_TIME), ParamName("Glide"_pgm, "Time"_pgm)),
        typename Table::Entry(static_cast<uint8_t>(PatchParam::FILTER_FREQ), ParamName("Filter"_pgm, "Freq"_pgm)),
        typename Table::Entry(static_cast<uint8_t>(PatchParam::FILTER_SHAPE), ParamName("Filter"_pgm, "Shape"_pgm)),
        typename Table::Entry(static_cast<uint8_t>(PatchParam::FILTER_TYPE), ParamName("Filter"_pgm, "Type"_pgm)),
        typename Table::Entry(static_cast<uint8_t>(PatchParam::FILTER_ENV_A), ParamName("Filter Env"_pgm, "Attack"_pgm)),
        typename Table::Entry(static_cast<uint8_t>(PatchParam::FILTER_ENV_D), ParamName("Filter Env"_pgm, "Decay"_pgm)),
        typename Table::Entry(static_cast<uint8_t>(PatchParam::FILTER_ENV_S), ParamName("Filter Env"_pgm, "Sustain"_pgm)),
        typename Table::Entry(static_cast<uint8_t>(PatchParam::FILTER_ENV_R), ParamName("Filter Env"_pgm, "Release"_pgm)),
        typename Table::Entry(static_cast<uint8_t>(PatchParam::FILTER_ENV_AMOUNT), ParamName("Filter Env"_pgm, "Amount"_pgm)),
        typename Table::Entry(static_cast<uint8_t>(PatchParam::FILTER_KEYTRACK), ParamName("Filter"_pgm, "Key Track"_pgm)),
        typename Table::Entry(static_cast<uint8_t>(PatchParam::LEVEL), ParamName("Level"_pgm, ""_pgm)),
        typename Table::Entry(static_cast<uint8_t>(PatchParam::PAN), ParamName("Pan"_pgm, ""_pgm)),
        typename Table::Entry(static_cast<uint8_t>(PatchParam::AMP_ENV_A), ParamName("Amp Env"_pgm, "Attack"_pgm)),
        typename Table::Entry(static_cast<uint8_t>(PatchParam::AMP_ENV_D), ParamName("Amp Env"_pgm, "Decay"_pgm)),
        typename Table::Entry(static_cast<uint8_t>(PatchParam::AMP_ENV_S), ParamName("Amp Env"_pgm, "Sustain"_pgm)),
        typename Table::Entry(static_cast<uint8_t>(PatchParam::AMP_ENV_R), ParamName("Amp Env"_pgm, "Release"_pgm)),
        typename Table::Entry(static_cast<uint8_t>(PatchParam::MODWHEEL_AMOUNT_OSC1_PITCH), ParamName("Mod Wheel>"_pgm, "Osc1 Pitch"_pgm)),
        typename Table::Entry(static_cast<uint8_t>(PatchParam::MODWHEEL_AMOUNT_OSC1_SHAPE1), ParamName("Mod Wheel>"_pgm, "Osc1 Shape 1"_pgm)),
        typename Table::Entry(static_cast<uint8_t>(PatchParam::MODWHEEL_AMOUNT_OSC1_SHAPE2), ParamName("Mod Wheel>"_pgm, "Osc1 Shape 2"_pgm)),
        typename Table::Entry(static_cast<uint8_t>(PatchParam::MODWHEEL_AMOUNT_OSC2_PITCH), ParamName("Mod Wheel>"_pgm, "Osc2 Pitch"_pgm)),
        typename Table::Entry(static_cast<uint8_t>(PatchParam::MODWHEEL_AMOUNT_OSC2_SHAPE), ParamName("Mod Wheel>"_pgm, "Osc2 Shape"_pgm)),
        typename Table::Entry(static_cast<uint8_t>(PatchParam::MODWHEEL_AMOUNT_OSC_SYNC_PHASE), ParamName("Mod Wheel>"_pgm, "Osc Sync Phase"_pgm)),
        typename Table::Entry(static_cast<uint8_t>(PatchParam::MODWHEEL_AMOUNT_OSC_CROSSMOD), ParamName("Mod Wheel>"_pgm, "Osc Cross Mod"_pgm)),
        typename Table::Entry(static_cast<uint8_t>(PatchParam::MODWHEEL_AMOUNT_OSC_RINGMOD), ParamName("Mod Wheel>"_pgm, "Osc Ring Mod"_pgm)),
        typename Table::Entry(static_cast<uint8_t>(PatchParam::MODWHEEL_AMOUNT_OSC_BALANCE), ParamName("Mod Wheel>"_pgm, "Osc Balance"_pgm)),
        typename Table::Entry(static_cast<uint8_t>(PatchParam::MODWHEEL_AMOUNT_FILTER_FREQ), ParamName("Mod Wheel>"_pgm, "Filter Freq"_pgm)),
        typename Table::Entry(static_cast<uint8_t>(PatchParam::MODWHEEL_AMOUNT_FILTER_SHAPE), ParamName("Mod Wheel>"_pgm, "Filter Shape"_pgm)),
        typename Table::Entry(static_cast<uint8_t>(PatchParam::MODWHEEL_AMOUNT_LEVEL), ParamName("Mod Wheel>"_pgm, "Level"_pgm)),
        typename Table::Entry(static_cast<uint8_t>(PatchParam::MODWHEEL_AMOUNT_PAN), ParamName("Mod Wheel>"_pgm, "Pan"_pgm)),
        typename Table::Entry(static_cast<uint8_t>(PatchParam::MODWHEEL_AMOUNT_LFO2_RATE), ParamName("Mod Wheel>"_pgm, "LFO2 Rate"_pgm)),
        typename Table::Entry(static_cast<uint8_t>(PatchParam::LFO1_RATE), ParamName("LFO1"_pgm, "Rate"_pgm)),
        typename Table::Entry(static_cast<uint8_t>(PatchParam::LFO1_WAVEFORM), ParamName("LFO1"_pgm, "Waveform"_pgm)),
        typename Table::Entry(static_cast<uint8_t>(PatchParam::LFO1_AMOUNT_OSC1_PITCH), ParamName("LFO1>"_pgm, "Osc1 Pitch"_pgm)),
        typename Table::Entry(static_cast<uint8_t>(PatchParam::LFO1_AMOUNT_OSC1_SHAPE1), ParamName("LFO1>"_pgm, "Osc1 Shape 1"_pgm)),
        typename Table::Entry(static_cast<uint8_t>(PatchParam::LFO1_AMOUNT_OSC1_SHAPE2), ParamName("LFO1>"_pgm, "Osc1 Shape 2"_pgm)),
        typename Table::Entry(static_cast<uint8_t>(PatchParam::LFO1_AMOUNT_OSC2_PITCH), ParamName("LFO1>"_pgm, "Osc2 Pitch"_pgm)),
        typename Table::Entry(static_cast<uint8_t>(PatchParam::LFO1_AMOUNT_OSC2_SHAPE), ParamName("LFO1>"_pgm, "Osc2 Shape"_pgm)),
        typename Table::Entry(static_cast<uint8_t>(PatchParam::LFO1_AMOUNT_OSC_SYNC_PHASE), ParamName("LFO1>"_pgm, "Osc Sync Phase"_pgm)),
        typename Table::Entry(static_cast<uint8_t>(PatchParam::LFO1_AMOUNT_OSC_CROSSMOD), ParamName("LFO1>"_pgm, "Osc Cross Mod"_pgm)),
        typename Table::Entry(static_cast<uint8_t>(PatchParam::LFO1_AMOUNT_OSC_RINGMOD), ParamName("LFO1>"_pgm, "Osc Ring Mod"_pgm)),
        typename Table::Entry(static_cast<uint8_t>(PatchParam::LFO1_AMOUNT_OSC_BALANCE), ParamName("LFO1>"_pgm, "Osc Balance"_pgm)),
        typename Table::Entry(static_cast<uint8_t>(PatchParam::LFO1_AMOUNT_FILTER_FREQ), ParamName("LFO1>"_pgm, "Filter Freq"_pgm)),
        typename Table::Entry(static_cast<uint8_t>(PatchParam::LFO1_AMOUNT_FILTER_SHAPE), ParamName("LFO1>"_pgm, "Filter Shape"_pgm)),
        typename Table::Entry(static_cast<uint8_t>(PatchParam::LFO1_AMOUNT_LEVEL), ParamName("LFO1>"_pgm, "Level"_pgm)),
        typename Table::Entry(static_cast<uint8_t>(PatchParam::LFO1_AMOUNT_PAN), ParamName("LFO1>"_pgm, "Pan"_pgm)),
        typename Table::Entry(static_cast<uint8_t>(PatchParam::LFO1_AMOUNT_LFO2_RATE), ParamName("LFO1>"_pgm, "LFO2 Rate"_pgm)),
        typename Table::Entry(static_cast<uint8_t>(PatchParam::LFO2_RATE), ParamName("LFO2"_pgm, "Rate"_pgm)),
        typename Table::Entry(static_cast<uint8_t>(PatchParam::LFO2_WAVEFORM), ParamName("LFO2"_pgm, "Waveform"_pgm)),
        typename Table::Entry(static_cast<uint8_t>(PatchParam::LFO2_AMOUNT_OSC1_PITCH), ParamName("LFO2>"_pgm, "Osc1 Pitch"_pgm)),
        typename Table::Entry(static_cast<uint8_t>(PatchParam::LFO2_AMOUNT_OSC1_SHAPE1), ParamName("LFO2>"_pgm, "Osc1 Shape 1"_pgm)),
        typename Table::Entry(static_cast<uint8_t>(PatchParam::LFO2_AMOUNT_OSC1_SHAPE2), ParamName("LFO2>"_pgm, "Osc1 Shape 2"_pgm)),
        typename Table::Entry(static_cast<uint8_t>(PatchParam::LFO2_AMOUNT_OSC2_PITCH), ParamName("LFO2>"_pgm, "Osc2 Pitch"_pgm)),
        typename Table::Entry(static_cast<uint8_t>(PatchParam::LFO2_AMOUNT_OSC2_SHAPE), ParamName("LFO2>"_pgm, "Osc2 Shape"_pgm)),
        typename Table::Entry(static_cast<uint8_t>(PatchParam::LFO2_AMOUNT_OSC_SYNC_PHASE), ParamName("LFO2>"_pgm, "Osc Sync Phase"_pgm)),
        typename Table::Entry(static_cast<uint8_t>(PatchParam::LFO2_AMOUNT_OSC_CROSSMOD), ParamName("LFO2>"_pgm, "Osc Cross Mod"_pgm)),
        typename Table::Entry(static_cast<uint8_t>(PatchParam::LFO2_AMOUNT_OSC_RINGMOD), ParamName("LFO2>"_pgm, "Osc Ring Mod"_pgm)),
        typename Table::Entry(static_cast<uint8_t>(PatchParam::LFO2_AMOUNT_OSC_BALANCE), ParamName("LFO2>"_pgm, "Osc Balance"_pgm)),
        typename Table::Entry(static_cast<uint8_t>(PatchParam::LFO2_AMOUNT_FILTER_FREQ), ParamName("LFO2>"_pgm, "Filter Freq"_pgm)),
        typename Table::Entry(static_cast<uint8_t>(PatchParam::LFO2_AMOUNT_FILTER_SHAPE), ParamName("LFO2>"_pgm, "Filter Shape"_pgm)),
        typename Table::Entry(static_cast<uint8_t>(PatchParam::LFO2_AMOUNT_LEVEL), ParamName("LFO2>"_pgm, "Level"_pgm)),
        typename Table::Entry(static_cast<uint8_t>(PatchParam::LFO2_AMOUNT_PAN), ParamName("LFO2>"_pgm, "Pan"_pgm)),
        typename Table::Entry(static_cast<uint8_t>(PatchParam::LFO_SYNC_PHASE), ParamName("LFO"_pgm, "Sync Phase"_pgm)),
        typename Table::Entry(static_cast<uint8_t>(PatchParam::LFO_SYNC), ParamName("LFO"_pgm, "Sync"_pgm)),
        typename Table::Entry(static_cast<uint8_t>(PatchParam::AUX_ENV_A), ParamName("Aux Env"_pgm, "Attack"_pgm)),
        typename Table::Entry(static_cast<uint8_t>(PatchParam::AUX_ENV_D), ParamName("Aux Env"_pgm, "Decay"_pgm)),
        typename Table::Entry(static_cast<uint8_t>(PatchParam::AUX_ENV_S), ParamName("Aux Env"_pgm, "Sustain"_pgm)),
        typename Table::Entry(static_cast<uint8_t>(PatchParam::AUX_ENV_R), ParamName("Aux Env"_pgm, "Release"_pgm)),
        typename Table::Entry(static_cast<uint8_t>(PatchParam::AUXENV_AMOUNT_OSC1_PITCH), ParamName("Env>"_pgm, "Osc1 Pitch"_pgm)),
        typename Table::Entry(static_cast<uint8_t>(PatchParam::AUXENV_AMOUNT_OSC1_SHAPE1), ParamName("Env>"_pgm, "Osc1 Shape 1"_pgm)),
        typename Table::Entry(static_cast<uint8_t>(PatchParam::AUXENV_AMOUNT_OSC1_SHAPE2), ParamName("Env>"_pgm, "Osc1 Shape 2"_pgm)),
        typename Table::Entry(static_cast<uint8_t>(PatchParam::AUXENV_AMOUNT_OSC2_PITCH), ParamName("Env>"_pgm, "Osc2 Pitch"_pgm)),
        typename Table::Entry(static_cast<uint8_t>(PatchParam::AUXENV_AMOUNT_OSC2_SHAPE), ParamName("Env>"_pgm, "Osc2 Shape"_pgm)),
        typename Table::Entry(static_cast<uint8_t>(PatchParam::AUXENV_AMOUNT_OSC_SYNC_PHASE), ParamName("Env>"_pgm, "Osc Sync Phase"_pgm)),
        typename Table::Entry(static_cast<uint8_t>(PatchParam::AUXENV_AMOUNT_OSC_CROSSMOD), ParamName("Env>"_pgm, "Osc Cross Mod"_pgm)),
        typename Table::Entry(static_cast<uint8_t>(PatchParam::AUXENV_AMOUNT_OSC_RINGMOD), ParamName("Env>"_pgm, "Osc Ring Mod"_pgm)),
        typename Table::Entry(static_cast<uint8_t>(PatchParam::AUXENV_AMOUNT_OSC_BALANCE), ParamName("Env>"_pgm, "Osc Balance"_pgm)),
        typename Table::Entry(static_cast<uint8_t>(PatchParam::AUXENV_AMOUNT_PAN), ParamName("Env>"_pgm, "Pan"_pgm)),
        typename Table::Entry(static_cast<uint8_t>(PatchParam::AUXENV_AMOUNT_FILTER_SHAPE), ParamName("Env>"_pgm, "Filter Shape"_pgm)),
        typename Table::Entry(static_cast<uint8_t>(PatchParam::AUXENV_AMOUNT_LFO2_RATE), ParamName("Env>"_pgm, "LFO2 Rate"_pgm)),
        typename Table::Entry(static_cast<uint8_t>(PatchParam::BASS), ParamName("Bass"_pgm, ""_pgm)),
        typename Table::Entry(static_cast<uint8_t>(PatchParam::TREBLE), ParamName("Treble"_pgm, ""_pgm)),
        typename Table::Entry(static_cast<uint8_t>(PatchParam::CHORUS_DEPTH), ParamName("Chorus"_pgm, "Depth"_pgm)),
        typename Table::Entry(static_cast<uint8_t>(PatchParam::CHORUS_RATE), ParamName("Chorus"_pgm, "Rate"_pgm)),
        typename Table::Entry(static_cast<uint8_t>(PatchParam::CHORUS_MODDEPTH), ParamName("Chorus"_pgm, "Mod Depth"_pgm)),
        typename Table::Entry(static_cast<uint8_t>(PatchParam::CHORUS_SPREAD), ParamName("Chorus"_pgm, "Spread"_pgm)),
        typename Table::Entry(static_cast<uint8_t>(PatchParam::CHORUS_MIX), ParamName("Chorus"_pgm, "Mix"_pgm)),
        typename Table::Entry(static_cast<uint8_t>(PatchParam::ECHO_DELAY), ParamName("Echo"_pgm, "Delay"_pgm)),
        typename Table::Entry(static_cast<uint8_t>(PatchParam::ECHO_FEEDBACK), ParamName("Echo"_pgm, "Feedback"_pgm)),
        typename Table::Entry(static_cast<uint8_t>(PatchParam::ECHO_SPREAD), ParamName("Echo"_pgm, "Spread"_pgm)),
        typename Table::Entry(static_cast<uint8_t>(PatchParam::ECHO_BRIGHTNESS), ParamName("Echo"_pgm, "Brightness"_pgm)),
        typename Table::Entry(static_cast<uint8_t>(PatchParam::ECHO_MIX), ParamName("Echo"_pgm, "Mix"_pgm)),
        typename Table::Entry(static_cast<uint8_t>(PatchParam::BITCRUSHER_SAMPLERATE), ParamName("Bitcrusher"_pgm, "Sample Rate"_pgm)),
        typename Table::Entry(static_cast<uint8_t>(PatchParam::BITCRUSHER_QUANTIZATION), ParamName("Bitcrusher"_pgm, "Quantization"_pgm)),
        typename Table::Entry(static_cast<uint8_t>(PatchParam::BITCRUSHER_MIX), ParamName("Bitcrusher"_pgm, "Mix"_pgm)),
        typename Table::Entry(static_cast<uint8_t>(PatchParam::DISTORTION_DRIVE), ParamName("Distortion"_pgm, "Drive"_pgm)),
        typename Table::Entry(static_cast<uint8_t>(PatchParam::DISTORTION_SHAPE), ParamName("Distortion"_pgm, "Shape"_pgm)),
        typename Table::Entry(static_cast<uint8_t>(PatchParam::DISTORTION_MIX), ParamName("Distortion"_pgm, "Mix"_pgm))
        );

        return LUT.getP(static_cast<uint8_t>(param));
    }
    
    // Param name (first line)
    // NB: this function returns a ParamName object in PROGMEM !
    static const ParamName GetParamName(const SceneParam param)
    {
        typedef SparseLUT<ParamName, uint8_t, static_cast<uint8_t>(SceneParam::NOFENTRIES)> Table;
        
        constexpr static const PROGMEM Table LUT(
        ParamName("Unknown"_pgm, ""_pgm),
        typename Table::Entry(static_cast<uint8_t>(SceneParam::LAYER_MODE), ParamName("Layer"_pgm, "Mode"_pgm))
        );

        return LUT.getP(static_cast<uint8_t>(param));
    }
    
    // Param name (first line)
    // NB: this function returns a ParamName object in PROGMEM !
    static const ParamName GetParamName(const ArpeggiatorParam param)
    {
        typedef SparseLUT<ParamName, uint8_t, static_cast<uint8_t>(ArpeggiatorParam::NOFENTRIES)> Table;
        
        constexpr static const PROGMEM Table LUT(
        ParamName("Unknown"_pgm, ""_pgm),
        typename Table::Entry(static_cast<uint8_t>(ArpeggiatorParam::MODE), ParamName("Arp"_pgm, "Mode"_pgm)),
        typename Table::Entry(static_cast<uint8_t>(ArpeggiatorParam::SPEED), ParamName("Arp"_pgm, "Speed"_pgm)),
        typename Table::Entry(static_cast<uint8_t>(ArpeggiatorParam::PATTERN), ParamName("Arp"_pgm, "Pattern"_pgm)),
        typename Table::Entry(static_cast<uint8_t>(ArpeggiatorParam::SCALE), ParamName("Arp"_pgm, "Scale"_pgm)),
        typename Table::Entry(static_cast<uint8_t>(ArpeggiatorParam::VELOCITY), ParamName("Arp"_pgm, "Velocity"_pgm))
        );

        return LUT.getP(static_cast<uint8_t>(param));
    }
};

# endif