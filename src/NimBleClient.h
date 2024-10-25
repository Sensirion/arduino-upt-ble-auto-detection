#ifndef SENSIRION_UPT_BLE_AUTO_DETECTION_NIMBLE_CLIENT_H
#define SENSIRION_UPT_BLE_AUTO_DETECTION_NIMBLE_CLIENT_H

#include "BleClient.h"
#include "NimBLEDevice.h"

class __attribute__((unused)) NimBleClient
    : public BleClient,
      public NimBLEAdvertisedDeviceCallbacks {
  public:
    NimBleClient();
    ~NimBleClient();
    void begin(BleClientCallback* callback) override;
    void keepAlive() override;

  private:
    NimBLEScan* _bleScan;
    BleClientCallback* _callback;
    void setupBleScans();
    void startBleScans();
    void onResult(NimBLEAdvertisedDevice* advertisedDevice) override;
};

#endif /* SENSIRION_UPT_BLE_AUTO_DETECTION_NIMBLE_CLIENT_H */
