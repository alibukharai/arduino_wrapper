#include "Button.h"

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  // initializing a button
  Button *btn1 = new Button(8, false);   // Button *btn = new Button(9, false, 0, 0, 100, 400);
  Button *btn2 = new Button(9, false);   // Button *btn = new Button(9, false, 0, 0, 100, 400);
  Button *btn3 = new Button(10, false);  // Button *btn = new Button(9, false, 0, 0, 100, 400);

  // attach callback function to the button event
  btn1->attachPressDown(&onButtonPressDown);
  btn1->attachPressUp(&onButtonPressUp);
  btn2->attachSingleClick(&onButtonSingleClick);
  btn2->attachDoubleClick(&onButtonDoubleClick);
  btn3->attachLongPressStart(&onButtonLongPressStart);
  btn3->attachLongPressHold(&onButtonLongPressHold);
  btn3->attachPressRepeatDone(&onButtonPressRepeatDone);

  // detach pressrepeatdone event from the button 3
  btn3->detachPressRepeatDone();

  // printing no of callback attach to button
  printf("No of callback attach to btn1 %d\n", btn1->countCallBack());
  printf("No of callback attach to btn2 %d\n", btn2->countCallBack());
  printf("No of callback attach to btn3 %d\n", btn3->countCallBack());

  // delete button 3
  btn3->deleteButton();

  // detach pressdowndown event from the button 2
  btn2->detachDoubleClick();

  // count the no of callback currently attach to the button
  printf("No of callback attach to btn1 %d\n", btn1->countCallBack());
  printf("No of callback attach to btn2 %d\n", btn2->countCallBack());

  // check the Current event on the button instance
  printf("Current event on the btn1 %d\n", btn1->getEvent());
  printf("Current event on the btn1 %d\n", btn2->getEvent());

  //get the number of times a but1 has been repeatedly pressed
  printf("No of times a but1 has been repeatedly pressed %d\n", btn1->getRepeat());

  //retrieve the elapsed time since the last btn2 event in milliseconds.
  printf("Elapsed time since the last btn2 event in milliseconds %d\n", btn2->getTickTime());
}

void loop() {
  delay(10);
}


//callback functions
static void onButtonPressDown() {
  Serial.println("Button Pressed down");
}

static void onButtonPressUp() {
  Serial.println("Button Pressed up");
}

static void onButtonSingleClick() {
  Serial.println("Button single click");
}

static void onButtonDoubleClick() {
  Serial.println("Button double click");
}

static void onButtonLongPressStart() {
  Serial.println("Button long press start");
}

static void onButtonLongPressHold() {
  Serial.println("Button long press hold");
}

static void onButtonPressRepeatDone() {
  Serial.println("Button press repeat done");
}
