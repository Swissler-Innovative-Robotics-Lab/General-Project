
#include "color.h"
#include "motor.h"
#include "meshota.h" 
void setup(){
  otaSetup();
}

void mainLoop(){
      uint8_t top = getColor(TOP_SENSOR);
      uint8_t bottom = getColor(BOTTOM_SENSOR);
      uint8_t left = getColor(LEFT_SENSOR);
      uint8_t right = getColor(RIGHT_SENSOR);

    
      if (top == COLOR_BLACK) {
          sendBroadcast("MOVE_UP", true);
          moveForward();
      } 
      else if (bottom == COLOR_BLACK) {
          sendBroadcast("MOVE_DOWN", true);
          moveBackward();
      } 
      else if (left == COLOR_BLACK) {
          sendBroadcast("MOVE_LEFT", true);
          turnLeft();
      } 
      else if (right == COLOR_BLACK) {
          sendBroadcast("MOVE_RIGHT", true);
          turnRight();
      } 
      else {
          sendBroadcast("STOP", true);
          stop();
      }
  }
    


void loop(){
  otaLoop();
}

  void moveForward() {
      setMotor(1, 255);
  }

  void moveBackward() {
      setMotor(-1, 255); 
  }

  void turnLeft() {
      setMotor(-3, 150); 
  }

  void turnRight() {
      setMotor(3, 150); 
  }

  void stop() {
      setMotor(0, 0); 
  }

