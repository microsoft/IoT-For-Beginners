<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "606f3af1c78e3741e48ce77c31cea626",
  "translation_date": "2025-08-27T21:13:26+00:00",
  "source_file": "6-consumer/lessons/3-spoken-feedback/pi-text-to-speech.md",
  "language_code": "cs"
}
-->
# Převod textu na řeč - Raspberry Pi

V této části lekce napíšete kód pro převod textu na řeč pomocí služby pro převod řeči.

## Převod textu na řeč pomocí služby pro převod řeči

Text lze odeslat do služby pro převod řeči pomocí REST API, aby se získal zvukový soubor, který lze přehrát na vašem IoT zařízení. Při požadavku na převod řeči je nutné určit hlas, který se má použít, protože řeč může být generována pomocí různých hlasů.

Každý jazyk podporuje různé hlasy a můžete provést REST požadavek na službu pro převod řeči, abyste získali seznam podporovaných hlasů pro každý jazyk.

### Úkol - získání hlasu

1. Otevřete projekt `smart-timer` ve VS Code.

1. Přidejte následující kód nad funkci `say`, abyste získali seznam hlasů pro daný jazyk:

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

    Tento kód definuje funkci nazvanou `get_voice`, která využívá službu pro převod řeči k získání seznamu hlasů. Poté najde první hlas, který odpovídá používanému jazyku.

    Tato funkce je následně volána k uložení prvního hlasu a název hlasu je vytištěn do konzole. Tento hlas lze požadovat jednou a jeho hodnota se použije při každém volání pro převod textu na řeč.

    > 💁 Kompletní seznam podporovaných hlasů najdete v [dokumentaci o podpoře jazyků a hlasů na Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#text-to-speech). Pokud chcete použít konkrétní hlas, můžete tuto funkci odstranit a pevně nastavit hlas na název hlasu z této dokumentace. Například:
    >
    > ```python
    > voice = 'hi-IN-SwaraNeural'
    > ```

### Úkol - převod textu na řeč

1. Pod tímto kódem definujte konstantu pro formát zvuku, který má být získán ze služby pro převod řeči. Při požadavku na zvuk můžete použít různé formáty.

    ```python
    playback_format = 'riff-48khz-16bit-mono-pcm'
    ```

    Formát, který můžete použít, závisí na vašem hardwaru. Pokud při přehrávání zvuku dostanete chyby `Invalid sample rate`, změňte tuto hodnotu na jinou. Seznam podporovaných hodnot najdete v [dokumentaci REST API pro převod textu na řeč na Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/rest-text-to-speech?WT.mc_id=academic-17441-jabenn#audio-outputs). Budete muset použít zvuk ve formátu `riff` a hodnoty, které můžete vyzkoušet, jsou `riff-16khz-16bit-mono-pcm`, `riff-24khz-16bit-mono-pcm` a `riff-48khz-16bit-mono-pcm`.

1. Pod tímto kódem deklarujte funkci nazvanou `get_speech`, která převede text na řeč pomocí REST API služby pro převod řeči:

    ```python
    def get_speech(text):
    ```

1. Ve funkci `get_speech` definujte URL, které se má volat, a hlavičky, které se mají předat:

    ```python
        url = f'https://{location}.tts.speech.microsoft.com/cognitiveservices/v1'
    
        headers = {
            'Authorization': 'Bearer ' + get_access_token(),
            'Content-Type': 'application/ssml+xml',
            'X-Microsoft-OutputFormat': playback_format
        }
    ```

    Tím se nastaví hlavičky pro použití vygenerovaného přístupového tokenu, obsah se nastaví na SSML a definuje se požadovaný formát zvuku.

1. Pod tímto kódem definujte SSML, které se má odeslat do REST API:

    ```python
    ssml =  f'<speak version=\'1.0\' xml:lang=\'{language}\'>'
    ssml += f'<voice xml:lang=\'{language}\' name=\'{voice}\'>'
    ssml += text
    ssml += '</voice>'
    ssml += '</speak>'
    ```

    Toto SSML nastavuje jazyk a hlas, který se má použít, spolu s textem, který se má převést.

1. Nakonec přidejte kód do této funkce, který provede REST požadavek a vrátí binární zvuková data:

    ```python
    response = requests.post(url, headers=headers, data=ssml.encode('utf-8'))
    return io.BytesIO(response.content)
    ```

### Úkol - přehrání zvuku

1. Pod funkcí `get_speech` definujte novou funkci pro přehrání zvuku vráceného voláním REST API:

    ```python
    def play_speech(speech):
    ```

1. Parametr `speech` předaný této funkci bude binární zvuková data vrácená z REST API. Použijte následující kód k otevření tohoto souboru jako zvukového souboru a jeho předání PyAudio pro přehrání zvuku:

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

    Tento kód používá PyAudio stream, stejně jako při zachytávání zvuku. Rozdíl je v tom, že stream je nastaven jako výstupní stream a data jsou čtena ze zvukových dat a posílána do streamu.

    Místo pevného nastavení detailů streamu, jako je vzorkovací frekvence, jsou tyto informace čteny ze zvukových dat.

1. Nahraďte obsah funkce `say` následujícím kódem:

    ```python
    speech = get_speech(text)
    play_speech(speech)
    ```

    Tento kód převede text na řeč jako binární zvuková data a přehraje zvuk.

1. Spusťte aplikaci a ujistěte se, že funkční aplikace také běží. Nastavte několik časovačů a uslyšíte hlasovou odpověď, která oznámí, že váš časovač byl nastaven, a poté další hlasovou odpověď, když časovač skončí.

    Pokud dostanete chyby `Invalid sample rate`, změňte `playback_format`, jak bylo popsáno výše.

> 💁 Tento kód najdete ve složce [code-spoken-response/pi](../../../../../6-consumer/lessons/3-spoken-feedback/code-spoken-response/pi).

😀 Váš program časovače byl úspěšný!

---

**Prohlášení**:  
Tento dokument byl přeložen pomocí služby AI pro překlady [Co-op Translator](https://github.com/Azure/co-op-translator). Ačkoli se snažíme o přesnost, mějte prosím na paměti, že automatizované překlady mohou obsahovat chyby nebo nepřesnosti. Původní dokument v jeho původním jazyce by měl být považován za autoritativní zdroj. Pro důležité informace se doporučuje profesionální lidský překlad. Neodpovídáme za žádná nedorozumění nebo nesprávné interpretace vyplývající z použití tohoto překladu.