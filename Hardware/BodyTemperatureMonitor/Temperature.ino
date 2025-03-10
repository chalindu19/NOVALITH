#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_MLX90614.h>
#include <WiFi.h>
#include <FirebaseESP32.h>

// Firebase configuration
#define FIREBASE_HOST "your-project.firebaseio.com"
#define FIREBASE_AUTH "your-database-secret"

// Wi-Fi credentials
#define WIFI_SSID "Galaxy S9"
#define WIFI_PASSWORD "839747650"

// I2C pins for ESP32 (SDA: 21, SCL: 22)
Adafruit_MLX90614 mlx = Adafruit_MLX90614();

// Firebase object
FirebaseData firebaseData;

// Sensor reading variables
int bodyTemp = 0;

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

  // Initialize I2C and MLX90614 sensor
  Wire.begin(21, 22); // SDA: 21, SCL: 22
  
  if (!mlx.begin()) {
    Serial.println("Error connecting to MLX sensor. Check wiring.");
    while (1);  // Halt the program if sensor is not connected
  }

  Serial.println("MLX90614 initialized.");
}

void loop() {
  // Read the body temperature from the MLX90614 sensor
  bodyTemp = mlx.readObjectTempC(); // Get temperature in Celsius

  // Display the temperature on Serial Monitor
  Serial.print("Body Temperature: ");
  Serial.print(bodyTemp);
  Serial.println(" °C");

  // Send data to Firebase
  if (Firebase.setInt(firebaseData, "/sensor/bodyTemperature", bodyTemp)) {
    Serial.println("Body temperature updated in Firebase.");
  } else {
    Serial.println("Error updating Firebase: " + firebaseData.errorReason());
  }

  // Wait before taking the next reading
  delay(5000); // 5 seconds delay
}
