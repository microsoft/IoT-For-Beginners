<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "6754c915dae64ba70fcd5e52c37f3adf",
  "translation_date": "2025-08-28T03:31:01+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/wio-terminal-commands.md",
  "language_code": "tr"
}
-->
# Gece lambanızı İnternet üzerinden kontrol edin - Wio Terminal

Bu dersin bu bölümünde, Wio Terminal'inize bir MQTT brokerından gönderilen komutlara abone olacaksınız.

## Komutlara Abone Olun

Bir sonraki adım, MQTT brokerından gönderilen komutlara abone olmak ve bunlara yanıt vermektir.

### Görev

Komutlara abone olun.

1. Gece lambası projesini VS Code'da açın.

1. Komutlar için konu adını tanımlamak üzere `config.h` dosyasının en altına aşağıdaki kodu ekleyin:

    ```cpp
    const string SERVER_COMMAND_TOPIC = ID + "/commands";
    ```

    `SERVER_COMMAND_TOPIC`, cihazın LED komutlarını almak için abone olacağı konudur.

1. MQTT istemcisi yeniden bağlandığında komut konusuna abone olmak için `reconnectMQTTClient` fonksiyonunun sonuna aşağıdaki satırı ekleyin:

    ```cpp
    client.subscribe(SERVER_COMMAND_TOPIC.c_str());
    ```

1. `reconnectMQTTClient` fonksiyonunun altına aşağıdaki kodu ekleyin:

    ```cpp
    void clientCallback(char *topic, uint8_t *payload, unsigned int length)
    {
        char buff[length + 1];
        for (int i = 0; i < length; i++)
        {
            buff[i] = (char)payload[i];
        }
        buff[length] = '\0';
    
        Serial.print("Message received:");
        Serial.println(buff);
    
        DynamicJsonDocument doc(1024);
        deserializeJson(doc, buff);
        JsonObject obj = doc.as<JsonObject>();
    
        bool led_on = obj["led_on"];
    
        if (led_on)
            digitalWrite(D0, HIGH);
        else
            digitalWrite(D0, LOW);
    }
    ```

    Bu fonksiyon, MQTT istemcisinin sunucudan bir mesaj aldığında çağıracağı geri çağırma (callback) olacaktır.

    Mesaj, bir dizi 8-bitlik işaretsiz tamsayı olarak alınır, bu nedenle metin olarak işlenebilmesi için bir karakter dizisine dönüştürülmesi gerekir.

    Mesaj bir JSON belgesi içerir ve ArduinoJson kütüphanesi kullanılarak çözülür. JSON belgesinin `led_on` özelliği okunur ve değere bağlı olarak LED açılır veya kapatılır.

1. `createMQTTClient` fonksiyonuna aşağıdaki kodu ekleyin:

    ```cpp
    client.setCallback(clientCallback);
    ```

    Bu kod, MQTT brokerından bir mesaj alındığında çağrılacak geri çağırmayı `clientCallback` olarak ayarlar.

    > 💁 `clientCallback` işleyicisi, abone olunan tüm konular için çağrılır. Daha sonra birden fazla konuyu dinleyen kod yazarsanız, geri çağırma fonksiyonuna iletilen `topic` parametresinden mesajın gönderildiği konuyu alabilirsiniz.

1. Kodu Wio Terminal'inize yükleyin ve Seri Monitör'ü kullanarak ışık seviyelerinin MQTT brokerına gönderildiğini görün.

1. Fiziksel veya sanal cihazınız tarafından algılanan ışık seviyelerini ayarlayın. Terminalde mesajların alındığını ve komutların gönderildiğini göreceksiniz. Ayrıca ışık seviyesine bağlı olarak LED'in açılıp kapandığını göreceksiniz.

> 💁 Bu kodu [code-commands/wio-terminal](../../../../../1-getting-started/lessons/4-connect-internet/code-commands/wio-terminal) klasöründe bulabilirsiniz.

😀 Cihazınızı bir MQTT brokerından gelen komutlara yanıt verecek şekilde başarıyla kodladınız.

---

**Feragatname**:  
Bu belge, AI çeviri hizmeti [Co-op Translator](https://github.com/Azure/co-op-translator) kullanılarak çevrilmiştir. Doğruluk için çaba göstersek de, otomatik çevirilerin hata veya yanlışlık içerebileceğini lütfen unutmayın. Belgenin orijinal dili, yetkili kaynak olarak kabul edilmelidir. Kritik bilgiler için profesyonel insan çevirisi önerilir. Bu çevirinin kullanımından kaynaklanan yanlış anlamalar veya yanlış yorumlamalar için sorumluluk kabul etmiyoruz.