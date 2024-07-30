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

#ifndef APPLICATION_EVENT_H
#define APPLICATION_EVENT_H

#include "midi_Types.h"
#include "ui_param_def.h"
#include "edit_menu_event.h"

#include <stdint.h>
#include <type_map.h>
#include <variant.h>
#include <string.h>
#include <pgm_string.h>
#include <array.h>



// Enumeration of all application event sources
enum class ApplicationEventSource : uint8_t
{
    UI_INPUT, // Event has been caused by UI input
    UI_UPDATE, // Event has been caused by UI update
    MIDI, // Event has been caused by a MIDI input
    CLOCK, // Event has been caused by a clock event
    NOF_ENTRIES
};

// Data structures for all application events
struct NoteOnEvent
{
    MidiChannel channel;
    uint8_t note;
    uint8_t velocity;
};

struct UiParamChangeEvent
{
    //ApplicationEventSource source;
    UiParamIdx paramIdx;
    UiParamValue paramValue;
};

struct UiParamShowEvent
{
    //ApplicationEventSource source;
    UiParamIdx paramIdx;
    UiParamValue paramValue;
};

struct HomeScreenEvent
{
    ApplicationEventSource source;
};


/*
An event can only be one of the types specified above.
To keep the interface thin, the top-level application event is implemented as a variant of all possible event data structures.
The top-level event handler is implemented as a visitor of the variant and dispatches the currently held alternative type of the variant to the corresponding event handler.
*/

using ApplicationEvent = Variant<
UiParamChangeEvent,
UiParamShowEvent,
EditMenuEvent
>;

// Comparison operator (needed by priority queue)
constexpr inline bool operator<(const ApplicationEvent& a, const ApplicationEvent& b)
{
    return a.index() < b.index();
}

#endif