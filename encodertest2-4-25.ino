#include <Arduino.h>
#include <motor.h>

// Pin configuration
#define INPUT_PIN 18  // Change to your actual pin
#define PULSES_PER_REV 3575  // Number of pulses per revolution
#define MSpin 10 // sleep pin
volatile uint32_t pulseCount = 0;  // Cumulative counter (resets on reboot)
volatile uint32_t revolutionCount = 0;  // Cumulative revolution counter (resets on reboot)

// Interrupt Service Routine (ISR)
void IRAM_ATTR countPulse() {
    pulseCount++;  // Increment count

    if (pulseCount >= PULSES_PER_REV){
      pulseCount = 0;
      revolutionCount++; //Revolution count
    }
}

void setup() {
    Serial.begin(9600);
    pinMode(INPUT_PIN, INPUT_PULLDOWN);  // Configure pin with pull-down resistor
    attachInterrupt(digitalPinToInterrupt(INPUT_PIN), countPulse, RISING);  // Trigger on rising edge
    motorSetup();
    Serial.println("Pulse and Revolution counter initialized.");
    Serial.println("Count starts at 0 (resets on reboot).");

}

void loop() {
    static unsigned long lastPrintTime = 0;
    setMotor(1,200);
    // Print pulse count every second
    if (millis() - lastPrintTime > 1000) {
        lastPrintTime = millis();
        Serial.print("Current Count: ");
        Serial.println(pulseCount);
    }

    // Print revolution count when it increments
    static uint32_t lastRevolutionCount = 0;
    if (revolutionCount > lastRevolutionCount) {
        lastRevolutionCount = revolutionCount;
        Serial.print("Revolution Count: ");
        Serial.println(revolutionCount);
    }
}
