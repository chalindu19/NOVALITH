#ifndef WIFI_SETUP_H
#define WIFI_SETUP_H

#include <WiFi.h>

#define WIFI_SSID "Galaxy S9"
#define WIFI_PASSWORD "839747650"

void initWiFi() {
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    Serial.print("Connecting to WiFi ..");
    while (WiFi.status() != WL_CONNECTED) {
        Serial.print('.');
        delay(1000);
    }
    Serial.println(WiFi.localIP());
}

#endif
