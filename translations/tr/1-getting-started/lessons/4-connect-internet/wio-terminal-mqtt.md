<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "d6faf0e8d3c2d6d20c0aef2a305dab18",
  "translation_date": "2025-08-28T03:31:34+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/wio-terminal-mqtt.md",
  "language_code": "tr"
}
-->
# Wio Terminal ile Gece Lambanızı İnternet Üzerinden Kontrol Edin

IoT cihazı, ışık sensörü okumasıyla telemetri değerlerini göndermek ve LED'i kontrol etmek için komutlar almak üzere MQTT kullanarak *test.mosquitto.org* ile iletişim kuracak şekilde kodlanmalıdır.

Bu dersin bu bölümünde, Wio Terminal'inizi bir MQTT brokerine bağlayacaksınız.

## WiFi ve MQTT Arduino Kütüphanelerini Kurun

MQTT brokeri ile iletişim kurmak için, Wio Terminal'deki WiFi çipini kullanmak ve MQTT ile iletişim kurmak için bazı Arduino kütüphanelerini yüklemeniz gerekiyor. Arduino cihazları için geliştirme yaparken, açık kaynak kodu içeren ve çok çeşitli yetenekleri uygulayan geniş bir kütüphane yelpazesi kullanabilirsiniz. Seeed, Wio Terminal'in WiFi üzerinden iletişim kurmasını sağlayan kütüphaneler yayınlar. Diğer geliştiriciler ise MQTT brokerleriyle iletişim kurmak için kütüphaneler yayınlamışlardır ve bu kütüphaneleri cihazınızla kullanacaksınız.

Bu kütüphaneler, PlatformIO'ya otomatik olarak aktarılabilen ve cihazınız için derlenebilen kaynak kod olarak sağlanır. Bu şekilde Arduino kütüphaneleri, Arduino çerçevesini destekleyen herhangi bir cihazda çalışır, tabii ki kütüphanenin gerektirdiği özel donanım cihazda mevcutsa. Bazı kütüphaneler, örneğin Seeed WiFi kütüphaneleri, belirli donanımlara özeldir.

Kütüphaneler global olarak yüklenebilir ve gerekirse derlenebilir veya belirli bir projeye dahil edilebilir. Bu ödevde, kütüphaneler projeye yüklenecektir.

✅ Kütüphane yönetimi hakkında daha fazla bilgi edinmek ve kütüphaneleri nasıl bulup yükleyeceğinizi öğrenmek için [PlatformIO kütüphane dokümantasyonu](https://docs.platformio.org/en/latest/librarymanager/index.html) adresine göz atabilirsiniz.

### Görev - WiFi ve MQTT Arduino kütüphanelerini yükleyin

Arduino kütüphanelerini yükleyin.

1. VS Code'da gece lambası projesini açın.

1. `platformio.ini` dosyasının sonuna aşağıdakileri ekleyin:

    ```ini
    lib_deps =
        seeed-studio/Seeed Arduino rpcWiFi @ 1.0.5
        seeed-studio/Seeed Arduino FS @ 2.1.1
        seeed-studio/Seeed Arduino SFUD @ 2.0.2
        seeed-studio/Seeed Arduino rpcUnified @ 2.1.3
        seeed-studio/Seeed_Arduino_mbedtls @ 3.0.1
    ```

    Bu, Seeed WiFi kütüphanelerini içe aktarır. `@ <number>` sözdizimi, kütüphanenin belirli bir sürüm numarasına atıfta bulunur.

    > 💁 `@ <number>` kısmını kaldırarak her zaman kütüphanelerin en son sürümünü kullanabilirsiniz, ancak daha sonraki sürümlerin aşağıdaki kodla çalışacağına dair bir garanti yoktur. Buradaki kod, kütüphanelerin bu sürümüyle test edilmiştir.

    Kütüphaneleri eklemek için yapmanız gereken tek şey budur. PlatformIO projeyi bir sonraki derlediğinde, bu kütüphanelerin kaynak kodunu indirir ve projenize dahil eder.

1. `lib_deps` kısmına aşağıdakileri ekleyin:

    ```ini
    knolleary/PubSubClient @ 2.8
    ```

    Bu, [PubSubClient](https://github.com/knolleary/pubsubclient) adlı bir Arduino MQTT istemcisini içe aktarır.

## WiFi'ye Bağlanın

Artık Wio Terminal WiFi'ye bağlanabilir.

### Görev - WiFi'ye bağlanın

Wio Terminal'i WiFi'ye bağlayın.

1. `src` klasöründe `config.h` adlı yeni bir dosya oluşturun. Bunu, `src` klasörünü veya içindeki `main.cpp` dosyasını seçerek ve gezgin üzerinde beliren **Yeni dosya** düğmesini seçerek yapabilirsiniz. Bu düğme yalnızca imleciniz gezgin üzerindeyken görünür.

    ![Yeni dosya düğmesi](../../../../../translated_images/tr/vscode-new-file-button.182702340fe6723c.png)

1. WiFi kimlik bilgilerinizi tanımlamak için bu dosyaya aşağıdaki kodu ekleyin:

    ```cpp
    #pragma once

    #include <string>
    
    using namespace std;
    
    // WiFi credentials
    const char *SSID = "<SSID>";
    const char *PASSWORD = "<PASSWORD>";
    ```

    `<SSID>` kısmını WiFi'nizin SSID'si ile değiştirin. `<PASSWORD>` kısmını WiFi şifrenizle değiştirin.

1. `main.cpp` dosyasını açın.

1. Dosyanın en üstüne aşağıdaki `#include` yönergelerini ekleyin:

    ```cpp
    #include <PubSubClient.h>
    #include <rpcWiFi.h>
    #include <SPI.h>
    
    #include "config.h"
    ```

    Bu, daha önce eklediğiniz kütüphanelerin başlık dosyalarını ve yapılandırma başlık dosyasını içerir. Bu başlık dosyaları, PlatformIO'ya kütüphanelerden kod getirmesi gerektiğini söylemek için gereklidir. Bu başlık dosyalarını açıkça dahil etmezseniz, bazı kodlar derlenmez ve derleyici hataları alırsınız.

1. `setup` fonksiyonunun üstüne aşağıdaki kodu ekleyin:

    ```cpp
    void connectWiFi()
    {
        while (WiFi.status() != WL_CONNECTED)
        {
            Serial.println("Connecting to WiFi..");
            WiFi.begin(SSID, PASSWORD);
            delay(500);
        }
    
        Serial.println("Connected!");
    }
    ```

    Bu kod, cihaz WiFi'ye bağlı değilken döngüye girer ve yapılandırma başlık dosyasındaki SSID ve şifreyi kullanarak bağlanmayı dener.

1. Bu fonksiyonu `setup` fonksiyonunun altına, pinler yapılandırıldıktan sonra çağırın.

    ```cpp
    connectWiFi();
    ```

1. Bu kodu cihazınıza yükleyin ve WiFi bağlantısının çalıştığını kontrol edin. Seri monitörde bunu görmelisiniz.

    ```output
    > Executing task: platformio device monitor <
    
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1101  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Connecting to WiFi..
    Connected!
    ```

## MQTT'ye Bağlanın

Wio Terminal WiFi'ye bağlandıktan sonra MQTT brokerine bağlanabilir.

### Görev - MQTT'ye bağlanın

MQTT brokerine bağlanın.

1. MQTT brokeri için bağlantı ayrıntılarını tanımlamak üzere `config.h` dosyasının sonuna aşağıdaki kodu ekleyin:

    ```cpp
    // MQTT settings
    const string ID = "<ID>";
    
    const string BROKER = "test.mosquitto.org";
    const string CLIENT_NAME = ID + "nightlight_client";
    ```

    `<ID>` kısmını bu cihaz istemcisi için kullanılacak benzersiz bir kimlik ile değiştirin ve bu kimlik daha sonra bu cihazın yayınladığı ve abone olduğu konular için kullanılacaktır. *test.mosquitto.org* brokeri herkese açık ve birçok kişi tarafından, bu ödevi yapan diğer öğrenciler dahil, kullanılmaktadır. Benzersiz bir MQTT istemci adı ve konu adlarına sahip olmak, kodunuzun başkalarınınkiyle çakışmamasını sağlar. Bu kimliği, bu ödevin ilerleyen bölümlerinde sunucu kodunu oluştururken de kullanmanız gerekecek.

    > 💁 Benzersiz bir kimlik oluşturmak için [GUIDGen](https://www.guidgen.com) gibi bir web sitesi kullanabilirsiniz.

    `BROKER`, MQTT brokerinin URL'sidir.

    `CLIENT_NAME`, bu MQTT istemcisi için brokerdeki benzersiz bir isimdir.

1. `main.cpp` dosyasını açın ve `connectWiFi` fonksiyonunun altına, `setup` fonksiyonunun üstüne aşağıdaki kodu ekleyin:

    ```cpp
    WiFiClient wioClient;
    PubSubClient client(wioClient);
    ```

    Bu kod, Wio Terminal WiFi kütüphanelerini kullanarak bir WiFi istemcisi oluşturur ve bunu kullanarak bir MQTT istemcisi oluşturur.

1. Bu kodun altına aşağıdakileri ekleyin:

    ```cpp
    void reconnectMQTTClient()
    {
        while (!client.connected())
        {
            Serial.print("Attempting MQTT connection...");
    
            if (client.connect(CLIENT_NAME.c_str()))
            {
                Serial.println("connected");
            }
            else
            {
                Serial.print("Retying in 5 seconds - failed, rc=");
                Serial.println(client.state());
                
                delay(5000);
            }
        }
    }
    ```

    Bu fonksiyon, MQTT brokerine bağlantıyı test eder ve bağlantı yoksa yeniden bağlanır. Bağlı olmadığı sürece döngüye girer ve yapılandırma başlık dosyasındaki benzersiz istemci adını kullanarak bağlanmayı dener.

    Bağlantı başarısız olursa, 5 saniye sonra yeniden dener.

1. `reconnectMQTTClient` fonksiyonunun altına aşağıdaki kodu ekleyin:

    ```cpp
    void createMQTTClient()
    {
        client.setServer(BROKER.c_str(), 1883);
        reconnectMQTTClient();
    }
    ```

    Bu kod, istemci için MQTT brokerini ayarlar ve bir mesaj alındığında geri çağırmayı yapılandırır. Daha sonra broker ile bağlantı kurmayı dener.

1. `setup` fonksiyonunda WiFi bağlandıktan sonra `createMQTTClient` fonksiyonunu çağırın.

1. Tüm `loop` fonksiyonunu aşağıdaki kodla değiştirin:

    ```cpp
    void loop()
    {
        reconnectMQTTClient();
        client.loop();
    
        delay(2000);
    }
    ```

    Bu kod, MQTT brokerine yeniden bağlanarak başlar. Bu bağlantılar kolayca kesilebilir, bu yüzden düzenli olarak kontrol etmek ve gerekirse yeniden bağlanmak önemlidir. Daha sonra, abone olunan konudaki gelen mesajları işlemek için MQTT istemcisinin `loop` metodunu çağırır. Bu uygulama tek iş parçacıklı olduğundan, mesajlar arka planda bir iş parçacığında alınamaz, bu nedenle ağ bağlantısında bekleyen mesajları işlemek için ana iş parçacığında zaman ayrılması gerekir.

    Son olarak, 2 saniyelik bir gecikme, ışık seviyelerinin çok sık gönderilmesini önler ve cihazın güç tüketimini azaltır.

1. Kodunuzu Wio Terminal'e yükleyin ve cihazın WiFi ve MQTT'ye bağlandığını görmek için Seri Monitör'ü kullanın.

    ```output
    > Executing task: platformio device monitor <
    
    source /Users/jimbennett/GitHub/IoT-For-Beginners/1-getting-started/lessons/4-connect-internet/code-mqtt/wio-terminal/nightlight/.venv/bin/activate
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1201  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Connecting to WiFi..
    Connected!
    Attempting MQTT connection...connected
    ```

> 💁 Bu kodu [code-mqtt/wio-terminal](../../../../../1-getting-started/lessons/4-connect-internet/code-mqtt/wio-terminal) klasöründe bulabilirsiniz.

😀 Cihazınızı başarıyla bir MQTT brokerine bağladınız.

---

**Feragatname**:  
Bu belge, AI çeviri hizmeti [Co-op Translator](https://github.com/Azure/co-op-translator) kullanılarak çevrilmiştir. Doğruluk için çaba göstersek de, otomatik çevirilerin hata veya yanlışlık içerebileceğini lütfen unutmayın. Belgenin orijinal dili, yetkili kaynak olarak kabul edilmelidir. Kritik bilgiler için profesyonel insan çevirisi önerilir. Bu çevirinin kullanımından kaynaklanan yanlış anlamalar veya yanlış yorumlamalar için sorumluluk kabul edilmez.