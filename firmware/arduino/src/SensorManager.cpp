#include "SensorManager.h"
#include <SPI.h>

namespace {
  File logFile;
}

void SensorManager::begin() {
  logFile = SD.open("senslog.csv", FILE_WRITE);
  if (logFile) {
    logFile.println("timestamp,uv,ir");
    logFile.flush();
  }
}

void SensorManager::logToSD(float uv, uint16_t ir) {
  if (!logFile) return;
  unsigned long ts = millis();
  logFile.printf("%lu,%.2f,%u\n", ts, uv, ir);
  logFile.flush();
}
