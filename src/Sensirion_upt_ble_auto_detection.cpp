#include "Sensirion_upt_ble_auto_detection.h"
#include "Arduino.h"
#include "NimBleClient.h"

namespace sensirion::upt::ble_auto_detection{

const int COMPANY_ID_FILTER = 54534;

void SensiScan::begin() {
    // these are the known device types that might be
    // detected!
    core::MYCO2();
    core::AQ_MINION();
    core::SHT40_GADGET();
    core::SHT43_GADGET();
    core::BLE_DIY_GADGET();
    core::HUMI_GADGET();

    core::InitSampleConfigurationMapping();
    _bleClient = new NimBleClient();
    _bleClient->begin(this);
}

__attribute__((unused)) void SensiScan::getSamplesFromScanResults(
    std::map<uint16_t, std::vector<core::Measurement>>& scanResults) {
    for (const auto& cachedSample : _sampleCache) {
        scanResults[cachedSample.first] = cachedSample.second;
    }
    _sampleCache.clear();
}

__attribute__((unused)) void SensiScan::keepAlive() {
    _bleClient->keepAlive();
}

void SensiScan::onAdvertisementReceived(uint64_t address, std::string name,
                                        std::string data) {
    uint16_t companyId = (uint16_t)data[0] << 8 | (uint8_t)data[1];
    if (companyId != COMPANY_ID_FILTER) {
        return;
    }

    // Build MetaData
    core::MetaData metaData{core::MetaData::DEVICE_UNDEFINED};
    metaData.deviceID = address;
    auto optionalDeviceType = core::DeviceTypeRegistry::GetDeviceType(name);
    if (!optionalDeviceType.has_value()){
        return; // it is not a known device!
    }

    metaData.deviceType = optionalDeviceType.value();

    // extract all samples
    std::vector<core::Measurement> samples;
    uint8_t error = decodeData(metaData, data, samples);
    if (error) {
        return;
    }

    // Last two digits of MAC addr. Suffice to uniquely ID a BLE device
    _sampleCache[getDeviceId(data)] = samples;
}

/**
 * @brief last two digits of MAC address uniquely define a device
 */
uint16_t SensiScan::getDeviceId(const std::string& data) {
    uint16_t deviceId = (uint16_t)data[4] << 8 | (uint16_t)data[5];
    return deviceId;
}

/**
 * @brief decode chunk of Advertisement containing encoded samples
 *
 * @returns 0 on success
 *          1 if the SampleType is unknown
 *          2 if the received data length is too short for the sample type
 */
uint8_t SensiScan::decodeData(const core::MetaData& metaData, const std::string& data,
                              std::vector<core::Measurement>& samples) {
    auto sampleType = static_cast<uint8_t>(data[3]);
                            
    core::DataType dataType = core::getDataTypeFromSampleType(sampleType);
    if (dataType == core::DataType::UNDEFINED){
        return 1;
    }
    core::SampleConfig sampleConfig = core::GetSampleConfiguration(dataType);
    if( sampleConfig.dataType != dataType){
        return 1;
    }

    if (data.length() < 6 + sampleConfig.sampleSizeBytes ) {
        /*
        NOTE: Here we ignore frames that are too short for T_RH_CO2_ALT data types 
        because the MyCO2 gadget is actually not sending the 2 reserved Bytes (ALT)
        */
       bool is_a_myco2_gadget = metaData.deviceType == core::MYCO2() && 
            data.length() == 6 + sampleConfig.sampleSizeBytes - 2;
       if (! is_a_myco2_gadget){
            return 2; // Frame too short 
       }
    }

    unsigned long timestamp = millis();
    
    for (const auto& sampleSlot : sampleConfig.sampleSlots) {
        uint16_t rawValue = core::getRawValue(data, 6 + sampleSlot.second.offset);
        samples.emplace_back(
            metaData,
            sampleSlot.first,
            core::DataPoint{timestamp, sampleSlot.second.decodingFunction(rawValue)}
        );
    }
    return 0;
}
} // end namespace sensirion::upt::ble_auto_detection