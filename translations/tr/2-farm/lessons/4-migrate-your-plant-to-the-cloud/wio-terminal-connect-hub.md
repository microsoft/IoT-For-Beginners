<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "28320305a35ea3bc59c41fe146a2e6ed",
  "translation_date": "2025-08-28T04:08:54+00:00",
  "source_file": "2-farm/lessons/4-migrate-your-plant-to-the-cloud/wio-terminal-connect-hub.md",
  "language_code": "tr"
}
-->
# IoT Cihazınızı Buluta Bağlayın - Wio Terminal

Bu dersin bu bölümünde, Wio Terminal cihazınızı IoT Hub'a bağlayarak telemetri gönderecek ve komutlar alacaksınız.

## Cihazınızı IoT Hub'a Bağlayın

Bir sonraki adım, cihazınızı IoT Hub'a bağlamaktır.

### Görev - IoT Hub'a bağlanın

1. VS Code'da `soil-moisture-sensor` projesini açın.

1. `platformio.ini` dosyasını açın. `knolleary/PubSubClient` kütüphane bağımlılığını kaldırın. Bu, genel bir MQTT broker'a bağlanmak için kullanılıyordu ve IoT Hub'a bağlanmak için gerekli değildir.

1. Aşağıdaki kütüphane bağımlılıklarını ekleyin:

    ```ini
    seeed-studio/Seeed Arduino RTC @ 2.0.0
    arduino-libraries/AzureIoTHub @ 1.6.0
    azure/AzureIoTUtility @ 1.6.1
    azure/AzureIoTProtocol_MQTT @ 1.6.0
    azure/AzureIoTProtocol_HTTP @ 1.6.0
    azure/AzureIoTSocket_WiFi @ 1.0.2
    ```

    `Seeed Arduino RTC` kütüphanesi, Wio Terminal'deki gerçek zamanlı saatle etkileşim kurmak için kod sağlar ve zamanı takip etmek için kullanılır. Diğer kütüphaneler, IoT cihazınızın IoT Hub'a bağlanmasını sağlar.

1. `platformio.ini` dosyasının sonuna aşağıdakileri ekleyin:

    ```ini
    build_flags =
        -DDONT_USE_UPLOADTOBLOB
    ```

    Bu, Arduino IoT Hub kodunu derlerken gerekli olan bir derleyici bayrağını ayarlar.

1. `config.h` başlık dosyasını açın. Tüm MQTT ayarlarını kaldırın ve cihaz bağlantı dizesi için aşağıdaki sabiti ekleyin:

    ```cpp
    // IoT Hub settings
    const char *CONNECTION_STRING = "<connection string>";
    ```

    `<connection string>` kısmını daha önce kopyaladığınız cihaz bağlantı dizesiyle değiştirin.

1. IoT Hub bağlantısı zaman tabanlı bir token kullanır. Bu, IoT cihazının mevcut zamanı bilmesi gerektiği anlamına gelir. Windows, macOS veya Linux gibi işletim sistemlerinin aksine, mikrodenetleyiciler mevcut zamanı otomatik olarak İnternet üzerinden senkronize etmez. Bu, mevcut zamanı bir [NTP](https://wikipedia.org/wiki/Network_Time_Protocol) sunucusundan alacak kod eklemeniz gerektiği anlamına gelir. Zaman alındıktan sonra, cihazın güç kaybetmediği sürece daha sonraki bir tarihte doğru zamanın istenmesine olanak tanıyan Wio Terminal'deki gerçek zamanlı saate kaydedilebilir. `ntp.h` adında yeni bir dosya oluşturun ve aşağıdaki kodu ekleyin:

    ```cpp
    #pragma once
    
    #include "DateTime.h"
    #include <time.h>
    #include "samd/NTPClientAz.h"
    #include <sys/time.h>

    static void initTime()
    {
        WiFiUDP _udp;
        time_t epochTime = (time_t)-1;
        NTPClientAz ntpClient;

        ntpClient.begin();

        while (true)
        {
            epochTime = ntpClient.getEpochTime("0.pool.ntp.org");

            if (epochTime == (time_t)-1)
            {
                Serial.println("Fetching NTP epoch time failed! Waiting 2 seconds to retry.");
                delay(2000);
            }
            else
            {
                Serial.print("Fetched NTP epoch time is: ");

                char buff[32];
                sprintf(buff, "%.f", difftime(epochTime, (time_t)0));
                Serial.println(buff);
                break;
            }
        }

        ntpClient.end();

        struct timeval tv;
        tv.tv_sec = epochTime;
        tv.tv_usec = 0;

        settimeofday(&tv, NULL);
    }
    ```

    Bu kodun detayları bu dersin kapsamı dışındadır. Bu, bir NTP sunucusundan mevcut zamanı alıp Wio Terminal'deki saati ayarlayan `initTime` adlı bir fonksiyon tanımlar.

1. `main.cpp` dosyasını açın ve tüm MQTT kodlarını kaldırın. Buna `PubSubClient.h` başlık dosyası, `PubSubClient` değişkeninin bildirimi, `reconnectMQTTClient` ve `createMQTTClient` yöntemleri ve bu değişkenlere ve yöntemlere yapılan tüm çağrılar dahildir. Bu dosya yalnızca WiFi'ye bağlanmak, toprak nemini almak ve bununla bir JSON belgesi oluşturmak için kod içermelidir.

1. IoT Hub kütüphanelerini ve zamanı ayarlamak için başlık dosyalarını dahil etmek üzere `main.cpp` dosyasının üstüne aşağıdaki `#include` yönergelerini ekleyin:

    ```cpp
    #include <AzureIoTHub.h>
    #include <AzureIoTProtocol_MQTT.h>
    #include <iothubtransportmqtt.h>
    #include "ntp.h"
    ```

1. Mevcut zamanı ayarlamak için `setup` fonksiyonunun sonuna aşağıdaki çağrıyı ekleyin:

    ```cpp
    initTime();
    ```

1. Dosyanın üst kısmına, include yönergelerinin hemen altına aşağıdaki değişken bildirimini ekleyin:

    ```cpp
    IOTHUB_DEVICE_CLIENT_LL_HANDLE _device_ll_handle;
    ```

    Bu, IoT Hub'a bir bağlantı için bir `IOTHUB_DEVICE_CLIENT_LL_HANDLE` tanımlar.

1. Bunun altına aşağıdaki kodu ekleyin:

    ```cpp
    static void connectionStatusCallback(IOTHUB_CLIENT_CONNECTION_STATUS result, IOTHUB_CLIENT_CONNECTION_STATUS_REASON reason, void *user_context)
    {
        if (result == IOTHUB_CLIENT_CONNECTION_AUTHENTICATED)
        {
            Serial.println("The device client is connected to iothub");
        }
        else
        {
            Serial.println("The device client has been disconnected");
        }
    }
    ```

    Bu, IoT Hub'a bağlantı durumu değiştiğinde (örneğin bağlanma veya bağlantının kesilmesi gibi) çağrılacak bir geri çağırma fonksiyonu tanımlar. Durum seri porta gönderilir.

1. Bunun altına IoT Hub'a bağlanmak için bir fonksiyon ekleyin:

    ```cpp
    void connectIoTHub()
    {
        IoTHub_Init();
    
        _device_ll_handle = IoTHubDeviceClient_LL_CreateFromConnectionString(CONNECTION_STRING, MQTT_Protocol);
        
        if (_device_ll_handle == NULL)
        {
            Serial.println("Failure creating Iothub device. Hint: Check your connection string.");
            return;
        }
    
        IoTHubDeviceClient_LL_SetConnectionStatusCallback(_device_ll_handle, connectionStatusCallback, NULL);
    }
    ```

    Bu kod, IoT Hub kütüphane kodunu başlatır ve ardından `config.h` başlık dosyasındaki bağlantı dizesini kullanarak bir bağlantı oluşturur. Bu bağlantı MQTT tabanlıdır. Bağlantı başarısız olursa, bu seri porta gönderilir - eğer çıktıda bunu görürseniz, bağlantı dizesini kontrol edin. Son olarak, bağlantı durumu geri çağırması ayarlanır.

1. Bu fonksiyonu `setup` fonksiyonunda `initTime` çağrısının altına çağırın:

    ```cpp
    connectIoTHub();
    ```

1. MQTT istemcisinde olduğu gibi, bu kod tek bir iş parçacığında çalışır, bu nedenle hub tarafından gönderilen ve hub'a gönderilen mesajları işlemek için zamana ihtiyaç duyar. Bunu yapmak için, `loop` fonksiyonunun üstüne aşağıdakileri ekleyin:

    ```cpp
    IoTHubDeviceClient_LL_DoWork(_device_ll_handle);
    ```

1. Bu kodu derleyip yükleyin. Seri monitörde bağlantıyı göreceksiniz:

    ```output
    Connecting to WiFi..
    Connected!
    Fetched NTP epoch time is: 1619983687
    Sending telemetry {"soil_moisture":391}
    The device client is connected to iothub
    ```

    Çıktıda, NTP zamanının alındığını ve ardından cihaz istemcisinin bağlandığını görebilirsiniz. Bağlanması birkaç saniye sürebilir, bu nedenle cihaz bağlanırken çıktıda toprak nemini görebilirsiniz.

    > 💁 NTP için UNIX zamanını daha okunabilir bir sürüme dönüştürmek için [unixtimestamp.com](https://www.unixtimestamp.com) gibi bir web sitesi kullanabilirsiniz.

## Telemetri Gönderin

Artık cihazınız bağlı olduğuna göre, telemetriyi MQTT broker yerine IoT Hub'a gönderebilirsiniz.

### Görev - telemetri gönderin

1. `setup` fonksiyonunun üstüne aşağıdaki fonksiyonu ekleyin:

    ```cpp
    void sendTelemetry(const char *telemetry)
    {
        IOTHUB_MESSAGE_HANDLE message_handle = IoTHubMessage_CreateFromString(telemetry);
        IoTHubDeviceClient_LL_SendEventAsync(_device_ll_handle, message_handle, NULL, NULL);
        IoTHubMessage_Destroy(message_handle);
    }
    ```

    Bu kod, bir parametre olarak geçirilen bir string'den bir IoT Hub mesajı oluşturur, bunu hub'a gönderir ve ardından mesaj nesnesini temizler.

1. Bu kodu `loop` fonksiyonunda, telemetri seri porta gönderildikten hemen sonra çağırın:

    ```cpp
    sendTelemetry(telemetry.c_str());
    ```

## Komutları İşleyin

Cihazınızın, röleyi kontrol etmek için sunucu kodundan gelen bir komutu işlemesi gerekir. Bu, doğrudan bir yöntem isteği olarak gönderilir.

### Görev - doğrudan bir yöntem isteğini işleyin

1. `connectIoTHub` fonksiyonunun öncesine aşağıdaki kodu ekleyin:

    ```cpp
    int directMethodCallback(const char *method_name, const unsigned char *payload, size_t size, unsigned char **response, size_t *response_size, void *userContextCallback)
    {
        Serial.printf("Direct method received %s\r\n", method_name);
    
        if (strcmp(method_name, "relay_on") == 0)
        {
            digitalWrite(PIN_WIRE_SCL, HIGH);
        }
        else if (strcmp(method_name, "relay_off") == 0)
        {
            digitalWrite(PIN_WIRE_SCL, LOW);
        }
    }
    ```

    Bu kod, IoT Hub kütüphanesinin doğrudan bir yöntem isteği aldığında çağırabileceği bir geri çağırma yöntemi tanımlar. İstenen yöntem `method_name` parametresinde gönderilir. Bu fonksiyon, çağrılan yöntemi seri porta yazdırır ve yöntem adına bağlı olarak röleyi açar veya kapatır.

    > 💁 Bu, yöntemin istenen durumunu bir yük olarak geçirerek ve bu yükü `payload` parametresinden alarak tek bir doğrudan yöntem isteği olarak da uygulanabilir.

1. `directMethodCallback` fonksiyonunun sonuna aşağıdaki kodu ekleyin:

    ```cpp
    char resultBuff[16];
    sprintf(resultBuff, "{\"Result\":\"\"}");
    *response_size = strlen(resultBuff);
    *response = (unsigned char *)malloc(*response_size);
    memcpy(*response, resultBuff, *response_size);

    return IOTHUB_CLIENT_OK;
    ```

    Doğrudan yöntem isteklerinin bir yanıtı olması gerekir ve yanıt iki bölümden oluşur - metin olarak bir yanıt ve bir dönüş kodu. Bu kod, aşağıdaki JSON belgesi olarak bir sonuç oluşturur:

    ```JSON
    {
        "Result": ""
    }
    ```

    Bu daha sonra `response` parametresine kopyalanır ve bu yanıtın boyutu `response_size` parametresinde ayarlanır. Bu kod daha sonra yöntemin doğru bir şekilde işlendiğini göstermek için `IOTHUB_CLIENT_OK` döndürür.

1. Geri çağırmayı bağlamak için `connectIoTHub` fonksiyonunun sonuna aşağıdakileri ekleyin:

    ```cpp
    IoTHubClient_LL_SetDeviceMethodCallback(_device_ll_handle, directMethodCallback, NULL);
    ```

1. `loop` fonksiyonu, IoT Hub tarafından gönderilen olayları işlemek için `IoTHubDeviceClient_LL_DoWork` fonksiyonunu çağıracaktır. Bu, yalnızca `delay` nedeniyle her 10 saniyede bir çağrılır, bu da doğrudan yöntemlerin yalnızca her 10 saniyede bir işlenmesi anlamına gelir. Bunu daha verimli hale getirmek için, 10 saniyelik gecikme, her seferinde `IoTHubDeviceClient_LL_DoWork` fonksiyonunu çağırarak birçok kısa gecikme olarak uygulanabilir. Bunu yapmak için, `loop` fonksiyonunun üstüne aşağıdaki kodu ekleyin:

    ```cpp
    void work_delay(int delay_time)
    {
        int current = 0;
        do
        {
            IoTHubDeviceClient_LL_DoWork(_device_ll_handle);
            delay(100);
            current += 100;
        } while (current < delay_time);
    }
    ```

    Bu kod, `delay_time` parametresinde verilen süre boyunca beklemek için gereken kadar kez `IoTHubDeviceClient_LL_DoWork` fonksiyonunu çağırarak ve her seferinde 100ms gecikerek tekrar tekrar döngü yapar. Bu, cihazın doğrudan yöntem isteklerini işlemek için en fazla 100ms beklediği anlamına gelir.

1. `loop` fonksiyonunda, `IoTHubDeviceClient_LL_DoWork` çağrısını kaldırın ve `delay(10000)` çağrısını aşağıdaki kodla değiştirin:

    ```cpp
    work_delay(10000);
    ```

> 💁 Bu kodu [code/wio-terminal](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud/code/wio-terminal) klasöründe bulabilirsiniz.

😀 Toprak nem sensörü programınız IoT Hub'a bağlandı!

---

**Feragatname**:  
Bu belge, AI çeviri hizmeti [Co-op Translator](https://github.com/Azure/co-op-translator) kullanılarak çevrilmiştir. Doğruluğu sağlamak için çaba göstersek de, otomatik çevirilerin hata veya yanlışlık içerebileceğini lütfen unutmayın. Belgenin orijinal dili, yetkili kaynak olarak kabul edilmelidir. Kritik bilgiler için profesyonel insan çevirisi önerilir. Bu çevirinin kullanımından kaynaklanan yanlış anlamalar veya yanlış yorumlamalar için sorumluluk kabul etmiyoruz.