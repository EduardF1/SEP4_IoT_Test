#include "pir_sensor.h"
#include "drivers/hcSr501.h"


//	Private constant pointer to the memory address of PORTE
static const uint8_t* PORTE = 0x0E;

//	Private constant integer to mock a pin (5)
static const uint8_t PE5 = 5;

//	Private pointer variable to the hcsr501_p driver instance, set to NULL
static hcsr501_p hcsr501_instance = NULL;

//	Function to initialize the driver instance and create the driver
void pir_createSensor() {
	hcsr501_instance = hcsr501_create(&PORTE, PE5);
}

