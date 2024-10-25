#ifndef SENSIRION_UPT_BLE_AUTO_DETECTION_BLE_CLIENT_H
#define SENSIRION_UPT_BLE_AUTO_DETECTION_BLE_CLIENT_H

#include "Arduino.h"
#include "BleClientCallback.h"
#include <functional>

class BleClient {
  public:
    virtual ~BleClient() = default;

    virtual void begin(BleClientCallback* callback) = 0;
    virtual void keepAlive() = 0;
};

#endif /* SENSIRION_UPT_BLE_AUTO_DETECTION_BLE_CLIENT_H */
