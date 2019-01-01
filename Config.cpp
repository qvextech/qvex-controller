#include "Config.h"
#include "FS.h"
#include "SPIFFS.h"

String ConfigFile::_path = "";
String ConfigFile::_content = "";

//Constructor
void ConfigFile::init(String path) {
  SPIFFS.begin();
  _path = path;
  ConfigFile::reload();
}

//Methods
bool ConfigFile::reload() {
  if(SPIFFS.exists(_path))
  {
    File f = SPIFFS.open(_path, "r+");
    if(f)
    {
      _content = f.readStringUntil('#');
      f.close();
      return true;
    }
    return false;
  }
  else
  {
    _content = "#";
    return true;
  }
}

bool ConfigFile::save() {
  if(_content.length())
  {
    File f = SPIFFS.open(_path, "w+");
    f.print(_content+"#");
    f.close();
    return true;
  }
  else
  {
    return false;
  }
}

bool ConfigFile::save(String content) {
  File f = SPIFFS.open(_path, "w+");
  f.print(content+"#");
  f.close();
}

String ConfigFile::getValue(String key) {
  if(_content.length())
  {
    int from,to;
    from = _content.indexOf(key);
    if(from != -1)
    {
      //Return value of a key
      to = _content.indexOf("\n",from);
      if(to == -1) to = _content.length()-2;
      String res = _content.substring(from+key.length()+1,to-1);
      return res;
    }
    //Key not found
    return "\a";
  }
  //File not loaded
  return "";
}

bool ConfigFile::setValue(String key, String value) {
  if(_content.length())
  {
    String curVal = ConfigFile::getValue(key);
    if(curVal != "\a")
    {
      //Replace value of a key
      _content.replace(key+"="+curVal,key+"="+value);
      return true;
    }
    //Key not found
    _content = key+"="+value+"\n"+_content;
    return true;
  }
  //File not loaded
  return false;
}

String ConfigFile::readFile()
{
  if(_content.length())
  {
    return _content;
  }
  return "";
}

String ConfigFile::readFileAsJSON()
{
  String content = _content;
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
  return json;
}
