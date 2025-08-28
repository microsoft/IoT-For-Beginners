<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "9aea84bcc7520222b0e1c50469d62d6a",
  "translation_date": "2025-08-28T04:03:58+00:00",
  "source_file": "2-farm/lessons/6-keep-your-plant-secure/single-board-computer-x509.md",
  "language_code": "tr"
}
-->
# X.509 Sertifikasını Cihaz Kodunuzda Kullanma - Sanal IoT Donanımı ve Raspberry Pi

Bu dersin bu bölümünde, sanal IoT cihazınızı veya Raspberry Pi'nizi X.509 sertifikası kullanarak IoT Hub'a bağlayacaksınız.

## Cihazınızı IoT Hub'a Bağlayın

Bir sonraki adım, cihazınızı X.509 sertifikaları kullanarak IoT Hub'a bağlamaktır.

### Görev - IoT Hub'a bağlanma

1. Anahtar ve sertifika dosyalarını IoT cihaz kodunuzun bulunduğu klasöre kopyalayın. Raspberry Pi'yi VS Code Remote SSH üzerinden kullanıyorsanız ve anahtarları PC veya Mac'inizde oluşturduysanız, dosyaları VS Code'daki gezgin bölümüne sürükleyip bırakarak kopyalayabilirsiniz.

1. `app.py` dosyasını açın.

1. X.509 sertifikası kullanarak bağlanmak için IoT Hub'ın ana bilgisayar adını ve X.509 sertifikasını kullanmanız gerekecek. Cihaz istemcisi oluşturulmadan önce aşağıdaki kodu ekleyerek ana bilgisayar adını içeren bir değişken oluşturun:

    ```python
    host_name = "<host_name>"
    ```

    `<host_name>` kısmını IoT Hub'ınızın ana bilgisayar adıyla değiştirin. Bunu `connection_string` içindeki `HostName` bölümünden alabilirsiniz. Bu, IoT Hub'ınızın adı olacak ve `.azure-devices.net` ile bitecektir.

1. Bunun altına cihaz kimliği içeren bir değişken tanımlayın:

    ```python
    device_id = "soil-moisture-sensor-x509"
    ```

1. X.509 dosyalarını içeren bir `X509` sınıfı örneğine ihtiyacınız olacak. `azure.iot.device` modülünden içe aktarılan sınıflar listesine `X509` ekleyin:

    ```python
    from azure.iot.device import IoTHubDeviceClient, Message, MethodResponse, X509
    ```

1. Sertifika ve anahtar dosyalarınızı kullanarak bir `X509` sınıfı örneği oluşturun. Bunun için aşağıdaki kodu `host_name` tanımının altına ekleyin:

    ```python
    x509 = X509("./soil-moisture-sensor-x509-cert.pem", "./soil-moisture-sensor-x509-key.pem")
    ```

    Bu, daha önce oluşturulan `soil-moisture-sensor-x509-cert.pem` ve `soil-moisture-sensor-x509-key.pem` dosyalarını kullanarak `X509` sınıfını oluşturacaktır.

1. Bağlantı dizesinden `device_client` oluşturan kod satırını aşağıdaki kodla değiştirin:

    ```python
    device_client = IoTHubDeviceClient.create_from_x509_certificate(x509, host_name, device_id)
    ```

    Bu, bağlantı dizesi yerine X.509 sertifikası kullanarak bağlanacaktır.

1. `connection_string` değişkenini içeren satırı silin.

1. Kodunuzu çalıştırın. IoT Hub'a gönderilen mesajları izleyin ve daha önce olduğu gibi doğrudan yöntem istekleri gönderin. Cihazın bağlandığını, toprak nemi ölçümlerini gönderdiğini ve doğrudan yöntem isteklerini aldığını göreceksiniz.

> 💁 Bu kodu [code/pi](../../../../../2-farm/lessons/6-keep-your-plant-secure/code/pi) veya [code/virtual-device](../../../../../2-farm/lessons/6-keep-your-plant-secure/code/virtual-device) klasöründe bulabilirsiniz.

😀 Toprak nemi sensörü programınız X.509 sertifikası kullanarak IoT Hub'a bağlandı!

---

**Feragatname**:  
Bu belge, AI çeviri hizmeti [Co-op Translator](https://github.com/Azure/co-op-translator) kullanılarak çevrilmiştir. Doğruluk için çaba göstersek de, otomatik çevirilerin hata veya yanlışlık içerebileceğini lütfen unutmayın. Belgenin orijinal dili, yetkili kaynak olarak kabul edilmelidir. Kritik bilgiler için profesyonel insan çevirisi önerilir. Bu çevirinin kullanımından kaynaklanan yanlış anlamalar veya yanlış yorumlamalardan sorumlu değiliz.