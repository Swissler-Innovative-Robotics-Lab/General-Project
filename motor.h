// libraries
#include <PID_v1.h>

// motor pins
#define MApin1 11
#define MApin2 12
#define MBpin1 6
#define MBpin2 9
#define MSpin 10
//#define PWM = 16;

//encoder pins
const int MAEN1 = 18;
const int MAEN2 = 17;
const int MBEN1 = 16;
const int MBEN2 = 15;

//variables
long baudrate = 9600;
volatile int pos = 0;
long prevt = 0;
float eprev = 0;
float eintegral = 0;

int pin;

//int pwmVal = 255;
int dir = 1;

void readEncoder(){
  int b = digitalRead(MAEN2);
  if(b>0){
    pos++;
  }
  else{
    pos--;
  }
}

void MotorSetup() {
  // put your setup code here, to run once:
  Serial.begin(baudrate);
  pinMode(MAEN1,INPUT);
  pinMode(MAEN2,INPUT);
  pinMode(MApin1,OUTPUT);
  pinMode(MApin2,OUTPUT);
  pinMode(MBpin1,OUTPUT);
  pinMode(MBpin2,OUTPUT);
  pinMode(MSpin, OUTPUT);
  digitalWrite(MSpin,HIGH);
  attachInterrupt(digitalPinToInterrupt(MAEN1),readEncoder, RISING);
}

float pwmVal(){

}

void setMotor(int dir, int pwmVal)
{
int HalfpwmVal = pwmVal/2;
  if(dir==1){
    analogWrite(MApin1,pwmVal);
    analogWrite(MApin2,0);
    analogWrite(MBpin1,pwmVal);
    analogWrite(MBpin2,0);
    //Serial.println("right");
  }
  else if(dir== -1){
    analogWrite(MApin1,0);
    analogWrite(MApin2,pwmVal);
    analogWrite(MBpin1,0);
    analogWrite(MBpin2,pwmVal);
    //Serial.println("left");
  }
  else if(dir== -2){
    analogWrite(MApin1,pwmVal);
    analogWrite(MApin2,0);
    analogWrite(MBpin1,0);
    analogWrite(MBpin2,pwmVal);
    //Serial.println("CW");
  }
  else if(dir== 2){
    analogWrite(MApin1,0);
    analogWrite(MApin2,pwmVal);
    analogWrite(MBpin1,pwmVal);
    analogWrite(MBpin2,0);
    //Serial.println("CCW");
  }
   else if(dir== 3){
    analogWrite(MApin1,pwmVal);
    analogWrite(MApin2,0);
    analogWrite(MBpin1,HalfpwmVal);
    analogWrite(MBpin2,0);
    //Serial.println("Slow right");
  }
   else if(dir== -3){
    analogWrite(MApin1,0);
    analogWrite(MApin2,pwmVal);
    analogWrite(MBpin1,0);
    analogWrite(MBpin2,HalfpwmVal);
    //Serial.println("Slow left");
  }

  else if(dir== 0){
    analogWrite(MApin1, 0);
    analogWrite(MApin2, 0);
    analogWrite(MBpin1, 0);
    analogWrite(MBpin2, 0);
    Serial.println("nothing");
  }
  //Serial.println(dir);
  //Serial.println(pwmVal);
}
