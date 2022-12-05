/**
 * @brief
 *
 */

#include "AiEsp32RotaryEncoder.h"

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

void onEncoderBtnClick()
{
    static unsigned long lastTimePressed = 0;
    // Ignore multiple press in that time milliseconds.
    if (millis() - lastTimePressed < debouncePeriod)
        return;
    lastTimePressed = millis();

    logln("Btn clicked!");
    logln("Publishing:");
    logln(String(MQTT_PUBS_TOPICS[1]) + ": " + String(MQTT_PUBS_MSGS[1]) + "\n");
    esp32MQTTclient.publish(MQTT_PUBS_TOPICS[1], MQTT_PUBS_MSGS[1]);
}

bool encoderBtnState = false;
bool encoderBtnPrevState = false;
void onEncoderBtnEvent()
{
    if (encoderBtnState != encoderBtnPrevState)
    {
        if (encoderBtnState)
        {
            logln("Btn pressed");
            logln("Publishing:");
            logln(String(MQTT_PUBS_TOPICS[1]) + ": " + String(MQTT_PUBS_MSGS[2]) + "\n");
            esp32MQTTclient.publish(MQTT_PUBS_TOPICS[1], MQTT_PUBS_MSGS[2]);
        }
        else
        {
            logln("Btn released");
            logln("Publishing:");
            logln(String(MQTT_PUBS_TOPICS[1]) + ": " + String(MQTT_PUBS_MSGS[3]) + "\n");
            esp32MQTTclient.publish(MQTT_PUBS_TOPICS[1], MQTT_PUBS_MSGS[3]);
        }
        encoderBtnPrevState = encoderBtnState;
    }
}

long prevEncoderVal = 0;
void watchLoopEncoder()
{
    // Don't print anything unless value changed.
    if (rotaryEncoder.encoderChanged())
    {
        long encoderValInt = rotaryEncoder.readEncoder();
        // Convert to str, for printing and for publishing to MQTT broker we need to conver that to a char* array.
        char encoderValStr[(((sizeof encoderValInt) * CHAR_BIT) + 2) / 3 + 2];
        itoa(encoderValInt, encoderValStr, 10);
        logln("Encoder Value: " + String(encoderValStr));

        if (encoderValInt > prevEncoderVal)
        {
            logln("DIRECTION: forward [>]");
            logln("Publishing:");
            logln(String(MQTT_PUBS_TOPICS[3]) + ": " + String(MQTT_PUBS_MSGS[4]) + "\n");
            esp32MQTTclient.publish(MQTT_PUBS_TOPICS[3], MQTT_PUBS_MSGS[4]);
        }
        if (encoderValInt < prevEncoderVal)
        {
            logln("DIRECTION: backward [<]");
            logln("Publishing:");
            logln(String(MQTT_PUBS_TOPICS[3]) + ": " + String(MQTT_PUBS_MSGS[5]) + "\n");
            esp32MQTTclient.publish(MQTT_PUBS_TOPICS[3], MQTT_PUBS_MSGS[5]);
        }
        prevEncoderVal = encoderValInt;

        // Additinally, after sending direction, also send teh raw angle.
        logln(String(MQTT_PUBS_TOPICS[2]) + ": " + String(encoderValStr) + "\n");
        esp32MQTTclient.publish(MQTT_PUBS_TOPICS[2], encoderValStr);
    }
    if (rotaryEncoder.isEncoderButtonClicked())
    {
        onEncoderBtnClick();
    }
    if (rotaryEncoder.isEncoderButtonDown())
    {
        encoderBtnState = true;
        onEncoderBtnEvent();
    }
    else
    {
        encoderBtnState = false;
        onEncoderBtnEvent();
    }
}

void setupEncoder()
{
    // we must initialize rotary encoder
    rotaryEncoder.begin();
    rotaryEncoder.setup(readEncoderISR);
    // set boundaries and if values should cycle or not
    // in this example we will set possible values between 0 and 1000;

    rotaryEncoder.setBoundaries(MIN_ENCODER_VAL, MAX_ENCODER_VAL, CIRCLE_VALUES); // minValue, maxValue, circleValues true|false (when max go to min and vice versa)

    /*Rotary acceleration introduced 25.2.2021.
     * in case range to select is huge, for example - select a value between 0 and 1000 and we want 785
     * without accelerateion you need long time to get to that number
     * Using acceleration, faster you turn, faster will the value raise.
     * For fine tuning slow down.
     */
    // rotaryEncoder.disableAcceleration(); //acceleration is now enabled by default - disable if you dont need it
    rotaryEncoder.setAcceleration(100); // or set the value - larger number = more accelearation; 0 or 1 means disabled acceleration
}
