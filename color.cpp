#include "color.h"
#include <math.h>

// ==== Sensor Object and Globals ====
Adafruit_TCS34725 color_sensor = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);
uint16_t max_brightness = 0;
uint16_t min_brightness = 65000;

void SensorSetup() {
  Serial.begin(115200);

  pinMode(PIN_LED, OUTPUT);
  digitalWrite(PIN_LED, LOW);

  pinMode(PIN_BUTTON, INPUT_PULLUP);
  delay(3000);
  Serial.println("Press Button");
}

float calcHue(float red, float green, float blue) {
  float R = red;
  float G = green;
  float B = blue;

  float hue;

  if (R >= G && G >= B) {
    // Orange Region
    hue = 60.0 * ((G - B) / (R - B));
  } else if (G >= R && R >= B) {
    // Chartreuse Region
    hue = 60.0 * (2.0 - (R - B) / (G - B));
  } else if (G >= B && B >= R) {
    // Spring Green Region
    hue = 60.0 * (2.0 + (B - R) / (G - R));
  } else if (B >= G && G >= R) {
    // Azure Region
    hue = 60.0 * (4.0 - (G - R) / (B - R));
  } else if (B >= R && R >= G) {
    // Violet Region
    hue = 60.0 * (4.0 + (R - G) / (B - G));
  } else if (R >= B && B >= G) {
    // Rose Region
    hue = 60.0 * (6.0 - (B - G) / (R - G));
  } else {
    hue = 0.0; // Fallback for any undefined edge cases
  }

  // Normalize to [0, 1] for use in color wheels or mapping
  hue = fmodf(hue / 360.0f, 1.0f);
  if (hue < 0) hue += 1.0f; // Ensure it's non-negative
  //Serial.print(" "); Serial.print(hue);
  return hue;
}

uint8_t determineColor(float hue, uint16_t brightness, uint16_t thresh_white, uint16_t thresh_black) {
  if (brightness > thresh_white) return COLOR_WHITE;
  if (brightness < thresh_black) return COLOR_BLACK;

  if (hue > RED_MIN_1) return COLOR_RED;
  if (hue > MAGENTA_MIN) return COLOR_MAGENTA;
  if (hue > BLUE_MIN) return COLOR_BLUE;
  if (hue > CYAN_MIN) return COLOR_CYAN;
  if (hue > GREEN_MIN) return COLOR_GREEN;
  if (hue > YELLOW_MIN) return COLOR_YELLOW;
  return COLOR_RED;  // fallback
}

uint8_t color() {
  uint16_t r, g, b, c;
  color_sensor.getRawData(&r, &g, &b, &c);
  //Serial.print(r/255.0); Serial.print(","); Serial.print(g/255.0); Serial.print(","); Serial.print(b/255.0); Serial.print(","); Serial.println(c/255.0);
  min_brightness = min(min_brightness, c);
  max_brightness = max(max_brightness, c);

  float hue = calcHue((float)r, (float)g, (float)b);

  return determineColor(hue, c, max_brightness - THRESH_WHITE_OFFSET, min_brightness + THRESH_BLACK_OFFSET);
}

void calcHSL() {
  float hue;
  uint16_t r, g, b, c;
  color_sensor.getRawData(&r, &g, &b, &c);
  // Normalize RGB using clear (total light) value
  float R = (float)r / (float)c;
  float G = (float)g / (float)c;
  float B = (float)b / (float)c;
  //Serial.print("RGB Vals: "); Serial.print(R); Serial.print(","); Serial.print(G); Serial.print(","); Serial.print(B); Serial.print(","); Serial.println(c);
  // HUE using Preucil logic (same as calcHue from earlier)
  hue = calcHue(R, G, B);  // already normalized to [0, 1]

  // Lightness from clear
  float maxRGB = fmax(fmax(R, G), B);
  float minRGB = fmin(fmin(R, G), B);
  float lightness = (maxRGB + minRGB) / 2.0;  // Lightness ∈ [0, 1]
  //Serial.print(" "); Serial.print(lightness); 

  // Saturation
  float delta = maxRGB - minRGB;
  float saturation;
  if (delta == 0.0f) {
    saturation = 0.0f;
  } else {
    saturation = delta / (1.0f - fabs(2.0f * lightness - 1.0f));
  }
  //Serial.print(" ");
  //Serial.println(saturation);

  //new serial transfer for .csv files
  if (isnan(hue)) hue = 0.0;
  if (hue < 0.0) hue += 1.0;
  if (hue > 1.0) hue -= 1.0;
  
  Serial.print(R); Serial.print(',');
  Serial.print(G); Serial.print(',');
  Serial.print(B); Serial.print(',');
  Serial.print(hue, 4); Serial.print(',');
  Serial.print(lightness, 4); Serial.print(',');
  Serial.println(saturation, 4);

  delay(100);  // Limit frequency

}
