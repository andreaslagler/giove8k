EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 3 9
Title "Audio DSP"
Date "2021-07-24"
Rev "1.0"
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 "Audio DSP with DAC interface"
$EndDescr
$Comp
L AudioBoard-rescue:C_Small-Audio-Audio-rescue C2
U 1 1 60FCACCC
P 2950 2600
F 0 "C2" H 2960 2670 50  0000 L CNN
F 1 "100n" H 2960 2520 50  0000 L CNN
F 2 "Capacitor_THT:C_Disc_D4.3mm_W1.9mm_P5.00mm" H 2950 2600 60  0001 C CNN
F 3 "" H 2950 2600 60  0000 C CNN
	1    2950 2600
	1    0    0    -1  
$EndComp
$Comp
L AudioBoard-rescue:C_Small-Audio-Audio-rescue C1
U 1 1 60FCACCD
P 2650 2600
F 0 "C1" H 2660 2670 50  0000 L CNN
F 1 "100n" H 2660 2520 50  0000 L CNN
F 2 "Capacitor_THT:C_Disc_D4.3mm_W1.9mm_P5.00mm" H 2650 2600 60  0001 C CNN
F 3 "" H 2650 2600 60  0000 C CNN
	1    2650 2600
	1    0    0    -1  
$EndComp
$Comp
L AudioBoard-rescue:CP_Small-Audio-Audio-rescue C3
U 1 1 60FCAB0B
P 3250 2600
F 0 "C3" H 3260 2670 50  0000 L CNN
F 1 "10u" H 3260 2520 50  0000 L CNN
F 2 "Capacitor_THT:CP_Radial_D5.0mm_P2.50mm" H 3250 2600 60  0001 C CNN
F 3 "" H 3250 2600 60  0000 C CNN
	1    3250 2600
	1    0    0    -1  
$EndComp
$Comp
L AudioBoard-rescue:GND-Audio-Audio-rescue #PWR07
U 1 1 60FCAB0C
P 2650 2700
F 0 "#PWR07" H 2650 2450 50  0001 C CNN
F 1 "GND" H 2650 2550 50  0000 C CNN
F 2 "" H 2650 2700 60  0000 C CNN
F 3 "" H 2650 2700 60  0000 C CNN
	1    2650 2700
	1    0    0    -1  
$EndComp
$Comp
L AudioBoard-rescue:GND-Audio-Audio-rescue #PWR08
U 1 1 60FCAB0D
P 2950 2700
F 0 "#PWR08" H 2950 2450 50  0001 C CNN
F 1 "GND" H 2950 2550 50  0000 C CNN
F 2 "" H 2950 2700 60  0000 C CNN
F 3 "" H 2950 2700 60  0000 C CNN
	1    2950 2700
	1    0    0    -1  
$EndComp
$Comp
L AudioBoard-rescue:GND-Audio-Audio-rescue #PWR09
U 1 1 60FCAB0E
P 3250 2700
F 0 "#PWR09" H 3250 2450 50  0001 C CNN
F 1 "GND" H 3250 2550 50  0000 C CNN
F 2 "" H 3250 2700 60  0000 C CNN
F 3 "" H 3250 2700 60  0000 C CNN
	1    3250 2700
	1    0    0    -1  
$EndComp
$Comp
L AudioBoard-rescue:GND-Audio-Audio-rescue #PWR010
U 1 1 60FCAB0F
P 3250 3700
F 0 "#PWR010" H 3250 3450 50  0001 C CNN
F 1 "GND" H 3250 3550 50  0000 C CNN
F 2 "" H 3250 3700 60  0000 C CNN
F 3 "" H 3250 3700 60  0000 C CNN
	1    3250 3700
	1    0    0    -1  
$EndComp
Text Label 6100 1300 0    60   ~ 0
OSC1
Text Label 6100 1400 0    60   ~ 0
OSC2
Text Label 6100 1500 0    60   ~ 0
SOSCO
Text Label 6100 2500 0    60   ~ 0
SOSCI
$Comp
L AudioBoard-rescue:+3.3V-Audio-Audio-rescue #PWR05
U 1 1 60FCAB10
P 2650 1600
AR Path="/60FCAB10" Ref="#PWR05"  Part="1" 
AR Path="/615A376B/61563857/60FCAB10" Ref="#PWR05"  Part="1" 
F 0 "#PWR05" H 2650 1450 50  0001 C CNN
F 1 "+3.3V" H 2650 1740 50  0000 C CNN
F 2 "" H 2650 1600 60  0000 C CNN
F 3 "" H 2650 1600 60  0000 C CNN
	1    2650 1600
	1    0    0    -1  
$EndComp
Wire Wire Line
	3500 2400 3250 2400
Wire Wire Line
	3250 2400 3250 2500
Wire Wire Line
	3500 2100 2950 2100
Wire Wire Line
	2950 1600 2950 2100
Wire Wire Line
	3500 1700 2650 1700
Wire Wire Line
	2650 1600 2650 1700
Wire Wire Line
	3250 3600 3500 3600
Wire Wire Line
	3250 3150 3250 3500
Wire Wire Line
	3500 3500 3250 3500
Connection ~ 3250 3500
Connection ~ 3250 3600
Connection ~ 2950 2100
Connection ~ 2650 1700
Text Label 6100 3300 0    60   ~ 0
~SS1
Text Label 3500 1100 2    60   ~ 0
~MCLR
Text HLabel 6300 2650 2    60   Input ~ 0
SCK0
Text HLabel 6300 2750 2    60   Input ~ 0
SDI0
Text HLabel 6300 2950 2    60   Input ~ 0
~SS0
Wire Wire Line
	6100 2700 6200 2700
Wire Wire Line
	6200 2700 6200 2650
Wire Wire Line
	6200 2650 6300 2650
Wire Wire Line
	6100 2800 6200 2800
Wire Wire Line
	6200 2800 6200 2750
Wire Wire Line
	6200 2750 6300 2750
Wire Wire Line
	6100 2900 6200 2900
Wire Wire Line
	6200 2900 6200 2850
Wire Wire Line
	6200 2850 6300 2850
Text Label 6500 4550 0    60   ~ 0
~MCLR
$Comp
L AudioBoard-rescue:C_Small-Audio-Audio-rescue C8
U 1 1 60FCAB11
P 6350 4750
F 0 "C8" H 6360 4820 50  0000 L CNN
F 1 "100n" H 6360 4670 50  0000 L CNN
F 2 "Capacitor_THT:C_Disc_D4.3mm_W1.9mm_P5.00mm" H 6350 4750 60  0001 C CNN
F 3 "" H 6350 4750 60  0000 C CNN
	1    6350 4750
	1    0    0    -1  
$EndComp
Wire Wire Line
	6350 4850 6350 4950
Wire Wire Line
	6350 4450 6350 4550
Connection ~ 6350 4550
$Comp
L AudioBoard-rescue:GND-Audio-Audio-rescue #PWR022
U 1 1 60FCACD5
P 6350 4950
F 0 "#PWR022" H 6350 4700 50  0001 C CNN
F 1 "GND" H 6350 4800 50  0000 C CNN
F 2 "" H 6350 4950 60  0000 C CNN
F 3 "" H 6350 4950 60  0000 C CNN
	1    6350 4950
	1    0    0    -1  
$EndComp
$Comp
L AudioBoard-rescue:R_Small-Audio-Audio-rescue R1
U 1 1 60FCAB13
P 6350 4350
F 0 "R1" H 6380 4370 50  0000 L CNN
F 1 "10k" H 6380 4310 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" H 6350 4350 60  0001 C CNN
F 3 "" H 6350 4350 60  0000 C CNN
	1    6350 4350
	1    0    0    -1  
$EndComp
$Comp
L AudioBoard-rescue:+3.3V-Audio-Audio-rescue #PWR011
U 1 1 60FCAEB8
P 6350 4250
AR Path="/60FCAEB8" Ref="#PWR011"  Part="1" 
AR Path="/615A376B/61563857/60FCAEB8" Ref="#PWR011"  Part="1" 
F 0 "#PWR011" H 6350 4100 50  0001 C CNN
F 1 "+3.3V" H 6350 4390 50  0000 C CNN
F 2 "" H 6350 4250 60  0000 C CNN
F 3 "" H 6350 4250 60  0000 C CNN
	1    6350 4250
	1    0    0    -1  
$EndComp
$Comp
L AudioBoard-rescue:Conn_01x06-Audio-Audio-rescue J3
U 1 1 60FCAB15
P 5400 4650
F 0 "J3" H 5400 4950 50  0000 C CNN
F 1 "ICSP_AUDIO" H 5400 4250 50  0000 C CNN
F 2 "Connector_Molex:Molex_KK-254_AE-6410-06A_1x06_P2.54mm_Vertical" H 5400 4650 50  0001 C CNN
F 3 "" H 5400 4650 50  0001 C CNN
	1    5400 4650
	1    0    0    -1  
$EndComp
Text Label 5200 4450 2    60   ~ 0
~MCLR
Wire Wire Line
	5200 4650 4550 4650
Wire Wire Line
	4550 4650 4550 4700
Wire Wire Line
	5200 4550 4550 4550
Wire Wire Line
	4550 4550 4550 4500
$Comp
L AudioBoard-rescue:GND-Audio-Audio-rescue #PWR014
U 1 1 60FCAB16
P 4550 4700
F 0 "#PWR014" H 4550 4450 50  0001 C CNN
F 1 "GND" H 4550 4550 50  0000 C CNN
F 2 "" H 4550 4700 60  0000 C CNN
F 3 "" H 4550 4700 60  0000 C CNN
	1    4550 4700
	1    0    0    -1  
$EndComp
$Comp
L AudioBoard-rescue:+3.3V-Audio-Audio-rescue #PWR012
U 1 1 60FCACDA
P 4550 4500
AR Path="/60FCACDA" Ref="#PWR012"  Part="1" 
AR Path="/615A376B/61563857/60FCACDA" Ref="#PWR012"  Part="1" 
F 0 "#PWR012" H 4550 4350 50  0001 C CNN
F 1 "+3.3V" H 4550 4640 50  0000 C CNN
F 2 "" H 4550 4500 60  0000 C CNN
F 3 "" H 4550 4500 60  0000 C CNN
	1    4550 4500
	1    0    0    -1  
$EndComp
NoConn ~ 5200 4950
$Comp
L AudioBoard-rescue:Crystal_Small-Audio-Audio-rescue Y1
U 1 1 60FCACDB
P 2850 4500
F 0 "Y1" H 2850 4600 50  0000 C CNN
F 1 "10MHz" H 2850 4400 50  0000 C CNN
F 2 "Crystal:Crystal_HC49-U_Vertical" H 2850 4500 60  0001 C CNN
F 3 "" H 2850 4500 60  0000 C CNN
	1    2850 4500
	1    0    0    -1  
$EndComp
$Comp
L AudioBoard-rescue:Crystal_Small-Audio-Audio-rescue Y2
U 1 1 5BCCCCBA
P 3650 4500
F 0 "Y2" H 3650 4600 50  0000 C CNN
F 1 "12.288MHz" H 3650 4400 50  0000 C CNN
F 2 "Crystal:Crystal_HC49-U_Vertical" H 3650 4500 60  0001 C CNN
F 3 "" H 3650 4500 60  0000 C CNN
	1    3650 4500
	1    0    0    -1  
$EndComp
$Comp
L AudioBoard-rescue:C_Small-Audio-Audio-rescue C4
U 1 1 60FCAB19
P 2650 4700
F 0 "C4" H 2660 4770 50  0000 L CNN
F 1 "18p" H 2660 4620 50  0000 L CNN
F 2 "Capacitor_THT:C_Disc_D3.0mm_W1.6mm_P2.50mm" H 2650 4700 60  0001 C CNN
F 3 "" H 2650 4700 60  0000 C CNN
	1    2650 4700
	1    0    0    -1  
$EndComp
$Comp
L AudioBoard-rescue:C_Small-Audio-Audio-rescue C5
U 1 1 60FCACDD
P 3050 4700
F 0 "C5" H 3060 4770 50  0000 L CNN
F 1 "18p" H 3060 4620 50  0000 L CNN
F 2 "Capacitor_THT:C_Disc_D3.0mm_W1.6mm_P2.50mm" H 3050 4700 60  0001 C CNN
F 3 "" H 3050 4700 60  0000 C CNN
	1    3050 4700
	1    0    0    -1  
$EndComp
$Comp
L AudioBoard-rescue:C_Small-Audio-Audio-rescue C6
U 1 1 5BCCD117
P 3450 4700
F 0 "C6" H 3460 4770 50  0000 L CNN
F 1 "18p" H 3460 4620 50  0000 L CNN
F 2 "Capacitor_THT:C_Disc_D3.0mm_W1.6mm_P2.50mm" H 3450 4700 60  0001 C CNN
F 3 "" H 3450 4700 60  0000 C CNN
	1    3450 4700
	1    0    0    -1  
$EndComp
$Comp
L AudioBoard-rescue:C_Small-Audio-Audio-rescue C7
U 1 1 5BCCD1AB
P 3850 4700
F 0 "C7" H 3860 4770 50  0000 L CNN
F 1 "18p" H 3860 4620 50  0000 L CNN
F 2 "Capacitor_THT:C_Disc_D3.0mm_W1.6mm_P2.50mm" H 3850 4700 60  0001 C CNN
F 3 "" H 3850 4700 60  0000 C CNN
	1    3850 4700
	1    0    0    -1  
$EndComp
$Comp
L AudioBoard-rescue:GND-Audio-Audio-rescue #PWR015
U 1 1 60FCACDE
P 2650 4800
F 0 "#PWR015" H 2650 4550 50  0001 C CNN
F 1 "GND" H 2650 4650 50  0000 C CNN
F 2 "" H 2650 4800 60  0000 C CNN
F 3 "" H 2650 4800 60  0000 C CNN
	1    2650 4800
	1    0    0    -1  
$EndComp
$Comp
L AudioBoard-rescue:GND-Audio-Audio-rescue #PWR016
U 1 1 60FCACDF
P 3050 4800
F 0 "#PWR016" H 3050 4550 50  0001 C CNN
F 1 "GND" H 3050 4650 50  0000 C CNN
F 2 "" H 3050 4800 60  0000 C CNN
F 3 "" H 3050 4800 60  0000 C CNN
	1    3050 4800
	1    0    0    -1  
$EndComp
$Comp
L AudioBoard-rescue:GND-Audio-Audio-rescue #PWR017
U 1 1 5BCCD34C
P 3450 4800
F 0 "#PWR017" H 3450 4550 50  0001 C CNN
F 1 "GND" H 3450 4650 50  0000 C CNN
F 2 "" H 3450 4800 60  0000 C CNN
F 3 "" H 3450 4800 60  0000 C CNN
	1    3450 4800
	1    0    0    -1  
$EndComp
$Comp
L AudioBoard-rescue:GND-Audio-Audio-rescue #PWR018
U 1 1 5BCCD3D2
P 3850 4800
F 0 "#PWR018" H 3850 4550 50  0001 C CNN
F 1 "GND" H 3850 4650 50  0000 C CNN
F 2 "" H 3850 4800 60  0000 C CNN
F 3 "" H 3850 4800 60  0000 C CNN
	1    3850 4800
	1    0    0    -1  
$EndComp
Wire Wire Line
	2650 4350 2650 4500
Wire Wire Line
	2650 4500 2750 4500
Wire Wire Line
	2950 4500 3050 4500
Wire Wire Line
	3050 4350 3050 4500
Wire Wire Line
	3450 4350 3450 4500
Wire Wire Line
	3450 4500 3550 4500
Wire Wire Line
	3750 4500 3850 4500
Wire Wire Line
	3850 4350 3850 4500
Connection ~ 2650 4500
Connection ~ 3050 4500
Connection ~ 3450 4500
Connection ~ 3850 4500
Text Label 2650 4350 0    60   ~ 0
OSC1
Text Label 3050 4350 0    60   ~ 0
OSC2
Text Label 3450 4350 0    60   ~ 0
SOSCO
Text Label 3850 4350 0    60   ~ 0
SOSCI
Wire Wire Line
	6100 3000 6200 3000
Wire Wire Line
	6200 3000 6200 2950
Wire Wire Line
	6200 2950 6300 2950
Text HLabel 6300 2850 2    60   Input ~ 0
SDO0
$Comp
L AudioBoard-rescue:GND-Audio-Audio-rescue #PWR025
U 1 1 60FCAB24
P 7350 5200
F 0 "#PWR025" H 7350 4950 50  0001 C CNN
F 1 "GND" H 7350 5050 50  0000 C CNN
F 2 "" H 7350 5200 60  0000 C CNN
F 3 "" H 7350 5200 60  0000 C CNN
	1    7350 5200
	1    0    0    -1  
$EndComp
Wire Wire Line
	6200 4550 6350 4550
Text Label 7650 4700 2    60   ~ 0
MUX1
Text Label 7650 5300 2    60   ~ 0
~SS1
$Comp
L AudioBoard-rescue:+3.3V-Audio-Audio-rescue #PWR024
U 1 1 60FCAB25
P 7350 5100
AR Path="/60FCAB25" Ref="#PWR024"  Part="1" 
AR Path="/615A376B/61563857/60FCAB25" Ref="#PWR024"  Part="1" 
F 0 "#PWR024" H 7350 4950 50  0001 C CNN
F 1 "+3.3V" H 7350 5240 50  0000 C CNN
F 2 "" H 7350 5100 60  0000 C CNN
F 3 "" H 7350 5100 60  0000 C CNN
	1    7350 5100
	1    0    0    -1  
$EndComp
Wire Wire Line
	7350 5100 7650 5100
Wire Wire Line
	7350 5200 7650 5200
$Comp
L AudioBoard-rescue:+3.3V-Audio-Audio-rescue #PWR013
U 1 1 60FCAB1D
P 8250 4500
AR Path="/60FCAB1D" Ref="#PWR013"  Part="1" 
AR Path="/615A376B/61563857/60FCAB1D" Ref="#PWR013"  Part="1" 
F 0 "#PWR013" H 8250 4350 50  0001 C CNN
F 1 "+3.3V" H 8250 4640 50  0000 C CNN
F 2 "" H 8250 4500 60  0000 C CNN
F 3 "" H 8250 4500 60  0000 C CNN
	1    8250 4500
	1    0    0    -1  
$EndComp
$Comp
L AudioBoard-rescue:SW_Push-Audio-Audio-rescue SW1
U 1 1 61564D48
P 6000 4550
F 0 "SW1" H 6050 4650 50  0000 L CNN
F 1 "RESET" H 6000 4490 50  0000 C CNN
F 2 "Button_Switch_THT:SW_PUSH_6mm" H 6000 4750 50  0001 C CNN
F 3 "" H 6000 4750 50  0001 C CNN
	1    6000 4550
	1    0    0    -1  
$EndComp
$Comp
L AudioBoard-rescue:GND-Audio-Audio-rescue #PWR021
U 1 1 61564D49
P 5800 4950
F 0 "#PWR021" H 5800 4700 50  0001 C CNN
F 1 "GND" H 5800 4800 50  0000 C CNN
F 2 "" H 5800 4950 60  0000 C CNN
F 3 "" H 5800 4950 60  0000 C CNN
	1    5800 4950
	1    0    0    -1  
$EndComp
Wire Wire Line
	5800 4950 5800 4550
Wire Wire Line
	3250 3500 3250 3600
Wire Wire Line
	3250 3600 3250 3700
Wire Wire Line
	2950 2100 2950 2500
Wire Wire Line
	2650 1700 2650 2500
Wire Wire Line
	6350 4550 6350 4650
Wire Wire Line
	6350 4550 6500 4550
Wire Wire Line
	2650 4500 2650 4600
Wire Wire Line
	3050 4500 3050 4600
Wire Wire Line
	3450 4500 3450 4600
Wire Wire Line
	3850 4500 3850 4600
$Comp
L AudioBoard-rescue:74LS138-Audio-Audio-rescue U2
U 1 1 60FCACE9
P 8250 4950
F 0 "U2" H 8350 5450 60  0000 C CNN
F 1 "74HCT138" H 8400 4401 60  0000 C CNN
F 2 "Package_DIP:DIP-16_W7.62mm" H 8250 4950 60  0001 C CNN
F 3 "" H 8250 4950 60  0000 C CNN
	1    8250 4950
	1    0    0    -1  
$EndComp
$Comp
L AudioBoard-rescue:GND-Audio-Audio-rescue #PWR026
U 1 1 60FCAED8
P 8250 5400
F 0 "#PWR026" H 8250 5150 50  0001 C CNN
F 1 "GND" H 8250 5250 50  0000 C CNN
F 2 "" H 8250 5400 60  0000 C CNN
F 3 "" H 8250 5400 60  0000 C CNN
	1    8250 5400
	1    0    0    -1  
$EndComp
Wire Wire Line
	3500 3150 3250 3150
Wire Wire Line
	6100 2200 6200 2200
Wire Wire Line
	6200 2200 6200 2150
Wire Wire Line
	6200 2150 6300 2150
Wire Wire Line
	6100 2300 6200 2300
Wire Wire Line
	6200 2300 6200 2250
Wire Wire Line
	6200 2250 6300 2250
Wire Wire Line
	6100 2400 6200 2400
Wire Wire Line
	6200 2400 6200 2350
Wire Wire Line
	6200 2350 6300 2350
Text HLabel 6300 2350 2    50   Input ~ 0
CSCK
Text HLabel 6300 2250 2    50   Input ~ 0
COFS
Text HLabel 6300 2150 2    50   Input ~ 0
CSDO
Text HLabel 8850 4600 2    60   Input ~ 0
~SS10
Text HLabel 8850 4700 2    60   Input ~ 0
~SS11
Text HLabel 8850 4800 2    60   Input ~ 0
~SS12
Text HLabel 8850 4900 2    60   Input ~ 0
~SS13
Text HLabel 6300 3350 2    60   Input ~ 0
SCK1
Text HLabel 6300 3450 2    60   Input ~ 0
SDI1
Text HLabel 6300 3550 2    60   Input ~ 0
SDO1
NoConn ~ 5550 4750
$Comp
L AudioBoard-rescue:GND-Audio-Audio-rescue #PWR023
U 1 1 5BCF2FA3
P 9500 5000
F 0 "#PWR023" H 9500 4750 50  0001 C CNN
F 1 "GND" H 9500 4850 50  0000 C CNN
F 2 "" H 9500 5000 60  0000 C CNN
F 3 "" H 9500 5000 60  0000 C CNN
	1    9500 5000
	1    0    0    -1  
$EndComp
$Comp
L AudioBoard-rescue:+3.3V-Audio-Audio-rescue #PWR020
U 1 1 60FCACF3
P 9500 4800
AR Path="/60FCACF3" Ref="#PWR020"  Part="1" 
AR Path="/615A376B/61563857/60FCACF3" Ref="#PWR020"  Part="1" 
F 0 "#PWR020" H 9500 4650 50  0001 C CNN
F 1 "+3.3V" H 9500 4940 50  0000 C CNN
F 2 "" H 9500 4800 60  0000 C CNN
F 3 "" H 9500 4800 60  0000 C CNN
	1    9500 4800
	1    0    0    -1  
$EndComp
$Comp
L AudioBoard-rescue:C_Small-Audio-Audio-rescue C9
U 1 1 60FCAB21
P 9500 4900
F 0 "C9" H 9510 4970 50  0000 L CNN
F 1 "100n" H 9510 4820 50  0000 L CNN
F 2 "Capacitor_THT:C_Disc_D4.3mm_W1.9mm_P5.00mm" H 9500 4900 60  0001 C CNN
F 3 "" H 9500 4900 60  0000 C CNN
	1    9500 4900
	1    0    0    -1  
$EndComp
NoConn ~ -2300 2200
NoConn ~ 8850 5000
NoConn ~ 8850 5100
NoConn ~ 8850 5200
NoConn ~ 8850 5300
$Comp
L AudioBoard-rescue:GND-Audio-Audio-rescue #PWR019
U 1 1 60FD861C
P 7350 4800
F 0 "#PWR019" H 7350 4550 50  0001 C CNN
F 1 "GND" H 7350 4650 50  0000 C CNN
F 2 "" H 7350 4800 60  0000 C CNN
F 3 "" H 7350 4800 60  0000 C CNN
	1    7350 4800
	1    0    0    -1  
$EndComp
Wire Wire Line
	7350 4800 7650 4800
NoConn ~ 6100 2600
NoConn ~ 6100 1100
NoConn ~ 6100 1200
$Comp
L AudioBoard-rescue:+3.3V-Audio-Audio-rescue #PWR0138
U 1 1 615AF35B
P 2950 1600
AR Path="/615AF35B" Ref="#PWR0138"  Part="1" 
AR Path="/615A376B/61563857/615AF35B" Ref="#PWR0138"  Part="1" 
F 0 "#PWR0138" H 2950 1450 50  0001 C CNN
F 1 "+3.3V" H 2950 1740 50  0000 C CNN
F 2 "" H 2950 1600 60  0000 C CNN
F 3 "" H 2950 1600 60  0000 C CNN
	1    2950 1600
	1    0    0    -1  
$EndComp
Wire Wire Line
	6100 3400 6200 3400
Wire Wire Line
	6200 3400 6200 3350
Wire Wire Line
	6200 3350 6300 3350
Wire Wire Line
	6100 3500 6200 3500
Wire Wire Line
	6200 3500 6200 3450
Wire Wire Line
	6200 3450 6300 3450
Wire Wire Line
	6100 3600 6200 3600
Wire Wire Line
	6200 3600 6200 3550
Wire Wire Line
	6200 3550 6300 3550
$Comp
L AudioBoard-rescue:DSPIC33FJ128GP802-Audio-Audio-rescue U1
U 1 1 5BC83147
P 4800 2900
F 0 "U1" H 3650 4950 50  0000 L CNN
F 1 "DSPIC33FJ128GP802" H 3650 4850 50  0000 L CNN
F 2 "Package_DIP:DIP-28_W7.62mm" H 4825 4000 50  0000 C CIN
F 3 "" H 4100 2500 60  0000 C CNN
	1    4800 2900
	1    0    0    -1  
$EndComp
Text Label 6100 2100 0    50   ~ 0
PGED
Wire Wire Line
	6200 2200 6600 2200
Connection ~ 6200 2200
Text Label 6600 2200 0    50   ~ 0
PGEC
Text Label 5200 4850 2    50   ~ 0
PGEC
Text Label 5200 4750 2    50   ~ 0
PGED
Text Label 7650 4600 2    60   ~ 0
MUX0
Text Label 6100 3200 0    60   ~ 0
MUX0
Text Label 6100 3100 0    60   ~ 0
MUX1
$EndSCHEMATC
