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
    if (millis() - lastTimePressed < debouncePeriod)
        return;
    lastTimePressed = millis();

    logln("Btn Pressed!");
    log("Sending MQTT data: ");
    logln("client/esp32_1_knob/button/state: pressed\n");

    esp32MQTTclient.publish("client/esp32_1_knob/button/state", "pressed");
    // esp32MQTTclient.publish(String(MQTT_PUBS_TOPICS[1]).c_str(), "pressed");
}

void watchLoopEncoder()
{
    // Don't print anything unless value changed.
    if (rotaryEncoder.encoderChanged())
    {
        long encoderValInt = rotaryEncoder.readEncoder();
        //  For printing and for publishing to MQTT broker we need to conver that to a char* array.
        char encoderValStr[(((sizeof encoderValInt) * CHAR_BIT) + 2) / 3 + 2];
        itoa(encoderValInt, encoderValStr, 10);

        logln("Encoder Value: " + String(encoderValStr));
        log("Sending MQTT data: ");
        logln("client/esp32_1_knob/encoder/value: " + String(encoderValStr) + "\n");

        esp32MQTTclient.publish("client/esp32_1_knob/encoder/value", encoderValStr);
        // esp32MQTTclient.publish(String(MQTT_PUBS_TOPICS[2]).c_str(), encoderValStr);
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
