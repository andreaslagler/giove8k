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

#ifndef VOICE_MANAGER_TYPES_H
#define	VOICE_MANAGER_TYPES_H

#include <stdint.h>
#include <stdbool.h>

//
typedef union
{
    uint16_t data;
    struct __attribute__((packed))
    {
        uint16_t velocity : 7;
        uint16_t note : 7;
        bool trigger : 1;
        bool gate : 1;
    };
} VoiceParams;

#endif
