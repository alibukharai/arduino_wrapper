#include "Ustream.h"

void setup() {
  // put your setup code here, to run once:
  Ustream *usb = new Ustream(false, true);
  usb->enableWifi(true);
  // usb->frameResolution(480, 480);
  // usb->frameInterval(5);
  // usb->frameBufferSize(35840);
  usb->user(&cameraFramecb, NULL);
  usb->config();
  // usb -> enableWifi();
}

void loop() {
}


static void cameraFramecb(uvc_frame *frame, void *user_ptr) {
  Serial.println("Button press repeat done");
}
