# अडियो क्याप्चर गर्नुहोस् - रास्पबेरी पाई

यस पाठको यस भागमा, तपाईंले रास्पबेरी पाईमा अडियो क्याप्चर गर्न कोड लेख्नुहुनेछ। अडियो क्याप्चर बटनद्वारा नियन्त्रण गरिनेछ।

## हार्डवेयर

रास्पबेरी पाईलाई अडियो क्याप्चर नियन्त्रण गर्न बटन आवश्यक छ।

तपाईंले प्रयोग गर्ने बटन Grove बटन हो। यो डिजिटल सेन्सर हो जसले सिग्नललाई अन वा अफ गर्छ। यी बटनहरूलाई बटन थिच्दा उच्च सिग्नल पठाउन र नथिच्दा कम सिग्नल पठाउन, वा थिच्दा कम र नथिच्दा उच्च सिग्नल पठाउन कन्फिगर गर्न सकिन्छ।

यदि तपाईं माइक्रोफोनको रूपमा ReSpeaker 2-Mics Pi HAT प्रयोग गर्दै हुनुहुन्छ भने, बटन जडान गर्न आवश्यक छैन किनभने यस HAT मा पहिले नै बटन फिट गरिएको छ। अर्को खण्डमा जानुहोस्।

### बटन जडान गर्नुहोस्

बटन Grove बेस HAT मा जडान गर्न सकिन्छ।

#### कार्य - बटन जडान गर्नुहोस्

![Grove बटन](../../../../../translated_images/ne/grove-button.a70cfbb809a85636.webp)

1. Grove केबलको एक छेउ बटन मोड्युलको सकेटमा हाल्नुहोस्। यो केवल एक तरिकाले मात्र जडान गर्न सकिन्छ।

1. रास्पबेरी पाई बन्द अवस्थामा, Grove केबलको अर्को छेउलाई Grove बेस HAT मा GPIO पिनको छेउमा रहेको सकेटको पंक्तिमा **D5** मार्क गरिएको डिजिटल सकेटमा जडान गर्नुहोस्। यो सकेट बाँया तर्फबाट दोस्रो हो।

![D5 सकेटमा जडान गरिएको Grove बटन](../../../../../translated_images/ne/pi-button.c7a1a4f55943341c.webp)

## अडियो क्याप्चर गर्नुहोस्

तपाईं माइक्रोफोनबाट Python कोड प्रयोग गरेर अडियो क्याप्चर गर्न सक्नुहुन्छ।

### कार्य - अडियो क्याप्चर गर्नुहोस्

1. पाईलाई पावर दिनुहोस् र बुट हुने समय पर्खनुहोस्।

1. VS Code सुरु गर्नुहोस्, चाहे पाईमा सिधै वा Remote SSH एक्सटेन्सनमार्फत जडान गरेर।

1. PyAudio Pip प्याकेजमा अडियो रेकर्ड र प्लेब्याक गर्ने फङ्सनहरू छन्। यो प्याकेजले केही अडियो लाइब्रेरीहरूमा निर्भर गर्दछ जसलाई पहिले इन्स्टल गर्न आवश्यक छ। यी कमाण्डहरू टर्मिनलमा चलाउनुहोस्:

    ```sh
    sudo apt update
    sudo apt install libportaudio0 libportaudio2 libportaudiocpp0 portaudio19-dev libasound2-plugins --yes 
    ```

1. PyAudio Pip प्याकेज इन्स्टल गर्नुहोस्।

    ```sh
    pip3 install pyaudio
    ```

1. `smart-timer` नामको नयाँ फोल्डर बनाउनुहोस् र यस फोल्डरमा `app.py` नामको फाइल थप्नुहोस्।

1. यस फाइलको माथि निम्न इम्पोर्टहरू थप्नुहोस्:

    ```python
    import io
    import pyaudio
    import time
    import wave
    
    from grove.factory import Factory
    ```

    यसले `pyaudio` मोड्युल, wave फाइलहरू ह्यान्डल गर्नका लागि केही स्ट्यान्डर्ड Python मोड्युलहरू, र `grove.factory` मोड्युललाई `Factory` इम्पोर्ट गर्नका लागि इम्पोर्ट गर्दछ।

1. यसपछि, Grove बटन बनाउन कोड थप्नुहोस्।

    यदि तपाईं ReSpeaker 2-Mics Pi HAT प्रयोग गर्दै हुनुहुन्छ भने, निम्न कोड प्रयोग गर्नुहोस्:

    ```python
    # The button on the ReSpeaker 2-Mics Pi HAT
    button = Factory.getButton("GPIO-LOW", 17)
    ```

    यसले **D17** पोर्टमा बटन बनाउँछ, जुन पोर्टमा ReSpeaker 2-Mics Pi HAT मा बटन जडान गरिएको छ। यो बटन थिच्दा कम सिग्नल पठाउन सेट गरिएको छ।

    यदि तपाईं ReSpeaker 2-Mics Pi HAT प्रयोग गर्दै हुनुहुन्न र Grove बटन बेस HAT मा जडान गर्दै हुनुहुन्छ भने, यो कोड प्रयोग गर्नुहोस्।

    ```python
    button = Factory.getButton("GPIO-HIGH", 5)
    ```

    यसले **D5** पोर्टमा बटन बनाउँछ जुन थिच्दा उच्च सिग्नल पठाउन सेट गरिएको छ।

1. यसपछि, अडियो ह्यान्डल गर्न PyAudio क्लासको एउटा इन्स्टेन्स बनाउनुहोस्:

    ```python
    audio = pyaudio.PyAudio()
    ```

1. माइक्रोफोन र स्पिकरको लागि हार्डवेयर कार्ड नम्बर घोषणा गर्नुहोस्। यो कार्ड नम्बर तपाईंले यस पाठको पहिले `arecord -l` र `aplay -l` चलाएर पत्ता लगाउनुभएको नम्बर हुनेछ।

    ```python
    microphone_card_number = <microphone card number>
    speaker_card_number = <speaker card number>
    ```

    `<microphone card number>` लाई तपाईंको माइक्रोफोनको कार्ड नम्बरले प्रतिस्थापन गर्नुहोस्।

    `<speaker card number>` लाई तपाईंको स्पिकरको कार्ड नम्बरले प्रतिस्थापन गर्नुहोस्, जुन तपाईंले `alsa.conf` फाइलमा सेट गर्नुभएको नम्बर हो।

1. यसपछि, अडियो क्याप्चर र प्लेब्याकको लागि प्रयोग गर्न नमूना दर घोषणा गर्नुहोस्। तपाईंले प्रयोग गरिरहेको हार्डवेयरको आधारमा यो परिवर्तन गर्न आवश्यक हुन सक्छ।

    ```python
    rate = 48000 #48KHz
    ```

    यदि तपाईंले पछि यो कोड चलाउँदा नमूना दर त्रुटिहरू पाउनुभयो भने, यो मानलाई `44100` वा `16000` मा परिवर्तन गर्नुहोस्। मान उच्च भएमा, अडियोको गुणस्तर राम्रो हुन्छ।

1. यसपछि, `capture_audio` नामको नयाँ फङ्सन बनाउनुहोस्। यो माइक्रोफोनबाट अडियो क्याप्चर गर्न बोलाइनेछ:

    ```python
    def capture_audio():
    ```

1. यस फङ्सनभित्र, अडियो क्याप्चर गर्न निम्न थप्नुहोस्:

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

    यो कोडले PyAudio वस्तु प्रयोग गरेर अडियो इनपुट स्ट्रिम खोल्छ। यो स्ट्रिमले माइक्रोफोनबाट 16KHz मा अडियो क्याप्चर गर्छ, 4096 बाइटको साइजको बफरहरूमा क्याप्चर गर्दै।

    कोडले Grove बटन थिचिएको बेला लुप गर्छ, प्रत्येक पटक यी 4096 बाइट बफरहरूलाई एरेमा पढ्छ।

    > 💁 तपाईं `open` मेथडमा पास गरिएका अप्सनहरूको बारेमा [PyAudio डकुमेन्टेशन](https://people.csail.mit.edu/hubert/pyaudio/docs/) मा थप पढ्न सक्नुहुन्छ।

    बटन रिलिज भएपछि, स्ट्रिम रोकिन्छ र बन्द गरिन्छ।

1. यस फङ्सनको अन्त्यमा निम्न थप्नुहोस्:

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

    यो कोडले बाइनरी बफर बनाउँछ, र क्याप्चर गरिएको सबै अडियोलाई [WAV फाइल](https://wikipedia.org/wiki/WAV) को रूपमा लेख्छ। यो फाइलमा अनकम्प्रेस्ड अडियो लेख्ने मानक तरिका हो। यो बफर फर्काइन्छ।

1. अडियो बफर प्लेब्याक गर्न `play_audio` फङ्सन थप्नुहोस्:

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

    यो फङ्सनले अर्को अडियो स्ट्रिम खोल्छ, यस पटक आउटपुटका लागि - अडियो प्ले गर्न। यसले इनपुट स्ट्रिमसँग समान सेटिङहरू प्रयोग गर्छ। बफरलाई wave फाइलको रूपमा खोलिन्छ र 4096 बाइटको चङ्कमा आउटपुट स्ट्रिममा लेखिन्छ, अडियो प्ले गर्दै। स्ट्रिम बन्द गरिन्छ।

1. `capture_audio` फङ्सनको तल निम्न कोड थप्नुहोस् जसले बटन थिचिएको बेला लुप गर्छ। बटन थिचिएपछि, अडियो क्याप्चर हुन्छ र प्ले गरिन्छ।

    ```python
    while True:
        while not button.is_pressed():
            time.sleep(.1)
        
        buffer = capture_audio()
        play_audio(buffer)
    ```

1. कोड चलाउनुहोस्। बटन थिच्नुहोस् र माइक्रोफोनमा बोल्नुहोस्। बटन रिलिज गर्नुहोस् जब तपाईं सक्नुहुन्छ, र तपाईंले रेकर्डिङ सुन्नुहुनेछ।

    तपाईंले PyAudio इन्स्टेन्स बनाउँदा केही ALSA त्रुटिहरू पाउन सक्नुहुन्छ। यो पाईमा तपाईंले नभएको अडियो उपकरणहरूको कन्फिगरेसनका कारण हो। यी त्रुटिहरूलाई बेवास्ता गर्न सकिन्छ।

    ```output
    pi@raspberrypi:~/smart-timer $ python3 app.py 
    ALSA lib pcm.c:2565:(snd_pcm_open_noupdate) Unknown PCM cards.pcm.front
    ALSA lib pcm.c:2565:(snd_pcm_open_noupdate) Unknown PCM cards.pcm.rear
    ALSA lib pcm.c:2565:(snd_pcm_open_noupdate) Unknown PCM cards.pcm.center_lfe
    ALSA lib pcm.c:2565:(snd_pcm_open_noupdate) Unknown PCM cards.pcm.side
    ```

    यदि तपाईंले निम्न त्रुटि पाउनुभयो:

    ```output
    OSError: [Errno -9997] Invalid sample rate
    ```

    भने `rate` लाई `44100` वा `16000` मा परिवर्तन गर्नुहोस्।

> 💁 तपाईंले यो कोड [code-record/pi](../../../../../6-consumer/lessons/1-speech-recognition/code-record/pi) फोल्डरमा पाउन सक्नुहुन्छ।

😀 तपाईंको अडियो रेकर्डिङ प्रोग्राम सफल भयो!

---

**अस्वीकरण**:  
यो दस्तावेज़ AI अनुवाद सेवा [Co-op Translator](https://github.com/Azure/co-op-translator) प्रयोग गरेर अनुवाद गरिएको छ। हामी शुद्धताको लागि प्रयास गर्छौं, तर कृपया ध्यान दिनुहोस् कि स्वचालित अनुवादमा त्रुटिहरू वा अशुद्धताहरू हुन सक्छ। यसको मूल भाषा मा रहेको मूल दस्तावेज़लाई आधिकारिक स्रोत मानिनुपर्छ। महत्वपूर्ण जानकारीको लागि, व्यावसायिक मानव अनुवाद सिफारिस गरिन्छ। यस अनुवादको प्रयोगबाट उत्पन्न हुने कुनै पनि गलतफहमी वा गलत व्याख्याको लागि हामी जिम्मेवार हुने छैनौं।