#include "Config.h"

#define CONFIG_PATH "/main.cfg"

//Define PCB version here <--
//#define PCB_DEV_0_1
//#define PCB_DEV_1_1
#define PCB_DEV_1_2

#define ADC_NO_OF_SAMPLES   100

#define DEVICE_NAME Config::device_name

//Default transition time
#define TRANS_T_DEF 500

//Enable automatic brightness [0,1]
#define LSENS_EN Config::lsens_enable
/* 
 *  Define LED strip type
 *  1 - SC
 *  2 - CCT
 *  3 - RGB
 *  4 - RGBW
 *  5 - WRGBWW
 *  
 *  13 - NEOPIXEL RGB
 *  14 - NEOPIXEL RGBW
 */
#define STRIP_TYPE Config::strip_type

//Number of addressable LEDs
#define ADDRESSABLE_LED_NUM Config::pixel_count
#define ADDRESSABLE_LED_NUM_DIRECT 30

//PWM settings
#define RESOLUTION 9
#define FREQUENCY 12000

//Enable MQTT [0,1]
#define MQTT_EN Config::mqtt_enable

//UDP
#define UDP_EN 1
#define UDP_PORT 7007
#define UDP_BUFFER_LEN 1000
//Touch
#define TOUCH_EN Config::touch_enable
#define TOUCH_CAL_SAMPLES 20

//Consumption meter
#define METER_EN Config::power_enable

//OTA update
#define OTA_GET_VERSION_URL "http://192.168.0.95/getVersion.php"

//Controller default mode
#define MODE_DEF 1

//Onboard indication addressable LEDs
#define ONBOARD_LED_NUM 4

//Safety settings
#define INNER_TEMP_THRESHOLD 60