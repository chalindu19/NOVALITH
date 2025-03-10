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
  Serial.begin(9600);
  pinMode(33, INPUT); // Leads off detection LO +
  pinMode(32, INPUT); // Leads off detection LO -
  pressure_sensor.begin(DOUT_Pin, SCK_Pin);
  Wire.begin(21, 22); // I2C pins for ESP32 (SDA: 21, SCL: 22)

  if (!ads.begin()) {
    Serial.println("Failed to initialize ADS1115!");
    while (1);
  }

  ads.setGain(GAIN_ONE); // Gain = 1 (±4.096V input range)

  if (!particleSensor.begin()) //Use default I2C port, 400kHz speed //Wire, I2C_SPEED_FAST
  {
    Serial.println("MAX30102 was not found. Please check wiring/power. ");
    while (1);
  }
  Serial.println("Place your index finger on the sensor with steady pressure.");

  particleSensor.setup(); //Configure sensor with default settings
  particleSensor.setPulseAmplitudeRed(0x0A); //Turn Red LED to low to indicate sensor is running
  particleSensor.setPulseAmplitudeGreen(0); //Turn off Green LED

  if (!mlx.begin()) {
    Serial.println("Error connecting to MLX sensor. Check wiring.");
    while (1);
  };

  initWiFi();
  configTime(0, 0, ntpServer);

  // Assign the api key (required)
  config.api_key = API_KEY;

  // Assign the user sign in credentials
  auth.user.email = USER_EMAIL;
  auth.user.password = USER_PASSWORD;

  // Assign the RTDB URL (required)
 

  // Assign the callback function for the long running token generation task */
  config.token_status_callback = tokenStatusCallback; //see addons/TokenHelper.h

  // Assign the maximum retry of token generation
  config.max_token_generation_retry = 5;

  // Initialize the library with the Firebase authen and config
  

  // Getting the user UID might take a few seconds
  Serial.println("Getting User UID");
  while ((auth.token.uid) == "") {
    Serial.print('.');
    delay(1000);
  }
  // Print user UID
  uid = auth.token.uid.c_str();
  Serial.print("User UID: ");
  Serial.println(uid);
}

// Function to read raw ADC value
int readSensorRaw(uint8_t channel) {
  return ads.readADC_SingleEnded(channel);
}

// Function to convert raw ADC value to percentage (0 - 100%)
float mapToPercentage(int rawValue) {
  float percentage = (rawValue / 26480.0) * 100.0;
  return constrain(percentage, 0, 100); // Ensures values stay within 0-100%
}

void loop() {

  timestamp = getTime();
  timestamp = timestamp + "000";

  if ((millis() - lastTime) > timerDelay) {
    dbData();
    lastTime = millis();
  }
  if ((millis() - lastTime2) > timerDelay2) {
    historyData();
    Firebase.RTDB.setString(&fbdo, liveData + "/isNew", "true");
    lastTime2 = millis();
  }

  currentMillis = millis();

  // Start a new reading session every 5 minutes
  if (!readingActive && (currentMillis - lastReadTime >= READ_INTERVAL)) {
    readingActive = true;
    readStartTime = currentMillis;
    Serial.println("Starting heart rate reading...");
  }

  if (!readingActive2 && (currentMillis - lastReadTime2 >= READ_INTERVAL2)) {
    readingActive2 = true;
    readStartTime2 = currentMillis;
    Serial.println("Starting ecg heart rate reading...");
  }

  if (readingActive2) {
    ecg();
  }

  // If reading is active, continue for 1 minute
  if (readingActive) {
    max30102Read();
  }



}
void Readpressure() {
  blood_pressure = pressure_sensor.mmHg();

  Firebase.RTDB.setString(&fbdo, liveData + "/blood_pressure", blood_pressure);
  delay(100);

  if (pressure_sensor.is_ready()) {
    Serial.print("Pressure (kPa): ");
    Serial.println(pressure_sensor.pascal());
  } else {
    Serial.println("Pressure sensor not found.");
  }

  Serial.print("ATM: ");
  Serial.println(pressure_sensor.atm());
  Serial.print("mmHg: ");
  Serial.println(pressure_sensor.mmHg());
  Serial.print("PSI: ");
  Serial.println(pressure_sensor.psi());


}
void readTempbody() {

}

void max30102Read() {

  irValue = particleSensor.getIR();

  if (irValue < 50000) {
    Serial.print(" No finger?");
    readingActive = false;
    lastReadTime = currentMillis;
  } else {
    b = true;
    delay(2000);

  }
  while (b) {

    currentMillis = millis();

    // Stop reading after 1 minute
    if (currentMillis - readStartTime >= READ_DURATION) {
      readingActive = false;
      b = false;
      lastReadTime = currentMillis;
      Serial.println("Heart rate reading completed.");
    }

    irValue = particleSensor.getIR();

    if (checkForBeat(irValue) == true)
    {
      //We sensed a beat!
      long delta = millis() - lastBeat;
      lastBeat = millis();

      beatsPerMinute = 60 / (delta / 1000.0);

      if (beatsPerMinute < 255 && beatsPerMinute > 20)
      {
        rates[rateSpot++] = (byte)beatsPerMinute; //Store this reading in the array
        rateSpot %= RATE_SIZE; //Wrap variable

        //Take average of readings
        beatAvg = 0;
        for (byte x = 0 ; x < RATE_SIZE ; x++)
          beatAvg += rates[x];
        beatAvg /= RATE_SIZE;
      }
    }

    Serial.print("IR=");
    Serial.print(irValue);
    Serial.print(", BPM=");
    Serial.print(beatsPerMinute);
    Serial.print(", Avg BPM=");
    Serial.print(beatAvg);


    if (irValue < 50000) {
      Serial.print(" No finger?");
      b = false;
    }
    Serial.println();
  }

  Serial.println();
  Firebase.RTDB.setString(&fbdo, liveData + "/heart_rate", beatAvg);
  delay(100);
}


void ecg() {

  while (readingActive2) {

    currentMillis = millis();

    if (currentMillis - readStartTime2 >= READ_DURATION2) {
      readingActive2 = false;
      lastReadTime2 = currentMillis;
      Serial.println("ECG Heart rate reading completed.");
    }

    // Check if leads are off
    if ((digitalRead(33) == 1) || (digitalRead(32) == 1)) {
      Serial.println("Leads off! No heart rate calculated.");
      bpm = 0;  // Reset BPM to avoid false readings
      delay(500);  // Slow down the loop to avoid spam
      return;
    }

    // Collect multiple samples and compute average ECG value
    int sumECG = 0;

    

    for (int i = 0; i < SAMPLE_SIZE; i++) {
      sumECG += analogRead(ECG_PIN);
      delayMicroseconds(500); // Short delay between readings to reduce noise
    }
    int avgECG = sumECG / SAMPLE_SIZE;  // Compute average of collected samples

    // Apply moving average filter
    ecgBuffer[bufferIndex] = avgECG;
    bufferIndex = (bufferIndex + 1) % MOVING_AVG_SIZE;
    int filteredECG = getMovingAverage();

    // Determine dynamic threshold
    static int maxECG = 0;
    if (filteredECG > maxECG) {
      maxECG = filteredECG;
    }
    int threshold = maxECG * THRESHOLD_FACTOR;

    // Detect R-peaks and calculate BPM
    if (filteredECG > threshold) {
      unsigned long currentTime = millis();
      if (currentTime - lastPeakTime > 300) {  // Ignore noise (minimum 300ms gap)
        unsigned long rrInterval = currentTime - lastPeakTime;
        lastPeakTime = currentTime;
        bpm = 60000.0 / rrInterval; // Convert RR interval to BPM
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
  if (Firebase.RTDB.getString(&fbdo, liveData + "/Prediction")) {
    if (fbdo.dataType() == "string") {
      Prediction = fbdo.stringData();
    }
  }
  else {
    Serial.println(fbdo.errorReason());
  } 
}
void notify() {
  Firebase.RTDB.setBool(&fbdo, notification + "/isNew", true);
  delay(200);
  Firebase.RTDB.setString(&fbdo, notification + "/message", Notify_Message);
  delay(200);
  
}