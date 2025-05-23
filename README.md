# Arduino Sensirion UPT BLE Auto Detection
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/sensirion/library/Sensirion%20UPT%20BLE%20Auto%20Detection.svg)](https://registry.platformio.org/libraries/sensirion/Sensirion%20UPT%20BLE%20Auto%20Detection) [![arduino-library-badge](https://www.ardu-badge.com/badge/Sensirion%20UPT%20BLE%20Auto%20Detection.svg?)](https://www.ardu-badge.com/Sensirion%20UPT%20BLE%20Auto%20Detection)

This library enables you to retrieve live measurements form your own Do-It-Yourself BLE enabled sensor gadget or most Sensirion Gadgets on the ESP32 platform.

## Supported Gadgets

- AQ Minion
- MyCO2
- SHT3X Gadget
- SHT40 Gadget
- SHT43 Gadget
- [DIY BLE Gadget](https://github.com/Sensirion/arduino-ble-gadget)

## How to use

**Please see [the example provided as reference](examples/GetLiveValues/GetLiveValues.ino) on how to use this library.**

### Recommended Hardware

This project was developed and tested on Espressif [ESP32 DevKitC](https://www.espressif.com/en/products/devkits/esp32-devkitc) hardware (see e.g. [ESP32-DevKitC-32D](https://www.digikey.com/en/products/detail/espressif-systems/ESP32-DEVKITC-32D/9356990)).
This library requires standard library compatibility. Some boards such as Arduino AVR Uno do not ship with this functionnality.

### Arduino

Install the software from the [official website](https://www.arduino.cc/en/software) and read [this short tutorial](https://docs.arduino.cc/software/ide-v2/tutorials/getting-started-ide-v2/) to get an introduction to the IDE.
Next, select your board and port in the Board Manager by following [these instructions](https://support.arduino.cc/hc/en-us/articles/4406856349970-Select-board-and-port-in-Arduino-IDE).

This library can be installed easily using the Arduino Library manager:
Start the [Arduino IDE](http://www.arduino.cc/en/main/software) and open the Library Manager via

    Sketch => Include Library => Manage Libraries...

Search for the `Sensirion UPT BLE Auto Detection` library in the `Filter your search...` field and install it by clicking the `install` button. Make sure to click "Install All", lest you'll have to manually search for and install the dependencies:

- [NimBLE-Arduino](https://www.arduino.cc/reference/en/libraries/nimble-arduino/).
- [Sensirion UPT Core](https://www.arduino.cc/reference/en/libraries/sensirion-upt-core/)

Alternatively, the library can also be added manually. To do this, download the latest release from github as a .zip file via

    Code => Download Zip

and add it to the [Arduino IDE](http://www.arduino.cc/en/main/software) via

    Sketch => Include Library => Add .ZIP Library...

In this second case, you'll have to also add all dependencies the same way.

### PlatformIO

An often more straightforward alternative to the Arduino IDE is the PlatformIO framework, which is the recommended approach on Linux/Unix systems and is detailed in the following.

The most straight-forward way to use [PlatformIO](https://platformio.org/platformio-ide) is as an extension to Microsoft's [Visual Studio Code](https://code.visualstudio.com/), you'll find it easily among the extensions available for it. Please refer to the official installation instructions [here](https://platformio.org/install/ide?install=vscode).

To use the library, add the following dependencies to your `platformio.ini`'s `lib_deps`:

```control
lib_deps =
    Sensirion UPT BLE Auto Detection
```

PlatformIO will automatically fetch the latest version of the dependencies during the build process.

Alternatively, to install this library in your project environment execute the following command in a terminal:

```bash
pio pkg install --library "Sensirion UPT BLE Auto Detection"
```

To test the default example (`GetLiveValues`), use the following platformio command from the project's root directory (the one containing the `platformio.ini` file):

```bash
pio run -t upload
```

and start the Serial monitor with

```bash
pio device monitor
```

In case you're using some other board, it is recommended you create a new environment in the `platformio.ini` file, using the existing environment as a template. Find your `board` parameter [here](https://docs.platformio.org/en/latest/boards/index.html).

## Sensirion BLE Specification
To learn more about the BLE *Services* and *Characteristics* used by Sensirion devices, please refer to [the dedicated documentation page.](https://sensirion.github.io/ble-services/)

## License

See [LICENSE](LICENSE).

## Credits

This repository is based on the great work of @MBjoern called [arduino-ble-sensiscan](https://github.com/MBjoern/arduino-ble-sensiscan). Kudos to him !
