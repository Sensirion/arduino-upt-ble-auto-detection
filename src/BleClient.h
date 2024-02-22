#ifndef _SENSIRION_UPT_BLE_AUTO_DETECTION_BLECLIENT_H
#define _SENSIRION_UPT_BLE_AUTO_DETECTION_BLECLIENT_H

#include "Arduino.h"
#include "BleClientCallback.h"
#include <functional>

class BleClient {
  public:
    virtual ~BleClient() = default;

    virtual void begin(BleClientCallback* callback) = 0;
    virtual void keepAlive() = 0;
};

#endif /* _SENSIRION_UPT_BLE_AUTO_DETECTION_BLECLIENT_H */
