#include <WiFi.h>
#include <Firebase_ESP_Client.h>
#include <Wire.h>
#include <Adafruit_MS5607.h>  // Added pressure sensor library

#define WIFI_SSID "Galaxy s9"
#define WIFI_PASSWORD "839747650"
#define API_KEY "AIzaSyAMwYHbDkd9uQDOjabL-rSwZ_GwkDc3ZJU"
#define USER_EMAIL "user@gmail.com"
#define USER_PASSWORD "User@123"
#define DATABASE_URL "https://novalith-c49fb-default-rtdb.firebaseio.com"

FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;
Adafruit_MS5607 pressureSensor; // Added pressure sensor object

void tokenStatusCallback(TokenInfo info) {
    Serial.printf("Token Info: type = %s, status = %s\n", 
                  info.token_type.c_str(), 
                  info.status.c_str());
}

void initWiFi() {
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    Serial.println("Connecting to WiFi...");
    while (WiFi.status() != WL_CONNECTED) {
        Serial.print('.');
        delay(1000);
    }
    Serial.println("\nConnected to WiFi!");
    Serial.println(WiFi.localIP());
}

void initializeNetwork() {
    initWiFi();
    config.api_key = API_KEY;
    auth.user.email = USER_EMAIL;
    auth.user.password = USER_PASSWORD;
    config.database_url = DATABASE_URL;

    Firebase.reconnectWiFi(true);
    fbdo.setResponseSize(4096);
    config.token_status_callback = tokenStatusCallback;
    config.max_token_generation_retry = 5;

    Firebase.begin(&config, &auth);

    Serial.println("Getting User UID...");
    while (auth.token.uid == "") {
        Serial.print('.');
        delay(1000);
    }

    Serial.print("\nUser UID: ");
    Serial.println(auth.token.uid.c_str());
}

// Initialize the pressure sensor
void initPressureSensor() {
    Serial.println("Initializing Pressure Sensor...");
    if (!pressureSensor.begin()) {
        Serial.println("Failed to initialize pressure sensor!");
        while (1);
    }
    Serial.println("Pressure Sensor Initialized Successfully!");
}

void setup() {
    Serial.begin(115200);
    initializeNetwork();
    initPressureSensor();
}

void loop() {
    // Placeholder for sensor data processing
}
