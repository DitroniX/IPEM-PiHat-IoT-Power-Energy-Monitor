/*
  Dave Williams, DitroniX 2019-2025 (ditronix.net)
  Full header information in README

  This test code is OPEN SOURCE and formatted for easier viewing.  Although is is not intended for real world use, it may be freely used, or modified as needed.
  It is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.

  Further information, details and examples can be found on our website wiki pages ditronix.net/wiki and also github.com/DitroniX
*/

// Libraries
#include <Arduino.h>

// ****************  VARIABLES / DEFINES / STATIC / STRUCTURES ****************

// ######### FUNCTIONS #########

// Initialise Zabbix
void InitialiseDomoticz()
{

    // Domoticz Integration Status
    if (EnableDomoticz == true && WiFi.status() == WL_CONNECTED)
    {
        Serial.println("Domoticz Enabled - Register Values Will be Published");
    }
    else
    {
        Serial.println("Domoticz Publishing is Disabled");
    }
}

// Publish to Domoticz - Single String Values
void PublishDomoticzString(int Sensor_Index, float Sensor_Value, String Sensor_Name = "")
{

    if (Sensor_Index > 0)
    {
        if (wlan_client.connect(DomoticzServer, DomoticzPort))
        {
            // Green LED
            digitalWrite(LED_Green, LOW);

            Serial.print("Sending Message to Domoticz #");
            Serial.print(Sensor_Index);
            Serial.print(" ");
            Serial.print(Sensor_Value);
            Serial.print(" \t");
            Serial.println(Sensor_Name);

            wlan_client.print("GET /json.htm?type=command&param=udevice&idx=");
            wlan_client.print(Sensor_Index);

            wlan_client.print("&svalue=");
            wlan_client.print(Sensor_Value);

            wlan_client.println(" HTTP/1.1");
            wlan_client.print("Host: ");
            wlan_client.print(DomoticzServer);
            wlan_client.print(":");

            wlan_client.println(DomoticzPort);
            wlan_client.println("User-Agent: Arduino-ethernet");
            wlan_client.println("Connection: close");
            wlan_client.println();

            wlan_client.stop();

            // Green LED
            digitalWrite(LED_Green, HIGH);
        }
        else
        {
            // Red LED
            digitalWrite(LED_Red, LOW);

            Serial.println("WiFi or Domoticz Server Not Connected");

            // Update OLED
            oled.clear();
            OLEDPrint("Error", 2, 0);
            OLEDPrint("Domoticz", 2, 2);
            oled.update();
            delay(1000);

            // Red LED
            digitalWrite(LED_Red, HIGH);

            // Stabalise for slow Access Points
            InitialiseWiFi();
        }
    }
} // PublishDomoticz

// Publish to Domoticz - Single Numeric Values
void PublishDomoticzNumeric(int Sensor_Index, float Sensor_Value, String Sensor_Name = "")
{

    if (Sensor_Index > 0)
    {
        if (wlan_client.connect(DomoticzServer, DomoticzPort))
        {
            // Green LED
            digitalWrite(LED_Green, LOW);

            Serial.print("Sending Message to Domoticz #");
            Serial.print(Sensor_Index);
            Serial.print(" ");
            Serial.print(Sensor_Value);
            Serial.print(" \t");
            Serial.println(Sensor_Name);

            wlan_client.print("GET /json.htm?type=command&param=udevice&idx=");
            wlan_client.print(Sensor_Index);

            wlan_client.print("&nvalue=");
            wlan_client.print(Sensor_Value);

            wlan_client.println(" HTTP/1.1");
            wlan_client.print("Host: ");
            wlan_client.print(DomoticzServer);
            wlan_client.print(":");

            wlan_client.println(DomoticzPort);
            wlan_client.println("User-Agent: Arduino-ethernet");
            wlan_client.println("Connection: close");
            wlan_client.println();

            wlan_client.stop();

            // Green LED
            digitalWrite(LED_Green, HIGH);
        }
        else
        {
            // Red LED
            digitalWrite(LED_Red, LOW);

            Serial.println("WiFi or Domoticz Server Not Connected");

            // Update OLED
            oled.clear();
            OLEDPrint("Error", 2, 0);
            OLEDPrint("Domoticz", 2, 2);
            oled.update();
            delay(1000);

            // Red LED
            digitalWrite(LED_Red, HIGH);

            // Stabalise for slow Access Points
            InitialiseWiFi();
        }
    }
} // PublishDomoticzNumeric

// Publish to Domoticz - Listed Values
void PublishDomoticzValues()
{

    if (wlan_client.connect(DomoticzServer, DomoticzPort))
    {

        // Voltage LineVoltage1, LineVoltage2, LineVoltage3, LineVoltageTotal, LineVoltageAverage
        if (idxLineVoltage1 > 0)
        {
            PublishDomoticzString(idxLineVoltage1, LineVoltage1, "LineVoltage1");
        }

        if (idxLineVoltage2 > 0)
        {
            PublishDomoticzString(idxLineVoltage2, LineVoltage2, "LineVoltage2");
        }

        if (idxLineVoltage3 > 0)
        {
            PublishDomoticzString(idxLineVoltage3, LineVoltage3, "LineVoltage3");
        }

        if (idxLineVoltageTotal > 0)
        {
            PublishDomoticzString(idxLineVoltageTotal, LineVoltageTotal, "LineVoltageTotal");
        }

        if (idxLineVoltageAverage > 0)
        {
            PublishDomoticzString(idxLineVoltageAverage, LineVoltageAverage, "LineVoltageAverage");
        }

        // Current LineCurrentCT1, LineCurrentCT2, LineCurrentCT3, LineCurrentCT4, LineCurrentCTN, LineCurrentTotal
        if (idxLineCurrentCT1 > 0)
        {
            PublishDomoticzString(idxLineCurrentCT1, LineCurrentCT1, "LineCurrentCT1");
        }

        if (idxLineCurrentCT2 > 0)
        {
            PublishDomoticzString(idxLineCurrentCT2, LineCurrentCT2, "LineCurrentCT2");
        }

        if (idxLineCurrentCT3 > 0)
        {
            PublishDomoticzString(idxLineCurrentCT3, LineCurrentCT3, "LineCurrentCT3");
        }
        if (idxLineCurrentCT4 > 0)
        {
            PublishDomoticzString(idxLineCurrentCT4, LineCurrentCT4, "LineCurrentCT4");
        }
        if (idxLineCurrentCTN > 0)
        {
            PublishDomoticzString(idxLineCurrentCTN, LineCurrentCTN, "LineCurrentCTN");
        }
        if (idxLineCurrentTotal > 0)
        {
            PublishDomoticzString(idxLineCurrentTotal, LineCurrentTotal, "LineCurrentTotal");
        }

        // Calculated Power CalculatedPowerCT1, CalculatedPowerCT2, CalculatedPowerCT3, CalculatedPowerCT4, CalculatedTotalPower
        if (idxCalculatedPowerCT1 > 0)
        {
            PublishDomoticzString(idxCalculatedPowerCT1, CalculatedPowerCT1, "CalculatedPowerCT1");
        }
        if (idxCalculatedPowerCT2 > 0)
        {
            PublishDomoticzString(idxCalculatedPowerCT2, CalculatedPowerCT2, "CalculatedPowerCT2");
        }
        if (idxCalculatedPowerCT3 > 0)
        {
            PublishDomoticzString(idxCalculatedPowerCT3, CalculatedPowerCT3, "CalculatedPowerCT3");
        }
        if (idxCalculatedPowerCT4 > 0)
        {
            PublishDomoticzString(idxCalculatedPowerCT4, CalculatedPowerCT4, "CalculatedPowerCT4");
        }
        if (idxCalculatedTotalPower > 0)
        {
            PublishDomoticzString(idxCalculatedTotalPower, CalculatedTotalPower, "CalculatedTotalPower");
        }

        // Active Power ActivePowerCT1, ActivePowerCT2, ActivePowerCT3, TotalActivePower
        if (idxActivePowerCT1 > 0)
        {
            PublishDomoticzString(idxActivePowerCT1, ActivePowerCT1, "ActivePowerCT1");
        }
        if (idxActivePowerCT2 > 0)
        {
            PublishDomoticzString(idxActivePowerCT2, ActivePowerCT2, "ActivePowerCT2");
        }
        if (idxActivePowerCT3 > 0)
        {
            PublishDomoticzString(idxActivePowerCT3, ActivePowerCT3, "ActivePowerCT3");
        }
        if (idxTotalActivePower > 0)
        {
            PublishDomoticzString(idxTotalActivePower, TotalActivePower, "TotalActivePower");
        }
        if (idxCalculatedTotalActivePower > 0)
        {
            PublishDomoticzString(idxCalculatedTotalActivePower, CalculatedTotalActivePower, "CalculatedTotalActivePower");
        }

        // Active Power Import ActivePowerImportCT1, ActivePowerImportCT2, ActivePowerImportCT3, TotalActivePowerImport
        if (idxActivePowerImportCT1 > 0)
        {
            PublishDomoticzString(idxActivePowerImportCT1, ActivePowerImportCT1, "ActivePowerImportCT1");
        }
        if (idxActivePowerImportCT2 > 0)
        {
            PublishDomoticzString(idxActivePowerImportCT2, ActivePowerImportCT2, "ActivePowerImportCT2");
        }
        if (idxActivePowerImportCT3 > 0)
        {
            PublishDomoticzString(idxActivePowerImportCT3, ActivePowerImportCT3, "ActivePowerImportCT3");
        }
        if (idxTotalActivePowerImport > 0)
        {
            PublishDomoticzString(idxTotalActivePowerImport, TotalActivePowerImport, "TotalActivePowerImport");
        }

        // Active Power Export ActivePowerExportCT1, ActivePowerExportCT2, ActivePowerExportCT3, TotalActivePowerExport
        if (idxActivePowerExportCT1 > 0)
        {
            PublishDomoticzString(idxActivePowerExportCT1, ActivePowerExportCT1, "ActivePowerExportCT1");
        }
        if (idxActivePowerExportCT2 > 0)
        {
            PublishDomoticzString(idxActivePowerExportCT2, ActivePowerExportCT2, "ActivePowerExportCT2");
        }
        if (idxActivePowerExportCT3 > 0)
        {
            PublishDomoticzString(idxActivePowerExportCT3, ActivePowerExportCT3, "ActivePowerExportCT3");
        }
        if (idxTotalActivePowerExport > 0)
        {
            PublishDomoticzString(idxTotalActivePowerExport, TotalActivePowerExport, "TotalActivePowerExport");
        }

        // Reactive Power ReactivePowerCT1, ReactivePowerCT2, ReactivePowerCT3, TotalReactivePower
        if (idxReactivePowerCT1 > 0)
        {
            PublishDomoticzString(idxReactivePowerCT1, ReactivePowerCT1, "ReactivePowerCT1");
        }
        if (idxReactivePowerCT2 > 0)
        {
            PublishDomoticzString(idxReactivePowerCT2, ReactivePowerCT2, "ReactivePowerCT2");
        }
        if (idxReactivePowerCT3 > 0)
        {
            PublishDomoticzString(idxReactivePowerCT3, ReactivePowerCT3, "ReactivePowerCT3");
        }
        if (idxTotalReactivePower > 0)
        {
            PublishDomoticzString(idxTotalReactivePower, TotalReactivePower, "TotalReactivePower");
        }
        if (idxCalculatedTotalReactivePower > 0)
        {
            PublishDomoticzString(idxCalculatedTotalReactivePower, CalculatedTotalReactivePower, "CalculatedTotalReactivePower");
        }

        // Apparent Popwer ApparentPowerCT1, ApparentPowerCT2, ApparentPowerCT3, TotalApparentPower
        if (idxApparentPowerCT1 > 0)
        {
            PublishDomoticzString(idxApparentPowerCT1, ApparentPowerCT1, "ApparentPowerCT1");
        }
        if (idxApparentPowerCT2 > 0)
        {
            PublishDomoticzString(idxApparentPowerCT2, ApparentPowerCT2, "ApparentPowerCT2");
        }
        if (idxApparentPowerCT3 > 0)
        {
            PublishDomoticzString(idxApparentPowerCT3, ApparentPowerCT3, "ApparentPowerCT3");
        }
        if (idxTotalApparentPower > 0)
        {
            PublishDomoticzString(idxTotalApparentPower, TotalApparentPower, "TotalApparentPower");
        }
        if (idxCalculatedTotalApparentPower > 0)
        {
            PublishDomoticzString(idxCalculatedTotalApparentPower, CalculatedTotalApparentPower, "CalculatedTotalApparentPower");
        }

        // ActivePower TotalActiveFundPower, TotalActiveHarPower
        if (idxTotalActiveFundPower > 0)
        {
            PublishDomoticzString(idxTotalActiveFundPower, TotalActiveFundPower, "TotalActiveFundPower");
        }
        if (idxTotalActiveHarPower > 0)
        {
            PublishDomoticzString(idxTotalActiveHarPower, TotalActiveHarPower, "TotalActiveHarPower");
        }

        // Power Factor PowerFactorCT1, PowerFactorCT2, PowerFactorCT3, TotalPowerFactor
        if (idxPowerFactorCT1 > 0)
        {
            PublishDomoticzString(idxPowerFactorCT1, PowerFactorCT1, "PowerFactorCT1");
        }
        if (idxPowerFactorCT2 > 0)
        {
            PublishDomoticzString(idxPowerFactorCT2, PowerFactorCT2, "PowerFactorCT2");
        }
        if (idxPowerFactorCT3 > 0)
        {
            PublishDomoticzString(idxPowerFactorCT3, PowerFactorCT3, "PowerFactorCT3");
        }
        if (idxTotalPowerFactor > 0)
        {
            PublishDomoticzString(idxTotalPowerFactor, TotalPowerFactor, "TotalPowerFactor");
        }

        // Phase Angle PhaseAngleCT1, PhaseAngleCT2, PhaseAngleCT3
        if (idxPhaseAngleCT1 > 0)
        {
            PublishDomoticzString(idxPhaseAngleCT1, PhaseAngleCT1, "PhaseAngleCT1");
        }
        if (idxPhaseAngleCT2 > 0)
        {
            PublishDomoticzString(idxPhaseAngleCT2, PhaseAngleCT2, "PhaseAngleCT2");
        }
        if (idxPhaseAngleCT3 > 0)
        {
            PublishDomoticzString(idxPhaseAngleCT3, PhaseAngleCT3, "PhaseAngleCT3");
        }
        // Other ChipTemperature, LineFrequency, DCVoltage, TMPTemperature
        if (idxChipTemperature > 0)
        {
            PublishDomoticzString(idxChipTemperature, ChipTemperature, "ChipTemperature");
        }
        if (idxLineFrequency > 0)
        {
            PublishDomoticzString(idxLineFrequency, LineFrequency, "PhaLineFrequencyseAngleC");
        }
        if (idxDCVoltage > 0)
        {
            PublishDomoticzString(idxDCVoltage, DCVoltage, "DCVoltage");
        }
        if (idxTMPTemperature > 0)
        {
            PublishDomoticzString(idxTMPTemperature, TemperatureC, "TMPTemperature");
        }
   }
    else
    {
        // Red LED
        digitalWrite(LED_Red, LOW);

        Serial.println("WiFi or Domoticz Server Not Connected");

        // Update OLED
        oled.clear();
        OLEDPrint("Error", 2, 0);
        OLEDPrint("Domoticz", 2, 2);
        oled.update();
        delay(1000);

        // Red LED
        digitalWrite(LED_Red, HIGH);

        // Stabalise for slow Access Points
        InitialiseWiFi();
    }
} // PublishDomoticzValues

// It is possible to post a Group of Values to a single Virtual Sensor and graph it (i.e. Voltage, Current, Wattage).
// This will require some coding in Domoticz (possible plugin/sensor type).  Feedback welcomed!.
// Publish to Domoticz EXAMPLE - Batch or Group Values Example to Virtual Sensor.  Update as needed.  Future WIP Option.
void PublishDomoticzATM(int Sensor_Index)
{
    if (Sensor_Index > 0)
    {
        if (wlan_client.connect(DomoticzServer, DomoticzPort))
        {
            // Green LED
            digitalWrite(LED_Green, LOW);

            Serial.print("Sending ATM Group Message to Domoticz #");
            Serial.print(Sensor_Index);

            wlan_client.print("GET /json.htm?type=command&param=udevice&idx=");
            wlan_client.print(Sensor_Index);

            // // Potential values to select from and batch post to a single sensor
            // wlan_client.print("&svalue=");
            // wlan_client.print(String(LineVoltage));
            // wlan_client.print(";");
            // wlan_client.print(String(LineCurrent));
            // wlan_client.print(";0;");
            // wlan_client.print(String(LineFrequency));
            // wlan_client.print(";0;");
            // wlan_client.print(String(ActivePower));
            // wlan_client.print(";0;");
            // wlan_client.print(String(ImportEnergy));
            // wlan_client.print(";0;");
            // wlan_client.print(String(ExportEnergy));
            // wlan_client.print(";0;");
            // wlan_client.print(String(PowerFactor));
            // wlan_client.print(";0;");
            // wlan_client.print(String(DCVoltage));
            // wlan_client.print(";0;");
            // wlan_client.print(String(TMPTemperature));
            // wlan_client.print(";0");

            /* Examples of Available Variables
            LineVoltage1, LineVoltage2, LineVoltage3, LineVoltageTotal, LineVoltageAverage
            LineCurrentCT1, LineCurrentCT2, LineCurrentCT3, LineCurrentCT4, LineCurrentCTN, LineCurrentTotal
            CalculatedPowerCT1, CalculatedPowerCT2, CalculatedPowerCT3, CalculatedPowerCT4, CalculatedPowerCTN, CalculatedTotalPower
            ActivePowerCT1, ActivePowerCT2, ActivePowerCT3, TotalActivePower, CalculatedTotalActivePower
            ActivePowerImportCT1, ActivePowerImportCT2, ActivePowerImportCT3, TotalActivePowerImport
            ActivePowerExportCT1, ActivePowerExportCT2, ActivePowerExportCT3, TotalActivePowerExport
            ReactivePowerCT1, ReactivePowerCT2, ReactivePowerCT3, TotalReactivePower, CalculatedTotalReactivePower
            ApparentPowerCT1, ApparentPowerCT2, ApparentPowerCT3, TotalApparentPower, CalculatedTotalApparentPower
            TotalActiveFundPower, TotalActiveHarPower
            PowerFactorCT1, PowerFactorCT2, PowerFactorCT3, TotalPowerFactor
            PhaseAngleCT1, PhaseAngleCT2, PhaseAngleCT3
            ChipTemperature, LineFrequency
            DCVoltage, TMPTemperature
            PWMLocalPower, PWMRemotePower, PWMPowerOutput, PWMPowerPercentage
            DACLocalPower, DACRemotePower, DACPowerPercentage, DACPowerOutput, DACVoltageOutput, DACChannelOutput

            *Control
            EnablePWMLocal, EnablePWMRemote, EnablePWMTestOutput
            EnableDACLocal, EnableDACRemote, EnableDACTestOutput
            */

            wlan_client.println(" HTTP/1.1");
            wlan_client.print("Host: ");
            wlan_client.print(DomoticzServer);
            wlan_client.print(":");

            wlan_client.println(DomoticzPort);
            wlan_client.println("User-Agent: Arduino-ethernet");
            wlan_client.println("Connection: close");
            wlan_client.println();

            wlan_client.stop();

            // Green LED
            digitalWrite(LED_Green, HIGH);
        }
        else
        {
            // Red LED
            digitalWrite(LED_Red, LOW);

            Serial.println("WiFi or Domoticz Server Not Connected");

            // Update OLED
            oled.clear();
            OLEDPrint("Error", 2, 0);
            OLEDPrint("Domoticz", 2, 2);
            oled.update();
            delay(1000);

            // Red LED
            digitalWrite(LED_Red, HIGH);

            // Stabalise for slow Access Points
            InitialiseWiFi();
        }
    }
} // PublishDomoticzATM
