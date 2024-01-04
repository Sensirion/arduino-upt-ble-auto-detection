/*
 SampleDecoder.h
 Created by Bjoern Muntwyler, 2021.
 Released under BSD-3 licence
 */

#ifndef ARDUINO_BLE_SENSISCAN_SAMPLEDECODER_H
#define ARDUINO_BLE_SENSISCAN_SAMPLEDECODER_H

#include "Sensirion_UPT_Core.h"
#include <string>
#include <vector>

namespace SampleDecoder {
uint8_t decode(uint8_t sampleType, const std::string& deviceName,
               const std::string& data, std::vector<DataPoint>& samples);

// Helpers
float decodeSimple(const std::string& data, uint8_t offset);
float decodeTemperatureV1(const std::string& data, uint8_t offset);
float decodeHumidityV1(const std::string& data, uint8_t offset);
float decodeHumidityV2(const std::string& data, uint8_t offset);
float decodePM2p5V1(const std::string& data, uint8_t offset);
float decodePMV2(const std::string& data, uint8_t offset);
float decodeHCHOV1(const std::string& data, uint8_t offset);
uint16_t getRawValue(const std::string& data, uint8_t offset);
}; // namespace SampleDecoder

#endif // ARDUINO_BLE_SENSISCAN_SAMPLEDECODER_H
