#include "Telemetry.h"

static const char* SSID     = "YourSSID";
static const char* PASS     = "YourPass";
static const char* MQTT_BROKER = "192.168.1.100";
static WiFiClient wifiClient;
static PubSubClient mqtt(wifiClient);

void Telemetry::begin() {
  WiFi.begin(SSID, PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
  mqtt.setServer(MQTT_BROKER, 1883);
}

void Telemetry::sendPacket(float uv, uint16_t ir) {
  if (!mqtt.connected()) {
    mqtt.connect("VSAT_Node");
  }
  char payload[64];
  snprintf(payload, sizeof(payload), "{\"uv\":%.2f,\"ir\":%u}", uv, ir);
  mqtt.publish("vsat/sensors", payload);
}
