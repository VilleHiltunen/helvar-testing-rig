EESchema Schematic File Version 4
LIBS:ConnectorPCB-cache
EELAYER 26 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title "Testing rig base plate connector pcb"
Date "2019-07-22"
Rev "1"
Comp "Aalto University"
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L Switch:SW_Reed SW2
U 1 1 5D359854
P 5950 3750
F 0 "SW2" H 5950 3972 50  0000 C CNN
F 1 "SW_Reed" H 5950 3881 50  0000 C CNN
F 2 "Battery_Connector_SMD:ReedSwitchHole" H 5950 3750 50  0001 C CNN
F 3 "~" H 5950 3750 50  0001 C CNN
	1    5950 3750
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:Mounting_Hole H2
U 1 1 5D3FA846
P 4000 2850
F 0 "H2" H 4100 2896 50  0000 L CNN
F 1 "MountingHole" H 4100 2805 50  0000 L CNN
F 2 "Battery_Connector_SMD:Screw_Hole" H 4000 2850 50  0001 C CNN
F 3 "~" H 4000 2850 50  0001 C CNN
	1    4000 2850
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:Mounting_Hole H4
U 1 1 5D3FB48C
P 4250 2850
F 0 "H4" H 4350 2896 50  0000 L CNN
F 1 "MountingHole" H 4350 2805 50  0000 L CNN
F 2 "Battery_Connector_SMD:Screw_Hole" H 4250 2850 50  0001 C CNN
F 3 "~" H 4250 2850 50  0001 C CNN
	1    4250 2850
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:Mounting_Hole H1
U 1 1 5D3FB67A
P 4000 2600
F 0 "H1" H 4100 2646 50  0000 L CNN
F 1 "MountingHole" H 4100 2555 50  0000 L CNN
F 2 "Battery_Connector_SMD:Screw_Hole" H 4000 2600 50  0001 C CNN
F 3 "~" H 4000 2600 50  0001 C CNN
	1    4000 2600
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:Mounting_Hole H3
U 1 1 5D3FBE46
P 4250 2600
F 0 "H3" H 4350 2646 50  0000 L CNN
F 1 "MountingHole" H 4350 2555 50  0000 L CNN
F 2 "Battery_Connector_SMD:Screw_Hole" H 4250 2600 50  0001 C CNN
F 3 "~" H 4250 2600 50  0001 C CNN
	1    4250 2600
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:Mounting_Hole H5
U 1 1 5D3FC0F9
P 5400 2600
F 0 "H5" H 5500 2646 50  0000 L CNN
F 1 "MagnetHole" H 5500 2555 50  0000 L CNN
F 2 "Battery_Connector_SMD:Magnet_Hole" H 5400 2600 50  0001 C CNN
F 3 "~" H 5400 2600 50  0001 C CNN
	1    5400 2600
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:Mounting_Hole H6
U 1 1 5D3FC5EE
P 5400 2850
F 0 "H6" H 5500 2896 50  0000 L CNN
F 1 "MagnetHole" H 5500 2805 50  0000 L CNN
F 2 "Battery_Connector_SMD:Magnet_Hole" H 5400 2850 50  0001 C CNN
F 3 "~" H 5400 2850 50  0001 C CNN
	1    5400 2850
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x06_Female J2
U 1 1 5D439936
P 7350 3550
F 0 "J2" H 7378 3526 50  0000 L CNN
F 1 "Conn_01x06_Female" H 7378 3435 50  0000 L CNN
F 2 "Battery_Connector_SMD:SMD_Connector_6X" H 7350 3550 50  0001 C CNN
F 3 "~" H 7350 3550 50  0001 C CNN
	1    7350 3550
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x06_Female J1
U 1 1 5D43D52B
P 4000 3650
F 0 "J1" H 3892 3125 50  0000 C CNN
F 1 "Conn_01x06_Female" H 3892 3216 50  0000 C CNN
F 2 "Battery_Connector_SMD:Battery_Connector_Pad_SMD" H 4000 3650 50  0001 C CNN
F 3 "~" H 4000 3650 50  0001 C CNN
	1    4000 3650
	-1   0    0    1   
$EndComp
Wire Wire Line
	4200 3350 6310 3350
Wire Wire Line
	4200 3450 5750 3450
$Comp
L Switch:SW_Reed SW1
U 1 1 5D358843
P 5950 3450
F 0 "SW1" H 5950 3228 50  0000 C CNN
F 1 "SW_Reed" H 5950 3319 50  0000 C CNN
F 2 "Battery_Connector_SMD:ReedSwitchHole" H 5950 3450 50  0001 C CNN
F 3 "~" H 5950 3450 50  0001 C CNN
	1    5950 3450
	-1   0    0    1   
$EndComp
Wire Wire Line
	6150 3450 6310 3450
Text Label 6750 3450 0    50   ~ 0
5V
Text Label 6750 3350 0    50   ~ 0
SIG
Text Label 6750 3550 0    50   ~ 0
GND
Wire Wire Line
	4200 3550 6310 3550
Wire Wire Line
	4200 3750 5750 3750
Wire Wire Line
	4200 3650 6310 3650
Wire Wire Line
	7000 3650 7000 3550
Connection ~ 7000 3650
Wire Wire Line
	7000 3650 7150 3650
Connection ~ 7000 3550
Wire Wire Line
	7000 3550 7150 3550
$Comp
L Connector:Conn_01x06_Female J3
U 1 1 5D43FA10
P 6510 3550
F 0 "J3" H 6538 3526 50  0000 L CNN
F 1 "Conn_01x06_Female" H 6538 3435 50  0000 L CNN
F 2 "Battery_Connector_SMD:SMD_Connector_6X" H 6510 3550 50  0001 C CNN
F 3 "~" H 6510 3550 50  0001 C CNN
	1    6510 3550
	1    0    0    -1  
$EndComp
Connection ~ 6310 3350
Wire Wire Line
	6310 3350 7150 3350
Connection ~ 6310 3450
Wire Wire Line
	6310 3450 7150 3450
Connection ~ 6310 3550
Wire Wire Line
	6310 3550 7000 3550
Connection ~ 6310 3650
Wire Wire Line
	6310 3650 7000 3650
Wire Wire Line
	7150 3750 7000 3750
Wire Wire Line
	7000 3750 7000 3650
Wire Wire Line
	6310 3750 6310 3650
Wire Wire Line
	6310 3850 6150 3850
Wire Wire Line
	6150 3850 6150 3750
Wire Wire Line
	6310 3850 7150 3850
Connection ~ 6310 3850
NoConn ~ 4200 3850
$EndSCHEMATC
