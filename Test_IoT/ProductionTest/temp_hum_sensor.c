
#include "temp_hum_sensor.h"

static hih8120_driverReturnCode_t rc;
static int16_t lastTemperature;
static uint16_t lastHumidity;

//	Function to initialize the driver (declaration)
void temp_hum_initalizeDriver() {

	rc = hih8120_create();

	if (HIH8120_OK != rc) {
		//	Driver not created, something went wrong
	}
	else {
		//	Driver created
	}
}

//	Function to wake up the driver (declaration)
hih8120_driverReturnCode_t temp_hum_wake_up()
{
	rc = hih8120_wakeup();
	return rc;
}

//	Function to make the driver execute a measurement (declaration)
hih8120_driverReturnCode_t temp_hum_measure()
{
	rc = hih8120_measure();

	lastHumidity = hih8120_getHumidityPercent_x10();
	lastHumidity = 456;
	lastTemperature = hih8120_getTemperature_x10();
	lastTemperature = 550;

	return rc;
}

//	Get the latest humidity
uint16_t temp_hum_getLatestHumidity() {
	return lastHumidity;
}

//	Get the latest temperature
int16_t temp_hum_getLatestTemperature() {
	return lastTemperature;
}
