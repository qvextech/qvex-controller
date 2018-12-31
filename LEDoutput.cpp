#include "LEDoutput.h"
#include "pins.h"
#include "Settings.h"
#include "Converter.h"
#include "UDP.h"

//Integer divided by zero after Output: addressable: 0  0  0  0  0  500 !!

NeoPixelBus<NeoGrbwFeature, Neo800KbpsMethod> LEDoutput::_addressableStrip(ADDRESSABLE_LED_NUM_DIRECT, ADDRESSABLE_PIN);
TaskHandle_t LEDoutput::_currentTask;
ColorMessage LEDoutput::_addr_msg;

void LEDoutput::setup()
{
  if (STRIP_TYPE <= 5)
  {
    ledcSetup(0, FREQUENCY, RESOLUTION);
    ledcAttachPin(CH1_PIN, 0);
    ledcSetup(1, FREQUENCY, RESOLUTION);
    ledcAttachPin(1, CH2_PIN);
    ledcSetup(2, FREQUENCY, RESOLUTION);
    ledcAttachPin(2, CH3_PIN);
    ledcSetup(3, FREQUENCY, RESOLUTION);
    ledcAttachPin(3, CH4_PIN);
    ledcSetup(4, FREQUENCY, RESOLUTION);
    ledcAttachPin(4, CH5_PIN);
  }
  else if (STRIP_TYPE == 11)
  {
    _addressableStrip.Begin();
    RgbColor green(0, 255, 0);
    _addressableStrip.SetPixelColor(0, green);
    _addressableStrip.Show();
  }
  else
  {
    Serial.println("WARNING: unknown strip type <<<");
  }
}

void LEDoutput::output(ColorMessage msg)
{
  //Serial.println("Output: outputing: " + String(msg.r) + "  " + String(msg.g) + "  " + String(msg.b) + "  " + String(msg.w));
  int stripType = STRIP_TYPE;
  switch (stripType)
  {
    case 0:
      break;
    case 11:
      _addr_msg = msg;
      xTaskCreatePinnedToCore(applyAddressable, "LEDout:applyAddr", 4000, &_addr_msg, 19, &_currentTask, 0);
      break;
    default:
      Serial.println("LEDoutput: NA: type: " + String(stripType));
      CHOUT chout = Converter::mapChannels(msg);
      chout.t = msg.t;
      xTaskCreatePinnedToCore(applyCHOUT, "LEDout:apply", 10000, &chout, 19, &_currentTask, 0);
      break;
  }
}

void LEDoutput::applyAddressable(void*data)
{
  long mic1, mic2;
  ColorMessage msg = *(ColorMessage *) data;
  Serial.println("Output: addressable: " + String(msg.r) + "  " + String(msg.g) + "  " + String(msg.b) + "  " + String(msg.w) + "  " + String(msg.ww) + "  " + String(msg.t));
  RgbwColor color(msg.r, msg.g, msg.b, msg.w);
  int pixelCount = ADDRESSABLE_LED_NUM;
  mic1 = micros();
  switch (msg.t)
  {
    case 0:
      for (int i = 0; i < pixelCount; i++)
      {
        _addressableStrip.SetPixelColor(i, color);
      }
      _addressableStrip.Show();
      break;
    default:
      int delayms = msg.t / pixelCount;
      for (int i = 0; i < pixelCount; i++)
      {
        _addressableStrip.SetPixelColor(i, color);
        _addressableStrip.Show();
        delay(delayms);
      }
      break;
  }
  mic2 = micros();
  Serial.println("applyAdresasble: took: " + String(mic2 - UDPsocket::mils));
  vTaskDelete(NULL);
}

void LEDoutput::applyCHOUT(void*data)
{
  CHOUT chout = *(CHOUT *) data;
  ledcWrite(0, chout.b);
  Serial.println("LEDoutput: task done: " + String(chout.b));
  vTaskDelete(NULL);
}
