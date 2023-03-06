#include "Button.h"

void setup()
{
    // put your setup code here, to run once:
    Serial.begin(115200);

    // initializing a button
    Button *btn = new Button(9, false); //incase of ADC button    "Button *btn = new Button(9, false, 0, 0, 100, 400);"
    btn->attachPressDown(&onButtonPressDown);
    btn->attachPressUp(&onButtonPressUp);
    btn->attachPressRepeat(&onButtonPressRepeat);
    btn->attachSingleClick(&onButtonSingleClick);
    btn->attachDoubleClick(&onButtonDoubleClick);
    btn->attachLongPressStart(&onButtonLongPressStart);
    btn->attachLongPressHold(&onButtonLongPressHold);
    btn->attachPressRepeatDone(&onButtonPressRepeatDone);

}

void loop()
{
    delay(10);
}


//callback functions
static void onButtonPressDown()
{
    Serial.println("Button Pressed down");
}

static void onButtonPressUp()
{
    Serial.println("Button Pressed up");
}

static void onButtonPressRepeat()
{
    Serial.println("Button press repeat");
}

static void onButtonSingleClick()
{
    Serial.println("Button single click");
}

static void onButtonDoubleClick()
{
    Serial.println("Button double click");
}

static void onButtonLongPressStart()
{
    Serial.println("Button long press start");
}

static void onButtonLongPressHold()
{
    Serial.println("Button long press hold");
}

static void onButtonPressRepeatDone()
{
    Serial.println("Button press repeat done");
}
