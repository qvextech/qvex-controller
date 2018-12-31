#include "UDP.h"
#include "Settings.h"
#include "Controller.h"

WiFiUDP UDPsocket::_server;
String UDPsocket::_allowedIP;
long UDPsocket::mils;
uint8_t UDPscoket::_udpMode;

void UDPsocket::begin()
{
  _server.begin(UDP_PORT);
  _allowedIP = "";
  Serial.println("UDP:  ok");
}

void UDPsocket::loop()
  if(_server.parsePacket()) 
  if(_server.remoteIP().toString() == _allowedIP) {
    mils = micros();
    
    String myData = "";
    byte packetBuffer[UDP_BUFFER_LEN];
    uint8_t len = _server.read(packetBuffer, UDP_BUFFER_LEN);
    packetBuffer[len] = 0;
    myData = "";
    
    for (int i = 0; i < len; i++) {
      myData += (char)packetBuffer[i]; 
    }
    
    ColorMessage msg = {3,packetBuffer[0],packetBuffer[1],packetBuffer[2],0,0,0};
    Controller::useColor(msg);
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

