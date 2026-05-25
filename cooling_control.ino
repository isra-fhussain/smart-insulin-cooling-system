#include <Arduino.h>

const int FAN_PIN = 3;
const int LED_PIN = 9;

// ── Insulin Protection Thresholds ─────────────────────────────
const float TEMP_THRESHOLD_HIGH = 30.0; // Fan ON
const float TEMP_THRESHOLD_LOW  = 28.0; // Fan OFF

bool isFanOn = false;

void setup() {
  pinMode(FAN_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(9600);

  Serial.println("--- Testing Mode: Hard-Coded Temperature ---");
}

void loop() {
  // ── MANUALLY CHANGE THIS VALUE TO TEST ──────────────────────
  float tempC = 45.0; // <--- Change this number to 25.0, 30.0, etc.
  // ────────────────────────────────────────────────────────────

  // Logic: Turn ON at 30°C, stay ON until drops below 28°C (hysteresis buffer)
  if (tempC >= TEMP_THRESHOLD_HIGH) {
    isFanOn = true;
  } else if (tempC <= TEMP_THRESHOLD_LOW) {
    isFanOn = false;
  }

  // Update hardware
  digitalWrite(FAN_PIN, isFanOn ? HIGH : LOW);
  digitalWrite(LED_PIN, isFanOn ? HIGH : LOW);

  // Status Printout
  Serial.print("Test Temperature: ");
  Serial.print(tempC);
  Serial.print(" C | Fan Status: ");
  Serial.println(isFanOn ? "ON (Cooling)" : "OFF (Safe)");

  delay(2000); // Slow down the loop for easier reading
}
