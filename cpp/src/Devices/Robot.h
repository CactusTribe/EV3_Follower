#ifndef ROBOT_H
#define ROBOT_H

#include "Engine.h"
#include "ColorSensor.h"
#include "../commons/Direction.h"

class Robot {

public:
	Robot();
	virtual ~Robot();

	Engine& getEngine();
	ColorSensor& getColorSensor();

	void scan_color();
	void line_follow();

private:
	Engine* _engine;
	ColorSensor* _sn_color;
};


#endif