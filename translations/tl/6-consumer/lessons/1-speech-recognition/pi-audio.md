<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "0ac0afcfb40cb5970ef4cb74f01c32e9",
  "translation_date": "2025-08-27T23:19:07+00:00",
  "source_file": "6-consumer/lessons/1-speech-recognition/pi-audio.md",
  "language_code": "tl"
}
-->
# Pagkuha ng Audio - Raspberry Pi

Sa bahaging ito ng aralin, magsusulat ka ng code upang makuha ang audio gamit ang iyong Raspberry Pi. Ang pagkuha ng audio ay kokontrolin ng isang button.

## Kagamitan

Kailangan ng Raspberry Pi ng isang button upang kontrolin ang pagkuha ng audio.

Ang button na gagamitin mo ay isang Grove button. Isa itong digital sensor na nagbubukas o nagsasara ng signal. Ang mga button na ito ay maaaring i-configure upang magpadala ng mataas na signal kapag pinindot, at mababa kapag hindi, o mababa kapag pinindot at mataas kapag hindi.

Kung gumagamit ka ng ReSpeaker 2-Mics Pi HAT bilang mikropono, hindi mo na kailangang mag-connect ng button dahil mayroon nang nakalagay na button sa hat na ito. Lumaktaw sa susunod na seksyon.

### Ikonekta ang Button

Ang button ay maaaring ikonekta sa Grove base hat.

#### Gawain - Ikonekta ang Button

![Isang Grove button](../../../../../translated_images/tl/grove-button.a70cfbb809a8563681003250cf5b06d68cdcc68624f9e2f493d5a534ae2da1e5.png)

1. Ipasok ang isang dulo ng Grove cable sa socket ng button module. Isa lang ang tamang paraan para maipasok ito.

1. Kapag naka-off ang Raspberry Pi, ikonekta ang kabilang dulo ng Grove cable sa digital socket na may markang **D5** sa Grove Base hat na nakakabit sa Pi. Ang socket na ito ay pangalawa mula sa kaliwa, sa hanay ng mga socket malapit sa GPIO pins.

![Ang Grove button na nakakonekta sa socket D5](../../../../../translated_images/tl/pi-button.c7a1a4f55943341ce1baf1057658e9a205804d4131d258e820c93f951df0abf3.png)

## Pagkuha ng Audio

Maaari kang kumuha ng audio mula sa mikropono gamit ang Python code.

### Gawain - Kumuha ng Audio

1. I-on ang Pi at hintaying mag-boot.

1. I-launch ang VS Code, direkta sa Pi o mag-connect gamit ang Remote SSH extension.

1. Ang PyAudio Pip package ay may mga function upang mag-record at mag-playback ng audio. Ang package na ito ay nangangailangan ng ilang audio libraries na kailangang i-install muna. Patakbuhin ang mga sumusunod na command sa terminal upang i-install ang mga ito:

    ```sh
    sudo apt update
    sudo apt install libportaudio0 libportaudio2 libportaudiocpp0 portaudio19-dev libasound2-plugins --yes 
    ```

1. I-install ang PyAudio Pip package.

    ```sh
    pip3 install pyaudio
    ```

1. Gumawa ng bagong folder na tinatawag na `smart-timer` at magdagdag ng file na tinatawag na `app.py` sa folder na ito.

1. Idagdag ang mga sumusunod na imports sa itaas ng file na ito:

    ```python
    import io
    import pyaudio
    import time
    import wave
    
    from grove.factory import Factory
    ```

    Ini-import nito ang `pyaudio` module, ilang standard na Python modules para sa paghawak ng wave files, at ang `grove.factory` module upang mag-import ng `Factory` para gumawa ng button class.

1. Sa ibaba nito, magdagdag ng code upang gumawa ng Grove button.

    Kung gumagamit ka ng ReSpeaker 2-Mics Pi HAT, gamitin ang sumusunod na code:

    ```python
    # The button on the ReSpeaker 2-Mics Pi HAT
    button = Factory.getButton("GPIO-LOW", 17)
    ```

    Gumagawa ito ng button sa port **D17**, ang port kung saan nakakonekta ang button sa ReSpeaker 2-Mics Pi HAT. Ang button na ito ay naka-set upang magpadala ng mababang signal kapag pinindot.

    Kung hindi ka gumagamit ng ReSpeaker 2-Mics Pi HAT, at gumagamit ng Grove button na nakakonekta sa base hat, gamitin ang code na ito:

    ```python
    button = Factory.getButton("GPIO-HIGH", 5)
    ```

    Gumagawa ito ng button sa port **D5** na naka-set upang magpadala ng mataas na signal kapag pinindot.

1. Sa ibaba nito, gumawa ng instance ng PyAudio class upang mag-handle ng audio:

    ```python
    audio = pyaudio.PyAudio()
    ```

1. Ideklara ang hardware card number para sa mikropono at speaker. Ito ang magiging numero ng card na nahanap mo sa pamamagitan ng pagpatakbo ng `arecord -l` at `aplay -l` kanina sa aralin.

    ```python
    microphone_card_number = <microphone card number>
    speaker_card_number = <speaker card number>
    ```

    Palitan ang `<microphone card number>` ng numero ng card ng iyong mikropono.

    Palitan ang `<speaker card number>` ng numero ng card ng iyong speaker, ang parehong numero na itinakda mo sa `alsa.conf` file.

1. Sa ibaba nito, ideklara ang sample rate na gagamitin para sa pagkuha at playback ng audio. Maaaring kailanganin mong baguhin ito depende sa hardware na ginagamit mo.

    ```python
    rate = 48000 #48KHz
    ```

    Kung makakakuha ka ng sample rate errors kapag pinatakbo ang code na ito, palitan ang value sa `44100` o `16000`. Mas mataas ang value, mas maganda ang kalidad ng tunog.

1. Sa ibaba nito, gumawa ng bagong function na tinatawag na `capture_audio`. Tatawagin ito upang kumuha ng audio mula sa mikropono:

    ```python
    def capture_audio():
    ```

1. Sa loob ng function na ito, idagdag ang sumusunod upang makuha ang audio:

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

    Ang code na ito ay nagbubukas ng audio input stream gamit ang PyAudio object. Ang stream na ito ay kukuha ng audio mula sa mikropono sa 16KHz, kinukuha ito sa buffers na may sukat na 4096 bytes.

    Ang code ay mag-loop habang ang Grove button ay pinindot, binabasa ang mga 4096 byte buffers sa isang array sa bawat pagkakataon.

    > 💁 Maaari kang magbasa pa tungkol sa mga options na ipinasa sa `open` method sa [PyAudio documentation](https://people.csail.mit.edu/hubert/pyaudio/docs/).

    Kapag binitiwan ang button, ang stream ay titigil at magsasara.

1. Idagdag ang sumusunod sa dulo ng function na ito:

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

    Ang code na ito ay gumagawa ng binary buffer, at isinusulat ang lahat ng nakuha na audio dito bilang isang [WAV file](https://wikipedia.org/wiki/WAV). Ito ay isang standard na paraan upang magsulat ng uncompressed audio sa isang file. Ang buffer na ito ay ibabalik.

1. Idagdag ang sumusunod na `play_audio` function upang i-playback ang audio buffer:

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

    Ang function na ito ay nagbubukas ng isa pang audio stream, sa pagkakataong ito para sa output - upang i-play ang audio. Ginagamit nito ang parehong settings tulad ng input stream. Ang buffer ay binubuksan bilang wave file at isinusulat sa output stream sa chunks na 4096 bytes, pinapatugtog ang audio. Ang stream ay magsasara pagkatapos.

1. Idagdag ang sumusunod na code sa ibaba ng `capture_audio` function upang mag-loop hanggang sa pinindot ang button. Kapag pinindot ang button, ang audio ay makukuha, pagkatapos ay ipapatugtog.

    ```python
    while True:
        while not button.is_pressed():
            time.sleep(.1)
        
        buffer = capture_audio()
        play_audio(buffer)
    ```

1. Patakbuhin ang code. Pindutin ang button at magsalita sa mikropono. Bitawan ang button kapag tapos ka na, at maririnig mo ang recording.

    Maaaring makakuha ka ng ilang ALSA errors kapag ginawa ang PyAudio instance. Ito ay dahil sa configuration sa Pi para sa mga audio devices na wala ka. Maaari mong balewalain ang mga error na ito.

    ```output
    pi@raspberrypi:~/smart-timer $ python3 app.py 
    ALSA lib pcm.c:2565:(snd_pcm_open_noupdate) Unknown PCM cards.pcm.front
    ALSA lib pcm.c:2565:(snd_pcm_open_noupdate) Unknown PCM cards.pcm.rear
    ALSA lib pcm.c:2565:(snd_pcm_open_noupdate) Unknown PCM cards.pcm.center_lfe
    ALSA lib pcm.c:2565:(snd_pcm_open_noupdate) Unknown PCM cards.pcm.side
    ```

    Kung makakakuha ka ng sumusunod na error:

    ```output
    OSError: [Errno -9997] Invalid sample rate
    ```

    palitan ang `rate` sa alinman sa 44100 o 16000.

> 💁 Maaari mong makita ang code na ito sa [code-record/pi](../../../../../6-consumer/lessons/1-speech-recognition/code-record/pi) folder.

😀 Tagumpay ang iyong audio recording program!

---

**Paunawa**:  
Ang dokumentong ito ay isinalin gamit ang AI translation service na [Co-op Translator](https://github.com/Azure/co-op-translator). Bagama't sinisikap naming maging tumpak, tandaan na ang mga awtomatikong pagsasalin ay maaaring maglaman ng mga pagkakamali o hindi pagkakatugma. Ang orihinal na dokumento sa kanyang katutubong wika ang dapat ituring na opisyal na sanggunian. Para sa mahalagang impormasyon, inirerekomenda ang propesyonal na pagsasalin ng tao. Hindi kami mananagot sa anumang hindi pagkakaunawaan o maling interpretasyon na maaaring magmula sa paggamit ng pagsasaling ito.