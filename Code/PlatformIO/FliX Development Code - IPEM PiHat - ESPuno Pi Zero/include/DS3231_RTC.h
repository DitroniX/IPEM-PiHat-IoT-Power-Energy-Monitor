/*
  Dave Williams, DitroniX 2019-2025 (ditronix.net)
  Full header information in README

  This test code is OPEN SOURCE and formatted for easier viewing.  Although is is not intended for real world use, it may be freely used, or modified as needed.
  It is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.

  Further information, details and examples can be found on our website ditronix.net, github.com/DitroniX and hackster.io/DitroniX
*/

#ifndef DS3231_RTC_H
#define DS3231_RTC_H

// Libraries
#include <Arduino.h>
#include <DS3231.h>

// ****************  VARIABLES / DEFINES / STATIC / STRUCTURES / CONSTANTS ****************

DS3231 myRTC;

bool century = false;
bool h12Flag;
bool pmFlag;

// **************** FUNCTIONS AND ROUTINES ****************

// Initialise DS3231
void Initialize_DS3231()
{

  Serial.println("Hardware RTC (DS3231) Initialised\nSetting: \t");

  Serial.print(myRTC.getYear(), DEC);
  Serial.print("-");
  Serial.print(myRTC.getMonth(century), DEC);
  Serial.print("-");
  Serial.print(myRTC.getDate(), DEC);
  Serial.print(" ");
  Serial.print(myRTC.getHour(h12Flag, pmFlag), DEC); // 24-hr
  Serial.print(":");
  Serial.print(myRTC.getMinute(), DEC);
  Serial.print(":");
  Serial.println(myRTC.getSecond(), DEC);

  Serial.println("");
}

#endif