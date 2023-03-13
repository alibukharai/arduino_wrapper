# This library provides a wrapper for ESP-IOT-SOLUTION/Components/Button

List of supported events:
 * Button pressed
 * Button released
 * Button pressed - repeated
 * Button single click
 * Button double click
 * Button long press start
 * Button long press hold
 * Button press repeat done

There are two ways this driver can handle buttons:
1. Buttons connected to standard digital GPIO
2. Multiple buttons connected to single ADC channel



## Supported Events 

| Events                      | Description                                                                                                             | Arduino Function      |
| --------------------------- | ----------------------------------------------------------------------------------------------------------------------- | --------------------- |
| `Button pressed`            | This event is triggered when the button is initially pressed down.                                                      | attachPressDown       |
| `Button released`           | This event is triggered when the button is released after being pressed down.                                           | attachPressUp         |
| `Button pressed - repeated` | This event is triggered when the button is pressed repeatedly in a short amount of time.                                | attachPressRepeat     |
| `Button single click`       | This event is triggered when the button is clicked once without any repeated presses.                                   | attachSingleClick     |
| `Button double click`       | This event is triggered when the button is clicked twice in quick succession.                                           | attachDoubleClick     |
| `Button long press start`   | This event is triggered when the button is held down for a specified amount of time, indicating a potential long press. | attachLongPressStart  |
| `Button long press hold`    | This event is triggered repeatedly while the button is held down after a long press has been detected.                  | attachLongPressHold   |
| `Button press repeat done`  | This event is triggered when the button repetition is completed                                                         | attachPressRepeatDone |



## Initializing a GPIO Button
```
  Button *btn = new Button(pin number, pullupActive)

```
This creates a new button object and assigns it to the pointer variable btn. The button::button() constructor is then defined to take two arguments: 
- **pin :** which specifies the pin number that the button is connected to



- **pullupActive :** which is a boolean value indicating whether the internal pull-up resistor of the pin should be enabled or not. If pullupActive is true, the pinMode() function sets the pin as an input with its internal pull-up resistor enabled. This means that the pin will read as HIGH when the button is not pressed, and LOW when the button is pressed. If pullupActive is false, the pinMode() function sets the pin as an input with its internal pull-up resistor disabled. In this case, the pin will read as a floating state, which may be either HIGH or LOW when the button is not pressed. When the button is pressed, it will again momentarily connect the pin to ground, causing it to read as LOW. 



## Initializing an ADC Button
```
  Button *btn = new Button(pin number, pullupActive, adc_channel, button_index, min, max);

```
This creates a new button object and assigns it to the pointer variable btn. The Button::Button() constructor is then defined arguments: 
- **pin :** which specifies the pin number that the button is connected to,

- **pullupActive :** which is a boolean value indicating whether the internal pull-up resistor of the pin should be enabled or not. If pullupActive is true, the pinMode() function sets the pin as an input with its internal pull-up resistor enabled. This means that the pin will read as HIGH when the button is not pressed, and LOW when the button is pressed. If pullupActive is false, the pinMode() function sets the pin as an input with its internal pull-up resistor disabled. In this case, the pin will read as a floating state, which may be either HIGH or LOW when the button is not pressed. When the button is pressed, it will again momentarily connect the pin to ground, causing it to read as LOW. 

- **adc_channel :** Channel of ADC 

- **button_index :** button index on the channel

- **min :** min voltage in millivolt corresponding to the button 


- **max :** max voltage in millivolt corresponding to the button 


## Attach Callback Function

```
 btn-> attachPressDown(& Callback Function name)

```
This attaches a callback function to the button's attachPressDown event, which triggers when the button is pressed down.

To use this code, you should replace & "Callback Function name" with the actual name of the function that you want to be called when the attachPressDown event occurs. This function will be executed whenever the button is pressed down. Such as toggling an LED or executing a sequence of instructions.


## Detach Callback Function 

```
  btn->detachPressDown

```
The code detaches any event handler that was previously attached to the button instance's attachPressDown event. This means that if a callback function was previously attached to this event using btn->attachPressDown(& Callback Function name), it will no longer be executed when the button is pressed down.

Detaching an event handler is useful when you want to change the behavior of a button or disable a specific event without affecting the other events attached to the button. For example, if you have multiple functions attached to the button's events and you want to disable only the attachPressDown event temporarily, you can use btn->detachPressDown() to remove the attachPressDown callback function without affecting the other event handlers.

## Delete Button 

```
  btn->deleteButton
 
```
The btn->deleteButton() code deletes the button instance created by new button(pin number, pullupActive), which means all the events attached to the button instance will be detached as well.

So, you don't need to detach the events manually before deleting the button instance using btn->deleteButton(). The function will automatically detach all the events and remove the instance from memory.

Deleting the button instance is useful when you no longer need the button and want to free up memory space.

## Count Call Back

```
  btn->countCallBack()
```
This function returns the number of callbacks **currently** attached to the button. This functions is useful for debugging and monitoring the state of the button instance, especially if you have multiple event handlers attached to the button and want to ensure that they are all being executed correctly.

## Get Event
```
  btn->getEvent()
```
This event is used to retrieve the current event type of a button instance. This can be helpful for monitoring the current state of the button instance and for triggering different actions or behaviors depending on the current event type.

typedef enum {
    BUTTON_PRESS_DOWN = 0,
    BUTTON_PRESS_UP,
    BUTTON_PRESS_REPEAT,
    BUTTON_PRESS_REPEAT_DONE,
    BUTTON_SINGLE_CLICK,
    BUTTON_DOUBLE_CLICK,
    BUTTON_LONG_PRESS_START,
    BUTTON_LONG_PRESS_HOLD,
    BUTTON_EVENT_MAX,
    BUTTON_NONE_PRESS,
} button_event_t;

  
## Get Repeat
```
  btn->getRepeat()
``` 

This function is used to retrieve the number of times a button has been repeatedly pressed since the last button event was triggered.

## Get Tick Time
```  
  btn->getTickTime()
```

 This function is used to retrieve the elapsed time since the last button event in milliseconds.

##  Get Long Press Hold Count 

```
  btn->getLongPressHoldCount()
```
This function is used to retrieve the number of times the button has been held down during a long press event.