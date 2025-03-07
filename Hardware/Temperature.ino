#include <Wire.h>
#include <Adafruit_MLX90614.h>
#include <WiFi.h>
#include <Firebase_ESP_Client.h>
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

void connectWiFi() {
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    Serial.print("Connecting to WiFi...");
    
    while (WiFi.status() != WL_CONNECTED) {
        Serial.print(".");
        delay(1000);
    }
    
    Serial.println("\nWiFi Connected!");
    Serial.println(WiFi.localIP());
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
    if (!getLocalTime(&timeinfo)) {
        return "Unknown Time";
    }
    char buffer[30];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", &timeinfo);
    return String(buffer);
}

void setup() {
    Serial.begin(115200);
    if (!mlx.begin()) {
        Serial.println("Error connecting to MLX90614. Check wiring!");
        while (1);
    }

    connectWiFi();
    setupFirebase();
    configTime(0, 0, ntpServer);
}

void loop() {
    float ambientTemp = mlx.readAmbientTempC();
    float objectTemp = mlx.readObjectTempC();

    json.clear();
    json.set("timestamp", getTimestamp());
    json.set("ambient_temp", ambientTemp);
    json.set("object_temp", objectTemp);

    Firebase.RTDB.setJSON(&fbdo, "/temperature_readings", &json);

    delay(60000);
}
