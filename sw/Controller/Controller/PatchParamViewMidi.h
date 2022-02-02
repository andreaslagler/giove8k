#ifndef PATCH_PARAM_VIEW_MIDI_H
#define PATCH_PARAM_VIEW_MIDI_H

#include "PatchParam_enums.h"
#include "ParamType.h"
#include "ControllerParam_def.h"
#include "ParamType.h"
#include "MIDITypes.h"
#include <stdint.h>

template <typename MidiOut>
class CParamViewMidi
{
	private:

	static constexpr uint8_t ConvertValue(PatchParam, uint8_t);
	static ENRPN ParamToNRPN(PatchParam);

	// Buffer for RPN/NRPN number
	static uint8_t s_uiLastValue;
	static uint8_t s_uiLastMSB;
	static uint8_t s_uiLastLSB;
    
    static MidiOut s_midiOut;

	public:

	static void Update(const PatchParam eParam, uint8_t uiValue)
	{
		// Write MSB
		const ENRPN eNRPN = ParamToNRPN(eParam);
		const uint8_t uiMSB = uint8_t(eNRPN >> 7);
		if (s_uiLastMSB != uiMSB)
		{
			s_midiOut.write(MidiControlChange{ECONTROLCHANGE_NRPN_MSB, uiMSB}); // NRPN MSB
			s_uiLastMSB = uiMSB;
		}

		// Write LSB
		const uint8_t uiLSB = uint8_t(eNRPN & 0b01111111);
		if (s_uiLastLSB != uiLSB)
		{
			s_midiOut.write(MidiControlChange{ECONTROLCHANGE_NRPN_LSB, uiLSB}); // NRPN LSB
			s_uiLastLSB = uiLSB;
		}

		uiValue = ConvertValue(eParam, uiValue);
		if (s_uiLastValue != uiValue)
		{
			s_midiOut.write(MidiControlChange{ECONTROLCHANGE_DATA_ENTRY_MSB, uiValue}); // Data Entry MSB
			s_uiLastValue = uiValue;
		}
	}
};

//////////////////////////////////////////////////////////////////////////
// Static init
template <typename MidiOut>
uint8_t CParamViewMidi<MidiOut>::s_uiLastMSB = 128;

template <typename MidiOut>
uint8_t CParamViewMidi<MidiOut>::s_uiLastLSB = 128;

template <typename MidiOut>
uint8_t CParamViewMidi<MidiOut>::s_uiLastValue = 128;

template <typename MidiOut>
MidiOut CParamViewMidi<MidiOut>::s_midiOut;

template <typename MidiOut>
constexpr uint8_t CParamViewMidi<MidiOut>::ConvertValue(const PatchParam eParam, const uint8_t uiValue)
{
	switch (getParamType(eParam))
	{
		case ParamType::SEMITONE:
		// -12..12 semitones
		
		// Map 0..255 to 0..24
		return uint8_t((uint16_t(25 * uiValue)) >> 8) ;
		break;

		case ParamType::ONOFF:
		case ParamType::FILTERTYPE:
		case ParamType::LFO_WAVEFORM:
		case ParamType::OSC1_WAVEFORM:
		case ParamType::OSC2_WAVEFORM:
		// Enums --> bypass
		return uiValue;

		default:
		// Map 0..255 to 0..127
		return uiValue >> 1;
	}
}


template <typename MidiOut>
ENRPN CParamViewMidi<MidiOut>::ParamToNRPN(const PatchParam eParam)
{
	typedef SparseLUT<ENRPN, uint8_t, static_cast<uint8_t>(PatchParam::NOFENTRIES)> Table;
	
	#define ENTRY(Controller) (Table::Entry(static_cast<uint8_t>(PatchParam::Controller), ENRPN_##Controller))

	static const PROGMEM Table LUT(
	ENRPN(0),
	ENTRY(OSC1_WAVEFORM),
	ENTRY(OSC1_SHAPE1),
	ENTRY(OSC1_SHAPE2),
	ENTRY(OSC2_PITCH),
	ENTRY(OSC2_WAVEFORM),
	ENTRY(OSC2_SHAPE),
	ENTRY(OSC_SYNC),
	ENTRY(OSC_SYNC_PHASE),
	ENTRY(OSC_CROSSMOD),
	ENTRY(OSC_RINGMOD),
	ENTRY(OSC_BALANCE),
	ENTRY(FILTER_FREQ),
	ENTRY(FILTER_SHAPE),
	ENTRY(FILTER_SHAPE),
	ENTRY(FILTER_ENV_A),
	ENTRY(FILTER_ENV_D),
	ENTRY(FILTER_ENV_S),
	ENTRY(FILTER_ENV_R),
	ENTRY(FILTER_ENV_AMOUNT),
	ENTRY(AMP_ENV_A),
	ENTRY(AMP_ENV_D),
	ENTRY(AMP_ENV_S),
	ENTRY(AMP_ENV_R),
	ENTRY(LFO1_RATE),
	ENTRY(LFO1_WAVEFORM),
	ENTRY(MODWHEEL_AMOUNT_OSC1_PITCH),
	ENTRY(MODWHEEL_AMOUNT_OSC1_SHAPE1),
	ENTRY(MODWHEEL_AMOUNT_OSC1_SHAPE2),
	ENTRY(MODWHEEL_AMOUNT_OSC2_PITCH),
	ENTRY(MODWHEEL_AMOUNT_OSC2_SHAPE),
	ENTRY(MODWHEEL_AMOUNT_OSC_SYNC_PHASE),
	ENTRY(MODWHEEL_AMOUNT_OSC_CROSSMOD),
	ENTRY(MODWHEEL_AMOUNT_OSC_RINGMOD),
	ENTRY(MODWHEEL_AMOUNT_OSC_BALANCE),
	ENTRY(MODWHEEL_AMOUNT_FILTER_FREQ),
	ENTRY(MODWHEEL_AMOUNT_FILTER_SHAPE),
	ENTRY(MODWHEEL_AMOUNT_LFO2_RATE),
	ENTRY(LFO1_AMOUNT_OSC1_PITCH),
	ENTRY(LFO1_AMOUNT_OSC1_SHAPE1),
	ENTRY(LFO1_AMOUNT_OSC1_SHAPE2),
	ENTRY(LFO1_AMOUNT_OSC2_PITCH),
	ENTRY(LFO1_AMOUNT_OSC2_SHAPE),
	ENTRY(LFO1_AMOUNT_OSC_SYNC_PHASE),
	ENTRY(LFO1_AMOUNT_OSC_CROSSMOD),
	ENTRY(LFO1_AMOUNT_OSC_RINGMOD),
	ENTRY(LFO1_AMOUNT_OSC_BALANCE),
	ENTRY(LFO1_AMOUNT_FILTER_FREQ),
	ENTRY(LFO1_AMOUNT_FILTER_SHAPE),
	ENTRY(LFO1_AMOUNT_LFO2_RATE),
	ENTRY(LFO2_RATE),
	ENTRY(LFO2_WAVEFORM),
	ENTRY(LFO2_AMOUNT_OSC1_PITCH),
	ENTRY(LFO2_AMOUNT_OSC1_SHAPE1),
	ENTRY(LFO2_AMOUNT_OSC1_SHAPE2),
	ENTRY(LFO2_AMOUNT_OSC2_PITCH),
	ENTRY(LFO2_AMOUNT_OSC2_SHAPE),
	ENTRY(LFO2_AMOUNT_OSC_SYNC_PHASE),
	ENTRY(LFO2_AMOUNT_OSC_CROSSMOD),
	ENTRY(LFO2_AMOUNT_OSC_RINGMOD),
	ENTRY(LFO2_AMOUNT_OSC_BALANCE),
	ENTRY(LFO2_AMOUNT_FILTER_FREQ),
	ENTRY(LFO2_AMOUNT_FILTER_SHAPE),
	ENTRY(LFO_SYNC_PHASE),
	ENTRY(LFO_SYNC),
	ENTRY(AUX_ENV_A),
	ENTRY(AUX_ENV_D),
	ENTRY(AUX_ENV_S),
	ENTRY(AUX_ENV_R),
	ENTRY(AUXENV_AMOUNT_OSC1_PITCH),
	ENTRY(AUXENV_AMOUNT_OSC1_SHAPE1),
	ENTRY(AUXENV_AMOUNT_OSC1_SHAPE2),
	ENTRY(AUXENV_AMOUNT_OSC2_PITCH),
	ENTRY(AUXENV_AMOUNT_OSC2_SHAPE),
	ENTRY(AUXENV_AMOUNT_OSC_SYNC_PHASE),
	ENTRY(AUXENV_AMOUNT_OSC_CROSSMOD),
	ENTRY(AUXENV_AMOUNT_OSC_RINGMOD),
	ENTRY(AUXENV_AMOUNT_OSC_BALANCE),
	ENTRY(AUXENV_AMOUNT_FILTER_SHAPE),
	ENTRY(AUXENV_AMOUNT_LFO2_RATE)
	);
    
	#undef ENTRY

	return LUT.getP(static_cast<uint8_t>(eParam));
}

#endif