#pragma once
#include <WiFi.h>
#include <PubSubClient.h>

namespace Telemetry {
  void begin();
  void sendPacket(float uv, uint16_t ir);
}
