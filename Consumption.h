#ifndef consumption_mod
#define consumption_mod

#if (ARDUINO >=100)
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

#include "esp_adc_cal.h"

class Consumption{
  public:
    static void begin();
    static uint32_t getPower(); //returns mW
    static uint16_t getVoltage(); //returns mV
    static uint16_t getCurrent(); //returns mA
  private:
    static void loop(void*);
    static esp_adc_cal_characteristics_t *adc_chars_vin;
	static esp_adc_cal_characteristics_t *adc_chars_current;
};

#endif
