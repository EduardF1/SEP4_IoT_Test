#pragma once

#include <stdint.h>

//	Pointer variable to a TEMP_HUM ADT
typedef struct TEMP_HUM* TEMP_HUM_t;

//	Function to initialize the driver
void temp_hum_initalizeDriver();

//	Function to create the driver
TEMP_HUM_t temp_hum_createSensor();

//	Function to return the last measured humidity
uint16_t temp_hum_getLatestHumidity(TEMP_HUM_t self);

//	Function to return the last measured temperature
uint16_t temp_hum_getLatestTemperature(TEMP_HUM_t self);
