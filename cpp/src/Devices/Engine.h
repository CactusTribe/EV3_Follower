#ifndef ENGINE_H
#define ENGINE_H

#include "../libs/ev3dev.h"
#include "../commons/Direction.h"

class Engine {

public:
	Engine();
	virtual ~Engine();

	void setSpeed(int speed);
	void setDirection(Direction dir);

	void run();
	void stop();
	bool running();

private:
	int _speed = 20;
	bool _run = false;
	Direction _direction; 
	ev3dev::large_motor* _motor_R;
	ev3dev::large_motor* _motor_L;

};

#endif