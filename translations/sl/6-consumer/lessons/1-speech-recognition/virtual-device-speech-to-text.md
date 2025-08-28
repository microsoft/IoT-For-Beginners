<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "c0550b254b9ba2539baf1e6bb5fc05f8",
  "translation_date": "2025-08-28T12:55:02+00:00",
  "source_file": "6-consumer/lessons/1-speech-recognition/virtual-device-speech-to-text.md",
  "language_code": "sl"
}
-->
# Pretvorba govora v besedilo - Virtualna IoT naprava

V tem delu lekcije boste napisali kodo za pretvorbo govora, zajetega z vašim mikrofonom, v besedilo z uporabo storitve za prepoznavanje govora.

## Pretvorba govora v besedilo

Na Windows, Linux in macOS lahko Python SDK za storitve prepoznavanja govora uporabite za poslušanje vašega mikrofona in pretvorbo zaznanega govora v besedilo. SDK bo neprekinjeno poslušal, zaznaval ravni zvoka in pošiljal govor v pretvorbo v besedilo, ko se raven zvoka zniža, na primer ob koncu bloka govora.

### Naloga - pretvorba govora v besedilo

1. Ustvarite novo Python aplikacijo na vašem računalniku v mapi z imenom `smart-timer` z eno datoteko, imenovano `app.py`, in Python virtualnim okoljem.

1. Namestite Pip paket za storitve prepoznavanja govora. Prepričajte se, da to nameščate iz terminala z aktiviranim virtualnim okoljem.

    ```sh
    pip install azure-cognitiveservices-speech
    ```

    > ⚠️ Če dobite naslednjo napako:
    >
    > ```output
    > ERROR: Could not find a version that satisfies the requirement azure-cognitiveservices-speech (from versions: none)
    > ERROR: No matching distribution found for azure-cognitiveservices-speech
    > ```
    >
    > Morate posodobiti Pip. To storite z naslednjim ukazom, nato poskusite znova namestiti paket.
    >
    > ```sh
    > pip install --upgrade pip
    > ```

1. Dodajte naslednje uvoze v datoteko `app.py`:

    ```python
    import requests
    import time
    from azure.cognitiveservices.speech import SpeechConfig, SpeechRecognizer
    ```

    To uvozi nekaj razredov, ki se uporabljajo za prepoznavanje govora.

1. Dodajte naslednjo kodo za deklaracijo konfiguracije:

    ```python
    speech_api_key = '<key>'
    location = '<location>'
    language = '<language>'

    recognizer_config = SpeechConfig(subscription=speech_api_key,
                                     region=location,
                                     speech_recognition_language=language)
    ```

    Zamenjajte `<key>` z API ključem za vašo storitev prepoznavanja govora. Zamenjajte `<location>` z lokacijo, ki ste jo uporabili ob ustvarjanju vira storitve prepoznavanja govora.

    Zamenjajte `<language>` z imenom lokalizacije jezika, v katerem boste govorili, na primer `en-GB` za angleščino ali `zn-HK` za kantonščino. Seznam podprtih jezikov in njihovih lokalizacijskih imen najdete v [dokumentaciji o podpori za jezike in glasove na Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text).

    Ta konfiguracija se nato uporabi za ustvarjanje objekta `SpeechConfig`, ki bo uporabljen za konfiguracijo storitev prepoznavanja govora.

1. Dodajte naslednjo kodo za ustvarjanje prepoznavalnika govora:

    ```python
    recognizer = SpeechRecognizer(speech_config=recognizer_config)
    ```

1. Prepoznavalnik govora deluje na ozadju, posluša zvok in pretvarja zaznan govor v besedilo. Besedilo lahko pridobite z uporabo funkcije povratnega klica - funkcije, ki jo definirate in posredujete prepoznavalniku. Vsakič, ko je zaznan govor, se funkcija povratnega klica pokliče. Dodajte naslednjo kodo za definiranje funkcije povratnega klica, jo posredujte prepoznavalniku ter definirajte funkcijo za obdelavo besedila, ki ga izpiše v konzolo:

    ```python
    def process_text(text):
        print(text)

    def recognized(args):
        process_text(args.result.text)
    
    recognizer.recognized.connect(recognized)
    ```

1. Prepoznavalnik začne poslušati šele, ko ga izrecno zaženete. Dodajte naslednjo kodo za začetek prepoznavanja. To se izvaja v ozadju, zato bo vaša aplikacija potrebovala tudi neskončno zanko, ki spi, da aplikacija ostane aktivna.

    ```python
    recognizer.start_continuous_recognition()

    while True:
        time.sleep(1)
    ```

1. Zaženite to aplikacijo. Govorite v mikrofon in avdio, pretvorjen v besedilo, bo izpisan v konzoli.

    ```output
    (.venv) ➜  smart-timer python3 app.py
    Hello world.
    Welcome to IoT for beginners.
    ```

    Poskusite različne vrste stavkov, skupaj s stavki, kjer besede zvenijo enako, vendar imajo različne pomene. Na primer, če govorite v angleščini, recite 'I want to buy two bananas and an apple too' in opazite, kako bo uporabil pravilne to, two in too glede na kontekst besede, ne le njen zvok.

> 💁 To kodo lahko najdete v mapi [code-speech-to-text/virtual-iot-device](../../../../../6-consumer/lessons/1-speech-recognition/code-speech-to-text/virtual-iot-device).

😀 Vaš program za pretvorbo govora v besedilo je bil uspešen!

---

**Omejitev odgovornosti**:  
Ta dokument je bil preveden z uporabo storitve za prevajanje z umetno inteligenco [Co-op Translator](https://github.com/Azure/co-op-translator). Čeprav si prizadevamo za natančnost, vas prosimo, da upoštevate, da lahko avtomatizirani prevodi vsebujejo napake ali netočnosti. Izvirni dokument v njegovem maternem jeziku je treba obravnavati kot avtoritativni vir. Za ključne informacije priporočamo profesionalni človeški prevod. Ne odgovarjamo za morebitna nesporazumevanja ali napačne razlage, ki bi nastale zaradi uporabe tega prevoda.