#include "Ultrasonic.h"

int main()
{
//	Ultrasonic sensor(0);
//	printf("%d",sensor.begin());
//	while(true)
//		printf("%d",sensor.getDistance());
	if(!Wire.begin() || wiringPiSetupGpio() == -1)
		printf("wire didn't begin\n");	
	delayMicroseconds(30);
	
	while(true){	
	if(Wire.beginTransmission(0x0a))
		printf("began transmission\n");
	printf("wrote: %d\n",Wire.writes(0x42));
	Wire.endTransmission();
	int back = Wire.requestFrom(0x0a,8);
	printf("got back bytes: %d\n", back);
	uint8_t buffer[2];
	for(int i =0; i<8; i++){
	buffer[i]=Wire.reads();
	printf("data1:%d\n",(int)(buffer[i])); 
	}
	delayMicroseconds(1000000);
	}
}
