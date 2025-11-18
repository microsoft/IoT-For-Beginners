<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "ed0fbd6aed084bfba7d5e2f206968c50",
  "translation_date": "2025-11-18T19:49:03+00:00",
  "source_file": "2-farm/lessons/3-automated-plant-watering/assignment.md",
  "language_code": "pcm"
}
-->
# Make Watering System Work Better

## Wetin You Go Do

Dis lesson show how you fit take control relay wit sensor data, and di relay fit control pump wey go dey water farm. For one soil wey dem don measure, if pump dey run for fixed time, e go always affect di soil moisture di same way. Dis mean say you fit sabi how many seconds of water wey go match one kind drop for soil moisture reading. Wit dis data, you fit build one better irrigation system.

For dis assignment, you go calculate how long di pump go run to make soil moisture rise reach di level wey you want.

> ⚠️ If you dey use virtual IoT hardware, you fit follow dis process, but you go dey simulate di result by manually dey increase di soil moisture reading by fixed amount every second wey di relay dey on.

1. Start wit dry soil. Measure di soil moisture.

1. Add fixed amount of water, either by running di pump for 1 second or by pouring fixed amount of water.

    > Di pump suppose dey run for constant rate, so every second wey di pump dey run, e go dey supply di same amount of water.

1. Wait make di soil moisture level balance, then take di reading.

1. Repeat dis process many times and make table for di results. Example of di table dey below.

    | Total Pump time | Soil Moisture | Decrease |
    | --- | --: | -: |
    | Dry | 643 |  0 |
    | 1s  | 621 | 22 |
    | 2s  | 601 | 20 |
    | 3s  | 579 | 22 |
    | 4s  | 560 | 19 |
    | 5s  | 539 | 21 |
    | 6s  | 521 | 18 |

1. Calculate di average increase for soil moisture per second of water. For di example above, every second of water dey reduce di reading by average of 20.3.

1. Use dis data to make di server code work better, make di pump dey run for di time wey go make soil moisture reach di level wey you need.

## How Dem Go Mark Am

| Criteria | Better Work | Okay Work | E Need Better Work |
| -------- | --------- | -------- | ----------------- |
| Capture soil moisture data | Fit capture many readings after adding fixed amount of water | Fit capture some readings wit fixed amount of water | Fit only capture one or two readings, or no fit use fixed amount of water |
| Adjust di server code | Fit calculate average decrease for soil moisture reading and update di server code to use am | Fit calculate average decrease, but no fit update di server code, or no fit calculate di average well, but use di value to update di server code well | No fit calculate di average, or no fit update di server code |

---

<!-- CO-OP TRANSLATOR DISCLAIMER START -->
**Disclaimer**:  
Dis dokyument don use AI transle-shon service [Co-op Translator](https://github.com/Azure/co-op-translator) do di transle-shon. Even as we dey try make am accurate, abeg make you sabi say transle-shon wey machine do fit get mistake or no dey correct well. Di original dokyument for di language wey dem write am first na di one wey you go take as di correct one. For important mata, e good make you use professional human transle-shon. We no go fit take blame for any misunderstanding or wrong interpretation wey fit happen because you use dis transle-shon.
<!-- CO-OP TRANSLATOR DISCLAIMER END -->