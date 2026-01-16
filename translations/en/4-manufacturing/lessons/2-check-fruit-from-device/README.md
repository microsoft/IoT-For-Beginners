<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "557f4ee96b752e0651d2e6e74aa6bd14",
  "translation_date": "2025-08-28T19:08:35+00:00",
  "source_file": "4-manufacturing/lessons/2-check-fruit-from-device/README.md",
  "language_code": "en"
}
-->
# Check fruit quality from an IoT device

![A sketchnote overview of this lesson](../../../../../translated_images/en/lesson-16.215daf18b00631fbdfd64c6fc2dc6044dff5d544288825d8076f9fb83d964c23.jpg)

> Sketchnote by [Nitya Narasimhan](https://github.com/nitya). Click the image for a larger version.

## Pre-lecture quiz

[Pre-lecture quiz](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/31)

## Introduction

In the previous lesson, you learned about image classifiers and how to train them to identify good and bad fruit. To use this image classifier in an IoT application, you need a way to capture an image using a camera and send it to the cloud for classification.

In this lesson, you will learn about camera sensors and how to use them with an IoT device to capture images. You will also learn how to call the image classifier from your IoT device.

This lesson will cover:

* [Camera sensors](../../../../../4-manufacturing/lessons/2-check-fruit-from-device)
* [Capture an image using an IoT device](../../../../../4-manufacturing/lessons/2-check-fruit-from-device)
* [Publish your image classifier](../../../../../4-manufacturing/lessons/2-check-fruit-from-device)
* [Classify images from your IoT device](../../../../../4-manufacturing/lessons/2-check-fruit-from-device)
* [Improve the model](../../../../../4-manufacturing/lessons/2-check-fruit-from-device)

## Camera sensors

Camera sensors are cameras that can be connected to your IoT device. They can capture still images or streaming video. Some provide raw image data, while others compress the data into formats like JPEG or PNG. IoT-compatible cameras are often smaller and lower resolution than typical cameras, but high-resolution options are available, rivaling top-end smartphones. You can also find cameras with interchangeable lenses, multi-camera setups, infrared thermal imaging, or UV capabilities.

![The light from a scene passes through a lens and is focused on a CMOS sensor](../../../../../translated_images/en/cmos-sensor.75f9cd74decb137149a4c9ea825251a4549497d67c0ae2776159e6102bb53aa9.png)

Most camera sensors use image sensors where each pixel is a photodiode. A lens focuses the image onto the sensor, and thousands or millions of photodiodes detect the light hitting them, recording it as pixel data.

> 💁 Lenses invert images, and the camera sensor flips them back to the correct orientation. This is similar to how your eyes work—images are detected upside down on the back of your eye, and your brain corrects them.

> 🎓 The image sensor is called an Active-Pixel Sensor (APS), with the most common type being a complementary metal-oxide semiconductor sensor, or CMOS. You may have heard the term CMOS sensor used for camera sensors.

Camera sensors are digital, sending image data as digital signals, often with the help of a library for communication. Cameras use protocols like SPI to transmit large amounts of data, as images are much larger than single values from sensors like temperature sensors.

✅ What are the limitations of image size with IoT devices? Consider the constraints, especially on microcontroller hardware.

## Capture an image using an IoT device

You can use your IoT device to capture an image for classification.

### Task - capture an image using an IoT device

Follow the appropriate guide to capture an image using your IoT device:

* [Arduino - Wio Terminal](wio-terminal-camera.md)
* [Single-board computer - Raspberry Pi](pi-camera.md)
* [Single-board computer - Virtual device](virtual-device-camera.md)

## Publish your image classifier

You trained your image classifier in the previous lesson. Before using it with your IoT device, you need to publish the model.

### Model iterations

During training in the last lesson, you may have noticed the **Performance** tab showing iterations. For example, the first training session would have been labeled *Iteration 1*. If you improved the model using prediction images, you would have seen *Iteration 2*.

Each training session creates a new iteration, allowing you to track different versions of your model trained on various datasets. When performing a **Quick Test**, you can use a dropdown to select an iteration and compare results.

Once satisfied with an iteration, you can publish it to make it accessible to external applications. This allows you to maintain a stable published version for devices while working on improvements in new iterations.

### Task - publish an iteration

Iterations are published through the Custom Vision portal.

1. Open the Custom Vision portal at [CustomVision.ai](https://customvision.ai) and sign in if needed. Then, open your `fruit-quality-detector` project.

1. Select the **Performance** tab at the top.

1. Choose the latest iteration from the *Iterations* list on the side.

1. Click the **Publish** button for the selected iteration.

    ![The publish button](../../../../../translated_images/en/custom-vision-publish-button.b7174e1977b0c33b8b72d4e5b1326c779e0af196f3849d09985ee2d7d5493a39.png)

1. In the *Publish Model* dialog, set the *Prediction resource* to the `fruit-quality-detector-prediction` resource created in the last lesson. Keep the name as `Iteration2` and click **Publish**.

1. After publishing, click the **Prediction URL** button. This will display the prediction API details needed to call the model from your IoT device. Focus on the section labeled *If you have an image file*. Copy the URL, which will look like:

    ```output
    https://<location>.api.cognitive.microsoft.com/customvision/v3.0/Prediction/<id>/classify/iterations/Iteration2/image
    ```

    Here, `<location>` is the location of your custom vision resource, and `<id>` is a unique identifier.

    Also, copy the *Prediction-Key*. This secure key is required to access the model. Only applications with this key can use the model; others will be denied.

    ![The prediction API dialog showing the URL and key](../../../../../translated_images/en/custom-vision-prediction-key-endpoint.30c569ffd0338864f319911f052d5e9b8c5066cb0800a26dd6f7ff5713130ad8.png)

✅ When a new iteration is published, it will have a different name. How would you update the iteration your IoT device is using?

## Classify images from your IoT device

You can now use the connection details to call the image classifier from your IoT device.

### Task - classify images from your IoT device

Follow the appropriate guide to classify images using your IoT device:

* [Arduino - Wio Terminal](wio-terminal-classify-image.md)
* [Single-board computer - Raspberry Pi/Virtual IoT device](single-board-computer-classify-image.md)

## Improve the model

You may notice that predictions from your IoT device's camera differ from what you expect. This happens because the model was trained on data that differs from the images used for predictions.

For optimal results, train the model with images similar to those used for predictions. For example, if you used a phone camera for training, the image quality, sharpness, and color may differ from those of an IoT device's camera.

![2 banana pictures, a low resolution one with poor lighting from an IoT device, and a high resolution one with good lighting from a phone](../../../../../translated_images/en/banana-picture-compare.174df164dc326a42cf7fb051a7497e6113c620e91552d92ca914220305d47d9a.png)

In the image above, the left banana picture was taken with a Raspberry Pi Camera, while the right one was taken with an iPhone. The iPhone image is sharper, with brighter colors and better contrast.

✅ What other factors might cause incorrect predictions from your IoT device's images? Consider the environment where the IoT device operates and what might affect the captured images.

To improve the model, retrain it using images captured from the IoT device.

### Task - improve the model

1. Classify multiple images of both ripe and unripe fruit using your IoT device.

1. In the Custom Vision portal, retrain the model using the images in the *Predictions* tab.

    > ⚠️ Refer to [the instructions for retraining your classifier in lesson 1 if needed](../1-train-fruit-detector/README.md#retrain-your-image-classifier).

1. If your new images differ significantly from the original training images, delete the original ones. Go to the *Training Images* tab, select the images, and click **Delete**. To select an image, hover over it and click the tick that appears.

1. Train a new iteration of the model and publish it using the steps above.

1. Update the endpoint URL in your code and re-run the app.

1. Repeat these steps until you are satisfied with the prediction results.

---

## 🚀 Challenge

How much do image resolution and lighting affect predictions?

Try adjusting the resolution of the images in your device code and observe the impact on image quality. Experiment with different lighting conditions as well.

If you were designing a production device for farms or factories, how would you ensure consistent results?

## Post-lecture quiz

[Post-lecture quiz](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/32)

## Review & Self Study

You trained your custom vision model using the portal, which requires pre-existing images. In real-world scenarios, you may not have training data that matches the images captured by your device's camera. To address this, you can train the model directly from your device using the training API, allowing you to use images captured by the IoT device.

* Learn more about the training API in the [using the Custom Vision SDK quick start](https://docs.microsoft.com/azure/cognitive-services/custom-vision-service/quickstarts/image-classification?WT.mc_id=academic-17441-jabenn&tabs=visual-studio&pivots=programming-language-python)

## Assignment

[Respond to classification results](assignment.md)

---

**Disclaimer**:  
This document has been translated using the AI translation service [Co-op Translator](https://github.com/Azure/co-op-translator). While we aim for accuracy, please note that automated translations may include errors or inaccuracies. The original document in its native language should be regarded as the authoritative source. For critical information, professional human translation is advised. We are not responsible for any misunderstandings or misinterpretations resulting from the use of this translation.