#ifndef ARDUINO_BLE_SENSISCAN_H
#define ARDUINO_BLE_SENSISCAN_H

#include "Arduino.h"
#include "BleClient.h"
#include "Sensirion_UPT_Core.h"
#include <map>
#include <string>
#include <vector>

class SensiScan: public BleClientCallback {
  public:
    explicit SensiScan() : _bleClient(nullptr){};

    void begin();
    void
    getScanResults(std::map<uint16_t, std::vector<Measurement>>& scanResults);
    void keepAlive();

  private:
    BleClient* _bleClient;
    std::map<uint16_t, std::vector<Measurement>> _sampleCache;
    void onAdvertisementReceived(std::string address, std::string name,
                                 std::string data) override;
    uint64_t squashMACAddress(const std::string& macAddressString);
    uint16_t getDeviceId(const std::string& data);
    uint8_t decodeData(const MetaData& metaData, const std::string& data,
                       std::vector<Measurement>& samples);
};

#endif // ARDUINO_BLE_SENSISCAN_H
