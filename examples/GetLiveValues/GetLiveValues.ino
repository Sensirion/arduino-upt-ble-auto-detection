#include "ArduinoBleSensiScan.h"
#include <Arduino.h>

void printMeasurement(const Measurement& measurement);
void printScanResults(
    const std::map<uint16_t, std::vector<Measurement>>& scanResults);
std::string arrayifyDeviceID(uint64_t deviceID);
void printMACAddess(const std::string& macAddress);

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

void printMeasurement(const Measurement& measurement) {
    // Get device and platform descriptive labels
    const char* platformLbl = devicePlatformLabel(
        measurement.metaData.platform, measurement.metaData.deviceType);
    const char* deviceLbl = deviceLabel(measurement.metaData.platform,
                                        measurement.metaData.deviceType);

    Serial.printf("Showing Measurement:\n");

    Serial.printf("  Data Point:\n");
    Serial.printf("    Measured at:\t%lus\n",
                  measurement.dataPoint.t_offset / 1000);
    Serial.printf("    Value:\t\t");
    switch (measurement.signalType) {
        case SignalType::TEMPERATURE_DEGREES_CELSIUS:
        case SignalType::RELATIVE_HUMIDITY_PERCENTAGE:
        case SignalType::VELOCITY_METERS_PER_SECOND:
            Serial.printf("%.1f\n", measurement.dataPoint.value);
            break;
        case SignalType::CO2_PARTS_PER_MILLION:
        case SignalType::HCHO_PARTS_PER_BILLION:
        case SignalType::PM1P0_MICRO_GRAMM_PER_CUBIC_METER:
        case SignalType::PM2P5_MICRO_GRAMM_PER_CUBIC_METER:
        case SignalType::PM4P0_MICRO_GRAMM_PER_CUBIC_METER:
        case SignalType::PM10P0_MICRO_GRAMM_PER_CUBIC_METER:
        case SignalType::RAW_VOC_INDEX:
        case SignalType::RAW_NOX_INDEX:
        case SignalType::VOC_INDEX:
        case SignalType::NOX_INDEX:
        case SignalType::GAS_CONCENTRATION_VOLUME_PERCENTAGE:
            Serial.printf("%i\n",
                          static_cast<int>(measurement.dataPoint.value));
            break;
        default:
            Serial.printf("%i\n",
                          static_cast<int>(measurement.dataPoint.value));
            break;
    }

    Serial.printf("  SignalType:\n");
    Serial.printf("    Physical Quantity:\t%s\n",
                  quantityOf(measurement.signalType));
    Serial.printf("    Units:\t\t%s\n", unitOf(measurement.signalType));

    Serial.printf("  Metadata:\n");
    Serial.printf("    Platform:\t\t%s\n", platformLbl);
    Serial.printf("    deviceID:\t\t");
    printMACAddess(arrayifyDeviceID(measurement.metaData.deviceID));
    Serial.println();
    Serial.printf("    Device Type:\t%s\n\n", deviceLbl);

    return;
}

std::string arrayifyDeviceID(uint64_t deviceID) {
    std::string address;
    for (int s = 5; s > -1; s--) {
        address[s] = static_cast<uint8_t>(deviceID);
        deviceID = deviceID >> 8;
    }
    return address;
}

void printMACAddess(const std::string& macAddress) {
    for (int i = 0; i < 5; i++) {
        Serial.printf("%X:", macAddress[i]);
    }
    Serial.printf("%X", macAddress[5]);
}
