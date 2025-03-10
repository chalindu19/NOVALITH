#include <Arduino.h>
#include <Wifi.h>
#include <Firebase_ESP_Client.h>
#include "MAX30105.h"
#include "heartRate.h"
// define wifi and fire base 

#define Wifi_SSID " "
#define WIFI_PASSWORD " "
#define API_KEY " "
#define USER_EMAIL " "
#define USER_PASSWORD " "
#define DATABASE_URL " "

// read the interval 
#define READ_INTERVAL 60000 

// global variables 
unsigned long lastTime = 0;
int bpm = 0;
MAX30105 particleSensor ;
FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config; 

void iniWifi(){
    Wifi.begin(Wifi_SSID,WIFI_PASSWORD);
    Serial.print("Connecting to Wifi");
    while (Wifi.status() !=WL_CONNECTED){
        Serial.print('.');
        delay(1000);
    }
    Serial.println("\nConnected to Wifi, IP: "+ Wifi.localIP().toString());
}


void initFirebase(){
    config.api_key = API_KEY;
    auth.user.email = USER_EMAIL;
    auth.user.password = USER_PASSWORD;
    config.database_url = DATABASE_URL;
    Firebase.begin(&config,&auth);
    fbdo.setResponseSize(4096); 
}

// check ox sensor connection 
bool initOximeter(){
    if (!particleSensor.begin()){
        Serial.println("MAX30102 not found.Please check power");
        return false;
    }
    return true;
}

long readSensorData (){
    return particleSensor.getIR();
}



int calculateHeartRate(long irValue){
    static long lastBeat =0;
    if (irValue> 50000){
        if (checkForBeat(irValue)== true){

        long delta =millis()-lastBeat;
        lastBeat=millis();
        return 60/ (delta / 1000.0);
        }
    }
    return 0; 
}


void sendDataToFirebase(int bpm){
    if (Firebase.RTDB.setString(&fbdo, "live data / heart_rate",String(bpm))){
        Serial.println("data sent to fire base successfully");
    } else {
        Serial.println("failed to sent data"+ fbdo.errorReason();)
    }
}


void checkWiFiStatus(){
    if (WiFi.status() !=WL_CONNECTED){
        Serial.println("wifi is disconnected ");
        initWiFi();
    }
}

// validate sensor reading 
bool isValidReading(int bpm){
    return bpm > 0 && bpm < 200 ; 
}

// log sensor for debugging 
void logSensorData(int bpm){
    Serial.print("heart rate(bpm):");
    Serial.println(bpm);  
}

 // firebase data handling 
bool updateFirebase(String path,String value){
    return Firebase.RTDB.setString(&fbdo,path,value);
}


void enableWatchdogTimer(){
    esp_task_wdt_init(10, true);
    esp_task_wdt_add(NULL);
}


void enablePowerSavingMode() {
    WiFi.setSleep(true);
}

  
void handleFirebaseErrors(){
    if (!Firebase.ready()){
        Serial.println("firebase disconnected ");
        initFirebase();
    }
}


// Debugging Message
void debugMessage() {
    Serial.println("System running smoothly...");
}


// Setup Function
void setup() {
    Serial.begin(9600);
  
    initWiFi();
    initFirebase();
    enableWatchdogTimer();
    enablePowerSavingMode();
  
    if (!initOximeter()) {
      Serial.println("Sensor initialization failed. Restarting...");
      ESP.restart();
    }
}



// Main Loop
void loop() {
    checkWiFiStatus();
  
    unsigned long currentMillis = millis();
    if (currentMillis - lastTime >= READ_INTERVAL) {
      lastTime = currentMillis;
  
      long irValue = readSensorData();
      bpm = calculateHeartRate(irValue);
  
      if (isValidReading(bpm)) {
        sendDataToFirebase(bpm);
        logSensorData(bpm);
      }
    }
    
    handleFirebaseErrors();
    debugMessage();
    delay(5000);
}  

