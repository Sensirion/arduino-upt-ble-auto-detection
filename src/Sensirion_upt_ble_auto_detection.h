#ifndef SENSIRION_UPT_BLE_AUTO_DETECTION_H
#define SENSIRION_UPT_BLE_AUTO_DETECTION_H

#include "Arduino.h"
#include "BleClient.h"
#include "Sensirion_UPT_Core.h"
#include <map>
#include <string>
#include <vector>
namespace sensirion::upt::ble_auto_detection{

class __attribute__((unused)) SensirionBleScanner: public BleClientCallback {
  public:
    explicit SensirionBleScanner() : _bleClient(nullptr) {};

    void begin();
    [[maybe_unused]] void
    getSamplesFromScanResults(std::map<uint16_t, std::vector<core::Measurement>>& scanResults);
    [[maybe_unused]] void keepAlive();

  private:
    BleClient* _bleClient;
    std::map<uint16_t, std::vector<core::Measurement>> _sampleCache;
    void onAdvertisementReceived(uint64_t address, std::string name,
                                 std::string data) override;
    static uint16_t getDeviceId(const std::string& data);
    static uint8_t decodeData(const core::MetaData& metaData, const std::string& data,
                              std::vector<core::Measurement>& samples);
};
} // end namespace ensirion::upt::ble_auto_detection

#endif /* SENSIRION_UPT_BLE_AUTO_DETECTION_H */
