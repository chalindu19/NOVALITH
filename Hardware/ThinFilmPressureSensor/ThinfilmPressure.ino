#include <WiFi.h>
#include <Firebase_ESP_Client.h>
#include <time.h>

#define WIFI_SSID "Galaxy s9"
#define WIFI_PASSWORD "839747650"
#define API_KEY "AIzaSyAMwYHbDkd9uQDOjabL-rSwZ_GwkDc3ZJU"
#define USER_EMAIL "user@gmail.com"
#define USER_PASSWORD "User@123"
#define DATABASE_URL "https://novalith-c49fb-default-rtdb.firebaseio.com"

FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

#define PRESSURE_SENSOR_PIN 34  

unsigned long lastUploadTime = 0;
const int uploadInterval = 5000;  

// Function to get timestamp
String getTimestamp() {
    time_t now;
    struct tm timeinfo;
    if (!getLocalTime(&timeinfo)) {
        Serial.println("Failed to obtain time");
        return "Unknown";
    }
    char buffer[30];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", &timeinfo);
    return String(buffer);
}

int readPressureSensor() {
    int pressureValue = analogRead(PRESSURE_SENSOR_PIN);
    Serial.print("Pressure Sensor Reading: ");
    Serial.println(pressureValue);
    return pressureValue;
}

// Upload sensor data to Firebase
void uploadData(int pressure) {
    if (Firebase.ready()) {
        String path = "/SensorData/" + String(auth.token.uid);
        
        FirebaseJson json;
        json.set("pressure", pressure);
        json.set("timestamp", getTimestamp());

        if (Firebase.updateNode(fbdo, path, json)) {
            Serial.println("Data uploaded successfully!");
        } else {
            Serial.print("Firebase upload failed: ");
            Serial.println(fbdo.errorReason());
        }
    } else {
        Serial.println("Firebase not ready, skipping upload...");
    }
}

void setup() {
    Serial.begin(115200);
    initWiFi();
    initializeFirebase();
}

void loop() {
    unsigned long currentTime = millis();

    if (currentTime - lastUploadTime >= uploadInterval) {
        lastUploadTime = currentTime;
        
        int pressure = readPressureSensor();
        uploadData(pressure);
    }
}
