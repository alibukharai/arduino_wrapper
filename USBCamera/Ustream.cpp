#include "Ustream.h"
#include "usb_stream.h"
#include "freertos/event_groups.h"

static const char *TAG = "uvc_mic_spk_demo";

bool ENABLE_UVC_CAMERA_FUNCTION = false;
bool ENABLE_UVC_WIFI_XFER = false;
bool ENABLE_UAC_MIC_SPK_FUNCTION = false;
bool ENABLE_UAC_FEATURE_CONTROL = false;
bool ENABLE_UAC_MIC_SPK_LOOPBACK = false;


Ustream::Ustream(bool cam_fnc, bool mic_fnc) {
  if (cam_fnc == true) {
    printf("Camera is enabled\n");
    ENABLE_UVC_CAMERA_FUNCTION = 1;
    _frameWidth = FRAME_RESOLUTION_ANY;
    _frameHeight = FRAME_RESOLUTION_ANY;
    _frameBufferSize = (35 * 1024);
    _frameInterval = FPS2INTERVAL(15);
  } else {
    printf("Camera is not enabled\n");
    ENABLE_UVC_CAMERA_FUNCTION = 0;
    _frameBufferSize = (35 * 1024);
  }
  if (mic_fnc == true) {
    printf("Mic is enabled\n");
    ENABLE_UAC_MIC_SPK_FUNCTION = 1;
    ENABLE_UAC_FEATURE_CONTROL = 0;
    ENABLE_UAC_MIC_SPK_LOOPBACK = 0;
  } else {
    printf("Mic is not enabled\n");
    ENABLE_UAC_MIC_SPK_FUNCTION = 0;
  }
}

void Ustream::enableWifi(bool wifi) {
  if (wifi == true) {
    printf("Wifi is enabled\n");
    ENABLE_UVC_WIFI_XFER = 1;
  } else {
    printf("Wifi is not enabled\n");
    ENABLE_UVC_WIFI_XFER = false;
  }
}

void Ustream ::frameResolution(int width, int height) {
  if (width == true && height == true) {
    _frameWidth = width;
    _frameHeight = height;
    printf("width %d , height %d is used\n", _frameWidth, _frameHeight);

  } else {
    printf("Default resolution is used\n");
    _frameWidth = FRAME_RESOLUTION_ANY;
    _frameHeight = FRAME_RESOLUTION_ANY;
    printf("Trying to used 35*1024 buffer size\n");
    _frameBufferSize = (35 * 1024);
  }
}

void Ustream ::frameInterval(int interval) {
  if (interval == true) {
    _frameInterval = FPS2INTERVAL(interval);
    printf("Frame interval %d\n", _frameInterval);
  } else {
    _frameInterval = FPS2INTERVAL(15);
    printf("Default Frame interval is used %d\n", _frameInterval);
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

void Ustream ::user(uvc_frame_callback_t *newFunction, void *cb_arg) {
  this->_user_frame_cb = newFunction;
  this->_user_frame_cb_arg = cb_arg;

}

static void _camera_frame_cb(uvc_frame_t *frame, void *ptr)
{
  Ustream *my_instance = (Ustream *)ptr;
  my_instance->_user_frame_cb(frame, my_instance->_user_frame_cb_arg);
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
    .frame_cb = _camera_frame_cb,
    .frame_cb_arg = this,
  };
}
