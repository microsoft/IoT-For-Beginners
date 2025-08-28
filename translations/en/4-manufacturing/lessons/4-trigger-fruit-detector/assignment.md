<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "1a85e50c33c38dcd2cde2a97d132f248",
  "translation_date": "2025-08-28T19:03:26+00:00",
  "source_file": "4-manufacturing/lessons/4-trigger-fruit-detector/assignment.md",
  "language_code": "en"
}
-->
# Build a fruit quality detector

## Instructions

Create a fruit quality detector!

Use everything you've learned so far to build a prototype fruit quality detector. Trigger image classification based on proximity using an AI model running on the edge, store the classification results in storage, and control an LED based on the ripeness of the fruit.

You should be able to assemble this using code you've written in previous lessons.

## Rubric

| Criteria | Exemplary | Adequate | Needs Improvement |
| -------- | --------- | -------- | ----------------- |
| Configure all the services | Successfully set up an IoT Hub, Azure Functions application, and Azure Storage | Successfully set up the IoT Hub, but not the Azure Functions app or Azure Storage | Unable to set up any IoT services |
| Monitor proximity and send the data to IoT Hub if an object is closer than a pre-defined distance and trigger the camera via a command | Successfully measured distance, sent a message to IoT Hub when an object was close enough, and sent a command to trigger the camera | Successfully measured proximity and sent data to IoT Hub, but unable to send a command to the camera | Unable to measure distance, send a message to IoT Hub, or trigger a command |
| Capture an image, classify it, and send the results to IoT Hub | Successfully captured an image, classified it using an edge device, and sent the results to IoT Hub | Successfully classified the image but not using an edge device, or unable to send the results to IoT Hub | Unable to classify an image |
| Turn the LED on or off depending on the results of the classification using a command sent to a device | Successfully turned an LED on via a command if the fruit was unripe | Successfully sent the command to the device but unable to control the LED | Unable to send a command to control the LED |

---

**Disclaimer**:  
This document has been translated using the AI translation service [Co-op Translator](https://github.com/Azure/co-op-translator). While we aim for accuracy, please note that automated translations may include errors or inaccuracies. The original document in its native language should be regarded as the authoritative source. For critical information, professional human translation is advised. We are not responsible for any misunderstandings or misinterpretations resulting from the use of this translation.