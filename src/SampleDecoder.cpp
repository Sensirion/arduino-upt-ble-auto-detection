/*
 SampleDecoder.cpp
 Created by Bjoern Muntwyler, 2021.
 Released under BSD-3 licence
 */

#include "SampleDecoder.h"
#include "Arduino.h"
#include <map>

typedef float (*tdecodeer)(const std::string&, uint8_t);

struct UnitEncoding {
    SignalType signalType;
    tdecodeer converterFct;
};

struct SampleEncoding {
    uint8_t minFrameSize;
    std::map<uint8_t, UnitEncoding> unitEncoding;
};

SampleEncoding getEncoding(uint8_t sampleType) {
    switch (sampleType) {
        case 4:
            return {
                10,
                {{6,
                  {SignalType::TEMPERATURE_DEGREES_CELSIUS,
                   &SampleDecoder::decodeTemperatureV1}},
                 {8,
                  {SignalType::RELATIVE_HUMIDITY_PERCENTAGE,
                   &SampleDecoder::decodeHumidityV1}}},
            };
        case 6:
            return {
                10,
                {{6,
                  {SignalType::TEMPERATURE_DEGREES_CELSIUS,
                   &SampleDecoder::decodeTemperatureV1}},
                 {8,
                  {SignalType::RELATIVE_HUMIDITY_PERCENTAGE,
                   &SampleDecoder::decodeHumidityV2}}},
            };
        case 3:
            return {
                12,
                {{6,
                  {SignalType::TEMPERATURE_DEGREES_CELSIUS,
                   &SampleDecoder::decodeTemperatureV1}},
                 {8,
                  {SignalType::RELATIVE_HUMIDITY_PERCENTAGE,
                   &SampleDecoder::decodeHumidityV1}},
                 {10, {SignalType::VOC_INDEX, &SampleDecoder::decodeSimple}}},
            };
        case 10:
            return {
                12,
                {{6,
                  {SignalType::TEMPERATURE_DEGREES_CELSIUS,
                   &SampleDecoder::decodeTemperatureV1}},
                 {8,
                  {SignalType::RELATIVE_HUMIDITY_PERCENTAGE,
                   &SampleDecoder::decodeHumidityV1}},
                 {10,
                  {SignalType::CO2_PARTS_PER_MILLION,
                   &SampleDecoder::decodeSimple}}},
            };
        case 8:
            return {
                12,
                {{6,
                  {SignalType::TEMPERATURE_DEGREES_CELSIUS,
                   &SampleDecoder::decodeTemperatureV1}},
                 {8,
                  {SignalType::RELATIVE_HUMIDITY_PERCENTAGE,
                   &SampleDecoder::decodeHumidityV1}},
                 {10,
                  {SignalType::CO2_PARTS_PER_MILLION,
                   &SampleDecoder::decodeSimple}}},
            };
        case 12:
            return {
                14,
                {{6,
                  {SignalType::TEMPERATURE_DEGREES_CELSIUS,
                   &SampleDecoder::decodeTemperatureV1}},
                 {8,
                  {SignalType::RELATIVE_HUMIDITY_PERCENTAGE,
                   &SampleDecoder::decodeHumidityV1}},
                 {10,
                  {SignalType::CO2_PARTS_PER_MILLION,
                   &SampleDecoder::decodeSimple}},
                 {12,
                  {SignalType::PM2P5_MICRO_GRAMM_PER_CUBIC_METER,
                   &SampleDecoder::decodePM2p5V1}}},
            };
        case 14:
            return {
                12,
                {{6,
                  {SignalType::TEMPERATURE_DEGREES_CELSIUS,
                   &SampleDecoder::decodeTemperatureV1}},
                 {8,
                  {SignalType::RELATIVE_HUMIDITY_PERCENTAGE,
                   &SampleDecoder::decodeHumidityV1}},
                 {10,
                  {SignalType::HCHO_PARTS_PER_BILLION,
                   &SampleDecoder::decodeHCHOV1}}},
            };
        case 16:
            return {
                14,
                {{6,
                  {SignalType::TEMPERATURE_DEGREES_CELSIUS,
                   &SampleDecoder::decodeTemperatureV1}},
                 {8,
                  {SignalType::RELATIVE_HUMIDITY_PERCENTAGE,
                   &SampleDecoder::decodeHumidityV1}},
                 {10, {SignalType::VOC_INDEX, &SampleDecoder::decodeSimple}},
                 {12,
                  {SignalType::PM2P5_MICRO_GRAMM_PER_CUBIC_METER,
                   &SampleDecoder::decodePM2p5V1}}},
            };
        case 20:
            return {
                18,
                {{6,
                  {SignalType::TEMPERATURE_DEGREES_CELSIUS,
                   &SampleDecoder::decodeTemperatureV1}},
                 {8,
                  {SignalType::RELATIVE_HUMIDITY_PERCENTAGE,
                   &SampleDecoder::decodeHumidityV1}},
                 {10,
                  {SignalType::CO2_PARTS_PER_MILLION,
                   &SampleDecoder::decodeSimple}},
                 {12, {SignalType::VOC_INDEX, &SampleDecoder::decodeSimple}},
                 {14,
                  {SignalType::PM2P5_MICRO_GRAMM_PER_CUBIC_METER,
                   &SampleDecoder::decodePM2p5V1}},
                 {16,
                  {SignalType::HCHO_PARTS_PER_BILLION,
                   &SampleDecoder::decodeHCHOV1}}},
            };
        case 22:
            return {
                14,
                {{6,
                  {SignalType::TEMPERATURE_DEGREES_CELSIUS,
                   &SampleDecoder::decodeTemperatureV1}},
                 {8,
                  {SignalType::RELATIVE_HUMIDITY_PERCENTAGE,
                   &SampleDecoder::decodeHumidityV1}},
                 {10, {SignalType::VOC_INDEX, &SampleDecoder::decodeSimple}},
                 {12, {SignalType::NOX_INDEX, &SampleDecoder::decodeSimple}}},
            };
        case 24:
            return {
                16,
                {{6,
                  {SignalType::TEMPERATURE_DEGREES_CELSIUS,
                   &SampleDecoder::decodeTemperatureV1}},
                 {8,
                  {SignalType::RELATIVE_HUMIDITY_PERCENTAGE,
                   &SampleDecoder::decodeHumidityV1}},
                 {10, {SignalType::VOC_INDEX, &SampleDecoder::decodeSimple}},
                 {12, {SignalType::NOX_INDEX, &SampleDecoder::decodeSimple}},
                 {14,
                  {SignalType::PM2P5_MICRO_GRAMM_PER_CUBIC_METER,
                   &SampleDecoder::decodePMV2}}},
            };
        case 26:
            return {
                18,
                {{6,
                  {SignalType::TEMPERATURE_DEGREES_CELSIUS,
                   &SampleDecoder::decodeTemperatureV1}},
                 {8,
                  {SignalType::RELATIVE_HUMIDITY_PERCENTAGE,
                   &SampleDecoder::decodeHumidityV1}},
                 {10,
                  {SignalType::CO2_PARTS_PER_MILLION,
                   &SampleDecoder::decodeSimple}},
                 {12, {SignalType::VOC_INDEX, &SampleDecoder::decodeSimple}},
                 {14, {SignalType::NOX_INDEX, &SampleDecoder::decodeSimple}},
                 {16,
                  {SignalType::PM2P5_MICRO_GRAMM_PER_CUBIC_METER,
                   &SampleDecoder::decodePMV2}}},
            };
        case 28:
            return {14,
                    {
                        {6,
                         {SignalType::TEMPERATURE_DEGREES_CELSIUS,
                          &SampleDecoder::decodeTemperatureV1}},
                        {8,
                         {SignalType::RELATIVE_HUMIDITY_PERCENTAGE,
                          &SampleDecoder::decodeHumidityV1}},
                        {10,
                         {SignalType::CO2_PARTS_PER_MILLION,
                          &SampleDecoder::decodeSimple}},
                        {12,
                         {SignalType::PM2P5_MICRO_GRAMM_PER_CUBIC_METER,
                          &SampleDecoder::decodePMV2}},
                    }};
        case 30:
            return {
                14,
                {
                    {6,
                     {SignalType::TEMPERATURE_DEGREES_CELSIUS,
                      &SampleDecoder::decodeTemperatureV1}},
                    {8,
                     {SignalType::RELATIVE_HUMIDITY_PERCENTAGE,
                      &SampleDecoder::decodeHumidityV1}},
                    {10, {SignalType::VOC_INDEX, &SampleDecoder::decodeSimple}},
                    {12,
                     {SignalType::PM2P5_MICRO_GRAMM_PER_CUBIC_METER,
                      &SampleDecoder::decodePMV2}},
                }};
        case 31:
            return {
                18,
                {{6,
                  {SignalType::TEMPERATURE_DEGREES_CELSIUS,
                   &SampleDecoder::decodeTemperatureV1}},
                 {8,
                  {SignalType::RELATIVE_HUMIDITY_PERCENTAGE,
                   &SampleDecoder::decodeHumidityV1}},
                 {10,
                  {SignalType::CO2_PARTS_PER_MILLION,
                   &SampleDecoder::decodeSimple}},
                 {12, {SignalType::VOC_INDEX, &SampleDecoder::decodeSimple}},
                 {14,
                  {SignalType::PM2P5_MICRO_GRAMM_PER_CUBIC_METER,
                   &SampleDecoder::decodePMV2}},
                 {16,
                  {SignalType::HCHO_PARTS_PER_BILLION,
                   &SampleDecoder::decodeHumidityV2}}},
            };
        case 34:
            return {14,
                    {
                        {6,
                         {SignalType::PM1P0_MICRO_GRAMM_PER_CUBIC_METER,
                          &SampleDecoder::decodePMV2}},
                        {8,
                         {SignalType::PM2P5_MICRO_GRAMM_PER_CUBIC_METER,
                          &SampleDecoder::decodePMV2}},
                        {10,
                         {SignalType::PM4P0_MICRO_GRAMM_PER_CUBIC_METER,
                          &SampleDecoder::decodePMV2}},
                        {12,
                         {SignalType::PM10P0_MICRO_GRAMM_PER_CUBIC_METER,
                          &SampleDecoder::decodePMV2}},
                    }};
        case 36:
            return {
                8,
                {
                    {6,
                     {SignalType::CO2_PARTS_PER_MILLION,
                      &SampleDecoder::decodeSimple}},
                },
            };

        default:
            return {0, {}};
    }
}

uint8_t SampleDecoder::decode(uint8_t sampleType, const std::string& deviceName,
                              const std::string& data,
                              std::vector<DataPoint>& samples) {
    SampleEncoding encoding = getEncoding(sampleType);
    if (data.length() < encoding.minFrameSize) {
        return 1; // Frame too short or sampleType unknown
    }

    unsigned long timestamp = millis();

    for (const auto& item : encoding.unitEncoding) {
        DataPoint dp(item.second.signalType,
                     item.second.converterFct(data, item.first), timestamp,
                     deviceName.c_str());
        samples.push_back(dp);
    }

    return 0;
}

float SampleDecoder::decodeSimple(const std::string& data, uint8_t offset) {
    uint16_t value = getRawValue(data, offset);
    return static_cast<float>(value);
}

float SampleDecoder::decodeTemperatureV1(const std::string& data,
                                         uint8_t offset) {
    uint16_t value = getRawValue(data, offset);
    return -45.0f + ((175.0f * static_cast<float>(value)) / 65535);
}

float SampleDecoder::decodeHumidityV1(const std::string& data, uint8_t offset) {
    uint16_t value = getRawValue(data, offset);
    return (100.0f * static_cast<float>(value)) / 65535;
}

float SampleDecoder::decodeHumidityV2(const std::string& data, uint8_t offset) {
    uint16_t value = getRawValue(data, offset);
    return (125.0f * static_cast<float>(value)) / 65535 - 6.0f;
}

float SampleDecoder::decodePM2p5V1(const std::string& data, uint8_t offset) {
    uint16_t value = getRawValue(data, offset);
    return (1000.0f * static_cast<float>(value)) / 65535;
}

float SampleDecoder::decodePMV2(const std::string& data, uint8_t offset) {
    uint16_t value = getRawValue(data, offset);
    return static_cast<float>(value) / 10.0f;
}

float SampleDecoder::decodeHCHOV1(const std::string& data, uint8_t offset) {
    uint16_t value = getRawValue(data, offset);
    return static_cast<float>(value) / 5.0f;
}

uint16_t SampleDecoder::getRawValue(const std::string& data, uint8_t offset) {
    return static_cast<uint16_t>(static_cast<uint16_t>(data[offset + 1]) << 8 |
                                 static_cast<uint8_t>(data[offset]));
}
