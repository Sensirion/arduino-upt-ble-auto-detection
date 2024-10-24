#ifndef SENSIRION_UPT_BLE_AUTO_DETECTION_BLE_CLIENT_CALLBACK_H
#define SENSIRION_UPT_BLE_AUTO_DETECTION_BLE_CLIENT_CALLBACK_H

class BleClientCallback {
  public:
    virtual ~BleClientCallback() = default;

    virtual void onAdvertisementReceived(std::string address, std::string name,
                                         std::string data) = 0;
};

#endif /* SENSIRION_UPT_BLE_AUTO_DETECTION_BLE_CLIENT_CALLBACK_H */
