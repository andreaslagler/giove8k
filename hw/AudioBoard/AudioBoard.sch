EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 9
Title "Synth"
Date "2021-07-25"
Rev "1.0"
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 "Top-Level block diagram"
$EndDescr
$Comp
L Connector:Conn_01x04_Male J1
U 1 1 610E46C6
P 6450 4950
F 0 "J1" H 6422 4832 50  0000 R CNN
F 1 "Conn_01x04_Male" H 6422 4923 50  0000 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x04_P2.54mm_Vertical" H 6450 4950 50  0001 C CNN
F 3 "~" H 6450 4950 50  0001 C CNN
	1    6450 4950
	-1   0    0    1   
$EndComp
Wire Wire Line
	5350 4950 6250 4950
Wire Wire Line
	5350 5050 6250 5050
Wire Wire Line
	6250 4750 6250 4450
Wire Wire Line
	6250 4850 6150 4850
Wire Wire Line
	6150 4850 6150 4550
Wire Wire Line
	6150 4550 6050 4550
$Comp
L power:GNDA #PWR02
U 1 1 610E61D9
P 6050 4550
F 0 "#PWR02" H 6050 4300 50  0001 C CNN
F 1 "GNDA" H 6055 4377 50  0000 C CNN
F 2 "" H 6050 4550 50  0001 C CNN
F 3 "" H 6050 4550 50  0001 C CNN
	1    6050 4550
	1    0    0    -1  
$EndComp
Wire Wire Line
	6250 4450 6050 4450
$Comp
L power:+5VA #PWR01
U 1 1 610E6CDD
P 6050 4450
F 0 "#PWR01" H 6050 4300 50  0001 C CNN
F 1 "+5VA" H 6065 4623 50  0000 C CNN
F 2 "" H 6050 4450 50  0001 C CNN
F 3 "" H 6050 4450 50  0001 C CNN
	1    6050 4450
	1    0    0    -1  
$EndComp
$Sheet
S 4750 4850 600  500 
U 615A376B
F0 "Audio" 50
F1 "Audio.sch" 50
F2 "OUT_L" I R 5350 4950 50 
F3 "OUT_R" I R 5350 5050 50 
F4 "SCK" I L 4750 4950 50 
F5 "SDI" I L 4750 5050 50 
F6 "SDO" I L 4750 5150 50 
F7 "~SS" I L 4750 5250 50 
$EndSheet
Wire Wire Line
	4750 5050 3400 5050
Wire Wire Line
	4750 5150 3400 5150
Wire Wire Line
	4750 5250 3400 5250
$Comp
L Connector:Conn_01x06_Male J2
U 1 1 615A695A
P 3200 5150
F 0 "J2" H 3172 5032 50  0000 R CNN
F 1 "Conn_01x06_Male" H 3172 5123 50  0000 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x06_P2.54mm_Vertical" H 3200 5150 50  0001 C CNN
F 3 "~" H 3200 5150 50  0001 C CNN
	1    3200 5150
	1    0    0    1   
$EndComp
$Comp
L power:+6V #PWR03
U 1 1 615A6964
P 3400 4850
F 0 "#PWR03" H 3400 4700 50  0001 C CNN
F 1 "+6V" H 3415 5023 50  0000 C CNN
F 2 "" H 3400 4850 50  0001 C CNN
F 3 "" H 3400 4850 50  0001 C CNN
	1    3400 4850
	-1   0    0    -1  
$EndComp
$Comp
L power:GND #PWR04
U 1 1 615A696E
P 3400 5350
F 0 "#PWR04" H 3400 5100 50  0001 C CNN
F 1 "GND" H 3405 5177 50  0000 C CNN
F 2 "" H 3400 5350 50  0001 C CNN
F 3 "" H 3400 5350 50  0001 C CNN
	1    3400 5350
	-1   0    0    -1  
$EndComp
Wire Wire Line
	4750 4950 3400 4950
$Sheet
S 4850 2600 500  150 
U 610B13E5
F0 "Power" 50
F1 "PowerAudio.sch" 50
$EndSheet
$Comp
L power:PWR_FLAG #FLG?
U 1 1 6169DB7B
P 7150 2950
AR Path="/610B13E5/6169DB7B" Ref="#FLG?"  Part="1" 
AR Path="/6169DB7B" Ref="#FLG0101"  Part="1" 
F 0 "#FLG0101" H 7150 3025 50  0001 C CNN
F 1 "PWR_FLAG" H 7150 3123 50  0000 C CNN
F 2 "" H 7150 2950 50  0001 C CNN
F 3 "~" H 7150 2950 50  0001 C CNN
	1    7150 2950
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 6169DB87
P 7150 2950
AR Path="/610B13E5/6169DB87" Ref="#PWR?"  Part="1" 
AR Path="/6169DB87" Ref="#PWR0124"  Part="1" 
F 0 "#PWR0124" H 7150 2700 50  0001 C CNN
F 1 "GND" H 7155 2777 50  0000 C CNN
F 2 "" H 7150 2950 50  0001 C CNN
F 3 "" H 7150 2950 50  0001 C CNN
	1    7150 2950
	1    0    0    -1  
$EndComp
$Comp
L power:PWR_FLAG #FLG?
U 1 1 6169DBAB
P 6400 2950
AR Path="/610B13E5/6169DBAB" Ref="#FLG?"  Part="1" 
AR Path="/6169DBAB" Ref="#FLG0105"  Part="1" 
F 0 "#FLG0105" H 6400 3025 50  0001 C CNN
F 1 "PWR_FLAG" H 6400 3123 50  0000 C CNN
F 2 "" H 6400 2950 50  0001 C CNN
F 3 "~" H 6400 2950 50  0001 C CNN
	1    6400 2950
	-1   0    0    1   
$EndComp
$Comp
L power:+6V #PWR?
U 1 1 6169DBB1
P 6400 2950
AR Path="/610B13E5/6169DBB1" Ref="#PWR?"  Part="1" 
AR Path="/6169DBB1" Ref="#PWR0139"  Part="1" 
F 0 "#PWR0139" H 6400 2800 50  0001 C CNN
F 1 "+6V" H 6415 3123 50  0000 C CNN
F 2 "" H 6400 2950 50  0001 C CNN
F 3 "" H 6400 2950 50  0001 C CNN
	1    6400 2950
	1    0    0    -1  
$EndComp
$EndSCHEMATC
