# This library provides a wrapper for ESP-IOT-SOLUTION/Components/usb/usb_stream

List of supported events:
 * enableCamera
 * frameResolution
 * frameInterval
 * frameBufferSize
 * registerCallback
 * config
 * start


## Initializing a USB
```
  USB_STREAM *usb = new USB_STREAM()

```
The statement instantiates a USB_STREAM object and allocates memory for it. The pointer variable named "usb" is then assigned to point to the newly created object.

## Enable Camera
```
  usb->enableCamera(true);

```
Executing this code will activate the camera and set default values for the following parameters:

- _frameWidth = FRAME_RESOLUTION_ANY
- _frameHeight = FRAME_RESOLUTION_ANY
- _frameBufferSize = (35 * 1024)
- _frameInterval = FPS2INTERVAL(15)


## Frame Resolution 

```
  usb->frameResolution(480, 320);

```
The code will set the frame resolution to the user-specified values of 480 pixels in width and 320 pixels in height, overriding the default settings.

## Frame Interval 

```
  usb->frameInterval(5);

```
By executing the command, the default time for capturing a frame will be replaced with the value of 5, as provided by the user.

## Frame BufferSize 

```
  usb->frameBufferSize(35840);
 
```
This will assign a buffer size to temporarily store image

## Register callback

```
  usb->registerCallBack(&cameraFramecb, NULL);
```
This method sets the size of a buffer used to temporarily store images.

## Config
```
  usb->config();
```
This method configure all the necessary values.

  
## Start
```
  usb->start();
``` 
Invoking the method on the object will initiate the USB stream.
