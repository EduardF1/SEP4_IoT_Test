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
	2) Add "drivers" to Include Directories in the project

*/



/// <summary>
/// PIR SENSOR TEST SUITE
/// </summary>


//	Fake function to create the PIR Sensor
FAKE_VALUE_FUNC(hcsr501_p, hcsr501_create, volatile uint8_t*, uint8_t);

FAKE_VALUE_FUNC(bool, hcsr501_isDetecting, hcsr501_p);

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

//	Fake function to wakeup the Temp_Hum Sensor
FAKE_VALUE_FUNC(hih8120_driverReturnCode_t, hih8120_wakeup);

//	Fake function to make the Temp_Hum Sensor execute a measurement
FAKE_VALUE_FUNC(hih8120_driverReturnCode_t, hih8120_measure);

//	Fake function to get the Humidity from the Temp_Hum Sensor
FAKE_VALUE_FUNC(uint16_t, hih8120_getHumidityPercent_x10);

//	Fake function to get the Temperature from the Temp_Hum Sensor
FAKE_VALUE_FUNC(int16_t, hih8120_getTemperature_x10);


class Temp_Hum_Test : public ::testing::Test
{
protected:
	void SetUp() override
	{
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
	void SetUp() override {
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
	ASSERT_EQ(1, hih8120_create_fake.call_count);
	ASSERT_TRUE(0 == hih8120_create_fake.return_val);
}

TEST_F(Temp_Hum_Test, Test_Temp_Hum_Create_driver_and_get_temperature_humidity) {
	//	Arrange
	hih8120_create();

	//	Act
	int16_t lastTemperature = temp_hum_getLatestTemperature();
	uint16_t lastHumidity = temp_hum_getLatestHumidity();

	//	Assert
	EXPECT_TRUE(1 == hih8120_create_fake.call_count);
	ASSERT_TRUE(0 == temp_hum_wake_up());
	ASSERT_TRUE(0 == temp_hum_measure());
	ASSERT_FALSE(lastTemperature == temp_hum_getLatestHumidity());
	ASSERT_FALSE(lastHumidity == temp_hum_getLatestTemperature());
}


TEST_F(CO2_Test, Test_CO2_create_and_get_CO2_value) {
	//	Arrange
	int co2ppm;
	//	Act
	co2ppm = co2_getLastCO2ppm();
	//	Assert
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

	uint16_t value = co2_getLastCO2ppm();
	co2_getLatestMeasurement();

	//	Assert
	ASSERT_TRUE(mh_z19_getCo2Ppm_fake.call_count == 1);
	EXPECT_TRUE(0 == mh_z19_getCo2Ppm_fake.return_val);
	ASSERT_TRUE(1500 == co2_getLastCO2ppm());
	ASSERT_FALSE(value == co2_getLastCO2ppm());
}


TEST_F(PIR_Test, Test_PIR_sensor_is_created) {
	//	Arrange
	//	Act
	pir_createSensor();
	hcsr501_p instance = get_pir_instance();

	//	Assert
	EXPECT_TRUE(hcsr501_create_fake.call_count == 1);
	ASSERT_TRUE(instance == get_pir_instance());
}

TEST_F(PIR_Test, Test_PIR_sensor_is_detecting) {
	//	Arrange
	//	Act
	pir_createSensor();
	hcsr501_p instance = get_pir_instance();

	//	Assert
	//EXPECT_FALSE(hcsr501_isDetecting_fake.return_val);
	ASSERT_FALSE(hcsr501_isDetecting(instance));
	//ASSERT_FALSE(isDetecting(instance));
	ASSERT_TRUE(0 == pir_sensor_getPeopleCount());
}