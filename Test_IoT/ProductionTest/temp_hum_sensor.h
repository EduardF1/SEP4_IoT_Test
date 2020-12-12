#pragma once

#include "drivers/serial.h"
#include "drivers/hih8120.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>


//	Function to initialize the driver
void temp_hum_initalizeDriver();

//	Function to wake up the driver
hih8120_driverReturnCode_t temp_hum_wake_up();

//	Function to make the driver execute a measurement
hih8120_driverReturnCode_t temp_hum_measure();

//	Function to return the last measured humidity
uint16_t temp_hum_getLatestHumidity();

//	Function to return the last measured temperature
int16_t temp_hum_getLatestTemperature();
