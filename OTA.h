#ifndef ota_mod
#define ota_mod

#if (ARDUINO >=100)
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

class OTA{
  public:
    static void begin();  
  private:
    static void code_loop(void*);
    static TaskHandle_t _currentTask;
    static void checkUpdate();
     
};

#endif
