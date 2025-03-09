#include <Wire.h>
#include <Adafruit_MLX90614.h>
#include <WiFi.h>
#include <Firebase_ESP_Client.h>
#include <ArduinoOTA.h>
#include "time.h"

// WiFi Credentials
#define WIFI_SSID "YourWiFiName"
#define WIFI_PASSWORD "YourWiFiPassword"

// Firebase Credentials
#define API_KEY "YourFirebaseAPIKey"
#define DATABASE_URL "https://your-firebase-database-url.firebaseio.com"
#define USER_EMAIL "user@gmail.com"
#define USER_PASSWORD "User@123"

// Firebase Objects
FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;
FirebaseJson json;

// MLX90614 Sensor Object
Adafruit_MLX90614 mlx = Adafruit_MLX90614();

// NTP Time Configuration
const char* ntpServer = "pool.ntp.org";
struct tm timeinfo;

// OTA Update LED
#define OTA_LED 2  

// Previous temperature readings for optimization
float previousAmbientTemp = -999;
float previousObjectTemp = -999;

void connectWiFi() {
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    WiFi.setSleep(true);
    Serial.print("Connecting to WiFi...");
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.print(".");
    }
    Serial.println("\nWiFi Connected!");
}

void setupFirebase() {
    config.api_key = API_KEY;
    auth.user.email = USER_EMAIL;
    auth.user.password = USER_PASSWORD;
    config.database_url = DATABASE_URL;

    Firebase.begin(&config, &auth);
    Firebase.reconnectWiFi(true);
    Serial.println("Connected to Firebase");
}

String getTimestamp() {
    if (!getLocalTime(&timeinfo)) return "Unknown Time";
    char buffer[30];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", &timeinfo);
    return String(buffer);
}

void setupOTA() {
    ArduinoOTA.setHostname("ESP32_TemperatureSensor");

    ArduinoOTA.onStart([]() {
        Serial.println("OTA Update Started...");
    });
    
    ArduinoOTA.onEnd([]() {
        Serial.println("\nOTA Update Completed!");
    });

    ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
        Serial.printf("OTA Progress: %u%%\r", (progress / (total / 100)));
        digitalWrite(OTA_LED, (progress / (total / 100)) % 2);
    });

    ArduinoOTA.onError([](ota_error_t error) {
        Serial.printf("OTA Error[%u]\n", error);
    });

    ArduinoOTA.begin();
    Serial.println("OTA Ready!");
}

void setup() {
    Serial.begin(115200);
    pinMode(OTA_LED, OUTPUT);
    digitalWrite(OTA_LED, LOW);

    if (!mlx.begin()) {
        Serial.println("Error connecting to MLX90614. Check wiring!");
        while (1);
    }

    connectWiFi();
    setupFirebase();
    setupOTA();
    configTime(0, 0, ntpServer);
}

void loop() {
    ArduinoOTA.handle();  // OTA Update Handling

    float ambientTemp = mlx.readAmbientTempC();
    float objectTemp = mlx.readObjectTempC();

    if (abs(ambientTemp - previousAmbientTemp) > 1.0 || abs(objectTemp - previousObjectTemp) > 1.0) {
        previousAmbientTemp = ambientTemp;
        previousObjectTemp = objectTemp;

        json.clear();
        json.set("timestamp", getTimestamp());
        json.set("ambient_temp", ambientTemp);
        json.set("object_temp", objectTemp);

        if (Firebase.RTDB.setJSON(&fbdo, "/temperature_readings", &json)) {
            Serial.println("✅ Data Sent to Firebase Successfully!");
        } else {
            Serial.print("❌ Firebase Error: ");
            Serial.println(fbdo.errorReason());
        }
    }
    delay(60000);
}