#include "Engine.h"

using namespace ev3dev;

Engine::Engine(large_motor r, large_motor l)
	: _motor_R(&r) , _motor_L(&l)
{
}

Engine::~Engine()
{
	delete _motor_R;
	delete _motor_L;
}


void Engine::setSpeed(int speed)
{
	_speed = speed;
	_motor_L->set_duty_cycle_sp(_speed);
	_motor_R->set_duty_cycle_sp(_speed);
}

void Engine::setDirection(Direction dir)
{
	_direction = dir;

	switch(_direction){
		case Direction::FORWARD:
			_motor_L->set_duty_cycle_sp(_speed);
			_motor_R->set_duty_cycle_sp(_speed);
		break;
		case Direction::BACKWARD:
			_motor_L->set_duty_cycle_sp(_speed * -1);
			_motor_R->set_duty_cycle_sp(_speed * -1);
		break;
		case Direction::LEFT:
			_motor_L->set_duty_cycle_sp(_speed * -1);
			_motor_R->set_duty_cycle_sp(_speed);
		break;
		case Direction::RIGHT:
			_motor_L->set_duty_cycle_sp(_speed);
			_motor_R->set_duty_cycle_sp(_speed * -1);
		break;
		default:
			_motor_L->set_duty_cycle_sp(0);
			_motor_R->set_duty_cycle_sp(0);
		break;
	}
}


void Engine::run()
{
	_motor_L->run_direct();
	_motor_R->run_direct();
}

void Engine::stop()
{
	_motor_L->stop();
	_motor_R->stop();
}
