# Konuşmayı Çevir - Raspberry Pi

Bu dersin bu bölümünde, çevirmen hizmetini kullanarak metni çevirmek için kod yazacaksınız.

## Çevirmen hizmetini kullanarak metni sese dönüştürme

Konuşma hizmeti REST API'si doğrudan çevirileri desteklemez, bunun yerine konuşmadan metne hizmeti tarafından oluşturulan metni ve konuşulan yanıtın metnini çevirmek için Çevirmen hizmetini kullanabilirsiniz. Bu hizmet, metni çevirmek için kullanabileceğiniz bir REST API sunar.

### Görev - Çevirmen kaynağını kullanarak metni çevirme

1. Akıllı zamanlayıcınızda 2 dil ayarlanacak - LUIS'i eğitmek için kullanılan sunucu dili (aynı dil, kullanıcıya konuşulacak mesajları oluşturmak için de kullanılır) ve kullanıcının konuştuğu dil. `language` değişkenini, kullanıcının konuşacağı dil olacak şekilde güncelleyin ve LUIS'i eğitmek için kullanılan dil için `server_language` adında yeni bir değişken ekleyin:

    ```python
    language = '<user language>'
    server_language = '<server language>'
    ```

    `<user language>` öğesini, konuşacağınız dil için yerel adla değiştirin, örneğin Fransızca için `fr-FR` veya Kantonca için `zn-HK`.

    `<server language>` öğesini, LUIS'i eğitmek için kullanılan dilin yerel adıyla değiştirin.

    Desteklenen dillerin ve yerel adlarının bir listesini [Microsoft belgelerinde Dil ve ses desteği dokümantasyonunda](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text) bulabilirsiniz.

    > 💁 Birden fazla dil konuşmuyorsanız, tercih ettiğiniz dilden seçtiğiniz bir dile çevirmek için [Bing Translate](https://www.bing.com/translator) veya [Google Translate](https://translate.google.com) gibi bir hizmeti kullanabilirsiniz. Bu hizmetler, çevrilen metnin sesini çalabilir.
    >
    > Örneğin, LUIS'i İngilizce olarak eğitirseniz ancak kullanıcı dili olarak Fransızca kullanmak isterseniz, Bing Translate'i kullanarak "2 dakika ve 27 saniyelik bir zamanlayıcı ayarla" gibi cümleleri İngilizceden Fransızcaya çevirebilirsiniz, ardından çeviriyi mikrofonunuza konuşmak için **Dinle çeviri** düğmesini kullanabilirsiniz.
    >
    > ![Bing Translate'deki dinle çeviri düğmesi](../../../../../translated_images/tr/bing-translate.348aa796d6efe2a9.webp)

1. `speech_api_key` altına çevirmen API anahtarını ekleyin:

    ```python
    translator_api_key = '<key>'
    ```

    `<key>` öğesini çevirmen hizmeti kaynağınızın API anahtarıyla değiştirin.

1. `say` fonksiyonunun üstünde, sunucu dilinden kullanıcı diline metni çevirecek bir `translate_text` fonksiyonu tanımlayın:

    ```python
    def translate_text(text, from_language, to_language):
    ```

    Bu fonksiyona, çevrilecek diller aktarılır - uygulamanız, konuşmayı tanırken kullanıcı dilinden sunucu diline ve konuşulan geri bildirim sağlarken sunucu dilinden kullanıcı diline dönüştürmelidir.

1. Bu fonksiyonun içinde, REST API çağrısı için URL ve başlıkları tanımlayın:

    ```python
    url = f'https://api.cognitive.microsofttranslator.com/translate?api-version=3.0'

    headers = {
        'Ocp-Apim-Subscription-Key': translator_api_key,
        'Ocp-Apim-Subscription-Region': location,
        'Content-type': 'application/json'
    }
    ```

    Bu API'nin URL'si konuma özgü değildir, bunun yerine konum bir başlık olarak iletilir. API anahtarı doğrudan kullanılır, bu nedenle konuşma hizmetinden farklı olarak, token sağlayıcı API'den bir erişim tokeni almanıza gerek yoktur.

1. Bunun altında çağrı için parametreleri ve gövdeyi tanımlayın:

    ```python
    params = {
        'from': from_language,
        'to': to_language
    }

    body = [{
        'text' : text
    }]
    ```

    `params`, API çağrısına iletilecek parametreleri tanımlar ve kaynak ve hedef dilleri iletir. Bu çağrı, `from` dilindeki metni `to` diline çevirecektir.

    `body`, çevrilecek metni içerir. Bu bir dizidir, çünkü aynı çağrıda birden fazla metin bloğu çevrilebilir.

1. REST API'yi çağırın ve yanıtı alın:

    ```python
    response = requests.post(url, headers=headers, params=params, json=body)
    ```

    Gelen yanıt, bir JSON dizisidir ve bir öğe çevirileri içerir. Bu öğe, gövdede iletilen tüm öğelerin çevirileri için bir dizi içerir.

    ```json
    [
        {
            "translations": [
                {
                    "text": "Set a 2 minute 27 second timer.",
                    "to": "en"
                }
            ]
        }
    ]
    ```

1. Dizideki ilk öğeden ilk çevirinin `test` özelliğini döndürün:

    ```python
    return response.json()[0]['translations'][0]['text']
    ```

1. `while True` döngüsünü, kullanıcı dilinden sunucu diline `convert_speech_to_text` çağrısından metni çevirmek için güncelleyin:

    ```python
    if len(text) > 0:
        print('Original:', text)
        text = translate_text(text, language, server_language)
        print('Translated:', text)

        message = Message(json.dumps({ 'speech': text }))
        device_client.send_message(message)
    ```

    Bu kod ayrıca metnin orijinal ve çevrilmiş versiyonlarını konsola yazdırır.

1. `say` fonksiyonunu, sunucu dilinden kullanıcı diline söylenecek metni çevirmek için güncelleyin:

    ```python
    def say(text):
        print('Original:', text)
        text = translate_text(text, server_language, language)
        print('Translated:', text)
        speech = get_speech(text)
        play_speech(speech)
    ```

    Bu kod ayrıca metnin orijinal ve çevrilmiş versiyonlarını konsola yazdırır.

1. Kodunuzu çalıştırın. Fonksiyon uygulamanızın çalıştığından emin olun ve ya kendiniz o dili konuşarak ya da bir çeviri uygulaması kullanarak kullanıcı dilinde bir zamanlayıcı isteyin.

    ```output
    pi@raspberrypi:~/smart-timer $ python3 app.py
    Connecting
    Connected
    Using voice fr-FR-DeniseNeural
    Original: Définir une minuterie de 2 minutes et 27 secondes.
    Translated: Set a timer of 2 minutes and 27 seconds.
    Original: 2 minute 27 second timer started.
    Translated: 2 minute 27 seconde minute a commencé.
    Original: Times up on your 2 minute 27 second timer.
    Translated: Chronométrant votre minuterie de 2 minutes 27 secondes.
    ```

    > 💁 Farklı dillerde bir şey söylemenin farklı yolları nedeniyle, LUIS'e verdiğiniz örneklerden biraz farklı çeviriler alabilirsiniz. Bu durumda, LUIS'e daha fazla örnek ekleyin, yeniden eğitin ve modeli yeniden yayınlayın.

> 💁 Bu kodu [code/pi](../../../../../6-consumer/lessons/4-multiple-language-support/code/pi) klasöründe bulabilirsiniz.

😀 Çok dilli zamanlayıcı programınız başarılı oldu!

---

**Feragatname**:  
Bu belge, [Co-op Translator](https://github.com/Azure/co-op-translator) adlı yapay zeka çeviri hizmeti kullanılarak çevrilmiştir. Doğruluk için çaba göstersek de, otomatik çevirilerin hata veya yanlışlıklar içerebileceğini lütfen unutmayın. Belgenin orijinal dili, yetkili kaynak olarak kabul edilmelidir. Kritik bilgiler için profesyonel insan çevirisi önerilir. Bu çevirinin kullanımından kaynaklanan yanlış anlama veya yanlış yorumlamalardan sorumlu değiliz.