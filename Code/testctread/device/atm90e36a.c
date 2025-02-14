#include <stdio.h>
#include <string.h>
#include <math.h>
#include <unistd.h>
#include <stdlib.h>

#include "spi.h"
#include "atm30e36a.h"

#define byte unsigned char

static unsigned short atm90e36_comms(unsigned char RW, unsigned short address, unsigned short val)
{
    unsigned char* data = (unsigned char*)&val;
    unsigned char* adata = (unsigned char*)&address;
    unsigned short output;
    unsigned short address1;
    double test;

    // Switch MSB and LSB of value
    output = (val >> 8) | (val << 8);
    val = output;

    // Set R/W flag
    address |= RW << 15;

    // Swap byte address
    address1 = (address >> 8) | (address << 8);
    address1 = address;
    address = address1;

    if (RW) {
        char outbuffer[4];
        char outbufferRX[4];
        memset(outbufferRX, 0x0, 4);
        outbuffer[0] = (address1 >> 8) & 0xFF;
        outbuffer[1] = (address1 & 0xFF);
        outbuffer[2] = 0xFF;
        outbuffer[3] = 0XFF;
        spi_txrx(outbuffer, outbufferRX, 4);

        output = ((outbufferRX[2] << 8)) | (outbufferRX[3]);
        test = (double)output;
        usleep(100);
    } else {
        char outbuffer[4];
        outbuffer[0] = (address1 >> 8) & 0xFF;
        outbuffer[1] = (address1 & 0xFF);
        outbuffer[2] = data[0];
        outbuffer[3] = data[1];
        spi_write(outbuffer, 4);
        usleep(100);
    }
    
    return output;
}

static int Read32Register(signed short regh_addr, signed short regl_addr)
{
    int val, val_h, val_l;
    val_h = atm90e36_comms(READ, regh_addr, 0xFFFF);
    val_l = atm90e36_comms(READ, regl_addr, 0xFFFF);
    val = atm90e36_comms(READ, regh_addr, 0xFFFF);

    val = val_h << 16;
    val |= val_l; // concatenate the 2 registers to make 1 32 bit number

    return (val);
} // ATM90E3x::Read32Register

void atm30e36a_init(void) {

}

static double GetLineVoltage(int CTNo) {
    unsigned short voltage = atm90e36_comms(READ, UrmsA + (2 * CTNo), 0xFFFF);
    return (double)voltage / 100;
}

static double GetFrequency() {
    unsigned short freq = atm90e36_comms(READ, Freq, 0xFFFF);
    return (double)freq / 100;
}

static double GetLineCurrentCT(int CTNo) {
    unsigned short current = atm90e36_comms(READ, IrmsA + (1 * CTNo), 0xFFFF);
    return (double)current / 1000;
}

static double GetActivePowerCT(int CTNo) {
    int val = Read32Register(PmeanA + (1 * CTNo), PmeanALSB + (1 * CTNo));
    return (double)val * 0.00032;
}

static double GetReactivePowerCT(int CTNo) {
    int val = Read32Register(QmeanA + (1 * CTNo), QmeanALSB + (1 * CTNo));
    return (double)val * 0.00032;
}

static double GetApparentPowerCT(int CTNo) {
    int val = Read32Register(SmeanA + (1 * CTNo), SmeanALSB + (1 * CTNo));
    return (double)val * 0.00032;
}

static double GetPowerFactorCT(int CTNo) {
    signed short pf = (signed short)atm90e36_comms(READ, PFmeanA + (1 * CTNo), 0xFFFF);
    return (double)pf / 1000;
}

static double GetPhaseCT(int CTNo) {
    unsigned short angleA = (unsigned short)atm90e36_comms(READ, PAngleA + (2 * CTNo), 0xFFFF);
    return (double)angleA / 10;
}

static double GetTemperature(int CTNo) {
    short int atemp = (short int)atm90e36_comms(READ, Temp, 0xFFFF);
    return (double)atemp;
}

struct CT_Value_Result* GetCTRead(unsigned char CT) {
    struct CT_Value_Result* result = malloc(sizeof(struct CT_Value_Result));

    memset(result, 0x0, sizeof(result));

    result->Voltage = GetLineVoltage(CT);
    result->Frequency = GetFrequency();
    result->ActivePower = GetActivePowerCT(CT);
    result->Current = GetLineCurrentCT(CT);
    result->Apprent = GetApparentPowerCT(CT);
    result->Phase = GetPhaseCT(CT);
    result->PowerFactor = GetPowerFactorCT(CT);
    result->Reactive = GetReactivePowerCT(CT);

    return result;
}

void atm30e36a_chipinit(void) {
    unsigned short LineFreq = 389;
    unsigned short PGAGain = 0b0101010101010101; // PMPGA 0x17  | DPGA Gain = 2 and PGA Gain = 1
    unsigned short sagV;
    unsigned short vSagTh = 0;
    unsigned short FreqHiThresh;
    unsigned short FreqLoThresh;
    unsigned short VoltageGain1 = 20200;
    unsigned short CurrentGainCT1 = 33500;

    if (LineFreq == 4485 || LineFreq == 5231)
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

    vSagTh = (sagV * 100 * sqrt(2)) / (2 * VoltageGain1 / 32768);

    
	atm90e36_comms(WRITE, SoftReset, 0x789A); // 70 Perform soft reset
    atm90e36_comms(WRITE, FuncEn0, 0x0);     // Voltage sag
    atm90e36_comms(WRITE, FuncEn1, 0x0);     // Voltage sag
    atm90e36_comms(WRITE, SagTh, 0x1);       // Voltage sag threshold

    atm90e36_comms(WRITE, ConfigStart, 0x5678); // Metering calibration startup
    atm90e36_comms(WRITE, PLconstH, 0x0861);    // PL Constant MSB (default)
    atm90e36_comms(WRITE, PLconstL, 0xC468);    // PL Constant LSB (default)
    atm90e36_comms(WRITE, MMode0, LineFreq);   // 0x1087.  Mode Config (60 Hz, 3P4W)
    atm90e36_comms(WRITE, MMode1, PGAGain);    // 0x1500.  0x5555 (x2) // 0x0000 (1x)
    atm90e36_comms(WRITE, PStartTh, 0x0000);    // Active Startup Power Threshold
    atm90e36_comms(WRITE, QStartTh, 0x0000);    // Reactive Startup Power Threshold
    atm90e36_comms(WRITE, SStartTh, 0x0000);    // Apparent Startup Power Threshold
    atm90e36_comms(WRITE, PPhaseTh, 0x0000);    // Active Phase Threshold
    atm90e36_comms(WRITE, QPhaseTh, 0x0000);    // Reactive Phase Threshold
    atm90e36_comms(WRITE, SPhaseTh, 0x0000);    // Apparent  Phase Threshold
    atm90e36_comms(WRITE, CSZero, 0x4741);      // Checksum 0

    atm90e36_comms(WRITE, CalStart, 0x5678); // Metering calibration startup
    atm90e36_comms(WRITE, GainA, 0x0000);    // Line calibration gain
    atm90e36_comms(WRITE, PhiA, 0x0000);     // Line calibration angle
    atm90e36_comms(WRITE, GainB, 0x0000);    // Line calibration gain
    atm90e36_comms(WRITE, PhiB, 0x0000);     // Line calibration angle
    atm90e36_comms(WRITE, GainC, 0x0000);    // Line calibration gain
    atm90e36_comms(WRITE, PhiC, 0x0000);     // Line calibration angle
    atm90e36_comms(WRITE, PoffsetA, 0x0000); // A line active power offset
    atm90e36_comms(WRITE, QoffsetA, 0x0000); // A line reactive power offset
    atm90e36_comms(WRITE, PoffsetB, 0x0000); // B line active power offset
    atm90e36_comms(WRITE, QoffsetB, 0x0000); // B line reactive power offset
    atm90e36_comms(WRITE, PoffsetC, 0x0000); // C line active power offset
    atm90e36_comms(WRITE, QoffsetC, 0x0000); // C line reactive power offset
    atm90e36_comms(WRITE, CSOne, 0x0000);    // Checksum 1

    atm90e36_comms(WRITE, HarmStart, 0x5678); // Metering calibration startup
    atm90e36_comms(WRITE, POffsetAF, 0x0000); // A Fund. active power offset
    atm90e36_comms(WRITE, POffsetBF, 0x0000); // B Fund. active power offset
    atm90e36_comms(WRITE, POffsetCF, 0x0000); // C Fund. active power offset
    atm90e36_comms(WRITE, PGainAF, 0x0000);   // A Fund. active power gain
    atm90e36_comms(WRITE, PGainBF, 0x0000);   // B Fund. active power gain
    atm90e36_comms(WRITE, PGainCF, 0x0000);   // C Fund. active power gain
    atm90e36_comms(WRITE, CSTwo, 0x0000);     // Checksum 2

    atm90e36_comms(WRITE, AdjStart, 0x5678); // Measurement calibration

    atm90e36_comms(WRITE, UgainA, VoltageGain1);  // A SVoltage rms gain
    atm90e36_comms(WRITE, IgainA, CurrentGainCT1);  // A line current gain.
    atm90e36_comms(WRITE, UoffsetA, 0x0000); // A Voltage offset
    atm90e36_comms(WRITE, IoffsetA, 0x0000); // A line current offset
    atm90e36_comms(WRITE, UgainB, VoltageGain1);  // B Voltage rms gain.
    atm90e36_comms(WRITE, IgainB, CurrentGainCT1);  // B line current gain
    atm90e36_comms(WRITE, UoffsetB, 0x0000); // B Voltage offset
    atm90e36_comms(WRITE, IoffsetB, 0x0000); // B line current offset
    atm90e36_comms(WRITE, UgainC, VoltageGain1);  // C Voltage rms gain
    atm90e36_comms(WRITE, IgainC, CurrentGainCT1);  // C line current gain
    atm90e36_comms(WRITE, UoffsetC, 0x0000); // C Voltage offset
    atm90e36_comms(WRITE, IoffsetC, 0x0000); // C line current offset
    
    atm90e36_comms(WRITE, IgainN, 0xFD7F); // D line current gain

    atm90e36_comms(WRITE, CSThree, 0x02F6); // Checksum 3
}