/*
  Dave Williams, DitroniX 2019-2025 (ditronix.net)
  Full header information in README

  This test code is OPEN SOURCE and formatted for easier viewing.  Although is is not intended for real world use, it may be freely used, or modified as needed.
  It is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.

  Further information, details and examples can be found on our website ditronix.net, github.com/DitroniX and hackster.io/DitroniX
*/

#ifndef PCA9671_GPIO_H
#define PCA9671_GPIO_H

// Libraries
#include <Arduino.h>
#include <Config.h> // User Configuration Variables
#include <PCA9671.h>

// ****************  VARIABLES / DEFINES / STATIC / STRUCTURES / CONSTANTS ****************

PCA9671 PCA(I2C_Address_IPH);

// **************** FUNCTIONS AND ROUTINES ****************

// Set PCA GPIO Output
void PCAGPIO(uint8_t GPIO_Output, boolean GPIO_State = LOW)
{
  PCA.write(GPIO_Output, GPIO_State);
}

// Force Default PCA9671 Pin State
void PCA9671_Force_Default_Pin_State()
{

  Serial.println("PCA9671 Default Pin State");

  // Serial.println("Set Default IPEM PiHat > ATM DMA Low = 0X03 = 0000 0011");
  // Wire.beginTransmission(I2C_Address_IPH);
  // Wire.write(0xFF);
  // Wire.write(0x03);
  // Wire.endTransmission();

  // Output Defaults Port
  PCAGPIO(ATM_PM0, HIGH);
  PCAGPIO(ATM_PM1, HIGH);

    // Output Defaults Port 1
  PCAGPIO(ATM_RESET, HIGH);
  PCAGPIO(ATM_CS, HIGH);
  PCAGPIO(ATM_DMA_CTRL, LOW);
  PCAGPIO(LED_Blue, LOW);
  PCAGPIO(LED_Red, LOW);
  PCAGPIO(LED_Green, LOW);
  PCAGPIO(Relay1, LOW);
  PCAGPIO(Relay2, LOW);
}

// Force Raw Software Reset and Pin States
void PCA9671_Software_Reset()
{
  Serial.println("PCA9671 Software Reset");

 // Force Raw Pin State Reset - Inputs with Weak Pull-Ups
  Serial.println("PCA9671 Full Software Reset with Pull Ups");
  Wire.beginTransmission(I2C_Address_IPH);
  Wire.write(0xFF);
  Wire.write(0xFF);
  Wire.endTransmission();

  delay(250); // Take a breather

  PCA9671_Force_Default_Pin_State();
}

// Force Hardware Reset via PCA9671 - SW10 / 2 MUST be OFF
void PCA9671_Hardware_Reset()
{
  Serial.println("PCA9671 Hardware Reset");

  digitalWrite(27, LOW); // PCA_RST via Pi Header
  delay(250);
  digitalWrite(27, HIGH); // PCA_RST via Pi Header

  delay(250); // Take a breather

  PCA9671_Force_Default_Pin_State();
}

void RGBTest()
{
  Serial.println("Testing RGB LED");

  // RGB
  PCAGPIO(LED_Red, HIGH);
  PCAGPIO(LED_Green, HIGH);
  PCAGPIO(LED_Blue, HIGH);
  delay(1000);
  PCAGPIO(LED_Red, LOW);
  PCAGPIO(LED_Green, LOW);
  PCAGPIO(LED_Blue, LOW);
}

void RelayTest()
{
  Serial.println("Testing Relays");

  // RGB
  PCAGPIO(Relay1, HIGH);
  PCAGPIO(Relay2, HIGH);
  delay(1000);
  PCAGPIO(Relay1, LOW);
  PCAGPIO(Relay2, LOW);
}

// Initialise PCA9671
void Initialise_PCA9671()
{

  // Serial.println(__FILE__);
  // Serial.print("PCA9671_LIB_VERSION: ");
  // Serial.println(PCA9685_LIB_VERSION);
  // Serial.println();

  if (!PCA.begin())
  {
    Serial.println("Could not initialize PCA9671...");
  }
  if (!PCA.isConnected())
  {
    Serial.println("=> PCA9671 not Connecting");
    // while (1)
    //   ;
  }

  // PCA9671_Hardware_Reset();
  PCA9671_Software_Reset();
}

#endif