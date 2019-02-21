#include "Wire.h"
#include <wiringPi.h>

//-----------NXT Ultrasonic Sensor----------//
// * may need to chage i2c frequency to 9600 kHZ

class Ultrasonic {
	private:
		enum commands{
			version         = 0x00,
			productId       = 0x08,
			sensorType      = 0x10,
			measurementUnit = 0x14,
			distance        = 0x42,
		};

		uint8_t slaveAddress;
		int sclPin2;
	public:
		Ultrasonic(int pinNum = 7);
		bool begin(uint8_t addr = 0x02);// 7 bit or 8 bit address??????
		int getDistance();
		int *readRegister(uint8_t registerAddr, uint8_t length);
		void clockPulse();
		char *getVersion();
		char *getProductId();
		char *getSensorType();
		char *getMeasurementUnit();
};