/**
 * @brief
 *
 */

// WIFI CONFIGS 
#define wifi_ssid       "SDPAP"                 // Update WIFI AP name according to your WIFI settings.
#define wifi_pwd        "Arpita_1491"           // Update WIFI AP PWD according to your WIFI settings.

// #define setStaticIP                             // Comment it if you do not want a static IP address.
#ifdef setStaticIP
#define staticIPAddr    {192, 168, 52, 18}      // Static IP address that you want to give your esp32.
#define gatewayIPAddr   {192, 168, 52, 1}       // IP address of the WIFI Router.
#define subnetAddr      {255, 255, 255, 0}
#endif


// MQTT CONFIGS
#define mqtt_broker     "192.168.52.106"        // IP address ofthe MQTT broker.
#define mqtt_port       1883                    // Port for the MQTT broker.

// #define MQTT_HAS_PWD                            // Comment it if the MQTT broker doesn't have security ctrl via username and pwd.
#ifdef MQTT_HAS_PWD
#define MQTT_USERNAME   "prophet_x&i_lab"       // if our MQTT broker has a security ctrl, update the usrname here. 
#define MQTT_PASSWORD   "Arpita_1491"           // if our MQTT broker has a security ctrl, update the pwd here. 
#endif
