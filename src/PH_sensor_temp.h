#ifndef PH_SENSOR_TEMP_H
#define PH_SENSOR_TEMP_H

#include <Arduino.h>
#include <DFRobot_PH.h>
#include <FIR.h>
#include <EEPROM.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#include "AS1412.h"

class PH_sensor_temp
{
private:
#define DOUT 46
#define SCLK 3
#define Temp_AIN 8

#define FILTER_TAP_NUM 41
#define EEPROM_SIZE 255

    DFRobot_PH ph;
#define GAIN 15

public:
    void begin();
    float get_pH();
    float get_ph_voltage();
    void cal_ph(char *cmdph);
    float get_temp_f();
    // PH_sensor(uint8_t dout, uint8_t sclk);
};

// PH_sensor::PH_sensor(uint8_t dout, uint8_t sclk)
// {
// }

#endif