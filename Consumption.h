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
  private:
    static void loop(void*);
    //static esp_adc_cal_characteristics_t *adc_chars;
};

#endif
