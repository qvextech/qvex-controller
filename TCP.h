#ifndef tcp_mod
#define tcp_mod

#if (ARDUINO >=100)
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

#include <WiFi.h>

class TCP{
  public:
    static void begin();
    static void loop();

  private:
    static WiFiServer _server;
    static uint8_t _ref;
    
};

#endif
