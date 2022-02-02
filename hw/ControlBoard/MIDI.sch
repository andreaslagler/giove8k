EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 7 24
Title "MIDI"
Date "2021-07-20"
Rev "1.0"
Comp ""
Comment1 ""
Comment2 "see https://de.wikipedia.org/wiki/Musical_Instrument_Digital_Interface"
Comment3 ""
Comment4 "MIDI I/O circuit"
$EndDescr
Text HLabel 7550 2200 2    50   Input ~ 0
Rx
$Comp
L Device:C C10
U 1 1 60F984F0
P 3850 2550
F 0 "C10" H 3965 2596 50  0000 L CNN
F 1 "100n" H 3965 2505 50  0000 L CNN
F 2 "Capacitor_THT:C_Disc_D5.0mm_W2.5mm_P5.00mm" H 3888 2400 50  0001 C CNN
F 3 "~" H 3850 2550 50  0001 C CNN
	1    3850 2550
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR060
U 1 1 60F988A3
P 3850 2700
F 0 "#PWR060" H 3850 2450 50  0001 C CNN
F 1 "GND" H 3855 2527 50  0000 C CNN
F 2 "" H 3850 2700 50  0001 C CNN
F 3 "" H 3850 2700 50  0001 C CNN
	1    3850 2700
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR059
U 1 1 60F97C36
P 3850 2400
F 0 "#PWR059" H 3850 2250 50  0001 C CNN
F 1 "+5V" H 3865 2573 50  0000 C CNN
F 2 "" H 3850 2400 50  0001 C CNN
F 3 "" H 3850 2400 50  0001 C CNN
	1    3850 2400
	1    0    0    -1  
$EndComp
$Comp
L 74xx:74AHC04 U6
U 3 1 6101422D
P 6300 5050
F 0 "U6" H 6300 4733 50  0000 C CNN
F 1 "74AHC04" H 6300 4824 50  0000 C CNN
F 2 "Package_DIP:DIP-14_W7.62mm" H 6300 5050 50  0001 C CNN
F 3 "https://assets.nexperia.com/documents/data-sheet/74AHC_AHCT04.pdf" H 6300 5050 50  0001 C CNN
	3    6300 5050
	-1   0    0    1   
$EndComp
$Comp
L 74xx:74AHC04 U6
U 2 1 61014B76
P 6900 5050
F 0 "U6" H 6900 4733 50  0000 C CNN
F 1 "74AHC04" H 6900 4824 50  0000 C CNN
F 2 "Package_DIP:DIP-14_W7.62mm" H 6900 5050 50  0001 C CNN
F 3 "https://assets.nexperia.com/documents/data-sheet/74AHC_AHCT04.pdf" H 6900 5050 50  0001 C CNN
	2    6900 5050
	-1   0    0    1   
$EndComp
$Comp
L 74xx:74AHC04 U6
U 4 1 61015A4B
P 6300 3950
F 0 "U6" H 6300 3633 50  0000 C CNN
F 1 "74AHC04" H 6300 3724 50  0000 C CNN
F 2 "Package_DIP:DIP-14_W7.62mm" H 6300 3950 50  0001 C CNN
F 3 "https://assets.nexperia.com/documents/data-sheet/74AHC_AHCT04.pdf" H 6300 3950 50  0001 C CNN
	4    6300 3950
	-1   0    0    1   
$EndComp
$Comp
L 74xx:74AHC04 U6
U 5 1 61016FB7
P 6900 3950
F 0 "U6" H 6900 3633 50  0000 C CNN
F 1 "74AHC04" H 6900 3724 50  0000 C CNN
F 2 "Package_DIP:DIP-14_W7.62mm" H 6900 3950 50  0001 C CNN
F 3 "https://assets.nexperia.com/documents/data-sheet/74AHC_AHCT04.pdf" H 6900 3950 50  0001 C CNN
	5    6900 3950
	-1   0    0    1   
$EndComp
$Comp
L Device:R R8
U 1 1 61017B49
P 5600 5050
F 0 "R8" V 5393 5050 50  0000 C CNN
F 1 "220" V 5484 5050 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 5530 5050 50  0001 C CNN
F 3 "~" H 5600 5050 50  0001 C CNN
	1    5600 5050
	0    1    1    0   
$EndComp
$Comp
L Device:R R7
U 1 1 6101E120
P 5600 4750
F 0 "R7" V 5393 4750 50  0000 C CNN
F 1 "220" V 5484 4750 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 5530 4750 50  0001 C CNN
F 3 "~" H 5600 4750 50  0001 C CNN
	1    5600 4750
	0    1    1    0   
$EndComp
$Comp
L Device:R R6
U 1 1 6101E4A8
P 5600 3950
F 0 "R6" V 5393 3950 50  0000 C CNN
F 1 "220" V 5484 3950 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 5530 3950 50  0001 C CNN
F 3 "~" H 5600 3950 50  0001 C CNN
	1    5600 3950
	0    1    1    0   
$EndComp
$Comp
L Device:R R5
U 1 1 610207C1
P 5600 3650
F 0 "R5" V 5393 3650 50  0000 C CNN
F 1 "220" V 5484 3650 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 5530 3650 50  0001 C CNN
F 3 "~" H 5600 3650 50  0001 C CNN
	1    5600 3650
	0    1    1    0   
$EndComp
$Comp
L Device:D D1
U 1 1 6102A8DB
P 5900 2550
F 0 "D1" V 5854 2629 50  0000 L CNN
F 1 "D" V 5945 2629 50  0000 L CNN
F 2 "Diode_THT:D_A-405_P10.16mm_Horizontal" H 5900 2550 50  0001 C CNN
F 3 "~" H 5900 2550 50  0001 C CNN
	1    5900 2550
	0    1    1    0   
$EndComp
$Comp
L Device:R R3
U 1 1 6102C18C
P 7050 2200
F 0 "R3" V 7257 2200 50  0000 C CNN
F 1 "470" V 7166 2200 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 6980 2200 50  0001 C CNN
F 3 "~" H 7050 2200 50  0001 C CNN
	1    7050 2200
	0    -1   -1   0   
$EndComp
Wire Wire Line
	5200 2700 5900 2700
Wire Wire Line
	5750 2400 5900 2400
Wire Wire Line
	6800 2300 6800 2200
Wire Wire Line
	6800 2200 6900 2200
$Comp
L Device:R R4
U 1 1 6102BA27
P 7050 2800
F 0 "R4" V 7257 2800 50  0000 C CNN
F 1 "10k" V 7166 2800 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 6980 2800 50  0001 C CNN
F 3 "~" H 7050 2800 50  0001 C CNN
	1    7050 2800
	0    -1   -1   0   
$EndComp
Wire Wire Line
	6800 2400 7300 2400
Wire Wire Line
	7300 2400 7300 2800
Wire Wire Line
	7300 2800 7200 2800
Wire Wire Line
	6800 2700 6800 2800
Wire Wire Line
	6800 2800 6900 2800
$Comp
L power:GND #PWR061
U 1 1 61036E9A
P 6800 2800
F 0 "#PWR061" H 6800 2550 50  0001 C CNN
F 1 "GND" H 6805 2627 50  0000 C CNN
F 2 "" H 6800 2800 50  0001 C CNN
F 3 "" H 6800 2800 50  0001 C CNN
	1    6800 2800
	1    0    0    -1  
$EndComp
Connection ~ 6800 2800
$Comp
L power:+5V #PWR058
U 1 1 61037300
P 6800 2200
F 0 "#PWR058" H 6800 2050 50  0001 C CNN
F 1 "+5V" H 6815 2373 50  0000 C CNN
F 2 "" H 6800 2200 50  0001 C CNN
F 3 "" H 6800 2200 50  0001 C CNN
	1    6800 2200
	1    0    0    -1  
$EndComp
Connection ~ 6800 2200
$Comp
L 74xx:74AHC04 U6
U 7 1 61037B70
P 3850 3900
F 0 "U6" H 4080 3946 50  0000 L CNN
F 1 "74AHC04" H 4080 3855 50  0000 L CNN
F 2 "Package_DIP:DIP-14_W7.62mm" H 3850 3900 50  0001 C CNN
F 3 "https://assets.nexperia.com/documents/data-sheet/74AHC_AHCT04.pdf" H 3850 3900 50  0001 C CNN
	7    3850 3900
	1    0    0    -1  
$EndComp
Wire Wire Line
	7200 2200 7200 2600
Wire Wire Line
	7200 2600 6800 2600
Connection ~ 7200 2200
Wire Wire Line
	7200 3950 7400 3950
Wire Wire Line
	7400 3950 7400 2200
Wire Wire Line
	5200 3950 5450 3950
Wire Wire Line
	5750 3950 6000 3950
Wire Wire Line
	5200 3650 5450 3650
Wire Wire Line
	5750 3650 5900 3650
Wire Wire Line
	5900 3650 5900 3600
Wire Wire Line
	7200 5050 7550 5050
Wire Wire Line
	5750 5050 6000 5050
Wire Wire Line
	5200 5050 5450 5050
Wire Wire Line
	5200 4750 5450 4750
Wire Wire Line
	5750 4750 5900 4750
Wire Wire Line
	5900 4750 5900 4700
$Comp
L power:+5V #PWR062
U 1 1 610473C6
P 5900 3600
F 0 "#PWR062" H 5900 3450 50  0001 C CNN
F 1 "+5V" H 5915 3773 50  0000 C CNN
F 2 "" H 5900 3600 50  0001 C CNN
F 3 "" H 5900 3600 50  0001 C CNN
	1    5900 3600
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR065
U 1 1 6104794E
P 5900 4700
F 0 "#PWR065" H 5900 4550 50  0001 C CNN
F 1 "+5V" H 5915 4873 50  0000 C CNN
F 2 "" H 5900 4700 50  0001 C CNN
F 3 "" H 5900 4700 50  0001 C CNN
	1    5900 4700
	1    0    0    -1  
$EndComp
Text HLabel 7550 5050 2    50   Input ~ 0
Tx
$Comp
L power:GND #PWR064
U 1 1 61049686
P 3850 4400
F 0 "#PWR064" H 3850 4150 50  0001 C CNN
F 1 "GND" H 3855 4227 50  0000 C CNN
F 2 "" H 3850 4400 50  0001 C CNN
F 3 "" H 3850 4400 50  0001 C CNN
	1    3850 4400
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR063
U 1 1 61049A83
P 3850 3400
F 0 "#PWR063" H 3850 3250 50  0001 C CNN
F 1 "+5V" H 3865 3573 50  0000 C CNN
F 2 "" H 3850 3400 50  0001 C CNN
F 3 "" H 3850 3400 50  0001 C CNN
	1    3850 3400
	1    0    0    -1  
$EndComp
Wire Wire Line
	7200 2200 7400 2200
Connection ~ 7400 2200
Wire Wire Line
	7400 2200 7550 2200
$Comp
L Connector:Conn_01x02_Male J2
U 1 1 6103FF75
P 5000 2500
F 0 "J2" H 5108 2681 50  0000 C CNN
F 1 "MIDI In" H 5108 2590 50  0000 C CNN
F 2 "Connector_Molex:Molex_KK-254_AE-6410-02A_1x02_P2.54mm_Vertical" H 5000 2500 50  0001 C CNN
F 3 "~" H 5000 2500 50  0001 C CNN
	1    5000 2500
	1    0    0    -1  
$EndComp
$Comp
L Device:R R2
U 1 1 61025642
P 5600 2400
F 0 "R2" V 5393 2400 50  0000 C CNN
F 1 "220" V 5484 2400 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 5530 2400 50  0001 C CNN
F 3 "~" H 5600 2400 50  0001 C CNN
	1    5600 2400
	0    1    1    0   
$EndComp
$Comp
L Isolator:6N138 U5
U 1 1 61012A8A
P 6500 2500
F 0 "U5" H 6500 2967 50  0000 C CNN
F 1 "6N138" H 6500 2876 50  0000 C CNN
F 2 "Package_DIP:DIP-8_W7.62mm" H 6790 2200 50  0001 C CNN
F 3 "http://www.onsemi.com/pub/Collateral/HCPL2731-D.pdf" H 6790 2200 50  0001 C CNN
	1    6500 2500
	1    0    0    -1  
$EndComp
Wire Wire Line
	5200 2600 5200 2700
Wire Wire Line
	5200 2500 5200 2400
Wire Wire Line
	5200 2400 5450 2400
Wire Wire Line
	5900 2400 6200 2400
Connection ~ 5900 2400
Wire Wire Line
	6200 2600 6200 2700
Wire Wire Line
	6200 2700 5900 2700
Connection ~ 5900 2700
$Comp
L Connector:Conn_01x02_Male J3
U 1 1 6105318F
P 5000 3750
F 0 "J3" H 5108 3931 50  0000 C CNN
F 1 "MIDI Thru" H 5108 3840 50  0000 C CNN
F 2 "Connector_Molex:Molex_KK-254_AE-6410-02A_1x02_P2.54mm_Vertical" H 5000 3750 50  0001 C CNN
F 3 "~" H 5000 3750 50  0001 C CNN
	1    5000 3750
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x02_Male J4
U 1 1 610536E1
P 5000 4850
F 0 "J4" H 5108 5031 50  0000 C CNN
F 1 "MIDI Out" H 5108 4940 50  0000 C CNN
F 2 "Connector_Molex:Molex_KK-254_AE-6410-02A_1x02_P2.54mm_Vertical" H 5000 4850 50  0001 C CNN
F 3 "~" H 5000 4850 50  0001 C CNN
	1    5000 4850
	1    0    0    -1  
$EndComp
Wire Wire Line
	5200 4850 5200 4750
Wire Wire Line
	5200 4950 5200 5050
Wire Wire Line
	5200 3750 5200 3650
Wire Wire Line
	5200 3850 5200 3950
$EndSCHEMATC