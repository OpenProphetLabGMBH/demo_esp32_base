/**
 * @brief
 *
 */

#include <PubSubClient.h>

long lastReconnectAttempt = 0; // A var that is used to check connection status of with the MQTT broker.

String MQTT_PUBLISH_TOPICS[2] = {"test1", "test2"};
// #define MQTT_SUBSCRIPTION_TOPIC "/icircuit/ESP32/serialdata/rx"

WiFiClient esp32WifiClient;
PubSubClient esp32MQTTclient(esp32WifiClient);

void mqttCallback(char *topic, byte *payload, unsigned int length)
{
    // Decide what to do with received data
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
        Serial.println("Connected to broker!");
        // Once connected, publish an announcement...
        log("Sending MQTT data: ");
        logln("client/esp32_1/status: online");
        esp32MQTTclient.publish("client/esp32_1/status", "online");
        // And re-subscribe...
        logln("Subscribing to MQTT topics: ");
        logln("1. system/for_clients");
        logln("2. system/for_clients");
        esp32MQTTclient.subscribe("system/for_clients");
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
