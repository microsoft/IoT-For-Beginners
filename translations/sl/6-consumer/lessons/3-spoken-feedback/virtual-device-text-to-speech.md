<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "7966848a1f870e4c42edb4db67b13c57",
  "translation_date": "2025-08-28T12:40:20+00:00",
  "source_file": "6-consumer/lessons/3-spoken-feedback/virtual-device-text-to-speech.md",
  "language_code": "sl"
}
-->
# Pretvorba besedila v govor - Virtualna IoT naprava

V tem delu lekcije boste napisali kodo za pretvorbo besedila v govor z uporabo storitve za govor.

## Pretvorba besedila v govor

SDK za storitve govora, ki ste ga uporabili v prejšnji lekciji za pretvorbo govora v besedilo, lahko uporabite tudi za pretvorbo besedila nazaj v govor. Pri zahtevi za govor morate določiti glas, ki ga želite uporabiti, saj je govor mogoče ustvariti z različnimi glasovi.

Vsak jezik podpira različne glasove, seznam podprtih glasov za posamezen jezik pa lahko pridobite iz SDK za storitve govora.

### Naloga - pretvorba besedila v govor

1. Odprite projekt `smart-timer` v VS Code in se prepričajte, da je virtualno okolje naloženo v terminalu.

1. Uvozite `SpeechSynthesizer` iz paketa `azure.cognitiveservices.speech` tako, da ga dodate obstoječim uvozom:

    ```python
    from azure.cognitiveservices.speech import SpeechConfig, SpeechRecognizer, SpeechSynthesizer
    ```

1. Nad funkcijo `say` ustvarite konfiguracijo za govor, ki jo boste uporabili s sintetizatorjem govora:

    ```python
    speech_config = SpeechConfig(subscription=speech_api_key,
                                 region=location)
    speech_config.speech_synthesis_language = language
    speech_synthesizer = SpeechSynthesizer(speech_config=speech_config)
    ```

    To uporablja isti API ključ, lokacijo in jezik, ki jih je uporabljal prepoznavalnik.

1. Pod to dodajte naslednjo kodo za pridobitev glasu in nastavitev na konfiguracijo govora:

    ```python
    voices = speech_synthesizer.get_voices_async().get().voices
    first_voice = next(x for x in voices if x.locale.lower() == language.lower())
    speech_config.speech_synthesis_voice_name = first_voice.short_name
    ```

    Ta koda pridobi seznam vseh razpoložljivih glasov in nato poišče prvi glas, ki ustreza jeziku, ki se uporablja.

    > 💁 Celoten seznam podprtih glasov lahko najdete v [dokumentaciji o podpori za jezike in glasove na Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#text-to-speech). Če želite uporabiti določen glas, lahko to funkcijo odstranite in ročno nastavite glas z imenom glasu iz te dokumentacije. Na primer:
    >
    > ```python
    > speech_config.speech_synthesis_voice_name = 'hi-IN-SwaraNeural'
    > ```

1. Posodobite vsebino funkcije `say`, da generira SSML za odgovor:

    ```python
    ssml =  f'<speak version=\'1.0\' xml:lang=\'{language}\'>'
    ssml += f'<voice xml:lang=\'{language}\' name=\'{first_voice.short_name}\'>'
    ssml += text
    ssml += '</voice>'
    ssml += '</speak>'
    ```

1. Pod tem ustavite prepoznavanje govora, predvajajte SSML in nato ponovno zaženite prepoznavanje:

    ```python
    recognizer.stop_continuous_recognition()
    speech_synthesizer.speak_ssml(ssml)
    recognizer.start_continuous_recognition()
    ```

    Prepoznavanje je ustavljeno, medtem ko se besedilo predvaja, da se prepreči, da bi bila napoved začetka časovnika zaznana, poslana v LUIS in morda interpretirana kot zahteva za nastavitev novega časovnika.

    > 💁 To lahko preizkusite tako, da zakomentirate vrstice za ustavitev in ponovni zagon prepoznavanja. Nastavite en časovnik in morda boste ugotovili, da napoved nastavi nov časovnik, kar povzroči novo napoved, ki vodi do novega časovnika, in tako naprej v neskončnost!

1. Zaženite aplikacijo in se prepričajte, da funkcijska aplikacija prav tako deluje. Nastavite nekaj časovnikov in slišali boste glasovni odgovor, ki pravi, da je vaš časovnik nastavljen, nato pa še en glasovni odgovor, ko je časovnik zaključen.

> 💁 To kodo lahko najdete v mapi [code-spoken-response/virtual-iot-device](../../../../../6-consumer/lessons/3-spoken-feedback/code-spoken-response/virtual-iot-device).

😀 Vaš program za časovnik je bil uspešen!

---

**Omejitev odgovornosti**:  
Ta dokument je bil preveden z uporabo storitve za prevajanje z umetno inteligenco [Co-op Translator](https://github.com/Azure/co-op-translator). Čeprav si prizadevamo za natančnost, vas prosimo, da upoštevate, da lahko avtomatizirani prevodi vsebujejo napake ali netočnosti. Izvirni dokument v njegovem maternem jeziku je treba obravnavati kot avtoritativni vir. Za ključne informacije priporočamo profesionalni človeški prevod. Ne prevzemamo odgovornosti za morebitna napačna razumevanja ali napačne interpretacije, ki bi nastale zaradi uporabe tega prevoda.