# Sanal tek kartlı bilgisayar

Bir IoT cihazı, sensörler ve aktüatörler satın almak yerine, bilgisayarınızı IoT donanımını simüle etmek için kullanabilirsiniz. [CounterFit projesi](https://github.com/CounterFit-IoT/CounterFit), sensörler ve aktüatörler gibi IoT donanımını simüle eden bir uygulamayı yerel olarak çalıştırmanıza ve fiziksel donanım kullanarak Raspberry Pi üzerinde yazacağınız kodla aynı şekilde yazılmış yerel Python kodundan sensörlere ve aktüatörlere erişmenize olanak tanır.

## Kurulum

CounterFit'i kullanmak için bilgisayarınıza bazı ücretsiz yazılımlar yüklemeniz gerekecek.

### Görev

Gerekli yazılımları yükleyin.

1. Python'u yükleyin. En son Python sürümünü yükleme talimatları için [Python indirme sayfasına](https://www.python.org/downloads/) bakın.

1. Visual Studio Code (VS Code) yükleyin. Bu, Python'da sanal cihaz kodunuzu yazmak için kullanacağınız editördür. VS Code'u yükleme talimatları için [VS Code belgelerine](https://code.visualstudio.com?WT.mc_id=academic-17441-jabenn) bakın.

    > 💁 Bu derslerde tercih ettiğiniz bir Python IDE veya editörünü kullanmakta özgürsünüz, ancak dersler VS Code kullanımı temel alınarak talimatlar verecektir.

1. VS Code Pylance uzantısını yükleyin. Bu, Python dil desteği sağlayan bir VS Code uzantısıdır. Bu uzantıyı VS Code'a yükleme talimatları için [Pylance uzantı belgelerine](https://marketplace.visualstudio.com/items?WT.mc_id=academic-17441-jabenn&itemName=ms-python.vscode-pylance) bakın.

CounterFit uygulamasını yükleme ve yapılandırma talimatları, ilgili zamanlarda ve proje bazında verilecektir.

## Merhaba Dünya

Yeni bir programlama dili veya teknolojiyle başlarken geleneksel olarak bir 'Merhaba Dünya' uygulaması oluşturulur - tüm araçların doğru şekilde yapılandırıldığını göstermek için `"Merhaba Dünya"` gibi bir metni çıktı olarak veren küçük bir uygulama.

Sanal IoT donanımı için Merhaba Dünya uygulaması, Python ve Visual Studio Code'un doğru şekilde yüklendiğinden emin olmanızı sağlar. Ayrıca sanal IoT sensörleri ve aktüatörleri için CounterFit'e bağlanır. Herhangi bir donanım kullanmaz, sadece her şeyin çalıştığını kanıtlamak için bağlanır.

Bu uygulama `nightlight` adlı bir klasörde bulunacak ve bu ödevin sonraki bölümlerinde gece lambası uygulamasını oluşturmak için farklı kodlarla yeniden kullanılacaktır.

### Bir Python sanal ortamı yapılandırın

Python'un güçlü özelliklerinden biri, [Pip paketlerini](https://pypi.org) yükleme yeteneğidir - bunlar, diğer kişiler tarafından yazılmış ve İnternet'e yayınlanmış kod paketleridir. Bir Pip paketini bilgisayarınıza tek bir komutla yükleyebilir ve ardından bu paketi kodunuzda kullanabilirsiniz. CounterFit ile iletişim kurmak için bir paket yüklemek için Pip kullanacaksınız.

Varsayılan olarak bir paket yüklediğinizde, bu paket bilgisayarınızda her yerde kullanılabilir hale gelir ve bu, paket sürümleriyle ilgili sorunlara yol açabilir - örneğin, bir uygulamanın bir paketin bir sürümüne bağlı olması ve başka bir uygulama için yeni bir sürüm yüklediğinizde bozulması gibi. Bu sorunu çözmek için, [Python sanal ortamı](https://docs.python.org/3/library/venv.html) kullanabilirsiniz; bu, özel bir klasörde Python'un bir kopyasıdır ve Pip paketlerini yüklediğinizde yalnızca o klasöre yüklenir.

> 💁 Eğer bir Raspberry Pi kullanıyorsanız, bu cihazda Pip paketlerini yönetmek için bir sanal ortam kurmadınız, bunun yerine küresel paketler kullanıyorsunuz çünkü Grove paketleri yükleyici betiği tarafından küresel olarak yüklenir.

#### Görev - bir Python sanal ortamı yapılandırın

Bir Python sanal ortamı yapılandırın ve CounterFit için Pip paketlerini yükleyin.

1. Terminalinizden veya komut satırından, yeni bir dizin oluşturmak ve bu dizine gitmek için aşağıdaki komutları çalıştırın:

    ```sh
    mkdir nightlight
    cd nightlight
    ```

1. Şimdi `.venv` klasöründe bir sanal ortam oluşturmak için aşağıdaki komutu çalıştırın:

    ```sh
    python3 -m venv .venv
    ```

    > 💁 Python 2'nin yanı sıra Python 3'ün (en son sürüm) yüklü olma ihtimaline karşı sanal ortamı oluşturmak için açıkça `python3` çağırmanız gerekir. Eğer Python 2 yüklüyse, `python` çağrısı Python 2'yi kullanacaktır.

1. Sanal ortamı etkinleştirin:

    * Windows'da:
        * Komut İstemi veya Windows Terminal üzerinden Komut İstemi kullanıyorsanız, aşağıdaki komutu çalıştırın:

            ```cmd
            .venv\Scripts\activate.bat
            ```

        * PowerShell kullanıyorsanız, aşağıdaki komutu çalıştırın:

            ```powershell
            .\.venv\Scripts\Activate.ps1
            ```

            > Eğer bu sistemde betiklerin çalıştırılmasının devre dışı bırakıldığına dair bir hata alırsanız, uygun bir yürütme politikası ayarlayarak betiklerin çalıştırılmasını etkinleştirmeniz gerekecektir. Bunu, PowerShell'i yönetici olarak başlatarak ve ardından aşağıdaki komutu çalıştırarak yapabilirsiniz:

            ```powershell
            Set-ExecutionPolicy -ExecutionPolicy Unrestricted
            ```

            Onay istendiğinde `Y` girin. Ardından PowerShell'i yeniden başlatın ve tekrar deneyin.

            Gerekirse bu yürütme politikasını daha sonra sıfırlayabilirsiniz. Bununla ilgili daha fazla bilgiyi [Microsoft Docs'taki Yürütme Politikaları sayfasında](https://docs.microsoft.com/powershell/module/microsoft.powershell.core/about/about_execution_policies?WT.mc_id=academic-17441-jabenn) bulabilirsiniz.

    * macOS veya Linux'ta, aşağıdaki komutu çalıştırın:

        ```cmd
        source ./.venv/bin/activate
        ```

    > 💁 Bu komutlar, sanal ortamı oluşturduğunuz konumdan çalıştırılmalıdır. `.venv` klasörüne asla gitmeniz gerekmez, her zaman etkinleştirme komutunu ve paketleri yüklemek veya kod çalıştırmak için komutları sanal ortamı oluşturduğunuz klasörden çalıştırmalısınız.

1. Sanal ortam etkinleştirildikten sonra, varsayılan `python` komutu, sanal ortamı oluşturmak için kullanılan Python sürümünü çalıştıracaktır. Sürümü almak için aşağıdaki komutu çalıştırın:

    ```sh
    python --version
    ```

    Çıktı aşağıdakileri içermelidir:

    ```output
    (.venv) ➜  nightlight python --version
    Python 3.9.1
    ```

    > 💁 Python sürümünüz farklı olabilir - sürüm 3.6 veya daha yüksek olduğu sürece sorun yok. Eğer değilse, bu klasörü silin, daha yeni bir Python sürümü yükleyin ve tekrar deneyin.

1. CounterFit için Pip paketlerini yüklemek için aşağıdaki komutları çalıştırın. Bu paketler, Grove donanımı için ana CounterFit uygulamasının yanı sıra shims içerir. Bu shims, fiziksel sensörler ve Grove ekosisteminden aktüatörler kullanıyormuş gibi kod yazmanıza olanak tanır, ancak sanal IoT cihazlarına bağlanır.

    ```sh
    pip install CounterFit
    pip install counterfit-connection
    pip install counterfit-shims-grove
    ```

    Bu pip paketleri yalnızca sanal ortamda yüklenecek ve bu ortamın dışında kullanılamayacaktır.

### Kodu yazın

Python sanal ortamı hazır olduğunda, 'Merhaba Dünya' uygulaması için kodu yazabilirsiniz.

#### Görev - kodu yazın

Konsola `"Merhaba Dünya"` yazdıran bir Python uygulaması oluşturun.

1. Sanal ortam içinde terminalinizden veya komut satırından aşağıdaki komutu çalıştırarak `app.py` adlı bir Python dosyası oluşturun:

    * Windows'dan çalıştırın:

        ```cmd
        type nul > app.py
        ```

    * macOS veya Linux'ta çalıştırın:

        ```cmd
        touch app.py
        ```

1. Mevcut klasörü VS Code'da açın:

    ```sh
    code .
    ```

    > 💁 Eğer terminaliniz macOS'ta `command not found` döndürüyorsa, bu VS Code'un PATH'e eklenmediği anlamına gelir. PATH'e VS Code'u eklemek için [VS Code belgelerindeki Komut satırından başlatma bölümündeki](https://code.visualstudio.com/docs/setup/mac?WT.mc_id=academic-17441-jabenn#_launching-from-the-command-line) talimatları izleyin ve ardından komutu çalıştırın. VS Code, Windows ve Linux'ta varsayılan olarak PATH'e eklenir.

1. VS Code başlatıldığında, Python sanal ortamını etkinleştirecektir. Seçilen sanal ortam alt durum çubuğunda görünecektir:

    ![VS Code seçilen sanal ortamı gösteriyor](../../../../../translated_images/tr/vscode-virtual-env.8ba42e04c3d533cf.webp)

1. VS Code Terminali, VS Code başlatıldığında zaten çalışıyorsa, sanal ortam terminalde etkinleştirilmemiş olacaktır. En kolay şey, **Aktif terminal örneğini kapat** düğmesini kullanarak terminali kapatmaktır:

    ![VS Code Aktif terminal örneğini kapat düğmesi](../../../../../translated_images/tr/vscode-kill-terminal.1cc4de7c6f25ee08.webp)

    Terminalin sanal ortamı etkinleştirdiğini, terminal isteminde sanal ortamın adının bir ön ek olarak görünmesiyle anlayabilirsiniz. Örneğin, şu şekilde olabilir:

    ```sh
    (.venv) ➜  nightlight
    ```

    Eğer istemde `.venv` ön eki yoksa, sanal ortam terminalde etkin değil demektir.

1. *Terminal -> Yeni Terminal* seçeneğini seçerek veya `` CTRL+` `` tuşlarına basarak yeni bir VS Code Terminali başlatın. Yeni terminal sanal ortamı yükleyecek ve bunu etkinleştirme çağrısı terminalde görünecektir. İstem ayrıca sanal ortamın adını (`.venv`) içerecektir:

    ```output
    ➜  nightlight source .venv/bin/activate
    (.venv) ➜  nightlight 
    ```

1. VS Code gezgininden `app.py` dosyasını açın ve aşağıdaki kodu ekleyin:

    ```python
    print('Hello World!')
    ```

    `print` fonksiyonu, kendisine iletilen her şeyi konsola yazdırır.

1. VS Code terminalinden, Python uygulamanızı çalıştırmak için aşağıdaki komutu çalıştırın:

    ```sh
    python app.py
    ```

    Çıktı aşağıdaki gibi olacaktır:

    ```output
    (.venv) ➜  nightlight python app.py 
    Hello World!
    ```

😀 'Merhaba Dünya' programınız başarılı oldu!

### 'Donanımı' bağlayın

İkinci bir 'Merhaba Dünya' adımı olarak, CounterFit uygulamasını çalıştıracak ve kodunuzu ona bağlayacaksınız. Bu, bir IoT donanımını bir geliştirme kitine bağlamanın sanal eşdeğeridir.

#### Görev - 'Donanımı' bağlayın

1. VS Code terminalinden, CounterFit uygulamasını aşağıdaki komutla başlatın:

    ```sh
    counterfit
    ```

    Uygulama çalışmaya başlayacak ve web tarayıcınızda açılacaktır:

    ![Counter Fit uygulaması bir tarayıcıda çalışıyor](../../../../../translated_images/tr/counterfit-first-run.433326358b669b31.webp)

    *Bağlantısız* olarak işaretlenecek ve sağ üst köşedeki LED kapalı olacaktır.

1. `app.py` dosyasının üstüne aşağıdaki kodu ekleyin:

    ```python
    from counterfit_connection import CounterFitConnection
    CounterFitConnection.init('127.0.0.1', 5000)
    ```

    Bu kod, daha önce yüklediğiniz `counterfit-connection` pip paketinden gelen `counterfit_connection` modülünden `CounterFitConnection` sınıfını içe aktarır. Ardından, `127.0.0.1` üzerinde çalışan CounterFit uygulamasına bir bağlantı başlatır, bu IP adresi her zaman yerel bilgisayarınıza erişmek için kullanılabilir (genellikle *localhost* olarak adlandırılır), 5000 portunda.

    > 💁 Eğer 5000 portunda çalışan başka uygulamalarınız varsa, bunu kodda portu güncelleyerek ve CounterFit'i `CounterFit --port <port_number>` komutuyla çalıştırarak değiştirebilirsiniz. `<port_number>` yerine kullanmak istediğiniz portu yazın.

1. CounterFit uygulaması mevcut terminalde çalıştığı için yeni bir VS Code terminali başlatmanız gerekecek. **Yeni bir entegre terminal oluştur** düğmesini seçerek bunu yapabilirsiniz.

    ![VS Code Yeni bir entegre terminal oluştur düğmesi](../../../../../translated_images/tr/vscode-new-terminal.77db8fc0f9cd3182.webp)

1. Bu yeni terminalde, daha önce olduğu gibi `app.py` dosyasını çalıştırın. CounterFit'in durumu **Bağlı** olarak değişecek ve LED yanacaktır.

    ![Counter Fit bağlı olarak gösteriliyor](../../../../../translated_images/tr/counterfit-connected.ed30b46d8f79b092.webp)

> 💁 Bu kodu [code/virtual-device](../../../../../1-getting-started/lessons/1-introduction-to-iot/code/virtual-device) klasöründe bulabilirsiniz.

😀 Donanıma bağlantınız başarılı oldu!

---

**Feragatname**:  
Bu belge, AI çeviri hizmeti [Co-op Translator](https://github.com/Azure/co-op-translator) kullanılarak çevrilmiştir. Doğruluk için çaba göstersek de, otomatik çevirilerin hata veya yanlışlıklar içerebileceğini lütfen unutmayın. Belgenin orijinal dili, yetkili kaynak olarak kabul edilmelidir. Kritik bilgiler için profesyonel insan çevirisi önerilir. Bu çevirinin kullanımından kaynaklanan yanlış anlamalar veya yanlış yorumlamalar için sorumluluk kabul etmiyoruz.