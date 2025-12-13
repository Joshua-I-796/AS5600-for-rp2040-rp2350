#ifndef TMCDRIVER_AS5600_H
#define TMCDRIVER_AS5600_H

#include "pico/stdlib.h"
//you dont need to worry about the second adress in the documentation for some of these registers as the AS5600 automatically provides data from both sub addresses for each register so only need to call the first address given also known as the high byte.
const uint8_t as5600_chipID = 0x36;

const uint8_t as5600_ZMCO = 0x00;
const uint16_t ZMCO_mask = 0x0300;

const uint8_t as5600_ZPOS = 0x01;
const uint8_t ZPOS_mask_H = 0x0F;
const uint8_t ZPOS_mask_L = 0xFF;

const uint8_t as5600_MPOS = 0x03;
const uint8_t MPOS_mask_H = 0x0F;
const uint8_t MPOS_mask_L = 0xFF;

const uint8_t as5600_MANG = 0x05;
const uint16_t MANG_mask = 0xFFF;

const uint8_t as5600_CONF = 0x07;
const uint16_t CONF_PM_mask = 0x03;
const uint16_t CONF_HYST_mask = 0x0C;
//const uint8_t CONF_L_OUTS_mask = 0x30;
//const uint8_t CONF_L_PWMF_mask = 0xC0;

//const uint8_t CONF_H_WD_mask = 0x20;

const uint8_t as5600_RAW_ANGLE = 0x0C;
const uint16_t RAW_ANGLE_mask = 0x0FFF;

const uint8_t as5600_ANGLE = 0x0E;
const uint16_t ANGLE_mask = 0x0FFF;

const uint8_t as5600_STATUS = 0x0B;
const uint8_t STATUS_MH_mask = 0x08;
const uint8_t STATUS_ML_mask = 0x10;
const uint8_t STATUS_MD_mask = 0x20;

const uint8_t as5600_AGC = 0x1A;
const uint8_t AGC_mask = 0xFF;

const uint8_t as5600_MAGNITUDE = 0x1B;
const uint16_t MAGNITUDE_mask = 0x0FFF;

float readAS5600_Angle();

int readAS5600_Status();
int readAS5600_AGC();
int readAS5600_Magnitude();
void writeAS5600_HYST(int lsb);
void writeAS5600_ZPOS(uint8_t zpos[2]);
void writeAS5600_MPOS(uint8_t mpos[2]);
void writeAS5600_PM(int mode);
int readAS5600_ZMCO();

// defenitely not including the burn register as i dont wish to permanently program my AS5600 thus rendering it un-reusable.
#endif //TMCDRIVER_AS5600_H