#ifndef lb_config
#define lb_config

#if (ARDUINO >=100)
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

class Config{
  public:
    // Initializer
    static bool init();

    // Methods
    static bool load(); //Load file from memory priv or pub
    static bool save(); //Save public config to memory
    static String readFile(String); //Read entire file
    static String readFileAsJSON(String); 

    //Config
    static String device_name,sku,mqtt_user,mqtt_password,mqtt_url;
    static bool lsens_enable,touch_enable,power_enable,mqtt_enable;
    static uint8_t strip_type;
    static uint16_t pixel_count,lsens_beta,switch_time,fw_version;

  private:
    static bool getBool(String);
    static int getInt(String);
};

#endif
