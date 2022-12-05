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
    // [TBD] Payload parsing and business logic
}

boolean connectToBroker()
{
#ifdef MQTT_IS_SECURE
    logln("** Configuring MQTT client with supplied security credentials!");
    esp32MQTTclient.connect("esp32MQTTClient", MQTT_USERNAME, MQTT_PASSWORD);
#else
    esp32MQTTclient.connect("esp32MQTTClient");
#endif

    if (esp32MQTTclient.connected())
    {
        logln("Connected to broker!");
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
            logln("Not Connected to broker!");
            logln("Trying to connect to broker at: mqtt://" + String(MQTT_BROKER) + ":" + String(MQTT_PORT));
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
