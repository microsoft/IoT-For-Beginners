<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "606f3af1c78e3741e48ce77c31cea626",
  "translation_date": "2025-08-28T09:03:13+00:00",
  "source_file": "6-consumer/lessons/3-spoken-feedback/pi-text-to-speech.md",
  "language_code": "ro"
}
-->
# Text to speech - Raspberry Pi

În această parte a lecției, vei scrie cod pentru a converti textul în vorbire folosind serviciul de vorbire.

## Conversia textului în vorbire folosind serviciul de vorbire

Textul poate fi trimis către serviciul de vorbire utilizând REST API pentru a obține vorbirea sub formă de fișier audio, care poate fi redat pe dispozitivul tău IoT. Când soliciți vorbirea, trebuie să specifici vocea utilizată, deoarece vorbirea poate fi generată folosind o varietate de voci diferite.

Fiecare limbă suportă o gamă de voci diferite, iar tu poți face o cerere REST către serviciul de vorbire pentru a obține lista vocilor disponibile pentru fiecare limbă.

### Sarcină - obține o voce

1. Deschide proiectul `smart-timer` în VS Code.

1. Adaugă următorul cod deasupra funcției `say` pentru a solicita lista vocilor pentru o limbă:

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

    Acest cod definește o funcție numită `get_voice` care utilizează serviciul de vorbire pentru a obține o listă de voci. Apoi găsește prima voce care se potrivește cu limba utilizată.

    Această funcție este apoi apelată pentru a stoca prima voce, iar numele vocii este afișat în consolă. Această voce poate fi solicitată o singură dată, iar valoarea poate fi utilizată pentru fiecare apel de conversie a textului în vorbire.

    > 💁 Poți obține lista completă a vocilor disponibile din [documentația despre suportul pentru limbi și voci pe Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#text-to-speech). Dacă dorești să utilizezi o voce specifică, poți elimina această funcție și să introduci manual numele vocii din această documentație. De exemplu:
    >
    > ```python
    > voice = 'hi-IN-SwaraNeural'
    > ```

### Sarcină - convertește textul în vorbire

1. Sub acest cod, definește o constantă pentru formatul audio care va fi obținut de la serviciile de vorbire. Când soliciți audio, poți face acest lucru într-o gamă de formate diferite.

    ```python
    playback_format = 'riff-48khz-16bit-mono-pcm'
    ```

    Formatul pe care îl poți utiliza depinde de hardware-ul tău. Dacă primești erori de tipul `Invalid sample rate` atunci când redai audio, schimbă acest format cu o altă valoare. Poți găsi lista valorilor acceptate în [documentația REST API pentru text-to-speech pe Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/rest-text-to-speech?WT.mc_id=academic-17441-jabenn#audio-outputs). Va trebui să utilizezi audio în format `riff`, iar valorile pe care le poți încerca sunt `riff-16khz-16bit-mono-pcm`, `riff-24khz-16bit-mono-pcm` și `riff-48khz-16bit-mono-pcm`.

1. Sub acest cod, declară o funcție numită `get_speech` care va converti textul în vorbire folosind REST API-ul serviciului de vorbire:

    ```python
    def get_speech(text):
    ```

1. În funcția `get_speech`, definește URL-ul care va fi apelat și anteturile care vor fi transmise:

    ```python
        url = f'https://{location}.tts.speech.microsoft.com/cognitiveservices/v1'
    
        headers = {
            'Authorization': 'Bearer ' + get_access_token(),
            'Content-Type': 'application/ssml+xml',
            'X-Microsoft-OutputFormat': playback_format
        }
    ```

    Acest cod setează anteturile pentru a utiliza un token de acces generat, definește conținutul ca SSML și specifică formatul audio necesar.

1. Sub acest cod, definește SSML-ul care va fi trimis către REST API:

    ```python
    ssml =  f'<speak version=\'1.0\' xml:lang=\'{language}\'>'
    ssml += f'<voice xml:lang=\'{language}\' name=\'{voice}\'>'
    ssml += text
    ssml += '</voice>'
    ssml += '</speak>'
    ```

    Acest SSML setează limba și vocea care vor fi utilizate, împreună cu textul care va fi convertit.

1. În cele din urmă, adaugă cod în această funcție pentru a face cererea REST și a returna datele audio binare:

    ```python
    response = requests.post(url, headers=headers, data=ssml.encode('utf-8'))
    return io.BytesIO(response.content)
    ```

### Sarcină - redă audio-ul

1. Sub funcția `get_speech`, definește o nouă funcție pentru a reda audio-ul returnat de apelul REST API:

    ```python
    def play_speech(speech):
    ```

1. Parametrul `speech` transmis acestei funcții va fi datele audio binare returnate de REST API. Utilizează următorul cod pentru a deschide acest fișier ca un fișier wave și pentru a-l reda folosind PyAudio:

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

    Acest cod utilizează un flux PyAudio, la fel ca în cazul capturării audio. Diferența aici este că fluxul este setat ca flux de ieșire, iar datele sunt citite din datele audio și transmise către flux.

    În loc să codifici manual detaliile fluxului, cum ar fi rata de eșantionare, acestea sunt citite din datele audio.

1. Înlocuiește conținutul funcției `say` cu următorul cod:

    ```python
    speech = get_speech(text)
    play_speech(speech)
    ```

    Acest cod convertește textul în vorbire sub formă de date audio binare și redă audio-ul.

1. Rulează aplicația și asigură-te că aplicația funcțională rulează de asemenea. Setează câteva cronometre și vei auzi un răspuns vocal care îți spune că cronometrul a fost setat, apoi un alt răspuns vocal când cronometrul se finalizează.

    Dacă primești erori de tipul `Invalid sample rate`, schimbă `playback_format` așa cum este descris mai sus.

> 💁 Poți găsi acest cod în folderul [code-spoken-response/pi](../../../../../6-consumer/lessons/3-spoken-feedback/code-spoken-response/pi).

😀 Programul tău de cronometru a fost un succes!

---

**Declinare de responsabilitate**:  
Acest document a fost tradus folosind serviciul de traducere AI [Co-op Translator](https://github.com/Azure/co-op-translator). Deși ne străduim să asigurăm acuratețea, vă rugăm să fiți conștienți că traducerile automate pot conține erori sau inexactități. Documentul original în limba sa natală ar trebui considerat sursa autoritară. Pentru informații critice, se recomandă traducerea profesională realizată de un specialist uman. Nu ne asumăm responsabilitatea pentru eventualele neînțelegeri sau interpretări greșite care pot apărea din utilizarea acestei traduceri.