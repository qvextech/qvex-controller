#ifndef lb_light_mod
#define lb_light_mod

#if (ARDUINO >=100)
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

#include "struct_def.h"
#include <Wire.h>
#include <VEML7700.h>

class Light{
  public:
    static void begin();
    static int16_t loop();
    static void set(int16_t);
    static uint16_t getOutsource(); //Returns raw uint16_t full range
    static uint16_t getAvgOutsource(); //Returns 50-sample averaged outsource value
    static uint32_t getOutsourceLux(); //Returns mililux
    static void adjust(CHOUT);
    static void calibrate();
    static bool pause;
  private:
    static int16_t getIfromValue(uint16_t);
    static void code_loop(void*);
    static VEML7700 _als;
    static int32_t _low;
    static int32_t _high;
    static CH2B _calibData;
    static uint16_t calibColor(CHOUT);
    static TaskHandle_t _currentTask;
};

#endif
