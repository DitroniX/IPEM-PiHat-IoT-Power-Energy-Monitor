/*
  Dave Williams, DitroniX 2019-2025 (ditronix.net)

  Example Code, to demonstrate and test the ESPuno Pi Zero, PCA9671 Test SPI CS Line

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

// Libraries
#include <Wire.h>

// **************** USER VARIABLES / DEFINES / STATIC / STRUCTURES / CONSTANTS ****************

#define PCA_Address 0x10  // Default 0x20.  I2C address with no switches or solder pads set

// Define I2C (Expansion Port)
#define I2C_SDA 6
#define I2C_SCL 7

// **************** FUNCTIONS AND ROUTINES ****************


// **************** SETUP ****************
void setup() {

  // Stabalise
  delay(250);

  // Initialise UART
  Serial.begin(115200, SERIAL_8N1);  //115200
  while (!Serial)
    ;
  Serial.println("");

  // Initialize I2C
  Wire.begin(I2C_SDA, I2C_SCL);

  Serial.println("ESPuno Zero Configured...");

  // // Force Raw Pin State Reset - Inputs with Weak Pull-Ups
  Serial.println("PCA9671 Full Software Reset with Pull Ups");
  Wire.beginTransmission(PCA_Address);
  Wire.write(0xFF);
  Wire.write(0xFF);
  Wire.endTransmission();

  delay(1000);  // Take a breather

  Serial.println("Set Default IPEM PiHat > ATM DMA Low = 0X03 = 0000 0011");
  Wire.beginTransmission(PCA_Address);
  Wire.write(0xFF);
  Wire.write(0x03);
  Wire.endTransmission();

  delay(1000);  // Take a breather

  Serial.println("Pull /CS Low and leave ATM DMA Low");
  Wire.beginTransmission(PCA_Address);
  Wire.write(0xFF);
  Wire.write(0x01);
  Wire.endTransmission();

  delay(1000);  // Take a breather

  Serial.println("Pull /CS High and leave ATM DMA Low");
  Wire.beginTransmission(PCA_Address);
  Wire.write(0xFF);
  Wire.write(0x03);
  Wire.endTransmission();
}

// **************** LOOP ****************
void loop() {
}