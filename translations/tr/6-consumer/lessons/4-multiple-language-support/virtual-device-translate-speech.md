<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "d620a470d9dd8614d99824832978360a",
  "translation_date": "2025-08-28T03:10:59+00:00",
  "source_file": "6-consumer/lessons/4-multiple-language-support/virtual-device-translate-speech.md",
  "language_code": "tr"
}
-->
# Konuşmayı Çevir - Sanal IoT Cihazı

Bu dersin bu bölümünde, konuşmayı metne dönüştürürken konuşma hizmetini kullanarak çeviri yapacak, ardından metni Translator hizmetiyle çevirip sesli bir yanıt oluşturacaksınız.

## Konuşma hizmetini kullanarak konuşmayı çevirin

Konuşma hizmeti, konuşmayı yalnızca aynı dilde metne dönüştürmekle kalmaz, aynı zamanda çıktıyı diğer dillere çevirebilir.

### Görev - konuşma hizmetini kullanarak konuşmayı çevirin

1. VS Code'da `smart-timer` projesini açın ve terminalde sanal ortamın yüklü olduğundan emin olun.

1. Mevcut import ifadelerinin altına aşağıdaki import ifadelerini ekleyin:

    ```python
    from azure.cognitiveservices import speech
    from azure.cognitiveservices.speech.translation import SpeechTranslationConfig, TranslationRecognizer
    import requests
    ```

    Bu, konuşmayı çevirmek için kullanılan sınıfları ve bu derste daha sonra Translator hizmetine çağrı yapmak için kullanılacak `requests` kütüphanesini içe aktarır.

1. Akıllı zamanlayıcınızda 2 dil ayarlanmış olacak - LUIS'i eğitmek için kullanılan sunucu dili (aynı dil, kullanıcıya konuşulacak mesajları oluşturmak için de kullanılır) ve kullanıcının konuştuğu dil. `language` değişkenini, kullanıcının konuşacağı dil olacak şekilde güncelleyin ve LUIS'i eğitmek için kullanılan dil için `server_language` adında yeni bir değişken ekleyin:

    ```python
    language = '<user language>'
    server_language = '<server language>'
    ```

    `<user language>` yerine, konuşacağınız dilin yerel ayar adını yazın, örneğin Fransızca için `fr-FR` veya Kantonca için `zn-HK`.

    `<server language>` yerine, LUIS'i eğitmek için kullanılan dilin yerel ayar adını yazın.

    Desteklenen dillerin ve yerel ayar adlarının bir listesini [Microsoft dokümanlarındaki Dil ve ses desteği dokümanında](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text) bulabilirsiniz.

    > 💁 Birden fazla dil konuşamıyorsanız, tercih ettiğiniz dilden başka bir dile çeviri yapmak için [Bing Translate](https://www.bing.com/translator) veya [Google Translate](https://translate.google.com) gibi bir hizmet kullanabilirsiniz. Bu hizmetler, çevrilen metnin sesini çalabilir. Ancak, konuşma tanıyıcı cihazınızdan gelen bazı ses çıkışlarını yok sayabilir, bu nedenle çevrilen metni çalmak için ek bir cihaz kullanmanız gerekebilir.
    >
    > Örneğin, LUIS'i İngilizce olarak eğitirseniz ancak kullanıcı dili olarak Fransızca kullanmak isterseniz, "set a 2 minute and 27 second timer" gibi cümleleri İngilizceden Fransızcaya Bing Translate kullanarak çevirebilir, ardından çeviriyi mikrofonunuza konuşmak için **Dinle çevirisi** düğmesini kullanabilirsiniz.
    >
    > ![Bing Translate'deki dinle çevirisi düğmesi](../../../../../translated_images/tr/bing-translate.348aa796d6efe2a92f41ea74a5cf42bb4c63d6faaa08e7f46924e072a35daa48.png)

1. `recognizer_config` ve `recognizer` tanımlarını aşağıdakiyle değiştirin:

    ```python
    translation_config = SpeechTranslationConfig(subscription=speech_api_key,
                                                 region=location,
                                                 speech_recognition_language=language,
                                                 target_languages=(language, server_language))
    
    recognizer = TranslationRecognizer(translation_config=translation_config)
    ```

    Bu, kullanıcı dilinde konuşmayı tanımak ve kullanıcı ve sunucu dilinde çeviriler oluşturmak için bir çeviri yapılandırması oluşturur. Daha sonra bu yapılandırmayı, konuşma tanımanın çıktısını birden fazla dile çevirebilen bir konuşma tanıyıcı olan bir çeviri tanıyıcı oluşturmak için kullanır.

    > 💁 Orijinal dilin `target_languages` içinde belirtilmesi gerekir, aksi takdirde herhangi bir çeviri almazsınız.

1. `recognized` fonksiyonunu güncelleyin ve fonksiyonun tüm içeriğini aşağıdakiyle değiştirin:

    ```python
    if args.result.reason == speech.ResultReason.TranslatedSpeech:
        language_match = next(l for l in args.result.translations if server_language.lower().startswith(l.lower()))
        text = args.result.translations[language_match]
        if (len(text) > 0):
            print(f'Translated text: {text}')
    
            message = Message(json.dumps({ 'speech': text }))
            device_client.send_message(message)
    ```

    Bu kod, tanınan olayın konuşmanın çevrilmesi nedeniyle mi tetiklendiğini kontrol eder (bu olay, konuşma tanındığında ancak çevrilmediğinde gibi başka zamanlarda da tetiklenebilir). Konuşma çevrildiyse, `args.result.translations` sözlüğünde sunucu diliyle eşleşen çeviriyi bulur.

    `args.result.translations` sözlüğü, yerel ayar ayarının tamamı yerine dil kısmına göre anahtarlanır. Örneğin, Fransızca için `fr-FR` çevirisi isterseniz, sözlükte `fr-FR` yerine `fr` için bir giriş bulunur.

    Çevrilen metin daha sonra IoT Hub'a gönderilir.

1. Çevirileri test etmek için bu kodu çalıştırın. Fonksiyon uygulamanızın çalıştığından emin olun ve ya kendiniz o dili konuşarak ya da bir çeviri uygulaması kullanarak kullanıcı dilinde bir zamanlayıcı isteyin.

    ```output
    (.venv) ➜  smart-timer python app.py
    Connecting
    Connected
    Translated text: Set a timer of 2 minutes and 27 seconds.
    ```

## Translator hizmetini kullanarak metni çevirin

Konuşma hizmeti, metni tekrar sese çevirme çevirisini desteklemez, bunun yerine metni çevirmek için Translator hizmetini kullanabilirsiniz. Bu hizmet, metni çevirmek için kullanabileceğiniz bir REST API sağlar.

### Görev - Translator kaynağını kullanarak metni çevirin

1. `speech_api_key` altına Translator API anahtarını ekleyin:

    ```python
    translator_api_key = '<key>'
    ```

    `<key>` yerine Translator hizmeti kaynağınız için API anahtarını yazın.

1. `say` fonksiyonunun üstüne, sunucu dilinden kullanıcı diline metin çevirecek bir `translate_text` fonksiyonu tanımlayın:

    ```python
    def translate_text(text):
    ```

1. Bu fonksiyonun içinde, REST API çağrısı için URL ve başlıkları tanımlayın:

    ```python
    url = f'https://api.cognitive.microsofttranslator.com/translate?api-version=3.0'

    headers = {
        'Ocp-Apim-Subscription-Key': translator_api_key,
        'Ocp-Apim-Subscription-Region': location,
        'Content-type': 'application/json'
    }
    ```

    Bu API'nin URL'si konuma özgü değildir, bunun yerine konum bir başlık olarak iletilir. API anahtarı doğrudan kullanılır, bu nedenle konuşma hizmetinden farklı olarak, token sağlayıcı API'den bir erişim belirteci almanıza gerek yoktur.

1. Bunun altına çağrı için parametreleri ve gövdeyi tanımlayın:

    ```python
    params = {
        'from': server_language,
        'to': language
    }

    body = [{
        'text' : text
    }]
    ```

    `params`, API çağrısına iletilecek parametreleri tanımlar ve `from` ve `to` dillerini iletir. Bu çağrı, `from` dilindeki metni `to` diline çevirecektir.

    `body`, çevrilecek metni içerir. Bu bir dizidir, çünkü aynı çağrıda birden fazla metin bloğu çevrilebilir.

1. REST API'yi çağırın ve yanıtı alın:

    ```python
    response = requests.post(url, headers=headers, params=params, json=body)
    ```

    Gelen yanıt, bir JSON dizisidir ve çevrilen metinleri içeren bir öğe içerir. Bu öğe, gövdede iletilen tüm öğelerin çevirileri için bir dizi içerir.

    ```json
    [
        {
            "translations": [
                {
                    "text": "Chronométrant votre minuterie de 2 minutes 27 secondes.",
                    "to": "fr"
                }
            ]
        }
    ]
    ```

1. Dizideki ilk öğeden ilk çevirinin `text` özelliğini döndürün:

    ```python
    return response.json()[0]['translations'][0]['text']
    ```

1. `say` fonksiyonunu, SSML oluşturulmadan önce söylenecek metni çevirecek şekilde güncelleyin:

    ```python
    print('Original:', text)
    text = translate_text(text)
    print('Translated:', text)
    ```

    Bu kod ayrıca orijinal ve çevrilmiş metin sürümlerini konsola yazdırır.

1. Kodunuzu çalıştırın. Fonksiyon uygulamanızın çalıştığından emin olun ve ya kendiniz o dili konuşarak ya da bir çeviri uygulaması kullanarak kullanıcı dilinde bir zamanlayıcı isteyin.

    ```output
    (.venv) ➜  smart-timer python app.py
    Connecting
    Connected
    Translated text: Set a timer of 2 minutes and 27 seconds.
    Original: 2 minute 27 second timer started.
    Translated: 2 minute 27 seconde minute a commencé.
    Original: Times up on your 2 minute 27 second timer.
    Translated: Chronométrant votre minuterie de 2 minutes 27 secondes.
    ```

    > 💁 Farklı dillerde bir şey söylemenin farklı yolları nedeniyle, LUIS'e verdiğiniz örneklerden biraz farklı çeviriler alabilirsiniz. Bu durumda, LUIS'e daha fazla örnek ekleyin, yeniden eğitin ve ardından modeli yeniden yayınlayın.

> 💁 Bu kodu [code/virtual-iot-device](../../../../../6-consumer/lessons/4-multiple-language-support/code/virtual-iot-device) klasöründe bulabilirsiniz.

😀 Çok dilli zamanlayıcı programınız başarılı oldu!

---

**Feragatname**:  
Bu belge, AI çeviri hizmeti [Co-op Translator](https://github.com/Azure/co-op-translator) kullanılarak çevrilmiştir. Doğruluğu sağlamak için çaba göstersek de, otomatik çevirilerin hata veya yanlışlık içerebileceğini lütfen unutmayın. Belgenin orijinal dili, yetkili kaynak olarak kabul edilmelidir. Kritik bilgiler için profesyonel insan çevirisi önerilir. Bu çevirinin kullanımından kaynaklanan yanlış anlamalar veya yanlış yorumlamalardan sorumlu değiliz.