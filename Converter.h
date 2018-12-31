#ifndef lb_converter
#define lb_converter

#if (ARDUINO >=100)
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

#include "struct_def.h"

class Converter{
  public:
    static ColorMessage convert(ColorMessage);
    static CHOUT mapChannels(ColorMessage);
  private:
    static RGB rgbDiff(RGB,RGB);
    static RGBW getColorFromRGB(RGB,RGB);
};

#endif
