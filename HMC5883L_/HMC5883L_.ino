/*
* HMC5883L_.ino
*
* Created: 9/2/2018 2:42:34 PM
* Author: Mateusz Patyk
* Email: matpatyk@gmail.com
*/

#include <Wire.h>

#include "Headers/Status.h"
#include "Headers/I2C_Sensor.h"
#include "Headers/HMC5883L.h"

void setup()
{
	Wire.begin();
	
	Status.begin();
	Status.checkStatus(Magnetometer);
}

void loop()
{
	if(Magnetometer.getDataReadyFlag())
	{
		Magnetometer.read();
		sFloatAxes scaled = Magnetometer.getScaled();
		Status.printMessage("X = " + String(scaled.X) + "\tY = " + String(scaled.Y) + "\tZ = " + String(scaled.Z));
	}
}