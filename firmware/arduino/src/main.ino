#include <Wire.h>
#include <LTR390.h>
#include <Adafruit_TSL2591.h>
#include <SPI.h>
#include <SD.h>

#include "SensorManager.h"
#include "Telemetry.h"

// I2C sensors
LTR390 uvSensor;
Adafruit_TSL2591 irSensor = Adafruit_TSL2591(2591);

// SD card
const int SD_CS = 4;

// Timing
unsigned long lastSend = 0;
const unsigned long SEND_INTERVAL = 5000;  // ms

void setup() {
  Serial.begin(115200);
  Wire.begin();

  // UV sensor init
  if (!uvSensor.begin()) {
    Serial.println("Error: UV sensor init failed");
  }
  // IR sensor init
  if (!irSensor.begin()) {
    Serial.println("Error: IR sensor init failed");
  }
  // SD init
  if (!SD.begin(SD_CS)) {
    Serial.println("Error: SD init failed");
  }
  SensorManager::begin();
  Telemetry::begin();
}

void loop() {
  // 1. Read sensors
  float uv = uvSensor.readUV();
  uint16_t ir = irSensor.getFullLuminosity();

  // 2. Log to SD
  SensorManager::logToSD(uv, ir);

  // 3. Send telemetry
  if (millis() - lastSend >= SEND_INTERVAL) {
    Telemetry::sendPacket(uv, ir);
    lastSend = millis();
  }

  delay(200);
}
