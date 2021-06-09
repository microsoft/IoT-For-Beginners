# Build a more efficient watering cycle

## Instructions

This lesson covered how to control a relay via sensor data, and that relay could in turn control a pump for an irrigation system. For a defined body of soil, running a pump for a fixed length of time should always have the same impact on the soil moisture. This means you can get an idea of how many seconds of irrigation correspond to a certain drop in soil moisture reading. Using this data you can build a more controlled irrigation system.

For this assignment you will calculate how long the pump should run for a particular rise in soil moisture.

> ⚠️ If you are using virtual IoT hardware, you can work through this process, but simulate the results by increasing the soil moisture reading manually by a fixed amount per second the relay is on.

1. Start with dry soil. Measure the soil moisture.

1. Add a fixed amount of water, either by running the pump for 1 second or by pouring a fixed amount in.

    > The pump should always run at a constant rate, so every second the pump runs it should supply the same amount of water.

1. Wait until the soil moisture level stabilizes and take a reading.

1. Repeat this multiple times and create a table of the results. An example of this table is given below.

    | Total Pump time | Soil Moisture | Decrease |
    | --- | --: | -: |
    | Dry | 643 |  0 |
    | 1s  | 621 | 22 |
    | 2s  | 601 | 20 |
    | 3s  | 579 | 22 |
    | 4s  | 560 | 19 |
    | 5s  | 539 | 21 |
    | 6s  | 521 | 18 |

1. Work out an average increase in soil moisture per second of water. In the example above, each second of water decreases the reading by an average of 20.3.

1. Use this data to improve the efficiency of your server code, running the pump for the required time to get the soil moisture to the level needed.

## Rubric

| Criteria | Exemplary | Adequate | Needs Improvement |
| -------- | --------- | -------- | ----------------- |
| Capture soil moisture date | Is able to capture multiple readings after adding fixed quantities of water | Is able to capture some readings with fixed quantities of water | Can only capture one or two readings, or is unable to use fixed quantities of water |
| Calibrate the server code | Is able to calculate an average decrease in soil moisture reading and update the server code to use this | Is able to calculate an average decrease, but cannot update the server code, or is unable to correctly calculate an average, but uses this value to correctly update the server code | Is unable to calculate an average, or update the server code |
