# Coğrafi Çitler

![Bu dersin genel bir sketchnote özeti](../../../../../translated_images/tr/lesson-14.63980c5150ae3c15.webp)

> Sketchnote: [Nitya Narasimhan](https://github.com/nitya). Daha büyük bir versiyon için resme tıklayın.

Bu video, coğrafi çitlerin ne olduğunu ve Azure Maps'te nasıl kullanılacağını anlatıyor. Bu dersin konuları:

[![Microsoft Developer IoT şovundan Azure Maps ile Coğrafi Çitler](https://img.youtube.com/vi/nsrgYhaYNVY/0.jpg)](https://www.youtube.com/watch?v=nsrgYhaYNVY)

> 🎥 Videoyu izlemek için yukarıdaki resme tıklayın

## Ders Öncesi Test

[Ders öncesi test](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/27)

## Giriş

Son 3 derste, çiftliğinizden işleme merkezine ürün taşıyan kamyonların konumunu IoT kullanarak takip ettiniz. GPS verilerini yakaladınız, buluta gönderip depoladınız ve harita üzerinde görselleştirdiniz. Tedarik zincirinizin verimliliğini artırmanın bir sonraki adımı, bir kamyon işleme merkezine yaklaşırken bir uyarı almak olacaktır. Böylece, araç geldiğinde boşaltma ekibi forkliftler ve diğer ekipmanlarla hazır olabilir. Bu şekilde hızlı bir şekilde boşaltma yapılabilir ve kamyon ile sürücünün bekleme süresi için ödeme yapmanız gerekmez.

Bu derste, coğrafi çitler hakkında bilgi edineceksiniz - işleme merkezine 2 km'lik bir sürüş mesafesi gibi tanımlanmış coğrafi bölgeler. Ayrıca GPS koordinatlarının bir coğrafi çitin içinde mi yoksa dışında mı olduğunu test etmeyi öğreneceksiniz. Böylece GPS sensörünüzün bir alana ulaşıp ulaşmadığını veya bir alandan ayrıldığını görebilirsiniz.

Bu derste şunları ele alacağız:

* [Coğrafi çitler nedir](../../../../../3-transport/lessons/4-geofences)
* [Bir coğrafi çit tanımlama](../../../../../3-transport/lessons/4-geofences)
* [Noktaları bir coğrafi çite karşı test etme](../../../../../3-transport/lessons/4-geofences)
* [Sunucusuz koddan coğrafi çitler kullanma](../../../../../3-transport/lessons/4-geofences)

> 🗑 Bu proje için son ders, bu nedenle bu dersi ve ödevi tamamladıktan sonra bulut hizmetlerinizi temizlemeyi unutmayın. Ödevi tamamlamak için hizmetlere ihtiyacınız olacak, bu yüzden önce ödevi tamamladığınızdan emin olun.
>
> Gerekirse [projenizi temizleme rehberine](../../../clean-up.md) başvurabilirsiniz.

## Coğrafi Çitler Nedir?

Coğrafi çit, gerçek dünyadaki bir coğrafi bölge için sanal bir sınırdır. Coğrafi çitler, bir nokta ve bir yarıçap olarak tanımlanan daireler (örneğin bir binanın etrafında 100m genişliğinde bir daire) veya bir okul bölgesi, şehir sınırları, üniversite veya ofis kampüsü gibi bir alanı kapsayan çokgenler olabilir.

![Microsoft şirket mağazası etrafında dairesel bir coğrafi çit ve Microsoft batı kampüsü etrafında çokgen bir coğrafi çit örnekleri](../../../../../translated_images/tr/geofence-examples.172fbc534665769f.webp)

> 💁 Belki de farkında olmadan coğrafi çitler kullanmış olabilirsiniz. iOS hatırlatıcılar uygulaması veya Google Keep'te bir konuma dayalı hatırlatıcı ayarladıysanız, bir coğrafi çit kullanmışsınızdır. Bu uygulamalar, verilen konuma dayalı bir coğrafi çit oluşturur ve telefonunuz coğrafi çite girdiğinde sizi uyarır.

Bir aracın bir coğrafi çitin içinde mi yoksa dışında mı olduğunu bilmek istemenizin birçok nedeni vardır:

* Boşaltma hazırlığı - bir aracın sahaya geldiğine dair bir bildirim almak, ekibin aracı boşaltmaya hazır olmasını sağlar ve araç bekleme süresini azaltır. Bu, bir sürücünün daha az bekleme süresiyle bir günde daha fazla teslimat yapmasını sağlayabilir.
* Vergi uyumu - Yeni Zelanda gibi bazı ülkeler, yalnızca kamu yollarında sürüş sırasında araç ağırlığına dayalı olarak dizel araçlar için yol vergisi alır. Coğrafi çitler kullanarak kamu yollarında sürülen kilometreyi, çiftlikler veya ağaç kesim alanları gibi özel yollarla karşılaştırabilirsiniz.
* Hırsızlık izleme - bir araç yalnızca belirli bir alanda kalmalıysa, örneğin bir çiftlikte, ve coğrafi çitten çıkarsa, çalınmış olabilir.
* Konum uyumu - bir iş sahasının, çiftliğin veya fabrikanın bazı bölümleri belirli araçlar için yasak olabilir. Örneğin, yapay gübre ve pestisit taşıyan araçların organik ürün yetiştirilen tarlalardan uzak tutulması gerekebilir. Bir coğrafi çite girilirse, araç uyum dışıdır ve sürücü bilgilendirilebilir.

✅ Coğrafi çitler için başka kullanım alanları düşünebilir misiniz?

Son derste GPS verilerini görselleştirmek için kullandığınız Azure Maps hizmeti, coğrafi çitler tanımlamanıza ve ardından bir noktanın coğrafi çitin içinde mi yoksa dışında mı olduğunu test etmenize olanak tanır.

## Bir Coğrafi Çit Tanımlama

Coğrafi çitler, önceki derste haritaya eklenen noktalarla aynı şekilde GeoJSON kullanılarak tanımlanır. Bu durumda, `Point` değerlerinden oluşan bir `FeatureCollection` yerine, bir `Polygon` içeren bir `FeatureCollection` olacaktır.

```json
{
   "type": "FeatureCollection",
   "features": [
     {
       "type": "Feature",
       "geometry": {
         "type": "Polygon",
         "coordinates": [
           [
             [
               -122.13393688201903,
               47.63829579223815
             ],
             [
               -122.13389128446579,
               47.63782047131512
             ],
             [
               -122.13240802288054,
               47.63783312249837
             ],
             [
               -122.13238388299942,
               47.63829037035086
             ],
             [
               -122.13393688201903,
               47.63829579223815
             ]
           ]
         ]
       },
       "properties": {
         "geometryId": "1"
       }
     }
   ]
}
```

Çokgendeki her nokta, bir dizideki bir uzunluk ve enlem çifti olarak tanımlanır ve bu noktalar, `coordinates` olarak ayarlanan bir dizide bulunur. Önceki derste bir `Point` için `coordinates`, enlem ve boylam içeren bir dizi idi. Bir `Polygon` için ise, uzunluk ve enlem içeren dizilerden oluşan bir dizidir.

> 💁 Unutmayın, GeoJSON noktalar için `boylam, enlem` kullanır, `enlem, boylam` değil.

Çokgen koordinatları dizisi, çokgendeki nokta sayısından her zaman 1 fazla girişe sahiptir. Son giriş, çokgeni kapatmak için ilk girişle aynıdır. Örneğin, bir dikdörtgen için 5 nokta olacaktır.

![Koordinatları olan bir dikdörtgen](../../../../../translated_images/tr/polygon-points.302193da381cb415.webp)

Yukarıdaki resimde bir dikdörtgen var. Çokgen koordinatları, sol üstteki 47,-122'den başlar, sonra sağa 47,-121'e gider, sonra aşağıya 46,-121'e, sonra sola 46,-122'ye ve sonra başlangıç noktasına, yani 47,-122'ye geri döner. Bu, çokgene 5 nokta verir - sol üst, sağ üst, sağ alt, sol alt ve sonra sol üst noktayı kapatmak için.

✅ Evinizin veya okulunuzun etrafında bir GeoJSON çokgeni oluşturmaya çalışın. [GeoJSON.io](https://geojson.io) gibi bir araç kullanabilirsiniz.

### Görev - Bir Coğrafi Çit Tanımlama

Azure Maps'te bir coğrafi çit kullanmak için önce Azure Maps hesabınıza yüklenmesi gerekir. Yüklendikten sonra, coğrafi çite karşı bir noktayı test etmek için kullanabileceğiniz benzersiz bir kimlik alırsınız. Coğrafi çitleri Azure Maps'e yüklemek için haritalar web API'sini kullanmanız gerekir. Azure Maps web API'sini [curl](https://curl.se) adlı bir araç kullanarak çağırabilirsiniz.

> 🎓 Curl, web uç noktalarına karşı istekler yapmak için bir komut satırı aracıdır.

1. Linux, macOS veya Windows 10'un yeni bir sürümünü kullanıyorsanız, muhtemelen curl zaten yüklüdür. Curl'ün yüklü olup olmadığını kontrol etmek için terminalinizden veya komut satırından aşağıdaki komutu çalıştırın:

    ```sh
    curl --version
    ```

    Curl için sürüm bilgilerini görmüyorsanız, [curl indirme sayfasından](https://curl.se/download.html) yüklemeniz gerekir.

    > 💁 Postman konusunda deneyimliyseniz, tercihinize bağlı olarak onu kullanabilirsiniz.

1. Bir çokgen içeren bir GeoJSON dosyası oluşturun. Bunu GPS sensörünüzle test edeceğiniz için, mevcut konumunuzun etrafında bir çokgen oluşturun. Bunu, yukarıda verilen GeoJSON örneğini manuel olarak düzenleyerek veya [GeoJSON.io](https://geojson.io) gibi bir araç kullanarak yapabilirsiniz.

    GeoJSON, `Polygon` türünde bir `geometry` içeren bir `FeatureCollection` içermelidir.

    Ayrıca, `geometry` öğesiyle aynı seviyede bir `properties` öğesi eklemeniz **GEREKİR** ve bu öğe bir `geometryId` içermelidir:

    ```json
    "properties": {
        "geometryId": "1"
    }
    ```

    [GeoJSON.io](https://geojson.io) kullanıyorsanız, bu öğeyi boş `properties` öğesine manuel olarak eklemeniz gerekecektir. Bunu, JSON dosyasını indirdikten sonra veya uygulamadaki JSON düzenleyicisinde yapabilirsiniz.

    Bu `geometryId` bu dosyada benzersiz olmalıdır. Birden fazla coğrafi çiti, aynı GeoJSON dosyasındaki bir `FeatureCollection` içindeki birden fazla `Feature` olarak yükleyebilirsiniz. Ancak her birinin farklı bir `geometryId` olması gerekir. Çokgenler, farklı bir dosyadan farklı bir zamanda yüklendiyse aynı `geometryId`ye sahip olabilir.

1. Bu dosyayı `geofence.json` olarak kaydedin ve terminalinizde veya konsolunuzda kaydedildiği yere gidin.

1. Coğrafi Çit oluşturmak için aşağıdaki curl komutunu çalıştırın:

    ```sh
    curl --request POST 'https://atlas.microsoft.com/mapData/upload?api-version=1.0&dataFormat=geojson&subscription-key=<subscription_key>' \
         --header 'Content-Type: application/json' \
         --include \
         --data @geofence.json
    ```

    URL'deki `<subscription_key>` öğesini Azure Maps hesabınızın API anahtarıyla değiştirin.

    URL, `https://atlas.microsoft.com/mapData/upload` API'si aracılığıyla harita verilerini yüklemek için kullanılır. Çağrı, hangi Azure Maps API'sinin kullanılacağını belirtmek için bir `api-version` parametresi içerir. Bu, API'nin zaman içinde değişmesine ancak geriye dönük uyumluluğu korumasına olanak tanır. Yüklenen veri formatı `geojson` olarak ayarlanır.

    Bu, yükleme API'sine POST isteğini çalıştırır ve `location` adlı bir başlık içeren yanıt başlıklarının bir listesini döndürür.

    ```output
    content-type: application/json
    location: https://us.atlas.microsoft.com/mapData/operations/1560ced6-3a80-46f2-84b2-5b1531820eab?api-version=1.0
    x-ms-azuremaps-region: West US 2
    x-content-type-options: nosniff
    strict-transport-security: max-age=31536000; includeSubDomains
    x-cache: CONFIG_NOCACHE
    date: Sat, 22 May 2021 21:34:57 GMT
    content-length: 0
    ```

    > 🎓 Bir web uç noktasını çağırırken, çağrıya `?` ardından `key=value` olarak anahtar-değer çiftleri ekleyerek parametreler geçirebilirsiniz. Anahtar-değer çiftlerini `&` ile ayırabilirsiniz.

1. Azure Maps bunu hemen işlemez, bu nedenle yükleme isteğinin tamamlanıp tamamlanmadığını kontrol etmek için `location` başlığında verilen URL'yi kullanmanız gerekir. Bu konuma bir GET isteği yaparak durumu görebilirsiniz. Azure Maps hesabınızın API anahtarını ekleyerek `location` URL'sinin sonuna `&subscription-key=<subscription_key>` eklemeniz gerekir. `<subscription_key>` öğesini Azure Maps hesabınızın API anahtarıyla değiştirin ve aşağıdaki komutu çalıştırın:

    ```sh
    curl --request GET '<location>&subscription-key=<subscription_key>'
    ```

    `<location>` öğesini `location` başlığının değeriyle ve `<subscription_key>` öğesini Azure Maps hesabınızın API anahtarıyla değiştirin.

1. Yanıttaki `status` değerini kontrol edin. Eğer `Succeeded` değilse, bir dakika bekleyin ve tekrar deneyin.

1. Durum `Succeeded` olarak döndüğünde, yanıttaki `resourceLocation` öğesine bakın. Bu, GeoJSON nesnesi için benzersiz kimlik (UDID) ayrıntılarını içerir. UDID, `metadata/` öğesinden sonra gelen ve `api-version` öğesini içermeyen değerdir. Örneğin, `resourceLocation` şu şekilde olsaydı:

    ```json
    {
      "resourceLocation": "https://us.atlas.microsoft.com/mapData/metadata/7c3776eb-da87-4c52-ae83-caadf980323a?api-version=1.0"
    }
    ```

    UDID `7c3776eb-da87-4c52-ae83-caadf980323a` olurdu.

    Bu UDID'nin bir kopyasını saklayın, çünkü coğrafi çiti test etmek için buna ihtiyacınız olacak.

## Noktaları Bir Coğrafi Çite Karşı Test Etme

Çokgen Azure Maps'e yüklendikten sonra, bir noktanın coğrafi çitin içinde mi yoksa dışında mı olduğunu test edebilirsiniz. Bunu, coğrafi çitin UDID'sini ve test edilecek noktanın enlem ve boylamını geçirerek bir web API isteği yaparak gerçekleştirirsiniz.

Bu isteği yaparken, `searchBuffer` adlı bir değer de geçirebilirsiniz. Bu, sonuçları döndürürken Maps API'nin ne kadar hassas olması gerektiğini belirtir. Bunun nedeni, GPS'in mükemmel bir şekilde doğru olmaması ve bazen konumların metrelerce veya daha fazla sapma gösterebilmesidir. Arama tamponu için varsayılan değer 50m'dir, ancak 0m ile 500m arasında değerler ayarlayabilirsiniz.

API çağrısından dönen sonuçlarda, sonuçlardan biri coğrafi çitin kenarına en yakın noktaya ölçülen bir `distance` değeridir. Bu değer, nokta coğrafi çitin dışındaysa pozitif, içindeyse negatif olur. Bu mesafe arama tamponundan küçükse, gerçek mesafe metre cinsinden döndürülür. Aksi takdirde değer 999 veya -999 olur. 999, noktanın coğrafi çitin dışında arama tamponundan daha fazla olduğu anlamına gelir. -999, noktanın coğrafi çitin içinde arama tamponundan daha fazla olduğu anlamına gelir.

![Etrafında 50m arama tamponu olan bir coğrafi çit](../../../../../translated_images/tr/search-buffer-and-distance.e6a79af3898183c7.webp)

Yukarıdaki resimde, coğrafi çitin etrafında 50m arama tamponu var.

* Coğrafi çitin merkezindeki bir nokta, arama tamponunun içinde, mesafesi **-999**.
* Arama tamponunun dışında olan bir nokta, mesafesi **999**.
* Coğrafi çitin içinde ve arama tamponunun içinde olan bir nokta, coğrafi çitten 6m uzaklıkta, mesafesi **6m**.
* Coğrafi çitin dışında ve arama tamponunun içinde olan bir nokta, coğrafi çitten 39m uzaklıkta, mesafesi **39m**.

Coğrafi çitin kenarına olan mesafeyi bilmek ve bunu araç konumuna dayalı kararlar alırken diğer bilgilerle, örneğin diğer GPS okumaları, hız ve yol verileriyle birleştirmek önemlidir.

Örneğin, bir aracın bir coğrafi çitin yanından geçen bir yolda ilerlediğini gösteren GPS okumalarını hayal edin. Eğer tek bir GPS değeri yanlışsa ve aracı coğrafi çitin içinde gösteriyorsa, bu değer görmezden gelinebilir.

![Microsoft kampüsünün yanından geçen 520 yolunda bir aracın GPS izi, yol boyunca GPS okumaları, ancak bir tanesi kampüste, bir coğrafi çitin içinde](../../../../../translated_images/tr/geofence-crossing-inaccurate-gps.6a3ed911202ad9ca.webp)
Yukarıdaki görselde, Microsoft kampüsünün bir kısmını kapsayan bir jeoçit bulunmaktadır. Kırmızı çizgi, 520 boyunca ilerleyen bir kamyonu ve GPS okumalarını gösteren daireleri temsil eder. Bu okumaların çoğu doğru ve 520 boyunca yer alırken, bir tanesi jeoçitin içinde yanlış bir okuma olarak görünmektedir. Bu okumanın doğru olması mümkün değildir - kamyonun 520'den kampüse aniden sapıp, ardından tekrar 520'ye dönmesi için yollar yoktur. Bu jeoçiti kontrol eden kod, jeoçit testi sonuçlarına göre işlem yapmadan önce önceki okumaları dikkate almalıdır.

✅ Bir GPS okumasının doğru kabul edilip edilemeyeceğini kontrol etmek için hangi ek verilere ihtiyaç duyarsınız?

### Görev - noktaları bir jeoçite karşı test etme

1. Web API sorgusu için URL'yi oluşturmakla başlayın. Format şu şekildedir:

    ```output
    https://atlas.microsoft.com/spatial/geofence/json?api-version=1.0&deviceId=gps-sensor&subscription-key=<subscription-key>&udid=<UDID>&lat=<lat>&lon=<lon>
    ```

    `<subscription_key>` kısmını Azure Maps hesabınızın API anahtarı ile değiştirin.

    `<UDID>` kısmını önceki görevdeki jeoçitin UDID'si ile değiştirin.

    `<lat>` ve `<lon>` kısmını test etmek istediğiniz enlem ve boylam ile değiştirin.

    Bu URL, GeoJSON kullanılarak tanımlanan bir jeoçiti sorgulamak için `https://atlas.microsoft.com/spatial/geofence/json` API'sini kullanır. `1.0` API sürümünü hedefler. `deviceId` parametresi gereklidir ve enlem ve boylamın geldiği cihazın adı olmalıdır.

    Varsayılan arama tamponu 50m'dir ve bunu `searchBuffer=<distance>` ek parametresini geçirerek değiştirebilirsiniz. `<distance>` değerini metre cinsinden 0 ile 500 arasında bir mesafeye ayarlayın.

1. Bu URL'ye bir GET isteği yapmak için curl kullanın:

    ```sh
    curl --request GET '<URL>'
    ```

    > 💁 Eğer `BadRequest` yanıt kodu alırsanız ve hata şu şekilde olursa:
    >
    > ```output
    > Invalid GeoJSON: All feature properties should contain a geometryId, which is used for identifying the geofence.
    > ```
    >
    > GeoJSON'unuzda `geometryId` içeren `properties` bölümü eksiktir. GeoJSON'unuzu düzeltmeniz, ardından yukarıdaki adımları tekrarlayarak yeniden yüklemeniz ve yeni bir UDID almanız gerekecek.

1. Yanıt, jeoçiti oluşturmak için kullanılan GeoJSON'da tanımlanan her bir çokgen için bir `geometries` listesi içerecektir. Her bir geometri, `distance`, `nearestLat` ve `nearestLon` olmak üzere 3 ilgi alanına sahip alana sahiptir.

    ```output
    {
        "geometries": [
            {
                "deviceId": "gps-sensor",
                "udId": "7c3776eb-da87-4c52-ae83-caadf980323a",
                "geometryId": "1",
                "distance": 999.0,
                "nearestLat": 47.645875,
                "nearestLon": -122.142713
            }
        ],
        "expiredGeofenceGeometryId": [],
        "invalidPeriodGeofenceGeometryId": []
    }
    ```

    * `nearestLat` ve `nearestLon`, test edilen konuma en yakın jeoçitin kenarındaki bir noktanın enlem ve boylamıdır.

    * `distance`, test edilen konumdan jeoçitin kenarındaki en yakın noktaya olan mesafedir. Negatif sayılar jeoçitin içinde, pozitif sayılar dışında anlamına gelir. Bu değer 50'den (varsayılan arama tamponu) küçük veya 999 olacaktır.

1. Bu işlemi jeoçitin içinde ve dışında bulunan konumlarla birden fazla kez tekrarlayın.

## Sunucusuz koddan jeoçitleri kullanma

Artık IoT Hub GPS olay verilerini jeoçite karşı test etmek için Functions uygulamanıza yeni bir tetikleyici ekleyebilirsiniz.

### Tüketici grupları

Önceki derslerden hatırlayacağınız gibi, IoT Hub, hub tarafından alınan ancak işlenmeyen olayları yeniden oynatmanıza izin verir. Ancak birden fazla tetikleyici bağlanırsa ne olur? Hangi tetikleyicinin hangi olayları işlediğini nasıl bilecek?

Cevap şu ki, bilemez! Bunun yerine, olayları okumak için birden fazla ayrı bağlantı tanımlayabilirsiniz ve her biri okunmamış mesajların yeniden oynatılmasını yönetebilir. Bunlara *tüketici grupları* denir. Uç noktaya bağlandığınızda, bağlanmak istediğiniz tüketici grubunu belirtebilirsiniz. Uygulamanızın her bir bileşeni farklı bir tüketici grubuna bağlanacaktır.

![Tek bir IoT Hub, aynı mesajları 3 farklı Functions uygulamasına dağıtan 3 tüketici grubuna sahip](../../../../../translated_images/tr/consumer-groups.a3262e26fc27ba20.webp)

Teorik olarak her tüketici grubuna 5 uygulama bağlanabilir ve mesajlar geldiğinde hepsi mesajları alır. En iyi uygulama, her tüketici grubuna yalnızca bir uygulamanın erişmesini sağlamak, böylece yinelenen mesaj işleme önlenir ve yeniden başlatıldığında tüm sıraya alınmış mesajlar doğru şekilde işlenir. Örneğin, Functions uygulamanızı hem yerel olarak hem de bulutta çalıştırırsanız, her ikisi de mesajları işler ve bu da depolama hesabında yinelenen blobların saklanmasına yol açar.

Önceki derste oluşturduğunuz IoT Hub tetikleyicisinin `function.json` dosyasını incelerseniz, olay hub tetikleyici bağlama bölümünde tüketici grubunu göreceksiniz:

```json
"consumerGroup": "$Default"
```

Bir IoT Hub oluşturduğunuzda, varsayılan olarak `$Default` tüketici grubu oluşturulur. Ek bir tetikleyici eklemek isterseniz, bunu yeni bir tüketici grubu kullanarak ekleyebilirsiniz.

> 💁 Bu derste, GPS verilerini depolamak için kullanılan işlevden farklı bir işlev kullanarak jeoçiti test edeceksiniz. Bu, tüketici gruplarını nasıl kullanacağınızı ve kodu daha okunabilir ve anlaşılır hale getirmek için nasıl ayıracağınızı göstermek içindir. Üretim uygulamasında bunu yapmanın birçok yolu vardır - her ikisini bir işlevde birleştirmek, depolama hesabındaki bir tetikleyiciyi kullanarak jeoçiti kontrol etmek için bir işlev çalıştırmak veya birden fazla işlev kullanmak. 'Doğru yol' yoktur, bu uygulamanızın geri kalanına ve ihtiyaçlarınıza bağlıdır.

### Görev - yeni bir tüketici grubu oluşturma

1. IoT Hub için `geofence` adlı yeni bir tüketici grubu oluşturmak için aşağıdaki komutu çalıştırın:

    ```sh
    az iot hub consumer-group create --name geofence \
                                     --hub-name <hub_name>
    ```

    `<hub_name>` kısmını IoT Hub için kullandığınız ad ile değiştirin.

1. IoT Hub için tüm tüketici gruplarını görmek isterseniz, aşağıdaki komutu çalıştırın:

    ```sh
    az iot hub consumer-group list --output table \
                                   --hub-name <hub_name>
    ```

    `<hub_name>` kısmını IoT Hub için kullandığınız ad ile değiştirin. Bu, tüm tüketici gruplarını listeleyecektir.

    ```output
    Name      ResourceGroup
    --------  ---------------
    $Default  gps-sensor
    geofence  gps-sensor
    ```

> 💁 Önceki derste IoT Hub olay monitörünü çalıştırdığınızda, `$Default` tüketici grubuna bağlandı. Bu nedenle olay monitörünü ve bir olay tetikleyicisini aynı anda çalıştıramazsınız. Her işlev uygulaması için diğer tüketici gruplarını kullanabilir ve `$Default` grubunu olay monitörü için saklayabilirsiniz.

### Görev - yeni bir IoT Hub tetikleyici oluşturma

1. Daha önceki derste oluşturduğunuz `gps-trigger` işlev uygulamasına yeni bir IoT Hub olay tetikleyici ekleyin. Bu işlevi `geofence-trigger` olarak adlandırın.

    > ⚠️ [Proje 2, ders 5'teki IoT Hub olay tetikleyici oluşturma talimatlarına gerekirse buradan bakabilirsiniz](../../../2-farm/lessons/5-migrate-application-to-the-cloud/README.md#create-an-iot-hub-event-trigger).

1. `function.json` dosyasındaki IoT Hub bağlantı dizesini yapılandırın. `local.settings.json` dosyası, Functions uygulamasındaki tüm tetikleyiciler arasında paylaşılır.

1. `function.json` dosyasındaki `consumerGroup` değerini yeni `geofence` tüketici grubunu referans alacak şekilde güncelleyin:

    ```json
    "consumerGroup": "geofence"
    ```

1. Bu tetikleyicide Azure Maps hesabınızın abonelik anahtarını kullanmanız gerekecek, bu yüzden `local.settings.json` dosyasına `MAPS_KEY` adlı yeni bir giriş ekleyin.

1. Functions uygulamasını çalıştırarak bağlandığından ve mesajları işlediğinden emin olun. Önceki dersten `iot-hub-trigger` da çalışacak ve blobları depolamaya yükleyecektir.

    > Blob depolamada yinelenen GPS okumalarını önlemek için bulutta çalışan Functions uygulamanızı durdurabilirsiniz. Bunu yapmak için aşağıdaki komutu kullanın:
    >
    > ```sh
    > az functionapp stop --resource-group gps-sensor \
    >                     --name <functions_app_name>
    > ```
    >
    > `<functions_app_name>` kısmını Functions uygulamanız için kullandığınız ad ile değiştirin.
    >
    > Daha sonra aşağıdaki komutla yeniden başlatabilirsiniz:
    >
    > ```sh
    > az functionapp start --resource-group gps-sensor \
    >                     --name <functions_app_name>
    > ```
    >
    > `<functions_app_name>` kısmını Functions uygulamanız için kullandığınız ad ile değiştirin.

### Görev - tetikleyiciden jeoçiti test etme

Bu derste daha önce bir noktanın jeoçitin içinde mi dışında mı olduğunu görmek için curl kullanarak bir jeoçiti sorguladınız. Benzer bir web isteğini tetikleyicinizin içinden yapabilirsiniz.

1. Jeoçiti sorgulamak için UDID'sine ihtiyacınız var. `local.settings.json` dosyasına `GEOFENCE_UDID` adlı yeni bir giriş ekleyin ve bu değeri girin.

1. Yeni `geofence-trigger` tetikleyicisinin `__init__.py` dosyasını açın.

1. Dosyanın üst kısmına aşağıdaki import'u ekleyin:

    ```python
    import json
    import os
    import requests
    ```

    `requests` paketi, web API çağrıları yapmanıza olanak tanır. Azure Maps'in bir Python SDK'sı yoktur, Python kodundan kullanmak için web API çağrıları yapmanız gerekir.

1. `main` metodunun başına aşağıdaki 2 satırı ekleyerek Maps abonelik anahtarını alın:

    ```python
    maps_key = os.environ['MAPS_KEY']
    geofence_udid = os.environ['GEOFENCE_UDID']    
    ```

1. `for event in events` döngüsünün içine aşağıdaki kodu ekleyerek her olaydan enlem ve boylamı alın:

    ```python
    event_body = json.loads(event.get_body().decode('utf-8'))
    lat = event_body['gps']['lat']
    lon = event_body['gps']['lon']
    ```

    Bu kod, olay gövdesindeki JSON'u bir sözlüğe dönüştürür ve ardından `gps` alanından `lat` ve `lon` değerlerini çıkarır.

1. `requests` kullanırken, curl ile yaptığınız gibi uzun bir URL oluşturmak yerine, yalnızca URL kısmını kullanabilir ve parametreleri bir sözlük olarak geçirebilirsiniz. Çağrılacak URL'yi tanımlamak ve parametreleri yapılandırmak için aşağıdaki kodu ekleyin:

    ```python
    url = 'https://atlas.microsoft.com/spatial/geofence/json'

    params = {
        'api-version': 1.0,
        'deviceId': 'gps-sensor',
        'subscription-key': maps_key,
        'udid' : geofence_udid,
        'lat' : lat,
        'lon' : lon
    }
    ```

    `params` sözlüğündeki öğeler, curl ile web API'yi çağırırken kullandığınız anahtar-değer çiftleriyle eşleşecektir.

1. Web API'yi çağırmak için aşağıdaki kod satırlarını ekleyin:

    ```python
    response = requests.get(url, params=params)
    response_body = json.loads(response.text)
    ```

    Bu, URL'yi parametrelerle çağırır ve bir yanıt nesnesi alır.

1. Bunun altına aşağıdaki kodu ekleyin:

    ```python
    distance = response_body['geometries'][0]['distance']

    if distance == 999:
        logging.info('Point is outside geofence')
    elif distance > 0:
        logging.info(f'Point is just outside geofence by a distance of {distance}m')
    elif distance == -999:
        logging.info(f'Point is inside geofence')
    else:
        logging.info(f'Point is just inside geofence by a distance of {distance}m')
    ```

    Bu kod, 1 geometri varsayar ve bu tek geometriden mesafeyi çıkarır. Ardından mesafeye göre farklı mesajlar kaydeder.

1. Bu kodu çalıştırın. GPS koordinatlarının jeoçitin içinde mi dışında mı olduğunu, eğer 50m içinde ise mesafeyi günlük çıktısında göreceksiniz. GPS sensörünüzün konumuna göre farklı jeoçitlerle bu kodu deneyin, sensörü hareket ettirmeyi deneyin (örneğin bir mobil telefonun WiFi'sine bağlı veya sanal IoT cihazında farklı koordinatlarla) ve değişimi gözlemleyin.

1. Hazır olduğunuzda, bu kodu buluttaki Functions uygulamanıza dağıtın. Yeni Uygulama Ayarlarını dağıtmayı unutmayın.

    > ⚠️ [Proje 2, ders 5'teki Uygulama Ayarlarını yükleme talimatlarına gerekirse buradan bakabilirsiniz](../../../2-farm/lessons/5-migrate-application-to-the-cloud/README.md#task---upload-your-application-settings).

    > ⚠️ [Proje 2, ders 5'teki Functions uygulamanızı buluta dağıtma talimatlarına gerekirse buradan bakabilirsiniz](../../../2-farm/lessons/5-migrate-application-to-the-cloud/README.md#task---deploy-your-functions-app-to-the-cloud).

> 💁 Bu kodu [code/functions](../../../../../3-transport/lessons/4-geofences/code/functions) klasöründe bulabilirsiniz.

---

## 🚀 Meydan Okuma

Bu derste, tek bir çokgen içeren bir GeoJSON dosyası kullanarak bir jeoçit eklediniz. Farklı `geometryId` değerlerine sahip birden fazla çokgen içeren bir GeoJSON dosyası yüklemeyi deneyin ve GPS koordinatlarının hangi çokgene en yakın veya içinde olduğunu bulmak için kodunuzu ayarlayın.

## Ders Sonrası Test

[Ders sonrası test](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/28)

## İnceleme ve Kendi Kendine Çalışma

* Jeoçitler ve bazı kullanım alanları hakkında daha fazla bilgi için [Wikipedia'daki Jeoçit sayfasını](https://en.wikipedia.org/wiki/Geo-fence) okuyun.
* Azure Maps jeoçit API'si hakkında daha fazla bilgi için [Microsoft Azure Maps Spatial - Get Geofence belgelerini](https://docs.microsoft.com/rest/api/maps/spatial/getgeofence?WT.mc_id=academic-17441-jabenn) okuyun.
* Tüketici grupları hakkında daha fazla bilgi için [Azure Event Hubs'daki Özellikler ve Terminoloji - Olay Tüketicileri belgelerini](https://docs.microsoft.com/azure/event-hubs/event-hubs-features?WT.mc_id=academic-17441-jabenn#event-consumers) okuyun.

## Ödev

[Twilio kullanarak bildirim gönderin](assignment.md)

---

**Feragatname**:  
Bu belge, [Co-op Translator](https://github.com/Azure/co-op-translator) adlı yapay zeka çeviri hizmeti kullanılarak çevrilmiştir. Doğruluk için çaba göstersek de, otomatik çevirilerin hata veya yanlışlıklar içerebileceğini lütfen unutmayın. Belgenin orijinal dili, yetkili kaynak olarak kabul edilmelidir. Kritik bilgiler için profesyonel insan çevirisi önerilir. Bu çevirinin kullanımından kaynaklanan yanlış anlama veya yanlış yorumlamalardan sorumlu değiliz.