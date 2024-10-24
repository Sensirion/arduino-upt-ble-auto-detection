#ifndef SENSIRION_UPT_BLE_AUTO_DETECTION_H
#define SENSIRION_UPT_BLE_AUTO_DETECTION_H

#include "Arduino.h"
#include "BleClient.h"
#include "Sensirion_UPT_Core.h"
#include <map>
#include <string>
#include <vector>

class __attribute__((unused)) SensiScan: public BleClientCallback {
  public:
    explicit SensiScan() : _bleClient(nullptr) {};

    void begin();
    __attribute__((unused)) void
    getScanResults(std::map<uint16_t, std::vector<Measurement>>& scanResults);
    __attribute__((unused)) void keepAlive();

  private:
    BleClient* _bleClient;
    std::map<uint16_t, std::vector<Measurement>> _sampleCache;
    void onAdvertisementReceived(std::string address, std::string name,
                                 std::string data) override;
    static uint64_t squashMACAddress(const std::string& macAddressString);
    static uint16_t getDeviceId(const std::string& data);
    static uint8_t decodeData(const MetaData& metaData, const std::string& data,
                              std::vector<Measurement>& samples);
};

#endif /* SENSIRION_UPT_BLE_AUTO_DETECTION_H */
