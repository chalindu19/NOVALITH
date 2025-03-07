#include <WiFi.h>
#include <Firebase_ESP_Client.h>

// WiFi credentials
#define WIFI_SSID "Galaxy s9"
#define WIFI_PASSWORD "839747650"

// Firebase credentials
#define API_KEY "AIzaSyAMwYHbDkd9uQDOjabL-rSwZ_GwkDc3ZJU"
#define DATABASE_URL "https://novalith-c49fb-default-rtdb.firebaseio.com"
#define USER_EMAIL "user@gmail.com"
#define USER_PASSWORD "User@123"

// Firebase objects
FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

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

void tokenStatusCallback(FirebaseAuthTokenInfo info) {
    Serial.printf("Token Info: type = %s, status = %s\n",
                  info.auth_type.c_str(), info.status.c_str());
}

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

// Function to simulate temperature reading
float readTemperature() {
    return 25.0 + (rand() % 10);  // Simulating a value between 25-35°C
}

void setup() {
    Serial.begin(115200);
    connectToWiFi();
    connectToFirebase();
}

void loop() {
    float temperature = readTemperature();
    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.println("°C");

    delay(5000);
}
