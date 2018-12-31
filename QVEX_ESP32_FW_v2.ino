#include "WIFI.h"
#include "MQTT.h"
#include "struct_def.h"
#include "Controller.h"
#include "Touch.h"
#include "LEDoutput.h"
#include "Settings.h"
#include "TCP.h"
#include "UDP.h"
#include "Consumption.h"
#include "Safety.h"
#include "HTTP.h"
#include "SSDP.h"
#include "OTA.h"

void setup() {
  Serial.begin(1000000);
  ConfigFile::init("/main.cfg");
  Serial.println("_________\n\nConfig:");
  Serial.println(ConfigFile::readFile());

  //Safety::begin(); //Stack - rtos timer overflow
  LEDoutput::setup();

  if (TOUCH_EN)Touch::begin();
  WIFI::begin();
  WIFI::connect();
  OTA::begin();
  QHTTP::begin();
  QSSDP::begin();
  if (TCP_EN)TCP::begin();
  if (UDP_EN)UDPsocket::begin();
  if (MQTT_EN)MQTT::begin();
  if (METER_EN)Consumption::begin();
}

void loop() {
  if (WIFI::check())
  {
    QHTTP::loop();
    if (TCP_EN)TCP::loop();
    if (UDP_EN)UDPsocket::loop();
    if (MQTT_EN)MQTT::loop();
  }
}
