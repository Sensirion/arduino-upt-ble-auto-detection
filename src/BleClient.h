#ifndef SENSIRION_UPT_BLE_AUTO_DETECTION_BLE_CLIENT_H
#define SENSIRION_UPT_BLE_AUTO_DETECTION_BLE_CLIENT_H

#include "Arduino.h"
#include "BleClientCallback.h"
#include <functional>
namespace sensirion::upt::ble_auto_detection{
class BleClient {
  public:
    virtual ~BleClient() = default;
    virtual void begin(BleClientCallback* callback) = 0;
    virtual void keepAlive() = 0;
};
} // end namespace sensirion::upt::ble_auto_detection
#endif /* SENSIRION_UPT_BLE_AUTO_DETECTION_BLE_CLIENT_H */
