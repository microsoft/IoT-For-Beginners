# Manufacturing and processing - using IoT to improve the processing of food

Once food reaches a central hub or processing plant, it isn't always just shipped out to supermarkets. A lot of the time the food goes through a number of processing steps, such as sorting by quality. This is a process that used to be manual - it would start in the field when pickers would only pick ripe fruit, then at the factory the fruit would be ride a conveyer belt and employees would manually remove any bruised or rotten fruit. Having picked and sorted strawberries myself as a summer job during school, I can testify that this isn't a fun job.

More modern setups rely on IoT for sorting. Some of the earliest devices like the sorters from [Weco](https://wecotek.com) use optical sensors to detect the quality of produce, rejecting green tomatoes for example. These can be deployed in harvesters on the farm itself, or in processing plants.

As advances happen in Artificial Intelligence (AI) and Machine Learning (ML), these machines can become more advanced, using ML models trained to distinguish between fruit and foreign objects such as rocks, dirt or insects. These models can also be trained to detect fruit quality, not just bruised fruit but early detection of disease or other crop problems.

> 🎓 The term *ML model* refers to the output of training machine learning software on a set of data. For example, you can train a ML model to distinguish between ripe and unripe tomatoes, then use the model on new images to see if the tomatoes are ripe or not.

In these 4 lessons you'll learn how to train image-based AI models to detect fruit quality, how to use these from an IoT device, and how to run these on the edge - that is on an IoT device rather than in the cloud.

> 💁 These lessons will use some cloud resources. If you don't complete all the lessons in this project, make sure you [Clean up your project](../clean-up.md).

## Topics

1. [Train a fruit quality detector](./lessons/1-train-fruit-detector/README.md)
1. [Check fruit quality from an IoT device](./lessons/2-check-fruit-from-device/README.md)
1. [Run your fruit detector on the edge](./lessons/3-run-fruit-detector-edge/README.md)
1. [Trigger fruit quality detection from a sensor](./lessons/4-trigger-fruit-detector/README.md)

## Credits

All the lessons were written with ♥️ by [Jim Bennett](https://GitHub.com/JimBobBennett)
