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

#ifndef INPUT_H
#define INPUT_H

#include "hardware.h"
#include "hardware_event.h"
#include <list.h>
#include <queue.h>

class Input : Hardware
{
    public:
    
    Input();
    
    void setEventHandler(auto& eventHandler)
    {
        m_eventHandler = eventHandler;
    }

    void doEvents();
    
    private:
    
    // Registered event handler observers for all possible hardware events
    function<void(const HardwareEvent&)> m_eventHandler;
    
    template <typename T>
    struct Less
    {
        constexpr bool operator()(const T& t1, const T& t2)
        {
            return t1 < t2;
        }
    };

    PriorityQueue<HardwareEvent, List<HardwareEvent>, Less<HardwareEvent>> m_eventQueue;    

    //static InternalClock s_internalClock;

    MidiInput m_midiInputParser;
    MidiInput m_midiKeyboardParser;
        
    //static constexpr void handleClockEvent()
    //{
        //HardwareEvent event;
        //event.type = HardwareEventType::Clock;
        //s_eventQueue.push(event);
    //}   
};

#endif