#include "Consumption.h"
#include "driver/adc.h"
#include "pins.h"
#include "Settings.h"

#define DEFAULT_VREF    1100
#define VIN_ATTEN ADC_ATTEN_DB_6
#define CURRENT_ATTEN ADC_ATTEN_DB_0

esp_adc_cal_characteristics_t *Consumption::adc_chars_vin;
esp_adc_cal_characteristics_t *Consumption::adc_chars_current;

void Consumption::begin()
{
  adc1_config_width(ADC_WIDTH_BIT_12);
  adc1_config_channel_atten(VIN_PIN, VIN_ATTEN);
  adc1_config_channel_atten(CURRENT_PIN, CURRENT_ATTEN);
  adc_chars_vin = (esp_adc_cal_characteristics_t *)calloc(1, sizeof(esp_adc_cal_characteristics_t));
  adc_chars_current = (esp_adc_cal_characteristics_t *)calloc(1, sizeof(esp_adc_cal_characteristics_t));
  esp_adc_cal_characterize(ADC_UNIT_1, VIN_ATTEN, ADC_WIDTH_BIT_12, DEFAULT_VREF, adc_chars_vin);
  esp_adc_cal_characterize(ADC_UNIT_1, CURRENT_ATTEN, ADC_WIDTH_BIT_12, DEFAULT_VREF, adc_chars_current);
  xTaskCreatePinnedToCore(loop, "Meter", 4000, NULL, 19, NULL, 0);
}

void Consumption::loop(void*)
{
  while (1)
  {
    /*uint32_t adc_vin = 0;
    uint32_t adc_current = 0;
    //Multisampling
    for (int i = 0; i < ADC_NO_OF_SAMPLES; i++) {
        adc_vin += adc1_get_raw(VIN_PIN);
        adc_current += adc1_get_raw(CURRENT_PIN);
    }
    adc_vin /= ADC_NO_OF_SAMPLES;
    adc_current /= ADC_NO_OF_SAMPLES;
    uint32_t adc_vin_calced = esp_adc_cal_raw_to_voltage(adc_vin, adc_chars_vin);
    uint32_t adc_current_calced = esp_adc_cal_raw_to_voltage(adc_current, adc_chars_current);
    uint32_t vin = adc_vin_calced*69;
    uint32_t current = adc_current_calced/0.02/33;
    float power = vin/1000.0*current;
    Serial.printf("Raw34: %d     Raw36: %d     V34: %dmV     V36: %dmV     Vin: %dmV     I: %dmA     P: %.2fmW\n", adc_vin, adc_current, adc_vin_calced, adc_current_calced, vin, current, power);*/
    //Serial.printf("V: %dmV     I: %dmA     P: %dmW\n",getVoltage(),getCurrent(),getPower());
    delay(5000);
  }
  vTaskDelete(NULL);  
}

uint16_t Consumption::getVoltage()
{
  uint32_t adc_reading = 0;
  for (int i = 0; i < ADC_NO_OF_SAMPLES; i++) {
      adc_reading += adc1_get_raw(VIN_PIN);
  }
  adc_reading /= ADC_NO_OF_SAMPLES;
  adc_reading = esp_adc_cal_raw_to_voltage(adc_reading, adc_chars_vin)*69;
  return uint16_t(adc_reading);
}

uint16_t Consumption::getCurrent()
{
  uint32_t adc_reading = 0;
  for (int i = 0; i < ADC_NO_OF_SAMPLES; i++) {
      adc_reading += adc1_get_raw(CURRENT_PIN);
  }
  adc_reading /= ADC_NO_OF_SAMPLES;
  adc_reading = esp_adc_cal_raw_to_voltage(adc_reading, adc_chars_current)/0.02/33;
  return uint16_t(adc_reading);
}

uint32_t Consumption::getPower()
{
  return getVoltage()/1000.0*getCurrent();
}