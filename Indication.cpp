#include "Indication.h"
#include "pins.h"

TaskHandle_t Indication::_currentTask;

void Indication::stop()
{
  vTaskDelete(_currentTask);
  digitalWrite(LD1_PIN,LOW);
}

void Indication::blink(uint16_t ms)
{
  pinMode(LD1_PIN,OUTPUT);
  xTaskCreatePinnedToCore(code_blink,"indic:connect",600,&ms,18,&_currentTask,0);
  delay(5);
}

void Indication::code_blink(void * data)
{
  uint16_t ms = *(uint16_t *) data;
  while(true)
  {
    digitalWrite(LD1_PIN,HIGH);
    delay(ms);
    digitalWrite(LD1_PIN,LOW);
    delay(ms);
  }
}


