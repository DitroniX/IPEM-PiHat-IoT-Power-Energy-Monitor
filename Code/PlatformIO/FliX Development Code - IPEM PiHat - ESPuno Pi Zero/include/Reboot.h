/*
  Dave Williams, DitroniX 2019-2025 (ditronix.net)
  Full header information in README

  This test code is OPEN SOURCE and formatted for easier viewing.  Although is is not intended for real world use, it may be freely used, or modified as needed.
  It is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.

  Further information, details and examples can be found on our website ditronix.net, github.com/DitroniX and hackster.io/DitroniX
*/

#ifndef REBOOT_H
#define REBOOT_H

// Libraries
#include <Arduino.h>
#include <Config.h> // User Configuration Variables

// Reset MCU
void (*resetFunc)(void) = 0; // DO NOT CHANGE. Declare Reset Function at Address 0x0000

// **************** FUNCTIONS AND ROUTINES ****************

// Force Reboot
void ForceReboot()
{
    Serial.println("\nForced Reboot ...");
    oled.clear();
    OLEDPrint(AppAcronym, 2, 0);
    OLEDPrint("Forced", 2, 3);
    OLEDPrint("Reboot", 2, 5);
    oled.update();
    delay(2000);

    resetFunc();
} // ForceReboot

// Check Time Period and Reset
void RebootCheck()
{
    // Routing polled and is used to optionally reboot the ESPuno Pi Zero after a defined period of time.

    if (millis() >= RebootTime && RebootTime != 0)
        ForceReboot();

} // RebootCheck

#endif