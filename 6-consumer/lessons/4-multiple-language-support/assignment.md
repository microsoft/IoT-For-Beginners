# Build a universal translator

## Instructions

A universal translator is a device that can translate between multiple languages, allowing folks who speak different languages to be able to communicate. Use what you have learned over the past few lessons to build a universal translator using 2 IoT devices.

> If you do not have 2 devices, follow the steps in the previous few lessons to set up a virtual IoT device as one of the IoT devices.

You should configure one device for one language, and one for another. Each device should accept speech, convert it to text, send it to the other device via IoT Hub and a Functions app, then translate it and play the translated speech.

> 💁 Tip: When sending the speech from one device to another, send the language it is in as well, making it easer to translate. You could even have each device register using IoT Hub and a Functions app first, passing the language they support to be stored in Azure Storage. You could then use a Functions app to do the translations, sending the translated text to the IoT device.

## Rubric

| Criteria | Exemplary | Adequate | Needs Improvement |
| -------- | --------- | -------- | ----------------- |
| Create a universal translator | Was able to build a universal translator, converting speech detected by one device into speech played by another device in a different language | Was able to get some components working, such as capturing speech, or translating, but was unable to build the end to end solution | Was unable to build any parts of a working universal translator |
