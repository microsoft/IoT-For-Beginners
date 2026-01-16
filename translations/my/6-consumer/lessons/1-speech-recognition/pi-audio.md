<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "0ac0afcfb40cb5970ef4cb74f01c32e9",
  "translation_date": "2025-08-28T16:26:39+00:00",
  "source_file": "6-consumer/lessons/1-speech-recognition/pi-audio.md",
  "language_code": "my"
}
-->
# အသံဖမ်းယူခြင်း - Raspberry Pi

ဒီသင်ခန်းစာအပိုင်းမှာ သင်ရဲ့ Raspberry Pi ပေါ်မှာ အသံဖမ်းယူဖို့ ကုဒ်ရေးမှာဖြစ်ပါတယ်။ အသံဖမ်းယူမှုကို ခလုတ်တစ်ခုက ထိန်းချုပ်ပေးမှာဖြစ်ပါတယ်။

## ဟာ့ဒ်ဝဲ

Raspberry Pi ကို အသံဖမ်းယူမှုကို ထိန်းချုပ်ဖို့ ခလုတ်တစ်ခုလိုအပ်ပါတယ်။

သင်အသုံးပြုမယ့် ခလုတ်က Grove ခလုတ်ဖြစ်ပါတယ်။ ဒါက သက်တောင့်သက်သာရှိတဲ့ အာရုံခံကိရိယာတစ်ခုဖြစ်ပြီး signal ကို ဖွင့်/ပိတ်လုပ်ပေးနိုင်ပါတယ်။ ဒီခလုတ်တွေကို ခလုတ်နှိပ်တဲ့အခါ high signal ပို့ပေးဖို့၊ နှိပ်မထားတဲ့အခါ low signal ပို့ပေးဖို့ သို့မဟုတ် နှိပ်တဲ့အခါ low signal ပို့ပေးပြီး နှိပ်မထားတဲ့အခါ high signal ပို့ပေးဖို့ အဆင်ပြေစွာ ပြင်ဆင်နိုင်ပါတယ်။

ReSpeaker 2-Mics Pi HAT ကို မိုက်ခရိုဖုန်းအဖြစ် အသုံးပြုနေပါက ခလုတ်တစ်ခု ချိတ်ဆက်ရန် မလိုအပ်ပါဘူး။ ဒီ HAT မှာ ခလုတ်တစ်ခု ရှိပြီးသားဖြစ်ပါတယ်။ နောက်ထပ်အပိုင်းဆီ သွားပါ။

### ခလုတ်ကို ချိတ်ဆက်ပါ

ခလုတ်ကို Grove base hat နဲ့ ချိတ်ဆက်နိုင်ပါတယ်။

#### လုပ်ဆောင်ရန် - ခလုတ်ကို ချိတ်ဆက်ပါ

![A grove button](../../../../../translated_images/my/grove-button.a70cfbb809a8563681003250cf5b06d68cdcc68624f9e2f493d5a534ae2da1e5.png)

1. Grove cable ရဲ့ တစ်ဖက်အဆုံးကို ခလုတ် module ရဲ့ socket ထဲထည့်ပါ။ ဒီ cable ကို တစ်ဖက်ဘက်သာ ထည့်နိုင်ပါတယ်။

1. Raspberry Pi ကို ပိတ်ထားပြီး Grove cable ရဲ့ တစ်ဖက်အဆုံးကို Pi ရဲ့ Grove Base hat ရဲ့ **D5** လို့ အမှတ်အသားပြထားတဲ့ digital socket ထဲ ချိတ်ဆက်ပါ။ ဒီ socket က GPIO pins ရဲ့ အနီးမှာရှိတဲ့ socket row ရဲ့ ဘယ်ဘက်မှ ဒုတိယတစ်ခုဖြစ်ပါတယ်။

![The grove button connected to socket D5](../../../../../translated_images/my/pi-button.c7a1a4f55943341ce1baf1057658e9a205804d4131d258e820c93f951df0abf3.png)

## အသံဖမ်းယူခြင်း

Python code ကို အသုံးပြုပြီး မိုက်ခရိုဖုန်းကနေ အသံဖမ်းယူနိုင်ပါတယ်။

### လုပ်ဆောင်ရန် - အသံဖမ်းယူပါ

1. Pi ကို ဖွင့်ပြီး boot ပြီးအောင် စောင့်ပါ။

1. VS Code ကို Pi ပေါ်မှာ တိုက်ရိုက်ဖွင့်ပါ၊ သို့မဟုတ် Remote SSH extension ကို အသုံးပြုပြီး ချိတ်ဆက်ပါ။

1. PyAudio Pip package မှာ အသံဖမ်းယူခြင်းနဲ့ ပြန်ဖွင့်ခြင်းလုပ်ဆောင်နိုင်တဲ့ function တွေ ပါပါတယ်။ ဒီ package က audio libraries တချို့ကို အရင် install လုပ်ထားဖို့ လိုအပ်ပါတယ်။ terminal မှာ အောက်ပါ command တွေကို run လုပ်ပါ။

    ```sh
    sudo apt update
    sudo apt install libportaudio0 libportaudio2 libportaudiocpp0 portaudio19-dev libasound2-plugins --yes 
    ```

1. PyAudio Pip package ကို install လုပ်ပါ။

    ```sh
    pip3 install pyaudio
    ```

1. `smart-timer` လို့ခေါ်တဲ့ folder အသစ်တစ်ခု ဖန်တီးပြီး `app.py` ဆိုတဲ့ file ကို ဒီ folder ထဲထည့်ပါ။

1. ဒီ file ရဲ့ အပေါ်ဆုံးမှာ အောက်ပါ imports တွေ ထည့်ပါ။

    ```python
    import io
    import pyaudio
    import time
    import wave
    
    from grove.factory import Factory
    ```

    ဒါက `pyaudio` module, wave files ကို handle လုပ်တဲ့ standard Python modules, နဲ့ `grove.factory` module ကို import လုပ်ပြီး button class တစ်ခု ဖန်တီးဖို့ Factory ကို import လုပ်ပေးပါတယ်။

1. ဒီအောက်မှာ Grove ခလုတ်တစ်ခု ဖန်တီးဖို့ code ထည့်ပါ။

    ReSpeaker 2-Mics Pi HAT ကို အသုံးပြုနေပါက အောက်ပါ code ကို အသုံးပြုပါ။

    ```python
    # The button on the ReSpeaker 2-Mics Pi HAT
    button = Factory.getButton("GPIO-LOW", 17)
    ```

    ဒါက **D17** port ပေါ်မှာ ခလုတ်တစ်ခု ဖန်တီးပေးပါတယ်။ ဒီ port က ReSpeaker 2-Mics Pi HAT ရဲ့ ခလုတ်ချိတ်ဆက်ထားတဲ့ port ဖြစ်ပါတယ်။ ဒီခလုတ်ကို နှိပ်တဲ့အခါ low signal ပို့ပေးဖို့ ပြင်ဆင်ထားပါတယ်။

    ReSpeaker 2-Mics Pi HAT ကို မသုံးဘဲ Grove ခလုတ်ကို base hat နဲ့ ချိတ်ဆက်ထားပါက ဒီ code ကို အသုံးပြုပါ။

    ```python
    button = Factory.getButton("GPIO-HIGH", 5)
    ```

    ဒါက **D5** port ပေါ်မှာ high signal ပို့ပေးတဲ့ ခလုတ်တစ်ခု ဖန်တီးပေးပါတယ်။

1. PyAudio class ရဲ့ instance တစ်ခု ဖန်တီးပြီး audio ကို handle လုပ်ပါ။

    ```python
    audio = pyaudio.PyAudio()
    ```

1. မိုက်ခရိုဖုန်းနဲ့ စပီကာအတွက် hardware card number ကို သတ်မှတ်ပါ။ ဒီ number က သင် `arecord -l` နဲ့ `aplay -l` ကို run လုပ်ပြီး ရှာတွေ့ထားတဲ့ number ဖြစ်ပါတယ်။

    ```python
    microphone_card_number = <microphone card number>
    speaker_card_number = <speaker card number>
    ```

    `<microphone card number>` ကို သင့်မိုက်ခရိုဖုန်းရဲ့ card number နဲ့ အစားထိုးပါ။

    `<speaker card number>` ကို သင့်စပီကာရဲ့ card number နဲ့ အစားထိုးပါ၊ `alsa.conf` file မှာ သတ်မှတ်ထားတဲ့ အတူတူ number ဖြစ်ပါတယ်။

1. ဒီအောက်မှာ audio capture နဲ့ playback အတွက် sample rate ကို သတ်မှတ်ပါ။ သင်အသုံးပြုနေတဲ့ hardware အပေါ်မူတည်ပြီး ဒီ value ကို ပြောင်းလဲဖို့ လိုအပ်နိုင်ပါတယ်။

    ```python
    rate = 48000 #48KHz
    ```

    code ကို later run လုပ်တဲ့အခါ sample rate error တွေ ရလာပါက ဒီ value ကို `44100` သို့မဟုတ် `16000` အဖြစ် ပြောင်းပါ။ value ပိုမြင့်ရင် အသံအရည်အသွေး ပိုကောင်းပါတယ်။

1. ဒီအောက်မှာ `capture_audio` ဆိုတဲ့ function အသစ်တစ်ခု ဖန်တီးပါ။ ဒီ function ကို မိုက်ခရိုဖုန်းကနေ အသံဖမ်းယူဖို့ ခေါ်သုံးပါမယ်။

    ```python
    def capture_audio():
    ```

1. ဒီ function ရဲ့ အတွင်းမှာ အောက်ပါ code ကို ထည့်ပြီး အသံဖမ်းယူပါ။

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

    ဒီ code က PyAudio object ကို အသုံးပြုပြီး audio input stream တစ်ခု ဖွင့်ပေးပါတယ်။ ဒီ stream က မိုက်ခရိုဖုန်းကနေ 16KHz နဲ့ အသံဖမ်းယူပြီး 4096 bytes အရွယ်ရှိ buffer တွေထဲမှာ သိမ်းဆည်းပေးပါတယ်။

    code က Grove ခလုတ်ကို နှိပ်ထားတဲ့အချိန်မှာ loop လုပ်ပြီး buffer တွေကို array ထဲမှာ သိမ်းဆည်းပေးပါတယ်။

    > 💁 `open` method ကို pass လုပ်တဲ့ options တွေကို [PyAudio documentation](https://people.csail.mit.edu/hubert/pyaudio/docs/) မှာ ပိုမိုဖတ်ရှုနိုင်ပါတယ်။

    ခလုတ်ကို လွှတ်လိုက်တဲ့အခါ stream ကို stop လုပ်ပြီး ပိတ်ပေးပါတယ်။

1. ဒီ function ရဲ့ အဆုံးမှာ အောက်ပါ code ကို ထည့်ပါ။

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

    ဒီ code က binary buffer တစ်ခု ဖန်တီးပြီး ဖမ်းယူထားတဲ့ audio ကို [WAV file](https://wikipedia.org/wiki/WAV) အဖြစ် သိမ်းဆည်းပေးပါတယ်။ ဒါက uncompressed audio ကို file အဖြစ် သိမ်းဆည်းတဲ့ standard နည်းလမ်းဖြစ်ပါတယ်။ buffer ကို ပြန်ပေးပို့ပါတယ်။

1. `play_audio` function ကို ထည့်ပြီး audio buffer ကို ပြန်ဖွင့်ပါ။

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

    ဒီ function က output stream တစ်ခု ဖွင့်ပြီး audio ကို ပြန်ဖွင့်ပေးပါတယ်။ input stream နဲ့ settings တူတူကို အသုံးပြုပါတယ်။ buffer ကို wave file အဖြစ် ဖွင့်ပြီး output stream ထဲမှာ 4096 byte chunks အဖြစ်ရေးပြီး audio ကို play လုပ်ပေးပါတယ်။ stream ကို ပိတ်ပေးပါတယ်။

1. `capture_audio` function အောက်မှာ အောက်ပါ code ကို ထည့်ပါ။ ဒီ code က ခလုတ်ကို နှိပ်တဲ့အထိ loop လုပ်ပြီး ခလုတ်ကို နှိပ်လိုက်တဲ့အခါ audio ကို ဖမ်းယူပြီး ပြန်ဖွင့်ပေးပါတယ်။

    ```python
    while True:
        while not button.is_pressed():
            time.sleep(.1)
        
        buffer = capture_audio()
        play_audio(buffer)
    ```

1. code ကို run လုပ်ပါ။ ခလုတ်ကို နှိပ်ပြီး မိုက်ခရိုဖုန်းထဲမှာ စကားပြောပါ။ ခလုတ်ကို လွှတ်လိုက်တဲ့အခါ သင်ဖမ်းယူထားတဲ့ အသံကို ပြန်ကြားရပါမယ်။

    PyAudio instance ဖန်တီးတဲ့အခါ ALSA error တွေ ရနိုင်ပါတယ်။ ဒါက Pi ရဲ့ audio device configuration အတွက် ဖြစ်ပါတယ်။ ဒီ error တွေကို လျစ်လျူရှုနိုင်ပါတယ်။

    ```output
    pi@raspberrypi:~/smart-timer $ python3 app.py 
    ALSA lib pcm.c:2565:(snd_pcm_open_noupdate) Unknown PCM cards.pcm.front
    ALSA lib pcm.c:2565:(snd_pcm_open_noupdate) Unknown PCM cards.pcm.rear
    ALSA lib pcm.c:2565:(snd_pcm_open_noupdate) Unknown PCM cards.pcm.center_lfe
    ALSA lib pcm.c:2565:(snd_pcm_open_noupdate) Unknown PCM cards.pcm.side
    ```

    အောက်ပါ error ရလာပါက:

    ```output
    OSError: [Errno -9997] Invalid sample rate
    ```

    `rate` ကို `44100` သို့မဟုတ် `16000` အဖြစ် ပြောင်းပါ။

> 💁 ဒီ code ကို [code-record/pi](../../../../../6-consumer/lessons/1-speech-recognition/code-record/pi) folder မှာ ရှာနိုင်ပါတယ်။

😀 သင့်ရဲ့ အသံဖမ်းယူမှု အစီအစဉ်အောင်မြင်ခဲ့ပါပြီ!

---

**အကြောင်းကြားချက်**:  
ဤစာရွက်စာတမ်းကို AI ဘာသာပြန်ဝန်ဆောင်မှု [Co-op Translator](https://github.com/Azure/co-op-translator) ကို အသုံးပြု၍ ဘာသာပြန်ထားပါသည်။ ကျွန်ုပ်တို့သည် တိကျမှုအတွက် ကြိုးစားနေသော်လည်း၊ အလိုအလျောက် ဘာသာပြန်မှုများတွင် အမှားများ သို့မဟုတ် မတိကျမှုများ ပါရှိနိုင်သည်ကို သတိပြုပါ။ မူရင်းဘာသာစကားဖြင့် ရေးသားထားသော စာရွက်စာတမ်းကို အာဏာတရ အရင်းအမြစ်အဖြစ် သတ်မှတ်သင့်ပါသည်။ အရေးကြီးသော အချက်အလက်များအတွက် လူက ဘာသာပြန်မှု ဝန်ဆောင်မှုကို အကြံပြုပါသည်။ ဤဘာသာပြန်မှုကို အသုံးပြုခြင်းမှ ဖြစ်ပေါ်လာသော အလွဲအမှားများ သို့မဟုတ် အနားလွဲမှုများအတွက် ကျွန်ုပ်တို့သည် တာဝန်မယူပါ။