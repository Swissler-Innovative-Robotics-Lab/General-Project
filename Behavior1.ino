// Libraries
#include <Wire.h>
#include <math.h>
#include <color.h>
#include <motor.h>
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

Adafruit_MPU6050 mpu;

void setup() {
  // put your setup code here, to run once:
  motorSetup();
  //Everything below is setup for MPU6050
  while (!Serial)
    delay(10); // will pause Zero, Leonardo, etc until serial console opens

  Serial.println("Adafruit MPU6050 test!");

  // Try to initialize!
  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }
  Serial.println("MPU6050 Found!");

  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  Serial.print("Accelerometer range set to: ");
  switch (mpu.getAccelerometerRange()) {
  case MPU6050_RANGE_2_G:
    Serial.println("+-2G");
    break;
  case MPU6050_RANGE_4_G:
    Serial.println("+-4G");
    break;
  case MPU6050_RANGE_8_G:
    Serial.println("+-8G");
    break;
  case MPU6050_RANGE_16_G:
    Serial.println("+-16G");
    break;
  }
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  Serial.print("Gyro range set to: ");
  switch (mpu.getGyroRange()) {
  case MPU6050_RANGE_250_DEG:
    Serial.println("+- 250 deg/s");
    break;
  case MPU6050_RANGE_500_DEG:
    Serial.println("+- 500 deg/s");
    break;
  case MPU6050_RANGE_1000_DEG:
    Serial.println("+- 1000 deg/s");
    break;
  case MPU6050_RANGE_2000_DEG:
    Serial.println("+- 2000 deg/s");
    break;
  }

  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
  Serial.print("Filter bandwidth set to: ");
  switch (mpu.getFilterBandwidth()) {
  case MPU6050_BAND_260_HZ:
    Serial.println("260 Hz");
    break;
  case MPU6050_BAND_184_HZ:
    Serial.println("184 Hz");
    break;
  case MPU6050_BAND_94_HZ:
    Serial.println("94 Hz");
    break;
  case MPU6050_BAND_44_HZ:
    Serial.println("44 Hz");
    break;
  case MPU6050_BAND_21_HZ:
    Serial.println("21 Hz");
    break;
  case MPU6050_BAND_10_HZ:
    Serial.println("10 Hz");
    break;
  case MPU6050_BAND_5_HZ:
    Serial.println("5 Hz");
    break;
  }

  Serial.println("");
  delay(100);

}

void loop() 
{
  /* Get new sensor events with the readings */
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);
  //Get Color reading
  marker = color();

  // put your main code here, to run repeatedly:
  //checking for red
  //if(marker == 2 & previous color != 2)
  //leftturn()
  if (marker == 2) 
  {
    setMotor(1,200);
    
    if (marker != last)
    //turn
    {
      Serial.println("Color is Red");
      setMotor(3,200);
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
      setMotor(-1, 200);
       if (marker != last)
       //turn
      {
        Serial.println("Color is Blue");
        setMotor(-3,200);
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