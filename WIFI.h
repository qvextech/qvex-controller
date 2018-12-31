#ifndef lb_wifi
#define lb_wifi

#if (ARDUINO >=100)
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

#include <WiFi.h>

class WIFI{
  public:
    static void connect();
    static bool check();
    static void begin();
  private:
    static WiFiServer _server;
};

#endif
