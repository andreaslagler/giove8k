EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 4 24
Title "SS MUX"
Date "2021-07-21"
Rev "1.0"
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 "1-8 Line Multiplexer"
$EndDescr
Text HLabel 6550 3150 2    50   Input ~ 0
~SS0
Text HLabel 5550 3350 0    50   Input ~ 0
A2
$Comp
L power:GND #PWR017
U 1 1 60F8E7DC
P 5200 4150
F 0 "#PWR017" H 5200 3900 50  0001 C CNN
F 1 "GND" H 5205 3977 50  0000 C CNN
F 2 "" H 5200 4150 50  0001 C CNN
F 3 "" H 5200 4150 50  0001 C CNN
	1    5200 4150
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR018
U 1 1 60F9889F
P 6050 4150
F 0 "#PWR018" H 6050 3900 50  0001 C CNN
F 1 "GND" H 6055 3977 50  0000 C CNN
F 2 "" H 6050 4150 50  0001 C CNN
F 3 "" H 6050 4150 50  0001 C CNN
	1    6050 4150
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR013
U 1 1 60F8EC8A
P 6050 2850
F 0 "#PWR013" H 6050 2700 50  0001 C CNN
F 1 "+5V" H 6065 3023 50  0000 C CNN
F 2 "" H 6050 2850 50  0001 C CNN
F 3 "" H 6050 2850 50  0001 C CNN
	1    6050 2850
	1    0    0    -1  
$EndComp
$Comp
L Device:C C7
U 1 1 60F8EC8C
P 4450 3450
F 0 "C7" H 4565 3496 50  0000 L CNN
F 1 "100n" H 4565 3405 50  0000 L CNN
F 2 "Capacitor_THT:C_Disc_D5.0mm_W2.5mm_P5.00mm" H 4488 3300 50  0001 C CNN
F 3 "~" H 4450 3450 50  0001 C CNN
	1    4450 3450
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR015
U 1 1 60F8E7E1
P 4450 3600
F 0 "#PWR015" H 4450 3350 50  0001 C CNN
F 1 "GND" H 4455 3427 50  0000 C CNN
F 2 "" H 4450 3600 50  0001 C CNN
F 3 "" H 4450 3600 50  0001 C CNN
	1    4450 3600
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR014
U 1 1 60F8E7E2
P 4450 3300
F 0 "#PWR014" H 4450 3150 50  0001 C CNN
F 1 "+5V" H 4465 3473 50  0000 C CNN
F 2 "" H 4450 3300 50  0001 C CNN
F 3 "" H 4450 3300 50  0001 C CNN
	1    4450 3300
	1    0    0    -1  
$EndComp
Wire Wire Line
	5200 3650 5550 3650
$Comp
L power:+5V #PWR016
U 1 1 60F984EF
P 5200 3650
F 0 "#PWR016" H 5200 3500 50  0001 C CNN
F 1 "+5V" H 5215 3823 50  0000 C CNN
F 2 "" H 5200 3650 50  0001 C CNN
F 3 "" H 5200 3650 50  0001 C CNN
	1    5200 3650
	1    0    0    -1  
$EndComp
Wire Wire Line
	5550 3750 5200 3750
Wire Wire Line
	5200 3750 5200 4150
$Comp
L 74xx:74LS138 U2
U 1 1 60F8134C
P 6050 3450
F 0 "U2" H 6050 4231 50  0000 C CNN
F 1 "74HC138" H 6050 4140 50  0000 C CNN
F 2 "Package_DIP:DIP-16_W7.62mm" H 6050 3450 50  0001 C CNN
F 3 "http://www.ti.com/lit/gpn/sn74LS138" H 6050 3450 50  0001 C CNN
	1    6050 3450
	1    0    0    -1  
$EndComp
Text HLabel 5550 3150 0    50   Input ~ 0
A0
Text HLabel 5550 3250 0    50   Input ~ 0
A1
Text HLabel 5550 3850 0    50   Input ~ 0
~SS
Text HLabel 6550 3250 2    50   Input ~ 0
~SS1
Text HLabel 6550 3350 2    50   Input ~ 0
~SS2
Text HLabel 6550 3450 2    50   Input ~ 0
~SS3
Text HLabel 6550 3550 2    50   Input ~ 0
~SS4
Text HLabel 6550 3650 2    50   Input ~ 0
~SS5
Text HLabel 6550 3750 2    50   Input ~ 0
~SS6
Text HLabel 6550 3850 2    50   Input ~ 0
~SS7
$EndSCHEMATC
