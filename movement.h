#pragma once

#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

// Declare the MPU6050 object
extern Adafruit_MPU6050 mpu;

// Variable declarations
extern float x;
extern float y;
extern float newtheta;
extern float current;
extern float goalHigh;
extern float goalLow;

// Function declarations
void AccelSetup();
float getTheta();
void toTheta(float goal);
void toThetaPID(float goal);