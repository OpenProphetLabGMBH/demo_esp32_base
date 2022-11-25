/**
 * Platform: lolin_d32
 * Developer/s: Saurabh Datta
 * License: MIT
 * About:
 * Credits:
 * Notes:
 */

#include <Arduino.h>
#include "config.h"
#include "oled.h"
#include "wifiManager.h"
#include "mqttManager.h"
#include "rotEncoder.h"

void setup()
{
    Serial.begin(115200);

#ifdef OLED_DISPLAY
    setupOLEDdisplay();
#endif

    delay(2000);
    connectToWifi();
    delay(2000);
    setupMQTT();
    setupEncoder();
}

void loop()
{
    // ** Non-Blocking "Reconnect to MQTT Broker" method
    watchMQTTStatus();

    // in loop call your custom function which will process rotary encoder values
    rotaryLoop();
}