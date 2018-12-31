#include "Config.h"

//Default transition time
#define TRANS_T_DEF 500

//Enable automatic brightness [0,1]
#define LIGHTSENS_EN ConfigFile::getValue("LSENS_EN").toInt() 

/* 
 *  Define LED strip type
 *  1 - SC
 *  2 - CCT
 *  3 - RGB
 *  4 - RGBW
 *  5 - WRGBWW
 *  
 *  10 - NEOPIXEL RGB
 *  11 - NEOPIXEL RGBW
 */
#define STRIP_TYPE ConfigFile::getValue("STRIP_TYPE").toInt()

//Number of addressable LEDs
#define ADDRESSABLE_LED_NUM ConfigFile::getValue("PIX_COUNT").toInt()
#define ADDRESSABLE_LED_NUM_DIRECT 30

//PWM settings
#define RESOLUTION 8
#define FREQUENCY 5000

//Enable MQTT [0,1]
#define MQTT_EN ConfigFile::getValue("MQTT_EN").toInt()

//TCP
#define TCP_EN 0
#define TCP_PORT 6000

//UDP
#define UDP_EN 1
#define UDP_PORT 7007
#define UDP_BUFFER_LEN 64
//Touch
#define TOUCH_EN ConfigFile::getValue("TOUCH_EN").toInt()
#define TOUCH_CAL_SAMPLES 1000

//Consumption meter
#define METER_EN ConfigFile::getValue("METER_EN").toInt()

//OTA update
#define OTA_GET_VERSION_URL "http://192.168.0.95/getVersion.php"
