<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "606f3af1c78e3741e48ce77c31cea626",
  "translation_date": "2025-08-28T12:45:53+00:00",
  "source_file": "6-consumer/lessons/3-spoken-feedback/pi-text-to-speech.md",
  "language_code": "hr"
}
-->
# Pretvaranje teksta u govor - Raspberry Pi

U ovom dijelu lekcije napisat ćete kod za pretvaranje teksta u govor koristeći uslugu govora.

## Pretvaranje teksta u govor pomoću usluge govora

Tekst se može poslati usluzi govora putem REST API-ja kako bi se dobio govor u obliku audio datoteke koja se može reproducirati na vašem IoT uređaju. Prilikom zahtjeva za govor, potrebno je odabrati glas koji će se koristiti, jer govor može biti generiran koristeći razne glasove.

Svaki jezik podržava različite glasove, a možete napraviti REST zahtjev prema usluzi govora kako biste dobili popis podržanih glasova za svaki jezik.

### Zadatak - odabir glasa

1. Otvorite projekt `smart-timer` u VS Code-u.

1. Dodajte sljedeći kod iznad funkcije `say` kako biste zatražili popis glasova za određeni jezik:

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

    Ovaj kod definira funkciju pod nazivom `get_voice` koja koristi uslugu govora za dobivanje popisa glasova. Zatim pronalazi prvi glas koji odgovara jeziku koji se koristi.

    Ova funkcija se zatim poziva kako bi se pohranio prvi glas, a ime glasa se ispisuje u konzolu. Ovaj glas može se zatražiti jednom, a vrijednost se može koristiti za svaki poziv za pretvaranje teksta u govor.

    > 💁 Cijeli popis podržanih glasova možete pronaći u [dokumentaciji o podršci za jezike i glasove na Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#text-to-speech). Ako želite koristiti određeni glas, možete ukloniti ovu funkciju i ručno unijeti ime glasa iz ove dokumentacije. Na primjer:
    >
    > ```python
    > voice = 'hi-IN-SwaraNeural'
    > ```

### Zadatak - pretvaranje teksta u govor

1. Ispod ovoga, definirajte konstantu za audio format koji će se dohvatiti iz usluge govora. Kada zatražite audio, možete to učiniti u različitim formatima.

    ```python
    playback_format = 'riff-48khz-16bit-mono-pcm'
    ```

    Format koji možete koristiti ovisi o vašem hardveru. Ako dobijete greške `Invalid sample rate` prilikom reprodukcije audija, promijenite ovo na drugu vrijednost. Popis podržanih vrijednosti možete pronaći u [REST API dokumentaciji za pretvaranje teksta u govor na Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/rest-text-to-speech?WT.mc_id=academic-17441-jabenn#audio-outputs). Morat ćete koristiti audio u `riff` formatu, a vrijednosti koje možete isprobati su `riff-16khz-16bit-mono-pcm`, `riff-24khz-16bit-mono-pcm` i `riff-48khz-16bit-mono-pcm`.

1. Ispod ovoga, deklarirajte funkciju pod nazivom `get_speech` koja će pretvoriti tekst u govor koristeći REST API usluge govora:

    ```python
    def get_speech(text):
    ```

1. U funkciji `get_speech`, definirajte URL za poziv i zaglavlja koja će se proslijediti:

    ```python
        url = f'https://{location}.tts.speech.microsoft.com/cognitiveservices/v1'
    
        headers = {
            'Authorization': 'Bearer ' + get_access_token(),
            'Content-Type': 'application/ssml+xml',
            'X-Microsoft-OutputFormat': playback_format
        }
    ```

    Ovo postavlja zaglavlja za korištenje generiranog pristupnog tokena, postavlja sadržaj na SSML i definira potrebni audio format.

1. Ispod ovoga, definirajte SSML koji će se poslati REST API-ju:

    ```python
    ssml =  f'<speak version=\'1.0\' xml:lang=\'{language}\'>'
    ssml += f'<voice xml:lang=\'{language}\' name=\'{voice}\'>'
    ssml += text
    ssml += '</voice>'
    ssml += '</speak>'
    ```

    Ovaj SSML postavlja jezik i glas koji će se koristiti, zajedno s tekstom koji će se pretvoriti.

1. Na kraju, dodajte kod u ovu funkciju za izvršavanje REST zahtjeva i vraćanje binarnih audio podataka:

    ```python
    response = requests.post(url, headers=headers, data=ssml.encode('utf-8'))
    return io.BytesIO(response.content)
    ```

### Zadatak - reprodukcija audija

1. Ispod funkcije `get_speech`, definirajte novu funkciju za reprodukciju audija koji je vraćen REST API pozivom:

    ```python
    def play_speech(speech):
    ```

1. `speech` koji se prosljeđuje ovoj funkciji bit će binarni audio podaci vraćeni iz REST API-ja. Koristite sljedeći kod za otvaranje ovoga kao wave datoteke i prosljeđivanje PyAudio-u za reprodukciju audija:

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

    Ovaj kod koristi PyAudio stream, isto kao i za snimanje audija. Razlika je u tome što je stream postavljen kao izlazni stream, a podaci se čitaju iz audio datoteke i prosljeđuju streamu.

    Umjesto da se detalji streama, poput sample rate-a, ručno unose, oni se čitaju iz audio podataka.

1. Zamijenite sadržaj funkcije `say` sljedećim:

    ```python
    speech = get_speech(text)
    play_speech(speech)
    ```

    Ovaj kod pretvara tekst u govor kao binarne audio podatke i reproducira audio.

1. Pokrenite aplikaciju i osigurajte da funkcijska aplikacija također radi. Postavite nekoliko timera i čut ćete glasovni odgovor koji kaže da je vaš timer postavljen, a zatim drugi glasovni odgovor kada timer završi.

    Ako dobijete greške `Invalid sample rate`, promijenite `playback_format` kako je gore opisano.

> 💁 Ovaj kod možete pronaći u [code-spoken-response/pi](../../../../../6-consumer/lessons/3-spoken-feedback/code-spoken-response/pi) mapi.

😀 Vaš program za timer bio je uspješan!

---

**Odricanje od odgovornosti**:  
Ovaj dokument je preveden pomoću AI usluge za prevođenje [Co-op Translator](https://github.com/Azure/co-op-translator). Iako nastojimo osigurati točnost, imajte na umu da automatski prijevodi mogu sadržavati pogreške ili netočnosti. Izvorni dokument na izvornom jeziku treba smatrati autoritativnim izvorom. Za kritične informacije preporučuje se profesionalni prijevod od strane ljudskog prevoditelja. Ne preuzimamo odgovornost za bilo kakva nesporazuma ili pogrešna tumačenja koja proizlaze iz korištenja ovog prijevoda.