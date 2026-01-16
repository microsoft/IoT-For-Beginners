<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "9c4320311c0f2c1884a6a21265d98a51",
  "translation_date": "2025-08-28T03:50:13+00:00",
  "source_file": "5-retail/lessons/2-check-stock-device/single-board-computer-count-stock.md",
  "language_code": "tr"
}
-->
# IoT Cihazınızdan Stok Sayımı - Sanal IoT Donanımı ve Raspberry Pi

Tahminler ve bunlara ait sınırlayıcı kutuların kombinasyonu, bir görüntüdeki stokları saymak için kullanılabilir.

## Sınırlayıcı Kutuları Göster

Sorun giderme adımı olarak, sınırlayıcı kutuları yalnızca konsola yazdırmakla kalmaz, aynı zamanda bir görüntü yakalandığında diske kaydedilen görüntü üzerinde de çizebilirsiniz.

### Görev - Sınırlayıcı Kutuları Yazdır

1. `stock-counter` projesinin VS Code'da açık olduğundan ve sanal bir IoT cihazı kullanıyorsanız sanal ortamın etkinleştirildiğinden emin olun.

1. `for` döngüsündeki `print` ifadesini aşağıdaki gibi değiştirerek sınırlayıcı kutuları konsola yazdırın:

    ```python
    print(f'{prediction.tag_name}:\t{prediction.probability * 100:.2f}%\t{prediction.bounding_box}')
    ```

1. Kamerayı bir raftaki stoklara doğrultarak uygulamayı çalıştırın. Sınırlayıcı kutular konsola yazdırılacak ve sol, üst, genişlik ve yükseklik değerleri 0-1 arasında olacaktır.

    ```output
    pi@raspberrypi:~/stock-counter $ python3 app.py 
    tomato paste:   33.42%  {'additional_properties': {}, 'left': 0.3455171, 'top': 0.09916268, 'width': 0.14175442, 'height': 0.29405564}
    tomato paste:   34.41%  {'additional_properties': {}, 'left': 0.48283678, 'top': 0.10242918, 'width': 0.11782813, 'height': 0.27467814}
    tomato paste:   31.25%  {'additional_properties': {}, 'left': 0.4923783, 'top': 0.35007596, 'width': 0.13668466, 'height': 0.28304994}
    tomato paste:   31.05%  {'additional_properties': {}, 'left': 0.36416405, 'top': 0.37494493, 'width': 0.14024884, 'height': 0.26880276}
    ```

### Görev - Görüntü Üzerine Sınırlayıcı Kutuları Çiz

1. [Pillow](https://pypi.org/project/Pillow/) adlı Pip paketi, görüntüler üzerinde çizim yapmak için kullanılabilir. Bunu aşağıdaki komutla yükleyin:

    ```sh
    pip3 install pillow
    ```

    Sanal bir IoT cihazı kullanıyorsanız, bu komutu etkinleştirilmiş sanal ortam içinde çalıştırdığınızdan emin olun.

1. `app.py` dosyasının en üstüne aşağıdaki import ifadesini ekleyin:

    ```python
    from PIL import Image, ImageDraw, ImageColor
    ```

    Bu, görüntüyü düzenlemek için gereken kodu içe aktarır.

1. `app.py` dosyasının sonuna aşağıdaki kodu ekleyin:

    ```python
    with Image.open('image.jpg') as im:
        draw = ImageDraw.Draw(im)
    
        for prediction in predictions:
            scale_left = prediction.bounding_box.left
            scale_top = prediction.bounding_box.top
            scale_right = prediction.bounding_box.left + prediction.bounding_box.width
            scale_bottom = prediction.bounding_box.top + prediction.bounding_box.height
            
            left = scale_left * im.width
            top = scale_top * im.height
            right = scale_right * im.width
            bottom = scale_bottom * im.height
    
            draw.rectangle([left, top, right, bottom], outline=ImageColor.getrgb('red'), width=2)
    
        im.save('image.jpg')
    ```

    Bu kod, daha önce düzenleme için kaydedilen görüntüyü açar. Ardından tahminler arasında döngü yaparak sınırlayıcı kutuları alır ve 0-1 aralığındaki sınırlayıcı kutu değerlerini kullanarak alt sağ koordinatı hesaplar. Bu değerler, görüntünün ilgili boyutuyla çarpılarak görüntü koordinatlarına dönüştürülür. Örneğin, sol değer 0.5 ve görüntü 600 piksel genişliğindeyse, bu değer 300'e dönüştürülür (0.5 x 600 = 300).

    Her sınırlayıcı kutu, görüntü üzerine kırmızı bir çizgiyle çizilir. Son olarak düzenlenmiş görüntü kaydedilir ve orijinal görüntünün üzerine yazılır.

1. Kamerayı bir raftaki stoklara doğrultarak uygulamayı çalıştırın. VS Code gezgininde `image.jpg` dosyasını göreceksiniz ve sınırlayıcı kutuları görmek için seçebilirsiniz.

    ![Her bir kutunun etrafında sınırlayıcı kutular olan 4 domates salçası kutusu](../../../../../translated_images/tr/rpi-stock-with-bounding-boxes.b5540e2ecb7cd49f.webp)

## Stok Sayımı

Yukarıda gösterilen görüntüde, sınırlayıcı kutuların küçük bir örtüşmesi var. Eğer bu örtüşme çok daha büyük olsaydı, sınırlayıcı kutular aynı nesneyi gösterebilirdi. Nesneleri doğru bir şekilde saymak için, önemli bir örtüşmeye sahip kutuları görmezden gelmeniz gerekir.

### Görev - Örtüşmeyi Görmezden Gelerek Stok Sayımı

1. [Shapely](https://pypi.org/project/Shapely/) adlı Pip paketi, kesişimi hesaplamak için kullanılabilir. Raspberry Pi kullanıyorsanız, önce bir kütüphane bağımlılığı yüklemeniz gerekir:

    ```sh
    sudo apt install libgeos-dev
    ```

1. Shapely Pip paketini yükleyin:

    ```sh
    pip3 install shapely
    ```

    Sanal bir IoT cihazı kullanıyorsanız, bu komutu etkinleştirilmiş sanal ortam içinde çalıştırdığınızdan emin olun.

1. `app.py` dosyasının en üstüne aşağıdaki import ifadesini ekleyin:

    ```python
    from shapely.geometry import Polygon
    ```

    Bu, örtüşmeyi hesaplamak için çokgenler oluşturmak için gereken kodu içe aktarır.

1. Sınırlayıcı kutuları çizen kodun üstüne aşağıdaki kodu ekleyin:

    ```python
    overlap_threshold = 0.20
    ```

    Bu, sınırlayıcı kutuların aynı nesne olarak kabul edilmesi için izin verilen yüzde örtüşme oranını tanımlar. 0.20, %20 örtüşmeyi ifade eder.

1. Shapely kullanarak örtüşmeyi hesaplamak için, sınırlayıcı kutuların Shapely çokgenlerine dönüştürülmesi gerekir. Bunu yapmak için aşağıdaki fonksiyonu ekleyin:

    ```python
    def create_polygon(prediction):
        scale_left = prediction.bounding_box.left
        scale_top = prediction.bounding_box.top
        scale_right = prediction.bounding_box.left + prediction.bounding_box.width
        scale_bottom = prediction.bounding_box.top + prediction.bounding_box.height
    
        return Polygon([(scale_left, scale_top), (scale_right, scale_top), (scale_right, scale_bottom), (scale_left, scale_bottom)])
    ```

    Bu, bir tahminin sınırlayıcı kutusunu kullanarak bir çokgen oluşturur.

1. Örtüşen nesneleri kaldırma mantığı, tüm sınırlayıcı kutuları karşılaştırmayı içerir. Eğer herhangi bir tahmin çiftinin sınırlayıcı kutuları eşik değerinden fazla örtüşüyorsa, tahminlerden biri silinir. Tüm tahminleri karşılaştırmak için, tahmin 1'i 2, 3, 4, vb. ile, ardından 2'yi 3, 4, vb. ile karşılaştırırsınız. Aşağıdaki kod bunu yapar:

    ```python
    to_delete = []

    for i in range(0, len(predictions)):
        polygon_1 = create_polygon(predictions[i])
    
        for j in range(i+1, len(predictions)):
            polygon_2 = create_polygon(predictions[j])
            overlap = polygon_1.intersection(polygon_2).area

            smallest_area = min(polygon_1.area, polygon_2.area)
    
            if overlap > (overlap_threshold * smallest_area):
                to_delete.append(predictions[i])
                break
    
    for d in to_delete:
        predictions.remove(d)

    print(f'Counted {len(predictions)} stock items')
    ```

    Örtüşme, Shapely'nin `Polygon.intersection` yöntemi kullanılarak hesaplanır ve bu yöntem örtüşmeyi içeren bir çokgen döndürür. Alan, bu çokgenden hesaplanır. Bu örtüşme eşiği mutlak bir değer değildir, ancak en küçük sınırlayıcı kutunun yüzde örtüşme eşiği aşılmaması için gereken alanı hesaplamak için kullanılır. Eğer örtüşme bu değeri aşarsa, tahmin silinmek üzere işaretlenir.

    Bir tahmin silinmek üzere işaretlendikten sonra tekrar kontrol edilmesine gerek yoktur, bu yüzden iç döngü bir sonraki tahmini kontrol etmek için kırılır. Bir liste üzerinde iterasyon yaparken öğeleri silemezsiniz, bu yüzden eşik değerinden fazla örtüşen sınırlayıcı kutular `to_delete` listesine eklenir ve ardından sonunda silinir.

    Son olarak stok sayımı konsola yazdırılır. Bu, stok seviyeleri düşükse bir IoT hizmetine gönderilebilir. Tüm bu kod, sınırlayıcı kutular çizilmeden önce çalışır, böylece oluşturulan görüntülerde örtüşme olmayan stok tahminlerini görürsünüz.

    > 💁 Bu, örtüşmeleri kaldırmak için çok basit bir yöntemdir; sadece örtüşen çiftteki ilk tahmini kaldırır. Üretim kodu için, burada daha fazla mantık eklemek isteyebilirsiniz, örneğin birden fazla nesne arasındaki örtüşmeleri dikkate almak veya bir sınırlayıcı kutunun başka bir kutunun içinde olup olmadığını kontrol etmek gibi.

1. Kamerayı bir raftaki stoklara doğrultarak uygulamayı çalıştırın. Çıktı, eşik değeri aşan örtüşmeleri olmayan sınırlayıcı kutuların sayısını gösterecektir. Tahminlerin görmezden gelindiğini görmek için `overlap_threshold` değerini ayarlamayı deneyin.

> 💁 Bu kodu [code-count/pi](../../../../../5-retail/lessons/2-check-stock-device/code-count/pi) veya [code-count/virtual-iot-device](../../../../../5-retail/lessons/2-check-stock-device/code-count/virtual-iot-device) klasöründe bulabilirsiniz.

😀 Stok sayacı programınız başarılı oldu!

---

**Feragatname**:  
Bu belge, AI çeviri hizmeti [Co-op Translator](https://github.com/Azure/co-op-translator) kullanılarak çevrilmiştir. Doğruluk için çaba göstersek de, otomatik çevirilerin hata veya yanlışlık içerebileceğini lütfen unutmayın. Belgenin orijinal dili, yetkili kaynak olarak kabul edilmelidir. Kritik bilgiler için profesyonel insan çevirisi önerilir. Bu çevirinin kullanımından kaynaklanan yanlış anlamalar veya yanlış yorumlamalardan sorumlu değiliz.