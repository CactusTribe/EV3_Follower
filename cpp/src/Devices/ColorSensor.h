#ifndef COLORSENSOR_H
#define COLORSENSOR_H

#include <unistd.h>
#include <vector>
#include "../ev3dev.h"

#include "../Color.h"
#include "../ColorRGB.h"
#include "../ColorEntry.h"


class ColorSensor {

public:
	ColorSensor();
	virtual ~ColorSensor();

	ColorRGB getColorRGB();
	void calibration();
	void sampling(int samples, ColorRGB& min, ColorRGB& max);

private:
	ev3dev::color_sensor* _sensor;
	std::vector<ColorEntry*> _dico_colors;

};

#endif