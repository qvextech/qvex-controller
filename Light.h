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
    static uint16_t getOutsource();
    static void adjust(CHOUT);
    static void calibrate();
  private:
    static VEML7700 _als;
    static int32_t _low;
    static int32_t _high;
    //static CH2B _calibData;
    static uint16_t calibrateSet(byte,byte,byte,byte,byte);
};

#endif
