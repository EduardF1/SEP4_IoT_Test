#include "drivers/serial.h"
#include "drivers/hih8120.h"

#include "temp_hum_sensor.h"

#include <stdio.h>
#include <stdlib.h>


//	Create the ADT
typedef struct TEMP_HUM {

	uint16_t lastTemperature;
	uint16_t lastHumidity;

}TEMP_HUM;


//	Function to initialize the driver (declaration)
void temp_hum_initalizeDriver() {
	hih8120_driverReturnCode_t rc = hih8120_create();

	if (HIH8120_OK != hih8120_create()) {
		//	Driver not created, something went wrong
	}
	else {
		//	Driver created
	}
}

//	Function to create the driver (declaration)
TEMP_HUM_t temp_hum_createSensor() {

	//	Initialize the driver
	temp_hum_initalizeDriver();

	//	Give the ADT memory
	TEMP_HUM_t self = malloc(sizeof(TEMP_HUM));

	//	Verify that memory was given
	if (self == NULL) {
		return NULL;
	}

	self->lastHumidity = 150;
	self->lastTemperature = 25;

	return self;
}

//	Get the latest humidity
uint16_t temp_hum_getLatestHumidity(TEMP_HUM_t self) {
	return self->lastHumidity;
}

//	Get the latest temperature
uint16_t temp_hum_getLatestTemperature(TEMP_HUM_t self) {
	return self->lastTemperature;
}
