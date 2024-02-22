#ifndef _SENSIRION_UPT_BLE_AUTO_DETECTION_NIMBLECLIENT_H
#define _SENSIRION_UPT_BLE_AUTO_DETECTION_NIMBLECLIENT_H

#include "BleClient.h"
#include "NimBLEDevice.h"

class NimBleClient: public BleClient, public NimBLEAdvertisedDeviceCallbacks {
  public:
    NimBleClient() : _bleScan(nullptr), _callback(nullptr){};
    void begin(BleClientCallback* callback) override;
    void keepAlive() override;

  private:
    NimBLEScan* _bleScan;
    BleClientCallback* _callback;
    void setupAndStartBleScans();
    void onResult(NimBLEAdvertisedDevice* advertisedDevice);
};

#endif /* _SENSIRION_UPT_BLE_AUTO_DETECTION_NIMBLECLIENT_H */
