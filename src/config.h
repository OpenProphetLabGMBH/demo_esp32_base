/**
 * @brief
 *
 */

#ifdef MONITOR
#define log(x) Serial.print(x);
#define logln(x) Serial.println(x);
#define loglnHex(x) Serial.println(x, HEX);
#define logHex(x) Serial.print(x, HEX);
#else
#define log(x) x;
#define logln(x) x;
#define loglnHex(x) x;
#define logHex(x) x;
#endif

#ifdef OLED_DISPLAY
#define scr_prnt(x) oled.print(x);
#else
#define scr_prnt(x) x;
#endif

// ------------------------------------------------------------------------------------------------------------ //
// For SSD1306 OLED 128x32 screen related
// ------------------------------------------------------------------------------------------------------------ //
#define OLED_RESET_PIN 17                    // Reset pin # (or -1 if sharing Arduino reset pin)
uint8_t SSD1306_ADDRESSES[2] = {0x3c, 0x3D}; // LUT for ssd1306 oled displays, used to validate discovered addr.
uint8_t OLED_SCREEN_ADDRESS = 0x3C;          //< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
// On board OLED display's parameters (for our SSD1306-128x32)
// Note: If you are using another SSD1306 screen resolution, say 128x64, then change the screen height ...
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32

// ------------------------------------------------------------------------------------------------------------ //
// For Rorary Encoder with Button related
// ------------------------------------------------------------------------------------------------------------ //
#define ROTARY_ENCODER_DATA_PIN 23
#define ROTARY_ENCODER_CLCK_PIN 19
#define ROTARY_ENCODER_BTN_PIN 22
#define ROTARY_ENCODER_VCC_PIN -1 // Put -1 if the VCC of encoder is tied to VCC pin on the borard directly.
static unsigned long debouncePeriod = 10;
