#include <WiFi.h>
#include <Firebase_ESP_Client.h>

#define WIFI_SSID "Galaxy s9"
#define WIFI_PASSWORD "839747650"
#define API_KEY "AIzaSyAMwYHbDkd9uQDOjabL-rSwZ_GwkDc3ZJU"
#define USER_EMAIL "user@gmail.com"
#define USER_PASSWORD "User@123"
#define DATABASE_URL "https://novalith-c49fb-default-rtdb.firebaseio.com"

// Firebase setup
FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

void tokenStatusCallback(TokenInfo info) {
    Serial.printf("Token Info: type = %s, status = %s\n", 
                  info.token_type.c_str(), 
                  info.status.c_str());
}

// WiFi initialization
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

// Firebase initialization
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

// FSR402 sensor setup
#define FSR_PIN A0  // Analog pin for FSR sensor

void setup() {
    Serial.begin(115200);
    initializeNetwork();  // Connects to WiFi and Firebase
    pinMode(FSR_PIN, INPUT);
}

// Function to read pressure from FSR402
int readPressure() {
    int fsrValue = analogRead(FSR_PIN);  // Read raw analog value
    int pressure = map(fsrValue, 0, 4095, 0, 100);  // Approximate pressure (0-100 scale)
    Serial.print("FSR Raw Value: ");
    Serial.print(fsrValue);
    Serial.print(" | Pressure Estimate: ");
    Serial.println(pressure);
    return pressure;
}

// Upload sensor data to Firebase
void uploadPressureToFirebase(int pressure) {
    String path = "/sensorData/pressure";
    if (Firebase.RTDB.setInt(&fbdo, path, pressure)) {
        Serial.println("✅ Data uploaded to Firebase successfully.");
    } else {
        Serial.println("❌ Firebase upload failed: " + fbdo.errorReason());
    }
}

void loop() {
    int pressure = readPressure();  // Get pressure reading
    uploadPressureToFirebase(pressure);  // Upload to Firebase
    delay(5000);  // Wait 5 seconds before next reading
}
