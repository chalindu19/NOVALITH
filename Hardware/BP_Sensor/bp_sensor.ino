#include <Wifi.h>
#include <Firebase_ESP_Client.h>
#include "DHT.h"

//wifi and fire base set up 
#define WIFI_SSID " "
#define WIFI_PASSWORD " "
#define API_KEY " "
#define USER_EMAIL " "
#define USER_PASSWORD " "
#define DATABASE_URL " "  



#define DOUT_Pin 17
#define SCK_Pin 16 

#define READ_INTERVAL 60000  // Interval to send data to Firebase in milliseconds

unsigned long lastTime=0;
long blood_pressure =0;
HX710B pressure_sensor;
FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config; 

void iniWifi(){
    Wifi.begin(Wifi_SSID,WIFI_PASSWORD);
    Serial.print("Connecting to wifi");
    while(Wifi.status() !=WL_CONNECTED){
        Serial.print('.');
        delay(1000);
    }
    Serial.println("\nConnected to Wifi,IP:" +Wifi.localIP().toString());
}



bool initPressureSensor (){
    pressure_sensor.begin(DOUT_Pin,SCK_Pin);
    return true; 
}


long readSensorData(){
    return pressure_sensor.mmHg();

}


void checkWiFiStatus(){
    if (WiFi.status() ! = WL_CONNECTED){
        Serial.println("wifi disconnected");
        initWiFi();
    }
}



bool isValidReading (long blood_pressure){
    return blood_pressure > 20 && blood_pressure < 200;
}

void logSensorData(long blood_pressure){
    Serial.print("blood pressure(mmHg): ");
    Serial.println(blood_pressure);  
}



void enableWatchdogTimer(){
    esp_task_wdt_init(10,true);
    esp_task_wdt_add(NULL);
}

void enablePowerSavingMode(){
    WiFi.setSleep(true); 
}



void debugMessage(){
    Serial.println("system running ");
}

void setup(){
    Serial.begin(9600);
    initWiFi();
    enableWatchdogTimer();
    enablePowerSavingMode();

    if(!initPressureSensor()){
        Serial.println("Sensor initialization failed");
        ESP.restart();
    }
}



void loop(){
    checkWiFiStatus();

    unsigned long currentMillis = millis();
    if (currentMillis-lastTime>= READ_INTERVAL){
        lastTime = currentMillis;

        long blood_pressure = readSensorData();
        if(isValidReading(blood_pressure)){
            sendDataToFirebase(blood_pressure);
            logSensorData(blood_pressure);
        }
    }
    //  add the fire base errors handling 
}
