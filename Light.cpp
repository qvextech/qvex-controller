#include "Light.h"

#define BETA 0.05
/*
CH2B Light::_calibData = {0,0,0,0,0};
int16_t Light::_low;
int16_t Light::_high;

void Light::calibrate(){
  /*uint16_t outsource = calibColor(0,0,0,0,0);
  
  _calibData.a = calibColor(255,0,0,0,0);
  _calibData.b = calibColor(0,255,0,0,0);
  _calibData.c = calibColor(0,0,255,0,0);
  _calibData.d = calibColor(0,0,0,255,0);
  _calibData.e = calibColor(0,0,0,0,255);

  _calibData.a = max(_calibData.a,outsource) - min(_calibData.a,outsource);
  _calibData.b = max(_calibData.b,outsource) - min(_calibData.b,outsource);
  _calibData.c = max(_calibData.c,outsource) - min(_calibData.c,outsource);
  _calibData.d = max(_calibData.d,outsource) - min(_calibData.d,outsource);
  _calibData.e = max(_calibData.e,outsource) - min(_calibData.e,outsource);

  CHOUT chout = {0,0,0,255,0,0};
  //SPIIF spiif.sendCH(chout);*/
//s}
/*
int16_t Light::loop()
{
  int16_t source = getOutsource();
  Serial.print("Source: "+String(source)+" | ");
  int16_t res = map(source,_low,_high,1000,0);
  return res;
}

void Light::set(int16_t intensity)
{
  uint16_t initL = getOutsource();
  _low = initL - (1000-intensity)*BETA;
  _high = initL + intensity*BETA;
  if(_low < 0) _low = 0;
  if(_high > 1022) _high = 1022;
  Serial.println("Light: initL: "+String(initL)+" low: "+String(_low)+" high: "+String(_high));
}

uint16_t Light::calibrateSet(byte a,byte b, byte c, byte d, byte e)
{
  CHOUT chout = {a,b,c,d,e,0};
  byte data[1] = {'l'};
  byte* in;
  
  //SPIIF spiif.sendCH(chout);
  delay(2000);
  //SPIIF spiif.send(data,1);
  delayMicroseconds(2000);
  //SPIIF in = spiif.receive(2);
  return (in[1] | in[0] << 8);
}

uint16_t Light::getOutsource()
{
  byte data[1] = {'l'};
  byte* in;
  //SPIIF spiif.send(data,1);
  delayMicroseconds(1000);
  //SPIIFin = spiif.receive(2);
  uint16_t res = (in[1] | in[0] << 8);
  /*Serial.print("Lsens calibration: ");Serial.print(_calibData.a,DEC);Serial.print(" ");Serial.print(_calibData.b,DEC);Serial.print(" ");Serial.print(_calibData.c,DEC);Serial.print(" ");Serial.print(_calibData.d,DEC);Serial.print(" ");Serial.print(_calibData.e,DEC);Serial.print("\n");
  Serial.print("Current LED: ");Serial.print(current.a,DEC);Serial.print(" ");Serial.print(current.b,DEC);Serial.print(" ");Serial.print(current.c,DEC);Serial.print(" ");Serial.print(current.d,DEC);Serial.print(" ");Serial.print(current.e,DEC);Serial.print("\n");
  Serial.println("Light: res1: "+String(res));
  res = res - (current.a*_calibData.a/255);
  Serial.println("Light: res2: "+String(res));
  res = res - (current.b*_calibData.b/255);
  Serial.println("Light: res3: "+String(res));
  res = res - (current.c*_calibData.c/255);
  Serial.println("Light: res4: "+String(res));
  res = res - (current.d*_calibData.d/255);
  Serial.println("Light: res5: "+String(res));
  res = res - (current.e*_calibData.e/255);
  Serial.println("Light: res4: "+String(res));*/
 /* return res;
}*/

