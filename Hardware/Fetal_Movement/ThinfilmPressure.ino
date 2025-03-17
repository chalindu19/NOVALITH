#include <WiFi.h>
#include <Firebase_ESP_Client.h>
#include <Wire.h>
#include <Adafruit_MS5607.h>
#include <time.h>  // For timestamps

// WiFi Credentials
#define WIFI_SSID "Galaxy s9"
#define WIFI_PASSWORD "839747650"

// Firebase Credentials
#define API_KEY "AIzaSyAMwYHbDkd9uQDOjabL-rSwZ_GwkDc3ZJU"
#define USER_EMAIL "user@gmail.com"
#define USER_PASSWORD "User@123"
#define DATABASE_URL "https://novalith-c49fb-default-rtdb.firebaseio.com"

FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;
Adafruit_MS5607 pressureSensor;

String userUID;
unsigned long lastUploadTime = 0;
const long uploadInterval = 5000;  // Upload every 5 seconds

// Firebase Token Status Callback
void tokenStatusCallback(TokenInfo info) {
    Serial.printf("Token Info: type = %s, status = %s\n", 
                  info.token_type.c_str(), 
                  info.status.c_str());
}

// Initialize WiFi Connection with Retry
void initWiFi() {
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    Serial.println("Connecting to WiFi...");
    int attempts = 0;
    while (WiFi.status() != WL_CONNECTED && attempts < 20) {
        Serial.print('.');
        delay(1000);
        attempts++;
    }

    if (WiFi.status() == WL_CONNECTED) {
        Serial.println("\nConnected to WiFi!");
        Serial.println(WiFi.localIP());
    } else {
        Serial.println("\nFailed to connect to WiFi. Restarting...");
        ESP.restart();
    }
}

// Initialize Firebase Authentication with Retry
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
    int attempts = 0;
    while (auth.token.uid == "" && attempts < 20) {
        Serial.print('.');
        delay(1000);
        attempts++;
    }

    if (auth.token.uid == "") {
        Serial.println("\nFailed to get User UID. Retrying...");
        return;  // Don't restart, allow retries
    }

    userUID = auth.token.uid.c_str();
    Serial.print("\nUser UID: ");
    Serial.println(userUID);
}

// Get Current Timestamp
String getTimestamp() {
    time_t now = time(nullptr);
    struct tm *timeinfo = localtime(&now);

    char buffer[30];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", timeinfo);
    return String(buffer);
}

// Initialize Pressure Sensor with Auto-Retry
void initPressureSensor() {
    Serial.println("Initializing Pressure Sensor...");
    int attempts = 0;
    while (!pressureSensor.begin() && attempts < 3) {
        Serial.println("Failed to initialize pressure sensor. Retrying...");
        delay(2000);
        attempts++;
    }

    if (attempts == 3) {
        Serial.println("Error: Could not initialize pressure sensor!");
    } else {
        Serial.println("Pressure Sensor Initialized Successfully!");
    }
}

// Send Data to Firebase with Timestamp
void sendDataToFirebase(float pressure, float temperature) {
    if (WiFi.status() != WL_CONNECTED) {
        Serial.println("WiFi Disconnected! Skipping Firebase upload...");
        return;
    }

    if (userUID == "") {
        Serial.println("User UID not available. Skipping upload...");
        return;
    }

    String path = "/users/" + userUID + "/sensor_data";

    FirebaseJson json;
    json.set("timestamp", getTimestamp());
    json.set("pressure", pressure);
    json.set("temperature", temperature);
    
    if (Firebase.RTDB.setJSON(&fbdo, path.c_str(), &json)) {
        Serial.println("Data sent to Firebase successfully.");
    } else {
        Serial.print("Firebase Error: ");
        Serial.println(fbdo.errorReason());
    }
}

// Read Pressure Sensor Data & Handle Errors
void readPressureSensor() {
    float pressure = pressureSensor.readPressure();
    float temperature = pressureSensor.readTemperature();

    if (isnan(pressure) || isnan(temperature)) {
        Serial.println("Error: Failed to read sensor data. Retrying sensor initialization...");
        initPressureSensor();
        return;
    }

    Serial.print("Pressure: ");
    Serial.print(pressure);
    Serial.println(" mbar");

    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.println(" °C");

    sendDataToFirebase(pressure, temperature);
}

void setup() {
    Serial.begin(115200);
    initializeNetwork();
    initPressureSensor();
}

void loop() {
    if (millis() - lastUploadTime >= uploadInterval) {
        readPressureSensor();
        lastUploadTime = millis();
    }
}
