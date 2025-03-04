#include <Wifi.h>
#include <Firebase_ESP_Client.h>
#include "DHT.h"

#define READ_INTERVAL 60000  // Interval to send data to Firebase in milliseconds

unsigned long lastTime = 0;
float pressure = 0.0;
float temperature = 0.0; 

