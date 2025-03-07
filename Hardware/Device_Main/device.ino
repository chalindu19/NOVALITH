#include <Arduino.h>
#include <WiFi.h>
#include <Firebase_ESP_Client.h>
#include "time.h"
#include "addons/TokenHelper.h"
#include "addons/RTDBHelper.h"
#include <Wire.h>
#include <Adafruit_ADS1X15.h>
#include "HX710B.h"
#include "MAX30105.h"
#include "heartRate.h"
#include <Adafruit_MLX90614.h>

#define WIFI_SSID ""
#define WIFI_PASSWORD ""
#define API_KEY "AIzaSyAMwYHbDkd9uQDOjabL-rSwZ_GwkDc3ZJU"
#define USER_EMAIL "user@gmail.com"
#define USER_PASSWORD "User@123"
#define DATABASE_URL ""

#define DOUT_Pin 17
#define SCK_Pin 16
#define ECG_PIN 34   // ECG sensor analog pin
#define THRESHOLD_FACTOR 0.7  // Dynamic threshold factor (adjust as needed)
#define MOVING_AVG_SIZE 5     // Number of samples for moving average
#define SAMPLE_SIZE 10        // Number of samples to average.0

#define READ_INTERVAL 60000 // 5 minutes in milliseconds
#define READ_DURATION 60000  // 1 minute in milliseconds

#define READ_INTERVAL2 65000 // 5 minutes in milliseconds
#define READ_DURATION2 20000  // 1 minute in milliseconds

unsigned long kick_previousMillis = 0;
const long kick_interval = 60000;

unsigned long lastReadTime = 0;
unsigned long readStartTime = 0;
bool readingActive = false;

unsigned long lastReadTime2 = 0;
unsigned long readStartTime2 = 0;
bool readingActive2 = false;

unsigned long lastPeakTime = 0;
int bpm = 0;
int ecgBuffer[MOVING_AVG_SIZE];  // Buffer for moving average filter
int bufferIndex = 0;

unsigned long currentMillis;

HX710B pressure_sensor;
Adafruit_ADS1115 ads;
MAX30105 particleSensor;
Adafruit_MLX90614 mlx = Adafruit_MLX90614();

long irValue;
bool b = false;
const byte RATE_SIZE = 4; //Increase this for more averaging. 4 is good.
byte rates[RATE_SIZE]; //Array of heart rates
byte rateSpot = 0;
long lastBeat = 0; //Time at which the last beat occurred
float beatsPerMinute;
int beatAvg = 0;

// Define Firebase objects
FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;
FirebaseJson json;

String liveData = "/liveData";
String History = "/history";
String notification = "/notification";

String uid, timestamp, DB_history, Notify_Message, Prediction;
struct tm timeinfo;

int blood_pressure = 0;
int bodytemp = 0;
int kicks_count = 0;
int percent1 = 0;
int percent2 = 0;
int percent3 = 0;
int percent4 = 0;
int percent_avg = 80;
int sta1, sta2, sta3, sta4,sta5;

const char* ntpServer = "pool.ntp.org";
unsigned long lastTime = 0;
unsigned long timerDelay = 10000;
unsigned long lastTime2 = 0;
unsigned long timerDelay2 = 60000;

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
unsigned long getTime() {
  time_t now;
  if (!getLocalTime(&timeinfo)) {
    //Serial.println("Failed to obtain time");
    return (0);
  }
  time(&now);
  return now;
}
void setup() {
  Serial.begin(115200);
  pinMode(AD8232_SIGNAL, INPUT);
  pinMode(LO_PLUS, INPUT);
  pinMode(LO_MINUS, INPUT);

  tft.begin();
  tft.setRotation(3);
  tft.fillScreen(ILI9341_BLACK);
  tft.setTextColor(ILI9341_WHITE);
  tft.setTextSize(2);
  tft.setCursor(10, 10);
  tft.print("ECG Monitor");
}
void readTempbody() {
 
}
void max30102Read() {

}
void ecg() {

  while (readingActive2) {

    currentMillis = millis();

    if (currentMillis - readStartTime2 >= READ_DURATION2) {
      readingActive2 = false;
      lastReadTime2 = currentMillis;
      Serial.println("ECG Heart rate reading completed.");
    }

    if (ecgValue > ECG_THRESHOLD && (ecgValue - lastECGValue) > SPIKE_THRESHOLD) {
      unsigned long currentTime = millis();
      unsigned long timeDiff = currentTime - lastPeakTime;

      if (timeDiff > 300) {
          int heartRate = 60000 / timeDiff;
          
          // Store the value in the buffer
          heartRateBuffer[bufferIndex] = heartRate;
          bufferIndex = (bufferIndex + 1) % 5;

          // Calculate rolling average BPM
          int avgHeartRate = 0;
          for (int i = 0; i < 5; i++) {
              avgHeartRate += heartRateBuffer[i];
          }
          avgHeartRate /= 5;

          Serial.print("Average Heart Rate: ");
          Serial.print(avgHeartRate);
          Serial.println(" BPM");

          lastPeakTime = currentTime;
          
        if (digitalRead(LO_PLUS) == HIGH || digitalRead(LO_MINUS) == HIGH) {
          Serial.println("WARNING: Leads Off!");
        }

        delay(DELAY_TIME);

        if (digitalRead(LO_PLUS) == HIGH || digitalRead(LO_MINUS) == HIGH) {
          Serial.println("WARNING: Leads Off!");
          tft.fillRect(10, 70, 200, 20, ILI9341_BLACK); // Clear previous warning
          tft.setCursor(10, 70);
          tft.setTextColor(ILI9341_RED);
          tft.print("WARNING: Leads Off!");
          tft.setTextColor(ILI9341_WHITE);
      } else {
          tft.fillRect(10, 70, 200, 20, ILI9341_BLACK); // Clear warning if leads are on
      }
      }
  }

    // Print data
    Serial.print("ECG: ");
    Serial.print(filteredECG);
    Serial.print(" | BPM: ");
    Serial.println(bpm);

    Firebase.RTDB.setString(&fbdo, liveData + "/ecg", bpm);

    delay(1);
  }


}
// Function to compute moving average
int getMovingAverage() {
  int sum = 0;
  for (int i = 0; i < MOVING_AVG_SIZE; i++) {
    sum += ecgBuffer[i];
  }
  return sum / MOVING_AVG_SIZE;
}
void historyData() {
  
}
void dbData() {
  
}
void notify() {
  
}