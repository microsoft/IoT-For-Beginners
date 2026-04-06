# ऑडिओ कॅप्चर करा - रास्पबेरी पाय

या धड्याच्या भागात, तुम्ही रास्पबेरी पायवर ऑडिओ कॅप्चर करण्यासाठी कोड लिहाल. ऑडिओ कॅप्चर एका बटणाद्वारे नियंत्रित केले जाईल.

## हार्डवेअर

रास्पबेरी पायला ऑडिओ कॅप्चर नियंत्रित करण्यासाठी बटणाची आवश्यकता आहे.

तुम्ही वापरणारे बटण हे ग्रोव्ह बटण आहे. हे एक डिजिटल सेन्सर आहे जो सिग्नल चालू किंवा बंद करतो. हे बटणे कॉन्फिगर केली जाऊ शकतात जेणेकरून बटण दाबल्यावर उच्च सिग्नल पाठवतात आणि न दाबल्यावर कमी सिग्नल पाठवतात, किंवा दाबल्यावर कमी आणि न दाबल्यावर उच्च सिग्नल पाठवतात.

जर तुम्ही मायक्रोफोन म्हणून ReSpeaker 2-Mics Pi HAT वापरत असाल, तर बटण जोडण्याची गरज नाही कारण या HAT मध्ये आधीच एक बटण बसवलेले आहे. पुढील विभागाकडे जा.

### बटण जोडा

बटण ग्रोव्ह बेस हॅटला जोडले जाऊ शकते.

#### कार्य - बटण जोडा

![ग्रोव्ह बटण](../../../../../translated_images/mr/grove-button.a70cfbb809a85636.webp)

1. ग्रोव्ह केबलचा एक टोक बटण मॉड्यूलवरील सॉकेटमध्ये घाला. हे फक्त एका दिशेने जाईल.

1. रास्पबेरी पाय बंद असताना, ग्रोव्ह केबलचा दुसरा टोक ग्रोव्ह बेस हॅटवरील **D5** म्हणून चिन्हांकित डिजिटल सॉकेटमध्ये जोडा. हे सॉकेट GPIO पिनच्या शेजारी असलेल्या सॉकेटच्या रांगेतील डावीकडून दुसरे आहे.

![ग्रोव्ह बटण D5 सॉकेटला जोडलेले](../../../../../translated_images/mr/pi-button.c7a1a4f55943341c.webp)

## ऑडिओ कॅप्चर करा

तुम्ही मायक्रोफोनमधून ऑडिओ Python कोड वापरून कॅप्चर करू शकता.

### कार्य - ऑडिओ कॅप्चर करा

1. पाय चालू करा आणि बूट होईपर्यंत थांबा.

1. VS Code सुरू करा, थेट पायवर किंवा Remote SSH विस्ताराद्वारे कनेक्ट करा.

1. PyAudio Pip पॅकेजमध्ये ऑडिओ रेकॉर्ड आणि प्लेबॅक करण्यासाठी फंक्शन्स आहेत. या पॅकेजला काही ऑडिओ लायब्ररींची आवश्यकता आहे जी आधी स्थापित करणे आवश्यक आहे. टर्मिनलमध्ये खालील कमांड चालवा:

    ```sh
    sudo apt update
    sudo apt install libportaudio0 libportaudio2 libportaudiocpp0 portaudio19-dev libasound2-plugins --yes 
    ```

1. PyAudio Pip पॅकेज स्थापित करा.

    ```sh
    pip3 install pyaudio
    ```

1. `smart-timer` नावाचा नवीन फोल्डर तयार करा आणि या फोल्डरमध्ये `app.py` नावाची फाइल जोडा.

1. या फाइलच्या शीर्षस्थानी खालील आयात जोडा:

    ```python
    import io
    import pyaudio
    import time
    import wave
    
    from grove.factory import Factory
    ```

    हे `pyaudio` मॉड्यूल, वेव्ह फाइल्स हाताळण्यासाठी काही स्टँडर्ड Python मॉड्यूल्स आणि `grove.factory` मॉड्यूल आयात करते जे बटण वर्ग तयार करण्यासाठी `Factory` आयात करते.

1. याखाली, ग्रोव्ह बटण तयार करण्यासाठी कोड जोडा.

    जर तुम्ही ReSpeaker 2-Mics Pi HAT वापरत असाल, तर खालील कोड वापरा:

    ```python
    # The button on the ReSpeaker 2-Mics Pi HAT
    button = Factory.getButton("GPIO-LOW", 17)
    ```

    हे **D17** पोर्टवर बटण तयार करते, जो ReSpeaker 2-Mics Pi HAT वर बटण जोडलेला पोर्ट आहे. हे बटण दाबल्यावर कमी सिग्नल पाठवण्यासाठी सेट केले आहे.

    जर तुम्ही ReSpeaker 2-Mics Pi HAT वापरत नसाल आणि ग्रोव्ह बटण बेस हॅटला जोडले असेल, तर हा कोड वापरा.

    ```python
    button = Factory.getButton("GPIO-HIGH", 5)
    ```

    हे **D5** पोर्टवर बटण तयार करते जे दाबल्यावर उच्च सिग्नल पाठवण्यासाठी सेट केले आहे.

1. याखाली, ऑडिओ हाताळण्यासाठी PyAudio वर्गाची एक उदाहरण तयार करा:

    ```python
    audio = pyaudio.PyAudio()
    ```

1. मायक्रोफोन आणि स्पीकरसाठी हार्डवेअर कार्ड क्रमांक घोषित करा. हा क्रमांक तुम्ही या धड्याच्या आधी `arecord -l` आणि `aplay -l` चालवून शोधला असेल.

    ```python
    microphone_card_number = <microphone card number>
    speaker_card_number = <speaker card number>
    ```

    `<microphone card number>` च्या जागी तुमच्या मायक्रोफोन कार्डचा क्रमांक ठेवा.

    `<speaker card number>` च्या जागी तुमच्या स्पीकर कार्डचा क्रमांक ठेवा, जो तुम्ही `alsa.conf` फाइलमध्ये सेट केला होता.

1. याखाली, ऑडिओ कॅप्चर आणि प्लेबॅकसाठी वापरण्यासाठी नमुना दर घोषित करा. तुम्ही वापरत असलेल्या हार्डवेअरनुसार तुम्हाला हे बदलावे लागेल.

    ```python
    rate = 48000 #48KHz
    ```

    जर तुम्हाला नंतर हा कोड चालवताना नमुना दर त्रुटी मिळाल्या, तर ही किंमत `44100` किंवा `16000` वर बदला. किंमत जास्त असेल, तर आवाजाची गुणवत्ता चांगली असेल.

1. याखाली, `capture_audio` नावाची नवीन फंक्शन तयार करा. हे मायक्रोफोनमधून ऑडिओ कॅप्चर करण्यासाठी कॉल केले जाईल:

    ```python
    def capture_audio():
    ```

1. या फंक्शनमध्ये, ऑडिओ कॅप्चर करण्यासाठी खालील कोड जोडा:

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

    हा कोड PyAudio ऑब्जेक्ट वापरून ऑडिओ इनपुट स्ट्रीम उघडतो. हा स्ट्रीम मायक्रोफोनमधून 16KHz वर ऑडिओ कॅप्चर करतो, 4096 बाइट्सच्या बफर्समध्ये कॅप्चर करतो.

    कोड नंतर ग्रोव्ह बटण दाबलेले असताना लूप करतो, प्रत्येक वेळी 4096 बाइट्सच्या बफर्स एका अ‍ॅरेमध्ये वाचतो.

    > 💁 तुम्ही `open` पद्धतीला दिलेल्या पर्यायांबद्दल अधिक वाचू शकता [PyAudio दस्तऐवज](https://people.csail.mit.edu/hubert/pyaudio/docs/) मध्ये.

    एकदा बटण सोडले की, स्ट्रीम थांबवला जातो आणि बंद केला जातो.

1. या फंक्शनच्या शेवटी खालील कोड जोडा:

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

    हा कोड एक बायनरी बफर तयार करतो आणि सर्व कॅप्चर केलेला ऑडिओ [WAV फाइल](https://wikipedia.org/wiki/WAV) म्हणून लिहितो. ही फाइल न संकुचित ऑडिओ लिहिण्याचा एक मानक मार्ग आहे. हा बफर नंतर परत केला जातो.

1. ऑडिओ बफर प्लेबॅक करण्यासाठी खालील `play_audio` फंक्शन जोडा:

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

    हे फंक्शन दुसरा ऑडिओ स्ट्रीम उघडते, यावेळी आउटपुटसाठी - ऑडिओ प्ले करण्यासाठी. हे इनपुट स्ट्रीमसारखेच सेटिंग्ज वापरते. बफर वेव्ह फाइल म्हणून उघडला जातो आणि 4096 बाइट्सच्या तुकड्यांमध्ये आउटपुट स्ट्रीममध्ये लिहिला जातो, ऑडिओ प्ले करतो. नंतर स्ट्रीम बंद केला जातो.

1. `capture_audio` फंक्शनखाली खालील कोड जोडा जो बटण दाबेपर्यंत लूप करतो. एकदा बटण दाबले की, ऑडिओ कॅप्चर केला जातो आणि नंतर प्ले केला जातो.

    ```python
    while True:
        while not button.is_pressed():
            time.sleep(.1)
        
        buffer = capture_audio()
        play_audio(buffer)
    ```

1. कोड चालवा. बटण दाबा आणि मायक्रोफोनमध्ये बोला. तुम्ही पूर्ण झाल्यावर बटण सोडा आणि तुम्हाला रेकॉर्डिंग ऐकू येईल.

    PyAudio उदाहरण तयार करताना तुम्हाला काही ALSA त्रुटी मिळू शकतात. हे तुमच्याकडे नसलेल्या ऑडिओ डिव्हाइससाठी पायवरील कॉन्फिगरेशनमुळे आहे. तुम्ही या त्रुटी दुर्लक्षित करू शकता.

    ```output
    pi@raspberrypi:~/smart-timer $ python3 app.py 
    ALSA lib pcm.c:2565:(snd_pcm_open_noupdate) Unknown PCM cards.pcm.front
    ALSA lib pcm.c:2565:(snd_pcm_open_noupdate) Unknown PCM cards.pcm.rear
    ALSA lib pcm.c:2565:(snd_pcm_open_noupdate) Unknown PCM cards.pcm.center_lfe
    ALSA lib pcm.c:2565:(snd_pcm_open_noupdate) Unknown PCM cards.pcm.side
    ```

    जर तुम्हाला खालील त्रुटी मिळाली:

    ```output
    OSError: [Errno -9997] Invalid sample rate
    ```

    तर `rate` `44100` किंवा `16000` वर बदला.

> 💁 तुम्ही हा कोड [code-record/pi](../../../../../6-consumer/lessons/1-speech-recognition/code-record/pi) फोल्डरमध्ये शोधू शकता.

😀 तुमचा ऑडिओ रेकॉर्डिंग प्रोग्राम यशस्वी झाला!

---

**अस्वीकरण**:  
हा दस्तऐवज AI भाषांतर सेवा [Co-op Translator](https://github.com/Azure/co-op-translator) वापरून भाषांतरित करण्यात आला आहे. आम्ही अचूकतेसाठी प्रयत्नशील असलो तरी कृपया लक्षात ठेवा की स्वयंचलित भाषांतरांमध्ये त्रुटी किंवा अचूकतेचा अभाव असू शकतो. मूळ भाषेतील दस्तऐवज हा अधिकृत स्रोत मानला जावा. महत्त्वाच्या माहितीसाठी व्यावसायिक मानवी भाषांतराची शिफारस केली जाते. या भाषांतराचा वापर करून निर्माण होणाऱ्या कोणत्याही गैरसमज किंवा चुकीच्या अर्थासाठी आम्ही जबाबदार राहणार नाही.