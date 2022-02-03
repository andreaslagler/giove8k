/*
Copyright (C) 2021 Andreas Lagler

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

#include "Voice.h"

////////////////////////////////////////////////////////////////////////////////
// Initialize voice state
////////////////////////////////////////////////////////////////////////////////
void initVoice(VoiceState * const voiceState)
{
    voiceState->oscState.osc1.feedbackState.readPos = 0;
    
    ////////////////////////////////////////////////////////////////////////////
    // Envelopes
    
    // Filter Envelope
    voiceState->filterEnvState.stage = ADSR_STAGE_R;
    voiceState->filterEnvState.value = 0;
    
    // Amp Envelope
    voiceState->ampEnvState.stage = ADSR_STAGE_R;
    voiceState->ampEnvState.value = 0;

    // Aux Envelope
    voiceState->auxEnvState.stage = ADSR_STAGE_R;
    voiceState->auxEnvState.value = 0;
}

