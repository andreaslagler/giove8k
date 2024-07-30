/*
Copyright (C) 2024 Andreas Lagler

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

#include "hardware.h"
#include "application.h"
#include "output.h"
#include "input.h"
#include <exception.h>

#include "hardware_event.h"
#include "application_event.h"

    
// Main function
int main(void)
{
    // (Hardware) input and associated logic
    Input input;

    // (Hardware) output and associated logic
    Output output;

    // Business logic of the application
    Application application;
    
    // Connect input to application using generic event handler
    auto inputEventHandler = [&](const HardwareEvent& event){application.handleEvent(event);};
    input.setEventHandler(inputEventHandler);
    
    // Connect output to application using generic event handler
    auto applicationEventHandler = [&](const ApplicationEvent& event){output.handleEvent(event);};
    application.setEventHandler(applicationEventHandler);
    
    // Now we are ready to globally enable all interrupts
    sei();
    
    // Wait for input events
    while (1)
    {
       input.doEvents();
    }
}

// Exception handler for bad allocation
void throw_bad_alloc()
{
    while(true);
}

// Exception handler for nullptr dereferencing
void throw_nullptr_error()
{
    while(true);
}

// This is needed to make new() and delete() work
__extension__ typedef int __guard __attribute__((mode (__DI__)));
extern "C" int __cxa_guard_acquire(__guard *);
extern "C" void __cxa_guard_release (__guard *);
extern "C" void __cxa_guard_abort (__guard *);
int __cxa_guard_acquire(__guard *g) {return !*(char *)(g);};
void __cxa_guard_release (__guard *g) {*(char *)g = 1;};
void __cxa_guard_abort (__guard *) {};