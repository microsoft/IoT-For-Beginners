<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "022e21f8629b721424c1de25195fff67",
  "translation_date": "2025-08-28T19:12:37+00:00",
  "source_file": "4-manufacturing/lessons/2-check-fruit-from-device/assignment.md",
  "language_code": "en"
}
-->
# Respond to classification results

## Instructions

Your device has classified images and has prediction values. Your device can use this information to take action—for example, it could send the data to an IoT Hub for processing by other systems, or it could control an actuator, such as lighting up an LED when the fruit is unripe.

Add code to your device to respond in a way of your choice—either send data to an IoT Hub, control an actuator, or combine both approaches. For instance, you could send data to an IoT Hub along with some serverless code that determines whether the fruit is ripe or not and sends back a command to control an actuator.

## Rubric

| Criteria | Exemplary | Adequate | Needs Improvement |
| -------- | --------- | -------- | ----------------- |
| Respond to predictions | Successfully implemented a response to predictions that consistently works with predictions of the same value. | Implemented a response that is not dependent on the predictions, such as simply sending raw data to an IoT Hub. | Was unable to program the device to respond to the predictions. |

---

**Disclaimer**:  
This document has been translated using the AI translation service [Co-op Translator](https://github.com/Azure/co-op-translator). While we aim for accuracy, please note that automated translations may include errors or inaccuracies. The original document in its native language should be regarded as the authoritative source. For critical information, professional human translation is advised. We are not responsible for any misunderstandings or misinterpretations resulting from the use of this translation.