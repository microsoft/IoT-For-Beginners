<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "c527ce85d69b1a3875366ec61cbed8aa",
  "translation_date": "2025-08-28T03:32:28+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/single-board-computer-commands.md",
  "language_code": "tr"
}
-->
# Gece lambanızı İnternet üzerinden kontrol edin - Sanal IoT Donanımı ve Raspberry Pi

Bu dersin bu bölümünde, bir MQTT brokerından Raspberry Pi'nize veya sanal IoT cihazınıza gönderilen komutlara abone olacaksınız.

## Komutlara Abone Olun

Bir sonraki adım, MQTT brokerından gönderilen komutlara abone olmak ve bunlara yanıt vermektir.

### Görev

Komutlara abone olun.

1. VS Code'da gece lambası projesini açın.

1. Eğer bir sanal IoT cihazı kullanıyorsanız, terminalin sanal ortamı çalıştırdığından emin olun. Eğer bir Raspberry Pi kullanıyorsanız, sanal bir ortam kullanmayacaksınız.

1. `client_telemetry_topic` tanımlarından sonra aşağıdaki kodu ekleyin:

    ```python
    server_command_topic = id + '/commands'
    ```

    `server_command_topic`, cihazın LED komutlarını almak için abone olacağı MQTT konusudur.

1. Ana döngünün hemen üstüne, `mqtt_client.loop_start()` satırından sonra aşağıdaki kodu ekleyin:

    ```python
    def handle_command(client, userdata, message):
        payload = json.loads(message.payload.decode())
        print("Message received:", payload)
    
        if payload['led_on']:
            led.on()
        else:
            led.off()
    
    mqtt_client.subscribe(server_command_topic)
    mqtt_client.on_message = handle_command
    ```

    Bu kod, bir mesajı JSON belgesi olarak okuyan ve `led_on` özelliğinin değerini arayan bir `handle_command` fonksiyonunu tanımlar. Eğer `True` olarak ayarlanmışsa LED açılır, aksi takdirde kapanır.

    MQTT istemcisi, sunucunun mesaj göndereceği konuya abone olur ve bir mesaj alındığında çağrılacak `handle_command` fonksiyonunu ayarlar.

    > 💁 `on_message` işleyicisi, abone olunan tüm konular için çağrılır. Daha sonra birden fazla konuyu dinleyen bir kod yazarsanız, mesajın gönderildiği konuyu işleyici fonksiyonuna iletilen `message` nesnesinden alabilirsiniz.

1. Kodu, ödevin önceki bölümündeki kodu çalıştırdığınız şekilde çalıştırın. Eğer bir sanal IoT cihazı kullanıyorsanız, CounterFit uygulamasının çalıştığından ve ışık sensörü ile LED'in doğru pinlerde oluşturulduğundan emin olun.

1. Fiziksel veya sanal cihazınız tarafından algılanan ışık seviyelerini ayarlayın. Alınan mesajlar ve gönderilen komutlar terminale yazılacaktır. Ayrıca, ışık seviyesine bağlı olarak LED açılıp kapanacaktır.

> 💁 Bu kodu [code-commands/virtual-device](../../../../../1-getting-started/lessons/4-connect-internet/code-commands/virtual-device) klasöründe veya [code-commands/pi](../../../../../1-getting-started/lessons/4-connect-internet/code-commands/pi) klasöründe bulabilirsiniz.

😀 Cihazınızı bir MQTT brokerından gelen komutlara yanıt verecek şekilde başarıyla kodladınız.

---

**Feragatname**:  
Bu belge, AI çeviri hizmeti [Co-op Translator](https://github.com/Azure/co-op-translator) kullanılarak çevrilmiştir. Doğruluğu sağlamak için çaba göstersek de, otomatik çevirilerin hata veya yanlışlık içerebileceğini lütfen unutmayın. Belgenin orijinal dili, yetkili kaynak olarak kabul edilmelidir. Kritik bilgiler için profesyonel insan çevirisi önerilir. Bu çevirinin kullanımından kaynaklanan yanlış anlamalar veya yanlış yorumlamalar için sorumluluk kabul etmiyoruz.