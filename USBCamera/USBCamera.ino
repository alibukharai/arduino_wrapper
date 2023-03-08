#include "Ustream.h"

void setup() {
  // put your setup code here, to run once:
  Ustream *usb = new Ustream(true, true);
  // usb->frameResolution(480, 480);
  // usb->frameInterval(5);
  // usb->frameBufferSize(35840);
  usb->config();
  // usb -> enableWifi();
}

void loop() {
}
