#include "LEDoutput.h"
#include "pins.h"
#include "Settings.h"
#include "Converter.h"
#include "UDP.h"

//Integer divided by zero after Output: addressable: 0  0  0  0  0  500 !!
NeoPixelBus<NeoGrbFeature, Neo800KbpsMethod>* LEDoutput::_addressableStrip = NULL;

TaskHandle_t LEDoutput::_currentTask;
ColorMessage LEDoutput::_addr_msg;
CHOUT LEDoutput::_classic_chout;
CHOUT LEDoutput::_stored_chout = {0,0,0,0,0,0};
bool LEDoutput::busy = false;

void LEDoutput::begin()
{
  if (STRIP_TYPE <= 5)
  {
    ledcAttachPin(CH1_PIN, 1);
    ledcSetup(0, FREQUENCY, RESOLUTION);
    ledcAttachPin(CH2_PIN, 2);
    ledcSetup(1, FREQUENCY, RESOLUTION);
    ledcAttachPin(CH3_PIN, 3);
    ledcSetup(2, FREQUENCY, RESOLUTION);
    ledcAttachPin(CH4_PIN, 4);
    ledcSetup(3, FREQUENCY, RESOLUTION);
    ledcAttachPin(CH5_PIN, 5);
    ledcSetup(4, FREQUENCY, RESOLUTION);
  }
  else if (STRIP_TYPE == 14)
  {
    _addressableStrip = new NeoPixelBus<NeoGrbFeature, Neo800KbpsMethod>(ADDRESSABLE_LED_NUM, ADDRESSABLE_PIN);
    _addressableStrip->Begin();
    _addressableStrip->Show();
  }
  else
  {
    Serial.println("WARNING: unknown strip type <<<");
  }
}

void LEDoutput::output(ColorMessage msg)
{
  Serial.println("Output: outputing: " + String(msg.r) + "  " + String(msg.g) + "  " + String(msg.b) + "  " + String(msg.w) + "  " + String(msg.ww));
  int stripType = STRIP_TYPE;
  switch (stripType)
  {
    case 0:
      break;
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
      _classic_chout = Converter::mapChannels(msg);
      _classic_chout.t = msg.t;
      xTaskCreatePinnedToCore(applyCHOUT, "LEDout:apply", 5000, &_classic_chout, 19, &_currentTask, 0);
      break;
    case 14:
      _addr_msg = msg;
      xTaskCreatePinnedToCore(applyAddressable, "LEDout:applyAddr", 5000, &_addr_msg, 19, &_currentTask, 0);
      break;
    default:
      Serial.println("LEDoutput: unknown strip type: " + String(stripType));
      break;
  }
}

void LEDoutput::output(byte data[],uint16_t length)
{
  int stripType = STRIP_TYPE;
  switch (stripType)
  {
    case 0:
      break;
    case 14:
      for(int i = 0; i < length; i+=4) {
          _addressableStrip->SetPixelColor(data[i], RgbColor((uint8_t)data[i+1],(uint8_t)data[i+2],(uint8_t)data[i+2]));
      } 
      _addressableStrip->Show();
      break;
    default:
      Serial.println("LEDoutput: strip type " + String(stripType) + "not applicable");
      break;
  }
}



void LEDoutput::applyAddressable(void*data)
{
  busy = true;
  long mic1, mic2;
  ColorMessage msg = *(ColorMessage *) data;
  Serial.println("Output: addressable: " + String(msg.r) + "  " + String(msg.g) + "  " + String(msg.b) + "  " + String(msg.w) + "  " + String(msg.ww) + "  " + String(msg.t));
  RgbColor color(msg.r, msg.g, msg.b);
  int pixelCount = ADDRESSABLE_LED_NUM;
  mic1 = micros();
  switch (msg.t)
  {
    case 0:
      for (int i = 0; i < pixelCount; i++)
      {
        _addressableStrip->SetPixelColor(i, color);
      }
      _addressableStrip->Show();
      break;
    default:
      int delayms = msg.t / pixelCount+1;
      delay(delayms);
      for (int i = 0; i < pixelCount; i++)
      {
        _addressableStrip->SetPixelColor(i, color);
        _addressableStrip->Show();
        delay(delayms);
      }
      break;
  }
  mic2 = micros();
  busy = false;
  vTaskDelete(NULL);
}

void LEDoutput::applyCHOUT(void*data)
{
  busy = true;
  CHOUT chout = *(CHOUT *) data;
  applyCHOUT(chout);
  vTaskDelete(NULL);
}

void LEDoutput::applyCHOUT(CHOUT chout)
{
  busy = true;
  if(chout.t != 0)applyCHOUToverTime(_stored_chout, chout);
  ledcWrite(1, chout.a);
  ledcWrite(2, chout.b);
  ledcWrite(3, chout.c);
  ledcWrite(4, chout.d);
  ledcWrite(5, chout.e);
  _stored_chout = chout;
  busy = false;
}



void LEDoutput::applyCHOUToverTime(CHOUT from, CHOUT to)
{
  float ticks = to.t/16.0;
  float diff_a = (to.a-from.a)/ticks;
  float diff_b = (to.b-from.b)/ticks;
  float diff_c = (to.c-from.c)/ticks;
  float diff_d = (to.d-from.d)/ticks;
  float diff_e = (to.e-from.e)/ticks;
  for (int i = 1; i <= ticks; ++i)
  {
    ledcWrite(1, from.a+diff_a*i);
    ledcWrite(2, from.b+diff_b*i);
    ledcWrite(3, from.c+diff_c*i);
    ledcWrite(4, from.d+diff_d*i);
    ledcWrite(5, from.e+diff_e*i);
    delay(16);
  }
}

CHOUT LEDoutput::getCurrentCHOUT()
{
  return _stored_chout;
}