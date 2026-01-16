<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "c677667095f6133eee418c7e53615d05",
  "translation_date": "2025-08-28T02:48:12+00:00",
  "source_file": "4-manufacturing/lessons/2-check-fruit-from-device/pi-camera.md",
  "language_code": "tr"
}
-->
# Bir görüntü yakalama - Raspberry Pi

Bu dersin bu bölümünde, Raspberry Pi'nize bir kamera sensörü ekleyecek ve ondan görüntü okuyacaksınız.

## Donanım

Raspberry Pi'nin bir kameraya ihtiyacı var.

Kullanacağınız kamera [Raspberry Pi Kamera Modülü](https://www.raspberrypi.org/products/camera-module-v2/). Bu kamera, Raspberry Pi ile çalışmak üzere tasarlanmıştır ve Pi üzerinde özel bir konektör aracılığıyla bağlanır.

> 💁 Bu kamera, [Mobil Endüstri İşlemci Arayüzü İttifakı tarafından geliştirilen bir protokol olan Kamera Seri Arayüzü](https://wikipedia.org/wiki/Camera_Serial_Interface) (MIPI-CSI) kullanır. Bu, görüntüleri göndermek için özel bir protokoldür.

## Kamerayı bağlama

Kamera, Raspberry Pi'ye bir şerit kablo kullanılarak bağlanabilir.

### Görev - kamerayı bağlama

![Bir Raspberry Pi Kamera](../../../../../translated_images/tr/pi-camera-module.4278753c31bd6e757aa2b858be97d72049f71616278cefe4fb5abb485b40a078.png)

1. Pi'yi kapatın.

1. Kamerayla birlikte gelen şerit kabloyu kameraya bağlayın. Bunu yapmak için, tutucudaki siyah plastik klipsi hafifçe çekerek biraz dışarı çıkarın, ardından kabloyu sokete kaydırın. Mavi taraf lensin dışına, metal pin şeritleri lensin içine bakacak şekilde yerleştirin. Kablo tamamen yerleştirildikten sonra siyah plastik klipsi tekrar yerine itin.

    Klipsi nasıl açacağınızı ve kabloyu nasıl yerleştireceğinizi gösteren bir animasyonu [Raspberry Pi Kamera Modülü ile Başlangıç Belgelerinde](https://projects.raspberrypi.org/en/projects/getting-started-with-picamera/2) bulabilirsiniz.

    ![Şerit kablo kamera modülüne yerleştirilmiş](../../../../../translated_images/tr/pi-camera-ribbon-cable.0bf82acd251611c21ac616f082849413e2b322a261d0e4f8fec344248083b07e.png)

1. Grove Base Hat'ı Pi'den çıkarın.

1. Şerit kabloyu Grove Base Hat'taki kamera yuvasından geçirin. Kablonun mavi tarafının **A0**, **A1** gibi analog portlara doğru baktığından emin olun.

    ![Şerit kablo Grove Base Hat'tan geçiyor](../../../../../translated_images/tr/grove-base-hat-ribbon-cable.501fed202fcf73b11b2b68f6d246189f7d15d3e4423c572ddee79d77b4632b47.png)

1. Şerit kabloyu Pi üzerindeki kamera portuna yerleştirin. Yine siyah plastik klipsi yukarı çekin, kabloyu yerleştirin ve klipsi tekrar yerine itin. Kablonun mavi tarafı USB ve ethernet portlarına doğru bakmalıdır.

    ![Şerit kablo Pi üzerindeki kamera soketine bağlı](../../../../../translated_images/tr/pi-camera-socket-ribbon-cable.a18309920b11800911082ed7aa6fb28e6d9be3a022e4079ff990016cae3fca10.png)

1. Grove Base Hat'ı tekrar takın.

## Kamerayı programlama

Raspberry Pi artık [PiCamera](https://pypi.org/project/picamera/) Python kütüphanesini kullanarak kamerayı programlamak için hazır.

### Görev - eski kamera modunu etkinleştirme

Ne yazık ki, Raspberry Pi OS Bullseye sürümüyle birlikte işletim sistemiyle gelen kamera yazılımı değişti ve varsayılan olarak PiCamera artık çalışmıyor. Bunun yerine PiCamera2 adlı bir alternatif geliştiriliyor, ancak henüz kullanıma hazır değil.

Şimdilik, PiCamera'nın çalışmasına izin vermek için Pi'nizi eski kamera moduna ayarlayabilirsiniz. Kamera soketi varsayılan olarak devre dışıdır, ancak eski kamera yazılımını açmak soketi otomatik olarak etkinleştirir.

1. Pi'yi açın ve başlatılmasını bekleyin.

1. VS Code'u doğrudan Pi üzerinde veya Remote SSH uzantısı aracılığıyla bağlanarak başlatın.

1. Terminalden aşağıdaki komutları çalıştırın:

    ```sh
    sudo raspi-config nonint do_legacy 0
    sudo reboot
    ```

    Bu, eski kamera yazılımını etkinleştirmek için bir ayarı değiştirecek ve ardından bu ayarın etkili olması için Pi'yi yeniden başlatacaktır.

1. Pi'nin yeniden başlatılmasını bekleyin ve ardından VS Code'u tekrar başlatın.

### Görev - kamerayı programlama

Cihazı programlayın.

1. Terminalden, `pi` kullanıcısının ana dizininde `fruit-quality-detector` adlı yeni bir klasör oluşturun. Bu klasörde `app.py` adlı bir dosya oluşturun.

1. Bu klasörü VS Code'da açın.

1. Kamera ile etkileşim kurmak için PiCamera Python kütüphanesini kullanabilirsiniz. Bunun için aşağıdaki komutla Pip paketini yükleyin:

    ```sh
    pip3 install picamera
    ```

1. `app.py` dosyanıza aşağıdaki kodu ekleyin:

    ```python
    import io
    import time
    from picamera import PiCamera
    ```

    Bu kod, `PiCamera` kütüphanesi dahil olmak üzere gerekli bazı kütüphaneleri içe aktarır.

1. Kamerayı başlatmak için aşağıdaki kodu ekleyin:

    ```python
    camera = PiCamera()
    camera.resolution = (640, 480)
    camera.rotation = 0
    
    time.sleep(2)
    ```

    Bu kod, bir PiCamera nesnesi oluşturur ve çözünürlüğü 640x480 olarak ayarlar. Daha yüksek çözünürlükler desteklenir (3280x2464'e kadar), ancak görüntü sınıflandırıcı çok daha küçük görüntülerde (227x227) çalıştığı için daha büyük görüntüleri yakalamaya ve göndermeye gerek yoktur.

    `camera.rotation = 0` satırı görüntünün dönüşünü ayarlar. Şerit kablo kameranın altına gelir, ancak kameranız sınıflandırmak istediğiniz öğeye daha kolay yönelmesi için döndürülmüşse, bu satırı döndürme derecesine göre değiştirebilirsiniz.

    ![Kamera bir içecek kutusunun üzerine asılmış](../../../../../translated_images/tr/pi-camera-upside-down.5376961ba31459883362124152ad6b823d5ac5fc14e85f317e22903bd681c2b6.png)

    Örneğin, şerit kabloyu bir şeyin üzerine asarak kameranın üst kısmında olacak şekilde yerleştirirseniz, dönüşü 180 olarak ayarlayın:

    ```python
    camera.rotation = 180
    ```

    Kamera başlatılmak için birkaç saniye alır, bu nedenle `time.sleep(2)` satırı eklenmiştir.

1. Görüntüyü ikili veri olarak yakalamak için aşağıdaki kodu ekleyin:

    ```python
    image = io.BytesIO()
    camera.capture(image, 'jpeg')
    image.seek(0)
    ```

    Bu kod, ikili verileri depolamak için bir `BytesIO` nesnesi oluşturur. Görüntü kameradan bir JPEG dosyası olarak okunur ve bu nesneye kaydedilir. Bu nesne, daha fazla veri gerektiğinde sona yazılabilmesi için bir konum göstergesine sahiptir, bu nedenle `image.seek(0)` satırı bu konumu başlangıca geri taşır, böylece tüm veri daha sonra okunabilir.

1. Bunun altına, görüntüyü bir dosyaya kaydetmek için aşağıdaki kodu ekleyin:

    ```python
    with open('image.jpg', 'wb') as image_file:
        image_file.write(image.read())
    ```

    Bu kod, yazma için `image.jpg` adlı bir dosya açar, ardından `BytesIO` nesnesinden tüm veriyi okur ve dosyaya yazar.

    > 💁 Görüntüyü doğrudan bir dosyaya yakalayabilirsiniz, `camera.capture` çağrısına dosya adını geçirerek. Bu dersin ilerleyen bölümlerinde görüntüyü görüntü sınıflandırıcınıza gönderebilmek için `BytesIO` nesnesi kullanılmıştır.

1. Kamerayı bir şeye doğrultun ve bu kodu çalıştırın.

1. Bir görüntü yakalanacak ve mevcut klasörde `image.jpg` olarak kaydedilecektir. Bu dosyayı VS Code gezgininde göreceksiniz. Dosyayı seçerek görüntüyü görüntüleyin. Döndürme gerekiyorsa, `camera.rotation = 0` satırını gerektiği gibi güncelleyin ve başka bir fotoğraf çekin.

> 💁 Bu kodu [code-camera/pi](../../../../../4-manufacturing/lessons/2-check-fruit-from-device/code-camera/pi) klasöründe bulabilirsiniz.

😀 Kamera programınız başarılı oldu!

---

**Feragatname**:  
Bu belge, AI çeviri hizmeti [Co-op Translator](https://github.com/Azure/co-op-translator) kullanılarak çevrilmiştir. Doğruluk için çaba göstersek de, otomatik çevirilerin hata veya yanlışlıklar içerebileceğini lütfen unutmayın. Belgenin orijinal dili, yetkili kaynak olarak kabul edilmelidir. Kritik bilgiler için profesyonel insan çevirisi önerilir. Bu çevirinin kullanımından kaynaklanan yanlış anlamalar veya yanlış yorumlamalardan sorumlu değiliz.