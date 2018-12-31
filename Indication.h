#ifndef indication_mod
#define indication_mod

#if (ARDUINO >=100)
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

class Indication{
  public:
    static void stop();
    static void blink(uint16_t);
    static void done();
  private:
    static void code_blink(void*);
    static void code_done(void*);
    static TaskHandle_t _currentTask;
    static uint16_t _tmp_uint;
};

#endif
