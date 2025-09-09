#ifndef SENSIRION_UPT_BLE_AUTO_DETECTION_BLE_CLIENT_CALLBACK_H
#define SENSIRION_UPT_BLE_AUTO_DETECTION_BLE_CLIENT_CALLBACK_H

#include <string>

namespace sensirion::upt::ble_auto_detection{

  class BleClientCallback {
  public:
    virtual ~BleClientCallback() = default;

    virtual void onAdvertisementReceived(uint64_t address, std::string name,
                                         std::string data) = 0;
};

} // end namespace sensirion::upt::ble_auto_detection
#endif /* SENSIRION_UPT_BLE_AUTO_DETECTION_BLE_CLIENT_CALLBACK_H */
