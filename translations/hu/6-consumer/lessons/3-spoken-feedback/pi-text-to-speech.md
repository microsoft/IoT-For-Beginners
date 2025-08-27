<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "606f3af1c78e3741e48ce77c31cea626",
  "translation_date": "2025-08-27T21:13:08+00:00",
  "source_file": "6-consumer/lessons/3-spoken-feedback/pi-text-to-speech.md",
  "language_code": "hu"
}
-->
# Szöveg beszéddé alakítása - Raspberry Pi

Ebben a leckében kódot fogsz írni, amely a szöveget beszéddé alakítja a beszédszolgáltatás segítségével.

## Szöveg beszéddé alakítása a beszédszolgáltatás használatával

A szöveget a REST API segítségével lehet elküldeni a beszédszolgáltatásnak, hogy hangfájlként visszakapjuk, amelyet lejátszhatunk az IoT eszközünkön. A beszéd kéréséhez meg kell adni a hangot, amelyet használni szeretnénk, mivel a beszéd különböző hangokkal generálható.

Minden nyelvhez különböző hangok állnak rendelkezésre, és REST kérést küldhetünk a beszédszolgáltatásnak, hogy megkapjuk az adott nyelvhez támogatott hangok listáját.

### Feladat - hang kiválasztása

1. Nyisd meg a `smart-timer` projektet a VS Code-ban.

1. Add hozzá az alábbi kódot a `say` függvény fölé, hogy lekérd egy nyelv hangjainak listáját:

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

    Ez a kód egy `get_voice` nevű függvényt definiál, amely a beszédszolgáltatást használja a hangok listájának lekérésére. Ezután megkeresi az első hangot, amely megfelel az aktuálisan használt nyelvnek.

    Ez a függvény meghívásra kerül, hogy elmentse az első hangot, és a hang neve kiírásra kerül a konzolra. Ezt a hangot egyszer kérhetjük le, és az értéket minden szöveg beszéddé alakítási hívásnál használhatjuk.

    > 💁 A támogatott hangok teljes listáját megtalálhatod a [Microsoft Docs nyelv- és hangtámogatási dokumentációjában](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#text-to-speech). Ha egy konkrét hangot szeretnél használni, akkor eltávolíthatod ezt a függvényt, és a dokumentációból származó hangnevet hard code-olhatod. Például:
    >
    > ```python
    > voice = 'hi-IN-SwaraNeural'
    > ```

### Feladat - szöveg beszéddé alakítása

1. Ezután definiálj egy konstansot az audio formátumhoz, amelyet a beszédszolgáltatástól szeretnél lekérni. Az audio különböző formátumokban kérhető.

    ```python
    playback_format = 'riff-48khz-16bit-mono-pcm'
    ```

    Az alkalmazható formátum a hardveredtől függ. Ha `Invalid sample rate` hibát kapsz az audio lejátszásakor, akkor változtasd meg ezt egy másik értékre. A támogatott értékek listáját megtalálhatod a [Text to speech REST API dokumentációjában a Microsoft Docs-on](https://docs.microsoft.com/azure/cognitive-services/speech-service/rest-text-to-speech?WT.mc_id=academic-17441-jabenn#audio-outputs). `riff` formátumú audio-t kell használnod, és az értékek, amelyeket kipróbálhatsz: `riff-16khz-16bit-mono-pcm`, `riff-24khz-16bit-mono-pcm` és `riff-48khz-16bit-mono-pcm`.

1. Ezután deklarálj egy `get_speech` nevű függvényt, amely a szöveget beszéddé alakítja a beszédszolgáltatás REST API-jának használatával:

    ```python
    def get_speech(text):
    ```

1. A `get_speech` függvényben definiáld az URL-t, amelyet hívni kell, és a fejléceket, amelyeket át kell adni:

    ```python
        url = f'https://{location}.tts.speech.microsoft.com/cognitiveservices/v1'
    
        headers = {
            'Authorization': 'Bearer ' + get_access_token(),
            'Content-Type': 'application/ssml+xml',
            'X-Microsoft-OutputFormat': playback_format
        }
    ```

    Ez beállítja a fejléceket egy generált hozzáférési token használatára, meghatározza az SSML tartalmat, és definiálja a szükséges audio formátumot.

1. Ezután definiáld az SSML-t, amelyet a REST API-nak küldesz:

    ```python
    ssml =  f'<speak version=\'1.0\' xml:lang=\'{language}\'>'
    ssml += f'<voice xml:lang=\'{language}\' name=\'{voice}\'>'
    ssml += text
    ssml += '</voice>'
    ssml += '</speak>'
    ```

    Ez az SSML beállítja a nyelvet és a hangot, amelyet használni szeretnél, valamint a szöveget, amelyet át kell alakítani.

1. Végül adj hozzá kódot ebben a függvényben, hogy végrehajtsa a REST kérést, és visszaadja a bináris audio adatokat:

    ```python
    response = requests.post(url, headers=headers, data=ssml.encode('utf-8'))
    return io.BytesIO(response.content)
    ```

### Feladat - az audio lejátszása

1. A `get_speech` függvény alatt definiálj egy új függvényt az audio lejátszására, amelyet a REST API hívás visszaadott:

    ```python
    def play_speech(speech):
    ```

1. A `speech`, amelyet ennek a függvénynek átadsz, a REST API által visszaadott bináris audio adat lesz. Használd az alábbi kódot, hogy megnyisd ezt hullámfájlként, és átadd PyAudio-nak az audio lejátszásához:

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

    Ez a kód PyAudio stream-et használ, ugyanúgy, mint az audio rögzítésnél. A különbség itt az, hogy a stream kimeneti stream-ként van beállítva, és az audio adatból olvasott adatokat továbbítja a stream-nek.

    Ahelyett, hogy a stream részleteit, például a mintavételi frekvenciát hard code-olnánk, az audio adatból olvassuk ki.

1. Cseréld ki a `say` függvény tartalmát az alábbiakra:

    ```python
    speech = get_speech(text)
    play_speech(speech)
    ```

    Ez a kód a szöveget bináris audio adatként alakítja át, és lejátsza az audio-t.

1. Futtasd az alkalmazást, és győződj meg róla, hogy a funkcióalkalmazás is fut. Állíts be néhány időzítőt, és hallani fogsz egy beszédes választ, amely közli, hogy az időzítőd beállításra került, majd egy másik beszédes választ, amikor az időzítő lejár.

    Ha `Invalid sample rate` hibát kapsz, változtasd meg a `playback_format`-ot a fent leírtak szerint.

> 💁 Ezt a kódot megtalálhatod a [code-spoken-response/pi](../../../../../6-consumer/lessons/3-spoken-feedback/code-spoken-response/pi) mappában.

😀 Az időzítő programod sikeres volt!

---

**Felelősség kizárása**:  
Ez a dokumentum az AI fordítási szolgáltatás, a [Co-op Translator](https://github.com/Azure/co-op-translator) segítségével lett lefordítva. Bár törekszünk a pontosságra, kérjük, vegye figyelembe, hogy az automatikus fordítások hibákat vagy pontatlanságokat tartalmazhatnak. Az eredeti dokumentum az eredeti nyelvén tekintendő hiteles forrásnak. Kritikus információk esetén javasolt professzionális emberi fordítást igénybe venni. Nem vállalunk felelősséget semmilyen félreértésért vagy téves értelmezésért, amely a fordítás használatából eredhet.