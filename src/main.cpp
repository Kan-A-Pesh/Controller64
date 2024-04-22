#include <Arduino.h>
#include <BleGamepad.h>
#include "./utils/pins.cpp"

BleGamepad bleGamepad("C0n7R0l3r", "Backrowms", 100);

void setup()
{
    pinMode(BUTTON_1_PIN, INPUT);
    pinMode(BUTTON_2_PIN, INPUT);
    pinMode(BUTTON_3_PIN, INPUT);
    pinMode(BUTTON_4_PIN, INPUT);
    pinMode(BUTTON_5_PIN, INPUT);
    pinMode(BUTTON_6_PIN, INPUT);
    pinMode(BUTTON_7_PIN, INPUT);
    pinMode(BUTTON_8_PIN, INPUT);
    pinMode(BUTTON_9_PIN, INPUT);
    pinMode(JOYSTICK_X_PIN, INPUT);
    pinMode(JOYSTICK_Y_PIN, INPUT);
    pinMode(JOYSTICK_BUTTON_PIN, INPUT);

    Serial.begin(9600);
    Serial.println("Starting BLE work!");

    bleGamepad.begin();

    // Setup controller with 16 buttons (plus start and select), accelerator, brake and steering
    BleGamepadConfiguration bleGamepadConfig;
    bleGamepadConfig.setAutoReport(false);
    bleGamepadConfig.setControllerType(CONTROLLER_TYPE_MULTI_AXIS); // CONTROLLER_TYPE_JOYSTICK, CONTROLLER_TYPE_GAMEPAD (DEFAULT), CONTROLLER_TYPE_MULTI_AXIS
    bleGamepadConfig.setButtonCount(10);
    bleGamepadConfig.setIncludeStart(false);
    bleGamepadConfig.setIncludeSelect(false);
    bleGamepadConfig.setWhichAxes(true, true, false, true, true, false, false, false);
    bleGamepadConfig.setWhichSimulationControls(false, false, false, false, false);
    bleGamepadConfig.setHatSwitchCount(1);

    // Some non-Windows operating systems and web based gamepad testers don't like min axis set below 0, so 0 is set by default
    bleGamepadConfig.setAxesMin(0x8001); // -32767 --> int16_t - 16 bit signed integer - Can be in decimal or hexadecimal
    bleGamepadConfig.setAxesMax(0x7FFF); // 32767 --> int16_t - 16 bit signed integer - Can be in decimal or hexadecimal

    // Shows how simulation control min/max axes can be set independently of the other axes
    bleGamepadConfig.setSimulationMin(-255); // -255 --> int16_t - 16 bit signed integer - Can be in decimal or hexadecimal
    bleGamepadConfig.setSimulationMax(255);  // 255 --> int16_t - 16 bit signed integer - Can be in decimal or hexadecimal

    bleGamepad.begin(&bleGamepadConfig);

    // Set x and y axes to center
    bleGamepad.setX(0);
    bleGamepad.setY(0);
}

void loop()
{
    if (!bleGamepad.isConnected())
    {
        Serial.println("BLE Gamepad is not connected");
        delay(1000);
        return;
    }

    // Check button states
    if (digitalRead(BUTTON_1_PIN) == HIGH)
        bleGamepad.press(BUTTON_1);
    else
        bleGamepad.release(BUTTON_1);

    if (digitalRead(BUTTON_2_PIN) == HIGH)
        bleGamepad.press(BUTTON_2);
    else
        bleGamepad.release(BUTTON_2);

    if (digitalRead(BUTTON_3_PIN) == HIGH)
        bleGamepad.press(BUTTON_3);
    else
        bleGamepad.release(BUTTON_3);

    if (digitalRead(BUTTON_4_PIN) == HIGH)
        bleGamepad.press(BUTTON_4);
    else
        bleGamepad.release(BUTTON_4);

    if (digitalRead(BUTTON_5_PIN) == HIGH)
        bleGamepad.press(BUTTON_5);
    else
        bleGamepad.release(BUTTON_5);

    if (digitalRead(BUTTON_6_PIN) == HIGH)
        bleGamepad.press(BUTTON_6);
    else
        bleGamepad.release(BUTTON_6);

    if (digitalRead(BUTTON_7_PIN) == HIGH)
        bleGamepad.press(BUTTON_7);
    else
        bleGamepad.release(BUTTON_7);

    if (digitalRead(BUTTON_8_PIN) == HIGH)
        bleGamepad.press(BUTTON_8);
    else
        bleGamepad.release(BUTTON_8);

    if (digitalRead(BUTTON_9_PIN) == HIGH)
        bleGamepad.press(BUTTON_9);
    else
        bleGamepad.release(BUTTON_9);

    // Print joystick X and Y axis values
    int joystickX = analogRead(JOYSTICK_X_PIN);
    int joystickY = analogRead(JOYSTICK_Y_PIN);

    joystickX = map(joystickX, 0, 4095, -100, 100);
    joystickY = map(joystickY, 0, 4095, -100, 100);

    bleGamepad.setX(joystickX);
    bleGamepad.setY(joystickY);

    // Check joystick button state
    if (digitalRead(JOYSTICK_BUTTON_PIN) == HIGH)
        bleGamepad.press(BUTTON_10);
    else
        bleGamepad.release(BUTTON_10);

    delay(100);
}
