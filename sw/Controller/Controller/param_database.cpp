/*
Copyright (C) 2022 Andreas Lagler

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

#include "param_database.h"

ParamDatabase::ParamDatabase()
{
    // Assign types to UI params
    
    // Effects section
    getParamValue(PatchParam::TONE_CONTROL_BASS) = SignedParam(0);
    getParamValue(PatchParam::TONE_CONTROL_TREBLE) = SignedParam(0);
    getParamValue(PatchParam::MULTI_FX_LEVEL) = UnsignedParam(0);
    getParamValue(PatchParam::DELAY_TIME) = UnsignedParam(0);
    getParamValue(PatchParam::DELAY_FEEDBACK) = UnsignedParam(0);
    getParamValue(PatchParam::DELAY_LEVEL) = UnsignedParam(0);
    getParamValue(PatchParam::VOICE_MOD_SEND) = OnOff(false);

    // LFO 1 section
    getParamValue(PatchParam::LFO1_WAVEFORM) = LFO1Waveform::TRI;
    getParamValue(PatchParam::LFO1_RATE) = UnsignedParam(0);
    getParamValue(PatchParam::LFO1_FADE) = UnsignedParam(0);

    // Modulation (LFO2 section
    getParamValue(PatchParam::LFO2_RATE) = UnsignedParam(0);
    getParamValue(PatchParam::LFO2_DEPTH_SELECT) = LFO2DepthSelect::PITCH;
    getParamValue(PatchParam::LFO2_DEPTH_PITCH) = SignedParam(0);
    getParamValue(PatchParam::LFO2_DEPTH_FILTER) = SignedParam(0);
    getParamValue(PatchParam::LFO2_DEPTH_AMP) = SignedParam(0);

    // Portamento section
    getParamValue(PatchParam::PORTAMENTO_ON) = OnOff(false);
    getParamValue(PatchParam::PORTAMENTO_TIME) = UnsignedParam(0);

    // Osc 1 section
    getParamValue(PatchParam::OSC1_WAVEFORM) = OSC1Waveform::SUPER_SAW;
    getParamValue(PatchParam::OSC1_CONTROL1) = UnsignedParam(0);
    getParamValue(PatchParam::OSC1_CONTROL2) = UnsignedParam(0);

    // Osc 2 section
    getParamValue(PatchParam::OSC2_WAVEFORM) = OSC2Waveform::SAW;
    getParamValue(PatchParam::OSC2_EXT) = OnOff(false);
    getParamValue(PatchParam::OSC2_SYNC) = OnOff(false);
    getParamValue(PatchParam::OSC2_RANGE) = OSC2Range(0);
    getParamValue(PatchParam::OSC2_FINE_WIDE) = PartDetune(0); // Detune by default, actual parameter type depends on OSC2 Range
    getParamValue(PatchParam::OSC2_CONTROL1) = UnsignedParam(0);
    getParamValue(PatchParam::OSC2_CONTROL2) = UnsignedParam(0);
    getParamValue(PatchParam::OSC2_RING) = OnOff(false);

    // Osc common section
    getParamValue(PatchParam::OSC_BALANCE) = SignedParam(0);
    getParamValue(PatchParam::OSC_XMOD_DEPTH) = UnsignedParam(0);
    getParamValue(PatchParam::OSC_LFO1_ENV_DESTINATION) = OSCLFO1EnvDest::OSC1_2;
    getParamValue(PatchParam::OSC_LFO1_DEPTH) = SignedParam(0);
    getParamValue(PatchParam::OSC_SHIFT) = OSCShift(0);

    // Pitch envelope section
    getParamValue(PatchParam::PITCH_ENVELOPE_DEPTH) = SignedParam(0);
    getParamValue(PatchParam::PITCH_ENVELOPE_A) = UnsignedParam(0);
    getParamValue(PatchParam::PITCH_ENVELOPE_D) = UnsignedParam(0);

    // Filter section
    getParamValue(PatchParam::FILTER_TYPE) = FilterType::LPF;
    getParamValue(PatchParam::FILTER_12DB_24DB) = FilterSlope::_12DB;
    getParamValue(PatchParam::FILTER_CUTOFF_FREQ) = UnsignedParam(63);
    getParamValue(PatchParam::FILTER_RESONANCE) = UnsignedParam(0);
    getParamValue(PatchParam::FILTER_KEY_FOLLOW) = SignedParam(0);
    getParamValue(PatchParam::FILTER_LFO1_DEPTH) = SignedParam(0);

    // Filter envelope section
    getParamValue(PatchParam::FILTER_ENVELOPE_DEPTH) = SignedParam(0);
    getParamValue(PatchParam::FILTER_ENVELOPE_A) = UnsignedParam(0);
    getParamValue(PatchParam::FILTER_ENVELOPE_D) = UnsignedParam(0);
    getParamValue(PatchParam::FILTER_ENVELOPE_S) = UnsignedParam(127);
    getParamValue(PatchParam::FILTER_ENVELOPE_R) = UnsignedParam(0);

    // Amp section
    getParamValue(PatchParam::AMP_LEVEL) = UnsignedParam(63);
    getParamValue(PatchParam::AMP_PAN) = AmpPan::OFF;
    getParamValue(PatchParam::AMP_LFO1_DEPTH) = SignedParam(0);
    
    // Amp envelope section
    getParamValue(PatchParam::AMP_ENVELOPE_A) = UnsignedParam(0);
    getParamValue(PatchParam::AMP_ENVELOPE_D) = UnsignedParam(0);
    getParamValue(PatchParam::AMP_ENVELOPE_S) = UnsignedParam(127);
    getParamValue(PatchParam::AMP_ENVELOPE_R) = UnsignedParam(0);

    // Control section
    getParamValue(PatchParam::MONO) = OnOff(false);
    getParamValue(PatchParam::LEGATO) = OnOff(false);
    getParamValue(PatchParam::UNSON) = OnOff(false);
    getParamValue(PatchParam::VELOCITY) = OnOff(false);
    getParamValue(PatchParam::VELOCITY_ASSIGN) = Range_127_100_50::_127;
    getParamValue(PatchParam::CONTROL_ASSIGN) = Range_127_100_50::_127;    

    // Panel Select section
    getParamValue(PerformanceParam::PART_SELECT) = PartSelect::LOWER;
    
    // Key Mode section
    getParamValue(PerformanceParam::KEY_MODE) = KeyMode::SINGLE;
    
    // Arpeggiator/RPS section
    getParamValue(PerformanceParam::ARP_STATE) = OnOff(false);
    getParamValue(PerformanceParam::ARP_MODE) = ArpMode::UP;
    getParamValue(PerformanceParam::ARP_RANGE) = ArpRange(1);
    getParamValue(PerformanceParam::ARP_HOLD) = OnOff(false);
    getParamValue(PerformanceParam::ARP_TEMPO) = ArpTempo(135);
    
    // Voice modulator section
    getParamValue(PerformanceParam::VOICE_MODULATOR_STATE) = OnOff(false);
    
    // External input section
    getParamValue(PerformanceParam::VOCAL_INPUT_SELECT) = OnOff(false);

    // Bank [1] PFM COMMON
    Array<uint8_t, 16> name{0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
    getParamValue(PerformanceParam::PERFORMANCE_NAME) = NameParam(name);
    getParamValue(PerformanceParam::PART_DETUNE) = PartDetune(0);
    getParamValue(PerformanceParam::OUTPUT_ASSIGN) = OutputAssign();
    getParamValue(PerformanceParam::VOICE_ASSIGN) = VoiceAssign();
    getParamValue(PerformanceParam::SPLIT_POINT) = MidiNote(0);
    getParamValue(PerformanceParam::ARP_DESTINATION) = ArpDestination();
    getParamValue(PerformanceParam::ARP_BEAT_PATTERN) = ArpBeatPattern();
    getParamValue(PerformanceParam::INDIVIDUAL_TRIG_STATE) = OnOff();
    getParamValue(PerformanceParam::INDIVIDUAL_TRIG_DESTINATION) = TrigDestination();
    getParamValue(PerformanceParam::INDIVIDUAL_TRIG_SOURCE_CHANNEL) = IndivTrigSrcChannel();
    getParamValue(PerformanceParam::INDIVIDUAL_TRIG_SOURCE_NOTE) = IndivTrigSrcNote(128);
    
    // Bank [2] VOICE MOD
    getParamValue(PerformanceParam::ALGORITHM) = Algorithm::SOLID;
    getParamValue(PerformanceParam::CONTROL1_ASSIGN) = ControlAssign::ENSEMBLE_LEVEL;
    getParamValue(PerformanceParam::CONTROL2_ASSIGN) = ControlAssign::ENSEMBLE_LEVEL;
    getParamValue(PerformanceParam::EXT_INST_SEND) = OnOff(false);
    getParamValue(PerformanceParam::EXT_VOCAL_SEND) = OnOff(false);
    getParamValue(PerformanceParam::EXT_VOCAL_SEND) = OnOff(false);
    getParamValue(PerformanceParam::EXT_VOCAL_SEND) = OnOff(false);
    getParamValue(PerformanceParam::VOICE_MODULATOR_DELAY_TYPE) = DelayType::PANNING_L_R;
    getParamValue(PerformanceParam::VOICE_MODULATOR_DELAY_SYNC) = DelaySync::OFF;
    getParamValue(PerformanceParam::ENSEMBLE_TYPE) = EnsembleType::ENSEMBLE_MILD;
    getParamValue(PerformanceParam::ENSEMBLE_SYNC) = EnsembleSync::OFF;
    getParamValue(PerformanceParam::VOCAL_MORPH_CONTROL) = OnOff(false);
    getParamValue(PerformanceParam::VOCAL_MORPH_SENS) = SignedParam(0);
    getParamValue(PerformanceParam::VOCAL_MORPH_THRESHOLD) = UnsignedParam(0);

    // Bank [3] PART
    getParamValue(PartParam::PART_TRANSPOSE) = PartTranspose(0);
    getParamValue(PartParam::PART_MIDI_CHANNEL) = PartMidiChannel::OFF;
    getParamValue(PartParam::CHORUS_SYNC) = ChorusSync::OFF;
    getParamValue(PartParam::DELAY_SYNC) = DelaySync::OFF;
    getParamValue(PartParam::LFO_SYNC) = EnsembleSync::OFF;

    // Bank [4] PATCH
    getParamValue(PatchParam::PATCH_NAME) = NameParam(name);
    getParamValue(PatchParam::MULTI_FX_TYPE) = MultiFXType::SUPER_CHORUS_SLOW;
    getParamValue(PatchParam::DELAY_TYPE) = DelayType::PANNING_L_R;
    getParamValue(PatchParam::BEND_RANGE_UP) = BendRangeUp(2);
    getParamValue(PatchParam::BEND_RANGE_DOWN) = BendRangeDown(2);
    getParamValue(PatchParam::MORPH_BEND_ASSIGN) = OnOff(false);
    getParamValue(PatchParam::UNISON_DETUNE) = UnisonDetune(0);
    getParamValue(PatchParam::ENV_TYPE_SOLO) = EnvTypeSolo::STANDARD;
    getParamValue(PatchParam::PATCH_GAIN) = PatchGain::_0DB;
    getParamValue(PatchParam::EXT_TRIG_SWITCH) = OnOff(false);
    getParamValue(PatchParam::EXT_TRIG_DEST) = TrigDestination::FILTER;
    
    // Bank [5] MIDI
    getParamValue(SystemParam::LOCAL_SWITCH) = OnOff(false);
    getParamValue(SystemParam::MIDI_SYNC) = MidiSync::OFF;
    getParamValue(SystemParam::DEVICE_ID) = DeviceId(17);
    getParamValue(SystemParam::RX_EXCLUSIVE) = OnOff(false);
    getParamValue(SystemParam::PERFORMANCE_CONTROL_CHANNEL) = PartMidiChannel::OFF;
    getParamValue(SystemParam::REMOTE_KEYBOARD_CHANNEL) = RemoteKeyboardChannel::ALL;
    getParamValue(SystemParam::MIDI_THRU) = MidiThru::OFF;
    getParamValue(SystemParam::TX_RX_EDIT) = OnOff(false);
    getParamValue(SystemParam::TX_RX_EDIT_MODE) = TxRxEditMode::MODE1;
    getParamValue(SystemParam::TX_RX_SETTING) = UnsignedParam(0); // TODO
    getParamValue(SystemParam::TX_RX_PROGRAM_CHANGE) = TxRxProgramChange::OFF;
    getParamValue(SystemParam::CONTROL_UP) = UnsignedParam(0); // TODO
    getParamValue(SystemParam::CONTROL_DOWN) = UnsignedParam(0); // TODO

    // Bank [6] SETUP
    getParamValue(SystemParam::LCD_CONTRAST) = LcdContrast(4);
    getParamValue(SystemParam::MASTER_TUNE) = MasterTune(127);
    getParamValue(SystemParam::POWER_UP_MODE) = UnsignedParam(0); // TODO
    getParamValue(SystemParam::PATTERN_TRIGGER_QUANTIZE) = PatternTriggerQuantize::OFF;
    getParamValue(SystemParam::MOTION_RESTART) = OnOff(false);

    
    // Voice Modulator Panel
    getParamValue(PerformanceParam::ENSEMBLE_LEVEL) = UnsignedParam(0);
    getParamValue(PerformanceParam::VOICE_MODULATOR_DELAY_LEVEL) = UnsignedParam(0);
    getParamValue(PerformanceParam::VOICE_MODULATOR_DELAY_TIME) = UnsignedParam(0);
    getParamValue(PerformanceParam::VOICE_MODULATOR_DELAY_FEEDBACK) = UnsignedParam(0);
    getParamValue(PerformanceParam::VOCAL_MIX) = UnsignedParam(0);
    getParamValue(PerformanceParam::VOICE_MODULATOR_RESONANCE) = UnsignedParam(0);
    getParamValue(PerformanceParam::VOICE_MODULATOR_ENV_RELEASE) = UnsignedParam(0);
    getParamValue(PerformanceParam::VOCAL_HOLD) = OnOff(false);
    getParamValue(PerformanceParam::VOICE_MODULATOR_PAN) = SignedParam(0);
    getParamValue(PerformanceParam::VOICE_MODULATOR_LEVEL) = UnsignedParam(0);
    getParamValue(PerformanceParam::VOICE_MODULATOR_NOISE_LEVEL) = UnsignedParam(0);
    getParamValue(PerformanceParam::VOICE_MODULATOR_NOISE_CUTOFF) = UnsignedParam(0);
    getParamValue(PerformanceParam::GATE_THRESHOLD) = UnsignedParam(0);
    getParamValue(PerformanceParam::ROBOT_OSCILLATOR_LEVEL) = UnsignedParam(0);
    getParamValue(PerformanceParam::ROBOT_OSCILLATOR_PITCH) = UnsignedParam(0);
    getParamValue(PerformanceParam::ROBOT_OSCILLATOR_CONTROL) = UnsignedParam(0);
    getParamValue(PerformanceParam::CHARACTER_1) = UnsignedParam(0);
    getParamValue(PerformanceParam::CHARACTER_2) = UnsignedParam(0);
    getParamValue(PerformanceParam::CHARACTER_3) = UnsignedParam(0);
    getParamValue(PerformanceParam::CHARACTER_4) = UnsignedParam(0);
    getParamValue(PerformanceParam::CHARACTER_5) = UnsignedParam(0);
    getParamValue(PerformanceParam::CHARACTER_6) = UnsignedParam(0);
    getParamValue(PerformanceParam::CHARACTER_7) = UnsignedParam(0);
    getParamValue(PerformanceParam::CHARACTER_8) = UnsignedParam(0);
    getParamValue(PerformanceParam::CHARACTER_9) = UnsignedParam(0);
    getParamValue(PerformanceParam::CHARACTER_10) = UnsignedParam(0);
    getParamValue(PerformanceParam::CHARACTER_11) = UnsignedParam(0);
    getParamValue(PerformanceParam::CHARACTER_12) = UnsignedParam(0);
}
