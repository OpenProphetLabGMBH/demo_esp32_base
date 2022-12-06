/**
 * @brief
 *
 */

#include <Arduino.h>
#include <AceButton.h>
using namespace ace_button;

const int BUTTON_PIN = 12;

bool GPIO_BTN_CLICKED = false;

// Automatically uses the default ButtonConfig. We will configure this later
// using AceButton::init() method in setup() below.
AceButton button(BUTTON_PIN);

// Forward reference to prevent Arduino compiler becoming confused.
void handleEvent(AceButton *, uint8_t, uint8_t);

void setupButtons()
{
    pinMode(BUTTON_PIN, INPUT_PULLUP);
    // button.init(BUTTON_PIN, LOW);

    // Configure the ButtonConfig with the event handler, and enable all higher
    // level events.
    ButtonConfig *buttonConfig = button.getButtonConfig();
    buttonConfig->setEventHandler(handleEvent);
    buttonConfig->setFeature(ButtonConfig::kFeatureClick);
    buttonConfig->setFeature(ButtonConfig::kFeatureDoubleClick);
    buttonConfig->setFeature(ButtonConfig::kFeatureLongPress);
    buttonConfig->setFeature(ButtonConfig::kFeatureRepeatPress);

    // Check if the button was pressed while booting
    if (button.isPressedRaw())
    {
        logln("setup(): button was pressed while booting");
    }
}

void watchGPIOButtons()
{
    // Should be called every 4-5ms or faster, for the default debouncing time
    // of ~20ms.
    button.check();
}

// The event handler for the button.
void handleEvent(AceButton * /* button */, uint8_t eventType, uint8_t buttonState)
{
    switch (eventType)
    {
    case AceButton::kEventClicked:
        logln("GPIO button Clicked!");
        GPIO_BTN_CLICKED = true;
        break;
    }
}