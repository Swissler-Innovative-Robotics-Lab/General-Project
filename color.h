#pragma once

#include <Arduino.h>
#include "Adafruit_TCS34725.h"

// ==== PIN DEFINITIONS ====
#define PIN_BUTTON  5
#define PIN_LED     13

// ==== THRESHOLDS ====
#define THRESHOLD_WHITE     3700
#define THRESHOLD_BLACK     800
#define THRESH_WHITE_OFFSET 500
#define THRESH_BLACK_OFFSET 200

// ==== HUE RANGES ====
#define RED_MIN_0     0
#define YELLOW_MIN    0.125
#define GREEN_MIN     0.25
#define CYAN_MIN      0.35
#define BLUE_MIN      0.53
#define MAGENTA_MIN   0.7
#define RED_MIN_1     0.85

// ==== COLOR LABELS ====
#define COLOR_WHITE     0
#define COLOR_BLACK     1
#define COLOR_RED       2
#define COLOR_YELLOW    3
#define COLOR_GREEN     4
#define COLOR_CYAN      5
#define COLOR_BLUE      6
#define COLOR_MAGENTA   7

// ==== Global Objects ====
extern Adafruit_TCS34725 color_sensor;
extern uint16_t max_brightness;
extern uint16_t min_brightness;

// ==== Function Prototypes ====
void SensorSetup();
float calcHue(float red, float green, float blue);
uint8_t determineColor(float hue, uint16_t brightness, uint16_t thresh_white, uint16_t thresh_black);
uint8_t color();
void calcHSL();
