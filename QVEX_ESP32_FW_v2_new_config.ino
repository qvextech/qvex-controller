#include "WIFI.h"
#include "MQTT.h"
#include "Controller.h"
#include "Touch.h"
#include "LEDoutput.h"
#include "Settings.h"
#include "UDP.h"
#include "TCP.h"
#include "Consumption.h"
#include "Safety.h"
#include "HTTP.h"
#include "SSDP.h"
#include "OTA.h"
#include "pins.h"
#include "Light.h"
#include "Indication.h"

void setup() {
  Serial.begin(1000000);
  Config::init();
  Serial.println("_________\n\nConfig:\n"+Config::readFile(CONFIG_PATH)+"\n____________");
  Serial.println(Config::touch_enable);
  Serial.println(Config::strip_type);
  Serial.println(Config::mqtt_url);

  Indication::begin();
  Safety::begin(); //Stack - rtos timer overflow
  LEDoutput::begin();

  if (TOUCH_EN)Touch::begin();          //Start touch read thread
  if (LSENS_EN)Light::begin();
  if (METER_EN)Consumption::begin();
  WIFI::begin();
  WIFI::connect();
  OTA::begin();                         //Start OTA thread
  QHTTP::begin();
  QSSDP::begin();
  if (TCP_EN)TCP::begin();
  if (UDP_EN)UDPsocket::begin();
  if (MQTT_EN)MQTT::begin();
}

void loop() {
  if (WIFI::check())
  {
    Controller::loop();
  }
}