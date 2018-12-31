#ifndef lb_config
#define lb_config

#if (ARDUINO >=100)
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

class ConfigFile{
  public:
    // Initializer
    static void init(String path);

    // Methods
    static bool reload(); //Load file from memory
    static bool save(); //Save file to memory
    static bool save(String content); //Overwrites entire file with given string, for debug purposes
    static String getValue(String key); //Get value from file
    static bool setValue(String key, String value); //Set value to file
    static String readFile(); //Read entire file

  private:
    static String _content;
    static String _path;
};

#endif
