# Dil Anlama

![Bu dersin genel bir sketchnote özeti](../../../../../translated_images/tr/lesson-22.6148ea28500d9e00.webp)

> Sketchnote: [Nitya Narasimhan](https://github.com/nitya). Daha büyük bir versiyon için görsele tıklayın.

## Ders Öncesi Test

[Ders öncesi test](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/43)

## Giriş

Son derste konuşmayı metne dönüştürdünüz. Akıllı bir zamanlayıcı programlamak için bu kodun söylenenleri anlaması gerekecek. Kullanıcının "3 dakikalık bir zamanlayıcı ayarla" gibi sabit bir ifade kullanacağını varsayabilirsiniz ve bu ifadeyi zamanlayıcının ne kadar süreyle ayarlanması gerektiğini anlamak için ayrıştırabilirsiniz. Ancak bu çok kullanıcı dostu bir yaklaşım değildir. Bir kullanıcı "3 dakika için bir zamanlayıcı ayarla" derse, siz veya ben ne demek istediğini anlayabiliriz, ancak kodunuz sabit bir ifade beklediği için bunu anlayamaz.

Dil anlama burada devreye girer. AI modelleri kullanılarak metni yorumlayabilir ve gerekli detayları döndürebilir. Örneğin, hem "3 dakikalık bir zamanlayıcı ayarla" hem de "3 dakika için bir zamanlayıcı ayarla" ifadelerini alabilir ve 3 dakikalık bir zamanlayıcı gerektiğini anlayabilir.

Bu derste dil anlama modellerini, nasıl oluşturulacağını, eğitileceğini ve kodunuzda nasıl kullanılacağını öğreneceksiniz.

Bu derste şunları ele alacağız:

* [Dil anlama](../../../../../6-consumer/lessons/2-language-understanding)
* [Dil anlama modeli oluşturma](../../../../../6-consumer/lessons/2-language-understanding)
* [Niyetler ve varlıklar](../../../../../6-consumer/lessons/2-language-understanding)
* [Dil anlama modelini kullanma](../../../../../6-consumer/lessons/2-language-understanding)

## Dil Anlama

İnsanlar yüz binlerce yıldır iletişim kurmak için dili kullanıyor. Kelimeler, sesler veya hareketlerle iletişim kurarız ve söylenenleri anlarız; hem kelimelerin, seslerin veya hareketlerin anlamını hem de bağlamlarını. Samimiyet ve alaycılığı anlayabiliriz, böylece aynı kelimeler ses tonumuza bağlı olarak farklı şeyler ifade edebilir.

✅ Son zamanlarda yaptığınız bazı konuşmaları düşünün. Konuşmanın ne kadarının bir bilgisayar için bağlam gerektirdiği için anlaması zor olurdu?

Dil anlama, doğal dil işleme (NLP) olarak adlandırılan yapay zeka alanının bir parçasıdır ve okuma-anlama ile ilgilenir; kelimelerin veya cümlelerin detaylarını anlamaya çalışır. Alexa veya Siri gibi bir sesli asistan kullanıyorsanız, dil anlama hizmetlerini kullanmışsınızdır. Bunlar, "Alexa, Taylor Swift'in son albümünü çal" ifadesini kızımın oturma odasında favori şarkılarıyla dans etmesine dönüştüren arka plandaki AI hizmetleridir.

> 💁 Bilgisayarlar, tüm ilerlemelerine rağmen, metni gerçekten anlamak konusunda hala uzun bir yol kat etmesi gerekiyor. Bilgisayarlarla dil anlama dediğimizde, insan iletişimi kadar gelişmiş bir şeyden bahsetmiyoruz; bunun yerine bazı kelimeleri alıp anahtar detayları çıkarmayı kastediyoruz.

Biz insanlar, dili düşünmeden anlarız. Eğer başka bir insana "Taylor Swift'in son albümünü çal" desem, ne demek istediğimi içgüdüsel olarak bilirler. Bir bilgisayar için bu daha zordur. Kelimeleri, konuşmadan metne dönüştürülmüş şekilde alması ve şu bilgileri çıkarması gerekir:

* Müzik çalınmalı
* Müzik, sanatçı Taylor Swift'e ait
* Belirli müzik, bir albümdeki birden fazla parçanın sıralı hali
* Taylor Swift'in birçok albümü var, bu yüzden kronolojik sıraya göre sıralanmalı ve en son yayınlanan albüm isteniyor

✅ Kahve sipariş etmek veya bir aile üyesinden bir şey istemek gibi taleplerinizi ifade ettiğiniz diğer cümleleri düşünün. Bilgisayarın cümleyi anlaması için çıkarması gereken bilgileri parçalamaya çalışın.

Dil anlama modelleri, dilden belirli detayları çıkarmak için eğitilmiş AI modelleridir ve ardından transfer öğrenimi kullanılarak belirli görevler için eğitilirler. Tıpkı küçük bir görüntü seti kullanarak Özel Görüntüleme modelini eğittiğiniz gibi. Bir modeli alabilir, ardından anlamasını istediğiniz metni kullanarak eğitebilirsiniz.

## Dil Anlama Modeli Oluşturma

![LUIS logosu](../../../../../translated_images/tr/luis-logo.5cb4f3e88c020ee6.webp)

Dil anlama modellerini, Microsoft'un Cognitive Services'ın bir parçası olan LUIS adlı dil anlama hizmetini kullanarak oluşturabilirsiniz.

### Görev - yazım kaynağı oluşturma

LUIS'i kullanmak için bir yazım kaynağı oluşturmanız gerekir.

1. `smart-timer` kaynak grubunuzda bir yazım kaynağı oluşturmak için aşağıdaki komutu kullanın:

    ```python
    az cognitiveservices account create --name smart-timer-luis-authoring \
                                        --resource-group smart-timer \
                                        --kind LUIS.Authoring \
                                        --sku F0 \
                                        --yes \
                                        --location <location>
    ```

    `<location>` değerini Kaynak Grubu oluştururken kullandığınız konumla değiştirin.

    > ⚠️ LUIS tüm bölgelerde mevcut değildir, bu yüzden şu hatayı alırsanız:
    >
    > ```output
    > InvalidApiSetId: The account type 'LUIS.Authoring' is either invalid or unavailable in given region.
    > ```
    >
    > farklı bir bölge seçin.

    Bu, ücretsiz katmanlı bir LUIS yazım kaynağı oluşturacaktır.

### Görev - dil anlama uygulaması oluşturma

1. Tarayıcınızda [luis.ai](https://luis.ai?WT.mc_id=academic-17441-jabenn) portalını açın ve Azure için kullandığınız aynı hesapla oturum açın.

1. Diyalogdaki talimatları takip ederek Azure aboneliğinizi seçin, ardından az önce oluşturduğunuz `smart-timer-luis-authoring` kaynağını seçin.

1. *Conversation apps* listesinden **New app** düğmesini seçerek yeni bir uygulama oluşturun. Yeni uygulamayı `smart-timer` olarak adlandırın ve *Culture* alanını dilinize ayarlayın.

    > 💁 Tahmin kaynağı için bir alan var. Tahmin için ayrı bir kaynak oluşturabilirsiniz, ancak ücretsiz yazım kaynağı ayda 1.000 tahmine izin verir ve geliştirme için yeterli olmalıdır, bu yüzden boş bırakabilirsiniz.

1. Uygulamayı oluşturduktan sonra açılan kılavuzu okuyarak dil anlama modelini eğitmek için yapmanız gereken adımları anlayın. Kılavuzu bitirdiğinizde kapatın.

## Niyetler ve Varlıklar

Dil anlama, *niyetler* ve *varlıklar* etrafında şekillenir. Niyetler, kelimelerin amacını ifade eder, örneğin müzik çalmak, zamanlayıcı ayarlamak veya yemek sipariş etmek. Varlıklar ise niyetin neye atıfta bulunduğunu ifade eder, örneğin albüm, zamanlayıcı süresi veya yemek türü. Modelin yorumladığı her cümlede en az bir niyet ve isteğe bağlı olarak bir veya daha fazla varlık bulunmalıdır.

Bazı örnekler:

| Cümle                                              | Niyet            | Varlıklar                                   |
| -------------------------------------------------- | ---------------- | ------------------------------------------ |
| "Taylor Swift'in son albümünü çal"                | *müzik çal*      | *Taylor Swift'in son albümü*               |
| "3 dakikalık bir zamanlayıcı ayarla"              | *zamanlayıcı ayarla* | *3 dakika*                                |
| "Zamanlayıcımı iptal et"                          | *zamanlayıcı iptal et* | Yok                                       |
| "3 büyük ananaslı pizza ve bir sezar salata sipariş et" | *yemek sipariş et* | *3 büyük ananaslı pizza*, *sezar salata* |

✅ Daha önce düşündüğünüz cümlelerde, o cümlenin niyeti ve varsa varlıkları ne olurdu?

LUIS'i eğitmek için önce varlıkları belirlersiniz. Bunlar sabit bir terim listesi olabilir veya metinden öğrenilebilir. Örneğin, menünüzdeki mevcut yiyeceklerin sabit bir listesini, her kelimenin varyasyonları (veya eş anlamlıları) ile sağlayabilirsiniz, örneğin *patlıcan* ve *aubergine* kelimeleri *aubergine* için varyasyonlar olarak. LUIS ayrıca kullanılabilecek önceden oluşturulmuş varlıklar sunar, örneğin sayılar ve konumlar.

Bir zamanlayıcı ayarlamak için, zaman için önceden oluşturulmuş sayı varlıklarını kullanan bir varlık ve bir diğeri birimler için (dakika ve saniye gibi) olmak üzere iki varlık ekleyebilirsiniz. Her birim, tekil ve çoğul formları kapsamak için birden fazla varyasyona sahip olacaktır - örneğin dakika ve dakikalar.

Varlıklar tanımlandıktan sonra niyetler oluşturursunuz. Bunlar, sağladığınız örnek cümlelere (bilinen adıyla ifadeler) dayalı olarak model tarafından öğrenilir. Örneğin, bir *zamanlayıcı ayarla* niyeti için şu cümleleri sağlayabilirsiniz:

* `1 saniyelik bir zamanlayıcı ayarla`
* `1 dakika 12 saniyelik bir zamanlayıcı ayarla`
* `3 dakikalık bir zamanlayıcı ayarla`
* `9 dakika 30 saniyelik bir zamanlayıcı ayarla`

Daha sonra LUIS'e bu cümlelerin hangi bölümlerinin varlıklarla eşleştiğini söylersiniz:

![1 dakika 12 saniyelik bir zamanlayıcı ayarla cümlesi varlıklara bölünmüş](../../../../../translated_images/tr/sentence-as-intent-entities.301401696f992259.webp)

`1 dakika 12 saniyelik bir zamanlayıcı ayarla` cümlesi `zamanlayıcı ayarla` niyetine sahiptir. Ayrıca 2 varlık ve her biri için 2 değer içerir:

|            | zaman | birim   |
| ---------- | ---: | ------ |
| 1 dakika   | 1    | dakika |
| 12 saniye  | 12   | saniye |

İyi bir model eğitmek için, bir kişinin aynı şeyi istemek için kullanabileceği birçok farklı yolu kapsayan çeşitli örnek cümlelere ihtiyacınız vardır.

> 💁 Herhangi bir AI modelinde olduğu gibi, eğitmek için kullandığınız veri ne kadar fazla ve ne kadar doğru olursa, model o kadar iyi olur.

✅ Aynı şeyi istemek için kullanabileceğiniz farklı yolları ve bir insanın anlamasını beklediğiniz yolları düşünün.

### Görev - dil anlama modellerine varlıklar ekleme

Zamanlayıcı için, bir zaman birimi (dakika veya saniye) ve dakika veya saniye sayısı için 2 varlık eklemeniz gerekir.

LUIS portalını kullanma talimatlarını [Microsoft Docs'taki LUIS portalında uygulama oluşturma hızlı başlangıç belgesinde](https://docs.microsoft.com/azure/cognitive-services/luis/luis-get-started-create-app?WT.mc_id=academic-17441-jabenn) bulabilirsiniz.

1. LUIS portalından *Entities* sekmesini seçin ve **Add prebuilt entity** düğmesini seçerek *number* önceden oluşturulmuş varlığı ekleyin, ardından listeden *number* seçin.

1. **Create** düğmesini kullanarak zaman birimi için yeni bir varlık oluşturun. Varlığı `time unit` olarak adlandırın ve türünü *List* olarak ayarlayın. *Normalized values* listesine `minute` ve `second` değerlerini ekleyin, tekil ve çoğul formları *synonyms* listesine ekleyin. Her eş anlamlıyı listeye eklemek için `return` tuşuna basın.

    | Normalized value | Synonyms        |
    | ---------------- | --------------- |
    | minute           | minute, minutes |
    | second           | second, seconds |

### Görev - dil anlama modellerine niyetler ekleme

1. *Intents* sekmesinden **Create** düğmesini seçerek yeni bir niyet oluşturun. Bu niyeti `set timer` olarak adlandırın.

1. Örnekler bölümüne, hem dakika hem saniye ve hem dakika hem saniye kombinasyonlarını kullanarak bir zamanlayıcı ayarlamanın farklı yollarını girin. Örnekler şunlar olabilir:

    * `1 saniyelik bir zamanlayıcı ayarla`
    * `4 dakikalık bir zamanlayıcı ayarla`
    * `dört dakika altı saniyelik bir zamanlayıcı ayarla`
    * `9 dakika 30 saniyelik bir zamanlayıcı ayarla`
    * `1 dakika 12 saniyelik bir zamanlayıcı ayarla`
    * `3 dakikalık bir zamanlayıcı ayarla`
    * `3 dakika 1 saniyelik bir zamanlayıcı ayarla`
    * `üç dakika bir saniyelik bir zamanlayıcı ayarla`
    * `1 dakika 1 saniyelik bir zamanlayıcı ayarla`
    * `30 saniyelik bir zamanlayıcı ayarla`
    * `1 saniyelik bir zamanlayıcı ayarla`

    Modelin hem kelimeleri hem de sayısal ifadeleri işleyebilmesi için sayıları kelime ve rakam olarak karıştırın.

1. Her örneği girerken, LUIS varlıkları algılamaya başlayacak ve bulduğu varlıkları altını çizerek ve etiketleyerek gösterecektir.

    ![LUIS tarafından altı çizilen ve etiketlenen sayılar ve zaman birimleriyle örnekler](../../../../../translated_images/tr/luis-intent-examples.25716580b2d2723c.webp)

### Görev - modeli eğit ve test et

1. Varlıklar ve niyetler yapılandırıldıktan sonra, üst menüdeki **Train** düğmesini kullanarak modeli eğitebilirsiniz. Bu düğmeyi seçin ve model birkaç saniye içinde eğitilecektir. Eğitim sırasında düğme gri olacaktır ve işlem tamamlandığında yeniden etkinleştirilecektir.

1. Üst menüden **Test** düğmesini seçerek dil anlama modelini test edin. `5 dakika 4 saniyelik bir zamanlayıcı ayarla` gibi bir metin girin ve enter tuşuna basın. Cümle, yazdığınız metin kutusunun altında bir kutuda görünecek ve bunun altında *top intent* veya en yüksek olasılıkla algılanan niyet görünecektir. Bu `set timer` olmalıdır. Niyet adı, algılanan niyetin doğru olma olasılığıyla birlikte görünecektir.

1. **Inspect** seçeneğini seçerek sonuçların ayrıntılı bir dökümünü görün. En yüksek puanlı niyet ve yüzde olasılığı ile birlikte algılanan varlıkların listelerini göreceksiniz.

1. Test panelini bitirdiğinizde kapatın.

### Görev - modeli yayınla

Bu modeli koddan kullanmak için yayınlamanız gerekir. LUIS'ten yayınlarken, test için bir aşama ortamına veya tam sürüm için bir ürün ortamına yayınlayabilirsiniz. Bu derste, bir aşama ortamı yeterlidir.

1. LUIS portalından üst menüdeki **Publish** düğmesini seçin.

1. *Staging slot* seçili olduğundan emin olun, ardından **Done** seçeneğini seçin. Uygulama yayınlandığında bir bildirim göreceksiniz.

1. Bunu curl kullanarak test edebilirsiniz. Curl komutunu oluşturmak için üç değere ihtiyacınız var - endpoint, uygulama kimliği (App ID) ve bir API anahtarı. Bunlara üst menüden seçilebilen **MANAGE** sekmesinden erişebilirsiniz.

    1. *Settings* bölümünden App ID'yi kopyalayın.
1. *Azure Kaynakları* bölümünden *Authoring Resource* seçeneğini seçin ve *Primary Key* ile *Endpoint URL* değerlerini kopyalayın.

1. Komut istemcisi veya terminalinizde aşağıdaki curl komutunu çalıştırın:

    ```sh
    curl "<endpoint url>/luis/prediction/v3.0/apps/<app id>/slots/staging/predict" \
          --request GET \
          --get \
          --data "subscription-key=<primary key>" \
          --data "verbose=false" \
          --data "show-all-intents=true" \
          --data-urlencode "query=<sentence>"
    ```

    `<endpoint url>` değerini *Azure Kaynakları* bölümünden aldığınız Endpoint URL ile değiştirin.

    `<app id>` değerini *Ayarlar* bölümünden aldığınız App ID ile değiştirin.

    `<primary key>` değerini *Azure Kaynakları* bölümünden aldığınız Primary Key ile değiştirin.

    `<sentence>` değerini test etmek istediğiniz cümle ile değiştirin.

1. Bu çağrının çıktısı, sorguyu, en yüksek olasılıklı niyeti ve türlerine göre ayrılmış bir varlık listesini detaylandıran bir JSON belgesi olacaktır.

    ```JSON
    {
        "query": "set a timer for 45 minutes and 12 seconds",
        "prediction": {
            "topIntent": "set timer",
            "intents": {
                "set timer": {
                    "score": 0.97031575
                },
                "None": {
                    "score": 0.02205793
                }
            },
            "entities": {
                "number": [
                    45,
                    12
                ],
                "time-unit": [
                    [
                        "minute"
                    ],
                    [
                        "second"
                    ]
                ]
            }
        }
    }
    ```

    Yukarıdaki JSON, `set a timer for 45 minutes and 12 seconds` sorgusundan elde edilmiştir:

    * `set timer` %97 olasılıkla en yüksek niyet olarak tespit edilmiştir.
    * İki *number* (sayı) varlığı tespit edilmiştir: `45` ve `12`.
    * İki *time-unit* (zaman birimi) varlığı tespit edilmiştir: `minute` ve `second`.

## Dil anlama modelini kullanma

Model yayınlandıktan sonra, LUIS modeli koddan çağrılabilir. Önceki derslerde, IoT Hub kullanarak bulut hizmetleriyle iletişim kurmuş, telemetri göndermiş ve komutları dinlemiştiniz. Bu oldukça asenkron bir süreçtir - telemetri gönderildikten sonra kodunuz yanıt beklemez ve bulut hizmeti kapalıysa bunu bilemezsiniz.

Akıllı bir zamanlayıcı için, bir zamanlayıcının ayarlandığını veya bulut hizmetlerinin kullanılamadığını kullanıcıya hemen söyleyebilmek için anında bir yanıt almak isteriz. Bunu yapmak için, IoT cihazımız bir IoT Hub'a güvenmek yerine doğrudan bir web uç noktasını çağıracaktır.

LUIS'i doğrudan IoT cihazından çağırmak yerine, farklı bir tetikleyici türü olan bir HTTP tetikleyici ile sunucusuz kod kullanabilirsiniz. Bu, işlev uygulamanızın REST isteklerini dinlemesine ve yanıt vermesine olanak tanır. Bu işlev, cihazınızın çağırabileceği bir REST uç noktası olacaktır.

> 💁 LUIS'i doğrudan IoT cihazınızdan çağırabilirsiniz, ancak sunucusuz kod gibi bir şey kullanmak daha iyidir. Bu şekilde, örneğin daha iyi bir model eğittiğinizde veya farklı bir dilde bir model eğittiğinizde çağırdığınız LUIS uygulamasını değiştirmek istediğinizde, yalnızca bulut kodunuzu güncellemeniz gerekir; potansiyel olarak binlerce veya milyonlarca IoT cihazına kodu yeniden dağıtmanız gerekmez.

### Görev - sunucusuz bir işlev uygulaması oluşturma

1. `smart-timer-trigger` adında bir Azure Functions uygulaması oluşturun ve bunu VS Code'da açın.

1. Bu uygulamaya, VS Code terminalinden aşağıdaki komutu kullanarak `speech-trigger` adında bir HTTP tetikleyici ekleyin:

    ```sh
    func new --name text-to-timer --template "HTTP trigger"
    ```

    Bu, `text-to-timer` adında bir HTTP tetikleyici oluşturacaktır.

1. İşlev uygulamasını çalıştırarak HTTP tetikleyiciyi test edin. Çalıştırıldığında, çıktıda uç nokta listelenecektir:

    ```output
    Functions:
    
            text-to-timer: [GET,POST] http://localhost:7071/api/text-to-timer
    ```

    Bunu tarayıcınızda [http://localhost:7071/api/text-to-timer](http://localhost:7071/api/text-to-timer) URL'sini yükleyerek test edin.

    ```output
    This HTTP triggered function executed successfully. Pass a name in the query string or in the request body for a personalized response.
    ```

### Görev - dil anlama modelini kullanma

1. LUIS için SDK, bir Pip paketi aracılığıyla kullanılabilir. Bu pakete bağımlılığı eklemek için `requirements.txt` dosyasına aşağıdaki satırı ekleyin:

    ```sh
    azure-cognitiveservices-language-luis
    ```

1. VS Code terminalinin sanal ortamı etkinleştirdiğinden emin olun ve Pip paketlerini yüklemek için aşağıdaki komutu çalıştırın:

    ```sh
    pip install -r requirements.txt
    ```

    > 💁 Hata alırsanız, aşağıdaki komutla pip'i yükseltmeniz gerekebilir:
    >
    > ```sh
    > pip install --upgrade pip
    > ```

1. LUIS API Anahtarınız, Endpoint URL'niz ve App ID'niz için **YÖNET** sekmesinden `local.settings.json` dosyasına yeni girişler ekleyin:

    ```JSON
    "LUIS_KEY": "<primary key>",
    "LUIS_ENDPOINT_URL": "<endpoint url>",
    "LUIS_APP_ID": "<app id>"
    ```

    `<endpoint url>` değerini **YÖNET** sekmesindeki *Azure Kaynakları* bölümünden aldığınız Endpoint URL ile değiştirin. Bu, `https://<location>.api.cognitive.microsoft.com/` formatında olacaktır.

    `<app id>` değerini **YÖNET** sekmesindeki *Ayarlar* bölümünden aldığınız App ID ile değiştirin.

    `<primary key>` değerini **YÖNET** sekmesindeki *Azure Kaynakları* bölümünden aldığınız Primary Key ile değiştirin.

1. `__init__.py` dosyasına aşağıdaki importları ekleyin:

    ```python
    import json
    import os
    from azure.cognitiveservices.language.luis.runtime import LUISRuntimeClient
    from msrest.authentication import CognitiveServicesCredentials
    ```

    Bu, bazı sistem kütüphanelerini ve LUIS ile etkileşim kurmak için gerekli kütüphaneleri içe aktarır.

1. `main` metodunun içeriğini silin ve aşağıdaki kodu ekleyin:

    ```python
    luis_key = os.environ['LUIS_KEY']
    endpoint_url = os.environ['LUIS_ENDPOINT_URL']
    app_id = os.environ['LUIS_APP_ID']
    
    credentials = CognitiveServicesCredentials(luis_key)
    client = LUISRuntimeClient(endpoint=endpoint_url, credentials=credentials)
    ```

    Bu, LUIS uygulamanız için `local.settings.json` dosyasına eklediğiniz değerleri yükler, API anahtarınızla bir kimlik bilgisi nesnesi oluşturur ve LUIS uygulamanızla etkileşim kurmak için bir LUIS istemci nesnesi oluşturur.

1. Bu HTTP tetikleyici, JSON olarak anlaşılması gereken metni içeren bir `text` özelliği ile HTTP isteğinin gövdesinden çağrılacaktır. Aşağıdaki kod, HTTP isteğinin gövdesinden değeri çıkarır ve konsola kaydeder. Bu kodu `main` fonksiyonuna ekleyin:

    ```python
    req_body = req.get_json()
    text = req_body['text']
    logging.info(f'Request - {text}')
    ```

1. LUIS'ten tahminler, bir tahmin isteği gönderilerek talep edilir - tahmin edilecek metni içeren bir JSON belgesi. Bunu aşağıdaki kodla oluşturun:

    ```python
    prediction_request = { 'query' : text }
    ```

1. Bu istek, uygulamanızın yayınlandığı staging slotunu kullanarak LUIS'e gönderilebilir:

    ```python
    prediction_response = client.prediction.get_slot_prediction(app_id, 'Staging', prediction_request)
    ```

1. Tahmin yanıtı, en yüksek niyeti - en yüksek tahmin puanına sahip niyeti - ve varlıkları içerir. En yüksek niyet `set timer` ise, varlıklar zamanlayıcı için gereken süreyi almak için okunabilir:

    ```python
    if prediction_response.prediction.top_intent == 'set timer':
        numbers = prediction_response.prediction.entities['number']
        time_units = prediction_response.prediction.entities['time unit']
        total_seconds = 0
    ```

    `number` varlıkları bir sayı dizisi olacaktır. Örneğin, *"Set a four minute 17 second timer."* dediyseniz, `number` dizisi 2 tam sayı içerecektir - 4 ve 17.

    `time unit` varlıkları, her zaman birimini içeren bir dizi dizisi olacaktır. Örneğin, *"Set a four minute 17 second timer."* dediyseniz, `time unit` dizisi her biri tek bir değer içeren 2 dizi içerecektir - `['minute']` ve `['second']`.

    *"Set a four minute 17 second timer."* için bu varlıkların JSON versiyonu:

    ```json
    {
        "number": [4, 17],
        "time unit": [
            ["minute"],
            ["second"]
        ]
    }
    ```

    Bu kod ayrıca zamanlayıcı için toplam süreyi saniye cinsinden tanımlayan bir sayaç oluşturur. Bu, varlıklardan alınan değerlerle doldurulacaktır.

1. Varlıklar bağlantılı değildir, ancak bunlar hakkında bazı varsayımlar yapabiliriz. Konuşma sırasına göre sıralanacaklardır, bu nedenle dizideki konum, hangi sayının hangi zaman birimiyle eşleştiğini belirlemek için kullanılabilir. Örneğin:

    * *"Set a 30 second timer"* - bu, bir sayı `30` ve bir zaman birimi `second` içerecektir, bu nedenle tek sayı tek zaman birimiyle eşleşecektir.
    * *"Set a 2 minute and 30 second timer"* - bu, iki sayı `2` ve `30` ve iki zaman birimi `minute` ve `second` içerecektir, bu nedenle ilk sayı ilk zaman birimi için (2 dakika) ve ikinci sayı ikinci zaman birimi için (30 saniye) olacaktır.

    Aşağıdaki kod, sayı varlıklarındaki öğe sayısını alır ve her diziden ilk öğeyi, ardından ikinciyi vb. çıkarır. Bunu `if` bloğunun içine ekleyin:

    ```python
    for i in range(0, len(numbers)):
        number = numbers[i]
        time_unit = time_units[i][0]
    ```

    *"Set a four minute 17 second timer."* için bu, iki kez döngü yapacak ve şu değerleri verecektir:

    | döngü sayısı | `number` | `time_unit` |
    | ------------:| --------:| ----------- |
    | 0            | 4        | minute      |
    | 1            | 17       | second      |

1. Bu döngü içinde, toplam zamanlayıcı süresini hesaplamak için sayı ve zaman birimini kullanın, her dakika için 60 saniye ve her saniye için saniye sayısını ekleyin.

    ```python
    if time_unit == 'minute':
        total_seconds += number * 60
    else:
        total_seconds += number
    ```

1. Varlıklar üzerinden yapılan bu döngünün dışında, zamanlayıcı için toplam süreyi günlüğe kaydedin:

    ```python
    logging.info(f'Timer required for {total_seconds} seconds')
    ```

1. Saniye sayısı, bir HTTP yanıtı olarak işlevden döndürülmelidir. `if` bloğunun sonunda aşağıdakileri ekleyin:

    ```python
    payload = {
        'seconds': total_seconds
    }
    return func.HttpResponse(json.dumps(payload), status_code=200)
    ```

    Bu kod, zamanlayıcı için toplam saniye sayısını içeren bir yük oluşturur, bunu bir JSON dizesine dönüştürür ve başarılı bir çağrıyı ifade eden 200 durum koduyla bir HTTP sonucu olarak döndürür.

1. Son olarak, niyet tanınmadığında bir hata kodu döndürmek için `if` bloğunun dışında aşağıdakileri ekleyin:

    ```python
    return func.HttpResponse(status_code=404)
    ```

    404, *bulunamadı* durum kodudur.

1. İşlev uygulamasını çalıştırın ve curl kullanarak test edin.

    ```sh
    curl --request POST 'http://localhost:7071/api/text-to-timer' \
         --header 'Content-Type: application/json' \
         --include \
         --data '{"text":"<text>"}'
    ```

    `<text>` değerini isteğinizin metniyle değiştirin, örneğin `set a 2 minutes 27 second timer`.

    İşlev uygulamasından aşağıdaki çıktıyı göreceksiniz:

    ```output
    Functions:

            text-to-timer: [GET,POST] http://localhost:7071/api/text-to-timer
    
    For detailed output, run func with --verbose flag.
    [2021-06-26T19:45:14.502Z] Worker process started and initialized.
    [2021-06-26T19:45:19.338Z] Host lock lease acquired by instance ID '000000000000000000000000951CAE4E'.
    [2021-06-26T19:45:52.059Z] Executing 'Functions.text-to-timer' (Reason='This function was programmatically called via the host APIs.', Id=f68bfb90-30e4-47a5-99da-126b66218e81)
    [2021-06-26T19:45:53.577Z] Timer required for 147 seconds
    [2021-06-26T19:45:53.746Z] Executed 'Functions.text-to-timer' (Succeeded, Id=f68bfb90-30e4-47a5-99da-126b66218e81, Duration=1750ms)
    ```

    Curl çağrısı aşağıdakini döndürecektir:

    ```output
    HTTP/1.1 200 OK
    Date: Tue, 29 Jun 2021 01:14:11 GMT
    Content-Type: text/plain; charset=utf-8
    Server: Kestrel
    Transfer-Encoding: chunked
    
    {"seconds": 147}
    ```

    Zamanlayıcı için saniye sayısı `"seconds"` değerinde yer alır.

> 💁 Bu kodu [code/functions](../../../../../6-consumer/lessons/2-language-understanding/code/functions) klasöründe bulabilirsiniz.

### Görev - işlevinizi IoT cihazınıza erişilebilir hale getirme

1. IoT cihazınızın REST uç noktanızı çağırabilmesi için URL'yi bilmesi gerekecektir. Daha önce eriştiğinizde, yerel makinenizdeki REST uç noktalarına erişmek için bir kısayol olan `localhost` kullandınız. IoT cihazınızın erişebilmesi için ya buluta yayın yapmanız ya da yerel olarak erişmek için IP adresinizi almanız gerekir.

    > ⚠️ Bir Wio Terminal kullanıyorsanız, işlev uygulamasını daha önce yaptığınız gibi dağıtamayacağınız anlamına gelen kütüphane bağımlılıkları olacağından, işlev uygulamasını yerel olarak çalıştırmak daha kolaydır. İşlev uygulamasını yerel olarak çalıştırın ve bilgisayarınızın IP adresi üzerinden erişin. Buluta dağıtmak isterseniz, bunu yapmanın yolu hakkında sonraki bir derste bilgi verilecektir.

    * İşlev uygulamasını yayınlayın - işlev uygulamanızı buluta yayınlamak için önceki derslerdeki talimatları izleyin. Yayınlandıktan sonra, URL `https://<APP_NAME>.azurewebsites.net/api/text-to-timer` olacaktır, burada `<APP_NAME>` işlev uygulamanızın adı olacaktır. Yerel ayarlarınızı da yayınladığınızdan emin olun.

      HTTP tetikleyicilerle çalışırken, varsayılan olarak bir işlev uygulaması anahtarıyla güvence altına alınırlar. Bu anahtarı almak için aşağıdaki komutu çalıştırın:

      ```sh
      az functionapp keys list --resource-group smart-timer \
                               --name <APP_NAME>                               
      ```

      `functionKeys` bölümündeki `default` girişinin değerini kopyalayın.

      ```output
      {
        "functionKeys": {
          "default": "sQO1LQaeK9N1qYD6SXeb/TctCmwQEkToLJU6Dw8TthNeUH8VA45hlA=="
        },
        "masterKey": "RSKOAIlyvvQEQt9dfpabJT018scaLpQu9p1poHIMCxx5LYrIQZyQ/g==",
        "systemKeys": {}
      }
      ```

      Bu anahtar, URL'ye bir sorgu parametresi olarak eklenmelidir, böylece son URL `https://<APP_NAME>.azurewebsites.net/api/text-to-timer?code=<FUNCTION_KEY>` olacaktır, burada `<APP_NAME>` işlev uygulamanızın adı ve `<FUNCTION_KEY>` varsayılan işlev anahtarınız olacaktır.

      > 💁 HTTP tetikleyicisinin yetkilendirme türünü `function.json` dosyasındaki `authlevel` ayarını kullanarak değiştirebilirsiniz. Bunun hakkında daha fazla bilgiyi [Microsoft belgelerindeki Azure Functions HTTP tetikleyici dokümantasyonunun yapılandırma bölümünde](https://docs.microsoft.com/azure/azure-functions/functions-bindings-http-webhook-trigger?WT.mc_id=academic-17441-jabenn&tabs=python#configuration) okuyabilirsiniz.

    * İşlev uygulamasını yerel olarak çalıştırın ve IP adresini kullanarak erişin - bilgisayarınızın yerel ağdaki IP adresini alabilir ve bunu URL'yi oluşturmak için kullanabilirsiniz.

      IP adresinizi bulun:

      * Windows 10'da, [IP adresinizi bulma kılavuzunu](https://support.microsoft.com/windows/find-your-ip-address-f21a9bbc-c582-55cd-35e0-73431160a1b9?WT.mc_id=academic-17441-jabenn) izleyin.
      * macOS'ta, [Mac'te IP adresinizi nasıl bulacağınızı](https://www.hellotech.com/guide/for/how-to-find-ip-address-on-mac) öğrenin.
      * Linux'ta, [Linux'ta IP adresinizi nasıl bulacağınızı](https://opensource.com/article/18/5/how-find-ip-address-linux) öğrenin.

      IP adresinizi aldıktan sonra, işlevi şu adreste erişebilirsiniz: `http://`

:7071/api/text-to-timer`, burada `<IP_ADDRESS>` sizin IP adresiniz olacak, örneğin `http://192.168.1.10:7071/api/text-to-timer`.

      > 💁 Bunun port 7071 kullandığını unutmayın, bu yüzden IP adresinden sonra `:7071` eklemeniz gerekecek.

      > 💁 Bu yalnızca IoT cihazınız bilgisayarınızla aynı ağda olduğunda çalışır.

1. Curl kullanarak endpoint'i test edin.

---

## 🚀 Meydan Okuma

Aynı şeyi istemenin birçok yolu vardır, örneğin bir zamanlayıcı ayarlamak. Bunu yapmanın farklı yollarını düşünün ve bunları LUIS uygulamanızda örnek olarak kullanın. Modelinizin bir zamanlayıcı istemenin birden fazla yoluyla ne kadar iyi başa çıkabildiğini görmek için bunları test edin.

## Ders Sonrası Test

[Ders sonrası test](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/44)

## Gözden Geçirme ve Kendi Kendine Çalışma

* LUIS ve yetenekleri hakkında daha fazla bilgi edinmek için [Microsoft dokümanlarındaki Language Understanding (LUIS) dokümantasyon sayfasını](https://docs.microsoft.com/azure/cognitive-services/luis/?WT.mc_id=academic-17441-jabenn) okuyun.  
* Dil anlama hakkında daha fazla bilgi edinmek için [Wikipedia'daki doğal dil anlama sayfasını](https://wikipedia.org/wiki/Natural-language_understanding) okuyun.  
* HTTP tetikleyicileri hakkında daha fazla bilgi edinmek için [Microsoft dokümanlarındaki Azure Functions HTTP tetikleyici dokümantasyonunu](https://docs.microsoft.com/azure/azure-functions/functions-bindings-http-webhook-trigger?WT.mc_id=academic-17441-jabenn&tabs=python) okuyun.  

## Ödev

[Zamanlayıcıyı iptal et](assignment.md)

---

**Feragatname**:  
Bu belge, AI çeviri hizmeti [Co-op Translator](https://github.com/Azure/co-op-translator) kullanılarak çevrilmiştir. Doğruluk için çaba göstersek de, otomatik çevirilerin hata veya yanlışlıklar içerebileceğini lütfen unutmayın. Belgenin orijinal dili, yetkili kaynak olarak kabul edilmelidir. Kritik bilgiler için profesyonel insan çevirisi önerilir. Bu çevirinin kullanımından kaynaklanan yanlış anlamalar veya yanlış yorumlamalar için sorumluluk kabul etmiyoruz.