#include <iostream>
#include <unistd.h>
#include "ev3dev.h"
#include "Devices/Engine.h"
#include "Devices/ColorSensor.h"
#include "ColorRGB.h"
#include "Color.h"

using namespace std;
using namespace ev3dev;


int main(){

	large_motor  motor_R(OUTPUT_A); // PORT (A|B|C|D)
	large_motor  motor_L(OUTPUT_D); // PORT (A|B|C|D)

	ColorSensor sn_color;
	sn_color.calibration();

	while(true){
		cout << " -> Scan color (Press Enter to validate): ";
		cin.ignore();

		Color color = sn_color.getColor();
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

/*
	ColorRGB color = sn_color.getColorRGB();
	cout << color << endl;

	ColorRGB c1(19, 401, 201);
	ColorRGB c2(100, 400, 200);

	cout << c1 << endl;
	cout << c2 << endl;
	cout << "c1 >= c2 : " << (c1>=c2) << endl;
	cout << "c1 <= c2 : " << (c1<=c2) << endl;
*/

/*
	Engine engine(motor_R, motor_L);
	engine.setDirection(Direction::FORWARD);
	engine.run();

	sleep(1);
	engine.stop();
	sleep(1);
	
	engine.setDirection(Direction::BACKWARD);
	engine.run();
	sleep(1);
	engine.stop();

	engine.setDirection(Direction::LEFT);
	engine.run();
	sleep(1);
	engine.stop();

	engine.setDirection(Direction::RIGHT);
	engine.run();
	sleep(1);
	engine.stop();
*/

	return 0;
}