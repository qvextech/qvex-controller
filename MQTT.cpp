#include <PubSubClient.h>
#include <WiFi.h>
#include "MQTT.h"
#include "struct_def.h"
#include "Parser.h"
#include "WIFI.h"
#include "Config.h"

String MQTT::_mac = "";
String MQTT::_topic = "";

WiFiClient espClient;
PubSubClient client(espClient);

void MQTT::begin()
{
  _mac = WiFi.macAddress();
  _mac.replace(":","");
  _topic = ConfigFile::getValue("mqtt_u")+"/"+ConfigFile::getValue("sku")+"/"+_mac;  
  client.setServer("192.168.0.95", 1883);
  client.setCallback(MQTT::callback);
}

void MQTT::reconnect() {
  if (client.connect(_mac.c_str(), ConfigFile::getValue("mqtt_u").c_str(), ConfigFile::getValue("mqtt_p").c_str())){
    Serial.println("MQTT: ok: "+_topic);
    client.subscribe(_topic.c_str());
  } else {
    Serial.print("MQTT failed: rc=");
    Serial.println(client.state());
  }
}

void MQTT::loop()
{
  if (!client.connected()) 
  {
    reconnect();
  }
  else
  {
    client.loop();
  }
}

void MQTT::callback(char* topic, byte* payload, unsigned int length) {
  Serial.println("MQTT: callback");
  String json = (char*)payload;
  Parser::processJSON(json);
}

