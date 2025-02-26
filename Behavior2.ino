// Libraries
#include <Wire.h>
#include <math.h>
#include <color.h>
#include <motor.h>
#include <movement.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>

// Variables
uint8_t marker;
int last;
// Define color codes
#define COLOR_RED 2
#define COLOR_BLUE 6
#define COLOR_BLACK 1
#define COLOR_WHITE 0
#define COLOR_GREEN 4
#define COLOR_MAGENTA 7



void setup() {
  // put your setup code here, to run once:
  MotorSetup();
  //Everything below is setup for MPU6050
  AccelSetup(); 
}

void loop() 
{
  //Get Color reading
  marker = color();
  setMotor(1,200);
  if (marker == 1){
    rotateUntil180FromStart();
  }
  delay(500); // Adjust the delay as needed
}
