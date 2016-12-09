#ifndef COLORENTRY_H
#define COLORENTRY_H

#include <iostream>
#include "Color.h"
#include "ColorRGB.h"

class ColorEntry {
public:
	ColorEntry();
	virtual ~ColorEntry();

	void setMin(ColorRGB min);
	void setMax(ColorRGB max);

	ColorRGB getMin();
	ColorRGB getMax();

private:
	ColorRGB _min;
	ColorRGB _max;

friend std::ostream& operator<<(std::ostream& out, ColorEntry& c);
};

#endif