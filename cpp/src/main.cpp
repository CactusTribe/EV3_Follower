#include <iostream>
#include <unistd.h>
#include <string.h>
#include <ctime>

#include "devices/Robot.h"

using namespace std;
using namespace ev3dev;

int main(int argc, char* argv[]){

	Robot robot;

	if(argc > 1){
		if(strcmp(argv[1], "-c") == 0){
			robot.getColorSensor().calibration();
			robot.getColorSensor().save_calibration("calibration.calib");
			exit(0);
		}
		if(strcmp(argv[1], "-s") == 0){
			robot.getColorSensor().open_calibration("calibration.calib");
			robot.scan_color();
			exit(0);
		}
	}

	robot.getColorSensor().open_calibration("calibration.calib");

	//robot.line_follow();

	robot.getEngine().stop();

	return 0;
}

