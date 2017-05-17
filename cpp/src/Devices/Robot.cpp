#include "Robot.h"

#define SPEED 60
#define SEARCH_SPEED 60
#define CORRECT_SPEED 60

#define SEARCH_TIME 0.4
#define CORRECT_TIME 0.2

#define DELAY_CORRECTION 0.1

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
	
	if(dir == Direction::RIGHT){
		//std::cout << " -> SEARCH RIGHT" << std::endl;
		_engine->setDirection(Direction::RIGHT);
	}
	else if(dir == Direction::LEFT){
		//std::cout << " -> SEARCH LEFT" << std::endl;
		_engine->setDirection(Direction::LEFT);
	}
	else{
		return false;
	}
	
	_engine->run();
	begin_time = clock();
	while(elapsed_time < seconds) {
		if(_sn_color->getColor() != bg_color){
			//std::cout << "LINE FOUND" << std::endl;
			_engine->stop();
			return true;
		}
		elapsed_time = double(clock() - begin_time) / CLOCKS_PER_SEC;
		//sleep(0.01);
	}

	return false;
}

Direction Robot::getOpposedDir(Direction dir){
	if(dir == Direction::LEFT){
		return Direction::RIGHT;
	}
	else{
		return Direction::LEFT;
	}
}


void Robot::line_follow(){

	// INITIALISATION
	clock_t begin_time_found = 1;
	double elapsed_time_found = 0;
	bool on_line = false;
	int background = _sn_color->getColor();

	Direction linePosition = Direction::LEFT;

	_engine->run();
	_engine->setSpeed(SPEED);
	_engine->setDirection(Direction::FORWARD);
	//std::cout << "BG COLOR # " << background << " (" << _sn_color->getColorName(background) << ")" << std::endl;

	while(true){

		try{

			// Si on est sur la ligne
			if(_sn_color->getColor() != background){
				_engine->run();
				_engine->setSpeed(SPEED);
				_engine->setDirection(Direction::FORWARD);
			}
			else{
				elapsed_time_found = double(clock() - begin_time_found) / CLOCKS_PER_SEC; 

				/* Correction de trajectoire */
				_engine->setSpeed(SEARCH_SPEED);

				if(elapsed_time_found >= DELAY_CORRECTION){
					on_line = search_line(linePosition, background, CORRECT_TIME);
				}
				else{
					on_line = search_line(getOpposedDir(linePosition), background, CORRECT_TIME);
					linePosition = getOpposedDir(linePosition);
				}
				
				//linePosition = getOpposedDir(linePosition);

				/* Si la correction échoue on va dans la direction opposée */
				if(!on_line){
					on_line = search_line(getOpposedDir(linePosition), background, SEARCH_TIME);
					linePosition = getOpposedDir(linePosition);

					if(on_line){
						begin_time_found = clock();
					}
					//lastDir = getOpposedDir(lastDir);
				}
				else{
					begin_time_found = clock();
				}

			}

		}catch ( ... )
		{ 
			std::cout << "Erreur inconnue.\n"; 
		}
	}
}

