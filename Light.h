#ifndef lb_light_mod
#define lb_light_mod

#if (ARDUINO >=100)
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

#include "struct_def.h"

class Light{
  public:
    static int16_t loop();
    static void set(int16_t);
    static uint16_t getOutsource();
    static void adjust(CHOUT);
    static void calibrate();
  private:
    static int16_t _low;
    static int16_t _high;
    //static CH2B _calibData;
    static uint16_t calibrateSet(byte,byte,byte,byte,byte);
};

#endif
