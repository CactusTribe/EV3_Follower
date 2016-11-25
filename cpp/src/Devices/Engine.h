#ifndef ENGINE_H
#define ENGINE_H

#include "../ev3dev.h"
#include "Direction.h"

class Engine {

public:
	Engine(ev3dev::large_motor r, ev3dev::large_motor l);
	virtual ~Engine();

	void setSpeed(int speed);
	void setDirection(Direction dir);

	void run();
	void stop();

private:
	int _speed = 40;
	Direction _direction = Direction::FORWARD; 
	ev3dev::large_motor* _motor_R;
	ev3dev::large_motor* _motor_L;

};

#endif