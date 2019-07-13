#include "OTA.h"
#include "Settings.h"
#include "Config.h"
#include "Indication.h"
#include <HTTPClient.h>
#include <ESP32httpUpdate.h>


TaskHandle_t OTA::_currentTask;

void OTA::begin()
{
  xTaskCreatePinnedToCore(code_loop,"OTA",20000,NULL,20,&_currentTask,1);
  Serial.println("OTA:  ok");
}

void OTA::code_loop(void*) 
{
  while(true)
  {
    delay(2500);
    checkUpdate();
    delay(2500);
  }
  vTaskDelete(NULL);
}

void OTA::checkUpdate()
{
  HTTPClient http;
  http.begin(OTA_GET_VERSION_URL);
  int httpCode = http.GET();
  if(httpCode == HTTP_CODE_OK) {
      uint16_t ver = http.getString().toInt();
      uint16_t curVer = Config::fw_version;
      if(curVer == 0) curVer = 60000;
      if(ver > curVer)
      {
        Serial.println("OTA: new FW ver on server: "+String(ver)+" (current: "+String(curVer)+")");
        ColorMessage blink = {0,20,0,20,0,0,60};
        //Indication::blink(blink);
        Serial.println("OTA: updating...");
        ESPhttpUpdate.rebootOnUpdate(false);
        t_httpUpdate_return ret = ESPhttpUpdate.update("http://192.168.0.95/qvex_fw/"+String(ver)+".bin");
        switch(ret) {
            case HTTP_UPDATE_FAILED:
                Serial.printf("HTTP_UPDATE_FAILD Error (%d): %s", ESPhttpUpdate.getLastError(), ESPhttpUpdate.getLastErrorString().c_str());
                Serial.println("");
                break;

            case HTTP_UPDATE_NO_UPDATES:
                Serial.println("HTTP_UPDATE_NO_UPDATES");
                break;

            case HTTP_UPDATE_OK:
                Serial.println("OTA: HTTP_UPDATE_OK");
                Config::fw_version=ver;
                Config::save();
                ESP.restart();
                break;
        }
      }
  }
  http.end();
}

