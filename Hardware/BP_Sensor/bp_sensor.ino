#define SENSOR_PIN 36  // GPIO36 (VP) for analog input

void setup() {
    Serial.begin(115200);
}

void loop() {
    int rawValue = analogRead(SENSOR_PIN);
    float voltage = (rawValue / 4095.0) * 3.3; // Convert to voltage (ESP32 ADC resolution)
    float pressure = (voltage - 0.5) * (40.0 / 2.5); // Approximate pressure conversion

    Serial.print("Raw Value: ");
    Serial.print(rawValue);
    Serial.print(" | Voltage: ");
    Serial.print(voltage, 2);
    Serial.print("V | Pressure: ");
    Serial.print(pressure, 2);
    Serial.println(" kPa");

    delay(500);
}

