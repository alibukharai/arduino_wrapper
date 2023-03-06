// Include required header files
#include "Button.h"
#include "original/button_gpio.h"
#include "original/button_adc.h"
#include "original/iot_button.h"

// Constructor for button using GPIO pin
Button::Button(int pin, const bool pullup)
{

    _buttonPin = pin;

    // Set pin mode based on pullup parameter
    pinMode(_buttonPin, pullup ? INPUT_PULLUP : INPUT_PULLDOWN);

    // Configure button using GPIO
    button_config_t cfg = {
        .type = BUTTON_TYPE_GPIO, // Set button type as GPIO
        .long_press_time = CONFIG_BUTTON_LONG_PRESS_TIME_MS, // Set long press time
        .short_press_time = CONFIG_BUTTON_SHORT_PRESS_TIME_MS, // Set short press time
        .gpio_button_config = {
            .gpio_num = pin, // Set GPIO pin number
            .active_level = pullup // Set active level based on pullup parameter
        }
    };
    _handle = iot_button_create(&cfg);
    // Print button created message for debugging purposes
    Serial.println("Button Created");
}

// Constructor for button using ADC pin
Button::Button(int pin, const bool pullup, uint8_t adc_channel, uint8_t button_index, uint16_t min, uint16_t max)
{
    _buttonPin = pin;

    // Set pin mode based on pullup parameter
    pinMode(_buttonPin, pullup ? INPUT_PULLUP : INPUT_PULLDOWN);

    // Configure button using ADC
    button_config_t cfg = {
        .type = BUTTON_TYPE_ADC, // Set button type as ADC
        .long_press_time = CONFIG_BUTTON_LONG_PRESS_TIME_MS, // Set long press time
        .short_press_time = CONFIG_BUTTON_SHORT_PRESS_TIME_MS, // Set short press time
        {
            .adc_button_config = {
                .adc_channel = adc_channel, // Set ADC channel
                .button_index = button_index, // Set button index
                .min = min, // Set minimum ADC reading
                .max = max // Set maximum ADC reading
            }
        }
    };
    // Create button handle
    _handle = iot_button_create(&cfg);
    // Print button created message for debugging purposes
    Serial.println("Button Created");
}

// Method to attach callback function for button press down event
void Button::attachPressDown(callbackFunction newFunction)
{
    if (newFunction != NULL) {
        this->_press_down_user_cb = newFunction;
        iot_button_register_cb(_handle, BUTTON_PRESS_DOWN, &_press_down_cb, this);
    }
}

// Internal callback function for button press down event
void _press_down_cb(void *arg, void *data)
{
    Button *my_instance = (Button *)data;
    if (my_instance->_press_down_user_cb != NULL) {
        my_instance->_press_down_user_cb();
    }
}
// Method to attach callback function for button press up event
void Button::attachPressUp(callbackFunction newFunction)
{
    if (newFunction != NULL) {
        this->_press_up_user_cb = newFunction;
        iot_button_register_cb(_handle, BUTTON_PRESS_UP, &_press_up_cb, this);
    }
}

// Internal callback function for button press up event
void _press_up_cb(void *arg, void *data)
{
    Button *my_instance = (Button *)data;
    if (my_instance->_press_up_user_cb != NULL) {
        my_instance->_press_up_user_cb();
    }
}

// Method to attach callback function for button press repeat event
void Button::attachPressRepeat(callbackFunction newFunction)
{
    if (newFunction != NULL) {
        this->_press_repeat_user_cb = newFunction;
        iot_button_register_cb(_handle, BUTTON_PRESS_REPEAT, &_press_repeat_cb, this);
    }
}

// Internal callback function for button press repeat event
void _press_repeat_cb(void *arg, void *data)
{
    Button *my_instance = (Button *)data;
    if (my_instance->_press_repeat_user_cb != NULL) {
        my_instance->_press_repeat_user_cb();
    }
}
// Method to attach callback function for button single click event
void Button::attachSingleClick(callbackFunction newFunction)
{
    if (newFunction != NULL) {
        this->_press_single_click_user_cb = newFunction;
        iot_button_register_cb(_handle, BUTTON_SINGLE_CLICK, &_press_single_click_cb, this);
    }
}

// Internal callback function for button single click event
void _press_single_click_cb(void *arg, void *data)
{
    Button *my_instance = (Button *)data;
    if (my_instance->_press_single_click_user_cb != NULL) {
        my_instance->_press_single_click_user_cb();
    }
}
// Method to attach callback function for button double click event
void Button::attachDoubleClick(callbackFunction newFunction)
{
    if (newFunction != NULL) {
        this->_press_double_click_user_cb = newFunction;
        iot_button_register_cb(_handle, BUTTON_DOUBLE_CLICK, &_press_double_click_cb, this);
    }
}

// Internal callback function for button double click event
void _press_double_click_cb(void *arg, void *data)
{
    Button *my_instance = (Button *)data;
    if (my_instance->_press_double_click_user_cb != NULL) {
        my_instance->_press_double_click_user_cb();
    }
}
// Method to attach callback function for button long press start event
void Button::attachLongPressStart(callbackFunction newFunction)
{
    if (newFunction != NULL) {
        this->_press_long_press_start_user_cb = newFunction;
        iot_button_register_cb(_handle, BUTTON_LONG_PRESS_START, &_press_long_press_start_cb, this);
    }
}

// Internal callback function for button long press start event
void _press_long_press_start_cb(void *arg, void *data)
{
    Button *my_instance = (Button *)data;
    if (my_instance->_press_long_press_start_user_cb != NULL) {
        my_instance->_press_long_press_start_user_cb();
    }
}
// Method to attach callback function for button long press hold event
void Button::attachLongPressHold(callbackFunction newFunction)
{
    if (newFunction != NULL) {
        this->_press_long_press_hold_user_cb = newFunction;
        iot_button_register_cb(_handle, BUTTON_LONG_PRESS_HOLD, &_press_long_press_hold_cb, this);
    }
}

// Internal callback function for button long press hold event
void _press_long_press_hold_cb(void *arg, void *data)
{
    Button *my_instance = (Button *)data;
    if (my_instance->_press_long_press_hold_user_cb != NULL) {
        my_instance->_press_long_press_hold_user_cb();
    }
}
// Method to attach callback function for button press repeat done event
void Button::attachPressRepeatDone(callbackFunction newFunction)
{
    if (newFunction != NULL) {
        this->_press_repeat_done_user_cb = newFunction;
        iot_button_register_cb(_handle, BUTTON_PRESS_REPEAT_DONE, &_press_repeat_done_cb, this);
    }
}

// Internal callback function for button press repeat done event
void _press_repeat_done_cb(void *arg, void *data)
{
    Button *my_instance = (Button *)data;
    if (my_instance->_press_repeat_done_user_cb != NULL) {
        my_instance->_press_repeat_done_user_cb();
    }
}

// Method to delete button
void Button::deleteButton(void)
{
    iot_button_delete(_handle);
    Serial.println("Button Deleted");
}

// Method to detach button press down event
void Button::detachPressDown(void)
{
    iot_button_unregister_cb(_handle, BUTTON_PRESS_DOWN);
    Serial.println("Event Button Press Down deatched");
}
// Method to detach button press up event
void Button::detachPressUp(void)
{
    iot_button_unregister_cb(_handle, BUTTON_PRESS_UP);
    Serial.println("Event Button Press Up deatched");
}
// Method to detach button press repeat event
void Button::detachPressRepeat(void)
{
    iot_button_unregister_cb(_handle, BUTTON_PRESS_REPEAT);
    Serial.println("Event Button Press Repeat deatched");
}

// Method to detach button single click event
void Button::detachSingleClick(void)
{
    iot_button_unregister_cb(_handle, BUTTON_SINGLE_CLICK);
    Serial.println("Event Button Single Click deatched");
}

// Method to detach button double click event
void Button::detachDoubleClick(void)
{
    iot_button_unregister_cb(_handle, BUTTON_DOUBLE_CLICK);
    Serial.println("Event Button Double Click deatched");
}

// Method to detach button long press start event
void Button::detachLongPressStart(void)
{
    iot_button_unregister_cb(_handle, BUTTON_LONG_PRESS_START);
    Serial.println("Event Button Long Press Start deatched");
}
// Method to detach button long press hold event
void Button::detachLongPressHold(void)
{
    iot_button_unregister_cb(_handle, BUTTON_LONG_PRESS_HOLD);
    Serial.println("Event Button Long Press Hold deatched");
}
// Method to detach button repeat down event
void Button::detachPressRepeatDone(void)
{
    iot_button_unregister_cb(_handle, BUTTON_PRESS_REPEAT_DONE);
    Serial.println("Event Button Press Repeat Done deatched");
}

// Method to count call back
size_t Button::countCallBack(void)
{
    return iot_button_count_cb(_handle);
}
// Method to get event
int Button::getEvent(void)
{
    return iot_button_get_event(_handle);
}
// Method to get repeat
u_int8_t Button::getRepeat(void)
{
    return iot_button_get_repeat(_handle);
}

// Method to get tick time
u_int16_t Button::getTickTime(void)
{
    return iot_button_get_ticks_time(_handle);
}
// Method to get long press hold count
u_int16_t Button::getLongPressHoldCount(void)
{
    return iot_button_get_long_press_hold_cnt(_handle);
}
