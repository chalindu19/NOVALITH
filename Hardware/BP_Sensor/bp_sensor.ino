#include <Wifi.h>
#include <Firebase_ESP_Client.h>
#include "DHT.h"

//wifi and fire base set up 




#define DOUT_Pin 17
#define SCK_Pin 16 
#define READ_INTERVAL 60000  // Interval to send data to Firebase in milliseconds

unsigned long lastTime=0;
long blood_pressure =0;
HX710B pressure_sensor;
FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config; 


