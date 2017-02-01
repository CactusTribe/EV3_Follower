#include <iostream>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <ctime>

#include "Devices/Robot.h"

using namespace std;
using namespace ev3dev;

void exit_handler(int s);

Robot robot;

int main(int argc, char* argv[]){

  struct sigaction sigIntHandler;
  sigIntHandler.sa_handler = exit_handler;
  sigemptyset(&sigIntHandler.sa_mask);
  sigIntHandler.sa_flags = 0;
  sigaction(SIGINT, &sigIntHandler, NULL);


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

  robot.line_follow();

  robot.getEngine().stop();

  return 0;
}

void exit_handler(int s){
  printf("Caught signal %d\n",s);
  robot.getEngine().stop();
  exit(1);
}
