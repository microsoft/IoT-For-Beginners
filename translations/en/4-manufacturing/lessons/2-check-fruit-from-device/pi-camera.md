<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "c677667095f6133eee418c7e53615d05",
  "translation_date": "2025-08-28T19:09:49+00:00",
  "source_file": "4-manufacturing/lessons/2-check-fruit-from-device/pi-camera.md",
  "language_code": "en"
}
-->
# Capture an image - Raspberry Pi

In this part of the lesson, you will add a camera sensor to your Raspberry Pi and capture images with it.

## Hardware

The Raspberry Pi requires a camera.

The camera you'll use is a [Raspberry Pi Camera Module](https://www.raspberrypi.org/products/camera-module-v2/). This camera is specifically designed for the Raspberry Pi and connects via a dedicated port on the device.

> 💁 This camera uses the [Camera Serial Interface, a protocol from the Mobile Industry Processor Interface Alliance](https://wikipedia.org/wiki/Camera_Serial_Interface), known as MIPI-CSI. This is a specialized protocol for transmitting images.

## Connect the camera

The camera can be connected to the Raspberry Pi using a ribbon cable.

### Task - Connect the camera

![A Raspberry Pi Camera](../../../../../translated_images/en/pi-camera-module.4278753c31bd6e757aa2b858be97d72049f71616278cefe4fb5abb485b40a078.png)

1. Turn off the Raspberry Pi.

1. Attach the ribbon cable that comes with the camera to the camera module. To do this, gently pull the black plastic clip on the connector outward, slide the cable into the socket with the blue side facing away from the lens and the metal pin strips facing toward the lens. Once the cable is fully inserted, push the black plastic clip back into place.

    You can find an animation showing how to open the clip and insert the cable in the [Raspberry Pi Getting Started with the Camera module documentation](https://projects.raspberrypi.org/en/projects/getting-started-with-picamera/2).

    ![The ribbon cable inserted into the camera module](../../../../../translated_images/en/pi-camera-ribbon-cable.0bf82acd251611c21ac616f082849413e2b322a261d0e4f8fec344248083b07e.png)

1. Remove the Grove Base Hat from the Raspberry Pi.

1. Pass the ribbon cable through the camera slot in the Grove Base Hat. Ensure the blue side of the cable faces the analog ports labeled **A0**, **A1**, etc.

    ![The ribbon cable passing through the Grove Base Hat](../../../../../translated_images/en/grove-base-hat-ribbon-cable.501fed202fcf73b11b2b68f6d246189f7d15d3e4423c572ddee79d77b4632b47.png)

1. Insert the ribbon cable into the camera port on the Raspberry Pi. Again, pull the black plastic clip upward, insert the cable, and push the clip back down. The blue side of the cable should face the USB and Ethernet ports.

    ![The ribbon cable connected to the camera socket on the Raspberry Pi](../../../../../translated_images/en/pi-camera-socket-ribbon-cable.a18309920b11800911082ed7aa6fb28e6d9be3a022e4079ff990016cae3fca10.png)

1. Reattach the Grove Base Hat.

## Program the camera

The Raspberry Pi can now be programmed to use the camera with the [PiCamera](https://pypi.org/project/picamera/) Python library.

### Task - Enable legacy camera mode

With the release of Raspberry Pi OS Bullseye, the camera software included in the OS changed, and PiCamera no longer works by default. A replacement library, PiCamera2, is in development but is not yet ready for use.

For now, you can enable legacy camera mode to make PiCamera functional. Enabling the legacy camera software will also automatically activate the camera port.

1. Power on the Raspberry Pi and wait for it to boot.

1. Open VS Code, either directly on the Raspberry Pi or by connecting via the Remote SSH extension.

1. Run the following commands in your terminal:

    ```sh
    sudo raspi-config nonint do_legacy 0
    sudo reboot
    ```

    These commands will enable the legacy camera software and reboot the Raspberry Pi to apply the changes.

1. Wait for the Raspberry Pi to reboot, then reopen VS Code.

### Task - Program the camera

Write a program to use the camera.

1. In the terminal, create a new folder in the `pi` user's home directory called `fruit-quality-detector`. Inside this folder, create a file named `app.py`.

1. Open this folder in VS Code.

1. To interact with the camera, use the PiCamera Python library. Install the library using the following command:

    ```sh
    pip3 install picamera
    ```

1. Add the following code to your `app.py` file:

    ```python
    import io
    import time
    from picamera import PiCamera
    ```

    This code imports the necessary libraries, including the `PiCamera` library.

1. Add the following code below to initialize the camera:

    ```python
    camera = PiCamera()
    camera.resolution = (640, 480)
    camera.rotation = 0
    
    time.sleep(2)
    ```

    This code creates a PiCamera object and sets the resolution to 640x480. Although higher resolutions are supported (up to 3280x2464), the image classifier works with much smaller images (227x227), so capturing larger images is unnecessary.

    The `camera.rotation = 0` line sets the image rotation. The ribbon cable connects to the bottom of the camera, but if you rotate the camera to better point at the object you want to classify, you can adjust this line to match the rotation angle.

    ![The camera hanging down over a drink can](../../../../../translated_images/en/pi-camera-upside-down.5376961ba31459883362124152ad6b823d5ac5fc14e85f317e22903bd681c2b6.png)

    For example, if you suspend the ribbon cable above the camera so it enters from the top, set the rotation to 180:

    ```python
    camera.rotation = 180
    ```

    The camera takes a few seconds to initialize, which is why `time.sleep(2)` is included.

1. Add the following code below to capture the image as binary data:

    ```python
    image = io.BytesIO()
    camera.capture(image, 'jpeg')
    image.seek(0)
    ```

    This code creates a `BytesIO` object to store binary data. The image is captured from the camera as a JPEG file and stored in this object. The `image.seek(0)` line resets the position indicator in the object to the start so all data can be read later.

1. Add the following code below to save the image to a file:

    ```python
    with open('image.jpg', 'wb') as image_file:
        image_file.write(image.read())
    ```

    This code opens a file named `image.jpg` for writing, then reads all the data from the `BytesIO` object and writes it to the file.

    > 💁 You can capture the image directly to a file instead of using a `BytesIO` object by passing the file name to the `camera.capture` call. The `BytesIO` object is used here so the image can later be sent to an image classifier.

1. Point the camera at an object and run the code.

1. An image will be captured and saved as `image.jpg` in the current folder. You can view this file in the VS Code explorer. If the image needs rotation, update the `camera.rotation = 0` line accordingly and take another picture.

> 💁 You can find this code in the [code-camera/pi](../../../../../4-manufacturing/lessons/2-check-fruit-from-device/code-camera/pi) folder.

😀 Your camera program is working successfully!

---

**Disclaimer**:  
This document has been translated using the AI translation service [Co-op Translator](https://github.com/Azure/co-op-translator). While we strive for accuracy, please note that automated translations may contain errors or inaccuracies. The original document in its native language should be regarded as the authoritative source. For critical information, professional human translation is recommended. We are not responsible for any misunderstandings or misinterpretations resulting from the use of this translation.