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

#ifndef SRAM_INTERFACE_H
#define	SRAM_INTERFACE_H

#include <stdint.h>

void configureSRAMInterface(void);
void startSRAMTransfer(
const uint16_t writePos,
const uint16_t readPos);
void waitSRAMTransfer();

int16_t * getSRAM0Buffer();
int16_t * getSRAM1Buffer();

#endif
