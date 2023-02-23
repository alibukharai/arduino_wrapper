#ifndef BUTTON_H
#define BUTTON_H
#include <Arduino.h>
#include "iot_button.h"

typedef void (*callbackFunction)(void);
void _press_down_cb(void *arg, void *data);
void _press_up_cb(void *arg, void *data);
void _press_repeat_cb(void *arg, void *data);
void _press_single_click_cb(void *arg, void *data);
void _press_double_click_cb(void *arg, void *data);
void _press_long_press_start_cb(void *arg, void *data);
void _press_long_press_hold_cb(void *arg, void *data);
void _press_repeat_done_cb(void *arg, void *data);


class Button {

private:
    int _buttonPin;
    button_handle_t _handle;

public:
    Button(int pin, const bool pullup);
    Button(int pin, const bool pullup, uint8_t adc_channel, uint8_t button_index, uint16_t min, uint16_t max);

    void attachPressDown(callbackFunction newFunction);
    void attachPressUp(callbackFunction newFunction);
    void attachPressRepeat(callbackFunction newFunction);
    void attachSingleClick(callbackFunction newFunction);
    void attachDoubleClick(callbackFunction newFunction);
    void attachLongPressStart(callbackFunction newFunction);
    void attachLongPressHold(callbackFunction newFunction);
    void attachPressRepeatDone(callbackFunction newFunction);

    callbackFunction _press_down_user_cb = NULL;
    callbackFunction _press_up_user_cb = NULL;
    callbackFunction _press_repeat_user_cb = NULL;
    callbackFunction _press_single_click_user_cb = NULL;
    callbackFunction _press_double_click_user_cb = NULL;
    callbackFunction _press_long_press_start_user_cb = NULL;
    callbackFunction _press_long_press_hold_user_cb = NULL;
    callbackFunction _press_repeat_done_user_cb = NULL;

    void detachPressDown(void);
    void detachPressUp(void);
    void detachPressRepeat(void);
    void detachSingleClick(void);
    void detachDoubleClick(void);
    void detachLongPressStart(void);
    void detachLongPressHold(void);
    void detachPressRepeatDone(void);

    void deleteButton(void);
    size_t countCallBack(void);
    int getEvent(void);
    u_int8_t getRepeat(void);
    u_int16_t getTickTime(void);
    u_int16_t getLongPressHoldCount(void);
};

#endif