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

#ifndef EDIT_MENU_ENUMS_H
#define EDIT_MENU_ENUMS_H

#include <stdint.h>

enum class EditMenuState : uint8_t
{
    IDLE = 0,
    EDIT,
    BANK1,
    BANK2,
    BANK3,
    BANK4,
    BANK5,
    BANK6,
    BANK7,
    BANK8
};


#endif