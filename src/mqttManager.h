/**
 * @brief
 *
 */

#include <PubSubClient.h>

WiFiClient esp32WifiClient;
PubSubClient esp32MQTTclient(esp32WifiClient);

long lastReconnectAttempt = 0; // A var that is used to check connection status of with the MQTT broker.

void mqttCallback(char *topic, byte *payload, unsigned int length)
{
    logln("Received MQTT message");
    log("Topic: ");
    logln(String(topic));
    // [WIP] Payload parsing and business logic

    payload[length] = '\0';
    String payloadStr = String((char *)payload);
    log("received payload:");
    logln(payloadStr);

    // switch states
    if (String(topic).equals(MQTT_SUBS_TOPICS[1]))
    {
        // if recievd "on"
        if (payloadStr.equals(MQTT_SUBS_MSGS[0]))
        {
            ledState = true;
        }
        // if recievd "off"
        if (payloadStr.equals(MQTT_SUBS_MSGS[1]))
        {
            ledState = false;
        }
    }
    if (String(topic).equals(MQTT_SUBS_TOPICS[2]))
    {
        // slider value
        ledBrightness = payloadStr.toFloat();
    }
}

boolean connectToBroker()
{
#ifdef MQTT_IS_SECURE
    // logln("** Configuring MQTT client with supplied security credentials!");
    logln("Trying to connect to MQTT broker at: mqtt://" + String(MQTT_BROKER) + ":" + String(MQTT_PORT) + "\nwith supplied security credentials!");
    esp32MQTTclient.connect("esp32MQTTClient", MQTT_USERNAME, MQTT_PASSWORD);
#else
    esp32MQTTclient.connect("esp32MQTTClient");
#endif
#ifdef OLED_DISPLAY
    u8g2log.println("CONNECTING TO BROKER ...");
    u8g2log.println(String(MQTT_BROKER) + " : " + String(MQTT_PORT));
#endif

    if (esp32MQTTclient.connected())
    {
        logln("Connected to broker!");
#ifdef OLED_DISPLAY
        u8g2log.println("\nCONNECTED TO BROKER!\n");
#endif
        // Once connected, publish an announcement ...
        logln("\nPublishing:");
        logln(String(MQTT_PUBS_TOPICS[0]) + ": " + String(MQTT_PUBS_MSGS[0]) + "\n");
        esp32MQTTclient.publish(MQTT_PUBS_TOPICS[0], MQTT_PUBS_MSGS[0]);

        // And re-subscribe to assigned topics
        logln("\nSubscribing to following MQTT Topics: ");
        for (int i = 0; i <= ((sizeof(MQTT_SUBS_TOPICS) / sizeof(MQTT_SUBS_TOPICS[0])) - 1); i++)
        {
            log(i);
            log(". ");
            logln(MQTT_SUBS_TOPICS[i]);
            esp32MQTTclient.subscribe(MQTT_SUBS_TOPICS[i]);
        }
    }
    return esp32MQTTclient.connected();
}

void setupMQTT()
{
    esp32MQTTclient.setServer(MQTT_BROKER, MQTT_PORT);
    esp32MQTTclient.setCallback(mqttCallback);

    lastReconnectAttempt = 0;
}

// ** Non-Blocking "Reconnect to MQTT Broker" method.
void watchMQTTStatus()
{
    if (!esp32MQTTclient.connected())
    {
        long now = millis();
        // Try every 5 sec
        if (now - lastReconnectAttempt > 5000)
        {
#ifdef OLED_DISPLAY
            u8g2log.println("\n[x] NOT CONNECTED TO BROKER");
            u8g2log.println("TRYING AGAIN ...");
#endif
            logln("Not Connected to broker!");
            lastReconnectAttempt = now;
            // Attempt to reconnect
            if (connectToBroker())
            {
                lastReconnectAttempt = 0;
            }
        }
    }
    else
    {
        esp32MQTTclient.loop(); // Client is connected, so loop()
    }
}

void showMQTTDetailsOnOLEDscrn()
{
    if (esp32MQTTclient.connected())
    {
#ifdef OLED_DISPLAY
        u8g2log.println("CONNECTED TO BROKER!");
        u8g2log.println(String(MQTT_BROKER) + " : " + String(MQTT_PORT));
#endif
    }
    else
    {
#ifdef OLED_DISPLAY
        u8g2log.println("[x] NOT CONNECTED TO BROKER!");
        u8g2log.println(String(MQTT_BROKER) + " : " + String(MQTT_PORT));
#endif
    }
}
