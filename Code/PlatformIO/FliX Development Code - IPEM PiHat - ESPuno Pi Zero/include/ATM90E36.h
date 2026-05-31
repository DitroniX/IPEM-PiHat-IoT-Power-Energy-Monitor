/*
  Dave Williams, DitroniX 2019-2025 (ditronix.net)
  Full header information in README

  This test code is OPEN SOURCE and formatted for easier viewing.  Although is is not intended for real world use, it may be freely used, or modified as needed.
  It is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.

  Further information, details and examples can be found on our website ditronix.net, github.com/DitroniX and hackster.io/DitroniX
*/

#ifndef ATM90E36_h
#define ATM90E36_h

// Libraries
#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>

// ****************  VARIABLES / DEFINES / STATIC / STRUCTURES / CONSTANTS ****************

// **************** DEFINE VOLTAGE REFERENCE ****************

// Read this page for IPEM PiHat and IPEM PiHat Lite 
// https://github.com/DitroniX/IPEM-PiHat-IoT-Power-Energy-Monitor/wiki/AC-Mains-Voltage-Sense-Input 

#define ATM_SINGLEVOLTAGE true // Set to true to use V1/ATM_V1P for VoltageGain1, VoltageGain2, VoltageGain3 and Calculations for CT1, CT2, CT3, CT4, CTN.  (Default true)

// **************** DEFINE PHASE TYPE ****************
#define ATM_SPLITPHASE false // If Split Phase (i.e. USA 120+120), set to true else leave false (NB. Not fully tested). ATM_SINGLEVOLTAGE = false

// **************** DEFINE STATUS REGISTERS ****************
#define SoftReset 0x00	 // Software Reset
#define SysStatus0 0x01	 // System Status0
#define SysStatus1 0x02	 // System Status1
#define FuncEn0 0x03	 // Function Enable0
#define FuncEn1 0x04	 // Function Enable1
#define ZXConfig 0x07	 // Zero-Crossing Config
#define SagTh 0x08		 // Voltage Sag Th
#define PhaseLossTh 0x09 // Voltage Phase Losing Th
#define INWarnTh0 0x0A	 // N Current Line Th
#define INWarnTh1 0x0B	 // Voltage ADC Th
#define THDNUTh 0x0C	 // Voltage THD Th
#define THDNITh 0x0D	 // Current THD Th
#define DMACtrl 0x0E	 // DMA Int. Control
#define LastSPIData 0x0F // Last Read/Write SPI Value

// **************** LOW POWER MODE REGISTERS - NOT USED - COMMON TO BOTH ATM90E36 ****************
#define DetectCtrl 0x10	  // Current Detect Controller
#define DetectTh1 0x11	  // Channel 1 Currrent Threshold in Detection Mode
#define DetectTh2 0x12	  // Channel 2 Currrent Threshold in Detection Mode
#define DetectTh3 0x13	  // Channel 3 Currrent Threshold in Detection Mode
#define PMoffsetCT1 0x14  // loffset for Phase A in Partial Measurment Mode
#define PMoffsetCT2 0x15  // loffset for Phase B in Partial Measurment Mode
#define PMoffsetCT3 0x16  // loffset for Phase C in Partial Measurment Mode
#define PMPGA 0x17		  // OGAgain Configuration in in Partial Measurment Mode
#define PMIRMSCT1 0x18	  // irms for Phase A in Partial Measurment Mode
#define PMIRMSCT2 0x19	  // irms for Phase B in Partial Measurment Mode
#define PMIRMSCT3 0x1A	  // irms for Phase C in Partial Measurment Mode
#define PMConfig 0x10B	  // Measure COnfiguraiton in Partial Measurment Mode
#define PMAvgSamples 0x1C // Number of 8K samples to be averages in RMS/mean computation
#define PMIRMSLSB 0x1D	  // LSB  bits of PMRRrms(A/B/C)

// **************** CONFIGURATION REGISTERS ****************
#define ConfigStart 0x30 // Configuration Start
#define PLconstH 0x31	 // High Word of PL_Constant
#define PLconstL 0x32	 // Low Word of PL_Constant
#define MMode0 0x33		 // Metering Mode Config
#define MMode1 0x34		 // Metering Mode Config
#define PStartTh 0x35	 // Startup Power Th (P)
#define QStartTh 0x36	 // Startup Power Th (Q)
#define SStartTh 0x37	 // Startup Power Th (S)
#define PPhaseTh 0x38	 // Startup Power Accum Th (P)
#define QPhaseTh 0x39	 // Startup Power Accum Th (Q)
#define SPhaseTh 0x3A	 // Startup Power Accum Th (S)
#define CSZero 0x3B		 // Checksum 0

// **************** CALIBRATION REGISTERS ****************
#define CalStart 0x40	// Cal Start
#define PoffsetCT1 0x41 // CT1 Line Power Offset (P)
#define QoffsetCT1 0x42 // CT1 Line Power Offset (Q)
#define PoffsetCT2 0x43 // CT2 Line Power Offset (P)
#define QoffsetCT2 0x44 // CT2 Line Power Offset (Q)
#define PoffsetCT3 0x45 // CT3 Line Power Offset (P)
#define QoffsetCT3 0x46 // CT3 Line Power Offset (Q)
#define GainCT1 0x47	// CT1 Line Calibration Gain
#define PhiCT1 0x48		// CT1 Line Calibration Angle
#define GainCT2 0x49	// CT2 Line Calibration Gain
#define PhiCT2 0x4A		// CT2 Line Calibration Angle
#define GainCT3 0x4B	// CT3 Line Calibration Gain
#define PhiCT3 0x4C		// CT3 Line Calibration Angle
#define CSOne 0x4D		// Checksum 1

// **************** FUNDAMENTAL/HARMONIC & ENERGY CALIBRATION REGISTERS ****************
#define HaRMStart 0x50	 // Harmonic Cal Start
#define PoffsetCT1F 0x51 // CT1 Fund Power Offset (P)
#define PoffsetCT2F 0x52 // CT2 Fund Power Offset (P)
#define PoffsetCT3F 0x53 // CT3 Fund Power Offset (P)
#define PGainCT1F 0x54	 // CT1 Fund Power Gain (P)
#define PGainCT2F 0x55	 // CT2 Fund Power Gain (P)
#define PGainCT3F 0x56	 // CT3 Fund Power Gain (P)
#define CSTwo 0x57		 // Checksum 2

// **************** MEASUREMENT CALIBRATION REGISTERS ****************
#define AdjStart 0x60	// Measurement Cal Start
#define UGainCT1 0x61	// CT1 Voltage RMS Gain
#define IGainCT1 0x62	// CT1 Current RMS Gain
#define UoffsetCT1 0x63 // CT1 Voltage Offset
#define IoffsetCT1 0x64 // CT1 Current Offset
#define UGainCT2 0x65	// CT2 Voltage RMS Gain
#define IGainCT2 0x66	// CT2 Current RMS Gain
#define UoffsetCT2 0x67 // CT2 Voltage Offset
#define IoffsetCT2 0x68 // CT2 Current Offset
#define UGainCT3 0x69	// CT3 Voltage RMS Gain
#define IGainCT3 0x6A	// CT3 Current RMS Gain
#define UoffsetCT3 0x6B // CT3 Voltage Offset
#define IoffsetCT3 0x6C // CT3 Current Offset
#define IgainN 0x6D		// N Current Gain
#define IoffsetN 0x6E	// N Current Offset
#define CSThree 0x6F	// Checksum 3

// **************** ENERGY REGISTERS - COMMON TO BOTH ATM90E36 ****************
#define APenergyT 0x80	 // Total Forward Active
#define APenergyCT1 0x81 // CT1 Forward Active
#define APenergyCT2 0x82 // CT2 Forward Active
#define APenergyCT3 0x83 // CT3 Forward Active
#define ANenergyT 0x84	 // Total Reverse Active
#define ANenergyCT1 0x85 // CT1 Reverse Active
#define ANenergyCT2 0x86 // CT2 Reverse Active
#define ANenergyCT3 0x87 // CT3 Reverse Active
#define RPenergyT 0x88	 // Total Forward Reactive
#define RPenergyCT1 0x89 // CT1 Forward Reactive
#define RPenergyCT2 0x8A // CT2 Forward Reactive
#define RPenergyCT3 0x8B // CT3 Forward Reactive
#define RNenergyT 0x8C	 // Total Reverse Reactive
#define RNenergyCT1 0x8D // CT1 Reverse Reactive
#define RNenergyCT2 0x8E // CT2 Reverse Reactive
#define RNenergyCT3 0x8F // CT3 Reverse Reactive

#define SAenergyT 0x90	// Total Apparent Energy
#define SenergyCT1 0x91 // CT1 Apparent Energy
#define SenergyCT2 0x92 // CT2 Apparent Energy
#define SenergyCT3 0x93 // CT3 Apparent Energy

#define SVenergyT 0x94 // Total Apparent Energy (Arit)

#define EnStatus0 0x95 // Metering Status 0
#define EnStatus1 0x96 // Metering Status 1
///////////////// 0x97	    // Reserved Register
#define SVmeanT 0x98	// Total Apparent Energy (Vect)
#define SVmeanTLSB 0x99 // LSB of Vector Sum

// **************** FUNDAMENTAL / HARMONIC ENERGY REGISTERS - COMMON TO BOTH ATM90E36 ****************
#define APenergyTF 0xA0	  // Total Forward Fund. Energy
#define APenergyCT1F 0xA1 // CT1 Forward Fund. Energy
#define APenergyCT2F 0xA2 // CT2 Forward Fund. Energy
#define APenergyCT3F 0xA3 // CT3 Forward Fund. Energy
#define ANenergyTF 0xA4	  // Total Reverse Fund Energy
#define ANenergyCT1F 0xA5 // CT1 Reverse Fund. Energy
#define ANenergyCT2F 0xA6 // CT2 Reverse Fund. Energy
#define ANenergyCT3F 0xA7 // CT3 Reverse Fund. Energy
#define APenergyTH 0xA8	  // Total Forward Harm. Energy
#define APenergyCT1H 0xA9 // CT1 Forward Harm. Energy
#define APenergyCT2H 0xAA // CT2 Forward Harm. Energy
#define APenergyCT3H 0xAB // CT3 Forward Harm. Energy
#define ANenergyTH 0xAC	  // Total Reverse Harm. Energy
#define ANenergyCT1H 0xAD // CT1 Reverse Harm. Energy
#define ANenergyCT2H 0xAE // CT2 Reverse Harm. Energy
#define ANenergyCT3H 0xAF // CT3 Reverse Harm. Energy

// **************** POWER & P.F. REGISTERS - COMMON TO BOTH ATM90E36 ****************
#define PmeanT 0xB0	   // Total Mean Power (P)
#define PmeanCT1 0xB1  // CT1 Mean Power (P)
#define PmeanCT2 0xB2  // CT2 Mean Power (P)
#define PmeanCT3 0xB3  // CT3 Mean Power (P)
#define QmeanT 0xB4	   // Total Mean Power (Q)
#define QmeanCT1 0xB5  // CT1 Mean Power (Q)
#define QmeanCT2 0xB6  // CT2 Mean Power (Q)
#define QmeanCT3 0xB7  // CT3 Mean Power (Q)
#define SmeanT 0xB8	   // Total Mean Power (S)
#define SmeanCT1 0xB9  // CT1 Mean Power (S)
#define SmeanCT2 0xBA  // CT2 Mean Power (S)
#define SmeanCT3 0xBB  // CT3 Mean Power (S)
#define PFmeanT 0xBC   // Mean Power Factor
#define PFmeanCT1 0xBD // CT1 Power Factor
#define PFmeanCT2 0xBE // CT2 Power Factor
#define PFmeanCT3 0xBF // CT3 Power Factor

// **************** POWER & P.F. REGISTERS - COMMON TO BOTH ATM90E36 ****************
#define PmeanTLSB 0xC0	 // Lower Word (Tot. Act. Power)
#define PmeanCT1LSB 0xC1 // Lower Word (CT1 Act. Power)
#define PmeanCT2LSB 0xC2 // Lower Word (CT2 Act. Power)
#define PmeanCT3LSB 0xC3 // Lower Word (CT3 Act. Power)
#define QmeanTLSB 0xC4	 // Lower Word (Tot. React. Power)
#define QmeanCT1LSB 0xC5 // Lower Word (CT1 React. Power)
#define QmeanCT2LSB 0xC6 // Lower Word (CT2 React. Power)
#define QmeanCT3LSB 0xC7 // Lower Word (CT3 React. Power)
#define SAmeanTLSB 0xC8	 // Lower Word (Tot. App. Power)
#define SmeanCT1LSB 0xC9 // Lower Word (CT1 App. Power)
#define SmeanCT2LSB 0xCA // Lower Word (CT2 App. Power)
#define SmeanCT3LSB 0xCB // Lower Word (CT3 App. Power)

// **************** FUND/HARM POWER & V/I RMS REGISTERS - COMMON TO BOTH ATM90E36 ****************
#define PmeanTF 0xD0   // Total Active Fund. Power
#define PmeanCT1F 0xD1 // CT1 Active Fund. Power
#define PmeanCT2F 0xD2 // CT2 Active Fund. Power
#define PmeanCT3F 0xD3 // CT3 Active Fund. Power
#define PmeanTH 0xD4   // Total Active Harm. Power
#define PmeanCT1H 0xD5 // CT1 Active Harm. Power
#define PmeanCT2H 0xD6 // CT2 Active Harm. Power
#define PmeanCT3H 0xD7 // CT3 Active Harm. Power
#define URMSCT1 0xD9   // CT1 RMS Voltage
#define URMSCT2 0xDA   // CT2 RMS Voltage
#define URMSCT3 0xDB   // CT3 RMS Voltage
#define IRMSN 0xDC	   // Calculated N RMS Current
#define IRMSCT1 0xDD   // CT1 RMS Current
#define IRMSCT2 0xDE   // CT2 RMS Current
#define IRMSCT3 0xDF   // CT3 RMS Current

// **************** FUND/HARM POWER & V/I RMS REGISTERS - COMMON TO BOTH ATM90E36 ****************
#define PmeanTFLSB 0xE0	  // Lower Word (Tot. Act. Fund. Power)
#define PmeanCT1FLSB 0xE1 // Lower Word (CT1 Act. Fund. Power)
#define PmeanCT2FLSB 0xE2 // Lower Word (CT2 Act. Fund. Power)
#define PmeanCT3FLSB 0xE3 // Lower Word (CT3 Act. Fund. Power)
#define PmeanTHLSB 0xE4	  // Lower Word (Tot. Act. Harm. Power)
#define PmeanCT1HLSB 0xE5 // Lower Word (CT1 Act. Harm. Power)
#define PmeanCT2HLSB 0xE6 // Lower Word (CT2 Act. Harm. Power)
#define PmeanCT3HLSB 0xE7 // Lower Word (CT3 Act. Harm. Power)
///////////////// 0xE8	    // Reserved Register
#define URMSCT1LSB 0xE9 // Lower Word (CT1 RMS Voltage)
#define URMSCT2LSB 0xEA // Lower Word (CT2 RMS Voltage)
#define URMSCT3LSB 0xEB // Lower Word (CT3 RMS Voltage)
///////////////// 0xEC	    // Reserved Register
#define IRMSCT1LSB 0xED // Lower Word (CT1 RMS Current)
#define IRMSCT2LSB 0xEE // Lower Word (CT2 RMS Current)
#define IRMSCT3LSB 0xEF // Lower Word (CT3 RMS Current)

// **************** PEAK, FREQUENCY, ANGLE & TEMP REGISTERS ****************
#define THDNUCT1 0xF1 // CT1 Voltage THD+N
#define THDNUCT2 0xF2 // CT2 Voltage THD+N
#define THDNUCT3 0xF3 // CT3 Voltage THD+N
///////////////// 0xF4	    // Reserved Register
#define THDNICT1 0xF5  // CT1 Current THD+N
#define THDNICT2 0xF6  // CT2 Current THD+N
#define THDNICT3 0xF7  // V Current THD+N
#define Freq 0xF8	   // Frequency
#define PAngleCT1 0xF9 // CT1 Mean Phase Angle
#define PAngleCT2 0xFA // CT2 Mean Phase Angle
#define PAngleCT3 0xFB // CT3 Mean Phase Angle
#define Temp 0xFC	   // Measured Temperature
#define UangleCT1 0xFD // CT1 Voltage Phase Angle
#define UangleCT2 0xFE // CT2 Voltage Phase Angle
#define UangleCT3 0xFF // CT3 Voltage Phase Angle

// **************** CLASS ****************

class ATM90E36
{
private:
	unsigned short CommEnergyIC(unsigned char RW, unsigned short address, unsigned short val);
	int _cs;
	unsigned short _lineFreq;
	unsigned short _pgagain;
	unsigned short _uGainCT1;
	unsigned short _uGainCT2;
	unsigned short _uGainCT3;
	unsigned short _iGainCT1;
	unsigned short _iGainCT2;
	unsigned short _iGainCT3;
	unsigned short _igainN;

	int Read32Register(signed short regh_addr, signed short regl_addr);

public:
	/* Construct */
	ATM90E36(void);
	/* Destruct */
	~ATM90E36(void);

	/* Initialization Functions */
	void begin(unsigned short lineFreq, unsigned short pgagain, unsigned short uGainCT1, unsigned short uGainCT2, unsigned short uGainCT3, unsigned short iGainCT1, unsigned short iGainCT2, unsigned short iGainCT3, unsigned short igainN);

	double
	CalculateVIOffset(unsigned short regh_addr, unsigned short regl_addr /*, unsigned short offset_reg*/);
	double CalculatePowerOffset(unsigned short regh_addr, unsigned short regl_addr /*, unsigned short offset_reg*/);
	double CalibrateVI(unsigned short reg, unsigned short actualVal);

	/* Main Electrical Parameters (GET)*/
	double GetLineVoltage1();
	double GetLineVoltage2();
	double GetLineVoltage3();

	double GetLineCurrentCT1();
	double GetLineCurrentCT2();
	double GetLineCurrentCT3();
	double GetLineCurrentCTN();

	double GetActivePowerCT1();
	double GetActivePowerCT2();
	double GetActivePowerCT3();
	double GetTotalActivePower();

	double GetReactivePowerCT1();
	double GetReactivePowerCT2();
	double GetReactivePowerCT3();
	double GetTotalReactivePower();

	double GetApparentPowerCT1();
	double GetApparentPowerCT2();
	double GetApparentPowerCT3();
	double GetTotalApparentPower();

	double GetFrequency();

	double GetPowerFactorCT1();
	double GetPowerFactorCT2();
	double GetPowerFactorCT3();
	double GetTotalPowerFactor();

	double GetVHarmCT1();
	double GetVHarmCT2();
	double GetVHarmCT3();

	double GetCHarmCT1();
	double GetCHarmCT2();
	double GetCHarmCT3();

	double GetPhaseCT1();
	double GetPhaseCT2();
	double GetPhaseCT3();

	double GetTemperature();

	/* Gain Parameters (GET)*/
	double GetValueRegister(unsigned short registerRead);

	/* Energy Consumption */
	double GetImportEnergy();

	double GetExportEnergy();

	/* System Status */
	unsigned short GetSysStatus0();
	unsigned short GetSysStatus1();
	unsigned short GetMeterStatus0();
	unsigned short GetMeterStatus1();

	/* Checksum Function */
	bool calibrationError();
};
#endif