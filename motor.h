#pragma once  // Prevents multiple includes

#include <Arduino.h>

// Motor pin definitions
#define MApin1 11
#define MApin2 12
#define MBpin1 6
#define MBpin2 9
#define MSpin 10

// Encoder pin declarations
extern const int MAEN1;
extern const int MAEN2;
extern const int MBEN1;
extern const int MBEN2;

// Global variables
extern long baudrate;
extern volatile int pos;
extern long prevt;
extern float eprev;
extern float eintegral;
extern volatile uint32_t pulseCount;
extern volatile uint32_t revolutionCount;
extern int pin;

// Function declarations
void MotorSetup();
void setMotor(int dir, int pwmVal);
void readEncoder();  // Add this if it's defined
