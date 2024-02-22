#include "ArduinoBleSensiScan.h"
#include "NimBleClient.h"

const int COMPANY_ID_FILTER = 54534;

void SensiScan::begin() {
    _bleClient = new NimBleClient();
    _bleClient->begin(this);
    _bleClient->keepAlive();
}

void SensiScan::getScanResults(
    std::map<uint16_t, std::vector<Measurement>>& scanResults) {
    for (const auto& cachedSample : _sampleCache) {
        scanResults[cachedSample.first] = _sampleCache[cachedSample.first];
    }
    _sampleCache.clear();
}

void SensiScan::keepAlive() {
    _bleClient->keepAlive();
}

void SensiScan::onAdvertisementReceived(const std::string address,
                                        std::string name, std::string data) {
    uint16_t companyId = (uint16_t)data[0] << 8 | (uint8_t)data[1];
    if (companyId != COMPANY_ID_FILTER) {
        return;
    }

    // Get MAC address as uint64_t
    uint64_t deviceID = squashMACAddress(address);

    // Build MetaData
    MetaData metaData;
    metaData.deviceID = deviceID;
    metaData.deviceType.bleGadgetType =
        bleGadgetTypeFromCompleteLocalName(name.c_str());
    metaData.platform = DevicePlatform::BLE;

    // extract all samples
    std::vector<Measurement> samples;
    uint8_t error = decodeData(metaData, data, samples);
    if (error) {
        return;
    }

    // Last two digits of MAC addr. suffice to uniquely ID a BLE device
    _sampleCache[getDeviceId(data)] = samples;
}

/**
 * @brief squash std::string address to a uint64_t
 * @note MAC address is comprised of 6 bytes
 */
uint64_t SensiScan::squashMACAddress(const std::string& macAddressString) {

    uint64_t deviceID = macAddressString[0];
    for (size_t i = 1; i < 6; i++) {
        deviceID = (deviceID << 8) | macAddressString[i];
    }

    return deviceID;
}

/**
 * @brief last two digits of MAC address uniquely define a device
 */
uint16_t SensiScan::getDeviceId(const std::string& data) {
    uint16_t deviceId = (uint16_t)data[4] << 8 | (uint16_t)data[5];
    return deviceId;
}

extern std::map<DataType, SampleConfig> sampleConfigSelector;

/**
 * @brief decode chunk of Advertisement containing encoded samples
 *
 * @returns 0 on success
 *          1 if the Frame is too short or if the SampleType is unknown
 */
uint8_t SensiScan::decodeData(const MetaData& metaData, const std::string& data,
                              std::vector<Measurement>& samples) {
    uint8_t sampleType = static_cast<uint8_t>(data[3]);

    DataType dataType = getDataTypeFromSampleType(sampleType);
    SampleConfig sampleConfig = sampleConfigSelector[dataType];

    if (data.length() < 6 + sampleConfig.sampleSizeBytes) {
        return 1; // Frame too short or no config found
    }

    unsigned long timestamp = millis();

    for (const auto& sampleSlot : sampleConfig.sampleSlots) {
        uint16_t rawValue = getRawValue(data, 6 + sampleSlot.second.offset);

        DataPoint dataPoint;
        dataPoint.t_offset = timestamp;
        dataPoint.value = sampleSlot.second.decodingFunction(rawValue);

        Measurement measurement;
        measurement.dataPoint = dataPoint;
        measurement.signalType = sampleSlot.first;
        measurement.metaData = metaData;

        samples.push_back(measurement);
    }
    return 0;
}
