#ifndef _SENSIRION_UPT_BLE_AUTO_DETECTION_BLECLIENTCALLBACK_H
#define _SENSIRION_UPT_BLE_AUTO_DETECTION_BLECLIENTCALLBACK_H

class BleClientCallback {
  public:
    virtual ~BleClientCallback() {
    }

    virtual void onAdvertisementReceived(std::string address, std::string name,
                                         std::string data);
};

#endif /* _SENSIRION_UPT_BLE_AUTO_DETECTION_BLECLIENTCALLBACK_H */
