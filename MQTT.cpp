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
  _topic = Config::mqtt_user+"/"+Config::sku+"/"+_mac;  
  client.setServer(Config::mqtt_url.c_str(), 1883);
  client.setCallback(MQTT::callback);
}

void MQTT::reconnect() {
  if (client.connect(_mac.c_str(), Config::mqtt_user.c_str(), Config::mqtt_password.c_str())){
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

