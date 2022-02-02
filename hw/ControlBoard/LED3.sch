EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 15 24
Title "LED (1)"
Date "2021-07-20"
Rev "1.0"
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 "LEDs on 8 Bit shift register"
$EndDescr
Text HLabel 3750 3350 0    50   Input ~ 0
~SS
Text HLabel 3750 3050 0    50   Input ~ 0
SCK
Text HLabel 3750 2850 0    50   Input ~ 0
SDI
Text HLabel 4550 3750 2    50   Input ~ 0
SDO
$Comp
L power:GND #PWR0208
U 1 1 60F4A5D5
P 3400 3950
F 0 "#PWR0208" H 3400 3700 50  0001 C CNN
F 1 "GND" H 3405 3777 50  0000 C CNN
F 2 "" H 3400 3950 50  0001 C CNN
F 3 "" H 3400 3950 50  0001 C CNN
	1    3400 3950
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0209
U 1 1 60FDE39F
P 4150 3950
F 0 "#PWR0209" H 4150 3700 50  0001 C CNN
F 1 "GND" H 4155 3777 50  0000 C CNN
F 2 "" H 4150 3950 50  0001 C CNN
F 3 "" H 4150 3950 50  0001 C CNN
	1    4150 3950
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR0204
U 1 1 60FDE29F
P 4150 2650
F 0 "#PWR0204" H 4150 2500 50  0001 C CNN
F 1 "+5V" H 4165 2823 50  0000 C CNN
F 2 "" H 4150 2650 50  0001 C CNN
F 3 "" H 4150 2650 50  0001 C CNN
	1    4150 2650
	1    0    0    -1  
$EndComp
$Comp
L Device:C C18
U 1 1 60FDE2A1
P 2850 3300
F 0 "C18" H 2965 3346 50  0000 L CNN
F 1 "100n" H 2965 3255 50  0000 L CNN
F 2 "Capacitor_THT:C_Disc_D5.0mm_W2.5mm_P5.00mm" H 2888 3150 50  0001 C CNN
F 3 "~" H 2850 3300 50  0001 C CNN
	1    2850 3300
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0207
U 1 1 60FE63C3
P 2850 3450
F 0 "#PWR0207" H 2850 3200 50  0001 C CNN
F 1 "GND" H 2855 3277 50  0000 C CNN
F 2 "" H 2850 3450 50  0001 C CNN
F 3 "" H 2850 3450 50  0001 C CNN
	1    2850 3450
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR0205
U 1 1 60FE63C4
P 2850 3150
F 0 "#PWR0205" H 2850 3000 50  0001 C CNN
F 1 "+5V" H 2865 3323 50  0000 C CNN
F 2 "" H 2850 3150 50  0001 C CNN
F 3 "" H 2850 3150 50  0001 C CNN
	1    2850 3150
	1    0    0    -1  
$EndComp
Wire Wire Line
	3400 3150 3750 3150
$Comp
L power:+5V #PWR0206
U 1 1 60FDE2A0
P 3400 3150
F 0 "#PWR0206" H 3400 3000 50  0001 C CNN
F 1 "+5V" H 3415 3323 50  0000 C CNN
F 2 "" H 3400 3150 50  0001 C CNN
F 3 "" H 3400 3150 50  0001 C CNN
	1    3400 3150
	1    0    0    -1  
$EndComp
$Comp
L 74xx:74HC595 U14
U 1 1 60FDE2A4
P 4150 3250
F 0 "U14" H 4150 4031 50  0000 C CNN
F 1 "74HC595" H 4150 3940 50  0000 C CNN
F 2 "Package_DIP:DIP-16_W7.62mm" H 4150 3250 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/sn74hc595.pdf" H 4150 3250 50  0001 C CNN
	1    4150 3250
	1    0    0    -1  
$EndComp
Wire Wire Line
	3750 3450 3400 3450
Wire Wire Line
	3400 3450 3400 3950
$Comp
L Device:LED D18
U 1 1 60FDE3A6
P 5300 4150
F 0 "D18" V 5339 4033 50  0000 R CNN
F 1 "LED" V 5248 4033 50  0000 R CNN
F 2 "LED_THT:LED_D3.0mm" H 5300 4150 50  0001 C CNN
F 3 "~" H 5300 4150 50  0001 C CNN
	1    5300 4150
	0    -1   -1   0   
$EndComp
$Comp
L Device:R R25
U 1 1 60FDE3A7
P 5300 3850
F 0 "R25" H 5370 3896 50  0000 L CNN
F 1 "1k5" H 5370 3805 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 5230 3850 50  0001 C CNN
F 3 "~" H 5300 3850 50  0001 C CNN
	1    5300 3850
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0210
U 1 1 60FDE3A8
P 5300 4300
F 0 "#PWR0210" H 5300 4050 50  0001 C CNN
F 1 "GND" H 5305 4127 50  0000 C CNN
F 2 "" H 5300 4300 50  0001 C CNN
F 3 "" H 5300 4300 50  0001 C CNN
	1    5300 4300
	1    0    0    -1  
$EndComp
$Comp
L Device:LED D19
U 1 1 60FDE4AA
P 5750 4150
F 0 "D19" V 5789 4033 50  0000 R CNN
F 1 "LED" V 5698 4033 50  0000 R CNN
F 2 "LED_THT:LED_D3.0mm" H 5750 4150 50  0001 C CNN
F 3 "~" H 5750 4150 50  0001 C CNN
	1    5750 4150
	0    -1   -1   0   
$EndComp
$Comp
L Device:R R26
U 1 1 60FE63CA
P 5750 3850
F 0 "R26" H 5820 3896 50  0000 L CNN
F 1 "1k5" H 5820 3805 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 5680 3850 50  0001 C CNN
F 3 "~" H 5750 3850 50  0001 C CNN
	1    5750 3850
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0211
U 1 1 60FDE4AC
P 5750 4300
F 0 "#PWR0211" H 5750 4050 50  0001 C CNN
F 1 "GND" H 5755 4127 50  0000 C CNN
F 2 "" H 5750 4300 50  0001 C CNN
F 3 "" H 5750 4300 50  0001 C CNN
	1    5750 4300
	1    0    0    -1  
$EndComp
$Comp
L Device:LED D20
U 1 1 60FDE4AD
P 6200 4150
F 0 "D20" V 6239 4033 50  0000 R CNN
F 1 "LED" V 6148 4033 50  0000 R CNN
F 2 "LED_THT:LED_D3.0mm" H 6200 4150 50  0001 C CNN
F 3 "~" H 6200 4150 50  0001 C CNN
	1    6200 4150
	0    -1   -1   0   
$EndComp
$Comp
L Device:R R27
U 1 1 60FDE2AC
P 6200 3850
F 0 "R27" H 6270 3896 50  0000 L CNN
F 1 "1k5" H 6270 3805 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 6130 3850 50  0001 C CNN
F 3 "~" H 6200 3850 50  0001 C CNN
	1    6200 3850
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0212
U 1 1 60FDE4AF
P 6200 4300
F 0 "#PWR0212" H 6200 4050 50  0001 C CNN
F 1 "GND" H 6205 4127 50  0000 C CNN
F 2 "" H 6200 4300 50  0001 C CNN
F 3 "" H 6200 4300 50  0001 C CNN
	1    6200 4300
	1    0    0    -1  
$EndComp
$Comp
L Device:LED D21
U 1 1 60FDE3AF
P 6650 4150
F 0 "D21" V 6689 4033 50  0000 R CNN
F 1 "LED" V 6598 4033 50  0000 R CNN
F 2 "LED_THT:LED_D3.0mm" H 6650 4150 50  0001 C CNN
F 3 "~" H 6650 4150 50  0001 C CNN
	1    6650 4150
	0    -1   -1   0   
$EndComp
$Comp
L Device:R R28
U 1 1 60FDE2AF
P 6650 3850
F 0 "R28" H 6720 3896 50  0000 L CNN
F 1 "1k5" H 6720 3805 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 6580 3850 50  0001 C CNN
F 3 "~" H 6650 3850 50  0001 C CNN
	1    6650 3850
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0213
U 1 1 60FDE2B0
P 6650 4300
F 0 "#PWR0213" H 6650 4050 50  0001 C CNN
F 1 "GND" H 6655 4127 50  0000 C CNN
F 2 "" H 6650 4300 50  0001 C CNN
F 3 "" H 6650 4300 50  0001 C CNN
	1    6650 4300
	1    0    0    -1  
$EndComp
$Comp
L Device:LED D22
U 1 1 60FDE3B2
P 7050 4150
F 0 "D22" V 7089 4033 50  0000 R CNN
F 1 "LED" V 6998 4033 50  0000 R CNN
F 2 "LED_THT:LED_D3.0mm" H 7050 4150 50  0001 C CNN
F 3 "~" H 7050 4150 50  0001 C CNN
	1    7050 4150
	0    -1   -1   0   
$EndComp
$Comp
L Device:R R29
U 1 1 60FDE2B2
P 7050 3850
F 0 "R29" H 7120 3896 50  0000 L CNN
F 1 "1k5" H 7120 3805 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 6980 3850 50  0001 C CNN
F 3 "~" H 7050 3850 50  0001 C CNN
	1    7050 3850
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0214
U 1 1 60FDE3B4
P 7050 4300
F 0 "#PWR0214" H 7050 4050 50  0001 C CNN
F 1 "GND" H 7055 4127 50  0000 C CNN
F 2 "" H 7050 4300 50  0001 C CNN
F 3 "" H 7050 4300 50  0001 C CNN
	1    7050 4300
	1    0    0    -1  
$EndComp
$Comp
L Device:LED D23
U 1 1 60FDE2B4
P 7500 4150
F 0 "D23" V 7539 4033 50  0000 R CNN
F 1 "LED" V 7448 4033 50  0000 R CNN
F 2 "LED_THT:LED_D3.0mm" H 7500 4150 50  0001 C CNN
F 3 "~" H 7500 4150 50  0001 C CNN
	1    7500 4150
	0    -1   -1   0   
$EndComp
$Comp
L Device:R R30
U 1 1 60FDE2B5
P 7500 3850
F 0 "R30" H 7570 3896 50  0000 L CNN
F 1 "1k5" H 7570 3805 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 7430 3850 50  0001 C CNN
F 3 "~" H 7500 3850 50  0001 C CNN
	1    7500 3850
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0215
U 1 1 60FDE2B6
P 7500 4300
F 0 "#PWR0215" H 7500 4050 50  0001 C CNN
F 1 "GND" H 7505 4127 50  0000 C CNN
F 2 "" H 7500 4300 50  0001 C CNN
F 3 "" H 7500 4300 50  0001 C CNN
	1    7500 4300
	1    0    0    -1  
$EndComp
$Comp
L Device:LED D24
U 1 1 60FDE4B9
P 7950 4150
F 0 "D24" V 7989 4033 50  0000 R CNN
F 1 "LED" V 7898 4033 50  0000 R CNN
F 2 "LED_THT:LED_D3.0mm" H 7950 4150 50  0001 C CNN
F 3 "~" H 7950 4150 50  0001 C CNN
	1    7950 4150
	0    -1   -1   0   
$EndComp
$Comp
L Device:R R31
U 1 1 60FDE2B8
P 7950 3850
F 0 "R31" H 8020 3896 50  0000 L CNN
F 1 "1k5" H 8020 3805 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 7880 3850 50  0001 C CNN
F 3 "~" H 7950 3850 50  0001 C CNN
	1    7950 3850
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0216
U 1 1 60FDE3BA
P 7950 4300
F 0 "#PWR0216" H 7950 4050 50  0001 C CNN
F 1 "GND" H 7955 4127 50  0000 C CNN
F 2 "" H 7950 4300 50  0001 C CNN
F 3 "" H 7950 4300 50  0001 C CNN
	1    7950 4300
	1    0    0    -1  
$EndComp
$Comp
L Device:LED D25
U 1 1 60FDE2BA
P 8400 4150
F 0 "D25" V 8439 4033 50  0000 R CNN
F 1 "LED" V 8348 4033 50  0000 R CNN
F 2 "LED_THT:LED_D3.0mm" H 8400 4150 50  0001 C CNN
F 3 "~" H 8400 4150 50  0001 C CNN
	1    8400 4150
	0    -1   -1   0   
$EndComp
$Comp
L Device:R R32
U 1 1 60FDE3BC
P 8400 3850
F 0 "R32" H 8470 3896 50  0000 L CNN
F 1 "1k5" H 8470 3805 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 8330 3850 50  0001 C CNN
F 3 "~" H 8400 3850 50  0001 C CNN
	1    8400 3850
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0217
U 1 1 60FDE3BD
P 8400 4300
F 0 "#PWR0217" H 8400 4050 50  0001 C CNN
F 1 "GND" H 8405 4127 50  0000 C CNN
F 2 "" H 8400 4300 50  0001 C CNN
F 3 "" H 8400 4300 50  0001 C CNN
	1    8400 4300
	1    0    0    -1  
$EndComp
Wire Wire Line
	4550 3550 5300 3550
Wire Wire Line
	5300 3550 5300 3700
Wire Wire Line
	4550 3450 5750 3450
Wire Wire Line
	5750 3450 5750 3700
Wire Wire Line
	4550 3350 6200 3350
Wire Wire Line
	6200 3350 6200 3700
Wire Wire Line
	4550 3250 6650 3250
Wire Wire Line
	6650 3250 6650 3700
Wire Wire Line
	4550 3150 7050 3150
Wire Wire Line
	7050 3150 7050 3700
Wire Wire Line
	4550 3050 7500 3050
Wire Wire Line
	7500 3050 7500 3700
Wire Wire Line
	4550 2950 7950 2950
Wire Wire Line
	7950 2950 7950 3700
Wire Wire Line
	4550 2850 8400 2850
Wire Wire Line
	8400 2850 8400 3700
$EndSCHEMATC