#include "Indication.h"
#include "pins.h"
#include "Settings.h"

TaskHandle_t Indication::_currentTask;
NeoPixelBus<NeoGrbFeature, Neo800KbpsMethod> Indication::_addressableStrip(ONBOARD_LED_NUM, ONBOARD_ADDRESSABLE_PIN);

void Indication::begin()
{
  _addressableStrip.Begin();
  RgbColor green(0, 255, 0);
  _addressableStrip.SetPixelColor(0, green);
  _addressableStrip.Show();
}

void Indication::stop()
{
  vTaskDelete(_currentTask);
  for (int i = 0; i < ONBOARD_LED_NUM; ++i)_addressableStrip.SetPixelColor(i, RgbColor(0,0,0));
  _addressableStrip.Show();
}

void Indication::done()
{

  vTaskDelete(NULL);
}

//Blink
void Indication::blink(uint8_t r,uint8_t g,uint8_t b,uint16_t time,uint8_t count)
{
  ColorMessage msg = {0,r,g,b,0,count,time};
  xTaskCreatePinnedToCore(code_blink,"indic:blink",1200,&msg,18,&_currentTask,0);
  delay(20);
}

void Indication::code_blink(void * data)
{
  ColorMessage msg = *(ColorMessage *) data;
  uint8_t count = 0;
  while(count < msg.ww || msg.ww == 0)
  {
    for (int i = 0; i < ONBOARD_LED_NUM; i++)_addressableStrip.SetPixelColor(i, RgbColor(msg.r,msg.g,msg.b));
    _addressableStrip.Show();  
    delay(msg.t);
    for (int i = 0; i < ONBOARD_LED_NUM; i++)_addressableStrip.SetPixelColor(i, RgbColor(0,0,0));
    _addressableStrip.Show();
    delay(msg.t);
    if(msg.ww != 0)count++;
  }
  vTaskDelete(NULL);
}


//Breath
void Indication::breath(uint8_t r,uint8_t g,uint8_t b,uint16_t time,uint8_t count)
{
  ColorMessage msg = {0,r,g,b,0,count,time};
  xTaskCreatePinnedToCore(code_breath,"indic:breath",1200,&msg,18,&_currentTask,0);
  delay(20);
}

void Indication::code_breath(void * data)
{
  ColorMessage msg = *(ColorMessage *) data;
  uint8_t count = 0;
  while(count < msg.ww || msg.ww == 0)
  {
    for (int a = 0; a < 127; a++) {
      for (int i = 0; i < ONBOARD_LED_NUM; i++)_addressableStrip.SetPixelColor(i, RgbColor(msg.r*a/127,msg.g*a/127,msg.b*a/127));
      _addressableStrip.Show();
      delay(msg.t);
    }
    for (int a = 127; a > 0; a--) {
      for (int i = 0; i < ONBOARD_LED_NUM; i++)_addressableStrip.SetPixelColor(i, RgbColor(msg.r*a/127,msg.g*a/127,msg.b*a/127));
      _addressableStrip.Show();
      delay(msg.t);
    }
    if(msg.ww != 0)count++;
  }
  vTaskDelete(NULL);
}