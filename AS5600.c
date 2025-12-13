#include "pico/stdlib.h"
#include <stdio.h>
#include"hardware/i2c.h"
#include "AS5600.h"

float readAS5600_Angle()
{
    uint8_t raw_data[2];
    i2c_write_blocking(i2c0, as5600_chipID, &as5600_ANGLE,1 , true);
    i2c_read_blocking(i2c0, as5600_chipID, raw_data, 2, false);
    uint16_t angle = (((uint16_t)raw_data[0] <<8) | raw_data[1])&ANGLE_mask;
    float degrees = (float)angle*360.0f/ 4096.0f;
    return degrees;
}

int readAS5600_Status()
{
    uint8_t raw_data[1];
    i2c_write_blocking(i2c0, as5600_chipID, &as5600_STATUS,1 , true);
    i2c_read_blocking(i2c0, as5600_chipID, raw_data, 1, false);
    int MD = raw_data[0] & STATUS_MD_mask;
    int ML = raw_data[0] & STATUS_ML_mask;
    int MH = raw_data[0] & STATUS_MH_mask;
    if (ML ==1)
    {
        printf("Magnet too weak\n");
        return 0;
    }
    else if (MH ==1)
    {
        printf("Magnet too strong\n");
        return 0;
    }
    return MD;
}

int readAS5600_AGC()
{
    uint8_t raw_data[1];
    i2c_write_blocking(i2c0, as5600_chipID, &as5600_AGC,1 , true);
    i2c_read_blocking(i2c0, as5600_chipID, raw_data, 1, false);
    int AGC = raw_data[0];
    return AGC;
}

int readAS5600_Magnitude()
{
    uint8_t raw_data[2];
    i2c_write_blocking(i2c0, as5600_chipID, &as5600_MAGNITUDE,1 , true);
    i2c_read_blocking(i2c0, as5600_chipID, raw_data, 2, false);
    int magnitude = ((uint16_t)raw_data[0] <<8) | raw_data[1];
    return magnitude;
}

void writeAS5600_HYST(int lsb)
{
    uint8_t raw_data[2];
    uint8_t send_data[3];
    i2c_write_blocking(i2c0, as5600_chipID, &as5600_CONF,1 , true);
    i2c_read_blocking(i2c0, as5600_chipID, raw_data, 2, false);
    send_data[0] = as5600_CONF;
    send_data[1] = raw_data[0];
    send_data[2] = (raw_data[1] & ~CONF_HYST_mask)| (lsb & CONF_HYST_mask);
    i2c_write_blocking(i2c0, as5600_chipID, send_data, 3, false);
    sleep_ms(100);
    i2c_write_blocking(i2c0, as5600_chipID, &as5600_CONF, 1, true);
    i2c_read_blocking(i2c0, as5600_chipID, raw_data, 2, false);
    int check = raw_data[1]&CONF_HYST_mask;
    if (check != lsb)
    {
        printf("HYST write failed\n");
    }
}

void writeAS5600_ZPOS(uint8_t zpos[2])
{
    uint8_t raw_data[2];
    uint8_t send_data[3];
    i2c_write_blocking(i2c0, as5600_chipID, &as5600_ZPOS,1 , true);
    i2c_read_blocking(i2c0, as5600_chipID, raw_data, 2, false);
    send_data[0] = as5600_ZPOS;
    send_data[1] = (raw_data[0] & ~ZPOS_mask_H) | zpos[0];
    send_data[2] = (raw_data[1] & ~ZPOS_mask_L) | zpos[1];
    i2c_write_blocking(i2c0, as5600_chipID, send_data, 3, false);
    sleep_ms(100);
    i2c_write_blocking(i2c0, as5600_chipID, &as5600_ZPOS, 1, true);
    i2c_read_blocking(i2c0, as5600_chipID, raw_data, 2, false);
    raw_data[0] = raw_data[0]&ZPOS_mask_H;
    raw_data[1] = raw_data[1]&ZPOS_mask_L;
    if (raw_data != zpos)
    {
        printf("ZPOS write failed\n");
    }
}

void writeAS5600_MPOS(uint8_t mpos[2])
{
    uint8_t raw_data[2];
    uint8_t send_data[3];
    i2c_write_blocking(i2c0, as5600_chipID, &as5600_MPOS,1 , true);
    i2c_read_blocking(i2c0, as5600_chipID, raw_data, 2, false);
    send_data[0] = as5600_MPOS;
    send_data[1] = (raw_data[0] & ~MPOS_mask_H) | mpos[0];
    send_data[2] = (raw_data[1] & ~MPOS_mask_L) | mpos[1];
    i2c_write_blocking(i2c0, as5600_chipID, send_data, 3, false);
    sleep_ms(100);
    i2c_write_blocking(i2c0, as5600_chipID, &as5600_MPOS, 1, true);
    i2c_read_blocking(i2c0, as5600_chipID, raw_data, 2, false);
    raw_data[0] = raw_data[0]&MPOS_mask_H;
    raw_data[1] = raw_data[1]&MPOS_mask_L;
    if (raw_data != mpos)
    {
        printf("ZPOS write failed\n");
    }
}

void writeAS5600_PM(int mode)
{
    uint8_t raw_data[2];
    uint8_t send_data[3];
    i2c_write_blocking(i2c0, as5600_chipID, &as5600_CONF,1 , true);
    i2c_read_blocking(i2c0, as5600_chipID, raw_data, 2, false);
    send_data[0] = as5600_CONF;
    send_data[1] = raw_data[0];
    send_data[2] = (raw_data[1] & ~CONF_PM_mask)| (mode & CONF_PM_mask);
    i2c_write_blocking(i2c0, as5600_chipID, send_data, 3, false);
    sleep_ms(100);
    i2c_write_blocking(i2c0, as5600_chipID, &as5600_CONF, 1, true);
    i2c_read_blocking(i2c0, as5600_chipID, raw_data, 2, false);
    int check = raw_data[1]&CONF_PM_mask;
    if (check != mode)
    {
        printf("PM write failed\n");
    }
}

int readAS5600_ZMCO()
{
    uint8_t raw_data[1];
    i2c_write_blocking(i2c0, as5600_chipID, &as5600_ZMCO, 1, true);
    i2c_read_blocking(i2c0, as5600_chipID, raw_data, 1, false);
    int check = raw_data[0] & ZMCO_mask;
    if (check != 0)
    {
        printf("AS5600 already Burned/Programmed\n");
    }
    return check;
}
