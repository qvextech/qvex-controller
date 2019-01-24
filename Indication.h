#ifndef indication_mod
#define indication_mod

#if (ARDUINO >=100)
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

#include <NeoPixelBus.h>
#include "struct_def.h"

class Indication{
  public:
    static void begin();
    static void stop();
    static void blink(uint8_t,uint8_t,uint8_t,uint16_t,uint8_t=0);
    static void breath(uint8_t,uint8_t,uint8_t,uint16_t,uint8_t=0);
    static void done();
  private:
    static void code_blink(void*);
    static void code_breath(void*);
    static void code_done(void*);
    static TaskHandle_t _currentTask;
    static NeoPixelBus<NeoGrbFeature, Neo800KbpsMethod> _addressableStrip;
    static uint16_t _tmp_uint;
};

#endif
