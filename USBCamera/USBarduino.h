//Header file guard
#ifndef USBARDUINO_H
#define USBARDUINO_H
//Include necessary header files
#include <stdio.h>
#include <assert.h>
#include "freertos/FreeRTOS.h"
#include "freertos/event_groups.h"
#include "freertos/task.h"
#include "esp_err.h"
#include "esp_log.h"
#include "usb_stream.h"

class USBarduino {
private:
  //Private member variables for storing camera settings and memory allocation
  int _frameWidth = FRAME_RESOLUTION_ANY;
  int _frameHeight = FRAME_RESOLUTION_ANY;
  int _frameInterval = FPS2INTERVAL(15);
  int _xferBufferSize = (35 * 1024);
  uint8_t *_xferBufferA = nullptr;
  uint8_t *_xferBufferB = nullptr;
  int _frameBufferSize = (5 * 1024);
  uint8_t *_frameBuffer = nullptr;
  int _frameCbArgument = NULL;
  //Private member functions for getting camera settings
  int _getframeHeight();
  int _getframeWidth();
  int _getframeInterval();
  int _getframeBufferSize();
public:
  //Public member variables for storing user-defined callback function and arguments

  uvc_frame_callback_t *_user_frame_cb = NULL;
  void *_user_frame_cb_arg = NULL;
  //Public member functions for configuring and starting camera stream
  USBarduino();  //constructor
  void enableCamera(bool cam_enable_func);
  void frameResolution(int width, int height);
  void frameInterval(int interval);
  void frameBufferSize(int buffersize);
  void registerCallBack(uvc_frame_callback_t *newFunction, void *cb_arg);
  void config();
  void start();
};

#endif  // USB_STREAM_H
