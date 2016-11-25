#include <string>
#include <sstream>
#include "ColorSensor.h"

using namespace ev3dev;

ColorSensor::ColorSensor()
{
	_sensor = new color_sensor(INPUT_1);
	_sensor->set_mode("RGB-RAW");
}

ColorSensor::~ColorSensor()
{
	delete _sensor;
}

void ColorSensor::calibration(int samples)
{

}


ColorRGB ColorSensor::getColor()
{
	return ColorRGB(_sensor->red(), _sensor->green(), _sensor->blue());
}