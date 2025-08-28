<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "1226517aae5f5b6f904434670394c688",
  "translation_date": "2025-08-28T03:32:07+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/single-board-computer-telemetry.md",
  "language_code": "tr"
}
-->
# İnternet Üzerinden Gece Lambanızı Kontrol Edin - Sanal IoT Donanımı ve Raspberry Pi

Bu dersin bu bölümünde, Raspberry Pi'nizden veya sanal IoT cihazınızdan ışık seviyeleriyle birlikte telemetriyi bir MQTT brokerına göndereceksiniz.

## Telemetri Yayınlama

Bir sonraki adım, telemetri ile bir JSON belgesi oluşturmak ve bunu MQTT brokerına göndermektir.

### Görev

Telemetriyi MQTT brokerına yayınlayın.

1. VS Code'da gece lambası projesini açın.

1. Eğer bir sanal IoT cihazı kullanıyorsanız, terminalin sanal ortamı çalıştırdığından emin olun. Eğer bir Raspberry Pi kullanıyorsanız, sanal bir ortam kullanmayacaksınız.

1. `app.py` dosyasının en üstüne şu import'u ekleyin:

    ```python
    import json
    ```

    `json` kütüphanesi, telemetriyi bir JSON belgesi olarak kodlamak için kullanılır.

1. `client_name` tanımından sonra şu satırları ekleyin:

    ```python
    client_telemetry_topic = id + '/telemetry'
    ```

    `client_telemetry_topic`, cihazın ışık seviyelerini yayınlayacağı MQTT konusudur.

1. Dosyanın sonundaki `while True:` döngüsünün içeriğini şu kodla değiştirin:

    ```python
    while True:
        light = light_sensor.light
        telemetry = json.dumps({'light' : light})

        print("Sending telemetry ", telemetry)
    
        mqtt_client.publish(client_telemetry_topic, telemetry)
    
        time.sleep(5)
    ```

    Bu kod, ışık seviyesini bir JSON belgesine paketler ve MQTT brokerına yayınlar. Daha sonra, mesajların gönderilme sıklığını azaltmak için bir süre bekler.

1. Kodu, ödevin önceki bölümündeki kodu çalıştırdığınız şekilde çalıştırın. Eğer bir sanal IoT cihazı kullanıyorsanız, CounterFit uygulamasının çalıştığından ve ışık sensörü ile LED'in doğru pinlerde oluşturulduğundan emin olun.

    ```output
    (.venv) ➜  nightlight python app.py 
    MQTT connected!
    Sending telemetry  {"light": 0}
    Sending telemetry  {"light": 0}
    ```

> 💁 Bu kodu [code-telemetry/virtual-device](../../../../../1-getting-started/lessons/4-connect-internet/code-telemetry/virtual-device) klasöründe veya [code-telemetry/pi](../../../../../1-getting-started/lessons/4-connect-internet/code-telemetry/pi) klasöründe bulabilirsiniz.

😀 Cihazınızdan başarıyla telemetri gönderdiniz.

---

**Feragatname**:  
Bu belge, AI çeviri hizmeti [Co-op Translator](https://github.com/Azure/co-op-translator) kullanılarak çevrilmiştir. Doğruluk için çaba göstersek de, otomatik çevirilerin hata veya yanlışlık içerebileceğini lütfen unutmayın. Belgenin orijinal dili, yetkili kaynak olarak kabul edilmelidir. Kritik bilgiler için profesyonel insan çevirisi önerilir. Bu çevirinin kullanımından kaynaklanan yanlış anlamalar veya yanlış yorumlamalardan sorumlu değiliz.