/*
  Dave Williams, DitroniX 2019-2025 (ditronix.net)
  Full header information in README

  Further information, details and examples can be found on our website and also GitHub wiki pages:
  * ditronix.net
  * github.com/DitroniX
  * github.com/DitroniX/ESPuno-Pi-Zero_WiFi-BT-Zigbee-Thread-60V
  * github.com/DitroniX/ESPuno-Pi-Zero_WiFi-BT-Zigbee-Thread-60V/wiki
  * hackster.io/DitroniX/espuno-pi-zero-wifi-bt-zigbee-thread-60v-69ef92
  * kickstarter.com/projects/ditronix/espuno-pi-zero

  This test code is OPEN SOURCE and formatted for easier viewing.  Although is is not intended for real world use, it may be freely used, or modified as needed.
  It is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.

  For board configuration, see https://github.com/DitroniX/ESPuno-Pi-Zero_WiFi-BT-Zigbee-Thread-60V/wiki/Arduino-IDE

  Further information, details and examples can be found on our website wiki pages ditronix.net/wiki and also github.com/DitroniX
*/

#ifndef CONFIG_H
#define CONFIG_H

// Libraries
#include <Arduino.h>

// ****************  GLOBAL VARIABLES / DEFINES / STATIC / STRUCTURES / CONSTANTS ****************

// ################################ Main ################################

// Application
const String AppVersion = "260530"; // Internal Firmware Date Code

// Version Check - Automatic Selection
String AppName;                   // App Name - Do Not Change
String AppAcronym = "IPEM PiHat"; // Board Acronym - Do Not Change

// App USER
const String LocationName = "R&D Test"; // Enter Name Location of Device such as House, Solar etc.  Used for Serial Monitor and OLED.

// Constants USER
const int AverageSamples = 25;                 // Average Multi-Samples within Calculate Average Value and Reduce Jitter.  Default 25
const int AverageDelay = 20;                   // Average Multi-Sample Delay within Calculate Average Value and Reduce Jitter. Default 20
const boolean EnableAveraging = true;          // Set to true to enable averaging (ESP32 DCV) within Calculate Average Value and Reduce Jitter.  Default true
const boolean EnableNoiseFilterSquelch = true; // This realtes to NoiseFilterSquelch Threshold.  false returns raw values.  Default true.

// Constants USER
const int LoopDelay = 1; // Loop Delay in Seconds

// ################################ Defaults ################################

boolean EnableSummaryInfo = true;               // Set to true to display, in Serial Monitor, Summary readings and displaying only one per reset cycle.  Default false.
boolean EnableBasicLoop = false;                 // Set to true to display, in Serial Monitor, loop readings and displaying only one per reset cycle.  Default true.
boolean EnableDisplayBoardConfiguration = false; // Set to true to display, in Serial Monitor, board software configuration Information if DisplayFull is true. Default true.

// ################################ System Defaults ################################

// Board Auto Configuration - Automatic Selection on I2C Scan - Do Not Change
boolean EnableATM = false;    // ATM90E36 - Do Not Change
boolean EnableEEPROM = false; // EEPROM - Do Not Change
boolean EnableDAC = false;    // MCP7428 DAC - Do Not Change
boolean EnableADC = false;    // ADS1115 ADC - Do Not Change
boolean EnableTMP = false;    // TMP102 - Do Not Change
boolean EnablePCA = false;    // PCA9671 - Do Not Change
boolean EnableRTC = false;    // DS3231 - Do Not Change

// ################################ I2C Configuration ################################

#define I2C_SDA 06 // Default 06 (C6) 21 (32)
#define I2C_SCL 07 // Default 07 (C6) 22 (32)
#define I2C_SPEED 100000 // Default 100 kHz = 100000.  Faster option 400 kHz = 400000

// ################################ SPI Configuration ################################

#define WRITE 0 // WRITE SPI // Default 0
#define READ 1  // READ SPI // Default 1

#define MISO 20 // SPI MISO // Default 20 (C6) 19 (32)
#define MOSI 18 // SPI MOSI // Default 18 (C6) 23 (32)
#define SCLK 19 // SPI SCLK // Default 19 (C6) 18 (32)

// Hardware SPI /CS1  (Set to 0 to disable hardware /CS and use GPIO Expander /CS Software Control)
#define CS_GPIO 14 // Default 14 (C6) 5 (32)
// Remember: If changing the /CS - Please check the DIP switch setting is correct on the IPEM PiHat, or IPEM PiHat Lite, Board

// ################################ ADS1115 ADC Configuration ################################

#define IPEM_ADS1115 0x4B // Default 0x4B - ADS1115 Address

// ################################ PCA9671 GPIO Expander Configuration ################################

// Define I2C (Addresses)
#define I2C_Address_EPZ 0x20 // ESPuno Pi Zero PCA9671 (0x20 Default - Avoid Conflicts)

// Just switch ON A1.  All the reset should be OFF
#define I2C_Address_IPH 0x21 // IPEM PiHat PCA9671 (0x10 or 0x21 Default - Set Switch - Avoid Conflicts)


// **************** PCA9671 INPUTS ****************
#define ATM_WO 0      // P00 - ATM Warning Out - Normally Low
#define ATM_IRQ0 1    // P01 - ATM IRQ Out - Normally Low
#define ATM_IRQ1 2    // P02 - ATM IRQ Out - Normally Low
#define User_Pad1 5   // P05 - User Solder Pad - Normally High
#define User_Pad2 6   // P06 - User Solder Pad - Normally High
#define User_Button 7 // P07 - User Button - Normally High

// **************** PCA9671 OUTPUTS ****************
#define ATM_PM0 3       // P03 - ATM Power Mode Select
#define ATM_PM1 4       // P04 - ATM Power Mode Select
#define ATM_RESET 8     // P10 - ATM Hardware Reset - Pending SW10 Settings
#define ATM_CS 9        // P11 - ATM SPI Chip Select - Pending SW10 Settings
#define ATM_DMA_CTRL 10 // P12 - ATM DMA Control - Pending SW10 Settings
#define LED_Blue 11     // P13 - Blue LED
#define LED_Red 12      // P14 - Red LED
#define LED_Green 13    // P15 - Green LED
#define Relay1 14       // P16 - Relay 1 (Not on IPEM PiHat Lite)
#define Relay2 15       // P17 - Relay 2 (Not on IPEM PiHat Lite)

#define PCA_RST 24 // GP24 - PCA9671 Hardware Reset (PCA_RST) - REDEFINED WIP

// ################################ ATM90E36 CALIBRATION SETTINGS GUIDE ################################

// LineFreq = 389 for 50 Hz (World)  4485 for (North America)
// VoltageGain = Depends on Transformer used for Voltage Isolation.  Below values are based on Greenbrook DAT01A (TC TR7) Transformer, set to 12V AC.  https://www.tlc-direct.co.uk/Products/TCTR7.html
// CurrentGainCTx = Depends on CT Clamps Used.  You can sue different on each channel is needed.  Below based on SCT-013-000 100A/50mA

// The below related to calibration of Voltage inputs (V1, V2 and V3), also Current Clamp inputs (CT1, CT2 and CT3 only).

// Mains Frequency
unsigned short LineFreq = 389; // MMode0 0x33 _lineFreq | 389

// Voltage and Current - Overall Gain
// PMPGA 0x17              DDV3V2V1I4I3I2I1  // D = DPGA       4/3/2/1 = V1-4 = I1-4
unsigned short PGAGain = 0b0101010101010101; // PMPGA 0x17  | DPGA Gain = 2 and PGA Gain = 1

// Voltage.
// This is calculated based on the DAT01 on 12V setting @ ~19V RMS.  Need to allow for +/- ~ 1% Tolerance.
// Calculations: Base value for 240V is 20200.  To increase/decrease change by Approx. ~100 per 1.0 V RMS.
// Calculations: Base value for 120V is 9700.  To increase/decrease change by Approx. ~100 per 1.0 V RMS.
#if ATM_SINGLEVOLTAGE == true
unsigned short VoltageGain1 = 20200;        // uGain = UgainA | 20200 Default Starting Value
unsigned short VoltageGain2 = VoltageGain1; // Duplicate V1 Values to V2 and V3.
unsigned short VoltageGain3 = VoltageGain1; // Duplicate V1 Values to V2 and V3.
#else
unsigned short VoltageGain1 = 20200; // uGain = UgainA | 20200 Default Starting Value
unsigned short VoltageGain2 = 20200; // uGain = UgainB | 20200 Default Starting Value
unsigned short VoltageGain3 = 20200; // uGain = UgainC | 20200 Default Starting Value
#endif

// Current
// This is calculated based on the YDH? 100A/50mA  Need to allow for +/- ~ 1% Tolerance.  Trim values are fine!
// Calculations: Base value for CT100/50 Mid Range 33500.  To increase/decrease change by Approx. ~500 per 0.01A RMS
unsigned short CurrentGainCT1 = 33500; // IgainA 0x62
unsigned short CurrentGainCT2 = 33500; // IgainA 0x65
unsigned short CurrentGainCT3 = 33500; // IgainA 0x6A
unsigned short CurrentGainCTN = 33500; // IgainA 0x6E

// ################################ MCU Auto Reboot ################################

// 0 reset disabled
// 300000UL call reset every 300 seconds (5 Minutes)
// 3600000UL call reset every 60 mins (1 Hour)
// 86400000UL call reset every 24 hours (1 Day)
// 604800000UL call reset every 7 days (1 Week).
// 2592000000UL call reset every 30 days (1 Month)

time_t RebootTime = 604800000UL; // Configure as needed.

// ################################ WiFi ################################

// WiFi.  Setup with your Wireless Information.  Add more as needed.
const char *ssid1 = "";     // WiFi Network SSID - Case Sensitive
const char *password1 = ""; // WiFi Network password - Case Sensitive
const char *ssid2 = "";     // WiFi Network SSID - Case Sensitive
const char *password2 = ""; // WiFi Network password - Case Sensitive
const char *ssid3 = "";     // WiFi Network SSID - Case Sensitive
const char *password3 = ""; // WiFi Network password - Case Sensitive

// WiFi. Force Disable for Testing.  !!!!! BEWARE Outside of Local Developmet Do NOT Disable as OTA will NOT work !!!!!
const boolean DisableWiFi = false; // Force Disable WiFi for Local USB Development and Testing Only.  You can leave SSID/IP etc populated.

// Set your Static IP address and Gateway - Alternatively leave at (0, 0, 0, 0)
IPAddress local_IP(0, 0, 0, 0);     // Leave at (0, 0, 0, 0) if DHCP required
IPAddress gateway(0, 0, 0, 0);      // Set to your Router IP = Gateway
IPAddress subnet(255, 255, 255, 0); // Should not need to change subnet from default (255, 255, 255, 0)

// Optional DNS Defaults.
IPAddress primaryDNS(0, 0, 0, 0);   // Defaults to your above Gateway IP if left as (0, 0, 0, 0)
IPAddress secondaryDNS(8, 8, 4, 4); // For Google Public DNS use for Primary or Secondary (8,8,8,8) and/or (8,8,4,4)

// ################################ MQTT Configuration ################################

// Setup with your MQTT Configration
const char *MQTTServer = "0.0.0.0"; // MQTT Server IP Address (Typically a Fixed Local Address)
int MQTTPort = 1883;                // MQTT Network Port (Default 1883)
const char *MQTTUser = "";          // MQTT User - if applicable
const char *MQTTPassword = "";      // MQTT Password - if applicable
String MQTTTopicMain = "ipem";      // MQTT Default Topic. Exclude the trailing /

// Enable Publishing
boolean EnableMQTT = true;         // Change to true, to enable Loop reading and sending data to MQTT.  Default false.
boolean EnableMQTTCallBack = true; // Under Development

// ################################ Domoticz Configuration ################################

// Domoticz Server info.  Setup with your Domoticz IP and Port
const char *DomoticzServer = "0.0.0.0"; // Domoticz Server IP Address (Typically a Fixed Local Address)
int DomoticzPort = 8080;                // Domoticz Network Port (Default 8080)
const char *Domoticz_User = "";         // Domoticz User - if applicable  (Not currently implimented in the connection)
const char *Domoticz_Password = "";     // Domoticz Password - if applicable  (Not currently implimented in the connection)

// Enable Publishing
boolean EnableDomoticz = false; // Change to true, to enable Loop reading and sending data to Domoticz.  Default false.

// Domoticz Hardware Device Indexes

// Set these values to the Domoticz Devices Indexes (IDX).  If Zero, then entry is ignored. A device first needs to be created in Domoticz, then use related IDX here.
int idxLineVoltage1 = 0;       // LineVoltage1 - Urms - Line 1 Voltage RMS
int idxLineVoltage2 = 0;       // LineVoltage2 - Urms - Line 2 Voltage RMS
int idxLineVoltage3 = 0;       // LineVoltage3 - Urms - Line 3 Voltage RMS
int idxLineVoltageAverage = 0; // LineVoltageAverage - Urms - Line Average Voltage RMS (V1+V2+V3/3)
int idxLineVoltageTotal = 0;   // LineVoltageTotal - Urms - Line Voltage Total RMS (V1+0+V3)

int idxLineCurrentCT1 = 0;   // LineCurrentCT1 - Irms - Line 1 Current RMS
int idxLineCurrentCT2 = 0;   // LineCurrentCT2 - Irms - Line 2 Current RMS
int idxLineCurrentCT3 = 0;   // LineCurrentCT3 - Irms - Line 3 Current RMS
int idxLineCurrentCT4 = 0;   // LineCurrentCT4 - Irms - Line 4 Current RMS (ESP)
int idxLineCurrentCTN = 0;   // LineCurrentCTN - Irms - Line N Current RMS
int idxLineCurrentTotal = 0; // LineCurrentTotal - Irms - Line Total Current RMS (CT1+CT2+CT3+(CT4))

int idxCalculatedPowerCT1 = 0;   // Calculated Power V*A Watts RMS
int idxCalculatedPowerCT2 = 0;   // Calculated Power V*A Watts RMS
int idxCalculatedPowerCT3 = 0;   // Calculated Power V*A Watts RMS
int idxCalculatedPowerCT4 = 0;   // Calculated Power V*A Watts RMS (ESP)
int idxCalculatedTotalPower = 0; // CalculatedTotalPower

int idxActivePowerCT1 = 0;             // ActivePowerCT1 - Pmean - Line Mean Active Power
int idxActivePowerCT2 = 0;             // ActivePowerCT2 - Pmean - Line Mean Active Power
int idxActivePowerCT3 = 0;             // ActivePowerCT3 - Pmean - Line Mean Active Power
int idxTotalActivePower = 0;           // TotalActivePower - Pmean - Line Mean Active Power
int idxCalculatedTotalActivePower = 0; // CalculatedTotalActivePower - Pmean - Line Mean Active Power

int idxActivePowerImportCT1 = 0;   // ActivePowerCT1 - Pmean - Line Mean Active Power Import
int idxActivePowerImportCT2 = 0;   // ActivePowerCT2 - Pmean - Line Mean Active Power Import
int idxActivePowerImportCT3 = 0;   // ActivePowerCT3 - Pmean - Line Mean Active Power Import
int idxTotalActivePowerImport = 0; // TotalActivePower - Pmean - Line Mean Active Power Import

int idxActivePowerExportCT1 = 0;   // ActivePowerCT1 - Pmean - Line Mean Active Power Export
int idxActivePowerExportCT2 = 0;   // ActivePowerCT2 - Pmean - Line Mean Active Power Export
int idxActivePowerExportCT3 = 0;   // ActivePowerCT3 - Pmean - Line Mean Active Power Export
int idxTotalActivePowerExport = 0; // TotalActivePower - Pmean - Line Mean Active Power Export

int idxReactivePowerCT1 = 0;             // ReactivePowerCT1 - Pmean - Line Mean Active Power
int idxReactivePowerCT2 = 0;             // ReactivePowerCT2 - Pmean - Line Mean Active Power
int idxReactivePowerCT3 = 0;             // ReactivePowerCT3 - Pmean - Line Mean Active Power
int idxTotalReactivePower = 0;           // TotalReactivePower - Pmean - Line Mean Active Power
int idxCalculatedTotalReactivePower = 0; // CalculatedTotalReactivePower - Pmean - Line Mean Active Power

int idxApparentPowerCT1 = 0;             // ApparentPowerCT1 - Pmean - Line Mean Apparent Power
int idxApparentPowerCT2 = 0;             // ApparentPowerCT2 - Pmean - Line Mean Apparent Power
int idxApparentPowerCT3 = 0;             // ApparentPowerCT3 - Pmean - Line Mean Apparent Power
int idxTotalApparentPower = 0;           // TotalApparentPower - Pmean - Line Mean Apparent Power
int idxCalculatedTotalApparentPower = 0; // CalculatedTotalApparentPower - Pmean - Line Mean Apparent Power

int idxTotalActiveFundPower = 0; // TotalActiveFundPower
int idxTotalActiveHarPower = 0;  // TotalActiveHarPower

int idxPowerFactorCT1 = 0;   // PowerFactorCT1 - PowerF - Line Power Factor
int idxPowerFactorCT2 = 0;   // PowerFactorCT2 - PowerF - Line Power Factor
int idxPowerFactorCT3 = 0;   // PowerFactorCT3 - PowerF - Line Power Factor
int idxTotalPowerFactor = 0; // TotalPowerFactor - PowerF - Line Power Factor

int idxPhaseAngleCT1 = 0; // PhaseAngleCT1 - Phase Angle
int idxPhaseAngleCT2 = 0; // PhaseAngleCT2 - Phase Angle
int idxPhaseAngleCT3 = 0; // PhaseAngleCT3 - Phase Angle

int idxChipTemperature = 0; // ChipTemperature ATM90E36 Internal Chip Temperature °C
int idxLineFrequency = 0;   // LineFrequency - Line Voltage Frequency

int idxDCVoltage = 0;      // PCB DC Input (Derived from AC)
int idxTMPTemperature = 0; // PCB NTC °C

int idxEnablePWMLocal = 0;     // PWM Output Local (Turn Switch On/Off)
int idxEnablePWMRemote = 0;    // PWM Output Remote (Turn Switch On/Off)
int idxPWMPowerOutput = 0;     // PWM Last Factored Power
int idxPWMPowerPercentage = 0; // PWM Percentage

int idxEnableDACLocal = 0;     // DAC Output Local (Turn Switch On/Off)
int idxEnableDACRemote = 0;    // DAC Output Remote (Turn Switch On/Off)
int idxDACPowerOutput = 0;     // DAC Last Factored Power
int idxDACPowerPercentage = 0; // DAC Percentage

// Set this value to the Domoticz Device Group Index (IDX) - Note: Currently Unused Virtual Device.
int idxDomoticzBase = 0; // If Zero, then entry is ignored.  Group device needs to be created in Domoticz. WIP.

#endif