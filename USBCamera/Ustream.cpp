#include "Ustream.h"
#include "usb_stream.h"

Ustream::Ustream(bool cam_fnc, bool mic_fnc) {
  printf("Starting USB Stream...\n");
  if (cam_fnc = false) {
#define ENABLE_UVC_CAMERA_FUNCTION 0 /* enable uvc function */
  } else {
#define ENABLE_UVC_CAMERA_FUNCTION 1 /* enable uvc function */
  }
  if (mic_fnc = false) {
#define ENABLE_UAC_MIC_SPK_FUNCTION 0
  } else {
#define ENABLE_UAC_MIC_SPK_FUNCTION 1
  }
}

void Ustream ::frameResolution(int width, int height) {
  if (width == true && height == true) {
    _frameWidth = width;
    _frameHeight = height;
  } else {
    _frameWidth = FRAME_RESOLUTION_ANY;
    _frameHeight = FRAME_RESOLUTION_ANY;
  }
}
void Ustream ::frameInterval(int interval) {
  if (interval == true) {
    _frameInterval = FPS2INTERVAL(interval);
    printf("frame interval %d\n", _frameInterval);
  } else {
    _frameInterval = FPS2INTERVAL(15);
    printf("else frame interval %d\n", _frameInterval);
  }
}
void Ustream ::frameBufferSize(int buffersize) {
  if (buffersize == true) {
    _frameBufferSize = buffersize;
  } else {
    _frameBufferSize = (35 * 1024);
  }
}


int Ustream::_getframeHeight() {
  // Return the value of myPrivateVariable
  return _frameHeight;
}
int Ustream::_getframeWidth() {
  // Return the value of myPrivateVariable
  return _frameWidth;
}

int Ustream::_getframeInterval() {
  // Return the value of myPrivateVariable
  return _frameInterval;
}
int Ustream::_getframeBufferSize() {
  // Return the value of myPrivateVariable
  return _frameBufferSize;
}

void Ustream ::config() {
  uint8_t *_xfer_buffer_a = (uint8_t *)malloc(_getframeBufferSize());
  assert(xfer_buffer_a != NULL);
  uint8_t *xfer_buffer_b = (uint8_t *)malloc(_getframeBufferSize());
  assert(xfer_buffer_b != NULL);
  // /* malloc frame buffer for a jpeg frame*/
  uint8_t *frame_buffer = (uint8_t *)malloc(_getframeBufferSize());
  assert(frame_buffer != NULL);

  uvc_config_t uvc_config = {
    .frame_width = _getframeWidth(),
    .frame_height = _getframeHeight(),
    .frame_interval = _getframeInterval(),
    .xfer_buffer_size = _getframeBufferSize(),
    .xfer_buffer_a = xfer_buffer_a,
    .xfer_buffer_b = xfer_buffer_b,
    .frame_buffer_size = _getframeBufferSize(),
    .frame_buffer = frame_buffer,
    // .frame_cb = &camera_frame_cb,
    .frame_cb_arg = NULL,
  };
}
