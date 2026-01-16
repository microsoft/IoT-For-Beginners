<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "0ac0afcfb40cb5970ef4cb74f01c32e9",
  "translation_date": "2025-08-27T22:32:14+00:00",
  "source_file": "6-consumer/lessons/1-speech-recognition/pi-audio.md",
  "language_code": "fi"
}
-->
# Tallenna ääntä - Raspberry Pi

Tässä osassa oppituntia kirjoitat koodia äänen tallentamiseen Raspberry Pi:llä. Äänentallennusta ohjataan painikkeella.

## Laitteisto

Raspberry Pi tarvitsee painikkeen äänen tallennuksen ohjaamiseen.

Käytettävä painike on Grove-painike. Tämä on digitaalinen anturi, joka kytkee signaalin päälle tai pois. Nämä painikkeet voidaan määrittää lähettämään korkea signaali, kun painiketta painetaan, ja matala, kun sitä ei paineta, tai matala, kun painetaan ja korkea, kun ei paineta.

Jos käytät ReSpeaker 2-Mics Pi HAT -mikrofonia, painiketta ei tarvitse liittää, sillä tämä HAT sisältää painikkeen valmiiksi. Siirry seuraavaan osioon.

### Liitä painike

Painike voidaan liittää Grove Base HAT:iin.

#### Tehtävä - liitä painike

![Grove-painike](../../../../../translated_images/fi/grove-button.a70cfbb809a8563681003250cf5b06d68cdcc68624f9e2f493d5a534ae2da1e5.png)

1. Työnnä Grove-kaapelin toinen pää painikemoduulin liittimeen. Se menee sisään vain yhdellä tavalla.

1. Kun Raspberry Pi on sammutettu, liitä Grove-kaapelin toinen pää digitaaliseen liittimeen, joka on merkitty **D5** Grove Base HAT:ssa, joka on kiinnitetty Pi:hin. Tämä liitin on toinen vasemmalta GPIO-pinnien vieressä olevassa rivissä.

![Grove-painike liitettynä liittimeen D5](../../../../../translated_images/fi/pi-button.c7a1a4f55943341ce1baf1057658e9a205804d4131d258e820c93f951df0abf3.png)

## Tallenna ääntä

Voit tallentaa ääntä mikrofonista Python-koodilla.

### Tehtävä - tallenna ääntä

1. Käynnistä Pi ja odota, että se käynnistyy.

1. Avaa VS Code joko suoraan Pi:llä tai yhdistä Remote SSH -laajennuksen kautta.

1. PyAudio Pip -paketti sisältää funktioita äänen tallentamiseen ja toistamiseen. Tämä paketti vaatii joitakin äänenkirjastoja, jotka täytyy asentaa ensin. Suorita seuraavat komennot terminaalissa asentaaksesi ne:

    ```sh
    sudo apt update
    sudo apt install libportaudio0 libportaudio2 libportaudiocpp0 portaudio19-dev libasound2-plugins --yes 
    ```

1. Asenna PyAudio Pip -paketti.

    ```sh
    pip3 install pyaudio
    ```

1. Luo uusi kansio nimeltä `smart-timer` ja lisää tiedosto nimeltä `app.py` tähän kansioon.

1. Lisää tiedoston alkuun seuraavat tuonnit:

    ```python
    import io
    import pyaudio
    import time
    import wave
    
    from grove.factory import Factory
    ```

    Tämä tuo `pyaudio`-moduulin, joitakin Pythonin vakio-moduuleja WAV-tiedostojen käsittelyyn sekä `grove.factory`-moduulin painikeluokan luomiseen.

1. Lisää tämän alle koodi Grove-painikkeen luomiseen.

    Jos käytät ReSpeaker 2-Mics Pi HAT:ia, käytä seuraavaa koodia:

    ```python
    # The button on the ReSpeaker 2-Mics Pi HAT
    button = Factory.getButton("GPIO-LOW", 17)
    ```

    Tämä luo painikkeen porttiin **D17**, joka on portti, johon ReSpeaker 2-Mics Pi HAT:n painike on liitetty. Tämä painike on asetettu lähettämään matala signaali, kun sitä painetaan.

    Jos et käytä ReSpeaker 2-Mics Pi HAT:ia, vaan Grove-painiketta, joka on liitetty Base HAT:iin, käytä tätä koodia:

    ```python
    button = Factory.getButton("GPIO-HIGH", 5)
    ```

    Tämä luo painikkeen porttiin **D5**, joka on asetettu lähettämään korkea signaali, kun sitä painetaan.

1. Lisää tämän alle PyAudio-luokan instanssi äänen käsittelyyn:

    ```python
    audio = pyaudio.PyAudio()
    ```

1. Määritä mikrofonin ja kaiuttimen laitteistokorttien numerot. Tämä on korttinumero, jonka löysit suorittamalla `arecord -l` ja `aplay -l` aiemmin tässä oppitunnissa.

    ```python
    microphone_card_number = <microphone card number>
    speaker_card_number = <speaker card number>
    ```

    Korvaa `<microphone card number>` mikrofonisi korttinumerolla.

    Korvaa `<speaker card number>` kaiuttimesi korttinumerolla, samalla numerolla, jonka määritit `alsa.conf`-tiedostossa.

1. Määritä tämän alle näytteenottotaajuus, jota käytetään äänen tallennuksessa ja toistossa. Saatat joutua muuttamaan tätä riippuen käyttämästäsi laitteistosta.

    ```python
    rate = 48000 #48KHz
    ```

    Jos saat näytteenottotaajuusvirheitä, kun suoritat koodia myöhemmin, muuta tämä arvo `44100` tai `16000`. Mitä korkeampi arvo, sitä parempi äänenlaatu.

1. Luo tämän alle uusi funktio nimeltä `capture_audio`. Tätä kutsutaan mikrofonin äänen tallentamiseen:

    ```python
    def capture_audio():
    ```

1. Lisää tämän funktion sisälle seuraava koodi äänen tallentamiseen:

    ```python
    stream = audio.open(format = pyaudio.paInt16,
                        rate = rate,
                        channels = 1, 
                        input_device_index = microphone_card_number,
                        input = True,
                        frames_per_buffer = 4096)

    frames = []

    while button.is_pressed():
        frames.append(stream.read(4096))

    stream.stop_stream()
    stream.close()
    ```

    Tämä koodi avaa äänen syöttövirran PyAudio-objektilla. Tämä virta tallentaa ääntä mikrofonista 16 kHz:n taajuudella, tallentaen sen 4096 tavun kokoisiin puskureihin.

    Koodi sitten silmukoi, kun Grove-painiketta painetaan, lukien nämä 4096 tavun puskurit taulukkoon joka kerta.

    > 💁 Voit lukea lisää `open`-metodille annetuista vaihtoehdoista [PyAudio-dokumentaatiosta](https://people.csail.mit.edu/hubert/pyaudio/docs/).

    Kun painike vapautetaan, virta pysäytetään ja suljetaan.

1. Lisää seuraava koodi tämän funktion loppuun:

    ```python
    wav_buffer = io.BytesIO()
    with wave.open(wav_buffer, 'wb') as wavefile:
        wavefile.setnchannels(1)
        wavefile.setsampwidth(audio.get_sample_size(pyaudio.paInt16))
        wavefile.setframerate(rate)
        wavefile.writeframes(b''.join(frames))
        wav_buffer.seek(0)

    return wav_buffer
    ```

    Tämä koodi luo binääripuskurin ja kirjoittaa kaikki tallennetut äänet siihen [WAV-tiedostona](https://wikipedia.org/wiki/WAV). Tämä on standarditapa kirjoittaa pakkaamatonta ääntä tiedostoon. Tämä puskurin sisältö palautetaan.

1. Lisää seuraava `play_audio`-funktio äänen toistamiseen:

    ```python
    def play_audio(buffer):
        stream = audio.open(format = pyaudio.paInt16,
                            rate = rate,
                            channels = 1,
                            output_device_index = speaker_card_number,
                            output = True)
    
        with wave.open(buffer, 'rb') as wf:
            data = wf.readframes(4096)
    
            while len(data) > 0:
                stream.write(data)
                data = wf.readframes(4096)
    
            stream.close()
    ```

    Tämä funktio avaa toisen äänen virran, tällä kertaa ulostulolle - äänen toistamiseen. Se käyttää samoja asetuksia kuin syöttövirta. Puskuri avataan WAV-tiedostona ja kirjoitetaan ulostulovirtaan 4096 tavun paloina, toistaen äänen. Virta suljetaan lopuksi.

1. Lisää seuraava koodi `capture_audio`-funktion alle silmukoimaan, kunnes painiketta painetaan. Kun painiketta painetaan, ääni tallennetaan ja toistetaan.

    ```python
    while True:
        while not button.is_pressed():
            time.sleep(.1)
        
        buffer = capture_audio()
        play_audio(buffer)
    ```

1. Suorita koodi. Paina painiketta ja puhu mikrofoniin. Vapauta painike, kun olet valmis, ja kuulet tallenteen.

    Saatat saada joitakin ALSA-virheitä, kun PyAudio-instanssi luodaan. Tämä johtuu Pi:n äänenlaitteiden konfiguraatiosta, joita sinulla ei ole. Voit ohittaa nämä virheet.

    ```output
    pi@raspberrypi:~/smart-timer $ python3 app.py 
    ALSA lib pcm.c:2565:(snd_pcm_open_noupdate) Unknown PCM cards.pcm.front
    ALSA lib pcm.c:2565:(snd_pcm_open_noupdate) Unknown PCM cards.pcm.rear
    ALSA lib pcm.c:2565:(snd_pcm_open_noupdate) Unknown PCM cards.pcm.center_lfe
    ALSA lib pcm.c:2565:(snd_pcm_open_noupdate) Unknown PCM cards.pcm.side
    ```

    Jos saat seuraavan virheen:

    ```output
    OSError: [Errno -9997] Invalid sample rate
    ```

    muuta `rate` joko arvoon 44100 tai 16000.

> 💁 Löydät tämän koodin [code-record/pi](../../../../../6-consumer/lessons/1-speech-recognition/code-record/pi) -kansiosta.

😀 Äänentallennusohjelmasi onnistui!

---

**Vastuuvapauslauseke**:  
Tämä asiakirja on käännetty käyttämällä tekoälypohjaista käännöspalvelua [Co-op Translator](https://github.com/Azure/co-op-translator). Vaikka pyrimme tarkkuuteen, huomioithan, että automaattiset käännökset voivat sisältää virheitä tai epätarkkuuksia. Alkuperäinen asiakirja sen alkuperäisellä kielellä tulisi pitää ensisijaisena lähteenä. Kriittisen tiedon osalta suositellaan ammattimaista ihmiskäännöstä. Emme ole vastuussa väärinkäsityksistä tai virhetulkinnoista, jotka johtuvat tämän käännöksen käytöstä.