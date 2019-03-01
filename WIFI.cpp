#include "WIFI.h"
#include "Config.h"
#include "Indication.h"
#include "esp_wifi.h"
#include "esp_smartconfig.h"

void WIFI::begin()
{
  WiFi.mode(WIFI_STA);
  wifi_config_t conf;
  int8_t power;
  esp_wifi_get_max_tx_power(&power);
  Serial.println("WIFI: Power: "+String(power));
  esp_wifi_get_config(WIFI_IF_STA, &conf);
  const char* ssid = reinterpret_cast<const char*>(conf.sta.ssid);
  if (strlen(ssid) == 0)
  {
    Serial.println("WIFI: Starting ESP-TOUCH");
    WiFi.mode(WIFI_AP_STA);
    WiFi.beginSmartConfig();
    while (!WiFi.smartConfigDone()) {
      delay(1000);
      Serial.print("_");
    }
    Serial.print("\n");
  }
  else
  {
    Serial.print("WIFI: SSID: "+String(ssid)+" ");
    WiFi.begin();
  }
  WiFi.setSleep(false);
}

void WIFI::connect()
{
  Indication::breath(255,0,255,5);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Indication::stop();
  Indication::blink(0,255,0,100,3);
  Serial.print("\nWIFI: ok: ");
  Serial.println(WiFi.localIP());
}

bool WIFI::check()
{ 
  if (WiFi.status() != WL_CONNECTED)
  {
    return false;
  }
  return true;
}