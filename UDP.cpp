#include "UDP.h"
#include "Settings.h"
#include "Controller.h"
#include "LEDoutput.h"

WiFiUDP UDPsocket::_server;
String UDPsocket::_allowedIP;
long UDPsocket::mils;

void UDPsocket::begin()
{
  _server.begin(UDP_PORT);
  _allowedIP = "";
  Serial.println("UDP:  ok");
}

void UDPsocket::loop()
{
  if(_server.parsePacket()) 
  if(_server.remoteIP().toString() == _allowedIP) {
    mils = micros();

    byte packetBuffer[UDP_BUFFER_LEN];
    uint16_t len = _server.read(packetBuffer, UDP_BUFFER_LEN);
    
    processPacket(packetBuffer,len);
  }
  else
  {
    Serial.println("UDP: IP rejected: "+_server.remoteIP().toString());
  }
  _server.flush();
}

void UDPsocket::allow(String newIP)
{
  _allowedIP = newIP;
  Serial.println("UDP: allowed IP set to "+_allowedIP);
}

void UDPsocket::processPacket(byte data[],uint16_t length)
{
  switch(Controller::getMode())
  {
    case 1:
    {
        ColorMessage msg = {3,data[0],data[1],data[2],0,0,0};
        Controller::useColor(msg);
        break;
    }
    case 2:
        //if(length>ADDRESSABLE_LED_NUM*4)length=ADDRESSABLE_LED_NUM*4; //Issue: ADDRESSABLE_LED_NUM may return 0
        LEDoutput::output(data,length);
        break;
  }
}

