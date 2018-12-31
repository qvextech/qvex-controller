#ifndef safety_mod
#define safety_mod

#if (ARDUINO >=100)
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

class Safety{
  public:
    static void begin();
  private:
    static void code_loop(void*);
    static TaskHandle_t _currentTask;
};

#endif
