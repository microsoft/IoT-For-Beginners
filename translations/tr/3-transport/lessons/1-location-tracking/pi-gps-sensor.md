# GPS Verilerini Okuma - Raspberry Pi

Bu dersin bu bölümünde, Raspberry Pi'ye bir GPS sensörü ekleyecek ve ondan veri okuyacaksınız.

## Donanım

Raspberry Pi'nin bir GPS sensörüne ihtiyacı var.

Kullanacağınız sensör, [Grove GPS Air530 sensörü](https://www.seeedstudio.com/Grove-GPS-Air530-p-4584.html). Bu sensör, hızlı ve doğru bir konum belirlemek için birden fazla GPS sistemine bağlanabilir. Sensör iki parçadan oluşur - sensörün temel elektronik bileşenleri ve uydulardan gelen radyo dalgalarını almak için ince bir kabloyla bağlanan harici bir anten.

Bu bir UART sensörüdür, bu nedenle GPS verilerini UART üzerinden gönderir.

## GPS Sensörünü Bağlama

Grove GPS sensörü Raspberry Pi'ye bağlanabilir.

### Görev - GPS sensörünü bağlayın

GPS sensörünü bağlayın.

![Bir Grove GPS sensörü](../../../../../translated_images/tr/grove-gps-sensor.247943bf69b03f0d.webp)

1. Grove kablosunun bir ucunu GPS sensöründeki sokete takın. Kablo yalnızca tek bir yönde takılabilir.

1. Raspberry Pi kapalıyken, Grove kablosunun diğer ucunu Pi'ye bağlı Grove Base hat üzerindeki **UART** olarak işaretlenmiş UART soketine bağlayın. Bu soket, SD Kart yuvasına en yakın olan tarafta, orta sıradadır ve USB portları ile ethernet soketinin diğer ucundadır.

    ![Grove GPS sensörü UART soketine bağlı](../../../../../translated_images/tr/pi-gps-sensor.1f99ee2b2f652891.webp)

1. GPS sensörünü, bağlı antenin gökyüzüne görünürlüğü olacak şekilde konumlandırın - ideal olarak açık bir pencerenin yanında veya dışarıda. Antenin önünde hiçbir şey olmadan daha net bir sinyal almak daha kolaydır.

## GPS Sensörünü Programlama

Artık Raspberry Pi, bağlı GPS sensörünü kullanacak şekilde programlanabilir.

### Görev - GPS sensörünü programlayın

Cihazı programlayın.

1. Pi'yi açın ve başlatılmasını bekleyin.

1. GPS sensöründe 2 LED bulunur - veri iletildiğinde yanıp sönen mavi bir LED ve uydulardan veri alındığında her saniye yanıp sönen yeşil bir LED. Pi'yi açtığınızda mavi LED'in yanıp söndüğünden emin olun. Birkaç dakika sonra yeşil LED yanıp sönecektir - eğer yanıp sönmezse, anteni yeniden konumlandırmanız gerekebilir.

1. VS Code'u başlatın, ya doğrudan Pi üzerinde ya da Remote SSH uzantısı aracılığıyla bağlanarak.

    > ⚠️ Gerekirse [1. dersteki VS Code'u kurma ve başlatma talimatlarına](../../../1-getting-started/lessons/1-introduction-to-iot/pi.md) başvurabilirsiniz.

1. Bluetooth'u destekleyen daha yeni Raspberry Pi sürümlerinde, Bluetooth için kullanılan seri port ile Grove UART portu için kullanılan seri port arasında bir çakışma vardır. Bunu düzeltmek için şu adımları izleyin:

    1. VS Code terminalinden, `nano` adlı yerleşik bir terminal metin düzenleyicisini kullanarak `/boot/config.txt` dosyasını şu komutla düzenleyin:

        ```sh
        sudo nano /boot/config.txt
        ```

        > Bu dosya, `sudo` yetkileriyle düzenlenmesi gerektiğinden VS Code tarafından düzenlenemez. VS Code bu yetkilerle çalışmaz.

    1. İmleç tuşlarını kullanarak dosyanın sonuna gidin, ardından aşağıdaki kodu kopyalayıp dosyanın sonuna yapıştırın:

        ```ini
        dtoverlay=pi3-miniuart-bt
        dtoverlay=pi3-disable-bt
        enable_uart=1
        ```

        Normal klavye kısayollarını kullanarak yapıştırabilirsiniz (`Windows, Linux veya Raspberry Pi OS'de Ctrl+v`, macOS'ta `Cmd+v`).

    1. Bu dosyayı kaydedin ve `Ctrl+x` tuşlarına basarak nano'dan çıkın. Değiştirilen tamponu kaydetmek isteyip istemediğiniz sorulduğunda `y` tuşuna basın, ardından `/boot/config.txt` dosyasını üzerine yazmayı onaylamak için `enter` tuşuna basın.

        > Bir hata yaparsanız, kaydetmeden çıkabilir ve bu adımları tekrar edebilirsiniz.

    1. `nano` ile `/boot/cmdline.txt` dosyasını şu komutla düzenleyin:

        ```sh
        sudo nano /boot/cmdline.txt
        ```

    1. Bu dosyada boşluklarla ayrılmış bir dizi anahtar/değer çifti bulunur. `console` anahtarı için olan tüm anahtar/değer çiftlerini kaldırın. Bunlar muhtemelen şu şekilde görünecektir:

        ```output
        console=serial0,115200 console=tty1 
        ```

        İmleç tuşlarını kullanarak bu girişlere gidin, ardından normal `del` veya `backspace` tuşlarını kullanarak silin.

        Örneğin, orijinal dosyanız şu şekilde görünüyorsa:

        ```output
        console=serial0,115200 console=tty1 root=PARTUUID=058e2867-02 rootfstype=ext4 elevator=deadline fsck.repair=yes rootwait
        ```

        Yeni sürüm şu şekilde olacaktır:

        ```output
        root=PARTUUID=058e2867-02 rootfstype=ext4 elevator=deadline fsck.repair=yes rootwait
        ```

    1. Yukarıdaki adımları izleyerek bu dosyayı kaydedin ve nano'dan çıkın.

    1. Pi'yi yeniden başlatın, ardından Pi yeniden başlatıldıktan sonra VS Code'a yeniden bağlanın.

1. Terminalden, `pi` kullanıcısının ana dizininde `gps-sensor` adlı yeni bir klasör oluşturun. Bu klasörde `app.py` adlı bir dosya oluşturun.

1. Bu klasörü VS Code'da açın.

1. GPS modülü, seri port üzerinden UART verileri gönderir. Python kodunuzdan seri portla iletişim kurmak için `pyserial` Pip paketini yükleyin:

    ```sh
    pip3 install pyserial
    ```

1. `app.py` dosyanıza aşağıdaki kodu ekleyin:

    ```python
    import time
    import serial
    
    serial = serial.Serial('/dev/ttyAMA0', 9600, timeout=1)
    serial.reset_input_buffer()
    serial.flush()
    
    def print_gps_data(line):
        print(line.rstrip())
    
    while True:
        line = serial.readline().decode('utf-8')
    
        while len(line) > 0:
            print_gps_data(line)
            line = serial.readline().decode('utf-8')
    
        time.sleep(1)
    ```

    Bu kod, `pyserial` Pip paketinden `serial` modülünü içe aktarır. Ardından, Grove Pi Base Hat'in UART portu için kullanılan `/dev/ttyAMA0` seri portuna bağlanır. Bu seri bağlantıdaki mevcut verileri temizler.

    Daha sonra, kendisine iletilen satırı konsola yazdıran `print_gps_data` adlı bir fonksiyon tanımlanır.

    Ardından kod, her döngüde seri porttan mümkün olduğunca çok sayıda metin satırı okuyarak sonsuza kadar döner. Her satır için `print_gps_data` fonksiyonunu çağırır.

    Tüm veriler okunduktan sonra, döngü 1 saniye uyur ve ardından tekrar dener.

1. Bu kodu çalıştırın. GPS sensöründen gelen ham çıktıyı göreceksiniz, örneğin şu şekilde:

    ```output
    $GNGGA,020604.001,4738.538654,N,12208.341758,W,1,3,,164.7,M,-17.1,M,,*67
    $GPGSA,A,1,,,,,,,,,,,,,,,*1E
    $BDGSA,A,1,,,,,,,,,,,,,,,*0F
    $GPGSV,1,1,00*79
    $BDGSV,1,1,00*68
    ```

    > Kodunuzu durdurup yeniden başlattığınızda aşağıdaki hatalardan birini alırsanız, while döngünüze bir `try - except` bloğu ekleyin.

      ```output
      UnicodeDecodeError: 'utf-8' codec can't decode byte 0x93 in position 0: invalid start byte
      UnicodeDecodeError: 'utf-8' codec can't decode byte 0xf1 in position 0: invalid continuation byte
      ```

    ```python
    while True:
        try:
            line = serial.readline().decode('utf-8')
              
            while len(line) > 0:
                print_gps_data()
                line = serial.readline().decode('utf-8')
      
        # There's a random chance the first byte being read is part way through a character.
        # Read another full line and continue.

        except UnicodeDecodeError:
            line = serial.readline().decode('utf-8')

    time.sleep(1)
    ```

> 💁 Bu kodu [code-gps/pi](../../../../../3-transport/lessons/1-location-tracking/code-gps/pi) klasöründe bulabilirsiniz.

😀 GPS sensörü programınız başarılı oldu!

---

**Feragatname**:  
Bu belge, AI çeviri hizmeti [Co-op Translator](https://github.com/Azure/co-op-translator) kullanılarak çevrilmiştir. Doğruluk için çaba göstersek de, otomatik çevirilerin hata veya yanlışlıklar içerebileceğini lütfen unutmayın. Belgenin orijinal dili, yetkili kaynak olarak kabul edilmelidir. Kritik bilgiler için profesyonel insan çevirisi önerilir. Bu çevirinin kullanımından kaynaklanan yanlış anlamalar veya yanlış yorumlamalar için sorumluluk kabul etmiyoruz.