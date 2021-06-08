# Respond to classification results

## Instructions

Your device has classified images, and has the values for the predictions. Your device could use this information to do something - it could sent it to IoT Hub for processing by other systems, or it could control an actuator such as an LED to light up when the fruit is unripe.

Add code to your device to respond in a way of your choosing - either send data to an IoT Hub, control an actuator, or combine the two and send data to an IoT Hub with some serverless code that determines if the fruit is ripe or not and sends back a command to control an actuator.

## Rubric

| Criteria | Exemplary | Adequate | Needs Improvement |
| -------- | --------- | -------- | ----------------- |
| Respond to predictions | Was able to implement a response to predictions that works consistently with predictions of the same value. | Was able to implement a response that is not dependant on the predictions, such as just sending raw data to an IoT Hub | Was unable to program the device to respond to the predictions |
