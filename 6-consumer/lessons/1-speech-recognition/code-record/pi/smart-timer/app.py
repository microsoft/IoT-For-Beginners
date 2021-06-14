import io
import pyaudio
import time
import wave

from grove.factory import Factory
button = Factory.getButton('GPIO-HIGH', 5)

audio = pyaudio.PyAudio()
microphone_card_number = 1
speaker_card_number = 1
rate = 48000

def capture_audio():
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

    wav_buffer = io.BytesIO()
    with wave.open(wav_buffer, 'wb') as wavefile:
        wavefile.setnchannels(1)
        wavefile.setsampwidth(audio.get_sample_size(pyaudio.paInt16))
        wavefile.setframerate(rate)
        wavefile.writeframes(b''.join(frames))
        wav_buffer.seek(0)

    return wav_buffer

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

while True:
    while not button.is_pressed():
        time.sleep(.1)

    buffer = capture_audio()
    play_audio(buffer)