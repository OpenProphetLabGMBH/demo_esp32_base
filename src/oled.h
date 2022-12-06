/**
 * @brief
 *
 */

#include <Wire.h>
#include <U8g2lib.h>

U8G2_SSD1306_128X64_NONAME_F_SW_I2C u8g2(U8G2_R0, OLED_CLK_PIN, OLED_DATA_PIN, /* reset=*/U8X8_PIN_NONE);
U8G2LOG u8g2log;
uint8_t u8log_buffer[U8LOG_WIDTH * U8LOG_HEIGHT];
boolean ENABLE_OLED = false;

// --- OLED display's i2c addr auto-discovery feature --- //
uint8_t getDisplayAddr()
{
    uint8_t error = 1;
    uint8_t address = 0x00;
    uint8_t foundAddr = 0x00;
    int nDevices = 0;

    // Buffer time to let the device initialize
    delay(100);

    for (address = 1; address < 127; address++)
    {
        // The i2c_scanner uses the return value of
        // the Write.endTransmisstion to see if
        // a device did acknowledge to the address.
        Wire.beginTransmission(address);
        error = Wire.endTransmission();
        if (error == 0)
        {
            foundAddr = address;
            logln("Found a i2c slave!");
            nDevices++;
            break;
        }
        else if (error == 4)
        {
            log("Error code: ");
            logln(error);
            log(F("Unknown error at address 0x"));
            logHex(foundAddr);
            logln("\n");
            break;
        }
    }

    if (nDevices == 0)
    {
        logln("No I2C devices found\n");
    }
    else
    {
        log("i2C SLAVE'S ADDR: [ Hex: 0x");
        logHex(foundAddr);
        log(", Binary: ");
        log(foundAddr);
        logln("]");
    }
    return foundAddr;
}

boolean validAddr(uint8_t _addr)
{
    bool isValidAddr = false;
    for (byte i = 0; i < sizeof(SSD1306_ADDRESSES); i++)
    {
        if (_addr == SSD1306_ADDRESSES[i])
        {
            isValidAddr = true;
            log("ADDR ");
            logHex(_addr);
            logln(" found in LUT");

            break;
        }
        else
        {
            isValidAddr = false;
        }
    }
    return isValidAddr;
}

void setupOLEDdisplay()
{
    logln("---------------------------------------------------------");
    logln("OLED SCREEN INIT SECTION");
    logln("---------------------------------------------------------");
    Wire.begin(22, 19);
    OLED_SCREEN_ADDRESS = getDisplayAddr();
    Wire.end();
    if (validAddr(OLED_SCREEN_ADDRESS))
    {
        ENABLE_OLED = true;
        logln("\nOLED SSD1306 CAN BE INITIATED!\n");
    }
    else
    {
        ENABLE_OLED = false;
        logln(F("\n[x] OLED SSD1306 CAN NOT BE INITIATED\n"));
    }
    if (ENABLE_OLED)
    {
        // SETUP OLED
        u8g2.begin();
        u8g2.setFont(u8g2_font_5x7_mf); // set the font for the terminal window
        u8g2log.begin(u8g2, U8LOG_WIDTH, U8LOG_HEIGHT, u8log_buffer);
        u8g2log.setLineHeightOffset(0); // set extra space between lines in pixel, this can be negative
        u8g2log.setRedrawMode(0);       // 0: Update screen with newline, 1: Update screen for every char
    }

    // .. for test:
    // ENABLE_OLED = false;
}
