# Set a timer and provide spoken feedback

Add a sketchnote if possible/appropriate

![Embed a video here if available](video-url)

## Pre-lecture quiz

[Pre-lecture quiz](https://brave-island-0b7c7f50f.azurestaticapps.net/quiz/45)

## Introduction

Smart assistants are not one-way communication devices. You speak to them, and they respond:

"Alexa, set a 3 minute timer"

"Ok, your timer is set for 3 minutes"

In the last 2 lessons you learned how to take speech and create text, then extract a set timer request from that text. In this lesson you will learn how to set the timer on the IoT device, responding to the user with spoken words confirming their timer, and alerting them when their timer is finished.

In this lesson we'll cover:

* [Text to speech](#text-to-speech)
* [Set the timer](#set-the-timer)
* [Convert text to speech](#convert-text-to-speech)

## Text to speech

## Set the timer

The timer can be set by sending a command from the serverless code, instructing the IoT device to set the timer. This command will contain the time in seconds till the timer needs to go off.

### Task - set the timer using a command

1. In your serverless code, add code to send a direct method request to your IoT device

    > ⚠️ You can refer to [the instructions for sending direct method requests in lesson 5 of the farm project if needed](../../../2-farm/lessons/5-migrate-application-to-the-cloud/README.md#send-direct-method-requests-from-serverless-code).

    You will need to set up the connection string for the IoT Hub with the service policy (*NOT* the device) in your `local.settings.json` file and add the `azure-iot-hub` pip package to your `requirements.txt` file. The device ID can be extracted from the event.

1. The direct method you send needs to be called `set-timer`, and will need to send the length of the timer as a JSON property called `time`. Use the following code to build the `CloudToDeviceMethod` using the `total_time` calculated from the data extracted by LUIS:

    ```python
    payload = {
        'time': total_time
    }
    direct_method = CloudToDeviceMethod(method_name='set-timer', payload=json.dumps(payload))
    ```

> 💁 You can find this code in the [code-command/functions](code-command/functions) folder.

### Task - respond to the command on the IoT device

1. On your IoT device, respond to the command.

    > ⚠️ You can refer to [the instructions for handling direct method requests from IoT devices in lesson 4 of the farm project if needed](../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud#task---connect-your-iot-device-to-the-cloud).

1. Work through the relevant guide to set a timer for the required time:

* [Arduino - Wio Terminal](wio-terminal-set-timer.md)
* [Single-board computer - Raspberry Pi/Virtual IoT device](single-board-computer-set-timer.md)

> 💁 You can find this code in the [code-command/wio-terminal](code-command/wio-terminal), [code-command/virtual-device](code-command/virtual-device), or [code-command/pi](code-command/pi) folder.

## Convert text to speech

The same speech service you used to convert speech to text can be used to convert text back into speech, and this can be played through a microphone on your IoT device.

### Task - convert text to speech

Work through the relevant guide to convert text to speech using your IoT device:

* [Arduino - Wio Terminal](wio-terminal-text-to-speech.md)
* [Single-board computer - Raspberry Pi](pi-text-to-speech.md)
* [Single-board computer - Virtual device](virtual-device-text-to-speech.md)

---

## 🚀 Challenge

## Post-lecture quiz

[Post-lecture quiz](https://brave-island-0b7c7f50f.azurestaticapps.net/quiz/46)

## Review & Self Study

## Assignment

[](assignment.md)
