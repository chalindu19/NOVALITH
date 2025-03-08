#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>

#define AD8232_SIGNAL A0  
#define LO_PLUS 2         
#define LO_MINUS 3        
#define DELAY_TIME 10      
#define ECG_THRESHOLD 500  
#define SPIKE_THRESHOLD 100  

Adafruit_ILI9341 tft = Adafruit_ILI9341(10, 9, 8);

unsigned long lastPeakTime = 0;
int lastECGValue = 0;
int heartRateBuffer[5] = {0};  // Stores last 5 heart rate values
int bufferIndex = 0;

void setup() {
    Serial.begin(115200);
    pinMode(AD8232_SIGNAL, INPUT);
    pinMode(LO_PLUS, INPUT);
    pinMode(LO_MINUS, INPUT);

    tft.begin();
    tft.setRotation(3);
    tft.fillScreen(ILI9341_BLACK);
    tft.setTextColor(ILI9341_WHITE);
    tft.setTextSize(2);
    tft.setCursor(10, 10);
    tft.print("ECG Monitor");
}

void loop() {
    int ecgValue = analogRead(AD8232_SIGNAL);
    Serial.print("ECG Value: ");
    Serial.println(ecgValue);

    // Display ECG value on screen
    tft.fillRect(10, 30, 200, 20, ILI9341_BLACK); // Clear previous value
    tft.setCursor(10, 30);
    tft.print("ECG Value: ");
    tft.print(ecgValue);

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

            // Display heart rate on screen
            tft.fillRect(10, 50, 200, 20, ILI9341_BLACK); // Clear previous value
            tft.setCursor(10, 50);
            tft.print("Heart Rate: ");
            tft.print(avgHeartRate);
            tft.print(" BPM");

            lastPeakTime = currentTime;
        }
    }

    lastECGValue = ecgValue;

    if (digitalRead(LO_PLUS) == HIGH || digitalRead(LO_MINUS) == HIGH) {
        Serial.println("WARNING: Leads Off!");
        tft.fillRect(10, 70, 200, 20, ILI9341_BLACK); // Clear previous warning
        tft.setCursor(10, 70);
        tft.setTextColor(ILI9341_RED);
        tft.print("WARNING: Leads Off!");
        tft.setTextColor(ILI9341_WHITE);
    } else {
        tft.fillRect(10, 70, 200, 20, ILI9341_BLACK); // Clear warning if leads are on
    }

    delay(DELAY_TIME);
}
