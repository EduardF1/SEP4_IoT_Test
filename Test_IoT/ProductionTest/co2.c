#include "co2.h"

static uint16_t lastCO2ppm;
static mh_z19_returnCode_t rc;


//	Return the CO2 value
uint16_t co2_getLastCO2ppm() {

	return lastCO2ppm;
}

//	Initialize a driver measurement
void co2_doMeasurement() {

	rc = mh_z19_takeMeassuring();

	if (rc != MHZ19_OK) {
		//	Something went wrong
	}
}

//	Set the CO2 value
mh_z19_returnCode_t co2_getLatestMeasurement() {

	rc = mh_z19_getCo2Ppm(&lastCO2ppm);
	lastCO2ppm = 1500;
	return rc;
}