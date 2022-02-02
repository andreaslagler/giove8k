EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 3 24
Title "CPU m328p"
Date "2021-07-21"
Rev "1.0"
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 "Atmega328p"
$EndDescr
$Comp
L ControlBoard-rescue:C_Small-CPU-rescue-CPU-rescue C5
U 1 1 5A1DD706
P 1100 4100
F 0 "C5" H 1110 4170 50  0000 L CNN
F 1 "100n" H 1110 4020 50  0000 L CNN
F 2 "Capacitor_THT:C_Disc_D5.0mm_W2.5mm_P5.00mm" H 1100 4100 60  0001 C CNN
F 3 "" H 1100 4100 60  0000 C CNN
	1    1100 4100
	1    0    0    -1  
$EndComp
$Comp
L ControlBoard-rescue:C_Small-CPU-rescue-CPU-rescue C6
U 1 1 5A1DD76F
P 1400 4100
F 0 "C6" H 1410 4170 50  0000 L CNN
F 1 "100n" H 1410 4020 50  0000 L CNN
F 2 "Capacitor_THT:C_Disc_D5.0mm_W2.5mm_P5.00mm" H 1400 4100 60  0001 C CNN
F 3 "" H 1400 4100 60  0000 C CNN
	1    1400 4100
	1    0    0    -1  
$EndComp
$Comp
L ControlBoard-rescue:GND-CPU-rescue-CPU-rescue #PWR012
U 1 1 5A1DD7D1
P 1100 4200
F 0 "#PWR012" H 1100 3950 50  0001 C CNN
F 1 "GND" H 1100 4050 50  0000 C CNN
F 2 "" H 1100 4200 60  0000 C CNN
F 3 "" H 1100 4200 60  0000 C CNN
	1    1100 4200
	1    0    0    -1  
$EndComp
$Comp
L ControlBoard-rescue:+5V-CPU-rescue-CPU-rescue #PWR010
U 1 1 5A1DD96D
P 1100 4000
AR Path="/5A1DD96D" Ref="#PWR010"  Part="1" 
AR Path="/60FD934A/60F8CC98/5A1DD96D" Ref="#PWR010"  Part="1" 
F 0 "#PWR010" H 1100 3850 50  0001 C CNN
F 1 "+5V" H 1100 4140 50  0000 C CNN
F 2 "" H 1100 4000 60  0000 C CNN
F 3 "" H 1100 4000 60  0000 C CNN
	1    1100 4000
	1    0    0    -1  
$EndComp
Connection ~ 1100 4000
Connection ~ 1100 4200
$Comp
L ControlBoard-rescue:ATMEGA328P-PU-CPU_TestBoard-cache-CPU-rescue U1
U 1 1 5A520401
P 3950 2800
F 0 "U1" H 3200 4050 50  0000 L BNN
F 1 "ATMEGA328P-PU" H 4350 1400 50  0000 L BNN
F 2 "Package_DIP:DIP-28_W7.62mm" H 3950 2800 50  0001 C CIN
F 3 "" H 3950 2800 50  0001 C CNN
	1    3950 2800
	1    0    0    -1  
$EndComp
$Comp
L ControlBoard-rescue:+5V-CPU-rescue-CPU-rescue #PWR02
U 1 1 5A520462
P 3050 1600
AR Path="/5A520462" Ref="#PWR02"  Part="1" 
AR Path="/60FD934A/60F8CC98/5A520462" Ref="#PWR02"  Part="1" 
F 0 "#PWR02" H 3050 1450 50  0001 C CNN
F 1 "+5V" H 3050 1740 50  0000 C CNN
F 2 "" H 3050 1600 60  0000 C CNN
F 3 "" H 3050 1600 60  0000 C CNN
	1    3050 1600
	1    0    0    -1  
$EndComp
$Comp
L ControlBoard-rescue:GND-CPU-rescue-CPU-rescue #PWR011
U 1 1 5A520874
P 3050 4100
F 0 "#PWR011" H 3050 3850 50  0001 C CNN
F 1 "GND" H 3050 3950 50  0000 C CNN
F 2 "" H 3050 4100 60  0000 C CNN
F 3 "" H 3050 4100 60  0000 C CNN
	1    3050 4100
	1    0    0    -1  
$EndComp
Text HLabel 4950 3300 2    60   Input ~ 0
RX
Text HLabel 4950 3400 2    60   Input ~ 0
TX
Text HLabel 4950 3500 2    60   Input ~ 0
INT0
Text HLabel 4950 3600 2    60   Input ~ 0
INT1
Text HLabel 4950 2550 2    60   Input ~ 0
AN0
Text HLabel 4950 2650 2    60   Input ~ 0
AN1
Text HLabel 4950 2750 2    60   Input ~ 0
AN2
Text HLabel 4950 2850 2    60   Input ~ 0
AN3
Wire Wire Line
	4950 2300 6300 2300
Wire Wire Line
	6800 2400 4950 2400
Wire Wire Line
	6800 2300 6800 2400
$Comp
L ControlBoard-rescue:Crystal_Small-CPU-rescue-CPU-rescue Y1
U 1 1 5A522586
P 6550 2300
F 0 "Y1" H 6550 2400 50  0000 C CNN
F 1 "20 MHz" H 6550 2200 50  0000 C CNN
F 2 "Crystal:Crystal_HC49-U_Vertical" H 6550 2300 60  0001 C CNN
F 3 "" H 6550 2300 60  0000 C CNN
	1    6550 2300
	1    0    0    -1  
$EndComp
Wire Wire Line
	6300 2300 6300 2500
Wire Wire Line
	6650 2300 6800 2300
Connection ~ 6300 2300
Connection ~ 6800 2400
$Comp
L ControlBoard-rescue:C_Small-CPU-rescue-CPU-rescue C2
U 1 1 5A523106
P 6300 2600
F 0 "C2" H 6310 2670 50  0000 L CNN
F 1 "22p" H 6310 2520 50  0000 L CNN
F 2 "Capacitor_THT:C_Disc_D3.0mm_W1.6mm_P2.50mm" H 6300 2600 60  0001 C CNN
F 3 "" H 6300 2600 60  0000 C CNN
	1    6300 2600
	1    0    0    -1  
$EndComp
$Comp
L ControlBoard-rescue:C_Small-CPU-rescue-CPU-rescue C3
U 1 1 5A52310C
P 6800 2600
F 0 "C3" H 6810 2670 50  0000 L CNN
F 1 "22p" H 6810 2520 50  0000 L CNN
F 2 "Capacitor_THT:C_Disc_D3.0mm_W1.6mm_P2.50mm" H 6800 2600 60  0001 C CNN
F 3 "" H 6800 2600 60  0000 C CNN
	1    6800 2600
	1    0    0    -1  
$EndComp
$Comp
L ControlBoard-rescue:GND-CPU-rescue-CPU-rescue #PWR06
U 1 1 5A523112
P 6800 2700
F 0 "#PWR06" H 6800 2450 50  0001 C CNN
F 1 "GND" H 6800 2550 50  0000 C CNN
F 2 "" H 6800 2700 60  0000 C CNN
F 3 "" H 6800 2700 60  0000 C CNN
	1    6800 2700
	1    0    0    -1  
$EndComp
$Comp
L ControlBoard-rescue:GND-CPU-rescue-CPU-rescue #PWR05
U 1 1 5A523118
P 6300 2700
F 0 "#PWR05" H 6300 2450 50  0001 C CNN
F 1 "GND" H 6300 2550 50  0000 C CNN
F 2 "" H 6300 2700 60  0000 C CNN
F 3 "" H 6300 2700 60  0000 C CNN
	1    6300 2700
	1    0    0    -1  
$EndComp
Text HLabel 4950 1900 2    60   Input ~ 0
~SS~
Text HLabel 7000 2000 2    60   Input ~ 0
MOSI
Text HLabel 7000 2100 2    60   Input ~ 0
MISO
Text HLabel 7000 2200 2    60   Input ~ 0
SCK
Text HLabel 4950 3800 2    60   Input ~ 0
MUX0
Text HLabel 4950 3900 2    60   Input ~ 0
MUX1
Text HLabel 4950 4000 2    60   Input ~ 0
MUX2
Text HLabel 4950 3700 2    60   Input ~ 0
CLK_IN
Text HLabel 4950 1700 2    60   Input ~ 0
CLK_OUT
Text HLabel 4950 1800 2    60   Input ~ 0
SYNC_OUT
Wire Wire Line
	1100 4000 1400 4000
Wire Wire Line
	1100 4200 1400 4200
$Comp
L ControlBoard-rescue:C_Small-CPU-rescue-CPU-rescue C1
U 1 1 5A533B4B
P 2950 2500
F 0 "C1" H 2960 2570 50  0000 L CNN
F 1 "100n" H 2960 2420 50  0000 L CNN
F 2 "Capacitor_THT:C_Disc_D5.0mm_W2.5mm_P5.00mm" H 2950 2500 60  0001 C CNN
F 3 "" H 2950 2500 60  0000 C CNN
	1    2950 2500
	1    0    0    -1  
$EndComp
$Comp
L ControlBoard-rescue:GND-CPU-rescue-CPU-rescue #PWR04
U 1 1 5A533B86
P 2950 2600
F 0 "#PWR04" H 2950 2350 50  0001 C CNN
F 1 "GND" H 2950 2450 50  0000 C CNN
F 2 "" H 2950 2600 60  0000 C CNN
F 3 "" H 2950 2600 60  0000 C CNN
	1    2950 2600
	1    0    0    -1  
$EndComp
Wire Wire Line
	2950 2400 2950 2300
Wire Wire Line
	2950 2300 3050 2300
Text HLabel 4950 2950 2    60   Input ~ 0
AN4
Text HLabel 4950 3050 2    60   Input ~ 0
AN5
$Comp
L ControlBoard-rescue:R_Small-CPU-rescue-CPU-rescue R1
U 1 1 5B557357
P 6850 3150
F 0 "R1" H 6880 3170 50  0000 L CNN
F 1 "10k" H 6880 3110 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" H 6850 3150 50  0001 C CNN
F 3 "" H 6850 3150 50  0001 C CNN
	1    6850 3150
	0    -1   1    0   
$EndComp
$Comp
L ControlBoard-rescue:C_Small-CPU-rescue-CPU-rescue C4
U 1 1 5B55735E
P 6400 3450
F 0 "C4" H 6410 3520 50  0000 L CNN
F 1 "100n" H 6410 3370 50  0000 L CNN
F 2 "Capacitor_THT:C_Disc_D5.0mm_W2.5mm_P5.00mm" H 6400 3450 50  0001 C CNN
F 3 "" H 6400 3450 50  0001 C CNN
	1    6400 3450
	-1   0    0    -1  
$EndComp
$Comp
L ControlBoard-rescue:SW_Push-CPU-rescue-CPU-rescue SW1
U 1 1 5B557365
P 6600 3450
F 0 "SW1" H 6650 3550 50  0000 L CNN
F 1 "SW_Push" H 6600 3390 50  0000 C CNN
F 2 "Button_Switch_THT:SW_PUSH_6mm" H 6600 3650 50  0001 C CNN
F 3 "" H 6600 3650 50  0001 C CNN
	1    6600 3450
	0    1    -1   0   
$EndComp
$Comp
L ControlBoard-rescue:GND-CPU-rescue-CPU-rescue #PWR09
U 1 1 5B55736C
P 6600 3650
F 0 "#PWR09" H 6600 3400 50  0001 C CNN
F 1 "GND" H 6600 3500 50  0000 C CNN
F 2 "" H 6600 3650 50  0001 C CNN
F 3 "" H 6600 3650 50  0001 C CNN
	1    6600 3650
	-1   0    0    -1  
$EndComp
$Comp
L ControlBoard-rescue:GND-CPU-rescue-CPU-rescue #PWR08
U 1 1 5B557372
P 6400 3650
F 0 "#PWR08" H 6400 3400 50  0001 C CNN
F 1 "GND" H 6400 3500 50  0000 C CNN
F 2 "" H 6400 3650 50  0001 C CNN
F 3 "" H 6400 3650 50  0001 C CNN
	1    6400 3650
	-1   0    0    -1  
$EndComp
$Comp
L ControlBoard-rescue:+5V-CPU-rescue-CPU-rescue #PWR07
U 1 1 5B557379
P 7050 3100
AR Path="/5B557379" Ref="#PWR07"  Part="1" 
AR Path="/60FD934A/60F8CC98/5B557379" Ref="#PWR07"  Part="1" 
F 0 "#PWR07" H 7050 2950 50  0001 C CNN
F 1 "+5V" H 7050 3240 50  0000 C CNN
F 2 "" H 7050 3100 50  0001 C CNN
F 3 "" H 7050 3100 50  0001 C CNN
	1    7050 3100
	-1   0    0    -1  
$EndComp
Wire Wire Line
	6600 3250 6600 3150
Connection ~ 6600 3150
Wire Wire Line
	6400 3150 6400 3350
Connection ~ 6400 3150
Wire Wire Line
	6400 3550 6400 3650
Wire Wire Line
	6950 3150 7050 3150
Wire Wire Line
	7050 3150 7050 3100
Wire Wire Line
	6300 2300 6450 2300
Wire Wire Line
	6800 2400 6800 2500
Wire Wire Line
	6600 3150 6750 3150
Wire Wire Line
	6400 3150 6600 3150
Wire Wire Line
	3050 3900 3050 4000
Wire Wire Line
	3050 1600 3050 1700
Connection ~ 3050 1700
Wire Wire Line
	3050 1700 3050 2000
Connection ~ 3050 4000
Wire Wire Line
	3050 4000 3050 4100
$Comp
L Connector:AVR-ISP-6 J1
U 1 1 610256F1
P 6700 1350
F 0 "J1" H 6370 1446 50  0000 R CNN
F 1 "AVR-ISP-6" H 6370 1355 50  0000 R CNN
F 2 "Connector_IDC:IDC-Header_2x03_P2.54mm_Vertical" V 6450 1400 50  0001 C CNN
F 3 " ~" H 5425 800 50  0001 C CNN
	1    6700 1350
	-1   0    0    -1  
$EndComp
$Comp
L ControlBoard-rescue:+5V-CPU-rescue-CPU-rescue #PWR01
U 1 1 5B558078
P 6800 850
AR Path="/5B558078" Ref="#PWR01"  Part="1" 
AR Path="/60FD934A/60F8CC98/5B558078" Ref="#PWR01"  Part="1" 
F 0 "#PWR01" H 6800 700 50  0001 C CNN
F 1 "+5V" H 6800 990 50  0000 C CNN
F 2 "" H 6800 850 50  0001 C CNN
F 3 "" H 6800 850 50  0001 C CNN
	1    6800 850 
	-1   0    0    -1  
$EndComp
$Comp
L ControlBoard-rescue:GND-CPU-rescue-CPU-rescue #PWR03
U 1 1 5B55806B
P 6800 1750
F 0 "#PWR03" H 6800 1500 50  0001 C CNN
F 1 "GND" H 6800 1600 50  0000 C CNN
F 2 "" H 6800 1750 50  0001 C CNN
F 3 "" H 6800 1750 50  0001 C CNN
	1    6800 1750
	-1   0    0    -1  
$EndComp
Wire Wire Line
	4950 3150 6100 3150
Wire Wire Line
	4950 2000 5900 2000
Wire Wire Line
	4950 2200 6000 2200
Wire Wire Line
	4950 2100 5800 2100
Wire Wire Line
	6300 1450 6100 1450
Wire Wire Line
	6100 1450 6100 3150
Connection ~ 6100 3150
Wire Wire Line
	6100 3150 6400 3150
Wire Wire Line
	6300 1350 6000 1350
Wire Wire Line
	6000 1350 6000 2200
Connection ~ 6000 2200
Wire Wire Line
	6000 2200 7000 2200
Wire Wire Line
	6300 1250 5900 1250
Wire Wire Line
	5900 1250 5900 2000
Connection ~ 5900 2000
Wire Wire Line
	5900 2000 7000 2000
Wire Wire Line
	6300 1150 5800 1150
Wire Wire Line
	5800 1150 5800 2100
Connection ~ 5800 2100
Wire Wire Line
	5800 2100 7000 2100
$EndSCHEMATC
