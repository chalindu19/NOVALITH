#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>

#define AD8232_SIGNAL A0  
#define LO_PLUS 2         
#define LO_MINUS 3        
#define ECG_THRESHOLD 550  
#define SPIKE_THRESHOLD 150  
#define PEAK_DELAY 200  

Adafruit_ILI9341 tft = Adafruit_ILI9341(10, 9, 8);

unsigned long lastPeakTime = 0;
int lastECGValue = 0;

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
    Serial.print("ECG: ");
    Serial.println(ecgValue);

    // Display ECG value
    tft.fillRect(10, 30, 200, 20, ILI9341_BLACK);
    tft.setCursor(10, 30);
    tft.print("ECG: ");
    tft.print(ecgValue);

    // Detect heart rate
    if (ecgValue > ECG_THRESHOLD && (ecgValue - lastECGValue) > SPIKE_THRESHOLD) {
        unsigned long currentTime = millis();
        if (currentTime - lastPeakTime > PEAK_DELAY) {
            int heartRate = 60000 / (currentTime - lastPeakTime);
            Serial.print("HR: ");
            Serial.println(heartRate);

            // Display heart rate
            tft.fillRect(10, 50, 200, 20, ILI9341_BLACK);
            tft.setCursor(10, 50);
            tft.print("HR: ");
            tft.print(heartRate);
            tft.print(" BPM");

            lastPeakTime = currentTime;
        }
    }

    // Leads-off detection
    if (digitalRead(LO_PLUS) || digitalRead(LO_MINUS)) {
        Serial.println("WARNING: Leads Off!");
        tft.fillRect(10, 70, 200, 20, ILI9341_BLACK);
        tft.setCursor(10, 70);
        tft.setTextColor(ILI9341_RED);
        tft.print("Leads Off!");
        tft.setTextColor(ILI9341_WHITE);
    } else {
        tft.fillRect(10, 70, 200, 20, ILI9341_BLACK);
    }

    lastECGValue = ecgValue;
}
