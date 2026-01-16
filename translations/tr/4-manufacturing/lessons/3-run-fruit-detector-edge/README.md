<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "2625af24587465c5547ae33d6cc000a5",
  "translation_date": "2025-08-28T02:43:51+00:00",
  "source_file": "4-manufacturing/lessons/3-run-fruit-detector-edge/README.md",
  "language_code": "tr"
}
-->
# Meyve Dedektörünüzü Uç Cihazda Çalıştırın

![Bu dersin genel bir sketchnote özeti](../../../../../translated_images/tr/lesson-17.bc333c3c35ba8e42cce666cfffa82b915f787f455bd94e006aea2b6f2722421a.jpg)

> Sketchnote: [Nitya Narasimhan](https://github.com/nitya). Daha büyük bir versiyon için resme tıklayın.

Bu video, IoT cihazlarında görüntü sınıflandırıcılarını çalıştırmayı, yani bu derste ele alınan konuyu genel olarak açıklamaktadır.

[![Azure IoT Edge'de Özel Görü AI](https://img.youtube.com/vi/_K5fqGLO8us/0.jpg)](https://www.youtube.com/watch?v=_K5fqGLO8us)

## Ders Öncesi Test

[Ders öncesi test](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/33)

## Giriş

Son derste, görüntü sınıflandırıcınızı kullanarak olgun ve olgunlaşmamış meyveleri sınıflandırdınız. IoT cihazınızdaki kamerayla yakalanan bir görüntüyü internet üzerinden bir bulut hizmetine gönderdiniz. Bu çağrılar zaman alır, maliyetlidir ve kullandığınız görüntü verilerinin türüne bağlı olarak gizlilikle ilgili sorunlara yol açabilir.

Bu derste, makine öğrenimi (ML) modellerini uçta - yani bulutta değil, kendi ağınızda çalışan IoT cihazlarında - nasıl çalıştıracağınızı öğreneceksiniz. Uç bilişimin bulut bilişime göre avantajlarını ve dezavantajlarını, AI modelinizi uca nasıl dağıtacağınızı ve IoT cihazınızdan nasıl erişeceğinizi öğreneceksiniz.

Bu derste şunları ele alacağız:

* [Uç bilişim](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge)
* [Azure IoT Edge](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge)
* [Bir IoT Edge cihazı kaydedin](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge)
* [Bir IoT Edge cihazı kurun](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge)
* [Modelinizi dışa aktarın](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge)
* [Dağıtım için konteynerinizi hazırlayın](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge)
* [Konteynerinizi dağıtın](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge)
* [IoT Edge cihazınızı kullanın](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge)

## Uç Bilişim

Uç bilişim, IoT verilerini işleyen bilgisayarların, verilerin oluşturulduğu yere mümkün olduğunca yakın olmasını içerir. Bu işlem bulutta yapılmak yerine, bulutun kenarına - yani iç ağınıza - taşınır.

![Bulutta internet hizmetlerini ve yerel ağdaki IoT cihazlarını gösteren bir mimari diyagram](../../../../../translated_images/tr/cloud-without-edge.b4da641f6022c95ed6b91fde8b5323abd2f94e0d52073ad54172ae8f5dac90e9.png)

Şimdiye kadarki derslerde, verileri toplayan ve analiz için buluta gönderen cihazlar kullandınız; bu işlemler bulutta sunucusuz işlevler veya AI modelleri çalıştırılarak gerçekleştirildi.

![Yerel ağdaki IoT cihazlarının uç cihazlara bağlandığını ve bu uç cihazların buluta bağlandığını gösteren bir mimari diyagram](../../../../../translated_images/tr/cloud-with-edge.1e26462c62c126fe150bd15a5714ddf0be599f09bacbad08b85be02b76ea1ae1.png)

Uç bilişim, bazı bulut hizmetlerini buluttan çıkarıp IoT cihazlarıyla aynı ağda çalışan bilgisayarlara taşımayı içerir. Bulutla yalnızca gerektiğinde iletişim kurulur. Örneğin, olgunluk analizi için meyveleri inceleyen AI modellerini uç cihazlarda çalıştırabilir ve yalnızca olgun ve olgunlaşmamış meyve sayısı gibi analizleri buluta gönderebilirsiniz.

✅ Şimdiye kadar oluşturduğunuz IoT uygulamalarını düşünün. Bunların hangi bölümleri uca taşınabilir?

### Avantajlar

Uç bilişimin avantajları şunlardır:

1. **Hız** - Uç bilişim, zaman açısından hassas veriler için idealdir çünkü işlemler cihazla aynı ağda yapılır, internet üzerinden çağrılar yapılmaz. Bu, daha yüksek hızlar sağlar çünkü iç ağlar, internet bağlantılarından çok daha hızlı çalışabilir ve veriler çok daha kısa mesafeler kat eder.

    > 💁 İnternet bağlantılarında optik kablolar kullanılarak veriler ışık hızında taşınabilse de, verilerin dünya çapında bulut sağlayıcılarına ulaşması zaman alabilir. Örneğin, Avrupa'dan ABD'deki bulut hizmetlerine veri gönderiyorsanız, verilerin Atlantik'i geçmesi en az 28 ms sürer. Bu süre, verilerin transatlantik kabloya ulaşması, elektrikten ışık sinyallerine ve tekrar geri dönmesi ve ardından bulut sağlayıcısına ulaşması için geçen süreyi içermez.

    Uç bilişim ayrıca daha az ağ trafiği gerektirir, bu da internet bağlantısının sınırlı bant genişliği nedeniyle yavaşlama riskini azaltır.

1. **Uzaktan erişilebilirlik** - Uç bilişim, sınırlı veya hiç bağlantı olmadığında ya da bağlantının sürekli kullanımı çok pahalı olduğunda çalışır. Örneğin, altyapının sınırlı olduğu insani yardım bölgelerinde veya gelişmekte olan ülkelerde.

1. **Daha düşük maliyetler** - Veri toplama, depolama, analiz ve eylemleri uç cihazda gerçekleştirmek, bulut hizmetlerinin kullanımını azaltır ve IoT uygulamanızın toplam maliyetini düşürebilir. Son zamanlarda, [NVIDIA'nın Jetson Nano'su](https://developer.nvidia.com/embedded/jetson-nano-developer-kit) gibi AI iş yüklerini çalıştırabilen ve 100 ABD dolarından daha düşük maliyetli cihazlar gibi uç bilişim için tasarlanmış cihazlarda artış olmuştur.

1. **Gizlilik ve güvenlik** - Uç bilişimle, veriler ağınızda kalır ve buluta yüklenmez. Bu, özellikle hassas ve kişisel olarak tanımlanabilir bilgiler için tercih edilir. Ayrıca, analiz edildikten sonra verilerin saklanmasına gerek kalmaz, bu da veri sızıntısı riskini büyük ölçüde azaltır. Örnekler arasında tıbbi veriler ve güvenlik kamerası görüntüleri bulunur.

1. **Güvensiz cihazlarla başa çıkma** - Güvenlik açıkları bilinen cihazları doğrudan ağınıza veya internete bağlamak istemiyorsanız, bu cihazları ayrı bir ağa bağlayarak bir IoT Edge cihazı geçidi olarak kullanabilirsiniz. Bu uç cihaz, daha geniş ağınıza veya internete bir bağlantıya da sahip olabilir ve veri akışlarını yönetebilir.

1. **Uyumsuz cihazlar için destek** - IoT Hub'a bağlanamayan cihazlarınız varsa, örneğin yalnızca HTTP bağlantıları kullanabilen veya yalnızca Bluetooth ile bağlanabilen cihazlar, bir IoT Edge cihazını geçit cihazı olarak kullanabilirsiniz. Bu cihaz, mesajları IoT Hub'a iletebilir.

✅ Araştırma yapın: Uç bilişimin başka hangi avantajları olabilir?

### Dezavantajlar

Uç bilişimin dezavantajları vardır ve bazı durumlarda bulut daha iyi bir seçenek olabilir:

1. **Ölçek ve esneklik** - Bulut bilişim, ağ ve veri ihtiyaçlarına gerçek zamanlı olarak sunucu ve diğer kaynakları ekleyerek veya azaltarak uyum sağlar. Daha fazla uç bilgisayar eklemek, manuel olarak daha fazla cihaz eklemeyi gerektirir.

1. **Güvenilirlik ve dayanıklılık** - Bulut bilişim, genellikle birden fazla konumda birden fazla sunucu sağlar ve bu da yedeklilik ve felaket kurtarma sağlar. Uçta aynı düzeyde yedeklilik sağlamak büyük yatırımlar ve çok fazla yapılandırma çalışması gerektirir.

1. **Bakım** - Bulut hizmet sağlayıcıları sistem bakımı ve güncellemeleri sağlar.

✅ Araştırma yapın: Uç bilişimin başka hangi dezavantajları olabilir?

Dezavantajlar, bulut kullanmanın avantajlarının tam tersidir - bu cihazları kendiniz oluşturup yönetmeniz gerekir, bulut sağlayıcılarının uzmanlığına ve ölçeğine güvenemezsiniz.

Bazı riskler, uç bilişimin doğası gereği hafifletilir. Örneğin, bir fabrikada makinelerden veri toplayan bir uç cihaz çalıştırıyorsanız, bazı felaket kurtarma senaryolarını düşünmenize gerek yoktur. Fabrikanın elektriği kesilirse, verileri işleyen uç cihazın yedeğine ihtiyacınız olmaz çünkü verileri üreten makineler de elektriksiz kalacaktır.

IoT sistemleri için genellikle bulut ve uç bilişimin bir karışımını kullanmak istersiniz. Sistemin, müşterilerinin ve bakımını yapanların ihtiyaçlarına göre her hizmetten yararlanabilirsiniz.

## Azure IoT Edge

![Azure IoT Edge logosu](../../../../../translated_images/tr/azure-iot-edge-logo.c1c076749b5cba2e8755262fadc2f19ca1146b948d76990b1229199ac2292d79.png)

Azure IoT Edge, iş yüklerini buluttan uca taşımaya yardımcı olabilecek bir hizmettir. Bir cihazı uç cihaz olarak ayarlarsınız ve buluttan bu uç cihaza kod dağıtabilirsiniz. Bu, bulut ve uç yeteneklerini karıştırmanıza olanak tanır.

> 🎓 *İş yükleri*, AI modelleri, uygulamalar veya sunucusuz işlevler gibi bir tür iş yapan herhangi bir hizmet için kullanılan bir terimdir.

Örneğin, bir görüntü sınıflandırıcısını bulutta eğitebilir, ardından buluttan bir uç cihaza dağıtabilirsiniz. IoT cihazınız daha sonra görüntüleri sınıflandırma için uç cihaza gönderir, internet üzerinden göndermek yerine. Modelin yeni bir iterasyonunu dağıtmanız gerekirse, bulutta eğitebilir ve IoT Edge'i kullanarak uç cihazdaki modeli yeni iterasyonunuza güncelleyebilirsiniz.

> 🎓 IoT Edge'e dağıtılan yazılımlar *modüller* olarak bilinir. Varsayılan olarak IoT Edge, `edgeAgent` ve `edgeHub` gibi IoT Hub ile iletişim kuran modülleri çalıştırır. Bir görüntü sınıflandırıcısı dağıttığınızda, bu ek bir modül olarak dağıtılır.

IoT Edge, IoT Hub'a entegredir, bu nedenle IoT cihazlarını yönetmek için kullandığınız aynı hizmeti kullanarak uç cihazları yönetebilirsiniz ve aynı güvenlik seviyesine sahiptir.

IoT Edge, *konteynerler* adı verilen kodları çalıştırır - bilgisayarınızdaki diğer uygulamalardan izole edilmiş şekilde çalışan kendi kendine yeten uygulamalar. Bir konteyner çalıştırdığınızda, bilgisayarınızda ayrı bir bilgisayar gibi davranır; kendi yazılımı, hizmetleri ve uygulamaları çalışır. Çoğu zaman konteynerler, bir klasör gibi şeyleri paylaşmayı seçmediğiniz sürece bilgisayarınızdaki hiçbir şeye erişemez. Konteyner daha sonra bir açık port üzerinden hizmetleri sunar ve bu porta bağlanabilir veya ağınıza açabilirsiniz.

![Bir web isteğinin bir konteynere yönlendirilmesi](../../../../../translated_images/tr/container-web-browser.4ee81dd4f0d8838ce622b2a0d600b6a4322b5d4fe43159facd87b7b34f84d66a.png)

Örneğin, bir konteynerde port 80'de (varsayılan HTTP portu) çalışan bir web sitesi olabilir ve bunu bilgisayarınızdan da port 80 üzerinden sunabilirsiniz.

✅ Araştırma yapın: Konteynerler ve Docker veya Moby gibi hizmetler hakkında bilgi edinin.

Custom Vision'ı kullanarak görüntü sınıflandırıcılarını indirip bunları konteyner olarak dağıtabilirsiniz. Bu konteynerler doğrudan bir cihaza çalıştırılabilir veya IoT Edge aracılığıyla dağıtılabilir. Bir konteynerde çalıştırıldıklarında, bulut versiyonuyla aynı REST API'si kullanılarak erişilebilirler, ancak uç cihazdaki konteyneri çalıştıran uç cihazın uç noktasına işaret eder.

## Bir IoT Edge Cihazı Kaydedin

Bir IoT Edge cihazını kullanmak için, IoT Hub'da kaydedilmesi gerekir.

### Görev - Bir IoT Edge cihazı kaydedin

1. `fruit-quality-detector` kaynak grubunda bir IoT Hub oluşturun. `fruit-quality-detector` tabanlı benzersiz bir ad verin.

1. IoT Hub'ınızda `fruit-quality-detector-edge` adında bir IoT Edge cihazı kaydedin. Bunu yapmak için kullanılan komut, bir uç cihaz olmayan bir cihaz kaydetmek için kullanılan komuta benzerdir, ancak `--edge-enabled` bayrağını geçirirsiniz.

    ```sh
    az iot hub device-identity create --edge-enabled \
                                      --device-id fruit-quality-detector-edge \
                                      --hub-name <hub_name>
    ```

    `<hub_name>` yerine IoT Hub'ınızın adını yazın.

1. Aşağıdaki komutu kullanarak cihazınızın bağlantı dizesini alın:

    ```sh
    az iot hub device-identity connection-string show --device-id fruit-quality-detector-edge \
                                                      --output table \
                                                      --hub-name <hub_name>
    ```

    `<hub_name>` yerine IoT Hub'ınızın adını yazın.

    Çıktıda gösterilen bağlantı dizesinin bir kopyasını alın.

## Bir IoT Edge Cihazı Kurun

Uç cihaz kaydını IoT Hub'da oluşturduktan sonra, uç cihazı kurabilirsiniz.

### Görev - IoT Edge Çalışma Zamanını Yükleyin ve Başlatın

**IoT Edge çalışma zamanı yalnızca Linux konteynerlerini çalıştırır.** Linux'ta veya Linux Sanal Makineleri kullanarak Windows'ta çalıştırılabilir.

* Eğer IoT cihazınız olarak bir Raspberry Pi kullanıyorsanız, bu desteklenen bir Linux sürümünü çalıştırır ve IoT Edge çalışma zamanını barındırabilir. [Microsoft dokümanlarındaki Azure IoT Edge for Linux yükleme kılavuzunu](https://docs.microsoft.com/azure/iot-edge/how-to-install-iot-edge?WT.mc_id=academic-17441-jabenn) takip ederek IoT Edge'i yükleyin ve bağlantı dizesini ayarlayın.

    > 💁 Unutmayın, Raspberry Pi OS, Debian Linux'un bir varyantıdır.

* Eğer bir Raspberry Pi kullanmıyorsanız ancak bir Linux bilgisayarınız varsa, IoT Edge çalışma zamanını çalıştırabilirsiniz. [Microsoft dokümanlarındaki Azure IoT Edge for Linux yükleme kılavuzunu](https://docs.microsoft.com/azure/iot-edge/how-to-install-iot-edge?WT.mc_id=academic-17441-jabenn) takip ederek IoT Edge'i yükleyin ve bağlantı dizesini ayarlayın.

* Eğer Windows kullanıyorsanız, IoT Edge çalışma zamanını bir Linux Sanal Makinesinde yükleyebilirsiniz. [Microsoft dokümanlarındaki bir Windows cihazına ilk IoT Edge modülünüzü dağıtma hızlı başlangıcının IoT Edge çalışma zamanını yükleme ve başlatma bölümünü](https://docs.microsoft.com/azure/iot-edge/quickstart?WT.mc_id=academic-17441-jabenn#install-and-start-the-iot-edge-runtime) takip edin. *Bir modül dağıtın* bölümüne ulaştığınızda durabilirsiniz.

* Eğer macOS kullanıyorsanız, IoT Edge cihazınız olarak kullanmak üzere bulutta bir sanal makine (VM) oluşturabilirsiniz. Bunlar, internet üzerinden erişebileceğiniz bulutta oluşturabileceğiniz bilgisayarlardır. IoT Edge yüklü bir Linux VM oluşturabilirsiniz. Bunun nasıl yapılacağına dair talimatlar için [IoT Edge çalıştıran bir sanal makine oluşturma kılavuzunu](vm-iotedge.md) takip edin.

## Modelinizi Dışa Aktarın

Sınıflandırıcıyı uçta çalıştırmak için, Custom Vision'dan dışa aktarılması gerekir. Custom Vision, iki tür model oluşturabilir - standart modeller ve kompakt modeller. Kompakt modeller, modelin boyutunu küçültmek için çeşitli teknikler kullanır ve bu da onu IoT cihazlarına indirilebilir ve dağıtılabilir hale getirir.

Görüntü sınıflandırıcısını oluşturduğunuzda, yiyecek görüntüleri üzerinde eğitim için optimize edilmiş bir model versiyonu olan *Food* alanını kullandınız. Custom Vision'da, projenizin alanını değiştirerek, eğitim verilerinizi kullanarak yeni alanla yeni bir model eğitebilirsiniz. Custom Vision tarafından desteklenen tüm alanlar standart ve kompakt olarak mevcuttur.

### Görev - Modelinizi Food (compact) alanını kullanarak eğitin
1. [CustomVision.ai](https://customvision.ai) portalunu açın ve henüz açık değilse giriş yapın. Ardından `fruit-quality-detector` projenizi açın.

1. **Ayarlar** düğmesini (⚙ simgesi) seçin.

1. *Alanlar* listesinden *Food (compact)* seçeneğini seçin.

1. *Export Capabilities* altında, *Basic platforms (Tensorflow, CoreML, ONNX, ...)* seçeneğinin seçili olduğundan emin olun.

1. Ayarlar sayfasının en altındaki **Değişiklikleri Kaydet** düğmesini seçin.

1. **Train** düğmesini kullanarak modeli yeniden eğitin ve *Quick training* seçeneğini seçin.

### Görev - modelinizi dışa aktarın

Model eğitildikten sonra bir konteyner olarak dışa aktarılması gerekir.

1. **Performance** sekmesini seçin ve kompakt alan kullanılarak eğitilmiş en son iterasyonu bulun.

1. Üstteki **Export** düğmesini seçin.

1. **DockerFile** seçeneğini seçin ve edge cihazınıza uygun bir versiyonu seçin:

    * IoT Edge'i bir Linux bilgisayarda, Windows bilgisayarda veya Sanal Makinede çalıştırıyorsanız, *Linux* versiyonunu seçin.
    * IoT Edge'i bir Raspberry Pi üzerinde çalıştırıyorsanız, *ARM (Raspberry Pi 3)* versiyonunu seçin.

> 🎓 Docker, konteynerleri yönetmek için en popüler araçlardan biridir ve bir DockerFile, konteynerin nasıl kurulacağına dair bir talimat setidir.

1. Custom Vision'ın ilgili dosyaları oluşturması için **Export** seçeneğini seçin, ardından bir zip dosyası olarak indirmek için **Download** seçeneğini seçin.

1. Dosyaları bilgisayarınıza kaydedin ve klasörü açın.

## Konteynerinizi dağıtıma hazırlayın

![Konteynerler oluşturulur, bir konteyner kaydına gönderilir ve IoT Edge kullanılarak edge cihazına dağıtılır](../../../../../translated_images/tr/container-edge-flow.c246050dd60ceefdb6ace026a4ce5c6aa4112bb5898ae23fbb2ab4be29ae3e1b.png)

Modelinizi indirdikten sonra, bir konteyner olarak oluşturulması ve bir konteyner kaydına gönderilmesi gerekir - konteynerleri saklayabileceğiniz çevrimiçi bir yer. IoT Edge daha sonra konteyneri kayıttan indirip cihazınıza gönderebilir.

![Azure Container Registry logosu](../../../../../translated_images/tr/azure-container-registry-logo.09494206991d4b295025ebff7d4e2900325e527a59184ffbc8464b6ab59654be.png)

Bu ders için kullanacağınız konteyner kaydı Azure Container Registry'dir. Bu ücretsiz bir hizmet değildir, bu yüzden işiniz bittiğinde [projenizi temizleyerek](../../../clean-up.md) para tasarrufu yapmayı unutmayın.

> 💁 Azure Container Registry kullanmanın maliyetlerini [Azure Container Registry fiyatlandırma sayfasında](https://azure.microsoft.com/pricing/details/container-registry/?WT.mc_id=academic-17441-jabenn) görebilirsiniz.

### Görev - Docker'ı yükleyin

Sınıflandırıcıyı oluşturmak ve dağıtmak için [Docker](https://www.docker.com/) yüklemeniz gerekebilir.

Bunu yalnızca IoT Edge'i yüklediğiniz cihazdan farklı bir cihazda konteyner oluşturmayı planlıyorsanız yapmanız gerekir - IoT Edge'i yüklemenin bir parçası olarak Docker sizin için yüklenir.

1. Docker konteynerini IoT Edge cihazınızdan farklı bir cihazda oluşturuyorsanız, [Docker yükleme sayfasındaki](https://www.docker.com/products/docker-desktop) talimatları izleyerek Docker Desktop veya Docker motorunu yükleyin. Yükleme tamamlandıktan sonra çalıştığından emin olun.

### Görev - bir konteyner kaydı kaynağı oluşturun

1. Terminal veya komut istemcinizden aşağıdaki komutu çalıştırarak bir Azure Container Registry kaynağı oluşturun:

    ```sh
    az acr create --resource-group fruit-quality-detector \
                  --sku Basic \
                  --name <Container registry name>
    ```

    `<Container registry name>` öğesini yalnızca harf ve rakamlar kullanarak konteyner kaydınız için benzersiz bir adla değiştirin. Bu adı `fruitqualitydetector` üzerine kurun. Bu ad, konteyner kaydına erişmek için URL'nin bir parçası haline gelir, bu nedenle küresel olarak benzersiz olmalıdır.

1. Aşağıdaki komutla Azure Container Registry'ye giriş yapın:

    ```sh
    az acr login --name <Container registry name>
    ```

    `<Container registry name>` öğesini konteyner kaydınız için kullandığınız adla değiştirin.

1. Aşağıdaki komutla konteyner kaydını yönetici moduna ayarlayın, böylece bir şifre oluşturabilirsiniz:

    ```sh
    az acr update --admin-enabled true \
                 --name <Container registry name>
    ```

    `<Container registry name>` öğesini konteyner kaydınız için kullandığınız adla değiştirin.

1. Aşağıdaki komutla konteyner kaydınız için şifreler oluşturun:

    ```sh
     az acr credential renew --password-name password \
                             --output table \
                             --name <Container registry name>
    ```

    `<Container registry name>` öğesini konteyner kaydınız için kullandığınız adla değiştirin.

    `PASSWORD` değerini bir yere kaydedin, çünkü bunu daha sonra kullanmanız gerekecek.

### Görev - konteynerinizi oluşturun

Custom Vision'dan indirdiğiniz şey, konteynerin nasıl oluşturulması gerektiğine dair talimatlar içeren bir DockerFile ve özel görüntü modelinizi barındırmak için konteyner içinde çalıştırılacak uygulama koduydu. Ayrıca bir REST API içerir. Docker'ı kullanarak DockerFile'dan etiketlenmiş bir konteyner oluşturabilir ve ardından bunu konteyner kaydınıza gönderebilirsiniz.

> 🎓 Konteynerlere bir ad ve versiyon tanımlayan bir etiket verilir. Bir konteyneri güncellemeniz gerektiğinde, aynı etiketi kullanarak daha yeni bir versiyonla oluşturabilirsiniz.

1. Terminal veya komut istemcinizi açın ve Custom Vision'dan indirdiğiniz açılmış modelin bulunduğu dizine gidin.

1. Görüntüyü oluşturmak ve etiketlemek için aşağıdaki komutu çalıştırın:

    ```sh
    docker build --platform <platform> -t <Container registry name>.azurecr.io/classifier:v1 .
    ```

    `<platform>` öğesini bu konteynerin çalışacağı platformla değiştirin. IoT Edge'i bir Raspberry Pi üzerinde çalıştırıyorsanız, bunu `linux/armhf` olarak ayarlayın, aksi takdirde `linux/amd64` olarak ayarlayın.

    > 💁 Bu komutu IoT Edge'i çalıştırdığınız cihazdan çalıştırıyorsanız, örneğin Raspberry Pi'den çalıştırıyorsanız, `--platform <platform>` kısmını atlayabilirsiniz çünkü varsayılan olarak mevcut platformu kullanır.

    `<Container registry name>` öğesini konteyner kaydınız için kullandığınız adla değiştirin.

    > 💁 Linux veya Raspberry Pi OS kullanıyorsanız bu komutu çalıştırmak için `sudo` kullanmanız gerekebilir.

    Docker görüntüyü oluşturacak ve gerekli tüm yazılımları yapılandıracaktır. Görüntü daha sonra `classifier:v1` olarak etiketlenecektir.

    ```output
    ➜  d4ccc45da0bb478bad287128e1274c3c.DockerFile.Linux docker build --platform linux/amd64 -t  fruitqualitydetectorjimb.azurecr.io/classifier:v1 .
    [+] Building 102.4s (11/11) FINISHED
     => [internal] load build definition from Dockerfile
     => => transferring dockerfile: 131B
     => [internal] load .dockerignore
     => => transferring context: 2B
     => [internal] load metadata for docker.io/library/python:3.7-slim
     => [internal] load build context
     => => transferring context: 905B
     => [1/6] FROM docker.io/library/python:3.7-slim@sha256:b21b91c9618e951a8cbca5b696424fa5e820800a88b7e7afd66bba0441a764d6
     => => resolve docker.io/library/python:3.7-slim@sha256:b21b91c9618e951a8cbca5b696424fa5e820800a88b7e7afd66bba0441a764d6
     => => sha256:b4d181a07f8025e00e0cb28f1cc14613da2ce26450b80c54aea537fa93cf3bda 27.15MB / 27.15MB
     => => sha256:de8ecf497b753094723ccf9cea8a46076e7cb845f333df99a6f4f397c93c6ea9 2.77MB / 2.77MB
     => => sha256:707b80804672b7c5d8f21e37c8396f319151e1298d976186b4f3b76ead9f10c8 10.06MB / 10.06MB
     => => sha256:b21b91c9618e951a8cbca5b696424fa5e820800a88b7e7afd66bba0441a764d6 1.86kB / 1.86kB
     => => sha256:44073386687709c437586676b572ff45128ff1f1570153c2f727140d4a9accad 1.37kB / 1.37kB
     => => sha256:3d94f0f2ca798607808b771a7766f47ae62a26f820e871dd488baeccc69838d1 8.31kB / 8.31kB
     => => sha256:283715715396fd56d0e90355125fd4ec57b4f0773f306fcd5fa353b998beeb41 233B / 233B
     => => sha256:8353afd48f6b84c3603ea49d204bdcf2a1daada15f5d6cad9cc916e186610a9f 2.64MB / 2.64MB
     => => extracting sha256:b4d181a07f8025e00e0cb28f1cc14613da2ce26450b80c54aea537fa93cf3bda
     => => extracting sha256:de8ecf497b753094723ccf9cea8a46076e7cb845f333df99a6f4f397c93c6ea9
     => => extracting sha256:707b80804672b7c5d8f21e37c8396f319151e1298d976186b4f3b76ead9f10c8
     => => extracting sha256:283715715396fd56d0e90355125fd4ec57b4f0773f306fcd5fa353b998beeb41
     => => extracting sha256:8353afd48f6b84c3603ea49d204bdcf2a1daada15f5d6cad9cc916e186610a9f
     => [2/6] RUN pip install -U pip
     => [3/6] RUN pip install --no-cache-dir numpy~=1.17.5 tensorflow~=2.0.2 flask~=1.1.2 pillow~=7.2.0
     => [4/6] RUN pip install --no-cache-dir mscviplib==2.200731.16
     => [5/6] COPY app /app
     => [6/6] WORKDIR /app
     => exporting to image
     => => exporting layers
     => => writing image sha256:1846b6f134431f78507ba7c079358ed66d944c0e185ab53428276bd822400386
     => => naming to fruitqualitydetectorjimb.azurecr.io/classifier:v1
    ```

### Görev - konteynerinizi konteyner kaydınıza gönderin

1. Konteynerinizi konteyner kaydınıza göndermek için aşağıdaki komutu kullanın:

    ```sh
    docker push <Container registry name>.azurecr.io/classifier:v1
    ```

    `<Container registry name>` öğesini konteyner kaydınız için kullandığınız adla değiştirin.

    > 💁 Linux kullanıyorsanız bu komutu çalıştırmak için `sudo` kullanmanız gerekebilir.

    Konteyner konteyner kaydına gönderilecektir.

    ```output
    ➜  d4ccc45da0bb478bad287128e1274c3c.DockerFile.Linux docker push fruitqualitydetectorjimb.azurecr.io/classifier:v1
    The push refers to repository [fruitqualitydetectorjimb.azurecr.io/classifier]
    5f70bf18a086: Pushed 
    8a1ba9294a22: Pushed 
    56cf27184a76: Pushed 
    b32154f3f5dd: Pushed 
    36103e9a3104: Pushed 
    e2abb3cacca0: Pushed 
    4213fd357bbe: Pushed 
    7ea163ba4dce: Pushed 
    537313a13d90: Pushed 
    764055ebc9a7: Pushed 
    v1: digest: sha256:ea7894652e610de83a5a9e429618e763b8904284253f4fa0c9f65f0df3a5ded8 size: 2423
    ```

1. Gönderimi doğrulamak için aşağıdaki komutla kaydınızdaki konteynerleri listeleyebilirsiniz:

    ```sh
    az acr repository list --output table \
                           --name <Container registry name> 
    ```

    `<Container registry name>` öğesini konteyner kaydınız için kullandığınız adla değiştirin.

    ```output
    ➜  d4ccc45da0bb478bad287128e1274c3c.DockerFile.Linux az acr repository list --name fruitqualitydetectorjimb --output table
    Result
    ----------
    classifier
    ```

    Çıktıda sınıflandırıcınızı göreceksiniz.

## Konteynerinizi dağıtın

Konteyneriniz artık IoT Edge cihazınıza dağıtılabilir. Dağıtım için bir dağıtım manifesti tanımlamanız gerekir - edge cihazına dağıtılacak modülleri listeleyen bir JSON belgesi.

### Görev - dağıtım manifestini oluşturun

1. Bilgisayarınızda bir yerde `deployment.json` adlı yeni bir dosya oluşturun.

1. Bu dosyaya aşağıdakileri ekleyin:

    ```json
    {
        "content": {
            "modulesContent": {
                "$edgeAgent": {
                    "properties.desired": {
                        "schemaVersion": "1.1",
                        "runtime": {
                            "type": "docker",
                            "settings": {
                                "minDockerVersion": "v1.25",
                                "loggingOptions": "",
                                "registryCredentials": {
                                    "ClassifierRegistry": {
                                        "username": "<Container registry name>",
                                        "password": "<Container registry password>",
                                        "address": "<Container registry name>.azurecr.io"
                                      }
                                }
                            }
                        },
                        "systemModules": {
                            "edgeAgent": {
                                "type": "docker",
                                "settings": {
                                    "image": "mcr.microsoft.com/azureiotedge-agent:1.1",
                                    "createOptions": "{}"
                                }
                            },
                            "edgeHub": {
                                "type": "docker",
                                "status": "running",
                                "restartPolicy": "always",
                                "settings": {
                                    "image": "mcr.microsoft.com/azureiotedge-hub:1.1",
                                    "createOptions": "{\"HostConfig\":{\"PortBindings\":{\"5671/tcp\":[{\"HostPort\":\"5671\"}],\"8883/tcp\":[{\"HostPort\":\"8883\"}],\"443/tcp\":[{\"HostPort\":\"443\"}]}}}"
                                }
                            }
                        },
                        "modules": {
                            "ImageClassifier": {
                                "version": "1.0",
                                "type": "docker",
                                "status": "running",
                                "restartPolicy": "always",
                                "settings": {
                                    "image": "<Container registry name>.azurecr.io/classifier:v1",
                                    "createOptions": "{\"ExposedPorts\": {\"80/tcp\": {}},\"HostConfig\": {\"PortBindings\": {\"80/tcp\": [{\"HostPort\": \"80\"}]}}}"
                                }
                            }
                        }
                    }
                },
                "$edgeHub": {
                    "properties.desired": {
                        "schemaVersion": "1.1",
                        "routes": {
                            "upstream": "FROM /messages/* INTO $upstream"
                        },
                        "storeAndForwardConfiguration": {
                            "timeToLiveSecs": 7200
                        }
                    }
                }
            }
        }
    }
    ```

    > 💁 Bu dosyayı [code-deployment/deployment](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge/code-deployment/deployment) klasöründe bulabilirsiniz.

    `<Container registry name>` öğesini konteyner kaydınız için kullandığınız adla değiştirin. Biri `ImageClassifier` modül bölümünde, diğer ikisi `registryCredentials` bölümünde.

    `registryCredentials` bölümündeki `<Container registry password>` öğesini konteyner kaydı şifrenizle değiştirin.

1. Dağıtım manifestinizi içeren klasörden aşağıdaki komutu çalıştırın:

    ```sh
    az iot edge set-modules --device-id fruit-quality-detector-edge \
                            --content deployment.json \
                            --hub-name <hub_name>
    ```

    `<hub_name>` öğesini IoT Hub adınızla değiştirin.

    Görüntü sınıflandırıcı modülü edge cihazınıza dağıtılacaktır.

### Görev - sınıflandırıcının çalıştığını doğrulayın

1. IoT Edge cihazına bağlanın:

    * IoT Edge'i çalıştırmak için bir Raspberry Pi kullanıyorsanız, terminalinizden veya VS Code'da bir uzak SSH oturumu üzerinden ssh ile bağlanın.
    * IoT Edge'i Windows'da bir Linux konteynerinde çalıştırıyorsanız, IoT Edge cihazına bağlanmak için [başarılı yapılandırmayı doğrulama kılavuzundaki](https://docs.microsoft.com/azure/iot-edge/how-to-install-iot-edge-on-windows?WT.mc_id=academic-17441-jabenn&view=iotedge-2018-06&tabs=powershell#verify-successful-configuration) adımları izleyin.
    * IoT Edge'i bir sanal makinede çalıştırıyorsanız, VM oluştururken ayarladığınız `adminUsername` ve `password` kullanarak ve IP adresi veya DNS adını kullanarak makineye SSH ile bağlanabilirsiniz:

        ```sh
        ssh <adminUsername>@<IP address>
        ```

        Veya:

        ```sh
        ssh <adminUsername>@<DNS Name>
        ```

        İstendiğinde şifrenizi girin.

1. Bağlandıktan sonra IoT Edge modüllerinin listesini almak için aşağıdaki komutu çalıştırın:

    ```sh
    iotedge list
    ```

    > 💁 Bu komutu `sudo` ile çalıştırmanız gerekebilir.

    Çalışan modülleri göreceksiniz:

    ```output
    jim@fruit-quality-detector-jimb:~$ iotedge list
    NAME             STATUS           DESCRIPTION      CONFIG
    ImageClassifier  running          Up 42 minutes    fruitqualitydetectorjimb.azurecr.io/classifier:v1
    edgeAgent        running          Up 42 minutes    mcr.microsoft.com/azureiotedge-agent:1.1
    edgeHub          running          Up 42 minutes    mcr.microsoft.com/azureiotedge-hub:1.1
    ```

1. Görüntü sınıflandırıcı modülünün günlüklerini aşağıdaki komutla kontrol edin:

    ```sh
    iotedge logs ImageClassifier
    ```

    > 💁 Bu komutu `sudo` ile çalıştırmanız gerekebilir.

    ```output
    jim@fruit-quality-detector-jimb:~$ iotedge logs ImageClassifier
    2021-07-05 20:30:15.387144: I tensorflow/core/platform/cpu_feature_guard.cc:142] Your CPU supports instructions that this TensorFlow binary was not compiled to use: AVX2 FMA
    2021-07-05 20:30:15.392185: I tensorflow/core/platform/profile_utils/cpu_utils.cc:94] CPU Frequency: 2394450000 Hz
    2021-07-05 20:30:15.392712: I tensorflow/compiler/xla/service/service.cc:168] XLA service 0x55ed9ac83470 executing computations on platform Host. Devices:
    2021-07-05 20:30:15.392806: I tensorflow/compiler/xla/service/service.cc:175]   StreamExecutor device (0): Host, Default Version
    Loading model...Success!
    Loading labels...2 found. Success!
     * Serving Flask app "app" (lazy loading)
     * Environment: production
       WARNING: This is a development server. Do not use it in a production deployment.
       Use a production WSGI server instead.
     * Debug mode: off
     * Running on http://0.0.0.0:80/ (Press CTRL+C to quit)
    ```

### Görev - görüntü sınıflandırıcıyı test edin

1. IoT Edge aracını çalıştıran bilgisayarın IP adresini veya ana bilgisayar adını kullanarak görüntü sınıflandırıcıyı test etmek için CURL kullanabilirsiniz. IP adresini bulun:

    * IoT Edge'in çalıştığı aynı makinedeyseniz, ana bilgisayar adı olarak `localhost` kullanabilirsiniz.
    * Bir VM kullanıyorsanız, VM'nin IP adresini veya DNS adını kullanabilirsiniz.
    * Aksi takdirde IoT Edge'i çalıştıran makinenin IP adresini şu şekilde bulabilirsiniz:
      * Windows 10'da [IP adresinizi bulma kılavuzunu](https://support.microsoft.com/windows/find-your-ip-address-f21a9bbc-c582-55cd-35e0-73431160a1b9?WT.mc_id=academic-17441-jabenn) takip edin.
      * macOS'ta [Mac'te IP adresinizi nasıl bulacağınızı](https://www.hellotech.com/guide/for/how-to-find-ip-address-on-mac) öğrenin.
      * Linux'ta [Linux'ta IP adresinizi bulma kılavuzundaki](https://opensource.com/article/18/5/how-find-ip-address-linux) özel IP adresinizi bulma bölümünü takip edin.

1. Yerel bir dosya ile konteyneri test etmek için aşağıdaki curl komutunu çalıştırabilirsiniz:

    ```sh
    curl --location \
         --request POST 'http://<IP address or name>/image' \
         --header 'Content-Type: image/png' \
         --data-binary '@<file_Name>' 
    ```

    `<IP address or name>` öğesini IoT Edge'i çalıştıran bilgisayarın IP adresi veya ana bilgisayar adıyla değiştirin. `<file_Name>` öğesini test edilecek dosyanın adıyla değiştirin.

    Çıktıda tahmin sonuçlarını göreceksiniz:

    ```output
    {
        "created": "2021-07-05T21:44:39.573181",
        "id": "",
        "iteration": "",
        "predictions": [
            {
                "boundingBox": null,
                "probability": 0.9995615482330322,
                "tagId": "",
                "tagName": "ripe"
            },
            {
                "boundingBox": null,
                "probability": 0.0004384400090202689,
                "tagId": "",
                "tagName": "unripe"
            }
        ],
        "project": ""
    }
    ```

    > 💁 Burada bir tahmin anahtarı sağlamaya gerek yoktur, çünkü bu bir Azure kaynağı kullanmıyor. Bunun yerine güvenlik, dahili güvenlik ihtiyaçlarına dayalı olarak dahili ağda yapılandırılır, halka açık bir uç nokta ve bir API anahtarına güvenmek yerine.

## IoT Edge cihazınızı kullanın

Artık Görüntü Sınıflandırıcı IoT Edge cihazınıza dağıtıldı, IoT cihazınızdan kullanabilirsiniz.

### Görev - IoT Edge cihazınızı kullanın

IoT Edge sınıflandırıcıyı kullanarak görüntüleri sınıflandırmak için ilgili kılavuzu takip edin:

* [Arduino - Wio Terminal](wio-terminal.md)
* [Tek kartlı bilgisayar - Raspberry Pi/Sanal IoT cihazı](single-board-computer.md)

### Model yeniden eğitimi

IoT Edge üzerinde görüntü sınıflandırıcı çalıştırmanın dezavantajlarından biri, Custom Vision projenize bağlı olmamasıdır. Custom Vision'daki **Predictions** sekmesine bakarsanız, Edge tabanlı sınıflandırıcı kullanılarak sınıflandırılan görüntüleri göremezsiniz.

Bu beklenen bir davranıştır - görüntüler sınıflandırma için buluta gönderilmez, bu yüzden bulutta mevcut olmazlar. IoT Edge kullanmanın avantajlarından biri gizliliktir, görüntülerin ağınızdan çıkmamasını sağlar, bir diğeri ise çevrimdışı çalışabilmektir, yani cihazın internet bağlantısı olmadığında görüntülerin yüklenmesine güvenmek zorunda kalmazsınız. Dezavantajı ise modelinizi geliştirmektir - görüntüleri manuel olarak yeniden sınıflandırmak ve görüntü sınıflandırıcıyı yeniden eğitmek için başka bir yol uygulamanız gerekir.

✅ Sınıflandırıcıyı yeniden eğitmek için görüntüleri yüklemenin yollarını düşünün.

---

## 🚀 Zorluk

AI modellerini edge cihazlarda çalıştırmak bulutta çalıştırmaktan daha hızlı olabilir - ağ geçişi daha kısadır. Ancak, modeli çalıştıran donanım buluttaki kadar güçlü olmayabileceğinden daha yavaş da olabilir.

Zamanlamalar yapın ve edge cihazınıza yapılan çağrının buluta yapılan çağrıdan daha hızlı mı yoksa daha yavaş mı olduğunu karşılaştırın? Farkı veya farkın olmamasını açıklamak için nedenler düşünün. Edge'de AI modellerini daha hızlı çalıştırmanın yollarını araştırın.

## Ders sonrası test

[Ders sonrası test](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/34)

## İnceleme ve Kendi Kendine Çalışma

* Konteynerler hakkında daha fazla bilgi edinmek için [Wikipedia'daki OS-level virtualization sayfasını](https://wikipedia.org/wiki/OS-level_virtualization) okuyun.
* 5G'nin uç bilişimi nasıl genişletebileceğine odaklanarak uç bilişim hakkında daha fazla bilgi edinin: [NetworkWorld'deki "Uç bilişim nedir ve neden önemlidir?" makalesi](https://www.networkworld.com/article/3224893/what-is-edge-computing-and-how-its-changing-the-network.html)
* IoT Edge'de yapay zeka hizmetlerini çalıştırmayı öğrenmek için şu bölümü izleyin: [Microsoft Channel9'daki Learn Live'da "Uçta dil algılama yapmak için önceden oluşturulmuş bir AI hizmetiyle Azure IoT Edge'i nasıl kullanacağınızı öğrenin" bölümü](https://channel9.msdn.com/Shows/Learn-Live/Sharpen-Your-AI-Edge-Skills-Episode-4-Learn-How-to-Use-Azure-IoT-Edge-on-a-Pre-Built-AI-Service-on-t?WT.mc_id=academic-17441-jabenn)

## Ödev

[Uçta diğer hizmetleri çalıştırın](assignment.md)

---

**Feragatname**:  
Bu belge, AI çeviri hizmeti [Co-op Translator](https://github.com/Azure/co-op-translator) kullanılarak çevrilmiştir. Doğruluk için çaba göstersek de, otomatik çevirilerin hata veya yanlışlıklar içerebileceğini lütfen unutmayın. Belgenin orijinal dili, yetkili kaynak olarak kabul edilmelidir. Kritik bilgiler için profesyonel insan çevirisi önerilir. Bu çevirinin kullanımından kaynaklanan yanlış anlamalar veya yanlış yorumlamalar için sorumluluk kabul etmiyoruz.