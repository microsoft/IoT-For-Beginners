<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "3ac42e284a7222c0e83d2d43231a364f",
  "translation_date": "2025-08-28T04:08:00+00:00",
  "source_file": "2-farm/lessons/4-migrate-your-plant-to-the-cloud/single-board-computer-connect-hub.md",
  "language_code": "tr"
}
-->
# IoT Cihazınızı Buluta Bağlayın - Sanal IoT Donanımı ve Raspberry Pi

Bu dersin bu bölümünde, sanal IoT cihazınızı veya Raspberry Pi'nizi IoT Hub'a bağlayarak telemetri gönderecek ve komutlar alacaksınız.

## Cihazınızı IoT Hub'a Bağlayın

Bir sonraki adım, cihazınızı IoT Hub'a bağlamaktır.

### Görev - IoT Hub'a bağlanın

1. VS Code'da `soil-moisture-sensor` klasörünü açın. Sanal bir IoT cihazı kullanıyorsanız, terminalde sanal ortamın çalıştığından emin olun.

1. Bazı ek Pip paketlerini yükleyin:

    ```sh
    pip3 install azure-iot-device
    ```

    `azure-iot-device`, IoT Hub ile iletişim kurmak için bir kütüphanedir.

1. Aşağıdaki importları, `app.py` dosyasının en üstüne, mevcut importların altına ekleyin:

    ```python
    from azure.iot.device import IoTHubDeviceClient, Message, MethodResponse
    ```

    Bu kod, IoT Hub ile iletişim kurmak için SDK'yı içe aktarır.

1. `import paho.mqtt.client as mqtt` satırını kaldırın çünkü bu kütüphane artık gerekli değil. MQTT kodunun tamamını, konu adları dahil, `mqtt_client` ve `handle_command` kullanan tüm kodları kaldırın. `while True:` döngüsünü koruyun, sadece bu döngüdeki `mqtt_client.publish` satırını silin.

1. Import ifadelerinin altına aşağıdaki kodu ekleyin:

    ```python
    connection_string = "<connection string>"
    ```

    `<connection string>` ifadesini, bu derste daha önce cihaz için aldığınız bağlantı dizesiyle değiştirin.

    > 💁 Bu en iyi uygulama değildir. Bağlantı dizeleri asla kaynak kodda saklanmamalıdır, çünkü bu, kaynak kod kontrolüne dahil edilip herkes tarafından bulunabilir. Burada basitlik adına bunu yapıyoruz. İdeal olarak, bir ortam değişkeni ve [`python-dotenv`](https://pypi.org/project/python-dotenv/) gibi bir araç kullanmalısınız. Bunu ilerleyen bir derste daha ayrıntılı öğreneceksiniz.

1. Bu kodun altına, IoT Hub ile iletişim kurabilecek bir cihaz istemcisi nesnesi oluşturmak ve bağlanmak için aşağıdaki kodu ekleyin:

    ```python
    device_client = IoTHubDeviceClient.create_from_connection_string(connection_string)

    print('Connecting')
    device_client.connect()
    print('Connected')
    ```

1. Bu kodu çalıştırın. Cihazınızın bağlandığını göreceksiniz.

    ```output
    pi@raspberrypi:~/soil-moisture-sensor $ python3 app.py 
    Connecting
    Connected
    Soil moisture: 379
    ```

## Telemetri Gönderin

Artık cihazınız bağlı olduğuna göre, MQTT broker yerine IoT Hub'a telemetri gönderebilirsiniz.

### Görev - telemetri gönderin

1. `while True` döngüsünün içine, uyuma işleminden hemen önce aşağıdaki kodu ekleyin:

    ```python
    message = Message(json.dumps({ 'soil_moisture': soil_moisture }))
    device_client.send_message(message)
    ```

    Bu kod, toprak nemi ölçümünü bir JSON dizesi olarak içeren bir IoT Hub `Message` oluşturur ve bunu cihazdan buluta bir mesaj olarak IoT Hub'a gönderir.

## Komutları İşleyin

Cihazınızın, röleyi kontrol etmek için sunucu kodundan bir komut alması gerekir. Bu, doğrudan bir yöntem isteği olarak gönderilir.

## Görev - doğrudan bir yöntem isteğini işleyin

1. `while True` döngüsünden önce aşağıdaki kodu ekleyin:

    ```python
    def handle_method_request(request):
        print("Direct method received - ", request.name)
    
        if request.name == "relay_on":
            relay.on()
        elif request.name == "relay_off":
            relay.off()    
    ```

    Bu, IoT Hub tarafından bir doğrudan yöntem çağrıldığında çağrılacak bir `handle_method_request` yöntemi tanımlar. Her doğrudan yöntemin bir adı vardır ve bu kod, röleyi açmak için `relay_on` ve kapatmak için `relay_off` adlı bir yöntem bekler.

    > 💁 Bu, tek bir doğrudan yöntem isteği içinde de uygulanabilir. Rölenin istenen durumunu, yöntem isteğiyle birlikte gönderilebilen ve `request` nesnesinden erişilebilen bir yük olarak geçirebilirsiniz.

1. Doğrudan yöntemler, çağıran koda işlendiklerini bildirmek için bir yanıt gerektirir. `handle_method_request` fonksiyonunun sonuna, isteğe yanıt oluşturmak için aşağıdaki kodu ekleyin:

    ```python
    method_response = MethodResponse.create_from_method_request(request, 200)
    device_client.send_method_response(method_response)
    ```

    Bu kod, doğrudan yöntem isteğine bir HTTP durum kodu 200 ile yanıt gönderir ve bunu IoT Hub'a geri gönderir.

1. Bu fonksiyon tanımının altına aşağıdaki kodu ekleyin:

    ```python
    device_client.on_method_request_received = handle_method_request
    ```

    Bu kod, bir doğrudan yöntem çağrıldığında IoT Hub istemcisinin `handle_method_request` fonksiyonunu çağırmasını söyler.

> 💁 Bu kodu [code/pi](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud/code/pi) veya [code/virtual-device](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud/code/virtual-device) klasöründe bulabilirsiniz.

😀 Toprak nem sensörü programınız IoT Hub'a bağlandı!

---

**Feragatname**:  
Bu belge, AI çeviri hizmeti [Co-op Translator](https://github.com/Azure/co-op-translator) kullanılarak çevrilmiştir. Doğruluk için çaba göstersek de, otomatik çevirilerin hata veya yanlışlık içerebileceğini lütfen unutmayın. Belgenin orijinal dili, yetkili kaynak olarak kabul edilmelidir. Kritik bilgiler için profesyonel insan çevirisi önerilir. Bu çevirinin kullanımından kaynaklanan yanlış anlamalar veya yanlış yorumlamalardan sorumlu değiliz.