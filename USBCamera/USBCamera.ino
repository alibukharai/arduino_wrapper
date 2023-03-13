#include "Ustream.h"

static const char *TAG = "uvc_mic_spk_demo";
static void cameraFramecb(uvc_frame *frame, void *user_ptr);

void setup() {
  // put your setup code here, to run once:
  Ustream *usb = new Ustream(true, false);
  usb->enableWifi(true);
  usb->frameResolution(480, 480);
  usb->frameInterval(5);
  usb->frameBufferSize(35840);
  usb->user(&cameraFramecb, NULL);
  // usb->config();
  // usb->start();
}

void loop() {
  vTaskDelay(100);
}


static void cameraFramecb(uvc_frame *frame, void *user_ptr) {
  ESP_LOGI(TAG, "uvc callback! frame_format = %d, seq = %" PRIu32 ", width = %" PRIu32 ", height = %" PRIu32 ", length = %u, ptr = %d",
           frame->frame_format, frame->sequence, frame->width, frame->height, frame->data_bytes, (int)user_ptr);
}
