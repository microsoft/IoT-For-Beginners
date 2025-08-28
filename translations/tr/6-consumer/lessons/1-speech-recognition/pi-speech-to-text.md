<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "af249a24d4fe4f4de4806adbc3bc9d86",
  "translation_date": "2025-08-28T03:04:52+00:00",
  "source_file": "6-consumer/lessons/1-speech-recognition/pi-speech-to-text.md",
  "language_code": "tr"
}
-->
# Konuşmadan Metne - Raspberry Pi

Bu dersin bu bölümünde, yakalanan sesli kayıttaki konuşmayı metne dönüştürmek için konuşma hizmetini kullanarak kod yazacaksınız.

## Sesi konuşma hizmetine gönderme

Ses, REST API kullanılarak konuşma hizmetine gönderilebilir. Konuşma hizmetini kullanmak için önce bir erişim belirteci (access token) talep etmeniz gerekir, ardından bu belirteci REST API'ye erişmek için kullanabilirsiniz. Bu erişim belirteçleri 10 dakika sonra sona erer, bu yüzden kodunuzun düzenli olarak yeni belirteç talep etmesi ve her zaman güncel olmasını sağlaması gerekir.

### Görev - erişim belirteci alın

1. Pi'nizdeki `smart-timer` projesini açın.

1. `play_audio` fonksiyonunu kaldırın. Artık buna ihtiyacınız yok çünkü akıllı zamanlayıcının size söylediklerinizi tekrar etmesini istemiyorsunuz.

1. `app.py` dosyasının en üstüne aşağıdaki import'u ekleyin:

    ```python
    import requests
    ```

1. Konuşma hizmeti için bazı ayarları tanımlamak üzere `while True` döngüsünün üstüne aşağıdaki kodu ekleyin:

    ```python
    speech_api_key = '<key>'
    location = '<location>'
    language = '<language>'
    ```

    `<key>` kısmını konuşma hizmeti kaynağınızın API anahtarı ile değiştirin. `<location>` kısmını konuşma hizmeti kaynağını oluşturduğunuz konum ile değiştirin.

    `<language>` kısmını konuşacağınız dilin yerel adı ile değiştirin, örneğin İngilizce için `en-GB` veya Kantonca için `zn-HK`. Desteklenen diller ve yerel adlarının listesini [Microsoft dokümanlarındaki Dil ve ses desteği dokümantasyonunda](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text) bulabilirsiniz.

1. Bunun altına, bir erişim belirteci almak için aşağıdaki fonksiyonu ekleyin:

    ```python
    def get_access_token():
        headers = {
            'Ocp-Apim-Subscription-Key': speech_api_key
        }
    
        token_endpoint = f'https://{location}.api.cognitive.microsoft.com/sts/v1.0/issuetoken'
        response = requests.post(token_endpoint, headers=headers)
        return str(response.text)
    ```

    Bu, API anahtarını bir başlık olarak geçirerek bir belirteç verme uç noktasını çağırır. Bu çağrı, konuşma hizmetlerini çağırmak için kullanılabilecek bir erişim belirteci döndürür.

1. Bunun altına, yakalanan sesli kayıttaki konuşmayı REST API kullanarak metne dönüştürmek için bir fonksiyon tanımlayın:

    ```python
    def convert_speech_to_text(buffer):
    ```

1. Bu fonksiyonun içinde, REST API URL'sini ve başlıklarını ayarlayın:

    ```python
    url = f'https://{location}.stt.speech.microsoft.com/speech/recognition/conversation/cognitiveservices/v1'

    headers = {
        'Authorization': 'Bearer ' + get_access_token(),
        'Content-Type': f'audio/wav; codecs=audio/pcm; samplerate={rate}',
        'Accept': 'application/json;text/xml'
    }

    params = {
        'language': language
    }
    ```

    Bu, konuşma hizmeti kaynağının konumunu kullanarak bir URL oluşturur. Ardından, `get_access_token` fonksiyonundan gelen erişim belirtecini, ses kaydı için kullanılan örnekleme oranını başlıklara ekler. Son olarak, URL ile birlikte geçilecek dil bilgilerini içeren bazı parametreler tanımlar.

1. Bunun altına, REST API'yi çağırmak ve metni geri almak için aşağıdaki kodu ekleyin:

    ```python
    response = requests.post(url, headers=headers, params=params, data=buffer)
    response_json = response.json()

    if response_json['RecognitionStatus'] == 'Success':
        return response_json['DisplayText']
    else:
        return ''
    ```

    Bu, URL'yi çağırır ve yanıt olarak gelen JSON değerini çözümler. Yanıttaki `RecognitionStatus` değeri, çağrının konuşmayı başarıyla metne dönüştürüp dönüştüremediğini belirtir. Eğer bu değer `Success` ise, metin fonksiyondan döndürülür, aksi takdirde boş bir string döndürülür.

1. `while True:` döngüsünün üstüne, konuşmadan metne hizmetinden dönen metni işlemek için bir fonksiyon tanımlayın. Bu fonksiyon şimdilik sadece metni konsola yazdıracaktır.

    ```python
    def process_text(text):
        print(text)
    ```

1. Son olarak, `while True` döngüsündeki `play_audio` çağrısını `convert_speech_to_text` fonksiyonuna bir çağrı ile değiştirin ve metni `process_text` fonksiyonuna iletin:

    ```python
    text = convert_speech_to_text(buffer)
    process_text(text)
    ```

1. Kodu çalıştırın. Düğmeye basın ve mikrofona konuşun. İşiniz bittiğinde düğmeyi bırakın ve ses metne dönüştürülerek konsola yazdırılsın.

    ```output
    pi@raspberrypi:~/smart-timer $ python3 app.py 
    Hello world.
    Welcome to IoT for beginners.
    ```

    Farklı türde cümleler deneyin, ayrıca aynı seslere sahip ancak farklı anlamlara sahip kelimeler içeren cümleler deneyin. Örneğin, İngilizce konuşuyorsanız, 'I want to buy two bananas and an apple too' deyin ve bağlamına göre doğru "to", "two" ve "too" kelimelerinin nasıl kullanıldığını fark edin, sadece sesine göre değil.

> 💁 Bu kodu [code-speech-to-text/pi](../../../../../6-consumer/lessons/1-speech-recognition/code-speech-to-text/pi) klasöründe bulabilirsiniz.

😀 Konuşmadan metne programınız başarılı oldu!

---

**Feragatname**:  
Bu belge, AI çeviri hizmeti [Co-op Translator](https://github.com/Azure/co-op-translator) kullanılarak çevrilmiştir. Doğruluk için çaba göstersek de, otomatik çevirilerin hata veya yanlışlıklar içerebileceğini lütfen unutmayın. Belgenin orijinal dili, yetkili kaynak olarak kabul edilmelidir. Kritik bilgiler için profesyonel insan çevirisi önerilir. Bu çevirinin kullanımından kaynaklanan yanlış anlamalar veya yanlış yorumlamalar için sorumluluk kabul etmiyoruz.