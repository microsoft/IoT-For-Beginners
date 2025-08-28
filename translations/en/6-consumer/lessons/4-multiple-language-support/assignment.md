<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "701f4a4466f9309b6e1d863077df0c06",
  "translation_date": "2025-08-28T19:34:14+00:00",
  "source_file": "6-consumer/lessons/4-multiple-language-support/assignment.md",
  "language_code": "en"
}
-->
# Build a universal translator

## Instructions

A universal translator is a device that can translate between multiple languages, allowing people who speak different languages to communicate. Use what you have learned over the past few lessons to create a universal translator using two IoT devices.

> If you do not have two devices, follow the steps in the previous lessons to set up a virtual IoT device as one of the IoT devices.

You should configure one device for one language and the other for another language. Each device should capture speech, convert it to text, send it to the other device via IoT Hub and a Functions app, then translate it and play the translated speech.

> 💁 Tip: When sending speech from one device to another, include the language it is in as well, making it easier to translate. You could even have each device register with IoT Hub and a Functions app first, passing the language they support to be stored in Azure Storage. Then, you could use a Functions app to handle the translations, sending the translated text back to the IoT device.

## Rubric

| Criteria | Exemplary | Adequate | Needs Improvement |
| -------- | --------- | -------- | ----------------- |
| Create a universal translator | Successfully built a universal translator that converts speech detected by one device into speech played by another device in a different language | Managed to get some components working, such as capturing speech or translating, but was unable to complete the end-to-end solution | Unable to create any functional parts of a universal translator |

---

**Disclaimer**:  
This document has been translated using the AI translation service [Co-op Translator](https://github.com/Azure/co-op-translator). While we aim for accuracy, please note that automated translations may include errors or inaccuracies. The original document in its native language should be regarded as the authoritative source. For critical information, professional human translation is advised. We are not responsible for any misunderstandings or misinterpretations resulting from the use of this translation.