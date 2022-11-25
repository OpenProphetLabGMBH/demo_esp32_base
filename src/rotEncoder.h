/**
 * @brief
 *
 */

#include "AiEsp32RotaryEncoder.h"

// Depending on your encoder - try 1,2 or 4 to get expected behaviour.
// #define ROTARY_ENCODER_STEPS 1
// #define ROTARY_ENCODER_STEPS 2
#define ROTARY_ENCODER_STEPS 4

// Instead of changing here, rather change numbers above.
AiEsp32RotaryEncoder rotaryEncoder = AiEsp32RotaryEncoder(
    ROTARY_ENCODER_DATA_PIN,
    ROTARY_ENCODER_CLCK_PIN,
    ROTARY_ENCODER_BTN_PIN,
    ROTARY_ENCODER_VCC_PIN,
    ROTARY_ENCODER_STEPS);

void IRAM_ATTR readEncoderISR()
{
    rotaryEncoder.readEncoder_ISR();
}

void rotaryOnButtonClick()
{
    static unsigned long lastTimePressed = 0;
    // Ignore multiple press in that time milliseconds.
    if (millis() - lastTimePressed < 20)
    {
        return;
    }
    lastTimePressed = millis();
    log("button pressed ");
    log(millis());
    logln(" milliseconds after restart");
}

void rotaryLoop()
{
    // Don't print anything unless value changed.
    if (rotaryEncoder.encoderChanged())
    {
        log("Value: ");
        logln(rotaryEncoder.readEncoder());
    }
    if (rotaryEncoder.isEncoderButtonClicked())
    {
        rotaryOnButtonClick();
    }
}

void setupEncoder()
{
    // we must initialize rotary encoder
    rotaryEncoder.begin();
    rotaryEncoder.setup(readEncoderISR);
    // set boundaries and if values should cycle or not
    // in this example we will set possible values between 0 and 1000;
    bool circleValues = true;
    rotaryEncoder.setBoundaries(0, 500, circleValues); // minValue, maxValue, circleValues true|false (when max go to min and vice versa)

    /*Rotary acceleration introduced 25.2.2021.
     * in case range to select is huge, for example - select a value between 0 and 1000 and we want 785
     * without accelerateion you need long time to get to that number
     * Using acceleration, faster you turn, faster will the value raise.
     * For fine tuning slow down.
     */
    // rotaryEncoder.disableAcceleration(); //acceleration is now enabled by default - disable if you dont need it
    rotaryEncoder.setAcceleration(100); // or set the value - larger number = more accelearation; 0 or 1 means disabled acceleration
}