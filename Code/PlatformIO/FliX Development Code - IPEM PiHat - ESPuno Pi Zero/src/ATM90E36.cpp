/*
  Dave Williams, DitroniX 2019-2025 (ditronix.net)
  Full header information in README

  This test code is OPEN SOURCE and formatted for easier viewing.  Although is is not intended for real world use, it may be freely used, or modified as needed.
  It is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.

  Further information, details and examples can be found on our website ditronix.net, github.com/DitroniX and hackster.io/DitroniX
*/

// Libraries
#include <ATM90E36.h>

// ****************  VARIABLES / DEFINES / STATIC / STRUCTURES / CONSTANTS ****************

ATM90E36::ATM90E36(void)  // WIP Temporary Code
{
  #include <Config.h> // User Configuration Variables
}

ATM90E36::~ATM90E36()
{
}

// **************** FUNCTIONS AND ROUTINES ****************

// WIP PCA9671 or Hardware SPI CS ### Temporary Code for Hardware/Software CS
void SPI_CS(boolean cs_state = HIGH)
{
 
  // delayMicroseconds(1);

 // Check Hardware CS value.  If > 0 then use Hardware - Else use Software GPIO Expander
  if (CS_GPIO > 0)
  {
    if (cs_state == HIGH)
      digitalWrite(CS_GPIO, HIGH);
    else
      digitalWrite(CS_GPIO, LOW);
  }
  else
  {
    if (cs_state == HIGH)
    {
      // Set Default IPEM PiHat > ATM DMA Low = 0X03 = 0000 0011
      Wire.beginTransmission(I2C_Address_IPH);
      Wire.write(0xFF);
      Wire.write(0x03);
      Wire.endTransmission();
    }
    else
    {
      // Pull /CS Low and leave ATM DMA Low
      Wire.beginTransmission(I2C_Address_IPH);
      Wire.write(0xFF);
      Wire.write(0x01);
      Wire.endTransmission();
    }
  }

  // delayMicroseconds(1);
}

// **************** ATM90E - Communication Establishment ****************
/*
  - Defines Register Mask
  - Treats the Register and SPI Comms
  - Outputs the required value in the register
*/
unsigned short ATM90E36::CommEnergyIC(unsigned char RW, unsigned short address, unsigned short val)
{
  unsigned char *data = (unsigned char *)&val;
  unsigned char *adata = (unsigned char *)&address;
  unsigned short output;
  unsigned short address1;

  // **************** SPI Settings ESP32 ****************
  SPISettings settings(200000, MSBFIRST, SPI_MODE3);

  // Switch MSB and LSB of value
  output = (val >> 8) | (val << 8);
  val = output;

  // Set R/W flag
  address |= RW << 15;

  // Swap byte address
  address1 = (address >> 8) | (address << 8);
  address = address1;

  // Transmit & Receive Data
  SPI.beginTransaction(settings);

  // Chip enable and wait for SPI activation
  SPI_CS(LOW);

  // Write address byte by byte
  for (byte i = 0; i < 2; i++)
  {
    SPI.transfer(*adata);
    adata++;
  }

  /* Must wait 4 us for data to become valid */
  delayMicroseconds(4);

  // READ Data
  // Do for each byte in transfer
  if (RW)
  {
    for (byte i = 0; i < 2; i++)
    {
      *data = SPI.transfer(0x00);
      data++;
    }
  }
  else
  {
    for (byte i = 0; i < 2; i++)
    {
      SPI.transfer(*data);
      data++;
    }
  }

  // Chip enable and wait for transaction to end
  SPI_CS(HIGH);

  SPI.endTransaction();

  output = (val >> 8) | (val << 8); // reverse MSB and LSB
  return output;
} // ATM90E36::CommEnergyIC

// **************** REGISTER FUNCTIONS ****************

int ATM90E36::Read32Register(signed short regh_addr, signed short regl_addr)
{
  int val, val_h, val_l;
  val_h = CommEnergyIC(READ, regh_addr, 0xFFFF);
  val_l = CommEnergyIC(READ, regl_addr, 0xFFFF);
  val = CommEnergyIC(READ, regh_addr, 0xFFFF);

  val = val_h << 16;
  val |= val_l; // concatenate the 2 registers to make 1 32 bit number

  return (val);
} // ATM90E36::Read32Register

double ATM90E36::CalculateVIOffset(unsigned short regh_addr, unsigned short regl_addr /*, unsigned short offset_reg*/)
{
  // for getting the lower registers of Voltage and Current and calculating the offset
  // should only be run when CT sensors are connected to the meter,
  // but not connected around wires
  uint32_t val, val_h, val_l;
  uint16_t offset;
  val_h = CommEnergyIC(READ, regh_addr, 0xFFFF);
  val_l = CommEnergyIC(READ, regl_addr, 0xFFFF);
  val = CommEnergyIC(READ, regh_addr, 0xFFFF);

  val = val_h << 16; // move high register up 16 bits
  val |= val_l;      // concatenate the 2 registers to make 1 32 bit number
  val = val >> 7;    // right shift 7 bits - lowest 7 get ignored - V & I registers need this
  val = (~val) + 1;  // 2s compliment

  offset = val; // keep lower 16 bits
  // CommEnergyIC(WRITE, offset_reg, (signed short)val);
  return uint16_t(offset);
} // ATM90E36::CalculateVIOffset

double ATM90E36::CalculatePowerOffset(unsigned short regh_addr, unsigned short regl_addr /*, unsigned short offset_reg*/)
{
  // for getting the lower registers of energy and calculating the offset
  // should only be run when CT sensors are connected to the meter,
  // but not connected around wires
  uint32_t val, val_h, val_l;
  uint16_t offset;
  val_h = CommEnergyIC(READ, regh_addr, 0xFFFF);
  val_l = CommEnergyIC(READ, regl_addr, 0xFFFF);
  val = CommEnergyIC(READ, regh_addr, 0xFFFF);

  val = val_h << 16; // move high register up 16 bits
  val |= val_l;      // concatenate the 2 registers to make 1 32 bit number
  val = (~val) + 1;  // 2s compliment

  offset = val; // keep lower 16 bits
  // CommEnergyIC(WRITE, offset_reg, (signed short)val);
  return uint16_t(offset);
} // ATM90E36::CalculatePowerOffset

double ATM90E36::CalibrateVI(unsigned short reg, unsigned short actualVal)
{
  // input the Voltage or Current register, and the actual value that it should be
  // actualVal can be from a calibration meter or known value from a power supply
  uint16_t gain, val, m, gainReg;

  // Sample the reading
  val = CommEnergyIC(READ, reg, 0xFFFF);
  val += CommEnergyIC(READ, reg, 0xFFFF);
  val += CommEnergyIC(READ, reg, 0xFFFF);
  val += CommEnergyIC(READ, reg, 0xFFFF);

  // Get value currently in gain register
  switch (reg)
  {
  case URMSCT1:
  {
    gainReg = UGainCT1;
  }
  case URMSCT2:
  {
    gainReg = UGainCT2;
  }
  case URMSCT3:
  {
    gainReg = UGainCT3;
  }
  case IRMSCT1:
  {
    gainReg = IGainCT1;
  }
  case IRMSCT2:
  {
    gainReg = IGainCT2;
  }
  case IRMSCT3:
  {
    gainReg = IGainCT3;
  }
  }

  gain = CommEnergyIC(READ, gainReg, 0xFFFF);
  m = actualVal;
  m = ((m * gain) / val);
  gain = m;

  // Write new value to gain register
  CommEnergyIC(WRITE, gainReg, gain);

  return (gain);
} // ATM90E36::CalibrateVI

/* Checksum Error Function */
bool ATM90E36::calibrationError()
{
  bool CS0, CS1, CS2, CS3;
  unsigned short systemstatus0 = GetSysStatus0();

  if (systemstatus0 & 0x4000)
  {
    CS0 = true;
  }
  else
  {
    CS0 = false;
  }

  if (systemstatus0 & 0x1000)
  {
    CS1 = true;
  }
  else
  {
    CS1 = false;
  }
  if (systemstatus0 & 0x0400)
  {
    CS2 = true;
  }
  else
  {
    CS2 = false;
  }
  if (systemstatus0 & 0x0100)
  {
    CS3 = true;
  }
  else
  {
    CS3 = false;
  }

  Serial.print("Checksum 0: ");
  Serial.print(CS0);
  Serial.print("\tChecksum 1: ");
  Serial.println(CS1);
  Serial.print("Checksum 2: ");
  Serial.print(CS2);
  Serial.print("\tChecksum 3: ");
  Serial.println(CS3);

  if (CS0 || CS1 || CS2 || CS3)
    return (true);
  else
    return (false);
}
// **************** PARAMETER FUNCTIONS ****************
// Returns Main Electrical Parameters, such as: Voltage, Current, Power, Energy, and Frequency, and Temperature

// **************** VOLTAGE
double ATM90E36::GetLineVoltage1()
{
  unsigned short voltage = CommEnergyIC(READ, URMSCT1, 0xFFFF);
  return (double)voltage / 100;
}
double ATM90E36::GetLineVoltage2()
{
  unsigned short voltage = CommEnergyIC(READ, URMSCT2, 0xFFFF);
  return (double)voltage / 100;
}
double ATM90E36::GetLineVoltage3()
{
  unsigned short voltage = CommEnergyIC(READ, URMSCT3, 0xFFFF);
  return (double)voltage / 100;
}

// **************** CURRENT
double ATM90E36::GetLineCurrentCT1()
{
  unsigned short current = CommEnergyIC(READ, IRMSCT1, 0xFFFF);
  return (double)current / 1000;
}
double ATM90E36::GetLineCurrentCT2()
{
  unsigned short current = CommEnergyIC(READ, IRMSCT2, 0xFFFF);
  return (double)current / 1000;
}
double ATM90E36::GetLineCurrentCT3()
{
  unsigned short current = CommEnergyIC(READ, IRMSCT3, 0xFFFF);
  return (double)current / 1000;
}

double ATM90E36::GetLineCurrentCTN()
{
  unsigned short current = CommEnergyIC(READ, IRMSN, 0xFFFF);
  return (double)current / 1000;
}

// **************** ACTIVE POWER
double ATM90E36::GetActivePowerCT1()
{
  signed short apower = (signed short)CommEnergyIC(READ, PmeanCT1, 0xFFFF);
  return (double)apower / 1000;
}
double ATM90E36::GetActivePowerCT2()
{
  signed short apower = (signed short)CommEnergyIC(READ, PmeanCT2, 0xFFFF);
  return (double)apower / 1000;
}
double ATM90E36::GetActivePowerCT3()
{
  signed short apower = (signed short)CommEnergyIC(READ, PmeanCT3, 0xFFFF);
  return (double)apower / 1000;
}
double ATM90E36::GetTotalActivePower()
{
  signed short apower = (signed short)CommEnergyIC(READ, PmeanT, 0xFFFF);
  return (double)apower / 250;
}

// **************** REACTIVE POWER ****************
double ATM90E36::GetReactivePowerCT1()
{
  signed short apower = (signed short)CommEnergyIC(READ, QmeanCT1, 0xFFFF);
  return (double)apower / 1000;
}
double ATM90E36::GetReactivePowerCT2()
{
  signed short apower = (signed short)CommEnergyIC(READ, QmeanCT2, 0xFFFF);
  return (double)apower / 1000;
}
double ATM90E36::GetReactivePowerCT3()
{
  signed short apower = (signed short)CommEnergyIC(READ, QmeanCT3, 0xFFFF);
  return (double)apower / 1000;
}
double ATM90E36::GetTotalReactivePower()
{
  signed short apower = (signed short)CommEnergyIC(READ, QmeanT, 0xFFFF);
  return (double)apower / 250;
}

// **************** APPARENT POWER ****************
double ATM90E36::GetApparentPowerCT1()
{
  signed short apower = (signed short)CommEnergyIC(READ, SmeanCT1, 0xFFFF);
  return (double)apower / 1000;
}
double ATM90E36::GetApparentPowerCT2()
{
  signed short apower = (signed short)CommEnergyIC(READ, SmeanCT2, 0xFFFF);
  return (double)apower / 1000;
}
double ATM90E36::GetApparentPowerCT3()
{
  signed short apower = (signed short)CommEnergyIC(READ, SmeanCT3, 0xFFFF);
  return (double)apower / 1000;
}
double ATM90E36::GetTotalApparentPower()
{
  signed short apower = (signed short)CommEnergyIC(READ, SmeanT, 0xFFFF);
  return (double)apower / 250;
}

// **************** FREQUENCY ****************
double ATM90E36::GetFrequency()
{
  unsigned short freq = CommEnergyIC(READ, Freq, 0xFFFF);
  return (double)freq / 100;
}

// **************** POWER FACTOR ****************
double ATM90E36::GetPowerFactorCT1()
{
  signed short pf = (signed short)CommEnergyIC(READ, PFmeanCT1, 0xFFFF);
  return (double)pf / 1000;
}
double ATM90E36::GetPowerFactorCT2()
{
  signed short pf = (signed short)CommEnergyIC(READ, PFmeanCT2, 0xFFFF);
  return (double)pf / 1000;
}
double ATM90E36::GetPowerFactorCT3()
{
  signed short pf = (signed short)CommEnergyIC(READ, PFmeanCT3, 0xFFFF);
  return (double)pf / 1000;
}
double ATM90E36::GetTotalPowerFactor()
{
  signed short pf = (signed short)CommEnergyIC(READ, PFmeanT, 0xFFFF);
  return (double)pf / 1000;
}

// **************** Voltage Harmonics ****************
double ATM90E36::GetVHarmCT1()
{
  unsigned short value = CommEnergyIC(READ, THDNUCT1, 0xFFFF);
  return (double)value;
}
double ATM90E36::GetVHarmCT2()
{
  unsigned short value = CommEnergyIC(READ, THDNUCT2, 0xFFFF);
  return (double)value;
}
double ATM90E36::GetVHarmCT3()
{
  unsigned short value = CommEnergyIC(READ, THDNUCT3, 0xFFFF);
  return (double)value;
}

// **************** Current Harmonics ****************
double ATM90E36::GetCHarmCT1()
{
  unsigned short value = CommEnergyIC(READ, THDNICT1, 0xFFFF);
  return (double)value;
}
double ATM90E36::GetCHarmCT2()
{
  unsigned short value = CommEnergyIC(READ, THDNICT2, 0xFFFF);
  return (double)value;
}
double ATM90E36::GetCHarmCT3()
{
  unsigned short value = CommEnergyIC(READ, THDNICT3, 0xFFFF);
  return (double)value;
}

// **************** MEAN PHASE ANGLE ****************
double ATM90E36::GetPhaseCT1()
{
  unsigned short angleA = (unsigned short)CommEnergyIC(READ, PAngleCT1, 0xFFFF);
  return (double)angleA / 10;
}
double ATM90E36::GetPhaseCT2()
{
  unsigned short angleB = (unsigned short)CommEnergyIC(READ, PAngleCT2, 0xFFFF);
  return (double)angleB / 10;
}
double ATM90E36::GetPhaseCT3()
{
  unsigned short angleC = (unsigned short)CommEnergyIC(READ, PAngleCT3, 0xFFFF);
  return (double)angleC / 10;
}

// **************** TEMPERATURE ****************
double ATM90E36::GetTemperature()
{
  short int atemp = (short int)CommEnergyIC(READ, Temp, 0xFFFF);
  return (double)atemp;
}

// **************** GET REGISTER VALUE ****************
double ATM90E36::GetValueRegister(unsigned short registerRead)
{
  return (double)CommEnergyIC(READ, registerRead, 0xFFFF); // returns value register
}

// REGULAR ENERGY MEASUREMENT

// **************** FORWARD ACTIVE ENERGY ****************
// these registers accumulate energy and are cleared after being read
double ATM90E36::GetImportEnergy()
{
  unsigned short ienergyT = CommEnergyIC(READ, APenergyT, 0xFFFF);
  // unsigned short ienergyCT1 = CommEnergyIC(READ, APenergyCT1, 0xFFFF);
  // unsigned short ienergyCT2 = CommEnergyIC(READ, APenergyCT2, 0xFFFF);
  // unsigned short ienergyCT3 = CommEnergyIC(READ, APenergyCT3, 0xFFFF);

  // unsigned short renergyT = CommEnergyIC(READ, RPenergyT, 0xFFFF);
  // unsigned short renergyCT1 = CommEnergyIC(READ, RPenergyCT1, 0xFFFF);
  // unsigned short renergyCT2 = CommEnergyIC(READ, RPenergyCT2, 0xFFFF);
  // unsigned short renergyCT3 = CommEnergyIC(READ, RPenergyCT3, 0xFFFF);

  // unsigned short senergyT = CommEnergyIC(READ, SAenergyT, 0xFFFF);
  // unsigned short senergyCT1 = CommEnergyIC(READ, SenergyCT1, 0xFFFF);
  // unsigned short senergyCT2 = CommEnergyIC(READ, SenergyCT2, 0xFFFF);
  // unsigned short senergyCT3 = CommEnergyIC(READ, SenergyCT3, 0xFFFF);

  return (double)(((double)ienergyT / 32) * 3600); // returns kWh
}

// **************** FORWARD REACTIVE ENERGY ****************

// **************** REVERSE ACTIVE ENERGY ****************
double ATM90E36::GetExportEnergy()
{
  unsigned short eenergyT = CommEnergyIC(READ, ANenergyT, 0xFFFF);
  // unsigned short eenergyCT1 = CommEnergyIC(READ, ANenergyCT1, 0xFFFF);
  // unsigned short eenergyCT2 = CommEnergyIC(READ, ANenergyCT2, 0xFFFF);
  // unsigned short eenergyCT3 = CommEnergyIC(READ, ANenergyCT3, 0xFFFF);

  // unsigned short reenergyT = CommEnergyIC(READ, RNenergyT, 0xFFFF);
  // unsigned short reenergyCT1 = CommEnergyIC(READ, RNenergyCT1, 0xFFFF);
  // unsigned short reenergyCT2 = CommEnergyIC(READ, RNenergyCT2, 0xFFFF);
  // unsigned short reenergyCT3 = CommEnergyIC(READ, RNenergyCT3, 0xFFFF);

  return (double)(((double)eenergyT / 32) * 3600); // returns kWh
}

// **************** REVERSE REACTIVE ENERGY ****************

// **************** System Status Registers ****************
unsigned short ATM90E36::GetSysStatus0()
{
  return CommEnergyIC(READ, SysStatus0, 0xFFFF);
}
unsigned short ATM90E36::GetSysStatus1()
{
  return CommEnergyIC(READ, SysStatus1, 0xFFFF);
}
unsigned short ATM90E36::GetMeterStatus0()
{
  return CommEnergyIC(READ, EnStatus0, 0xFFFF);
}
unsigned short ATM90E36::GetMeterStatus1()
{
  return CommEnergyIC(READ, EnStatus1, 0xFFFF);
}

// **************** Configuration ****************
// Use SPI MODE 0 for the ATM90E36 ??????

#if ATM_SPLITPHASE == true
void ATM90E36::begin(unsigned short lineFreq, unsigned short pgagain, unsigned short uGainCT1, unsigned short uGainCT2, unsigned short uGainCT3, unsigned short iGainCT1, unsigned short iGainCT2, unsigned short iGainCT3)
#endif

#if ATM_SPLITPHASE == false
    void ATM90E36::begin(unsigned short lineFreq, unsigned short pgagain, unsigned short uGainCT1, unsigned short uGainCT2, unsigned short uGainCT3, unsigned short iGainCT1, unsigned short iGainCT2, unsigned short iGainCT3, unsigned short igainN)
#endif
{
  _cs = 5;              // SS IPEM = GP5
  _lineFreq = lineFreq; // frequency of power
  _pgagain = pgagain;   // PGA Gain for current channels#

#if ATM_SINGLEVOLTAGE == true
  _uGainCT1 = uGainCT1; // Voltage RMS Gain
  _uGainCT2 = uGainCT1; // Duplicate uGainCT1 Values to _uGainCT2 and _uGainCT3.
  _uGainCT3 = uGainCT1; // Duplicate uGainCT1 Values to _uGainCT2 and _uGainCT3.
#else
  _uGainCT1 = uGainCT1; // Voltage 1 RMS Gain
  _uGainCT2 = uGainCT2; // Voltage 2 RMS Gain
  _uGainCT3 = uGainCT3; // Voltage 3 RMS Gain
#endif

  _iGainCT1 = iGainCT1; // CT1
  _iGainCT2 = iGainCT2; // CT2 - not used for single split phase meter
  _iGainCT3 = iGainCT3; // CT3 or CT2 for single split phase meter

#if ATM_SPLITPHASE == false
  _igainN = igainN; // CTN (Used on the ATM90E36)
#endif

  /* Enable SPI for ATM90E36 Communication*/
  SPI.begin(SCLK, MISO, MOSI);

  Serial.println("Connecting to the ATM90E36");

  // Chip Select Information
  if (CS_GPIO > 0)
    Serial.println("ATM90E36 SPI Control Using External GPIO for /CS");
  else
    Serial.println("ATM90E36 SPI Control Using GPIO Expander for /CS");

  Serial.println("");

  // Calculation for voltage sag threshold - assumes we do not want to go under 90v for split phase and 190v otherwise
  // determine proper low and high frequency threshold
  unsigned short vSagTh;
  unsigned short sagV;
  unsigned short FreqHiThresh;
  unsigned short FreqLoThresh;
  if (_lineFreq == 4485 || _lineFreq == 5231)
  {
    sagV = 90;
    FreqHiThresh = 61 * 100;
    FreqLoThresh = 59 * 100;
  }
  else
  {
    sagV = 190;
    FreqHiThresh = 51 * 100;
    FreqLoThresh = 49 * 100;
  }

  vSagTh = (sagV * 100 * sqrt(2)) / (2 * _uGainCT1 / 32768);

  // **************** Initialize registers ****************
  CommEnergyIC(WRITE, SoftReset, 0x789A); // 70 Perform soft reset

  // SagTh = Vth * 100 * sqrt(2) / (2 * Ugain / 32768)
  CommEnergyIC(WRITE, FuncEn0, 0x0000); // Voltage sag
  CommEnergyIC(WRITE, FuncEn1, 0x0000); // Voltage sag
  CommEnergyIC(WRITE, SagTh, 0x0001);   // Voltage sag threshold

  // **************** Status registers ****************

  // **************** Set metering config values (CONFIG) ****************

  CommEnergyIC(WRITE, ConfigStart, 0x5678); // Metering calibration startup
  CommEnergyIC(WRITE, PLconstH, 0x0861);    // PL Constant MSB (default)
  CommEnergyIC(WRITE, PLconstL, 0xC468);    // PL Constant LSB (default)
  CommEnergyIC(WRITE, MMode0, _lineFreq);   // 0x1087.  Mode Config (60 Hz, 3P4W)
  CommEnergyIC(WRITE, MMode1, _pgagain);    // 0x1500.  0x5555 (x2) // 0x0000 (1x)
  CommEnergyIC(WRITE, PStartTh, 0x0000);    // Active Startup Power Threshold
  CommEnergyIC(WRITE, QStartTh, 0x0000);    // Reactive Startup Power Threshold
  CommEnergyIC(WRITE, SStartTh, 0x0000);    // Apparent Startup Power Threshold
  CommEnergyIC(WRITE, PPhaseTh, 0x0000);    // Active Phase Threshold
  CommEnergyIC(WRITE, QPhaseTh, 0x0000);    // Reactive Phase Threshold
  CommEnergyIC(WRITE, SPhaseTh, 0x0000);    // Apparent  Phase Threshold
  CommEnergyIC(WRITE, CSZero, 0x4741);      // Checksum 0

  // **************** Set Metering Calibration Register Values (CALIBRATION) ****************
  CommEnergyIC(WRITE, CalStart, 0x5678);   // Metering calibration startup
  CommEnergyIC(WRITE, GainCT1, 0x0000);    // Line calibration gain
  CommEnergyIC(WRITE, PhiCT1, 0x0000);     // Line calibration angle
  CommEnergyIC(WRITE, GainCT2, 0x0000);    // Line calibration gain
  CommEnergyIC(WRITE, PhiCT2, 0x0000);     // Line calibration angle
  CommEnergyIC(WRITE, GainCT3, 0x0000);    // Line calibration gain
  CommEnergyIC(WRITE, PhiCT3, 0x0000);     // Line calibration angle
  CommEnergyIC(WRITE, PoffsetCT1, 0x0000); // CT1 line active power offset
  CommEnergyIC(WRITE, QoffsetCT1, 0x0000); // CT1 line reactive power offset
  CommEnergyIC(WRITE, PoffsetCT2, 0x0000); // CT2 line active power offset
  CommEnergyIC(WRITE, QoffsetCT2, 0x0000); // CT2 line reactive power offset
  CommEnergyIC(WRITE, PoffsetCT3, 0x0000); // CT3 line active power offset
  CommEnergyIC(WRITE, QoffsetCT3, 0x0000); // CT3 line reactive power offset
  CommEnergyIC(WRITE, CSOne, 0x0000);      // Checksum 1

  // **************** FUNDAMENTAL/HARMONIC & ENERGY CALIBRATION REGISTERS ****************
  CommEnergyIC(WRITE, HaRMStart, 0x5678);   // Metering calibration startup
  CommEnergyIC(WRITE, PoffsetCT1F, 0x0000); // CT1 Fund. active power offset
  CommEnergyIC(WRITE, PoffsetCT2F, 0x0000); // CT2 Fund. active power offset
  CommEnergyIC(WRITE, PoffsetCT3F, 0x0000); // CT3 Fund. active power offset
  CommEnergyIC(WRITE, PGainCT1F, 0x0000);   // CT1 Fund. active power gain
  CommEnergyIC(WRITE, PGainCT2F, 0x0000);   // CT2 Fund. active power gain
  CommEnergyIC(WRITE, PGainCT3F, 0x0000);   // CT3 Fund. active power gain
  CommEnergyIC(WRITE, CSTwo, 0x0000);       // Checksum 2

  // **************** MEASUREMENT CALIBRATION REGISTERS ****************
  CommEnergyIC(WRITE, AdjStart, 0x5678); // Measurement calibration

  // A
  CommEnergyIC(WRITE, UGainCT1, _uGainCT1); // CT1 SVoltage RMS gain
  CommEnergyIC(WRITE, IGainCT1, _iGainCT1); // CT1 line current gain.
  CommEnergyIC(WRITE, UoffsetCT1, 0x0000);  // CT1 Voltage offset
  CommEnergyIC(WRITE, IoffsetCT1, 0x0000);  // CT1 line current offset
  // B
  CommEnergyIC(WRITE, UGainCT2, _uGainCT2); // CT2 Voltage RMS gain.
  CommEnergyIC(WRITE, IGainCT2, _iGainCT2); // CT2 line current gain
  CommEnergyIC(WRITE, UoffsetCT2, 0x0000);  // CT2 Voltage offset
  CommEnergyIC(WRITE, IoffsetCT2, 0x0000);  // CT2 line current offset
  // C
  CommEnergyIC(WRITE, UGainCT3, _uGainCT3); // CT3 Voltage RMS gain
  CommEnergyIC(WRITE, IGainCT3, _iGainCT3); // CT3 line current gain
  CommEnergyIC(WRITE, UoffsetCT3, 0x0000);  // CT3 Voltage offset
  CommEnergyIC(WRITE, IoffsetCT3, 0x0000);  // CT3 line current offset
  // N
  CommEnergyIC(WRITE, IgainN, 0xFD7F); // D line current gain

  CommEnergyIC(WRITE, CSThree, 0x02F6); // Checksum 3

  Serial.println("ATM90E36 Registers Updated");

  // Settle ATM (Tea and Biscuit Time)
  delay(1000);

  // **************** DEFINE EMM STATUS REGISTERS ****************
}
