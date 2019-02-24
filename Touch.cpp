#include "Touch.h"
#include "Controller.h"
#include "pins.h"
#include "Settings.h"

uint8_t Touch::_ref;

void Touch::begin() {
  calibrate();
  xTaskCreatePinnedToCore(loop, "Touch:loop", 10000, NULL, 20, NULL, 0);
  Serial.println("Touch: ok");
}

void Touch::loop(void*data)
{
  while (1)
  {
    if (touchRead(TOUCH_PIN) < _ref) handleTouch();
    delay(30);
  }
  vTaskDelete(NULL);
}


void Touch::handleTouch()
{
  delay(10);
  if (touchRead(TOUCH_PIN) < _ref)
  {
    long mils = millis();
    while (mils + 400 > millis())
    {
      if (touchRead(TOUCH_PIN) > _ref) //Touch shorter than 400ms -> vyp/zap
      {
        Controller::state();
        delay(500);
        return;
      }
      delay(50);
    }
    int n = Controller::getIntensity();
    int dir = 1;
    while (touchRead(TOUCH_PIN) < _ref) //If touch is longer than 400ms -> loop through intensity range while touch still active
    {
      n += 6 * dir;
      if (n > 1000){dir = -1; n=1000;}
      if (n < 0){dir = 1; n=0;}
      Controller::previewIntensity(n);
      delay(10);
    }
    Controller::applyIntensity(n);
  }
}

void Touch::calibrate()
{
  uint8_t val = 255;
  uint8_t touch;
  touchRead(TOUCH_PIN);
  touchRead(TOUCH_PIN);
  delay(2);
  for(int i = 0; i < TOUCH_CAL_SAMPLES; i++)
  {
    touch = touchRead(TOUCH_PIN);
    if(touch < val) val = touch;
    delayMicroseconds(100);
  }
  _ref = val*0.97;
  Serial.println("Touch: calibrate: result: "+String(_ref));
}

