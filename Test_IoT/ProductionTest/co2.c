#include "co2.h"
#include "drivers/sen14262.h"
#include "drivers/mh_z19.h"
#include <stdio.h>
#include <stdlib.h>


//	CO2 ADT
typedef struct CO2 {
	uint16_t lastCO2ppm;
}CO2;


//	Create the ADT
CO2_t co2_createSensor() {

	//	Give it memory
	CO2_t self = malloc(sizeof(CO2));

	//	Check if there was enough memory for the ADT to be created
	if (self == NULL) {
		return NULL;
	}

	//	Set CO2 to 0
	self->lastCO2ppm = 0;

	//	Return the pointer
	return self;
}

//	Return the CO2 value
uint16_t co2_getLastCO2ppm(CO2_t self) {

	return self->lastCO2ppm;
}

//	Initialize a driver measurement
void co2_doMeasurement() {
	int rc = mh_z19_takeMeassuring();
	if (rc != MHZ19_OK) {
		//	Something went wrong
	}
}

//	Set the CO2 value in the CO2 ADT
void co2_getLatestMeasurement(CO2_t self) {
	mh_z19_getCo2Ppm(&self->lastCO2ppm);
	printf("CO2 is: %d\n", co2_getLastCO2ppm(self));
}