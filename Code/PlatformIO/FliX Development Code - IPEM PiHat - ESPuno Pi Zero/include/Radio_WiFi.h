/*
  Dave Williams, DitroniX 2019-2025 (ditronix.net)
  Full header information in README

  This test code is OPEN SOURCE and formatted for easier viewing.  Although is is not intended for real world use, it may be freely used, or modified as needed.
  It is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.

  Further information, details and examples can be found on our website ditronix.net, github.com/DitroniX and hackster.io/DitroniX
*/

#ifndef Radio_WiFi_H
#define Radio_WiFi_H

// Libraries
#include <Arduino.h>
#include <Config.h> // User Configuration Variables
#include <WiFi.h>
#include <WiFiMulti.h>
#include <WiFiUdp.h>
#include <WiFiClient.h>

// ****************  VARIABLES / DEFINES / STATIC / STRUCTURES ****************

// WiFi Other
WiFiClient wlan_client;                   // Initialize the Client Library  / Client Instance
WiFiMulti wifiMulti;                      // Multiple WiFi Options - Auto Scanning
int WifiMaxAPScan = 6;                    // Multiple WiFi Scan Maximum APs (Default 5)
String HostNameHeader = AppAcronym + "-"; // Hostname Prefix
String HostName;                          // Hostname
// String RSSILevel;                         // WiFi RSSI Level Information
const uint32_t connectTimeoutMs = 10000; // WiFi connect timeout per AP. Increase when connecting takes longer.

// ######### FUNCTIONS #########

// Return Some Meaningful Information From RSSI
String RSSI_Info(int RSSI_Value)
{
    switch (-RSSI_Value) // Inverted dBm Level ;)
    {
        {
        case 0 ... 30:
            return "Signal Very Strong";
            break;
        case 31 ... 50:
            return "Signal Excellent";
            break;
        case 51 ... 60:
            return "Signal Healthy";
            break;
        case 61 ... 70:
            return "Signal Very Good";
            break;
        case 71 ... 80:
            return "Signal Good";
            break;
        case 81 ... 90:
            return "Signal Poor - Try Moving Position";
            break;
        case 91 ... 100:
            return "Signal Very Low! - Move Position";
            break;
        default:
            return "No Signal :(";
            break;
        }
    }

} // RSSI_Info

// Wifi Information
void DisplayWiFiConfiguration()
{

    // RSSIInformation();

    PrintUnderline("Connection Details:");
    Serial.println("WiFi SSID \t " + String(WiFi.SSID()) + " (Wifi Station Mode)");

    if (local_IP.toString() == WiFi.localIP().toString().c_str())
    {
        Serial.printf("WiFi IP \t %s (Static)\n", WiFi.localIP().toString().c_str());
    }
    else
    {
        Serial.printf("WiFi IP \t %s (DHCP)\n", WiFi.localIP().toString().c_str());
    }

    Serial.printf("WiFi MASK \t %s\n", WiFi.subnetMask().toString().c_str());
    Serial.printf("WiFi GW \t %s\n", WiFi.gatewayIP().toString().c_str());
    Serial.printf("WiFi DNS 1 \t %s\n", WiFi.dnsIP().toString().c_str());
    Serial.printf("WiFi DNS 2 \t %s\n", WiFi.dnsIP(1).toString().c_str());
    Serial.println("WiFi MAC \t " + WiFi.macAddress());
    Serial.printf("WiFi Hostname \t %s\n", WiFi.getHostname());
    Serial.println("WiFi RSSI \t " + String(WiFi.RSSI()) + " dBm (" + RSSI_Info(WiFi.RSSI()) + ")");

    Serial.println("");
} // DisplayWiFiConfiguration

// Force Hostname
void ForceHostName(void)
{
    HostName = HostNameHeader;
    HostName.concat(WiFi.macAddress().substring(WiFi.macAddress().length() - 5, WiFi.macAddress().length()));
    HostName.replace(":", "");
    WiFi.setHostname(HostName.c_str());
    HostName = WiFi.getHostname();
} // ForceHostName

// Configure Static IP address (if not 0.0.0.0)
void InitialiseStaticIP()

{
    if (local_IP.toString() != "0.0.0.0")
    {
        // Serial.printf("WiFI Current IP\t \t %s\n", WiFi.localIP().toString().c_str());

        if (primaryDNS.toString() != "0.0.0.0")
        {
            if (!WiFi.config(local_IP, gateway, subnet, primaryDNS, secondaryDNS))
                ;
            {

                Serial.println("STA Static IP Failed to configure");
            }
        }
        else // Use Gateway IP for DNS 1
        {
            if (!WiFi.config(local_IP, gateway, subnet, gateway, secondaryDNS))
            {
                Serial.println("STA Static IP Failed to configure");
            }
        }
    }
} // InitialiseStaticIP

// Initialise WiFi
void InitialiseWiFi()
{

    // WiFi Integration Status
    if (WiFi.status() == WL_CONNECTED)
    {
        Serial.println("Wi-Fi is Enabled");
    }
    else
    {
        Serial.println("Wi-Fi is Disabled");
    }

    // Connect or reconnect to WiFi
    if (WiFi.status() != WL_CONNECTED && strlen(ssid1))
    {

        // Green LED
        digitalWrite(LED_Green, LOW);

        // App and Starting...
        oled.clear();
        OLEDPrint(AppAcronym, 2, 0);
        OLEDPrint("Cnx Wi-Fi ", 2, 2);
        oled.update();

        // Wifi Settings
        WiFi.mode(WIFI_STA);
        WiFi.setAutoReconnect(true);
        WiFi.persistent(true);

        // Multi-WiFi Connections.  Add more as needed.
        if (strlen(ssid1))
            wifiMulti.addAP(ssid1, password1);
        if (strlen(ssid2))
            wifiMulti.addAP(ssid2, password2);
        if (strlen(ssid3))
            wifiMulti.addAP(ssid3, password3);

        Serial.println("Scanning WiFi Networks... Please wait...");
        int n = WiFi.scanNetworks();

        if (n == 0)
        {
            Serial.println("No Wi-FI Networks Found");
        }
        else
        {
            Serial.print(n);
            Serial.print(" x Wi-Fi Networks Found.\t");
            Serial.println("Scanning for " + String(WifiMaxAPScan) + " SSIDs Only.");
            for (int i = 0; i < n; ++i)
            {
                // Print SSID and RSSI for Each Network Found
                Serial.print(" ");
                Serial.print(i + 1);
                Serial.print(": ");
                Serial.printf("%25s", WiFi.SSID(i).c_str());
                Serial.print(" (");
                Serial.print(WiFi.RSSI(i));
                Serial.print(" dBm " + RSSI_Info(WiFi.RSSI(i)) + ")");
                Serial.println((WiFi.encryptionType(i) == WIFI_AUTH_OPEN) ? " " : "*");
                delay(10);

                // Do Not Unnecessarily Dither - Scan first X Access Points Only
                if (i >= (WifiMaxAPScan - 1))
                    break;
            }
        }

        // Connect to Wi-Fi using wifiMulti (connects to the SSID with strongest connection)
        Serial.println("\nConnecting WiFi...");

        // Auto Reconnect Timeout
        unsigned long ReconnectTimeout;
        ReconnectTimeout = millis();

        while (wifiMulti.run() != WL_CONNECTED)
        { // Wait for the Wi-Fi to connect: scan for Wi-Fi networks, and connect to the strongest of the networks above
            delay(500);
            Serial.print('.');

            // Auto Reboot if not connected in 1 minute.  Occassionally needed after reflash.
            // if ((millis() - ReconnectTimeout) > 60000UL)
                // ForceReboot();
        }

        // Green LED
        digitalWrite(LED_Green, HIGH);

        // if (wifiMulti.run() == WL_CONNECTED)
        {
            // // Stabalise for Slow Access Points
            // while (WiFi.status() != WL_CONNECTED)
            // {
            //     delay(500);
            //     Serial.print(".");
            // }

            Serial.println("Connected to " + String(WiFi.SSID()) + "\n");

            delay(500);

            // Force Local IP and Make Static
            InitialiseStaticIP();

            ForceHostName();

            // Wifi Information
            DisplayWiFiConfiguration();
            // }
        }
    }
} // InitialiseWiFi

#endif