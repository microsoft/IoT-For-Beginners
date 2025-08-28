<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "606f3af1c78e3741e48ce77c31cea626",
  "translation_date": "2025-08-28T09:02:51+00:00",
  "source_file": "6-consumer/lessons/3-spoken-feedback/pi-text-to-speech.md",
  "language_code": "sk"
}
-->
# Text na reč - Raspberry Pi

V tejto časti lekcie napíšete kód na konverziu textu na reč pomocou služby reči.

## Konverzia textu na reč pomocou služby reči

Text môže byť odoslaný do služby reči pomocou REST API, aby sa získala reč vo forme zvukového súboru, ktorý je možné prehrať na vašom IoT zariadení. Pri požiadavke na reč je potrebné zadať hlas, ktorý sa má použiť, pretože reč môže byť generovaná pomocou rôznych hlasov.

Každý jazyk podporuje rôzne hlasy a môžete vykonať REST požiadavku na službu reči, aby ste získali zoznam podporovaných hlasov pre každý jazyk.

### Úloha - získanie hlasu

1. Otvorte projekt `smart-timer` vo VS Code.

1. Pridajte nasledujúci kód nad funkciu `say`, aby ste požiadali o zoznam hlasov pre jazyk:

    ```python
    def get_voice():
        url = f'https://{location}.tts.speech.microsoft.com/cognitiveservices/voices/list'
    
        headers = {
            'Authorization': 'Bearer ' + get_access_token()
        }
    
        response = requests.get(url, headers=headers)
        voices_json = json.loads(response.text)
    
        first_voice = next(x for x in voices_json if x['Locale'].lower() == language.lower() and x['VoiceType'] == 'Neural')
        return first_voice['ShortName']
    
    voice = get_voice()
    print(f'Using voice {voice}')
    ```

    Tento kód definuje funkciu nazvanú `get_voice`, ktorá používa službu reči na získanie zoznamu hlasov. Následne nájde prvý hlas, ktorý zodpovedá používanému jazyku.

    Táto funkcia je potom volaná na uloženie prvého hlasu a názov hlasu je vytlačený do konzoly. Tento hlas môže byť požadovaný raz a jeho hodnota použitá pri každom volaní na konverziu textu na reč.

    > 💁 Kompletný zoznam podporovaných hlasov môžete získať z [dokumentácie o podpore jazykov a hlasov na Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#text-to-speech). Ak chcete použiť konkrétny hlas, môžete túto funkciu odstrániť a pevne zadať hlas podľa názvu hlasu z tejto dokumentácie. Napríklad:
    >
    > ```python
    > voice = 'hi-IN-SwaraNeural'
    > ```

### Úloha - konverzia textu na reč

1. Pod týmto definujte konštantu pre formát zvuku, ktorý sa má získať zo služby reči. Pri požiadavke na zvuk môžete použiť rôzne formáty.

    ```python
    playback_format = 'riff-48khz-16bit-mono-pcm'
    ```

    Formát, ktorý môžete použiť, závisí od vášho hardvéru. Ak dostanete chyby `Invalid sample rate` pri prehrávaní zvuku, zmeňte to na inú hodnotu. Zoznam podporovaných hodnôt nájdete v [dokumentácii REST API pre text na reč na Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/rest-text-to-speech?WT.mc_id=academic-17441-jabenn#audio-outputs). Budete musieť použiť zvuk vo formáte `riff` a hodnoty, ktoré môžete vyskúšať, sú `riff-16khz-16bit-mono-pcm`, `riff-24khz-16bit-mono-pcm` a `riff-48khz-16bit-mono-pcm`.

1. Pod týmto deklarujte funkciu nazvanú `get_speech`, ktorá bude konvertovať text na reč pomocou REST API služby reči:

    ```python
    def get_speech(text):
    ```

1. Vo funkcii `get_speech` definujte URL na volanie a hlavičky na odoslanie:

    ```python
        url = f'https://{location}.tts.speech.microsoft.com/cognitiveservices/v1'
    
        headers = {
            'Authorization': 'Bearer ' + get_access_token(),
            'Content-Type': 'application/ssml+xml',
            'X-Microsoft-OutputFormat': playback_format
        }
    ```

    Toto nastaví hlavičky na použitie generovaného prístupového tokenu, nastaví obsah na SSML a definuje potrebný formát zvuku.

1. Pod týmto definujte SSML na odoslanie do REST API:

    ```python
    ssml =  f'<speak version=\'1.0\' xml:lang=\'{language}\'>'
    ssml += f'<voice xml:lang=\'{language}\' name=\'{voice}\'>'
    ssml += text
    ssml += '</voice>'
    ssml += '</speak>'
    ```

    Tento SSML nastaví jazyk a hlas, ktorý sa má použiť, spolu s textom na konverziu.

1. Nakoniec pridajte kód do tejto funkcie na vykonanie REST požiadavky a vrátenie binárnych zvukových dát:

    ```python
    response = requests.post(url, headers=headers, data=ssml.encode('utf-8'))
    return io.BytesIO(response.content)
    ```

### Úloha - prehrávanie zvuku

1. Pod funkciou `get_speech` definujte novú funkciu na prehrávanie zvuku vráteného z REST API volania:

    ```python
    def play_speech(speech):
    ```

1. Parameter `speech` odovzdaný do tejto funkcie bude binárny zvukový údaj vrátený z REST API. Použite nasledujúci kód na otvorenie tohto ako wave súboru a jeho odovzdanie do PyAudio na prehrávanie zvuku:

    ```python
    def play_speech(speech):
        with wave.open(speech, 'rb') as wave_file:
            stream = audio.open(format=audio.get_format_from_width(wave_file.getsampwidth()),
                                channels=wave_file.getnchannels(),
                                rate=wave_file.getframerate(),
                                output_device_index=speaker_card_number,
                                output=True)

            data = wave_file.readframes(4096)

            while len(data) > 0:
                stream.write(data)
                data = wave_file.readframes(4096)

            stream.stop_stream()
            stream.close()
    ```

    Tento kód používa PyAudio stream, rovnako ako pri zachytávaní zvuku. Rozdiel je v tom, že stream je nastavený ako výstupný stream a údaje sú čítané zo zvukových dát a posúvané do streamu.

    Namiesto pevného nastavenia detailov streamu, ako je vzorkovacia frekvencia, sú tieto údaje čítané zo zvukových dát.

1. Nahraďte obsah funkcie `say` nasledujúcim:

    ```python
    speech = get_speech(text)
    play_speech(speech)
    ```

    Tento kód konvertuje text na reč ako binárne zvukové údaje a prehráva zvuk.

1. Spustite aplikáciu a uistite sa, že funkčná aplikácia tiež beží. Nastavte niekoľko časovačov a budete počuť hovorenú odpoveď, ktorá oznámi, že váš časovač bol nastavený, a potom ďalšiu hovorenú odpoveď, keď časovač skončí.

    Ak dostanete chyby `Invalid sample rate`, zmeňte `playback_format` podľa vyššie uvedeného popisu.

> 💁 Tento kód nájdete v priečinku [code-spoken-response/pi](../../../../../6-consumer/lessons/3-spoken-feedback/code-spoken-response/pi).

😀 Váš program časovača bol úspešný!

---

**Upozornenie**:  
Tento dokument bol preložený pomocou služby na automatický preklad [Co-op Translator](https://github.com/Azure/co-op-translator). Aj keď sa snažíme o presnosť, upozorňujeme, že automatické preklady môžu obsahovať chyby alebo nepresnosti. Pôvodný dokument v jeho pôvodnom jazyku by mal byť považovaný za autoritatívny zdroj. Pre dôležité informácie sa odporúča profesionálny ľudský preklad. Nezodpovedáme za akékoľvek nedorozumenia alebo nesprávne interpretácie vyplývajúce z použitia tohto prekladu.