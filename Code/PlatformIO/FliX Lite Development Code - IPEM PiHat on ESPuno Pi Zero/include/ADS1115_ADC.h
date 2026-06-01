/*
  Dave Williams, DitroniX 2019-2025 (ditronix.net)
  Full header information in README

  This test code is OPEN SOURCE and formatted for easier viewing.  Although is is not intended for real world use, it may be freely used, or modified as needed.
  It is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.

  Further information, details and examples can be found on our website ditronix.net, github.com/DitroniX and hackster.io/DitroniX
*/

#ifndef ADS1115_ADC_H
#define ADS1115_ADC_H

// Libraries
#include <Arduino.h>
#include <Adafruit_ADS1X15.h>  //https://github.com/adafruit/Adafruit_ADS1X15/blob/master/examples/singleended/singleended.ino

// ****************  VARIABLES / DEFINES / STATIC / STRUCTURES / CONSTANTS ****************

Adafruit_ADS1115 ipem_adc; // 16bit ADC

// WORK IN POREGRESS

// Initialise IPEX ADS1115 ADC (Default Address 0x49)
void Initialise_ADS1115_ADC()
{

  if (!ipem_adc.begin(IPEM_ADS1115))
  {
    Serial.println("Failed to initialize ADS1115");
    while (1)
    {
      delay(10);
    }
  }
  else
  {
    Serial.println("ADC (ADS1115) Initialised\n");

    int16_t adc0, adc1, adc2, adc3;
    float volts0, volts1, volts2, volts3;

    adc0 = ipem_adc.readADC_SingleEnded(0);
    adc1 = ipem_adc.readADC_SingleEnded(1);
    adc2 = ipem_adc.readADC_SingleEnded(2);
    adc3 = ipem_adc.readADC_SingleEnded(3);

    volts0 = ipem_adc.computeVolts(adc0);
    volts1 = ipem_adc.computeVolts(adc1);
    volts2 = ipem_adc.computeVolts(adc2);
    volts3 = ipem_adc.computeVolts(adc3);

    Serial.print("AIN0: ");
    Serial.print(adc0);
    Serial.print("  ");
    Serial.print(volts0);
    Serial.println("V");
    Serial.print("AIN1: ");
    Serial.print(adc1);
    Serial.print("  ");
    Serial.print(volts1);
    Serial.println("V");
    Serial.print("AIN2: ");
    Serial.print(adc2);
    Serial.print("  ");
    Serial.print(volts2);
    Serial.println("V");
    Serial.print("AIN3: ");
    Serial.print(adc3);
    Serial.print("  ");
    Serial.print(volts3);
    Serial.println("V");
    Serial.println("");
  }
}

#endif