<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "7966848a1f870e4c42edb4db67b13c57",
  "translation_date": "2025-08-28T19:17:40+00:00",
  "source_file": "6-consumer/lessons/3-spoken-feedback/virtual-device-text-to-speech.md",
  "language_code": "lt"
}
-->
# Teksto į kalbą - Virtualus IoT įrenginys

Šioje pamokos dalyje rašysite kodą, kuris konvertuos tekstą į kalbą, naudodamas kalbos paslaugą.

## Konvertuoti tekstą į kalbą

Kalbos paslaugų SDK, kurį naudojote ankstesnėje pamokoje tekstui konvertuoti į kalbą, taip pat gali būti naudojamas tekstui konvertuoti atgal į kalbą. Prašant kalbos, reikia nurodyti balsą, kuris bus naudojamas, nes kalba gali būti generuojama naudojant įvairius balsus.

Kiekviena kalba palaiko įvairius balsus, o kalbos paslaugų SDK galite gauti sąrašą balsų, palaikomų kiekvienai kalbai.

### Užduotis - konvertuoti tekstą į kalbą

1. Atidarykite `smart-timer` projektą VS Code ir įsitikinkite, kad terminale įkeltas virtualus aplinkos nustatymas.

1. Importuokite `SpeechSynthesizer` iš `azure.cognitiveservices.speech` paketo, pridėdami jį prie esamų importų:

    ```python
    from azure.cognitiveservices.speech import SpeechConfig, SpeechRecognizer, SpeechSynthesizer
    ```

1. Virš `say` funkcijos sukurkite kalbos konfigūraciją, kuri bus naudojama su kalbos sintezatoriumi:

    ```python
    speech_config = SpeechConfig(subscription=speech_api_key,
                                 region=location)
    speech_config.speech_synthesis_language = language
    speech_synthesizer = SpeechSynthesizer(speech_config=speech_config)
    ```

    Tai naudoja tą patį API raktą, vietą ir kalbą, kurie buvo naudojami atpažinimo įrankyje.

1. Po to pridėkite šį kodą, kad gautumėte balsą ir nustatytumėte jį kalbos konfigūracijoje:

    ```python
    voices = speech_synthesizer.get_voices_async().get().voices
    first_voice = next(x for x in voices if x.locale.lower() == language.lower())
    speech_config.speech_synthesis_voice_name = first_voice.short_name
    ```

    Šis kodas gauna visų galimų balsų sąrašą, tada suranda pirmą balsą, kuris atitinka naudojamą kalbą.

    > 💁 Visą palaikomų balsų sąrašą galite rasti [Microsoft Docs kalbų ir balsų palaikymo dokumentacijoje](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#text-to-speech). Jei norite naudoti konkretų balsą, galite pašalinti šią funkciją ir tiesiogiai nurodyti balsą pagal šios dokumentacijos balsų pavadinimą. Pavyzdžiui:
    >
    > ```python
    > speech_config.speech_synthesis_voice_name = 'hi-IN-SwaraNeural'
    > ```

1. Atnaujinkite `say` funkcijos turinį, kad sugeneruotumėte SSML atsakymui:

    ```python
    ssml =  f'<speak version=\'1.0\' xml:lang=\'{language}\'>'
    ssml += f'<voice xml:lang=\'{language}\' name=\'{first_voice.short_name}\'>'
    ssml += text
    ssml += '</voice>'
    ssml += '</speak>'
    ```

1. Po to sustabdykite kalbos atpažinimą, perskaitykite SSML, tada vėl paleiskite atpažinimą:

    ```python
    recognizer.stop_continuous_recognition()
    speech_synthesizer.speak_ssml(ssml)
    recognizer.start_continuous_recognition()
    ```

    Atpažinimas sustabdomas, kol tekstas yra skaitomas, kad būtų išvengta situacijos, kai laikmačio paleidimo pranešimas yra atpažįstamas, siunčiamas į LUIS ir galimai interpretuojamas kaip naujo laikmačio nustatymo užklausa.

    > 💁 Galite tai išbandyti, iškomentuodami eilutes, kurios sustabdo ir vėl paleidžia atpažinimą. Nustatykite vieną laikmatį, ir galite pastebėti, kad pranešimas nustato naują laikmatį, kuris sukelia naują pranešimą, vedantį į naują laikmatį, ir taip be galo!

1. Paleiskite programą ir įsitikinkite, kad funkcijų programa taip pat veikia. Nustatykite kelis laikmačius, ir išgirsite balsu sakomą atsakymą, kad jūsų laikmatis buvo nustatytas, o vėliau kitą atsakymą, kai laikmatis baigsis.

> 💁 Šį kodą galite rasti [code-spoken-response/virtual-iot-device](../../../../../6-consumer/lessons/3-spoken-feedback/code-spoken-response/virtual-iot-device) aplanke.

😀 Jūsų laikmačio programa buvo sėkminga!

---

**Atsakomybės apribojimas**:  
Šis dokumentas buvo išverstas naudojant dirbtinio intelekto vertimo paslaugą [Co-op Translator](https://github.com/Azure/co-op-translator). Nors siekiame tikslumo, atkreipiame dėmesį, kad automatiniai vertimai gali turėti klaidų ar netikslumų. Originalus dokumentas jo gimtąja kalba turėtų būti laikomas autoritetingu šaltiniu. Kritinei informacijai rekomenduojama naudoti profesionalų žmogaus vertimą. Mes neprisiimame atsakomybės už nesusipratimus ar klaidingus aiškinimus, kylančius dėl šio vertimo naudojimo.