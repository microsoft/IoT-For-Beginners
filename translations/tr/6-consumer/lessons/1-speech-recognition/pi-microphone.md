<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "7e45d884493c5222348b43fbc4481b6a",
  "translation_date": "2025-08-28T03:04:20+00:00",
  "source_file": "6-consumer/lessons/1-speech-recognition/pi-microphone.md",
  "language_code": "tr"
}
-->
# Mikrofonunuzu ve Hoparlörlerinizi Yapılandırma - Raspberry Pi

Bu dersin bu bölümünde, Raspberry Pi'nize bir mikrofon ve hoparlör ekleyeceksiniz.

## Donanım

Raspberry Pi bir mikrofona ihtiyaç duyar.

Pi'nin dahili bir mikrofonu yoktur, bu yüzden harici bir mikrofon eklemeniz gerekecek. Bunu yapmanın birkaç yolu vardır:

* USB mikrofon
* USB kulaklık
* USB hepsi bir arada hoparlörlü telefon
* USB ses adaptörü ve 3.5mm jaklı mikrofon
* [ReSpeaker 2-Mics Pi HAT](https://www.seeedstudio.com/ReSpeaker-2-Mics-Pi-HAT.html)

> 💁 Bluetooth mikrofonlar Raspberry Pi'de tamamen desteklenmez, bu yüzden bir Bluetooth mikrofon veya kulaklık kullanıyorsanız, eşleştirme veya ses kaydı konusunda sorun yaşayabilirsiniz.

Raspberry Pi'ler 3.5mm kulaklık jakı ile gelir. Bunu kulaklık, kulaklık seti veya hoparlör bağlamak için kullanabilirsiniz. Ayrıca hoparlörleri şu yöntemlerle ekleyebilirsiniz:

* HDMI ses çıkışı ile bir monitör veya TV
* USB hoparlörler
* USB kulaklık
* USB hepsi bir arada hoparlörlü telefon
* [ReSpeaker 2-Mics Pi HAT](https://www.seeedstudio.com/ReSpeaker-2-Mics-Pi-HAT.html) ile bir hoparlör bağlayarak, ya 3.5mm jak üzerinden ya da JST portu üzerinden

## Mikrofon ve Hoparlörleri Bağlama ve Yapılandırma

Mikrofon ve hoparlörlerin bağlanması ve yapılandırılması gerekmektedir.

### Görev - Mikrofonu bağlama ve yapılandırma

1. Mikrofonu uygun yöntemle bağlayın. Örneğin, USB portlarından biri üzerinden bağlayabilirsiniz.

1. Eğer ReSpeaker 2-Mics Pi HAT kullanıyorsanız, Grove tabanlı hattı çıkarabilir ve yerine ReSpeaker hattını takabilirsiniz.

    ![ReSpeaker hattı takılı bir Raspberry Pi](../../../../../translated_images/tr/pi-respeaker-hat.f00fabe7dd039a93e2e0aa0fc946c9af0c6a9eb17c32fa1ca097fb4e384f69f0.png)

    Bu dersin ilerleyen bölümlerinde bir Grove düğmesine ihtiyacınız olacak, ancak bu hattın içine bir düğme yerleştirilmiştir, bu yüzden Grove tabanlı hattı gerekli değildir.

    Hattı taktıktan sonra bazı sürücüleri yüklemeniz gerekecek. Sürücü yükleme talimatları için [Seeed başlangıç talimatlarına](https://wiki.seeedstudio.com/ReSpeaker_2_Mics_Pi_HAT_Raspberry/#getting-started) başvurun.

    > ⚠️ Talimatlar bir depoyu klonlamak için `git` kullanır. Eğer Pi'nizde `git` yüklü değilse, aşağıdaki komutu çalıştırarak yükleyebilirsiniz:
    >
    > ```sh
    > sudo apt install git --yes
    > ```

1. Mikrofon hakkında bilgi görmek için Pi'de veya VS Code üzerinden uzaktan SSH oturumu ile bağlı Terminal'de aşağıdaki komutu çalıştırın:

    ```sh
    arecord -l
    ```

    Bağlı mikrofonların bir listesini göreceksiniz. Bu liste aşağıdaki gibi görünebilir:

    ```output
    pi@raspberrypi:~ $ arecord -l
    **** List of CAPTURE Hardware Devices ****
    card 1: M0 [eMeet M0], device 0: USB Audio [USB Audio]
      Subdevices: 1/1
      Subdevice #0: subdevice #0
    ```

    Sadece bir mikrofonunuz olduğunu varsayarsak, yalnızca bir giriş görmelisiniz. Linux'ta mikrofon yapılandırması karmaşık olabilir, bu yüzden en kolayı yalnızca bir mikrofon kullanmak ve diğerlerini çıkarmaktır.

    Kart numarasını not alın, çünkü bunu daha sonra kullanacaksınız. Yukarıdaki çıktıda kart numarası 1'dir.

### Görev - Hoparlörü bağlama ve yapılandırma

1. Hoparlörleri uygun yöntemle bağlayın.

1. Hoparlörler hakkında bilgi görmek için Pi'de veya VS Code üzerinden uzaktan SSH oturumu ile bağlı Terminal'de aşağıdaki komutu çalıştırın:

    ```sh
    aplay -l
    ```

    Bağlı hoparlörlerin bir listesini göreceksiniz. Bu liste aşağıdaki gibi görünebilir:

    ```output
    pi@raspberrypi:~ $ aplay -l
    **** List of PLAYBACK Hardware Devices ****
    card 0: Headphones [bcm2835 Headphones], device 0: bcm2835 Headphones [bcm2835 Headphones]
      Subdevices: 8/8
      Subdevice #0: subdevice #0
      Subdevice #1: subdevice #1
      Subdevice #2: subdevice #2
      Subdevice #3: subdevice #3
      Subdevice #4: subdevice #4
      Subdevice #5: subdevice #5
      Subdevice #6: subdevice #6
      Subdevice #7: subdevice #7
    card 1: M0 [eMeet M0], device 0: USB Audio [USB Audio]
      Subdevices: 1/1
      Subdevice #0: subdevice #0
    ```

    Her zaman `card 0: Headphones` göreceksiniz çünkü bu dahili kulaklık jakıdır. Eğer ek hoparlörler eklediyseniz, örneğin bir USB hoparlör, bu da listede görünecektir.

1. Eğer dahili kulaklık jakına bağlı bir hoparlör veya kulaklık yerine ek bir hoparlör kullanıyorsanız, bunu varsayılan olarak yapılandırmanız gerekir. Bunu yapmak için aşağıdaki komutu çalıştırın:

    ```sh
    sudo nano /usr/share/alsa/alsa.conf
    ```

    Bu, `nano` adlı terminal tabanlı bir metin düzenleyicide bir yapılandırma dosyasını açacaktır. Klavyenizdeki ok tuşlarını kullanarak aşağı kaydırın ve şu satırı bulun:

    ```output
    defaults.pcm.card 0
    ```

    Değeri, `aplay -l` çağrısından gelen listeden kullanmak istediğiniz kart numarasına değiştirin. Örneğin, yukarıdaki çıktıda `card 1: M0 [eMeet M0], device 0: USB Audio [USB Audio]` adlı ikinci bir ses kartı var, kart 1'i kullanıyor. Bunu kullanmak için satırı şu şekilde güncellerdim:

    ```output
    defaults.pcm.card 1
    ```

    Bu değeri uygun kart numarasına ayarlayın. Klavyenizdeki ok tuşlarını kullanarak numaraya gidin, ardından metin dosyalarını düzenlerken normal şekilde silip yeni numarayı yazabilirsiniz.

1. Değişiklikleri kaydedin ve dosyayı kapatmak için `Ctrl+x` tuşlarına basın. Dosyayı kaydetmek için `y` tuşuna basın, ardından dosya adını seçmek için `return` tuşuna basın.

### Görev - Mikrofon ve hoparlörü test etme

1. Mikrofon üzerinden 5 saniyelik ses kaydetmek için aşağıdaki komutu çalıştırın:

    ```sh
    arecord --format=S16_LE --duration=5 --rate=16000 --file-type=wav out.wav
    ```

    Bu komut çalışırken, mikrofonunuza ses yapın; konuşarak, şarkı söyleyerek, beatbox yaparak, bir enstrüman çalarak veya istediğiniz şekilde.

1. 5 saniye sonra kayıt duracak. Kaydedilen sesi oynatmak için aşağıdaki komutu çalıştırın:

    ```sh
    aplay --format=S16_LE --rate=16000 out.wav
    ```

    Sesi hoparlörlerden oynatıldığını duyacaksınız. Hoparlörünüzdeki çıkış sesini gerektiği gibi ayarlayın.

1. Dahili mikrofon portunun ses seviyesini ayarlamanız veya mikrofonun kazancını ayarlamanız gerekiyorsa, `alsamixer` yardımcı programını kullanabilirsiniz. Bu yardımcı program hakkında daha fazla bilgi için [Linux alsamixer man sayfasını](https://linux.die.net/man/1/alsamixer) okuyabilirsiniz.

1. Eğer sesi oynatırken hata alıyorsanız, `alsa.conf` dosyasındaki `defaults.pcm.card` olarak ayarladığınız kartı kontrol edin.

---

**Feragatname**:  
Bu belge, AI çeviri hizmeti [Co-op Translator](https://github.com/Azure/co-op-translator) kullanılarak çevrilmiştir. Doğruluk için çaba göstersek de, otomatik çevirilerin hata veya yanlışlıklar içerebileceğini lütfen unutmayın. Belgenin orijinal dilindeki hali, yetkili kaynak olarak kabul edilmelidir. Kritik bilgiler için profesyonel insan çevirisi önerilir. Bu çevirinin kullanımından kaynaklanan yanlış anlamalar veya yanlış yorumlamalar için sorumluluk kabul etmiyoruz.