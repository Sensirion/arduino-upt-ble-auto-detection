#include <Arduino.h>
#include "ArduinoBleSensiScan.h"

SensiScan sensiScan = SensiScan();

void setup() {
    Serial.begin(115200);
    while (!Serial) {
        delay(100);
    }

    sensiScan.begin();
}

void printScanResults(std::map<Gadget, std::vector<DataPoint>> &scanResults) {
    if (scanResults.empty()) {
        Serial.printf("No data available.\n");
        return;
    }

    Serial.println("New Scan Results:");
    for (const auto& item : scanResults) {
        Gadget gadget = item.first;
        Serial.printf(" - %s Gadget with Id: %s \n", gadget.name.c_str(), gadget.deviceId.c_str());
        for (int i = 0; i < item.second.size(); i++) {
            Serial.printf("\t- %s ->\t%f \t@%i\n", quantityOf(item.second[i].signalType), item.second[i].value, item.second[i].timeStamp);
        }
    }
    Serial.println();
}

void loop() {
    std::map<Gadget, std::vector<DataPoint>> scanResults;
    delay(1000);

    sensiScan.getScanResults(scanResults);

    printScanResults(scanResults);
}
