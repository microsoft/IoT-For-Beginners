<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "1c9e5fa8b7be726c75a97232b1e41c97",
  "translation_date": "2025-08-28T20:14:23+00:00",
  "source_file": "5-retail/lessons/2-check-stock-device/README.md",
  "language_code": "en"
}
-->
# Check stock from an IoT device

![A sketchnote overview of this lesson](../../../../../translated_images/en/lesson-20.0211df9551a8abb300fc8fcf7dc2789468dea2eabe9202273ac077b0ba37f15e.jpg)

> Sketchnote by [Nitya Narasimhan](https://github.com/nitya). Click the image for a larger version.

## Pre-lecture quiz

[Pre-lecture quiz](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/39)

## Introduction

In the previous lesson, you learned about the various applications of object detection in retail and how to train an object detector to identify stock. In this lesson, you'll learn how to use your object detector on an IoT device to count stock.

This lesson will cover:

* [Stock counting](../../../../../5-retail/lessons/2-check-stock-device)
* [Call your object detector from your IoT device](../../../../../5-retail/lessons/2-check-stock-device)
* [Bounding boxes](../../../../../5-retail/lessons/2-check-stock-device)
* [Retrain the model](../../../../../5-retail/lessons/2-check-stock-device)
* [Count stock](../../../../../5-retail/lessons/2-check-stock-device)

> 🗑 This is the final lesson in this project. After completing this lesson and the assignment, remember to clean up your cloud services. You'll need these services to complete the assignment, so ensure you finish that first.
>
> Refer to [the clean up your project guide](../../../clean-up.md) if you need instructions on how to do this.

## Stock counting

Object detectors can be used to check stock, either by counting items or ensuring they are in the correct location. IoT devices equipped with cameras can be deployed throughout a store to monitor stock, starting with high-priority areas where restocking is critical, such as shelves with small quantities of high-value items.

For instance, if a camera monitors a shelf that holds 8 cans of tomato paste, and the object detector identifies only 7 cans, it indicates one is missing and needs to be restocked.

![7 cans of tomato paste on a shelf, 4 on the top row, 3 on top](../../../../../translated_images/en/stock-7-cans-tomato-paste.f86059cc573d7bec.webp)

In the image above, an object detector has identified 7 cans of tomato paste on a shelf designed to hold 8. The IoT device can notify staff about the need to restock and even provide the location of the missing item, which is especially useful if robots are used for restocking.

> 💁 Depending on the store and the item's popularity, restocking might not occur if only one can is missing. You would need to create an algorithm that determines restocking needs based on your products, customers, and other factors.

✅ In what other scenarios could you combine object detection with robots?

Sometimes, incorrect stock ends up on shelves. This could happen due to human error during restocking or customers placing items back in the wrong spot. For non-perishable items like canned goods, this is merely inconvenient. However, for perishable items like frozen or chilled goods, this could render the product unsellable, as it may be unclear how long it was out of refrigeration.

Object detection can identify misplaced items and alert a human or robot to return them to their correct location.

![A rogue can of baby corn on the tomato paste shelf](../../../../../translated_images/en/stock-rogue-corn.be1f3ada8c457854.webp)

In the image above, a can of baby corn has been placed on the tomato paste shelf. The object detector identifies this, enabling the IoT device to notify a human or robot to correct the mistake.

## Call your object detector from your IoT device

The object detector you trained in the previous lesson can now be accessed from your IoT device.

### Task - publish an iteration of your object detector

Iterations are published through the Custom Vision portal.

1. Open the Custom Vision portal at [CustomVision.ai](https://customvision.ai) and sign in if you haven't already. Then, open your `stock-detector` project.

1. Click the **Performance** tab at the top.

1. Select the latest iteration from the *Iterations* list on the side.

1. Click the **Publish** button for the iteration.

    ![The publish button](../../../../../translated_images/en/custom-vision-object-detector-publish-button.34ee379fc650ccb9856c3868d0003f413b9529f102fc73c37168c98d721cc293.png)

1. In the *Publish Model* dialog, set the *Prediction resource* to the `stock-detector-prediction` resource you created in the last lesson. Keep the name as `Iteration2`, and click the **Publish** button.

1. Once published, click the **Prediction URL** button. This will display the prediction API details, which you'll need to call the model from your IoT device. Look for the section labeled *If you have an image file*. Copy the URL, which will look something like:

    ```output
    https://<location>.api.cognitive.microsoft.com/customvision/v3.0/Prediction/<id>/detect/iterations/Iteration2/image
    ```

    Here, `<location>` corresponds to the location of your custom vision resource, and `<id>` is a long alphanumeric ID.

    Also, copy the *Prediction-Key* value. This secure key is required to access the model. Only applications with this key can use the model; others will be denied access.

    ![The prediction API dialog showing the URL and key](../../../../../translated_images/en/custom-vision-prediction-key-endpoint.30c569ffd0338864f319911f052d5e9b8c5066cb0800a26dd6f7ff5713130ad8.png)

✅ When a new iteration is published, it will have a different name. How would you update the IoT device to use the new iteration?

### Task - call your object detector from your IoT device

Follow the appropriate guide below to use the object detector on your IoT device:

* [Arduino - Wio Terminal](wio-terminal-object-detector.md)
* [Single-board computer - Raspberry Pi/Virtual device](single-board-computer-object-detector.md)

## Bounding boxes

When you use the object detector, it not only identifies objects with their tags and probabilities but also provides bounding boxes. These boxes define the area where the object was detected.

> 💁 A bounding box is a rectangle that outlines the detected object.

In the **Predictions** tab of Custom Vision, the results of a prediction include bounding boxes drawn on the image sent for analysis.

![4 cans of tomato paste on a shelf with predictions for the 4 detections of 35.8%, 33.5%, 25.7% and 16.6%](../../../../../translated_images/en/custom-vision-stock-prediction.942266ab1bcca3410ecdf23643b9f5f570cfab2345235074e24c51f285777613.png)

In the image above, 4 cans of tomato paste were detected. Red rectangles indicate the bounding boxes for each detected object.

✅ Open the predictions in Custom Vision and examine the bounding boxes.

Bounding boxes are defined by four values: top, left, height, and width. These values range from 0 to 1, representing percentages of the image's dimensions. The origin (0,0) is the top-left corner of the image. The top value indicates the distance from the top, while the bottom of the bounding box is calculated as the top plus the height.

![A bounding box around a can of tomato paste](../../../../../translated_images/en/bounding-box.1420a7ea0d3d15f71e1ffb5cf4b2271d184fac051f990abc541975168d163684.png)

In the image above, which is 600 pixels wide and 800 pixels tall, the bounding box starts 320 pixels down, giving a top value of 0.4 (800 x 0.4 = 320). From the left, it starts 240 pixels across, giving a left value of 0.4 (600 x 0.4 = 240). The height is 240 pixels, giving a height value of 0.3 (800 x 0.3 = 240). The width is 120 pixels, giving a width value of 0.2 (600 x 0.2 = 120).

| Coordinate | Value |
| ---------- | ----: |
| Top        | 0.4   |
| Left       | 0.4   |
| Height     | 0.3   |
| Width      | 0.2   |

Using percentage values ensures that the bounding box scales proportionally, regardless of the image size.

Bounding boxes and probabilities can be used to evaluate detection accuracy. For example, if overlapping objects are detected, your code can analyze the bounding boxes and ignore improbable detections.

![Two bounding boxes overlapping a can of tomato paste](../../../../../translated_images/en/overlap-object-detection.d431e03cae75072a2760430eca7f2c5fdd43045bfd72dadcbf12711f7cd6c2ae.png)

In the example above, one bounding box predicts a can of tomato paste with 78.3% confidence. A second, smaller bounding box inside the first predicts the same object with 64.3% confidence. Your code can identify the overlap and discard the less probable detection.

✅ Can you think of a scenario where detecting one object inside another is valid?

## Retrain the model

As with the image classifier, you can retrain your model using data collected by your IoT device. This real-world data ensures the model performs well in practical scenarios.

Unlike the image classifier, you must review each bounding box detected by the model. Incorrect boxes must be deleted, and misplaced ones adjusted.

### Task - retrain the model

1. Capture a variety of images using your IoT device.

1. In the **Predictions** tab, select an image. Red rectangles will indicate the detected bounding boxes.

1. Review each bounding box. Select a box to view its tag. Adjust its size using the corner handles if needed. If the tag is incorrect, delete it with the **X** button and assign the correct tag. Delete any bounding boxes that don't contain objects using the trashcan button.

1. Once done, close the editor. The image will move from the **Predictions** tab to the **Training Images** tab. Repeat this process for all predictions.

1. Click the **Train** button to retrain your model. After training, publish the new iteration and update your IoT device with the new iteration's URL.

1. Redeploy your code and test your IoT device.

## Count stock

By combining the number of detected objects with their bounding boxes, you can count the stock on a shelf.

### Task - count stock

Follow the appropriate guide below to count stock using the object detector's results on your IoT device:

* [Arduino - Wio Terminal](wio-terminal-count-stock.md)
* [Single-board computer - Raspberry Pi/Virtual device](single-board-computer-count-stock.md)

---

## 🚀 Challenge

Can you detect incorrect stock? Train your model to recognize multiple objects, then update your app to alert you if the wrong stock is detected.

Take it a step further by detecting side-by-side stock on the same shelf. Define limits on bounding boxes to identify misplaced items.

## Post-lecture quiz

[Post-lecture quiz](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/40)

## Review & Self Study

* Learn more about designing an end-to-end stock detection system from the [Out of stock detection at the edge pattern guide on Microsoft Docs](https://docs.microsoft.com/hybrid/app-solutions/pattern-out-of-stock-at-edge?WT.mc_id=academic-17441-jabenn).
* Explore other ways to build retail solutions using IoT and cloud services by watching this [Behind the scenes of a retail solution - Hands On! video on YouTube](https://www.youtube.com/watch?v=m3Pc300x2Mw).

## Assignment

[Use your object detector on the edge](assignment.md)

---

**Disclaimer**:  
This document has been translated using the AI translation service [Co-op Translator](https://github.com/Azure/co-op-translator). While we aim for accuracy, please note that automated translations may include errors or inaccuracies. The original document in its native language should be regarded as the authoritative source. For critical information, professional human translation is advised. We are not responsible for any misunderstandings or misinterpretations resulting from the use of this translation.