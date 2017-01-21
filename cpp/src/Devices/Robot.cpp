#include "Robot.h"

Robot::Robot()
{
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
	
	if(dir == Direction::RIGHT){
		std::cout << " -> SEARCH RIGHT" << std::endl;
		_engine->setDirection(Direction::RIGHT);
		_engine->run();
	}
	else if(dir == Direction::LEFT){
		std::cout << " -> SEARCH LEFT" << std::endl;
		_engine->setDirection(Direction::LEFT);
		_engine->run();
	}
	else{
		return false;
	}
	
	begin_time = clock();
	while(elapsed_time < seconds) {
		if(_sn_color->getColor() != bg_color){
			std::cout << "LINE FOUND" << std::endl;
			return true;
		}
		elapsed_time = double(clock() - begin_time) / CLOCKS_PER_SEC;
	}

	return false;
}

void Robot::line_follow(){

	// INITIALISATION
	bool on_line = false;
	double search_time = 0.1;
	Direction lastDir = Direction::RIGHT;
	_engine->setSpeed(30);

	// GET BACKGROUND COLOR
	int background = _sn_color->getColor();
	std::cout << "BG COLOR # " << background << " (" << _sn_color->getColorName(background) << ")" << std::endl;

	while(true){
		// Si on est sur la ligne
		if(_sn_color->getColor() != background){
			_engine->setDirection(Direction::FORWARD);
			_engine->run();
		}
		else{
			on_line = search_line(lastDir, background, search_time);

			if(!on_line){
				if(lastDir == Direction::LEFT){
					on_line = search_line(Direction::RIGHT, background, 1000);
					lastDir = Direction::RIGHT;
				}
				else if(lastDir == Direction::RIGHT){
					on_line = search_line(Direction::LEFT, background, search_time * 2);
					lastDir = Direction::LEFT;
				}

				if(!on_line){
					lastDir = Direction::RIGHT;
				}
			}
		}
	}
}



