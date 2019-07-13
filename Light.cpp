#include "Light.h"
#include "pins.h"
#include "Settings.h"
#include "driver/adc.h"
#include "LEDoutput.h"

#define BETA 0.5

CH2B Light::_calibData = {0,0,0,0,0};
int32_t Light::_low = 0;
int32_t Light::_high = 65535;
VEML7700 Light::_als;

void Light::calibrate(){
  CHOUT chout;

  chout.a = 0; chout.b = 0; chout.c = 0; chout.d = 0; chout.e = 0; chout.t = 0;
  LEDoutput::applyCHOUT(chout);
  uint16_t outsource;
  delay(50);
  _als.getALS(outsource);

  chout.a = 255;
  LEDoutput::applyCHOUT(chout);
  delay(50);
  _als.getALS(_calibData.a);

  chout.a = 0; chout.b = 255;
  LEDoutput::applyCHOUT(chout);
  delay(50);
  _als.getALS(_calibData.b);

  chout.b = 0; chout.c = 255;
  LEDoutput::applyCHOUT(chout);
  delay(50);
  _als.getALS(_calibData.c);

  chout.c = 0; chout.d = 255;
  LEDoutput::applyCHOUT(chout);
  delay(50);
  _als.getALS(_calibData.d);

  chout.d = 0; chout.e = 255;
  LEDoutput::applyCHOUT(chout);
  delay(50);
  _als.getALS(_calibData.e);

  chout.e = 0;
  LEDoutput::applyCHOUT(chout);

  _calibData.a = max(_calibData.a,outsource) - min(_calibData.a,outsource);
  _calibData.b = max(_calibData.b,outsource) - min(_calibData.b,outsource);
  _calibData.c = max(_calibData.c,outsource) - min(_calibData.c,outsource);
  _calibData.d = max(_calibData.d,outsource) - min(_calibData.d,outsource);
  _calibData.e = max(_calibData.e,outsource) - min(_calibData.e,outsource);

  Serial.print("Light: calibration: ");Serial.print(String(outsource)+" ");Serial.print(_calibData.a,DEC);Serial.print(" ");Serial.print(_calibData.b,DEC);Serial.print(" ");Serial.print(_calibData.c,DEC);Serial.print(" ");Serial.print(_calibData.d,DEC);Serial.print(" ");Serial.print(_calibData.e,DEC);Serial.print("\n");
}

void Light::begin()
{
  _als.begin();
  _als.setGain(VEML7700::ALS_GAIN_d8);
  _als.setIntegrationTime(VEML7700::ALS_INTEGRATION_25ms);
  _als.setPowerSaving(0);
  _als.setPowerSaving(VEML7700::ALS_POWER_MODE_1);

  calibrate();
  Serial.println("Light: ok");
}

int16_t Light::loop()
{
  uint16_t source = getOutsource();
  Serial.println("Light: loop: outsource: "+String(source));
  int16_t res = map(source,_low,_high,1000,0);
  if(res < 0)res = 0; if(res > 1000)res = 1000;
  Serial.println("Light: loop: suggestedI: "+String(res));
  return res;
}

void Light::set(int16_t intensity)
{
  uint16_t initL = getOutsource();
  _low = initL - (1000-intensity)*BETA;
  _high = initL + intensity*BETA;
  Serial.println("Light: initL: "+String(initL)+" low: "+String(_low)+" high: "+String(_high));
}

uint32_t Light::getOutsourceLux()
{
  float lux;
  _als.scaleLux(getOutsource(), lux);
  return uint32_t(lux*1000);
}

uint16_t Light::getOutsource()
{
  int32_t raw;
  uint16_t als;
  Serial.println(millis());
  _als.getALS(als);
  Serial.println(millis());
  raw = als;
  CHOUT current = LEDoutput::getCurrentCHOUT();

  Serial.println("Light: raw-wl: "+String(raw));

  raw = raw - (current.a*_calibData.a/255);
  raw = raw - (current.b*_calibData.b/255);
  raw = raw - (current.c*_calibData.c/255);
  raw = raw - (current.d*_calibData.d/255);
  raw = raw - (current.e*_calibData.e/255);

  Serial.println("Light: raw-wol: "+String(raw));
  if(raw < 0) raw = 0;
  return (uint16_t)raw;
}