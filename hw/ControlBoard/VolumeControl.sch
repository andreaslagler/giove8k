EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 24 24
Title "Volume Control"
Date "2021-08-02"
Rev "1.0"
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 "Volume Control with output buffers"
$EndDescr
Wire Wire Line
	7350 2400 7350 2550
$Comp
L ControlBoard-rescue:CP_Small-Audio-DAC-rescue C26
U 1 1 5BCA9140
P 8150 2300
F 0 "C26" H 8160 2370 50  0000 L CNN
F 1 "10u" H 8160 2220 50  0000 L CNN
F 2 "Capacitor_THT:CP_Radial_D5.0mm_P2.50mm" H 8150 2300 60  0001 C CNN
F 3 "" H 8150 2300 60  0000 C CNN
	1    8150 2300
	0    -1   -1   0   
$EndComp
$Comp
L Device:R_POT_Dual_Separate RV39
U 2 1 60329D1B
P 7050 2550
F 0 "RV39" H 6981 2504 50  0000 R CNN
F 1 "22kA" H 6981 2595 50  0000 R CNN
F 2 "Potentiometer_THT:Potentiometer_Alpha_RD902F-40-00D_Dual_Vertical_CircularHoles" H 7050 2550 50  0001 C CNN
F 3 "~" H 7050 2550 50  0001 C CNN
	2    7050 2550
	1    0    0    1   
$EndComp
$Comp
L Device:R_POT_Dual_Separate RV39
U 1 1 6032A294
P 7050 4250
F 0 "RV39" H 6980 4204 50  0000 R CNN
F 1 "22kA" H 6980 4295 50  0000 R CNN
F 2 "Potentiometer_THT:Potentiometer_Alpha_RD902F-40-00D_Dual_Vertical_CircularHoles" H 7050 4250 50  0001 C CNN
F 3 "~" H 7050 4250 50  0001 C CNN
	1    7050 4250
	1    0    0    1   
$EndComp
$Comp
L ControlBoard-rescue:R_Small-Audio-DAC-rescue R60
U 1 1 6036A858
P 8400 2300
F 0 "R60" H 8430 2320 50  0000 L CNN
F 1 "100" H 8430 2260 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" H 8400 2300 60  0001 C CNN
F 3 "" H 8400 2300 60  0000 C CNN
	1    8400 2300
	0    1    1    0   
$EndComp
Wire Wire Line
	7950 2300 7950 2550
Wire Wire Line
	7350 2200 7250 2200
Wire Wire Line
	7250 2200 7250 2550
Wire Wire Line
	7250 2550 7200 2550
Wire Wire Line
	7050 2700 7050 2750
Wire Wire Line
	7950 2300 8050 2300
Wire Wire Line
	8250 2300 8300 2300
Wire Wire Line
	8500 2300 8550 2300
Wire Wire Line
	7350 4100 7350 4250
$Comp
L ControlBoard-rescue:CP_Small-Audio-DAC-rescue C27
U 1 1 6098C714
P 8150 4000
F 0 "C27" H 8160 4070 50  0000 L CNN
F 1 "10u" H 8160 3920 50  0000 L CNN
F 2 "Capacitor_THT:CP_Radial_D5.0mm_P2.50mm" H 8150 4000 60  0001 C CNN
F 3 "" H 8150 4000 60  0000 C CNN
	1    8150 4000
	0    -1   -1   0   
$EndComp
$Comp
L ControlBoard-rescue:R_Small-Audio-DAC-rescue R63
U 1 1 6098C742
P 8400 4000
F 0 "R63" H 8430 4020 50  0000 L CNN
F 1 "100" H 8430 3960 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" H 8400 4000 60  0001 C CNN
F 3 "" H 8400 4000 60  0000 C CNN
	1    8400 4000
	0    1    1    0   
$EndComp
Wire Wire Line
	7950 4000 7950 4250
Wire Wire Line
	7350 3900 7250 3900
Wire Wire Line
	7250 3900 7250 4250
Wire Wire Line
	7250 4250 7200 4250
Wire Wire Line
	7050 4400 7050 4450
Wire Wire Line
	7950 4000 8050 4000
Wire Wire Line
	8250 4000 8300 4000
Wire Wire Line
	8500 4000 8550 4000
$Comp
L Connector:Conn_01x02_Male J8
U 1 1 60FEDE6D
P 8750 2400
F 0 "J8" H 8722 2282 50  0000 R CNN
F 1 "Conn_01x02_Male" H 8722 2373 50  0000 R CNN
F 2 "Connector_Molex:Molex_KK-254_AE-6410-02A_1x02_P2.54mm_Vertical" H 8750 2400 50  0001 C CNN
F 3 "~" H 8750 2400 50  0001 C CNN
	1    8750 2400
	-1   0    0    1   
$EndComp
Wire Wire Line
	8550 2400 8550 2750
$Comp
L Connector:Conn_01x02_Male J9
U 1 1 60FF3D71
P 8750 4100
F 0 "J9" H 8722 3982 50  0000 R CNN
F 1 "Conn_01x02_Male" H 8722 4073 50  0000 R CNN
F 2 "Connector_Molex:Molex_KK-254_AE-6410-02A_1x02_P2.54mm_Vertical" H 8750 4100 50  0001 C CNN
F 3 "~" H 8750 4100 50  0001 C CNN
	1    8750 4100
	-1   0    0    1   
$EndComp
Wire Wire Line
	8550 4100 8550 4450
$Comp
L power:+5VA #PWR0291
U 1 1 610AD36E
P 5000 2950
F 0 "#PWR0291" H 5000 2800 50  0001 C CNN
F 1 "+5VA" H 5015 3123 50  0000 C CNN
F 2 "" H 5000 2950 50  0001 C CNN
F 3 "" H 5000 2950 50  0001 C CNN
	1    5000 2950
	1    0    0    -1  
$EndComp
$Comp
L power:GNDA #PWR0292
U 1 1 610B2700
P 7050 2750
F 0 "#PWR0292" H 7050 2500 50  0001 C CNN
F 1 "GNDA" H 7055 2577 50  0000 C CNN
F 2 "" H 7050 2750 50  0001 C CNN
F 3 "" H 7050 2750 50  0001 C CNN
	1    7050 2750
	1    0    0    -1  
$EndComp
Text HLabel 6100 2400 0    50   Input ~ 0
AudioL
Text HLabel 6050 4100 0    50   Input ~ 0
AudioR
$Comp
L power:GNDA #PWR0293
U 1 1 610B6317
P 5000 3550
F 0 "#PWR0293" H 5000 3300 50  0001 C CNN
F 1 "GNDA" H 5005 3377 50  0000 C CNN
F 2 "" H 5000 3550 50  0001 C CNN
F 3 "" H 5000 3550 50  0001 C CNN
	1    5000 3550
	1    0    0    -1  
$EndComp
$Comp
L power:GNDA #PWR0294
U 1 1 610B6586
P 8550 2750
F 0 "#PWR0294" H 8550 2500 50  0001 C CNN
F 1 "GNDA" H 8555 2577 50  0000 C CNN
F 2 "" H 8550 2750 50  0001 C CNN
F 3 "" H 8550 2750 50  0001 C CNN
	1    8550 2750
	1    0    0    -1  
$EndComp
$Comp
L power:GNDA #PWR0295
U 1 1 610B6D65
P 7050 4450
F 0 "#PWR0295" H 7050 4200 50  0001 C CNN
F 1 "GNDA" H 7055 4277 50  0000 C CNN
F 2 "" H 7050 4450 50  0001 C CNN
F 3 "" H 7050 4450 50  0001 C CNN
	1    7050 4450
	1    0    0    -1  
$EndComp
$Comp
L power:GNDA #PWR0296
U 1 1 610B701F
P 8550 4450
F 0 "#PWR0296" H 8550 4200 50  0001 C CNN
F 1 "GNDA" H 8555 4277 50  0000 C CNN
F 2 "" H 8550 4450 50  0001 C CNN
F 3 "" H 8550 4450 50  0001 C CNN
	1    8550 4450
	1    0    0    -1  
$EndComp
$Comp
L Amplifier_Operational:MCP6002-xP U21
U 1 1 610BAF63
P 7650 2300
F 0 "U21" H 7650 2667 50  0000 C CNN
F 1 "MCP6002-xP" H 7650 2576 50  0000 C CNN
F 2 "Package_DIP:DIP-8_W7.62mm" H 7650 2300 50  0001 C CNN
F 3 "http://ww1.microchip.com/downloads/en/DeviceDoc/21733j.pdf" H 7650 2300 50  0001 C CNN
	1    7650 2300
	1    0    0    -1  
$EndComp
$Comp
L Amplifier_Operational:MCP6002-xP U21
U 2 1 610BBCB3
P 7650 4000
F 0 "U21" H 7650 4367 50  0000 C CNN
F 1 "MCP6002-xP" H 7650 4276 50  0000 C CNN
F 2 "Package_DIP:DIP-8_W7.62mm" H 7650 4000 50  0001 C CNN
F 3 "http://ww1.microchip.com/downloads/en/DeviceDoc/21733j.pdf" H 7650 4000 50  0001 C CNN
	2    7650 4000
	1    0    0    -1  
$EndComp
$Comp
L Amplifier_Operational:MCP6002-xP U21
U 3 1 610BC5E7
P 5100 3250
F 0 "U21" H 5058 3296 50  0000 L CNN
F 1 "MCP6002-xP" H 5058 3205 50  0000 L CNN
F 2 "Package_DIP:DIP-8_W7.62mm" H 5100 3250 50  0001 C CNN
F 3 "http://ww1.microchip.com/downloads/en/DeviceDoc/21733j.pdf" H 5100 3250 50  0001 C CNN
	3    5100 3250
	1    0    0    -1  
$EndComp
Connection ~ 7950 2300
Connection ~ 7950 4000
Wire Wire Line
	7350 2550 7950 2550
Wire Wire Line
	7350 4250 7950 4250
$Comp
L Amplifier_Operational:MCP6002-xP U24
U 1 1 61650C20
P 6400 2300
F 0 "U24" H 6400 2667 50  0000 C CNN
F 1 "MCP6002-xP" H 6400 2576 50  0000 C CNN
F 2 "Package_DIP:DIP-8_W7.62mm" H 6400 2300 50  0001 C CNN
F 3 "http://ww1.microchip.com/downloads/en/DeviceDoc/21733j.pdf" H 6400 2300 50  0001 C CNN
	1    6400 2300
	1    0    0    1   
$EndComp
Wire Wire Line
	6100 2200 6100 2050
Wire Wire Line
	6100 2050 6700 2050
$Comp
L Amplifier_Operational:MCP6002-xP U24
U 2 1 61660132
P 6350 4000
F 0 "U24" H 6350 4367 50  0000 C CNN
F 1 "MCP6002-xP" H 6350 4276 50  0000 C CNN
F 2 "Package_DIP:DIP-8_W7.62mm" H 6350 4000 50  0001 C CNN
F 3 "http://ww1.microchip.com/downloads/en/DeviceDoc/21733j.pdf" H 6350 4000 50  0001 C CNN
	2    6350 4000
	1    0    0    1   
$EndComp
Wire Wire Line
	6050 3900 6050 3750
Wire Wire Line
	6050 3750 6650 3750
$Comp
L power:+5VA #PWR0283
U 1 1 61678D5D
P 4150 2950
F 0 "#PWR0283" H 4150 2800 50  0001 C CNN
F 1 "+5VA" H 4165 3123 50  0000 C CNN
F 2 "" H 4150 2950 50  0001 C CNN
F 3 "" H 4150 2950 50  0001 C CNN
	1    4150 2950
	1    0    0    -1  
$EndComp
$Comp
L power:GNDA #PWR0284
U 1 1 61678D67
P 4150 3550
F 0 "#PWR0284" H 4150 3300 50  0001 C CNN
F 1 "GNDA" H 4155 3377 50  0000 C CNN
F 2 "" H 4150 3550 50  0001 C CNN
F 3 "" H 4150 3550 50  0001 C CNN
	1    4150 3550
	1    0    0    -1  
$EndComp
$Comp
L Amplifier_Operational:MCP6002-xP U24
U 3 1 61678D71
P 4250 3250
F 0 "U24" H 4208 3296 50  0000 L CNN
F 1 "MCP6002-xP" H 4208 3205 50  0000 L CNN
F 2 "Package_DIP:DIP-8_W7.62mm" H 4250 3250 50  0001 C CNN
F 3 "http://ww1.microchip.com/downloads/en/DeviceDoc/21733j.pdf" H 4250 3250 50  0001 C CNN
	3    4250 3250
	1    0    0    -1  
$EndComp
Wire Wire Line
	6700 2050 6700 2300
Wire Wire Line
	6700 2300 7050 2300
Wire Wire Line
	7050 2300 7050 2400
Connection ~ 6700 2300
Wire Wire Line
	6650 3750 6650 4000
Wire Wire Line
	6650 4000 7050 4000
Wire Wire Line
	7050 4000 7050 4100
Connection ~ 6650 4000
$EndSCHEMATC
