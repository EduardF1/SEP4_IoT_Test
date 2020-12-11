#include "gtest/gtest.h"
#include "../../fff-master/fff.h"	//	add FFF interface dependecy
DEFINE_FFF_GLOBALS	//	Initialize the framework

//	include external C-code files
extern "C"
{
#include "drivers/hih8120.h"
#include "drivers/mh_z19.h"
#include "drivers/serial.h"
#include "drivers/hcSr501.h"

#include "temp_hum_sensor.h"
#include "co2.h"
#include "pir_sensor.h"

#include <stdbool.h>
}

/*
	SETUP:

	1) Disable the precompiled headers
	2) Add "drivers" and "fff-master" Include Directories in the project
	3) Add "drivers" in the Library Directories of the project

*/



/// <summary>
/// PIR SENSOR TEST SUITE
/// </summary>


//	Fake function to create the PIR Sensor
FAKE_VALUE_FUNC(hcsr501_p, hcsr501_create, volatile uint8_t*, uint8_t);

class PIR_Test : public ::testing::Test
{
protected:
	void SetUp() override
	{
		FFF_RESET_HISTORY();
	}

	void TearDown() override
	{

	}
};

/// <summary>
/// Temp_Hum SENSOR TEST SUITE
/// </summary>

//	Fake function to create the Temp_Hum Sensor
FAKE_VALUE_FUNC(hih8120_driverReturnCode_t, hih8120_create);


class Temp_Hum_Test : public ::testing::Test
{
protected:
	TEMP_HUM_t TEMP_HUM_Sensor;
	void SetUp() override
	{
		TEMP_HUM_Sensor = temp_hum_createSensor();
		RESET_FAKE(hih8120_create);
		FFF_RESET_HISTORY();
	}

	void TearDown() override
	{

	}
};

//	Fake function to take a measuring from the CO2 Sensor
FAKE_VALUE_FUNC(mh_z19_returnCode_t, mh_z19_takeMeassuring);

//	Fake function to get the CO2 value from the CO2 Sensor
FAKE_VALUE_FUNC(mh_z19_returnCode_t, mh_z19_getCo2Ppm, uint16_t*);


/// <summary>
/// CO2 SENSOR TEST SUITE
/// </summary>

class CO2_Test : public ::testing::Test
{
protected:
	CO2_t CO2_Sensor;
	void SetUp() override {
		CO2_Sensor = co2_createSensor();
		RESET_FAKE(mh_z19_takeMeassuring);
		RESET_FAKE(mh_z19_getCo2Ppm);
		FFF_RESET_HISTORY();
	}
	void TearDown() override {

	}

};


TEST_F(Temp_Hum_Test, Test_Temp_Hum_initialize_driver_is_called) {
	//	Arrange
	//	Act
	temp_hum_initalizeDriver();

	//	Assert
	ASSERT_EQ(2, hih8120_create_fake.call_count);
}

TEST_F(Temp_Hum_Test, Test_Temp_Hum_Create_driver_and_get_temperature_humidity) {
	//	Arrange
	hih8120_create();
	int temp_latestHumidity = 0;
	int temp_latestTemperature = 0;

	//	Act
	temp_latestHumidity = temp_hum_getLatestHumidity(TEMP_HUM_Sensor);
	temp_latestTemperature = temp_hum_getLatestTemperature(TEMP_HUM_Sensor);

	//	Assert
	EXPECT_TRUE(1, hih8120_create_fake.call_count);
	ASSERT_TRUE(NULL != TEMP_HUM_Sensor);
	ASSERT_TRUE(temp_latestHumidity == 150);
	EXPECT_TRUE(temp_latestTemperature == 25);
}


TEST_F(CO2_Test, Test_CO2_create_and_get_CO2_value) {
	//	Arrange
	int co2ppm;
	//	Act
	co2ppm = co2_getLastCO2ppm(CO2_Sensor);
	//	Assert
	EXPECT_TRUE(NULL != CO2_Sensor);
	EXPECT_EQ(0, co2ppm);
}

TEST_F(CO2_Test, Test_CO2_measure_is_called_10_times) {
	//	Arrange
	//	Act
	for (int i = 0; i < 10; i++)
	{
		co2_doMeasurement();
	}

	//	Assert
	ASSERT_EQ(10, mh_z19_takeMeassuring_fake.call_count);
}

TEST_F(CO2_Test, Test_CO2_set_data_is_called) {
	//	Arrange
	//	Act
	co2_getLatestMeasurement(CO2_Sensor);

	//	Assert
	ASSERT_TRUE(mh_z19_getCo2Ppm_fake.call_count == 1);
}


TEST_F(PIR_Test, Test_PIR_sensor_is_created) {
	//	Arrange
	//	Act
	pir_createSensor();

	//	Assert
	EXPECT_TRUE(hcsr501_create_fake.call_count == 1);
}