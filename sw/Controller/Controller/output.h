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

#ifndef OUTPUT_H
#define OUTPUT_H

#include "hardware.h"
#include "application_event.h"
#include <string_stream.h>
#include "lookup_table.h"

class Output : public Hardware
{
    public:
    
    void handleEvent(const ApplicationEvent& event)
    {
        // Use a lambda (overloaded with 'auto' for all event types) as visitor
        auto eventHandler = [&](auto&& arg)
        {
            handleEvent(forward<decltype(arg)>(arg));
        };
        
        visit(eventHandler, event);
    }
    
    private:
    
    void handleEvent(const NoteOnEvent& event);
    void handleEvent(const UiParamChangeEvent& event);
    void handleEvent(const UiParamShowEvent& event);
    void handleEvent(const HomeScreenEvent& event);
   
    void handleEvent(const EditMenuEvent& event);   
    
    // String stream for LCD output
    StringStream<typename LCD::FrameBuffer> m_lcdStream{LCD::getBuffer()};
    
    //// String for home screen
    //StaticString<LCD::getNofColumns() * LCD::getNofRows()> m_homeScreen;
//
    //static PgmString noteToString(uint8_t note, int8_t& octave)
    //{
        //typedef SparseLUT<PgmString, uint8_t, 12> Table;
        //
        //constexpr static const PROGMEM Table LUT
        //(
        //"n/a"_pgm,
        //Table::Entry(0, "C"_pgm),
        //Table::Entry(1, "C#"_pgm),
        //Table::Entry(2, "D"_pgm),
        //Table::Entry(3, "D#"_pgm),
        //Table::Entry(4, "E"_pgm),
        //Table::Entry(5, "F"_pgm),
        //Table::Entry(6, "F#"_pgm),
        //Table::Entry(7, "G"_pgm),
        //Table::Entry(8, "G#"_pgm),
        //Table::Entry(9, "A"_pgm),
        //Table::Entry(10, "Bb"_pgm),
        //Table::Entry(11, "B"_pgm)
        //);
        //
        //const uint8_t semiTone = mod<12>(note);
        //octave = static_cast<int8_t>(note) - 1; // Lowest MIDI note is C-1
        //return LUT.getP(semiTone);
    //}

};


#endif