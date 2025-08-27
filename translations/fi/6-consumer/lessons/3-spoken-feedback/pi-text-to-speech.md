<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "606f3af1c78e3741e48ce77c31cea626",
  "translation_date": "2025-08-27T22:27:30+00:00",
  "source_file": "6-consumer/lessons/3-spoken-feedback/pi-text-to-speech.md",
  "language_code": "fi"
}
-->
# Teksti puheeksi - Raspberry Pi

Tässä osassa oppituntia kirjoitat koodia, joka muuntaa tekstin puheeksi käyttämällä puhepalvelua.

## Muunna teksti puheeksi puhepalvelun avulla

Teksti voidaan lähettää puhepalveluun REST API:n kautta, jolloin saadaan puhetta äänitiedostona, joka voidaan toistaa IoT-laitteellasi. Kun pyydät puhetta, sinun täytyy määrittää käytettävä ääni, sillä puhetta voidaan tuottaa monilla eri äänillä.

Jokainen kieli tukee useita eri ääniä, ja voit tehdä REST-pyynnön puhepalveluun saadaksesi listan tuetuista äänistä kullekin kielelle.

### Tehtävä - valitse ääni

1. Avaa `smart-timer`-projekti VS Codessa.

1. Lisää seuraava koodi `say`-funktion yläpuolelle pyytääksesi listan äänistä tietylle kielelle:

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

    Tämä koodi määrittää funktion nimeltä `get_voice`, joka käyttää puhepalvelua saadakseen listan äänistä. Se etsii ensimmäisen äänen, joka vastaa käytettävää kieltä.

    Tämä funktio kutsutaan tallentamaan ensimmäinen ääni, ja äänen nimi tulostetaan konsoliin. Tämä ääni voidaan pyytää kerran, ja arvoa voidaan käyttää jokaisessa tekstin muuntamisessa puheeksi.

    > 💁 Voit saada täydellisen listan tuetuista äänistä [Microsoft Docsin kieli- ja äänitukidokumentaatiosta](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#text-to-speech). Jos haluat käyttää tiettyä ääntä, voit poistaa tämän funktion ja kovakoodata äänen nimen tästä dokumentaatiosta. Esimerkiksi:
    >
    > ```python
    > voice = 'hi-IN-SwaraNeural'
    > ```

### Tehtävä - muunna teksti puheeksi

1. Määritä tämän alle vakio ääniformaatille, joka haetaan puhepalvelusta. Kun pyydät ääntä, voit tehdä sen useissa eri formaateissa.

    ```python
    playback_format = 'riff-48khz-16bit-mono-pcm'
    ```

    Käytettävä formaatti riippuu laitteistostasi. Jos saat virheitä kuten `Invalid sample rate` ääntä toistaessasi, vaihda tämä toiseen arvoon. Löydät tuettujen arvojen listan [Text to speech REST API -dokumentaatiosta Microsoft Docsissa](https://docs.microsoft.com/azure/cognitive-services/speech-service/rest-text-to-speech?WT.mc_id=academic-17441-jabenn#audio-outputs). Sinun täytyy käyttää `riff`-formaattia, ja kokeiltavat arvot ovat `riff-16khz-16bit-mono-pcm`, `riff-24khz-16bit-mono-pcm` ja `riff-48khz-16bit-mono-pcm`.

1. Määritä tämän alle funktio nimeltä `get_speech`, joka muuntaa tekstin puheeksi käyttämällä puhepalvelun REST API:ta:

    ```python
    def get_speech(text):
    ```

1. `get_speech`-funktiossa määritä URL, jota kutsutaan, ja otsikot, jotka lähetetään:

    ```python
        url = f'https://{location}.tts.speech.microsoft.com/cognitiveservices/v1'
    
        headers = {
            'Authorization': 'Bearer ' + get_access_token(),
            'Content-Type': 'application/ssml+xml',
            'X-Microsoft-OutputFormat': playback_format
        }
    ```

    Tämä asettaa otsikot käyttämään luotua käyttöoikeustunnusta, määrittää sisällön SSML-muotoon ja määrittää tarvittavan ääniformaatin.

1. Määritä tämän alle SSML, joka lähetetään REST API:lle:

    ```python
    ssml =  f'<speak version=\'1.0\' xml:lang=\'{language}\'>'
    ssml += f'<voice xml:lang=\'{language}\' name=\'{voice}\'>'
    ssml += text
    ssml += '</voice>'
    ssml += '</speak>'
    ```

    Tämä SSML määrittää käytettävän kielen ja äänen sekä tekstin, joka muunnetaan.

1. Lopuksi lisää koodi tähän funktioon tekemään REST-pyyntö ja palauttamaan binaarinen äänidata:

    ```python
    response = requests.post(url, headers=headers, data=ssml.encode('utf-8'))
    return io.BytesIO(response.content)
    ```

### Tehtävä - toista ääni

1. Määritä `get_speech`-funktion alle uusi funktio, joka toistaa REST API -kutsun palauttaman äänen:

    ```python
    def play_speech(speech):
    ```

1. `speech`, joka välitetään tähän funktioon, on binaarinen äänidata, jonka REST API palauttaa. Käytä seuraavaa koodia avataksesi tämän wave-tiedostona ja välittääksesi sen PyAudiolle äänen toistamiseksi:

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

    Tämä koodi käyttää PyAudio-streamia, samalla tavalla kuin äänen tallentamisessa. Erona tässä on, että stream määritetään ulostulostreamiksi, ja data luetaan äänidatasta ja välitetään streamiin.

    Sen sijaan, että streamin yksityiskohdat kuten näytteenottotaajuus kovakoodattaisiin, ne luetaan äänidatasta.

1. Korvaa `say`-funktion sisältö seuraavalla:

    ```python
    speech = get_speech(text)
    play_speech(speech)
    ```

    Tämä koodi muuntaa tekstin puheeksi binaarisena äänidatana ja toistaa äänen.

1. Suorita sovellus ja varmista, että funktiosovellus on myös käynnissä. Aseta joitakin ajastimia, ja kuulet puhutun vastauksen, joka kertoo, että ajastimesi on asetettu, ja toisen puhutun vastauksen, kun ajastin on valmis.

    Jos saat virheitä kuten `Invalid sample rate`, muuta `playback_format` yllä kuvatulla tavalla.

> 💁 Löydät tämän koodin [code-spoken-response/pi](../../../../../6-consumer/lessons/3-spoken-feedback/code-spoken-response/pi) -kansiosta.

😀 Ajastinohjelmasi oli menestys!

---

**Vastuuvapauslauseke**:  
Tämä asiakirja on käännetty käyttämällä tekoälypohjaista käännöspalvelua [Co-op Translator](https://github.com/Azure/co-op-translator). Vaikka pyrimme tarkkuuteen, huomioithan, että automaattiset käännökset voivat sisältää virheitä tai epätarkkuuksia. Alkuperäistä asiakirjaa sen alkuperäisellä kielellä tulisi pitää ensisijaisena lähteenä. Kriittisen tiedon osalta suositellaan ammattimaista ihmiskäännöstä. Emme ole vastuussa väärinkäsityksistä tai virhetulkinnoista, jotka johtuvat tämän käännöksen käytöstä.