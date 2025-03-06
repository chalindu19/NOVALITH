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



