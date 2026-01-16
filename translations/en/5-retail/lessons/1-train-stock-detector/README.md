<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "8df310a42f902139a01417dacb1ffbef",
  "translation_date": "2025-08-28T20:12:37+00:00",
  "source_file": "5-retail/lessons/1-train-stock-detector/README.md",
  "language_code": "en"
}
-->
# Train a stock detector

![A sketchnote overview of this lesson](../../../../../translated_images/en/lesson-19.cf6973cecadf080c4b526310620dc4d6f5994c80fb0139c6f378cc9ca2d435cd.jpg)

> Sketchnote by [Nitya Narasimhan](https://github.com/nitya). Click the image for a larger version.

This video provides an overview of Object Detection using the Azure Custom Vision service, which will be explored in this lesson.

[![Custom Vision 2 - Object Detection Made Easy | The Xamarin Show](https://img.youtube.com/vi/wtTYSyBUpFc/0.jpg)](https://www.youtube.com/watch?v=wtTYSyBUpFc)

> 🎥 Click the image above to watch the video

## Pre-lecture quiz

[Pre-lecture quiz](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/37)

## Introduction

In the previous project, you used AI to train an image classifier—a model that can determine whether an image contains something, such as ripe or unripe fruit. Another type of AI model that works with images is object detection. These models don’t classify an image by tags; instead, they are trained to recognize objects and locate them within images. This means they can not only detect the presence of an object but also identify its position in the image, enabling you to count objects.

In this lesson, you will learn about object detection, including its applications in retail. You will also learn how to train an object detector in the cloud.

In this lesson, we’ll cover:

* [Object detection](../../../../../5-retail/lessons/1-train-stock-detector)
* [Use object detection in retail](../../../../../5-retail/lessons/1-train-stock-detector)
* [Train an object detector](../../../../../5-retail/lessons/1-train-stock-detector)
* [Test your object detector](../../../../../5-retail/lessons/1-train-stock-detector)
* [Retrain your object detector](../../../../../5-retail/lessons/1-train-stock-detector)

## Object detection

Object detection involves identifying objects in images using AI. Unlike the image classifier you trained in the last project, object detection doesn’t focus on predicting the best tag for an entire image. Instead, it identifies one or more objects within an image.

### Object detection vs image classification

Image classification is about categorizing an image as a whole—determining the probabilities that the entire image matches each tag. The model returns probabilities for every tag it was trained on.

![Image classification of cashew nuts and tomato paste](../../../../../translated_images/en/image-classifier-cashews-tomato.bc2e16ab8f05cf9ac0f59f73e32efc4227f9a5b601b90b2c60f436694547a965.png)

In the example above, two images are classified using a model trained to identify tubs of cashew nuts or cans of tomato paste. The first image is a tub of cashew nuts, and the classifier provides the following results:

| Tag            | Probability |
| -------------- | ----------: |
| `cashew nuts`  | 98.4%       |
| `tomato paste` | 1.6%        |

The second image is a can of tomato paste, and the results are:

| Tag            | Probability |
| -------------- | ----------: |
| `cashew nuts`  | 0.7%        |
| `tomato paste` | 99.3%       |

You could use these probabilities with a threshold percentage to predict what’s in the image. But what if an image contained multiple cans of tomato paste or both cashew nuts and tomato paste? The results might not provide the information you need. This is where object detection becomes useful.

Object detection involves training a model to recognize objects. Instead of providing images containing the object and labeling the entire image with a tag, you highlight the specific section of the image containing the object and tag that. You can tag a single object or multiple objects in an image. This way, the model learns what the object itself looks like, not just what images containing the object look like.

When you use the model to make predictions, instead of receiving a list of tags and probabilities, you get a list of detected objects, their bounding boxes, and the probability that each object matches its assigned tag.

> 🎓 *Bounding boxes* are the rectangles drawn around an object.

![Object detection of cashew nuts and tomato paste](../../../../../translated_images/en/object-detector-cashews-tomato.1af7c26686b4db0e709754aeb196f4e73271f54e2085db3bcccb70d4a0d84d97.png)

The image above contains both a tub of cashew nuts and three cans of tomato paste. The object detector identifies the cashew nuts, returning the bounding box around the cashew nuts along with the probability (97.6%) that the bounding box contains the object. The detector also identifies three cans of tomato paste, providing separate bounding boxes for each detected can, along with the probability for each.

✅ Think of some scenarios where you might want to use image-based AI models. Which ones would require classification, and which would require object detection?

### How object detection works

Object detection uses complex ML models. These models divide the image into multiple cells and check whether the center of a bounding box matches the center of an image that resembles one of the training images. You can think of this as running an image classifier over different parts of the image to find matches.

> 💁 This is a simplified explanation. There are many techniques for object detection, and you can learn more about them on the [Object detection page on Wikipedia](https://wikipedia.org/wiki/Object_detection).

There are several models capable of object detection. One well-known model is [YOLO (You Only Look Once)](https://pjreddie.com/darknet/yolo/), which is extremely fast and can detect 20 different classes of objects, such as people, dogs, bottles, and cars.

✅ Learn more about the YOLO model at [pjreddie.com/darknet/yolo/](https://pjreddie.com/darknet/yolo/)

Object detection models can be retrained using transfer learning to detect custom objects.

## Use object detection in retail

Object detection has many applications in retail, including:

* **Stock checking and counting** - Identifying when stock is low on shelves. If stock levels are too low, notifications can be sent to staff or robots to restock shelves.
* **Mask detection** - In stores with mask policies during public health events, object detection can identify people wearing masks and those without.
* **Automated billing** - Detecting items picked off shelves in automated stores and billing customers accordingly.
* **Hazard detection** - Identifying broken items on the floor or spilled liquids and alerting cleaning crews.

✅ Research additional use cases for object detection in retail.

## Train an object detector

You can train an object detector using Custom Vision, similar to how you trained an image classifier.

### Task - create an object detector

1. Create a Resource Group for this project called `stock-detector`.

1. Create a free Custom Vision training resource and a free Custom Vision prediction resource in the `stock-detector` resource group. Name them `stock-detector-training` and `stock-detector-prediction`.

    > 💁 You can only have one free training and prediction resource, so ensure you’ve cleaned up your project from earlier lessons.

    > ⚠️ Refer to [the instructions for creating training and prediction resources from project 4, lesson 1 if needed](../../../4-manufacturing/lessons/1-train-fruit-detector/README.md#task---create-a-cognitive-services-resource).

1. Open the Custom Vision portal at [CustomVision.ai](https://customvision.ai) and sign in with the Microsoft account linked to your Azure account.

1. Follow the [Create a new Project section of the Build an object detector quickstart on the Microsoft docs](https://docs.microsoft.com/azure/cognitive-services/custom-vision-service/get-started-build-detector?WT.mc_id=academic-17441-jabenn#create-a-new-project) to create a new Custom Vision project. The UI may change, so these docs are the most up-to-date reference.

    Name your project `stock-detector`.

    When creating your project, use the `stock-detector-training` resource you created earlier. Select the *Object Detection* project type and the *Products on Shelves* domain.

    ![The settings for the custom vision project with the name set to fruit-quality-detector, no description, the resource set to fruit-quality-detector-training, the project type set to classification, the classification types set to multi class and the domains set to food](../../../../../translated_images/en/custom-vision-create-object-detector-project.32d4fb9aa8e7e7375f8a799bfce517aca970f2cb65e42d4245c5e635c734ab29.png)

    ✅ The *Products on Shelves* domain is specifically designed for detecting stock on store shelves. Learn more about the different domains in the [Select a domain documentation on Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/custom-vision-service/select-domain?WT.mc_id=academic-17441-jabenn#object-detection).

✅ Take some time to explore the Custom Vision UI for your object detector.

### Task - train your object detector

To train your model, you’ll need a set of images containing the objects you want to detect.

1. Collect images of the object you want to detect. You’ll need at least 15 images of each object from various angles and lighting conditions, but more is better. Since this object detector uses the *Products on Shelves* domain, try to arrange the objects as if they were on a store shelf. You’ll also need a few images to test the model. If you’re detecting multiple objects, include testing images with all the objects.

    > 💁 Images with multiple objects count toward the 15-image minimum for all objects in the image.

    Your images should be in PNG or JPEG format and smaller than 6MB. If you use an iPhone, for example, the images may be high-resolution HEIC files, so you’ll need to convert and possibly resize them. The more images you have, the better, and you should aim for a balanced number of images for each object.

    You can find example images of cashew nuts and tomato paste in the [images](../../../../../5-retail/lessons/1-train-stock-detector/images) folder.

1. Follow the [Upload and tag images section of the Build an object detector quickstart on the Microsoft docs](https://docs.microsoft.com/azure/cognitive-services/custom-vision-service/get-started-build-detector?WT.mc_id=academic-17441-jabenn#upload-and-tag-images) to upload your training images. Create relevant tags for the objects you want to detect.

    ![The upload dialogs showing the upload of ripe and unripe banana pictures](../../../../../translated_images/en/image-upload-object-detector.77c7892c3093cb59b79018edecd678749a75d71a099bc8a2d2f2f76320f88a5b.png)

    When drawing bounding boxes around objects, keep them tight around the object. Tagging all the images can take time, but the tool will suggest bounding boxes, speeding up the process.

    ![Tagging some tomato paste](../../../../../translated_images/en/object-detector-tag-tomato-paste.f47c362fb0f0eb582f3bc68cf3855fb43a805106395358d41896a269c210b7b4.png)

    > 💁 If you have more than 15 images per object, you can train after tagging 15 images and use the **Suggested tags** feature. This uses the trained model to detect objects in untagged images. You can confirm or reject the suggested bounding boxes, saving time.

1. Follow the [Train the detector section of the Build an object detector quickstart on the Microsoft docs](https://docs.microsoft.com/azure/cognitive-services/custom-vision-service/get-started-build-detector?WT.mc_id=academic-17441-jabenn#train-the-detector) to train the object detector on your tagged images.

    Choose **Quick Training** as the training type.

The object detector will begin training. This process takes a few minutes.

## Test your object detector

Once your object detector is trained, you can test it by providing new images to detect objects.

### Task - test your object detector

1. Use the **Quick Test** button to upload testing images and verify that the objects are detected. Use the testing images you prepared earlier, not the ones used for training.

    ![3 cans of tomato paste detected with probabilities of 38%, 35.5% and 34.6%](../../../../../translated_images/en/object-detector-detected-tomato-paste.52656fe87af4c37b4ee540526d63e73ed075da2e54a9a060aa528e0c562fb1b6.png)

1. Test all the available testing images and observe the probabilities.

## Retrain your object detector

When testing your object detector, it may not perform as expected, just like image classifiers in the previous project. You can improve your object detector by retraining it with images where it made mistakes.

Every time you make a prediction using the quick test option, the image and results are saved. You can use these images to retrain your model.

1. Go to the **Predictions** tab to find the images you used for testing.

1. Confirm any correct detections, delete incorrect ones, and add any missing objects.

1. Retrain and re-test the model.

---

## 🚀 Challenge

What would happen if you used the object detector with similar-looking items, such as cans of tomato paste and chopped tomatoes from the same brand?

If you have similar-looking items, test this by adding images of them to your object detector.

## Post-lecture quiz
[Post-lecture quiz](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/38)

## Review & Self Study

* When you trained your object detector, you would have seen values for *Precision*, *Recall*, and *mAP* that evaluate the performance of the model you created. Learn more about these metrics by reading [the Evaluate the detector section of the Build an object detector quickstart on the Microsoft docs](https://docs.microsoft.com/azure/cognitive-services/custom-vision-service/get-started-build-detector?WT.mc_id=academic-17441-jabenn#evaluate-the-detector).
* Explore additional information about object detection on the [Object detection page on Wikipedia](https://wikipedia.org/wiki/Object_detection).

## Assignment

[Compare domains](assignment.md)

---

**Disclaimer**:  
This document has been translated using the AI translation service [Co-op Translator](https://github.com/Azure/co-op-translator). While we aim for accuracy, please note that automated translations may include errors or inaccuracies. The original document in its native language should be regarded as the authoritative source. For critical information, professional human translation is advised. We are not responsible for any misunderstandings or misinterpretations resulting from the use of this translation.