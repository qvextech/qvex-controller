#ifndef http_mod
#define http_mod

#if (ARDUINO >=100)
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

#include <WebServer.h>

class QHTTP{
	public:
    static long mic1;
		static void begin();
    static void loop();
	private:
    static void settings();
    static void colorReceived();
		static WebServer _HTTP;
};

#endif
