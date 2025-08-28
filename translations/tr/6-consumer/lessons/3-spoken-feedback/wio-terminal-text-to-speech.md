<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "a202fa5889790a3777bfc33dd9f4b459",
  "translation_date": "2025-08-28T02:57:23+00:00",
  "source_file": "6-consumer/lessons/3-spoken-feedback/wio-terminal-text-to-speech.md",
  "language_code": "tr"
}
-->
# Metinden Sese - Wio Terminal

Bu dersin bu bölümünde, metni sese dönüştürerek sesli geri bildirim sağlayacaksınız.

## Metinden Sese

Bir önceki derste konuşmayı metne dönüştürmek için kullandığınız konuşma hizmetleri SDK'sı, metni tekrar sese dönüştürmek için de kullanılabilir.

## Ses Listesi Almak

Konuşma talep ederken, kullanılacak sesi belirtmeniz gerekir çünkü konuşma, çeşitli farklı sesler kullanılarak oluşturulabilir. Her dil, farklı seslerden oluşan bir yelpazeyi destekler ve her dil için desteklenen seslerin listesini konuşma hizmetleri SDK'sından alabilirsiniz. Ancak, mikrodenetleyicilerin sınırlamaları burada devreye giriyor - metinden sese hizmetleri tarafından desteklenen seslerin listesini almak için yapılan çağrı, 77KB'den büyük bir JSON belgesidir ve bu, Wio Terminal tarafından işlenemeyecek kadar büyüktür. Yazım sırasında, tam liste 215 ses içeriyor ve her biri aşağıdaki gibi bir JSON belgesiyle tanımlanıyor:

```json
{
    "Name": "Microsoft Server Speech Text to Speech Voice (en-US, AriaNeural)",
    "DisplayName": "Aria",
    "LocalName": "Aria",
    "ShortName": "en-US-AriaNeural",
    "Gender": "Female",
    "Locale": "en-US",
    "StyleList": [
        "chat",
        "customerservice",
        "narration-professional",
        "newscast-casual",
        "newscast-formal",
        "cheerful",
        "empathetic"
    ],
    "SampleRateHertz": "24000",
    "VoiceType": "Neural",
    "Status": "GA"
}
```

Bu JSON, birden fazla ses stiline sahip olan **Aria** sesi içindir. Metni sese dönüştürürken gereken tek şey, `en-US-AriaNeural` gibi kısa isimdir.

Bu listenin tamamını mikrodenetleyicinize indirip çözümlemek yerine, kullandığınız dil için ses listesini almak ve bunu Wio Terminal'den çağırmak için biraz daha sunucusuz kod yazmanız gerekecek. Kodunuz daha sonra listedeki uygun bir sesi, örneğin bulduğu ilk sesi seçebilir.

### Görev - Ses Listesi Almak için Sunucusuz Bir Fonksiyon Oluşturun

1. VS Code'da `smart-timer-trigger` projenizi açın ve sanal ortamın etkinleştirildiğinden emin olarak terminali açın. Değilse, terminali kapatıp yeniden oluşturun.

1. `local.settings.json` dosyasını açın ve konuşma API anahtarı ve konumu için ayarları ekleyin:

    ```json
    "SPEECH_KEY": "<key>",
    "SPEECH_LOCATION": "<location>"
    ```

    `<key>` kısmını konuşma hizmeti kaynağınızın API anahtarıyla değiştirin. `<location>` kısmını ise konuşma hizmeti kaynağını oluşturduğunuz konumla değiştirin.

1. Bu uygulamaya `get-voices` adında yeni bir HTTP tetikleyici eklemek için, VS Code terminalinde fonksiyon uygulaması projesinin kök klasöründen aşağıdaki komutu çalıştırın:

    ```sh
    func new --name get-voices --template "HTTP trigger"
    ```

    Bu, `get-voices` adında bir HTTP tetikleyici oluşturacaktır.

1. `get-voices` klasöründeki `__init__.py` dosyasının içeriğini aşağıdakiyle değiştirin:

    ```python
    import json
    import os
    import requests
    
    import azure.functions as func
    
    def main(req: func.HttpRequest) -> func.HttpResponse:
        location = os.environ['SPEECH_LOCATION']
        speech_key = os.environ['SPEECH_KEY']
    
        req_body = req.get_json()
        language = req_body['language']
    
        url = f'https://{location}.tts.speech.microsoft.com/cognitiveservices/voices/list'
    
        headers = {
            'Ocp-Apim-Subscription-Key': speech_key
        }
    
        response = requests.get(url, headers=headers)
        voices_json = json.loads(response.text)
    
        voices = filter(lambda x: x['Locale'].lower() == language.lower(), voices_json)
        voices = map(lambda x: x['ShortName'], voices)
    
        return func.HttpResponse(json.dumps(list(voices)), status_code=200)
    ```

    Bu kod, sesleri almak için bir HTTP isteği yapar. Bu ses listesi, tüm diller için sesleri içeren büyük bir JSON bloğudur, bu nedenle istek gövdesinde iletilen dil için sesler filtrelenir, ardından kısa isim çıkarılır ve bir JSON listesi olarak döndürülür. Metni sese dönüştürmek için gereken değer kısa isimdir, bu nedenle yalnızca bu değer döndürülür.

    > 💁 Gerekirse, yalnızca istediğiniz sesleri seçmek için filtreyi değiştirebilirsiniz.

    Bu, verilerin boyutunu yazım sırasında 77KB'den, çok daha küçük bir JSON belgesine indirir. Örneğin, ABD sesleri için bu 408 bayttır.

1. Fonksiyon uygulamanızı yerel olarak çalıştırın. Daha sonra bunu, `text-to-timer` HTTP tetikleyicinizi test ettiğiniz gibi bir araç (örneğin curl) kullanarak çağırabilirsiniz. Dilinizi bir JSON gövdesi olarak ilettiğinizden emin olun:

    ```json
    {
        "language":"<language>"
    }
    ```

    `<language>` kısmını dilinizle değiştirin, örneğin `en-GB` veya `zh-CN`.

> 💁 Bu kodu [code-spoken-response/functions](../../../../../6-consumer/lessons/3-spoken-feedback/code-spoken-response/functions) klasöründe bulabilirsiniz.

### Görev - Wio Terminal'inizden Sesi Alın

1. `smart-timer` projenizi VS Code'da açın (henüz açık değilse).

1. `config.h` başlık dosyasını açın ve fonksiyon uygulamanızın URL'sini ekleyin:

    ```cpp
    const char *GET_VOICES_FUNCTION_URL = "<URL>";
    ```

    `<URL>` kısmını, fonksiyon uygulamanızdaki `get-voices` HTTP tetikleyicisinin URL'siyle değiştirin. Bu, `TEXT_TO_TIMER_FUNCTION_URL` değeriyle aynı olacaktır, ancak `text-to-timer` yerine `get-voices` fonksiyon adını içerecektir.

1. `src` klasöründe `text_to_speech.h` adında yeni bir dosya oluşturun. Bu, metni sese dönüştürmek için bir sınıf tanımlamak için kullanılacaktır.

1. Yeni `text_to_speech.h` dosyasının en üstüne aşağıdaki include yönergelerini ekleyin:

    ```cpp
    #pragma once

    #include <Arduino.h>
    #include <ArduinoJson.h>
    #include <HTTPClient.h>
    #include <Seeed_FS.h>
    #include <SD/Seeed_SD.h>
    #include <WiFiClient.h>
    #include <WiFiClientSecure.h>
    
    #include "config.h"
    #include "speech_to_text.h"
    ```

1. Bu yönergelerin altına, uygulamanın geri kalanında kullanılabilecek bir örnekle birlikte `TextToSpeech` sınıfını bildiren aşağıdaki kodu ekleyin:

    ```cpp
    class TextToSpeech
    {
    public:
    private:
    };
    
    TextToSpeech textToSpeech;
    ```

1. Fonksiyon uygulamanızı çağırmak için bir WiFi istemcisi bildirmeniz gerekir. Sınıfın `private` bölümüne aşağıdakileri ekleyin:

    ```cpp
    WiFiClient _client;
    ```

1. `private` bölümüne, seçilen ses için bir alan ekleyin:

    ```cpp
    String _voice;
    ```

1. `public` bölümüne, ilk sesi alacak bir `init` fonksiyonu ekleyin:

    ```cpp
    void init()
    {
    }
    ```

1. Sesleri almak için, dile sahip bir JSON belgesinin fonksiyon uygulamasına gönderilmesi gerekir. Bu JSON belgesini oluşturmak için `init` fonksiyonuna aşağıdaki kodu ekleyin:

    ```cpp
    DynamicJsonDocument doc(1024);
    doc["language"] = LANGUAGE;

    String body;
    serializeJson(doc, body);
    ```

1. Ardından bir `HTTPClient` oluşturun ve JSON belgesini göndererek fonksiyon uygulamasını çağırın:

    ```cpp
    HTTPClient httpClient;
    httpClient.begin(_client, GET_VOICES_FUNCTION_URL);

    int httpResponseCode = httpClient.POST(body);
    ```

1. Bunun altına, yanıt kodunu kontrol eden ve eğer 200 (başarılı) ise ses listesini çıkaran, listeden ilk sesi alan kodu ekleyin:

    ```cpp
    if (httpResponseCode == 200)
    {
        String result = httpClient.getString();
        Serial.println(result);

        DynamicJsonDocument doc(1024);
        deserializeJson(doc, result.c_str());

        JsonArray obj = doc.as<JsonArray>();
        _voice = obj[0].as<String>();

        Serial.print("Using voice ");
        Serial.println(_voice);
    }
    else
    {
        Serial.print("Failed to get voices - error ");
        Serial.println(httpResponseCode);
    }
    ```

1. Bunun ardından, HTTP istemci bağlantısını sonlandırın:

    ```cpp
    httpClient.end();
    ```

1. `main.cpp` dosyasını açın ve bu yeni başlık dosyasını dahil etmek için en üste aşağıdaki include yönergesini ekleyin:

    ```cpp
    #include "text_to_speech.h"
    ```

1. `setup` fonksiyonunda, `speechToText.init();` çağrısının altına, `TextToSpeech` sınıfını başlatmak için aşağıdakileri ekleyin:

    ```cpp
    textToSpeech.init();
    ```

1. Bu kodu derleyin, Wio Terminal'inize yükleyin ve seri monitör üzerinden test edin. Fonksiyon uygulamanızın çalıştığından emin olun.

    Fonksiyon uygulamasından döndürülen mevcut seslerin listesini ve seçilen sesi göreceksiniz.

    ```output
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1101  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Connecting to WiFi..
    Connected!
    Got access token.
    ["en-US-JennyNeural", "en-US-JennyMultilingualNeural", "en-US-GuyNeural", "en-US-AriaNeural", "en-US-AmberNeural", "en-US-AnaNeural", "en-US-AshleyNeural", "en-US-BrandonNeural", "en-US-ChristopherNeural", "en-US-CoraNeural", "en-US-ElizabethNeural", "en-US-EricNeural", "en-US-JacobNeural", "en-US-MichelleNeural", "en-US-MonicaNeural", "en-US-AriaRUS", "en-US-BenjaminRUS", "en-US-GuyRUS", "en-US-ZiraRUS"]
    Using voice en-US-JennyNeural
    Ready.
    ```

## Metni Sese Dönüştürmek

Kullanılacak bir ses elde ettikten sonra, bu ses metni sese dönüştürmek için kullanılabilir. Sesleri dönüştürürken aynı bellek sınırlamaları geçerlidir, bu nedenle ses, ReSpeaker üzerinden çalınmak üzere SD karta yazılmalıdır.

> 💁 Bu projedeki önceki derslerde, mikrofondan alınan konuşmayı depolamak için flash bellek kullandınız. Bu ders, Seeed ses kütüphanelerini kullanarak SD karttan ses çalmanın daha kolay olması nedeniyle bir SD kart kullanır.

Dikkate alınması gereken başka bir sınırlama daha vardır: konuşma hizmetinden alınan mevcut ses verileri ve Wio Terminal'in desteklediği formatlar. Tam bilgisayarların aksine, mikrodenetleyiciler için ses kütüphaneleri destekledikleri ses formatlarında çok sınırlı olabilir. Örneğin, ReSpeaker üzerinden ses çalabilen Seeed Arduino Audio kütüphanesi yalnızca 44.1KHz örnekleme hızında sesi destekler. Azure konuşma hizmetleri bir dizi formatta ses sağlayabilir, ancak bunların hiçbiri bu örnekleme hızını kullanmaz; yalnızca 8KHz, 16KHz, 24KHz ve 48KHz sağlar. Bu, sesin 44.1KHz'ye yeniden örneklenmesi gerektiği anlamına gelir; bu, özellikle bellek açısından Wio Terminal'in sahip olduğundan daha fazla kaynağa ihtiyaç duyar.

Bu tür verileri manipüle etmeniz gerektiğinde, özellikle veri bir web çağrısı yoluyla alınıyorsa, sunucusuz kod kullanmak genellikle daha iyidir. Wio Terminal, dönüştürülecek metni ileten bir sunucusuz fonksiyonu çağırabilir ve sunucusuz fonksiyon hem konuşma hizmetini çağırarak metni sese dönüştürebilir hem de sesi gerekli örnekleme hızına yeniden örnekleyebilir. Daha sonra sesi, Wio Terminal'in SD karta kaydetmesi ve ReSpeaker üzerinden çalması için gereken formatta döndürebilir.

### Görev - Metni Sese Dönüştürmek için Sunucusuz Bir Fonksiyon Oluşturun

1. VS Code'da `smart-timer-trigger` projenizi açın ve sanal ortamın etkinleştirildiğinden emin olarak terminali açın. Değilse, terminali kapatıp yeniden oluşturun.

1. Bu uygulamaya `text-to-speech` adında yeni bir HTTP tetikleyici eklemek için, VS Code terminalinde fonksiyon uygulaması projesinin kök klasöründen aşağıdaki komutu çalıştırın:

    ```sh
    func new --name text-to-speech --template "HTTP trigger"
    ```

    Bu, `text-to-speech` adında bir HTTP tetikleyici oluşturacaktır.

1. [librosa](https://librosa.org) Pip paketi, sesi yeniden örneklemek için işlevlere sahiptir, bu nedenle bunu `requirements.txt` dosyasına ekleyin:

    ```sh
    librosa
    ```

    Eklendikten sonra, VS Code terminalinden aşağıdaki komutu kullanarak Pip paketlerini yükleyin:

    ```sh
    pip install -r requirements.txt
    ```

    > ⚠️ Linux, Raspberry Pi OS dahil, kullanıyorsanız, aşağıdaki komutla `libsndfile` yüklemeniz gerekebilir:
    >
    > ```sh
    > sudo apt update
    > sudo apt install libsndfile1-dev
    > ```

1. Metni sese dönüştürmek için, konuşma API anahtarını doğrudan kullanamazsınız; bunun yerine, bir erişim jetonu talep etmeniz gerekir. Bu talep, API anahtarını kullanarak kimlik doğrulaması yapar. `text-to-speech` klasöründeki `__init__.py` dosyasını açın ve içindeki tüm kodu aşağıdakiyle değiştirin:

    ```python
    import io
    import os
    import requests
    
    import librosa
    import soundfile as sf
    import azure.functions as func
    
    location = os.environ['SPEECH_LOCATION']
    speech_key = os.environ['SPEECH_KEY']
    
    def get_access_token():
        headers = {
            'Ocp-Apim-Subscription-Key': speech_key
        }
    
        token_endpoint = f'https://{location}.api.cognitive.microsoft.com/sts/v1.0/issuetoken'
        response = requests.post(token_endpoint, headers=headers)
        return str(response.text)
    ```

    Bu, ayarlardan okunacak konum ve konuşma anahtarı için sabitler tanımlar. Daha sonra, konuşma hizmeti için bir erişim jetonu alacak `get_access_token` fonksiyonunu tanımlar.

1. Bu kodun altına aşağıdakileri ekleyin:

    ```python
    playback_format = 'riff-48khz-16bit-mono-pcm'

    def main(req: func.HttpRequest) -> func.HttpResponse:
        req_body = req.get_json()
        language = req_body['language']
        voice = req_body['voice']
        text = req_body['text']
    
        url = f'https://{location}.tts.speech.microsoft.com/cognitiveservices/v1'
    
        headers = {
            'Authorization': 'Bearer ' + get_access_token(),
            'Content-Type': 'application/ssml+xml',
            'X-Microsoft-OutputFormat': playback_format
        }
    
        ssml =  f'<speak version=\'1.0\' xml:lang=\'{language}\'>'
        ssml += f'<voice xml:lang=\'{language}\' name=\'{voice}\'>'
        ssml += text
        ssml += '</voice>'
        ssml += '</speak>'
    
        response = requests.post(url, headers=headers, data=ssml.encode('utf-8'))
    
        raw_audio, sample_rate = librosa.load(io.BytesIO(response.content), sr=48000)
        resampled = librosa.resample(raw_audio, sample_rate, 44100)
        
        output_buffer = io.BytesIO()
        sf.write(output_buffer, resampled, 44100, 'PCM_16', format='wav')
        output_buffer.seek(0)
    
        return func.HttpResponse(output_buffer.read(), status_code=200)
    ```

    Bu, metni sese dönüştüren HTTP tetikleyiciyi tanımlar. Dönüştürülecek metni, dili ve sesi istekle gönderilen JSON gövdesinden çıkarır, konuşmayı talep etmek için biraz SSML oluşturur ve ardından erişim jetonunu kullanarak ilgili REST API'yi çağırır. Bu REST API çağrısı, 16-bit, 48KHz mono WAV dosyası olarak kodlanmış sesi döndürür; bu, `playback_format` değerine göre REST API çağrısına gönderilir.

    Daha sonra bu ses, `librosa` tarafından 48KHz örnekleme hızından 44.1KHz örnekleme hızına yeniden örneklenir ve ardından bu ses, döndürülen bir ikili tamponda saklanır.

1. Fonksiyon uygulamanızı yerel olarak çalıştırın veya buluta dağıtın. Daha sonra bunu, `text-to-timer` HTTP tetikleyicinizi test ettiğiniz gibi bir araç (örneğin curl) kullanarak çağırabilirsiniz. Dil, ses ve metni JSON gövdesi olarak ilettiğinizden emin olun:

    ```json
    {
        "language": "<language>",
        "voice": "<voice>",
        "text": "<text>"
    }
    ```

    `<language>` kısmını dilinizle değiştirin, örneğin `en-GB` veya `zh-CN`. `<voice>` kısmını kullanmak istediğiniz sesle değiştirin. `<text>` kısmını ise sese dönüştürmek istediğiniz metinle değiştirin. Çıktıyı bir dosyaya kaydedebilir ve WAV dosyalarını çalabilen herhangi bir ses oynatıcıyla çalabilirsiniz.

    Örneğin, "Hello" kelimesini ABD İngilizcesi ile Jenny Neural sesi kullanarak sese dönüştürmek için, fonksiyon uygulaması yerel olarak çalışırken aşağıdaki curl komutunu kullanabilirsiniz:

    ```sh
    curl -X GET 'http://localhost:7071/api/text-to-speech' \
         -H 'Content-Type: application/json' \
         -o hello.wav \
         -d '{
           "language":"en-US",
           "voice": "en-US-JennyNeural",
           "text": "Hello"
         }'
    ```

    Bu, sesi `hello.wav` olarak geçerli dizine kaydedecektir.

> 💁 Bu kodu [code-spoken-response/functions](../../../../../6-consumer/lessons/3-spoken-feedback/code-spoken-response/functions) klasöründe bulabilirsiniz.

### Görev - Wio Terminal'inizden Konuşmayı Alın

1. `smart-timer` projenizi VS Code'da açın (henüz açık değilse).

1. `config.h` başlık dosyasını açın ve fonksiyon uygulamanızın URL'sini ekleyin:

    ```cpp
    const char *TEXT_TO_SPEECH_FUNCTION_URL = "<URL>";
    ```

    `<URL>` kısmını, fonksiyon uygulamanızdaki `text-to-speech` HTTP tetikleyicisinin URL'siyle değiştirin. Bu, `TEXT_TO_TIMER_FUNCTION_URL` değeriyle aynı olacaktır, ancak `text-to-timer` yerine `text-to-speech` fonksiyon adını içerecektir.

1. `text_to_speech.h` başlık dosyasını açın ve `TextToSpeech` sınıfının `public` bölümüne aşağıdaki yöntemi ekleyin:

    ```cpp
    void convertTextToSpeech(String text)
    {
    }
    ```

1. `convertTextToSpeech` yöntemine, fonksiyon uygulamasına gönderilecek JSON'u oluşturmak için aşağıdaki kodu ekleyin:

    ```cpp
    DynamicJsonDocument doc(1024);
    doc["language"] = LANGUAGE;
    doc["voice"] = _voice;
    doc["text"] = text;

    String body;
    serializeJson(doc, body);
    ```

    Bu, dili, sesi ve metni JSON belgesine yazar, ardından bunu bir dizeye serileştirir.

1. Bunun altına, fonksiyon uygulamasını çağırmak için aşağıdaki kodu ekleyin:

    ```cpp
    HTTPClient httpClient;
    httpClient.begin(_client, TEXT_TO_SPEECH_FUNCTION_URL);

    int httpResponseCode = httpClient.POST(body);
    ```

    Bu, bir HTTPClient oluşturur ve JSON belgesini kullanarak metni sese dönüştürmek için POST isteği yapar.

1. Çağrı başarılı olursa, fonksiyon uygulamasından döndürülen ham ikili veri, SD kartta bir dosyaya aktarılabilir. Bunu yapmak için aşağıdaki kodu ekleyin:

    ```cpp
    if (httpResponseCode == 200)
    {            
        File wav_file = SD.open("SPEECH.WAV", FILE_WRITE);
        httpClient.writeToStream(&wav_file);
        wav_file.close();
    }
    else
    {
        Serial.print("Failed to get speech - error ");
        Serial.println(httpResponseCode);
    }
    ```

    Bu kod, yanıtı kontrol eder ve eğer 200 (başarılı) ise, ikili veriyi SD Kartın kökünde `SPEECH.WAV` adlı bir dosyaya aktarır.

1. Bu yöntemin sonunda, HTTP bağlantısını kapatın:

    ```cpp
    httpClient.end();
    ```

1. Artık konuşulacak metin sese dönüştürülebilir. `main.cpp` dosyasında, `say` fonksiyonunun sonuna aşağıdaki satırı ekleyerek söylenecek metni sese dönüştürün:
```cpp
    textToSpeech.convertTextToSpeech(text);
    ```

### Görev - Wio Terminal cihazınızdan ses çalın

**Yakında geliyor**

## Fonksiyon uygulamanızı buluta dağıtma

Fonksiyon uygulamasını yerel olarak çalıştırmanın sebebi, Linux'taki `librosa` Pip paketinin varsayılan olarak yüklü olmayan bir kütüphaneye bağımlı olmasıdır ve bu kütüphane, fonksiyon uygulaması çalışmadan önce yüklenmelidir. Fonksiyon uygulamaları sunucusuzdur - yönetebileceğiniz sunucular yoktur, dolayısıyla bu kütüphaneyi önceden yüklemenin bir yolu yoktur.

Bunun yerine, fonksiyon uygulamanızı bir Docker konteyneri kullanarak dağıtmanız gerekir. Bu konteyner, bulut tarafından, fonksiyon uygulamanızın yeni bir örneğini başlatması gerektiğinde (örneğin, talep mevcut kaynakları aştığında veya fonksiyon uygulaması bir süredir kullanılmadığı için kapatıldığında) dağıtılır.

Bir fonksiyon uygulaması oluşturma ve Docker üzerinden dağıtma talimatlarını [Microsoft Docs'taki özel bir konteyner kullanarak Linux'ta bir fonksiyon oluşturma dokümanında](https://docs.microsoft.com/azure/azure-functions/functions-create-function-linux-custom-image?WT.mc_id=academic-17441-jabenn&tabs=bash%2Cazurecli&pivots=programming-language-python) bulabilirsiniz.

Bu işlem tamamlandıktan sonra, Wio Terminal kodunuzu bu fonksiyona erişecek şekilde uyarlayabilirsiniz:

1. Azure Functions sertifikasını `config.h` dosyasına ekleyin:

    ```cpp
    const char *FUNCTIONS_CERTIFICATE =
        "-----BEGIN CERTIFICATE-----\r\n"
        "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\r\n"
        "-----END CERTIFICATE-----\r\n";
    ```

1. Tüm `<WiFiClient.h>` dahil etmelerini `<WiFiClientSecure.h>` ile değiştirin.

1. Tüm `WiFiClient` alanlarını `WiFiClientSecure` ile değiştirin.

1. `WiFiClientSecure` alanına sahip her sınıfta bir kurucu (constructor) ekleyin ve bu kurucuda sertifikayı ayarlayın:

    ```cpp
    _client.setCACert(FUNCTIONS_CERTIFICATE);
    ```

---

**Feragatname**:  
Bu belge, AI çeviri hizmeti [Co-op Translator](https://github.com/Azure/co-op-translator) kullanılarak çevrilmiştir. Doğruluk için çaba göstersek de, otomatik çevirilerin hata veya yanlışlık içerebileceğini lütfen unutmayın. Belgenin orijinal dili, yetkili kaynak olarak kabul edilmelidir. Kritik bilgiler için profesyonel insan çevirisi önerilir. Bu çevirinin kullanımından kaynaklanan yanlış anlamalar veya yanlış yorumlamalardan sorumlu değiliz.