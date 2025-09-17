#ifndef SENSIRION_UPT_BLE_AUTO_DETECTION_NIMBLE_CLIENT_H
#define SENSIRION_UPT_BLE_AUTO_DETECTION_NIMBLE_CLIENT_H

#include "BleClient.h"
#include "NimBLEDevice.h"

namespace sensirion::upt::ble_auto_detection{

static constexpr uint32_t SCAN_DURATION_MS = 30 * 1000; // 30 seconds scans.

class NimBleClient
    : public BleClient,
      public NimBLEScanCallbacks {
  public:
    NimBleClient();
    ~NimBleClient();
    void begin(BleClientCallback* callback) override;
    void keepAlive() override;
    NimBleClient& operator=(NimBleClient&& other) = delete;

  private:
    NimBLEScan* _bleScan;
    BleClientCallback* _callback;
    void setupBleScans();
    void startBleScans();
    void onResult(const NimBLEAdvertisedDevice* advertisedDevice) override;
    void onScanEnd(const NimBLEScanResults& results, int reason) override;
};
} // end namespace sensirion::upt::ble_auto_detection
#endif /* SENSIRION_UPT_BLE_AUTO_DETECTION_NIMBLE_CLIENT_H */
