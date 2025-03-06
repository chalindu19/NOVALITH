#define AD8232_SIGNAL A0  
#define LO_PLUS 2         
#define LO_MINUS 3        
#define DELAY_TIME 10      
#define ECG_THRESHOLD 500  
#define SPIKE_THRESHOLD 100  // Change in signal that indicates a spike

int lastECGValue = 0;  

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

    // Detect sudden spikes
    if (abs(ecgValue - lastECGValue) > SPIKE_THRESHOLD) {
        Serial.println("WARNING: Sudden Heart Rate Spike Detected!");
    }

    lastECGValue = ecgValue;  

    if (digitalRead(LO_PLUS) == HIGH || digitalRead(LO_MINUS) == HIGH) {
        Serial.println("WARNING: Leads Off!");
    }

    delay(DELAY_TIME);
}
