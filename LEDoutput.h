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
      static void output(ColorMessage, bool=true);
      static void output(byte[],uint16_t);
      static void begin();
      static bool busy;
      static CHOUT getCurrentOutput();
    private:
      static void outputTask(void*);
      static void outputCode(ColorMessage);
      static void applyCHOUT(CHOUT);
      static void applyAddressable(ColorMessage);
      static void applyCHOUToverTime(CHOUT,CHOUT);
      static TaskHandle_t _currentTask;
      static NeoPixelBus<NeoGrbFeature, Neo800KbpsMethod>* _addressableStrip;
      static ColorMessage _msg;
      static CHOUT _stored_output;

};

#endif
