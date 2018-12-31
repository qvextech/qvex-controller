#include "TCP.h"
#include "Settings.h"

WiFiServer TCP::_server(TCP_PORT);

void TCP::begin()
{
  _server.begin();
  Serial.println("TCP:  ok");
}

void TCP::loop()
{
  WiFiClient client = _server.available();
  if(client)
  {
    Serial.println("TCP: client connected");
    while(client.connected())
    {
      if(client.available())
      {
        char c = client.read();
        Serial.write(c);
      }
    }
    Serial.println("TCP: client disconnected");
  }
}
