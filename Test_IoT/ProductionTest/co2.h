#pragma once

#include <stdint.h>

//	Pointer to the CO2 ADT
typedef struct CO2* CO2_t;

//	Function to the create the CO2 ADT
CO2_t co2_createSensor();

//	Function to return the CO2 value from the created CO2 ADT
uint16_t co2_getLastCO2ppm(CO2_t self);

//	Function to set the CO2 value in the CO2 ADT
void co2_getLatestMeasurement(CO2_t self);

//	Function to initialize a measurement of the driver - MhZ19
void co2_doMeasurement();