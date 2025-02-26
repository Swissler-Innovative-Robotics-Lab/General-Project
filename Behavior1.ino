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

  // put your main code here, to run repeatedly:
  //checking for red
  //if(marker == 2 & previous color != 2)
  //leftturn()
  if (marker == 2) 
  {
    Landscape();
    setMotor(1,200);
    
    if (marker != last)
    //turn
    {
      Serial.println("Color is Red");
    }
    //radians = setMotor();
    //distance = radians * circumference;
    //
  }
  else
  {
    //checking for blue
    if (marker == 6)
    {
      Portrait();
      setMotor(1, 200);
       if (marker != last)
       //turn
      {
        Serial.println("Color is Blue");
      }

    }
    //checking for black
    else if(marker == 1 && marker == 0)
    {
      setMotor(0,0);
       if (marker != last)
    {
    Serial.println("Color is Black or White");
    }
    }
    // checking for green
    else if(marker == 4)
    {
      setMotor(2,200);
       if (marker != last)
    {
    Serial.println("Color is Green");
    }
    }
    //checking for magenta
    else if(marker == 7)
    {
      setMotor(-2,200);
       if (marker != last)
    {
    Serial.println("Color is Magenta");
    }
    }

  }
  last = marker;

}
