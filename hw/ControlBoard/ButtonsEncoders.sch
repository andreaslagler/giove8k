EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 6 24
Title "Buttons / Encoders"
Date "2021-07-20"
Rev "1.0"
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 "Push buttons / encoders on 16 Bit serial I/O expander"
$EndDescr
$Comp
L Interface_Expansion:MCP23S17_SP U4
U 1 1 60F49767
P 3350 3150
F 0 "U4" H 3350 4431 50  0000 C CNN
F 1 "MCP23S17_SP" H 3350 4340 50  0000 C CNN
F 2 "Package_DIP:DIP-28_W7.62mm" H 3550 2150 50  0001 L CNN
F 3 "http://ww1.microchip.com/downloads/en/DeviceDoc/20001952C.pdf" H 3550 2050 50  0001 L CNN
	1    3350 3150
	1    0    0    -1  
$EndComp
Text HLabel 2650 2350 0    50   Input ~ 0
~SS
Text HLabel 2650 2450 0    50   Input ~ 0
SCK
Text HLabel 2650 2550 0    50   Input ~ 0
SDI
Text HLabel 2650 2650 0    50   Input ~ 0
SDO
Text HLabel 2650 3050 0    50   Input ~ 0
INT
$Comp
L power:GND #PWR050
U 1 1 60F8EC88
P 2300 4450
F 0 "#PWR050" H 2300 4200 50  0001 C CNN
F 1 "GND" H 2305 4277 50  0000 C CNN
F 2 "" H 2300 4450 50  0001 C CNN
F 3 "" H 2300 4450 50  0001 C CNN
	1    2300 4450
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR051
U 1 1 60F8EC89
P 3350 4450
F 0 "#PWR051" H 3350 4200 50  0001 C CNN
F 1 "GND" H 3355 4277 50  0000 C CNN
F 2 "" H 3350 4450 50  0001 C CNN
F 3 "" H 3350 4450 50  0001 C CNN
	1    3350 4450
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR041
U 1 1 60FBB43C
P 3350 2050
F 0 "#PWR041" H 3350 1900 50  0001 C CNN
F 1 "+5V" H 3365 2223 50  0000 C CNN
F 2 "" H 3350 2050 50  0001 C CNN
F 3 "" H 3350 2050 50  0001 C CNN
	1    3350 2050
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR044
U 1 1 60F8EC8B
P 2300 3250
F 0 "#PWR044" H 2300 3100 50  0001 C CNN
F 1 "+5V" H 2315 3423 50  0000 C CNN
F 2 "" H 2300 3250 50  0001 C CNN
F 3 "" H 2300 3250 50  0001 C CNN
	1    2300 3250
	1    0    0    -1  
$EndComp
Wire Wire Line
	2300 3250 2650 3250
Wire Wire Line
	2650 3950 2300 3950
Wire Wire Line
	2300 3950 2300 4450
Wire Wire Line
	2650 3850 2300 3850
Wire Wire Line
	2300 3850 2300 3950
Connection ~ 2300 3950
Wire Wire Line
	2650 3750 2300 3750
Wire Wire Line
	2300 3750 2300 3850
Connection ~ 2300 3850
$Comp
L Device:C C9
U 1 1 60F97C34
P 1300 3100
F 0 "C9" H 1415 3146 50  0000 L CNN
F 1 "100n" H 1415 3055 50  0000 L CNN
F 2 "Capacitor_THT:C_Disc_D5.0mm_W2.5mm_P5.00mm" H 1338 2950 50  0001 C CNN
F 3 "~" H 1300 3100 50  0001 C CNN
	1    1300 3100
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR043
U 1 1 60F97C35
P 1300 3250
F 0 "#PWR043" H 1300 3000 50  0001 C CNN
F 1 "GND" H 1305 3077 50  0000 C CNN
F 2 "" H 1300 3250 50  0001 C CNN
F 3 "" H 1300 3250 50  0001 C CNN
	1    1300 3250
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR042
U 1 1 60F8EC8E
P 1300 2950
F 0 "#PWR042" H 1300 2800 50  0001 C CNN
F 1 "+5V" H 1315 3123 50  0000 C CNN
F 2 "" H 1300 2950 50  0001 C CNN
F 3 "" H 1300 2950 50  0001 C CNN
	1    1300 2950
	1    0    0    -1  
$EndComp
NoConn ~ 2650 2950
$Comp
L Switch:SW_Push SW21
U 1 1 60F7CEC7
P 9500 4250
F 0 "SW21" H 9500 4065 50  0000 C CNN
F 1 "SW_Push" H 9500 4156 50  0000 C CNN
F 2 "Button_Switch_THT:SW_PUSH-12mm" H 9500 4450 50  0001 C CNN
F 3 "~" H 9500 4450 50  0001 C CNN
	1    9500 4250
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR055
U 1 1 60F7CEDB
P 9500 4450
F 0 "#PWR055" H 9500 4200 50  0001 C CNN
F 1 "GND" H 9505 4277 50  0000 C CNN
F 2 "" H 9500 4450 50  0001 C CNN
F 3 "" H 9500 4450 50  0001 C CNN
	1    9500 4450
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_Push SW22
U 1 1 60F7CEE5
P 9900 4250
F 0 "SW22" H 9900 4065 50  0000 C CNN
F 1 "SW_Push" H 9900 4156 50  0000 C CNN
F 2 "Button_Switch_THT:SW_PUSH-12mm" H 9900 4450 50  0001 C CNN
F 3 "~" H 9900 4450 50  0001 C CNN
	1    9900 4250
	0    -1   -1   0   
$EndComp
$Comp
L Switch:SW_Push SW23
U 1 1 60F7CEEF
P 10300 4250
F 0 "SW23" H 10300 4065 50  0000 C CNN
F 1 "SW_Push" H 10300 4156 50  0000 C CNN
F 2 "Button_Switch_THT:SW_PUSH-12mm" H 10300 4450 50  0001 C CNN
F 3 "~" H 10300 4450 50  0001 C CNN
	1    10300 4250
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR056
U 1 1 60F7CEF9
P 9900 4450
F 0 "#PWR056" H 9900 4200 50  0001 C CNN
F 1 "GND" H 9905 4277 50  0000 C CNN
F 2 "" H 9900 4450 50  0001 C CNN
F 3 "" H 9900 4450 50  0001 C CNN
	1    9900 4450
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR057
U 1 1 60F7CF03
P 10300 4450
F 0 "#PWR057" H 10300 4200 50  0001 C CNN
F 1 "GND" H 10305 4277 50  0000 C CNN
F 2 "" H 10300 4450 50  0001 C CNN
F 3 "" H 10300 4450 50  0001 C CNN
	1    10300 4450
	1    0    0    -1  
$EndComp
Wire Wire Line
	4050 2550 9500 2550
Wire Wire Line
	9500 2550 9500 4050
Wire Wire Line
	4050 2450 9900 2450
Wire Wire Line
	9900 2450 9900 4050
Wire Wire Line
	4050 2350 10300 2350
Wire Wire Line
	10300 2350 10300 4050
Wire Wire Line
	3350 4250 3350 4450
Wire Wire Line
	4050 3950 4150 3950
Wire Wire Line
	4150 3950 4150 4050
Wire Wire Line
	4050 3750 4950 3750
Wire Wire Line
	4950 3750 4950 4050
Wire Wire Line
	4050 3550 5900 3550
Wire Wire Line
	5900 3550 5900 4050
Wire Wire Line
	4050 3250 7100 3250
Wire Wire Line
	4050 3050 7500 3050
$Comp
L Switch:SW_Push SW27
U 1 1 611A9A10
P 5900 4250
F 0 "SW27" H 5900 4065 50  0000 C CNN
F 1 "SW_Push" H 5900 4156 50  0000 C CNN
F 2 "Button_Switch_THT:SW_PUSH-12mm" H 5900 4450 50  0001 C CNN
F 3 "~" H 5900 4450 50  0001 C CNN
	1    5900 4250
	0    -1   -1   0   
$EndComp
$Comp
L Switch:SW_Push SW28
U 1 1 611A9A16
P 6300 4250
F 0 "SW28" H 6300 4065 50  0000 C CNN
F 1 "SW_Push" H 6300 4156 50  0000 C CNN
F 2 "Button_Switch_THT:SW_PUSH-12mm" H 6300 4450 50  0001 C CNN
F 3 "~" H 6300 4450 50  0001 C CNN
	1    6300 4250
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR048
U 1 1 611A9A1C
P 5900 4450
F 0 "#PWR048" H 5900 4200 50  0001 C CNN
F 1 "GND" H 5905 4277 50  0000 C CNN
F 2 "" H 5900 4450 50  0001 C CNN
F 3 "" H 5900 4450 50  0001 C CNN
	1    5900 4450
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR049
U 1 1 611A9A22
P 6300 4450
F 0 "#PWR049" H 6300 4200 50  0001 C CNN
F 1 "GND" H 6305 4277 50  0000 C CNN
F 2 "" H 6300 4450 50  0001 C CNN
F 3 "" H 6300 4450 50  0001 C CNN
	1    6300 4450
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_Push SW29
U 1 1 611A9A28
P 6700 4250
F 0 "SW29" H 6700 4065 50  0000 C CNN
F 1 "SW_Push" H 6700 4156 50  0000 C CNN
F 2 "Button_Switch_THT:SW_PUSH-12mm" H 6700 4450 50  0001 C CNN
F 3 "~" H 6700 4450 50  0001 C CNN
	1    6700 4250
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR0299
U 1 1 611A9A34
P 6700 4450
F 0 "#PWR0299" H 6700 4200 50  0001 C CNN
F 1 "GND" H 6705 4277 50  0000 C CNN
F 2 "" H 6700 4450 50  0001 C CNN
F 3 "" H 6700 4450 50  0001 C CNN
	1    6700 4450
	1    0    0    -1  
$EndComp
Wire Wire Line
	7100 4050 7100 3250
Wire Wire Line
	7500 4050 7500 3050
Wire Wire Line
	4350 3850 4350 4050
Wire Wire Line
	4050 3850 4350 3850
$Comp
L Device:Rotary_Encoder SW24
U 1 1 60FB4BF2
P 5050 4350
F 0 "SW24" V 4947 4580 50  0000 L CNN
F 1 "RotEnc" V 5038 4580 50  0000 L CNN
F 2 "Rotary_Encoder:RotaryEncoder_Alps_EC12E_Vertical_H20mm_CircularMountingHoles" H 4900 4510 50  0001 C CNN
F 3 "~" H 5050 4610 50  0001 C CNN
	1    5050 4350
	0    1    1    0   
$EndComp
Wire Wire Line
	5050 3950 5450 3950
Wire Wire Line
	5050 4050 5050 3950
Wire Wire Line
	5150 3650 5150 4050
Wire Wire Line
	4050 3650 5150 3650
Wire Wire Line
	6300 3450 6300 4050
Wire Wire Line
	4050 3450 6300 3450
$Comp
L Device:Rotary_Encoder SW25
U 1 1 60FBE70C
P 8900 4350
F 0 "SW25" V 8797 4580 50  0000 L CNN
F 1 "RotEnc" V 8888 4580 50  0000 L CNN
F 2 "Rotary_Encoder:RotaryEncoder_Alps_EC12E_Vertical_H20mm_CircularMountingHoles" H 8750 4510 50  0001 C CNN
F 3 "~" H 8900 4610 50  0001 C CNN
	1    8900 4350
	0    1    1    0   
$EndComp
Wire Wire Line
	8800 2750 8800 4050
Wire Wire Line
	4050 2750 8800 2750
Wire Wire Line
	9000 2650 9000 4050
Wire Wire Line
	4050 2650 9000 2650
Wire Wire Line
	8900 3950 9300 3950
Wire Wire Line
	8900 4050 8900 3950
$Comp
L power:GND #PWR0302
U 1 1 611F476A
P 9300 3950
F 0 "#PWR0302" H 9300 3700 50  0001 C CNN
F 1 "GND" H 9305 3777 50  0000 C CNN
F 2 "" H 9300 3950 50  0001 C CNN
F 3 "" H 9300 3950 50  0001 C CNN
	1    9300 3950
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_Push SW18
U 1 1 60F8EC8F
P 7500 4250
F 0 "SW18" H 7500 4065 50  0000 C CNN
F 1 "SW_Push" H 7500 4156 50  0000 C CNN
F 2 "Button_Switch_THT:SW_PUSH-12mm" H 7500 4450 50  0001 C CNN
F 3 "~" H 7500 4450 50  0001 C CNN
	1    7500 4250
	0    -1   -1   0   
$EndComp
$Comp
L Switch:SW_Push SW19
U 1 1 60F7CE9F
P 7900 4250
F 0 "SW19" H 7900 4065 50  0000 C CNN
F 1 "SW_Push" H 7900 4156 50  0000 C CNN
F 2 "Button_Switch_THT:SW_PUSH-12mm" H 7900 4450 50  0001 C CNN
F 3 "~" H 7900 4450 50  0001 C CNN
	1    7900 4250
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR052
U 1 1 60F7CEA9
P 7500 4450
F 0 "#PWR052" H 7500 4200 50  0001 C CNN
F 1 "GND" H 7505 4277 50  0000 C CNN
F 2 "" H 7500 4450 50  0001 C CNN
F 3 "" H 7500 4450 50  0001 C CNN
	1    7500 4450
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR053
U 1 1 60F7CEB3
P 7900 4450
F 0 "#PWR053" H 7900 4200 50  0001 C CNN
F 1 "GND" H 7905 4277 50  0000 C CNN
F 2 "" H 7900 4450 50  0001 C CNN
F 3 "" H 7900 4450 50  0001 C CNN
	1    7900 4450
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_Push SW20
U 1 1 60F8EC93
P 8300 4250
F 0 "SW20" H 8300 4065 50  0000 C CNN
F 1 "SW_Push" H 8300 4156 50  0000 C CNN
F 2 "Button_Switch_THT:SW_PUSH-12mm" H 8300 4450 50  0001 C CNN
F 3 "~" H 8300 4450 50  0001 C CNN
	1    8300 4250
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR054
U 1 1 60F7CED1
P 8300 4450
F 0 "#PWR054" H 8300 4200 50  0001 C CNN
F 1 "GND" H 8305 4277 50  0000 C CNN
F 2 "" H 8300 4450 50  0001 C CNN
F 3 "" H 8300 4450 50  0001 C CNN
	1    8300 4450
	1    0    0    -1  
$EndComp
Wire Wire Line
	7900 4050 7900 2950
Wire Wire Line
	4050 2950 7900 2950
Wire Wire Line
	8300 2850 8300 4050
Wire Wire Line
	4050 2850 8300 2850
$Comp
L Switch:SW_Push SW30
U 1 1 611A9A2E
P 7100 4250
F 0 "SW30" H 7100 4065 50  0000 C CNN
F 1 "SW_Push" H 7100 4156 50  0000 C CNN
F 2 "Button_Switch_THT:SW_PUSH-12mm" H 7100 4450 50  0001 C CNN
F 3 "~" H 7100 4450 50  0001 C CNN
	1    7100 4250
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR0300
U 1 1 611A9A3A
P 7100 4450
F 0 "#PWR0300" H 7100 4200 50  0001 C CNN
F 1 "GND" H 7105 4277 50  0000 C CNN
F 2 "" H 7100 4450 50  0001 C CNN
F 3 "" H 7100 4450 50  0001 C CNN
	1    7100 4450
	1    0    0    -1  
$EndComp
Wire Wire Line
	4050 3350 6700 3350
Wire Wire Line
	6700 3350 6700 4050
$Comp
L power:GND #PWR047
U 1 1 60FC8B8C
P 5450 3950
F 0 "#PWR047" H 5450 3700 50  0001 C CNN
F 1 "GND" H 5455 3777 50  0000 C CNN
F 2 "" H 5450 3950 50  0001 C CNN
F 3 "" H 5450 3950 50  0001 C CNN
	1    5450 3950
	1    0    0    -1  
$EndComp
Wire Wire Line
	4250 4050 4250 3950
Wire Wire Line
	4250 3950 4650 3950
$Comp
L power:GND #PWR0301
U 1 1 611F3AE1
P 4650 3950
F 0 "#PWR0301" H 4650 3700 50  0001 C CNN
F 1 "GND" H 4655 3777 50  0000 C CNN
F 2 "" H 4650 3950 50  0001 C CNN
F 3 "" H 4650 3950 50  0001 C CNN
	1    4650 3950
	1    0    0    -1  
$EndComp
$Comp
L Device:Rotary_Encoder SW26
U 1 1 60FBEE24
P 4250 4350
F 0 "SW26" V 4147 4580 50  0000 L CNN
F 1 "RotEnc" V 4238 4580 50  0000 L CNN
F 2 "Rotary_Encoder:RotaryEncoder_Alps_EC12E_Vertical_H20mm_CircularMountingHoles" H 4100 4510 50  0001 C CNN
F 3 "~" H 4250 4610 50  0001 C CNN
	1    4250 4350
	0    1    1    0   
$EndComp
$EndSCHEMATC