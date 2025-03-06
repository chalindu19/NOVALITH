#include <WiFi.h>
#include <Firebase_ESP_Client.h>
#include <Wire.h>  // For I2C communication (if needed for the temperature sensor)

// Replace these with your actual WiFi and Firebase credentials
#define WIFI_SSID "Galaxy s9"
#define WIFI_PASSWORD "839747650"
#define API_KEY "AIzaSyAMwYHbDkd9uQDOjabL-rSwZ_GwkDc3ZJU"
#define DATABASE_URL "https://novalith-c49fb-default-rtdb.firebaseio.com"
#define USER_EMAIL "user@gmail.com"
#define USER_PASSWORD "User@123"

// Firebase objects
FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

// Function to connect to WiFi
void connectToWiFi() {
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    Serial.print("Connecting to WiFi: ");
    Serial.println(WIFI_SSID);

    while (WiFi.status() != WL_CONNECTED) {
        Serial.print('.');
        delay(1000);
    }
    Serial.println("\nConnected to WiFi!");
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());
}

// Token callback function for Firebase authentication
void tokenStatusCallback(FirebaseAuthTokenInfo info) {
    Serial.printf("Token Info: type = %s, status = %s\n",
                  info.auth_type.c_str(), info.status.c_str());
}

// Function to connect to Firebase
void connectToFirebase() {
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

// Function to read temperature (Replace with your actual sensor code)
float readTemperature() {
    // Dummy temperature value for testing
    float tempC = 25.0 + (rand() % 10);  // Random value between 25-35°C
    return tempC;
}

void setup() {
    Serial.begin(115200);
    
    connectToWiFi();      // Connect to WiFi
    connectToFirebase();  // Connect to Firebase
}

void loop() {
    float temperature = readTemperature();
    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.println("°C");

    // Push temperature data to Firebase
    if (Firebase.RTDB.setFloat(&fbdo, "/temperature/value", temperature)) {
        Serial.println("Temperature uploaded to Firebase.");
    } else {
        Serial.print("Firebase error: ");
        Serial.println(fbdo.errorReason());
    }

    delay(5000); // Upload temperature every 5 seconds
}
