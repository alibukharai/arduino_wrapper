// Include header file for Ustream class
#include "USB_STREAM.h"

// Define a constant string for logging
static const char *TAG = "demo";

// The setup function runs once on startup
void setup() {
  // Instantiate a Ustream object
  USB_STREAM *usb = new USB_STREAM();
  // Enable the camera

  usb->enableCamera(true);
  
  // Register the camera frame callback function
  usb->registerCallBack(&cameraFramecb, NULL);

  // Configure the camera stream
  usb->config();

  // Start the camera stream
  usb->start();
}

// The loop function runs repeatedly
void loop() {
  // Delay the task for 100ms
  vTaskDelay(100);
}

// Define the camera frame callback function implementation
static void cameraFramecb(uvc_frame *frame, void *user_ptr) {
  // Print log message with frame information
  ESP_LOGI(TAG, "uvc callback! frame_format = %d, seq = %" PRIu32 ", width = %" PRIu32 ", height = %" PRIu32 ", length = %u, ptr = %d",
           frame->frame_format, frame->sequence, frame->width, frame->height, frame->data_bytes, (int)user_ptr);
}
