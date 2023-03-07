#include "Ustream.h"

void setup() {
  // put your setup code here, to run once:
  Ustream *usb = new Ustream(true, true);
  usb -> frameResolution(480,480);
  usb -> enableWifi();
}

void loop() {
}
