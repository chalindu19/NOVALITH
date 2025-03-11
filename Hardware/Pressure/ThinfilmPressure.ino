#include <Arduino.h>
#include <WiFi.h>
#include <FirebaseESP32.h>

// Firebase configuration
#define FIREBASE_HOST "your-project.firebaseio.com"
#define FIREBASE_AUTH "your-database-secret"

// Wi-Fi credentials
#define WIFI_SSID "your-SSID"
#define WIFI_PASSWORD "your-WiFi-password"

// Define the analog input pin for the pressure sensor
#define PRESSURE_SENSOR_PIN 34  // GPIO34 (ESP32 ADC pin)

// Firebase object
FirebaseData firebaseData;

// Pressure sensor variable
int pressureValue = 0;

// Function to connect to Wi-Fi
void connectToWiFi() {
  Serial.print("Connecting to WiFi");
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println("Connected to WiFi");
}

// Function to initialize Firebase
void initFirebase() {
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true); // Automatically reconnect if the connection drops
}

void setup() {
  // Start Serial Monitor
  Serial.begin(115200);

  // Connect to Wi-Fi
  connectToWiFi();

  // Initialize Firebase
  initFirebase();

  // Configure the pressure sensor pin as an input
  pinMode(PRESSURE_SENSOR_PIN, INPUT);

  Serial.println("Thin Film Pressure Sensor Initialized.");
}

void loop() {
  // Read the pressure sensor value (ADC)
  pressureValue = analogRead(PRESSURE_SENSOR_PIN);

  // Display the pressure value on Serial Monitor
  Serial.print("Pressure Sensor Value: ");
  Serial.println(pressureValue);

  // Send data to Firebase
  if (Firebase.setInt(firebaseData, "/sensor/pressure", pressureValue)) {
    Serial.println("Pressure value updated in Firebase.");
  } else {
    Serial.println("Error updating Firebase: " + firebaseData.errorReason());
  }

  // Wait before taking the next reading
  delay(5000); // 5 seconds delay
}
