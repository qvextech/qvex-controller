#include "Consumption.h"
#include "driver/adc.h"

#define DEFAULT_VREF    1100
#define NO_OF_SAMPLES   100



void Consumption::begin()
{
  adc1_config_width(ADC_WIDTH_BIT_12);
  adc1_config_channel_atten(ADC1_CHANNEL_0, ADC_ATTEN_DB_0);
  xTaskCreatePinnedToCore(loop, "Meter", 4000, NULL, 19, NULL, 0);
}

void Consumption::loop(void*)
{
  esp_adc_cal_characteristics_t *adc_chars;
  adc_chars = (esp_adc_cal_characteristics_t *)calloc(1, sizeof(esp_adc_cal_characteristics_t));
  esp_adc_cal_value_t val_type = esp_adc_cal_characterize(ADC_UNIT_1, ADC_ATTEN_DB_0, ADC_WIDTH_BIT_10, DEFAULT_VREF, adc_chars);
  
  while (1)
  {
    uint32_t adc_reading = 0;
    for (int i = 0; i < NO_OF_SAMPLES; i++) {
      adc_reading += analogRead(36);
      delayMicroseconds(10);
    }
    adc_reading /= NO_OF_SAMPLES;
    uint32_t voltage = esp_adc_cal_raw_to_voltage(adc_reading, adc_chars);
    
    Serial.print("Raw: ");
    Serial.print(adc_reading);
    Serial.print(" Voltage: ");
    Serial.print(voltage);
    Serial.print(" Current: ");
    Serial.println(voltage / 36.9 / 31.303, 4);
    delay(5000);
  }
  
  
}

