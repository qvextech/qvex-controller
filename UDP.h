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

  private:
    static void processPacket(byte[],uint16_t);
    static WiFiUDP _server;    
    static String _allowedIP;
    static uint16_t _maxPacketLength;
};

#endif
