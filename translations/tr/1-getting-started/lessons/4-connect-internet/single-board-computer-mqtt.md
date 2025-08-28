<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "90fb93446e03c38f3c0e4009c2471906",
  "translation_date": "2025-08-28T03:33:11+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/single-board-computer-mqtt.md",
  "language_code": "tr"
}
-->
# Gece lambanızı İnternet üzerinden kontrol edin - Sanal IoT Donanımı ve Raspberry Pi

IoT cihazının, ışık sensörü okumasıyla telemetri değerlerini göndermek ve LED'i kontrol etmek için komutlar almak üzere MQTT kullanarak *test.mosquitto.org* ile iletişim kuracak şekilde kodlanması gerekiyor.

Bu dersin bu bölümünde, Raspberry Pi veya sanal IoT cihazınızı bir MQTT brokerine bağlayacaksınız.

## MQTT istemci paketini yükleyin

MQTT broker ile iletişim kurmak için, Pi'nize veya sanal bir cihaz kullanıyorsanız sanal ortamınıza bir MQTT kütüphanesi pip paketi yüklemeniz gerekiyor.

### Görev

Pip paketini yükleyin

1. VS Code'da gece lambası projesini açın.

1. Sanal bir IoT cihazı kullanıyorsanız, terminalin sanal ortamı çalıştırdığından emin olun. Raspberry Pi kullanıyorsanız sanal bir ortam kullanmayacaksınız.

1. MQTT pip paketini yüklemek için aşağıdaki komutu çalıştırın:

    ```sh
    pip3 install paho-mqtt
    ```

## Cihazı kodlayın

Cihaz kodlamaya hazır.

### Görev

Cihaz kodunu yazın.

1. `app.py` dosyasının en üstüne aşağıdaki import'u ekleyin:

    ```python
    import paho.mqtt.client as mqtt
    ```

    `paho.mqtt.client` kütüphanesi, uygulamanızın MQTT üzerinden iletişim kurmasını sağlar.

1. Işık sensörü ve LED tanımlarından sonra aşağıdaki kodu ekleyin:

    ```python
    id = '<ID>'

    client_name = id + 'nightlight_client'
    ```

    `<ID>` yerine bu cihaz istemcisi için kullanılacak benzersiz bir kimlik girin. Bu kimlik, daha sonra bu cihazın yayınladığı ve abone olduğu konular için kullanılacaktır. *test.mosquitto.org* brokeri herkese açık ve birçok kişi tarafından, bu ödevi yapan diğer öğrenciler de dahil olmak üzere, kullanılmaktadır. Benzersiz bir MQTT istemci adı ve konu adları kullanmak, kodunuzun başkalarının koduyla çakışmamasını sağlar. Bu kimliği, bu ödevin ilerleyen bölümlerinde sunucu kodunu oluştururken de kullanmanız gerekecek.

    > 💁 Benzersiz bir kimlik oluşturmak için [GUIDGen](https://www.guidgen.com) gibi bir web sitesi kullanabilirsiniz.

    `client_name`, broker üzerindeki bu MQTT istemcisi için benzersiz bir isimdir.

1. MQTT istemci nesnesi oluşturmak ve MQTT brokerine bağlanmak için bu yeni kodun altına aşağıdaki kodu ekleyin:

    ```python
    mqtt_client = mqtt.Client(client_name)
    mqtt_client.connect('test.mosquitto.org')
    
    mqtt_client.loop_start()

    print("MQTT connected!")
    ```

    Bu kod, istemci nesnesini oluşturur, herkese açık MQTT brokerine bağlanır ve arka planda bir işleme döngüsü başlatır. Bu döngü, abone olunan konulardaki mesajları dinler.

1. Ödevin önceki bölümündeki kodu çalıştırdığınız şekilde bu kodu çalıştırın. Sanal bir IoT cihazı kullanıyorsanız, CounterFit uygulamasının çalıştığından ve ışık sensörü ile LED'in doğru pinlerde oluşturulduğundan emin olun.

    ```output
    (.venv) ➜  nightlight python app.py 
    MQTT connected!
    Light level: 0
    Light level: 0
    ```

> 💁 Bu kodu [code-mqtt/virtual-device](../../../../../1-getting-started/lessons/4-connect-internet/code-mqtt/virtual-device) klasöründe veya [code-mqtt/pi](../../../../../1-getting-started/lessons/4-connect-internet/code-mqtt/pi) klasöründe bulabilirsiniz.

😀 Cihazınızı başarıyla bir MQTT brokerine bağladınız.

---

**Feragatname**:  
Bu belge, AI çeviri hizmeti [Co-op Translator](https://github.com/Azure/co-op-translator) kullanılarak çevrilmiştir. Doğruluk için çaba göstersek de, otomatik çevirilerin hata veya yanlışlıklar içerebileceğini lütfen unutmayın. Belgenin orijinal dili, yetkili kaynak olarak kabul edilmelidir. Kritik bilgiler için profesyonel insan çevirisi önerilir. Bu çevirinin kullanımından kaynaklanan yanlış anlamalar veya yanlış yorumlamalar için sorumluluk kabul etmiyoruz.