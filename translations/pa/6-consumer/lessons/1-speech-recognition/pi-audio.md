# ਆਡੀਓ ਕੈਪਚਰ ਕਰੋ - ਰਾਸਪਬੈਰੀ ਪਾਈ

ਇਸ ਪਾਠ ਦੇ ਇਸ ਹਿੱਸੇ ਵਿੱਚ, ਤੁਸੀਂ ਰਾਸਪਬੈਰੀ ਪਾਈ 'ਤੇ ਆਡੀਓ ਕੈਪਚਰ ਕਰਨ ਲਈ ਕੋਡ ਲਿਖੋਗੇ। ਆਡੀਓ ਕੈਪਚਰ ਨੂੰ ਇੱਕ ਬਟਨ ਦੁਆਰਾ ਕੰਟਰੋਲ ਕੀਤਾ ਜਾਵੇਗਾ।

## ਹਾਰਡਵੇਅਰ

ਰਾਸਪਬੈਰੀ ਪਾਈ ਨੂੰ ਆਡੀਓ ਕੈਪਚਰ ਨੂੰ ਕੰਟਰੋਲ ਕਰਨ ਲਈ ਇੱਕ ਬਟਨ ਦੀ ਲੋੜ ਹੈ।

ਤੁਹਾਡੇ ਦੁਆਰਾ ਵਰਤਿਆ ਜਾਣ ਵਾਲਾ ਬਟਨ ਇੱਕ ਗਰੋਵ ਬਟਨ ਹੈ। ਇਹ ਇੱਕ ਡਿਜੀਟਲ ਸੈਂਸਰ ਹੈ ਜੋ ਸਿਗਨਲ ਨੂੰ ਚਾਲੂ ਜਾਂ ਬੰਦ ਕਰਦਾ ਹੈ। ਇਹ ਬਟਨ ਇਸ ਤਰੀਕੇ ਨਾਲ ਸੰਰਚਿਤ ਕੀਤੇ ਜਾ ਸਕਦੇ ਹਨ ਕਿ ਜਦੋਂ ਬਟਨ ਦਬਾਇਆ ਜਾਂਦਾ ਹੈ ਤਾਂ ਉੱਚਾ ਸਿਗਨਲ ਭੇਜਦੇ ਹਨ, ਅਤੇ ਜਦੋਂ ਨਹੀਂ ਦਬਾਇਆ ਜਾਂਦਾ ਤਾਂ ਘੱਟ, ਜਾਂ ਜਦੋਂ ਦਬਾਇਆ ਜਾਂਦਾ ਹੈ ਤਾਂ ਘੱਟ ਅਤੇ ਜਦੋਂ ਨਹੀਂ ਦਬਾਇਆ ਜਾਂਦਾ ਤਾਂ ਉੱਚਾ।

ਜੇਕਰ ਤੁਸੀਂ ਮਾਈਕ੍ਰੋਫੋਨ ਵਜੋਂ ReSpeaker 2-Mics Pi HAT ਵਰਤ ਰਹੇ ਹੋ, ਤਾਂ ਬਟਨ ਨੂੰ ਜੁੜਨ ਦੀ ਕੋਈ ਲੋੜ ਨਹੀਂ ਹੈ ਕਿਉਂਕਿ ਇਸ HAT ਵਿੱਚ ਪਹਿਲਾਂ ਹੀ ਇੱਕ ਬਟਨ ਲਗਾਇਆ ਗਿਆ ਹੈ। ਅਗਲੇ ਭਾਗ 'ਤੇ ਜਾਓ।

### ਬਟਨ ਨੂੰ ਜੁੜੋ

ਬਟਨ ਨੂੰ ਗਰੋਵ ਬੇਸ HAT ਨਾਲ ਜੁੜਿਆ ਜਾ ਸਕਦਾ ਹੈ।

#### ਕੰਮ - ਬਟਨ ਨੂੰ ਜੁੜੋ

![ਇੱਕ ਗਰੋਵ ਬਟਨ](../../../../../translated_images/pa/grove-button.a70cfbb809a85636.webp)

1. ਗਰੋਵ ਕੇਬਲ ਦੇ ਇੱਕ ਸਿਰੇ ਨੂੰ ਬਟਨ ਮੋਡੀਊਲ ਦੇ ਸਾਕਟ ਵਿੱਚ ਪਾਓ। ਇਹ ਸਿਰਫ ਇੱਕ ਹੀ ਦਿਸ਼ਾ ਵਿੱਚ ਜਾਵੇਗਾ।

1. ਰਾਸਪਬੈਰੀ ਪਾਈ ਨੂੰ ਬੰਦ ਕਰਕੇ, ਗਰੋਵ ਕੇਬਲ ਦੇ ਦੂਜੇ ਸਿਰੇ ਨੂੰ **D5** ਨਾਲ ਚਿੰਨ੍ਹਿਤ ਡਿਜੀਟਲ ਸਾਕਟ ਵਿੱਚ ਜੁੜੋ ਜੋ ਪਾਈ ਨਾਲ ਜੁੜੇ ਗਰੋਵ ਬੇਸ HAT 'ਤੇ ਹੈ। ਇਹ ਸਾਕਟ GPIO ਪਿੰਸ ਦੇ ਕੋਲ ਸਾਕਟਾਂ ਦੀ ਲਾਈਨ ਵਿੱਚ ਦੂਜਾ ਹੈ।

![ਗਰੋਵ ਬਟਨ D5 ਸਾਕਟ ਨਾਲ ਜੁੜਿਆ](../../../../../translated_images/pa/pi-button.c7a1a4f55943341c.webp)

## ਆਡੀਓ ਕੈਪਚਰ ਕਰੋ

ਤੁਸੀਂ ਮਾਈਕ੍ਰੋਫੋਨ ਤੋਂ ਆਡੀਓ ਪਾਈਥਨ ਕੋਡ ਦੀ ਵਰਤੋਂ ਕਰਕੇ ਕੈਪਚਰ ਕਰ ਸਕਦੇ ਹੋ।

### ਕੰਮ - ਆਡੀਓ ਕੈਪਚਰ ਕਰੋ

1. ਪਾਈ ਨੂੰ ਚਾਲੂ ਕਰੋ ਅਤੇ ਬੂਟ ਹੋਣ ਦੀ ਉਡੀਕ ਕਰੋ।

1. VS Code ਲਾਂਚ ਕਰੋ, ਜਾਂ ਤਾਂ ਸਿੱਧੇ ਪਾਈ 'ਤੇ, ਜਾਂ ਰਿਮੋਟ SSH ਐਕਸਟੈਂਸ਼ਨ ਦੁਆਰਾ ਕਨੈਕਟ ਕਰੋ।

1. PyAudio Pip ਪੈਕੇਜ ਵਿੱਚ ਆਡੀਓ ਨੂੰ ਰਿਕਾਰਡ ਅਤੇ ਪਲੇਬੈਕ ਕਰਨ ਦੇ ਫੰਕਸ਼ਨ ਹਨ। ਇਸ ਪੈਕੇਜ ਨੂੰ ਕੁਝ ਆਡੀਓ ਲਾਇਬ੍ਰੇਰੀਆਂ ਦੀ ਲੋੜ ਹੈ ਜੋ ਪਹਿਲਾਂ ਇੰਸਟਾਲ ਕੀਤੀਆਂ ਜਾਣੀਆਂ ਚਾਹੀਦੀਆਂ ਹਨ। ਟਰਮੀਨਲ ਵਿੱਚ ਹੇਠਾਂ ਦਿੱਤੇ ਕਮਾਂਡ ਚਲਾਓ:

    ```sh
    sudo apt update
    sudo apt install libportaudio0 libportaudio2 libportaudiocpp0 portaudio19-dev libasound2-plugins --yes 
    ```

1. PyAudio Pip ਪੈਕੇਜ ਇੰਸਟਾਲ ਕਰੋ।

    ```sh
    pip3 install pyaudio
    ```

1. ਇੱਕ ਨਵਾਂ ਫੋਲਡਰ ਬਣਾਓ ਜਿਸਦਾ ਨਾਮ `smart-timer` ਰੱਖੋ ਅਤੇ ਇਸ ਫੋਲਡਰ ਵਿੱਚ `app.py` ਨਾਮਕ ਫਾਈਲ ਸ਼ਾਮਲ ਕਰੋ।

1. ਇਸ ਫਾਈਲ ਦੇ ਉੱਪਰ ਹੇਠਾਂ ਦਿੱਤੇ ਇੰਪੋਰਟਸ ਸ਼ਾਮਲ ਕਰੋ:

    ```python
    import io
    import pyaudio
    import time
    import wave
    
    from grove.factory import Factory
    ```

    ਇਹ `pyaudio` ਮੋਡੀਊਲ, ਕੁਝ ਸਟੈਂਡਰਡ ਪਾਈਥਨ ਮੋਡੀਊਲਾਂ ਨੂੰ ਵੇਵ ਫਾਈਲਾਂ ਨੂੰ ਹੈਂਡਲ ਕਰਨ ਲਈ, ਅਤੇ `grove.factory` ਮੋਡੀਊਲ ਨੂੰ ਇੱਕ `Factory` ਨੂੰ ਇੰਪੋਰਟ ਕਰਨ ਲਈ ਬਟਨ ਕਲਾਸ ਬਣਾਉਣ ਲਈ ਇੰਪੋਰਟ ਕਰਦਾ ਹੈ।

1. ਇਸ ਤੋਂ ਹੇਠਾਂ, ਗਰੋਵ ਬਟਨ ਬਣਾਉਣ ਲਈ ਕੋਡ ਸ਼ਾਮਲ ਕਰੋ।

    ਜੇਕਰ ਤੁਸੀਂ ReSpeaker 2-Mics Pi HAT ਵਰਤ ਰਹੇ ਹੋ, ਤਾਂ ਹੇਠਾਂ ਦਿੱਤਾ ਕੋਡ ਵਰਤੋ:

    ```python
    # The button on the ReSpeaker 2-Mics Pi HAT
    button = Factory.getButton("GPIO-LOW", 17)
    ```

    ਇਹ **D17** ਪੋਰਟ 'ਤੇ ਇੱਕ ਬਟਨ ਬਣਾਉਂਦਾ ਹੈ, ਉਹ ਪੋਰਟ ਜਿਸ ਨਾਲ ReSpeaker 2-Mics Pi HAT 'ਤੇ ਬਟਨ ਜੁੜਿਆ ਹੋਇਆ ਹੈ। ਇਹ ਬਟਨ ਦਬਾਏ ਜਾਣ 'ਤੇ ਘੱਟ ਸਿਗਨਲ ਭੇਜਣ ਲਈ ਸੈਟ ਕੀਤਾ ਗਿਆ ਹੈ।

    ਜੇਕਰ ਤੁਸੀਂ ReSpeaker 2-Mics Pi HAT ਨਹੀਂ ਵਰਤ ਰਹੇ ਹੋ, ਅਤੇ ਗਰੋਵ ਬਟਨ ਨੂੰ ਬੇਸ HAT ਨਾਲ ਜੋੜ ਰਹੇ ਹੋ, ਤਾਂ ਇਹ ਕੋਡ ਵਰਤੋ।

    ```python
    button = Factory.getButton("GPIO-HIGH", 5)
    ```

    ਇਹ **D5** ਪੋਰਟ 'ਤੇ ਇੱਕ ਬਟਨ ਬਣਾਉਂਦਾ ਹੈ ਜੋ ਦਬਾਏ ਜਾਣ 'ਤੇ ਉੱਚਾ ਸਿਗਨਲ ਭੇਜਣ ਲਈ ਸੈਟ ਕੀਤਾ ਗਿਆ ਹੈ।

1. ਇਸ ਤੋਂ ਹੇਠਾਂ, PyAudio ਕਲਾਸ ਦਾ ਇੱਕ ਇੰਸਟੈਂਸ ਬਣਾਓ ਜੋ ਆਡੀਓ ਨੂੰ ਹੈਂਡਲ ਕਰੇ:

    ```python
    audio = pyaudio.PyAudio()
    ```

1. ਮਾਈਕ੍ਰੋਫੋਨ ਅਤੇ ਸਪੀਕਰ ਲਈ ਹਾਰਡਵੇਅਰ ਕਾਰਡ ਨੰਬਰ ਘੋਸ਼ਿਤ ਕਰੋ। ਇਹ ਉਹ ਨੰਬਰ ਹੋਵੇਗਾ ਜੋ ਤੁਸੀਂ ਇਸ ਪਾਠ ਵਿੱਚ ਪਹਿਲਾਂ `arecord -l` ਅਤੇ `aplay -l` ਚਲਾਕੇ ਪਾਇਆ ਸੀ।

    ```python
    microphone_card_number = <microphone card number>
    speaker_card_number = <speaker card number>
    ```

    `<microphone card number>` ਨੂੰ ਆਪਣੇ ਮਾਈਕ੍ਰੋਫੋਨ ਕਾਰਡ ਦੇ ਨੰਬਰ ਨਾਲ ਬਦਲੋ।

    `<speaker card number>` ਨੂੰ ਆਪਣੇ ਸਪੀਕਰ ਕਾਰਡ ਦੇ ਨੰਬਰ ਨਾਲ ਬਦਲੋ, ਉਹੀ ਨੰਬਰ ਜੋ ਤੁਸੀਂ `alsa.conf` ਫਾਈਲ ਵਿੱਚ ਸੈਟ ਕੀਤਾ ਸੀ।

1. ਇਸ ਤੋਂ ਹੇਠਾਂ, ਆਡੀਓ ਕੈਪਚਰ ਅਤੇ ਪਲੇਬੈਕ ਲਈ ਵਰਤਣ ਵਾਲਾ ਸੈਂਪਲ ਰੇਟ ਘੋਸ਼ਿਤ ਕਰੋ। ਤੁਸੀਂ ਵਰਤ ਰਹੇ ਹਾਰਡਵੇਅਰ ਦੇ ਅਨੁਸਾਰ ਇਸ ਨੂੰ ਬਦਲਣ ਦੀ ਲੋੜ ਹੋ ਸਕਦੀ ਹੈ।

    ```python
    rate = 48000 #48KHz
    ```

    ਜੇਕਰ ਤੁਸੀਂ ਬਾਅਦ ਵਿੱਚ ਇਹ ਕੋਡ ਚਲਾਉਣ ਸਮੇਂ ਸੈਂਪਲ ਰੇਟ ਐਰਰ ਪ੍ਰਾਪਤ ਕਰਦੇ ਹੋ, ਤਾਂ ਇਸ ਮੁੱਲ ਨੂੰ `44100` ਜਾਂ `16000` ਵਿੱਚ ਬਦਲੋ। ਮੁੱਲ ਜਿੰਨਾ ਉੱਚਾ ਹੋਵੇਗਾ, ਧੁਨੀ ਦੀ ਗੁਣਵੱਤਾ ਉਤਨੀ ਹੀ ਚੰਗੀ ਹੋਵੇਗੀ।

1. ਇਸ ਤੋਂ ਹੇਠਾਂ, ਇੱਕ ਨਵਾਂ ਫੰਕਸ਼ਨ `capture_audio` ਬਣਾਓ। ਇਹ ਮਾਈਕ੍ਰੋਫੋਨ ਤੋਂ ਆਡੀਓ ਕੈਪਚਰ ਕਰਨ ਲਈ ਕਾਲ ਕੀਤਾ ਜਾਵੇਗਾ:

    ```python
    def capture_audio():
    ```

1. ਇਸ ਫੰਕਸ਼ਨ ਦੇ ਅੰਦਰ, ਆਡੀਓ ਕੈਪਚਰ ਕਰਨ ਲਈ ਹੇਠਾਂ ਦਿੱਤਾ ਸ਼ਾਮਲ ਕਰੋ:

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

    ਇਹ ਕੋਡ PyAudio ਆਬਜੈਕਟ ਦੀ ਵਰਤੋਂ ਕਰਕੇ ਇੱਕ ਆਡੀਓ ਇਨਪੁਟ ਸਟ੍ਰੀਮ ਖੋਲ੍ਹਦਾ ਹੈ। ਇਹ ਸਟ੍ਰੀਮ ਮਾਈਕ੍ਰੋਫੋਨ ਤੋਂ 16KHz 'ਤੇ ਆਡੀਓ ਕੈਪਚਰ ਕਰੇਗਾ, ਇਸਨੂੰ 4096 ਬਾਈਟ ਦੇ ਬਫਰ ਵਿੱਚ ਕੈਪਚਰ ਕਰੇਗਾ।

    ਕੋਡ ਫਿਰ ਗਰੋਵ ਬਟਨ ਦਬਾਏ ਜਾਣ ਤੱਕ ਲੂਪ ਕਰਦਾ ਹੈ, ਹਰ ਵਾਰ 4096 ਬਾਈਟ ਬਫਰ ਨੂੰ ਇੱਕ ਐਰੇ ਵਿੱਚ ਪੜ੍ਹਦਾ ਹੈ।

    > 💁 ਤੁਸੀਂ `open` ਮੈਥਡ ਨੂੰ ਪਾਸ ਕੀਤੇ ਗਏ ਵਿਕਲਪਾਂ ਬਾਰੇ ਹੋਰ ਜਾਣਕਾਰੀ [PyAudio ਦਸਤਾਵੇਜ਼](https://people.csail.mit.edu/hubert/pyaudio/docs/) ਵਿੱਚ ਪੜ੍ਹ ਸਕਦੇ ਹੋ।

    ਜਦੋਂ ਬਟਨ ਛੱਡਿਆ ਜਾਂਦਾ ਹੈ, ਸਟ੍ਰੀਮ ਰੋਕ ਦਿੱਤੀ ਜਾਂਦੀ ਹੈ ਅਤੇ ਬੰਦ ਕਰ ਦਿੱਤੀ ਜਾਂਦੀ ਹੈ।

1. ਇਸ ਫੰਕਸ਼ਨ ਦੇ ਅੰਤ ਵਿੱਚ ਹੇਠਾਂ ਦਿੱਤਾ ਸ਼ਾਮਲ ਕਰੋ:

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

    ਇਹ ਕੋਡ ਇੱਕ ਬਾਈਨਰੀ ਬਫਰ ਬਣਾਉਂਦਾ ਹੈ, ਅਤੇ ਸਾਰੇ ਕੈਪਚਰ ਕੀਤੇ ਗਏ ਆਡੀਓ ਨੂੰ [WAV ਫਾਈਲ](https://wikipedia.org/wiki/WAV) ਵਜੋਂ ਲਿਖਦਾ ਹੈ। ਇਹ ਅਨਕੰਪ੍ਰੈਸਡ ਆਡੀਓ ਨੂੰ ਫਾਈਲ ਵਿੱਚ ਲਿਖਣ ਦਾ ਇੱਕ ਸਟੈਂਡਰਡ ਤਰੀਕਾ ਹੈ। ਇਹ ਬਫਰ ਫਿਰ ਵਾਪਸ ਕੀਤਾ ਜਾਂਦਾ ਹੈ।

1. ਹੇਠਾਂ ਦਿੱਤਾ `play_audio` ਫੰਕਸ਼ਨ ਸ਼ਾਮਲ ਕਰੋ ਜੋ ਆਡੀਓ ਬਫਰ ਨੂੰ ਪਲੇਬੈਕ ਕਰੇਗਾ:

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

    ਇਹ ਫੰਕਸ਼ਨ ਇੱਕ ਹੋਰ ਆਡੀਓ ਸਟ੍ਰੀਮ ਖੋਲ੍ਹਦਾ ਹੈ, ਇਸ ਵਾਰ ਆਉਟਪੁੱਟ ਲਈ - ਆਡੀਓ ਪਲੇ ਕਰਨ ਲਈ। ਇਹ ਇਨਪੁਟ ਸਟ੍ਰੀਮ ਦੇ ਸਮਾਨ ਸੈਟਿੰਗਾਂ ਦੀ ਵਰਤੋਂ ਕਰਦਾ ਹੈ। ਬਫਰ ਫਿਰ ਇੱਕ ਵੇਵ ਫਾਈਲ ਵਜੋਂ ਖੋਲ੍ਹਿਆ ਜਾਂਦਾ ਹੈ ਅਤੇ 4096 ਬਾਈਟ ਚੰਕ ਵਿੱਚ ਆਉਟਪੁੱਟ ਸਟ੍ਰੀਮ ਵਿੱਚ ਲਿਖਿਆ ਜਾਂਦਾ ਹੈ, ਆਡੀਓ ਪਲੇ ਕਰਦਾ ਹੈ। ਸਟ੍ਰੀਮ ਫਿਰ ਬੰਦ ਕਰ ਦਿੱਤੀ ਜਾਂਦੀ ਹੈ।

1. `capture_audio` ਫੰਕਸ਼ਨ ਦੇ ਹੇਠਾਂ ਹੇਠਾਂ ਦਿੱਤਾ ਕੋਡ ਸ਼ਾਮਲ ਕਰੋ ਜੋ ਲੂਪ ਕਰੇਗਾ ਜਦ ਤੱਕ ਬਟਨ ਦਬਾਇਆ ਨਹੀਂ ਜਾਂਦਾ। ਜਦੋਂ ਬਟਨ ਦਬਾਇਆ ਜਾਂਦਾ ਹੈ, ਆਡੀਓ ਕੈਪਚਰ ਕੀਤਾ ਜਾਂਦਾ ਹੈ, ਫਿਰ ਪਲੇ ਕੀਤਾ ਜਾਂਦਾ ਹੈ।

    ```python
    while True:
        while not button.is_pressed():
            time.sleep(.1)
        
        buffer = capture_audio()
        play_audio(buffer)
    ```

1. ਕੋਡ ਚਲਾਓ। ਬਟਨ ਦਬਾਓ ਅਤੇ ਮਾਈਕ੍ਰੋਫੋਨ ਵਿੱਚ ਬੋਲੋ। ਜਦੋਂ ਤੁਸੀਂ ਖਤਮ ਕਰ ਲੈਂਦੇ ਹੋ, ਬਟਨ ਛੱਡੋ, ਅਤੇ ਤੁਸੀਂ ਰਿਕਾਰਡਿੰਗ ਸੁਣੋਗੇ।

    ਜਦੋਂ PyAudio ਇੰਸਟੈਂਸ ਬਣਾਇਆ ਜਾਂਦਾ ਹੈ, ਤਾਂ ਤੁਸੀਂ ਕੁਝ ALSA ਐਰਰ ਪ੍ਰਾਪਤ ਕਰ ਸਕਦੇ ਹੋ। ਇਹ ਪਾਈ 'ਤੇ ਆਡੀਓ ਡਿਵਾਈਸਾਂ ਲਈ ਸੰਰਚਨਾ ਦੇ ਕਾਰਨ ਹੈ ਜੋ ਤੁਹਾਡੇ ਕੋਲ ਨਹੀਂ ਹਨ। ਤੁਸੀਂ ਇਹ ਐਰਰ ਅਣਡਿੱਠੇ ਕਰ ਸਕਦੇ ਹੋ।

    ```output
    pi@raspberrypi:~/smart-timer $ python3 app.py 
    ALSA lib pcm.c:2565:(snd_pcm_open_noupdate) Unknown PCM cards.pcm.front
    ALSA lib pcm.c:2565:(snd_pcm_open_noupdate) Unknown PCM cards.pcm.rear
    ALSA lib pcm.c:2565:(snd_pcm_open_noupdate) Unknown PCM cards.pcm.center_lfe
    ALSA lib pcm.c:2565:(snd_pcm_open_noupdate) Unknown PCM cards.pcm.side
    ```

    ਜੇਕਰ ਤੁਹਾਨੂੰ ਹੇਠਾਂ ਦਿੱਤਾ ਐਰਰ ਮਿਲਦਾ ਹੈ:

    ```output
    OSError: [Errno -9997] Invalid sample rate
    ```

    ਤਾਂ `rate` ਨੂੰ 44100 ਜਾਂ 16000 ਵਿੱਚ ਬਦਲੋ।

> 💁 ਤੁਸੀਂ ਇਹ ਕੋਡ [code-record/pi](../../../../../6-consumer/lessons/1-speech-recognition/code-record/pi) ਫੋਲਡਰ ਵਿੱਚ ਪਾ ਸਕਦੇ ਹੋ।

😀 ਤੁਹਾਡਾ ਆਡੀਓ ਰਿਕਾਰਡਿੰਗ ਪ੍ਰੋਗਰਾਮ ਸਫਲ ਰਿਹਾ!

---

**ਅਸਵੀਕਤੀ**:  
ਇਹ ਦਸਤਾਵੇਜ਼ AI ਅਨੁਵਾਦ ਸੇਵਾ [Co-op Translator](https://github.com/Azure/co-op-translator) ਦੀ ਵਰਤੋਂ ਕਰਕੇ ਅਨੁਵਾਦ ਕੀਤਾ ਗਿਆ ਹੈ। ਜਦੋਂ ਕਿ ਅਸੀਂ ਸਹੀ ਹੋਣ ਦੀ ਕੋਸ਼ਿਸ਼ ਕਰਦੇ ਹਾਂ, ਕਿਰਪਾ ਕਰਕੇ ਧਿਆਨ ਦਿਓ ਕਿ ਸਵੈਚਾਲਿਤ ਅਨੁਵਾਦਾਂ ਵਿੱਚ ਗਲਤੀਆਂ ਜਾਂ ਅਸੁਚਨਾਵਾਂ ਹੋ ਸਕਦੀਆਂ ਹਨ। ਮੂਲ ਦਸਤਾਵੇਜ਼ ਨੂੰ ਇਸਦੀ ਮੂਲ ਭਾਸ਼ਾ ਵਿੱਚ ਅਧਿਕਾਰਤ ਸਰੋਤ ਮੰਨਿਆ ਜਾਣਾ ਚਾਹੀਦਾ ਹੈ। ਮਹੱਤਵਪੂਰਨ ਜਾਣਕਾਰੀ ਲਈ, ਪੇਸ਼ੇਵਰ ਮਨੁੱਖੀ ਅਨੁਵਾਦ ਦੀ ਸਿਫਾਰਸ਼ ਕੀਤੀ ਜਾਂਦੀ ਹੈ। ਇਸ ਅਨੁਵਾਦ ਦੀ ਵਰਤੋਂ ਤੋਂ ਪੈਦਾ ਹੋਣ ਵਾਲੇ ਕਿਸੇ ਵੀ ਗਲਤਫਹਿਮੀ ਜਾਂ ਗਲਤ ਵਿਆਖਿਆ ਲਈ ਅਸੀਂ ਜ਼ਿੰਮੇਵਾਰ ਨਹੀਂ ਹਾਂ।