<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "9095c61445c2bca7245ef9b59a186a11",
  "translation_date": "2025-08-28T03:20:00+00:00",
  "source_file": "3-transport/lessons/3-visualize-location-data/README.md",
  "language_code": "tr"
}
-->
# Konum Verilerini Görselleştirme

![Bu dersin genel bir sketchnote görünümü](../../../../../translated_images/tr/lesson-13.a259db1485021be7d7c72e90842fbe0ab977529e8684c179b5fb1ea75e92b3ef.jpg)

> Sketchnote: [Nitya Narasimhan](https://github.com/nitya). Daha büyük bir versiyon için resme tıklayın.

Bu video, bu derste ele alınacak bir hizmet olan Azure Maps ile IoT'nin genel bir görünümünü sunar.

[![Azure Maps - Microsoft Azure Kurumsal Konum Platformu](https://img.youtube.com/vi/P5i2GFTtb2s/0.jpg)](https://www.youtube.com/watch?v=P5i2GFTtb2s)

> 🎥 Videoyu izlemek için yukarıdaki resme tıklayın

## Ders Öncesi Test

[Ders öncesi test](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/25)

## Giriş

Son derste, sensörlerinizden GPS verilerini alıp, sunucusuz kod kullanarak bulutta bir depolama konteynerine kaydetmeyi öğrendiniz. Şimdi bu noktaları bir Azure haritasında nasıl görselleştireceğinizi keşfedeceksiniz. Bir web sayfasında harita oluşturmayı, GeoJSON veri formatını ve yakalanan tüm GPS noktalarını haritanızda nasıl çizeceğinizi öğreneceksiniz.

Bu derste şunları ele alacağız:

* [Veri görselleştirme nedir](../../../../../3-transport/lessons/3-visualize-location-data)
* [Harita hizmetleri](../../../../../3-transport/lessons/3-visualize-location-data)
* [Azure Maps kaynağı oluşturma](../../../../../3-transport/lessons/3-visualize-location-data)
* [Bir web sayfasında harita gösterme](../../../../../3-transport/lessons/3-visualize-location-data)
* [GeoJSON formatı](../../../../../3-transport/lessons/3-visualize-location-data)
* [GeoJSON kullanarak GPS verilerini bir haritada çizme](../../../../../3-transport/lessons/3-visualize-location-data)

> 💁 Bu ders, az miktarda HTML ve JavaScript içerecek. HTML ve JavaScript kullanarak web geliştirme hakkında daha fazla bilgi edinmek isterseniz, [Web development for beginners](https://github.com/microsoft/Web-Dev-For-Beginners) kaynağına göz atabilirsiniz.

## Veri Görselleştirme Nedir

Veri görselleştirme, adından da anlaşılacağı gibi, verileri insanların daha kolay anlamasını sağlayacak şekilde görselleştirmektir. Genellikle grafikler ve tablolarla ilişkilendirilir, ancak verileri görsel olarak temsil eden herhangi bir yöntemdir. Bu, insanların veriyi daha iyi anlamasına ve kararlar almasına yardımcı olur.

Basit bir örnek alalım - çiftlik projesinde toprak nemi ölçümlerini yakalamıştınız. 1 Haziran 2021 tarihinde her saat başı yakalanan toprak nemi verilerinin bir tablosu şu şekilde olabilir:

| Tarih            | Okuma   |
| ----------------- | -------:|
| 01/06/2021 00:00 |     257 |
| 01/06/2021 01:00 |     268 |
| 01/06/2021 02:00 |     295 |
| 01/06/2021 03:00 |     305 |
| 01/06/2021 04:00 |     325 |
| 01/06/2021 05:00 |     359 |
| 01/06/2021 06:00 |     398 |
| 01/06/2021 07:00 |     410 |
| 01/06/2021 08:00 |     429 |
| 01/06/2021 09:00 |     451 |
| 01/06/2021 10:00 |     460 |
| 01/06/2021 11:00 |     452 |
| 01/06/2021 12:00 |     420 |
| 01/06/2021 13:00 |     408 |
| 01/06/2021 14:00 |     431 |
| 01/06/2021 15:00 |     462 |
| 01/06/2021 16:00 |     432 |
| 01/06/2021 17:00 |     402 |
| 01/06/2021 18:00 |     387 |
| 01/06/2021 19:00 |     360 |
| 01/06/2021 20:00 |     358 |
| 01/06/2021 21:00 |     354 |
| 01/06/2021 22:00 |     356 |
| 01/06/2021 23:00 |     362 |

Bu veriyi anlamak insan için zor olabilir. Anlamı olmayan bir sayı duvarı gibidir. Bu veriyi görselleştirmek için ilk adım olarak bir çizgi grafiğe dökebiliriz:

![Yukarıdaki verilerin çizgi grafiği](../../../../../translated_images/tr/chart-soil-moisture.fd6d9d0cdc0b5f75e78038ecb8945dfc84b38851359de99d84b16e3336d6d7c2.png)

Bu grafik, otomatik sulama sisteminin 450 nem okumasında açıldığı noktayı gösteren bir çizgi eklenerek daha da geliştirilebilir:

![450 nem okumasında bir çizgi ile toprak nemi grafiği](../../../../../translated_images/tr/chart-soil-moisture-relay.fbb391236d34a64d0abf1df396e9197e0a24df14150620b9cc820a64a55c9326.png)

Bu grafik, toprak nemi seviyelerinin ne olduğunu ve sulama sisteminin açıldığı noktaları çok hızlı bir şekilde gösterir.

Grafikler, veriyi görselleştirmek için tek araç değildir. Hava durumu izleyen IoT cihazları, hava koşullarını bulut simgesi, yağmur bulutu gibi sembollerle görselleştiren web veya mobil uygulamalara sahip olabilir. Veriyi görselleştirmek için ciddi ve eğlenceli birçok yöntem vardır.

✅ Verilerin görselleştirildiği yöntemleri düşünün. Hangi yöntemler en netti ve karar vermenizi en hızlı şekilde sağladı?

En iyi görselleştirmeler, insanların hızlı kararlar almasını sağlar. Örneğin, endüstriyel makinelerden gelen tüm okuma türlerini gösteren bir gösterge duvarı işlenmesi zor olabilir, ancak bir şeyler ters gittiğinde yanıp sönen kırmızı bir ışık bir insanın karar vermesini sağlar. Bazen en iyi görselleştirme yanıp sönen bir ışık olabilir!

GPS verileriyle çalışırken, en net görselleştirme veriyi bir haritada çizmek olabilir. Örneğin, teslimat kamyonlarını gösteren bir harita, bir işleme tesisindeki çalışanların kamyonların ne zaman geleceğini görmesine yardımcı olabilir. Bu harita, yalnızca kamyonların mevcut konumlarını değil, aynı zamanda bir kamyonun içeriği hakkında bilgi verirse, tesis çalışanları buna göre plan yapabilir - örneğin, yakınlarda bir soğutmalı kamyon görürlerse buzdolabında yer hazırlayabilirler.

## Harita Hizmetleri

Haritalarla çalışmak ilginç bir egzersizdir ve Bing Maps, Leaflet, Open Street Maps ve Google Maps gibi birçok seçenek vardır. Bu derste, [Azure Maps](https://azure.microsoft.com/services/azure-maps/?WT.mc_id=academic-17441-jabenn) hakkında bilgi edinecek ve GPS verilerinizi nasıl görüntüleyebileceğinizi öğreneceksiniz.

![Azure Maps logosu](../../../../../translated_images/tr/azure-maps-logo.35d01dcfbd81fe6140e94257aaa1538f785a58c91576d14e0ebe7a2f6c694b99.png)

Azure Maps, "coğrafi bağlamı web ve mobil uygulamalara sağlamak için taze harita verilerini kullanan bir dizi coğrafi hizmet ve SDK'dır." Geliştiricilere, önerilen trafik rotaları sağlama, trafik olayları hakkında bilgi verme, iç mekan navigasyonu, arama yetenekleri, yükseklik bilgisi, hava durumu hizmetleri ve daha fazlasını yapabilen güzel, etkileşimli haritalar oluşturmak için araçlar sunar.

✅ Bazı [harita kodu örneklerini](https://docs.microsoft.com/samples/browse?WT.mc_id=academic-17441-jabenn&products=azure-maps) deneyin

Haritaları boş bir tuval, döşemeler, uydu görüntüleri, yolların üstüne bindirilmiş uydu görüntüleri, çeşitli gri tonlamalı haritalar, yükseklik göstermek için gölgeli kabartma haritaları, gece görünümü haritaları ve yüksek kontrastlı harita olarak görüntüleyebilirsiniz. Haritalarınızı [Azure Event Grid](https://azure.microsoft.com/services/event-grid/?WT.mc_id=academic-17441-jabenn) ile entegre ederek gerçek zamanlı güncellemeler alabilirsiniz. Haritalarınızın davranışını ve görünümünü kontrol etmek için haritanın sıkıştırma, sürükleme ve tıklama gibi olaylara tepki vermesini sağlayan çeşitli kontrolleri etkinleştirebilirsiniz. Haritanızın görünümünü kontrol etmek için baloncuklar, çizgiler, çokgenler, ısı haritaları ve daha fazlasını içeren katmanlar ekleyebilirsiniz. Hangi harita stilini uygulayacağınız, seçtiğiniz SDK'ya bağlıdır.

Azure Maps API'lerine [REST API](https://docs.microsoft.com/javascript/api/azure-maps-rest/?WT.mc_id=academic-17441-jabenn&view=azure-maps-typescript-latest), [Web SDK](https://docs.microsoft.com/azure/azure-maps/how-to-use-map-control?WT.mc_id=academic-17441-jabenn) veya bir mobil uygulama geliştiriyorsanız [Android SDK](https://docs.microsoft.com/azure/azure-maps/how-to-use-android-map-control-library?WT.mc_id=academic-17441-jabenn&pivots=programming-language-java-android) kullanarak erişebilirsiniz.

Bu derste, bir harita çizmek ve sensörünüzün GPS konumlarının yolunu göstermek için web SDK'sını kullanacaksınız.

## Azure Maps Kaynağı Oluşturma

İlk adımınız bir Azure Maps hesabı oluşturmaktır.

### Görev - Azure Maps kaynağı oluşturma

1. `gps-sensor` kaynak grubunuzda bir Azure Maps kaynağı oluşturmak için Terminal veya Komut İsteminden aşağıdaki komutu çalıştırın:

    ```sh
    az maps account create --name gps-sensor \
                           --resource-group gps-sensor \
                           --accept-tos \
                           --sku S1
    ```

    Bu, `gps-sensor` adlı bir Azure Maps kaynağı oluşturacaktır. Kullanılan katman `S1` olup, ücretsiz bir dizi çağrı içeren bir dizi özellik sunan ücretli bir katmandır.

    > 💁 Azure Maps kullanmanın maliyetini görmek için [Azure Maps fiyatlandırma sayfasına](https://azure.microsoft.com/pricing/details/azure-maps/?WT.mc_id=academic-17441-jabenn) göz atın.

1. Harita kaynağı için bir API anahtarına ihtiyacınız olacak. Bu anahtarı almak için aşağıdaki komutu kullanın:

    ```sh
    az maps account keys list --name gps-sensor \
                              --resource-group gps-sensor \
                              --output table
    ```

    `PrimaryKey` değerini kopyalayın.

## Bir Web Sayfasında Harita Gösterme

Şimdi bir sonraki adımı atabilir ve haritanızı bir web sayfasında görüntüleyebilirsiniz. Küçük web uygulamanız için yalnızca bir `html` dosyası kullanacağız; unutmayın ki üretim veya ekip ortamında web uygulamanız muhtemelen daha fazla hareketli parçaya sahip olacaktır!

### Görev - bir web sayfasında harita gösterme

1. Yerel bilgisayarınızda bir klasörde `index.html` adlı bir dosya oluşturun. Haritayı tutacak HTML işaretlemesini ekleyin:

    ```html
    <html>
    <head>
        <style>
            #myMap {
                width:100%;
                height:100%;
            }
        </style>
    </head>
    
    <body onload="init()">
        <div id="myMap"></div>
    </body>
    </html>
    ```

    Harita, `myMap` `div` içinde yüklenecektir. Birkaç stil, sayfanın genişliğini ve yüksekliğini kaplamasına izin verir.

    > 🎓 Bir `div`, bir web sayfasının adlandırılabilir ve stillendirilebilir bir bölümüdür.

1. Açılış `<head>` etiketinin altına, harita görüntüsünü kontrol etmek için bir harici stil sayfası ve davranışını yönetmek için Web SDK'dan bir harici betik ekleyin:

    ```html
    <link rel="stylesheet" href="https://atlas.microsoft.com/sdk/javascript/mapcontrol/2/atlas.min.css" type="text/css" />
    <script src="https://atlas.microsoft.com/sdk/javascript/mapcontrol/2/atlas.min.js"></script>
    ```

    Bu stil sayfası, haritanın nasıl göründüğüne dair ayarları içerir ve betik dosyası haritayı yüklemek için kod içerir. Bu kodu eklemek, C++ başlık dosyalarını dahil etmeye veya Python modüllerini içe aktarmaya benzer.

1. Bu betiğin altına, haritayı başlatmak için bir betik bloğu ekleyin.

    ```javascript
    <script type='text/javascript'>
        function init() {
            var map = new atlas.Map('myMap', {
                center: [-122.26473, 47.73444],
                zoom: 12,
                authOptions: {
                    authType: "subscriptionKey",
                    subscriptionKey: "<subscription_key>",

                }
            });
        }
    </script>
    ```

    `<subscription_key>` kısmını Azure Maps hesabınızın API anahtarıyla değiştirin.

    `index.html` sayfanızı bir web tarayıcısında açarsanız, bir harita yüklendiğini ve Seattle bölgesine odaklandığını görmelisiniz.

    ![Washington Eyaleti, ABD'deki bir şehir olan Seattle'ı gösteren bir harita](../../../../../translated_images/tr/map-image.8fb2c53eb23ef39c1c0a4410a5282e879b3b452b707eb066ff04c5488d3d72b7.png)

    ✅ Harita görüntünüzü değiştirmek için zoom ve merkez parametreleriyle deney yapın. Haritanın merkezini yeniden ayarlamak için verilerinizin enlem ve boylamına karşılık gelen farklı koordinatlar ekleyebilirsiniz.

> 💁 Web uygulamalarıyla yerel olarak çalışmanın daha iyi bir yolu [http-server](https://www.npmjs.com/package/http-server) kurmaktır. Bu aracı kullanmadan önce [node.js](https://nodejs.org/) ve [npm](https://www.npmjs.com/) kurulu olmalıdır. Bu araçlar kurulduktan sonra, `index.html` dosyanızın bulunduğu konuma gidip `http-server` yazabilirsiniz. Web uygulaması yerel bir web sunucusunda [http://127.0.0.1:8080/](http://127.0.0.1:8080/) adresinde açılacaktır.

## GeoJSON Formatı

Web uygulamanızın haritayı görüntülediği yer artık hazır olduğuna göre, depolama hesabınızdan GPS verilerini çıkarıp haritanın üzerine bir katman olarak işaretçilerle görüntülemeniz gerekiyor. Bunu yapmadan önce, Azure Maps tarafından gereksinim duyulan [GeoJSON](https://wikipedia.org/wiki/GeoJSON) formatına bir göz atalım.

[GeoJSON](https://geojson.org/), coğrafi verileri işlemek için özel bir formatlama ile tasarlanmış açık bir JSON standart spesifikasyonudur. Örnek verileri test ederek [geojson.io](https://geojson.io) kullanarak öğrenebilir ve GeoJSON dosyalarını hata ayıklamak için bu aracı kullanabilirsiniz.

Örnek GeoJSON verisi şu şekilde görünür:

```json
{
  "type": "FeatureCollection",
  "features": [
    {
      "type": "Feature",
      "geometry": {
        "type": "Point",
        "coordinates": [
          -2.10237979888916,
          57.164918677004714
        ]
      }
    }
  ]
}
```

Özellikle dikkat edilmesi gereken, verilerin bir `FeatureCollection` içinde bir `Feature` olarak nasıl iç içe geçtiğidir. Bu nesne içinde, `geometry` ve `coordinates` bulunur; bunlar enlem ve boylamı belirtir.

✅ GeoJSON oluştururken, nesnedeki `latitude` ve `longitude` sırasına dikkat edin, aksi takdirde noktalarınız olması gereken yerde görünmez! GeoJSON, noktalar için veriyi `lon,lat` sırasıyla bekler, `lat,lon` değil.

`Geometry` farklı türlere sahip olabilir, örneğin tek bir nokta veya bir çokgen. Bu örnekte, iki koordinat belirtilmiş bir nokta vardır: boylam ve enlem.
✅ Azure Maps, standart GeoJSON'u ve daireler ile diğer geometrileri çizme yeteneği gibi [gelişmiş özellikleri](https://docs.microsoft.com/azure/azure-maps/extend-geojson?WT.mc_id=academic-17441-jabenn) destekler.

## GeoJSON kullanarak GPS verilerini bir haritada gösterme

Artık önceki derste oluşturduğunuz depolamadan veri almaya hazırsınız. Hatırlatma olarak, bu veriler blob depolamada bir dizi dosya olarak saklanır, bu nedenle dosyaları almanız ve Azure Maps'in verileri kullanabilmesi için bunları ayrıştırmanız gerekir.

### Görev - depolamayı bir web sayfasından erişilebilir hale getirme

Depolamanıza veri almak için bir çağrı yaptığınızda, tarayıcınızın konsolunda hatalar görürseniz şaşırmayın. Bunun nedeni, bu depolamanın verilerini harici web uygulamalarının okuyabilmesi için [CORS](https://developer.mozilla.org/docs/Web/HTTP/CORS) izinlerini ayarlamanız gerektiğidir.

> 🎓 CORS, "Cross-Origin Resource Sharing" (Kaynaklar Arası Paylaşım) anlamına gelir ve genellikle güvenlik nedenleriyle Azure'da açıkça ayarlanması gerekir. Beklemediğiniz sitelerin verilerinize erişmesini engeller.

1. CORS'u etkinleştirmek için aşağıdaki komutu çalıştırın:

    ```sh
    az storage cors add --methods GET \
                        --origins "*" \
                        --services b \
                        --account-name <storage_name> \
                        --account-key <key1>
    ```

    `<storage_name>` ile depolama hesabınızın adını değiştirin. `<key1>` ile depolama hesabınızın hesap anahtarını değiştirin.

    Bu komut, herhangi bir web sitesinin (joker karakter `*` herhangi bir site anlamına gelir) depolama hesabınızdan veri almak için bir *GET* isteği yapmasına izin verir. `--services b` yalnızca bloblar için bu ayarı uygulamak anlamına gelir.

### Görev - GPS verilerini depolamadan yükleme

1. `init` fonksiyonunun tüm içeriğini aşağıdaki kodla değiştirin:

    ```javascript
    fetch("https://<storage_name>.blob.core.windows.net/gps-data/?restype=container&comp=list")
        .then(response => response.text())
        .then(str => new window.DOMParser().parseFromString(str, "text/xml"))
        .then(xml => {
            let blobList = Array.from(xml.querySelectorAll("Url"));
                blobList.forEach(async blobUrl => {
                    loadJSON(blobUrl.innerHTML)                
        });
    })
    .then( response => {
        map = new atlas.Map('myMap', {
            center: [-122.26473, 47.73444],
            zoom: 14,
            authOptions: {
                authType: "subscriptionKey",
                subscriptionKey: "<subscription_key>",
    
            }
        });
        map.events.add('ready', function () {
            var source = new atlas.source.DataSource();
            map.sources.add(source);
            map.layers.add(new atlas.layer.BubbleLayer(source));
            source.add(features);
        })
    })
    ```

    `<storage_name>` ile depolama hesabınızın adını değiştirin. `<subscription_key>` ile Azure Maps hesabınızın API anahtarını değiştirin.

    Burada birkaç şey oluyor. İlk olarak, kod blob konteynerinizden GPS verilerinizi depolama hesabınızın adını kullanarak oluşturulan bir URL uç noktası aracılığıyla alır. Bu URL, `gps-data`dan veri alır, kaynak türünün bir konteyner olduğunu (`restype=container`) belirtir ve tüm bloblar hakkında bilgi listeler. Bu liste blobların kendisini döndürmez, ancak blob verilerini yüklemek için kullanılabilecek bir URL döndürür.

    > 💁 Bu URL'yi tarayıcınıza koyarak konteynerinizdeki tüm blobların detaylarını görebilirsiniz. Her öğe, tarayıcınızda blobun içeriğini görmek için de yüklenebilecek bir `Url` özelliğine sahip olacaktır.

    Bu kod daha sonra her bir blobu yükler, bir `loadJSON` fonksiyonunu çağırır ve bu fonksiyon bir sonraki adımda oluşturulacaktır. Ardından harita kontrolünü oluşturur ve `ready` olayına kod ekler. Bu olay, harita web sayfasında görüntülendiğinde çağrılır.

    Ready olayı, daha sonra doldurulacak GeoJSON verilerini içeren bir Azure Maps veri kaynağı oluşturur. Bu veri kaynağı, haritada GeoJSON'daki her bir noktanın merkezinde bir dizi daire olan bir baloncuk katmanı oluşturmak için kullanılır.

1. `init` fonksiyonunun altına, script bloğunuza `loadJSON` fonksiyonunu ekleyin:

    ```javascript
    var map, features;

    function loadJSON(file) {
        var xhr = new XMLHttpRequest();
        features = [];
        xhr.onreadystatechange = function () {
            if (xhr.readyState === XMLHttpRequest.DONE) {
                if (xhr.status === 200) {
                    gps = JSON.parse(xhr.responseText)
                    features.push(
                        new atlas.data.Feature(new atlas.data.Point([parseFloat(gps.gps.lon), parseFloat(gps.gps.lat)]))
                    )
                }
            }
        };
        xhr.open("GET", file, true);
        xhr.send();
    }    
    ```

    Bu fonksiyon, JSON verilerini ayrıştırmak ve bunları GeoJSON olarak uzunluk ve enlem koordinatları şeklinde okunabilir hale getirmek için fetch rutini tarafından çağrılır. 
    Ayrıştırıldıktan sonra, veriler bir GeoJSON `Feature` olarak ayarlanır. Harita başlatılır ve verilerinizin izlediği yolun etrafında küçük baloncuklar görünür:

1. HTML sayfasını tarayıcınızda yükleyin. Harita yüklenecek, ardından depolamadan tüm GPS verileri yüklenecek ve haritada gösterilecektir.

    ![Seattle yakınlarındaki Saint Edward State Park'ın bir haritası, parkın kenarındaki yolu gösteren daireler](../../../../../translated_images/tr/map-path.896832e72dc696ffe20650e4051027d4855442d955f93fdbb80bb417ca8a406f.png)

> 💁 Bu kodu [code](../../../../../3-transport/lessons/3-visualize-location-data/code) klasöründe bulabilirsiniz.

---

## 🚀 Meydan Okuma

Statik verileri haritada işaretleyiciler olarak göstermek güzel. Zaman damgalı JSON dosyalarını kullanarak işaretleyicilerin yolunu zaman içinde göstermek için bu web uygulamasını animasyon ekleyerek geliştirebilir misiniz? İşte haritalarda animasyon kullanımıyla ilgili [bazı örnekler](https://azuremapscodesamples.azurewebsites.net/).

## Ders sonrası test

[Ders sonrası test](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/26)

## Gözden Geçirme ve Kendi Kendine Çalışma

Azure Maps, IoT cihazlarıyla çalışmak için özellikle kullanışlıdır.

* [Microsoft dokümanlarındaki Azure Maps dokümantasyonu](https://docs.microsoft.com/azure/azure-maps/tutorial-iot-hub-maps?WT.mc_id=academic-17441-jabenn) üzerinde bazı kullanım alanlarını araştırın.
* [Microsoft Learn'deki Azure Maps ile ilk rota bulma uygulamanızı oluşturun](https://docs.microsoft.com/learn/modules/create-your-first-app-with-azure-maps/?WT.mc_id=academic-17441-jabenn) adlı kendi kendine öğrenme modülü ile harita yapımı ve yol noktaları hakkındaki bilginizi derinleştirin.

## Ödev

[Uygulamanızı dağıtın](assignment.md)

---

**Feragatname**:  
Bu belge, AI çeviri hizmeti [Co-op Translator](https://github.com/Azure/co-op-translator) kullanılarak çevrilmiştir. Doğruluk için çaba göstersek de, otomatik çevirilerin hata veya yanlışlıklar içerebileceğini lütfen unutmayın. Belgenin orijinal dili, yetkili kaynak olarak kabul edilmelidir. Kritik bilgiler için profesyonel insan çevirisi önerilir. Bu çevirinin kullanımından kaynaklanan yanlış anlamalar veya yanlış yorumlamalar için sorumluluk kabul etmiyoruz.