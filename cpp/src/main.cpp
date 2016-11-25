#include <iostream>
#include <unistd.h>
#include "ev3dev.h"
#include "Devices/Engine.h"
#include "Devices/ColorSensor.h"
#include "ColorRGB.h"

using namespace std;
using namespace ev3dev;


int main(){

	large_motor  motor_R(OUTPUT_A); // PORT (A|B|C|D)
	large_motor  motor_L(OUTPUT_D); // PORT (A|B|C|D)

	ColorSensor sn_color;
	sn_color.calibration(50);

	ColorRGB color = sn_color.getColor();
	cout << color << endl;

	ColorRGB c1(19, 401, 201);
	ColorRGB c2(100, 400, 200);

	cout << c1 << endl;
	cout << c2 << endl;
	cout << "c1 >= c2 : " << (c1>=c2) << endl;
	cout << "c1 <= c2 : " << (c1<=c2) << endl;

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