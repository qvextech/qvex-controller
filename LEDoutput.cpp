#include "LEDoutput.h"
#include "pins.h"
#include "Settings.h"
#include "Converter.h"
#include "UDP.h"

//Integer divided by zero after Output: addressable: 0  0  0  0  0  500 !!
NeoPixelBus<NeoGrbFeature, Neo800KbpsMethod>* LEDoutput::_addressableStrip = NULL;

TaskHandle_t LEDoutput::_currentTask;
ColorMessage LEDoutput::_msg;
CHOUT LEDoutput::_stored_output = {0,0,0,0,0,0};
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

void LEDoutput::output(ColorMessage msg, bool runInTask)
{
  _msg = msg;
  if(runInTask){
    if(busy)vTaskDelete(_currentTask);
    xTaskCreatePinnedToCore(outputTask, "LEDout:output", 5000, &_msg, 19, &_currentTask, 0);
  }
  else {
    if(busy)vTaskDelete(_currentTask);
    busy = true;
    outputCode(msg);
    busy = false;
  }
}

void LEDoutput::outputTask(void*data)
{
  busy = true;
  ColorMessage msg = *(ColorMessage *) data;
  outputCode(msg);
  busy = false;
  vTaskDelete(NULL);
}

void LEDoutput::outputCode(ColorMessage msg)
{
  Serial.println("Output: outputing: " + String(msg.r) + "  " + String(msg.g) + "  " + String(msg.b) + "  " + String(msg.w) + "  " + String(msg.ww) + " t: " + String(msg.t));
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
      applyCHOUT(Converter::mapChannels(msg));
      break;
    case 14:
      applyAddressable(msg);
      break;
    default:
      Serial.println("LEDoutput: unknown strip type: " + String(stripType));
      break;
  };
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



void LEDoutput::applyAddressable(ColorMessage msg)
{
  Serial.println("Output: addressable: " + String(msg.r) + "  " + String(msg.g) + "  " + String(msg.b) + "  " + String(msg.w) + "  " + String(msg.ww) + "  " + String(msg.t));
  RgbColor color(msg.r, msg.g, msg.b);
  int pixelCount = ADDRESSABLE_LED_NUM;
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
  _stored_output.a = msg.r; _stored_output.b = msg.g; _stored_output.c = msg.b; _stored_output.d = msg.w; _stored_output.e = msg.ww;
}

void LEDoutput::applyCHOUT(CHOUT chout)
{
  if(chout.t != 0)applyCHOUToverTime(_stored_output, chout);
  ledcWrite(1, chout.a);
  ledcWrite(2, chout.b);
  ledcWrite(3, chout.c);
  ledcWrite(4, chout.d);
  ledcWrite(5, chout.e);
  _stored_output = chout;
}



void LEDoutput::applyCHOUToverTime(CHOUT from, CHOUT to)
{
  CHOUT chout;
  chout.t = 0;
  float ticks = to.t/16.0;
  float diff_a = (to.a-from.a)/ticks;
  float diff_b = (to.b-from.b)/ticks;
  float diff_c = (to.c-from.c)/ticks;
  float diff_d = (to.d-from.d)/ticks;
  float diff_e = (to.e-from.e)/ticks;
  for (int i = 1; i <= ticks; ++i)
  {
    chout.a = from.a+diff_a*i;
    chout.b = from.b+diff_b*i;
    chout.c = from.c+diff_c*i;
    chout.d = from.d+diff_d*i;
    chout.e = from.e+diff_e*i;
    applyCHOUT(chout);
    delay(16);
  }
}

CHOUT LEDoutput::getCurrentOutput()
{
  return _stored_output;
}