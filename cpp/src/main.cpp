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
	bool on_line = false;

	while(true){
		if(sn_color.getColor() == Color::BLACK){
			
			cout << "BLACK -> FORWARD" << endl;
			engine.setDirection(Direction::FORWARD);
			engine.run();
			on_line = true;

		}
		else{
			cout << "WHITE -> Stop engine" << endl;
			engine.stop();
			on_line = false;

			// Cherche la ligne à droite
			cout << " -> SEARCH RIGHT" << endl;
			engine.setDirection(Direction::RIGHT);
			engine.run();
			begin_time = clock();

			while(elapsed_time < 0.1) {
				if(sn_color.getColor() == Color::BLACK){
					cout << "LINE FOUND" << endl;
					on_line = true;
					break;
				}

				cout << "LINE NOT FOUND" << endl;
				elapsed_time = double(clock() - begin_time) / CLOCKS_PER_SEC;
				std::cout << elapsed_time << std::endl;
			}
			engine.stop();
			sleep(0.5);


			if(on_line == false){
				// Cherche la ligne à gauche
				cout << " -> SEARCH LEFT" << endl;
				engine.setDirection(Direction::LEFT);
				engine.run();
				begin_time = clock();
				elapsed_time = 0;

				while(elapsed_time < 0.2) {
					if(sn_color.getColor() == Color::BLACK){
						cout << "LINE FOUND" << endl;
						on_line = true;
						break;
					}

					cout << "LINE NOT FOUND" << endl;
					elapsed_time = double(clock() - begin_time) / CLOCKS_PER_SEC;
					std::cout << elapsed_time << std::endl;
				}

				//Retour sur l'alignement
				engine.setDirection(Direction::RIGHT);
				engine.run();
				begin_time = clock();
				elapsed_time = 0;

				while(elapsed_time < 0.1) {
					elapsed_time = double(clock() - begin_time) / CLOCKS_PER_SEC;
				}

				engine.stop();
				sleep(0.5);			
			}

			if(on_line == false){
				// Cherche la ligne devant
				cout << " -> SEARCH FORWARD" << endl;
				engine.setDirection(Direction::FORWARD);
				engine.run();
				begin_time = clock();
				elapsed_time = 0;

				while(elapsed_time < 0.5) {
					if(sn_color.getColor() == Color::BLACK){
						cout << "LINE FOUND" << endl;
						on_line = true;
						break;
					}

					cout << "LINE NOT FOUND" << endl;
					elapsed_time = double(clock() - begin_time) / CLOCKS_PER_SEC;
					std::cout << elapsed_time << std::endl;
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