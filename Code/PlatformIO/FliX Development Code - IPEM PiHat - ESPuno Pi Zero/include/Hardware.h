/*
  Dave Williams, DitroniX 2019-2025 (ditronix.net)
  Full header information in README

  This test code is OPEN SOURCE and formatted for easier viewing.  Although is is not intended for real world use, it may be freely used, or modified as needed.
  It is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.

  Further information, details and examples can be found on our website wiki pages ditronix.net/wiki and also github.com/DitroniX
*/

// Libraries
#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>

#include <OLED.h>

#include <24C64_EEPROM.h>
#include <ATM90E36.h>
#include <ADS1115_ADC.h>
#include <TMP102.h>
#include <DS3231_RTC.h>

// ****************  VARIABLES / DEFINES / STATIC / STRUCTURES / CONSTANTS ****************

// Constants Application
uint64_t chipid = ESP.getEfuseMac(); // Get ChipID (essentially the MAC address)

// Variables
// float TemperatureC;      // Temperature
// float TemperatureF;      // Temperature
int VoltageSensorRaw;    // ADC Raw Voltage Value
float VoltageCalculated; // Calculated Voltage Value
int VoltagePercentage;   // Voltage Percentage
int OLEDCount;           // OLED Information Counter

// Variables ATM
float LineVoltage1, LineVoltage2, LineVoltage3, LineVoltageTotal, LineVoltageAverage;
float LineCurrentCT1, LineCurrentCT2, LineCurrentCT3, LineCurrentCT4, LineCurrentCTN, LineCurrentTotal;
float CalculatedPowerCT1, CalculatedPowerCT2, CalculatedPowerCT3, CalculatedPowerCT4, CalculatedPowerCTN, CalculatedTotalPower;
float ActivePowerCT1, ActivePowerCT2, ActivePowerCT3, TotalActivePower, CalculatedTotalActivePower;
float ActivePowerImportCT1, ActivePowerImportCT2, ActivePowerImportCT3, TotalActivePowerImport;
float ActivePowerExportCT1, ActivePowerExportCT2, ActivePowerExportCT3, TotalActivePowerExport;
float ReactivePowerCT1, ReactivePowerCT2, ReactivePowerCT3, TotalReactivePower, CalculatedTotalReactivePower;
float ApparentPowerCT1, ApparentPowerCT2, ApparentPowerCT3, TotalApparentPower, CalculatedTotalApparentPower;
float TotalActiveFundPower, TotalActiveHarPower;
float PowerFactorCT1, PowerFactorCT2, PowerFactorCT3, TotalPowerFactor;
float PhaseAngleCT1, PhaseAngleCT2, PhaseAngleCT3;
float VoltageHarmonicsCT1, VoltageHarmonicsCT2, VoltageHarmonicsCT3;
float CurrentHarmonicsCT1, CurrentHarmonicsCT2, CurrentHarmonicsCT3;
float ChipTemperature, LineFrequency;

// Variables PCB
float DCVoltage; // DCV Input Voltage

// **************** Initialize ATM90E36 IC Class ****************
ATM90E36 eic{}; //

// **************** FUNCTIONS AND ROUTINES ****************

// Display BIN from Var
void DisplayBIN16(int var)
{
  for (unsigned int i = 0x8000; i; i >>= 1)
  {
    Serial.write(var & i ? '1' : '0');
  }
  Serial.print(" ");
} // DisplayBIN16

// Display Hex from Var
void DisplayHEX(unsigned long var, unsigned char numChars)
{
  unsigned long mask = 0x0000000F;
  mask = mask << 4 * (numChars - 1);

  for (unsigned int i = numChars; i > 0; --i)
  {
    Serial.print(((var & mask) >> (i - 1) * 4), HEX);
    mask = mask >> 4;
  }
  Serial.print(" ");
} // DisplayHEX

// Return Rounded Value to 2 decimals and Remove +/- Noise Threshold.  Default 0.02
float NoiseFilterSquelch(float Value, float Threshold = 0.02, boolean AllowNegative = true, float ValueMax = 0)
{
  if (EnableNoiseFilterSquelch == true) // If false, output is raw value
  {
    Value = roundf(Value * 100) / 100; // Round to 2 Decimal Places

    if (Value >= -Threshold && Value <= Threshold) // Window Comparator / Squelch.  Default 0.2
      Value = 0;

    if (AllowNegative == false && Value < 0) // Negative Value Filter.  Default true
      Value = 0;

    if (ValueMax != 0 && Value > ValueMax) // Maximum Filter.  Default 0
      Value = 0;
  }

  return Value;
} // NoiseFilterSquelch

// Map float values to percentages
float MapValues(float x, float DC_Min, float DC_Max, float Percentage_Min, float Percentage_Max)
{
  return (x - DC_Min) * (Percentage_Max - Percentage_Min) / (DC_Max - DC_Min) + Percentage_Min;
}

// Calculate Average Value and Reduce Jitter
int CalculateADCAverage(int SensorChannel)
{
  int AverageRAW = 0;
  if (EnableAveraging == true)
  {

    for (int i = 0; i < AverageSamples; i++)
    {
      AverageRAW = AverageRAW + analogRead(SensorChannel);
      delay(AverageDelay);
    }
    AverageRAW = AverageRAW / AverageSamples;
    if (AverageRAW < 2)
      AverageRAW = 0;
  }
  else
  {
    AverageRAW = analogRead(SensorChannel);
  }
  return AverageRAW;
} // CalculateADCAverage

// I2C Bus Scanner
void ScanI2CBus()
{

  // Useful Reference https://i2cdevices.org/addresses

  byte error, address;
  int nDevices;

  Serial.println("Scanning I2C Bus for Devices for Auto Configuration ...");

  nDevices = 0;
  for (address = 1; address < 127; address++)
  {
    Wire.beginTransmission(address);
    error = Wire.endTransmission();
    nDevices++;
    if (nDevices == 1)
      Serial.println(" I2C Possible Device(s) found at Address:");
    if (error == 0)
    {
      Serial.print(" * Hex 0x");
      Serial.print(address, HEX);

      Serial.print(" (");
      if (address < 16)
      {
        Serial.print("0");
      }
      Serial.print(address);
      Serial.print(")\t");

      switch (address)
      {
      case 0x10 ... 0x1F:
        Serial.print(" PCA9671 GPIO Expander");
        EnablePCA = true;
        break;
      case 0x20:
        Serial.print(" PCA9671 GPIO Expander (Default)");
        EnablePCA = true;
        break;
      case 0x21 ... 0x2F:
        Serial.print(" PCA9671 GPIO Expander");
        EnablePCA = true;
        break;
      // case 0x50 ... 0x68: // Commented Out to Stop 'Case' Conflicts
      //   Serial.print(" PCA9671 GPIO Expander");
      // EnablePCA = true;
      //   break;
      case 0x48:
        Serial.print(" TMP102 Temperature Sensor Espuno Pi Zero");
        EnableTMP = true;
        break;
      case 0x4A:
        Serial.print(" TMP102 Temperature Sensor IPEM PiHat");
        EnableTMP = true;
        break;
      case 0x4B:
        Serial.print(" ADS1115 16-bit ADC IPEM PiHat");
        EnableADC = true;
        break;
      case 0x3C ... 0x3D:
        Serial.print(" OLED");
        EnableOLED = true;
        break;
      case 0x50:
        Serial.print(" EEPROM ESPuno Pi Zero");
        EnableEEPROM = true;
        break;
      case 0x55:
        Serial.print(" EEPROM IPEM PiHat");
        EnableEEPROM = true;
        break;
      case 0x58:
        Serial.print(" EEPROM ESPuno Pi Zero (Reserved Address)");
        break;
      case 0x60 ... 0x62:
        Serial.print(" MCP4728 12-bit DAC IPEM PiHat");
        EnableDAC = true;
        break;
      case 0x68:
        Serial.print(" DS3231 RTC IPEM PiHat");
        EnableRTC = true;
        break;
      case 0x71 ... 0x77:
        Serial.print(" PCA9671 GPIO Expander");
        break;
      case 0x7C:
        Serial.print(" PCA9671 GPIO Expander (Reserved Address)");
        EnablePCA = true;
        break;
      default:
        Serial.print(" ?");
        break;
      }
      Serial.println();
    }
    else if (error == 4)
    {
      Serial.print(" * Unknown error at address Decimal ");
      if (address < 16)
      {
        Serial.print("0");
      }
      Serial.print(address);
      Serial.print(" = Hex 0x");
      Serial.println(address, HEX);
    }
  }
  if (nDevices == 0)
  {
    Serial.println(" * No I2C devices found. Possible Hardware Issue?");
  }
  else
  {
    Serial.println(" I2C Bus Scan Complete\n");
  }
} // ScanI2CBus

void ConfigureBoard()
{

  Serial.println("Scanning and Configuring Board.. Please Wait..\n");

  // Initialize SPI Hardware Chip Select
  if (CS_GPIO > 0)
  {
    // Hardware Chip Select CS1
    pinMode(CS_GPIO, OUTPUT);
    digitalWrite(CS_GPIO, HIGH);
  }

  // Initialize I2C
  Wire.begin(I2C_SDA, I2C_SCL);
  Wire.setClock(I2C_SPEED); // Default 100 kHz = 100000

  // Display Hardware Options
  PrintUnderline("Hardware Options and Auto Configuration");

  // Scan I2C Bus and Report Devices
  ScanI2CBus();

  // Header Auto Configure
  // Board Type

  AppName = "Unknown Board";

  if (EnablePCA == true && EnableRTC == false && EnableTMP == true)
  {
    AppName = "IPEM PiHat Lite";
    AppAcronym = "IPEM PiHat";
  }

  if (EnablePCA == true && EnableRTC == true && EnableTMP == true)
  {
    AppName = "IPEM PiHat";
    AppAcronym = "IPEM PiHat";
  }

  Serial.println("Detected: " + AppName + " ATM90E36 IoT Power Energy Monitor");

  Serial.println("Hardware Setup and Power-Up Test\n");

  PrintUnderline(AppName + " Register Status and Startup Report");
  Serial.printf("ESP32 Serial ID: %04X", (uint16_t)(chipid >> 32));
  Serial.printf("%08X", (uint32_t)chipid);
  Serial.println("");
  Serial.print("FliX Firmware Version: ");
  Serial.println(AppVersion);
  Serial.print("Board Location: ");
  Serial.println(LocationName);

  // Initialize EEPROM
  if (EnableEEPROM == true)
    InitializeEEPROM();

  // Initialise ADC
  if (EnableADC == true)
    Initialise_ADS1115_ADC();

  // Initialize OLED
  if (EnableOLED == true)
    Initialise_OLED();

  // Initialize TMP
  if (EnableTMP == true)
    Initialise_TMP102();

  // Initialize RTC
  if (EnableRTC == true)
    Initialize_DS3231();

  // Initialize PCA GPIO Expander
  if (EnablePCA == true)
  {
    Initialise_PCA9671();

    // Test RGB LED
    RGBTest();

    // Test Relays (Only on IPEM PiHat)
    if (EnableRTC == true)
      RelayTest();
  }

} // ConfigureBoard

// Display Board Configuration
void DisplayBoardConfiguration()
{

  // Header
  Serial.println("Register Status and Diagnostic Report");
  Serial.printf("ESP32 Serial ID: %04X", (uint16_t)(chipid >> 32));
  Serial.printf("%08X", (uint32_t)chipid);
  Serial.println("");
  Serial.print("Firmware Version: ");
  Serial.println(AppVersion);
  Serial.print("Location: ");
  Serial.println(LocationName);
  Serial.println("");

  // Stabalise
  delay(100);

  // Display Hardware Configuration for ATM90E32 ATM90E36
  PrintUnderline("Hardware Configuration for ATM90E36");

  // Configuration / ATM Status Values
#if ATM_SINGLEVOLTAGE == true
  Serial.println("AC Voltage Inputs:\tSingle Input V1 will be used for Current Phase Calculations");
#else
#if ATM_SPLITPHASE == false // World Single, Three Phase or 3 x Single Phases
  Serial.println("AC Voltage Inputs:\tMulti Separated V1 V2 V3 - 3 Phase, or 3 x Single Phase Configuration.");
#else                       // USA Split Phase 120+120
  Serial.println("AC Voltage Inputs:\tMulti Dual V1 and V3 - USA Configuration");
#endif
#endif

#if ATM_SPLITPHASE == true
#if ATM_SINGLEVOLTAGE == false
  // USA 120+120
  Serial.println("Split AC Voltage:\tDual Input V1 + V3 Enabled - USA Configuration");
  Serial.println("CT Current Clamps:\tPhase Configured for 1 and 3 + 1 Phase (I4N)");

#else
  // Cannot have Split AC Voltage input with Single Voltage Input Selected
  Serial.println("Split AC Voltage:\tConfiguration Error (Check ATM_SINGLEVOLTAGE)");
#endif
#else
  // World
  Serial.println("Split AC Voltage:\tDual or Split Voltage Input Disabled");
  Serial.println("CT Current Clamps:\tConfigured for 1, 2, 3 Phase");
#endif

  // Registers
  String SysStatus0_Value = String(eic.GetSysStatus0(), HEX); // EMMState0
  SysStatus0_Value.toUpperCase();
  String SysStatus1_Value = String(eic.GetSysStatus1(), HEX); // EMMState1
  SysStatus1_Value.toUpperCase();
  String MeterStatus0_Value = String(eic.GetMeterStatus0(), HEX); // EMMIntState0
  MeterStatus0_Value.toUpperCase();
  String MeterStatus1_Value = String(eic.GetMeterStatus1(), HEX); // EMMIntState1
  MeterStatus1_Value.toUpperCase();

  Serial.println("\n[ATM90E36 Status Register Values]");
  Serial.println("System Status: \t\tS0:0x" + SysStatus0_Value + "\t\tS1:0x" + SysStatus1_Value);
  Serial.println("Meter Status:  \t\tE0:0x" + MeterStatus0_Value + "\t\tE1:0x" + MeterStatus1_Value);

  // Stabalise
  delay(100);

  // if true the MCU is not getting data from the ATM90E36 energy meter
  unsigned short sys0 = eic.GetSysStatus0(); // EMMState0
  if (sys0 == 65535 || sys0 == 0)
  {
    EnableATM = false;

    Serial.println("");
    Serial.println("***********************************************************************");
    Serial.print("* Error: Not Correct Data from ATM90E36");
    Serial.println(" Energy Meter - Check Settings *");
    Serial.println("***********************************************************************\n");

    // Potential Reboot MCU to Reset Hardware
  }
  else
  {
    EnableATM = true;
    Serial.println("\nATM90E36 Connected - Communication Successful\n");
  }

} // DisplayBoardConfiguration