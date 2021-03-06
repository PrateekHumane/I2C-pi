#include "Ultrasonic.h"

Ultrasonic::Ultrasonic(int pinNum = 7)
{
	sclPin2 = pinNum;	
}

bool Ultrasonic::begin(uint8_t addr = 0x02)
{
	slaveAddress = addr >> 1; // use the 7 bit address instead
	if(!Wire.begin() || wiringPiSetupGpio() == -1) // start the wire and wiringPi libraries
		return false;
	pinMode(sclPin2,OUTPUT); // set the clock pin HIGH to start any commands - I do not understand why this is necessary
	digitalWrite(sclPin2, HIGH);

	return true;
}

int * Ultrasonic::readRegister(uint8_t registerAddr, uint8_t length)
{
	delayMicroseconds(30);

	//-- tell the slave which register to grab data from---//
	Wire.beginTransmission(slaveAddress);
	Wire.write(registerAddr);
	Wire.endTransmission();

	clockPulse();

	Wire.requestFrom(sensorAddress, length);
	int * buffer = new int[length];
	while(Wire.available())
	{
		buffer[i] = Wire.read();
	}

	return buffer;
}

void UltrasonicSensor::clockPulse()  
{
    delayMicroseconds(60);
    pinMode(clockPin, OUTPUT);
    digitalWrite(clockPin, LOW); 
    delayMicroseconds(34);
    pinMode(clockPin, INPUT);
    digitalWrite(clockPin, HIGH); 
    delayMicroseconds(60);    
}

int Ultrasonic::getDistance()
{
	int *distance = readRegister(commands::distance, 1);
	return distance[0];
}

char *Ultrasonic::getVersion()
{
	char *version = readRegister(commands::version, 4);
	return version; 
}


char *Ultrasonic::getProductId()
{
	char *productId = readRegister(commands::productId, 4);
	return productId; 
}

char *Ultrasonic::getSensorId()
{
	char *sensorId = readRegister(commands::sensorId, 4);
	return sensorId; 
}

char *Ultrasonic::measurementUnit()
{
	char *measurementUnit = readRegister(commands::measurementUnit, 6);
	return measurementUnit; 
}