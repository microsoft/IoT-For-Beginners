<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "7966848a1f870e4c42edb4db67b13c57",
  "translation_date": "2025-08-27T21:08:07+00:00",
  "source_file": "6-consumer/lessons/3-spoken-feedback/virtual-device-text-to-speech.md",
  "language_code": "hu"
}
-->
# Szöveg beszéddé alakítása - Virtuális IoT eszköz

Ebben a leckében kódot fogsz írni, amely a szöveget beszéddé alakítja a beszédszolgáltatás segítségével.

## Szöveg beszéddé alakítása

Az előző leckében használt beszédszolgáltatások SDK, amely a beszédet szöveggé alakította, arra is használható, hogy a szöveget visszaalakítsa beszéddé. A beszéd kéréséhez meg kell adnod a hangot, amelyet használni szeretnél, mivel a beszéd különböző hangokkal generálható.

Minden nyelvhez különböző hangok állnak rendelkezésre, és a beszédszolgáltatások SDK segítségével lekérheted az adott nyelvhez támogatott hangok listáját.

### Feladat - szöveg beszéddé alakítása

1. Nyisd meg a `smart-timer` projektet a VS Code-ban, és győződj meg róla, hogy a virtuális környezet betöltődött a terminálban.

1. Importáld a `SpeechSynthesizer`-t az `azure.cognitiveservices.speech` csomagból az alábbi módon, hozzáadva a meglévő importokhoz:

    ```python
    from azure.cognitiveservices.speech import SpeechConfig, SpeechRecognizer, SpeechSynthesizer
    ```

1. A `say` függvény fölött hozz létre egy beszédkonfigurációt, amelyet a beszédszintetizátor használni fog:

    ```python
    speech_config = SpeechConfig(subscription=speech_api_key,
                                 region=location)
    speech_config.speech_synthesis_language = language
    speech_synthesizer = SpeechSynthesizer(speech_config=speech_config)
    ```

    Ez ugyanazt az API kulcsot, helyet és nyelvet használja, amelyet a felismerő is használt.

1. Ezután add hozzá az alábbi kódot, hogy lekérj egy hangot, és beállítsd azt a beszédkonfigurációban:

    ```python
    voices = speech_synthesizer.get_voices_async().get().voices
    first_voice = next(x for x in voices if x.locale.lower() == language.lower())
    speech_config.speech_synthesis_voice_name = first_voice.short_name
    ```

    Ez lekéri az összes elérhető hang listáját, majd megkeresi az első hangot, amely megfelel a használt nyelvnek.

    > 💁 A támogatott hangok teljes listáját megtalálhatod a [Microsoft Docs nyelv- és hangtámogatási dokumentációjában](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#text-to-speech). Ha egy konkrét hangot szeretnél használni, akkor eltávolíthatod ezt a funkciót, és a dokumentációban található hangnévvel hardcode-olhatod a hangot. Például:
    >
    > ```python
    > speech_config.speech_synthesis_voice_name = 'hi-IN-SwaraNeural'
    > ```

1. Frissítsd a `say` függvény tartalmát, hogy SSML-t generáljon a válaszhoz:

    ```python
    ssml =  f'<speak version=\'1.0\' xml:lang=\'{language}\'>'
    ssml += f'<voice xml:lang=\'{language}\' name=\'{first_voice.short_name}\'>'
    ssml += text
    ssml += '</voice>'
    ssml += '</speak>'
    ```

1. Ezután állítsd le a beszédfelismerést, mondasd el az SSML-t, majd indítsd újra a felismerést:

    ```python
    recognizer.stop_continuous_recognition()
    speech_synthesizer.speak_ssml(ssml)
    recognizer.start_continuous_recognition()
    ```

    A felismerés leállításra kerül, amíg a szöveg elhangzik, hogy elkerüljük, hogy a visszaszámláló indításának bejelentése felismerésre kerüljön, elküldésre kerüljön a LUIS-nek, és esetleg új visszaszámláló beállításaként értelmeződjön.

    > 💁 Ezt kipróbálhatod úgy, hogy kikommentezed a felismerés leállítására és újraindítására vonatkozó sorokat. Állíts be egy visszaszámlálót, és lehet, hogy azt tapasztalod, hogy a bejelentés új visszaszámlálót állít be, ami új bejelentést okoz, ami új visszaszámlálót eredményez, és így tovább végtelenül!

1. Futtasd az alkalmazást, és győződj meg róla, hogy a funkcióalkalmazás is fut. Állíts be néhány visszaszámlálót, és hallani fogsz egy beszélt választ, amely közli, hogy a visszaszámláló beállításra került, majd egy másik beszélt választ, amikor a visszaszámláló lejár.

> 💁 Ezt a kódot megtalálhatod a [code-spoken-response/virtual-iot-device](../../../../../6-consumer/lessons/3-spoken-feedback/code-spoken-response/virtual-iot-device) mappában.

😀 A visszaszámláló programod sikeres volt!

---

**Felelősség kizárása**:  
Ez a dokumentum az AI fordítási szolgáltatás, a [Co-op Translator](https://github.com/Azure/co-op-translator) segítségével lett lefordítva. Bár törekszünk a pontosságra, kérjük, vegye figyelembe, hogy az automatikus fordítások hibákat vagy pontatlanságokat tartalmazhatnak. Az eredeti dokumentum az eredeti nyelvén tekintendő hiteles forrásnak. Kritikus információk esetén javasolt professzionális emberi fordítást igénybe venni. Nem vállalunk felelősséget semmilyen félreértésért vagy téves értelmezésért, amely a fordítás használatából eredhet.