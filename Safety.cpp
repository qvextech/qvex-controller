#include "Safety.h"
#include "Setting.h"

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
	xTaskCreatePinnedToCore(code_loop,"safety",1000,NULL,18,&_currentTask,0);
}

void Safety::code_loop(void*) 
{
	int tmp;
	while(true)
	{
		tmp = (temprature_sens_read() - 32 ) / 1.8;
		if(tmp >= INNER_TEMP_THRESHOLD)Serial.println("Temperature WARNING!: "+String(tmp));
  		delay(15000);
	}
	vTaskDelete(NULL);
}
