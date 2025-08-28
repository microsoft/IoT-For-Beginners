<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "606f3af1c78e3741e48ce77c31cea626",
  "translation_date": "2025-08-28T19:20:35+00:00",
  "source_file": "6-consumer/lessons/3-spoken-feedback/pi-text-to-speech.md",
  "language_code": "lt"
}
-->
# Teksto pavertimas garsu - Raspberry Pi

Šioje pamokos dalyje rašysite kodą, kuris pavers tekstą garsu, naudodamas kalbos paslaugą.

## Teksto pavertimas garsu naudojant kalbos paslaugą

Tekstas gali būti siunčiamas į kalbos paslaugą per REST API, kad būtų gautas garsas kaip garso failas, kurį galima atkurti jūsų IoT įrenginyje. Prašant garso, reikia nurodyti balsą, nes garsas gali būti generuojamas naudojant įvairius balsus.

Kiekviena kalba palaiko įvairius balsus, ir galite atlikti REST užklausą kalbos paslaugai, kad gautumėte palaikomų balsų sąrašą kiekvienai kalbai.

### Užduotis - pasirinkti balsą

1. Atidarykite `smart-timer` projektą VS Code aplinkoje.

1. Pridėkite šį kodą virš `say` funkcijos, kad gautumėte kalbos balsų sąrašą:

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

    Šis kodas apibrėžia funkciją, vadinamą `get_voice`, kuri naudoja kalbos paslaugą balsų sąrašui gauti. Tada ji suranda pirmą balsą, kuris atitinka naudojamą kalbą.

    Ši funkcija yra iškviečiama, kad būtų išsaugotas pirmasis balsas, o balso pavadinimas atspausdinamas konsolėje. Šį balsą galima nustatyti vieną kartą ir naudoti kiekvieną kartą, kai tekstas paverčiamas garsu.

    > 💁 Visą palaikomų balsų sąrašą galite rasti [Microsoft Docs kalbų ir balsų palaikymo dokumentacijoje](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#text-to-speech). Jei norite naudoti konkretų balsą, galite pašalinti šią funkciją ir tiesiogiai įrašyti balso pavadinimą iš šios dokumentacijos. Pavyzdžiui:
    >
    > ```python
    > voice = 'hi-IN-SwaraNeural'
    > ```

### Užduotis - paversti tekstą garsu

1. Po šio kodo apibrėžkite konstantą, nurodančią garso formatą, kuris bus gautas iš kalbos paslaugų. Prašant garso, galite pasirinkti iš įvairių formatų.

    ```python
    playback_format = 'riff-48khz-16bit-mono-pcm'
    ```

    Naudojamas formatas priklauso nuo jūsų įrangos. Jei gaunate klaidą `Invalid sample rate`, pakeiskite šį formatą į kitą. Palaikomų formatų sąrašą galite rasti [Text to speech REST API dokumentacijoje Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/rest-text-to-speech?WT.mc_id=academic-17441-jabenn#audio-outputs). Turėsite naudoti `riff` formato garsą, o galimi variantai yra `riff-16khz-16bit-mono-pcm`, `riff-24khz-16bit-mono-pcm` ir `riff-48khz-16bit-mono-pcm`.

1. Po šio kodo apibrėžkite funkciją, vadinamą `get_speech`, kuri pavers tekstą garsu naudodama kalbos paslaugos REST API:

    ```python
    def get_speech(text):
    ```

1. `get_speech` funkcijoje apibrėžkite URL, kurį reikia iškviesti, ir antraštes, kurias reikia perduoti:

    ```python
        url = f'https://{location}.tts.speech.microsoft.com/cognitiveservices/v1'
    
        headers = {
            'Authorization': 'Bearer ' + get_access_token(),
            'Content-Type': 'application/ssml+xml',
            'X-Microsoft-OutputFormat': playback_format
        }
    ```

    Šiame kode antraštės nustatomos taip, kad būtų naudojamas sugeneruotas prieigos raktas, turinys nustatomas kaip SSML, o garso formatas - kaip reikalingas.

1. Po šio kodo apibrėžkite SSML, kuris bus siunčiamas į REST API:

    ```python
    ssml =  f'<speak version=\'1.0\' xml:lang=\'{language}\'>'
    ssml += f'<voice xml:lang=\'{language}\' name=\'{voice}\'>'
    ssml += text
    ssml += '</voice>'
    ssml += '</speak>'
    ```

    Šis SSML nustato kalbą ir balsą, kuris bus naudojamas, taip pat tekstą, kurį reikia paversti.

1. Galiausiai pridėkite kodą šioje funkcijoje, kad atliktumėte REST užklausą ir grąžintumėte dvejetainius garso duomenis:

    ```python
    response = requests.post(url, headers=headers, data=ssml.encode('utf-8'))
    return io.BytesIO(response.content)
    ```

### Užduotis - atkurti garsą

1. Po `get_speech` funkcijos apibrėžkite naują funkciją, kuri atkurs garsą, grąžintą REST API užklausos metu:

    ```python
    def play_speech(speech):
    ```

1. `speech`, perduotas šiai funkcijai, bus dvejetainiai garso duomenys, grąžinti iš REST API. Naudokite šį kodą, kad atidarytumėte juos kaip bangos failą ir perduotumėte PyAudio, kad garsas būtų atkurtas:

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

    Šis kodas naudoja PyAudio srautą, kaip ir garso įrašymui. Skirtumas tas, kad srautas nustatomas kaip išvesties srautas, o duomenys skaitomi iš garso duomenų ir perduodami į srautą.

    Vietoj to, kad srauto detalės, tokios kaip pavyzdžių dažnis, būtų užkoduotos, jos nuskaitomos iš garso duomenų.

1. Pakeiskite `say` funkcijos turinį į šį:

    ```python
    speech = get_speech(text)
    play_speech(speech)
    ```

    Šis kodas paverčia tekstą garsu kaip dvejetainius garso duomenis ir atkuria garsą.

1. Paleiskite programą ir įsitikinkite, kad funkcijų programa taip pat veikia. Nustatykite kelis laikmačius, ir išgirsite balsu pranešimą, kad jūsų laikmatis buvo nustatytas, o vėliau kitą pranešimą, kai laikmatis baigsis.

    Jei gaunate klaidą `Invalid sample rate`, pakeiskite `playback_format`, kaip aprašyta aukščiau.

> 💁 Šį kodą galite rasti [code-spoken-response/pi](../../../../../6-consumer/lessons/3-spoken-feedback/code-spoken-response/pi) aplanke.

😀 Jūsų laikmačio programa buvo sėkminga!

---

**Atsakomybės apribojimas**:  
Šis dokumentas buvo išverstas naudojant AI vertimo paslaugą [Co-op Translator](https://github.com/Azure/co-op-translator). Nors siekiame tikslumo, prašome atkreipti dėmesį, kad automatiniai vertimai gali turėti klaidų ar netikslumų. Originalus dokumentas jo gimtąja kalba turėtų būti laikomas autoritetingu šaltiniu. Kritinei informacijai rekomenduojama naudoti profesionalų žmogaus vertimą. Mes neprisiimame atsakomybės už nesusipratimus ar klaidingus interpretavimus, atsiradusius dėl šio vertimo naudojimo.