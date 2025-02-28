#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include <BLE2902.h>

// Define the pin where the FSR402 is connected
const int fsrPin = A0;  // Change to your analog pin (A0 for ESP32)

// Create BLE server and service
BLEServer *pServer = nullptr;
BLEService *pService = nullptr;
BLECharacteristic *pCharacteristic = nullptr;

void setup() {
  // Start serial communication for debugging
  Serial.begin(115200);

  // Initialize BLE
  BLEDevice::init("FSR402_Sensor");  // Name of the device
  pServer = BLEDevice::createServer();
  pService = pServer->createService(BLEUUID((uint16_t)0x180D));  // Standard Health Thermometer Service
  pCharacteristic = pService->createCharacteristic(
                      BLEUUID((uint16_t)0x2A1C),   // Standard Pressure characteristic
                      BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_NOTIFY
                    );

  pCharacteristic->addDescriptor(new BLE2902());

  pService->start();
  BLEAdvertising *pAdvertising = pServer->getAdvertising();
  pAdvertising->start();

  Serial.println("BLE server is running, waiting for connections...");
}

void loop() {
  // Read pressure from the FSR402 sensor
  int fsrReading = analogRead(fsrPin);

  // Convert the reading to a string
  String pressure = String(fsrReading);

  // Set the value of the characteristic and notify clients
  pCharacteristic->setValue(pressure.c_str());
  pCharacteristic->notify();

  // Print the value to the Serial Monitor
  Serial.print("FSR Reading: ");
  Serial.println(fsrReading);

  delay(500);  // Update every 500ms
}
