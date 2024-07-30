/*
Copyright (C) 2023 Andreas Lagler

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

#ifndef BUFFERED_LEDS_H
#define BUFFERED_LEDS_H

#include <stdint.h>
#include <array.h>
#include <bool_array.h>

enum class LedState : uint8_t
{
    OFF = 0,
    ON,
    BLINKING
};

template <typename LEDPort, uint8_t t_nofLeds = 8 * LEDPort::getNofBytes()>
class BufferedLeds
{
    public:
    
    static constexpr void init()
    {
        for (auto& state : m_states)
        {
            state = LedState::OFF;
        }
        s_refreshCounter = 0;
    }
    
    
    static void refresh()
    {
        BoolArray<t_nofLeds> buffer;
        const bool blinkState = (++s_refreshCounter & s_refreshDivider) > 0;
        
        for (uint8_t cnt = 0; cnt < t_nofLeds; ++cnt)
        {
            switch (m_states[cnt])
            {
                case LedState::OFF:
                buffer.clear(cnt);
                break;
                
                case LedState::ON:
                buffer.set(cnt);
                break;
                
                case LedState::BLINKING:
                buffer.set(cnt, blinkState);
                break;
            }
        }
        
        LEDPort::put(buffer.data().m_data);
    }
    
    static constexpr void set(const uint8_t idx, const LedState state)
    {
        m_states[idx] = state;
    }
    
    static constexpr void set(const uint8_t startIdx, const uint8_t nofLeds, const LedState state)
    {
        const uint8_t endIdx = startIdx + nofLeds;
        for (uint8_t idx = startIdx; idx < endIdx; ++idx)
        {
            set(idx, state);
        }        
    }
    
    private:
    
    static Array<LedState, t_nofLeds> m_states;
    static uint8_t s_refreshCounter; // Needed for blinking logic
    static constexpr uint8_t s_refreshDivider = (1<<3);
};

// Static initialization
template <typename LEDPort, uint8_t t_nofLeds>
Array<LedState, t_nofLeds> BufferedLeds<LEDPort, t_nofLeds>::m_states;

template <typename LEDPort, uint8_t t_nofLeds>
uint8_t BufferedLeds<LEDPort, t_nofLeds>::s_refreshCounter;


#endif