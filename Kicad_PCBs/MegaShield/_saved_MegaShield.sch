EESchema Schematic File Version 4
EELAYER 26 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L arduino:Arduino_Mega2560_Shield XA1
U 1 1 5D5D7660
P 5250 3850
F 0 "XA1" H 5250 1470 60  0000 C CNN
F 1 "Arduino_Mega2560_Shield" H 5250 1364 60  0000 C CNN
F 2 "Arduino:Arduino_Mega2560_Shield" H 5950 6600 60  0001 C CNN
F 3 "https://store.arduino.cc/arduino-mega-2560-rev3" H 5950 6600 60  0001 C CNN
	1    5250 3850
	1    0    0    -1  
$EndComp
NoConn ~ 5000 1250
NoConn ~ 5100 1250
NoConn ~ 5200 1250
NoConn ~ 5300 1250
NoConn ~ 5400 1250
NoConn ~ 5500 1250
NoConn ~ 3950 1700
NoConn ~ 3950 1800
NoConn ~ 3950 2100
NoConn ~ 3950 2200
NoConn ~ 3950 2300
NoConn ~ 3950 2400
NoConn ~ 3950 2500
NoConn ~ 3950 2600
NoConn ~ 3950 2700
NoConn ~ 3950 2800
$Comp
L Interface_UART:MAX1487E U1
U 1 1 5D5D7CA4
P 3000 2100
F 0 "U1" H 3000 1322 50  0000 C CNN
F 1 "MAX1487E" H 3000 1413 50  0000 C CNN
F 2 "Quickprints:NSOIC-8" H 3000 1400 50  0001 C CNN
F 3 "https://datasheets.maximintegrated.com/en/ds/MAX1487E-MAX491E.pdf" H 3000 2150 50  0001 C CNN
	1    3000 2100
	-1   0    0    1   
$EndComp
Wire Wire Line
	3750 1900 3950 1900
Wire Wire Line
	3400 1900 3600 1900
Wire Wire Line
	3600 1900 3600 2000
Wire Wire Line
	3400 2000 3400 2100
Text GLabel 3500 2100 2    50   Input ~ 0
DR
Wire Wire Line
	3500 2100 3400 2100
Connection ~ 3400 2100
Text GLabel 6550 1800 2    50   Input ~ 0
DR
Text GLabel 7450 1700 0    50   Input ~ 0
SEN_RL
Text GLabel 7450 1800 0    50   Input ~ 0
SEN_LL
Text GLabel 7450 1900 0    50   Input ~ 0
X_RL
Text GLabel 7450 2200 0    50   Input ~ 0
Y_LL
Text GLabel 7450 2000 0    50   Input ~ 0
X_LL
Text GLabel 7450 2100 0    50   Input ~ 0
Y_RL
$Comp
L Device:R R1
U 1 1 5D5D8AFC
P 1500 4050
F 0 "R1" V 1707 4050 50  0000 C CNN
F 1 "R" V 1616 4050 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 1430 4050 50  0001 C CNN
F 3 "~" H 1500 4050 50  0001 C CNN
	1    1500 4050
	0    -1   -1   0   
$EndComp
$Comp
L Transistor_BJT:2N2219 Q1
U 1 1 5D5D8D79
P 1900 4050
F 0 "Q1" H 2091 4096 50  0000 L CNN
F 1 "2N2219" H 2091 4005 50  0000 L CNN
F 2 "Quickprints:BJT" H 2100 3975 50  0001 L CIN
F 3 "http://www.onsemi.com/pub_link/Collateral/2N2219-D.PDF" H 1900 4050 50  0001 L CNN
	1    1900 4050
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x02_Male J3
U 1 1 5D5D9476
P 1650 2000
F 0 "J3" H 1756 2178 50  0000 C CNN
F 1 "rs485conn" H 1756 2087 50  0000 C CNN
F 2 "Quickprints:2_2.54" H 1650 2000 50  0001 C CNN
F 3 "~" H 1650 2000 50  0001 C CNN
	1    1650 2000
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x02_Male J1
U 1 1 5D5D9545
P 1300 2000
F 0 "J1" H 1406 2178 50  0000 C CNN
F 1 "rs485conn" H 1406 2087 50  0000 C CNN
F 2 "Quickprints:2_2.54" H 1300 2000 50  0001 C CNN
F 3 "~" H 1300 2000 50  0001 C CNN
	1    1300 2000
	1    0    0    -1  
$EndComp
Wire Wire Line
	2600 1900 2300 1900
Wire Wire Line
	2100 1900 2100 2000
Wire Wire Line
	2100 2000 1850 2000
Wire Wire Line
	2100 1900 1500 1900
Wire Wire Line
	1500 1900 1500 2000
Connection ~ 2100 1900
Wire Wire Line
	2600 2200 2300 2200
Wire Wire Line
	1850 2200 1850 2100
Wire Wire Line
	1850 2200 1500 2200
Wire Wire Line
	1500 2200 1500 2100
Connection ~ 1850 2200
Text GLabel 2300 1500 1    50   Input ~ 0
5V
$Comp
L Device:R R3
U 1 1 5D5D9A65
P 2300 1700
F 0 "R3" H 2370 1746 50  0000 L CNN
F 1 "R" H 2370 1655 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 2230 1700 50  0001 C CNN
F 3 "~" H 2300 1700 50  0001 C CNN
	1    2300 1700
	1    0    0    -1  
$EndComp
Wire Wire Line
	2300 1550 2300 1500
Wire Wire Line
	2300 1850 2300 1900
Connection ~ 2300 1900
Wire Wire Line
	2300 1900 2100 1900
$Comp
L Device:R R4
U 1 1 5D5D9E7B
P 2300 2550
F 0 "R4" H 2370 2596 50  0000 L CNN
F 1 "R" H 2370 2505 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 2230 2550 50  0001 C CNN
F 3 "~" H 2300 2550 50  0001 C CNN
	1    2300 2550
	1    0    0    -1  
$EndComp
Wire Wire Line
	2300 2400 2300 2200
Connection ~ 2300 2200
Wire Wire Line
	2300 2200 1850 2200
Text GLabel 2300 2850 3    50   Input ~ 0
GND
Wire Wire Line
	2300 2850 2300 2700
Text GLabel 1200 4050 0    50   Input ~ 0
HEAT
Wire Wire Line
	1650 4050 1700 4050
Wire Wire Line
	1350 4050 1200 4050
Text GLabel 3350 5100 0    50   Input ~ 0
GND
Wire Wire Line
	3350 5100 3500 5100
Text GLabel 3200 5700 0    50   Input ~ 0
5V
Wire Wire Line
	3950 5700 3200 5700
$Comp
L pspice:MPMOS M1
U 1 1 5D5DC1F0
P 3100 3900
F 0 "M1" H 3387 3946 50  0000 L CNN
F 1 "MPMOS" H 3387 3855 50  0000 L CNN
F 2 "Quickprints:MOSFET" H 3100 3900 50  0001 C CNN
F 3 "" H 3100 3900 50  0001 C CNN
	1    3100 3900
	1    0    0    -1  
$EndComp
$Comp
L Device:R R2
U 1 1 5D5DC6B2
P 2000 3550
F 0 "R2" H 1930 3504 50  0000 R CNN
F 1 "R" H 1930 3595 50  0000 R CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 1930 3550 50  0001 C CNN
F 3 "~" H 2000 3550 50  0001 C CNN
	1    2000 3550
	-1   0    0    1   
$EndComp
NoConn ~ 3300 3700
Text GLabel 2800 3200 1    50   Input ~ 0
12V
Wire Wire Line
	2000 3700 2000 3800
Text GLabel 2000 4950 3    50   Input ~ 0
GND
Wire Wire Line
	2000 4250 2000 4950
Wire Wire Line
	3200 3700 3200 3300
Wire Wire Line
	3200 3300 2800 3300
Wire Wire Line
	2000 3300 2000 3400
Wire Wire Line
	2800 3300 2800 3200
Connection ~ 2800 3300
Wire Wire Line
	2800 3300 2500 3300
Wire Wire Line
	2000 3800 2750 3800
Wire Wire Line
	2750 3800 2750 3900
Wire Wire Line
	2750 3900 2900 3900
Connection ~ 2000 3800
Wire Wire Line
	2000 3800 2000 3850
$Comp
L pspice:DIODE D1
U 1 1 5D5DEE99
P 3500 4500
F 0 "D1" V 3546 4372 50  0000 R CNN
F 1 "DIODE" V 3455 4372 50  0000 R CNN
F 2 "Diode_THT:D_DO-41_SOD81_P10.16mm_Horizontal" H 3500 4500 50  0001 C CNN
F 3 "" H 3500 4500 50  0001 C CNN
	1    3500 4500
	0    -1   -1   0   
$EndComp
Wire Wire Line
	3500 4300 3500 4150
Wire Wire Line
	3500 4150 3200 4150
Wire Wire Line
	3200 4150 3200 4100
Wire Wire Line
	3500 4700 3500 5100
Connection ~ 3500 5100
Wire Wire Line
	3500 5100 3950 5100
$Comp
L Connector:Conn_01x01_Male J5
U 1 1 5D5DFF2E
P 3200 4650
F 0 "J5" V 3353 4563 50  0000 R CNN
F 1 "HeatingPad" V 3262 4563 50  0000 R CNN
F 2 "Quickprints:VinPad" H 3200 4650 50  0001 C CNN
F 3 "~" H 3200 4650 50  0001 C CNN
	1    3200 4650
	0    -1   -1   0   
$EndComp
Wire Wire Line
	3200 4450 3200 4150
Connection ~ 3200 4150
Text GLabel 3000 2600 3    50   Input ~ 0
5V
Text GLabel 3000 1500 1    50   Input ~ 0
GND
$Comp
L Connector:Conn_01x02_Male J6
U 1 1 5D5E1FD4
P 3300 2950
F 0 "J6" V 3360 2990 50  0000 L CNN
F 1 "Xpow" V 3451 2990 50  0000 L CNN
F 2 "Quickprints:2_2.54" H 3300 2950 50  0001 C CNN
F 3 "~" H 3300 2950 50  0001 C CNN
	1    3300 2950
	0    1    1    0   
$EndComp
$Comp
L Connector:Conn_01x02_Male J2
U 1 1 5D5E2052
P 1600 2900
F 0 "J2" V 1660 2940 50  0000 L CNN
F 1 "Ypow" V 1751 2940 50  0000 L CNN
F 2 "Quickprints:2_2.54" H 1600 2900 50  0001 C CNN
F 3 "~" H 1600 2900 50  0001 C CNN
	1    1600 2900
	0    1    1    0   
$EndComp
$Comp
L Connector:Conn_01x16_Female J11
U 1 1 5D5E292E
P 8500 3850
F 0 "J11" H 8528 3826 50  0000 L CNN
F 1 "tmc2208" H 8528 3735 50  0000 L CNN
F 2 "Quickprints:StepStick" H 8500 3850 50  0001 C CNN
F 3 "~" H 8500 3850 50  0001 C CNN
	1    8500 3850
	1    0    0    -1  
$EndComp
Text GLabel 7850 3150 0    50   Input ~ 0
GND
Text GLabel 7800 3250 0    50   Input ~ 0
5V
$Comp
L Connector:Conn_01x04_Male J9
U 1 1 5D5E2DE3
P 7650 3450
F 0 "J9" H 7756 3728 50  0000 C CNN
F 1 "SenStepper" H 7756 3637 50  0000 C CNN
F 2 "Quickprints:4_2.54" H 7650 3450 50  0001 C CNN
F 3 "~" H 7650 3450 50  0001 C CNN
	1    7650 3450
	1    0    0    -1  
$EndComp
Text GLabel 7850 3850 0    50   Input ~ 0
12V
NoConn ~ 8300 3750
Text GLabel 7850 3950 0    50   Input ~ 0
DIR
Text GLabel 7850 4050 0    50   Input ~ 0
STEP
NoConn ~ 8300 4150
NoConn ~ 8300 4250
NoConn ~ 8300 4350
Text GLabel 7850 4450 0    50   Input ~ 0
5V
NoConn ~ 8300 4550
Text GLabel 7850 4650 0    50   Input ~ 0
EN
Wire Wire Line
	7850 4650 8300 4650
Wire Wire Line
	8300 4450 7850 4450
Wire Wire Line
	7850 4050 8300 4050
Wire Wire Line
	8300 3950 7850 3950
Wire Wire Line
	7850 3850 8300 3850
Wire Wire Line
	8300 3650 7850 3650
Wire Wire Line
	7850 3550 8300 3550
Wire Wire Line
	8300 3450 7850 3450
Wire Wire Line
	7850 3350 8300 3350
Wire Wire Line
	8300 3250 7800 3250
Wire Wire Line
	8300 3150 7850 3150
Wire Wire Line
	3200 3300 3300 3300
Wire Wire Line
	3300 3300 3300 3150
Connection ~ 3200 3300
Wire Wire Line
	2000 3300 2000 3100
Wire Wire Line
	2000 3100 1600 3100
Connection ~ 2000 3300
Text GLabel 1500 3100 3    50   Input ~ 0
GND
Text GLabel 3200 3200 0    50   Input ~ 0
GND
Wire Wire Line
	3200 3200 3200 3150
NoConn ~ 3950 5600
$Comp
L Connector:Conn_01x01_Male J4
U 1 1 5D5F65CD
P 3100 6000
F 0 "J4" H 3206 6178 50  0000 C CNN
F 1 "5V_VIN" H 3206 6087 50  0000 C CNN
F 2 "Quickprints:VinPad" H 3100 6000 50  0001 C CNN
F 3 "~" H 3100 6000 50  0001 C CNN
	1    3100 6000
	1    0    0    -1  
$EndComp
Wire Wire Line
	3300 6000 3950 6000
NoConn ~ 3950 4800
NoConn ~ 3950 4900
Text GLabel 6550 1900 2    50   Input ~ 0
DIR
Text GLabel 6550 2000 2    50   Input ~ 0
STEP
Text GLabel 6550 2100 2    50   Input ~ 0
EN
Text GLabel 6550 2200 2    50   Input ~ 0
SEN_RL
Text GLabel 6550 2300 2    50   Input ~ 0
SEN_LL
Text GLabel 6550 2400 2    50   Input ~ 0
X_RL
Text GLabel 6550 2500 2    50   Input ~ 0
X_LL
Text GLabel 6550 2600 2    50   Input ~ 0
Y_RL
Text GLabel 6550 2800 2    50   Input ~ 0
HEAT
Text GLabel 6550 2700 2    50   Input ~ 0
Y_LL
NoConn ~ 3950 3000
NoConn ~ 3950 3100
NoConn ~ 3950 3200
NoConn ~ 3950 3300
NoConn ~ 3950 3400
NoConn ~ 3950 3500
NoConn ~ 3950 3600
NoConn ~ 3950 3700
NoConn ~ 3950 3800
NoConn ~ 3950 3900
NoConn ~ 3950 4000
NoConn ~ 3950 4100
NoConn ~ 3950 4200
NoConn ~ 3950 4300
NoConn ~ 3950 4400
NoConn ~ 3950 4500
NoConn ~ 3950 4600
$Comp
L Connector:Conn_01x04_Male J10
U 1 1 5D60B5DB
P 7800 5450
F 0 "J10" V 7953 5162 50  0000 R CNN
F 1 "limitSwitches" V 7862 5162 50  0000 R CNN
F 2 "Quickprints:4_2.54" H 7800 5450 50  0001 C CNN
F 3 "~" H 7800 5450 50  0001 C CNN
	1    7800 5450
	0    -1   -1   0   
$EndComp
Text GLabel 7700 5000 0    50   Input ~ 0
GND
Wire Wire Line
	7700 5000 7700 5250
Wire Wire Line
	7700 5000 7800 5000
Wire Wire Line
	7800 5000 7800 5250
Wire Wire Line
	7800 5000 7900 5000
Wire Wire Line
	7900 5000 7900 5250
Connection ~ 7800 5000
Wire Wire Line
	7900 5000 8000 5000
Wire Wire Line
	8000 5000 8000 5250
Connection ~ 7900 5000
$Comp
L Connector:Conn_01x06_Male J8
U 1 1 5D618D16
P 7650 2000
F 0 "J8" H 7623 1880 50  0000 R CNN
F 1 "SensorLimits" H 7623 1971 50  0000 R CNN
F 2 "Quickprints:6_2.54" H 7650 2000 50  0001 C CNN
F 3 "~" H 7650 2000 50  0001 C CNN
	1    7650 2000
	-1   0    0    1   
$EndComp
NoConn ~ 6550 2900
NoConn ~ 6550 3000
NoConn ~ 6550 3100
NoConn ~ 6550 3200
NoConn ~ 6550 3300
NoConn ~ 6550 3400
NoConn ~ 6550 3500
NoConn ~ 6550 3600
NoConn ~ 6550 3700
NoConn ~ 6550 3800
NoConn ~ 6550 3900
NoConn ~ 6550 4000
NoConn ~ 6550 4100
NoConn ~ 6550 4200
NoConn ~ 6550 4300
NoConn ~ 6550 4400
NoConn ~ 6550 4500
NoConn ~ 6550 4600
NoConn ~ 6550 4700
NoConn ~ 6550 4800
NoConn ~ 6550 4900
NoConn ~ 6550 5000
NoConn ~ 6550 5100
NoConn ~ 6550 5200
NoConn ~ 6550 5300
NoConn ~ 6550 5400
NoConn ~ 6550 5500
NoConn ~ 6550 5600
NoConn ~ 6550 5700
NoConn ~ 6550 5800
NoConn ~ 6550 5900
NoConn ~ 6550 6000
$Comp
L pspice:CAP C1
U 1 1 5D63F215
P 1550 3550
F 0 "C1" V 1865 3550 50  0000 C CNN
F 1 "CAP" V 1774 3550 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" H 1550 3550 50  0001 C CNN
F 3 "" H 1550 3550 50  0001 C CNN
	1    1550 3550
	0    -1   -1   0   
$EndComp
Wire Wire Line
	1800 3550 1800 3300
Wire Wire Line
	1800 3300 2000 3300
Text GLabel 1300 3550 0    50   Input ~ 0
GND
Wire Wire Line
	3600 2000 3750 2000
Wire Wire Line
	3750 2000 3750 1900
Wire Wire Line
	3850 2200 3850 2000
Wire Wire Line
	3850 2000 3950 2000
Wire Wire Line
	3400 2200 3850 2200
Wire Wire Line
	3950 5200 3950 5100
Connection ~ 3950 5100
Wire Wire Line
	3950 5300 3950 5200
Connection ~ 3950 5200
Wire Wire Line
	3950 5400 3950 5350
Connection ~ 3950 5300
Wire Wire Line
	3950 5500 3950 5400
Connection ~ 3950 5400
Wire Wire Line
	3950 5700 3950 5800
Connection ~ 3950 5700
Wire Wire Line
	3950 5900 3950 5800
Connection ~ 3950 5800
$Comp
L Connector:Conn_01x01_Male J7
U 1 1 5D64F22F
P 2500 3000
F 0 "J7" V 2560 3041 50  0000 L CNN
F 1 "12V_VIN" V 2651 3041 50  0000 L CNN
F 2 "Quickprints:VinPad" H 2500 3000 50  0001 C CNN
F 3 "~" H 2500 3000 50  0001 C CNN
	1    2500 3000
	0    1    1    0   
$EndComp
Wire Wire Line
	2500 3200 2500 3300
Connection ~ 2500 3300
Wire Wire Line
	2500 3300 2000 3300
NoConn ~ 6550 1700
$Comp
L Connector:Conn_01x01_Male J12
U 1 1 5D65327A
P 3150 5350
F 0 "J12" H 3256 5528 50  0000 C CNN
F 1 "GND_VIN" H 3256 5437 50  0000 C CNN
F 2 "Quickprints:VinPad" H 3150 5350 50  0001 C CNN
F 3 "~" H 3150 5350 50  0001 C CNN
	1    3150 5350
	1    0    0    -1  
$EndComp
Wire Wire Line
	3350 5350 3950 5350
Connection ~ 3950 5350
Wire Wire Line
	3950 5350 3950 5300
$EndSCHEMATC
