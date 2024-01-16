/*
 ArduinoBleSensiScan.h - Library for collecting sensor data via Bluetooth.
 Created by Bjoern Muntwyler, 2021.
 Released under BSD-3 licence
 */

#ifndef ARDUINO_BLE_SENSISCAN_H
#define ARDUINO_BLE_SENSISCAN_H

#include "Arduino.h"
#include "BleClient.h"
#include "SampleDecoder.h"
#include "Sensirion_UPT_Core.h"
#include <map>
#include <string>
#include <vector>

class SensiScan: public BleClientCallback {
  public:
    explicit SensiScan() : _bleClient(nullptr){};

    void begin();
    void
    getScanResults(std::map<uint16_t, std::vector<DataPoint>>& scanResults);
    void keepAlive();

  private:
    BleClient* _bleClient;
    std::map<uint16_t, std::vector<DataPoint>> _dataPointCache;
    void onAdvertisementReceived(std::string address, std::string name,
                                 std::string manufacturerData) override;
    uint16_t getDeviceId(const std::string& data);
};

#endif // ARDUINO_BLE_SENSISCAN_H
