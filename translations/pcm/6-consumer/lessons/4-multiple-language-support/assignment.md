<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "701f4a4466f9309b6e1d863077df0c06",
  "translation_date": "2025-11-18T19:21:53+00:00",
  "source_file": "6-consumer/lessons/4-multiple-language-support/assignment.md",
  "language_code": "pcm"
}
-->
# Build universal translator

## Instructions

Universal translator na device wey fit translate between plenty languages, so people wey dey speak different languages fit communicate. Use wetin you don learn for di past few lessons to build universal translator wey go use 2 IoT devices.

> If you no get 2 devices, follow di steps for di previous lessons to set up virtual IoT device as one of di IoT devices.

You go configure one device for one language, and di other one for another language. Each device go collect speech, change am to text, send am go di other device through IoT Hub and Functions app, then translate am and play di translated speech.

> 💁 Tip: When you dey send di speech from one device go di other one, send di language wey e dey inside too, e go make di translation easier. You fit even make each device register with IoT Hub and Functions app first, pass di language wey dem support make e store for Azure Storage. You fit use Functions app to do di translations, send di translated text go di IoT device.

## Rubric

| Criteria | Exemplary | Adequate | Needs Improvement |
| -------- | --------- | -------- | ----------------- |
| Create universal translator | Fit build universal translator, change speech wey one device detect to speech wey di other device play for different language | Fit make some parts work, like capture speech or translate, but no fit build di full solution | No fit build any part of di universal translator |

---

<!-- CO-OP TRANSLATOR DISCLAIMER START -->
**Disclaimer**:  
Dis dokyument don use AI translation service [Co-op Translator](https://github.com/Azure/co-op-translator) do di translation. Even as we dey try make am correct, abeg sabi say machine translation fit get mistake or no dey accurate well. Di original dokyument for im native language na di main correct source. For important information, e good make professional human translation dey use. We no go fit take blame for any misunderstanding or wrong interpretation wey fit happen because of dis translation.
<!-- CO-OP TRANSLATOR DISCLAIMER END -->