#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include <BLE2902.h>

// Define the pin where the FSR402 is connected
const int fsrPin = A0;  
int batteryLevel = 100; // simulate the battery percentag


BLEServer *pServer = nullptr;
BLEService *pService = nullptr;
BLECharacteristic *pPressureCharacteristic = nullptr;
BLECharacteristic *pBatteryCharacteristic = nullptr;


void setup() {
  
  Serial.begin(115200);

  // Initialize BLE
  BLEDevice::init("FSR402_Sensor");  
  pServer = BLEDevice::createServer();
  pService = pServer->createService(BLEUUID((uint16_t)0x180D)); 

  pPressureCharacteristic = pService->createCharacteristic(
                      BLEUUID((uint16_t)0x2A1C),   
                      BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_NOTIFY
                    );

  pBatteryCharacteristic = pService -> createCharacteristic(
                              BLEUUID((uint16_t)0x2A1C),   
                              BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_NOTIFY              
  );                 

  pPressureCharacteristic->addDescriptor(new BLE2902());
  pBatteryCharacteristic->addDescriptor(new BLE2902());

  pService->start();
  BLEAdvertising *pAdvertising = pServer->getAdvertising();
  pAdvertising->start();

  Serial.println("BLE server is running, with Battery level waiting for connections...");
}

void loop() {
  
  int fsrReading = analogRead(fsrPin);
  String pressure = String(fsrReading);
  String battery = String(batteryLevel) + "%";


  
  pPressureCharacteristic->setValue(pressure.c_str());
  pPressureCharacteristic->notify();

  pBatteryCharacteristic->setValue(pressure.c_str());
  pBatteryCharacteristic->notify();

  
  Serial.print("FSR Reading: ");
  Serial.println(fsrReading);
  Serial.print("  | Battery: ");
  Serial.println(battery);

  batteryLevel = max(0,batteryLevel - 1);
  delay(500);  // Update every 500ms
}
