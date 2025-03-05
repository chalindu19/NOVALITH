#include <Wifi.h>
#include <Firebase_ESP_Client.h>
#include "DHT.h"

#define READ_INTERVAL 60000  // Interval to send data to Firebase in milliseconds

unsigned long lastTime = 0;
float pressure = 0.0;
float temperature = 0.0; 
void initWiFi() {
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    Serial.print("Connecting to WiFi ..");
    while (WiFi.status() != WL_CONNECTED) {
      Serial.print('.');
      delay(1000);
    }
    Serial.println("Connected! IP Address: ");
    Serial.println(WiFi.localIP());
  }  

