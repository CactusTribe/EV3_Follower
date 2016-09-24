#include <iostream>
#include "../header/ev3dev.h"

using namespace std;
using namespace ev3dev;


int main(){
	cout << "Start engine !" << endl;

	int speed = 500; 
	int time = 2000; 								// ms
	large_motor  motor_A(OUTPUT_A); // PORT (A|B|C|D)
	
	motor_A.set_speed_sp(speed);
	motor_A.set_time_sp(time).run_timed();
	
}