#include "Config.h"
#include "FS.h"
#include "SPIFFS.h"
#include "Settings.h"

String Config::device_name, Config::mqtt_password, Config::mqtt_user, Config::mqtt_url, Config::sku;
bool Config::lsens_enable,Config::touch_enable,Config::power_enable,Config::mqtt_enable;
uint8_t Config::strip_type;
uint16_t Config::pixel_count,Config::lsens_beta,Config::switch_time,Config::fw_version;

//Constructor
bool Config::init() {
  SPIFFS.begin();
  return load();
}

//Methods
bool Config::load() {

  uint16_t i;

  i=0;
  String content = readFile(CONFIG_PATH);
  if(content != "")
  {
    lsens_enable = getBool(content.substring(i,content.indexOf('\n',i))); i = content.indexOf('\n',i)+1;
    power_enable = getBool(content.substring(i,content.indexOf('\n',i))); i = content.indexOf('\n',i)+1;
    touch_enable = getBool(content.substring(i,content.indexOf('\n',i))); i = content.indexOf('\n',i)+1;
    mqtt_enable = getBool(content.substring(i,content.indexOf('\n',i))); i = content.indexOf('\n',i)+1;
    pixel_count = getInt(content.substring(i,content.indexOf('\n',i))); i = content.indexOf('\n',i)+1;
    strip_type = getInt(content.substring(i,content.indexOf('\n',i))); i = content.indexOf('\n',i)+1;
    switch_time = getInt(content.substring(i,content.indexOf('\n',i))); i = content.indexOf('\n',i)+1;
    device_name = content.substring(i,content.indexOf('\n',i)); i = content.indexOf('\n',i)+1;
    lsens_beta = getInt(content.substring(i,content.indexOf('\n',i))); i = content.indexOf('\n',i)+1;
    fw_version = getInt(content.substring(i,content.indexOf('\n',i))); i = content.indexOf('\n',i)+1;
    sku = content.substring(i,content.indexOf('\n',i)); i = content.indexOf('\n',i)+1;
    mqtt_user = content.substring(i,content.indexOf('\n',i)); i = content.indexOf('\n',i)+1;
    mqtt_password = content.substring(i,content.indexOf('\n',i)); i = content.indexOf('\n',i)+1;
    mqtt_url = content.substring(i,content.indexOf('\n',i)); i = content.indexOf('\n',i)+1;
  }else return false;

  return true;
}

bool Config::save(){
  String content;

  if(!SPIFFS.exists(CONFIG_PATH))return false;
  File f = SPIFFS.open(CONFIG_PATH, "r+");
  if(!f)return false;

  content="";
  content+=String((int)lsens_enable)+"\n";
  content+=String((int)power_enable)+"\n";
  content+=String((int)touch_enable)+"\n";
  content+=String((int)mqtt_enable)+"\n";
  content+=String(pixel_count)+"\n";
  content+=String(strip_type)+"\n";
  content+=String(switch_time)+"\n";
  content+=device_name+"\n";
  content+=String(lsens_beta)+"\n";
  content+=String(fw_version)+"\n";
  content+=sku+"\n";
  content+=mqtt_user+"\n";
  content+=mqtt_password+"\n";
  content+=mqtt_url+"\n";

  f.print(content);
  f.close();

  return true;
}

String Config::readFile(String path){
  if(!SPIFFS.exists(path))return "";
  File f = SPIFFS.open(path, "r+");
  if(!f)return "";
  String content = f.readString();
  f.close();
  return content;
}

String Config::readFileAsJSON(String path){
/*  String content = _content;
  int start = 0;
  int cursor = 0;
  String json = "{";

  while(start < content.length())
  {
    if(start != 0)json+=",";
    cursor = content.indexOf("=",start);
    json+="\""+content.substring(start,cursor)+"\""+":";
    start = content.indexOf("\n",cursor)+1;
    json+="\""+content.substring(cursor+1,start-2)+"\"";
  }

  json+="}";
  return json;*/
}

bool Config::getBool(String string){
  Serial.println("getBool of: "+string);
  return (bool)string.toInt();
}

int Config::getInt(String string){
  Serial.println("getInt of: "+string);
  return string.toInt();
}