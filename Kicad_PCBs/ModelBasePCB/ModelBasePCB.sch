EESchema Schematic File Version 4
LIBS:ModelBasePCB-cache
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
L Connector:Conn_01x06_Female J1
U 1 1 5D4961FD
P 2750 3350
F 0 "J1" H 2644 2825 50  0000 C CNN
F 1 "Conn_01x06_Female" H 2644 2916 50  0000 C CNN
F 2 "Battery_Connector_SMD:Battery_Connector_Pad_SMD" H 2750 3350 50  0001 C CNN
F 3 "~" H 2750 3350 50  0001 C CNN
	1    2750 3350
	-1   0    0    1   
$EndComp
NoConn ~ 2950 3550
Wire Wire Line
	2950 3450 3600 3450
$Comp
L Connector:Conn_01x05_Male J2
U 1 1 5D4965B6
P 3800 3250
F 0 "J2" H 3773 3180 50  0000 R CNN
F 1 "Conn_01x05_Male" H 3773 3271 50  0000 R CNN
F 2 "Battery_Connector_SMD:PiikkiThroughHole" H 3800 3250 50  0001 C CNN
F 3 "~" H 3800 3250 50  0001 C CNN
	1    3800 3250
	-1   0    0    1   
$EndComp
Wire Wire Line
	3600 3350 2950 3350
Wire Wire Line
	2950 3250 3600 3250
Wire Wire Line
	3600 3150 2950 3150
Wire Wire Line
	2950 3050 3600 3050
Text Label 3300 3050 0    50   ~ 0
SIG
Text Label 3300 3150 0    50   ~ 0
5V
Text Label 3300 3250 0    50   ~ 0
GND
Text Label 3300 3350 0    50   ~ 0
GND
Text Label 3300 3450 0    50   ~ 0
12V
$EndSCHEMATC
