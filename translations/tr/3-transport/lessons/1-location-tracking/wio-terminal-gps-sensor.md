<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "da6ae0a795cf06be33d23ca5b8493fc8",
  "translation_date": "2025-08-28T03:15:08+00:00",
  "source_file": "3-transport/lessons/1-location-tracking/wio-terminal-gps-sensor.md",
  "language_code": "tr"
}
-->
# GPS Verilerini Okuma - Wio Terminal

Bu dersin bu bölümünde, Wio Terminal'inize bir GPS sensörü ekleyecek ve ondan değerler okuyacaksınız.

## Donanım

Wio Terminal için bir GPS sensörü gereklidir.

Kullanacağınız sensör [Grove GPS Air530 sensörü](https://www.seeedstudio.com/Grove-GPS-Air530-p-4584.html). Bu sensör, hızlı ve doğru bir konum belirleme için birden fazla GPS sistemine bağlanabilir. Sensör, iki parçadan oluşur - sensörün temel elektronik bileşenleri ve uydulardan radyo dalgalarını almak için ince bir kabloyla bağlanan harici anten.

Bu bir UART sensörüdür, dolayısıyla GPS verilerini UART üzerinden gönderir.

### GPS Sensörünü Bağlama

Grove GPS sensörü, Wio Terminal'e bağlanabilir.

#### Görev - GPS sensörünü bağlayın

GPS sensörünü bağlayın.

![Bir Grove GPS sensörü](../../../../../translated_images/tr/grove-gps-sensor.247943bf69b03f0d1820ef6ed10c587f9b650e8db55b936851c92412180bd3e2.png)

1. Grove kablosunun bir ucunu GPS sensöründeki sokete takın. Kablo yalnızca tek bir yönde takılabilir.

1. Wio Terminal'i bilgisayarınızdan veya başka bir güç kaynağından ayırarak, Grove kablosunun diğer ucunu ekranı size dönük şekilde Wio Terminal'in sol tarafındaki Grove soketine bağlayın. Bu soket, güç düğmesine en yakın olan sokettir.

    ![Grove GPS sensörü sol sokete bağlı](../../../../../translated_images/tr/wio-gps-sensor.19fd52b81ce58095.webp)

1. GPS sensörünü, bağlı antenin gökyüzüne görünürlüğü olacak şekilde konumlandırın - ideal olarak açık bir pencere yanında veya dışarıda. Antenin önünde hiçbir engel olmaması, daha net bir sinyal almayı kolaylaştırır.

1. Artık Wio Terminal'i bilgisayarınıza bağlayabilirsiniz.

1. GPS sensöründe 2 LED bulunur - veri iletildiğinde yanıp sönen mavi bir LED ve uydulardan veri alındığında her saniye yanıp sönen yeşil bir LED. Wio Terminal'i açtığınızda mavi LED'in yanıp söndüğünden emin olun. Birkaç dakika sonra yeşil LED yanıp sönecektir - eğer yanıp sönmezse, anteni yeniden konumlandırmanız gerekebilir.

## GPS Sensörünü Programlama

Wio Terminal artık bağlı GPS sensörünü kullanacak şekilde programlanabilir.

### Görev - GPS sensörünü programlayın

Cihazı programlayın.

1. PlatformIO kullanarak yeni bir Wio Terminal projesi oluşturun. Bu projeye `gps-sensor` adını verin. `setup` fonksiyonunda seri portu yapılandırmak için kod ekleyin.

1. `main.cpp` dosyasının en üstüne aşağıdaki include direktifini ekleyin. Bu, UART için sol Grove portunu yapılandırmak üzere işlevler içeren bir başlık dosyasını dahil eder:

    ```cpp
    #include <wiring_private.h>
    ```

1. Bunun altına, UART portuna bir seri port bağlantısı tanımlamak için aşağıdaki kod satırını ekleyin:

    ```cpp
    static Uart Serial3(&sercom3, PIN_WIRE_SCL, PIN_WIRE_SDA, SERCOM_RX_PAD_1, UART_TX_PAD_0);
    ```

1. Bazı dahili sinyal işleyicilerini bu seri porta yönlendirmek için kod eklemeniz gerekiyor. `Serial3` tanımının altına aşağıdaki kodu ekleyin:

    ```cpp
    void SERCOM3_0_Handler()
    {
        Serial3.IrqHandler();
    }
    
    void SERCOM3_1_Handler()
    {
        Serial3.IrqHandler();
    }
    
    void SERCOM3_2_Handler()
    {
        Serial3.IrqHandler();
    }
    
    void SERCOM3_3_Handler()
    {
        Serial3.IrqHandler();
    }
    ```

1. `setup` fonksiyonunda, `Serial` port yapılandırmasının altına, UART seri portunu yapılandırmak için aşağıdaki kodu ekleyin:

    ```cpp
    Serial3.begin(9600);

    while (!Serial3)
        ; // Wait for Serial3 to be ready

    delay(1000);
    ```

1. `setup` fonksiyonundaki bu kodun altına, Grove pinini seri porta bağlamak için aşağıdaki kodu ekleyin:

    ```cpp
    pinPeripheral(PIN_WIRE_SCL, PIO_SERCOM_ALT);
    ```

1. `loop` fonksiyonundan önce, GPS verilerini seri monitöre göndermek için aşağıdaki işlevi ekleyin:

    ```cpp
    void printGPSData()
    {
        Serial.println(Serial3.readStringUntil('\n'));
    }
    ```

1. `loop` fonksiyonunda, UART seri portundan veri okumak ve seri monitöre çıktı göndermek için aşağıdaki kodu ekleyin:

    ```cpp
    while (Serial3.available() > 0)
    {
        printGPSData();
    }
    
    delay(1000);
    ```

    Bu kod, UART seri portundan veri okur. `readStringUntil` işlevi, bir sonlandırıcı karaktere kadar okuma yapar, bu durumda bir yeni satır karakteri. Bu, bir NMEA cümlesini tamamen okuyacaktır (NMEA cümleleri bir yeni satır karakteri ile sonlandırılır). UART seri portundan veri okunabildiği sürece, veri okunur ve `printGPSData` işlevi aracılığıyla seri monitöre gönderilir. Daha fazla veri okunamadığında, `loop` 1 saniye (1,000ms) bekler.

1. Kodu derleyin ve Wio Terminal'e yükleyin.

1. Yükleme tamamlandıktan sonra, seri monitör kullanarak GPS verilerini izleyebilirsiniz.

    ```output
    > Executing task: platformio device monitor <
    
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1201  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    $GNGGA,020604.001,4738.538654,N,12208.341758,W,1,3,,164.7,M,-17.1,M,,*67
    $GPGSA,A,1,,,,,,,,,,,,,,,*1E
    $BDGSA,A,1,,,,,,,,,,,,,,,*0F
    $GPGSV,1,1,00*79
    $BDGSV,1,1,00*68
    ```

> 💁 Bu kodu [code-gps/wio-terminal](../../../../../3-transport/lessons/1-location-tracking/code-gps/wio-terminal) klasöründe bulabilirsiniz.

😀 GPS sensörü programınız başarıyla çalıştı!

---

**Feragatname**:  
Bu belge, AI çeviri hizmeti [Co-op Translator](https://github.com/Azure/co-op-translator) kullanılarak çevrilmiştir. Doğruluk için çaba göstersek de, otomatik çevirilerin hata veya yanlışlıklar içerebileceğini lütfen unutmayın. Belgenin orijinal dili, yetkili kaynak olarak kabul edilmelidir. Kritik bilgiler için profesyonel insan çevirisi önerilir. Bu çevirinin kullanımından kaynaklanan yanlış anlamalar veya yanlış yorumlamalar için sorumluluk kabul etmiyoruz.