EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 5 9
Title "DSP"
Date "2021-07-24"
Rev "1.0"
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 "Wave-generating DSP"
$EndDescr
$Comp
L AudioBoard-rescue:C_Small-Audio-DSP-rescue C20
U 1 1 61567806
P 2450 3100
F 0 "C20" H 2460 3170 50  0000 L CNN
F 1 "100n" H 2460 3020 50  0000 L CNN
F 2 "Capacitor_THT:C_Disc_D4.3mm_W1.9mm_P5.00mm" H 2450 3100 60  0001 C CNN
F 3 "" H 2450 3100 60  0000 C CNN
	1    2450 3100
	1    0    0    -1  
$EndComp
$Comp
L AudioBoard-rescue:C_Small-Audio-DSP-rescue C19
U 1 1 61567807
P 2150 3100
F 0 "C19" H 2160 3170 50  0000 L CNN
F 1 "100n" H 2160 3020 50  0000 L CNN
F 2 "Capacitor_THT:C_Disc_D4.3mm_W1.9mm_P5.00mm" H 2150 3100 60  0001 C CNN
F 3 "" H 2150 3100 60  0000 C CNN
	1    2150 3100
	1    0    0    -1  
$EndComp
$Comp
L AudioBoard-rescue:CP_Small-Audio-DSP-rescue C21
U 1 1 61567808
P 2750 3100
F 0 "C21" H 2760 3170 50  0000 L CNN
F 1 "10u" H 2760 3020 50  0000 L CNN
F 2 "Capacitor_THT:CP_Radial_D5.0mm_P2.50mm" H 2750 3100 60  0001 C CNN
F 3 "" H 2750 3100 60  0000 C CNN
	1    2750 3100
	1    0    0    -1  
$EndComp
$Comp
L AudioBoard-rescue:GND-Audio-DSP-rescue #PWR057
U 1 1 61567809
P 2150 3200
F 0 "#PWR057" H 2150 2950 50  0001 C CNN
F 1 "GND" H 2150 3050 50  0000 C CNN
F 2 "" H 2150 3200 60  0000 C CNN
F 3 "" H 2150 3200 60  0000 C CNN
	1    2150 3200
	1    0    0    -1  
$EndComp
$Comp
L AudioBoard-rescue:GND-Audio-DSP-rescue #PWR058
U 1 1 6156780A
P 2450 3200
F 0 "#PWR058" H 2450 2950 50  0001 C CNN
F 1 "GND" H 2450 3050 50  0000 C CNN
F 2 "" H 2450 3200 60  0000 C CNN
F 3 "" H 2450 3200 60  0000 C CNN
	1    2450 3200
	1    0    0    -1  
$EndComp
$Comp
L AudioBoard-rescue:GND-Audio-DSP-rescue #PWR059
U 1 1 6156780B
P 2750 3200
F 0 "#PWR059" H 2750 2950 50  0001 C CNN
F 1 "GND" H 2750 3050 50  0000 C CNN
F 2 "" H 2750 3200 60  0000 C CNN
F 3 "" H 2750 3200 60  0000 C CNN
	1    2750 3200
	1    0    0    -1  
$EndComp
$Comp
L AudioBoard-rescue:GND-Audio-DSP-rescue #PWR065
U 1 1 6156780C
P 2750 4200
F 0 "#PWR065" H 2750 3950 50  0001 C CNN
F 1 "GND" H 2750 4050 50  0000 C CNN
F 2 "" H 2750 4200 60  0000 C CNN
F 3 "" H 2750 4200 60  0000 C CNN
	1    2750 4200
	1    0    0    -1  
$EndComp
Text Label 5600 1800 0    60   ~ 0
OSC1
Text Label 5600 1900 0    60   ~ 0
OSC2
$Comp
L AudioBoard-rescue:+3.3V-Audio-DSP-rescue #PWR050
U 1 1 6156780D
P 2150 2100
F 0 "#PWR050" H 2150 1950 50  0001 C CNN
F 1 "+3.3V" H 2150 2240 50  0000 C CNN
F 2 "" H 2150 2100 60  0000 C CNN
F 3 "" H 2150 2100 60  0000 C CNN
	1    2150 2100
	1    0    0    -1  
$EndComp
Wire Wire Line
	3000 2900 2750 2900
Wire Wire Line
	2750 2900 2750 3000
Wire Wire Line
	3000 2600 2450 2600
Wire Wire Line
	2450 2100 2450 2600
Wire Wire Line
	3000 2200 2150 2200
Wire Wire Line
	2150 2100 2150 2200
Wire Wire Line
	2750 3650 2750 4000
Wire Wire Line
	3000 4000 2750 4000
Connection ~ 2750 4000
Connection ~ 2450 2600
Connection ~ 2150 2200
Text Label 5600 3300 0    60   ~ 0
SCK1
Text Label 5600 3500 0    60   ~ 0
SDI1
Text Label 5600 3400 0    60   ~ 0
SDO1
Text Label 5600 2900 0    60   ~ 0
PGED
Text Label 3000 1600 2    60   ~ 0
~MCLR
Text HLabel 5800 4050 2    60   Input ~ 0
SCK0
Text HLabel 5800 3850 2    60   Input ~ 0
SDI0
Text HLabel 5800 3750 2    60   Input ~ 0
~SS0
Wire Wire Line
	5600 4100 5700 4100
Wire Wire Line
	5700 4100 5700 4050
Wire Wire Line
	5700 4050 5800 4050
Wire Wire Line
	5600 3900 5700 3900
Wire Wire Line
	5700 3900 5700 3850
Wire Wire Line
	5700 3850 5800 3850
Wire Wire Line
	5600 4000 5700 4000
Wire Wire Line
	5700 4000 5700 3950
Wire Wire Line
	5700 3950 5800 3950
Text Label 6000 5050 0    60   ~ 0
~MCLR
$Comp
L AudioBoard-rescue:C_Small-Audio-DSP-rescue C25
U 1 1 61567C5D
P 5850 5250
F 0 "C25" H 5860 5320 50  0000 L CNN
F 1 "100n" H 5860 5170 50  0000 L CNN
F 2 "Capacitor_THT:C_Disc_D4.3mm_W1.9mm_P5.00mm" H 5850 5250 60  0001 C CNN
F 3 "" H 5850 5250 60  0000 C CNN
	1    5850 5250
	1    0    0    -1  
$EndComp
Wire Wire Line
	5850 5350 5850 5450
Wire Wire Line
	5850 4950 5850 5050
Connection ~ 5850 5050
$Comp
L AudioBoard-rescue:GND-Audio-DSP-rescue #PWR072
U 1 1 61567940
P 5850 5450
F 0 "#PWR072" H 5850 5200 50  0001 C CNN
F 1 "GND" H 5850 5300 50  0000 C CNN
F 2 "" H 5850 5450 60  0000 C CNN
F 3 "" H 5850 5450 60  0000 C CNN
	1    5850 5450
	1    0    0    -1  
$EndComp
$Comp
L AudioBoard-rescue:R_Small-Audio-DSP-rescue R3
U 1 1 61567941
P 5850 4850
F 0 "R3" H 5880 4870 50  0000 L CNN
F 1 "10k" H 5880 4810 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" H 5850 4850 60  0001 C CNN
F 3 "" H 5850 4850 60  0000 C CNN
	1    5850 4850
	1    0    0    -1  
$EndComp
$Comp
L AudioBoard-rescue:+3.3V-Audio-DSP-rescue #PWR066
U 1 1 61567811
P 5850 4750
F 0 "#PWR066" H 5850 4600 50  0001 C CNN
F 1 "+3.3V" H 5850 4890 50  0000 C CNN
F 2 "" H 5850 4750 60  0000 C CNN
F 3 "" H 5850 4750 60  0000 C CNN
	1    5850 4750
	1    0    0    -1  
$EndComp
$Comp
L AudioBoard-rescue:Conn_01x06-Audio-DSP-rescue J5
U 1 1 61567943
P 4900 5150
F 0 "J5" H 4900 5450 50  0000 C CNN
F 1 "ICSP" H 4900 4750 50  0000 C CNN
F 2 "Connector_Molex:Molex_KK-254_AE-6410-06A_1x06_P2.54mm_Vertical" H 4900 5150 50  0001 C CNN
F 3 "" H 4900 5150 50  0001 C CNN
	1    4900 5150
	1    0    0    -1  
$EndComp
Text Label 4700 4950 2    60   ~ 0
~MCLR
Text Label 4700 5250 2    60   ~ 0
PGED
Wire Wire Line
	4700 5150 4050 5150
Wire Wire Line
	4050 5150 4050 5200
Wire Wire Line
	4700 5050 4050 5050
Wire Wire Line
	4050 5050 4050 5000
$Comp
L AudioBoard-rescue:GND-Audio-DSP-rescue #PWR068
U 1 1 5BCB9BA6
P 4050 5200
F 0 "#PWR068" H 4050 4950 50  0001 C CNN
F 1 "GND" H 4050 5050 50  0000 C CNN
F 2 "" H 4050 5200 60  0000 C CNN
F 3 "" H 4050 5200 60  0000 C CNN
	1    4050 5200
	1    0    0    -1  
$EndComp
$Comp
L AudioBoard-rescue:+3.3V-Audio-DSP-rescue #PWR067
U 1 1 61567814
P 4050 5000
F 0 "#PWR067" H 4050 4850 50  0001 C CNN
F 1 "+3.3V" H 4050 5140 50  0000 C CNN
F 2 "" H 4050 5000 60  0000 C CNN
F 3 "" H 4050 5000 60  0000 C CNN
	1    4050 5000
	1    0    0    -1  
$EndComp
NoConn ~ 4700 5450
$Comp
L AudioBoard-rescue:Crystal_Small-Audio-DSP-rescue Y4
U 1 1 5BCCCC4B
P 2350 5000
F 0 "Y4" H 2350 5100 50  0000 C CNN
F 1 "10MHz" H 2350 4900 50  0000 C CNN
F 2 "Crystal:Crystal_HC49-U_Vertical" H 2350 5000 60  0001 C CNN
F 3 "" H 2350 5000 60  0000 C CNN
	1    2350 5000
	1    0    0    -1  
$EndComp
$Comp
L AudioBoard-rescue:C_Small-Audio-DSP-rescue C23
U 1 1 5BCCCFEA
P 2150 5200
F 0 "C23" H 2160 5270 50  0000 L CNN
F 1 "18p" H 2160 5120 50  0000 L CNN
F 2 "Capacitor_THT:C_Disc_D3.0mm_W1.6mm_P2.50mm" H 2150 5200 60  0001 C CNN
F 3 "" H 2150 5200 60  0000 C CNN
	1    2150 5200
	1    0    0    -1  
$EndComp
$Comp
L AudioBoard-rescue:C_Small-Audio-DSP-rescue C24
U 1 1 5BCCD086
P 2550 5200
F 0 "C24" H 2560 5270 50  0000 L CNN
F 1 "18p" H 2560 5120 50  0000 L CNN
F 2 "Capacitor_THT:C_Disc_D3.0mm_W1.6mm_P2.50mm" H 2550 5200 60  0001 C CNN
F 3 "" H 2550 5200 60  0000 C CNN
	1    2550 5200
	1    0    0    -1  
$EndComp
$Comp
L AudioBoard-rescue:GND-Audio-DSP-rescue #PWR069
U 1 1 61567C67
P 2150 5300
F 0 "#PWR069" H 2150 5050 50  0001 C CNN
F 1 "GND" H 2150 5150 50  0000 C CNN
F 2 "" H 2150 5300 60  0000 C CNN
F 3 "" H 2150 5300 60  0000 C CNN
	1    2150 5300
	1    0    0    -1  
$EndComp
$Comp
L AudioBoard-rescue:GND-Audio-DSP-rescue #PWR070
U 1 1 5BCCD2C6
P 2550 5300
F 0 "#PWR070" H 2550 5050 50  0001 C CNN
F 1 "GND" H 2550 5150 50  0000 C CNN
F 2 "" H 2550 5300 60  0000 C CNN
F 3 "" H 2550 5300 60  0000 C CNN
	1    2550 5300
	1    0    0    -1  
$EndComp
Wire Wire Line
	2150 4850 2150 5000
Wire Wire Line
	2150 5000 2250 5000
Wire Wire Line
	2450 5000 2550 5000
Wire Wire Line
	2550 4850 2550 5000
Connection ~ 2150 5000
Connection ~ 2550 5000
Text Label 2150 4850 0    60   ~ 0
OSC1
Text Label 2550 4850 0    60   ~ 0
OSC2
$Comp
L AudioBoard-rescue:23LC_SRAM-Audio-DSP-rescue U6
U 1 1 5BCCF519
P 8000 2450
F 0 "U6" H 7700 2700 50  0000 L CNN
F 1 "23LC_SRAM" H 8050 2700 50  0000 L CNN
F 2 "Package_DIP:DIP-8_W7.62mm" H 7650 2400 50  0001 C CNN
F 3 "" H 7650 2400 50  0001 C CNN
	1    8000 2450
	1    0    0    -1  
$EndComp
$Comp
L AudioBoard-rescue:+3.3V-Audio-DSP-rescue #PWR053
U 1 1 6156781B
P 8000 2150
F 0 "#PWR053" H 8000 2000 50  0001 C CNN
F 1 "+3.3V" H 8000 2290 50  0000 C CNN
F 2 "" H 8000 2150 60  0000 C CNN
F 3 "" H 8000 2150 60  0000 C CNN
	1    8000 2150
	1    0    0    -1  
$EndComp
$Comp
L AudioBoard-rescue:GND-Audio-DSP-rescue #PWR056
U 1 1 6156781C
P 8000 2750
F 0 "#PWR056" H 8000 2500 50  0001 C CNN
F 1 "GND" H 8000 2600 50  0000 C CNN
F 2 "" H 8000 2750 60  0000 C CNN
F 3 "" H 8000 2750 60  0000 C CNN
	1    8000 2750
	1    0    0    -1  
$EndComp
NoConn ~ 7600 2350
Wire Wire Line
	7600 2450 7500 2450
Wire Wire Line
	7500 2450 7500 2150
$Comp
L AudioBoard-rescue:+3.3V-Audio-DSP-rescue #PWR052
U 1 1 6156781D
P 7500 2150
F 0 "#PWR052" H 7500 2000 50  0001 C CNN
F 1 "+3.3V" H 7500 2290 50  0000 C CNN
F 2 "" H 7500 2150 60  0000 C CNN
F 3 "" H 7500 2150 60  0000 C CNN
	1    7500 2150
	1    0    0    -1  
$EndComp
Text Label 8400 2350 0    60   ~ 0
SCK1
Text Label 8400 2550 0    60   ~ 0
SDI1
Text Label 7600 2550 2    60   ~ 0
~SS10
Text Label 8400 2450 0    60   ~ 0
SDO1
$Comp
L AudioBoard-rescue:23LC_SRAM-Audio-DSP-rescue U8
U 1 1 6156781E
P 8000 3500
F 0 "U8" H 7700 3750 50  0000 L CNN
F 1 "23LC_SRAM" H 8050 3750 50  0000 L CNN
F 2 "Package_DIP:DIP-8_W7.62mm" H 7650 3450 50  0001 C CNN
F 3 "" H 7650 3450 50  0001 C CNN
	1    8000 3500
	1    0    0    -1  
$EndComp
$Comp
L AudioBoard-rescue:+3.3V-Audio-DSP-rescue #PWR061
U 1 1 61567950
P 8000 3200
F 0 "#PWR061" H 8000 3050 50  0001 C CNN
F 1 "+3.3V" H 8000 3340 50  0000 C CNN
F 2 "" H 8000 3200 60  0000 C CNN
F 3 "" H 8000 3200 60  0000 C CNN
	1    8000 3200
	1    0    0    -1  
$EndComp
$Comp
L AudioBoard-rescue:GND-Audio-DSP-rescue #PWR064
U 1 1 61567951
P 8000 3800
F 0 "#PWR064" H 8000 3550 50  0001 C CNN
F 1 "GND" H 8000 3650 50  0000 C CNN
F 2 "" H 8000 3800 60  0000 C CNN
F 3 "" H 8000 3800 60  0000 C CNN
	1    8000 3800
	1    0    0    -1  
$EndComp
NoConn ~ 7600 3400
Wire Wire Line
	7600 3500 7500 3500
Wire Wire Line
	7500 3500 7500 3200
$Comp
L AudioBoard-rescue:+3.3V-Audio-DSP-rescue #PWR060
U 1 1 61567821
P 7500 3200
F 0 "#PWR060" H 7500 3050 50  0001 C CNN
F 1 "+3.3V" H 7500 3340 50  0000 C CNN
F 2 "" H 7500 3200 60  0000 C CNN
F 3 "" H 7500 3200 60  0000 C CNN
	1    7500 3200
	1    0    0    -1  
$EndComp
Text Label 8400 3400 0    60   ~ 0
SCK1
Text Label 8400 3600 0    60   ~ 0
SDI1
Text Label 7600 3600 2    60   ~ 0
~SS11
Text Label 8400 3500 0    60   ~ 0
SDO1
Wire Wire Line
	5600 3800 5700 3800
Wire Wire Line
	5700 3800 5700 3750
Wire Wire Line
	5700 3750 5800 3750
Text HLabel 5800 3950 2    60   Input ~ 0
SDO0
Wire Wire Line
	5700 5050 5850 5050
$Comp
L AudioBoard-rescue:SW_Push-Audio-DSP-rescue SW3
U 1 1 61567822
P 5500 5050
F 0 "SW3" H 5550 5150 50  0000 L CNN
F 1 "RESET" H 5500 4990 50  0000 C CNN
F 2 "Button_Switch_THT:SW_PUSH_6mm" H 5500 5250 50  0001 C CNN
F 3 "" H 5500 5250 50  0001 C CNN
	1    5500 5050
	1    0    0    -1  
$EndComp
$Comp
L AudioBoard-rescue:GND-Audio-DSP-rescue #PWR071
U 1 1 61567823
P 5300 5450
F 0 "#PWR071" H 5300 5200 50  0001 C CNN
F 1 "GND" H 5300 5300 50  0000 C CNN
F 2 "" H 5300 5450 60  0000 C CNN
F 3 "" H 5300 5450 60  0000 C CNN
	1    5300 5450
	1    0    0    -1  
$EndComp
Wire Wire Line
	5300 5450 5300 5050
$Comp
L AudioBoard-rescue:C_Small-Audio-DSP-rescue C22
U 1 1 61567824
P 9250 3450
F 0 "C22" H 9260 3520 50  0000 L CNN
F 1 "100n" H 9260 3370 50  0000 L CNN
F 2 "Capacitor_THT:C_Disc_D4.3mm_W1.9mm_P5.00mm" H 9250 3450 60  0001 C CNN
F 3 "" H 9250 3450 60  0000 C CNN
	1    9250 3450
	1    0    0    -1  
$EndComp
$Comp
L AudioBoard-rescue:+3.3V-Audio-DSP-rescue #PWR062
U 1 1 61567825
P 9250 3350
F 0 "#PWR062" H 9250 3200 50  0001 C CNN
F 1 "+3.3V" H 9250 3490 50  0000 C CNN
F 2 "" H 9250 3350 60  0000 C CNN
F 3 "" H 9250 3350 60  0000 C CNN
	1    9250 3350
	1    0    0    -1  
$EndComp
$Comp
L AudioBoard-rescue:GND-Audio-DSP-rescue #PWR063
U 1 1 61567826
P 9250 3550
F 0 "#PWR063" H 9250 3300 50  0001 C CNN
F 1 "GND" H 9250 3400 50  0000 C CNN
F 2 "" H 9250 3550 60  0000 C CNN
F 3 "" H 9250 3550 60  0000 C CNN
	1    9250 3550
	1    0    0    -1  
$EndComp
$Comp
L AudioBoard-rescue:C_Small-Audio-DSP-rescue C18
U 1 1 61567958
P 9250 2450
F 0 "C18" H 9260 2520 50  0000 L CNN
F 1 "100n" H 9260 2370 50  0000 L CNN
F 2 "Capacitor_THT:C_Disc_D4.3mm_W1.9mm_P5.00mm" H 9250 2450 60  0001 C CNN
F 3 "" H 9250 2450 60  0000 C CNN
	1    9250 2450
	1    0    0    -1  
$EndComp
$Comp
L AudioBoard-rescue:+3.3V-Audio-DSP-rescue #PWR054
U 1 1 61567959
P 9250 2350
F 0 "#PWR054" H 9250 2200 50  0001 C CNN
F 1 "+3.3V" H 9250 2490 50  0000 C CNN
F 2 "" H 9250 2350 60  0000 C CNN
F 3 "" H 9250 2350 60  0000 C CNN
	1    9250 2350
	1    0    0    -1  
$EndComp
$Comp
L AudioBoard-rescue:GND-Audio-DSP-rescue #PWR055
U 1 1 6156795A
P 9250 2550
F 0 "#PWR055" H 9250 2300 50  0001 C CNN
F 1 "GND" H 9250 2400 50  0000 C CNN
F 2 "" H 9250 2550 60  0000 C CNN
F 3 "" H 9250 2550 60  0000 C CNN
	1    9250 2550
	1    0    0    -1  
$EndComp
Wire Wire Line
	2450 2600 2450 3000
Wire Wire Line
	2150 2200 2150 3000
Wire Wire Line
	5850 5050 5850 5150
Wire Wire Line
	5850 5050 6000 5050
Wire Wire Line
	2150 5000 2150 5100
Wire Wire Line
	2550 5000 2550 5100
Wire Wire Line
	3000 3650 2750 3650
Text Label 5600 2800 0    60   ~ 0
PGEC
NoConn ~ 5600 2000
NoConn ~ 5600 2700
NoConn ~ 5600 3600
NoConn ~ 5600 3100
Text Label 4700 5350 2    60   ~ 0
PGEC
$Comp
L AudioBoard-rescue:+3.3V-Audio-DSP-rescue #PWR051
U 1 1 61567C79
P 2450 2100
F 0 "#PWR051" H 2450 1950 50  0001 C CNN
F 1 "+3.3V" H 2450 2240 50  0000 C CNN
F 2 "" H 2450 2100 60  0000 C CNN
F 3 "" H 2450 2100 60  0000 C CNN
	1    2450 2100
	1    0    0    -1  
$EndComp
NoConn ~ 5600 1600
NoConn ~ 5600 1700
Text Label 5600 3700 0    60   ~ 0
~SS11
Text Label 5600 3200 0    60   ~ 0
~SS10
$Comp
L AudioBoard-rescue:Audio_DSPIC33EP128GP502-dspic33ep U7
U 1 1 6156782B
P 4300 3400
F 0 "U7" H 4300 5556 50  0000 C CNN
F 1 "DSPIC33EP128GP502" H 4300 5465 50  0000 C CNN
F 2 "Package_DIP:DIP-28_W7.62mm" H 4300 5374 50  0000 C CIN
F 3 "" H 3600 3000 60  0000 C CNN
	1    4300 3400
	1    0    0    -1  
$EndComp
NoConn ~ 5600 3000
NoConn ~ 5600 2600
Wire Wire Line
	2750 4000 2750 4100
Wire Wire Line
	3000 4100 2750 4100
Connection ~ 2750 4100
Wire Wire Line
	2750 4100 2750 4200
$EndSCHEMATC