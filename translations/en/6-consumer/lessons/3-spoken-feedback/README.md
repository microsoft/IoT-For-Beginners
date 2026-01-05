<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "b73fe10ec6b580fba2affb6f6e0a5c4d",
  "translation_date": "2025-08-28T19:17:58+00:00",
  "source_file": "6-consumer/lessons/3-spoken-feedback/README.md",
  "language_code": "en"
}
-->
# Set a timer and provide spoken feedback

![A sketchnote overview of this lesson](../../../../../translated_images/lesson-23.f38483e1d4df4828990d3f02d60e46c978b075d384ae7cb4f7bab738e107c850.en.jpg)

> Sketchnote by [Nitya Narasimhan](https://github.com/nitya). Click the image for a larger version.

## Pre-lecture quiz

[Pre-lecture quiz](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/45)

## Introduction

Smart assistants are not just devices for one-way communication. You talk to them, and they respond:

"Alexa, set a 3-minute timer."

"Ok, your timer is set for 3 minutes."

In the last two lessons, you learned how to convert speech into text and extract a timer request from that text. In this lesson, you’ll learn how to set the timer on an IoT device, respond to the user with spoken confirmation, and notify them when the timer is complete.

In this lesson, we’ll cover:

* [Text to speech](../../../../../6-consumer/lessons/3-spoken-feedback)
* [Set the timer](../../../../../6-consumer/lessons/3-spoken-feedback)
* [Convert text to speech](../../../../../6-consumer/lessons/3-spoken-feedback)

## Text to speech

Text to speech, as the name suggests, is the process of turning text into audio that represents spoken words. The basic idea is to break the text into its individual sounds (called phonemes) and then create audio for those sounds, either using pre-recorded clips or AI-generated audio.

![The three stages of typical text to speech systems](../../../../../translated_images/tts-overview.193843cf3f5ee09f.en.png)

Text to speech systems generally have three stages:

* Text analysis
* Linguistic analysis
* Waveform generation

### Text analysis

Text analysis involves taking the provided text and converting it into words that can be used to generate speech. For example, if you convert "Hello world," no text analysis is needed because the two words can be directly converted to speech. However, if you have "1234," it might need to be converted into "One thousand, two hundred thirty-four" or "One, two, three, four," depending on the context. For "I have 1234 apples," it would be "One thousand, two hundred thirty-four," but for "The child counted 1234," it would be "One, two, three, four."

The way words are created varies not only by language but also by the locale of that language. For instance, in American English, 120 is "One hundred twenty," while in British English, it’s "One hundred and twenty," with the inclusion of "and" after the hundreds.

✅ Other examples requiring text analysis include abbreviations like "in" for inch and "st" for saint or street. Can you think of similar examples in your language where words are ambiguous without context?

Once the words are defined, they are sent for linguistic analysis.

### Linguistic analysis

Linguistic analysis breaks the words into phonemes. Phonemes depend not only on the letters but also on their placement in the word. For example, in English, the 'a' sound in "car" and "care" is different. The English language has 44 phonemes for its 26 letters, with some phonemes shared by different letters, such as the same sound at the start of "circle" and "serpent."

✅ Research task: What are the phonemes in your language?

After converting words into phonemes, additional data is added to adjust intonation, tone, or duration based on context. For example, in English, raising the pitch at the end of a sentence can turn it into a question.

For instance, the sentence "You have an apple" is a statement. But if the pitch rises at the end, it becomes "You have an apple?"—a question. Linguistic analysis uses punctuation like question marks to determine pitch changes.

Once phonemes are generated, they are sent to the waveform generation stage to produce audio.

### Waveform generation

Early electronic text-to-speech systems used single audio recordings for each phoneme, resulting in robotic, monotonous voices. The phonemes from linguistic analysis were matched to pre-recorded sounds and stitched together to create audio.

✅ Research task: Find audio samples from early speech synthesis systems. Compare them to modern systems like those used in smart assistants.

Modern waveform generation uses machine learning models, particularly deep learning (large neural networks that mimic brain neurons), to create more natural-sounding voices that can be indistinguishable from human speech.

> 💁 Some ML models can be fine-tuned using transfer learning to mimic real people’s voices. This makes voice-based security systems, like those used by banks, less reliable since someone with a few minutes of your voice recording could impersonate you.

These advanced ML models are being trained to combine all three steps into end-to-end speech synthesizers.

## Set the timer

To set the timer, your IoT device needs to call the REST endpoint you created using serverless code. It will then use the returned number of seconds to set the timer.

### Task - call the serverless function to get the timer time

Follow the relevant guide to call the REST endpoint from your IoT device and set a timer for the required duration:

* [Arduino - Wio Terminal](wio-terminal-set-timer.md)
* [Single-board computer - Raspberry Pi/Virtual IoT device](single-board-computer-set-timer.md)

## Convert text to speech

The same speech service you used to convert speech to text can also convert text back into speech. This audio can then be played through a speaker on your IoT device. The text is sent to the speech service along with specifications like audio type (e.g., sample rate), and the service returns binary audio data.

When making this request, you use *Speech Synthesis Markup Language* (SSML), an XML-based language for speech synthesis. SSML defines the text to convert, the language, the voice to use, and even parameters like speed, volume, and pitch for specific words.

For example, this SSML converts the text "Your 3-minute 5-second timer has been set" into speech using a British English voice called `en-GB-MiaNeural`:

```xml
<speak version='1.0' xml:lang='en-GB'>
    <voice xml:lang='en-GB' name='en-GB-MiaNeural'>
        Your 3 minute 5 second time has been set
    </voice>
</speak>
```

> 💁 Most text-to-speech systems offer multiple voices for different languages, including accents like British English or New Zealand English.

### Task - convert text to speech

Follow the relevant guide to convert text to speech using your IoT device:

* [Arduino - Wio Terminal](wio-terminal-text-to-speech.md)
* [Single-board computer - Raspberry Pi](pi-text-to-speech.md)
* [Single-board computer - Virtual device](virtual-device-text-to-speech.md)

---

## 🚀 Challenge

SSML allows you to modify how words are spoken, such as emphasizing certain words, adding pauses, or changing pitch. Experiment with these features by sending different SSML from your IoT device and comparing the results. Learn more about SSML in the [Speech Synthesis Markup Language (SSML) Version 1.1 specification from the World Wide Web Consortium](https://www.w3.org/TR/speech-synthesis11/).

## Post-lecture quiz

[Post-lecture quiz](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/46)

## Review & Self Study

* Read more about speech synthesis on the [speech synthesis page on Wikipedia](https://wikipedia.org/wiki/Speech_synthesis).
* Learn how criminals use speech synthesis to commit fraud in the [fake voices 'help cyber crooks steal cash' article on BBC News](https://www.bbc.com/news/technology-48908736).
* Explore the risks to voice actors from AI-generated voices in the [TikTok lawsuit highlights how AI is impacting voice actors article on Vice](https://www.vice.com/en/article/z3xqwj/this-tiktok-lawsuit-is-highlighting-how-ai-is-screwing-over-voice-actors).

## Assignment

[Cancel the timer](assignment.md)

---

**Disclaimer**:  
This document has been translated using the AI translation service [Co-op Translator](https://github.com/Azure/co-op-translator). While we aim for accuracy, please note that automated translations may include errors or inaccuracies. The original document in its native language should be regarded as the authoritative source. For critical information, professional human translation is advised. We are not responsible for any misunderstandings or misinterpretations resulting from the use of this translation.