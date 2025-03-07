#include <Arduino.h>
#include <Wifi.h>
#include <Firebase_ESP_Client.h>
#include "MAX30105.h"
#include "heartRate.h"
// define wifi and fire base 


#define READ_INTERVAL 60000 

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
