<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "c0550b254b9ba2539baf1e6bb5fc05f8",
  "translation_date": "2025-08-28T03:03:13+00:00",
  "source_file": "6-consumer/lessons/1-speech-recognition/virtual-device-speech-to-text.md",
  "language_code": "tr"
}
-->
# Konuşmadan Metne - Sanal IoT Cihazı

Bu dersin bu bölümünde, mikrofonunuzdan alınan konuşmayı konuşma hizmetini kullanarak metne dönüştürmek için kod yazacaksınız.

## Konuşmayı Metne Dönüştürme

Windows, Linux ve macOS'ta, konuşma hizmetlerinin Python SDK'sı mikrofonunuzu dinlemek ve algılanan konuşmayı metne dönüştürmek için kullanılabilir. Sürekli olarak dinler, ses seviyelerini algılar ve konuşma bloğunun sonunda ses seviyesi düştüğünde konuşmayı metne dönüştürmek için gönderir.

### Görev - Konuşmayı Metne Dönüştürme

1. Bilgisayarınızda `smart-timer` adlı bir klasörde `app.py` adlı tek bir dosya ve bir Python sanal ortamı ile yeni bir Python uygulaması oluşturun.

1. Konuşma hizmetleri için Pip paketini yükleyin. Sanal ortamın aktif olduğu bir terminalden yüklediğinizden emin olun.

    ```sh
    pip install azure-cognitiveservices-speech
    ```

    > ⚠️ Eğer aşağıdaki hatayı alırsanız:
    >
    > ```output
    > ERROR: Could not find a version that satisfies the requirement azure-cognitiveservices-speech (from versions: none)
    > ERROR: No matching distribution found for azure-cognitiveservices-speech
    > ```
    >
    > Pip'i güncellemeniz gerekecek. Bunu aşağıdaki komutla yapın ve ardından paketi tekrar yüklemeyi deneyin:
    >
    > ```sh
    > pip install --upgrade pip
    > ```

1. `app.py` dosyasına aşağıdaki importları ekleyin:

    ```python
    import requests
    import time
    from azure.cognitiveservices.speech import SpeechConfig, SpeechRecognizer
    ```

    Bu, konuşmayı tanımak için kullanılan bazı sınıfları içe aktarır.

1. Bazı yapılandırmaları tanımlamak için aşağıdaki kodu ekleyin:

    ```python
    speech_api_key = '<key>'
    location = '<location>'
    language = '<language>'

    recognizer_config = SpeechConfig(subscription=speech_api_key,
                                     region=location,
                                     speech_recognition_language=language)
    ```

    `<key>` kısmını konuşma hizmetinizin API anahtarı ile değiştirin. `<location>` kısmını konuşma hizmeti kaynağını oluşturduğunuz konum ile değiştirin.

    `<language>` kısmını konuşacağınız dilin yerel adı ile değiştirin, örneğin İngilizce için `en-GB` veya Kantonca için `zn-HK`. Desteklenen diller ve yerel adlarının listesini [Microsoft dokümanlarındaki Dil ve ses desteği dokümantasyonunda](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text) bulabilirsiniz.

    Bu yapılandırma, konuşma hizmetlerini yapılandırmak için kullanılacak bir `SpeechConfig` nesnesi oluşturmak için kullanılır.

1. Bir konuşma tanıyıcı oluşturmak için aşağıdaki kodu ekleyin:

    ```python
    recognizer = SpeechRecognizer(speech_config=recognizer_config)
    ```

1. Konuşma tanıyıcı, bir arka plan iş parçacığında çalışır, sesi dinler ve içindeki konuşmayı metne dönüştürür. Metni bir geri çağırma fonksiyonu kullanarak alabilirsiniz - tanıyıcıya tanımlayıp ilettiğiniz bir fonksiyon. Her konuşma algılandığında, geri çağırma fonksiyonu çağrılır. Aşağıdaki kodu ekleyerek bir geri çağırma tanımlayın ve bu geri çağırmayı tanıyıcıya iletin, ayrıca metni işlemek için bir fonksiyon tanımlayın ve bunu konsola yazdırın:

    ```python
    def process_text(text):
        print(text)

    def recognized(args):
        process_text(args.result.text)
    
    recognizer.recognized.connect(recognized)
    ```

1. Tanıyıcı yalnızca açıkça başlatıldığında dinlemeye başlar. Tanımayı başlatmak için aşağıdaki kodu ekleyin. Bu arka planda çalışır, bu nedenle uygulamanızın çalışmaya devam etmesi için uyuyan bir sonsuz döngüye ihtiyacı olacaktır.

    ```python
    recognizer.start_continuous_recognition()

    while True:
        time.sleep(1)
    ```

1. Bu uygulamayı çalıştırın. Mikrofonunuza konuşun ve metne dönüştürülen sesin konsola çıktısını alın.

    ```output
    (.venv) ➜  smart-timer python3 app.py
    Hello world.
    Welcome to IoT for beginners.
    ```

    Farklı türde cümleler deneyin, ayrıca kelimelerin aynı şekilde ses çıkarıp farklı anlamlara sahip olduğu cümleler deneyin. Örneğin, İngilizce konuşuyorsanız, 'I want to buy two bananas and an apple too' deyin ve kelimenin sadece sesine değil, bağlamına göre doğru "to", "two" ve "too" kullanıldığını fark edin.

> 💁 Bu kodu [code-speech-to-text/virtual-iot-device](../../../../../6-consumer/lessons/1-speech-recognition/code-speech-to-text/virtual-iot-device) klasöründe bulabilirsiniz.

😀 Konuşmadan metne programınız başarılı oldu!

---

**Feragatname**:  
Bu belge, AI çeviri hizmeti [Co-op Translator](https://github.com/Azure/co-op-translator) kullanılarak çevrilmiştir. Doğruluk için çaba göstersek de, otomatik çevirilerin hata veya yanlışlıklar içerebileceğini lütfen unutmayın. Belgenin orijinal dili, yetkili kaynak olarak kabul edilmelidir. Kritik bilgiler için profesyonel insan çevirisi önerilir. Bu çevirinin kullanımından kaynaklanan yanlış anlamalar veya yanlış yorumlamalar için sorumluluk kabul etmiyoruz.