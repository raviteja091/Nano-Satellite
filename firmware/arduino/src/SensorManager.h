#pragma once
#include <SD.h>

namespace SensorManager {
  void begin();
  void logToSD(float uv, uint16_t ir);
}
