# Konuşmayı Çevir - Wio Terminal

Bu dersin bu bölümünde, çevirmen hizmetini kullanarak metni çevirmek için kod yazacaksınız.

## Çevirmen hizmetini kullanarak metni sese dönüştürme

Konuşma hizmeti REST API'si doğrudan çevirileri desteklemez, ancak konuşmadan metne hizmeti tarafından oluşturulan metni ve konuşulan yanıtın metnini çevirmek için Çevirmen hizmetini kullanabilirsiniz. Bu hizmet, metni çevirmek için kullanabileceğiniz bir REST API'ye sahiptir, ancak kullanımı kolaylaştırmak için bu, işlevler uygulamanızda başka bir HTTP tetikleyici ile sarılacaktır.

### Görev - metni çevirmek için sunucusuz bir işlev oluşturma

1. VS Code'da `smart-timer-trigger` projenizi açın ve sanal ortamın etkinleştirildiğinden emin olarak terminali açın. Eğer etkin değilse, terminali kapatıp yeniden oluşturun.

1. `local.settings.json` dosyasını açın ve çevirmen API anahtarı ve konumu için ayarları ekleyin:

    ```json
    "TRANSLATOR_KEY": "<key>",
    "TRANSLATOR_LOCATION": "<location>"
    ```

    `<key>` öğesini çevirmen hizmeti kaynağınızın API anahtarıyla değiştirin. `<location>` öğesini çevirmen hizmeti kaynağını oluşturduğunuz konumla değiştirin.

1. VS Code terminalinde işlevler uygulama projesinin kök klasöründen aşağıdaki komutu kullanarak bu uygulamaya `translate-text` adlı yeni bir HTTP tetikleyici ekleyin:

    ```sh
    func new --name translate-text --template "HTTP trigger"
    ```

    Bu, `translate-text` adlı bir HTTP tetikleyici oluşturacaktır.

1. `translate-text` klasöründeki `__init__.py` dosyasının içeriğini aşağıdakiyle değiştirin:

    ```python
    import logging
    import os
    import requests
    
    import azure.functions as func
    
    location = os.environ['TRANSLATOR_LOCATION']
    translator_key = os.environ['TRANSLATOR_KEY']
    
    def main(req: func.HttpRequest) -> func.HttpResponse:
        req_body = req.get_json()
        from_language = req_body['from_language']
        to_language = req_body['to_language']
        text = req_body['text']
        
        logging.info(f'Translating {text} from {from_language} to {to_language}')
    
        url = f'https://api.cognitive.microsofttranslator.com/translate?api-version=3.0'
    
        headers = {
            'Ocp-Apim-Subscription-Key': translator_key,
            'Ocp-Apim-Subscription-Region': location,
            'Content-type': 'application/json'
        }
    
        params = {
            'from': from_language,
            'to': to_language
        }
    
        body = [{
            'text' : text
        }]
        
        response = requests.post(url, headers=headers, params=params, json=body)
        return func.HttpResponse(response.json()[0]['translations'][0]['text'])
    ```

    Bu kod, HTTP isteğinden metni ve dilleri çıkarır. Daha sonra, dilleri URL için parametreler ve çevrilecek metni gövde olarak geçirerek çevirmen REST API'sine bir istek yapar. Son olarak, çeviri döndürülür.

1. İşlev uygulamanızı yerel olarak çalıştırın. Daha sonra bunu, `text-to-timer` HTTP tetikleyicinizi test ettiğiniz şekilde curl gibi bir araç kullanarak çağırabilirsiniz. Çevrilecek metni ve dilleri JSON gövdesi olarak geçirdiğinizden emin olun:

    ```json
    {
        "text": "Définir une minuterie de 30 secondes",
        "from_language": "fr-FR",
        "to_language": "en-US"
    }
    ```

    Bu örnek, Fransızca'dan ABD İngilizcesine *Définir une minuterie de 30 secondes* metnini çevirir. *Set a 30-second timer* olarak dönecektir.

> 💁 Bu kodu [code/functions](../../../../../6-consumer/lessons/4-multiple-language-support/code/functions) klasöründe bulabilirsiniz.

### Görev - metni çevirmek için çevirmen işlevini kullanma

1. `smart-timer` projesini VS Code'da açın, eğer zaten açık değilse.

1. Akıllı zamanlayıcınızda 2 dil ayarlanmış olacak - LUIS'i eğitmek için kullanılan sunucunun dili (aynı dil, kullanıcıya konuşulacak mesajları oluşturmak için de kullanılır) ve kullanıcının konuştuğu dil. `config.h` başlık dosyasındaki `LANGUAGE` sabitini, kullanıcı tarafından konuşulacak dil olacak şekilde güncelleyin ve LUIS'i eğitmek için kullanılan dil için `SERVER_LANGUAGE` adlı yeni bir sabit ekleyin:

    ```cpp
    const char *LANGUAGE = "<user language>";
    const char *SERVER_LANGUAGE = "<server language>";
    ```

    `<user language>` öğesini konuşacağınız dil için yerel adla değiştirin, örneğin Fransızca için `fr-FR` veya Kantonca için `zn-HK`.

    `<server language>` öğesini LUIS'i eğitmek için kullanılan dilin yerel adıyla değiştirin.

    Desteklenen dillerin ve yerel adlarının bir listesini [Microsoft belgelerinde Dil ve ses desteği dokümantasyonunda](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text) bulabilirsiniz.

    > 💁 Birden fazla dil konuşmuyorsanız, tercih ettiğiniz dilden seçtiğiniz bir dile çevirmek için [Bing Translate](https://www.bing.com/translator) veya [Google Translate](https://translate.google.com) gibi bir hizmeti kullanabilirsiniz. Bu hizmetler daha sonra çevrilen metnin sesini çalabilir.
    >
    > Örneğin, LUIS'i İngilizce olarak eğitirseniz, ancak kullanıcı dili olarak Fransızca kullanmak isterseniz, Bing Translate kullanarak "set a 2 minute and 27 second timer" gibi cümleleri İngilizceden Fransızcaya çevirebilirsiniz, ardından çeviriyi mikrofonunuza konuşmak için **Listen translation** düğmesini kullanabilirsiniz.
    >
    > ![Bing Translate'deki dinleme çevirisi düğmesi](../../../../../translated_images/tr/bing-translate.348aa796d6efe2a9.webp)

1. `SPEECH_LOCATION` altına çevirmen API anahtarı ve konumunu ekleyin:

    ```cpp
    const char *TRANSLATOR_API_KEY = "<KEY>";
    const char *TRANSLATOR_LOCATION = "<LOCATION>";
    ```

    `<KEY>` öğesini çevirmen hizmeti kaynağınızın API anahtarıyla değiştirin. `<LOCATION>` öğesini çevirmen hizmeti kaynağını oluşturduğunuz konumla değiştirin.

1. `VOICE_URL` altına çevirmen tetikleyici URL'sini ekleyin:

    ```cpp
    const char *TRANSLATE_FUNCTION_URL = "<URL>";
    ```

    `<URL>` öğesini işlev uygulamanızdaki `translate-text` HTTP tetikleyicisinin URL'siyle değiştirin. Bu, `TEXT_TO_TIMER_FUNCTION_URL` için değerle aynı olacak, ancak işlev adı `text-to-timer` yerine `translate-text` olacaktır.

1. `src` klasörüne `text_translator.h` adlı yeni bir dosya ekleyin.

1. Bu yeni `text_translator.h` başlık dosyası, metni çevirmek için bir sınıf içerecek. Bu sınıfı bildirmek için aşağıdakileri bu dosyaya ekleyin:

    ```cpp
    #pragma once
    
    #include <Arduino.h>
    #include <ArduinoJson.h>
    #include <HTTPClient.h>
    #include <WiFiClient.h>
    
    #include "config.h"
    
    class TextTranslator
    {
    public:   
    private:
        WiFiClient _client;
    };
    
    TextTranslator textTranslator;
    ```

    Bu, `TextTranslator` sınıfını ve bu sınıfın bir örneğini bildirir. Sınıfın WiFi istemcisi için tek bir alanı vardır.

1. Bu sınıfın `public` bölümüne, metni çevirmek için bir yöntem ekleyin:

    ```cpp
    String translateText(String text, String from_language, String to_language)
    {
    }
    ```

    Bu yöntem, çevrilecek dili ve çevrilecek dili alır. Konuşmayı işlerken, konuşma kullanıcı dilinden LUIS sunucu diline çevrilecek ve yanıt verirken LUIS sunucu dilinden kullanıcı diline çevrilecektir.

1. Bu yöntemde, çevrilecek metni ve dilleri içeren bir JSON gövdesi oluşturmak için kod ekleyin:

    ```cpp
    DynamicJsonDocument doc(1024);
    doc["text"] = text;
    doc["from_language"] = from_language;
    doc["to_language"] = to_language;

    String body;
    serializeJson(doc, body);

    Serial.print("Translating ");
    Serial.print(text);
    Serial.print(" from ");
    Serial.print(from_language);
    Serial.print(" to ");
    Serial.print(to_language);
    ```

1. Bunun altına, gövdeyi sunucusuz işlev uygulamasına göndermek için aşağıdaki kodu ekleyin:

    ```cpp
    HTTPClient httpClient;
    httpClient.begin(_client, TRANSLATE_FUNCTION_URL);

    int httpResponseCode = httpClient.POST(body);
    ```

1. Ardından, yanıtı almak için kod ekleyin:

    ```cpp
    String translated_text = "";

    if (httpResponseCode == 200)
    {
        translated_text = httpClient.getString();
        Serial.print("Translated: ");
        Serial.println(translated_text);
    }
    else
    {
        Serial.print("Failed to translate text - error ");
        Serial.println(httpResponseCode);
    }
    ```

1. Son olarak, bağlantıyı kapatmak ve çevrilen metni döndürmek için kod ekleyin:

    ```cpp
    httpClient.end();

    return translated_text;
    ```

### Görev - tanınan konuşmayı ve yanıtları çevirme

1. `main.cpp` dosyasını açın.

1. Dosyanın üst kısmına `TextTranslator` sınıfı başlık dosyası için bir include yönergesi ekleyin:

    ```cpp
    #include "text_translator.h"
    ```

1. Bir zamanlayıcı ayarlandığında veya süresi dolduğunda söylenen metin çevrilmelidir. Bunu yapmak için, `say` işlevinin ilk satırı olarak aşağıdakileri ekleyin:

    ```cpp
    text = textTranslator.translateText(text, LANGUAGE, SERVER_LANGUAGE);
    ```

    Bu, metni kullanıcı diline çevirecektir.

1. `processAudio` işlevinde, metin, `String text = speechToText.convertSpeechToText();` çağrısıyla yakalanan seslerden alınır. Bu çağrıdan sonra metni çevirin:

    ```cpp
    String text = speechToText.convertSpeechToText();
    text = textTranslator.translateText(text, LANGUAGE, SERVER_LANGUAGE);
    ```

    Bu, metni kullanıcı dilinden sunucuda kullanılan dile çevirecektir.

1. Bu kodu derleyin, Wio Terminal'inize yükleyin ve seri monitör üzerinden test edin. Seri monitörde `Ready` gördüğünüzde, C düğmesine (sol tarafta, güç anahtarına en yakın olan) basın ve konuşun. İşlev uygulamanızın çalıştığından emin olun ve kullanıcı dilinde bir zamanlayıcı isteyin, ya o dili kendiniz konuşarak ya da bir çeviri uygulaması kullanarak.

    ```output
    Connecting to WiFi..
    Connected!
    Got access token.
    Ready.
    Starting recording...
    Finished recording
    Sending speech...
    Speech sent!
    {"RecognitionStatus":"Success","DisplayText":"Définir une minuterie de 2 minutes 27 secondes.","Offset":9600000,"Duration":40400000}
    Translating Définir une minuterie de 2 minutes 27 secondes. from fr-FR to en-US
    Translated: Set a timer of 2 minutes 27 seconds.
    Set a timer of 2 minutes 27 seconds.
    {"seconds": 147}
    Translating 2 minute 27 second timer started. from en-US to fr-FR
    Translated: 2 minute 27 seconde minute a commencé.
    2 minute 27 seconde minute a commencé.
    Translating Times up on your 2 minute 27 second timer. from en-US to fr-FR
    Translated: Chronométrant votre minuterie de 2 minutes 27 secondes.
    Chronométrant votre minuterie de 2 minutes 27 secondes.
    ```

> 💁 Bu kodu [code/wio-terminal](../../../../../6-consumer/lessons/4-multiple-language-support/code/wio-terminal) klasöründe bulabilirsiniz.

😀 Çok dilli zamanlayıcı programınız başarıyla tamamlandı!

---

**Feragatname**:  
Bu belge, AI çeviri hizmeti [Co-op Translator](https://github.com/Azure/co-op-translator) kullanılarak çevrilmiştir. Doğruluğu sağlamak için çaba göstersek de, otomatik çevirilerin hata veya yanlışlık içerebileceğini lütfen unutmayın. Belgenin orijinal dili, yetkili kaynak olarak kabul edilmelidir. Kritik bilgiler için profesyonel insan çevirisi önerilir. Bu çevirinin kullanımından kaynaklanan yanlış anlamalar veya yanlış yorumlamalar için sorumluluk kabul etmiyoruz.