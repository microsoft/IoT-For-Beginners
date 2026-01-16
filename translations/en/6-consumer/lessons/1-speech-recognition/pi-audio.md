<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "0ac0afcfb40cb5970ef4cb74f01c32e9",
  "translation_date": "2025-08-28T19:24:53+00:00",
  "source_file": "6-consumer/lessons/1-speech-recognition/pi-audio.md",
  "language_code": "en"
}
-->
# Capture audio - Raspberry Pi

In this part of the lesson, you will write code to record audio on your Raspberry Pi. The audio recording will be controlled by a button.

## Hardware

The Raspberry Pi requires a button to manage the audio recording.

The button you'll use is a Grove button. This is a digital sensor that toggles a signal on or off. These buttons can be configured to send a high signal when pressed and a low signal when not, or vice versa.

If you're using a ReSpeaker 2-Mics Pi HAT as a microphone, you don't need to connect an external button since this hat already has one built in. Skip to the next section.

### Connect the button

The button can be connected to the Grove base hat.

#### Task - connect the button

![A grove button](../../../../../translated_images/en/grove-button.a70cfbb809a8563681003250cf5b06d68cdcc68624f9e2f493d5a534ae2da1e5.png)

1. Insert one end of a Grove cable into the socket on the button module. It will only fit one way.

1. With the Raspberry Pi powered off, connect the other end of the Grove cable to the digital socket labeled **D5** on the Grove Base hat attached to the Pi. This socket is the second from the left in the row of sockets next to the GPIO pins.

![The grove button connected to socket D5](../../../../../translated_images/en/pi-button.c7a1a4f55943341ce1baf1057658e9a205804d4131d258e820c93f951df0abf3.png)

## Capture audio

You can record audio from the microphone using Python code.

### Task - capture audio

1. Power up the Pi and wait for it to boot.

1. Open VS Code, either directly on the Pi or by connecting via the Remote SSH extension.

1. The PyAudio Pip package provides functions to record and play audio. This package depends on some audio libraries that need to be installed first. Run the following commands in the terminal to install them:

    ```sh
    sudo apt update
    sudo apt install libportaudio0 libportaudio2 libportaudiocpp0 portaudio19-dev libasound2-plugins --yes 
    ```

1. Install the PyAudio Pip package.

    ```sh
    pip3 install pyaudio
    ```

1. Create a new folder called `smart-timer` and add a file named `app.py` to this folder.

1. Add the following imports at the top of the file:

    ```python
    import io
    import pyaudio
    import time
    import wave
    
    from grove.factory import Factory
    ```

    This imports the `pyaudio` module, some standard Python modules for handling wave files, and the `grove.factory` module to import a `Factory` for creating a button class.

1. Below this, add code to create a Grove button.

    If you're using the ReSpeaker 2-Mics Pi HAT, use the following code:

    ```python
    # The button on the ReSpeaker 2-Mics Pi HAT
    button = Factory.getButton("GPIO-LOW", 17)
    ```

    This creates a button on port **D17**, which is the port connected to the button on the ReSpeaker 2-Mics Pi HAT. This button is configured to send a low signal when pressed.

    If you're not using the ReSpeaker 2-Mics Pi HAT and are instead using a Grove button connected to the base hat, use this code:

    ```python
    button = Factory.getButton("GPIO-HIGH", 5)
    ```

    This creates a button on port **D5**, configured to send a high signal when pressed.

1. Below this, create an instance of the PyAudio class to manage audio:

    ```python
    audio = pyaudio.PyAudio()
    ```

1. Specify the hardware card number for the microphone and speaker. This will be the number you identified earlier in the lesson by running `arecord -l` and `aplay -l`.

    ```python
    microphone_card_number = <microphone card number>
    speaker_card_number = <speaker card number>
    ```

    Replace `<microphone card number>` with the number of your microphone's card.

    Replace `<speaker card number>` with the number of your speaker's card, which is the same number you set in the `alsa.conf` file.

1. Below this, define the sample rate for audio recording and playback. You may need to adjust this depending on your hardware.

    ```python
    rate = 48000 #48KHz
    ```

    If you encounter sample rate errors when running the code later, change this value to `44100` or `16000`. Higher values result in better sound quality.

1. Below this, create a new function called `capture_audio`. This function will handle audio recording from the microphone:

    ```python
    def capture_audio():
    ```

1. Inside this function, add the following code to record audio:

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

    This code opens an audio input stream using the PyAudio object. The stream captures audio from the microphone at 16KHz, storing it in buffers of 4096 bytes.

    The code loops while the Grove button is pressed, reading these 4096-byte buffers into an array each time.

    > 💁 You can learn more about the options passed to the `open` method in the [PyAudio documentation](https://people.csail.mit.edu/hubert/pyaudio/docs/).

    Once the button is released, the stream is stopped and closed.

1. Add the following code at the end of this function:

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

    This code creates a binary buffer and writes all the recorded audio to it as a [WAV file](https://wikipedia.org/wiki/WAV). WAV is a standard format for storing uncompressed audio. The buffer is then returned.

1. Add the following `play_audio` function to play back the recorded audio:

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

    This function opens another audio stream, this time for output, to play the audio. It uses the same settings as the input stream. The buffer is opened as a wave file and written to the output stream in 4096-byte chunks, playing the audio. The stream is then closed.

1. Add the following code below the `capture_audio` function to loop until the button is pressed. Once the button is pressed, the audio is recorded and then played back.

    ```python
    while True:
        while not button.is_pressed():
            time.sleep(.1)
        
        buffer = capture_audio()
        play_audio(buffer)
    ```

1. Run the code. Press the button and speak into the microphone. Release the button when you're done, and you'll hear the recording.

    You may see some ALSA errors when the PyAudio instance is created. These errors are caused by configurations for audio devices that aren't present on the Pi. You can ignore them.

    ```output
    pi@raspberrypi:~/smart-timer $ python3 app.py 
    ALSA lib pcm.c:2565:(snd_pcm_open_noupdate) Unknown PCM cards.pcm.front
    ALSA lib pcm.c:2565:(snd_pcm_open_noupdate) Unknown PCM cards.pcm.rear
    ALSA lib pcm.c:2565:(snd_pcm_open_noupdate) Unknown PCM cards.pcm.center_lfe
    ALSA lib pcm.c:2565:(snd_pcm_open_noupdate) Unknown PCM cards.pcm.side
    ```

    If you encounter the following error:

    ```output
    OSError: [Errno -9997] Invalid sample rate
    ```

    change the `rate` to either 44100 or 16000.

> 💁 You can find this code in the [code-record/pi](../../../../../6-consumer/lessons/1-speech-recognition/code-record/pi) folder.

😀 Your audio recording program is working perfectly!

---

**Disclaimer**:  
This document has been translated using the AI translation service [Co-op Translator](https://github.com/Azure/co-op-translator). While we aim for accuracy, please note that automated translations may include errors or inaccuracies. The original document in its native language should be regarded as the authoritative source. For critical information, professional human translation is advised. We are not responsible for any misunderstandings or misinterpretations resulting from the use of this translation.