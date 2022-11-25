/**
 * @brief
 *
 */

#include <WiFi.h>

// A method that connects to a given wifi AP and tries to assign a static IP address (defined in config.h).
void connectToWifi()
{
    delay(2000);
    log("Connecting to: ");
    logln(WIFI_SSID);
#ifdef OLED_DISPLAY
    oled.clearDisplay();
    oled.setCursor(0, 0);
    oled.println("Connecting to AP:\n\n");
    oled.println(WIFI_SSID)
        oled.display();
#endif

// Giving the esp32 a ststic IP, after it connects to the WIFI.
#ifdef SET_STATIC_IP_FOR_STA
    IPAddress staticIP(STA_STATIC_IP_ADDR); // Set your Static IP address.
    IPAddress gateway(STA_GATEWAY_IP_ADDR); // Set your Gateway IP address.
    IPAddress subnet(STA_SUBNET_ADDR);
    if (!WiFi.config(staticIP, gateway, subnet))
    {
        logln("STA Failed to configure");
#ifdef OLED_DISPLAY
        oled.clearDisplay();
        oled.setCursor(0, 0);
        oled.println("STA Failed to\n\nconfigure");
        oled.display();
#endif
    }
#endif
    // Start to connect to WIFI
    WiFi.begin(WIFI_SSID, WIFI_PWD);
    // Check if WIFI is connected ornot
    while (WiFi.status() != WL_CONNECTED || WiFi.status() != 3)
    {
        delay(100);
        log(".");
    }
    // Dump info

#ifdef SET_STATIC_IP_FOR_STA
    logln("");
    logln("WiFi connected!");
    log("STATIC IP address: ");
    logln(WiFi.localIP());
    log("MAC address: ");
    logln(WiFi.macAddress());
#ifdef OLED_DISPLAY
    oled.clearDisplay();
    oled.setCursor(0, 0);
    oled.println("STATIC IP address: ");
    oled.display();
#endif
#else
    logln("");
    logln("WiFi connected!");
    log("DNS IP address: ");
    logln(WiFi.localIP());
    log("MAC address: ");
    logln(WiFi.macAddress());
#ifdef OLED_DISPLAY
    oled.clearDisplay();
    oled.setCursor(0, 0);
    oled.println("DNS IP address: ");
    oled.display();
#endif
#endif
}
