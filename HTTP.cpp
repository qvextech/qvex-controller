#include "HTTP.h"
#include "SSDP.h"
#include "Settings.h"
#include "Controller.h"
#include "UDP.h"
#include "struct_def.h"

WebServer QHTTP::_HTTP(80);
long QHTTP::mic1 = 0;

void QHTTP::begin()
{
  _HTTP.on("/description.xml", HTTP_GET, []() {
    QSSDP::schema(_HTTP.client());
  });
  _HTTP.on("/settings", HTTP_POST, settings);
  _HTTP.on("/color", HTTP_POST, colorReceived);
  _HTTP.on("/startUDP", HTTP_POST, []() {
    UDPsocket::allow(_HTTP.arg("ip"));
    _HTTP.send(200, "text/plain", "OK");
  });
  _HTTP.begin();
  Serial.println("HTTP: ok");
}

void QHTTP::loop()
{
  _HTTP.handleClient();
}

void QHTTP::settings()
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

