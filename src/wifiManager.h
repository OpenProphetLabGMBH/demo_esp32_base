/**
 * @brief
 *
 */

#include <WiFi.h>

// A method that connects to a given wifi AP and tries to assign a static IP address (defined in config.h).
void connectToWifi()
{
    delay(2000);
    Serial.print("Connecting to ");
    Serial.println(wifi_ssid);

// Giving the esp32 a ststic IP, after it connects to the WIFI.
#ifdef setStaticIP
    IPAddress staticIP(staticIPAddr); // Set your Static IP address.
    IPAddress gateway(gatewayIPAddr); // Set your Gateway IP address.
    IPAddress subnet(subnetAddr);
    if (!WiFi.config(staticIP, gateway, subnet))
    {
        Serial.println("STA Failed to configure");
    }
#endif
    // Start to connect to WIFI
    WiFi.begin(wifi_ssid, wifi_pwd);
    // Check if WIFI is connected ornot
    while (WiFi.status() != WL_CONNECTED || WiFi.status() != 3)
    {
        delay(100);
        Serial.print(".");
    }
    // Dump info
    Serial.println("");
    Serial.println("WiFi connected!");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
    Serial.print("MAC address: ");
    Serial.println(WiFi.macAddress());
}