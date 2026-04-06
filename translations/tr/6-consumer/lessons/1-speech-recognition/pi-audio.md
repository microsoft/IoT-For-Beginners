# Ses Kaydı - Raspberry Pi

Bu dersin bu bölümünde, Raspberry Pi üzerinde ses kaydı yapmak için kod yazacaksınız. Ses kaydı bir düğme ile kontrol edilecek.

## Donanım

Raspberry Pi'nin ses kaydını kontrol etmek için bir düğmeye ihtiyacı var.

Kullanacağınız düğme bir Grove düğmesidir. Bu, bir sinyali açıp kapatan dijital bir sensördür. Bu düğmeler, düğmeye basıldığında yüksek sinyal, basılmadığında düşük sinyal gönderecek şekilde veya basıldığında düşük, basılmadığında yüksek sinyal gönderecek şekilde yapılandırılabilir.

Eğer mikrofon olarak ReSpeaker 2-Mics Pi HAT kullanıyorsanız, bu HAT üzerinde zaten bir düğme bulunduğundan ekstra bir düğme bağlamanıza gerek yoktur. Bir sonraki bölüme geçebilirsiniz.

### Düğmeyi Bağlama

Düğme, Grove tabanlı HAT'e bağlanabilir.

#### Görev - Düğmeyi Bağlayın

![Bir Grove düğmesi](../../../../../translated_images/tr/grove-button.a70cfbb809a85636.webp)

1. Grove kablosunun bir ucunu düğme modülündeki sokete takın. Kablo yalnızca tek bir yönde takılabilir.

1. Raspberry Pi kapalıyken, Grove kablosunun diğer ucunu Pi'ye bağlı Grove Base HAT üzerindeki **D5** işaretli dijital sokete bağlayın. Bu soket, GPIO pinlerinin yanındaki soket sırasının soldan ikinci soketidir.

![Düğme D5 soketine bağlı](../../../../../translated_images/tr/pi-button.c7a1a4f55943341c.webp)

## Ses Kaydı

Python kodu kullanarak mikrofondan ses kaydı yapabilirsiniz.

### Görev - Ses Kaydı Yapın

1. Pi'yi açın ve başlatılmasını bekleyin.

1. VS Code'u başlatın, ya doğrudan Pi üzerinde ya da Remote SSH uzantısı ile bağlanarak.

1. PyAudio Pip paketi, ses kaydı ve oynatma işlevlerini içerir. Bu paket, öncelikle bazı ses kütüphanelerinin yüklenmesini gerektirir. Terminalde aşağıdaki komutları çalıştırarak bu kütüphaneleri yükleyin:

    ```sh
    sudo apt update
    sudo apt install libportaudio0 libportaudio2 libportaudiocpp0 portaudio19-dev libasound2-plugins --yes 
    ```

1. PyAudio Pip paketini yükleyin.

    ```sh
    pip3 install pyaudio
    ```

1. `smart-timer` adında yeni bir klasör oluşturun ve bu klasöre `app.py` adında bir dosya ekleyin.

1. Bu dosyanın en üstüne aşağıdaki importları ekleyin:

    ```python
    import io
    import pyaudio
    import time
    import wave
    
    from grove.factory import Factory
    ```

    Bu, `pyaudio` modülünü, dalga dosyalarını işlemek için bazı standart Python modüllerini ve bir düğme sınıfı oluşturmak için `grove.factory` modülünü içe aktarır.

1. Bunun altına bir Grove düğmesi oluşturmak için kod ekleyin.

    Eğer ReSpeaker 2-Mics Pi HAT kullanıyorsanız, aşağıdaki kodu kullanın:

    ```python
    # The button on the ReSpeaker 2-Mics Pi HAT
    button = Factory.getButton("GPIO-LOW", 17)
    ```

    Bu, ReSpeaker 2-Mics Pi HAT üzerindeki düğmenin bağlı olduğu **D17** portunda bir düğme oluşturur. Bu düğme, basıldığında düşük sinyal gönderecek şekilde ayarlanmıştır.

    Eğer ReSpeaker 2-Mics Pi HAT kullanmıyorsanız ve Grove düğmesini tabanlı HAT'e bağladıysanız, bu kodu kullanın:

    ```python
    button = Factory.getButton("GPIO-HIGH", 5)
    ```

    Bu, **D5** portunda bir düğme oluşturur ve basıldığında yüksek sinyal gönderecek şekilde ayarlanmıştır.

1. Bunun altına, ses işlemlerini yönetmek için bir PyAudio sınıfı örneği oluşturun:

    ```python
    audio = pyaudio.PyAudio()
    ```

1. Mikrofon ve hoparlör için donanım kart numarasını tanımlayın. Bu, bu derste daha önce `arecord -l` ve `aplay -l` komutlarını çalıştırarak bulduğunuz numara olacaktır.

    ```python
    microphone_card_number = <microphone card number>
    speaker_card_number = <speaker card number>
    ```

    `<microphone card number>` yerine mikrofon kart numaranızı yazın.

    `<speaker card number>` yerine hoparlör kart numaranızı yazın, bu numara `alsa.conf` dosyasında ayarladığınız numarayla aynı olmalıdır.

1. Bunun altına, ses kaydı ve oynatma için kullanılacak örnekleme oranını tanımlayın. Kullandığınız donanıma bağlı olarak bu değeri değiştirmeniz gerekebilir.

    ```python
    rate = 48000 #48KHz
    ```

    Eğer bu kodu çalıştırırken örnekleme oranı hataları alırsanız, bu değeri `44100` veya `16000` olarak değiştirin. Değer ne kadar yüksek olursa, ses kalitesi o kadar iyi olur.

1. Bunun altına, `capture_audio` adında yeni bir fonksiyon oluşturun. Bu fonksiyon, mikrofondan ses kaydı yapmak için çağrılacaktır:

    ```python
    def capture_audio():
    ```

1. Bu fonksiyonun içine, ses kaydı yapmak için aşağıdaki kodu ekleyin:

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

    Bu kod, PyAudio nesnesini kullanarak bir ses giriş akışı açar. Bu akış, mikrofondan 16KHz hızında ses kaydeder ve 4096 baytlık tamponlar halinde yakalar.

    Kod, Grove düğmesi basılı olduğu sürece döngüye girer ve her seferinde bu 4096 baytlık tamponları bir diziye okur.

    > 💁 `open` metoduna geçirilen seçenekler hakkında daha fazla bilgi için [PyAudio belgelerine](https://people.csail.mit.edu/hubert/pyaudio/docs/) göz atabilirsiniz.

    Düğme bırakıldığında, akış durdurulur ve kapatılır.

1. Bu fonksiyonun sonuna aşağıdaki kodu ekleyin:

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

    Bu kod, bir ikili tampon oluşturur ve yakalanan tüm sesleri bir [WAV dosyası](https://wikipedia.org/wiki/WAV) olarak yazar. Bu, sıkıştırılmamış sesleri bir dosyaya yazmanın standart bir yoludur. Bu tampon daha sonra döndürülür.

1. Ses tamponunu oynatmak için aşağıdaki `play_audio` fonksiyonunu ekleyin:

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

    Bu fonksiyon, ses çalmak için bir ses çıkış akışı açar. Giriş akışı ile aynı ayarları kullanır. Tampon, bir dalga dosyası olarak açılır ve 4096 baytlık parçalar halinde çıkış akışına yazılarak ses çalınır. Akış daha sonra kapatılır.

1. `capture_audio` fonksiyonunun altına aşağıdaki kodu ekleyin. Bu kod, düğme basılana kadar döngüye girer. Düğme basıldığında ses kaydedilir ve ardından çalınır.

    ```python
    while True:
        while not button.is_pressed():
            time.sleep(.1)
        
        buffer = capture_audio()
        play_audio(buffer)
    ```

1. Kodu çalıştırın. Düğmeye basın ve mikrofona konuşun. İşiniz bittiğinde düğmeyi bırakın ve kaydı dinleyin.

    PyAudio örneği oluşturulduğunda bazı ALSA hataları alabilirsiniz. Bu, Pi üzerindeki ses cihazları için yapılandırmadan kaynaklanır ve bu hataları görmezden gelebilirsiniz.

    ```output
    pi@raspberrypi:~/smart-timer $ python3 app.py 
    ALSA lib pcm.c:2565:(snd_pcm_open_noupdate) Unknown PCM cards.pcm.front
    ALSA lib pcm.c:2565:(snd_pcm_open_noupdate) Unknown PCM cards.pcm.rear
    ALSA lib pcm.c:2565:(snd_pcm_open_noupdate) Unknown PCM cards.pcm.center_lfe
    ALSA lib pcm.c:2565:(snd_pcm_open_noupdate) Unknown PCM cards.pcm.side
    ```

    Eğer aşağıdaki hatayı alırsanız:

    ```output
    OSError: [Errno -9997] Invalid sample rate
    ```

    `rate` değerini `44100` veya `16000` olarak değiştirin.

> 💁 Bu kodu [code-record/pi](../../../../../6-consumer/lessons/1-speech-recognition/code-record/pi) klasöründe bulabilirsiniz.

😀 Ses kaydı programınız başarılı oldu!

---

**Feragatname**:  
Bu belge, AI çeviri hizmeti [Co-op Translator](https://github.com/Azure/co-op-translator) kullanılarak çevrilmiştir. Doğruluk için çaba göstersek de, otomatik çevirilerin hata veya yanlışlıklar içerebileceğini lütfen unutmayın. Belgenin orijinal dili, yetkili kaynak olarak kabul edilmelidir. Kritik bilgiler için profesyonel insan çevirisi önerilir. Bu çevirinin kullanımından kaynaklanan yanlış anlamalar veya yanlış yorumlamalar için sorumluluk kabul etmiyoruz.