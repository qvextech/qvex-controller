#include "HTTP.h"
#include "SSDP.h"
#include "Config.h"
#include "Settings.h"
#include "Controller.h"
#include "UDP.h"
#include "struct_def.h"
#include "Consumption.h"
#include "Light.h"
#include "WiFi.h"

WebServer QHTTP::_HTTP(80);
long QHTTP::mic1 = 0;

void QHTTP::begin()
{
  //SSDP device description
  _HTTP.on("/description.xml", HTTP_GET, []() {
    QSSDP::schema(_HTTP.client());
  });

  //Apply to device's settings
  _HTTP.on("/set", HTTP_POST, set);

  //Change color
  _HTTP.on("/color", HTTP_POST, colorReceived);

  //Change intensity
  _HTTP.on("/intensity", HTTP_POST, intensity);

  //Get device settings
  _HTTP.on("/get/settings",HTTP_GET, []() {
    _HTTP.send(200, "text/plain", ConfigFile::readFileAsJSON());
  });

  //Get device info
  _HTTP.on("/get/mac",HTTP_GET, []() {
    String mac = WiFi.macAddress();
    mac.replace(":","");
    _HTTP.send(200, "text/plain", mac);
  });

  _HTTP.on("/get/power",HTTP_GET, []() {
    _HTTP.send(200, "text/plain", String(Consumption::getPower()));
  });

  _HTTP.on("/get/voltage",HTTP_GET, []() {
    _HTTP.send(200, "text/plain", String(Consumption::getVoltage()));
  });

  _HTTP.on("/get/current",HTTP_GET, []() {
    _HTTP.send(200, "text/plain", String(Consumption::getCurrent()));
  });

  _HTTP.on("/get/light",HTTP_GET, []() {
    _HTTP.send(200, "text/plain", String(Light::getOutsourceLux()));
  });

  //Request to start UDP channel
  _HTTP.on("/startUDP", HTTP_POST, []() {
    if(_HTTP.arg("individual")=="1" && Controller::getMode() != 2)Controller::setMode(2);
    UDPsocket::allow(_HTTP.arg("ip"));
    String pixes = ConfigFile::getValue("PIX_COUNT");
    _HTTP.send(200, "text/plain", "{\"pixels\":"+pixes+",\"max_packet\":"+String(pixes.toInt()*4)+"}");
  });

  _HTTP.on("/endUDP", HTTP_POST, []() {
    Controller::setMode(1);
    UDPsocket::allow("");
    _HTTP.send(200, "text/plain", "OK");
  });




  _HTTP.begin();
  Serial.println("HTTP: ok");
}

void QHTTP::loop()
{
  _HTTP.handleClient();
}

void QHTTP::set()
{
  for (int i = 0; i < _HTTP.args(); i++)ConfigFile::setValue(_HTTP.argName(i), _HTTP.arg(i));
  ConfigFile::save();
  _HTTP.send(200, "text/plain", "OK");
  delay(50);
  ESP.restart();
}

void QHTTP::colorReceived()
{
  ColorMessage msg = {_HTTP.arg("type").toInt(), _HTTP.arg("r").toInt(), _HTTP.arg("g").toInt(), _HTTP.arg("b").toInt(), _HTTP.arg("w").toInt(), _HTTP.arg("ww").toInt(), _HTTP.arg("time").toInt()};
  Controller::useColor(msg);
  _HTTP.send(200, "text/plain", "OK");
}

void QHTTP::intensity()
{
  Controller::applyIntensity(_HTTP.arg("value").toInt());
  _HTTP.send(200, "text/plain", "OK");
}
