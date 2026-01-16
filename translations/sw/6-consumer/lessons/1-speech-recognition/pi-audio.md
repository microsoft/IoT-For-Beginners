<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "0ac0afcfb40cb5970ef4cb74f01c32e9",
  "translation_date": "2025-08-27T21:19:48+00:00",
  "source_file": "6-consumer/lessons/1-speech-recognition/pi-audio.md",
  "language_code": "sw"
}
-->
# Kurekodi sauti - Raspberry Pi

Katika sehemu hii ya somo, utaandika msimbo wa kurekodi sauti kwenye Raspberry Pi yako. Kurekodi sauti kutadhibitiwa na kitufe.

## Vifaa

Raspberry Pi inahitaji kitufe cha kudhibiti kurekodi sauti.

Kitufe utakachotumia ni kitufe cha Grove. Hiki ni kihisi cha kidijitali kinachowasha au kuzima ishara. Vifungo hivi vinaweza kusanidiwa kutuma ishara ya juu wakati kitufe kinapobanwa, na ya chini wakati hakibaniwi, au ya chini wakati kinabanwa na ya juu wakati hakibaniwi.

Ikiwa unatumia ReSpeaker 2-Mics Pi HAT kama kipaza sauti, basi hakuna haja ya kuunganisha kitufe kwani HAT hii tayari ina kitufe kilichowekwa. Ruka hadi sehemu inayofuata.

### Unganisha kitufe

Kitufe kinaweza kuunganishwa kwenye Grove base hat.

#### Kazi - unganisha kitufe

![Kitufe cha Grove](../../../../../translated_images/sw/grove-button.a70cfbb809a8563681003250cf5b06d68cdcc68624f9e2f493d5a534ae2da1e5.png)

1. Ingiza mwisho mmoja wa kebo ya Grove kwenye soketi ya moduli ya kitufe. Itaingia kwa njia moja tu.

1. Ukiwa na Raspberry Pi imezimwa, unganisha mwisho mwingine wa kebo ya Grove kwenye soketi ya kidijitali iliyoandikwa **D5** kwenye Grove Base hat iliyounganishwa na Pi. Soketi hii ni ya pili kutoka kushoto, kwenye safu ya soketi karibu na pini za GPIO.

![Kitufe cha Grove kimeunganishwa kwenye soketi D5](../../../../../translated_images/sw/pi-button.c7a1a4f55943341ce1baf1057658e9a205804d4131d258e820c93f951df0abf3.png)

## Kurekodi sauti

Unaweza kurekodi sauti kutoka kwa kipaza sauti kwa kutumia msimbo wa Python.

### Kazi - kurekodi sauti

1. Washa Pi na subiri ianze.

1. Fungua VS Code, moja kwa moja kwenye Pi, au unganisha kupitia kiendelezi cha Remote SSH.

1. Kipeto cha PyAudio Pip kina kazi za kurekodi na kucheza sauti. Kipeto hiki kinategemea baadhi ya maktaba za sauti ambazo zinahitaji kusakinishwa kwanza. Endesha amri zifuatazo kwenye terminal ili kusakinisha hizi:

    ```sh
    sudo apt update
    sudo apt install libportaudio0 libportaudio2 libportaudiocpp0 portaudio19-dev libasound2-plugins --yes 
    ```

1. Sakinisha kipeto cha PyAudio Pip.

    ```sh
    pip3 install pyaudio
    ```

1. Unda folda mpya inayoitwa `smart-timer` na ongeza faili inayoitwa `app.py` kwenye folda hii.

1. Ongeza uingizaji ufuatao juu ya faili hii:

    ```python
    import io
    import pyaudio
    import time
    import wave
    
    from grove.factory import Factory
    ```

    Hii inaingiza moduli ya `pyaudio`, baadhi ya moduli za kawaida za Python za kushughulikia faili za mawimbi, na moduli ya `grove.factory` kuingiza `Factory` ya kuunda darasa la kitufe.

1. Chini ya hii, ongeza msimbo wa kuunda kitufe cha Grove.

    Ikiwa unatumia ReSpeaker 2-Mics Pi HAT, tumia msimbo ufuatao:

    ```python
    # The button on the ReSpeaker 2-Mics Pi HAT
    button = Factory.getButton("GPIO-LOW", 17)
    ```

    Hii inaunda kitufe kwenye bandari **D17**, bandari ambayo kitufe kwenye ReSpeaker 2-Mics Pi HAT kimeunganishwa. Kitufe hiki kimewekwa kutuma ishara ya chini wakati kinabanwa.

    Ikiwa hutumii ReSpeaker 2-Mics Pi HAT, na unatumia kitufe cha Grove kilichounganishwa kwenye base hat, tumia msimbo huu.

    ```python
    button = Factory.getButton("GPIO-HIGH", 5)
    ```

    Hii inaunda kitufe kwenye bandari **D5** ambacho kimewekwa kutuma ishara ya juu wakati kinabanwa.

1. Chini ya hii, unda mfano wa darasa la PyAudio kushughulikia sauti:

    ```python
    audio = pyaudio.PyAudio()
    ```

1. Tangaza namba ya kadi ya vifaa vya kipaza sauti na spika. Hii itakuwa namba ya kadi uliyopata kwa kuendesha `arecord -l` na `aplay -l` mapema katika somo hili.

    ```python
    microphone_card_number = <microphone card number>
    speaker_card_number = <speaker card number>
    ```

    Badilisha `<microphone card number>` na namba ya kadi ya kipaza sauti chako.

    Badilisha `<speaker card number>` na namba ya kadi ya spika zako, namba ile ile uliyoweka kwenye faili ya `alsa.conf`.

1. Chini ya hii, tangaza kiwango cha sampuli cha kutumia kwa kurekodi na kucheza sauti. Unaweza kuhitaji kubadilisha hii kulingana na vifaa unavyotumia.

    ```python
    rate = 48000 #48KHz
    ```

    Ikiwa unapata makosa ya kiwango cha sampuli wakati wa kuendesha msimbo huu baadaye, badilisha thamani hii kuwa `44100` au `16000`. Thamani ya juu zaidi, ubora wa sauti ni bora zaidi.

1. Chini ya hii, unda kazi mpya inayoitwa `capture_audio`. Hii itaitwa kurekodi sauti kutoka kwa kipaza sauti:

    ```python
    def capture_audio():
    ```

1. Ndani ya kazi hii, ongeza yafuatayo ili kurekodi sauti:

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

    Msimbo huu unafungua mkondo wa sauti wa kuingiza kwa kutumia kitu cha PyAudio. Mkondo huu utarekodi sauti kutoka kwa kipaza sauti kwa 16KHz, ukirekodi katika buffers za ukubwa wa byte 4096.

    Msimbo kisha unazunguka wakati kitufe cha Grove kinabanwa, ukisoma buffers hizi za byte 4096 kwenye safu kila wakati.

    > 💁 Unaweza kusoma zaidi kuhusu chaguo zinazopitishwa kwa njia ya `open` katika [hati za PyAudio](https://people.csail.mit.edu/hubert/pyaudio/docs/).

    Mara kitufe kinapoachiliwa, mkondo unazimwa na kufungwa.

1. Ongeza yafuatayo mwishoni mwa kazi hii:

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

    Msimbo huu unaunda buffer ya binary, na kuandika sauti yote iliyorekodiwa ndani yake kama [faili ya WAV](https://wikipedia.org/wiki/WAV). Hii ni njia ya kawaida ya kuandika sauti isiyobanwa kwenye faili. Buffer hii kisha inarejeshwa.

1. Ongeza kazi ifuatayo ya `play_audio` ili kucheza buffer ya sauti:

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

    Kazi hii inafungua mkondo mwingine wa sauti, wakati huu kwa ajili ya kutoa - kucheza sauti. Inatumia mipangilio sawa na mkondo wa kuingiza. Buffer kisha inafunguliwa kama faili ya mawimbi na kuandikwa kwenye mkondo wa kutoa katika vipande vya byte 4096, ikicheza sauti. Mkondo kisha unafungwa.

1. Ongeza msimbo ufuatao chini ya kazi ya `capture_audio` ili kuzunguka hadi kitufe kinabanwa. Mara kitufe kinapobanwa, sauti inarekodiwa, kisha inachezwa.

    ```python
    while True:
        while not button.is_pressed():
            time.sleep(.1)
        
        buffer = capture_audio()
        play_audio(buffer)
    ```

1. Endesha msimbo. Bana kitufe na zungumza kwenye kipaza sauti. Achilia kitufe unapomaliza, na utasikia rekodi.

    Unaweza kupata baadhi ya makosa ya ALSA wakati kitu cha PyAudio kinaundwa. Hii ni kutokana na usanidi kwenye Pi kwa vifaa vya sauti ambavyo huna. Unaweza kupuuza makosa haya.

    ```output
    pi@raspberrypi:~/smart-timer $ python3 app.py 
    ALSA lib pcm.c:2565:(snd_pcm_open_noupdate) Unknown PCM cards.pcm.front
    ALSA lib pcm.c:2565:(snd_pcm_open_noupdate) Unknown PCM cards.pcm.rear
    ALSA lib pcm.c:2565:(snd_pcm_open_noupdate) Unknown PCM cards.pcm.center_lfe
    ALSA lib pcm.c:2565:(snd_pcm_open_noupdate) Unknown PCM cards.pcm.side
    ```

    Ikiwa unapata kosa lifuatalo:

    ```output
    OSError: [Errno -9997] Invalid sample rate
    ```

    basi badilisha `rate` kuwa aidha 44100 au 16000.

> 💁 Unaweza kupata msimbo huu katika folda ya [code-record/pi](../../../../../6-consumer/lessons/1-speech-recognition/code-record/pi).

😀 Programu yako ya kurekodi sauti imefanikiwa!

---

**Kanusho**:  
Hati hii imetafsiriwa kwa kutumia huduma ya kutafsiri ya AI [Co-op Translator](https://github.com/Azure/co-op-translator). Ingawa tunajitahidi kuhakikisha usahihi, tafadhali fahamu kuwa tafsiri za kiotomatiki zinaweza kuwa na makosa au kutokuwa sahihi. Hati ya asili katika lugha yake ya awali inapaswa kuzingatiwa kama chanzo cha mamlaka. Kwa taarifa muhimu, tafsiri ya kitaalamu ya binadamu inapendekezwa. Hatutawajibika kwa kutoelewana au tafsiri zisizo sahihi zinazotokana na matumizi ya tafsiri hii.