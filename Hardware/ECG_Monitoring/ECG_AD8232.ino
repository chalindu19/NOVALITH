#define AD8232_SIGNAL A0  
#define LO_PLUS 2         
#define LO_MINUS 3        

// Define constants for delay and signal threshold
#define DELAY_TIME 10         // Delay in milliseconds
#define ECG_THRESHOLD 500     // Example threshold for ECG signal stability

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

    // Check if signal exceeds the threshold
    if (ecgValue > ECG_THRESHOLD) {
        Serial.println("ECG signal is strong");
    }

    if (digitalRead(LO_PLUS) == HIGH || digitalRead(LO_MINUS) == HIGH) {
        Serial.println("WARNING: Leads Off!");
    }

    delay(DELAY_TIME);
}
