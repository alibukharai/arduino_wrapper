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



#define ENABLE_UVC_FRAME_RESOLUTION_ANY


class Ustream {
private:
  int _frameWidth;
  int _frameHeigth;
  int _frameInterval;
  int _xferBufferSize;
  int _xferBufferA;
  int _xferBufferB;
  int _frameBufferSize;
  int _frameBuffer;
  int _frameCb;
  int _frameCbArgument;

public:
  Ustream(bool cam_fnc, bool mic_fnc);
  void frameResolution(int width, int height);
  void frameInterval(int interval);
  void frameBufferSize(int buffersize);
  // void enableWifi();
};

#endif  // USB_STREAM_H
