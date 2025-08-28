<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "606f3af1c78e3741e48ce77c31cea626",
  "translation_date": "2025-08-28T12:46:12+00:00",
  "source_file": "6-consumer/lessons/3-spoken-feedback/pi-text-to-speech.md",
  "language_code": "sl"
}
-->
# Pretvorba besedila v govor - Raspberry Pi

V tem delu lekcije boste napisali kodo za pretvorbo besedila v govor z uporabo storitve za govor.

## Pretvorba besedila v govor z uporabo storitve za govor

Besedilo lahko pošljete storitvi za govor prek REST API-ja, da pridobite govor kot zvočno datoteko, ki jo lahko predvajate na svoji IoT napravi. Pri zahtevi za govor morate določiti glas, saj se govor lahko ustvari z različnimi glasovi.

Vsak jezik podpira različne glasove, REST zahtevo pa lahko pošljete storitvi za govor, da pridobite seznam podprtih glasov za posamezen jezik.

### Naloga - pridobite glas

1. Odprite projekt `smart-timer` v VS Code.

1. Nad funkcijo `say` dodajte naslednjo kodo, da zahtevate seznam glasov za določen jezik:

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

    Ta koda definira funkcijo z imenom `get_voice`, ki uporablja storitev za govor za pridobitev seznama glasov. Nato najde prvi glas, ki ustreza jeziku, ki se uporablja.

    Ta funkcija se nato pokliče, da shrani prvi glas, ime glasu pa se izpiše v konzolo. Ta glas lahko zahtevate enkrat, vrednost pa uporabite pri vsakem klicu za pretvorbo besedila v govor.

    > 💁 Celoten seznam podprtih glasov lahko najdete v [dokumentaciji o podpori za jezike in glasove na Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#text-to-speech). Če želite uporabiti določen glas, lahko to funkcijo odstranite in ročno nastavite glas na ime glasu iz te dokumentacije. Na primer:
    >
    > ```python
    > voice = 'hi-IN-SwaraNeural'
    > ```

### Naloga - pretvorba besedila v govor

1. Spodaj definirajte konstanto za zvočni format, ki ga želite pridobiti iz storitve za govor. Ko zahtevate zvok, to lahko storite v različnih formatih.

    ```python
    playback_format = 'riff-48khz-16bit-mono-pcm'
    ```

    Format, ki ga lahko uporabite, je odvisen od vaše strojne opreme. Če dobite napake `Invalid sample rate` pri predvajanju zvoka, spremenite to na drugo vrednost. Seznam podprtih vrednosti najdete v [dokumentaciji REST API-ja za pretvorbo besedila v govor na Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/rest-text-to-speech?WT.mc_id=academic-17441-jabenn#audio-outputs). Uporabiti morate zvok v formatu `riff`, vrednosti, ki jih lahko poskusite, pa so `riff-16khz-16bit-mono-pcm`, `riff-24khz-16bit-mono-pcm` in `riff-48khz-16bit-mono-pcm`.

1. Spodaj deklarirajte funkcijo z imenom `get_speech`, ki bo pretvorila besedilo v govor z uporabo REST API-ja storitve za govor:

    ```python
    def get_speech(text):
    ```

1. V funkciji `get_speech` definirajte URL za klic in glave, ki jih je treba posredovati:

    ```python
        url = f'https://{location}.tts.speech.microsoft.com/cognitiveservices/v1'
    
        headers = {
            'Authorization': 'Bearer ' + get_access_token(),
            'Content-Type': 'application/ssml+xml',
            'X-Microsoft-OutputFormat': playback_format
        }
    ```

    To nastavi glave za uporabo generiranega dostopnega žetona, določi vsebino kot SSML in definira potreben zvočni format.

1. Spodaj definirajte SSML, ki ga boste poslali REST API-ju:

    ```python
    ssml =  f'<speak version=\'1.0\' xml:lang=\'{language}\'>'
    ssml += f'<voice xml:lang=\'{language}\' name=\'{voice}\'>'
    ssml += text
    ssml += '</voice>'
    ssml += '</speak>'
    ```

    Ta SSML nastavi jezik in glas, ki ga želite uporabiti, skupaj z besedilom za pretvorbo.

1. Na koncu dodajte kodo v tej funkciji, da izvedete REST zahtevo in vrnete binarne podatke zvoka:

    ```python
    response = requests.post(url, headers=headers, data=ssml.encode('utf-8'))
    return io.BytesIO(response.content)
    ```

### Naloga - predvajanje zvoka

1. Spodaj pod funkcijo `get_speech` definirajte novo funkcijo za predvajanje zvoka, ki ga vrne REST API klic:

    ```python
    def play_speech(speech):
    ```

1. `speech`, ki se posreduje tej funkciji, bodo binarni podatki zvoka, ki jih vrne REST API. Uporabite naslednjo kodo, da to odprete kot valovno datoteko in jo posredujete PyAudio za predvajanje zvoka:

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

    Ta koda uporablja PyAudio tok, enako kot pri zajemanju zvoka. Razlika je v tem, da je tok nastavljen kot izhodni tok, podatki pa se berejo iz zvočnih podatkov in pošiljajo v tok.

    Namesto da bi trdo kodirali podrobnosti toka, kot je vzorčna frekvenca, se te berejo iz zvočnih podatkov.

1. Zamenjajte vsebino funkcije `say` z naslednjim:

    ```python
    speech = get_speech(text)
    play_speech(speech)
    ```

    Ta koda pretvori besedilo v govor kot binarne zvočne podatke in predvaja zvok.

1. Zaženite aplikacijo in poskrbite, da funkcijska aplikacija tudi deluje. Nastavite nekaj časovnikov in slišali boste govorjeni odgovor, ki pravi, da je vaš časovnik nastavljen, nato pa še en govorjeni odgovor, ko je časovnik končan.

    Če dobite napake `Invalid sample rate`, spremenite `playback_format`, kot je opisano zgoraj.

> 💁 To kodo lahko najdete v mapi [code-spoken-response/pi](../../../../../6-consumer/lessons/3-spoken-feedback/code-spoken-response/pi).

😀 Vaš program za časovnik je bil uspešen!

---

**Omejitev odgovornosti**:  
Ta dokument je bil preveden z uporabo storitve za prevajanje z umetno inteligenco [Co-op Translator](https://github.com/Azure/co-op-translator). Čeprav si prizadevamo za natančnost, vas prosimo, da upoštevate, da lahko avtomatizirani prevodi vsebujejo napake ali netočnosti. Izvirni dokument v njegovem maternem jeziku je treba obravnavati kot avtoritativni vir. Za ključne informacije priporočamo profesionalni človeški prevod. Ne prevzemamo odgovornosti za morebitna nesporazume ali napačne razlage, ki bi nastale zaradi uporabe tega prevoda.