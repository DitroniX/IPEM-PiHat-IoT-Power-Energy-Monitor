**IPEM PiHat and IPEM PiHat Lite | ATM90E36 IoT Power Energy Monitor SDK**

 - **Super exciting news that my first [KickStarter](https://www.kickstarter.com/projects/ditronix/ipem-raspberry-pihat-iot-atm90-mains-power-energy-monitor) project has been fully funded - so thank you all for your support.** 
 - [**Please feel free to take a moment and check it out!**]([url](https://www.kickstarter.com/projects/ditronix/ipem-raspberry-pihat-iot-atm90-mains-power-energy-monitor))

Based on the popular https://github.com/DitroniX/IPEM-IoT-Power-Energy-Monitor, the **IPEM PiHat** takes both IPEC and IPEM to another level via the Raspberry Pi.

[![KickStarter](https://github.com/DitroniX/DitroniX/blob/main/Files/KickStarter-SupportUs.png 'KickStarter')](https://www.kickstarter.com/projects/ditronix/ipem-raspberry-pihat-iot-atm90-mains-power-energy-monitor?ref=3vw3ge)

**These main GitHub pages and accompanying [Wiki](https://github.com/DitroniX/IPEM-PiHat-IoT-Power-Energy-Monitor/wiki) pages are being updated to include details of the production version of IPEM PiHat and PiHat Lite.**

**NOTE:** These boards have been put into production, fulfillment will be first made to KickStarter Pledges, then they will immediately be made available on [eBay] (https://www.ebay.co.uk/sch/i.html?_saslop=1&_ssn=ditronixuk&_dmd=2).  See updates below for timeline.

## Updates:

 - 25-04-08 - Boards Tested and pleased to sahre, that they are now being shipped to all Kickstarter backers.  
 - 25-04-02 - Production boards (Both Variants), in Production QA.  Delivery to me by early next week.  Final Check on Production boards upon arrival and then shipping to KickStarter Backers! Then added to eBay. Excellent.
 - 25-03-26 - Preproduction testing complete and Production boards (Both Variants), ordered.
 - 25-03-21 - Excellent news in that testing is almost complete.  This is a range of comprehensive testing of the both boards, various electrical testing and safety compliance.  Taken a few days longer than planned but all is good.  Production still planned for this month.
 - 25-03-14 - Testing the Preproduction boards. See this [YouTube Update](https://www.youtube.com/watch?v=YpOppCA2oIU&ab_channel=DitroniX)
 - 25-03-11 - Preproduction boards have arrived and now going through testing, with updates to Wiki on-route.
 - 25-03-05 - Preproduction boards being finalised in SMT manufacture.  Once these arrive, they can be fully tested in preparation for the production boards to be ordered.
 - 25-02-28 - All components are now available. Preproduction boards ordered and currently in Data Preparation.
 - 25-02-27 - Final BOM components are expected to arrive today and then the Preproduction boards will be immediately ordered.
 - 25-02-17 - Awaiting full BOM STK following Chinese NY Holiday.
   Preproduction boards can then be ordered/tested.
 - 25-02-14 - Preproduction IPEM PiHat and IPEM PiHat Lite boards are
   being ordered.
 - 25-02-05 - Example 3D renders of pre-production boards. Comparison
   Chart. 
 - 25-02-02 - Work now continues in supporting documentation, Wiki and
   software examples code.
 - 25-01-23 - Pre-production schematics have been finalised and the
   boards routed.
 - 25-01-17 - Collated feedback. Finalise Pre-production design of both IPEM
   PiHat and IPEM PiHat Lite.

As we steam ahead to production, just wanted to share some photos of the final pre-production version of the two great looking boards.

## Notable visual changes from original Beta which was shown on KickStarter.  These changes took constructive feedback, which helps users to get even more from the boards.

-   Improved layout
-   GPIO Expander
-   DIL Switches added to speed up configuration
-   Accurate RTC DS3231, with Battery Backup (CR2032) connection
-   Switchable Rogowski Inputs and filtering
-   LDO regulator to provide isolated 3V3 to each stacked board
-   Swapped DAC and ADC for improved SN ratio
-   Type C 5V DC input on PiHat Lite. This feeds into the two Raspberry Pi 5V GPIO Pins, so allowing you to power the whole system (single boards, or stacked), via Type C.

You can see the two boards and get an update on my [YouTube Update](https://www.youtube.com/watch?v=YpOppCA2oIU&ab_channel=DitroniX)

## IPEM PiHat - PreProduction

![IPEM PiHat - PreProduction](https://github.com/DitroniX/IPEM-PiHat-IoT-Power-Energy-Monitor/blob/main/Datasheets%20and%20Information/IPEM%20PiHat%201.2502.102%20PreProd.jpg)

![IPEM PiHat - PreProduction](https://github.com/DitroniX/IPEM-PiHat-IoT-Power-Energy-Monitor/blob/main/Datasheets%20and%20Information/IPEM%20PiHat%201.2502.102%20PreProd%20BTM.jpg)

## IPEM PiHat Lite - PreProduction

![IPEM PiHat Lite - PreProduction](https://github.com/DitroniX/IPEM-PiHat-IoT-Power-Energy-Monitor/blob/main/Datasheets%20and%20Information/IPEM%20PiHat%20Lite%201.2502.102%20PreProd.jpg)

![IPEM PiHat Lite - PreProduction](https://github.com/DitroniX/IPEM-PiHat-IoT-Power-Energy-Monitor/blob/main/Datasheets%20and%20Information/IPEM%20PiHat%20Lite%201.2502.102%20PreProd%20BTM.jpg)


-------------------------------------------------------------------

**Board Addressing**
   
The IPEM board uses SPI as a means of data communication, with an I2C expander to provide individual GPIO functionality to each ATM90E36.

Following design thoughts prior to finalising the production board, the following improvements have been added.

Change from OneWire to using a two wire I2C Expander. This provides 64 individual addresses, so essentially 64 stacked IPEM's (although this is theoretical).

The design improvement is a much more sensible route as you now assign a fixed address to each board using a DIP switch. This also makes it so much easier is field and with software support and configuration.

The unique design will allow up to a max of:

* 1 x IPEM PiHat + 63 x IPEM PiHat Lite's

or

* 64 x IPEM PiHat Lite's
   
 **CT Clamps and Rogowski Current Transformer**
 
The original IPEM design provided for using the  YHDC SCT-013 100A-50mA.

The updated IPEM PiHat and IPEM PiHat Lite production design, now allows for either use of CT Clamps, and/or Rogowski Current Transformers.  This allows for a wider spectrum of current ranges and cable sizes to be monitored.

 - CT Clamps are the main stream safe and easy method to monitor currents from the mains tails or consumer unit circuits.
   
 - Rogowski Current Transformers are typically for very high currents, or specialised current monitoring.

 **The Prototype Board**

![IPEM PiHat - Beta Preview](https://github.com/DitroniX/IPEM-PiHat-IoT-Power-Energy-Monitor/blob/main/Datasheets%20and%20Information/DitroniX.net%20Raspberry%20Pi%205%20-%20IPEM%20Power%20Energy%20Monitor%20Board.jpg)
IPEM Raspberry Pi PiHat ATM90E36 Energy Monitor 

![IPEM PiHat - Beta Preview](https://github.com/DitroniX/IPEM-PiHat-IoT-Power-Energy-Monitor/blob/main/Datasheets%20and%20Information/DitroniX.net%20Raspberry%20Pi%205%20-IPEM%20Power%20Energy%20Monitor%20-%20Side%20View.jpg)
IPEM Raspberry Pi PiHat ATM90E36 Energy Monitor 

The IPEM Raspberry Pi PiHat ATM90E36 IoT Power Energy Monitor SDK contains all of the IPEM (ESP32) functionality and includes the ATM90E36.  It then adds the ADC and DAC functionality of IPEC and IPEX (ESP32) boards.

The ATM90E36 contains all of the ATM90E32 functions plus additional functionality, and so will be the main release.

![IPEM PiHat - Beta Overview](https://github.com/DitroniX/IPEM-PiHat-IoT-Power-Energy-Monitor/blob/main/Datasheets%20and%20Information/DitroniX.net%20IPEM%20Raspberry%20Pi%20PiHat%20Power%20Energy%20Monitor%20Board%20SDK%20Interfaces.jpg)

**Overview**
![IPEM PiHat - Beta Overview](https://github.com/DitroniX/IPEM-PiHat-IoT-Power-Energy-Monitor/blob/main/Datasheets%20and%20Information/DitroniX.net%20IPEM%20Raspberry%20Pi%20PiHat%20Power%20Energy%20Monitor%20Board%20SDK%20Overview.png)

**Mains Monitoring Options**

All my boards are designed to be safe and easy to use - with NO live parts or dangerous exposed voltages.

Both the **IPEM PiHat** and **IPEM PiHat Lite** are capable of monitoring a number of variations in energy monitoring systems.

 - Single phase (Home, Office etc.) 
 - Multiple Single Phases.  (Different circuits or home/office rings, Inverters etc.) 
 - Dual Phase (2 x Live -Typically for USA.  i.e. 2 x 110V) 
 - Three Phase Star (3 x Live and 1 x Neutral) 
 - Three Phase Delta (3 x Live)

## Top Level **PREVIEW** Features:

IPEM PiHat is available in two variants:

* IPEM PiHat
* IPEM PiHat Lite

A comparison table is available [Comparison Table](https://github.com/DitroniX/IPEM-PiHat-IoT-Power-Energy-Monitor/wiki/Comparison-Table)

-   **Compact**  and  **Flexible Design**  SDK Board
    -   All connections are  **low voltage**, for  **safe operation**
    -   **Easy to interface**
    -   Designed to fit on a Raspberry Pi
    -   Designed to easily Interface other MCUs
-    **ATM90E36**  Energy Monitor
        - Measures Currents
            -   Single phase
            -   Two phase
            -   Dual phase
            -   Split phase
            -   Three-phase four-wire (3P4W, Y0)
            -   Three-phase three-wire (3P3W, Y or Δ), systems.
        - 3 x Phases Line CT Clamp Input
            -   Example YHDC SCT013000
        - 1 x Phase Neutral CT Clamp
            -   Example YHDC SCT013000
            -   Only Required for Three-phase four-wire (3P4W)
        - 3 x Voltage Inputs (AC RMS)
            - Single Phases use same AC Input on all three
            - Three Phase use separate AC Input on each
        - DMA Mode (Logging via SPI)
            - Power Modes Settings
            - Auto DMA selection option via GPIO
            - SPI Interface
-   **PCA9671**  GPIO Expander
    -   I2C GPIO Expander
    -   Up to 64 Addresses
    -   Allows Stacking of IPEM PiHat Lite
    -   Controls the ATM90E36 /CS and GPIO
    -   I2C Interface
-   **DS3231**  RTC
    -   Accurate Real Time Clock
    -   Battery Back Up Option
    -   I2C Interface
-   **24C64**  EEPROM
    -   Parameter Settings
    -   Logging
    -   I2C Interface
 - **MCP4728** DAC
	 - 12bit I2C DAC
	 - Four Independent Buffered Output Channels
	 - Configured for Default DAC Out, or Modulated (Example MPPT)
		 - Configurable Solder Pads
	 - On-Board DAC EEPROM (For DAC Codes and Addressing)
	 - Can be configured to drive DAC based on CT Clamp Current / Power
    -   I2C Interface
 - **ADS1115** ADC
	 - 16bit I2C DAC 
	 - Independent Analogue Inputs
		 - 4 x Single Ended
		 - 2 x Differential Pairs
    -   I2C Interface
-   **OLED I2C**
    -   I2C Interface
    -   OLED I2C Connector
        -   Configurable Power Pins
-   **AC Low Voltage**  Input (for Safety)
    -   Power safely derived from a SELV / Wall AC/AC Power Supply
        -   8 to 12V AC RMS
        -   Examples GreenBrook DAT01A or TLC TC TR7
-   **TMP102** Temperature 
    -   Digital Ambient Temperature Monitor
    -   I2C Interface
-   **Isolated Outputs**
    -   Two Relays for Isolated NC or NO outputs
    -   Max 2A 30V DC
    -   Interfaces to GPIO Expander
-   **Programmable Button** User  
    -   User General Use
    -   Interfaces to GPIO Expander
-   **Solder Pads** User  
    -   User Configuration General Use
    -   2 x Solder Pads
    -   Interfaces to GPIO Expander
-   **RGB Status LED** User  
    -   User Configurable
    -   Interfaces to GPIO Expander
-   **Power LED**
    -   On 3V3
-   **ATM CT LEDs**
    -   CF1 - Active
    -   CF2 - ReActive
    -   CF3 - Fundamental
    -   CF4 - Harmonic
-   **IPEM PiHat Power**
    -   Designed to take 5V power from Raspberry Pi Header
    -   Internal 5V to 3V3 LDO Power Supply
-   **IPEM PiHat Lite Power**
    -   Designed to take 5V power from Raspberry Pi Header
    -   Internal 5V to 3V3 LDO Power Supply
    -   Can be powered via Type C UCB
	    - This also feeds 5V to Pi Header (Raspberry Pi), and other stacked PiHat boards.
-   **PCB** designed the same size as a Raspberry Pi.
    -   Also allows for the optional OLED display to be included, or not.
    -   Size**  85 mm x 55 mm
------------

**In The Box - [Ship Kit](https://github.com/DitroniX/IPEM-PiHat-IoT-Power-Energy-Monitor/wiki/IPEM-PiHat-Ship-Kit)**

In the Box for IPEM PiHat

 - 1 x IPEM PiHat 	
	 - SMD (Surface Mounted Components) Populated / Tested.
	 - 1 x Terminal Blocks (4 Pin Not Soldered) 
	 - 1 x 40 Pin 2x20 Header (Not Soldered) 
	 - 4 x Sets of M2.5 x 18 Pillar, Pan Heads and Nuts 
	 - 2 x 6 pin JST Pigtail (Open Ended for ADC/DAC) 
	 - 1 x Strip of straight pin header (Not Soldered) 
	 - 1 x 4 pin header socket (Not Soldered) 
	 - 1 x Complimentary screwdriver

In the Box for IPEM PiHat Lite

 - 1 x IPEM PiHat Lite	
	 - SMD (Surface Mounted Components) Populated / Tested.
	 - 1 x Terminal Blocks (4 Pin Not Soldered) 
	 - 1 x 40 Pin 2x20 Header (Not Soldered) 
	 - 4 x Sets of M2.5 x 15 Pillar, Pan Heads and Nuts 
	 - 1 x Strip of straight pin header (Not Soldered) 
	 - 1 x 4 pin header socket (Not Soldered) 
	 - 1 x Complimentary screwdriver


You will need to provide a CT Current Clamp. Ideally a YHDC SCT-013-000.  A Rogowski Current Transformer maybe used for very high currents or specialist measurements.

All test code is OPEN SOURCE and although is is not intended for real world use, it may be freely used, or modified as needed. It is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.

## **Purchase**
[![Display-Type-B](https://raw.githubusercontent.com/DitroniX/DitroniX/main/Files/DitroniX.net%20STEM%20IoT%20eBay.jpg?raw=true)](https://www.ebay.co.uk/usr/ditronixuk)

Our STEM SDK boards and accessories are available from our online shops on [eBay](https://www.ebay.co.uk/usr/ditronixuk) 
## **Further Information**

Additional information, and other technical details on this project, maybe found in the related repository pages.

**Repository Folders**

 - **Code** *(Code examples for Raspberry Pi, Arduino  IDE and PlatformIO)*
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
