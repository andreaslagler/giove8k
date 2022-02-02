#ifndef CONTROLLER_PARAM_DEF_H
#define CONTROLLER_PARAM_DEF_H

#include <stdint.h>

// This enum defines all control change parameters
typedef enum : uint8_t
{
    ECONTROLCHANGE_BANK_SELECT_MSB = 0,
    ECONTROLCHANGE_MODULATION_MSB = 1,
    ECONTROLCHANGE_BREATH_CONROL_MSB = 2,
    ECONTROLCHANGE_FOOT_CONTROL_MSB = 4,
    ECONTROLCHANGE_PORTAMENTO_TIME_MSB = 5,
    ECONTROLCHANGE_DATA_ENTRY_MSB = 6,
    ECONTROLCHANGE_MAIN_VOLUME_MSB = 7,
    ECONTROLCHANGE_BALANCE_MSB = 8,
    ECONTROLCHANGE_PANORAMA_MSB = 10,
    ECONTROLCHANGE_EXPRESSION_MSB =  11,
    ECONTROLCHANGE_GENERAL_PURPOSE_1_MSB = 16,
    ECONTROLCHANGE_GENERAL_PURPOSE_2_MSB = 17,
    ECONTROLCHANGE_GENERAL_PURPOSE_3_MSB = 18,
    ECONTROLCHANGE_GENERAL_PURPOSE_4_MSB = 19,
    ECONTROLCHANGE_BANK_SELECT_LSB = 32,
    ECONTROLCHANGE_MODULATION_LSB = 33,
    ECONTROLCHANGE_BREATH_CONTROL_LSB = 34,
    ECONTROLCHANGE_FOOT_CONTROLLER_LSB = 36,
    ECONTROLCHANGE_PORTAMENTO_TIME_LSB = 37,
    ECONTROLCHANGE_DATA_ENTRY_LSB = 38,
    ECONTROLCHANGE_MAIN_VOLUME_LSB = 39,
    ECONTROLCHANGE_BALANCE_LSB = 40,
    ECONTROLCHANGE_PANORAMA_LSB = 42,
    ECONTROLCHANGE_EXPRESSION_LSB = 43,
    ECONTROLCHANGE_GENERAL_PURPOSE_1_LSB = 48,
    ECONTROLCHANGE_GENERAL_PURPOSE_2_LSB = 49,
    ECONTROLCHANGE_GENERAL_PURPOSE_3_LSB = 50,
    ECONTROLCHANGE_GENERAL_PURPOSE_4_LSB = 51,
    ECONTROLCHANGE_SUSTAIN_ON_OFF = 64,
    ECONTROLCHANGE_PORTAMENTO_ON_OFF = 65,
    ECONTROLCHANGE_SOSTENUTO_ON_OFF = 66,
    ECONTROLCHANGE_SOFT_ON_OFF = 67,
    ECONTROLCHANGE_GENERAL_PURPOSE_5 = 80,
    ECONTROLCHANGE_GENERAL_PURPOSE_6 = 81,
    ECONTROLCHANGE_GENERAL_PURPOSE_7 = 82,
    ECONTROLCHANGE_GENERAL_PURPOSE_8 = 83,
    ECONTROLCHANGE_PORTAMENTO_CONTROL = 84,
    ECONTROLCHANGE_REVERB_DEPTH = 91,
    ECONTROLCHANGE_TREMOLO_DEPTH = 92,
    ECONTROLCHANGE_CHORUS_DEPTH = 93,
    ECONTROLCHANGE_CELESTE_DEPTH = 94,
    ECONTROLCHANGE_PHASER_DEPTH = 95,
    ECONTROLCHANGE_DATA_INCREMENT = 96,
    ECONTROLCHANGE_DATA_DECREMENT = 97,
    ECONTROLCHANGE_NRPN_LSB = 98,
    ECONTROLCHANGE_NRPN_MSB = 99,
    ECONTROLCHANGE_RPN_LSB = 100,
    ECONTROLCHANGE_RPN_MSB = 101,
    ECONTROLCHANGE_ALL_SOUND_OFF = 120,
    ECONTROLCHANGE_RESET_ALL_CONTROLLER = 121,
    ECONTROLCHANGE_LOCAL_CONTROL = 122,
    ECONTROLCHANGE_ALL_NOTES_OFF = 123,
    ECONTROLCHANGE_OMNI_OFF = 124,
    ECONTROLCHANGE_OMNI_ON = 125,
    ECONTROLCHANGE_MONO_ON_POLY_OFF = 126,
    ECONTROLCHANGE_POLY_ON_MONO_OFF = 127,
    ECONTROLCHANGE_NOFENTRIES
} ECONTROLCHANGE;

// This enum defines all NRPNs (non-registered parameters)
// NB: MSB and LSB are 7bit !!!
typedef enum : uint16_t
{
    ENRPN_VIBRATO_RATE = 0x0108,
    ENRPN_VIBRATO_DEPTH = 0x0109,
    ENRPN_VIBRATO_DELAY = 0x010A,
    ENRPN_FILTER_FREQ = 0x0120,
    ENRPN_FILTER_SHAPE = 0x0121,
    ENRPN_FILTER_TYPE,
    ENRPN_OSC1_PITCH,
    ENRPN_OSC1_DETUNE,
    ENRPN_OSC1_WAVEFORM,
    ENRPN_OSC1_SHAPE1,
    ENRPN_OSC1_SHAPE2,
    ENRPN_OSC2_PITCH,
    ENRPN_OSC2_DETUNE,
    ENRPN_OSC2_WAVEFORM,
    ENRPN_OSC2_SHAPE,
    ENRPN_OSC_SYNC,
    ENRPN_OSC_SYNC_PHASE,
    ENRPN_OSC_CROSSMOD,
    ENRPN_OSC_RINGMOD,
    ENRPN_OSC_BALANCE,
    ENRPN_AMP_ENV_A = 0x0163,
    ENRPN_AMP_ENV_D = 0x0164,
    ENRPN_AMP_ENV_S,
    ENRPN_AMP_ENV_R = 0x0166,
    ENRPN_FILTER_ENV_A,
    ENRPN_FILTER_ENV_D,
    ENRPN_FILTER_ENV_S,
    ENRPN_FILTER_ENV_R,
    ENRPN_FILTER_ENV_AMOUNT,
    ENRPN_AUX_ENV_A,
    ENRPN_AUX_ENV_D,
    ENRPN_AUX_ENV_S,
    ENRPN_AUX_ENV_R,
    ENRPN_MODWHEEL_AMOUNT_OSC1_PITCH,
    ENRPN_MODWHEEL_AMOUNT_OSC1_DETUNE,
    ENRPN_MODWHEEL_AMOUNT_OSC1_WAVEFORM,
    ENRPN_MODWHEEL_AMOUNT_OSC1_SHAPE1,
    ENRPN_MODWHEEL_AMOUNT_OSC1_SHAPE2,
    ENRPN_MODWHEEL_AMOUNT_OSC2_PITCH,
    ENRPN_MODWHEEL_AMOUNT_OSC2_DETUNE,
    ENRPN_MODWHEEL_AMOUNT_OSC2_WAVEFORM,
    ENRPN_MODWHEEL_AMOUNT_OSC2_SHAPE,
    ENRPN_MODWHEEL_AMOUNT_OSC_SYNC_PHASE,
    ENRPN_MODWHEEL_AMOUNT_OSC_CROSSMOD,
    ENRPN_MODWHEEL_AMOUNT_OSC_RINGMOD,
    ENRPN_MODWHEEL_AMOUNT_OSC_BALANCE,
    ENRPN_MODWHEEL_AMOUNT_FILTER_FREQ,
    ENRPN_MODWHEEL_AMOUNT_FILTER_SHAPE,
    ENRPN_MODWHEEL_AMOUNT_LFO2_RATE,
    ENRPN_AUXENV_AMOUNT_OSC1_PITCH,
    ENRPN_AUXENV_AMOUNT_OSC1_DETUNE,
    ENRPN_AUXENV_AMOUNT_OSC1_WAVEFORM,
    ENRPN_AUXENV_AMOUNT_OSC1_SHAPE1,
    ENRPN_AUXENV_AMOUNT_OSC1_SHAPE2,
    ENRPN_AUXENV_AMOUNT_OSC2_PITCH,
    ENRPN_AUXENV_AMOUNT_OSC2_DETUNE,
    ENRPN_AUXENV_AMOUNT_OSC2_WAVEFORM,
    ENRPN_AUXENV_AMOUNT_OSC2_SHAPE,
    ENRPN_AUXENV_AMOUNT_OSC_SYNC_PHASE,
    ENRPN_AUXENV_AMOUNT_OSC_CROSSMOD,
    ENRPN_AUXENV_AMOUNT_OSC_RINGMOD,
    ENRPN_AUXENV_AMOUNT_OSC_BALANCE,
    ENRPN_AUXENV_AMOUNT_FILTER_FREQ,
    ENRPN_AUXENV_AMOUNT_FILTER_SHAPE,
    ENRPN_AUXENV_AMOUNT_LFO2_RATE,
    ENRPN_LFO1_RATE,
    ENRPN_LFO1_WAVEFORM,
    ENRPN_LFO1_AMOUNT_OSC1_PITCH,
    ENRPN_LFO1_AMOUNT_OSC1_DETUNE,
    ENRPN_LFO1_AMOUNT_OSC1_WAVEFORM,
    ENRPN_LFO1_AMOUNT_OSC1_SHAPE1,
    ENRPN_LFO1_AMOUNT_OSC1_SHAPE2,
    ENRPN_LFO1_AMOUNT_OSC2_PITCH,
    ENRPN_LFO1_AMOUNT_OSC2_DETUNE,
    ENRPN_LFO1_AMOUNT_OSC2_WAVEFORM,
    ENRPN_LFO1_AMOUNT_OSC2_SHAPE,
    ENRPN_LFO1_AMOUNT_OSC_SYNC_PHASE,
    ENRPN_LFO1_AMOUNT_OSC_CROSSMOD,
    ENRPN_LFO1_AMOUNT_OSC_RINGMOD,
    ENRPN_LFO1_AMOUNT_OSC_BALANCE,
    ENRPN_LFO1_AMOUNT_FILTER_FREQ,
    ENRPN_LFO1_AMOUNT_FILTER_SHAPE,
    ENRPN_LFO1_AMOUNT_LFO2_RATE,
    ENRPN_LFO2_RATE,
    ENRPN_LFO2_WAVEFORM,
    ENRPN_LFO2_AMOUNT_OSC1_PITCH,
    ENRPN_LFO2_AMOUNT_OSC1_DETUNE,
    ENRPN_LFO2_AMOUNT_OSC1_WAVEFORM,
    ENRPN_LFO2_AMOUNT_OSC1_SHAPE1,
    ENRPN_LFO2_AMOUNT_OSC1_SHAPE2,
    ENRPN_LFO2_AMOUNT_OSC2_PITCH,
    ENRPN_LFO2_AMOUNT_OSC2_DETUNE,
    ENRPN_LFO2_AMOUNT_OSC2_WAVEFORM,
    ENRPN_LFO2_AMOUNT_OSC2_SHAPE,
    ENRPN_LFO2_AMOUNT_OSC_SYNC_PHASE,
    ENRPN_LFO2_AMOUNT_OSC_CROSSMOD,
    ENRPN_LFO2_AMOUNT_OSC_RINGMOD,
    ENRPN_LFO2_AMOUNT_OSC_BALANCE,
    ENRPN_LFO2_AMOUNT_FILTER_FREQ,
    ENRPN_LFO2_AMOUNT_FILTER_SHAPE,
    ENRPN_LFO_SYNC_PHASE,
    ENRPN_LFO_SYNC,
    ENRPN_NOFENTRIES
} ENRPN;

#endif