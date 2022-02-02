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

#include "hardware_def.h"
#include "Controller.h"
#include "dsp_interface.h"
#include "user_interface.h"
#include "PatchParamViewMidi.h"

#include "ring_buffer.h"
#include "MidiInput.h"
#include "MidiOutput.h"

#include "scheduler.h"

#include <util/delay.h>

#include "m328p_Timer1.h"
#include "m328p_Timer2.h"


//////////////////////////////////////////////////////////////////////////
// Definitions

//////////////////////////////////////////////////////////////////////////
// Type defs
typedef Scheduler<Hardware::Atomic>::Task Task;
typedef Scheduler<Hardware::Atomic>::Delay Delay;

//////////////////////////////////////////////////////////////////////////
// Global variables

Controller controller;
Scheduler<Hardware::Atomic> scheduler;

// MIDI subsystem
RingBuffer<uint8_t, 5, true> midiInBuffer;
MidiInput midiInput;



//////////////////////////////////////////////////////////////////////////
// TASKs

// Recurring Task: GUI refresh
Task refreshGUITask(
[]{
    Hardware::PotentiometerScanner::scanPotentiometers();
    controller.requestHomeScreen();    
    Hardware::LCD::refresh();
    constexpr Delay tGUIRefreshIntervalMS = 100;
    scheduler.schedule(refreshGUITask, tGUIRefreshIntervalMS);
});

// Task: Re-Arm GUI Controls on SerialIO0
Task reArmSerialIO0Task(
[]{
    Hardware::SerialIO_0::reArmInterrupt();
    Hardware::Int0::enableInterrupt();
});

// Task: Read SerialIO0 (with zero latency), then schedule the re-arm task
Task readSerialIO0Task(
[]{
    Hardware::SerialIO_0::onInterrupt();
    constexpr Delay tSerialIO0SettlingMS = 10;
    scheduler.schedule(reArmSerialIO0Task, tSerialIO0SettlingMS);
});

// Task: Re-Arm GUI Controls on SerialIO1
Task reArmSerialIO1Task(
[]{
    Hardware::SerialIO_1::reArmInterrupt();
    Hardware::Int1::enableInterrupt();
});

// Task: Read SerialIO1 (with zero latency), then schedule the re-arm task
Task readSerialIO1Task(
[]{
    Hardware::SerialIO_1::onInterrupt();
    constexpr Delay tSerialIO1SettlingMS = 10;
    scheduler.schedule(reArmSerialIO1Task, tSerialIO1SettlingMS);
});

// Recurring Task: Send clock event to arpeggiator
Task clockArpeggiatorTask(
[]{
    // Re-arm arpeggiator
    if (controller.getArpeggiatorState())
    {
        Delay tArp32Period = controller.getArpeggiatorClock();
        scheduler.schedule(clockArpeggiatorTask, tArp32Period);
    }
    controller.clockArpeggiator();
});





//////////////////////////////////////////////////////////////////////////
// Int 0 ISR
void Hardware::Int0::handleInterrupt()
{
    // Prevent the ISR from being called before the re-arm
    disableInterrupt();
    scheduler.schedule(readSerialIO0Task, 0);
}

//////////////////////////////////////////////////////////////////////////
// Int 1 ISR
void Hardware::Int1::handleInterrupt()
{
    // Prevent the ISR from being called before the re-arm
    disableInterrupt();
    scheduler.schedule(readSerialIO1Task, 0);
}

//////////////////////////////////////////////////////////////////////////
// ISR for UDR empty interrupt
void Hardware::MidiIO::USART::handleUDREmpty()
{
    Hardware::MidiIO::transmitNextByte();
}

//////////////////////////////////////////////////////////////////////////
// ISR for Rx Complete interrupt
void Hardware::MidiIO::USART::handleRXComplete()
{
    midiInBuffer.write(Hardware::MidiIO::get());
}

//////////////////////////////////////////////////////////////////////////
// ISR for Timer overflow
void Hardware::SchedulerTimer::handleOVF()
{
    scheduler.clock();
}

//////////////////////////////////////////////////////////////////////////
// Main function
int main(void)
{
    // Init hardware peripherals
    Hardware::init();
    
    _delay_ms(1000);

    // Register potentiometer callbacks
    Hardware::PotentiometerOsc1Pitch::registerObserver([](const uint8_t value) {controller.setUIParam(UIParam::OSC1_PITCH, value);});
    Hardware::PotentiometerOsc1Detune::registerObserver([](const uint8_t value) {controller.setUIParam(UIParam::OSC1_DETUNE, value);});
    Hardware::PotentiometerOsc1Shape1::registerObserver([](const uint8_t value) {controller.setUIParam(UIParam::OSC1_SHAPE1, value);});
    Hardware::PotentiometerOsc1Shape2::registerObserver([](const uint8_t value) {controller.setUIParam(UIParam::OSC1_SHAPE2, value);});
    Hardware::PotentiometerOsc2Pitch::registerObserver([](const uint8_t value) {controller.setUIParam(UIParam::OSC2_PITCH, value);});
    Hardware::PotentiometerOsc2Detune::registerObserver([](const uint8_t value) {controller.setUIParam(UIParam::OSC2_DETUNE, value);});
    Hardware::PotentiometerOsc2Shape::registerObserver([](const uint8_t value) {controller.setUIParam(UIParam::OSC2_SHAPE, value);});
    Hardware::PotentiometerOscSyncPhase::registerObserver([](const uint8_t value) {controller.setUIParam(UIParam::OSC_SYNC_PHASE, value);});
    Hardware::PotentiometerOscBalance::registerObserver([](const uint8_t value) {controller.setUIParam(UIParam::OSC_BALANCE, value);});
    Hardware::PotentiometerOscRingModAmount::registerObserver([](const uint8_t value) {controller.setUIParam(UIParam::OSC_RINGMOD, value);});
    Hardware::PotentiometerOscCrossModAmount::registerObserver([](const uint8_t value) {controller.setUIParam(UIParam::OSC_CROSSMOD, value);});
    Hardware::PotentiometerFilterFreq::registerObserver([](const uint8_t value) {controller.setUIParam(UIParam::FILTER_FREQ, value);});
    Hardware::PotentiometerFilterShape::registerObserver([](const uint8_t value) {controller.setUIParam(UIParam::FILTER_SHAPE, value);});
    Hardware::PotentiometerFilterEnvAmount::registerObserver([](const uint8_t value) {controller.setUIParam(UIParam::FILTER_ENV_AMOUNT, value);});
    Hardware::PotentiometerFilterKeyTrack::registerObserver([](const uint8_t value) {controller.setUIParam(UIParam::FILTER_KEYTRACK, value);});
    Hardware::PotentiometerFilterEnvAttack::registerObserver([](const uint8_t value) {controller.setUIParam(UIParam::FILTER_ENV_A, value);});
    Hardware::PotentiometerFilterEnvDecay::registerObserver([](const uint8_t value) {controller.setUIParam(UIParam::FILTER_ENV_D, value);});
    Hardware::PotentiometerFilterEnvSustain::registerObserver([](const uint8_t value) {controller.setUIParam(UIParam::FILTER_ENV_S, value);});
    Hardware::PotentiometerFilterEnvRelease::registerObserver([](const uint8_t value) {controller.setUIParam(UIParam::FILTER_ENV_R, value);});
    Hardware::PotentiometerAmpBalance::registerObserver([](const uint8_t value) {controller.setUIParam(UIParam::PAN, value);});
    Hardware::PotentiometerAmpLevel::registerObserver([](const uint8_t value) {controller.setUIParam(UIParam::LEVEL, value);});
    Hardware::PotentiometerAmpEnvAttack::registerObserver([](const uint8_t value) {controller.setUIParam(UIParam::AMP_ENV_A, value);});
    Hardware::PotentiometerAmpEnvDecay::registerObserver([](const uint8_t value) {controller.setUIParam(UIParam::AMP_ENV_D, value);});
    Hardware::PotentiometerAmpEnvSustain::registerObserver([](const uint8_t value) {controller.setUIParam(UIParam::AMP_ENV_S, value);});
    Hardware::PotentiometerAmpEnvRelease::registerObserver([](const uint8_t value) {controller.setUIParam(UIParam::AMP_ENV_R, value);});
    Hardware::PotentiometerAuxEnvAttack::registerObserver([](const uint8_t value) {controller.setUIParam(UIParam::AUX_ENV_A, value);});
    Hardware::PotentiometerAuxEnvDecay::registerObserver([](const uint8_t value) {controller.setUIParam(UIParam::AUX_ENV_D, value);});
    Hardware::PotentiometerAuxEnvSustain::registerObserver([](const uint8_t value) {controller.setUIParam(UIParam::AUX_ENV_S, value);});
    Hardware::PotentiometerAuxEnvRelease::registerObserver([](const uint8_t value) {controller.setUIParam(UIParam::AUX_ENV_R, value);});
    Hardware::PotentiometerLFO1Rate::registerObserver([](const uint8_t value) {controller.setUIParam(UIParam::LFO1_RATE, value);});
    Hardware::PotentiometerLFO2Rate::registerObserver([](const uint8_t value) {controller.setUIParam(UIParam::LFO2_RATE, value);});
    Hardware::PotentiometerLFOSyncPhase::registerObserver([](const uint8_t value) {controller.setUIParam(UIParam::LFO_SYNC_PHASE, value);});
    Hardware::PotentiometerModAmount::registerObserver([](const uint8_t value) {controller.setUIParam(UIParam::MOD_AMOUNT, value);});
    Hardware::PotentiometerGlideTime::registerObserver([](const uint8_t value) {controller.setUIParam(UIParam::GLIDE_TIME, value);});
    Hardware::PotentiometerFXParamValue::registerObserver([](const uint8_t value) {controller.setUIParam(UIParam::FX_PARAM_VALUE, value);});
    Hardware::PotentiometerArpSpeed::registerObserver([](const uint8_t value) {controller.setUIParam(UIParam::ARP_SPEED, value);});
    Hardware::PotentiometerBass::registerObserver([](const uint8_t value) {controller.setUIParam(UIParam::BASS, value);});
    Hardware::PotentiometerTreble::registerObserver([](const uint8_t value) {controller.setUIParam(UIParam::TREBLE, value);});
    
    // Register push-button callbacks
    Hardware::Button_OSC1_Waveform::registerObserver([]() {controller.toggleUIParam(UIParam::OSC1_WAVEFORM);});
    Hardware::Button_OSC2_Waveform::registerObserver([]() {controller.toggleUIParam(UIParam::OSC2_WAVEFORM);});
    Hardware::Button_OSC_Sync::registerObserver([]() {controller.toggleUIParam(UIParam::OSC_SYNC);});
    Hardware::Button_Legato::registerObserver([]() {controller.toggleUIParam(UIParam::LEGATO);});
    Hardware::Button_Filter_Type::registerObserver([]() {controller.toggleUIParam(UIParam::FILTER_TYPE);});
    Hardware::Button_LFO1_Waveform::registerObserver([]() {controller.toggleUIParam(UIParam::LFO1_WAVEFORM);});
    Hardware::Button_LFO2_Waveform::registerObserver([]() {controller.toggleUIParam(UIParam::LFO2_WAVEFORM);});
    Hardware::Button_LFO_Sync::registerObserver([]() {controller.toggleUIParam(UIParam::LFO_SYNC);});
    Hardware::Button_Arp_Mode::registerObserver([]() {controller.toggleUIParam(UIParam::ARP_MODE);});
    Hardware::Button_LayerSelect::registerObserver([]() {controller.toggleUIParam(UIParam::SELECTED_LAYER);});
    Hardware::Button_LayerMode::registerObserver([]() {controller.toggleUIParam(UIParam::LAYER_MODE);});
    Hardware::Button_LoadPatch::registerObserver([]() {controller.onLoadPatch();});
    Hardware::Button_SavePatch::registerObserver([]() {controller.onSavePatch();});
    Hardware::Button_LoadScene::registerObserver([]() {controller.onLoadScene();});
    Hardware::Button_SaveScene::registerObserver([]() {controller.onSaveScene();});
    Hardware::Button_EnterNext::registerObserver([]() {controller.onEnterNext();});
    Hardware::Button_CancelBack::registerObserver([]() {controller.onCancelBack();});

    // Register rotary encoder callbacks
    Hardware::Encoder_ModSrc::registerObserverCW([]() {controller.incUIParam(UIParam::MOD_SRC);});
    Hardware::Encoder_ModSrc::registerObserverCCW([]() {controller.decUIParam(UIParam::MOD_SRC);});
    Hardware::Encoder_ModDst::registerObserverCW([]() {controller.incUIParam(UIParam::MOD_DST);});
    Hardware::Encoder_ModDst::registerObserverCCW([]() {controller.decUIParam(UIParam::MOD_DST);});
    Hardware::Encoder_ArpPattern::registerObserverCW([]() {controller.incUIParam(UIParam::ARP_PATTERN);});
    Hardware::Encoder_ArpPattern::registerObserverCCW([]() {controller.decUIParam(UIParam::ARP_PATTERN);});
    Hardware::Encoder_FXParam::registerObserverCW([]() {controller.incUIParam(UIParam::FX_PARAM);});
    Hardware::Encoder_FXParam::registerObserverCCW([]() {controller.decUIParam(UIParam::FX_PARAM);});
    Hardware::Encoder_UpDown::registerObserverCW([]() {controller.onUp();});
    Hardware::Encoder_UpDown::registerObserverCCW([]() {controller.onDown();});
    
    // MIDI Parser
    midiInput.registerObserver([](const MidiControlChange & data) {controller.onControlChange(data.controller, data.value);});
    midiInput.registerObserver([](const MidiNoteOn & stData) {controller.onNoteOn(stData.note, stData.velocity);});
    midiInput.registerObserver([](const MidiNoteOff & stData) {controller.onNoteOff(stData.note);});
    midiInput.registerObserver([](const MidiPitchBend & stData) {DSPInterface::updateControllerParam(ControllerParam::PITCHBEND_MSB, stData.MSB); DSPInterface::updateControllerParam(ControllerParam::PITCHBEND_LSB, stData.LSB);});

    // Register controller callbacks
    controller.registerPatchParamObserver([](const PatchParam param, const uint8_t value) {DSPInterface::updatePatchParam(param, value); UserInterface::onPatchParamUpdate(param, value);});
    controller.registerPatchParamSilentObserver([](const PatchParam param, const uint8_t value) {DSPInterface::updatePatchParam(param, value); UserInterfaceLED::onPatchParamUpdate(param, value);});
    controller.registerSceneParamObserver([](const SceneParam param, const uint8_t value) {DSPInterface::updateSceneParam(param, value); UserInterface::onSceneParamUpdate(param, value);});
    controller.registerSceneParamSilentObserver([](const SceneParam param, const uint8_t value) {DSPInterface::updateSceneParam(param, value); UserInterfaceLED::onSceneParamUpdate(param, value);});
    controller.registerSelectedLayerObserver([](const uint8_t layerIdx) {DSPInterface::updateControllerParam(ControllerParam::SELECTED_LAYER, layerIdx); UserInterface::onSelectedLayerUpdate(layerIdx);});
    controller.registerSelectedLayerSilentObserver([](const uint8_t layerIdx) {DSPInterface::updateControllerParam(ControllerParam::SELECTED_LAYER, layerIdx); UserInterfaceLED::onSelectedLayerUpdate(layerIdx);});        
    controller.registerLoadPatchObserver([](const uint8_t patchIdx, const String<10>& patchName){UserInterface::onLoadPatch(patchIdx, patchName);});
    controller.registerSavePatchObserver([](const uint8_t patchIdx, const UIEditableString<10>& patchName){UserInterface::onSavePatch(patchIdx, patchName);});
    controller.registerLoadSceneObserver([](const uint8_t sceneIdx, const String<10>& sceneName){UserInterface::onLoadScene(sceneIdx, sceneName);});
    controller.registerSaveSceneObserver([](const uint8_t sceneIdx, const UIEditableString<10>& sceneName){UserInterface::onSaveScene(sceneIdx, sceneName);});
    controller.registerSaveRenameObserver([](const uint8_t idx, const UIEditableString<10>& name){UserInterface::onSaveRename(idx, name);});
    controller.registerSaveConfirmObserver([](const uint8_t idx, const UIEditableString<10>& name){UserInterface::onSaveConfirm(idx, name);});
    controller.registerHomeScreenObserver([](const uint8_t sceneIdx, const String<10>& sceneName, const uint8_t patchIdx, const String<10>& patchName){UserInterfaceLCD::ShowHomeScreen(sceneIdx, sceneName, patchIdx, patchName);});
    controller.registerArpParamObserver([](const ArpeggiatorParam param, const uint8_t value){if (ArpeggiatorParam::MODE == param && static_cast<uint8_t>(OnOff::ON) == value) clockArpeggiatorTask.execute(); UserInterface::onArpParamUpdate(param, value);});
        
    controller.registerNoteOnObserver([](const uint8_t note, const uint8_t velocity){DSPInterface::noteOn(note, velocity);});
    controller.registerNoteOffObserver([](const uint8_t note){DSPInterface::noteOff(note);});
    controller.registerControllerParamObserver([](const ControllerParam param, const uint8_t value) {DSPInterface::updateControllerParam(param, value);});

    // schedule Tasks
    constexpr Delay tGUIRefreshIntervalMS = 100;
    scheduler.schedule(refreshGUITask, tGUIRefreshIntervalMS);

    // Now we are ready to globally enable all interrupts
    sei();
    
    controller.init();
    DSPInterface::allNotesOff();
    Hardware::PotentiometerScanner::scanPotentiometers(true);

    uint8_t uiData = 0;
    while (1)
    {
        // Check for received Midi data to process
        while (midiInBuffer.read(uiData))
        {
            midiInput.parse(uiData);
        }

        // Check for tasks to execute
        scheduler.executeNextTask();
    }
}