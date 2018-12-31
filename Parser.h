#ifndef lb_parser_mod
#define lb_parser_mod

#if (ARDUINO >=100)
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

class Parser{
  public:
    static void processJSON(String);
};

#endif

