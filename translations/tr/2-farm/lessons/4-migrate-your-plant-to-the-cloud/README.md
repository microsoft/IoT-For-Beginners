# Bitkinizi Buluta Taşıyın

![Bu dersin bir skeç notu özeti](../../../../../translated_images/tr/lesson-8.3f21f3c11159e6a0.webp)

> Skeç notu: [Nitya Narasimhan](https://github.com/nitya). Daha büyük bir versiyon için görsele tıklayın.

Bu ders, [Microsoft Reactor](https://developer.microsoft.com/reactor/?WT.mc_id=academic-17441-jabenn) tarafından sunulan [IoT for Beginners Projesi 2 - Dijital Tarım Serisi](https://youtube.com/playlist?list=PLmsFUfdnGr3yCutmcVg6eAUEfsGiFXgcx) kapsamında öğretilmiştir.

[![Azure IoT Hub ile cihazınızı buluta bağlayın](https://img.youtube.com/vi/bNxjopXkhvk/0.jpg)](https://youtu.be/bNxjopXkhvk)

## Ders Öncesi Test

[Ders öncesi test](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/15)

## Giriş

Son derste, bitkinizi bir MQTT brokerına nasıl bağlayacağınızı ve yerel olarak çalışan bir sunucu kodundan bir röleyi nasıl kontrol edeceğinizi öğrendiniz. Bu, evdeki bireysel bitkilerden ticari çiftliklere kadar kullanılan internet bağlantılı otomatik sulama sistemlerinin temelini oluşturur.

IoT cihazı, ilkeleri göstermek için bir genel MQTT brokerı ile iletişim kurdu, ancak bu en güvenilir veya güvenli yöntem değildir. Bu derste, bulut ve genel bulut hizmetleri tarafından sağlanan IoT yetenekleri hakkında bilgi edineceksiniz. Ayrıca, bitkinizi genel MQTT brokerından bu bulut hizmetlerinden birine nasıl taşıyacağınızı öğreneceksiniz.

Bu derste şunları ele alacağız:

* [Bulut nedir?](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud)
* [Bir bulut aboneliği oluşturun](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud)
* [Bulut IoT hizmetleri](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud)
* [Bulutta bir IoT hizmeti oluşturun](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud)
* [IoT Hub ile iletişim kurun](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud)
* [Cihazınızı IoT hizmetine bağlayın](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud)

## Bulut Nedir?

Bulut öncesinde, bir şirket çalışanlarına (örneğin veritabanları veya dosya depolama) ya da halka (örneğin web siteleri) hizmet sağlamak istediğinde, bir veri merkezi kurar ve işletirdi. Bu, birkaç bilgisayarlı bir odadan, birçok bilgisayarlı bir binaya kadar değişebilirdi. Şirket her şeyi yönetmek zorundaydı, örneğin:

* Bilgisayar satın alma
* Donanım bakımı
* Güç ve soğutma
* Ağ bağlantısı
* Güvenlik, bina güvenliği ve bilgisayarlardaki yazılım güvenliği dahil
* Yazılım kurulumu ve güncellemeleri

Bu oldukça pahalı olabilir, geniş bir yetenek yelpazesine sahip çalışanlar gerektirebilir ve gerektiğinde değişiklik yapmak çok yavaş olabilirdi. Örneğin, bir çevrimiçi mağaza yoğun bir tatil sezonu için plan yapmak istediğinde, aylar öncesinden daha fazla donanım satın almak, yapılandırmak, kurmak ve satış sürecini çalıştıracak yazılımı yüklemek zorunda kalırdı. Tatil sezonu sona erdiğinde ve satışlar tekrar düştüğünde, satın alınmış bilgisayarlar bir sonraki yoğun sezona kadar boşta kalırdı.

✅ Sizce bu, şirketlerin hızlı hareket etmesine olanak tanır mıydı? Bir çevrimiçi giyim perakendecisi, bir ünlünün kıyafetlerini giymesi nedeniyle aniden popüler hale gelirse, siparişlerdeki ani artışı desteklemek için bilgi işlem gücünü yeterince hızlı artırabilir miydi?

### Başkasının Bilgisayarı

Bulut genellikle şaka yollu olarak 'başkasının bilgisayarı' olarak adlandırılır. İlk fikir basitti - bilgisayar satın almak yerine, başkasının bilgisayarını kiralarsınız. Başkası, bir bulut bilişim sağlayıcısı, devasa veri merkezlerini yönetirdi. Donanımı satın almak ve kurmak, güç ve soğutmayı yönetmek, ağ bağlantısını sağlamak, bina güvenliğini sağlamak, donanım ve yazılım güncellemelerini yapmak gibi her şeyden sorumlu olurlardı. Müşteri olarak, ihtiyacınız olan bilgisayarları kiralar, talep arttığında daha fazlasını kiralar, talep düştüğünde ise kiraladığınız miktarı azaltırdınız. Bu bulut veri merkezleri dünyanın dört bir yanına yayılmıştır.

![Bir Microsoft bulut veri merkezi](../../../../../translated_images/tr/azure-region-existing.73f704604f2aa6cb.webp)
![Bir Microsoft bulut veri merkezi planlanan genişleme](../../../../../translated_images/tr/azure-region-planned-expansion.a5074a1e8af74f15.webp)

Bu veri merkezleri birkaç kilometrekare büyüklüğünde olabilir. Yukarıdaki görseller birkaç yıl önce bir Microsoft bulut veri merkezinde çekilmiş olup, başlangıç boyutunu ve planlanan genişlemeyi göstermektedir. Genişleme için temizlenen alan 5 kilometrekareden fazladır.

> 💁 Bu veri merkezleri o kadar büyük miktarda enerji gerektirir ki, bazılarının kendi enerji santralleri vardır. Boyutları ve bulut sağlayıcılarının yatırımları nedeniyle, genellikle çevre dostudurlar. Çok sayıda küçük veri merkezine göre daha verimlidirler, çoğunlukla yenilenebilir enerjiyle çalışırlar ve bulut sağlayıcıları atıkları azaltmak, su kullanımını kesmek ve veri merkezleri inşa etmek için kesilen ormanları yeniden dikmek için yoğun çaba harcarlar. Bir bulut sağlayıcısının sürdürülebilirlik üzerinde nasıl çalıştığını [Azure sürdürülebilirlik sitesi](https://azure.microsoft.com/global-infrastructure/sustainability/?WT.mc_id=academic-17441-jabenn) üzerinden okuyabilirsiniz.

✅ Araştırma yapın: [Microsoft'un Azure'u](https://azure.microsoft.com/?WT.mc_id=academic-17441-jabenn) veya [Google'ın GCP'si](https://cloud.google.com) gibi büyük bulutlar hakkında bilgi edinin. Kaç tane veri merkezleri var ve bunlar dünyanın neresinde?

Bulut kullanmak, şirketlerin maliyetlerini düşürür ve bulut bilişim uzmanlığını sağlayıcıya bırakırken, şirketlerin en iyi yaptıkları işe odaklanmalarını sağlar. Şirketler artık veri merkezi alanı kiralamak veya satın almak, farklı sağlayıcılardan bağlantı ve güç için ödeme yapmak ya da uzmanları işe almak zorunda kalmazlar. Bunun yerine, her şeyin halledilmesi için bulut sağlayıcısına aylık bir fatura öderler.

Bulut sağlayıcısı, maliyetleri düşürmek için ölçek ekonomilerinden yararlanabilir, donanımı toplu olarak daha düşük maliyetle satın alabilir, bakım iş yüklerini azaltmak için araçlara yatırım yapabilir ve hatta bulut tekliflerini geliştirmek için kendi donanımlarını tasarlayıp üretebilir.

### Microsoft Azure

Azure, Microsoft'un geliştiriciler için sunduğu buluttur ve bu derslerde kullanacağınız bulut hizmetidir. Aşağıdaki video, Azure hakkında kısa bir genel bakış sunar:

[![Azure videosunun genel bakışı](../../../../../translated_images/tr/what-is-azure-video-thumbnail.20174db09e03bbb8.webp)](https://www.microsoft.com/videoplayer/embed/RE4Ibng?WT.mc_id=academic-17441-jabenn)

## Bir Bulut Aboneliği Oluşturun

Buluttaki hizmetleri kullanmak için bir bulut sağlayıcısından bir abonelik oluşturmanız gerekir. Bu ders için bir Microsoft Azure aboneliği oluşturacaksınız. Zaten bir Azure aboneliğiniz varsa, bu görevi atlayabilirsiniz. Burada açıklanan abonelik ayrıntıları yazım sırasında doğrudur, ancak değişebilir.

> 💁 Bu derslere okulunuz aracılığıyla erişiyorsanız, zaten bir Azure aboneliğiniz olabilir. Öğretmeninizle kontrol edin.

Azure'da iki farklı ücretsiz abonelik türü bulunmaktadır:

* **Azure for Students** - Bu, 18 yaş ve üzeri öğrenciler için tasarlanmış bir aboneliktir. Kayıt olmak için bir kredi kartına ihtiyacınız yoktur ve öğrenci olduğunuzu doğrulamak için okul e-posta adresinizi kullanırsınız. Kayıt olduğunuzda, bulut kaynakları için harcayabileceğiniz 100 ABD doları ve bir IoT hizmetinin ücretsiz bir sürümü dahil ücretsiz hizmetler alırsınız. Bu abonelik 12 ay sürer ve öğrenci olduğunuz sürece her yıl yenileyebilirsiniz.

* **Azure ücretsiz abonelik** - Bu, öğrenci olmayan herkes için bir aboneliktir. Abonelik için kayıt olmak için bir kredi kartına ihtiyacınız olacak, ancak kartınızdan ücret alınmayacaktır, bu yalnızca gerçek bir insan olduğunuzu doğrulamak içindir. İlk 30 gün boyunca herhangi bir hizmette kullanabileceğiniz 200 ABD doları kredi alırsınız ve Azure hizmetlerinin ücretsiz katmanlarına erişebilirsiniz. Krediniz tükendiğinde, yalnızca bir ödeme yaparak devam eden aboneliğe geçerseniz kartınızdan ücret alınır.

> 💁 Microsoft, 18 yaş altı öğrenciler için bir Azure for Students Starter aboneliği sunmaktadır, ancak yazım sırasında bu abonelik IoT hizmetlerini desteklememektedir.

### Görev - Ücretsiz bir bulut aboneliği oluşturun

18 yaş ve üzeri bir öğrenciyseniz, bir Azure for Students aboneliğine kaydolabilirsiniz. Bir okul e-posta adresiyle doğrulama yapmanız gerekecek. Bunu iki şekilde yapabilirsiniz:

* [education.github.com/pack](https://education.github.com/pack) adresinden bir GitHub öğrenci geliştirici paketi için kaydolun. Bu, GitHub ve Microsoft Azure dahil olmak üzere bir dizi araç ve teklife erişim sağlar. Geliştirici paketine kaydolduktan sonra, Azure for Students teklifini etkinleştirebilirsiniz.

* [azure.microsoft.com/free/students](https://azure.microsoft.com/free/students/?WT.mc_id=academic-17441-jabenn) adresinden doğrudan bir Azure for Students hesabı için kaydolun.

> ⚠️ Okul e-posta adresiniz tanınmazsa, bu [repo'da bir sorun bildirin](https://github.com/Microsoft/IoT-For-Beginners/issues) ve adresinizin Azure for Students izin listesine eklenip eklenemeyeceğini kontrol edeceğiz.

Öğrenci değilseniz veya geçerli bir okul e-posta adresiniz yoksa, bir Azure Ücretsiz aboneliği için kaydolabilirsiniz.

* [azure.microsoft.com/free](https://azure.microsoft.com/free/?WT.mc_id=academic-17441-jabenn) adresinden bir Azure Ücretsiz Aboneliği için kaydolun.

## Bulut IoT Hizmetleri

Kullandığınız genel test MQTT brokerı öğrenme sırasında harika bir araçtır, ancak ticari bir ortamda kullanmak için bazı dezavantajları vardır:

* Güvenilirlik - Bu ücretsiz bir hizmettir, garanti sunmaz ve istediğiniz zaman kapatılabilir.
* Güvenlik - Genel bir hizmettir, bu nedenle herhangi biri telemetrinizi dinleyebilir veya donanımınızı kontrol etmek için komutlar gönderebilir.
* Performans - Sadece birkaç test mesajı için tasarlanmıştır, bu nedenle çok sayıda mesaj gönderildiğinde başa çıkamaz.
* Keşif - Bağlı cihazların ne olduğunu bilmenin bir yolu yoktur.

Buluttaki IoT hizmetleri bu sorunları çözer. Büyük bulut sağlayıcıları tarafından yönetilirler, güvenilirlik için büyük yatırımlar yaparlar ve ortaya çıkabilecek sorunları çözmek için hazırdırlar. Verilerinizi okuyan veya sahte komutlar gönderen hackerları engellemek için güvenlik yerleşiktir. Ayrıca, bulutun ihtiyaç duyulduğunda ölçeklenebilmesi sayesinde, her gün milyonlarca mesajı işleyebilecek yüksek performansa sahiptirler.

> 💁 Bu avantajlar için aylık bir ücret ödersiniz, ancak çoğu bulut sağlayıcısı günlük sınırlı sayıda mesaj veya bağlanabilecek cihazlarla ücretsiz bir IoT hizmeti sunar. Bu ücretsiz sürüm, genellikle bir geliştiricinin hizmeti öğrenmesi için fazlasıyla yeterlidir. Bu derste ücretsiz bir sürüm kullanacaksınız.

IoT cihazları, bir cihaz SDK'sı (hizmetin özellikleriyle çalışmak için kod sağlayan bir kütüphane) veya MQTT ya da HTTP gibi bir iletişim protokolü aracılığıyla doğrudan bir bulut hizmetine bağlanır. Cihaz SDK'sı genellikle en kolay yoldur çünkü her şeyi sizin için halleder, örneğin hangi konulara yayın yapacağınızı veya abone olacağınızı ve güvenliği nasıl yöneteceğinizi bilir.

![Cihazlar bir cihaz SDK'sı kullanarak bir hizmete bağlanır. Sunucu kodu da bir SDK aracılığıyla hizmete bağlanır](../../../../../translated_images/tr/iot-service-connectivity.7e873847921a5d6f.webp)

Cihazınız daha sonra uygulamanızın diğer bölümleriyle bu hizmet üzerinden iletişim kurar - tıpkı MQTT üzerinden telemetri gönderip komutlar aldığınız gibi. Bu genellikle bir hizmet SDK'sı veya benzer bir kütüphane kullanılarak yapılır. Mesajlar cihazınızdan hizmete gelir, burada uygulamanızın diğer bileşenleri tarafından okunabilir ve mesajlar cihazınıza geri gönderilebilir.

![Geçerli bir gizli anahtarı olmayan cihazlar IoT hizmetine bağlanamaz](../../../../../translated_images/tr/iot-service-allowed-denied-connection.818b0063ac213fb8.webp)

Bu hizmetler, bağlanıp veri gönderebilecek tüm cihazları bilerek güvenlik sağlar, ya cihazların hizmetle önceden kaydedilmesiyle ya da cihazlara hizmete ilk kez bağlandıklarında kendilerini kaydetmek için kullanabilecekleri gizli anahtarlar veya sertifikalar verilmesiyle. Bilinmeyen cihazlar bağlanamaz, bağlanmaya çalışırlarsa hizmet bağlantıyı reddeder ve gönderdikleri mesajları görmezden gelir.

✅ Araştırma yapın: Herhangi bir cihazın veya kodun bağlanabileceği açık bir IoT hizmetine sahip olmanın dezavantajı nedir? Hackerların bundan yararlandığına dair belirli örnekler bulabilir misiniz?

Uygulamanızın diğer bileşenleri IoT hizmetine bağlanabilir ve bağlı veya kayıtlı tüm cihazlar hakkında bilgi edinebilir ve bunlarla toplu veya bireysel olarak doğrudan iletişim kurabilir.
💁 IoT hizmetleri ayrıca ek yetenekler sunar ve bulut sağlayıcılarının hizmete bağlanabilecek ek hizmetleri ve uygulamaları vardır. Örneğin, tüm cihazlar tarafından gönderilen tüm telemetri mesajlarını bir veritabanında saklamak istiyorsanız, genellikle bulut sağlayıcısının yapılandırma aracında birkaç tıklama ile hizmeti bir veritabanına bağlamak ve verileri akış halinde göndermek mümkündür.
## Bulutta bir IoT hizmeti oluşturun

Artık bir Azure aboneliğiniz olduğuna göre, bir IoT hizmetine kaydolabilirsiniz. Microsoft'un IoT hizmeti Azure IoT Hub olarak adlandırılır.

![Azure IoT Hub logosu](../../../../../translated_images/tr/azure-iot-hub-logo.28a19de76d0a1932.webp)

Aşağıdaki video, Azure IoT Hub hakkında kısa bir genel bakış sunar:

[![Azure IoT Hub videosunun genel bakışı](https://img.youtube.com/vi/smuZaZZXKsU/0.jpg)](https://www.youtube.com/watch?v=smuZaZZXKsU)

> 🎥 Videoyu izlemek için yukarıdaki görsele tıklayın

✅ Biraz araştırma yapın ve [Microsoft IoT Hub belgelerindeki](https://docs.microsoft.com/azure/iot-hub/about-iot-hub?WT.mc_id=academic-17441-jabenn) IoT Hub genel bakışını okuyun.

Azure'da mevcut olan bulut hizmetleri, web tabanlı bir portal veya komut satırı arayüzü (CLI) aracılığıyla yapılandırılabilir. Bu görev için CLI kullanacaksınız.

### Görev - Azure CLI'yi yükleyin

Azure CLI'yi kullanmak için önce PC'nize veya Mac'inize yüklenmesi gerekir.

1. CLI'yi yüklemek için [Azure CLI belgelerindeki](https://docs.microsoft.com/cli/azure/install-azure-cli?WT.mc_id=academic-17441-jabenn) talimatları izleyin.

1. Azure CLI, çok çeşitli Azure hizmetlerini yönetme yetenekleri ekleyen bir dizi uzantıyı destekler. Komut satırınızdan veya terminalinizden aşağıdaki komutu çalıştırarak IoT uzantısını yükleyin:

    ```sh
    az extension add --name azure-iot
    ```

1. Komut satırınızdan veya terminalinizden aşağıdaki komutu çalıştırarak Azure CLI'den Azure aboneliğinize giriş yapın.

    ```sh
    az login
    ```

    Varsayılan tarayıcınızda bir web sayfası açılacaktır. Azure aboneliğinize kaydolurken kullandığınız hesapla giriş yapın. Giriş yaptıktan sonra tarayıcı sekmesini kapatabilirsiniz.

1. Birden fazla Azure aboneliğiniz varsa, örneğin okul tarafından sağlanan bir abonelik ve kendi Azure for Students aboneliğiniz gibi, kullanmak istediğiniz aboneliği seçmeniz gerekecektir. Erişiminiz olan tüm abonelikleri listelemek için aşağıdaki komutu çalıştırın:

    ```sh
    az account list --output table
    ```

    Çıktıda, her aboneliğin adı ve `SubscriptionId` bilgisi görünecektir.

    ```output
    ➜  ~ az account list --output table
    Name                    CloudName    SubscriptionId                        State    IsDefault
    ----------------------  -----------  ------------------------------------  -------  -----------
    School-subscription     AzureCloud   cb30cde9-814a-42f0-a111-754cb788e4e1  Enabled  True
    Azure for Students      AzureCloud   fa51c31b-162c-4599-add6-781def2e1fbf  Enabled  False
    ```

    Kullanmak istediğiniz aboneliği seçmek için aşağıdaki komutu kullanın:

    ```sh
    az account set --subscription <SubscriptionId>
    ```

    `<SubscriptionId>` yerine kullanmak istediğiniz aboneliğin kimliğini yazın. Bu komutu çalıştırdıktan sonra hesaplarınızı listeleme komutunu tekrar çalıştırın. `IsDefault` sütununun, yeni ayarladığınız abonelik için `True` olarak işaretlendiğini göreceksiniz.

### Görev - bir kaynak grubu oluşturun

Azure hizmetleri, IoT Hub örnekleri, sanal makineler, veritabanları veya yapay zeka hizmetleri gibi, **kaynaklar** olarak adlandırılır. Her kaynak bir **Kaynak Grubu** içinde yer almalıdır; bu, bir veya daha fazla kaynağın mantıksal bir gruplamasıdır.

> 💁 Kaynak gruplarını kullanmak, birden fazla hizmeti aynı anda yönetmenizi sağlar. Örneğin, bu proje için tüm dersleri tamamladıktan sonra kaynak grubunu silebilirsiniz ve içindeki tüm kaynaklar otomatik olarak silinir.

1. Dünya genelinde birden fazla Azure veri merkezi vardır ve bunlar bölgelere ayrılmıştır. Bir Azure kaynağı veya kaynak grubu oluşturduğunuzda, nerede oluşturulmasını istediğinizi belirtmeniz gerekir. Konumların listesini almak için aşağıdaki komutu çalıştırın:

    ```sh
    az account list-locations --output table
    ```

    Uzun bir konum listesi göreceksiniz.

    > 💁 Yazım sırasında, dağıtım yapabileceğiniz 65 konum bulunmaktadır.

    ```output
        ➜  ~ az account list-locations --output table
    DisplayName               Name                 RegionalDisplayName
    ------------------------  -------------------  -------------------------------------
    East US                   eastus               (US) East US
    East US 2                 eastus2              (US) East US 2
    South Central US          southcentralus       (US) South Central US
    ...
    ```

    Size en yakın bölgenin `Name` sütunundaki değeri not edin. Bölgeleri bir harita üzerinde [Azure coğrafyaları sayfasında](https://azure.microsoft.com/global-infrastructure/geographies/?WT.mc_id=academic-17441-jabenn) bulabilirsiniz.

1. `soil-moisture-sensor` adlı bir kaynak grubu oluşturmak için aşağıdaki komutu çalıştırın. Kaynak grubu adlarının aboneliğinizde benzersiz olması gerekir.

    ```sh
    az group create --name soil-moisture-sensor \
                    --location <location>
    ```

    `<location>` yerine bir önceki adımda seçtiğiniz konumu yazın.

### Görev - bir IoT Hub oluşturun

Artık kaynak grubunuzda bir IoT Hub kaynağı oluşturabilirsiniz.

1. IoT Hub kaynağınızı oluşturmak için aşağıdaki komutu kullanın:

    ```sh
    az iot hub create --resource-group soil-moisture-sensor \
                      --sku F1 \
                      --partition-count 2 \
                      --name <hub_name>
    ```

    `<hub_name>` yerine hub için bir ad yazın. Bu adın küresel olarak benzersiz olması gerekir - yani başka hiç kimse aynı ada sahip bir IoT Hub oluşturamaz. Bu ad, hub'a işaret eden bir URL'de kullanılır, bu yüzden benzersiz olmalıdır. `soil-moisture-sensor-` gibi bir şey kullanın ve sonuna rastgele kelimeler veya adınızı ekleyin.

    `--sku F1` seçeneği, ücretsiz bir katman kullanılmasını söyler. Ücretsiz katman, günlük 8.000 mesajı ve tam fiyatlı katmanların çoğu özelliğini destekler.

    > 🎓 Azure hizmetlerinin farklı fiyatlandırma seviyelerine katmanlar denir. Her katman farklı bir maliyete sahiptir ve farklı özellikler veya veri hacimleri sunar.

    > 💁 Fiyatlandırma hakkında daha fazla bilgi edinmek isterseniz, [Azure IoT Hub fiyatlandırma kılavuzuna](https://azure.microsoft.com/pricing/details/iot-hub/?WT.mc_id=academic-17441-jabenn) göz atabilirsiniz.

    `--partition-count 2` seçeneği, IoT Hub'ın desteklediği veri akışı sayısını tanımlar. Daha fazla bölüm, IoT Hub'dan birden fazla şey okuma ve yazma yaparken veri tıkanıklığını azaltır. Bölümler bu derslerin kapsamı dışındadır, ancak ücretsiz bir katman IoT Hub oluşturmak için bu değerin ayarlanması gerekir.

    > 💁 Abonelik başına yalnızca bir ücretsiz katman IoT Hub oluşturabilirsiniz.

IoT Hub oluşturulacaktır. Bu işlem bir dakika kadar sürebilir.

## IoT Hub ile iletişim kurun

Önceki derste, MQTT kullanarak farklı amaçlara sahip farklı konular üzerinde mesajlar gönderdiniz ve aldınız. Farklı konular üzerinden mesaj göndermek yerine, IoT Hub cihazın Hub ile veya Hub'ın cihazla iletişim kurması için tanımlı bir dizi yol sunar.

> 💁 IoT Hub ile cihazınız arasındaki bu iletişim, arka planda MQTT, HTTPS veya AMQP kullanabilir.

* Cihazdan buluta (D2C) mesajlar - bunlar, bir cihazdan IoT Hub'a gönderilen telemetri gibi mesajlardır. Daha sonra uygulama kodunuz tarafından IoT Hub'dan okunabilir.

    > 🎓 Arka planda, IoT Hub bir Azure hizmeti olan [Event Hubs](https://docs.microsoft.com/azure/event-hubs/?WT.mc_id=academic-17441-jabenn) kullanır. Hub'a gönderilen mesajları okumak için yazılan kodda bunlar genellikle olaylar olarak adlandırılır.

* Buluttan cihaza (C2D) mesajlar - bunlar, uygulama kodundan bir IoT Hub aracılığıyla bir IoT cihazına gönderilen mesajlardır.

* Doğrudan yöntem istekleri - bunlar, uygulama kodundan bir IoT Hub aracılığıyla bir IoT cihazına, cihazın bir şey yapmasını istemek için gönderilen mesajlardır, örneğin bir aktüatörü kontrol etmek. Bu mesajlar, uygulama kodunuzun başarılı bir şekilde işlenip işlenmediğini anlayabilmesi için bir yanıt gerektirir.

* Cihaz ikizleri - bunlar, cihaz ve IoT Hub arasında senkronize edilen JSON belgeleridir ve cihaz tarafından bildirilen veya IoT Hub tarafından cihazda ayarlanması gereken (istenen) ayarları veya diğer özellikleri depolamak için kullanılır.

IoT Hub, mesajları ve doğrudan yöntem isteklerini yapılandırılabilir bir süre boyunca (varsayılan olarak bir gün) saklayabilir, böylece bir cihaz veya uygulama kodu bağlantısını kaybederse, yeniden bağlandığında çevrimdışıyken gönderilen mesajları alabilir. Cihaz ikizleri IoT Hub'da kalıcı olarak saklanır, böylece bir cihaz herhangi bir zamanda yeniden bağlanabilir ve en son cihaz ikizini alabilir.

✅ Araştırma yapın: Bu mesaj türleri hakkında daha fazla bilgi edinmek için IoT Hub belgelerindeki [Cihazdan buluta iletişim kılavuzunu](https://docs.microsoft.com/azure/iot-hub/iot-hub-devguide-d2c-guidance?WT.mc_id=academic-17441-jabenn) ve [Buluttan cihaza iletişim kılavuzunu](https://docs.microsoft.com/azure/iot-hub/iot-hub-devguide-c2d-guidance?WT.mc_id=academic-17441-jabenn) okuyun.

## Cihazınızı IoT hizmetine bağlayın

Hub oluşturulduktan sonra, IoT cihazınız ona bağlanabilir. Yalnızca kayıtlı cihazlar bir hizmete bağlanabilir, bu nedenle önce cihazınızı kaydetmeniz gerekecektir. Kayıt yaptığınızda, cihazın bağlanmak için kullanabileceği bir bağlantı dizesi alabilirsiniz. Bu bağlantı dizesi cihaza özeldir ve IoT Hub, cihaz ve bu cihazın bağlanmasına izin veren bir gizli anahtar hakkında bilgi içerir.

> 🎓 Bağlantı dizesi, bağlantı ayrıntılarını içeren bir metin parçası için genel bir terimdir. Bunlar, IoT Hub'lara, veritabanlarına ve birçok diğer hizmete bağlanırken kullanılır. Genellikle bir URL gibi bir hizmet tanımlayıcısı ve bir gizli anahtar gibi güvenlik bilgileri içerir. Bunlar, hizmete bağlanmak için SDK'lara iletilir.

> ⚠️ Bağlantı dizeleri güvenli tutulmalıdır! Güvenlik, ilerleyen derslerde daha ayrıntılı olarak ele alınacaktır.

### Görev - IoT cihazınızı kaydedin

IoT cihazı, Azure CLI kullanılarak IoT Hub'ınıza kaydedilebilir.

1. Bir cihaz kaydetmek için aşağıdaki komutu çalıştırın:

    ```sh
    az iot hub device-identity create --device-id soil-moisture-sensor \
                                      --hub-name <hub_name>
    ```

    `<hub_name>` yerine IoT Hub için kullandığınız adı yazın.

    Bu, `soil-moisture-sensor` kimliğine sahip bir cihaz oluşturacaktır.

1. IoT cihazınız, SDK'yı kullanarak IoT Hub'ınıza bağlandığında, hub'ın URL'si ve bir gizli anahtar içeren bir bağlantı dizesi kullanması gerekir. Bağlantı dizesini almak için aşağıdaki komutu çalıştırın:

    ```sh
    az iot hub device-identity connection-string show --device-id soil-moisture-sensor \
                                                      --output table \
                                                      --hub-name <hub_name>
    ```

    `<hub_name>` yerine IoT Hub için kullandığınız adı yazın.

1. Çıktıda gösterilen bağlantı dizesini saklayın, çünkü daha sonra buna ihtiyacınız olacak.

### Görev - IoT cihazınızı buluta bağlayın

IoT cihazınızı buluta bağlamak için ilgili kılavuzu takip edin:

* [Arduino - Wio Terminal](wio-terminal-connect-hub.md)
* [Tek kartlı bilgisayar - Raspberry Pi/Sanal IoT cihazı](single-board-computer-connect-hub.md)

### Görev - olayları izleyin

Şimdilik, sunucu kodunuzu güncellemeyeceksiniz. Bunun yerine, IoT cihazınızdan gelen olayları izlemek için Azure CLI'yi kullanabilirsiniz.

1. IoT cihazınızın çalıştığından ve toprak nemi telemetri değerlerini gönderdiğinden emin olun.

1. IoT Hub'ınıza gönderilen mesajları izlemek için komut istemcinizde veya terminalinizde aşağıdaki komutu çalıştırın:

    ```sh
    az iot hub monitor-events --hub-name <hub_name>
    ```

    `<hub_name>` yerine IoT Hub için kullandığınız adı yazın.

    IoT cihazınız tarafından gönderilen mesajlar konsol çıktısında görünecektir.

    ```output
    Starting event monitor, use ctrl-c to stop...
    {
        "event": {
            "origin": "soil-moisture-sensor",
            "module": "",
            "interface": "",
            "component": "",
            "payload": "{\"soil_moisture\": 376}"
        }
    },
    {
        "event": {
            "origin": "soil-moisture-sensor",
            "module": "",
            "interface": "",
            "component": "",
            "payload": "{\"soil_moisture\": 381}"
        }
    }
    ```

    `payload` içeriği, IoT cihazınız tarafından gönderilen mesajla eşleşecektir.

    > Yazım sırasında, `az iot` uzantısı Apple Silicon üzerinde tam olarak çalışmamaktadır. Eğer bir Apple Silicon cihazı kullanıyorsanız, mesajları farklı bir şekilde izlemeniz gerekecektir, örneğin [Visual Studio Code için Azure IoT Araçları](https://docs.microsoft.com/en-us/azure/iot-hub/iot-hub-vscode-iot-toolkit-cloud-device-messaging) kullanarak.

1. Bu mesajlara, otomatik olarak eklenen bir dizi özellik vardır, örneğin gönderildikleri zaman damgası. Bunlara *ek açıklamalar* denir. Tüm mesaj ek açıklamalarını görüntülemek için aşağıdaki komutu kullanın:

    ```sh
    az iot hub monitor-events --properties anno --hub-name <hub_name>
    ```

    `<hub_name>` yerine IoT Hub için kullandığınız adı yazın.

    IoT cihazınız tarafından gönderilen mesajlar konsol çıktısında görünecektir.

    ```output
    Starting event monitor, use ctrl-c to stop...
    {
        "event": {
            "origin": "soil-moisture-sensor",
            "module": "",
            "interface": "",
            "component": "",
            "properties": {},
            "annotations": {
                "iothub-connection-device-id": "soil-moisture-sensor",
                "iothub-connection-auth-method": "{\"scope\":\"device\",\"type\":\"sas\",\"issuer\":\"iothub\",\"acceptingIpFilterRule\":null}",
                "iothub-connection-auth-generation-id": "637553997165220462",
                "iothub-enqueuedtime": 1619976150288,
                "iothub-message-source": "Telemetry",
                "x-opt-sequence-number": 1379,
                "x-opt-offset": "550576",
                "x-opt-enqueued-time": 1619976150277
            },
            "payload": "{\"soil_moisture\": 381}"
        }
    }
    ```

    Ek açıklamalardaki zaman değerleri, 1 Ocak 1970 gece yarısından itibaren geçen saniyeleri temsil eden [UNIX zamanı](https://wikipedia.org/wiki/Unix_time) formatındadır.

    İşiniz bittiğinde olay izleyiciyi kapatın.

### Görev - IoT cihazınızı kontrol edin

Azure CLI'yi kullanarak IoT cihazınızda doğrudan yöntemler çağırabilirsiniz.

1. IoT cihazında `relay_on` yöntemini çağırmak için komut istemcinizde veya terminalinizde aşağıdaki komutu çalıştırın:

    ```sh
    az iot hub invoke-device-method --device-id soil-moisture-sensor \
                                    --method-name relay_on \
                                    --method-payload '{}' \
                                    --hub-name <hub_name>
    ```

    `
<hub_adı>
` IoT Hub için kullandığınız adı kullanarak.

    Bu, belirtilen `method-name` için doğrudan bir yöntem isteği gönderir. Doğrudan yöntemler, yöntem için veri içeren bir yük alabilir ve bu, `method-payload` parametresinde JSON olarak belirtilebilir.

    Rölenin açıldığını ve IoT cihazınızdan gelen ilgili çıktıyı göreceksiniz:

    ```output
    Direct method received -  relay_on
    ```

1. Yukarıdaki adımı tekrarlayın, ancak `--method-name` değerini `relay_off` olarak ayarlayın. Rölenin kapandığını ve IoT cihazından gelen ilgili çıktıyı göreceksiniz.

---

## 🚀 Meydan Okuma

IoT Hub'ın ücretsiz katmanı günde 8.000 mesaja izin verir. Yazdığınız kod her 10 saniyede bir telemetri mesajı gönderir. Her 10 saniyede bir mesaj gönderildiğinde günde kaç mesaj olur?

Toprak nemi ölçümlerinin ne sıklıkla gönderilmesi gerektiğini düşünün. Kodunuzu ücretsiz katmanda kalacak şekilde ve gerektiği kadar sık kontrol edecek ama çok sık olmayacak şekilde nasıl değiştirebilirsiniz? İkinci bir cihaz eklemek isteseydiniz ne olurdu?

## Ders Sonrası Test

[Ders sonrası test](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/16)

## Gözden Geçirme ve Kendi Kendine Çalışma

IoT Hub SDK, hem Arduino hem de Python için açık kaynaklıdır. GitHub'daki kod depolarında, farklı IoT Hub özellikleriyle nasıl çalışılacağını gösteren bir dizi örnek bulunmaktadır.

* Wio Terminal kullanıyorsanız, [GitHub'daki Arduino örneklerine](https://github.com/Azure/azure-iot-pal-arduino/tree/master/pal/samples) göz atın.
* Raspberry Pi veya Sanal cihaz kullanıyorsanız, [GitHub'daki Python örneklerine](https://github.com/Azure/azure-iot-sdk-python/tree/master/azure-iot-hub/samples) göz atın.

## Ödev

[Bulut hizmetleri hakkında bilgi edinin](assignment.md)

---

**Feragatname**:  
Bu belge, AI çeviri hizmeti [Co-op Translator](https://github.com/Azure/co-op-translator) kullanılarak çevrilmiştir. Doğruluk için çaba göstersek de, otomatik çevirilerin hata veya yanlışlıklar içerebileceğini lütfen unutmayın. Belgenin orijinal dili, yetkili kaynak olarak kabul edilmelidir. Kritik bilgiler için profesyonel insan çevirisi önerilir. Bu çevirinin kullanımından kaynaklanan yanlış anlamalar veya yanlış yorumlamalardan sorumlu değiliz.