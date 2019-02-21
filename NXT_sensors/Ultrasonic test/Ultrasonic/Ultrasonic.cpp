#include "Ultrasonic.h"

Ultrasonic::Ultrasonic(int pinNum/* = 7*/)
{
	sclPin2 = pinNum;
}

bool Ultrasonic::begin(uint8_t addr/* = 0x02*/)
{
	slaveAddress = addr >> 1; // use the 7 bit address instead
	if(!Wire.begin() || wiringPiSetup() == -1) // start the wire and wiringPi libraries
		return false;
	pinMode(sclPin2,OUTPUT); // set the clock pin HIGH to start any command - I do not understand why this is necessary
	digitalWrite(sclPin2, HIGH);

	return true;
}

uint8_t * Ultrasonic::readRegister(uint8_t registerAddr, uint8_t length)
{
	delayMicroseconds(30);

	//-- tell the slave which register to grab data from---//
	Wire.beginTransmission(slaveAddress);
	Wire.writes(registerAddr);
	Wire.endTransmission();

	clockPulse();

	Wire.requestFrom(slaveAddress, length);
	uint8_t * buffer = new uint8_t[length];
	for(int i = 0;Wire.available();i++)
	{
		buffer[i] = Wire.reads();
	}

	return buffer;
}

void Ultrasonic::clockPulse()
{
    delayMicroseconds(60);
    pinMode(sclPin2, OUTPUT);
    digitalWrite(sclPin2, LOW);
    delayMicroseconds(34);
    pinMode(sclPin2, INPUT);
    digitalWrite(sclPin2, HIGH);
    delayMicroseconds(60);
}

int Ultrasonic::getDistance()
{
	command = distance;
	int *distance = (int *)readRegister(command, 1);
	return distance[0];
}

char *Ultrasonic::getVersion()
{
	command = version;
	uint8_t *versions = readRegister(version, 4);
	return (char *)versions;
}


char *Ultrasonic::getProductId()
{
	command = productId;
	uint8_t *productIds = readRegister(command, 4);
	return (char *)productIds;
}

char *Ultrasonic::getSensorType()
{
	command = sensorType;
	uint8_t *sensorType = readRegister(command, 4);
	return (char *)sensorType;
}

char *Ultrasonic::getMeasurementUnit()
{
	command = measurementUnit;
	uint8_t *measurementUnit = readRegister(command, 6);
	return (char*)measurementUnit;
}
