# Recognize speech with an IoT device

Add a sketchnote if possible/appropriate

![Embed a video here if available](video-url)

## Pre-lecture quiz

[Pre-lecture quiz](https://brave-island-0b7c7f50f.azurestaticapps.net/quiz/33)

## Introduction

'Alexa, set a 12 minute timer'

'Alexa, timer status'

'Alexa set a 8 minute timer called steam broccoli'

Smart devices are becoming more and more pervasive. Not just as smart speakers like HomePods, Echos and Google Homes, but embedded in our phones, watches, and even light fittings and thermostats. I have at least 19 devices in my home that have voice assistants, and that's just the ones I know about!

Voice control increases accessibility allowing folks with limited movement to interact with devices. Whether it is a permanent disability such as being born without arms, to temporary disabilities such as broken arms, or having your hands full of shopping or young children, being able to control our houses from our voice instead of our hands opens up a world of access. Shouting 'Hey Siri, close my garage door' whilst dealing with a baby change and an unruly toddler can be a small but effective improvement on life.

One of the more popular uses for voice assistants is setting timers, especially kitchen timers. Being able to set multiple timers with just your voice is a great help in the kitchen - no need to stop kneading dough, stirring soup, or clean dumpling filling off your hands to use a physical timer.

In this lesson you will learn about building voice recognition into IoT devices. You'll learn about microphones as sensors, how to capture audio from a microphone attached to an IoT device, and how to use AI to convert what is heard into text. Throughout the rest of this project you will build a smart kitchen timer, able to set timers using your voice multiple languages.

In this lesson we'll cover:

* [Microphones](#microphones)
* [Capture audio from your IoT device](#capture-audio-from-your-iot-device)
* [Speech to text](#speech-to-text)
* [Privacy](#privacy)
* [Convert speech to text](#convert-speech-to-text)

## Microphones

## Capture audio from your IoT device

Your IoT device can be connected to a microphone to capture audio, ready for conversion to text. It can also be connected to speakers to output audio. In later lessons this will be used to give audio feedback, but it is useful to set up speakers now to test the microphone.

### Task - configure your microphone and speakers

Work through the relevant guide to configure the microphone and speakers for your IoT device:

* [Arduino - Wio Terminal](wio-terminal-microphone.md)
* [Single-board computer - Raspberry Pi](pi-microphone.md)
* [Single-board computer - Virtual device](virtual-device-microphone.md)

### Task - capture audio

Work through the relevant guide to capture audio on your IoT device:

* [Arduino - Wio Terminal](wio-terminal-audio.md)
* [Single-board computer - Raspberry Pi](pi-audio.md)
* [Single-board computer - Virtual device](virtual-device-audio.md)

## Speech to text




## Privacy



Wake words. TinyML. Not a button - just to make it easier.




## Convert speech to text

Just like with image classification in the last project, there are pre-built AI services that can take speech as an audio file and convert it to text. Once such service is the Speech Service, part of the Cognitive Services, pre-built AI services you can use in your apps.

### Task - configure a speech AI resource

1. Create a Resource Group for this project called `smart-timer`

1. Use the following command to create a free speech resource:

    ```sh
    az cognitiveservices account create --name smart-timer \
                                        --resource-group smart-timer \
                                        --kind SpeechServices \
                                        --sku F0 \
                                        --yes \
                                        --location <location>
    ```

    Replace `<location>` with the location you used when creating the Resource Group.

1. You will need an API key to access the speech resource from your code. Run the following command to get the key:

    ```sh
    az cognitiveservices account keys list --name smart-timer \
                                           --resource-group smart-timer \
                                           --output table
    ```

    Take a copy of one of the keys.

### Task - convert speech to text

Work through the relevant guide to convert speech to text on your IoT device:

* [Arduino - Wio Terminal](wio-terminal-speech-to-text.md)
* [Single-board computer - Raspberry Pi](pi-speech-to-text.md)
* [Single-board computer - Virtual device](virtual-device-speech-to-text.md)

### Task - send converted speech to an IoT services

To use the results of the speech to text conversion, you need to send it to the cloud. There it will be interpreted and responses sent back to the IoT device as commands.

1. Create a new IoT Hub in the `smart-timer` resource group, and register a new device called `smart-timer`.

1. Connect your IoT device to this IoT Hub using what you have learned in previous lessons, and send the speech as telemetry. Use a JSON document in this format:

    ```json
    {
        "speech" : "<converted speech>"
    }
    ```

    Where `<converted speech>` is the output from the speech to text call.

1. Verify that messages are being sent by monitoring the Event Hub compatible endpoint using the `az iot hub monitor-events` command.

---

## 🚀 Challenge

## Post-lecture quiz

[Post-lecture quiz](https://brave-island-0b7c7f50f.azurestaticapps.net/quiz/34)

## Review & Self Study

* Read more on the Cognitive Services speech service on the [Speech service documentation on Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/?WT.mc_id=academic-17441-jabenn)
* Read about keyword spotting on the [Keyword recognition documentation on Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/keyword-recognition-overview?WT.mc_id=academic-17441-jabenn)

## Assignment

[](assignment.md)
