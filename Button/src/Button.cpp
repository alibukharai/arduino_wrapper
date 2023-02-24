#include "Button.h"
#include "original/button_gpio.h"
#include "original/button_adc.h"
#include "original/iot_button.h"


Button::Button(int pin, const bool pullup)
{

    _buttonPin = pin;
    pinMode(_buttonPin, pullup ? INPUT_PULLUP : INPUT_PULLDOWN);

    button_config_t cfg = {
        .type = BUTTON_TYPE_GPIO,
        .long_press_time = CONFIG_BUTTON_LONG_PRESS_TIME_MS,
        .short_press_time = CONFIG_BUTTON_SHORT_PRESS_TIME_MS,
        .gpio_button_config = {
            .gpio_num = pin,
            .active_level = pullup
        }
    };
    _handle = iot_button_create(&cfg);
    Serial.println("Button Created");
}


Button::Button(int pin, const bool pullup, uint8_t adc_channel, uint8_t button_index, uint16_t min, uint16_t max)
{
    _buttonPin = pin;
    pinMode(_buttonPin, pullup ? INPUT_PULLUP : INPUT_PULLDOWN);

    button_config_t cfg = {
        .type = BUTTON_TYPE_ADC,
        .long_press_time = CONFIG_BUTTON_LONG_PRESS_TIME_MS,
        .short_press_time = CONFIG_BUTTON_SHORT_PRESS_TIME_MS,
        {
            .adc_button_config = {
                .adc_channel = adc_channel,
                .button_index = button_index,
                .min = min,
                .max = max
            }
        }
    };
    _handle = iot_button_create(&cfg);
    Serial.println("Button Created");
}


void Button::attachPressDown(callbackFunction newFunction)
{
    if (newFunction != NULL) {
        this->_press_down_user_cb = newFunction;
        iot_button_register_cb(_handle, BUTTON_PRESS_DOWN, &_press_down_cb, this);
    }
}
void _press_down_cb(void *arg, void *data)
{
    Button *my_instance = (Button *)data;
    if (my_instance->_press_down_user_cb != NULL) {
        my_instance->_press_down_user_cb();
    }
}

void Button::attachPressUp(callbackFunction newFunction)
{
    if (newFunction != NULL) {
        this->_press_up_user_cb = newFunction;
        iot_button_register_cb(_handle, BUTTON_PRESS_UP, &_press_up_cb, this);
    }
}

void _press_up_cb(void *arg, void *data)
{
    Button *my_instance = (Button *)data;
    if (my_instance->_press_up_user_cb != NULL) {
        my_instance->_press_up_user_cb();
    }
}

void Button::attachPressRepeat(callbackFunction newFunction)
{
    if (newFunction != NULL) {
        this->_press_repeat_user_cb = newFunction;
        iot_button_register_cb(_handle, BUTTON_PRESS_REPEAT, &_press_repeat_cb, this);
    }
}

void _press_repeat_cb(void *arg, void *data)
{
    Button *my_instance = (Button *)data;
    if (my_instance->_press_repeat_user_cb != NULL) {
        my_instance->_press_repeat_user_cb();
    }
}

void Button::attachSingleClick(callbackFunction newFunction)
{
    if (newFunction != NULL) {
        this->_press_single_click_user_cb = newFunction;
        iot_button_register_cb(_handle, BUTTON_SINGLE_CLICK, &_press_single_click_cb, this);
    }
}

void _press_single_click_cb(void *arg, void *data)
{
    Button *my_instance = (Button *)data;
    if (my_instance->_press_single_click_user_cb != NULL) {
        my_instance->_press_single_click_user_cb();
    }
}

void Button::attachDoubleClick(callbackFunction newFunction)
{
    if (newFunction != NULL) {
        this->_press_double_click_user_cb = newFunction;
        iot_button_register_cb(_handle, BUTTON_DOUBLE_CLICK, &_press_double_click_cb, this);
    }
}

void _press_double_click_cb(void *arg, void *data)
{
    Button *my_instance = (Button *)data;
    if (my_instance->_press_double_click_user_cb != NULL) {
        my_instance->_press_double_click_user_cb();
    }
}

void Button::attachLongPressStart(callbackFunction newFunction)
{
    if (newFunction != NULL) {
        this->_press_long_press_start_user_cb = newFunction;
        iot_button_register_cb(_handle, BUTTON_LONG_PRESS_START, &_press_long_press_start_cb, this);
    }
}

void _press_long_press_start_cb(void *arg, void *data)
{
    Button *my_instance = (Button *)data;
    if (my_instance->_press_long_press_start_user_cb != NULL) {
        my_instance->_press_long_press_start_user_cb();
    }
}

void Button::attachLongPressHold(callbackFunction newFunction)
{
    if (newFunction != NULL) {
        this->_press_long_press_hold_user_cb = newFunction;
        iot_button_register_cb(_handle, BUTTON_LONG_PRESS_HOLD, &_press_long_press_hold_cb, this);
    }
}

void _press_long_press_hold_cb(void *arg, void *data)
{
    Button *my_instance = (Button *)data;
    if (my_instance->_press_long_press_hold_user_cb != NULL) {
        my_instance->_press_long_press_hold_user_cb();
    }
}

void Button::attachPressRepeatDone(callbackFunction newFunction)
{
    if (newFunction != NULL) {
        this->_press_repeat_done_user_cb = newFunction;
        iot_button_register_cb(_handle, BUTTON_PRESS_REPEAT_DONE, &_press_repeat_done_cb, this);
    }
}

void _press_repeat_done_cb(void *arg, void *data)
{
    Button *my_instance = (Button *)data;
    if (my_instance->_press_repeat_done_user_cb != NULL) {
        my_instance->_press_repeat_done_user_cb();
    }
}

void Button::deleteButton(void)
{
    iot_button_delete(_handle);
    Serial.println("Button Deleted");
}

void Button::detachPressDown(void)
{
    iot_button_unregister_cb(_handle, BUTTON_PRESS_DOWN);
    Serial.println("Event Button Press Down deatched");
}

void Button::detachPressUp(void)
{
    iot_button_unregister_cb(_handle, BUTTON_PRESS_UP);
    Serial.println("Event Button Press Up deatched");
}

void Button::detachPressRepeat(void)
{
    iot_button_unregister_cb(_handle, BUTTON_PRESS_REPEAT);
    Serial.println("Event Button Press Repeat deatched");
}

void Button::detachSingleClick(void)
{
    iot_button_unregister_cb(_handle, BUTTON_SINGLE_CLICK);
    Serial.println("Event Button Single Click deatched");
}

void Button::detachDoubleClick(void)
{
    iot_button_unregister_cb(_handle, BUTTON_DOUBLE_CLICK);
    Serial.println("Event Button Double Click deatched");
}

void Button::detachLongPressStart(void)
{
    iot_button_unregister_cb(_handle, BUTTON_LONG_PRESS_START);
    Serial.println("Event Button Long Press Start deatched");
}

void Button::detachLongPressHold(void)
{
    iot_button_unregister_cb(_handle, BUTTON_LONG_PRESS_HOLD);
    Serial.println("Event Button Long Press Hold deatched");
}

void Button::detachPressRepeatDone(void)
{
    iot_button_unregister_cb(_handle, BUTTON_PRESS_REPEAT_DONE);
    Serial.println("Event Button Press Repeat Done deatched");
}

size_t Button::countCallBack(void)
{
    return iot_button_count_cb(_handle);
}

int Button::getEvent(void)
{
    return iot_button_get_event(_handle);
}

u_int8_t Button::getRepeat(void)
{
    return iot_button_get_repeat(_handle);
}

u_int16_t Button::getTickTime(void)
{
    return iot_button_get_ticks_time(_handle);
}

u_int16_t Button::getLongPressHoldCount(void)
{
    return iot_button_get_long_press_hold_cnt(_handle);
}
