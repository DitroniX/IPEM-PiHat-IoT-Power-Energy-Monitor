**IPEM PiHat ATM90E32 ATM90E36 IoT Power Energy Monitor SDK** - PREVIEW

Based on the popular https://github.com/DitroniX/IPEM-IoT-Power-Energy-Monitor, the **IPEM PiHat** takes both IPEC and IPEM to another level via the Raspberry Pi.

***SDK available - January 2025***   Please contact us for further details.

![IPEM PiHat - Beta Preview](https://github.com/DitroniX/IPEM-PiHat-IoT-Power-Energy-Monitor/blob/main/Datasheets%20and%20Information/IPEM%20PiHat%20ATM90E32%20ATM90E36%20Beta%20Preview.png)

The **IPEM PiHat ATM90E32 ATM90E36 IoT Power Energy Monitor SDK** contains all of the IPEM functionality, except the ESP32, and includes either the ATM90E32 or ATM90E36, then adds the ADC and DAC functionality of IPEC and IPEX.

![IPEM PiHat - Beta Overview](https://github.com/DitroniX/IPEM-PiHat-IoT-Power-Energy-Monitor/blob/main/Datasheets%20and%20Information/DitroniX.net%20IPEM%20PiHat%20Power%20Energy%20Monitor%20Board%20SDK.png)

**Mains Monitoring Options**

All my boards are designed to be safe and easy to use - with NO live parts or dangerous exposed voltages.

The IPEM and IPEC series are capable of monitoring a number of variations in energy monitoring systems.

 - Single phase (Home, Office etc.) 
 - Multiple Single Phases.  (Different circuits or home/office rings, Inverters etc.) 
 - Dual Phase (2 x Live -Typically for USA.  i.e. 2 x 110V) 
 - Three Phase Star (3 x Live and 1 x Neutral) [Needs ATM90E36 version] 
 - Three Phase Delta (3 x Live)

Top Level **PREVIEW** Features:

The  **IPEM PiHat IoT Power Energy Monitor**  board main features:

-   **Compact**  and  **Flexible Design**  SDK Board
    -   All connections are  **low voltage**, for  **safe operation**
    -   **Easy to interface**
-   _Designed to fit on a Raspberry Pi
-   _Optional_  **ATM90E**  Series
    -   **ATM90E32**  Energy Monitor
        -   3 x Phases Line CT Clamp Input
            -   Example YHDC SCT013000
        -   3 x Voltage Inputs (AC RMS)
        -   Power Modes Settings
    -   **ATM90E36**  Energy Monitor
        -   3 x Phases Line CT Clamp Input
            -   Example YHDC SCT013000
        -   3 x Voltage Inputs (AC RMS)
        -   1 x Phase Neutral CT Clamp
        -   DMA Mode (Logging via SPI)
        -   Power Modes Settings
        -   Auto DMA selection opton via GPIO
-   **24C64**  EEPROM
    -   Parameter Settings
    -   Logging
 - **MCP4728** DAC
	 - 12bit I2C DAC
	 - Four Independent Buffered Output Channels
	 - Configured for Default DAC Out, or Modulated (Example MPPT)
		 - Configurable Solder Pads
	 - On-Board DAC EEPROM (For DAC Codes and Addressing)
	 - Can be configured to drive DAC based on CT Clamp Current / Power
 - **ADS1115** ADC
	 - 16bit I2C DAC 
-   **OLED I2C**
    -   I2C Interface
    -   OLED I2C Connector
        -   Configurable Power Pins
-   **AC Low Voltage**  Input (for Safety)
    -   Power safely derived from a SELV / Wall AC/AC Power Supply
        -   8 to 12V AC RMS
        -   Examples GreenBrook DAT01A or TLC TC TR7
-   On Board  **NTC**  (Temperature)
-   **Isolated Outputs**
    -   Two Relays for Isolated NC or NO outputs
    -   Max 2A 30V DC or 0.5A 240V AC
-   User  **Programmable Button**
-   **RGB Status LED**
    -   User Configurable
-   **Power LED**
    -   On 3V3
-   **ATM CT LEDs**
    -   CF1 - Active
    -   CF2 - ReActive
    -   CF3 - Fundamental
    -   CF4 - Harmonic
-   **PCB** designed the same size as a Raspberry Pi.
    -   Also allows for the optional OLED display to be included, or not.
    -   Size**  85 mm x 55 mm


------------

**In The Box**

Details to follow.

You will need to provide a CT Current Clamp. Ideally YHDC SCT-013-000

All test code is OPEN SOURCE and although is is not intended for real world use, it may be freely used, or modified as needed. It is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.

## **Purchase**
[![Display-Type-B](https://raw.githubusercontent.com/DitroniX/DitroniX/main/Files/DitroniX.net%20STEM%20IoT%20eBay.jpg?raw=true)](https://www.ebay.co.uk/usr/ditronixuk)

Our STEM SDK boards and accessories are available from our online shops on [eBay](https://www.ebay.co.uk/usr/ditronixuk) 
## **Further Information**

Additional information, and other technical details on this project, maybe found in the related repository pages.

**Repository Folders**

 - **Code** *(Code examples for Arduino  IDE and PlatformIO)*
 -  **Datasheets and Information** *(Component Datasheets, Schematics, Board Layouts, Photos, Technical Documentation)*
 - **Certification** *(Related Repository Project or Part, Certification Information)*

**Repository Tabs**

 - **Wiki** *(Related Repository Wiki pages and Technical User Information)*
 - **Discussions** *(Related Repository User Discussion Forum)*
 - **Issues** *(Related Repository Technical Issues and Fixes)*

***

We value our Customers, Users of our designs and STEM Communities, all over the World . Should you have any other questions, or feedback to share to others, please feel free to:

* Visit the related [Project](https://github.com/DitroniX?tab=repositories) *plus the related* **Discussions** and **Wiki** Pages.  See tab in each separate repository.
* **Project Community Information** can be found at https://www.hackster.io/DitroniX
* [DitroniX.net Website - Contact Us](https://ditronix.net/contact/)
* **Twitter**: [https://twitter.com/DitroniX](https://twitter.com/DitroniX)
* [Supporting the STEM Projects - BuyMeACoffee](https://www.buymeacoffee.com/DitroniX)
*  **LinkedIN**: [https://www.linkedin.com/in/g8puo/](https://www.linkedin.com/in/g8puo/)

***Dave Williams, Maidstone, UK.***

Electronics Engineer | Software Developer | R&D Support | RF Engineering | Product Certification and Testing | STEM Ambassador

## STEM

**Supporting [STEM Learning](https://www.stem.org.uk/)**

Life is one long exciting learning curve, help others by setting the seed to knowledge.

![DitroniX Supporting STEM](https://hackster.imgix.net/uploads/attachments/1606838/stem_ambassador_-_100_volunteer_badge_edxfxlrfbc1_bjdqharfoe1_xbqi2KUcri.png?auto=compress%2Cformat&w=540&fit=max)
