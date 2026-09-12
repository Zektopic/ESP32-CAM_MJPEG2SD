#include <WiFi.h>

const char* candidates[] = {
    "Repeater_2.4G_FA12D4",
    "OpenWrt_2",
    "OpenWrt",
    "SLT-Fiber-2.4G_6f48"
};

const char* pass = "dash9343";

void onWiFiEvent(WiFiEvent_t event, WiFiEventInfo_t info) {
    switch(event) {
        case ARDUINO_EVENT_WIFI_STA_START:
            Serial.println("[WiFi] STA Started");
            break;
        case ARDUINO_EVENT_WIFI_STA_CONNECTED:
            Serial.println("[WiFi] Connected to AP!");
            break;
        case ARDUINO_EVENT_WIFI_STA_GOT_IP:
            Serial.printf("[WiFi] Got IP: %s\n", WiFi.localIP().toString().c_str());
            break;
        case ARDUINO_EVENT_WIFI_STA_DISCONNECTED:
            Serial.printf("[WiFi] Disconnected, reason: %d\n", info.wifi_sta_disconnected.reason);
            break;
        default:
            break;
    }
}

void setup() {
    Serial.begin(115200);
    delay(1000);
    Serial.println("\n\n=== Testing Candidate SSIDs ===");
    WiFi.onEvent(onWiFiEvent);

    for (int i = 0; i < 4; i++) {
        Serial.printf("\n--- Trying SSID: '%s' ---\n", candidates[i]);
        WiFi.disconnect(true);
        delay(500);
        WiFi.mode(WIFI_STA);
        WiFi.begin(candidates[i], pass);

        unsigned long start = millis();
        while (WiFi.status() != WL_CONNECTED && millis() - start < 10000) {
            Serial.print(".");
            delay(500);
        }
        Serial.println();

        if (WiFi.status() == WL_CONNECTED) {
            Serial.printf(">>> SUCCESS on SSID '%s'! <<<\n", candidates[i]);
            Serial.printf("IP: %s, GW: %s, RSSI: %d dBm\n", 
                WiFi.localIP().toString().c_str(), WiFi.gatewayIP().toString().c_str(), (int)WiFi.RSSI());
            break;
        } else {
            Serial.printf("Failed on SSID '%s'\n", candidates[i]);
        }
    }
}

void loop() {
    if (WiFi.status() == WL_CONNECTED) {
        Serial.printf("Online! IP: %s\n", WiFi.localIP().toString().c_str());
    }
    delay(5000);
}
