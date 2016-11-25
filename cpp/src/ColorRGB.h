#ifndef COLORRGB_H
#define COLORRGB_H

#include <iostream>

class ColorRGB {

public:
	ColorRGB();
	ColorRGB(int r, int g, int b);
	virtual ~ColorRGB();

	int red();
	int green();
	int blue();

private:
	int _red = -1;
	int _green = -1;
	int _blue = -1;


friend std::ostream& operator<<(std::ostream& out, ColorRGB& color);
friend bool operator>=(ColorRGB& color1, ColorRGB& color2);
friend bool operator<=(ColorRGB& color1, ColorRGB& color2);
};

#endif