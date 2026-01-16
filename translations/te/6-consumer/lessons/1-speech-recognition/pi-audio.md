<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "0ac0afcfb40cb5970ef4cb74f01c32e9",
  "translation_date": "2026-01-07T03:17:03+00:00",
  "source_file": "6-consumer/lessons/1-speech-recognition/pi-audio.md",
  "language_code": "te"
}
-->
# ఆడియో క్యాప్చర్ - రాస్ప్బెర్రీ పై

పాఠం యొక్క ఈ భాగంలో, మీరు మీ రాస్ప్బెర్రీ పైపై ఆడియోను క్యాప్చర్ చేయడానికి కోడ్ రాస్తారు. ఆడియో క్యాప్చర్‌ను ఒక బటన్ ద్వారా నియంత్రించబడుతుంది.

## హార్డ్‌వేర్

రాస్ప్బెర్రీ పైకు ఆడియో క్యాప్చర్‌ను నియంత్రించేందుకు ఒక బటన్ అవసరం.

మీరు ఉపయోగించే బటన్ ఒక గ్రోవ్ బటన్. ఇది ఒక డిజిటల్ సెన్సార్, ఇది సిగ్నల్‌ను ఆన్ లేదా ఆఫ్ చేస్తుంది. ఈ బటన్లు బటన్ నొక్కినప్పుడు హై సిగ్నల్ పంపించడానికి మరియు నొక్కకపోయిందప్పుడు లో సిగ్నల్ పంపించడానికి, లేదా నొక్కినప్పుడు లో మరియు నొక్కకపోయిందప్పుడు హై గా ఉండే విధంగా కాన్ఫిగర్ చేయబడవచ్చు.

మీరు మైక్రోఫోన్‌గా ReSpeaker 2-Mics Pi HAT ఉపయోగిస్తుంటే, ఈ HATలో ఇప్పటికే ఒక బటన్ ఉండడంతో బటన్ కనెక్ట్ చేయడం అవసరం లేదు. తదుపరి విభాగానికి వెళ్లండి.

### బటన్ కనెక్ట్ చేయండి

బటన్‌ను గ్రోవ్ బేస్ HATకి కనెక్ట్ చేయవచ్చు.

#### టాస్క్ - బటన్ కనెక్ట్ చేయండి

![A grove button](../../../../../translated_images/te/grove-button.a70cfbb809a85636.png)

1. గ్రోవ్ కేబుల్ యొక్క ఒక చివరని బటన్ మాడ్యూల్ మీద ఉన్న సాకెట్‌లో ఎక్కించండి. ఇది ఒక దిశలోనే ప్రవేశిస్తుంది.

1. రాస్ప్బెర్రీ పైని పవర్ ఆఫ్ చేసినప్పుడు, గ్రోవ్ కేబుల్ యొక్క మరొక చివరని Piకి ఉన్న గ్రోవ్ బేస్ HATలోని డిజిటల్ సాకెట్ **D5** (GPIO పిన్ల పక్కన ఉన్న సాకెట్‌ల వరుసలో ఎడమ నుండి రెండవది)కి కనెక్ట్ చేయండి.

![The grove button connected to socket D5](../../../../../translated_images/te/pi-button.c7a1a4f55943341c.png)

## ఆడియో క్యాప్చర్ చేయండి

Python కోడ్ ఉపయోగించి మైక్రోఫోన్ నుండి ఆడియోని క్యాప్చర్ చేయవచ్చు.

### టాస్క్ - ఆడియో క్యాప్చర్ చేయండి

1. Pi ని పవర్ ఆన్ చేసి, బూట్ అయ్యేవరకు వేచి ఉండండి

1. VS Code ను ప్రారంభించండి, అది Pi పై నేరుగా కావచ్చు, లేదా Remote SSH విస్తరణ ద్వారా కనెక్ట్ కావచ్చు.

1. PyAudio Pip ప్యాకేజీ ఆడియో రికార్డ్ మరియు ప్లే బ్యాక్ చేయడానికి ఫంక్షన్లు కలిగి ఉంటుంది. ఈ ప్యాకేజీ కొన్ని ఆడియో లైబ్రెరీలపై ఆధారపడి ఉంటుంది, అవి ముందుగా ఇన్‌స్టాల్ చేయాలి. టెర్మినల్‌లో క్రింది ఆదేశాలను అమలు చేయండి:

    ```sh
    sudo apt update
    sudo apt install libportaudio0 libportaudio2 libportaudiocpp0 portaudio19-dev libasound2-plugins --yes 
    ```

1. PyAudio Pip ప్యాకేజీని ఇన్‌స్టాల్ చేయండి.

    ```sh
    pip3 install pyaudio
    ```

1. `smart-timer` అనే కొత్త ఫోల్డర్ సృష్టించి, ఆ ఫోల్డర్‌లో `app.py` ఫైలు జోడించండి.

1. ఈ ఫైల్ టాప్ లో క్రింది దిగుమతులను జోడించండి:

    ```python
    import io
    import pyaudio
    import time
    import wave
    
    from grove.factory import Factory
    ```

    ఇది `pyaudio` మాడ్యూల్ ని, wave ఫైళ్లను హ్యాండిల్ చేసే కొన్ని స్టాండర్డ్ Python మాడ్యూల్స్ ని, మరియు `grove.factory` మాడ్యూల్ నుండి బటన్ క్లాస్ సృష్టించడానికి `Factory`ని దిగుమతు చేస్తుంది.

1. దీని క్రింద గ్రోవ్ బటన్ సృష్టించడానికి కోడ్ జోడించండి.

    మీరు ReSpeaker 2-Mics Pi HAT ఉపయోగిస్తుంటే, క్రింది కోడ్ ఉపయోగించండి:

    ```python
    # రీస్పీకర్ 2-మైక్స్ పి హెచ్‌ఏటీపై బటన్
    button = Factory.getButton("GPIO-LOW", 17)
    ```

    ఇది బటన్ ని పోర్ట్ **D17**పై సృష్టిస్తుంది, ఇది ReSpeaker 2-Mics Pi HATలో బటన్ కనెక్ట్ అయిన పోర్ట్. ఈ బటన్ నొక్కినప్పుడు లో సిగ్నల్ పంపుతుంది.

    మీరు ReSpeaker 2-Mics Pi HAT ఉపయోగించకపోతే మరియు గ్రోవ్ బటన్‌ను బేస్ HATకి కనెక్ట్ చేస్తే, క్రింది కోడ్ ఉపయోగించండి.

    ```python
    button = Factory.getButton("GPIO-HIGH", 5)
    ```

    ఇది బటన్ ని పోర్ట్ **D5**పై సృష్టిస్తుంది, ఇది నొక్కినప్పుడు హై సిగ్నల్ పంపుతుంది.

1. దీని క్రింద PyAudio క్లాస్ యొక్క ఇనిస్టెన్స్ ను ఆడియో హ్యాండిల్ చేయడానికి సృష్టించండి:

    ```python
    audio = pyaudio.PyAudio()
    ```

1. మైక్రోఫోన్ మరియు స్పీకర్ యొక్క హార్డ్‌వేర్ కార్డ్ సంఖ్యను డిక్లేర్ చేయండి. ఇది ఈ పాఠంలో ముందుగా `arecord -l` మరియు `aplay -l` ఉపయోగించి మీరు కనుగొన్న కార్డ్ సంఖ్య ఉంటుంది.

    ```python
    microphone_card_number = <microphone card number>
    speaker_card_number = <speaker card number>
    ```

    `<microphone card number>` స్థానంలో మీ మైక్రోఫోన్ కార్డ్ సంఖ్యను ఉంచండి.

    `<speaker card number>` స్థానంలో మీరు `alsa.conf` ఫైల్ లో సెట్ చేసిన స్పీకర్ కార్డ్ సంఖ్యను ఉంచండి.

1. ఇది క్రింద ఆడియో క్యాప్చర్ మరియు ప్లేబ్యాక్‌కు ఉపయోగించడానికి శాంపిల్ రేట్‌ను డిక్లేర్ చేయండి. మీరు ఉపయోగించు హార్డ్‌వేర్ ఆధారంగా మీరు దీన్ని మార్చాల్సివచ్చు.

    ```python
    rate = 48000 #48కెహెర్జ్
    ```

    ఈ కోడ్ ని తర్వాత నడుపుతున్నప్పుడు శాంపిల్ రేట్ లో పొరపాట్లు వస్తే, ఈ విలువను `44100` లేదా `16000` గా మార్చండి. విలువ ఎక్కువైతే, శబ్దం నాణ్యత మెరుగైనది.

1. దీని క్రింద, `capture_audio` అనే కొత్త ఫంక్షన్ సృష్టించండి. ఇది మైక్రోఫోన్ నుండి ఆడియో క్యాప్చర్ చేయడానికి పిలవబడి ఉంటుంది:

    ```python
    def capture_audio():
    ```

1. ఈ ఫంక్షన్ లో క్రింది కోడ్ జోడించండి ఆడియో క్యాప్చర్ కొరకు:

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

    ఈ కోడ్ PyAudio వస్తువు ఉపయోగించి ఒక ఆడియో ఇన్‌పుట్ స్ట్రీమ్ తీసుకుపోతుంది. ఈ స్ట్రీమ్ 16KHz వద్ద మైక్రోఫోన్ నుండి ఆడియో క్యాప్చర్ చేస్తుంది, 4096 బైట్ల బఫర్ పరిమాణంలో.

    కోడ్ తర్వాత గ్రోవ్ బటన్ నొక్కబడినంతవరకు ఈ 4096 బైట్ల బఫర్లను చదివి అర్రేలో నిల్వ చేస్తూ లూప్ చేస్తుంది.

    > 💁 మీరు `open` పద్ధతికి ఇచ్చే ఎంపికల గురించి మరింత చదవవచ్చు [PyAudio డాక్యుమెంటేషన్](https://people.csail.mit.edu/hubert/pyaudio/docs/).

    బటన్ విడుదల అయితే, స్ట్రీమ్ ఆపబడుతుంది మరియు మూసివేయబడుతుంది.

1. ఈ ఫంక్షన్ చివర క్రింది కోడ్ జోడించండి:

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

    ఈ కోడ్ ఒక బైనరీ బఫర్ సృష్టించి, క్యాప్చర్ చేసిన అన్ని ఆడియోను [WAV ఫైల్](https://wikipedia.org/wiki/WAV) రూపంలో దీనిలో వ్రాస్తుంది. ఇది కంప్రెస్స్ కాని ఆడియోని ఫైల్‌గా రాయడానికి ఒక స్టాండర్డ్ విధానం. ఈ బఫర్ తిరిగి ఇవ్వబడుతుంది.

1. క్రింది `play_audio` ఫంక్షన్ ను ఆడియో బఫర్ ప్లేబ్యాక్ చేయడానికి జోడించండి:

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

    ఈ ఫంక్షన్ మరో ఆడియో స్ట్రీమ్ తెరుస్తుంది, ఈ సారి అవుట్పుట్ కోసం - ఆడియో ప్లే చేయడానికి. ఇది ఇన్‌పుట్ స్ట్రీమ్ వంటి సెట్టింగ్స్ ఉపయోగిస్తుంది. బఫర్ ఒక కదలిక గల WAV ఫైల్‌గా తీసుకొని, 4096 బైట్ల చంక్లలో అవుట్పుట్ స్ట్రీమ్‌కి వ్రాసి ఆడియో ప్లే చేస్తుంది. తర్వాత స్ట్రీమ్ మూసివేయబడుతుంది.

1. `capture_audio` ఫంక్షన్ క్రింద క్రింది కోడ్ జోడించండి, బటన్ నొక్కబడే వరకు లూప్ చేస్తుంది. బటన్ నొక్కితే, ఆడియో క్యాప్చర్ చేసి, ఆ తర్వాత ప్లే చేస్తుంది.

    ```python
    while True:
        while not button.is_pressed():
            time.sleep(.1)
        
        buffer = capture_audio()
        play_audio(buffer)
    ```

1. కోడ్ ను రన్ చేయండి. బటన్ నొక్కి, మైక్రోఫోన్ దగ్గర మాట్లాడండి. ముగిసాక బటన్ విడిచినప్పుడვე రికార్డింగ్ వినిపిస్తుంది.

    PyAudio ఇనిస్టెన్స్ సృష్టించినప్పుడు కొన్ని ALSA లోపాలు రావచ్చు. అవి మీ వద్ద లేని ఆడియో పరికరాల కోసం Pi పై కాన్ఫిగరేషన్ వల్ల ఉన్నాయి. ఈ లోపాలను మీరు పరిగణనలోకి తీసుకోవాల్సినది లేదు.

    ```output
    pi@raspberrypi:~/smart-timer $ python3 app.py 
    ALSA lib pcm.c:2565:(snd_pcm_open_noupdate) Unknown PCM cards.pcm.front
    ALSA lib pcm.c:2565:(snd_pcm_open_noupdate) Unknown PCM cards.pcm.rear
    ALSA lib pcm.c:2565:(snd_pcm_open_noupdate) Unknown PCM cards.pcm.center_lfe
    ALSA lib pcm.c:2565:(snd_pcm_open_noupdate) Unknown PCM cards.pcm.side
    ```

    మీరు క్రింది లోపాన్ని పొందితే:

    ```output
    OSError: [Errno -9997] Invalid sample rate
    ```

    `rate` ను 44100 లేదా 16000 కి మార్చండి.

> 💁 మీరు ఈ కోడ్‌ను [code-record/pi](../../../../../6-consumer/lessons/1-speech-recognition/code-record/pi) ఫోల్డర్‌లో కనుగొనవచ్చు.

😀 మీ ఆడియో రికార్డింగ్ ప్రోగ్రామ్ విజయవంతమైంది!

---

<!-- CO-OP TRANSLATOR DISCLAIMER START -->
**డిస్క్లెయిమర్**:  
ఈ పత్రం AI అనువాద సేవ [Co-op Translator](https://github.com/Azure/co-op-translator) ఉపయోగించి అనువదించబడినది. మేము సరిగ్గా అనువదించాలని ప్రయత్నించినప్పటికీ, స్వయంచాలక అనువాదాలలో పొరపాట్లు లేదా తప్పుడు వివరాలు ఉండవచ్చు అని దయచేసి గమనించండి. మూల పత్రం native భాషలోని అధికారిక మూలంగా పరిగణించాలి. ముఖ్యమైన సమాచారానికి, నిపుణుల చేత అనువాదం వసూలు చేయుట మంచిది. ఈ అనువాదం ఉపయోగం వలన ఏర్పడిన ఏవైనా సంఘర్షణలు లేదా తప్పుదోవలకు మేము బాధ్యులు కాదు.
<!-- CO-OP TRANSLATOR DISCLAIMER END -->