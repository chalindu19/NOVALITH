#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>
#include <esp_sleep.h>

#define AD8232_SIGNAL A0  
#define LO_PLUS 2         
#define LO_MINUS 3        
#define ECG_THRESHOLD 550  
#define PEAK_DELAY 200  
#define WAKE_UP_PIN 34  
#define BUZZER_PIN 5  
#define DELAY_TIME 500

Adafruit_ILI9341 tft = Adafruit_ILI9341(10, 9, 8);
unsigned long lastPeakTime = 0;

void setup() {
    Serial.begin(115200);
    pinMode(AD8232_SIGNAL, INPUT);
    pinMode(LO_PLUS, INPUT);
    pinMode(LO_MINUS, INPUT);
    pinMode(WAKE_UP_PIN, INPUT_PULLUP);
    pinMode(BUZZER_PIN, OUTPUT);
    
    tft.begin();
    tft.setRotation(3);
    tft.fillScreen(ILI9341_BLACK);
    tft.setTextColor(ILI9341_WHITE);
    tft.setTextSize(2);
    tft.setCursor(10, 10);
    tft.print("ECG Monitor");
}

void loop() {
    while (readingActive2) {

        currentMillis = millis();
    
        if (currentMillis - readStartTime2 >= READ_DURATION2) {
          readingActive2 = false;
          lastReadTime2 = currentMillis;
          Serial.println("ECG Heart rate reading completed.");
        }
    
        // Check if leads are off
        if ((digitalRead(33) == 1) || (digitalRead(32) == 1)) {
          Serial.println("Leads off! No heart rate calculated.");
          bpm = 0;  // Reset BPM to avoid false readings
          delay(500);  // Slow down the loop to avoid spam
          return;
        }
    
        // Collect multiple samples and compute average ECG value
        int sumECG = 0;
    
        
    
        for (int i = 0; i < SAMPLE_SIZE; i++) {
          sumECG += analogRead(ECG_PIN);
          delayMicroseconds(500); // Short delay between readings to reduce noise
        }
        int avgECG = sumECG / SAMPLE_SIZE;  // Compute average of collected samples
    
        // Apply moving average filter
        ecgBuffer[bufferIndex] = avgECG;
        bufferIndex = (bufferIndex + 1) % MOVING_AVG_SIZE;
        int filteredECG = getMovingAverage();
    
        // Determine dynamic threshold
        static int maxECG = 0;
        if (filteredECG > maxECG) {
          maxECG = filteredECG;
        }
        int threshold = maxECG * THRESHOLD_FACTOR;
    
        // Detect R-peaks and calculate BPM
        if (filteredECG > threshold) {
          unsigned long currentTime = millis();
          if (currentTime - lastPeakTime > 300) {  // Ignore noise (minimum 300ms gap)
            unsigned long rrInterval = currentTime - lastPeakTime;
            lastPeakTime = currentTime;
            bpm = 60000.0 / rrInterval; // Convert RR interval to BPM
          }
        }
    
        // Print data
        Serial.print("ECG: ");
        Serial.print(filteredECG);
        Serial.print(" | BPM: ");
        Serial.println(bpm);
    
        Firebase.RTDB.setString(&fbdo, liveData + "/ecg", bpm);
    
        delay(1);
      }
    }    