<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "7966848a1f870e4c42edb4db67b13c57",
  "translation_date": "2025-08-27T21:07:54+00:00",
  "source_file": "6-consumer/lessons/3-spoken-feedback/virtual-device-text-to-speech.md",
  "language_code": "sw"
}
-->
# Kusoma Maandishi kwa Sauti - Kifaa Pepe cha IoT

Katika sehemu hii ya somo, utaandika msimbo wa kubadilisha maandishi kuwa sauti kwa kutumia huduma ya sauti.

## Kubadilisha maandishi kuwa sauti

SDK ya huduma za sauti uliyotumia katika somo lililopita kubadilisha sauti kuwa maandishi inaweza pia kutumika kubadilisha maandishi kuwa sauti. Unapohitaji sauti, unapaswa kutoa sauti itakayotumika, kwani sauti inaweza kuzalishwa kwa kutumia sauti mbalimbali.

Kila lugha ina sauti tofauti zinazopatikana, na unaweza kupata orodha ya sauti zinazoungwa mkono kwa kila lugha kutoka kwenye SDK ya huduma za sauti.

### Kazi - Badilisha maandishi kuwa sauti

1. Fungua mradi wa `smart-timer` kwenye VS Code, na hakikisha mazingira pepe yamewashwa kwenye terminali.

1. Leta `SpeechSynthesizer` kutoka kwenye kifurushi cha `azure.cognitiveservices.speech` kwa kuongeza kwenye uingizaji uliopo:

    ```python
    from azure.cognitiveservices.speech import SpeechConfig, SpeechRecognizer, SpeechSynthesizer
    ```

1. Juu ya kazi ya `say`, tengeneza usanidi wa sauti wa kutumia na speech synthesizer:

    ```python
    speech_config = SpeechConfig(subscription=speech_api_key,
                                 region=location)
    speech_config.speech_synthesis_language = language
    speech_synthesizer = SpeechSynthesizer(speech_config=speech_config)
    ```

    Hii inatumia API key, eneo, na lugha sawa na ile iliyotumiwa na recognizer.

1. Chini ya hapo, ongeza msimbo ufuatao ili kupata sauti na kuiweka kwenye speech config:

    ```python
    voices = speech_synthesizer.get_voices_async().get().voices
    first_voice = next(x for x in voices if x.locale.lower() == language.lower())
    speech_config.speech_synthesis_voice_name = first_voice.short_name
    ```

    Hii inachukua orodha ya sauti zote zinazopatikana, kisha inatafuta sauti ya kwanza inayolingana na lugha inayotumika.

    > 💁 Unaweza kupata orodha kamili ya sauti zinazoungwa mkono kutoka kwenye [Nyaraka za msaada wa lugha na sauti kwenye Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#text-to-speech). Ikiwa unataka kutumia sauti maalum, basi unaweza kuondoa kazi hii na kuweka jina la sauti moja kwa moja kutoka kwenye nyaraka hizi. Kwa mfano:
    >
    > ```python
    > speech_config.speech_synthesis_voice_name = 'hi-IN-SwaraNeural'
    > ```

1. Sasisha yaliyomo kwenye kazi ya `say` ili kuzalisha SSML kwa jibu:

    ```python
    ssml =  f'<speak version=\'1.0\' xml:lang=\'{language}\'>'
    ssml += f'<voice xml:lang=\'{language}\' name=\'{first_voice.short_name}\'>'
    ssml += text
    ssml += '</voice>'
    ssml += '</speak>'
    ```

1. Chini ya hapo, simamisha utambuzi wa sauti, ongea SSML, kisha anza tena utambuzi:

    ```python
    recognizer.stop_continuous_recognition()
    speech_synthesizer.speak_ssml(ssml)
    recognizer.start_continuous_recognition()
    ```

    Utambuzi unasimamishwa wakati maandishi yanazungumzwa ili kuepuka tangazo la kuanza kwa kipima muda kugunduliwa, kutumwa kwa LUIS, na labda kufasiriwa kama ombi la kuweka kipima muda kipya.

    > 💁 Unaweza kujaribu hili kwa kutoa maoni kwenye mistari ya kusimamisha na kuanzisha tena utambuzi. Weka kipima muda kimoja, na unaweza kugundua kuwa tangazo linaweka kipima muda kipya, ambacho husababisha tangazo jipya, na hivyo kuendelea milele!

1. Endesha programu, na hakikisha programu ya kazi pia inaendelea. Weka vipima muda, na utasikia jibu la sauti likisema kuwa kipima muda chako kimewekwa, kisha jibu lingine la sauti wakati kipima muda kinapokamilika.

> 💁 Unaweza kupata msimbo huu kwenye folda ya [code-spoken-response/virtual-iot-device](../../../../../6-consumer/lessons/3-spoken-feedback/code-spoken-response/virtual-iot-device).

😀 Programu yako ya kipima muda imefanikiwa!

---

**Kanusho**:  
Hati hii imetafsiriwa kwa kutumia huduma ya tafsiri ya AI [Co-op Translator](https://github.com/Azure/co-op-translator). Ingawa tunajitahidi kuhakikisha usahihi, tafsiri za kiotomatiki zinaweza kuwa na makosa au kutokuwa sahihi. Hati ya asili katika lugha yake ya awali inapaswa kuchukuliwa kama chanzo cha mamlaka. Kwa taarifa muhimu, tafsiri ya kitaalamu ya binadamu inapendekezwa. Hatutawajibika kwa kutoelewana au tafsiri zisizo sahihi zinazotokana na matumizi ya tafsiri hii.