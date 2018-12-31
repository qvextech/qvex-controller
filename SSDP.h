#ifndef ssdp_mod
#define ssdp_mod

#if (ARDUINO >=100)
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

#include <WiFi.h>

class QSSDP{
	public:
		static void begin();
		static void schema(WiFiClient);
};

#endif
