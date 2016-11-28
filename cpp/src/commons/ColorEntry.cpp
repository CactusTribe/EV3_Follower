#include "ColorEntry.h"

ColorEntry::ColorEntry(Color color)
	: _color(color)
{

}

ColorEntry::~ColorEntry()
{

}

void ColorEntry::setMin(ColorRGB min)
{
	_min = min;
}

void ColorEntry::setMax(ColorRGB max)
{
	_max = max;
}

ColorRGB ColorEntry::getMin()
{
	return _min;
}

ColorRGB ColorEntry::getMax()
{
	return _max;
}

Color ColorEntry::getColor()
{
	return _color;
}

std::ostream& operator<<(std::ostream& out, ColorEntry& c)
{
	switch(c._color){
		case Color::RED:
			out << "RED";
		break;

		case Color::GREEN:
			out << "GREEN";
		break;

		case Color::BLUE:
			out << "BLUE";
		break;

		case Color::YELLOW:
			out << "YELLOW";
		break;

		case Color::WHITE:
			out << "WHITE";
		break;

		case Color::BLACK:
			out << "BLACK";
		break;

		default:
			out << "UNKNOW";
		break;
	}

	return out;
}