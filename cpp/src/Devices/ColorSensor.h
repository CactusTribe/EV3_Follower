#ifndef COLORSENSOR_H
#define COLORSENSOR_H

#include "../ev3dev.h"
#include "../ColorRGB.h"

class ColorSensor {

public:
	ColorSensor();
	virtual ~ColorSensor();

	ColorRGB getColor();
	void calibration(int samples);

private:
	ev3dev::color_sensor* _sensor;

};

#endif