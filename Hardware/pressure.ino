#include <WiFi.h>
#include <Firebase_ESP_Client.h>
#include <Wire.h>
#include <Adafruit_MS5607.h>

#define WIFI_SSID "Galaxy s9"
#define WIFI_PASSWORD "839747650"
#define API_KEY "AIzaSyAMwYHbDkd9uQDOjabL-rSwZ_GwkDc3ZJU"
#define USER_EMAIL "user@gmail.com"
#define USER_PASSWORD "User@123"
#define DATABASE_URL "https://novalith-c49fb-default-rtdb.firebaseio.com"

FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;
Adafruit_MS5607 pressureSensor;

String userUID;

void tokenStatusCallback(TokenInfo info) {
    Serial.printf("Token Info: type = %s, status = %s\n", 
                  info.token_type.c_str(), 
                  info.status.c_str());
}

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
        Serial.println("\nFailed to get User UID. Restarting...");
        ESP.restart();
    }

    userUID = auth.token.uid.c_str();
    Serial.print("\nUser UID: ");
    Serial.println(userUID);
}

void initPressureSensor() {
    Serial.println("Initializing Pressure Sensor...");
    if (!pressureSensor.begin()) {
        Serial.println("Failed to initialize pressure sensor! Restarting...");
        delay(3000);
        ESP.restart();
    }
    Serial.println("Pressure Sensor Initialized Successfully!");
}

void sendDataToFirebase(float pressure, float temperature) {
    String path = "/users/" + userUID + "/sensor_data";

    FirebaseJson json;
    json.set("pressure", pressure);
    json.set("temperature", temperature);
    
    if (Firebase.RTDB.setJSON(&fbdo, path.c_str(), &json)) {
        Serial.println("Data sent to Firebase successfully.");
    } else {
        Serial.print("Firebase Error: ");
        Serial.println(fbdo.errorReason());
    }
}

void readPressureSensor() {
    float pressure = pressureSensor.readPressure();
    float temperature = pressureSensor.readTemperature();

    if (isnan(pressure) || isnan(temperature)) {
        Serial.println("Error: Failed to read sensor data.");
        return;
    }

    Serial.print("Pressure: ");
    Serial.print(pressure);
    Serial.println(" mbar");

    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.println(" °C");

    sendDataToFirebase(pressure, temperature);

    delay(5000); // Upload data every 5 seconds
}

void setup() {
    Serial.begin(115200);
    initializeNetwork();
    initPressureSensor();
}

void loop() {
    readPressureSensor();
}
