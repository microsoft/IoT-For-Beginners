# Uygulama Mantığınızı Buluta Taşıyın

![Bu dersin genel bir sketchnote özeti](../../../../../translated_images/tr/lesson-9.dfe99c8e891f48e1.webp)

> Sketchnote: [Nitya Narasimhan](https://github.com/nitya). Daha büyük bir versiyon için görsele tıklayın.

Bu ders, [IoT for Beginners Projesi 2 - Dijital Tarım serisi](https://youtube.com/playlist?list=PLmsFUfdnGr3yCutmcVg6eAUEfsGiFXgcx) kapsamında [Microsoft Reactor](https://developer.microsoft.com/reactor/?WT.mc_id=academic-17441-jabenn) tarafından öğretilmiştir.

[![IoT cihazınızı sunucusuz kodla kontrol edin](https://img.youtube.com/vi/VVZDcs5u1_I/0.jpg)](https://youtu.be/VVZDcs5u1_I)

## Ders Öncesi Test

[Ders öncesi test](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/17)

## Giriş

Son derste, bitki toprak nemi izleme ve röle kontrolünüzü bulut tabanlı bir IoT hizmetine nasıl bağlayacağınızı öğrendiniz. Bir sonraki adım, rölenin zamanlamasını kontrol eden sunucu kodunu buluta taşımaktır. Bu derste, bunu sunucusuz fonksiyonlar kullanarak nasıl yapacağınızı öğreneceksiniz.

Bu derste şunları ele alacağız:

* [Sunucusuz nedir?](../../../../../2-farm/lessons/5-migrate-application-to-the-cloud)
* [Sunucusuz bir uygulama oluşturun](../../../../../2-farm/lessons/5-migrate-application-to-the-cloud)
* [Bir IoT Hub olay tetikleyicisi oluşturun](../../../../../2-farm/lessons/5-migrate-application-to-the-cloud)
* [Sunucusuz koddan doğrudan yöntem istekleri gönderin](../../../../../2-farm/lessons/5-migrate-application-to-the-cloud)
* [Sunucusuz kodunuzu buluta dağıtın](../../../../../2-farm/lessons/5-migrate-application-to-the-cloud)

## Sunucusuz Nedir?

Sunucusuz ya da sunucusuz bilişim, farklı türdeki olaylara yanıt olarak bulutta çalışan küçük kod blokları oluşturmayı içerir. Olay gerçekleştiğinde kodunuz çalıştırılır ve olaya dair veriler kodunuza iletilir. Bu olaylar, web isteklerinden, bir kuyruğa eklenen mesajlardan, bir veritabanındaki veri değişikliklerinden veya IoT cihazları tarafından bir IoT hizmetine gönderilen mesajlardan kaynaklanabilir.

![IoT hizmetinden sunucusuz bir hizmete gönderilen olaylar, aynı anda birden fazla fonksiyon tarafından işleniyor](../../../../../translated_images/tr/iot-messages-to-serverless.0194da1cc0732bb7.webp)

> 💁 Daha önce veritabanı tetikleyicileri kullandıysanız, bunu bir olay (örneğin bir satır ekleme) tarafından tetiklenen kod olarak düşünebilirsiniz.

![Birçok olay aynı anda gönderildiğinde, sunucusuz hizmet bunları aynı anda çalıştırmak için ölçeklenir](../../../../../translated_images/tr/serverless-scaling.f8c769adf0413fd1.webp)

Kodunuz yalnızca olay gerçekleştiğinde çalıştırılır, diğer zamanlarda kodunuz aktif değildir. Olay gerçekleşir, kodunuz yüklenir ve çalıştırılır. Bu, sunucusuz yapıyı oldukça ölçeklenebilir hale getirir - birçok olay aynı anda gerçekleşirse, bulut sağlayıcısı fonksiyonunuzu aynı anda ihtiyaç duyduğunuz kadar çalıştırabilir. Bunun dezavantajı, olaylar arasında bilgi paylaşmanız gerekiyorsa, bunu bellekte saklamak yerine bir veritabanı gibi bir yerde saklamanız gerektiğidir.

Kodunuz, olayla ilgili ayrıntıları bir parametre olarak alan bir fonksiyon olarak yazılır. Bu sunucusuz fonksiyonları yazmak için çok çeşitli programlama dillerini kullanabilirsiniz.

> 🎓 Sunucusuz, aynı zamanda Hizmet Olarak Fonksiyonlar (FaaS) olarak da adlandırılır, çünkü her olay tetikleyicisi kodda bir fonksiyon olarak uygulanır.

Adına rağmen, sunucusuz aslında sunucular kullanır. Bu isim, bir geliştirici olarak kodunuzu çalıştırmak için gereken sunucularla ilgilenmemenizden kaynaklanır; tek önemsediğiniz, kodunuzun bir olaya yanıt olarak çalıştırılmasıdır. Bulut sağlayıcısı, kodunuzu çalıştırmak için gereken sunucuları, ağları, depolamayı, CPU'yu, belleği ve diğer her şeyi yöneten bir sunucusuz *çalışma zamanı* sağlar. Bu model, hizmet için sunucu başına ödeme yapamayacağınız anlamına gelir, çünkü bir sunucu yoktur. Bunun yerine, kodunuzun çalıştığı süre ve kullanılan bellek miktarı için ödeme yaparsınız.

> 💰 Sunucusuz, bulutta kod çalıştırmanın en ucuz yollarından biridir. Örneğin, yazı yazıldığı sırada, bir bulut sağlayıcısı tüm sunucusuz fonksiyonlarınızın ayda toplam 1.000.000 kez çalıştırılmasına izin verir ve bundan sonra her 1.000.000 çalıştırma için 0,20 ABD doları ücret alır. Kodunuz çalışmadığında ödeme yapmazsınız.

Bir IoT geliştiricisi olarak, sunucusuz model idealdir. Bulut barındırmalı IoT hizmetinize bağlı herhangi bir IoT cihazından gelen mesajlara yanıt olarak çağrılan bir fonksiyon yazabilirsiniz. Kodunuz gönderilen tüm mesajları işler, ancak yalnızca gerektiğinde çalışır.

✅ MQTT üzerinden mesajları dinleyen sunucu kodu olarak yazdığınız koda geri dönün. Bu kodun sunucusuz olarak bulutta nasıl çalışabileceğini düşünün. Kodun sunucusuz bilişimi desteklemek için nasıl değiştirilebileceğini düşünün.

> 💁 Sunucusuz model, kod çalıştırmanın ötesine geçerek diğer bulut hizmetlerine de taşınıyor. Örneğin, sunucusuz veritabanları, sorgu veya ekleme gibi veritabanına yapılan her istek başına ödeme yapılan bir fiyatlandırma modeliyle bulutta mevcuttur. Örneğin, birincil anahtara karşı bir satırın seçilmesi, birçok tabloyu birleştiren ve binlerce satır döndüren karmaşık bir işlemden daha az maliyetlidir.

## Sunucusuz Bir Uygulama Oluşturun

Microsoft'un sunucusuz bilişim hizmeti Azure Functions olarak adlandırılır.

![Azure Functions logosu](../../../../../translated_images/tr/azure-functions-logo.1cfc8e3204c9c44a.webp)

Aşağıdaki kısa video, Azure Functions hakkında bir genel bakış sunar.

[![Azure Functions genel bakış videosu](https://img.youtube.com/vi/8-jz5f_JyEQ/0.jpg)](https://www.youtube.com/watch?v=8-jz5f_JyEQ)

> 🎥 Videoyu izlemek için yukarıdaki görsele tıklayın.

✅ Biraz araştırma yapın ve [Microsoft Azure Functions belgelerindeki](https://docs.microsoft.com/azure/azure-functions/functions-overview?WT.mc_id=academic-17441-jabenn) Azure Functions genel bakışını okuyun.

Azure Functions yazmak için, seçtiğiniz dilde bir Azure Functions uygulamasıyla başlarsınız. Azure Functions, Python, JavaScript, TypeScript, C#, F#, Java ve Powershell dillerini destekler. Bu derste, Python'da bir Azure Functions uygulamasının nasıl yazılacağını öğreneceksiniz.

> 💁 Azure Functions ayrıca özel işleyicileri destekler, böylece HTTP isteklerini destekleyen herhangi bir dilde, hatta COBOL gibi eski dillerde bile fonksiyonlarınızı yazabilirsiniz.

Functions uygulamaları, bir veya daha fazla *tetikleyici* içerir - olaylara yanıt veren fonksiyonlar. Bir Functions uygulamasında birden fazla tetikleyici olabilir ve hepsi ortak bir yapılandırmayı paylaşır. Örneğin, Functions uygulamanızın yapılandırma dosyasında IoT Hub bağlantı ayrıntılarını bulundurabilirsiniz ve uygulamadaki tüm fonksiyonlar bu bağlantıyı kullanarak olayları dinleyebilir.

### Görev - Azure Functions Araçlarını Yükleyin

> Yazı yazıldığı sırada, Azure Functions kod araçları Python projeleriyle Apple Silicon üzerinde tam olarak çalışmamaktadır. Bunun yerine Intel tabanlı bir Mac, Windows PC veya Linux PC kullanmanız gerekecektir.

Azure Functions'un harika bir özelliği, yerel olarak çalıştırılabilmesidir. Bulutta kullanılan aynı çalışma zamanı bilgisayarınızda çalıştırılabilir, bu da IoT mesajlarına yanıt veren kod yazmanıza ve bunu yerel olarak çalıştırmanıza olanak tanır. Hatta olaylar işlenirken kodunuzu hata ayıklayabilirsiniz. Kodunuzdan memnun olduğunuzda, buluta dağıtabilirsiniz.

Azure Functions araçları, Azure Functions Core Tools olarak bilinen bir CLI olarak mevcuttur.

1. [Azure Functions Core Tools belgelerindeki](https://docs.microsoft.com/azure/azure-functions/functions-run-local?WT.mc_id=academic-17441-jabenn) talimatları izleyerek Azure Functions core tools'u yükleyin.

1. VS Code için Azure Functions uzantısını yükleyin. Bu uzantı, Azure fonksiyonları oluşturma, hata ayıklama ve dağıtma desteği sağlar. Bu uzantıyı VS Code'a yükleme talimatları için [Azure Functions uzantı belgelerine](https://marketplace.visualstudio.com/items?WT.mc_id=academic-17441-jabenn&itemName=ms-azuretools.vscode-azurefunctions) bakın.

Azure Functions uygulamanızı buluta dağıttığınızda, uygulama dosyaları ve günlük dosyaları gibi şeyleri depolamak için küçük bir miktar bulut depolama alanı kullanması gerekir. Functions uygulamanızı yerel olarak çalıştırdığınızda, yine de bulut depolamaya bağlanmanız gerekir, ancak gerçek bulut depolama yerine, [Azurite](https://github.com/Azure/Azurite) adlı bir depolama emülatörü kullanabilirsiniz. Bu, yerel olarak çalışır ancak bulut depolama gibi davranır.

> 🎓 Azure'da, Azure Functions'un kullandığı depolama bir Azure Depolama Hesabıdır. Bu hesaplar dosyaları, blobları, tablolardaki verileri veya kuyruklardaki verileri depolayabilir. Bir depolama hesabını birçok uygulama arasında paylaşabilirsiniz, örneğin bir Functions uygulaması ve bir web uygulaması.

1. Azurite bir Node.js uygulamasıdır, bu nedenle Node.js yüklemeniz gerekecektir. [Node.js web sitesindeki](https://nodejs.org/) indirme ve kurulum talimatlarını bulabilirsiniz. Mac kullanıyorsanız, ayrıca [Homebrew](https://formulae.brew.sh/formula/node) üzerinden de yükleyebilirsiniz.

1. Azurite'ı aşağıdaki komutla yükleyin (`npm`, Node.js yüklediğinizde kurulan bir araçtır):

    ```sh
    npm install -g azurite
    ```

1. Azurite'ın veri depolamak için kullanacağı `azurite` adlı bir klasör oluşturun:

    ```sh
    mkdir azurite
    ```

1. Azurite'ı çalıştırın ve bu yeni klasörü belirtin:

    ```sh
    azurite --location azurite
    ```

    Azurite depolama emülatörü başlatılacak ve yerel Functions çalışma zamanı bağlanmaya hazır hale gelecektir.

    ```output
    ➜  ~ azurite --location azurite  
    Azurite Blob service is starting at http://127.0.0.1:10000
    Azurite Blob service is successfully listening at http://127.0.0.1:10000
    Azurite Queue service is starting at http://127.0.0.1:10001
    Azurite Queue service is successfully listening at http://127.0.0.1:10001
    Azurite Table service is starting at http://127.0.0.1:10002
    Azurite Table service is successfully listening at http://127.0.0.1:10002
    ```

### Görev - Bir Azure Functions Projesi Oluşturun

Azure Functions CLI, yeni bir Functions uygulaması oluşturmak için kullanılabilir.

1. Functions uygulamanız için bir klasör oluşturun ve bu klasöre gidin. Adını `soil-moisture-trigger` koyun:

    ```sh
    mkdir soil-moisture-trigger
    cd soil-moisture-trigger
    ```

1. Bu klasörün içinde bir Python sanal ortamı oluşturun:

    ```sh
    python3 -m venv .venv
    ```

1. Sanal ortamı etkinleştirin:

    * Windows'ta:
        * Komut İstemi veya Windows Terminal üzerinden Komut İstemi kullanıyorsanız, şu komutu çalıştırın:

            ```cmd
            .venv\Scripts\activate.bat
            ```

        * PowerShell kullanıyorsanız, şu komutu çalıştırın:

            ```powershell
            .\.venv\Scripts\Activate.ps1
            ```

    * macOS veya Linux'ta şu komutu çalıştırın:

        ```cmd
        source ./.venv/bin/activate
        ```

    > 💁 Bu komutlar, sanal ortamı oluşturduğunuz konumdan çalıştırılmalıdır. `.venv` klasörüne asla gitmeniz gerekmez, her zaman etkinleştirme komutunu ve paketleri yüklemek veya kod çalıştırmak için gereken komutları sanal ortamı oluşturduğunuz klasörden çalıştırmalısınız.

1. Aşağıdaki komutu çalıştırarak bu klasörde bir Functions uygulaması oluşturun:

    ```sh
    func init --worker-runtime python soil-moisture-trigger
    ```

    Bu, mevcut klasörün içine üç dosya oluşturacaktır:

    * `host.json` - Bu JSON belgesi, Functions uygulamanız için ayarları içerir. Bu ayarları değiştirmeniz gerekmeyecek.
    * `local.settings.json` - Bu JSON belgesi, IoT Hub bağlantı dizeleri gibi uygulamanızın yerel olarak çalışırken kullanacağı ayarları içerir. Bu ayarlar yalnızca yerel olarak kullanılır ve kaynak kod kontrolüne eklenmemelidir. Uygulama buluta dağıtıldığında, bu ayarlar dağıtılmaz, bunun yerine ayarlar uygulama ayarlarından yüklenir. Bu, bu derste daha sonra ele alınacaktır.
    * `requirements.txt` - Bu, Functions uygulamanızı çalıştırmak için gereken Pip paketlerini içeren bir [Pip gereksinimler dosyasıdır](https://pip.pypa.io/en/stable/user_guide/#requirements-files).

1. `local.settings.json` dosyasında, Functions uygulamasının kullanacağı depolama hesabı için bir ayar bulunur. Bu varsayılan olarak boş bir ayardır, bu nedenle ayarlanması gerekir. Azurite yerel depolama emülatörüne bağlanmak için bu değeri aşağıdaki gibi ayarlayın:

    ```json
    "AzureWebJobsStorage": "UseDevelopmentStorage=true",
    ```

1. Gereken Pip paketlerini gereksinimler dosyasını kullanarak yükleyin:

    ```sh
    pip install -r requirements.txt
    ```

    > 💁 Gerekli Pip paketlerinin bu dosyada olması gerekir, böylece Functions uygulaması buluta dağıtıldığında, çalışma zamanı doğru paketleri yüklediğinden emin olabilir.

1. Her şeyin doğru çalıştığından emin olmak için Functions çalışma zamanını başlatabilirsiniz. Bunu yapmak için şu komutu çalıştırın:

    ```sh
    func start
    ```

    Çalışma zamanının başlatıldığını ve herhangi bir iş fonksiyonu (tetikleyici) bulamadığını rapor ettiğini göreceksiniz.

    ```output
    (.venv) ➜  soil-moisture-trigger func start
    Found Python version 3.9.1 (python3).
    
    Azure Functions Core Tools
    Core Tools Version:       3.0.3442 Commit hash: 6bfab24b2743f8421475d996402c398d2fe4a9e0  (64-bit)
    Function Runtime Version: 3.0.15417.0
    
    [2021-05-05T01:24:46.795Z] No job functions found.
    ```
> ⚠️ Eğer bir güvenlik duvarı bildirimi alırsanız, erişim izni verin çünkü `func` uygulamasının ağınıza okuma ve yazma yetkisine sahip olması gerekiyor.
> ⚠️ Eğer macOS kullanıyorsanız, çıktıda uyarılar olabilir:
>
> ```output
    > (.venv) ➜  soil-moisture-trigger func start
    > Found Python version 3.9.1 (python3).
    >
    > Azure Functions Core Tools
    > Core Tools Version:       3.0.3442 Commit hash: 6bfab24b2743f8421475d996402c398d2fe4a9e0  (64-bit)
    > Function Runtime Version: 3.0.15417.0
    >
    > [2021-06-16T08:18:28.315Z] Cannot create directory for shared memory usage: /dev/shm/AzureFunctions
    > [2021-06-16T08:18:28.316Z] System.IO.FileSystem: Access to the path '/dev/shm/AzureFunctions' is denied. Operation not permitted.
    > [2021-06-16T08:18:30.361Z] No job functions found.
    > ```
>
> Functions uygulaması doğru bir şekilde başlıyor ve çalışan fonksiyonları listeliyorsa bu uyarıları görmezden gelebilirsiniz. [Microsoft Docs Q&A'deki bu soruda](https://docs.microsoft.com/answers/questions/396617/azure-functions-core-tools-error-osx-devshmazurefu.html?WT.mc_id=academic-17441-jabenn) belirtildiği gibi bu uyarılar önemsenmeyebilir.

1. Functions uygulamasını `ctrl+c` tuşlarına basarak durdurun.

1. Mevcut klasörü VS Code'da açın. Bunu ya VS Code'u açıp bu klasörü seçerek ya da aşağıdaki komutu çalıştırarak yapabilirsiniz:

    ```sh
    code .
    ```

    VS Code, Functions projenizi algılayacak ve şu bildirimi gösterecektir:

    ```output
    Detected an Azure Functions Project in folder "soil-moisture-trigger" that may have been created outside of
    VS Code. Initialize for optimal use with VS Code?
    ```

    ![Bildirim](../../../../../translated_images/tr/vscode-azure-functions-init-notification.bd19b49229963edb.webp)

    Bu bildirimi seçerek **Evet** deyin.

1. VS Code terminalinde Python sanal ortamının çalıştığından emin olun. Gerekirse sanal ortamı sonlandırıp yeniden başlatın.

## IoT Hub olay tetikleyicisi oluşturma

Functions uygulaması, sunucusuz kodunuzun kabuğudur. IoT Hub olaylarına yanıt vermek için bu uygulamaya bir IoT Hub tetikleyicisi ekleyebilirsiniz. Bu tetikleyici, IoT Hub'a gönderilen mesajların akışına bağlanmalı ve bu mesajlara yanıt vermelidir. Mesaj akışını almak için tetikleyicinizin IoT Hub'ın *Event Hub uyumlu uç noktası*na bağlanması gerekir.

IoT Hub, Azure Event Hubs adlı başka bir Azure hizmetine dayanır. Event Hubs, mesaj gönderip almanıza olanak tanıyan bir hizmettir; IoT Hub ise IoT cihazları için ek özellikler ekleyerek bunu genişletir. IoT Hub'dan mesajları okumak için bağlanma yöntemi, Event Hubs kullanıyormuşsunuz gibi aynıdır.

✅ Araştırma yapın: [Azure Event Hubs belgelerinde](https://docs.microsoft.com/azure/event-hubs/event-hubs-about?WT.mc_id=academic-17441-jabenn) Event Hubs'ın genel bakışını okuyun. Temel özellikler IoT Hub ile nasıl karşılaştırılıyor?

Bir IoT cihazının IoT Hub'a bağlanabilmesi için yalnızca izin verilen cihazların bağlanmasını sağlayan bir gizli anahtar kullanması gerekir. Mesajları okumak için bağlanırken de aynı durum geçerlidir; kodunuzun bir gizli anahtar içeren ve IoT Hub'ın ayrıntılarını içeren bir bağlantı dizesine ihtiyacı olacaktır.

> 💁 Varsayılan bağlantı dizesi **iothubowner** izinlerine sahiptir, bu da onu kullanan herhangi bir koda IoT Hub üzerinde tam izinler verir. İdeal olarak, yalnızca gerekli olan en düşük izin seviyesinde bağlanmalısınız. Bu, bir sonraki derste ele alınacaktır.

Tetkikleyiciniz bağlandıktan sonra, IoT Hub'a gönderilen her mesaj için fonksiyon içindeki kod çağrılacaktır; mesajın hangi cihazdan gönderildiği fark etmeksizin. Tetkikleyici, mesajı bir parametre olarak alacaktır.

### Görev - Event Hub uyumlu uç nokta bağlantı dizesini alın

1. IoT Hub'ın Event Hub uyumlu uç noktası için bağlantı dizesini almak üzere VS Code terminalinden aşağıdaki komutu çalıştırın:

    ```sh
    az iot hub connection-string show --default-eventhub \
                                      --output table \
                                      --hub-name <hub_name>
    ```

    `<hub_name>` kısmını IoT Hub için kullandığınız adla değiştirin.

1. VS Code'da `local.settings.json` dosyasını açın. `Values` bölümüne aşağıdaki ek değeri ekleyin:

    ```json
    "IOT_HUB_CONNECTION_STRING": "<connection string>"
    ```

    `<connection string>` kısmını önceki adımdan aldığınız değerle değiştirin. Bu geçerli bir JSON yapmak için yukarıdaki satırdan sonra bir virgül eklemeniz gerekecek.

### Görev - bir olay tetikleyicisi oluşturun

Artık olay tetikleyicisini oluşturmaya hazırsınız.

1. VS Code terminalinden `soil-moisture-trigger` klasörünün içinden aşağıdaki komutu çalıştırın:

    ```sh
    func new --name iot-hub-trigger --template "Azure Event Hub trigger"
    ```

    Bu, `iot-hub-trigger` adlı yeni bir Fonksiyon oluşturur. Tetkikleyici, IoT Hub'daki Event Hub uyumlu uç noktaya bağlanacak, böylece bir Event Hub tetikleyicisi kullanabilirsiniz. IoT Hub için özel bir tetikleyici yoktur.

Bu işlem, `soil-moisture-trigger` klasörünün içinde `iot-hub-trigger` adlı bir klasör oluşturur ve bu klasör şu dosyaları içerir:

* `__init__.py` - Bu, tetikleyiciyi içeren Python kod dosyasıdır ve bu klasörü bir Python modülüne dönüştürmek için standart Python dosya adı sözleşmesini kullanır.

    Bu dosya aşağıdaki kodu içerir:

    ```python
    import logging

    import azure.functions as func


    def main(event: func.EventHubEvent):
        logging.info('Python EventHub trigger processed an event: %s',
                    event.get_body().decode('utf-8'))
    ```

    Tetkikleyicinin çekirdeği `main` fonksiyonudur. IoT Hub'dan gelen olaylarla bu fonksiyon çağrılır. Bu fonksiyonun `event` adlı bir parametresi vardır ve bu parametre bir `EventHubEvent` içerir. IoT Hub'a her mesaj gönderildiğinde, bu fonksiyon mesajı `event` olarak ve önceki derste gördüğünüz açıklamalarla aynı olan özelliklerle birlikte alır.

    Bu fonksiyonun çekirdeği, olayı kaydeder.

* `function.json` - Bu dosya tetikleyici için yapılandırma içerir. Ana yapılandırma `bindings` adlı bir bölümde bulunur. Binding, Azure Functions ile diğer Azure hizmetleri arasındaki bağlantı için kullanılan terimdir. Bu fonksiyonun bir Event Hub'a giriş binding'i vardır - Event Hub'a bağlanır ve veri alır.

    > 💁 Ayrıca bir fonksiyonun çıktısının başka bir hizmete gönderilmesi için çıkış binding'leri de ekleyebilirsiniz. Örneğin, bir veritabanına bir çıkış binding'i ekleyebilir ve IoT Hub olayını fonksiyondan döndürebilir, böylece otomatik olarak veritabanına eklenir.

    ✅ Araştırma yapın: [Azure Functions tetikleyiciler ve binding kavramları belgelerinde](https://docs.microsoft.com/azure/azure-functions/functions-triggers-bindings?WT.mc_id=academic-17441-jabenn&tabs=python) binding'ler hakkında bilgi edinin.

    `bindings` bölümü binding için yapılandırma içerir. İlginç olan değerler şunlardır:

  * `"type": "eventHubTrigger"` - Bu, fonksiyonun Event Hub'dan gelen olayları dinlemesi gerektiğini belirtir.
  * `"name": "events"` - Bu, Event Hub olayları için kullanılacak parametre adıdır. Bu, Python kodundaki `main` fonksiyonundaki parametre adıyla eşleşir.
  * `"direction": "in"` - Bu bir giriş binding'idir, Event Hub'dan gelen veri fonksiyona gelir.
  * `"connection": ""` - Bu, bağlantı dizesini okumak için ayarın adını tanımlar. Yerel olarak çalıştırıldığında, bu ayarı `local.settings.json` dosyasından okur.

    > 💁 Bağlantı dizesi `function.json` dosyasında saklanamaz, ayarlardan okunması gerekir. Bu, bağlantı dizenizi yanlışlıkla ifşa etmenizi önlemek içindir.

1. [Azure Functions şablonundaki bir hatadan](https://github.com/Azure/azure-functions-templates/issues/1250) dolayı, `function.json` dosyasındaki `cardinality` alanı yanlış bir değere sahiptir. Bu alanı `many` değerinden `one` değerine güncelleyin:

    ```json
    "cardinality": "one",
    ```

1. `function.json` dosyasındaki `"connection"` değerini, `local.settings.json` dosyasına eklediğiniz yeni değere işaret edecek şekilde güncelleyin:

    ```json
    "connection": "IOT_HUB_CONNECTION_STRING",
    ```

    > 💁 Unutmayın - bu ayara işaret etmeli, gerçek bağlantı dizesini içermemelidir.

1. Bağlantı dizesi `eventHubName` değerini içerir, bu nedenle `function.json` dosyasındaki bu değerin boş bir dizeye ayarlanması gerekir. Bu değeri boş bir dizeye güncelleyin:

    ```json
    "eventHubName": "",
    ```

### Görev - olay tetikleyicisini çalıştırın

1. IoT Hub olay monitörünün çalışmadığından emin olun. Bu, Functions uygulamasıyla aynı anda çalışıyorsa, Functions uygulaması bağlanamaz ve olayları tüketemez.

    > 💁 Birden fazla uygulama, farklı *tüketici grupları* kullanarak IoT Hub uç noktalarına bağlanabilir. Bunlar ilerleyen bir derste ele alınacaktır.

1. Functions uygulamasını çalıştırmak için VS Code terminalinden aşağıdaki komutu çalıştırın:

    ```sh
    func start
    ```

    Functions uygulaması başlayacak ve `iot-hub-trigger` fonksiyonunu keşfedecektir. Ardından, IoT Hub'a son bir gün içinde gönderilen tüm olayları işleyecektir.

    ```output
    (.venv) ➜  soil-moisture-trigger func start
    Found Python version 3.9.1 (python3).
    
    Azure Functions Core Tools
    Core Tools Version:       3.0.3442 Commit hash: 6bfab24b2743f8421475d996402c398d2fe4a9e0  (64-bit)
    Function Runtime Version: 3.0.15417.0
    
    Functions:
    
            iot-hub-trigger: eventHubTrigger
    
    For detailed output, run func with --verbose flag.
    [2021-05-05T02:44:07.517Z] Worker process started and initialized.
    [2021-05-05T02:44:09.202Z] Executing 'Functions.iot-hub-trigger' (Reason='(null)', Id=802803a5-eae9-4401-a1f4-176631456ce4)
    [2021-05-05T02:44:09.205Z] Trigger Details: PartitionId: 0, Offset: 1011240-1011632, EnqueueTimeUtc: 2021-05-04T19:04:04.2030000Z-2021-05-04T19:04:04.3900000Z, SequenceNumber: 2546-2547, Count: 2
    [2021-05-05T02:44:09.352Z] Python EventHub trigger processed an event: {"soil_moisture":628}
    [2021-05-05T02:44:09.354Z] Python EventHub trigger processed an event: {"soil_moisture":624}
    [2021-05-05T02:44:09.395Z] Executed 'Functions.iot-hub-trigger' (Succeeded, Id=802803a5-eae9-4401-a1f4-176631456ce4, Duration=245ms)
    ```

    Her fonksiyon çağrısı, çıktıda `Executing 'Functions.iot-hub-trigger'`/`Executed 'Functions.iot-hub-trigger'` bloklarıyla çevrili olacaktır, böylece her fonksiyon çağrısında kaç mesaj işlendiğini görebilirsiniz.

1. IoT cihazınızın çalıştığından emin olun. Functions uygulamasında yeni toprak nemi mesajlarının göründüğünü göreceksiniz.

1. Functions uygulamasını durdurup yeniden başlatın. Önceki mesajları tekrar işlemeyeceğini, yalnızca yeni mesajları işleyeceğini göreceksiniz.

> 💁 VS Code ayrıca Functions uygulamanızı hata ayıklamayı destekler. Kodun her satırının başındaki kenarlığa tıklayarak, kodun bir satırına imleci yerleştirip *Çalıştır -> Kesme noktası değiştir* seçeneğini seçerek veya `F9` tuşuna basarak kesme noktaları ayarlayabilirsiniz. Hata ayıklayıcıyı başlatmak için *Çalıştır -> Hata ayıklamayı başlat* seçeneğini seçebilir, `F5` tuşuna basabilir veya *Çalıştır ve hata ayıkla* panelini seçip **Hata ayıklamayı başlat** düğmesine tıklayabilirsiniz. Bunu yaparak işlenen olayların ayrıntılarını görebilirsiniz.

#### Sorun Giderme

* Eğer şu hatayı alırsanız:

    ```output
    The listener for function 'Functions.iot-hub-trigger' was unable to start. Microsoft.WindowsAzure.Storage: Connection refused. System.Net.Http: Connection refused. System.Private.CoreLib: Connection refused.
    ```

    Azurite'ın çalıştığından ve `local.settings.json` dosyasındaki `AzureWebJobsStorage` ayarını `UseDevelopmentStorage=true` olarak ayarladığınızdan emin olun.

* Eğer şu hatayı alırsanız:

    ```output
    System.Private.CoreLib: Exception while executing function: Functions.iot-hub-trigger. System.Private.CoreLib: Result: Failure Exception: AttributeError: 'list' object has no attribute 'get_body'
    ```

    `function.json` dosyasındaki `cardinality` değerini `one` olarak ayarladığınızdan emin olun.

* Eğer şu hatayı alırsanız:

    ```output
    Azure.Messaging.EventHubs: The path to an Event Hub may be specified as part of the connection string or as a separate value, but not both.  Please verify that your connection string does not have the `EntityPath` token if you are passing an explicit Event Hub name. (Parameter 'connectionString').
    ```

    `function.json` dosyasındaki `eventHubName` değerini boş bir dize olarak ayarladığınızdan emin olun.

## Sunucusuz koddan doğrudan yöntem istekleri gönderme

Şu ana kadar Functions uygulamanız, Event Hub uyumlu uç noktayı kullanarak IoT Hub'dan gelen mesajları dinliyor. Şimdi IoT cihazına komut göndermeniz gerekiyor. Bu, IoT Hub'a *Registry Manager* üzerinden farklı bir bağlantı kullanılarak yapılır. Registry Manager, IoT Hub'a kayıtlı cihazları görmenizi ve bu cihazlarla bulut cihaz mesajları, doğrudan yöntem istekleri veya cihaz ikizini güncelleyerek iletişim kurmanızı sağlar. Ayrıca IoT Hub'dan IoT cihazları kaydetmek, güncellemek veya silmek için de kullanılabilir.

Registry Manager'a bağlanmak için bir bağlantı dizesine ihtiyacınız var.

### Görev - Registry Manager bağlantı dizesini alın

1. Bağlantı dizesini almak için aşağıdaki komutu çalıştırın:

    ```sh
    az iot hub connection-string show --policy-name service \
                                      --output table \
                                      --hub-name <hub_name>
    ```

    `<hub_name>` kısmını IoT Hub için kullandığınız adla değiştirin.

    Bağlantı dizesi, `--policy-name service` parametresi kullanılarak *ServiceConnect* politikası için istenir. Bir bağlantı dizesi talep ettiğinizde, bu bağlantı dizisinin hangi izinlere sahip olacağını belirtebilirsiniz. ServiceConnect politikası, kodunuzun bağlanmasına ve IoT cihazlarına mesaj göndermesine izin verir.

    ✅ Araştırma yapın: [IoT Hub izinleri belgelerinde](https://docs.microsoft.com/azure/iot-hub/iot-hub-devguide-security#iot-hub-permissions?WT.mc_id=academic-17441-jabenn) farklı politikalar hakkında bilgi edinin.

1. VS Code'da `local.settings.json` dosyasını açın. `Values` bölümüne aşağıdaki ek değeri ekleyin:

    ```json
    "REGISTRY_MANAGER_CONNECTION_STRING": "<connection string>"
    ```

    `<connection string>` kısmını önceki adımdan aldığınız değerle değiştirin. Bu geçerli bir JSON yapmak için yukarıdaki satırdan sonra bir virgül eklemeniz gerekecek.

### Görev - bir cihaza doğrudan yöntem isteği gönderin

1. Registry Manager için SDK, bir Pip paketi aracılığıyla kullanılabilir. Bu pakete bağımlılığı eklemek için `requirements.txt` dosyasına aşağıdaki satırı ekleyin:

    ```sh
    azure-iot-hub
    ```

1. VS Code terminalinde sanal ortamın etkin olduğundan emin olun ve Pip paketlerini yüklemek için aşağıdaki komutu çalıştırın:

    ```sh
    pip install -r requirements.txt
    ```

1. `__init__.py` dosyasına aşağıdaki importları ekleyin:

    ```python
    import json
    import os
    from azure.iot.hub import IoTHubRegistryManager
    from azure.iot.hub.models import CloudToDeviceMethod
    ```

    Bu, sistem kütüphanelerini ve Registry Manager ile doğrudan yöntem istekleri göndermek için kütüphaneleri içe aktarır.

1. `main` metodunun içindeki kodu kaldırın, ancak metodu kendisini koruyun.

1. `main` metodunun içine aşağıdaki kodu ekleyin:

    ```python
    body = json.loads(event.get_body().decode('utf-8'))
    device_id = event.iothub_metadata['connection-device-id']

    logging.info(f'Received message: {body} from {device_id}')
    ```

    Bu kod, IoT cihazı tarafından gönderilen JSON mesajını içeren olayın gövdesini çıkarır.

    Daha sonra, mesajla birlikte gönderilen açıklamalardan cihaz kimliğini alır. Olayın gövdesi, telemetri olarak gönderilen mesajı içerir; `iothub_metadata` sözlüğü ise IoT Hub tarafından ayarlanan cihaz kimliği ve mesajın gönderildiği zaman gibi özellikleri içerir.

    Bu bilgiler daha sonra kaydedilir. Functions uygulamasını yerel olarak çalıştırdığınızda bu kaydı terminalde göreceksiniz.

1. Bunun altına aşağıdaki kodu ekleyin:

    ```python
    soil_moisture = body['soil_moisture']

    if soil_moisture > 450:
        direct_method = CloudToDeviceMethod(method_name='relay_on', payload='{}')
    else:
        direct_method = CloudToDeviceMethod(method_name='relay_off', payload='{}')
    ```

    Bu kod, mesajdan toprak nemini alır. Daha sonra toprak nemini kontrol eder ve değere bağlı olarak `relay_on` veya `relay_off` doğrudan yöntem isteği için bir yardımcı sınıf oluşturur. Yöntem isteği bir yük gerektirmez, bu nedenle boş bir JSON belgesi gönderilir.

1. Bunun altına aşağıdaki kodu ekleyin:

    ```python
    logging.info(f'Sending direct method request for {direct_method.method_name} for device {device_id}')

    registry_manager_connection_string = os.environ['REGISTRY_MANAGER_CONNECTION_STRING']
    registry_manager = IoTHubRegistryManager(registry_manager_connection_string)
    ```
Bu kod, `local.settings.json` dosyasından `REGISTRY_MANAGER_CONNECTION_STRING` değerini yükler. Bu dosyadaki değerler ortam değişkenleri olarak kullanılabilir hale gelir ve `os.environ` fonksiyonu kullanılarak okunabilir. Bu fonksiyon, tüm ortam değişkenlerini içeren bir sözlük döndürür.

> 💁 Bu kod buluta dağıtıldığında, `local.settings.json` dosyasındaki değerler *Uygulama Ayarları* olarak ayarlanır ve ortam değişkenlerinden okunabilir.

Kod daha sonra bağlantı dizesini kullanarak Registry Manager yardımcı sınıfının bir örneğini oluşturur.

1. Bunun altına aşağıdaki kodu ekleyin:

    ```python
    registry_manager.invoke_device_method(device_id, direct_method)

    logging.info('Direct method request sent!')
    ```

    Bu kod, registry manager'a telemetri gönderen cihaza doğrudan yöntem isteği göndermesini söyler.

    > 💁 Daha önceki derslerde MQTT kullanarak oluşturduğunuz uygulama sürümlerinde, röle kontrol komutları tüm cihazlara gönderiliyordu. Kod, yalnızca bir cihazınız olacağını varsayıyordu. Bu kod sürümü, yöntem isteğini tek bir cihaza gönderir, bu nedenle birden fazla nem sensörü ve röle kurulumunuz varsa doğru yöntemi doğru cihaza göndermek için çalışır.

1. Functions uygulamasını çalıştırın ve IoT cihazınızın veri gönderdiğinden emin olun. Mesajların işlendiğini ve doğrudan yöntem isteklerinin gönderildiğini göreceksiniz. Toprak nem sensörünü toprağın içine ve dışına hareket ettirerek değerlerin değiştiğini ve rölenin açılıp kapandığını gözlemleyin.

> 💁 Bu kodu [code/functions](../../../../../2-farm/lessons/5-migrate-application-to-the-cloud/code/functions) klasöründe bulabilirsiniz.

## Sunucusuz kodunuzu buluta dağıtın

Kodunuz artık yerel olarak çalışıyor, bu yüzden bir sonraki adım Functions App'i buluta dağıtmaktır.

### Görev - bulut kaynaklarını oluşturun

Functions uygulamanızın, IoT Hub için oluşturduğunuz Resource Group içinde yer alan bir Azure Functions App kaynağına dağıtılması gerekiyor. Ayrıca, yerel olarak çalışan emüle edilmiş depolama yerine Azure'da bir Storage Account oluşturmanız gerekecek.

1. Bir depolama hesabı oluşturmak için aşağıdaki komutu çalıştırın:

    ```sh
    az storage account create --resource-group soil-moisture-sensor \
                              --sku Standard_LRS \
                              --name <storage_name> 
    ```

    `<storage_name>` yerine depolama hesabınız için bir ad yazın. Bu ad, depolama hesabına erişmek için kullanılan URL'nin bir parçasını oluşturduğu için küresel olarak benzersiz olmalıdır. Bu ad için yalnızca küçük harfler ve rakamlar kullanılabilir, başka karakterler kullanılamaz ve 24 karakterle sınırlıdır. `sms` gibi bir şey kullanın ve sonuna rastgele kelimeler veya adınızı ekleyerek benzersiz bir tanımlayıcı ekleyin.

    `--sku Standard_LRS`, en düşük maliyetli genel amaçlı hesabı seçerek fiyatlandırma katmanını belirler. Depolama için ücretsiz bir katman yoktur ve kullandığınız kadar ödeme yaparsınız. Maliyetler nispeten düşüktür, en pahalı depolama gigabayt başına ayda 0,05 ABD dolarından azdır.

    ✅ Fiyatlandırma hakkında daha fazla bilgi edinin: [Azure Storage Account pricing page](https://azure.microsoft.com/pricing/details/storage/?WT.mc_id=academic-17441-jabenn)

1. Bir Function App oluşturmak için aşağıdaki komutu çalıştırın:

    ```sh
    az functionapp create --resource-group soil-moisture-sensor \
                          --runtime python \
                          --functions-version 3 \
                          --os-type Linux \
                          --consumption-plan-location <location> \
                          --storage-account <storage_name> \
                          --name <functions_app_name>
    ```

    `<location>` yerine önceki derste Resource Group oluştururken kullandığınız konumu yazın.

    `<storage_name>` yerine bir önceki adımda oluşturduğunuz depolama hesabının adını yazın.

    `<functions_app_name>` yerine Functions App için benzersiz bir ad yazın. Bu ad, Functions App'e erişmek için kullanılan URL'nin bir parçasını oluşturduğu için küresel olarak benzersiz olmalıdır. `soil-moisture-sensor-` gibi bir şey kullanın ve sonuna rastgele kelimeler veya adınızı ekleyerek benzersiz bir tanımlayıcı ekleyin.

    `--functions-version 3` seçeneği, kullanılacak Azure Functions sürümünü ayarlar. Sürüm 3 en son sürümdür.

    `--os-type Linux`, Functions runtime'ın bu fonksiyonları barındırmak için Linux'u kullanmasını söyler. Fonksiyonlar kullanılan programlama diline bağlı olarak Linux veya Windows üzerinde barındırılabilir. Python uygulamaları yalnızca Linux üzerinde desteklenir.

### Görev - uygulama ayarlarınızı yükleyin

Functions App'inizi geliştirirken, IoT Hub bağlantı dizeleri için `local.settings.json` dosyasına bazı ayarlar kaydettiniz. Bu ayarların, kodunuz tarafından kullanılabilmesi için Azure'daki Functions App'in Uygulama Ayarlarına yazılması gerekiyor.

> 🎓 `local.settings.json` dosyası yalnızca yerel geliştirme ayarları içindir ve GitHub gibi kaynak kod kontrolüne eklenmemelidir. Buluta dağıtıldığında, Uygulama Ayarları kullanılır. Uygulama Ayarları, bulutta barındırılan anahtar/değer çiftleridir ve kodunuzda veya IoT Hub'a bağlanırken runtime tarafından ortam değişkenlerinden okunur.

1. Functions App Uygulama Ayarlarında `IOT_HUB_CONNECTION_STRING` ayarını belirlemek için aşağıdaki komutu çalıştırın:

    ```sh
    az functionapp config appsettings set --resource-group soil-moisture-sensor \
                                          --name <functions_app_name> \
                                          --settings "IOT_HUB_CONNECTION_STRING=<connection string>"
    ```

    `<functions_app_name>` yerine Functions App için kullandığınız adı yazın.

    `<connection string>` yerine `local.settings.json` dosyasındaki `IOT_HUB_CONNECTION_STRING` değerini yazın.

1. Yukarıdaki adımı tekrarlayın, ancak `REGISTRY_MANAGER_CONNECTION_STRING` değerini `local.settings.json` dosyasındaki karşılık gelen değerle ayarlayın.

Bu komutları çalıştırdığınızda, aynı zamanda Functions App için tüm Uygulama Ayarlarının bir listesini de göreceksiniz. Değerlerinizin doğru ayarlandığını kontrol etmek için bu listeyi kullanabilirsiniz.

> 💁 `AzureWebJobsStorage` için zaten ayarlanmış bir değer göreceksiniz. `local.settings.json` dosyanızda, bu değer yerel depolama emülatörünü kullanmak için ayarlanmıştı. Functions App oluşturduğunuzda, depolama hesabını bir parametre olarak geçersiniz ve bu ayar otomatik olarak belirlenir.

### Görev - Functions App'inizi buluta dağıtın

Functions App artık hazır olduğuna göre, kodunuz dağıtılabilir.

1. Functions App'inizi yayınlamak için VS Code terminalinden aşağıdaki komutu çalıştırın:

    ```sh
    func azure functionapp publish <functions_app_name>
    ```

    `<functions_app_name>` yerine Functions App için kullandığınız adı yazın.

Kod paketlenip Functions App'e gönderilecek, burada dağıtılacak ve başlatılacak. Konsol çıktısı oldukça fazla olacak ve dağıtımın onayı ile dağıtılan fonksiyonların bir listesini içerecek. Bu durumda liste yalnızca tetikleyiciyi içerecek.

```output
Deployment successful.
Remote build succeeded!
Syncing triggers...
Functions in soil-moisture-sensor:
    iot-hub-trigger - [eventHubTrigger]
```

IoT cihazınızın çalıştığından emin olun. Nem seviyelerini değiştirerek toprağın nemini ayarlayın veya sensörü toprağın içine ve dışına hareket ettirin. Toprak nemi değiştikçe rölenin açılıp kapandığını göreceksiniz.

---

## 🚀 Zorluk

Önceki derste, röle için zamanlamayı röle açıkken ve kapandıktan kısa bir süre sonra MQTT mesajlarından aboneliği kaldırarak yönettiniz. Burada bu yöntemi kullanamazsınız - IoT Hub tetikleyicinizi abonelikten çıkaramazsınız.

Functions App'inizde bunu farklı şekillerde nasıl ele alabileceğinizi düşünün.

## Ders sonrası test

[Ders sonrası test](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/18)

## İnceleme ve Kendi Kendine Çalışma

* Sunucusuz bilişim hakkında daha fazla bilgi edinin: [Serverless Computing page on Wikipedia](https://wikipedia.org/wiki/Serverless_computing)
* Azure'da sunucusuz kullanımı ve daha fazla örnek hakkında bilgi edinin: [Go serverless for your IoT needs Azure blog post](https://azure.microsoft.com/blog/go-serverless-for-your-iot-needs/?WT.mc_id=academic-17441-jabenn)
* Azure Functions hakkında daha fazla bilgi edinin: [Azure Functions YouTube channel](https://www.youtube.com/c/AzureFunctions)

## Ödev

[Manuel röle kontrolü ekleyin](assignment.md)

---

**Feragatname**:  
Bu belge, AI çeviri hizmeti [Co-op Translator](https://github.com/Azure/co-op-translator) kullanılarak çevrilmiştir. Doğruluk için çaba göstersek de, otomatik çevirilerin hata veya yanlışlıklar içerebileceğini lütfen unutmayın. Belgenin orijinal dili, yetkili kaynak olarak kabul edilmelidir. Kritik bilgiler için profesyonel insan çevirisi önerilir. Bu çevirinin kullanımından kaynaklanan yanlış anlamalar veya yanlış yorumlamalar için sorumluluk kabul etmiyoruz.