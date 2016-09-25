#include <iostream>
#include <unistd.h>
#include "ev3dev.h"

using namespace std;
using namespace ev3dev;


int main(){
	large_motor  motor_A(OUTPUT_A); // PORT (A|B|C|D)

	//int speed = 100; 
	//int time = 1000; 								// ms
		
	//motor_A.set_speed_sp(speed);
	//motor_A.set_time_sp(time).run_timed();

	cout << "Start engine !" << endl;

	motor_A.set_duty_cycle_sp(30);
	motor_A.run_direct();
	sleep(2);
	motor_A.stop();

	sleep(1);
	motor_A.set_duty_cycle_sp(-30);
	motor_A.run_direct();
	sleep(2);
	motor_A.stop();

	cout << "Done." << endl;
	
}