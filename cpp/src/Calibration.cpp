#include <iostream>
#include <unistd.h>
#include "ev3dev.h"
#include "Devices/ColorSensor.h"
#include "ColorRGB.h"
#include "Color.h"

using namespace std;
using namespace ev3dev;

int main(){

	ColorSensor sn_color;
	sn_color.calibration();
	sn_color.save_calibration("calibration.calib");

	return 0;
}