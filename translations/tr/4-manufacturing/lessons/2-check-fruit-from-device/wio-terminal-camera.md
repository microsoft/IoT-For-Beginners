# Bir Görüntü Yakalama - Wio Terminal

Bu dersin bu bölümünde, Wio Terminal'inize bir kamera ekleyecek ve bu kameradan görüntüler yakalayacaksınız.

## Donanım

Wio Terminal bir kameraya ihtiyaç duyar.

Kullanacağınız kamera bir [ArduCam Mini 2MP Plus](https://www.arducam.com/product/arducam-2mp-spi-camera-b0067-arduino/). Bu, OV2640 görüntü sensörüne dayalı 2 megapiksel bir kameradır. Görüntüleri yakalamak için bir SPI arayüzü üzerinden iletişim kurar ve sensörü yapılandırmak için I2C kullanır.

## Kamerayı Bağlama

ArduCam bir Grove soketine sahip değildir, bunun yerine SPI ve I2C veri yollarına Wio Terminal'in GPIO pinleri üzerinden bağlanır.

### Görev - Kamerayı bağlayın

Kamerayı bağlayın.

![Bir ArduCam sensörü](../../../../../translated_images/tr/arducam.20e4e4cbb2682965.webp)

1. ArduCam'in altındaki pinler, Wio Terminal'in GPIO pinlerine bağlanmalıdır. Doğru pinleri bulmayı kolaylaştırmak için, Wio Terminal ile birlikte gelen GPIO pin etiketini pinlerin etrafına yapıştırın:

    ![GPIO pin etiketi takılmış Wio Terminal](../../../../../translated_images/tr/wio-terminal-pin-sticker.b90b1535937b84bd.webp)

1. Jumper kabloları kullanarak aşağıdaki bağlantıları yapın:

    | ArduCAM pini | Wio Terminal pini | Açıklama                                |
    | ------------ | ----------------- | --------------------------------------- |
    | CS           | 24 (SPI_CS)       | SPI Yonga Seçimi                        |
    | MOSI         | 19 (SPI_MOSI)     | SPI Kontrolcü Çıkışı, Çevresel Giriş    |
    | MISO         | 21 (SPI_MISO)     | SPI Kontrolcü Girişi, Çevresel Çıkış    |
    | SCK          | 23 (SPI_SCLK)     | SPI Seri Saat                          |
    | GND          | 6 (GND)           | Topraklama - 0V                         |
    | VCC          | 4 (5V)            | 5V güç kaynağı                          |
    | SDA          | 3 (I2C1_SDA)      | I2C Seri Veri                           |
    | SCL          | 5 (I2C1_SCL)      | I2C Seri Saat                           |

    ![Jumper kablolarla ArduCam'e bağlanmış Wio Terminal](../../../../../translated_images/tr/arducam-wio-terminal-connections.a4d5a4049bdb5ab8.webp)

    GND ve VCC bağlantıları, ArduCam'e 5V güç sağlar. Bu, 3V ile çalışan Grove sensörlerinden farklı olarak 5V ile çalışır. Bu güç, cihazı besleyen USB-C bağlantısından gelir.

    > 💁 SPI bağlantısı için, ArduCam üzerindeki pin etiketleri ve Wio Terminal pin adları kodda eski adlandırma düzenini kullanır. Bu dersteki talimatlar, kodda kullanılan pin adları hariç, yeni adlandırma düzenini kullanacaktır.

1. Artık Wio Terminal'i bilgisayarınıza bağlayabilirsiniz.

## Kameraya Bağlanmak için Cihazı Programlama

Wio Terminal artık bağlı ArduCAM kamerayı kullanacak şekilde programlanabilir.

### Görev - Kameraya bağlanmak için cihazı programlayın

1. PlatformIO kullanarak yeni bir Wio Terminal projesi oluşturun. Bu projeye `fruit-quality-detector` adını verin. Seri portu yapılandırmak için `setup` fonksiyonuna kod ekleyin.

1. WiFi'ye bağlanmak için kod ekleyin ve WiFi kimlik bilgilerinizi `config.h` adlı bir dosyada saklayın. Gerekli kütüphaneleri `platformio.ini` dosyasına eklemeyi unutmayın.

1. ArduCam kütüphanesi, `platformio.ini` dosyasından yüklenebilecek bir Arduino kütüphanesi olarak mevcut değildir. Bunun yerine, GitHub sayfasından kaynak kod olarak yüklenmesi gerekir. Bunu şu şekilde yapabilirsiniz:

    * [https://github.com/ArduCAM/Arduino.git](https://github.com/ArduCAM/Arduino.git) adresinden repo'yu klonlayarak
    * GitHub'daki repo'ya giderek [github.com/ArduCAM/Arduino](https://github.com/ArduCAM/Arduino) ve **Code** düğmesinden kodu zip olarak indirerek

1. Bu koddan yalnızca `ArduCAM` klasörüne ihtiyacınız var. Tüm klasörü projenizin `lib` klasörüne kopyalayın.

    > ⚠️ Tüm klasör kopyalanmalıdır, böylece kod `lib/ArduCam` içinde olur. `ArduCam` klasörünün içeriğini `lib` klasörüne kopyalamayın, tüm klasörü taşıyın.

1. ArduCam kütüphane kodu, birden fazla kamera türü için çalışır. Kullanmak istediğiniz kamera türü, derleyici bayrakları kullanılarak yapılandırılır - bu, kullanmadığınız kameralar için olan kodu kaldırarak oluşturulan kütüphaneyi olabildiğince küçük tutar. OV2640 kamera için kütüphaneyi yapılandırmak için, `platformio.ini` dosyasının sonuna aşağıdakileri ekleyin:

    ```ini
    build_flags =
        -DARDUCAM_SHIELD_V2
        -DOV2640_CAM
    ```

    Bu, 2 derleyici bayrağı ayarlar:

      * `ARDUCAM_SHIELD_V2`, kütüphaneye kameranın bir Arduino kartında (shield) olduğunu söyler.
      * `OV2640_CAM`, kütüphaneye yalnızca OV2640 kamera için kod eklemesini söyler.

1. `src` klasörüne `camera.h` adlı bir başlık dosyası ekleyin. Bu dosya, kamera ile iletişim kurmak için kod içerecektir. Bu dosyaya şu kodu ekleyin:

    ```cpp
    #pragma once
    
    #include <ArduCAM.h>
    #include <Wire.h>
    
    class Camera
    {
    public:
        Camera(int format, int image_size) : _arducam(OV2640, PIN_SPI_SS)
        {
            _format = format;
            _image_size = image_size;
        }
    
        bool init()
        {
            // Reset the CPLD
            _arducam.write_reg(0x07, 0x80);
            delay(100);
    
            _arducam.write_reg(0x07, 0x00);
            delay(100);
    
            // Check if the ArduCAM SPI bus is OK
            _arducam.write_reg(ARDUCHIP_TEST1, 0x55);
            if (_arducam.read_reg(ARDUCHIP_TEST1) != 0x55)
            {
                return false;
            }
                
            // Change MCU mode
            _arducam.set_mode(MCU2LCD_MODE);
    
            uint8_t vid, pid;
    
            // Check if the camera module type is OV2640
            _arducam.wrSensorReg8_8(0xff, 0x01);
            _arducam.rdSensorReg8_8(OV2640_CHIPID_HIGH, &vid);
            _arducam.rdSensorReg8_8(OV2640_CHIPID_LOW, &pid);
            if ((vid != 0x26) && ((pid != 0x41) || (pid != 0x42)))
            {
                return false;
            }
            
            _arducam.set_format(_format);
            _arducam.InitCAM();
            _arducam.OV2640_set_JPEG_size(_image_size);
            _arducam.OV2640_set_Light_Mode(Auto);
            _arducam.OV2640_set_Special_effects(Normal);
            delay(1000);
    
            return true;
        }
    
        void startCapture()
        {
            _arducam.flush_fifo();
            _arducam.clear_fifo_flag();
            _arducam.start_capture();
        }
    
        bool captureReady()
        {
            return _arducam.get_bit(ARDUCHIP_TRIG, CAP_DONE_MASK);
        }
    
        bool readImageToBuffer(byte **buffer, uint32_t &buffer_length)
        {
            if (!captureReady()) return false;
    
            // Get the image file length
            uint32_t length = _arducam.read_fifo_length();
            buffer_length = length;
    
            if (length >= MAX_FIFO_SIZE)
            {
                return false;
            }
            if (length == 0)
            {
                return false;
            }
    
            // create the buffer
            byte *buf = new byte[length];
    
            uint8_t temp = 0, temp_last = 0;
            int i = 0;
            uint32_t buffer_pos = 0;
            bool is_header = false;
    
            _arducam.CS_LOW();
            _arducam.set_fifo_burst();
            
            while (length--)
            {
                temp_last = temp;
                temp = SPI.transfer(0x00);
                //Read JPEG data from FIFO
                if ((temp == 0xD9) && (temp_last == 0xFF)) //If find the end ,break while,
                {
                    buf[buffer_pos] = temp;
    
                    buffer_pos++;
                    i++;
                    
                    _arducam.CS_HIGH();
                }
                if (is_header == true)
                {
                    //Write image data to buffer if not full
                    if (i < 256)
                    {
                        buf[buffer_pos] = temp;
                        buffer_pos++;
                        i++;
                    }
                    else
                    {
                        _arducam.CS_HIGH();
    
                        i = 0;
                        buf[buffer_pos] = temp;
    
                        buffer_pos++;
                        i++;
    
                        _arducam.CS_LOW();
                        _arducam.set_fifo_burst();
                    }
                }
                else if ((temp == 0xD8) & (temp_last == 0xFF))
                {
                    is_header = true;
    
                    buf[buffer_pos] = temp_last;
                    buffer_pos++;
                    i++;
    
                    buf[buffer_pos] = temp;
                    buffer_pos++;
                    i++;
                }
            }
            
            _arducam.clear_fifo_flag();
    
            _arducam.set_format(_format);
            _arducam.InitCAM();
            _arducam.OV2640_set_JPEG_size(_image_size);
    
            // return the buffer
            *buffer = buf;
        }
    
    private:
        ArduCAM _arducam;
        int _format;
        int _image_size;
    };
    ```

    Bu, ArduCam kütüphanelerini kullanarak kamerayı yapılandıran ve gerektiğinde SPI veri yolu üzerinden görüntüleri çıkaran düşük seviyeli bir koddur. Bu kod, ArduCam'e çok özeldir, bu yüzden şu anda nasıl çalıştığını anlamanız gerekmez.

1. `main.cpp` dosyasında, diğer `include` ifadelerinin altına bu yeni dosyayı dahil etmek ve bir kamera sınıfı örneği oluşturmak için şu kodu ekleyin:

    ```cpp
    #include "camera.h"

    Camera camera = Camera(JPEG, OV2640_640x480);
    ```

    Bu, görüntüleri 640x480 çözünürlükte JPEG olarak kaydeden bir `Camera` oluşturur. Daha yüksek çözünürlükler desteklenir (3280x2464'e kadar), ancak görüntü sınıflandırıcı çok daha küçük görüntülerde (227x227) çalışır, bu nedenle daha büyük görüntüleri yakalamaya ve göndermeye gerek yoktur.

1. Kamerayı kurmak için bir fonksiyon tanımlamak üzere aşağıdaki kodu ekleyin:

    ```cpp
    void setupCamera()
    {
        pinMode(PIN_SPI_SS, OUTPUT);
        digitalWrite(PIN_SPI_SS, HIGH);
    
        Wire.begin();
        SPI.begin();
    
        if (!camera.init())
        {
            Serial.println("Error setting up the camera!");
        }
    }
    ```

    Bu `setupCamera` fonksiyonu, SPI yonga seçme pinini (`PIN_SPI_SS`) yüksek olarak yapılandırarak Wio Terminal'i SPI kontrolcüsü yapar. Daha sonra I2C ve SPI veri yollarını başlatır. Son olarak, kamera sensör ayarlarını yapılandıran ve her şeyin doğru şekilde bağlandığından emin olan kamera sınıfını başlatır.

1. Bu fonksiyonu `setup` fonksiyonunun sonunda çağırın:

    ```cpp
    setupCamera();
    ```

1. Bu kodu derleyin ve yükleyin, ardından seri monitörden çıktıyı kontrol edin. Eğer `Error setting up the camera!` mesajını görürseniz, tüm kabloların ArduCam üzerindeki doğru pinlere ve Wio Terminal'in GPIO pinlerine bağlandığından ve tüm jumper kabloların düzgün oturduğundan emin olun.

## Bir Görüntü Yakalama

Wio Terminal artık bir düğmeye basıldığında bir görüntü yakalayacak şekilde programlanabilir.

### Görev - Bir görüntü yakalayın

1. Mikrodenetleyiciler kodunuzu sürekli çalıştırır, bu nedenle bir fotoğraf çekmek gibi bir işlemi tetiklemek için bir sensöre tepki vermek gerekir. Wio Terminal'in düğmeleri vardır, bu nedenle kamera, düğmelerden biriyle tetiklenecek şekilde ayarlanabilir. Güç anahtarına en yakın olan üstteki üç düğmeden biri olan C düğmesini yapılandırmak için `setup` fonksiyonunun sonuna şu kodu ekleyin:

    ![Güç anahtarına en yakın C düğmesi](../../../../../translated_images/tr/wio-terminal-c-button.73df3cb1c1445ea0.webp)

    ```cpp
    pinMode(WIO_KEY_C, INPUT_PULLUP);
    ```

    `INPUT_PULLUP` modu, bir girişi tersine çevirir. Örneğin, normalde bir düğme basılmadığında düşük bir sinyal, basıldığında ise yüksek bir sinyal gönderir. `INPUT_PULLUP` olarak ayarlandığında, basılmadığında yüksek bir sinyal, basıldığında ise düşük bir sinyal gönderir.

1. `loop` fonksiyonundan önce düğme basılmasına yanıt verecek boş bir fonksiyon ekleyin:

    ```cpp
    void buttonPressed()
    {
        
    }
    ```

1. Düğme basıldığında bu fonksiyonu `loop` metodunda çağırın:

    ```cpp
    void loop()
    {
        if (digitalRead(WIO_KEY_C) == LOW)
        {
            buttonPressed();
            delay(2000);
        }
    
        delay(200);
    }
    ```

    Bu kod, düğmenin basılıp basılmadığını kontrol eder. Eğer basılmışsa, `buttonPressed` fonksiyonu çağrılır ve döngü 2 saniye gecikir. Bu, düğmenin bırakılması için zaman tanır, böylece uzun bir basış iki kez kaydedilmez.

    > 💁 Wio Terminal üzerindeki düğme `INPUT_PULLUP` olarak ayarlanmıştır, bu nedenle basılmadığında yüksek bir sinyal, basıldığında ise düşük bir sinyal gönderir.

1. `buttonPressed` fonksiyonuna şu kodu ekleyin:

    ```cpp
    camera.startCapture();
 
    while (!camera.captureReady())
        delay(100);

    Serial.println("Image captured");

    byte *buffer;
    uint32_t length;

    if (camera.readImageToBuffer(&buffer, length))
    {
        Serial.print("Image read to buffer with length ");
        Serial.println(length);

        delete(buffer);
    }
    ```

    Bu kod, `startCapture` çağrısıyla kamera yakalamayı başlatır. Kamera donanımı, verileri talep ettiğinizde döndürmek yerine, bir görüntü yakalamayı başlatma talimatı gönderir ve kamera arka planda görüntüyü yakalamak, JPEG'e dönüştürmek ve kameranın kendi yerel tamponunda saklamak için çalışır. Daha sonra `captureReady` çağrısı, görüntü yakalamanın tamamlanıp tamamlanmadığını kontrol eder.

    Yakalama tamamlandıktan sonra, görüntü verileri kameranın tamponundan yerel bir tampona (bayt dizisi) `readImageToBuffer` çağrısıyla kopyalanır. Tamponun uzunluğu daha sonra seri monitöre gönderilir.

1. Bu kodu derleyin ve yükleyin, ardından seri monitördeki çıktıyı kontrol edin. Her C düğmesine bastığınızda bir görüntü yakalanacak ve görüntü boyutu seri monitöre gönderilecektir.

    ```output
    Connecting to WiFi..
    Connected!
    Image captured
    Image read to buffer with length 9224
    Image captured
    Image read to buffer with length 11272
    ```

    Farklı görüntülerin farklı boyutları olacaktır. Bunlar JPEG olarak sıkıştırılmıştır ve belirli bir çözünürlükteki bir JPEG dosyasının boyutu, görüntünün içeriğine bağlıdır.

> 💁 Bu kodu [code-camera/wio-terminal](../../../../../4-manufacturing/lessons/2-check-fruit-from-device/code-camera/wio-terminal) klasöründe bulabilirsiniz.

😀 Wio Terminal ile başarıyla görüntü yakaladınız.

## İsteğe Bağlı - Kamera Görüntülerini Bir SD Kart Kullanarak Doğrulama

Kamera tarafından yakalanan görüntüleri görmenin en kolay yolu, bunları Wio Terminal'deki bir SD karta yazmak ve ardından bilgisayarınızda görüntülemektir. Bu adımı, yedek bir microSD kartınız ve bilgisayarınızda bir microSD kart yuvası veya bir adaptör varsa yapabilirsiniz.

Wio Terminal yalnızca 16GB'a kadar microSD kartları destekler. Daha büyük bir SD kartınız varsa çalışmaz.

### Görev - Kamera görüntülerini bir SD kart kullanarak doğrulayın

1. Bilgisayarınızdaki ilgili uygulamaları (macOS'ta Disk Utility, Windows'ta File Explorer veya Linux'ta komut satırı araçları) kullanarak bir microSD kartı FAT32 veya exFAT olarak biçimlendirin.

1. MicroSD kartı güç anahtarının hemen altındaki yuvaya yerleştirin. Yerine oturup tıklayana kadar tamamen yerleştirdiğinizden emin olun, bunu yapmak için bir tırnak veya ince bir araç kullanmanız gerekebilir.

1. `main.cpp` dosyasının en üstüne şu include ifadelerini ekleyin:

    ```cpp
    #include "SD/Seeed_SD.h"
    #include <Seeed_FS.h>
    ```

1. `setup` fonksiyonundan önce şu fonksiyonu ekleyin:

    ```cpp
    void setupSDCard()
    {
        while (!SD.begin(SDCARD_SS_PIN, SDCARD_SPI))
        {
            Serial.println("SD Card Error");
        }
    }
    ```

    Bu, SPI veri yolunu kullanarak SD kartı yapılandırır.

1. Bunu `setup` fonksiyonundan çağırın:

    ```cpp
    setupSDCard();
    ```

1. `buttonPressed` fonksiyonunun üstüne şu kodu ekleyin:

    ```cpp
    int fileNum = 1;

    void saveToSDCard(byte *buffer, uint32_t length)
    {
        char buff[16];
        sprintf(buff, "%d.jpg", fileNum);
        fileNum++;
    
        File outFile = SD.open(buff, FILE_WRITE );
        outFile.write(buffer, length);
        outFile.close();

        Serial.print("Image written to file ");
        Serial.println(buff);
    }
    ```

    Bu, bir dosya sayacı için bir global değişken tanımlar. Bu, görüntü dosya adları için kullanılır, böylece birden fazla görüntü artan dosya adlarıyla yakalanabilir - `1.jpg`, `2.jpg` ve benzeri.

    Daha sonra, bir bayt veri tamponu ve tamponun uzunluğunu alan `saveToSDCard` fonksiyonunu tanımlar. Bir dosya adı dosya sayacını kullanarak oluşturulur ve dosya sayacı bir sonraki dosya için artırılır. Tampondaki ikili veriler daha sonra dosyaya yazılır.

1. `saveToSDCard` fonksiyonunu `buttonPressed` fonksiyonundan çağırın. Çağrı **tampon silinmeden önce** yapılmalıdır:

    ```cpp
    Serial.print("Image read to buffer with length ");
    Serial.println(length);

    saveToSDCard(buffer, length);
    
    delete(buffer);
    ```

1. Bu kodu derleyin ve yükleyin, ardından seri monitördeki çıktıyı kontrol edin. Her C düğmesine bastığınızda bir görüntü yakalanacak ve SD karta kaydedilecektir.

    ```output
    Connecting to WiFi..
    Connected!
    Image captured
    Image read to buffer with length 16392
    Image written to file 1.jpg
    Image captured
    Image read to buffer with length 14344
    Image written to file 2.jpg
    ```

1. MicroSD kartı kapatın ve hafifçe içeri itip serbest bırakarak çıkarın, kart dışarı fırlayacaktır. Bunu yapmak için ince bir araç kullanmanız gerekebilir. MicroSD kartı bilgisayarınıza takarak görüntüleri görüntüleyin.

    ![ArduCam kullanılarak çekilmiş bir muz resmi](../../../../../translated_images/tr/banana-arducam.be1b32d4267a8194.webp)
💁 Kameranın beyaz dengesinin kendini ayarlaması birkaç görüntü alabilir. Bunu, çekilen görüntülerin renginden fark edeceksiniz, ilk birkaç görüntü renk açısından farklı görünebilir. Bunu her zaman `setup` fonksiyonunda birkaç görüntü yakalayıp bunları görmezden gelecek şekilde kodu değiştirerek aşabilirsiniz.


---

**Feragatname**:  
Bu belge, AI çeviri hizmeti [Co-op Translator](https://github.com/Azure/co-op-translator) kullanılarak çevrilmiştir. Doğruluk için çaba göstersek de, otomatik çevirilerin hata veya yanlışlıklar içerebileceğini lütfen unutmayın. Belgenin orijinal dili, yetkili kaynak olarak kabul edilmelidir. Kritik bilgiler için profesyonel insan çevirisi önerilir. Bu çevirinin kullanımından kaynaklanan yanlış anlamalar veya yanlış yorumlamalar için sorumluluk kabul etmiyoruz.