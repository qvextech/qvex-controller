/*LB-FW Controller module (core module)

   Takes care of
   - Executing color/state control requests
   - Saving state and color to RAM and/or flash memory (according to settings)
   - Converting CCT/SC/RGB/WRGBWW/RGBW/HSL values to specific channels according to strip type setting (using convertor module)
   - Adjusting light levels according to light sensor (using Lsens module)

   << MODULE SCHEME
    Parser      ->
    Touch       ->
    Animation   ->
                    Controller
                                -> LED Output
   <<
*/

#ifndef controller_mod
#define controller_mod

#if (ARDUINO >=100)
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

#include "struct_def.h"

class Controller {
  public:
    // Methods
    static void useColor(ColorMessage);
    static void state(bool);
    static void state();
    static uint16_t getIntensity();
    static void previewIntensity(uint16_t);
    static void applyIntensity(uint16_t);
    static void setMode(uint8_t);
    static uint8_t getMode();
    static void loopNetwork();

  private:
    static ColorMessage getFromMaxed(ColorMessage,uint16_t);
    static ColorMessage getFromMaxed(ColorMessage);
    static ColorMessage getMaxed(ColorMessage);
    static int16_t _intensity;
    static bool _state;
    static ColorMessage _color;
    static ColorMessage _maxed;
    static uint8_t _currentMode;

};

#endif

