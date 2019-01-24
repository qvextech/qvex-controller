#ifndef ledoutput_mod
#define ledoutput_mod

#if (ARDUINO >=100)
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

#include "struct_def.h"
#include <NeoPixelBus.h>

class LEDoutput{
    public:
      static void output(ColorMessage);
      static void output(byte[],uint16_t);
      static void setup();
    private:
      static void applyCHOUT(void*);
      static void applyAddressable(void*);
      static TaskHandle_t _currentTask;
      static NeoPixelBus<NeoGrbwFeature, Neo800KbpsMethod> _addressableStrip;
      static ColorMessage _addr_msg;
      static CHOUT _classic_chout;
};

#endif
