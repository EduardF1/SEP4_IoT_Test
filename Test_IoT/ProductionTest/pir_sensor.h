#pragma once

#include <stdint.h>
#include <stdbool.h>
#include "drivers/hcSr501.h"

//	Function to create the driver
void pir_createSensor();

bool isDetecting(hcsr501_p hcsr501_instance);

//	Function to return the number of people (detections of the sensor)
uint16_t pir_sensor_getPeopleCount();

//	Function to return the driver instance
hcsr501_p get_pir_instance();