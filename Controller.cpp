#include "Controller.h"
#include "Converter.h"
#include "LEDoutput.h"
#include "Settings.h"
#include <algorithm>
#include <initializer_list>

/*#define max(a,b) \
  ({ __typeof__ (a) _a = (a); \
      __typeof__ (b) _b = (b); \
    _a > _b ? _a : _b; })
*/
ColorMessage Controller::_color = {0, 255, 0, 255, 0, 0};// [unused,r,g,b,w,ww,unused]
ColorMessage Controller::_maxed = {0, 255, 0, 255, 0, 1000};// [unused,r,g,b,w,ww,intensity]
bool Controller::_state = false;

// >>> Public methods <<<

void Controller::useColor(ColorMessage msg)
{
  msg = Converter::convert(msg);
  _color = msg;
  if (TOUCH_EN || LIGHTSENS_EN)_maxed = getMaxed(msg);
  //Set LSENS new intensity HERE
  Serial.println("Controller: from " + String(msg.r) + " to " + String(_maxed.r) + " with " + String(_maxed.t) + " multiplier");
  _state = true;
  LEDoutput::output(msg);
}

void Controller::state(bool new_state)
{
  if (new_state && !_state) // New state ON
  {
    _state = true;
    ColorMessage msg = _color;
    msg.t = TRANS_T_DEF;
    Serial.println("Controller: outputing: " + String(msg.r) + "  " + String(msg.g) + "  " + String(msg.b) + "  " + String(msg.w) + "  " + String(msg.ww) + "  " + String(msg.t));
    LEDoutput::output(msg);
  }
  else if (!new_state && _state) // New state OFF
  {
    _state = false;
    ColorMessage msg = {0, 0, 0, 0, 0, 0, TRANS_T_DEF};
    LEDoutput::output(msg);
  }
}
void Controller::state(){state(!_state);}


//Intensity methods
uint16_t Controller::getIntensity(){return _maxed.t;}

void Controller::previewIntensity(uint16_t intensity)
{
  //Pause LSENS if not paused HERE
  LEDoutput::output(getFromMaxed(_maxed,intensity));
}

void Controller::applyIntensity(uint16_t intensity)
{
  _maxed.t = intensity;
  _color = getFromMaxed(_maxed);
  LEDoutput::output(_color);
  //Resume LSENS somewhere here (colision alert)
}




// >>> Private methods <<<
// get maxed color from the provided color
ColorMessage Controller::getMaxed(ColorMessage msg)
{
  byte maximum = std::max({msg.r, msg.g, msg.b, msg.w, msg.ww});
  float mul = 255.0 / maximum;
  ColorMessage res = {msg.type, msg.r * mul, msg.g * mul, msg.b * mul, msg.w * mul, msg.ww * mul};
  res.t = (float)maximum / (std::max({res.r, res.g, res.b, res.w, res.ww})) * 1000;
  return res;
}
//get color from 
ColorMessage Controller::getFromMaxed(ColorMessage msg){return getFromMaxed(msg,msg.t);}
ColorMessage Controller::getFromMaxed(ColorMessage msg,uint16_t intensity)
{
  msg.r = msg.r*intensity/1000;
  msg.g = msg.g*intensity/1000;
  msg.b = msg.b*intensity/1000;
  msg.w = msg.w*intensity/1000;
  msg.ww = msg.ww*intensity/1000;
  msg.t = 0;
  return msg;
}


