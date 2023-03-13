#include <btn_config.h>
#include <button_adc.h>
#include <button_gpio.h>
#include <iot_button.h>
#include <Button.h>

// Include header file for Ustream class
#include "USBarduino.h"

// Define a constant string for logging
static const char *TAG = "demo";

// The setup function runs once on startup
void setup() {
  // Instantiate a Ustream object
  USBarduino *usb = new USBarduino();
  // Enable the camera

  usb->enableCamera(true);
  // usb->frameResolution(480, 320);
  // usb->frameInterval(5);
  // usb->frameBufferSize(35840);

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
