Supporting HW project using pio on esp32 for [protopie_py_bridge_examples](https://github.com/OpenProphetLabGMBH/protopie_py_bridge_examples/tree/master/python_mqtt_bridge)

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

Then Navigate to:

