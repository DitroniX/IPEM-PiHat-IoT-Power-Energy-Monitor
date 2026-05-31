/*
  Dave Williams, DitroniX 2019-2025 (ditronix.net)
  Full header information in README

  This test code is OPEN SOURCE and formatted for easier viewing.  Although is is not intended for real world use, it may be freely used, or modified as needed.
  It is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.

  Further information, details and examples can be found on our website ditronix.net, github.com/DitroniX and hackster.io/DitroniX
*/

Example Terminal Output with Resistive Load and 247V AC Input (Via 12V AC transformer)

Note: Remember to change the ESPuno Pi Zero default PCA9671 I2C Address to 0x10 (or other), otherwise it may conflict with the default IPEM PiHat PCA9671 address.

**************************************************************************************

FliX IPEM PiHat Series - Integrated Firmware for DitroniX Power Energy Monitor SDK Boards

Scanning and Configuring Board.. Please Wait..

Hardware Options and Auto Configuration
────────────────────────────────────────
Scanning I2C Bus for Devices for Auto Configuration ...
 I2C Possible Device(s) found at Address:
 * Hex 0x10 (16)         PCA9671 GPIO Expander
 * Hex 0x20 (32)         PCA9671 GPIO Expander (Default)
 * Hex 0x3C (60)         OLED
 * Hex 0x4A (74)         TMP102 Temperature Sensor IPEM PiHat
 * Hex 0x4B (75)         ADS1115 16-bit ADC IPEM PiHat
 * Hex 0x50 (80)         EEPROM ESPuno Pi Zero
 * Hex 0x55 (85)         EEPROM IPEM PiHat
 * Hex 0x58 (88)         EEPROM ESPuno Pi Zero (Reserved Address)
 * Hex 0x60 (96)         MCP4728 12-bit DAC IPEM PiHat
 * Hex 0x68 (104)        DS3231 RTC IPEM PiHat
 * Hex 0x7C (124)        PCA9671 GPIO Expander (Reserved Address)
 I2C Bus Scan Complete

Detected: IPEM PiHat ATM90E36 IoT Power Energy Monitor
Hardware Setup and Power-Up Test

IPEM PiHat Register Status and Startup Report
──────────────────────────────────────────────
ESP32 Serial ID: 84FEFF23B3E4
FliX Firmware Version: 250614
Board Location: R&D Test

EEPROM Check: FFFF

ADC (ADS1115) Initialised

AIN0: 3099  0.58V
AIN1: 3104  0.58V
AIN2: 3102  0.58V
AIN3: 3105  0.58V


Initialising OLED Display
OLED Display Initialised
Temperature Sensor (TMP102) Initialised

TMP102 Temperature: 28.56 °C

Hardware RTC (DS3231) Initialised
Setting:
0-1-1 1:21:0

PCA9671 Software Reset
PCA9671 Full Software Reset with Pull Ups
PCA9671 Default Pin State
Testing RGB LED
Testing Relays

Wi-Fi Options
──────────────
Wi-Fi is Disabled
MQTT Publishing is Disabled
Domoticz Publishing is Disabled

Software Options
─────────────────
Connecting to the ATM90E36
ATM90E36 SPI Control Using GPIO Expander for /CS

ATM90E36 Registers Updated

Hardware Setup and Power-Up Test - Board Initialized
Register Status and Diagnostic Report
ESP32 Serial ID: 84FEFF23B3E4
Firmware Version: 250614
Location: R&D Test

Hardware Configuration for ATM90E36
────────────────────────────────────
AC Voltage Inputs:      Single Input V1 will be used for Current Phase Calculations
Split AC Voltage:       Dual or Split Voltage Input Disabled
CT Current Clamps:      Configured for 1, 2, 3 Phase

[ATM90E36 Status Register Values]
System Status:          S0:0xC0         S1:0x0
Meter Status:           E0:0x5          E1:0x0

ATM90E36 Connected - Communication Successful

Mains RMS Voltage
──────────────────
- - - - - - - - - - - - - - - - - - - - - - - - - - -
Voltage 1: 245.16 V (Single Line Voltage Selected)

Mains RMS Current
──────────────────
Current CT1: 1.38 A
Current CT2: 1.38 A
Current CT3: 1.37 A
- - - - - - - - - - - - - - - - - - 
Accumulative Current CTN: 4.13 A
- - - - - - - - - - - - - - - - - - - - - - -
Actual Total Current: 4.13 A (CT1~CT2~CT3)

Calculated RMS Power
─────────────────────
Power V1*I1: 338.32 W   0.34 kW
Power V1*I2: 338.32 W   0.34 kW
Power V1*I3: 335.87 W   0.34 kW
- - - - - - - - - - - - - - - - - - - - - - - - -
Calculated Total Power: 1012.04 W (CT1~CT2~CT3)

Active Power (Absorbed or Used by the Load)
────────────────────────────────────────────
Active Power CT1: -0.34 kW      (Export)
Active Power CT2: -0.34 kW      (Export)
Active Power CT3: -0.34 kW      (Export)
- - - - - - - - - - - - - - - - - - - - -
Total Active Power: -0.68 kW    (Export)
- - - - - - - - - - - - - - - - - - - - - - - - - - - -
Calculated Total Active Power: -1.02 W (CT1~CT2~CT3)

Re-Active Power
────────────────
ReActive Power CT1: 0.00 VAR
ReActive Power CT2: 0.00 VAR
ReActive Power CT3: 0.00 VAR
- - - - - - - - - - - - - - - - - - - - - - - - 
Total ReActive Power: -0.04 VAR (CT1~CT2~CT3)
- - - - - - - - - - - - - - - - - - - - - - - - - - - -
Calculated Total Reactive Power: 0.00 W (CT1~CT2~CT3)

Apparent Power (Total Amount of Power Flowing from Source to Load)
───────────────────────────────────────────────────────────────────
Apparent Power CT1: 0.34 VA
Apparent Power CT2: 0.34 VA
Apparent Power CT3: 0.34 VA
- - - - - - - - - - - - - - - - - - - - - - -
Total Apparent Power: 0.67 VA (CT1~CT2~CT3)
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
Calculated Total Apparent Power: 1.02 VA (CT1~CT2~CT3)


Power Factor
─────────────
Power Factor CT1: 0.00 PF
Power Factor CT2: 0.00 PF
Power Factor CT3: 0.00 PF
- - - - - - - - - - - - - - -
Total Power Factor: 0.00 PF

Phase Angle
────────────
Phase Angle CT1: 0.00
Phase Angle CT2: 0.00
Phase Angle CT3: 0.00

Voltage Harmonics
──────────────────
Voltage Harmonics CT1: 0.00
Voltage Harmonics CT2: 0.00
Voltage Harmonics CT3: 0.00

Current Harmonics
──────────────────
Current Harmonics CT1: 0.00
Current Harmonics CT2: 0.00
Current Harmonics CT3: 0.00

Other Information
──────────────────
Chip Temperature: 23.00 °C

Mains Frequency: 49.91 Hz

TMP102 Temperature: 28.06 °C