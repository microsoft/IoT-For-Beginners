<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "3764e089adf2d5801272bc0895f8498b",
  "translation_date": "2025-08-28T18:58:00+00:00",
  "source_file": "4-manufacturing/README.md",
  "language_code": "en"
}
-->
# Manufacturing and processing - using IoT to improve the processing of food

Once food reaches a central hub or processing plant, it doesn’t always get shipped directly to supermarkets. Often, the food undergoes several processing steps, such as being sorted by quality. This process used to be done manually—it would start in the field, where pickers would only harvest ripe fruit, and then continue at the factory, where the fruit would travel along a conveyor belt, and employees would manually remove any bruised or rotten pieces. Having picked and sorted strawberries myself as a summer job during school, I can confirm that this is not an enjoyable task.

Modern systems now rely on IoT for sorting. Some of the earliest devices, like the sorters from [Weco](https://wecotek.com), use optical sensors to assess the quality of produce, rejecting items like green tomatoes. These devices can be used directly on harvesters in the field or in processing plants.

With advancements in Artificial Intelligence (AI) and Machine Learning (ML), these machines are becoming more sophisticated. They can use ML models trained to differentiate between fruit and foreign objects such as rocks, dirt, or insects. These models can also assess fruit quality, identifying not just bruised fruit but also early signs of disease or other crop issues.

> 🎓 The term *ML model* refers to the result of training machine learning software on a dataset. For instance, you can train an ML model to distinguish between ripe and unripe tomatoes, and then use the model on new images to determine whether the tomatoes are ripe.

In these 4 lessons, you’ll learn how to train image-based AI models to evaluate fruit quality, how to use these models on an IoT device, and how to run them on the edge—that is, directly on an IoT device rather than in the cloud.

> 💁 These lessons will use some cloud resources. If you don’t complete all the lessons in this project, make sure you [clean up your project](../clean-up.md).

## Topics

1. [Train a fruit quality detector](./lessons/1-train-fruit-detector/README.md)  
1. [Check fruit quality from an IoT device](./lessons/2-check-fruit-from-device/README.md)  
1. [Run your fruit detector on the edge](./lessons/3-run-fruit-detector-edge/README.md)  
1. [Trigger fruit quality detection from a sensor](./lessons/4-trigger-fruit-detector/README.md)  

## Credits

All the lessons were written with ♥️ by [Jen Fox](https://github.com/jenfoxbot) and [Jim Bennett](https://GitHub.com/JimBobBennett)  

---

**Disclaimer**:  
This document has been translated using the AI translation service [Co-op Translator](https://github.com/Azure/co-op-translator). While we aim for accuracy, please note that automated translations may include errors or inaccuracies. The original document in its native language should be regarded as the authoritative source. For critical information, professional human translation is advised. We are not responsible for any misunderstandings or misinterpretations resulting from the use of this translation.