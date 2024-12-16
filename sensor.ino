// Include library for ESP8266
#include <ESP8266WiFi.h>

// Pin definitions
#define LDR_PIN A0 // Pin analog untuk LDR
#define LED_PIN 5  // GPIO5 (D1) untuk modul LED merah

// Light threshold
const int lightThreshold = 500; // Nilai ambang untuk cahaya (0-1023)
const int sampleCount = 10;    // Jumlah sampel untuk averaging

void setup() {
  // Initialize serial communication
  Serial.begin(115200);

  // Configure LED pin as output
  pinMode(LED_PIN, OUTPUT);

  // Print initialization message
  Serial.println("LDR monitoring started...");
}

void loop() {
  // Read multiple values from LDR and calculate the average
  int ldrSum = 0;
  for (int i = 0; i < sampleCount; i++) {
    ldrSum += analogRead(LDR_PIN);
    delay(10); // Small delay between readings
  }
  int ldrValue = ldrSum / sampleCount;

  // Print LDR value to Serial Monitor
  Serial.print("LDR Value (averaged): ");
  Serial.println(ldrValue);

  // Control LED based on light threshold
  if (ldrValue < lightThreshold) {
    digitalWrite(LED_PIN, HIGH); // Turn on LED
  } else {
    digitalWrite(LED_PIN, LOW); // Turn off LED
  }LDR Value (averaged): 236
LDR Value (averaged): 162
LDR Value (averaged): 222
LDR Value (averaged): 245
LDR Value (averaged): 236
LDR Value (averaged): 61
LDR Value (averaged): 237
LDR Value (averaged): 237
LDR Value (averaged): 233
LDR Value (averaged): 237
LDR Value (averaged): 247

  // Delay to stabilize readings
  delay(500);
}
