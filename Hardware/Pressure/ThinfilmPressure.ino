#include <WiFi.h>
#include <Firebase_ESP_Client.h>

#define WIFI_SSID "Galaxy s9"
#define WIFI_PASSWORD "839747650"
#define API_KEY "AIzaSyAMwYHbDkd9uQDOjabL-rSwZ_GwkDc3ZJU"
#define USER_EMAIL "user@gmail.com"
#define USER_PASSWORD "User@123"
#define DATABASE_URL "https://novalith-c49fb-default-rtdb.firebaseio.com"

FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

#define PRESSURE_SENSOR_PIN 34  // ADC pin for the FSR402 sensor

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

void initializeFirebase() {
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

// New Function: Reads pressure sensor data
int readPressureSensor() {
    int pressureValue = analogRead(PRESSURE_SENSOR_PIN);
    Serial.print("Pressure Sensor Reading: ");
    Serial.println(pressureValue);
    return pressureValue;
}

void setup() {
    Serial.begin(115200);
    initWiFi();
    initializeFirebase();
}

void loop() {
    readPressureSensor();  // Reads the sensor value and prints it
    delay(5000);  // Delay for 5 seconds before the next reading
}
