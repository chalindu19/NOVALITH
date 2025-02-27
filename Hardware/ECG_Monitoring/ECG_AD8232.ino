// Include necessary libraries (ESP32 automatically supports Serial)
#define AD8232_SIGNAL A0  // ECG Output pin
#define LO_PLUS 2         // Leads-Off Detection (LO+)
#define LO_MINUS 3        // Leads-Off Detection (LO-)

void setup() {
    Serial.begin(115200);  // Start serial communication
    
    // Set up the sensor and lead detection pins
    pinMode(AD8232_SIGNAL, INPUT);
    pinMode(LO_PLUS, INPUT);
    pinMode(LO_MINUS, INPUT);
}

void loop() {
    int ecgValue = analogRead(AD8232_SIGNAL);  // Read ECG signal
    
    Serial.print("ECG Value: ");
    Serial.println(ecgValue);  // Print ECG value
    
    // Check if ECG leads are disconnected
    if (digitalRead(LO_PLUS) == HIGH || digitalRead(LO_MINUS) == HIGH) {
        Serial.println("WARNING: Leads Off!");
    }

    delay(10); // Small delay for stable readings
}
