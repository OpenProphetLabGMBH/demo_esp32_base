/**
 * @brief
 *
 */

// WIFI CONFIGS 
// #define SET_STATIC_IP                            // Comment it if you do not want a static IP address.
#ifdef SET_STATIC_IP
#define STATIC_IP_ADDR    {192, 168, 52, 18}      // Static IP address that you want to give your esp32.
#define GATEWAY_IP_ADDR   {192, 168, 52, 1}       // IP address of the WIFI Router.
#define SUBNET_ADDR      {255, 255, 255, 0}
#endif


// MQTT CONFIGS
// #define MQTT_HAS_PWD                            // Comment it if the MQTT broker doesn't have security ctrl via username and pwd.
#ifdef MQTT_HAS_PWD
#define MQTT_USERNAME   "prophet_x&i_lab"       // if our MQTT broker has a security ctrl, update the usrname here. 
#define MQTT_PASSWORD   "Arpita_1491"           // if our MQTT broker has a security ctrl, update the pwd here. 
#endif
