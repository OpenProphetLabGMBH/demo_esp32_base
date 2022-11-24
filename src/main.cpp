/**
 * Platform: lolin_d32
 * Developer/s: Saurabh Datta
 * License: MIT
 * About:
 * Credits:
 * Notes:
 */

#include <Arduino.h>
#include "debug.h"
#include "wifiManager.h"
#include "mqttManager.h"

void setup()
{
    Serial.begin(115200);
    delay(2000);
    connectToWifi();
    delay(2000);
    setupMQTT();
}

void loop()
{
    // ** Non-Blocking "Reconnect to MQTT Broker" method
    watchMQTTStatus();
}