#include "movement.h"
#include <Arduino.h>
#include <motor.h>  // Optional if you call setMotor inside toTheta

Adafruit_MPU6050 mpu;

float x;
float y;
float newtheta;
float current;
float goalHigh;
float goalLow;

void AccelSetup() {
  while (!Serial)
    delay(10);

  Serial.println("Adafruit MPU6050 test!");

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
    case MPU6050_RANGE_2_G: Serial.println("+-2G"); break;
    case MPU6050_RANGE_4_G: Serial.println("+-4G"); break;
    case MPU6050_RANGE_8_G: Serial.println("+-8G"); break;
    case MPU6050_RANGE_16_G: Serial.println("+-16G"); break;
  }

  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  Serial.print("Gyro range set to: ");
  switch (mpu.getGyroRange()) {
    case MPU6050_RANGE_250_DEG: Serial.println("+- 250 deg/s"); break;
    case MPU6050_RANGE_500_DEG: Serial.println("+- 500 deg/s"); break;
    case MPU6050_RANGE_1000_DEG: Serial.println("+- 1000 deg/s"); break;
    case MPU6050_RANGE_2000_DEG: Serial.println("+- 2000 deg/s"); break;
  }

  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
  Serial.print("Filter bandwidth set to: ");
  switch (mpu.getFilterBandwidth()) {
    case MPU6050_BAND_260_HZ: Serial.println("260 Hz"); break;
    case MPU6050_BAND_184_HZ: Serial.println("184 Hz"); break;
    case MPU6050_BAND_94_HZ: Serial.println("94 Hz"); break;
    case MPU6050_BAND_44_HZ: Serial.println("44 Hz"); break;
    case MPU6050_BAND_21_HZ: Serial.println("21 Hz"); break;
    case MPU6050_BAND_10_HZ: Serial.println("10 Hz"); break;
    case MPU6050_BAND_5_HZ: Serial.println("5 Hz"); break;
  }

  Serial.println("");
  delay(100);
}

float getTheta() {
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  x = a.acceleration.x;
  y = a.acceleration.y;

  float theta = atan2(y, x) * 180.0 / PI;

  if (theta < 0) {
    newtheta = 360 + theta;
    Serial.print("x accel: "); Serial.print(x, 3);
    Serial.print(" y accel: "); Serial.print(y, 3);
    Serial.print(" Theta (θ): "); Serial.print(theta);
    Serial.print(" New Theta (θ): "); Serial.println(newtheta);
    delay(500);
    return newtheta;
  } else {
    Serial.print("x accel: "); Serial.print(x, 3);
    Serial.print(" y accel: "); Serial.print(y, 3);
    Serial.print(" Theta (θ): "); Serial.println(theta);
    delay(500);
    return theta;
  }
}

void toTheta(float goal) {
  goalHigh = goal + 5;
  goalLow = goal - 5;

  while (current > goalHigh || current < goalLow) {
    Serial.println("NOT IN RANGE");
    current = getTheta();
    setMotor(2, 100); // Uncomment if needed
    delay(10);
  }
  setMotor(0,0);
}

void toThetaPID(float goal) {
  float Kp = 2.0;
  float Ki = 0.01;
  float Kd = 1.0;

  float error, previousError = 0;
  float integral = 0;
  float derivative;
  float output;

  goalHigh = goal + 3;
  goalLow = goal - 3;

  unsigned long lastTime = millis();

  while (true) {
    current = getTheta();
    error = goal - current;

    // Handle angle wraparound (e.g., 359 -> 0)
    if (error > 180) error -= 360;
    if (error < -180) error += 360;

    if (abs(error) < 3) {
      setMotor(0, 0); // Stop motors
      break;
    }

    unsigned long currentTime = millis();
    float deltaTime = (currentTime - lastTime) / 1000.0;  // in seconds
    lastTime = currentTime;

    integral += error * deltaTime;
    derivative = (error - previousError) / deltaTime;
    previousError = error;

    output = Kp * error + Ki * integral + Kd * derivative;

    // Clamp output
    int pwmVal = constrain(abs(output), 50, 255);
    int direction = (error > 0) ? 2 : -2;

    setMotor(direction, pwmVal);

    Serial.print("Error: "); Serial.print(error);
    Serial.print(" PWM: "); Serial.println(pwmVal);

    delay(100);
  }
}