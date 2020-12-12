#include "pir_sensor.h"


//	Private constant pointer to the memory address of PORTE
static const uint8_t* PORTE = 0x0E;

//	Private constant integer to mock a pin (5)
static const uint8_t PE5 = 5;

//	Private pointer variable to the hcsr501_p driver instance, set to NULL
static hcsr501_p hcsr501_instance = NULL;

static uint16_t people;

//	Function to initialize the driver instance and create the driver
void pir_createSensor() {
	hcsr501_instance = hcsr501_create(&PORTE, PE5);
}

hcsr501_p get_pir_instance()
{
	return hcsr501_instance;
}

bool isDetecting(hcsr501_p hcsr501_instance)
{
	if (hcsr501_instance != NULL)                        // If there is an instance of the driver
	{
		if (hcsr501_isDetecting(hcsr501_instance))       // If the driver is detecting movement
		{
			return true;
		}
		else
		{
			people++;                                    // Increment counter
			return false;
		}
	}
}

uint16_t pir_sensor_getPeopleCount()
{
	return people;
}