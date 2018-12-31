#include "Safety.h"

#ifdef __cplusplus
extern "C" {
#endif
uint8_t temprature_sens_read();
#ifdef __cplusplus
}
#endif
uint8_t temprature_sens_read();

TaskHandle_t Safety::_currentTask;

void Safety::begin()
{
	xTaskCreatePinnedToCore(code_loop,"safety",500,NULL,18,&_currentTask,0);
}

void Safety::code_loop(void*) 
{
	while(true)
	{
		if((temprature_sens_read() - 32 ) / 1.8 > 90)Serial.println("Temperature WARNING !");
  	delay(5000);
	}
	vTaskDelete(NULL);
}
