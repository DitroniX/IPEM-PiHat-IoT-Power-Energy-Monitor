Dave Williams, DitroniX 2019-2025 (ditronix.net)

**Development Code - WORK-IN-PROGRESS - NOT FINALASED!!!**

Initial Draft Release: 15th June 2025

### **Purpose of Code**

The purpose of this firmware code is to drive an IPEM PiHat, or IPEM PiHat Lite, Energy Monitoring Board from an ESP based MCU, rather than from a Raspberry Pi.

The code was developed essentially as an internal testing 'tool', which exercises the IPEM PiHat boards during R&D, bring up and testing.

**Development**

This code was developed and tested on the below hardware:

 - [IPEM PiHat](https://github.com/DitroniX/IPEM-PiHat-IoT-Power-Energy-Monitor), or [IPEM PiHat Lite](https://github.com/DitroniX/IPEM-PiHat-IoT-Power-Energy-Monitor)
 - [ESPuno Pi Zero](https://github.com/DitroniX/ESPuno-Pi-Zero_WiFi-BT-Zigbee-Thread-60V)

### **Top Level Overview**

This firmware is a work-in-progress stripped down and updated version of the original FLiX code that resides in https://github.com/DitroniX/FLIX-DitroniX-Power-Energy-Monitors-Firmware

The purpose of this test code is to cycle through the various main functions of the boards, as part of board bring up testing.

This code has expanded way past it's original IPEM bring-up task and is now quite comprehensive. It can now be, as is, used for both bring-up, final use and publishing.

A number of software switches are used, throughout. The defaults variables and switches are contained in config.h

**Energy Monitoring Board**

The FLiX firmware core driver is for the [Atmel  ATM90E36](https://www.microchip.com/en-us/product/atm90e36a), which is a High Performance and Accurate Mains Energy Monitoring device, as used on the IPEM Series of IoT Power Energy Monitor SDK boards.

Communications to the ATM90E36 is via SPI.   This firmware allows SPI Chip Select via either GPIO from the ESP32-C6, or software control via the GPIO Expander.  The [IPEM PiHat configuration](https://github.com/DitroniX/IPEM-PiHat-IoT-Power-Energy-Monitor/wiki/DIP-Switch-Configuration) being used to control this.

**Modules**

The firmware currently incorporates the following 'modules'

 - Main
	 - Hardware
 - [Devices](https://github.com/DitroniX/IPEM-PiHat-IoT-Power-Energy-Monitor/wiki/Devices)
	 - ATM90E36 (Energy Monitoring)
	 - [PCA9671](https://github.com/DitroniX/IPEM-PiHat-IoT-Power-Energy-Monitor/wiki/GPIO-Configuration-%E2%80%90-IPEM-PiHat) (I2C GPIO Expander)
	 - OLED (Driver for SSD1306 I2C Display - Default 0.96")
	 - TMP102 (I2C Temperature Sensor)
	 - DS3231 (I2C RTC)
	 - ADS1115 (I2C ADC)
	 - 24C64 (EEPROM)
 - Publishing
	 - Wi-Fi
		 - MQTT
		 - Domoticz

### **Compiling and Flashing**
This code has been developed within the Microsoft VS Code and [Platform IO](https://github.com/DitroniX/ESPuno-Pi-Zero_WiFi-BT-Zigbee-Thread-60V/wiki/PlatformIO-Configuration) environment IDE.

**Files**

The *platformio.ini* contains the configuration for the ESP32-C6 based ESPuno Pi Zero board, along with the prerequisite third party library dependencies.

The *config.h* contains the main user variables, software switches and configuration parameters

**Logging**
A comprehensive serial log output is included in the firmware.  Examples are included in the root of the code folder.



  ### **Configuration**

This version of firmware code has the setups for bring-up testing of the board:  

- AUTO Configuration of IPEM PiHat ATM90E36 variant:
	- IPEM PiHat
	- IPEM PiHat Lite
- Connected to an ESPuno Pi Zero ESP32-C6 MCU

- DIP Switches configured as per [Defaults](https://github.com/DitroniX/IPEM-PiHat-IoT-Power-Energy-Monitor/wiki/DIP-Switch-Configuration#dip-switch-defaults-for-local)

- Multi-Voltage Input (ATM_SINGLEVOLTAGE true)

- Split-Phase USA - Disabled (ATM_SPLITPHASE false)

- Display of Board Configuration (EnableDisplayBoardConfiguration true)

- Loop Refreshing Terminal Output (EnableBasicLoop false) - Display Info ONCE uppon Reset.

- Value Outputs are filtered through a Software Noise Filter / Comparator / Squelch (EnableNoiseFilterSquelch true)

- OLED 0.96" Display SSD1306 128x32. (EnableOLEDLoop true)

- Board Location and Firmware Version to OLED and Serial Monitor

- Wi-Fi (DisableWiFi false) Requires SSID/PWD to auto enable

- MQTT Publishing - Disabled (EnableMQTT false)

- Domoticz Publishing - Disabled (EnableDomoticz false)

- IP Address Defaults to DHCP. Static IP Address Configuration in WiFi-OTA.h

### **Calibration**

This version of firmware has been designed to reduce to a minimum calibration of the ATM90E36.

**[Mains Sense Input](https://github.com/DitroniX/IPEM-PiHat-IoT-Power-Energy-Monitor/wiki/AC-Mains-Voltage-Sense-Input)**

A 50Hz or 60Hz sense signal is required in order to synchronise with the signals from the CT Clamps.  This signal is fed into the IPEM boards via a low voltage AC signal (8 to 12V AC RMS), which is typically provided, for safety reasons, via SELV mains transformer.

Most users use a Bell Transformer, such as a GreenBrook DAT01A. or TLC TC TR7. You could use a 'wall wart' type power supply but this MUST be an AC _transformer _type and NOT a switched mode.

Voltages default calculation settings are based on Single/Three Phase Voltage Inputs from a Greenbrook DAT01A (TC TR7) Transformer, set to 12V AC.

**[Current Clamps](https://github.com/DitroniX/IPEM-PiHat-IoT-Power-Energy-Monitor/wiki/Current-Clamps)**

Current measurements are taken from sensors called Current Clamps.  These can be either Current Transformer (CT), Clamps, and/or Rogowski Current Transformers.

- Current Clamp default example settings are based on SCT-013-000 100A/50mA.

- Current Clamps CT1, CT2 and CT3 are connected to the ATM90E36. Calibration requirements should be minimal and board ready to use.

- AC Voltage Inputs V1, V2 and V3 are connected to the ATM90E36. Calibration requirements should be minimal and board ready to use.

- Current Clamp CT4 is only needed when measuring Three-phase four-wire (3P4W, Y0), installations.
  

**WiFi and OTA Updates**

- Setup WiFi

- Configure Multi-WiFi SSID/PWD

- Setup Optional Static IP address and Gateway (DHCP or Static)

- Setup Preferred Hostname

- Setup Serial Device over IP (Used for OTA)

- Display WiFI Signal Meter

**MQTT**

- Setup connection to MQTT Broker / Home Automation

- Configure Required Values to Publish to MQTT Broker
  

**DOMOTICZ**

- Setup connection to Domoticz Home Automation

- Configure Required Values to Publish to Domoticz Hardware Device Indexes

- When Publishing to Domoticz - Mute Detailed Output to Serial (Loop)

  



  

Enjoy! Dave Williams, DitroniX.net

  

**Remember!**

  

- Set the BOARD to ESP32, 'WEMOS D1 MINI ESP32' DEV Module (or similar).

- You may set the BAUD rate to 921600 to speed up flashing.

- The SDK board does NOT need external power to flash. It will take Power from the USB 5V.

- You can safely connect both USB Power and PSU AC In, at the sme time (Makes development much easier).

  

**Other Notes**

  

In the default state, upon first power up and during reset, the Green LED may be partially lit. Once programmed and the GPIO defined, the Green LED will go off after power up.

  

This test code is OPEN SOURCE and formatted for easier viewing. Although is is not intended for real world use, it may be freely used, or modified as needed.

  

It is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.

  

**Wiki and Code Examples**

  

Further information, details and code examples can be found on our wiki pages on github.com/DitroniX

  

- https://github.com/DitroniX
- https://github.com/DitroniX/IPEM-PiHat-IoT-Power-Energy-Monitor
- https://github.com/DitroniX/IPEM-PiHat-IoT-Power-Energy-Monitor/wiki
- https://github.com/DitroniX/ESPuno-Pi-Zero_WiFi-BT-Zigbee-Thread-60V
- https://github.com/DitroniX/ESPuno-Pi-Zero_WiFi-BT-Zigbee-Thread-60V/wiki
- https://github.com/DitroniX/PGEZ-PCA9671-GPIO-Expander-Zero/wiki

 
### **Acknowledgements**


Base 90E32/36 register formulation is based on the original excellent ground work from Tisham Dhar, whatnick \| ATM90E36 Energy Monitor Core. This then being adapted over time where needed.
 

FLiX main VSCode / Platform IO base, E36 Registers/Code Merged, Adapted, Updated, Software Logic/Routines, Bring Up Firmware, Comprehensive Functions and Wi-Fi integration such as OTA, Domoticz Integration etc. by Date Williams