#ifndef lb_mqtt_mod
#define lb_mqtt_mod

#if (ARDUINO >=100)
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

class MQTT{
  public:
    static void begin();
    static void loop();

  private:
    static void callback(char*,byte*,unsigned int);
    static void reconnect();
    static String _topic;
    static String _mac;
    static unsigned long _last;
    
};

#endif
