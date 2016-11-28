#include "Engine.h"

using namespace ev3dev;

Engine::Engine()
{
	_motor_R = new large_motor(OUTPUT_A);
	_motor_L = new large_motor(OUTPUT_D);

	_direction = Direction::FORWARD;
	_run = false;
	
	_motor_L->run_direct();
	_motor_R->run_direct();
}

Engine::~Engine()
{
	_motor_R->reset();
	_motor_L->reset();

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
}


void Engine::run()
{

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

	//_motor_L->run_direct();
	//_motor_R->run_direct();
	_run = true;
}

void Engine::stop()
{
	//_motor_L->stop();
	//_motor_R->stop();
	_motor_L->set_duty_cycle_sp(0);
	_motor_R->set_duty_cycle_sp(0);
	_run = false;
}

bool Engine::running()
{
	return _run;
}
