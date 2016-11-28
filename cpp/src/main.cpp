#include <iostream>
#include <unistd.h>
#include "ev3dev.h"
#include "Devices/Engine.h"
#include "Devices/ColorSensor.h"
#include "ColorRGB.h"
#include "Color.h"

using namespace std;
using namespace ev3dev;

void scan_color(ColorSensor& sn_color);
void line_follow(Engine& engine, ColorSensor& sn_color);

int main(){

	Engine engine;
	ColorSensor sn_color;

	sn_color.calibration();
	//scan_color(sn_color);
	
	//line_follow(engine, sn_color);

	return 0;
}

void line_follow(Engine& engine, ColorSensor& sn_color){

	while(true){
		if(sn_color.getColor() == Color::BLACK){
			
			if(engine.running() == false){
				cout << "BLACK -> Start engine" << endl;
				engine.run();
			}
			else{
				cout << "BLACK -> Engine running" << endl;
			}

		}
		else{
			cout << "WHITE -> Stop engine" << endl;
			engine.stop();
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