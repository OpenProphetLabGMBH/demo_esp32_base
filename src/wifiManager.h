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
    u8g2log.println("CONNECTING TO AP:");
    u8g2log.println(WIFI_SSID);
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
        u8g2log.println("STAION MODE");
        u8g2log.println("FAILED!");
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

#ifdef SET_STATIC_IP_FOR_STA
    logln("");
    logln("WiFi connected!");
    log("STATIC IP address: ");
    logln(WiFi.localIP());
    log("MAC address: ");
    logln(WiFi.macAddress());
#ifdef OLED_DISPLAY
    u8g2log.println("CONNECTED TO WIFI!");
    u8g2log.println("STATIC IP ADDR: ");
    u8g2log.println(WiFi.localIP());
#endif
#else
    logln("");
    logln("WiFi connected!");
    log("DNS IP address: ");
    logln(WiFi.localIP());
    log("MAC address: ");
    logln(WiFi.macAddress());
#ifdef OLED_DISPLAY
    u8g2log.println("CONNECTED TO WIFI!");
    u8g2log.println("DNS IP ADDR: ");
    u8g2log.println(WiFi.localIP());
#endif
#endif
}

void showWIFIDetailsOnOLEDscrn()
{
    u8g2log.println("\nWIFI AP:");
    u8g2log.println(WIFI_SSID);
    if (WiFi.isConnected())
    {
#ifdef SET_STATIC_IP_FOR_STA
        u8g2log.println("CONNECTED TO WIFI!");
        u8g2log.println("STATIC IP ADDR: ");
        u8g2log.println(WiFi.localIP());
#else
        u8g2log.println("CONNECTED TO WIFI!");
        u8g2log.println("DNS IP ADDR: ");
        u8g2log.println(WiFi.localIP());
#endif
    }
    else
    {
        u8g2log.println("[x] NOT CONNECTED TO WIFI!");
    }
}
