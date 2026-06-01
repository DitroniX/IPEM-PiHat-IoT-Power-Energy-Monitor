/*
  Dave Williams, DitroniX 2019-2025 (ditronix.net)
  Full header information in README

  This test code is OPEN SOURCE and formatted for easier viewing.  Although is is not intended for real world use, it may be freely used, or modified as needed.
  It is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.

  Further information, details and examples can be found on our website ditronix.net, github.com/DitroniX and hackster.io/DitroniX
*/

#ifndef TMP102_H
#define TMP102_H

// Libraries
#include <Arduino.h>
#include <SparkFunTMP102.h>

// ****************  VARIABLES / DEFINES / STATIC / STRUCTURES / CONSTANTS ****************
TMP102 TempSensor;

// Variables TMP102
float TemperatureC; // TMP102 Temperature C
float TemperatureF; // TMP102 Temperature F

// **************** FUNCTIONS AND ROUTINES ****************

// Read PCB NTC Thermister on VN
void ReadTMPTemperature()
{
  TemperatureC = TempSensor.readTempC(); // Centigrade
  // TemperatureF = TempSensor.readTempF(); // Fahrenheit

  Serial.println("TMP102 Temperature: " + String(TemperatureC) + " °C\n");
  TempSensor.sleep(); // Return sensor to sleep

} // ReadTMPTemperature

// Initialise TMP102 Digital Temnperature Sensor
void Initialise_TMP102()
{
  if (!TempSensor.begin(0x4A))
  {
    Serial.println("Failed to initialize TMP102");
    while (1)
      ;
  }

  Serial.println("Temperature Sensor (TMP102) Initialised\n");
  delay(100);

  ReadTMPTemperature();
  TempSensor.sleep(); // Put sensor to sleep
}

#endif