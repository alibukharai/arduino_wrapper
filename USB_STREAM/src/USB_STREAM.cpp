// Include necessary headers
#include "USB_STREAM.h"
#include "original/usb_stream.h"
#include "freertos/event_groups.h"

// Define the static variable TAG with a string "driver"
static const char *TAG = "driver";

// Define a static variable ret with a value of ESP_FAIL
esp_err_t ret = ESP_FAIL;


// Define an empty constructor for the USB_STREAM class
USB_STREAM::USB_STREAM() {
}

// Define a method to enable/disable the camera and set its properties accordingly
void USB_STREAM::enableCamera(bool cam_enable_func) {
  if (cam_enable_func == true) {
    printf("Camera is enabled\n");
    _frameWidth = FRAME_RESOLUTION_ANY;
    _frameHeight = FRAME_RESOLUTION_ANY;
    _frameBufferSize = (35 * 1024);
    _frameInterval = FPS2INTERVAL(15);
  } else {
    printf("Camera is not enabled\n");
  }
}

// Define a method to set the frame resolution
void USB_STREAM ::frameResolution(int width, int height) {
  if (width > 0 && height > 0) {
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

// Define a method to set the frame interval
void USB_STREAM ::frameInterval(int interval) {
  if (interval > 0) {
    _frameInterval = FPS2INTERVAL(interval);
    printf("Frame interval %d\n", _frameInterval);
  } else {
    _frameInterval = FPS2INTERVAL(15);
    printf("Default Frame interval is used FPS2INTERVAL(15)\n");
  }
}

// Define a method to set the frame buffer size
void USB_STREAM ::frameBufferSize(int buffersize) {
  if (buffersize > 0) {
    _frameBufferSize = buffersize;
  } else {
    _frameBufferSize = (35 * 1024);
  }
}

// Define a method to get the frame height
int USB_STREAM::_getframeHeight() {
  return _frameHeight;
}

// Define a method to get the frame width
int USB_STREAM::_getframeWidth() {
  return _frameWidth;
}

// Define a method to get the frame interval
int USB_STREAM::_getframeInterval() {
  return _frameInterval;
}

// Define a method to get the frame buffer size
int USB_STREAM::_getframeBufferSize() {
  return _frameBufferSize;
}

// Define a method to register a user-defined callback function
void USB_STREAM ::registerCallBack(uvc_frame_callback_t *newFunction, void *cb_arg) {
  if (newFunction != NULL) {
    this->_user_frame_cb = newFunction;
    this->_user_frame_cb_arg = cb_arg;
  } else {
    printf("registerCallBack function error\n");
  }
}

// Define a static method that serves as the callback function for the camera frame
static void _camera_frame_cb(uvc_frame_t *frame, void *ptr) {
  USB_STREAM *my_instance = (USB_STREAM *)ptr;
  if (my_instance->_user_frame_cb != NULL) {
    my_instance->_user_frame_cb(frame, my_instance->_user_frame_cb_arg);
  }
}

// Define a method to configure the camera stream
void USB_STREAM ::config() {
  // Allocate memory for transfer buffers and frame buffer
  uint8_t *_xferBufferA = (uint8_t *)malloc(_getframeBufferSize());
  assert(_xferBufferA != NULL);
  uint8_t *_xferBufferB = (uint8_t *)malloc(_getframeBufferSize());
  assert(_xferBufferB != NULL);
  // /* malloc frame buffer for a jpeg frame*/
  uint8_t *_frameBuffer = (uint8_t *)malloc(_getframeBufferSize());
  assert(_frameBuffer != NULL);

  // Populate the UVC configuration struct
  uvc_config_t uvc_config = {
    .frame_width = _getframeWidth(),
    .frame_height = _getframeHeight(),
    .frame_interval = _getframeInterval(),
    .xfer_buffer_size = _getframeBufferSize(),
    .xfer_buffer_a = _xferBufferA,
    .xfer_buffer_b = _xferBufferB,
    .frame_buffer_size = _getframeBufferSize(),
    .frame_buffer = _frameBuffer,
    .frame_cb = &_camera_frame_cb,
    .frame_cb_arg = this,
  };

  // Configure the UVC streaming with the provided configuration
  ret = uvc_streaming_config(&uvc_config);
  if (ret != ESP_OK) {
    ESP_LOGE(TAG, "uvc streaming config failed");
  }
}

// Define a method to start the USB streaming
void USB_STREAM ::start() {
  ret = usb_streaming_start();
  if (ret != ESP_OK) {
    printf("usb streaming start failed\n");
  } else
    printf("usb streaming start succeed\n");
}
