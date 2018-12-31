#ifndef udp_mod
#define udp_mod

#if (ARDUINO >=100)
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

#include <WiFiUdp.h>

class UDPsocket{
  public:
    static void begin();
    static void loop();
    static void allow(String);
    static long mils;

  private:
    static WiFiUDP _server;    
    static String _allowedIP;
};

#endif
