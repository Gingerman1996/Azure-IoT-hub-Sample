#ifndef AS1412_H
#define AS1412_H

#include <Arduino.h>

class AS1412
{
private:
    uint8_t DOUT;
    uint8_t SCLK;
#define READ_DATA true
#define READ_REGIS false
#define READ_ERROR 0x1ffffff

    bool data_ready();
    int myshiftIn(uint8_t dataPin, uint8_t clockPin,
                  bool red, uint8_t pulse);
    void myshiftOut(uint8_t dataPin, uint8_t clockPin,
                    uint8_t val, uint8_t pulse);

public:
    int readData();
    int readRegis();
    void sendRegis(int data);
    void init();
    AS1412(uint8_t datapin, uint8_t sckpin);
};

#endif