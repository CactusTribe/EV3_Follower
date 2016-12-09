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
		std::cout << " -> Scan color (Press Enter) [q]Quit : ";
		rep = std::cin.get();

		if(rep.compare("q") == 0){
			break;
		}
		std::cout << " # Référence n°" << _sn_color->getColor() << std::endl;
	}
}

void Robot::line_follow(){
	clock_t begin_time = 0;
	double elapsed_time = 0;
	double search_time = 0.2;
	bool on_line = false;
	Direction lastDir = Direction::RIGHT;

	while(true){
		if(_sn_color->getColor() != 0){
			_engine->setDirection(Direction::FORWARD);
			_engine->run();
			on_line = true;
		}
		else{
			std::cout << "LINE LOOSE" << std::endl;
			_engine->stop();
			on_line = false;

			//-------------------------------------------
			// SEARCH LASTDIR
			//-------------------------------------------
			std::cout << " -> SEARCH LASTDIR" << std::endl;
			_engine->setDirection(lastDir);
			_engine->run();
			begin_time = clock();

			while(elapsed_time < search_time) {
				if(_sn_color->getColor() != 0){
					std::cout << "LINE FOUND" << std::endl;
					on_line = true;
					break;
				}
				elapsed_time = double(clock() - begin_time) / CLOCKS_PER_SEC;
			}

			_engine->stop();
			sleep(0.5);

			if(on_line == false){
				// Retour sur l'alignement
				elapsed_time = 0;

				if(lastDir == Direction::LEFT){
					_engine->setDirection(Direction::RIGHT);
					lastDir = Direction::RIGHT;
				}
				else if(lastDir == Direction::RIGHT){
					_engine->setDirection(Direction::LEFT);
					lastDir = Direction::LEFT;
				}

				_engine->run();
				begin_time = clock();

				while(elapsed_time < search_time) {
					elapsed_time = double(clock() - begin_time) / CLOCKS_PER_SEC;
				}

				_engine->stop();
				sleep(0.5);	
			}
			//------------------------------------------


			//-------------------------------------------
			// SEARCH -LASTDIR
			//-------------------------------------------
			if(on_line == false){
				// Cherche la ligne à gauche
				std::cout << " -> SEARCH -LASTDIR" << std::endl;
				elapsed_time = 0;
				_engine->setDirection(lastDir);
				_engine->run();
				begin_time = clock();
				
				while(elapsed_time < search_time) {
					if(_sn_color->getColor() != 0){
						std::cout << "LINE FOUND" << std::endl;
						on_line = true;
						break;
					}
					elapsed_time = double(clock() - begin_time) / CLOCKS_PER_SEC;
				}

				_engine->stop();
				sleep(0.5);	

				if(on_line == false){
					//Retour sur l'alignement

					if(lastDir == Direction::LEFT){
						_engine->setDirection(Direction::RIGHT);
						lastDir = Direction::RIGHT;
					}
					else if(lastDir == Direction::RIGHT){
						_engine->setDirection(Direction::LEFT);
						lastDir = Direction::LEFT;
					}

					_engine->run();
					begin_time = clock();
					elapsed_time = 0;

					while(elapsed_time < search_time) {
						elapsed_time = double(clock() - begin_time) / CLOCKS_PER_SEC;
					}

					_engine->stop();
					sleep(0.5);		
				}	
			}
			//------------------------------------------


			//-------------------------------------------
			// SEARCH FORWARD
			//-------------------------------------------
			if(on_line == false){
				// Cherche la ligne devant
				std::cout << " -> SEARCH FORWARD" << std::endl;
				elapsed_time = 0;
				_engine->setDirection(Direction::FORWARD);
				_engine->run();
				begin_time = clock();
				
				while(elapsed_time < search_time) {
					if(_sn_color->getColor() != 0){
						std::cout << "LINE FOUND" << std::endl;
						on_line = true;
						break;
					}
					elapsed_time = double(clock() - begin_time) / CLOCKS_PER_SEC;
				}		
				_engine->stop();
				sleep(0.5);		
			}

			if(on_line == false){
				break;
			}
		}
	}
}

