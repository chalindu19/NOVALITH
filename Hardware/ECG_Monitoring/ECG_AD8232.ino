#define AD8232_SIGNAL A0  
#define LO_PLUS 2         
#define LO_MINUS 3        
#define DELAY_TIME 10      
#define ECG_THRESHOLD 500  

const int SMOOTH_WINDOW = 10;  // Number of readings for moving average
int ecgBuffer[SMOOTH_WINDOW] = {0};  
int bufferIndex = 0;  

void setup() {
    Serial.begin(115200);
    pinMode(AD8232_SIGNAL, INPUT);
    pinMode(LO_PLUS, INPUT);
    pinMode(LO_MINUS, INPUT);
}

void loop() {
    int rawValue = analogRead(AD8232_SIGNAL);

    // Add new value to the buffer and calculate the moving average
    ecgBuffer[bufferIndex] = rawValue;
    bufferIndex = (bufferIndex + 1) % SMOOTH_WINDOW;

    int sum = 0;
    for (int i = 0; i < SMOOTH_WINDOW; i++) {
        sum += ecgBuffer[i];
    }
    int ecgValue = sum / SMOOTH_WINDOW;  // Smoothed ECG value

    Serial.print("Smoothed ECG Value: ");
    Serial.println(ecgValue);

    if (digitalRead(LO_PLUS) == HIGH || digitalRead(LO_MINUS) == HIGH) {
        Serial.println("WARNING: Leads Off!");
    }

    delay(DELAY_TIME);
}
