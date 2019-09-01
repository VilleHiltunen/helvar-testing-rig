EESchema Schematic File Version 4
LIBS:BackbonePCB-cache
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
L Connector:Conn_01x32_Female J12
U 1 1 5D46F4CB
P 11200 3550
F 0 "J12" H 11000 3500 50  0000 L CNN
F 1 "Conn_01x32_Female" V 11200 3250 50  0000 L CNN
F 2 "Battery_Connector_SMD:Connector_32x" H 11200 3550 50  0001 C CNN
F 3 "~" H 11200 3550 50  0001 C CNN
	1    11200 3550
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x32_Female J9
U 1 1 5D474612
P 7500 3650
F 0 "J9" H 7392 1825 50  0000 C CNN
F 1 "Conn_01x32_Female" H 7392 1916 50  0000 C CNN
F 2 "Battery_Connector_SMD:Connector_32x" H 7500 3650 50  0001 C CNN
F 3 "~" H 7500 3650 50  0001 C CNN
	1    7500 3650
	-1   0    0    1   
$EndComp
Wire Wire Line
	5750 2050 5850 2050
Wire Wire Line
	5750 2050 5750 2150
Wire Wire Line
	5850 2150 5750 2150
Wire Wire Line
	4250 2050 4200 2050
Wire Wire Line
	4200 2150 4250 2150
Wire Wire Line
	4250 2150 4250 2050
Connection ~ 4250 2050
Connection ~ 5750 2050
Wire Wire Line
	5850 4500 5750 4500
Wire Wire Line
	4200 4500 4250 4500
Wire Wire Line
	5750 4600 5850 4600
Wire Wire Line
	4300 4600 4200 4600
Wire Wire Line
	4300 5100 4450 5100
$Comp
L Connector:Conn_01x06_Female J3
U 1 1 5D6988C5
P 4550 850
F 0 "J3" V 4488 462 50  0000 R CNN
F 1 "Conn_01x06_Female" V 4397 462 50  0000 R CNN
F 2 "Battery_Connector_SMD:SMD_Connector_6X" H 4550 850 50  0001 C CNN
F 3 "~" H 4550 850 50  0001 C CNN
	1    4550 850 
	0    -1   -1   0   
$EndComp
$Comp
L Connector:Conn_01x06_Female J5
U 1 1 5D69ADF4
P 5400 850
F 0 "J5" V 5338 462 50  0000 R CNN
F 1 "Conn_01x06_Female" V 5247 462 50  0000 R CNN
F 2 "Battery_Connector_SMD:SMD_Connector_6X" H 5400 850 50  0001 C CNN
F 3 "~" H 5400 850 50  0001 C CNN
	1    5400 850 
	0    -1   -1   0   
$EndComp
$Comp
L Connector:Conn_01x06_Female J4
U 1 1 5D69B656
P 4750 5900
F 0 "J4" V 4596 6148 50  0000 L CNN
F 1 "Conn_01x06_Female" V 4687 6148 50  0000 L CNN
F 2 "Battery_Connector_SMD:SMD_Connector_6X" H 4750 5900 50  0001 C CNN
F 3 "~" H 4750 5900 50  0001 C CNN
	1    4750 5900
	0    1    1    0   
$EndComp
$Comp
L Connector:Conn_01x06_Female J6
U 1 1 5D69C96B
P 5450 5900
F 0 "J6" V 5296 6148 50  0000 L CNN
F 1 "Conn_01x06_Female" V 5387 6148 50  0000 L CNN
F 2 "Battery_Connector_SMD:SMD_Connector_6X" H 5450 5900 50  0001 C CNN
F 3 "~" H 5450 5900 50  0001 C CNN
	1    5450 5900
	0    1    1    0   
$EndComp
Text Label 5300 2050 0    50   ~ 0
GND
Text Label 4950 3800 0    50   ~ 0
5V
Text Label 5100 5100 0    50   ~ 0
12V
Wire Wire Line
	4750 1050 4750 1100
Wire Wire Line
	4650 1050 4650 1100
Wire Wire Line
	4550 1050 4550 1100
Wire Wire Line
	4450 1050 4450 1100
Wire Wire Line
	4350 1050 4350 1100
Wire Wire Line
	5600 1050 5600 1100
Wire Wire Line
	5500 1050 5500 1100
Wire Wire Line
	5400 1050 5400 1100
Wire Wire Line
	5300 1050 5300 1100
Wire Wire Line
	5200 1050 5200 1100
Wire Wire Line
	5550 5700 5550 5650
Wire Wire Line
	5450 5700 5450 5650
Wire Wire Line
	5350 5700 5350 5650
Wire Wire Line
	5250 5700 5250 5600
Connection ~ 5250 5100
Wire Wire Line
	5250 5100 5750 5100
Wire Wire Line
	4550 5700 4550 5650
Connection ~ 4550 5100
Wire Wire Line
	4450 5700 4450 5650
Wire Wire Line
	4450 5650 4550 5650
Connection ~ 4550 5650
Wire Wire Line
	4550 5650 4550 5100
Wire Wire Line
	5450 5650 5550 5650
Connection ~ 5450 5650
Wire Wire Line
	5350 5650 5450 5650
Wire Wire Line
	5150 5700 5150 5600
Wire Wire Line
	5150 5600 5250 5600
Connection ~ 5250 5600
Wire Wire Line
	5250 5600 5250 5100
Wire Wire Line
	5600 1100 5500 1100
Connection ~ 5500 1100
Wire Wire Line
	5400 1100 5500 1100
Wire Wire Line
	5300 1100 5200 1100
Wire Wire Line
	4750 1100 4650 1100
Connection ~ 4650 1100
Wire Wire Line
	4650 1100 4550 1100
Wire Wire Line
	4450 1100 4350 1100
$Comp
L Mechanical:Mounting_Hole H1
U 1 1 5DA1EBB9
P 6800 1700
F 0 "H1" H 6900 1746 50  0000 L CNN
F 1 "MountingHole" H 6900 1655 50  0000 L CNN
F 2 "Battery_Connector_SMD:Screw_Hole" H 6800 1700 50  0001 C CNN
F 3 "~" H 6800 1700 50  0001 C CNN
	1    6800 1700
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:Mounting_Hole H2
U 1 1 5DA1F830
P 6800 2300
F 0 "H2" H 6900 2346 50  0000 L CNN
F 1 "MountingHole" H 6900 2255 50  0000 L CNN
F 2 "Battery_Connector_SMD:Screw_Hole" H 6800 2300 50  0001 C CNN
F 3 "~" H 6800 2300 50  0001 C CNN
	1    6800 2300
	1    0    0    -1  
$EndComp
Wire Wire Line
	4550 5100 5200 5100
Wire Wire Line
	4250 2050 4650 2050
Wire Wire Line
	4650 5700 4650 5650
Wire Wire Line
	4850 5650 4850 5700
Wire Wire Line
	4650 5650 4750 5650
Wire Wire Line
	4750 5700 4750 5650
Connection ~ 4750 5650
Wire Wire Line
	4750 5650 4850 5650
Wire Wire Line
	4750 5650 4750 2050
Connection ~ 4750 2050
Wire Wire Line
	4750 2050 5450 2050
Wire Wire Line
	5450 5650 5450 2050
Connection ~ 5450 2050
Wire Wire Line
	5450 2050 5500 2050
Wire Wire Line
	4250 3800 4850 3800
Connection ~ 4950 3800
Wire Wire Line
	4850 1050 4850 3800
Connection ~ 4850 3800
Wire Wire Line
	4850 3800 4950 3800
Wire Wire Line
	4650 1100 4650 2050
Connection ~ 4650 2050
Wire Wire Line
	4650 2050 4750 2050
Wire Wire Line
	5500 1100 5500 2050
Connection ~ 5500 2050
Wire Wire Line
	5500 2050 5750 2050
Connection ~ 5200 1100
Connection ~ 4450 1100
Wire Wire Line
	4950 3800 4950 5700
Wire Wire Line
	4950 3800 5650 3800
Connection ~ 5650 3800
Wire Wire Line
	5650 5700 5650 3800
Wire Wire Line
	5200 1100 5200 5100
Connection ~ 5200 5100
Wire Wire Line
	5200 5100 5250 5100
Connection ~ 4450 5100
Wire Wire Line
	4450 5100 4550 5100
Wire Wire Line
	4450 1100 4450 5100
$Comp
L Connector:Conn_01x02_Female J1
U 1 1 5D4EA64D
P 4000 2150
F 0 "J1" H 3894 1825 50  0000 C CNN
F 1 "Conn_01x02_Female" H 3894 1916 50  0000 C CNN
F 2 "Battery_Connector_SMD:SMD_Connector_2X" H 4000 2150 50  0001 C CNN
F 3 "~" H 4000 2150 50  0001 C CNN
	1    4000 2150
	-1   0    0    1   
$EndComp
$Comp
L Connector:Conn_01x02_Female J2
U 1 1 5D4EA6C5
P 4000 4600
F 0 "J2" H 3894 4275 50  0000 C CNN
F 1 "Conn_01x02_Female" H 3894 4366 50  0000 C CNN
F 2 "Battery_Connector_SMD:SMD_Connector_2X" H 4000 4600 50  0001 C CNN
F 3 "~" H 4000 4600 50  0001 C CNN
	1    4000 4600
	-1   0    0    1   
$EndComp
$Comp
L Connector:Conn_01x02_Female J7
U 1 1 5D4EAB04
P 6050 2050
F 0 "J7" H 6077 2026 50  0000 L CNN
F 1 "Conn_01x02_Female" H 6077 1935 50  0000 L CNN
F 2 "Battery_Connector_SMD:SMD_Connector_2X" H 6050 2050 50  0001 C CNN
F 3 "~" H 6050 2050 50  0001 C CNN
	1    6050 2050
	1    0    0    -1  
$EndComp
Wire Wire Line
	5650 3800 5700 3800
Wire Wire Line
	4250 3800 4250 4500
Wire Wire Line
	4300 4600 4300 5100
$Comp
L Connector:Conn_01x02_Female J8
U 1 1 5D4EAA1A
P 6050 4500
F 0 "J8" H 6077 4476 50  0000 L CNN
F 1 "Conn_01x02_Female" H 6077 4385 50  0000 L CNN
F 2 "Battery_Connector_SMD:SMD_Connector_2X" H 6050 4500 50  0001 C CNN
F 3 "~" H 6050 4500 50  0001 C CNN
	1    6050 4500
	1    0    0    -1  
$EndComp
Wire Wire Line
	5750 4600 5750 5100
Wire Wire Line
	5750 3800 5750 4500
$Comp
L Connector:Conn_01x16_Female J10
U 1 1 5D59ABD7
P 8400 1250
F 0 "J10" V 8565 1180 50  0000 C CNN
F 1 "Conn_01x16_Female" V 8474 1180 50  0000 C CNN
F 2 "Battery_Connector_SMD:Connector_16x" H 8400 1250 50  0001 C CNN
F 3 "~" H 8400 1250 50  0001 C CNN
	1    8400 1250
	0    -1   -1   0   
$EndComp
$Comp
L Connector:Conn_01x16_Female J11
U 1 1 5D59AD17
P 10200 5600
F 0 "J11" V 10272 5530 50  0000 C CNN
F 1 "Conn_01x16_Female" V 10363 5530 50  0000 C CNN
F 2 "Battery_Connector_SMD:Connector_16x" H 10200 5600 50  0001 C CNN
F 3 "~" H 10200 5600 50  0001 C CNN
	1    10200 5600
	0    1    1    0   
$EndComp
Wire Wire Line
	7700 2050 11000 2050
Wire Wire Line
	7700 2150 9400 2150
Wire Wire Line
	7700 2250 7800 2250
Wire Wire Line
	7700 2350 9500 2350
Wire Wire Line
	7700 2450 7900 2450
Wire Wire Line
	7700 2550 9600 2550
Wire Wire Line
	7700 2650 8000 2650
Wire Wire Line
	7700 2750 9700 2750
Wire Wire Line
	7700 2850 8100 2850
Wire Wire Line
	7700 2950 9800 2950
Wire Wire Line
	7700 3050 8200 3050
Wire Wire Line
	7700 3150 9900 3150
Wire Wire Line
	7700 3250 8300 3250
Wire Wire Line
	7700 3350 10000 3350
Wire Wire Line
	7700 3450 8400 3450
Wire Wire Line
	7700 3550 10100 3550
Wire Wire Line
	7700 3650 8500 3650
Wire Wire Line
	7700 3750 10200 3750
Wire Wire Line
	7700 3850 8600 3850
Wire Wire Line
	7700 3950 10300 3950
Wire Wire Line
	7700 4050 8700 4050
Wire Wire Line
	7700 4150 10400 4150
Wire Wire Line
	7700 4250 8800 4250
Wire Wire Line
	7700 4350 10500 4350
Wire Wire Line
	7700 4450 8900 4450
Wire Wire Line
	7700 4550 10600 4550
Wire Wire Line
	7700 4650 9000 4650
Wire Wire Line
	7700 4750 10700 4750
Wire Wire Line
	7700 4850 9100 4850
Wire Wire Line
	7700 4950 10800 4950
Wire Wire Line
	7700 5050 9200 5050
Wire Wire Line
	7700 5150 10900 5150
Wire Wire Line
	7700 1450 7700 2050
Connection ~ 7700 2050
Wire Wire Line
	7800 1450 7800 2250
Connection ~ 7800 2250
Wire Wire Line
	7800 2250 11000 2250
Wire Wire Line
	7900 1450 7900 2450
Connection ~ 7900 2450
Wire Wire Line
	7900 2450 11000 2450
Wire Wire Line
	8000 1450 8000 2650
Connection ~ 8000 2650
Wire Wire Line
	8000 2650 11000 2650
Wire Wire Line
	8100 1450 8100 2850
Connection ~ 8100 2850
Wire Wire Line
	8100 2850 11000 2850
Wire Wire Line
	8200 1450 8200 3050
Connection ~ 8200 3050
Wire Wire Line
	8200 3050 11000 3050
Wire Wire Line
	8300 1450 8300 3250
Connection ~ 8300 3250
Wire Wire Line
	8300 3250 11000 3250
Wire Wire Line
	8400 1450 8400 3450
Connection ~ 8400 3450
Wire Wire Line
	8400 3450 11000 3450
Wire Wire Line
	8500 1450 8500 3650
Connection ~ 8500 3650
Wire Wire Line
	8500 3650 11000 3650
Wire Wire Line
	8600 1450 8600 3850
Connection ~ 8600 3850
Wire Wire Line
	8600 3850 11000 3850
Wire Wire Line
	8700 1450 8700 4050
Connection ~ 8700 4050
Wire Wire Line
	8700 4050 11000 4050
Wire Wire Line
	8800 1450 8800 4250
Connection ~ 8800 4250
Wire Wire Line
	8800 4250 11000 4250
Wire Wire Line
	8900 1450 8900 4450
Connection ~ 8900 4450
Wire Wire Line
	8900 4450 11000 4450
Wire Wire Line
	9000 1450 9000 4650
Connection ~ 9000 4650
Wire Wire Line
	9000 4650 11000 4650
Wire Wire Line
	9100 1450 9100 4850
Connection ~ 9100 4850
Wire Wire Line
	9100 4850 11000 4850
Wire Wire Line
	9200 1450 9200 5050
Connection ~ 9200 5050
Wire Wire Line
	9200 5050 11000 5050
Wire Wire Line
	9400 5400 9400 2150
Connection ~ 9400 2150
Wire Wire Line
	9400 2150 11000 2150
Wire Wire Line
	9500 5400 9500 2350
Connection ~ 9500 2350
Wire Wire Line
	9500 2350 11000 2350
Wire Wire Line
	9600 5400 9600 2550
Connection ~ 9600 2550
Wire Wire Line
	9600 2550 11000 2550
Wire Wire Line
	9700 5400 9700 2750
Connection ~ 9700 2750
Wire Wire Line
	9700 2750 11000 2750
Wire Wire Line
	9800 5400 9800 2950
Connection ~ 9800 2950
Wire Wire Line
	9800 2950 11000 2950
Wire Wire Line
	9900 5400 9900 3150
Connection ~ 9900 3150
Wire Wire Line
	9900 3150 11000 3150
Wire Wire Line
	10000 5400 10000 3350
Connection ~ 10000 3350
Wire Wire Line
	10000 3350 11000 3350
Wire Wire Line
	10100 5400 10100 3550
Connection ~ 10100 3550
Wire Wire Line
	10100 3550 11000 3550
Wire Wire Line
	10200 5400 10200 3750
Connection ~ 10200 3750
Wire Wire Line
	10200 3750 11000 3750
Wire Wire Line
	10300 5400 10300 3950
Connection ~ 10300 3950
Wire Wire Line
	10300 3950 11000 3950
Wire Wire Line
	10400 5400 10400 4150
Connection ~ 10400 4150
Wire Wire Line
	10400 4150 11000 4150
Wire Wire Line
	10500 5400 10500 4350
Connection ~ 10500 4350
Wire Wire Line
	10500 4350 11000 4350
Wire Wire Line
	10600 5400 10600 4550
Connection ~ 10600 4550
Wire Wire Line
	10600 4550 11000 4550
Wire Wire Line
	10700 5400 10700 4750
Connection ~ 10700 4750
Wire Wire Line
	10700 4750 11000 4750
Wire Wire Line
	10800 5400 10800 4950
Connection ~ 10800 4950
Wire Wire Line
	10800 4950 11000 4950
Wire Wire Line
	10900 5400 10900 5150
Connection ~ 10900 5150
Wire Wire Line
	10900 5150 11000 5150
Wire Wire Line
	5700 1050 5700 3800
Connection ~ 5700 3800
Wire Wire Line
	5700 3800 5750 3800
$EndSCHEMATC
