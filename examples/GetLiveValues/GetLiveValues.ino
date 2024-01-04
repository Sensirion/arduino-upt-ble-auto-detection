#include "ArduinoBleSensiScan.h"
#include <Arduino.h>

SensiScan sensiScan = SensiScan();

void setup() {
    Serial.begin(115200);
    while (!Serial) {
        delay(100);
    }

    sensiScan.begin();
}

void printScanResults(
    const std::map<uint16_t, std::vector<DataPoint>>& scanResults) {
    if (scanResults.empty()) {
        Serial.printf("No data available.\n");
        return;
    }

    Serial.println("New Scan Results:");
    for (const auto& item : scanResults) {
        uint16_t deviceId = item.first;
        uint8_t lowByte = deviceId & 0xFF;
        uint8_t highByte = (deviceId >> 8) & 0xFF;
        Serial.printf(" - %s Gadget with Id: %x:%x \n",
                      item.second[0].sourceDevice, highByte, lowByte);
        for (const auto& dp : item.second) {
            Serial.printf("\t- %s ->\t%f \t@%i\n", quantityOf(dp.signalType),
                          dp.value, dp.timeStamp);
        }
    }
    Serial.println();
}

void loop() {
    std::map<uint16_t, std::vector<DataPoint>> scanResults;
    delay(1000);

    sensiScan.getScanResults(scanResults);

    printScanResults(scanResults);
}
