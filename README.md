# README

## What is this?

Supporting HW project using pio (in VS CODE) on esp32 for [protopie_py_bridge_examples](https://github.com/OpenProphetLabGMBH/protopie_py_bridge_examples/tree/master/python_mqtt_bridge)

## Building & uploading instructions:

In [platformio.ini](https://github.com/OpenProphetLabGMBH/demo_esp32_base/blob/main/platformio.ini) file, please update the below, based on your current OS.
```ini
[env:lolin_d32_mac]
upload_port = /dev/tty.usbserial-xxxx
monitor_port = /dev/tty.usbserial-xxxx

[env:lolin_d32_Linux]
upload_port = /dev/ttyUSBX
monitor_port = /dev/ttyUSBX
```

Then click the pio icon:

![nav 0](/Assets/nav0.png)

And `build/upload/monitor` for your specific dev system

![nav 1](/Assets/nav1.png)

## Notes:

1. Mostly, All the major adjustable configurations (except Digital IO definitions ) are distributed, mainly between [platformio.ini](https://github.com/OpenProphetLabGMBH/demo_esp32_base/blob/main/platformio.ini) and [config.h](https://github.com/OpenProphetLabGMBH/demo_esp32_base/blob/main/src/config.h).
2. Some __environment variables__ that are used in [platformio.ini](https://github.com/OpenProphetLabGMBH/demo_esp32_base/blob/main/platformio.ini) (well commented) and affects the complied binary, have been put there for future automation purposes so that those can be changed from commandline directtly during the __build__ or __upload__ operations, without editing the files necessarily.