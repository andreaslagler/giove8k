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

#ifndef SYNTH_DEF_H
#define	SYNTH_DEF_H

// Global synth definitions

// Number of sound layers
#define NOF_LAYERS 2

// Number of DSPs
#define NOF_DSPS 2

// Number of voices per DSP
#define NOF_VOICES_DSP 4

// Total number of voices
#define NOF_VOICES_TOTAL (NOF_VOICES_DSP * NOF_DSPS)

#endif
 