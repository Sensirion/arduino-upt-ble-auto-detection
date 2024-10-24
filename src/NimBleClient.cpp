#include "NimBleClient.h"

NimBleClient::NimBleClient() : _callback(nullptr) {
    // CONFIG_BTDM_SCAN_DUPL_TYPE_DATA_DEVICE (2)
    // Filter by address and data, advertisements from the same address will be
    // reported only once, except if the data in the advertisement has changed,
    // then it will be reported again.
    NimBLEDevice::setScanFilterMode(CONFIG_BTDM_SCAN_DUPL_TYPE_DATA_DEVICE);
    NimBLEDevice::setScanDuplicateCacheSize(200);
    NimBLEDevice::init("");
    _bleScan = NimBLEDevice::getScan();
    setupBleScans();
}

NimBleClient::~NimBleClient() {
    _bleScan->stop();
}

void NimBleClient::begin(BleClientCallback* callback) {
    _callback = callback;
    startBleScans();
}

void NimBleClient::keepAlive() {
    // If an error occurs that stops the scan, it will be restarted here.
    if (!_bleScan->isScanning()) {
        // Start scan with: duration = 0 seconds(forever), no scan end callback,
        // not a continuation of a previous scan.
        startBleScans();
    }
}

void NimBleClient::onResult(NimBLEAdvertisedDevice* advertisedDevice) {
    if (!advertisedDevice->haveManufacturerData()) {
        return;
    }

    // MAC address contains 6 bytes of MAC address (in reversed order)
    const uint8_t* bleMACAddress = advertisedDevice->getAddress().getNative();
    uint64_t address = 0;
    size_t address_size = 6;
    // reverse MAC address and store it as 64-bit unsigned int
    for (int ix = 0; ix < address_size; ix++) {
        address = (address << 8) | bleMACAddress[address_size - 1 - ix];
    }

    std::string name = advertisedDevice->haveName()
                           ? advertisedDevice->getName()
                           : "UNDEFINED";
    std::string manufacturerData = advertisedDevice->getManufacturerData();

    _callback->onAdvertisementReceived(address, name, manufacturerData);
}

void NimBleClient::setupBleScans() {
    // Activate callback on advertisement update
    _bleScan->setAdvertisedDeviceCallbacks(this, true);
    // Set active scanning, this will get more data from the advertiser.
    _bleScan->setActiveScan(true);
    // How often the scan occurs / switches channels; in milliseconds,
    _bleScan->setInterval(97);
    // How long to scan during the interval; in milliseconds.
    _bleScan->setWindow(37);
    // do not store the scan results, use callback only.
    _bleScan->setMaxResults(0);
}

void NimBleClient::startBleScans() {
    // Start scan with: duration = 0 seconds(forever), no scan end callback,
    // not a continuation of a previous scan.
    _bleScan->start(0, nullptr, false);
}
