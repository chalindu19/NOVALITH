#define AD8232_SIGNAL A0  
#define LO_PLUS 2         
#define LO_MINUS 3        
#define DELAY_TIME 10      
#define ECG_THRESHOLD 500  
#define SPIKE_THRESHOLD 100  
#define FILTER_WINDOW 5  // Moving Average Window

int lastECGValue = 0;
int ecgReadings[FILTER_WINDOW] = {0};  
int index = 0;  

void setup() {
    Serial.begin(115200);
    pinMode(AD8232_SIGNAL, INPUT);
    pinMode(LO_PLUS, INPUT);
    pinMode(LO_MINUS, INPUT);
}

int getFilteredECG() {
    ecgReadings[index] = analogRead(AD8232_SIGNAL);
    index = (index + 1) % FILTER_WINDOW;  

    int sum = 0;
    for (int i = 0; i < FILTER_WINDOW; i++) {
        sum += ecgReadings[i];
    }
    return sum / FILTER_WINDOW;
}

void loop() {
    int ecgValue = getFilteredECG();
    
    Serial.print("Filtered ECG Value: ");
    Serial.println(ecgValue);

    if (abs(ecgValue - lastECGValue) > SPIKE_THRESHOLD) {
        Serial.println("WARNING: Sudden Heart Rate Spike Detected!");
    }

    lastECGValue = ecgValue;  

    if (digitalRead(LO_PLUS) == HIGH || digitalRead(LO_MINUS) == HIGH) {
        Serial.println("WARNING: Leads Off!");
    }

    delay(DELAY_TIME);
}
