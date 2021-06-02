# Train a fruit quality detector

Add a sketchnote if possible/appropriate

![Embed a video here if available](video-url)

## Pre-lecture quiz

[Pre-lecture quiz](https://brave-island-0b7c7f50f.azurestaticapps.net/quiz/29)

## Introduction

The recent rise in Artificial Intelligence (AI) and Machine Learning (ML) is providing a wide range of capabilities to todays developers. ML models can be trained to recognize different things in images, including unripe fruit, and this can be used in IoT devices to help sort produce either as it is being harvested, or during processing in factories or warehouses.

In this lesson you will learn about image classification - using ML models to distinguish between images of different things. You will learn how to train an image classifier to distinguish between fruit that is good, and fruit that is bad, either under or over ripe, bruised, or rotten.

In this lesson we'll cover:

* [Using AI and ML to sort food](#using-ai-and-ml-to-sort-food)
* [Image classification via Machine Learning](#image-classification-via-machine-learning)
* [Train an image classifier](#train-an-image-classifier)
* [Test your image classifier](#test-your-image-classifier)

## Using AI and ML to sort food

Feeding the global population is hard, especially at a price that makes food affordable for all. One of the largest costs is labor, so farmers are increasingly turning to automation and tools like IoT to reduce their labor costs. Harvesting by hand is labor intensive (and often backbreaking work), and is being replaced by machinery, especially in richer nations. Despite the savings in cost of using machinery to harvest, there is a downside - the ability to sort food as it is being harvested.

Not all crops ripen evenly. Tomatoes, for example, can still have some green fruits on the vine when the majority is ready for harvest. Although it is a waste to harvest these early, it is cheaper and easier for the farmer to harvest everything using machinery and dispose of the unripe produce later.

✅ Have a look at different fruits or vegetables, either growing near you in farms or in your garden, or in shops, Are they all the same ripeness, or do you see variation?

Sorting produce moved from the harvest to the factory, with food travelling on long conveyer belts with teams of people picking over the produce removing anything that wasn't up to the required quality standard. Harvesting was cheaper thanks to machinery, but there was still a cost to manually sort food.

![If a red tomato is detected it continues its journey uninterrupted. If a green tomato is detected it is flicked into a waste bin by a lever](../../../images/optical-tomato-sorting.png)

***If a red tomato is detected it continues its journey uninterrupted. If a green tomato is detected it is flicked into a waste bin by a lever. tomato by parkjisun from the Noun Project - from the [Noun Project](https://thenounproject.com)***

The next evolution was to use machines to sort, either built into the harvester, or in the processing plants. The first generation of these machines used optical sensors to detect colors, controlling actuators to push green tomatoes into a waste bin using levers of puffs of air, leaving red tomatoes to continue on a network of conveyor belts.

The video below shows one of these machines in action.

[![Automatic sorting of tomatoes via color](https://img.youtube.com/vi/AcRL91DouAU/0.jpg)](https://www.youtube.com/watch?v=AcRL91DouAU)

In this video, as tomatoes fall from one conveyer belt to another, green tomatoes are detected and flicked into a bin using levers.

✅ What conditions would you need in a factory or in a field for these optical sensors to work correctly?

The latest evolutions of these sorting machines take advantage of AI and ML, using models trained to distinguish good produce from bad, not just by obvious color differences such as green tomatoes vs red, but by more subtle differences in appearance that can indicate disease or bruising.

## Image classification via Machine Learning

Traditional programming is where you take data, apply an algorithm to the data, and get output. For example, in the last project you took GPS coordinates and a geofence, applied an algorithm that was provided by Azure Maps, and got back a result of if the point was inside or outside the geofence. You input more data, you get more output.

![Traditional development takes input and an algorithm and gives output. Machine learning uses input and output data to train a model, and this model can take new input data to generate new output](../../../images/traditional-vs-ml.png)

Machine learning turns this around - you start with data and known outputs, and the machine learning tools work out the algorithm. You can then take that algorithm, called a *machine learning model*, and input new data and get new output.

> 🎓 The process of a machine learning tool generating a model is called *training*. The inputs and known outputs are called *training data*.

For example, you could give a model millions of pictures of unripe strawberries as input training data, with the training output set as `unripe`, and millions of ripe strawberry pictures as training data with the output set as `ripe`. The ML tools will then generate a model. You then give this model a new picture of a strawberry and it will predict if the new picture is a ripe or an unripe strawberry.

> 🎓 The results of ML models are called *predictions*

![2 strawberries, a rip one with a prediction of 99.7% ripe, 0.3% unripe, and an unripe one with a prediction of 1.4% ripe, 98.6% unripe](../../../images/strawberries-ripe-vs-unripe-predictions.png)

ML models don't give a binary answer, instead they give probabilities. For example, a model may be given a picture of a strawberry and predict `ripe` at 99.7% and `unripe` at 0.3%. Your code would then pick the best prediction and decide the strawberry is ripe.

The ML model used to detect images like this is called an *image classifier* - it is given labelled images, and then classifies new images based off these labels.

## Train an image classifier

To successfully train an image classifier you need millions of images. As it turns out, once you have an image classifier trained on millions or billions of assorted images, you can re-use it and re-train it using a small set of images and get great results, using a process called transfer learning.

Once an image classifier has been trained for a wide variety of images, it's internals are great at recognizing shapes, colors and patterns. Transfer learning allows the model to take what it has already learned in recognizing image parts, and use that to recognize new images.

![Once you can recognize shapes, they can be put into different configurations to make a boat or a cat](../../../images/shapes-to-images.png)

You can think of this as a bit like children's shape books, where once you can recognize a semi-circle, a rectangle and a triangle, you can recognize a sailboat or a cat depending on the configuration of these shapes. The image classifier can recognize the shapes, and the transfer learning teaches it what combination makes a boat or a cat - or a ripe strawberry.

There are a wide range of tools that can help you do this, including cloud-based services that can help you train your model, then use it via web APIs.

> 💁 Training these models takes a lot of computer power, usually via Graphics Processing Units, or GPUs. The same specialized hardware that makes graphics on your Xbox look amazing can also be used to train machine learning models. By using the cloud you have access to the power you need, just for the time you need it.

## Custom Vision

Custom Vision is a cloud based tool for training image classifiers. It allows you to train a classifier using only a small number of images. You can upload images through a web portal, web API or an SDK, giving each image a *tag* that has the classification of that image. You then train the model, and test it out to see how well it performs. Once you are happy with the model, you can publish versions of it that can be accessed through a web API or an SDK.

Custom Vision is part of a range of AI tools from Microsoft called Cognitive Services. These are AI tools that can be used either without any training, or with a small amount of training. They include speech recognition and translation, language understanding and image analysis. These are available with a free tier as services in Azure.

> 💁 The free tier is more than enough to create a model, train it, then use it for development work. You can read about the limits of the free tier on the [Custom Vision Limits and quotas page on Microsoft docs](https://docs.microsoft.com/azure/cognitive-services/custom-vision-service/limits-and-quotas?WT.mc_id=academic-17441-jabenn).

### Task - create a cognitive services resource

To use Custom Vision, you first need to create two cognitive services resources in Azure using the Azure CLI, one for Custom Vision training and one for Custom Vision prediction.

1. Create a Resource Group for this project called `fruit-quality-detector`

1. Use the following command to create a free Custom Vision training resource:

    ```sh
    az cognitiveservices account create --name fruit-quality-detector-training \
                                        --resource-group fruit-quality-detector \
                                        --kind CustomVision.Training \
                                        --sku F0 \
                                        --yes \
                                        --location <location>
    ```

    Replace `<location>` with the location you used when creating the Resource Group.

    This will create a Custom Vision training resource in your Resource Group. It will be called `fruit-quality-detector-training` and use the `F0` sku, which is the free tier. The `--yes` option means you agree to the terms and conditions of the cognitive services.

1. Use the following command to create a free Custom Vision prediction resource:

    ```sh
    az cognitiveservices account create --name fruit-quality-detector-prediction \
                                        --resource-group fruit-quality-detector \
                                        --kind CustomVision.Prediction \
                                        --sku F0 \
                                        --yes \
                                        --location <location>
    ```

    Replace `<location>` with the location you used when creating the Resource Group.

    This will create a Custom Vision training resource in your Resource Group. It will be called `fruit-quality-detector-prediction` and use the `F0` sku, which is the free tier. The `--yes` option means you agree to the terms and conditions of the cognitive services.

### Task - create an image classifier project

1. Follow the [Create a new Project section of the Build a classifier quickstart on the Microsoft docs](https://docs.microsoft.com/azure/cognitive-services/custom-vision-service/getting-started-build-a-classifier?WT.mc_id=academic-17441-jabenn#create-a-new-project) to create a new Custom Vision project. The UI may change and these docs are always the most up to date reference.

    Call your project `food-quality-detector`.

    When you create your project, make sure to use the `fruit-quality-detector-training` resource you created earlier. Use a *Classification* project type, a *Multiclass* classification type, and the *Food* domain.

### Task - train your image classifier project

To train an image classifier, you will need multiple pictures of fruit, both good and bad quality to tag as good and bad, such as an ripe and an overripe banana.

> 💁 These classifiers can classify images of anything, so if you don't have fruit to hand of differing quality, you can use two different types of fruit, or cats and dogs!

Ideally each picture should be just the fruit, with either a consistent background, or a wide variety of backgrounds. Ensure there's nothing in the background that is specific to ripe vs unripe fruit.

> 💁 It's important not to have specific backgrounds for each tag, otherwise the classifier may just classify based on the background. There was an example of a classifier for skin cancer that was trained on moles both normal and cancerous, and the cancerous ones all had rulers against them to measure the size. It turned out the classifier was 100% accurate at identifying rulers in pictures.

## Test your image classifier

### Task - test your image classifier

---

## 🚀 Challenge

## Post-lecture quiz

[Post-lecture quiz](https://brave-island-0b7c7f50f.azurestaticapps.net/quiz/30)

## Review & Self Study

## Assignment

[](assignment.md)
