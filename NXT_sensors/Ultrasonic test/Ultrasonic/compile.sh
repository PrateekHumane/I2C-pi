gcc -c -fPIC Wire.cpp -o Wire.o
ar rcs libWire.a Wire.o
gcc -c Ultrasonic.cpp -o Ultrasonic.o
g++ Ultrasonic.o -Wl,--whole-archive libWire.a -Wl,--no-whole-archive -shared -o libUltrasonic.so
gcc -L/home/pi/Documents/I2C/NXT_sensors/Ultrasonic -Wl,-rpath=/home/pi/Documents/I2C/NXT_sensors/Ultrasonic -Wall -o test example.cpp -lUltrasonic -lwiringPi
