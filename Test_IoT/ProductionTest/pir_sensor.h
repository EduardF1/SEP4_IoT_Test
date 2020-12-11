#pragma once

#include <stdint.h>

//	Function to create the driver
void pir_createSensor();

//	Function to return the number of people (detections of the sensor)
uint16_t pir_sensor_getPeopleCount();