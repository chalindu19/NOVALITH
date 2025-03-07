#define AD8232_SIGNAL A0  
#define LO_PLUS 2         
#define LO_MINUS 3        
#define DELAY_TIME 10      
#define ECG_THRESHOLD 500  
#define SPIKE_THRESHOLD 100  

unsigned long lastPeakTime = 0;
int lastECGValue = 0;
int heartRateBuffer[5] = {0};  // Stores last 5 heart rate values
int bufferIndex = 0;

void setup() {
    Serial.begin(115200);
    pinMode(AD8232_SIGNAL, INPUT);
    pinMode(LO_PLUS, INPUT);
    pinMode(LO_MINUS, INPUT);
}

void loop() {
    int ecgValue = analogRead(AD8232_SIGNAL);
    Serial.print("ECG Value: ");
    Serial.println(ecgValue);

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
        }
    }

    lastECGValue = ecgValue;

    if (digitalRead(LO_PLUS) == HIGH || digitalRead(LO_MINUS) == HIGH) {
        Serial.println("WARNING: Leads Off!");
    }

    delay(DELAY_TIME);
}
