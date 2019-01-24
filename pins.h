#include "Settings.h"

#ifndef pins
#define pins

#ifdef PCB_DEV_0_1
	#error No pins defined for PCB version 0.1
#elif defined PCB_DEV_1_1
	#define CH1_PIN 4
	#define CH2_PIN 16
	#define CH3_PIN 17
	#define CH4_PIN 5
	#define CH5_PIN 18
	#define LD1_PIN 33
	#define LD2_PIN 21
	#define LD3_PIN 23
	#define LIGHT_PIN 7
	#define TOUCH_PIN 14
	#define ADDRESSABLE_PIN 32
	#define CURRENT_PIN 36
#elif defined PCB_DEV_1_2
	#define CH1_PIN 18
	#define CH2_PIN 17
	#define CH3_PIN 16
	#define CH4_PIN 4
	#define CH5_PIN 12
	#define TOUCH_PIN 14
	#define ADDRESSABLE_PIN 32
	#define ONBOARD_ADDRESSABLE_PIN 25
	#define THERMISTOR_PIN 33
	#define LIGHT_PIN ADC1_GPIO39_CHANNEL
	#define VIN_PIN ADC1_GPIO34_CHANNEL
	#define CURRENT_PIN ADC1_GPIO36_CHANNEL
#endif

#endif
