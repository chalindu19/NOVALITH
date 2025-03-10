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

// global variables 
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

// initialize the fire base 
void initFirebase(){
    config.api_key = API_KEY;
    auth.user.email = USER_EMAIL; 
    auth.user.password = USER_PASSWORD;
    config.database_url = DATABASE_URL; 
    Firebase.begin(&config,&auth);
    fbdo.setResponseSize(4096); 
}

//check the pressure sensor connection 
bool initPressureSensor (){
    pressure_sensor.begin(DOUT_Pin,SCK_Pin);
    return true; 
}


long readSensorData(){
    return pressure_sensor.mmHg();

}

// Send Data to Firebase
void sendDataToFirebase(long blood_pressure) {
    if (Firebase.RTDB.setString(&fbdo, "liveData/blood_pressure", String(blood_pressure))) {
      Serial.println("Data sent to the  Fire base successfully.");
    } else {
      Serial.println("Failed to send data: " + fbdo.errorReason());
    }
}


void checkWiFiStatus(){
    if (WiFi.status() ! = WL_CONNECTED){
        Serial.println("wifi disconnected");
        initWiFi();
    }
}


// validate the sensor reading 
bool isValidReading (long blood_pressure){
    return blood_pressure > 20 && blood_pressure < 200;
}

void logSensorData(long blood_pressure){
    Serial.print("blood pressure(mmHg): ");
    Serial.println(blood_pressure);  
}

     // Optimize Firebase Data Handling
bool updateFirebase(String path, String value) {
    return Firebase.RTDB.setString(&fbdo, path, value);
}



void enableWatchdogTimer(){
    esp_task_wdt_init(10,true);
    esp_task_wdt_add(NULL);
}

void enablePowerSavingMode(){
    WiFi.setSleep(true); 
}


    // Handle Firebase Errors
void handleFirebaseErrors() {
    if (!Firebase.ready()) {
      Serial.println("Firebase disconnected");
      initFirebase();
    }
}


void debugMessage(){
    Serial.println("system running ");
}
 // set up the function 
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
