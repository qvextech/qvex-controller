#include <ArduinoJson.h>
#include "Parser.h"
#include "Controller.h"

void Parser::processJSON(String json)
{
  DynamicJsonBuffer jsonBuffer(2);
  JsonObject& root = jsonBuffer.parseObject(json);

  int x = root["type"];
  switch (x) {
    case 1: //SC
    case 2: //CCT
    case 3: //RGB
    case 4: //RGBW
    case 5: //WRGBWW
    {
      ColorMessage msg = {root["type"], root["color"]["r"], root["color"]["g"], root["color"]["b"], root["color"]["w"], root["color"]["ww"], root["time"]};
      Controller::useColor(msg);
      break;
    }
    default:
      Serial.println("Invalid message type");
      break;
  }
}
