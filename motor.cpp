#include "motor.h"

// Encoder pin definitions
const int MAEN1 = 18;
const int MAEN2 = 17;
const int MBEN1 = 16;
const int MBEN2 = 15;

// Global variables
long baudrate = 115200;
volatile int pos = 0;
long prevt = 0;
float eprev = 0;
float eintegral = 0;
volatile uint32_t pulseCount = 0;
volatile uint32_t revolutionCount = 0;
int pin;

void readEncoder() {
  // Your encoder logic here
  // example:
  pulseCount++;
}

void MotorSetup() {
  pinMode(MAEN1, INPUT);
  pinMode(MAEN2, INPUT);
  pinMode(MApin1, OUTPUT);
  pinMode(MApin2, OUTPUT);
  pinMode(MBpin1, OUTPUT);
  pinMode(MBpin2, OUTPUT);
  pinMode(MSpin, OUTPUT);
  digitalWrite(MSpin, HIGH);

  pinMode(MAEN1, INPUT_PULLDOWN);
  attachInterrupt(digitalPinToInterrupt(MAEN1), readEncoder, RISING);
}

void setMotor(int dir, int pwmVal) {
  int HalfpwmVal = pwmVal / 2;
// add a delay if second motor doesn't turn on
  switch (dir) {
    case 1:
      analogWrite(MApin1, pwmVal);
      analogWrite(MApin2, 0);
      analogWrite(MBpin1, pwmVal);
      analogWrite(MBpin2, 0);
      break;
    case -1:
      analogWrite(MApin1, 0);
      analogWrite(MApin2, pwmVal);
      analogWrite(MBpin1, 0);
      analogWrite(MBpin2, pwmVal);
      break;
    case -2:
      analogWrite(MApin1, pwmVal);
      analogWrite(MApin2, 0);
      analogWrite(MBpin1, 0);
      analogWrite(MBpin2, pwmVal);
      break;
    case 2:
      analogWrite(MApin1, 0);
      analogWrite(MApin2, pwmVal);
      analogWrite(MBpin1, pwmVal);
      analogWrite(MBpin2, 0);
      break;
    case 3:
      analogWrite(MApin1, pwmVal);
      analogWrite(MApin2, 0);
      analogWrite(MBpin1, HalfpwmVal);
      analogWrite(MBpin2, 0);
      break;
    case -3:
      analogWrite(MApin1, 0);
      analogWrite(MApin2, pwmVal);
      analogWrite(MBpin1, 0);
      analogWrite(MBpin2, HalfpwmVal);
      break;
    case 0:
    default:
      analogWrite(MApin1, 0);
      analogWrite(MApin2, 0);
      analogWrite(MBpin1, 0);
      analogWrite(MBpin2, 0);
      Serial.println("nothing");
      break;
  }
}
