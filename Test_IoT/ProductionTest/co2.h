#pragma once

#include <stdint.h>
#include "drivers/mh_z19.h"
#include <stdio.h>
#include <stdlib.h>


//	Function to return the CO2 value from the created CO2 ADT
uint16_t co2_getLastCO2ppm();

//	Function to set the CO2 value in the CO2 ADT
mh_z19_returnCode_t co2_getLatestMeasurement();

//	Function to initialize a measurement of the driver - MhZ19
void co2_doMeasurement();