<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "3ba7150ffc4a6999f6c3cfb4906ec7df",
  "translation_date": "2025-08-28T19:10:31+00:00",
  "source_file": "4-manufacturing/lessons/2-check-fruit-from-device/virtual-device-camera.md",
  "language_code": "en"
}
-->
# Capture an image - Virtual IoT Hardware

In this part of the lesson, you will add a camera sensor to your virtual IoT device and read images from it.

## Hardware

The virtual IoT device will use a simulated camera that sends images either from files or your webcam.

### Add the camera to CounterFit

To use a virtual camera, you need to add one to the CounterFit app.

#### Task - Add the camera to CounterFit

Add the Camera to the CounterFit app.

1. Create a new Python app on your computer in a folder called `fruit-quality-detector` with a single file named `app.py` and a Python virtual environment. Add the CounterFit pip packages.

    > ⚠️ You can refer to [the instructions for creating and setting up a CounterFit Python project in lesson 1 if needed](../../../1-getting-started/lessons/1-introduction-to-iot/virtual-device.md).

1. Install an additional Pip package to add a CounterFit shim that simulates some of the [Picamera Pip package](https://pypi.org/project/picamera/). Make sure you install this from a terminal with the virtual environment activated.

    ```sh
    pip install counterfit-shims-picamera
    ```

1. Ensure the CounterFit web app is running.

1. Create a camera:

    1. In the *Create sensor* box in the *Sensors* pane, drop down the *Sensor type* box and select *Camera*.

    1. Set the *Name* to `Picamera`.

    1. Click the **Add** button to create the camera.

    ![The camera settings](../../../../../translated_images/en/counterfit-create-camera.a5de97f59c0bd3cbe0416d7e89a3cfe86d19fbae05c641c53a91286412af0a34.png)

    The camera will be created and appear in the sensors list.

    ![The camera created](../../../../../translated_images/en/counterfit-camera.001ec52194c8ee5d3f617173da2c79e1df903d10882adc625cbfc493525125d4.png)

## Program the camera

The virtual IoT device can now be programmed to use the virtual camera.

### Task - Program the camera

Program the device.

1. Make sure the `fruit-quality-detector` app is open in VS Code.

1. Open the `app.py` file.

1. Add the following code to the top of `app.py` to connect the app to CounterFit:

    ```python
    from counterfit_connection import CounterFitConnection
    CounterFitConnection.init('127.0.0.1', 5000)
    ```

1. Add the following code to your `app.py` file:

    ```python
    import io
    from counterfit_shims_picamera import PiCamera
    ```

    This code imports some necessary libraries, including the `PiCamera` class from the counterfit_shims_picamera library.

1. Add the following code below this to initialize the camera:

    ```python
    camera = PiCamera()
    camera.resolution = (640, 480)
    camera.rotation = 0
    ```

    This code creates a PiCamera object and sets the resolution to 640x480. Although higher resolutions are supported, the image classifier works on much smaller images (227x227), so there’s no need to capture and send larger images.

    The `camera.rotation = 0` line sets the rotation of the image in degrees. If you need to rotate the image from the webcam or file, adjust this value as needed. For example, if you want to change the orientation of a banana image captured in landscape mode to portrait, set `camera.rotation = 90`.

1. Add the following code below this to capture the image as binary data:

    ```python
    image = io.BytesIO()
    camera.capture(image, 'jpeg')
    image.seek(0)
    ```

    This code creates a `BytesIO` object to store binary data. The image is read from the camera as a JPEG file and stored in this object. The `image.seek(0)` line moves the position indicator back to the start so that all the data can be read later.

1. Below this, add the following code to save the image to a file:

    ```python
    with open('image.jpg', 'wb') as image_file:
        image_file.write(image.read())
    ```

    This code opens a file called `image.jpg` for writing, then reads all the data from the `BytesIO` object and writes it to the file.

    > 💁 You can capture the image directly to a file instead of a `BytesIO` object by passing the file name to the `camera.capture` call. The reason for using the `BytesIO` object is to allow you to send the image to your image classifier later in this lesson.

1. Configure the image that the camera in CounterFit will capture. You can either set the *Source* to *File* and upload an image file, or set the *Source* to *WebCam* to capture images from your webcam. Make sure to click the **Set** button after selecting a picture or your webcam.

    ![CounterFit with a file set as the image source, and a web cam set showing a person holding a banana in a preview of the webcam](../../../../../translated_images/en/counterfit-camera-options.eb3bd5150a8e7dffbf24bc5bcaba0cf2cdef95fbe6bbe393695d173817d6b8df.png)

1. An image will be captured and saved as `image.jpg` in the current folder. You will see this file in the VS Code explorer. Select the file to view the image. If it needs rotation, update the `camera.rotation = 0` line as necessary and take another picture.

> 💁 You can find this code in the [code-camera/virtual-iot-device](../../../../../4-manufacturing/lessons/2-check-fruit-from-device/code-camera/virtual-iot-device) folder.

😀 Your camera program was a success!

---

**Disclaimer**:  
This document has been translated using the AI translation service [Co-op Translator](https://github.com/Azure/co-op-translator). While we aim for accuracy, please note that automated translations may include errors or inaccuracies. The original document in its native language should be regarded as the authoritative source. For critical information, professional human translation is advised. We are not responsible for any misunderstandings or misinterpretations resulting from the use of this translation.