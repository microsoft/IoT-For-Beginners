<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "8ff0d0a1d29832bb896b9c103b69a452",
  "translation_date": "2025-08-28T03:37:37+00:00",
  "source_file": "1-getting-started/lessons/1-introduction-to-iot/pi.md",
  "language_code": "tr"
}
-->
# Raspberry Pi

[Raspberry Pi](https://raspberrypi.org), tek kartlı bir bilgisayardır. Sensörler ve aktüatörler eklemek için geniş bir cihaz ve ekosistem yelpazesi kullanabilirsiniz. Bu derslerde, [Grove](https://www.seeedstudio.com/category/Grove-c-1003.html) adlı bir donanım ekosistemini kullanarak sensörlere erişim sağlayacak ve Raspberry Pi'nizi Python ile kodlayacaksınız.

![Bir Raspberry Pi 4](../../../../../translated_images/tr/raspberry-pi-4.fd4590d308c3d456.webp)

## Kurulum

Raspberry Pi'nizi IoT donanımı olarak kullanıyorsanız iki seçeneğiniz var: Bu derslerin tamamını Raspberry Pi üzerinde doğrudan kodlayarak çalışabilirsiniz veya 'headless' bir Pi'ye uzaktan bağlanarak bilgisayarınızdan kod yazabilirsiniz.

Başlamadan önce, Grove Base Hat'i Pi'nize bağlamanız gerekiyor.

### Görev - Kurulum

Grove Base Hat'i Pi'nize takın ve Pi'yi yapılandırın.

1. Grove Base Hat'i Pi'nize bağlayın. Hat üzerindeki soket, Pi'nin tüm GPIO pinlerine tam oturur ve tabana sıkıca oturacak şekilde pinlerin üzerine kayar. Hat, Pi'nin üzerine oturur ve onu kaplar.

    ![Grove Hat'in takılması](../../../../../images/pi-grove-hat-fitting.gif)

1. Pi'nizi nasıl programlamak istediğinize karar verin ve aşağıdaki ilgili bölüme gidin:

    * [Pi'nizde doğrudan çalışın](../../../../../1-getting-started/lessons/1-introduction-to-iot)
    * [Pi'yi kodlamak için uzaktan erişim](../../../../../1-getting-started/lessons/1-introduction-to-iot)

### Pi'nizde doğrudan çalışın

Pi'nizde doğrudan çalışmak istiyorsanız, Raspberry Pi OS'in masaüstü sürümünü kullanabilir ve ihtiyacınız olan tüm araçları kurabilirsiniz.

#### Görev - Pi'nizde doğrudan çalışın

Pi'nizi geliştirme için ayarlayın.

1. Pi'nizi kurmak, klavye/fare/monitör bağlamak, WiFi veya ethernet ağına bağlanmak ve yazılımı güncellemek için [Raspberry Pi kurulum rehberi](https://projects.raspberrypi.org/en/projects/raspberry-pi-setting-up) talimatlarını izleyin.

Grove sensörlerini ve aktüatörlerini kullanarak Pi'yi programlamak için cihaz kodunu yazmanıza olanak tanıyan bir düzenleyici ve Grove donanımıyla etkileşim kuran çeşitli kütüphaneler ve araçlar kurmanız gerekecek.

1. Pi yeniden başlatıldıktan sonra, **Terminal** simgesine tıklayarak veya *Menu -> Accessories -> Terminal* seçeneğini seçerek Terminal'i başlatın.

1. İşletim sisteminin ve yüklü yazılımın güncel olduğundan emin olmak için aşağıdaki komutu çalıştırın:

    ```sh
    sudo apt update && sudo apt full-upgrade --yes
    ```

1. Grove donanımı için gerekli tüm kütüphaneleri kurmak için aşağıdaki komutları çalıştırın:

    ```sh
    sudo apt install git python3-dev python3-pip --yes

    git clone https://github.com/Seeed-Studio/grove.py
    cd grove.py
    sudo pip3 install .

    sudo raspi-config nonint do_i2c 0
    ```

    Bu işlem, Git'i ve Python paketlerini yüklemek için Pip'i kurarak başlar.

    Python'un güçlü özelliklerinden biri, [Pip paketlerini](https://pypi.org) yükleme yeteneğidir - bunlar, diğer kişiler tarafından yazılmış ve internete yayınlanmış kod paketleridir. Bir komutla bir Pip paketini bilgisayarınıza yükleyebilir ve ardından bu paketi kodunuzda kullanabilirsiniz.

    Seeed Grove Python paketleri kaynaktan yüklenmelidir. Bu komutlar, bu paketin kaynak kodunu içeren depoyu klonlar ve ardından yerel olarak kurar.

    > 💁 Varsayılan olarak bir paket yüklediğinizde, bu paket bilgisayarınızda her yerde kullanılabilir hale gelir ve bu durum paket sürümleriyle ilgili sorunlara yol açabilir - örneğin, bir uygulama bir paketin bir sürümüne bağlıyken, başka bir uygulama için yeni bir sürüm yüklediğinizde bu sürüm bozulabilir. Bu sorunu çözmek için [Python sanal ortamı](https://docs.python.org/3/library/venv.html) kullanabilirsiniz; bu, Python'un özel bir klasördeki bir kopyasıdır ve Pip paketlerini yüklediğinizde yalnızca o klasöre yüklenir. Pi'nizi kullanırken sanal ortamlar kullanmayacaksınız. Grove yükleme betiği, Grove Python paketlerini küresel olarak yükler, bu nedenle sanal bir ortam kurmanız ve ardından Grove paketlerini manuel olarak bu ortamda yeniden yüklemeniz gerekir. Her proje için temiz bir SD kartı yeniden flaşlayan birçok Pi geliştiricisi olduğu için küresel paketleri kullanmak daha kolaydır.

    Son olarak, I<sup>2</sup>C arayüzünü etkinleştirir.

1. Pi'yi menüyü kullanarak veya Terminal'de aşağıdaki komutu çalıştırarak yeniden başlatın:

    ```sh
    sudo reboot
    ```

1. Pi yeniden başlatıldıktan sonra, Terminal'i yeniden başlatın ve cihaz kodunuzu Python'da yazmak için kullanacağınız düzenleyici olan [Visual Studio Code (VS Code)](https://code.visualstudio.com?WT.mc_id=academic-17441-jabenn)'u yüklemek için aşağıdaki komutu çalıştırın:

    ```sh
    sudo apt install code
    ```

    Bu yüklendikten sonra, VS Code üst menüden erişilebilir olacaktır.

    > 💁 Bu derslerde talimatlar VS Code kullanılarak verilecektir, ancak tercih ettiğiniz bir Python IDE veya düzenleyiciyi kullanmakta özgürsünüz.

1. Pylance'ı yükleyin. Bu, Python dil desteği sağlayan VS Code için bir uzantıdır. Bu uzantıyı VS Code'da yüklemek için [Pylance uzantı belgelerine](https://marketplace.visualstudio.com/items?WT.mc_id=academic-17441-jabenn&itemName=ms-python.vscode-pylance) başvurun.

### Pi'yi kodlamak için uzaktan erişim

Pi üzerinde doğrudan kod yazmak yerine, Pi'yi bir klavye/fare/monitöre bağlı olmadan 'headless' çalıştırabilir ve bilgisayarınızdan Visual Studio Code kullanarak yapılandırabilir ve kodlayabilirsiniz.

#### Pi OS'yi ayarlayın

Uzaktan kod yazmak için, Pi OS'nin bir SD karta yüklenmesi gerekir.

##### Görev - Pi OS'yi ayarlayın

Headless Pi OS'yi ayarlayın.

1. [Raspberry Pi OS yazılım sayfasından](https://www.raspberrypi.org/software/) **Raspberry Pi Imager**'ı indirin ve yükleyin.

1. Gerekirse bir adaptör kullanarak bir SD kartı bilgisayarınıza takın.

1. Raspberry Pi Imager'ı başlatın.

1. Raspberry Pi Imager'dan **CHOOSE OS** düğmesini seçin, ardından *Raspberry Pi OS (Other)* ve ardından *Raspberry Pi OS Lite (32-bit)* seçeneğini seçin.

    ![Raspberry Pi Imager ile Raspberry Pi OS Lite seçili](../../../../../translated_images/tr/raspberry-pi-imager.24aedeab9e233d84.webp)

    > 💁 Raspberry Pi OS Lite, Raspberry Pi OS'nin masaüstü kullanıcı arayüzü veya kullanıcı arayüzü tabanlı araçları içermeyen bir sürümüdür. Bunlar headless bir Pi için gerekli değildir ve kurulumun daha küçük ve açılış süresinin daha hızlı olmasını sağlar.

1. **CHOOSE STORAGE** düğmesini seçin ve SD kartınızı seçin.

1. **Advanced Options**'ı `Ctrl+Shift+X` tuşlarına basarak başlatın. Bu seçenekler, Raspberry Pi OS'nin SD karta yazılmadan önce bazı ön yapılandırmalarını sağlar.

    1. **Enable SSH** kutusunu işaretleyin ve `pi` kullanıcısı için bir şifre belirleyin. Bu, Pi'ye daha sonra giriş yapmak için kullanacağınız şifre olacaktır.

    1. Pi'ye WiFi üzerinden bağlanmayı planlıyorsanız, **Configure WiFi** kutusunu işaretleyin ve WiFi SSID ve şifrenizi girin, ayrıca WiFi ülkenizi seçin. Ethernet kablosu kullanacaksanız bunu yapmanıza gerek yoktur. Bağlandığınız ağın bilgisayarınızın bulunduğu ağla aynı olduğundan emin olun.

    1. **Set locale settings** kutusunu işaretleyin ve ülkenizi ve zaman diliminizi ayarlayın.

    1. **SAVE** düğmesini seçin.

1. OS'yi SD karta yazmak için **WRITE** düğmesini seçin. macOS kullanıyorsanız, disk görüntülerini yazan temel araçların ayrıcalıklı erişime ihtiyacı olduğu için şifrenizi girmeniz istenecektir.

OS SD karta yazılacak ve işlem tamamlandığında kart işletim sistemi tarafından çıkarılacak ve size bildirimde bulunulacaktır. SD kartı bilgisayarınızdan çıkarın, Pi'ye takın, Pi'yi açın ve düzgün bir şekilde başlatılması için yaklaşık 2 dakika bekleyin.

#### Pi'ye bağlanın

Bir sonraki adım, Pi'ye uzaktan erişmektir. Bunu, macOS, Linux ve Windows'un son sürümlerinde bulunan `ssh` kullanarak yapabilirsiniz.

##### Görev - Pi'ye bağlanın

Pi'ye uzaktan erişin.

1. Bir Terminal veya Komut İstemi başlatın ve Pi'ye bağlanmak için aşağıdaki komutu girin:

    ```sh
    ssh pi@raspberrypi.local
    ```

    Windows'un eski bir sürümünü kullanıyorsanız ve `ssh` yüklü değilse, OpenSSH kullanabilirsiniz. Kurulum talimatlarını [OpenSSH kurulum belgelerinde](https://docs.microsoft.com//windows-server/administration/openssh/openssh_install_firstuse?WT.mc_id=academic-17441-jabenn) bulabilirsiniz.

1. Bu, Pi'ye bağlanmalı ve şifreyi sormalıdır.

    Bilgisayarları `<hostname>.local` kullanarak ağınızda bulabilmek, Linux ve Windows'a oldukça yeni bir eklemedir. Linux veya Windows kullanıyorsanız ve Hostname bulunamadı hatası alıyorsanız, ZeroConf ağını (Apple tarafından Bonjour olarak da adlandırılır) etkinleştirmek için ek yazılım yüklemeniz gerekecektir:

    1. Linux kullanıyorsanız, aşağıdaki komutla Avahi'yi yükleyin:

        ```sh
        sudo apt-get install avahi-daemon
        ```

    1. Windows kullanıyorsanız, ZeroConf'u etkinleştirmenin en kolay yolu [Windows için Bonjour Yazdırma Hizmetleri](http://support.apple.com/kb/DL999)'ni yüklemektir. Ayrıca [Windows için iTunes](https://www.apple.com/itunes/download/) yükleyerek daha yeni bir yardımcı program sürümünü (tek başına mevcut olmayan) edinebilirsiniz.

    > 💁 `raspberrypi.local` kullanarak bağlanamıyorsanız, Pi'nizin IP adresini kullanabilirsiniz. IP adresini almanın birden fazla yolunu açıklayan [Raspberry Pi IP adresi belgelerine](https://www.raspberrypi.org/documentation/remote-access/ip-address.md) başvurun.

1. Raspberry Pi Imager Advanced Options'da belirlediğiniz şifreyi girin.

#### Pi'deki yazılımı yapılandırın

Pi'ye bağlandıktan sonra, işletim sisteminin güncel olduğundan emin olmanız ve Grove donanımıyla etkileşim kuran çeşitli kütüphaneler ve araçları yüklemeniz gerekir.

##### Görev - Pi'deki yazılımı yapılandırın

Yüklü Pi yazılımını yapılandırın ve Grove kütüphanelerini yükleyin.

1. `ssh` oturumunuzdan, Pi'yi güncellemek ve ardından yeniden başlatmak için aşağıdaki komutu çalıştırın:

    ```sh
    sudo apt update && sudo apt full-upgrade --yes && sudo reboot
    ```

    Pi güncellenecek ve yeniden başlatılacaktır. Pi yeniden başlatıldığında `ssh` oturumu sona erecek, bu yüzden yaklaşık 30 saniye bekleyin ve ardından yeniden bağlanın.

1. Yeniden bağlanmış `ssh` oturumundan, Grove donanımı için gerekli tüm kütüphaneleri yüklemek için aşağıdaki komutları çalıştırın:

    ```sh
    sudo apt install git python3-dev python3-pip --yes

    git clone https://github.com/Seeed-Studio/grove.py
    cd grove.py
    sudo pip3 install .

    sudo raspi-config nonint do_i2c 0
    ```

    Bu işlem, Git'i ve Python paketlerini yüklemek için Pip'i kurarak başlar.

    Python'un güçlü özelliklerinden biri, [Pip paketlerini](https://pypi.org) yükleme yeteneğidir - bunlar, diğer kişiler tarafından yazılmış ve internete yayınlanmış kod paketleridir. Bir komutla bir Pip paketini bilgisayarınıza yükleyebilir ve ardından bu paketi kodunuzda kullanabilirsiniz.

    Seeed Grove Python paketleri kaynaktan yüklenmelidir. Bu komutlar, bu paketin kaynak kodunu içeren depoyu klonlar ve ardından yerel olarak kurar.

    > 💁 Varsayılan olarak bir paket yüklediğinizde, bu paket bilgisayarınızda her yerde kullanılabilir hale gelir ve bu durum paket sürümleriyle ilgili sorunlara yol açabilir - örneğin, bir uygulama bir paketin bir sürümüne bağlıyken, başka bir uygulama için yeni bir sürüm yüklediğinizde bu sürüm bozulabilir. Bu sorunu çözmek için [Python sanal ortamı](https://docs.python.org/3/library/venv.html) kullanabilirsiniz; bu, Python'un özel bir klasördeki bir kopyasıdır ve Pip paketlerini yüklediğinizde yalnızca o klasöre yüklenir. Pi'nizi kullanırken sanal ortamlar kullanmayacaksınız. Grove yükleme betiği, Grove Python paketlerini küresel olarak yükler, bu nedenle sanal bir ortam kurmanız ve ardından Grove paketlerini manuel olarak bu ortamda yeniden yüklemeniz gerekir. Her proje için temiz bir SD kartı yeniden flaşlayan birçok Pi geliştiricisi olduğu için küresel paketleri kullanmak daha kolaydır.

    Son olarak, I<sup>2</sup>C arayüzünü etkinleştirir.

1. Pi'yi aşağıdaki komutu çalıştırarak yeniden başlatın:

    ```sh
    sudo reboot
    ```

    Pi yeniden başlatıldığında `ssh` oturumu sona erecek. Yeniden bağlanmanıza gerek yoktur.

#### Uzaktan erişim için VS Code'u yapılandırın

Pi yapılandırıldıktan sonra, bilgisayarınızdan Visual Studio Code (VS Code) kullanarak Pi'ye bağlanabilirsiniz - bu, Python'da cihaz kodunuzu yazmak için kullanacağınız ücretsiz bir geliştirici metin editörüdür.

##### Görev - Uzaktan erişim için VS Code'u yapılandırın

Gerekli yazılımı yükleyin ve Pi'nize uzaktan bağlanın.

1. [VS Code belgelerini](https://code.visualstudio.com?WT.mc_id=academic-17441-jabenn) takip ederek bilgisayarınıza VS Code'u yükleyin.

1. [VS Code SSH kullanarak Uzaktan Geliştirme belgelerindeki](https://code.visualstudio.com/docs/remote/ssh?WT.mc_id=academic-17441-jabenn) talimatları izleyerek gerekli bileşenleri yükleyin.

1. Aynı talimatları izleyerek VS Code'u Pi'ye bağlayın.

1. Bağlandıktan sonra, [uzantıları yönetme](https://code.visualstudio.com/docs/remote/ssh#_managing-extensions?WT.mc_id=academic-17441-jabenn) talimatlarını izleyerek [Pylance uzantısını](https://marketplace.visualstudio.com/items?WT.mc_id=academic-17441-jabenn&itemName=ms-python.vscode-pylance) Pi'ye uzaktan yükleyin.

## Merhaba dünya
Yeni bir programlama dili veya teknolojiyle çalışmaya başlarken, genellikle bir 'Merhaba Dünya' uygulaması oluşturulur - tüm araçların doğru şekilde yapılandırıldığını göstermek için `"Merhaba Dünya"` gibi bir metni çıktı olarak veren küçük bir uygulama.

Pi için Merhaba Dünya uygulaması, Python ve Visual Studio Code'un doğru şekilde kurulduğundan emin olmanızı sağlayacaktır.

Bu uygulama `nightlight` adlı bir klasörde bulunacak ve bu ödevin ilerleyen bölümlerinde gece lambası uygulamasını oluşturmak için farklı kodlarla yeniden kullanılacaktır.

### Görev - merhaba dünya

Merhaba Dünya uygulamasını oluşturun.

1. VS Code'u başlatın, ya doğrudan Pi üzerinde ya da Remote SSH uzantısını kullanarak bilgisayarınızdan Pi'ye bağlanarak.

1. *Terminal -> Yeni Terminal* seçeneğini seçerek veya `` CTRL+` `` tuşlarına basarak VS Code Terminalini başlatın. Terminal, `pi` kullanıcısının ana dizininde açılacaktır.

1. Kodunuz için bir dizin oluşturmak ve bu dizin içinde `app.py` adlı bir Python dosyası oluşturmak için aşağıdaki komutları çalıştırın:

    ```sh
    mkdir nightlight
    cd nightlight
    touch app.py
    ```

1. Bu klasörü VS Code'da açmak için *Dosya -> Aç...* seçeneğini seçin ve *nightlight* klasörünü seçtikten sonra **Tamam**'ı tıklayın.

    ![VS Code açma penceresi nightlight klasörünü gösteriyor](../../../../../translated_images/tr/vscode-open-nightlight-remote.d3d2a4011e30d535.webp)

1. VS Code gezgininden `app.py` dosyasını açın ve aşağıdaki kodu ekleyin:

    ```python
    print('Hello World!')
    ```

    `print` fonksiyonu, kendisine iletilen her şeyi konsola yazdırır.

1. Python uygulamanızı çalıştırmak için VS Code Terminalinden aşağıdaki komutu çalıştırın:

    ```sh
    python app.py
    ```

    > 💁 Eğer Python 2'nin yanı sıra Python 3 (en son sürüm) yüklüyse, bu kodu çalıştırmak için açıkça `python3` çağırmanız gerekebilir. Eğer Python 2 yüklüyse, `python` komutunu çağırmak Python 2'yi kullanacaktır. Varsayılan olarak, en son Raspberry Pi OS sürümleri yalnızca Python 3 içerir.

    Terminalde aşağıdaki çıktı görünecektir:

    ```output
    pi@raspberrypi:~/nightlight $ python3 app.py
    Hello World!
    ```

> 💁 Bu kodu [code/pi](../../../../../1-getting-started/lessons/1-introduction-to-iot/code/pi) klasöründe bulabilirsiniz.

😀 'Merhaba Dünya' programınız başarıyla çalıştı!

---

**Feragatname**:  
Bu belge, AI çeviri hizmeti [Co-op Translator](https://github.com/Azure/co-op-translator) kullanılarak çevrilmiştir. Doğruluk için çaba göstersek de, otomatik çevirilerin hata veya yanlışlıklar içerebileceğini lütfen unutmayın. Belgenin orijinal dili, yetkili kaynak olarak kabul edilmelidir. Kritik bilgiler için profesyonel insan çevirisi önerilir. Bu çevirinin kullanımından kaynaklanan yanlış anlamalar veya yanlış yorumlamalar için sorumluluk kabul etmiyoruz.