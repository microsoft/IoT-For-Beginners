<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "c16de27b0074abe81d6a8bad5e5b1a6b",
  "translation_date": "2025-08-28T19:30:48+00:00",
  "source_file": "6-consumer/lessons/4-multiple-language-support/README.md",
  "language_code": "en"
}
-->
# Support multiple languages

![A sketchnote overview of this lesson](../../../../../translated_images/lesson-24.4246968ed058510ab275052e87ef9aa89c7b2f938915d103c605c04dc6cd5bb7.en.jpg)

> Sketchnote by [Nitya Narasimhan](https://github.com/nitya). Click the image for a larger version.

This video provides an overview of Azure speech services, including speech-to-text and text-to-speech from previous lessons, as well as speech translation, which is the focus of this lesson:

[![Recognizing speech with a few lines of Python from Microsoft Build 2020](https://img.youtube.com/vi/h6xbpMPSGEA/0.jpg)](https://www.youtube.com/watch?v=h6xbpMPSGEA)

> 🎥 Click the image above to watch the video

## Pre-lecture quiz

[Pre-lecture quiz](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/47)

## Introduction

In the last three lessons, you explored converting speech to text, understanding language, and converting text to speech, all powered by AI. Another area of human communication where AI can assist is language translation—converting text from one language to another, such as English to French.

In this lesson, you'll learn how to use AI to translate text, enabling your smart timer to interact with users in multiple languages.

This lesson will cover:

* [Translate text](../../../../../6-consumer/lessons/4-multiple-language-support)
* [Translation services](../../../../../6-consumer/lessons/4-multiple-language-support)
* [Create a translator resource](../../../../../6-consumer/lessons/4-multiple-language-support)
* [Support multiple languages in applications with translations](../../../../../6-consumer/lessons/4-multiple-language-support)
* [Translate text using an AI service](../../../../../6-consumer/lessons/4-multiple-language-support)

> 🗑 This is the final lesson in this project. After completing this lesson and the assignment, remember to clean up your cloud services. You'll need the services to complete the assignment, so ensure you finish that first.
>
> Refer to [the clean up your project guide](../../../clean-up.md) if needed for instructions.

## Translate text

Text translation has been a computer science challenge for over 70 years. Thanks to advancements in AI and computing power, it is now approaching a level of accuracy comparable to human translators.

> 💁 The origins of translation can be traced back even further, to [Al-Kindi](https://wikipedia.org/wiki/Al-Kindi), a 9th-century Arabic cryptographer who developed techniques for language translation.

### Machine translations

Text translation began as a technology called Machine Translation (MT), which translates between different language pairs. MT works by substituting words in one language with their counterparts in another, using techniques to ensure phrases or parts of sentences are translated correctly when word-for-word substitution doesn't make sense.

> 🎓 When translators support translation between two languages, these are called *language pairs*. Different tools support different language pairs, and coverage may vary. For example, a translator might support English to Spanish and Spanish to Italian but not English to Italian.

For instance, translating "Hello world" from English to French involves substitution: "Bonjour" for "Hello" and "le monde" for "world," resulting in "Bonjour le monde."

However, substitutions fail when languages use different structures to express the same idea. For example, the English sentence "My name is Jim" translates to "Je m'appelle Jim" in French, which literally means "I call myself Jim." The word order and grammar differ significantly between the two languages.

> 💁 Some words are never translated—names, for example, remain the same across languages. When translating into languages with different alphabets or sounds, words can be *transliterated*, meaning they are adapted to sound the same as the original word.

Idioms also pose challenges for translation. These are phrases with meanings that differ from their literal interpretation. For example, the English idiom "I've got ants in my pants" means "I'm restless," not that ants are literally in your clothing. In German, the equivalent idiom is "I have bumble bees in the bottom."

> 💁 Different locales add complexity. In American English, "pants" refers to outerwear, while in British English, "pants" means underwear.

✅ If you speak multiple languages, think of some phrases that don't directly translate.

Machine translation systems rely on extensive rule databases to translate phrases and idioms, combined with statistical methods to select the best translation. These methods use large datasets of human-translated works to determine the most likely translation, a technique called *statistical machine translation*. Some systems use intermediate representations of language, translating to and from this intermediate language to simplify adding new languages.

### Neural translations

Neural translations leverage AI to translate entire sentences using a single model. These models are trained on massive datasets of human-translated content, such as web pages, books, and United Nations documents.

Neural translation models are typically smaller than machine translation models because they don't require large databases of phrases and idioms. Modern AI services often combine statistical machine translation and neural translation techniques.

There is no perfect 1:1 translation for any language pair. Different models may produce slightly different results based on their training data. Translations are not always symmetrical—translating a sentence back and forth between two languages may yield slightly different results.

✅ Try different online translators like [Bing Translate](https://www.bing.com/translator), [Google Translate](https://translate.google.com), or the Apple Translate app. Compare the translations of a few sentences. Also, try translating in one tool and translating back in another.

## Translation services

Several AI services can be integrated into applications to translate speech and text.

### Cognitive services Speech service

![The speech service logo](../../../../../translated_images/azure-speech-logo.a1f08c4befb0159f2cb5d692d3baf5b599e7b44759d316da907bda1508f46a4a.en.png)

The speech service you've used in previous lessons includes translation capabilities for speech recognition. When recognizing speech, you can request the text in the original language and other languages.

> 💁 This feature is only available through the speech SDK; the REST API does not include built-in translation.

### Cognitive services Translator service

![The translator service logo](../../../../../translated_images/azure-translator-logo.c6ed3a4a433edfd2f11577eca105412c50b8396b194cbbd730723dd1d0793bcd.en.png)

The Translator service is a dedicated translation tool that can translate text from one language to one or more target languages. It offers additional features like profanity masking and custom translations for specific terms or phrases.

For example, when translating "I have a Raspberry Pi" (referring to the single-board computer) into French, you would want to keep "Raspberry Pi" unchanged, resulting in "J’ai un Raspberry Pi" instead of "J’ai une pi aux framboises."

## Create a translator resource

For this lesson, you'll need a Translator resource. You'll use the REST API to translate text.

### Task - create a translator resource

1. From your terminal or command prompt, run the following command to create a translator resource in your `smart-timer` resource group:

    ```sh
    az cognitiveservices account create --name smart-timer-translator \
                                        --resource-group smart-timer \
                                        --kind TextTranslation \
                                        --sku F0 \
                                        --yes \
                                        --location <location>
    ```

    Replace `<location>` with the location you used when creating the Resource Group.

2. Retrieve the key for the translator service:

    ```sh
    az cognitiveservices account keys list --name smart-timer-translator \
                                           --resource-group smart-timer \
                                           --output table
    ```

    Copy one of the keys.

## Support multiple languages in applications with translations

Ideally, your application should support as many languages as possible, from speech recognition to language understanding to responding with speech. Translation services can significantly speed up development.

![A smart timer architecture translating Japanese to English, processing in English then translating back to Japanese](../../../../../translated_images/translated-smart-timer.08ac20057fdc5c37.en.png)

Imagine building a smart timer that operates entirely in English—understanding spoken English, processing it, and responding in English. To add support for Japanese, you could translate spoken Japanese to English text, process it in English, and then translate the response back to Japanese before speaking it. This approach allows you to quickly add Japanese support while planning for full end-to-end support later.

> 💁 The downside of relying on machine translation is that different languages and cultures express ideas differently, so translations may not always match expectations.

Machine translations also enable apps and devices to translate user-generated content in real time. Science fiction often features "universal translators" that convert alien languages into English. While the alien part remains fictional, real-time translation devices are already a reality.

One example is the [Microsoft Translator](https://www.microsoft.com/translator/apps/?WT.mc_id=academic-17441-jabenn) mobile app, demonstrated in this video:

[![Microsoft Translator live feature in action](https://img.youtube.com/vi/16yAGeP2FuM/0.jpg)](https://www.youtube.com/watch?v=16yAGeP2FuM)

> 🎥 Click the image above to watch the video

Imagine having such a device, especially when traveling or interacting with people who speak a different language. Automatic translation devices in airports or hospitals could greatly improve accessibility.

✅ Research: Are there any translation IoT devices commercially available? What about translation features in smart devices?

> 👽 While there are no universal translators for alien languages, the [Microsoft Translator does support Klingon](https://www.microsoft.com/translator/blog/2013/05/14/announcing-klingon-for-bing-translator/?WT.mc_id=academic-17441-jabenn). Qapla’!

## Translate text using an AI service

You can use an AI service to add translation capabilities to your smart timer.

### Task - translate text using an AI service

Follow the relevant guide to translate text on your IoT device:

* [Arduino - Wio Terminal](wio-terminal-translate-speech.md)
* [Single-board computer - Raspberry Pi](pi-translate-speech.md)
* [Single-board computer - Virtual device](virtual-device-translate-speech.md)

---

## 🚀 Challenge

How can machine translations benefit other IoT applications beyond smart devices? Think of ways translations can help, not just with spoken words but with text.

## Post-lecture quiz

[Post-lecture quiz](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/48)

## Review & Self Study

* Learn more about machine translation on the [machine translation page on Wikipedia](https://wikipedia.org/wiki/Machine_translation)
* Explore neural machine translation on the [neural machine translation page on Wikipedia](https://wikipedia.org/wiki/Neural_machine_translation)
* Check out the list of supported languages for Microsoft speech services in the [language and voice support for the Speech service documentation on Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn)

## Assignment

[Build a universal translator](assignment.md)

---

**Disclaimer**:  
This document has been translated using the AI translation service [Co-op Translator](https://github.com/Azure/co-op-translator). While we aim for accuracy, please note that automated translations may include errors or inaccuracies. The original document in its native language should be regarded as the authoritative source. For critical information, professional human translation is advised. We are not responsible for any misunderstandings or misinterpretations resulting from the use of this translation.