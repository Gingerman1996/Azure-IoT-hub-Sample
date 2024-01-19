#include "PH_sensor_temp.h"

AS1412 _myADC(DOUT, SCLK);
FIR<float, FILTER_TAP_NUM> fir_lp;
OneWire oneWire(Temp_AIN);
DallasTemperature temp(&oneWire);
DeviceAddress temperatureAddress;

static float coef_lp[FILTER_TAP_NUM] = {-739, -4287, -10846, -17843, -19459, -11695, 2365, 12558,
                                        9836, -3841, -14769, -9785, 8690, 21429, 10328, -19556,
                                        -37339, -10814, 61324, 140496, 174838, 140496, 61324, -10814,
                                        -37339, -19556, 10328, 21429, 8690, -9785, -14769, -3841,
                                        9836, 12558, 2365, -11695, -19459, -17843, -10846, -4287, -739};
void PH_sensor_temp::begin()
{
    EEPROM.begin(EEPROM_SIZE);
    _myADC.init();
    ph.begin();
    temp.begin();
    fir_lp.setFilterCoeffs(coef_lp);
}

float PH_sensor_temp::get_pH()
{
    float voltage;
    float phValue;
    float temperature = this->get_temp_f();

    voltage = _myADC.readData();

    float data_fir = fir_lp.processReading(voltage) * 15;
    float data_voltage = (data_fir / pow(2, 24)) * 3300 + 1100;
    phValue = ph.readPH(data_voltage, temperature);
    return (phValue);
}

float PH_sensor_temp::get_ph_voltage()
{
    float voltage;
    float phValue;
    float temperature = this->get_temp_f();

    voltage = _myADC.readData();

    float data_fir = fir_lp.processReading(voltage) * 15;
    float data_voltage = (data_fir / pow(2, 24)) * 3300 + 1100;
    return (data_voltage);
}

void PH_sensor_temp::cal_ph(char *cmdph)
{
    float voltage;
    float temperature = this->get_temp_f();

    voltage = _myADC.readData(); // read the voltage
    float data_fir = fir_lp.processReading(voltage) * 15;
    float data_voltage = (data_fir / pow(2, 24)) * 3300 + 1100;
    ph.calibration(data_voltage, temperature, cmdph);
}

float PH_sensor_temp::get_temp_f()
{
    temp.requestTemperatures();
    return (temp.getTempCByIndex(0));
}