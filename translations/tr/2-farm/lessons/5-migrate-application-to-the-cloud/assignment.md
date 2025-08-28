<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "c24b6e4d90501c9199f2ceb6a648a337",
  "translation_date": "2025-08-28T04:01:12+00:00",
  "source_file": "2-farm/lessons/5-migrate-application-to-the-cloud/assignment.md",
  "language_code": "tr"
}
-->
# Manuel Röle Kontrolü Ekle

## Talimatlar

Sunucusuz kod, HTTP istekleri de dahil olmak üzere birçok farklı şey tarafından tetiklenebilir. HTTP tetikleyicilerini kullanarak röle kontrolünü manuel olarak devre dışı bırakabilir veya etkinleştirebilirsiniz. Bu, bir web isteği aracılığıyla birinin röleyi açıp kapatmasına olanak tanır.

Bu görev için, cihazınıza komut göndermek için bu derste öğrendiklerinizi yeniden kullanarak, röleyi açıp kapatmak için Functions App'inize iki HTTP tetikleyici eklemeniz gerekiyor.

Bazı ipuçları:

* Mevcut Functions App'inize bir HTTP tetikleyici eklemek için aşağıdaki komutu kullanabilirsiniz:

    ```sh
    func new --name <trigger name> --template "HTTP trigger"
    ```

    `<trigger name>` kısmını HTTP tetikleyiciniz için bir adla değiştirin. Örneğin, `relay_on` ve `relay_off` gibi adlar kullanabilirsiniz.

* HTTP tetikleyiciler erişim kontrolüne sahip olabilir. Varsayılan olarak, çalıştırılabilmesi için URL ile birlikte işleve özgü bir API anahtarı geçirilmesi gerekir. Bu görev için, bu kısıtlamayı kaldırabilir ve herkesin işlevi çalıştırabilmesini sağlayabilirsiniz. Bunu yapmak için, HTTP tetikleyiciler için `function.json` dosyasındaki `authLevel` ayarını aşağıdaki şekilde güncelleyin:

    ```json
    "authLevel": "anonymous"
    ```

    > 💁 Bu erişim kontrolü hakkında daha fazla bilgiyi [Function access keys documentation](https://docs.microsoft.com/azure/azure-functions/functions-bindings-http-webhook-trigger?WT.mc_id=academic-17441-jabenn#authorization-keys) adresinde okuyabilirsiniz.

* HTTP tetikleyiciler varsayılan olarak GET ve POST isteklerini destekler. Bu, onları web tarayıcınızı kullanarak çağırabileceğiniz anlamına gelir - web tarayıcıları GET istekleri yapar.

    Functions App'inizi yerel olarak çalıştırdığınızda, tetikleyicinin URL'sini göreceksiniz:

    ```output
    Functions:

        relay_off: [GET,POST] http://localhost:7071/api/relay_off

        relay_on: [GET,POST] http://localhost:7071/api/relay_on

        iot-hub-trigger: eventHubTrigger
    ```

    URL'yi tarayıcınıza yapıştırın ve `enter` tuşuna basın veya VS Code'daki terminal penceresindeki bağlantıya `Ctrl+click` (macOS'ta `Cmd+click`) yaparak varsayılan tarayıcınızda açın. Bu, tetikleyiciyi çalıştıracaktır.

    > 💁 URL'nin `/api` içerdiğine dikkat edin - HTTP tetikleyiciler varsayılan olarak `api` alt alanında bulunur.

* Functions App'i dağıttığınızda, HTTP tetikleyici URL'si şu şekilde olacaktır:

    `https://<functions app name>.azurewebsites.net/api/<trigger name>`

    Burada `<functions app name>` Functions App'inizin adı, `<trigger name>` ise tetikleyicinizin adıdır.

## Değerlendirme Kriterleri

| Kriter | Örnek Çalışma | Yeterli | Geliştirmeye Açık |
| -------- | --------- | -------- | ----------------- |
| HTTP tetikleyiciler oluşturma | Röleyi açıp kapatmak için uygun adlara sahip 2 tetikleyici oluşturuldu | Uygun bir ada sahip bir tetikleyici oluşturuldu | Hiçbir tetikleyici oluşturulamadı |
| HTTP tetikleyicilerden röleyi kontrol etme | Her iki tetikleyici de IoT Hub'a bağlanarak röleyi uygun şekilde kontrol edebildi | Bir tetikleyici IoT Hub'a bağlanarak röleyi uygun şekilde kontrol edebildi | Tetikleyiciler IoT Hub'a bağlanamadı |

---

**Feragatname**:  
Bu belge, AI çeviri hizmeti [Co-op Translator](https://github.com/Azure/co-op-translator) kullanılarak çevrilmiştir. Doğruluk için çaba göstersek de, otomatik çevirilerin hata veya yanlışlıklar içerebileceğini lütfen unutmayın. Belgenin orijinal dili, yetkili kaynak olarak kabul edilmelidir. Kritik bilgiler için profesyonel insan çevirisi önerilir. Bu çevirinin kullanımından kaynaklanan yanlış anlamalar veya yanlış yorumlamalar için sorumluluk kabul etmiyoruz.