#include "AS1412.h"

AS1412::AS1412(uint8_t datapin, uint8_t sckpin)
{
    DOUT = datapin;
    SCLK = sckpin;
}

bool AS1412::data_ready()
{
    while (digitalRead(DOUT))
    {
    }
    return (true);
}

int AS1412::myshiftIn(uint8_t dataPin, uint8_t clockPin,
                      bool red, uint8_t pulse)
{
    int value = 0;
    uint8_t pulse_send;
    uint last_bit;

    if (red == true)
        pulse_send = pulse + 3;
    else
        pulse_send = pulse;

    for (uint8_t i; i < pulse_send; ++i)
    {

        digitalWrite(SCLK, HIGH);
        digitalWrite(SCLK, LOW);
        if (i < pulse)
        {
            value |= digitalRead(dataPin) << (pulse - 1 - i);
        }
        else
            last_bit |= digitalRead(dataPin) << (26 - i);
    }
    return value;
}

void AS1412::myshiftOut(uint8_t dataPin, uint8_t clockPin,
                        uint8_t val, uint8_t pulse)
{
    for (uint8_t i; i < pulse; i++)
    {
        digitalWrite(clockPin, HIGH);

        digitalWrite(dataPin, !!(val & (1 << (pulse - 1 - i))));
        Serial.print(!!(val & (1 << (pulse - 1 - i))));

        digitalWrite(clockPin, LOW);
    }
    Serial.println();
}

void AS1412::init()
{
    pinMode(DOUT, INPUT);
    pinMode(SCLK, OUTPUT);

    while (!digitalRead(DOUT))
    {
    }
}

int AS1412::readData()
{
    int data = 0;
    pinMode(DOUT, INPUT);

    if (data_ready())
        data = myshiftIn(DOUT, SCLK, READ_DATA, 24);
    return data;
}

int AS1412::readRegis()
{
    bool dout = 0;
    int data = 0b1010110;
    int regis = 0;
    pinMode(DOUT, INPUT_PULLUP);
    if (data_ready())
    {
        for (int i = 0; i < 46; i++)
        {
            if (i < 29)
            {
                digitalWrite(SCLK, HIGH);
                delayMicroseconds(50);
                digitalWrite(SCLK, LOW);
                Serial.printf("%d", digitalRead(DOUT));
                if ((i + 1) % 4 == 0)
                    Serial.printf(" ");
                if (i == 28)
                {
                    Serial.println();
                }
            }
            else if (i < 36)
            {
                pinMode(DOUT, OUTPUT);
                if (i == 29)
                    Serial.print("0");
                digitalWrite(SCLK, HIGH);
                delayMicroseconds(50);
                digitalWrite(SCLK, LOW);
                digitalWrite(DOUT, !!(data & (1 << (35 - i))));
                Serial.print(!!(data & (1 << (35 - i))));
                if ((i + 1) % 4 == 0)
                    Serial.printf(" ");
                if (i == 35)
                {
                    Serial.println();
                }
            }
            else if (i == 36)
            {
                pinMode(DOUT, INPUT_PULLUP);
                delayMicroseconds(50);
                digitalWrite(SCLK, HIGH);
                digitalWrite(SCLK, LOW);
                // Serial.println(digitalRead(DOUT));
            }
            else if (i < 45)
            {
                digitalWrite(SCLK, HIGH);
                delayMicroseconds(50);
                digitalWrite(SCLK, LOW);
                // regis |= digitalRead(DOUT) << (44 - i);
                // Serial.print(digitalRead(DOUT));
                Serial.printf("%d", digitalRead(DOUT));
                if (i % 4 == 0)
                    Serial.printf(" ");
                if (i == 44)
                {
                    Serial.println();
                }
            }
            else if (i == 45)
            {
                digitalWrite(SCLK, HIGH);
                delayMicroseconds(50);
                digitalWrite(SCLK, LOW);
                Serial.print(digitalRead(DOUT));
            }
        }
        Serial.println();
    }
    return regis;
}

void AS1412::sendRegis(int data)
{
    int dout = 0;
    int regis = 0;
    int cmd = 0b1100101;
    pinMode(DOUT, INPUT);
    if (data_ready())
    {
        dout = myshiftIn(DOUT, SCLK, READ_DATA, 24);

        // for (int i = 0; i < 46; i++)
        // {
        //   if (i < 29)
        //   {
        //     dout = myshiftIn(DOUT, SCLK, READ_DATA, 24);
        //   }
        //   else if (i < 36)
        //   {
        //     pinMode(DOUT, OUTPUT);
        //     digitalWrite(SCLK, HIGH);
        //     digitalWrite(SCLK, LOW);
        //     digitalWrite(DOUT, !!(cmd & (1 << (35 - i))));
        //     Serial.print(!!(cmd & (1 << (35 - i))));
        //     if(i == 35)
        //     {
        //       Serial.println();
        //     }
        //   }
        //   else if (i == 36)
        //   {
        //     digitalWrite(SCLK, HIGH);
        //     digitalWrite(SCLK, LOW);
        //   }
        //   else if (i < 45)
        //   {
        //     digitalWrite(SCLK, HIGH);
        //     digitalWrite(SCLK, LOW);
        //     digitalWrite(DOUT, !!(data & (1 << (44 - i))));
        //     Serial.print(!!(data & (1 << (44 - i))));
        //     ;
        //     if (i == 44)
        //     {
        //       Serial.println();
        //     }
        //   }
        //   else if (i == 45)
        //   {
        //     digitalWrite(SCLK, HIGH);
        //     digitalWrite(SCLK, LOW);
        //     Serial.print(digitalRead(DOUT));
        //   }
    }
    Serial.println();
}
