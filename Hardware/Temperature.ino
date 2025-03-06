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

void initWiFi() {
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to WiFi ..");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(1000);
  }
  Serial.println(WiFi.localIP());
  Serial.println();
}
// compile the code.
void tokenStatusCallback(FirebaseAuthTokenInfo info) {
  Serial.printf("Token Info: type = %s, status = %s\n",
                info.auth_type.c_str(), info.status.c_str());
}

void setup() {
  Serial.begin(9600);
  initWiFi();

  // Assign the API key
  config.api_key = API_KEY;

  
  auth.user.email = "user@gmail";
  auth.user.password = "user@123";

  
  config.database_url = DATABASE_URL;

  Firebase.reconnectWiFi(true);
  fbdo.setResponseSize(4096);


  config.token_status_callback = tokenStatusCallback;

  // Assign the maximum retry for token generation
  config.max_token_generation_retry = 5;

  // Initialize Firebase
  Firebase.begin(&config, &auth);

  Serial.println("Getting User UID");
  while ((auth.token.uid) == "") {
    Serial.print('.');
    delay(1000);
  }

  Serial.print("User UID: ");
  Serial.println(auth.token.uid.c_str());
}

void loop() {

}
