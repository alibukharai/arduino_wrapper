#ifndef USTREAM_H
#define USTREAM_H

#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <inttypes.h>
#include "freertos/FreeRTOS.h"
#include "freertos/event_groups.h"
#include "freertos/task.h"
#include "esp_err.h"
#include "esp_log.h"
#include "usb_stream.h"



#define ENABLE_UVC_FRAME_RESOLUTION_ANY


class Ustream {
private:
  int _frameWidth = FRAME_RESOLUTION_ANY;
  int _frameHeight = FRAME_RESOLUTION_ANY;
  int _frameInterval = FPS2INTERVAL(15);
  int _xferBufferSize = (35 * 1024);
  uint8_t *xfer_buffer_a = xfer_buffer_a;
  uint8_t *xfer_buffer_b = xfer_buffer_b;
  int _frameBufferSize = (5 * 1024);
  uint8_t *frame_buffer = frame_buffer;
  // int _frameCb = &camera_frame_cb;
  int _frameCbArgument = NULL;

  int _getframeHeight();
  int _getframeWidth();
  int _getframeInterval();
  int _getframeBufferSize();
public:
  Ustream(bool cam_fnc, bool mic_fnc);
  void frameResolution(int width, int height);
  void frameInterval(int interval);
  void frameBufferSize(int buffersize);
  void config(void);
  // void enableWifi();
};

#endif  // USB_STREAM_H
