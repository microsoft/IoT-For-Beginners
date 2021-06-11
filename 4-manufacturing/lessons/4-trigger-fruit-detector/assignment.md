# Build a fruit quality detector

## Instructions

Build the fruit quality detector!

Take everything you have learned so far and build the prototype fruit quality detector. Trigger image classification based off proximity using an AI model running on the edge, store the results of the classification in storage, and control an LED based off the ripeness of the fruit.

You should be able to piece this together using code you have previously written in all the lessons so far.

## Rubric

| Criteria | Exemplary | Adequate | Needs Improvement |
| -------- | --------- | -------- | ----------------- |
| Configure all the services | Was able to set up an IoT Hub, Azure functions application and Azure storage | Was able to set up the IoT Hub, but not either the Azure functions app or Azure storage | Was unable to set up any internet IoT services |
| Monitor proximity and send the data to IoT Hub if an object is closer than a pre-defined distance and trigger the camera via a command | Was able to measure distance and send a message to an IoT Hub when an object is close enough, and have a command send to trigger the camera | Was able to measure proximity and send to IoT Hub, but unable to get a command sent to the camera | Was unable to measure distance and send a message to IoT Hub, or trigger a command  |
| Capture an image, classify it and send the results to IoT Hub | Was able to capture an image, classify it using an edge device and send the results to IoT Hub | Was able to classify the image but not using an edge device, or was unable to send the results to IoT Hub | Was unable to classify an image |
| Turn the LED on or off depending on the results of the classification using a command sent to a device | Was able to turn an LED on via a command if the fruit was unripe | Was able to send the command to the device but not control the LED | Was unable to send a command to control the LED |
