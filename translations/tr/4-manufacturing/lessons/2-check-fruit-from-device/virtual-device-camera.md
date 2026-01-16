<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "3ba7150ffc4a6999f6c3cfb4906ec7df",
  "translation_date": "2025-08-28T02:48:52+00:00",
  "source_file": "4-manufacturing/lessons/2-check-fruit-from-device/virtual-device-camera.md",
  "language_code": "tr"
}
-->
# Bir Görüntü Yakalama - Sanal IoT Donanımı

Bu dersin bu bölümünde, sanal IoT cihazınıza bir kamera sensörü ekleyecek ve bu sensörden görüntüler okuyacaksınız.

## Donanım

Sanal IoT cihazı, dosyalardan veya web kameranızdan görüntüler gönderen simüle edilmiş bir kamera kullanacaktır.

### Kamerayı CounterFit'e Ekleme

Sanal bir kamera kullanmak için, CounterFit uygulamasına bir kamera eklemeniz gerekir.

#### Görev - Kamerayı CounterFit'e ekleyin

Kamerayı CounterFit uygulamasına ekleyin.

1. Bilgisayarınızda `fruit-quality-detector` adlı bir klasörde `app.py` adlı tek bir dosya ve bir Python sanal ortamı ile yeni bir Python uygulaması oluşturun ve CounterFit pip paketlerini ekleyin.

    > ⚠️ Gerekirse [ders 1'de CounterFit Python projesi oluşturma ve ayarlama talimatlarına](../../../1-getting-started/lessons/1-introduction-to-iot/virtual-device.md) başvurabilirsiniz.

1. Kamera sensörleriyle iletişim kurabilen ve bazı [Picamera Pip paketi](https://pypi.org/project/picamera/) özelliklerini simüle eden bir CounterFit shim yüklemek için ek bir Pip paketi yükleyin. Bu işlemi, sanal ortamın etkin olduğu bir terminalden yaptığınızdan emin olun.

    ```sh
    pip install counterfit-shims-picamera
    ```

1. CounterFit web uygulamasının çalıştığından emin olun.

1. Bir kamera oluşturun:

    1. *Sensors* panelindeki *Create sensor* kutusunda, *Sensor type* açılır kutusundan *Camera* seçeneğini seçin.

    1. *Name* alanına `Picamera` yazın.

    1. Kamerayı oluşturmak için **Add** düğmesini seçin.

    ![Kamera ayarları](../../../../../translated_images/tr/counterfit-create-camera.a5de97f59c0bd3cbe0416d7e89a3cfe86d19fbae05c641c53a91286412af0a34.png)

    Kamera oluşturulacak ve sensörler listesinde görünecektir.

    ![Oluşturulan kamera](../../../../../translated_images/tr/counterfit-camera.001ec52194c8ee5d3f617173da2c79e1df903d10882adc625cbfc493525125d4.png)

## Kamerayı Programlama

Sanal IoT cihazı artık sanal kamerayı kullanacak şekilde programlanabilir.

### Görev - Kamerayı programlayın

Cihazı programlayın.

1. `fruit-quality-detector` uygulamasının VS Code'da açık olduğundan emin olun.

1. `app.py` dosyasını açın.

1. Uygulamayı CounterFit'e bağlamak için aşağıdaki kodu `app.py` dosyasının en üstüne ekleyin:

    ```python
    from counterfit_connection import CounterFitConnection
    CounterFitConnection.init('127.0.0.1', 5000)
    ```

1. Aşağıdaki kodu `app.py` dosyanıza ekleyin:

    ```python
    import io
    from counterfit_shims_picamera import PiCamera
    ```

    Bu kod, gerekli bazı kütüphaneleri, CounterFit shim'inden `PiCamera` sınıfı dahil olmak üzere içe aktarır.

1. Kamerayı başlatmak için aşağıdaki kodu ekleyin:

    ```python
    camera = PiCamera()
    camera.resolution = (640, 480)
    camera.rotation = 0
    ```

    Bu kod, bir PiCamera nesnesi oluşturur ve çözünürlüğü 640x480 olarak ayarlar. Daha yüksek çözünürlükler desteklenmesine rağmen, görüntü sınıflandırıcı çok daha küçük görüntülerle (227x227) çalışır, bu nedenle daha büyük görüntüler yakalamaya ve göndermeye gerek yoktur.

    `camera.rotation = 0` satırı, görüntünün döndürülme açısını derece cinsinden ayarlar. Web kamerasından veya dosyadan gelen görüntüyü döndürmeniz gerekiyorsa, bu değeri uygun şekilde ayarlayın. Örneğin, bir web kamerasındaki yatay moddaki bir muz görüntüsünü dikey moda çevirmek istiyorsanız, `camera.rotation = 90` olarak ayarlayın.

1. Görüntüyü ikili veri olarak yakalamak için aşağıdaki kodu ekleyin:

    ```python
    image = io.BytesIO()
    camera.capture(image, 'jpeg')
    image.seek(0)
    ```

    Bu kod, ikili verileri depolamak için bir `BytesIO` nesnesi oluşturur. Görüntü, kameradan bir JPEG dosyası olarak okunur ve bu nesnede saklanır. Bu nesne, verilerin neresinde olduğunu bilmek için bir konum göstergesine sahiptir, böylece gerekirse daha fazla veri sona yazılabilir. `image.seek(0)` satırı, bu konumu başa döndürerek tüm verilerin daha sonra okunabilmesini sağlar.

1. Görüntüyü bir dosyaya kaydetmek için aşağıdakileri ekleyin:

    ```python
    with open('image.jpg', 'wb') as image_file:
        image_file.write(image.read())
    ```

    Bu kod, yazma için `image.jpg` adlı bir dosya açar, ardından `BytesIO` nesnesinden tüm verileri okur ve bu dosyaya yazar.

    > 💁 Görüntüyü bir `BytesIO` nesnesi yerine doğrudan bir dosyaya yakalamak için `camera.capture` çağrısına dosya adını geçebilirsiniz. Bu derste daha sonra görüntüyü görüntü sınıflandırıcınıza gönderebilmek için `BytesIO` nesnesi kullanılmıştır.

1. CounterFit'teki kameranın yakalayacağı görüntüyü yapılandırın. *Source* seçeneğini *File* olarak ayarlayabilir ve bir görüntü dosyası yükleyebilir veya *Source* seçeneğini *WebCam* olarak ayarlayarak görüntülerin web kameranızdan yakalanmasını sağlayabilirsiniz. Bir resim seçtikten veya web kameranızı seçtikten sonra **Set** düğmesini seçtiğinizden emin olun.

    ![CounterFit'te bir dosyanın görüntü kaynağı olarak ayarlandığı ve bir kişinin muz tuttuğu bir web kamerası önizlemesi](../../../../../translated_images/tr/counterfit-camera-options.eb3bd5150a8e7dffbf24bc5bcaba0cf2cdef95fbe6bbe393695d173817d6b8df.png)

1. Bir görüntü yakalanacak ve mevcut klasörde `image.jpg` olarak kaydedilecektir. Bu dosyayı VS Code gezgininde göreceksiniz. Dosyayı seçerek görüntüyü görüntüleyin. Döndürme gerekiyorsa, `camera.rotation = 0` satırını uygun şekilde güncelleyin ve başka bir fotoğraf çekin.

> 💁 Bu kodu [code-camera/virtual-iot-device](../../../../../4-manufacturing/lessons/2-check-fruit-from-device/code-camera/virtual-iot-device) klasöründe bulabilirsiniz.

😀 Kamera programınız başarıyla çalıştı!

---

**Feragatname**:  
Bu belge, AI çeviri hizmeti [Co-op Translator](https://github.com/Azure/co-op-translator) kullanılarak çevrilmiştir. Doğruluk için çaba göstersek de, otomatik çevirilerin hata veya yanlışlıklar içerebileceğini lütfen unutmayın. Belgenin orijinal dili, yetkili kaynak olarak kabul edilmelidir. Kritik bilgiler için profesyonel insan çevirisi önerilir. Bu çevirinin kullanımından kaynaklanan yanlış anlamalar veya yanlış yorumlamalar için sorumluluk kabul etmiyoruz.