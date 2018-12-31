#ifndef lb_touch_mod
#define lb_touch_mod

#if (ARDUINO >=100)
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

#include "struct_def.h"

class Touch{
  public:
    static void begin();
    static void loop(void*);
    static void calibrate();
    
  private:
    static void handleTouch();
    static int readTouch();
    static uint8_t _ref;
};

#endif
