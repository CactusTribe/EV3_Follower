#include <string>
#include <sstream>
#include "ColorSensor.h"

using namespace ev3dev;

ColorSensor::ColorSensor()
{
	_sensor = new color_sensor(INPUT_1);
	_sensor->set_mode("RGB-RAW");

	_dico_colors.push_back(new ColorEntry(Color::RED));
	_dico_colors.push_back(new ColorEntry(Color::GREEN));
	_dico_colors.push_back(new ColorEntry(Color::BLUE));
	_dico_colors.push_back(new ColorEntry(Color::YELLOW));
	_dico_colors.push_back(new ColorEntry(Color::WHITE));
	_dico_colors.push_back(new ColorEntry(Color::BLACK));

}

ColorSensor::~ColorSensor()
{
	delete _sensor;

	for(uint i=0; i<_dico_colors.size(); i++){
		delete _dico_colors[i];
	}
}

void ColorSensor::calibration()
{
	int samples = 50;
	ColorRGB min; // 1020 = valeur maxi du capteur
	ColorRGB max;

	std::cout << " # Calibration ..." << std::endl;
	std::cout << " ------------------------------" << std::endl;

	for(uint i=0; i<_dico_colors.size(); i++){

		std::cout << " -> " << *(_dico_colors[i]) << " reference. (Press Enter to validate): ";
		std::cin.ignore();
		sampling(samples, min, max);
		//std::cout << "  > min" << min << " max" << max << std::endl;

		_dico_colors[i]->setMin(min);
		_dico_colors[i]->setMax(max);
	}

	std::cout << " ------------------------------" << std::endl;
	std::cout << " # Calibration done !" << std::endl;
	std::cout << " ------------------------------" << std::endl;
	
}

void ColorSensor::sampling(int samples, ColorRGB& min, ColorRGB& max)
{
	min.set_red(1020);
	min.set_green(1020);
	min.set_blue(1020);

	max.set_red(0);
	max.set_green(0);
	max.set_blue(0);

	int cur_r, cur_g, cur_b = 0;

	for(int i=0; i<samples; i++){
		cur_r = _sensor->red();
		cur_g = _sensor->green();
		cur_b = _sensor->blue();

		if(cur_r < min.red())
			min.set_red(cur_r);
		if(cur_r > max.red())
			max.set_red(cur_r);

		if(cur_g < min.green())
			min.set_green(cur_g);
		if(cur_g > max.green())
			max.set_green(cur_g);

		if(cur_b < min.blue())
			min.set_blue(cur_b);
		if(cur_b > max.blue())
			max.set_blue(cur_b);
	}
}


ColorRGB ColorSensor::getColorRGB()
{
	return ColorRGB(_sensor->red(), _sensor->green(), _sensor->blue());
}