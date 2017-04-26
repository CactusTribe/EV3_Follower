#include "Robot.h"

#define SPEED 60

#define SEARCH_SPEED 60
#define SEARCH_TIME 0.2

#define CORRECT_SPEED 50
#define CORRECT_TIME 0.1

Robot::Robot()
{
	sleep(2);
	_engine = new Engine();
	_sn_color = new ColorSensor();
}

Robot::~Robot()
{
	delete _engine;
	delete _sn_color;
}

Engine& Robot::getEngine()
{
	return *_engine;
}

ColorSensor& Robot::getColorSensor()
{
	return *_sn_color;
}

void Robot::scan_color(){
	std::string rep = "";

	while(true){
		std::cout << " -> [Enter]Scan [q]Quit : ";
		rep = std::cin.get();

		if(rep.compare("q") == 0){
			break;
		}
		int color_ref = _sn_color->getColor();
		std::string color_name = _sn_color->getColorName(color_ref);

		std::cout << " Color #" << color_ref << " (" << color_name << ")" << std::endl;
	}
}

bool Robot::search_line(Direction dir, int bg_color, double seconds){
	clock_t begin_time = 0;
	double elapsed_time = 0;
	_engine->setSpeed(SEARCH_SPEED);
	
	if(dir == Direction::RIGHT){
		//std::cout << " -> SEARCH RIGHT" << std::endl;
		_engine->setDirection(Direction::RIGHT);
		//_engine->run();
	}
	else if(dir == Direction::LEFT){
		//std::cout << " -> SEARCH LEFT" << std::endl;
		_engine->setDirection(Direction::LEFT);
		//_engine->run();
	}
	else{
		return false;
	}
	
	begin_time = clock();
	while(elapsed_time < seconds) {
		if(_sn_color->getColor() != bg_color){
			//std::cout << "LINE FOUND" << std::endl;
			//_engine->setSpeed(0);
			return true;
		}
		elapsed_time = double(clock() - begin_time) / CLOCKS_PER_SEC;
		sleep(0.01);
	}

	return false;
}

void Robot::line_follow(){

	// INITIALISATION
	bool on_line = false;
	Direction lastDir = Direction::LEFT;
	Direction lastDirCorrection = Direction::LEFT;
	int background = _sn_color->getColor();

	_engine->setSpeed(SPEED);
	_engine->setDirection(Direction::FORWARD);
	//std::cout << "BG COLOR # " << background << " (" << _sn_color->getColorName(background) << ")" << std::endl;

	while(true){
		// Si on est sur la ligne
		if(_sn_color->getColor() != background){
			_engine->setSpeed(SPEED);
			_engine->setDirection(Direction::FORWARD);
			//_engine->run();
		}
		else{

			// Correction de la trajectoire
			if(lastDirCorrection == Direction::LEFT){
					on_line = search_line(Direction::RIGHT, background, CORRECT_TIME);
					lastDirCorrection = Direction::RIGHT;
			}
			else{
					on_line = search_line(Direction::LEFT, background, CORRECT_TIME);
					lastDirCorrection = Direction::LEFT;
			}

			//on_line = search_line(lastDir, background, CORRECT_TIME);
			// Si la correction ne suffit pas a trouver la ligne
			if(!on_line){
				if(lastDirCorrection == Direction::LEFT){
					on_line = search_line(Direction::RIGHT, background, SEARCH_TIME);
					lastDir = Direction::RIGHT;
				}
				else{
					on_line = search_line(Direction::LEFT, background, SEARCH_TIME);
					lastDir = Direction::LEFT;
				}

				if(!on_line){
					lastDir = Direction::RIGHT;
				}
			}

		}
	}
}

