#include "Sensirion_upt_ble_auto_detection.h"
#include <Arduino.h>

using namespace sensirion::upt::core;
using namespace sensirion::upt::ble_auto_detection;

void printScanResults(
    const std::map<uint16_t, std::vector<Measurement>>& scanResults);

SensirionBleScanner bleScanner = SensirionBleScanner();
std::map<uint16_t, std::vector<Measurement>> lastBleScanSamples;

void setup() {
    Serial.begin(115200);
    delay(1000); // Wait for serial connection

    bleScanner.begin();
}

void loop() {
    delay(1000);

    bleScanner.getSamplesFromScanResults(lastBleScanSamples);
    printScanResults(lastBleScanSamples);
    lastBleScanSamples.clear();

    // ensure scanning is restarted in case of errors.
    bleScanner.keepAlive();
}

void printScanResults(
    const std::map<uint16_t, std::vector<Measurement>>& bleScanSamples) {
    if (bleScanSamples.empty()) {
        Serial.printf("No new sample received.\n");
        return;
    }

    // Show found devices
    /* Consider that the device ID (as decoded from the key to the Measurements,
     * or item.first) is read from the BLE Advertisement whereas
     * Measurement.metaData.deviceID contains the MAC address of the device
     * broadcasting the Advertisement. The key should match the last two bytes
     * of the MAC address. */
    Serial.println("======================================");
    Serial.printf("%i new samples from scan results:\n", bleScanSamples.size());
    for (const auto& item : bleScanSamples) {
        uint16_t deviceId = item.first;
        uint8_t lowByte = deviceId & 0xFF;
        uint8_t highByte = (deviceId >> 8) & 0xFF;

        const char* deviceLbl =
            deviceLabel(item.second[0].metaData.deviceType);
        Serial.printf(" - %s Gadget with Id: %X:%X\n", deviceLbl, highByte,
                      lowByte);
    }
    Serial.println("--------------------------------------");

    // Show obtained measurements
    
    for (const auto& item : bleScanSamples) {
        for (const auto& measurement : item.second) {
            printMeasurement(measurement);
        }
    }
    Serial.println("--------------------------------------");
}
