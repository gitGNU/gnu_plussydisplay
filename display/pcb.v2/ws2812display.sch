EESchema Schematic File Version 2
LIBS:ws2812display-rescue
LIBS:power
LIBS:device
LIBS:transistors
LIBS:conn
LIBS:linear
LIBS:regul
LIBS:74xx
LIBS:cmos4000
LIBS:adc-dac
LIBS:memory
LIBS:xilinx
LIBS:microcontrollers
LIBS:dsp
LIBS:microchip
LIBS:analog_switches
LIBS:motorola
LIBS:texas
LIBS:intel
LIBS:audio
LIBS:interface
LIBS:digital-audio
LIBS:philips
LIBS:display
LIBS:cypress
LIBS:siliconi
LIBS:opto
LIBS:atmel
LIBS:contrib
LIBS:valves
LIBS:cc_conn
LIBS:cc_con-prog
LIBS:cc_linear
LIBS:cc_regulator
LIBS:cc_rlc
LIBS:cc_stm32
LIBS:con-harting-ml
LIBS:cc_display
LIBS:cc_if-driver
LIBS:cc_transistor
LIBS:cc_sensors
LIBS:cc_con-usb
LIBS:ws2812display-cache
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 2
Title "Plussy Display"
Date ""
Rev ""
Comp ""
Comment1 "http://www.gnu.org/licenses/gpl-3.0.txt"
Comment2 "LICENSE: GNU GPLv3"
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L CC_STM32F401xE U102
U 1 1 55FECB90
P 3000 2500
F 0 "U102" H 2750 3600 60  0000 C CNN
F 1 "CC_STM32F401xE" H 3000 -400 60  0000 C CNN
F 2 "cc_stm32package:lqfp64" H 3050 2500 60  0001 C CNN
F 3 "" H 3050 2500 60  0000 C CNN
	1    3000 2500
	1    0    0    -1  
$EndComp
$Comp
L CC_XC6204 U101
U 1 1 55FECC9B
P 6450 2000
F 0 "U101" H 6750 2050 50  0000 C CNN
F 1 "CC_XC6204" H 6750 1550 50  0000 C CNN
F 2 "SMD_Packages:SOT23-5" H 6450 2000 50  0001 C CNN
F 3 "" H 6450 2000 50  0000 C CNN
	1    6450 2000
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR01
U 1 1 55FECE72
P 5950 2700
F 0 "#PWR01" H 5950 2450 50  0001 C CNN
F 1 "GND" H 5950 2550 50  0000 C CNN
F 2 "" H 5950 2700 60  0000 C CNN
F 3 "" H 5950 2700 60  0000 C CNN
	1    5950 2700
	1    0    0    -1  
$EndComp
$Comp
L +3.3V #PWR02
U 1 1 55FECE8A
P 7400 2000
F 0 "#PWR02" H 7400 1850 50  0001 C CNN
F 1 "+3.3V" H 7400 2140 50  0000 C CNN
F 2 "" H 7400 2000 60  0000 C CNN
F 3 "" H 7400 2000 60  0000 C CNN
	1    7400 2000
	1    0    0    -1  
$EndComp
$Comp
L VCC #PWR03
U 1 1 55FECEA2
P 6150 2000
F 0 "#PWR03" H 6150 1850 50  0001 C CNN
F 1 "VCC" H 6150 2150 50  0000 C CNN
F 2 "" H 6150 2000 60  0000 C CNN
F 3 "" H 6150 2000 60  0000 C CNN
	1    6150 2000
	1    0    0    -1  
$EndComp
$Comp
L CC-C C101
U 1 1 55FECEBA
P 5950 2400
F 0 "C101" H 5950 2500 40  0000 L CNN
F 1 "1u/10V" H 5700 2300 40  0000 L CNN
F 2 "cc_rcl:rcl-cc-0603" H 5988 2250 30  0001 C CNN
F 3 "" H 5950 2400 60  0000 C CNN
	1    5950 2400
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR04
U 1 1 55FECF44
P 6150 2700
F 0 "#PWR04" H 6150 2450 50  0001 C CNN
F 1 "GND" H 6150 2550 50  0000 C CNN
F 2 "" H 6150 2700 60  0000 C CNN
F 3 "" H 6150 2700 60  0000 C CNN
	1    6150 2700
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR05
U 1 1 55FED037
P 7400 2700
F 0 "#PWR05" H 7400 2450 50  0001 C CNN
F 1 "GND" H 7400 2550 50  0000 C CNN
F 2 "" H 7400 2700 60  0000 C CNN
F 3 "" H 7400 2700 60  0000 C CNN
	1    7400 2700
	1    0    0    -1  
$EndComp
$Comp
L CC-C C102
U 1 1 55FED04B
P 7400 2400
F 0 "C102" H 7400 2500 40  0000 L CNN
F 1 "1u/10V" H 7150 2300 40  0000 L CNN
F 2 "cc_rcl:rcl-cc-0603" H 7438 2250 30  0001 C CNN
F 3 "" H 7400 2400 60  0000 C CNN
	1    7400 2400
	1    0    0    -1  
$EndComp
$Comp
L CC-C C106
U 1 1 55FED3F6
P 3800 4050
F 0 "C106" H 3800 4150 40  0000 L CNN
F 1 "2u2/6V" V 3750 4150 40  0000 L CNN
F 2 "cc_rcl:rcl-cc-0603" H 3838 3900 30  0001 C CNN
F 3 "" H 3800 4050 60  0000 C CNN
	1    3800 4050
	0    1    1    0   
$EndComp
$Comp
L GND #PWR06
U 1 1 55FED587
P 4100 4050
F 0 "#PWR06" H 4100 3800 50  0001 C CNN
F 1 "GND" H 4100 3900 50  0000 C CNN
F 2 "" H 4100 4050 60  0000 C CNN
F 3 "" H 4100 4050 60  0000 C CNN
	1    4100 4050
	0    -1   -1   0   
$EndComp
$Comp
L GND #PWR07
U 1 1 55FED74F
P 3600 5300
F 0 "#PWR07" H 3600 5050 50  0001 C CNN
F 1 "GND" H 3600 5150 50  0000 C CNN
F 2 "" H 3600 5300 60  0000 C CNN
F 3 "" H 3600 5300 60  0000 C CNN
	1    3600 5300
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR08
U 1 1 55FED769
P 2400 5300
F 0 "#PWR08" H 2400 5050 50  0001 C CNN
F 1 "GND" H 2400 5150 50  0000 C CNN
F 2 "" H 2400 5300 60  0000 C CNN
F 3 "" H 2400 5300 60  0000 C CNN
	1    2400 5300
	1    0    0    -1  
$EndComp
NoConn ~ 3500 3000
NoConn ~ 3500 3100
$Comp
L SW_PUSH SW101
U 1 1 55FEDDC1
P 9800 1100
F 0 "SW101" H 9950 1210 50  0000 C CNN
F 1 "SW_PUSH" H 9800 1020 50  0000 C CNN
F 2 "cc_switches:TASTER_3305B" H 9800 1100 60  0001 C CNN
F 3 "" H 9800 1100 60  0000 C CNN
	1    9800 1100
	1    0    0    -1  
$EndComp
$Comp
L SW_PUSH SW102
U 1 1 55FEDF2A
P 9800 1400
F 0 "SW102" H 9950 1510 50  0000 C CNN
F 1 "SW_PUSH" H 9800 1320 50  0000 C CNN
F 2 "cc_switches:TASTER_3305B" H 9800 1400 60  0001 C CNN
F 3 "" H 9800 1400 60  0000 C CNN
	1    9800 1400
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR09
U 1 1 55FEE094
P 10200 1100
F 0 "#PWR09" H 10200 850 50  0001 C CNN
F 1 "GND" H 10200 950 50  0000 C CNN
F 2 "" H 10200 1100 60  0000 C CNN
F 3 "" H 10200 1100 60  0000 C CNN
	1    10200 1100
	0    -1   -1   0   
$EndComp
$Comp
L GND #PWR010
U 1 1 55FEE0B4
P 10200 1400
F 0 "#PWR010" H 10200 1150 50  0001 C CNN
F 1 "GND" H 10200 1250 50  0000 C CNN
F 2 "" H 10200 1400 60  0000 C CNN
F 3 "" H 10200 1400 60  0000 C CNN
	1    10200 1400
	0    -1   -1   0   
$EndComp
Text GLabel 2400 3600 0    50   Input ~ 0
SWO
Text GLabel 2400 2900 0    50   Input ~ 0
JTMS
Text GLabel 2400 3000 0    50   Input ~ 0
JTCK
Text GLabel 3600 3800 2    50   Input ~ 0
nRST
$Comp
L CC_STM32SWD U104
U 1 1 55FEF8E0
P 6650 4300
F 0 "U104" H 6550 4750 60  0000 C CNN
F 1 "CC_STM32SWD" H 6650 3850 60  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x06" H 6750 4350 60  0001 C CNN
F 3 "" H 6750 4350 60  0000 C CNN
	1    6650 4300
	1    0    0    -1  
$EndComp
$Comp
L +3.3V #PWR011
U 1 1 55FEFA61
P 6200 3950
F 0 "#PWR011" H 6200 3800 50  0001 C CNN
F 1 "+3.3V" H 6200 4090 50  0000 C CNN
F 2 "" H 6200 3950 60  0000 C CNN
F 3 "" H 6200 3950 60  0000 C CNN
	1    6200 3950
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR012
U 1 1 55FEFD82
P 6200 4650
F 0 "#PWR012" H 6200 4400 50  0001 C CNN
F 1 "GND" H 6200 4500 50  0000 C CNN
F 2 "" H 6200 4650 60  0000 C CNN
F 3 "" H 6200 4650 60  0000 C CNN
	1    6200 4650
	1    0    0    -1  
$EndComp
Text GLabel 6100 4150 0    50   Input ~ 0
JTCK
Text GLabel 6100 4350 0    50   Input ~ 0
JTMS
Text GLabel 6100 4450 0    50   Input ~ 0
nRST
Text GLabel 6100 4550 0    50   Input ~ 0
SWO
Text GLabel 9400 1100 0    50   Input ~ 0
nRST
Text GLabel 9400 1400 0    50   Input ~ 0
USERBTN
Text GLabel 3600 2900 2    50   Input ~ 0
USERBTN
$Comp
L CC-XTAL-4P X101
U 1 1 55FF14C2
P 4350 3550
F 0 "X101" H 4350 3800 60  0000 C CNN
F 1 "12MHz" H 4350 3700 60  0000 C CNN
F 2 "cc_rcl:Q_EUROQUARTZ_MJ_3x5x1" H 4350 3550 60  0001 C CNN
F 3 "" H 4350 3550 60  0000 C CNN
	1    4350 3550
	0    -1   -1   0   
$EndComp
$Comp
L CC-C C105
U 1 1 55FF19DE
P 4650 3800
F 0 "C105" H 4650 3900 40  0000 L CNN
F 1 "12p" H 4656 3715 40  0000 L CNN
F 2 "cc_rcl:rcl-cc-0603" H 4688 3650 30  0001 C CNN
F 3 "" H 4650 3800 60  0000 C CNN
	1    4650 3800
	0    1    1    0   
$EndComp
$Comp
L CC-C C104
U 1 1 55FF1A97
P 4650 3300
F 0 "C104" H 4650 3400 40  0000 L CNN
F 1 "12p" H 4656 3215 40  0000 L CNN
F 2 "cc_rcl:rcl-cc-0603" H 4688 3150 30  0001 C CNN
F 3 "" H 4650 3300 60  0000 C CNN
	1    4650 3300
	0    1    1    0   
$EndComp
$Comp
L GND #PWR013
U 1 1 55FF1FCF
P 5050 3550
F 0 "#PWR013" H 5050 3300 50  0001 C CNN
F 1 "GND" H 5050 3400 50  0000 C CNN
F 2 "" H 5050 3550 60  0000 C CNN
F 3 "" H 5050 3550 60  0000 C CNN
	1    5050 3550
	0    -1   -1   0   
$EndComp
$Comp
L CC-C C107
U 1 1 55FF2A8C
P 3850 4700
F 0 "C107" H 3850 4800 40  0000 L CNN
F 1 "1u" H 3856 4615 40  0000 L CNN
F 2 "cc_rcl:rcl-cc-0603" H 3888 4550 30  0001 C CNN
F 3 "" H 3850 4700 60  0000 C CNN
	1    3850 4700
	1    0    0    -1  
$EndComp
$Comp
L CC-C C108
U 1 1 55FF2B3B
P 4100 4700
F 0 "C108" H 4100 4800 40  0000 L CNN
F 1 "100n" H 4106 4615 40  0000 L CNN
F 2 "cc_rcl:rcl-cc-0603" H 4138 4550 30  0001 C CNN
F 3 "" H 4100 4700 60  0000 C CNN
	1    4100 4700
	1    0    0    -1  
$EndComp
$Comp
L CC-C C109
U 1 1 55FF2B82
P 4350 4700
F 0 "C109" H 4350 4800 40  0000 L CNN
F 1 "100n" H 4356 4615 40  0000 L CNN
F 2 "cc_rcl:rcl-cc-0603" H 4388 4550 30  0001 C CNN
F 3 "" H 4350 4700 60  0000 C CNN
	1    4350 4700
	1    0    0    -1  
$EndComp
$Comp
L CC-C C110
U 1 1 55FF2BD0
P 4600 4700
F 0 "C110" H 4600 4800 40  0000 L CNN
F 1 "100n" H 4606 4615 40  0000 L CNN
F 2 "cc_rcl:rcl-cc-0603" H 4638 4550 30  0001 C CNN
F 3 "" H 4600 4700 60  0000 C CNN
	1    4600 4700
	1    0    0    -1  
$EndComp
$Comp
L CC-C C111
U 1 1 55FF2C92
P 4850 4700
F 0 "C111" H 4850 4800 40  0000 L CNN
F 1 "100n" H 4856 4615 40  0000 L CNN
F 2 "cc_rcl:rcl-cc-0603" H 4888 4550 30  0001 C CNN
F 3 "" H 4850 4700 60  0000 C CNN
	1    4850 4700
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR014
U 1 1 55FF2F14
P 3850 5300
F 0 "#PWR014" H 3850 5050 50  0001 C CNN
F 1 "GND" H 3850 5150 50  0000 C CNN
F 2 "" H 3850 5300 60  0000 C CNN
F 3 "" H 3850 5300 60  0000 C CNN
	1    3850 5300
	1    0    0    -1  
$EndComp
$Comp
L VAA #PWR015
U 1 1 55FF3638
P 4100 4200
F 0 "#PWR015" H 4100 4050 50  0001 C CNN
F 1 "VAA" H 4100 4350 50  0000 C CNN
F 2 "" H 4100 4200 60  0000 C CNN
F 3 "" H 4100 4200 60  0000 C CNN
	1    4100 4200
	0    1    1    0   
$EndComp
$Comp
L +3.3V #PWR016
U 1 1 55FF39F8
P 4850 4300
F 0 "#PWR016" H 4850 4150 50  0001 C CNN
F 1 "+3.3V" H 4850 4440 50  0000 C CNN
F 2 "" H 4850 4300 60  0000 C CNN
F 3 "" H 4850 4300 60  0000 C CNN
	1    4850 4300
	1    0    0    -1  
$EndComp
$Comp
L VAA #PWR017
U 1 1 55FF3BBA
P 5950 6600
F 0 "#PWR017" H 5950 6450 50  0001 C CNN
F 1 "VAA" H 5950 6750 50  0000 C CNN
F 2 "" H 5950 6600 60  0000 C CNN
F 3 "" H 5950 6600 60  0000 C CNN
	1    5950 6600
	1    0    0    -1  
$EndComp
$Comp
L CC-C C112
U 1 1 55FF3ECB
P 5950 7000
F 0 "C112" H 5950 7100 40  0000 L CNN
F 1 "100n" H 5956 6915 40  0000 L CNN
F 2 "cc_rcl:rcl-cc-0603" H 5988 6850 30  0001 C CNN
F 3 "" H 5950 7000 60  0000 C CNN
	1    5950 7000
	1    0    0    -1  
$EndComp
$Comp
L CC-L L101
U 1 1 55FF3FE6
P 6250 6700
F 0 "L101" V 6330 6700 40  0000 C CNN
F 1 "BEAD" V 6257 6701 40  0000 C CNN
F 2 "cc_rcl:rcl-cc-0603" V 6180 6700 30  0001 C CNN
F 3 "" H 6250 6700 30  0000 C CNN
	1    6250 6700
	0    1    1    0   
$EndComp
$Comp
L +3.3V #PWR018
U 1 1 55FF4065
P 6550 6600
F 0 "#PWR018" H 6550 6450 50  0001 C CNN
F 1 "+3.3V" H 6550 6740 50  0000 C CNN
F 2 "" H 6550 6600 60  0000 C CNN
F 3 "" H 6550 6600 60  0000 C CNN
	1    6550 6600
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR019
U 1 1 55FF40FC
P 5950 7300
F 0 "#PWR019" H 5950 7050 50  0001 C CNN
F 1 "GND" H 5950 7150 50  0000 C CNN
F 2 "" H 5950 7300 60  0000 C CNN
F 3 "" H 5950 7300 60  0000 C CNN
	1    5950 7300
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR020
U 1 1 55FF4F2C
P 4100 3900
F 0 "#PWR020" H 4100 3650 50  0001 C CNN
F 1 "GND" H 4100 3750 50  0000 C CNN
F 2 "" H 4100 3900 60  0000 C CNN
F 3 "" H 4100 3900 60  0000 C CNN
	1    4100 3900
	0    -1   -1   0   
$EndComp
$Comp
L LED D101
U 1 1 55FF556A
P 1700 2100
F 0 "D101" H 1700 2200 50  0000 C CNN
F 1 "LED_G" H 1700 2000 50  0000 C CNN
F 2 "LEDs:LED-0603" H 1700 2100 60  0001 C CNN
F 3 "" H 1700 2100 60  0000 C CNN
	1    1700 2100
	1    0    0    -1  
$EndComp
$Comp
L CC-R R103
U 1 1 55FF56E0
P 2200 2100
F 0 "R103" V 2150 2250 40  0000 C CNN
F 1 "470" V 2207 2101 40  0000 C CNN
F 2 "cc_rcl:rcl-cc-0603" V 2130 2100 30  0001 C CNN
F 3 "" H 2200 2100 30  0000 C CNN
	1    2200 2100
	0    1    1    0   
$EndComp
$Comp
L GND #PWR021
U 1 1 55FF5AC0
P 1400 2100
F 0 "#PWR021" H 1400 1850 50  0001 C CNN
F 1 "GND" H 1400 1950 50  0000 C CNN
F 2 "" H 1400 2100 60  0000 C CNN
F 3 "" H 1400 2100 60  0000 C CNN
	1    1400 2100
	0    1    1    0   
$EndComp
$Comp
L LED D102
U 1 1 55FF6559
P 7700 2900
F 0 "D102" H 7700 3000 50  0000 C CNN
F 1 "LED_R" H 7700 2800 50  0000 C CNN
F 2 "LEDs:LED-0603" H 7700 2900 60  0001 C CNN
F 3 "" H 7700 2900 60  0000 C CNN
	1    7700 2900
	0    -1   -1   0   
$EndComp
$Comp
L CC-R R109
U 1 1 55FF6AD9
P 7700 2400
F 0 "R109" V 7650 2550 40  0000 C CNN
F 1 "470" V 7707 2401 40  0000 C CNN
F 2 "cc_rcl:rcl-cc-0603" V 7630 2400 30  0001 C CNN
F 3 "" H 7700 2400 30  0000 C CNN
	1    7700 2400
	-1   0    0    1   
$EndComp
$Comp
L GND #PWR022
U 1 1 55FF6FC5
P 7700 3200
F 0 "#PWR022" H 7700 2950 50  0001 C CNN
F 1 "GND" H 7700 3050 50  0000 C CNN
F 2 "" H 7700 3200 60  0000 C CNN
F 3 "" H 7700 3200 60  0000 C CNN
	1    7700 3200
	1    0    0    -1  
$EndComp
Text GLabel 2400 3700 0    50   Input ~ 0
WS2811_DIN
$Comp
L CONN_01X02 P106
U 1 1 55FF8B4F
P 8300 5750
F 0 "P106" H 8300 5900 50  0000 C CNN
F 1 "CONN_01X02" V 8450 5750 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x02" H 8300 5750 60  0001 C CNN
F 3 "" H 8300 5750 60  0000 C CNN
	1    8300 5750
	1    0    0    -1  
$EndComp
$Comp
L CONN_01X03 P108
U 1 1 55FF8C7F
P 6750 5800
F 0 "P108" H 6750 6000 50  0000 C CNN
F 1 "CONN_01X03" V 6900 5800 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x03" H 6750 5800 60  0001 C CNN
F 3 "" H 6750 5800 60  0000 C CNN
	1    6750 5800
	1    0    0    -1  
$EndComp
Text GLabel 8000 5700 0    50   Input ~ 0
WS2811_DIN
$Comp
L GND #PWR023
U 1 1 55FF95DF
P 8000 5900
F 0 "#PWR023" H 8000 5650 50  0001 C CNN
F 1 "GND" H 8000 5750 50  0000 C CNN
F 2 "" H 8000 5900 60  0000 C CNN
F 3 "" H 8000 5900 60  0000 C CNN
	1    8000 5900
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR024
U 1 1 55FF963B
P 6450 6000
F 0 "#PWR024" H 6450 5750 50  0001 C CNN
F 1 "GND" H 6450 5850 50  0000 C CNN
F 2 "" H 6450 6000 60  0000 C CNN
F 3 "" H 6450 6000 60  0000 C CNN
	1    6450 6000
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR025
U 1 1 55FF9CCE
P 9150 4550
F 0 "#PWR025" H 9150 4300 50  0001 C CNN
F 1 "GND" H 9150 4400 50  0000 C CNN
F 2 "" H 9150 4550 60  0000 C CNN
F 3 "" H 9150 4550 60  0000 C CNN
	1    9150 4550
	1    0    0    -1  
$EndComp
$Comp
L VCC #PWR026
U 1 1 55FF9F93
P 9050 4150
F 0 "#PWR026" H 9050 4000 50  0001 C CNN
F 1 "VCC" H 9050 4300 50  0000 C CNN
F 2 "" H 9050 4150 60  0000 C CNN
F 3 "" H 9050 4150 60  0000 C CNN
	1    9050 4150
	1    0    0    -1  
$EndComp
Text GLabel 6450 5700 0    50   Input ~ 0
USART_TX
Text GLabel 6450 5800 0    50   Input ~ 0
USART_RX
$Comp
L CONN_01X02 P107
U 1 1 55FFC9C3
P 9600 5750
F 0 "P107" H 9600 5900 50  0000 C CNN
F 1 "CONN_01X02" V 9750 5750 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x02" H 9600 5750 60  0001 C CNN
F 3 "" H 9600 5750 60  0000 C CNN
	1    9600 5750
	1    0    0    -1  
$EndComp
Text GLabel 9300 5700 0    50   Input ~ 0
WS2811_DOUT
$Comp
L GND #PWR027
U 1 1 55FFC9CB
P 9300 5900
F 0 "#PWR027" H 9300 5650 50  0001 C CNN
F 1 "GND" H 9300 5750 50  0000 C CNN
F 2 "" H 9300 5900 60  0000 C CNN
F 3 "" H 9300 5900 60  0000 C CNN
	1    9300 5900
	1    0    0    -1  
$EndComp
$Comp
L CONN_01X02 P105
U 1 1 55FFE2C6
P 8300 5150
F 0 "P105" H 8300 5300 50  0000 C CNN
F 1 "CONN_01X02" V 8450 5150 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x02" H 8300 5150 60  0001 C CNN
F 3 "" H 8300 5150 60  0000 C CNN
	1    8300 5150
	1    0    0    -1  
$EndComp
Text GLabel 8000 5100 0    50   Input ~ 0
WS2811_DIN_AUX1
$Comp
L GND #PWR028
U 1 1 55FFE2CE
P 8000 5300
F 0 "#PWR028" H 8000 5050 50  0001 C CNN
F 1 "GND" H 8000 5150 50  0000 C CNN
F 2 "" H 8000 5300 60  0000 C CNN
F 3 "" H 8000 5300 60  0000 C CNN
	1    8000 5300
	1    0    0    -1  
$EndComp
$Comp
L CONN_01X02 P104
U 1 1 55FFE341
P 8300 4550
F 0 "P104" H 8300 4700 50  0000 C CNN
F 1 "CONN_01X02" V 8450 4550 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x02" H 8300 4550 60  0001 C CNN
F 3 "" H 8300 4550 60  0000 C CNN
	1    8300 4550
	1    0    0    -1  
$EndComp
Text GLabel 8000 4500 0    50   Input ~ 0
WS2811_DIN_AUX2
$Comp
L GND #PWR029
U 1 1 55FFE349
P 8000 4700
F 0 "#PWR029" H 8000 4450 50  0001 C CNN
F 1 "GND" H 8000 4550 50  0000 C CNN
F 2 "" H 8000 4700 60  0000 C CNN
F 3 "" H 8000 4700 60  0000 C CNN
	1    8000 4700
	1    0    0    -1  
$EndComp
Text GLabel 2400 3800 0    50   Input ~ 0
WS2811_DIN_AUX1
Text GLabel 2400 3300 0    50   Input ~ 0
WS2811_DIN_AUX2
Text GLabel 2400 3400 0    50   Input ~ 0
WS2811_DIN_AUX3
$Comp
L CONN_01X02 P102
U 1 1 5600042A
P 8300 4000
F 0 "P102" H 8300 4150 50  0000 C CNN
F 1 "CONN_01X02" V 8450 4000 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x02" H 8300 4000 60  0001 C CNN
F 3 "" H 8300 4000 60  0000 C CNN
	1    8300 4000
	1    0    0    -1  
$EndComp
Text GLabel 8000 3950 0    50   Input ~ 0
WS2811_DIN_AUX3
$Comp
L GND #PWR030
U 1 1 56000432
P 8000 4150
F 0 "#PWR030" H 8000 3900 50  0001 C CNN
F 1 "GND" H 8000 4000 50  0000 C CNN
F 2 "" H 8000 4150 60  0000 C CNN
F 3 "" H 8000 4150 60  0000 C CNN
	1    8000 4150
	1    0    0    -1  
$EndComp
$Sheet
S 6150 1050 1000 300 
U 560099FA
F0 "LEDS" 50
F1 "ws2812matrix_leds.sch" 50
F2 "MATRIX_DOUT" O R 7150 1150 50 
F3 "MATRIX_DIN" I L 6150 1250 50 
$EndSheet
Text GLabel 6050 1250 0    50   Input ~ 0
WS2811_DIN
Text GLabel 7250 1150 2    50   Input ~ 0
WS2811_DOUT
NoConn ~ 2500 1600
NoConn ~ 2500 1700
NoConn ~ 2500 2000
NoConn ~ 2500 2400
NoConn ~ 2500 3100
NoConn ~ 2500 3500
NoConn ~ 2500 3900
NoConn ~ 2500 4000
NoConn ~ 2500 4300
NoConn ~ 2500 4500
NoConn ~ 2500 4600
NoConn ~ 2500 4700
NoConn ~ 2500 4800
NoConn ~ 3500 3300
NoConn ~ 3500 2500
NoConn ~ 3500 2400
NoConn ~ 3500 2300
NoConn ~ 3500 2200
NoConn ~ 3500 2100
NoConn ~ 3500 2000
NoConn ~ 3500 1700
NoConn ~ 3500 1600
$Comp
L PWR_FLAG #FLG031
U 1 1 55FFD18F
P 8950 4350
F 0 "#FLG031" H 8950 4445 50  0001 C CNN
F 1 "PWR_FLAG" H 8950 4530 50  0000 C CNN
F 2 "" H 8950 4350 60  0000 C CNN
F 3 "" H 8950 4350 60  0000 C CNN
	1    8950 4350
	0    -1   -1   0   
$EndComp
$Comp
L PWR_FLAG #FLG032
U 1 1 55FFE16F
P 9150 3850
F 0 "#FLG032" H 9150 3945 50  0001 C CNN
F 1 "PWR_FLAG" H 9150 4030 50  0000 C CNN
F 2 "" H 9150 3850 60  0000 C CNN
F 3 "" H 9150 3850 60  0000 C CNN
	1    9150 3850
	1    0    0    -1  
$EndComp
$Comp
L PWR_FLAG #FLG033
U 1 1 56002566
P 5850 6700
F 0 "#FLG033" H 5850 6795 50  0001 C CNN
F 1 "PWR_FLAG" H 5850 6880 50  0000 C CNN
F 2 "" H 5850 6700 60  0000 C CNN
F 3 "" H 5850 6700 60  0000 C CNN
	1    5850 6700
	0    -1   -1   0   
$EndComp
$Comp
L CC-R R111
U 1 1 56195D4F
P 3800 2600
F 0 "R111" V 3750 2400 40  0000 C CNN
F 1 "n.b." V 3807 2601 40  0000 C CNN
F 2 "cc_rcl:rcl-cc-0603" V 3730 2600 30  0001 C CNN
F 3 "" H 3800 2600 30  0000 C CNN
	1    3800 2600
	0    1    1    0   
$EndComp
$Comp
L CC-R R112
U 1 1 56195E05
P 3800 2700
F 0 "R112" V 3750 2500 40  0000 C CNN
F 1 "0" V 3807 2701 40  0000 C CNN
F 2 "cc_rcl:rcl-cc-0603" V 3730 2700 30  0001 C CNN
F 3 "" H 3800 2700 30  0000 C CNN
	1    3800 2700
	0    1    1    0   
$EndComp
$Comp
L CC-R R113
U 1 1 56195EAD
P 3800 2800
F 0 "R113" V 3750 2600 40  0000 C CNN
F 1 "n.b." V 3807 2801 40  0000 C CNN
F 2 "cc_rcl:rcl-cc-0603" V 3730 2800 30  0001 C CNN
F 3 "" H 3800 2800 30  0000 C CNN
	1    3800 2800
	0    1    1    0   
$EndComp
$Comp
L GND #PWR034
U 1 1 56197BCA
P 4200 2700
F 0 "#PWR034" H 4200 2450 50  0001 C CNN
F 1 "GND" H 4200 2550 50  0000 C CNN
F 2 "" H 4200 2700 60  0000 C CNN
F 3 "" H 4200 2700 60  0000 C CNN
	1    4200 2700
	0    -1   -1   0   
$EndComp
Wire Wire Line
	7250 2100 7700 2100
Wire Wire Line
	7400 2000 7400 2200
Connection ~ 7400 2100
Wire Wire Line
	7400 2600 7400 2700
Wire Wire Line
	5950 2700 5950 2600
Wire Wire Line
	6150 2700 6150 2300
Wire Wire Line
	6150 2300 6250 2300
Wire Wire Line
	6150 2200 6250 2200
Wire Wire Line
	6150 2000 6150 2200
Wire Wire Line
	5950 2100 6250 2100
Connection ~ 6150 2100
Wire Wire Line
	5950 2100 5950 2200
Wire Wire Line
	3500 5000 3600 5000
Wire Wire Line
	3600 5000 3600 5300
Wire Wire Line
	3500 5200 3600 5200
Connection ~ 3600 5200
Wire Wire Line
	3500 5100 3600 5100
Connection ~ 3600 5100
Wire Wire Line
	2500 5000 2400 5000
Wire Wire Line
	2400 5000 2400 5300
Wire Wire Line
	2500 5100 2400 5100
Connection ~ 2400 5100
Wire Wire Line
	9400 1100 9500 1100
Wire Wire Line
	9400 1400 9500 1400
Wire Wire Line
	2400 3600 2500 3600
Wire Wire Line
	2400 2900 2500 2900
Wire Wire Line
	2400 3000 2500 3000
Wire Wire Line
	3600 3800 3500 3800
Wire Wire Line
	3500 4050 3600 4050
Wire Wire Line
	4000 4050 4100 4050
Wire Wire Line
	6300 4250 6200 4250
Wire Wire Line
	6200 4250 6200 4650
Wire Wire Line
	6300 4050 6200 4050
Wire Wire Line
	6200 4050 6200 3950
Wire Wire Line
	6100 4150 6300 4150
Wire Wire Line
	6100 4350 6300 4350
Wire Wire Line
	6100 4450 6300 4450
Wire Wire Line
	6100 4550 6300 4550
Wire Wire Line
	10100 1100 10200 1100
Wire Wire Line
	10100 1400 10200 1400
Wire Wire Line
	3500 2900 3600 2900
Wire Wire Line
	3500 3500 4000 3500
Wire Wire Line
	4000 3500 4000 3300
Wire Wire Line
	4000 3300 4450 3300
Wire Wire Line
	3500 3600 4000 3600
Wire Wire Line
	4000 3600 4000 3800
Wire Wire Line
	4000 3800 4450 3800
Wire Wire Line
	4850 3300 4950 3300
Wire Wire Line
	4950 3300 4950 3800
Wire Wire Line
	4950 3800 4850 3800
Wire Wire Line
	4550 3500 4950 3500
Connection ~ 4950 3500
Wire Wire Line
	4550 3600 4950 3600
Connection ~ 4950 3600
Wire Wire Line
	4950 3550 5050 3550
Connection ~ 4950 3550
Wire Wire Line
	4350 3400 4350 3300
Connection ~ 4350 3300
Wire Wire Line
	4350 3700 4350 3800
Connection ~ 4350 3800
Wire Wire Line
	3850 4900 3850 5300
Wire Wire Line
	3850 5000 4850 5000
Wire Wire Line
	4850 5000 4850 4900
Connection ~ 3850 5000
Wire Wire Line
	4600 4900 4600 5000
Connection ~ 4600 5000
Wire Wire Line
	4350 4900 4350 5000
Connection ~ 4350 5000
Wire Wire Line
	4100 4900 4100 5000
Connection ~ 4100 5000
Wire Wire Line
	3500 4400 4850 4400
Wire Wire Line
	4850 4300 4850 4500
Wire Wire Line
	4600 4400 4600 4500
Connection ~ 4600 4400
Wire Wire Line
	4350 4400 4350 4500
Connection ~ 4350 4400
Wire Wire Line
	4100 4400 4100 4500
Connection ~ 4100 4400
Wire Wire Line
	3850 4400 3850 4500
Connection ~ 3850 4400
Wire Wire Line
	3500 4500 3600 4500
Wire Wire Line
	3600 4400 3600 4800
Connection ~ 3600 4400
Wire Wire Line
	3600 4600 3500 4600
Connection ~ 3600 4500
Wire Wire Line
	3600 4700 3500 4700
Connection ~ 3600 4600
Wire Wire Line
	3600 4800 3500 4800
Connection ~ 3600 4700
Wire Wire Line
	3500 4200 4100 4200
Connection ~ 4850 4400
Wire Wire Line
	5950 7300 5950 7200
Wire Wire Line
	5950 6600 5950 6800
Wire Wire Line
	5850 6700 6050 6700
Connection ~ 5950 6700
Wire Wire Line
	6450 6700 6550 6700
Wire Wire Line
	6550 6700 6550 6600
Wire Wire Line
	3500 3900 4100 3900
Wire Wire Line
	2500 2100 2400 2100
Wire Wire Line
	2000 2100 1900 2100
Wire Wire Line
	1400 2100 1500 2100
Wire Wire Line
	7700 2100 7700 2200
Wire Wire Line
	7700 2600 7700 2700
Wire Wire Line
	7700 3100 7700 3200
Wire Wire Line
	2400 3700 2500 3700
Wire Wire Line
	8000 5700 8100 5700
Wire Wire Line
	6550 5900 6450 5900
Wire Wire Line
	6450 5900 6450 6000
Wire Wire Line
	6450 5700 6550 5700
Wire Wire Line
	6450 5800 6550 5800
Wire Wire Line
	8100 5800 8000 5800
Wire Wire Line
	8000 5800 8000 5900
Wire Wire Line
	9150 4450 9250 4450
Wire Wire Line
	9150 3850 9150 4550
Connection ~ 9150 4450
Wire Wire Line
	8950 4350 9250 4350
Wire Wire Line
	9050 4350 9050 4150
Wire Wire Line
	9300 5700 9400 5700
Wire Wire Line
	9400 5800 9300 5800
Wire Wire Line
	9300 5800 9300 5900
Wire Wire Line
	8000 5100 8100 5100
Wire Wire Line
	8100 5200 8000 5200
Wire Wire Line
	8000 5200 8000 5300
Wire Wire Line
	8000 4500 8100 4500
Wire Wire Line
	8100 4600 8000 4600
Wire Wire Line
	8000 4600 8000 4700
Wire Wire Line
	2400 3800 2500 3800
Wire Wire Line
	2500 3300 2400 3300
Wire Wire Line
	2500 3400 2400 3400
Wire Wire Line
	8000 3950 8100 3950
Wire Wire Line
	8100 4050 8000 4050
Wire Wire Line
	8000 4050 8000 4150
Wire Wire Line
	6050 1250 6150 1250
Wire Wire Line
	7150 1150 7250 1150
Connection ~ 9050 4350
Wire Wire Line
	4000 2600 4100 2600
Wire Wire Line
	4100 2600 4100 2800
Wire Wire Line
	4100 2800 4000 2800
Wire Wire Line
	4000 2700 4200 2700
Connection ~ 4100 2700
Wire Wire Line
	3500 2600 3600 2600
Wire Wire Line
	3500 2700 3600 2700
Wire Wire Line
	3500 2800 3600 2800
Text Notes 4450 2850 0    50   ~ 0
version setting resistors:\nR111 - bit0\nR112 - bit1\nR113 - bit2\n=> This is version 2.
$Comp
L CC-R R114
U 1 1 561B0C6B
P 1100 2550
F 0 "R114" V 1050 2350 40  0000 C CNN
F 1 "10k" V 1107 2551 40  0000 C CNN
F 2 "cc_rcl:rcl-cc-0603" V 1030 2550 30  0001 C CNN
F 3 "" H 1100 2550 30  0000 C CNN
	1    1100 2550
	0    1    1    0   
$EndComp
$Comp
L CC-R R115
U 1 1 561B0D4B
P 1650 2550
F 0 "R115" V 1600 2350 40  0000 C CNN
F 1 "10k" V 1657 2551 40  0000 C CNN
F 2 "cc_rcl:rcl-cc-0603" V 1580 2550 30  0001 C CNN
F 3 "" H 1650 2550 30  0000 C CNN
	1    1650 2550
	0    -1   -1   0   
$EndComp
$Comp
L CC-R R116
U 1 1 561B1259
P 1100 2650
F 0 "R116" V 1050 2450 40  0000 C CNN
F 1 "10k" V 1107 2651 40  0000 C CNN
F 2 "cc_rcl:rcl-cc-0603" V 1030 2650 30  0001 C CNN
F 3 "" H 1100 2650 30  0000 C CNN
	1    1100 2650
	0    1    1    0   
$EndComp
$Comp
L CC-R R117
U 1 1 561B130F
P 1650 2650
F 0 "R117" V 1600 2450 40  0000 C CNN
F 1 "10k" V 1657 2651 40  0000 C CNN
F 2 "cc_rcl:rcl-cc-0603" V 1580 2650 30  0001 C CNN
F 3 "" H 1650 2650 30  0000 C CNN
	1    1650 2650
	0    -1   -1   0   
$EndComp
$Comp
L GND #PWR035
U 1 1 561B2325
P 1950 2750
F 0 "#PWR035" H 1950 2500 50  0001 C CNN
F 1 "GND" H 1950 2600 50  0000 C CNN
F 2 "" H 1950 2750 60  0000 C CNN
F 3 "" H 1950 2750 60  0000 C CNN
	1    1950 2750
	1    0    0    -1  
$EndComp
Wire Wire Line
	1850 2550 1950 2550
Wire Wire Line
	1950 2550 1950 2750
Wire Wire Line
	1850 2650 1950 2650
Connection ~ 1950 2650
Wire Wire Line
	1300 2550 1450 2550
Wire Wire Line
	1300 2650 1450 2650
Wire Wire Line
	1350 2550 1350 2300
Wire Wire Line
	1350 2300 2400 2300
Wire Wire Line
	2400 2300 2400 2200
Wire Wire Line
	2400 2200 2500 2200
Connection ~ 1350 2550
Wire Wire Line
	1400 2650 1400 2350
Wire Wire Line
	1400 2350 2450 2350
Wire Wire Line
	2450 2350 2450 2300
Wire Wire Line
	2450 2300 2500 2300
Connection ~ 1400 2650
$Comp
L VCC #PWR036
U 1 1 561B3974
P 800 2450
F 0 "#PWR036" H 800 2300 50  0001 C CNN
F 1 "VCC" H 800 2600 50  0000 C CNN
F 2 "" H 800 2450 60  0000 C CNN
F 3 "" H 800 2450 60  0000 C CNN
	1    800  2450
	1    0    0    -1  
$EndComp
Wire Wire Line
	900  2550 800  2550
Wire Wire Line
	800  2450 800  2650
Wire Wire Line
	800  2650 900  2650
Connection ~ 800  2550
$Comp
L CONN_01X02 P103
U 1 1 5619DE3D
P 9450 4400
F 0 "P103" H 9450 4550 50  0000 C CNN
F 1 "CONN_01X02" V 9600 4400 50  0000 C CNN
F 2 "cc_con-lst:con-ria-TYPE_230_249_2PIN" H 9450 4400 60  0001 C CNN
F 3 "" H 9450 4400 60  0000 C CNN
	1    9450 4400
	1    0    0    -1  
$EndComp
$Comp
L CONN_01X02 P110
U 1 1 5619E20F
P 10100 4400
F 0 "P110" H 10100 4550 50  0000 C CNN
F 1 "CONN_01X02" V 10250 4400 50  0000 C CNN
F 2 "cc_con-lst:con-ria-TYPE_230_249_2PIN" H 10100 4400 60  0001 C CNN
F 3 "" H 10100 4400 60  0000 C CNN
	1    10100 4400
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR037
U 1 1 5619E2EB
P 9800 4550
F 0 "#PWR037" H 9800 4300 50  0001 C CNN
F 1 "GND" H 9800 4400 50  0000 C CNN
F 2 "" H 9800 4550 60  0000 C CNN
F 3 "" H 9800 4550 60  0000 C CNN
	1    9800 4550
	1    0    0    -1  
$EndComp
$Comp
L VCC #PWR038
U 1 1 5619E39E
P 9800 4250
F 0 "#PWR038" H 9800 4100 50  0001 C CNN
F 1 "VCC" H 9800 4400 50  0000 C CNN
F 2 "" H 9800 4250 60  0000 C CNN
F 3 "" H 9800 4250 60  0000 C CNN
	1    9800 4250
	1    0    0    -1  
$EndComp
Wire Wire Line
	9900 4450 9800 4450
Wire Wire Line
	9800 4450 9800 4550
Wire Wire Line
	9900 4350 9800 4350
Wire Wire Line
	9800 4350 9800 4250
NoConn ~ 3500 1900
NoConn ~ 3500 1800
NoConn ~ 2500 4200
NoConn ~ 2500 4100
$Comp
L CC-R R101
U 1 1 5777BC90
P 2200 1800
F 0 "R101" V 2150 1950 40  0000 C CNN
F 1 "100" V 2207 1801 40  0000 C CNN
F 2 "cc_rcl:rcl-cc-0603" V 2130 1800 30  0001 C CNN
F 3 "" H 2200 1800 30  0000 C CNN
	1    2200 1800
	0    1    1    0   
$EndComp
$Comp
L CC-R R102
U 1 1 5777BD28
P 2200 1900
F 0 "R102" V 2150 2050 40  0000 C CNN
F 1 "100" V 2207 1901 40  0000 C CNN
F 2 "cc_rcl:rcl-cc-0603" V 2130 1900 30  0001 C CNN
F 3 "" H 2200 1900 30  0000 C CNN
	1    2200 1900
	0    1    1    0   
$EndComp
Wire Wire Line
	2400 1800 2500 1800
Wire Wire Line
	2400 1900 2500 1900
Wire Wire Line
	2000 1800 1900 1800
Wire Wire Line
	1900 1900 2000 1900
Text GLabel 1900 1800 0    50   Input ~ 0
USART_TX
Text GLabel 1900 1900 0    50   Input ~ 0
USART_RX
Wire Wire Line
	2400 2800 2500 2800
Wire Wire Line
	2500 2700 2400 2700
Wire Wire Line
	2400 2600 2500 2600
Wire Wire Line
	2400 2500 2500 2500
Text GLabel 2400 2500 0    50   Input ~ 0
USB_VBUS
Text GLabel 2400 2600 0    50   Input ~ 0
USB_ID
Text GLabel 2400 2700 0    50   Input ~ 0
USB_D-
Text GLabel 2400 2800 0    50   Input ~ 0
USB_D+
$Comp
L CC-USB-MINIB-ASSMANN J101
U 1 1 57812E84
P 10150 2600
F 0 "J101" H 10100 3150 60  0000 C CNN
F 1 "USB-MINIB" V 9950 2650 60  0000 C CNN
F 2 "cc_con-usb:con-usb-USB-B-MINI-THD" H 10150 2600 60  0001 C CNN
F 3 "" H 10150 2600 60  0000 C CNN
	1    10150 2600
	-1   0    0    -1  
$EndComp
Wire Wire Line
	9550 2200 9650 2200
Wire Wire Line
	9550 2300 9650 2300
Wire Wire Line
	9550 2400 9650 2400
Wire Wire Line
	9550 2500 9650 2500
$Comp
L GND #PWR039
U 1 1 578133E2
P 9550 3000
F 0 "#PWR039" H 9550 2750 50  0001 C CNN
F 1 "GND" H 9550 2850 50  0000 C CNN
F 2 "" H 9550 3000 60  0000 C CNN
F 3 "" H 9550 3000 60  0000 C CNN
	1    9550 3000
	1    0    0    -1  
$EndComp
Wire Wire Line
	9650 2600 9550 2600
Wire Wire Line
	9550 2600 9550 3000
Wire Wire Line
	9650 2800 9550 2800
Connection ~ 9550 2800
Wire Wire Line
	9650 2900 9550 2900
Connection ~ 9550 2900
Text GLabel 9550 2200 0    50   Input ~ 0
USB_VBUS
Text GLabel 9550 2300 0    50   Input ~ 0
USB_D-
Text GLabel 9550 2400 0    50   Input ~ 0
USB_D+
Text GLabel 9550 2500 0    50   Input ~ 0
USB_ID
$EndSCHEMATC
