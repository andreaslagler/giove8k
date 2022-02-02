EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 2 9
Title "Audio DSP"
Date "2021-07-24"
Rev "1.0"
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 "Audio DSP with DAC interface"
$EndDescr
$Sheet
S 2150 1700 650  1250
U 61563857
F0 "DSP0" 50
F1 "DSP0.sch" 50
F2 "SCK0" I L 2150 1800 50 
F3 "SDI0" I L 2150 1900 50 
F4 "~SS0" I L 2150 2100 50 
F5 "SDO0" I L 2150 2000 50 
F6 "CSCK" I R 2800 1800 50 
F7 "COFS" I R 2800 1900 50 
F8 "CSDO" I R 2800 2000 50 
F9 "~SS10" I R 2800 2550 50 
F10 "~SS11" I R 2800 2650 50 
F11 "~SS12" I R 2800 2750 50 
F12 "~SS13" I R 2800 2850 50 
F13 "SCK1" I R 2800 2250 50 
F14 "SDI1" I R 2800 2350 50 
F15 "SDO1" I R 2800 2450 50 
$EndSheet
$Sheet
S 4050 1700 550  500 
U 61564560
F0 "DSP1" 50
F1 "DSP1.sch" 50
F2 "SCK0" I L 4050 1800 50 
F3 "SDI0" I L 4050 1900 50 
F4 "~SS0" I L 4050 2100 50 
F5 "SDO0" I L 4050 2000 50 
$EndSheet
$Sheet
S 4050 3950 550  500 
U 61564C3C
F0 "DSP4" 50
F1 "DSP4.sch" 50
F2 "SCK0" I L 4050 4050 50 
F3 "SDI0" I L 4050 4150 50 
F4 "~SS0" I L 4050 4350 50 
F5 "SDO0" I L 4050 4250 50 
$EndSheet
$Sheet
S 4050 3200 550  500 
U 61564B90
F0 "DSP3" 50
F1 "DSP3.sch" 50
F2 "SCK0" I L 4050 3300 50 
F3 "SDI0" I L 4050 3400 50 
F4 "~SS0" I L 4050 3600 50 
F5 "SDO0" I L 4050 3500 50 
$EndSheet
$Sheet
S 4050 2450 550  500 
U 61564A08
F0 "DSP2" 50
F1 "DSP2.sch" 50
F2 "SCK0" I L 4050 2550 50 
F3 "SDI0" I L 4050 2650 50 
F4 "~SS0" I L 4050 2850 50 
F5 "SDO0" I L 4050 2750 50 
$EndSheet
$Sheet
S 5650 1900 600  400 
U 61567B0E
F0 "DAC" 50
F1 "DAC.sch" 50
F2 "BCK" I L 5650 2000 50 
F3 "WS" I L 5650 2100 50 
F4 "DATA" I L 5650 2200 50 
F5 "OUT_L" I R 6250 2000 50 
F6 "OUT_R" I R 6250 2100 50 
$EndSheet
Wire Wire Line
	2800 1800 2900 1800
Text Label 2900 1800 0    50   ~ 0
CSK
Wire Wire Line
	2800 1900 2900 1900
Text Label 2900 1900 0    50   ~ 0
COFS
Wire Wire Line
	2800 2000 2900 2000
Text Label 2900 2000 0    50   ~ 0
CSDO
Wire Wire Line
	2800 2250 2900 2250
Text Label 2900 2250 0    50   ~ 0
SCK1
Wire Wire Line
	2800 2350 2900 2350
Text Label 2900 2350 0    50   ~ 0
SDI1
Wire Wire Line
	2800 2450 2900 2450
Text Label 2900 2450 0    50   ~ 0
SDO1
Wire Wire Line
	2800 2550 2900 2550
Text Label 2900 2550 0    50   ~ 0
~SS0
Wire Wire Line
	2800 2650 2900 2650
Text Label 2900 2650 0    50   ~ 0
~SS1
Wire Wire Line
	2800 2750 2900 2750
Text Label 2900 2750 0    50   ~ 0
~SS2
Wire Wire Line
	2800 2850 2900 2850
Text Label 2900 2850 0    50   ~ 0
~SS3
Wire Wire Line
	4050 1800 3950 1800
Text Label 3950 1800 2    50   ~ 0
SCK1
Wire Wire Line
	4050 1900 3950 1900
Text Label 3950 1900 2    50   ~ 0
SDO1
Wire Wire Line
	4050 2000 3950 2000
Text Label 3950 2000 2    50   ~ 0
SDI1
Wire Wire Line
	4050 2100 3950 2100
Text Label 3950 2100 2    50   ~ 0
~SS0
Wire Wire Line
	2150 1800 2050 1800
Wire Wire Line
	2150 1900 2050 1900
Wire Wire Line
	2150 2000 2050 2000
Wire Wire Line
	2150 2100 2050 2100
Wire Wire Line
	4050 2550 3950 2550
Text Label 3950 2550 2    50   ~ 0
SCK1
Wire Wire Line
	4050 2650 3950 2650
Text Label 3950 2650 2    50   ~ 0
SDO1
Wire Wire Line
	4050 2750 3950 2750
Text Label 3950 2750 2    50   ~ 0
SDI1
Wire Wire Line
	4050 2850 3950 2850
Text Label 3950 2850 2    50   ~ 0
~SS1
Wire Wire Line
	5650 2000 5550 2000
Text Label 5550 2000 2    50   ~ 0
CSK
Wire Wire Line
	5650 2100 5550 2100
Text Label 5550 2100 2    50   ~ 0
COFS
Wire Wire Line
	5650 2200 5550 2200
Text Label 5550 2200 2    50   ~ 0
CSDO
Wire Wire Line
	4050 3300 3950 3300
Text Label 3950 3300 2    50   ~ 0
SCK1
Wire Wire Line
	4050 3400 3950 3400
Text Label 3950 3400 2    50   ~ 0
SDO1
Wire Wire Line
	4050 3500 3950 3500
Text Label 3950 3500 2    50   ~ 0
SDI1
Wire Wire Line
	4050 3600 3950 3600
Text Label 3950 3600 2    50   ~ 0
~SS2
Wire Wire Line
	4050 4050 3950 4050
Text Label 3950 4050 2    50   ~ 0
SCK1
Wire Wire Line
	4050 4150 3950 4150
Text Label 3950 4150 2    50   ~ 0
SDO1
Wire Wire Line
	4050 4250 3950 4250
Text Label 3950 4250 2    50   ~ 0
SDI1
Wire Wire Line
	4050 4350 3950 4350
Text Label 3950 4350 2    50   ~ 0
~SS3
Text HLabel 6350 2000 2    50   Input ~ 0
OUT_L
Text HLabel 6350 2100 2    50   Input ~ 0
OUT_R
Wire Wire Line
	6250 2000 6350 2000
Wire Wire Line
	6250 2100 6350 2100
Text HLabel 2050 1800 0    50   Input ~ 0
SCK
Text HLabel 2050 1900 0    50   Input ~ 0
SDI
Text HLabel 2050 2000 0    50   Input ~ 0
SDO
Text HLabel 2050 2100 0    50   Input ~ 0
~SS
$EndSCHEMATC