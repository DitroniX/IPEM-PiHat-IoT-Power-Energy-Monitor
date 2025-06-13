/*
  Dave Williams, DitroniX 2019-2025 (ditronix.net)

  Example Code, to demonstrate and test the ESPuno Pi Zero, PCA9671 Read Pins (Default High)

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
#include "PCA9671.h"  // https://github.com/RobTillaart/PCA9671

// **************** USER VARIABLES / DEFINES / STATIC / STRUCTURES / CONSTANTS ****************

#define PCA_Address 0x20  // Default I2C address with no switches or solder pads set

PCA9671 PCA(PCA_Address);

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

  Serial.println(__FILE__);
  Serial.print("PCA9671_LIB_VERSION:\t");
  Serial.println(PCA9671_LIB_VERSION);
  Serial.println();

  // Initialize I2C
  Wire.begin(I2C_SDA, I2C_SCL);

  Serial.println("ESPuno Zero Configured...");

  PCA.begin();

  delay(1000);
}

// **************** LOOP ****************
void loop() {

  // uint16_t value = PCA.read16();
  // Serial.print("#38:\t");
  // Serial.println(value);

  // for (int i = 0; i < 255; i++) {
  //   PCA.write16(i);
  //   delay(100);
  // }

  // PCA.write(0, 1);
  // for (int i = 0; i < 15; i++) {
  //   PCA.shiftLeft();
  //   delay(100);
  // }

  // for (int i = 0; i < 15; i++) {
  //   PCA.shiftRight();
  //   delay(100);
  // }

  // for (int i = 0; i < 16; i++) {
  //   PCA.write(i, 1);
  //   delay(100);
  // }

  // for (int i = 0; i < 16; i++) {
  //   PCA.toggle(i);
  //   delay(100);
  //   PCA.toggle(i);
  //   delay(100);
  // }
  
  delay(2000);
}