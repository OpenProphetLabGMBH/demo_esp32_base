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
#include "buttons.h"
#include "oled.h"
#include "wifiManager.h"
#include "mqttManager.h"
#include "rotEncoder.h"
#include "leds.h"

void setup()
{
    Serial.begin(115200);
    delay(1000);

    setupButtons();

#ifdef OLED_DISPLAY
    setupOLEDdisplay();
#endif

    delay(500);
    connectToWifi();
    delay(500);
    setupMQTT();
    setupEncoder();

    setupLEDs();
}



void loop()
{
    // ** Non-Blocking "Reconnect to MQTT Broker" method
    watchMQTTStatus();
    watchLoopEncoder();
    watchGPIOButtons();
    updateLEDs();

    if (GPIO_BTN_CLICKED)
    {
        showWIFIDetailsOnOLEDscrn();
        showMQTTDetailsOnOLEDscrn();
        GPIO_BTN_CLICKED = false;
    }
}
