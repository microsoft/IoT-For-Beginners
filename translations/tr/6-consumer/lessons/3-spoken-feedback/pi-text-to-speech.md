<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "606f3af1c78e3741e48ce77c31cea626",
  "translation_date": "2025-08-28T02:58:31+00:00",
  "source_file": "6-consumer/lessons/3-spoken-feedback/pi-text-to-speech.md",
  "language_code": "tr"
}
-->
# Metinden Konuşmaya - Raspberry Pi

Bu dersin bu bölümünde, konuşma hizmetini kullanarak metni konuşmaya dönüştüren bir kod yazacaksınız.

## Konuşma Hizmetini Kullanarak Metni Konuşmaya Dönüştürme

Metin, IoT cihazınızda çalınabilecek bir ses dosyası olarak konuşma hizmetine REST API kullanılarak gönderilebilir. Konuşma talep ederken, kullanılacak sesi belirtmeniz gerekir çünkü konuşma, farklı sesler kullanılarak oluşturulabilir.

Her dil, çeşitli sesleri destekler ve her dil için desteklenen seslerin listesini almak için konuşma hizmetine bir REST isteği gönderebilirsiniz.

### Görev - Bir Ses Alın

1. VS Code'da `smart-timer` projesini açın.

1. Bir dil için ses listesini talep etmek üzere `say` fonksiyonunun üstüne aşağıdaki kodu ekleyin:

    ```python
    def get_voice():
        url = f'https://{location}.tts.speech.microsoft.com/cognitiveservices/voices/list'
    
        headers = {
            'Authorization': 'Bearer ' + get_access_token()
        }
    
        response = requests.get(url, headers=headers)
        voices_json = json.loads(response.text)
    
        first_voice = next(x for x in voices_json if x['Locale'].lower() == language.lower() and x['VoiceType'] == 'Neural')
        return first_voice['ShortName']
    
    voice = get_voice()
    print(f'Using voice {voice}')
    ```

    Bu kod, konuşma hizmetini kullanarak bir ses listesi alan `get_voice` adlı bir fonksiyon tanımlar. Daha sonra kullanılan dile uyan ilk sesi bulur.

    Bu fonksiyon, ilk sesi saklamak ve ses adını konsola yazdırmak için çağrılır. Bu ses bir kez talep edilebilir ve metni konuşmaya dönüştürmek için yapılan her çağrıda kullanılabilir.

    > 💁 Desteklenen seslerin tam listesini [Microsoft Docs'taki Dil ve Ses Desteği dokümanından](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#text-to-speech) alabilirsiniz. Belirli bir sesi kullanmak istiyorsanız, bu fonksiyonu kaldırabilir ve bu dokümandan ses adını sabit kodlayabilirsiniz. Örneğin:
    >
    > ```python
    > voice = 'hi-IN-SwaraNeural'
    > ```

### Görev - Metni Konuşmaya Dönüştürme

1. Bunun altına, konuşma hizmetlerinden alınacak ses formatı için bir sabit tanımlayın. Ses talep ettiğinizde, bunu farklı formatlarda yapabilirsiniz.

    ```python
    playback_format = 'riff-48khz-16bit-mono-pcm'
    ```

    Kullanabileceğiniz format, donanımınıza bağlıdır. Eğer sesi çalarken `Invalid sample rate` (Geçersiz örnekleme oranı) hataları alırsanız, bunu başka bir değere değiştirin. Desteklenen değerlerin listesini [Microsoft Docs'taki Metinden Konuşmaya REST API dokümanında](https://docs.microsoft.com/azure/cognitive-services/speech-service/rest-text-to-speech?WT.mc_id=academic-17441-jabenn#audio-outputs) bulabilirsiniz. `riff` formatında ses kullanmanız gerekecek ve denemeniz gereken değerler `riff-16khz-16bit-mono-pcm`, `riff-24khz-16bit-mono-pcm` ve `riff-48khz-16bit-mono-pcm` olacaktır.

1. Bunun altına, konuşma hizmeti REST API'sini kullanarak metni konuşmaya dönüştürecek `get_speech` adlı bir fonksiyon tanımlayın:

    ```python
    def get_speech(text):
    ```

1. `get_speech` fonksiyonunda, çağrılacak URL'yi ve gönderilecek başlıkları tanımlayın:

    ```python
        url = f'https://{location}.tts.speech.microsoft.com/cognitiveservices/v1'
    
        headers = {
            'Authorization': 'Bearer ' + get_access_token(),
            'Content-Type': 'application/ssml+xml',
            'X-Microsoft-OutputFormat': playback_format
        }
    ```

    Bu, bir erişim jetonu oluşturmak, içeriği SSML olarak ayarlamak ve gerekli ses formatını tanımlamak için başlıkları ayarlar.

1. Bunun altına, REST API'ye gönderilecek SSML'yi tanımlayın:

    ```python
    ssml =  f'<speak version=\'1.0\' xml:lang=\'{language}\'>'
    ssml += f'<voice xml:lang=\'{language}\' name=\'{voice}\'>'
    ssml += text
    ssml += '</voice>'
    ssml += '</speak>'
    ```

    Bu SSML, kullanılacak dili ve sesi, ayrıca dönüştürülecek metni ayarlar.

1. Son olarak, bu fonksiyona REST isteği yapacak ve ikili ses verilerini döndürecek kodu ekleyin:

    ```python
    response = requests.post(url, headers=headers, data=ssml.encode('utf-8'))
    return io.BytesIO(response.content)
    ```

### Görev - Sesi Çalma

1. `get_speech` fonksiyonunun altına, REST API çağrısından dönen sesi çalmak için yeni bir fonksiyon tanımlayın:

    ```python
    def play_speech(speech):
    ```

1. Bu fonksiyona geçirilen `speech`, REST API'den dönen ikili ses verisi olacaktır. Bu veriyi bir dalga dosyası olarak açmak ve PyAudio kullanarak çalmak için aşağıdaki kodu kullanın:

    ```python
    def play_speech(speech):
        with wave.open(speech, 'rb') as wave_file:
            stream = audio.open(format=audio.get_format_from_width(wave_file.getsampwidth()),
                                channels=wave_file.getnchannels(),
                                rate=wave_file.getframerate(),
                                output_device_index=speaker_card_number,
                                output=True)

            data = wave_file.readframes(4096)

            while len(data) > 0:
                stream.write(data)
                data = wave_file.readframes(4096)

            stream.stop_stream()
            stream.close()
    ```

    Bu kod, bir PyAudio akışı kullanır; ses kaydetme işlemine benzer. Buradaki fark, akışın bir çıkış akışı olarak ayarlanması ve ses verilerinden okunan verilerin akışa aktarılmasıdır.

    Akış detaylarını sabit kodlamak yerine, bunlar ses verilerinden okunur.

1. `say` fonksiyonunun içeriğini aşağıdakiyle değiştirin:

    ```python
    speech = get_speech(text)
    play_speech(speech)
    ```

    Bu kod, metni ikili ses verisi olarak konuşmaya dönüştürür ve sesi çalar.

1. Uygulamayı çalıştırın ve işlev uygulamasının da çalıştığından emin olun. Bazı zamanlayıcılar ayarlayın; zamanlayıcınızın ayarlandığını söyleyen bir sesli yanıt ve zamanlayıcı tamamlandığında başka bir sesli yanıt duyacaksınız.

    Eğer `Invalid sample rate` hataları alırsanız, yukarıda açıklandığı gibi `playback_format` değerini değiştirin.

> 💁 Bu kodu [code-spoken-response/pi](../../../../../6-consumer/lessons/3-spoken-feedback/code-spoken-response/pi) klasöründe bulabilirsiniz.

😀 Zamanlayıcı programınız başarılı oldu!

---

**Feragatname**:  
Bu belge, AI çeviri hizmeti [Co-op Translator](https://github.com/Azure/co-op-translator) kullanılarak çevrilmiştir. Doğruluk için çaba göstersek de, otomatik çevirilerin hata veya yanlışlıklar içerebileceğini lütfen unutmayın. Belgenin orijinal dili, yetkili kaynak olarak kabul edilmelidir. Kritik bilgiler için profesyonel insan çevirisi önerilir. Bu çevirinin kullanımından kaynaklanan yanlış anlamalar veya yanlış yorumlamalardan sorumlu değiliz.