#include <iostream>
#include <unistd.h>
#include <string.h>
#include <ctime>

#include "devices/Engine.h"
#include "devices/ColorSensor.h"
#include "commons/Color.h"
#include "commons/Direction.h"

using namespace std;
using namespace ev3dev;

void scan_color(ColorSensor& sn_color);
void line_follow(Engine& engine, ColorSensor& sn_color);

int main(int argc, char* argv[]){

	Engine engine;
	ColorSensor sn_color;

	if(argc > 1){
		if(strcmp(argv[1], "-c") == 0){
			sn_color.calibration();
			sn_color.save_calibration("calibration.calib");
			exit(0);
		}
	}


	sn_color.open_calibration("calibration.calib");
	//scan_color(sn_color);
	
	line_follow(engine, sn_color);

	engine.stop();

	return 0;
}

void line_follow(Engine& engine, ColorSensor& sn_color){
	clock_t begin_time = 0;
	double elapsed_time = 0;
	double search_time = 0.2;
	bool on_line = false;
	Direction lastDir = Direction::RIGHT;

	while(true){
		if(sn_color.getColor() != Color::WHITE){
			
			cout << "BLACK -> FORWARD" << endl;
			engine.setDirection(Direction::FORWARD);
			engine.run();
			on_line = true;

		}
		else{
			cout << "WHITE -> Stop engine" << endl;
			engine.stop();
			on_line = false;

			
			//-------------------------------------------
			// SEARCH LASTDIR
			//-------------------------------------------
			cout << " -> SEARCH LASTDIR" << endl;
			engine.setDirection(lastDir);
			engine.run();
			begin_time = clock();

			while(elapsed_time < search_time) {
				if(sn_color.getColor() != Color::WHITE){
					cout << "LINE FOUND" << endl;
					on_line = true;
					break;
				}

				elapsed_time = double(clock() - begin_time) / CLOCKS_PER_SEC;
			}
			engine.stop();
			sleep(0.5);

			if(on_line == false){
				// Retour sur l'alignement
				elapsed_time = 0;

				if(lastDir == Direction::LEFT){
					engine.setDirection(Direction::RIGHT);
					lastDir = Direction::RIGHT;
				}
				else if(lastDir == Direction::RIGHT){
					engine.setDirection(Direction::LEFT);
					lastDir = Direction::LEFT;
				}

				engine.run();
				begin_time = clock();

				while(elapsed_time < search_time) {
					elapsed_time = double(clock() - begin_time) / CLOCKS_PER_SEC;
				}

				engine.stop();
				sleep(0.5);	
			}
			//------------------------------------------


			//-------------------------------------------
			// SEARCH -LASTDIR
			//-------------------------------------------
			if(on_line == false){
				// Cherche la ligne à gauche
				cout << " -> SEARCH -LASTDIR" << endl;
				elapsed_time = 0;
				engine.setDirection(lastDir);
				engine.run();
				begin_time = clock();
				

				while(elapsed_time < search_time) {
					if(sn_color.getColor() != Color::WHITE){
						cout << "LINE FOUND" << endl;
						on_line = true;
						break;
					}

					elapsed_time = double(clock() - begin_time) / CLOCKS_PER_SEC;
				}
				engine.stop();
				sleep(0.5);	

				if(on_line == false){
					//Retour sur l'alignement

					if(lastDir == Direction::LEFT){
						engine.setDirection(Direction::RIGHT);
						lastDir = Direction::RIGHT;
					}
					else if(lastDir == Direction::RIGHT){
						engine.setDirection(Direction::LEFT);
						lastDir = Direction::LEFT;
					}

					engine.run();
					begin_time = clock();
					elapsed_time = 0;

					while(elapsed_time < search_time) {
						elapsed_time = double(clock() - begin_time) / CLOCKS_PER_SEC;
					}

					engine.stop();
					sleep(0.5);		
				}	
			}
			//------------------------------------------


			//-------------------------------------------
			// SEARCH FORWARD
			//-------------------------------------------
			if(on_line == false){
				// Cherche la ligne devant
				cout << " -> SEARCH FORWARD" << endl;
				elapsed_time = 0;
				engine.setDirection(Direction::FORWARD);
				engine.run();
				begin_time = clock();
				
				while(elapsed_time < search_time) {
					if(sn_color.getColor() != Color::WHITE){
						cout << "LINE FOUND" << endl;
						on_line = true;
						break;
					}

					elapsed_time = double(clock() - begin_time) / CLOCKS_PER_SEC;
				}		
				engine.stop();
				sleep(0.5);		
			}

			if(on_line == false){
				break;
			}

		}

	}

}

void scan_color(ColorSensor& cs){
	while(true){
		cout << " -> Scan color (Press Enter): ";
		cin.ignore();

		Color color = cs.getColor();
		switch(color){
			case Color::RED:
				cout << "RED" << endl;
			break;

			case Color::GREEN:
				cout << "GREEN" << endl;
			break;

			case Color::BLUE:
				cout << "BLUE" << endl;
			break;

			case Color::YELLOW:
				cout << "YELLOW" << endl;
			break;

			case Color::WHITE:
				cout << "WHITE" << endl;
			break;

			case Color::BLACK:
				cout << "BLACK" << endl;
			break;

			case Color::UNKNOW:
				cout << "UNKNOW" << endl;
			break;
		}
	}
}