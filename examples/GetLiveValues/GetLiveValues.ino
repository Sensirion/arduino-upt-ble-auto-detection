#include "Sensirion_upt_ble_auto_detection.h"
#include <Arduino.h>

void printScanResults(
    const std::map<uint16_t, std::vector<Measurement>>& scanResults);

SensiScan sensiScan = SensiScan();

void setup() {
    Serial.begin(115200);
    delay(1000); // Wait for serial connection

    sensiScan.begin();
}

void loop() {
    std::map<uint16_t, std::vector<Measurement>> scanResults;
    delay(1000);

    sensiScan.getScanResults(scanResults);

    printScanResults(scanResults);
}

void printScanResults(
    const std::map<uint16_t, std::vector<Measurement>>& scanResults) {
    if (scanResults.empty()) {
        Serial.printf("No data available.\n");
        return;
    }

    // Show found devices
    /* Consider that the device ID (as decoded from the key to the Measurements,
     * or item.first) is read from the BLE Advertisement whereas
     * Measurement.metaData.deviceID contains the MAC address of the device
     * broadcasting the Advertisement. The key should match the last two bytes
     * of the MAC address. */
    Serial.println("======================================");
    Serial.println("New Scan Results:");
    for (const auto& item : scanResults) {
        uint16_t deviceId = item.first;
        uint8_t lowByte = deviceId & 0xFF;
        uint8_t highByte = (deviceId >> 8) & 0xFF;

        const char* deviceLbl =
            bleGadgetLabel(item.second[0].metaData.deviceType.bleGadgetType);
        Serial.printf(" - %s Gadget with Id: %X:%X\n", deviceLbl, highByte,
                      lowByte);
    }
    Serial.println("--------------------------------------");

    // Show obtained measurements
    for (const auto& item : scanResults) {
        for (const auto& measurement : item.second) {
            printMeasurement(measurement);
        }
    }
    Serial.println("--------------------------------------");
}
