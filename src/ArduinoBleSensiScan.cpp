/*
 ArduinoBleSensiScan.cpp - Library for collecting sensor data via Bluetooth.
 Created by Bjoern Muntwyler, 2021.
 Released under BSD-3 licence
 */

#include "ArduinoBleSensiScan.h"
#include "NimBleClient.h"

const int COMPANY_ID_FILTER = 54534;

void SensiScan::begin() {
    _bleClient = new NimBleClient();
    _bleClient->begin(this);
    _bleClient->keepAlive();
}

void SensiScan::getScanResults(
    std::map<uint16_t, std::vector<DataPoint>>& scanResults) {
    // Deep copy cachedScanResult into scanResults
    for (const auto& cachedScanResult : _dataPointCache) {
        std::vector<DataPoint> dpVect;
        std::transform(cachedScanResult.second.begin(),
                       cachedScanResult.second.end(),
                       std::back_inserter(dpVect), [](const DataPoint& dp) {
                           // DataPoint lacks a copy ctor or assignment operator
                           return DataPoint(dp.signalType, dp.value,
                                            dp.timeStamp, dp.sourceDevice);
                       });
        scanResults[cachedScanResult.first] = dpVect;
    }
    _dataPointCache.clear();
}

void SensiScan::keepAlive() {
    _bleClient->keepAlive();
}

void SensiScan::onAdvertisementReceived(std::string address, std::string name,
                                        std::string data) {
    uint16_t companyId = (uint16_t)data[0] << 8 | (uint8_t)data[1];
    if (companyId != COMPANY_ID_FILTER) {
        return;
    }

    uint8_t sampleType = (uint8_t)data[3];
    uint16_t deviceId = getDeviceId(data);

    std::vector<DataPoint> samples;
    uint8_t error = SampleDecoder::decode(sampleType, name, data, samples);
    if (error) {
        return;
    }

    _dataPointCache[deviceId] = samples;
}

/**
 * @brief last two digits of MAC address uniquely define a device
 */
uint16_t SensiScan::getDeviceId(const std::string& data) {
    uint16_t deviceId = (uint16_t)data[4] << 8 | (uint16_t)data[5];
    return deviceId;
}
