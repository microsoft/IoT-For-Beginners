<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "9713e21a309662f6fcb271b573d47848",
  "translation_date": "2026-01-06T04:01:16+00:00",
  "source_file": "TROUBLESHOOTING.md",
  "language_code": "tr"
}
-->
# Sorun Giderme Kılavuzu

Bu kılavuz, IoT for Beginners müfredatı üzerinde çalışırken karşılaşılan yaygın sorunları çözmenize yardımcı olur. Sorunlar, kolay gezinme için kategori bazında düzenlenmiştir.

## İçindekiler

- [Kurulum Sorunları](../..)
  - [Python Kurulumu](../..)
  - [VS Code ve Uzantılar](../..)
  - [PlatformIO (Wio Terminal)](../..)
  - [Grove Kütüphaneleri](../..)
- [Donanım Sorunları](../..)
  - [Raspberry Pi](../..)
  - [Wio Terminal](../..)
  - [Sanal Cihaz (CounterFit)](../..)
- [Bağlantı Sorunları](../..)
  - [WiFi Bağlantısı](../..)
  - [Bulut Servisleri](../..)
  - [MQTT](../..)
- [Sensör ve Aktüatör Sorunları](../..)
  - [Grove Sensörleri](../..)
  - [Kamera](../..)
  - [Mikrofon ve Hoparlör](../..)
- [Geliştirme Ortamı Sorunları](../..)
  - [VS Code](../..)
  - [Python Sanal Ortamları](../..)
  - [Bağımlılıklar](../..)
- [Performans Sorunları](../..)
- [Yaygın Hata Mesajları](../..)
- [Yardım Alma](../..)

---

## Kurulum Sorunları

### Python Kurulumu

#### Sorun: Python sürümü çok eski
**Hata:** `Python 3.6 veya üzeri gereklidir`

**Çözüm:**
1. En son Python 3 sürümünü [python.org](https://www.python.org/downloads/) adresinden indirin
2. Windows'ta kurulum sırasında "Add Python to PATH" seçeneğini işaretleyin
3. Kurulumu doğrulayın:
   ```bash
   python3 --version
   ```

#### Sorun: Birden fazla Python sürümü çatışmaya yol açıyor
**Belirtiler:** Yanlış Python sürümü çalışıyor, paketler yanlış konuma kuruluyor

**Çözüm:**
- **Windows:** Python 3'ü açıkça çağırmak için `python` yerine `py -3` kullanın
- **macOS/Linux:** `python` yerine `python3` kullanın
- Projeler için her zaman sanal ortamlar oluşturun ve kullanın

#### Sorun: pip komutu bulunamadı
**Hata:** `'pip' iç veya dış komut olarak tanınmıyor`

**Çözüm:**
1. `pip` yerine `pip3` deneyin
2. Ya da `python -m pip` ya da `python3 -m pip` kullanın
3. Python'un PATH'e eklendiğinden emin olun (Python'u yeniden yükleyip seçeneği işaretleyin)

### VS Code ve Uzantılar

#### Sorun: Pylance uzantısı çalışmıyor
**Belirtiler:** Python IntelliSense, kod tamamlama veya tür denetimi yok

**Çözüm:**
1. VS Code Komut Paletini açın (`Ctrl+Shift+P` veya `Cmd+Shift+P`)
2. "Python: Select Interpreter" komutunu çalıştırın
3. Doğru Python yorumlayıcısını seçin (sanal ortam kullanıyorsanız onu)
4. VS Code penceresini yeniden yükleyin

#### Sorun: VS Code sanal ortamı algılamıyor
**Belirtiler:** Yanlış Python yorumlayıcısı seçilmiş

**Çözüm:**
1. Sanal ortamın terminalde etkinleştirildiğinden emin olun
2. Komut Paletini açın ve "Python: Select Interpreter" komutunu çalıştırın
3. `.venv` klasöründeki yorumlayıcıyı seçin
4. Durum çubuğunda (sol alt) doğru Python sürümünün gösterildiğini kontrol edin

### PlatformIO (Wio Terminal)

#### Sorun: PlatformIO kurulumu başarısız
**Hata:** PlatformIO kurulumu sırasında çeşitli hatalar

**Çözüm:**
1. VS Code'un güncel olduğundan emin olun
2. Önce C/C++ uzantısını yükleyin
3. PlatformIO'yu yükledikten sonra VS Code'u yeniden başlatın
4. İnternet bağlantınızı kontrol edin (PlatformIO büyük dosyalar indirir)

#### Sorun: Board PlatformIO tarafından algılanmıyor
**Belirtiler:** Wio Terminal'a kod yüklenemiyor

**Çözüm:**
1. Farklı USB kablo deneyin (bazı kablolar sadece şarj için)
2. Aygıt Yöneticisi'ni (Windows) veya `ls /dev/tty*` (macOS/Linux) kontrol edin
3. USB sürücülerini yükleyin veya güncelleyin
4. Farklı USB portu deneyin
5. Wio Terminal'da güç anahtarını hızlıca iki kez kaydırarak bootloader moduna girin

#### Sorun: PlatformIO derleme hataları
**Hata:** `fatal error: Arduino.h: No such file or directory`

**Çözüm:**
1. Projelerdeki `.pio` klasörünü silin
2. Komut Paletinde "PlatformIO: Rebuild" çalıştırın
3. `platformio.ini` dosyasının doğru board yapılandırmasına sahip olduğundan emin olun:
   ```ini
   [env:seeed_wio_terminal]
   platform = atmelsam
   board = seeed_wio_terminal
   framework = arduino
   ```

### Grove Kütüphaneleri

#### Sorun: Raspberry Pi'de Grove kütüphanesi import hatası
**Hata:** `ModuleNotFoundError: No module named 'grove'`

**Çözüm:**
1. Grove kütüphanelerini yeniden yükleyin:
   ```bash
   cd ~
   git clone https://github.com/Seeed-Studio/grove.py
   cd grove.py
   sudo pip3 install .
   ```
2. Sanal ortam kullanıyorsanız, kütüphaneleri global olarak yüklemeniz veya kopyalamanız gerekebilir
3. I2C'nin etkin olduğundan emin olun: `sudo raspi-config nonint do_i2c 0`

#### Sorun: Grove sensör algılanmıyor
**Hata:** `IOError: [Errno 121] Remote I/O error`

**Çözüm:**
1. Fiziksel bağlantıları kontrol edin (Grove kablosunun tam takılı olduğundan emin olun)
2. Sensörün doğru porta (analog, dijital, I2C, UART) bağlı olduğundan emin olun
3. Cihazın I2C bus'ta görünüp görünmediğine bakmak için `i2cdetect -y 1` çalıştırın
4. Farklı bir Grove kablosu deneyin
5. Grove Base Hat'in Raspberry Pi GPIO pinlerine düzgün oturduğundan emin olun

---

## Donanım Sorunları

### Raspberry Pi

#### Sorun: Raspberry Pi açılmıyor
**Belirtiler:** Ekran yok, LED etkinliği yok veya gökkuşağı ekranı

**Çözüm:**
1. **Güç kaynağını kontrol edin:** Pi 4 için resmi 5V 3A USB-C güç kaynağı kullanın
2. **SD kart sorunları:** 
   - SD kartı yeniden formatlayıp Raspberry Pi OS’u yeniden yükleyin
   - Farklı bir SD kart deneyin (önerilen markaları kullanın)
   - SD kartın düzgün takılı olduğundan emin olun
3. **HDMI bağlantısını kontrol edin:** Pi 4'te her iki HDMI portunu deneyin, güç kaynağına en yakın olanı kullanın

#### Sorun: Raspberry Pi'ye SSH yapılamıyor
**Belirtiler:** Bağlantı reddedildi veya zaman aşımı

**Çözüm:**
1. SSH'yi etkinleştirin:
   - Raspberry Pi Imager ile SD kartı yazarken gelişmiş seçeneklerden SSH’yi etkinleştirin
   - Ya da boot bölümüne uzantısız `ssh` adlı boş dosya oluşturun
2. Pi’nin IP adresini bulun:
   - Router'ın bağlı cihazlar listesine bakın
   - `ping raspberrypi.local` kullanın (mDNS çalışıyorsa)
   - `nmap` veya Angry IP Scanner gibi ağ tarama araçları kullanın
3. Ağı kontrol edin:
   - Pi ve bilgisayar aynı ağda olmalı
   - WiFi yerine Ethernet bağlantısını deneyin
4. Kullanıcı adı/şifreyi doğrulayın (varsayılan: kullanıcı `pi`, şifre `raspberry`)

#### Sorun: Grove Base Hat algılanmıyor
**Belirtiler:** Sensörler çalışmıyor, I2C hataları

**Çözüm:**
1. Base Hat’in tüm GPIO pinlerine tam oturduğundan emin olun
2. Pi veya Base Hat’ta eğilmiş pin olup olmadığını kontrol edin
3. I2C arayüzünü etkinleştirin:
   ```bash
   sudo raspi-config nonint do_i2c 0
   sudo reboot
   ```
4. I2C’nin çalıştığını doğrulayın: `i2cdetect -y 1`

#### Sorun: Raspberry Pi yavaş çalışıyor
**Belirtiler:** Arayüz donuk, yavaş tepki

**Çözüm:**
1. SD kart hızını kontrol edin (Sınıf 10 veya üstü kullanın, ya da USB üzerinden SSD bağlayın)
2. Disk alanını boşaltın: kontrol için `df -h` kullanın, gereksiz dosyaları silin
3. Kamera veya ekran yoğun kullanılmıyorsa `raspi-config` ile GPU belleğini azaltın
4. Gereksiz uygulamaları kapatın
5. Pi 3 veya daha eski modeller kullanıyorsanız, daha fazla RAM’li Pi 4’e yükseltme düşünün

### Wio Terminal

#### Sorun: Wio Terminal ekranı boş kalıyor
**Belirtiler:** Kod yüklendikten sonra görüntü yok

**Çözüm:**
1. Kodunuzun ekranı başlattığından emin olun (TFT_eSPI kütüphanesi gibi)
2. [Seeed Wiki](https://wiki.seeedstudio.com/Wio-Terminal-Getting-Started/) adresinden Wio Terminal firmware güncellemesi yapın
3. Ekran başlatma kodu ekleyin:
   ```cpp
   #include <TFT_eSPI.h>
   TFT_eSPI tft;
   tft.begin();
   tft.fillScreen(TFT_BLACK);
   ```
4. Donanımı test etmek için PlatformIO’dan örnek sketch yüklemeyi deneyin

#### Sorun: Wio Terminal’de WiFi çalışmıyor
**Belirtiler:** WiFi’ye bağlanamama, ağ hataları

**Çözüm:**
1. **WiFi firmware güncelleyin:** [Wio Terminal WiFi firmware update guide](https://wiki.seeedstudio.com/Wio-Terminal-Network-Overview/) takip edin
2. **WiFi bilgilerini kontrol edin:** SSID ve şifrenin doğru olduğundan emin olun
3. **WiFi bandı:** Wio Terminal sadece 2.4GHz WiFi destekler (5GHz değil)
4. **Sinyal gücü:** Router’a yakınlaşın
5. **Router ayarları:** Bazı kurumsal/WPA-Enterprise ağlar çalışmayabilir

#### Sorun: Bilgisayar Wio Terminal’i tanımıyor
**Belirtiler:** USB cihaz tespit edilemiyor

**Çözüm:**
1. **Farklı USB kablo deneyin:** Sadece şarj kablosu değil, veri kablosu kullanın
2. **Bootloader moduna geçin:** Güç anahtarını iki kez hızlıca aşağı kaydırın
   - Mavi LED yanıp sönmeli, Aygıt Yöneticisi’nde "Arduino" olarak görünmeli
3. **Sürücüleri yükleyin (Windows):**
   - [Seeed USB sürücüsünü](https://wiki.seeedstudio.com/Driver_for_Seeeduino/) indirin ve yükleyin
4. **Farklı USB portu deneyin:** USB hub kullanmayın, doğrudan bağlantı yapın
5. **Sistem USB sürücülerini güncelleyin**

#### Sorun: Wio Terminal üzerinde sensörler çalışmıyor
**Belirtiler:** Grove sensörleri veri okumuyor

**Çözüm:**
1. Grove kablo bağlantılarını kontrol edin
2. Doğru Grove portunu kullandığınızdan emin olun (sol veya sağ)
3. Sensör için uygun kütüphaneler dahil edin
4. Sensörün güç ihtiyacını kontrol edin
5. Kütüphaneden örnek kod ile sensörü test edin

### Sanal Cihaz (CounterFit)

#### Sorun: CounterFit uygulaması başlamıyor
**Hata:** CounterFit başlatıldığında çeşitli Python hataları

**Çözüm:**
1. Sanal ortamın etkin olduğundan emin olun
2. CounterFit’i yükleyin/yeniden yükleyin:
   ```bash
   pip install CounterFit
   ```
3. 5000 portunun başka bir uygulama tarafından kullanılmadığını kontrol edin:
   - Windows: `netstat -ano | findstr :5000`
   - macOS/Linux: `lsof -i :5000`
4. 5000 portunu kullanan süreci sonlandırın veya farklı bir port kullanın:
   ```bash
   counterfit --port 5001
   ```

#### Sorun: Koddan CounterFit’e bağlanılamıyor
**Hata:** Bağlantı reddedildi veya zaman aşımı

**Çözüm:**
1. CounterFit’in çalıştığını doğrulayın: Tarayıcıda `http://127.0.0.1:5000` açın
2. Koddaki bağlantı URL’sinin CounterFit adresiyle eşleştiğini kontrol edin
3. Güvenlik duvarının bağlantıyı engellemediğinden emin olun
4. Hem CounterFit uygulamasını hem de kodu yeniden başlatmayı deneyin

#### Sorun: CounterFit içinde sensörler görünmüyor
**Belirtiler:** Oluşturulan sensörler CounterFit arayüzünde listelenmiyor

**Çözüm:**
1. Kod çalışmadan önce CounterFit arayüzünden sensörleri oluşturun
2. Tarayıcı sayfasını yenileyin
3. Sensör tipinin kod ile uyumlu olduğundan emin olun
4. Tarayıcı önbelleğini temizleyin

---

## Bağlantı Sorunları

### WiFi Bağlantısı

#### Sorun: Cihaz WiFi’ye bağlanamıyor
**Belirtiler:** Bağlantı zaman aşımı, kimlik doğrulama hatası

**Çözüm:**
1. **SSID ve şifreyi kontrol edin:** Bilgilerin doğruluğunu teyit edin
2. **WiFi bandı:** Çoğu IoT cihazı sadece 2.4GHz destekler (5GHz değil)
3. **Router ayarları:**
   - AP izolasyonunu kapatın (etkinse)
   - WPA2-PSK güvenliğini kullanın (WPA3, WEP veya açık ağlardan kaçının)
   - DHCP’nin etkin olduğundan emin olun
4. **Gizli ağlar:** SSID gizliyse cihazı manuel olarak yapılandırmanız gerekebilir
5. **Sinyal gücü:** Cihazı router’a yaklaştırın
6. **Parazit:** Diğer cihazlar, mikrodalga fırınlar veya duvarlar parazit yapabilir

#### Sorun: WiFi bağlantısı sık sık kopuyor
**Belirtiler:** Aralıklı bağlantı sorunları

**Çözüm:**
1. Router’ın kararlılığını kontrol edin, gerekirse yeniden başlatın
2. Cihazın firmware’ini güncelleyin
3. DHCP yerine statik IP kullanmayı deneyin
4. Router’a uzaklığı azaltın veya WiFi menzil genişletici kullanın
5. Diğer cihazlardan kaynaklanan paraziti kontrol edin
6. Güç kaynağının yeterli olduğundan emin olun (özellikle Raspberry Pi için)

### Bulut Servisleri

#### Sorun: Azure IoT Hub’a bağlanılamıyor
**Hata:** Kimlik doğrulama başarısız, bağlantı reddedildi

**Çözüm:**
1. **Kimlik bilgilerini doğrulayın:**
   - Bağlantı dizesinin doğru olduğundan emin olun
   - Bağlantı dizesinde ekstra boşluk veya satır sonu olmadığını kontrol edin
2. **Cihaz kaydını kontrol edin:** Cihazın IoT Hub’da kayıtlı olması gerekir
3. **Güvenlik duvarı/proxy:** MQTT (port 8883) veya HTTPS (port 443) çıkışının açık olduğundan emin olun
4. **IoT Hub bölgesi:** Hub’ın çalıştığı bölgenin doğru ve gecikmeye yol açmayan konumda olduğundan emin olun
5. **Kotanın aşılmadığını kontrol edin**
6. Bağlantıyı test edin:
   ```bash
   az iot hub device-identity show-connection-string --hub-name YourIoTHub --device-id YourDevice
   ```

#### Sorun: Azure Functions tetiklenmiyor
**Belirtiler:** Mesajlar gönderiliyor ancak fonksiyon çalışmıyor

**Çözüm:**
1. Function App’in çalışır durumda olduğundan emin olun (durdurulmamış)
2. Function App ayarlarında bağlantı dizesini kontrol edin
3. Azure Portal’da fonksiyon kayıtlarını inceleyin
4. Event Hub uyumlu uç noktanın doğru yapılandırıldığından emin olun
5. Mesaj formatının fonksiyon beklentisiyle uyumlu olduğunu kontrol edin
6. Function App hizmet planını kontrol edin (tüketim vs. adanmış)

### MQTT
#### Problem: MQTT bağlantısı başarısız oluyor  
**Hata:** Bağlantı reddedildi, kimlik doğrulama başarısız

**Çözüm:**  
1. **Broker adresi:** Broker URL/IP adresinin doğru olduğundan emin olun  
2. **Port:** Port numarasını kontrol edin (şifresiz için 1883, TLS için 8883)  
3. **Kimlik doğrulama:** Gerekliyse kullanıcı adı/şifresini doğrulayın  
4. **TLS/SSL:** Sertifikaların geçerli ve güvenilir olduğundan emin olun  
5. **Güvenlik duvarı:** Portun engellenmediğini kontrol edin  
6. **MQTT istemcisi ile test:** MQTT Explorer veya mosquitto_pub/sub kullanarak test edin

#### Problem: MQTT mesajları alınmıyor  
**Belirtiler:** Mesajlar yayınlanıyor ancak aboneler almıyor

**Çözüm:**  
1. **Konu adları:** Abone konusu yayıncı konusuyla tam eşleşmeli  
2. **QoS seviyesi:** 0 yerine QoS 1 veya 2 deneyin  
3. **Joker karakterler:** Konu joker karakterlerinin doğru kullanıldığını kontrol edin (`+` tek seviye, `#` çok seviye için)  
4. **Saklanan mesajlar:** Yayıncı sakla bayrağını kullanabilir  
5. **Bağlantı zamanlaması:** Abonenin mesajlar yayınlanmadan önce bağlandığından emin olun

---

## Sensör ve Aktüatör Sorunları

### Grove Sensörler

#### Problem: Sensör yanlış değerler döndürüyor  
**Belirtiler:** Okumalar 0, -1 veya anlamsız değerler

**Çözüm:**  
1. **Bağlantıları kontrol edin:** Sensörün düzgün bağlandığından emin olun  
2. **Doğru port:** Sensörün doğru port tipinde olduğundan emin olun:  
   - Analog sensörler → Analog portlar (A0, A2, A4)  
   - Dijital sensörler → Dijital portlar (D5, D16, D18 vb.)  
   - I2C sensörler → I2C portlar  
3. **Kalibrasyon:** Bazı sensörler kalibrasyon gerektirir (toprak nemi, ışık)  
4. **Güç döngüsü:** Sensörü çıkarıp tekrar takın  
5. **Sensör veri sayfası:** Sensörün özelliklerini ve gereksinimlerini kontrol edin

#### Problem: Kapasitif toprak nem sensörü her zaman ıslak okuyor  
**Belirtiler:** Sensör kuru iken bile yüksek nem okuyor

**Çözüm:**  
1. **Kalibrasyon gerekli:** Toprak sensörleri kalibrasyon ister:  
   - Havadaki değeri oku (kuru referans)  
   - Suda değer oku (ıslak referans)  
   - Okumaları bu değerler arasında haritalandır  
2. **Sensör kaplamasını kontrol et:** Nem sensörlerinin kaplaması zarar görürse bozulabilir  
3. **Yerleştirme:** Sensörün tamamen toprak içine girdiğinden emin olun

#### Problem: Sıcaklık/nem sensörü yanlış değerler gösteriyor  
**Belirtiler:** DHT11/DHT22 yanlış sıcaklık veya nem gösteriyor

**Çözüm:**  
1. **Sensör yerleşimi:** Doğrudan güneş ışığı, ısı kaynakları veya hava akımından kaçının  
2. **Isınma süresi:** Sensöre güç verildikten sonra 2 saniye bekleyin  
3. **Okuma sıklığı:** DHT sensörleri arasında en az 2 saniye olmalı  
4. **Yoğuşmayı kontrol et:** Yoğuşma okumaları etkileyebilir  
5. **Sensör kalitesi:** DHT11, DHT22’den daha az hassastır

### Kamera

#### Problem: Raspberry Pi’de kamera algılanmıyor  
**Hata:** `mmal: mmal_vc_component_create: failed to create component 'vc.ril.camera'`

**Çözüm:**  
1. **Kamera arayüzünü etkinleştirin:**  
   ```bash
   sudo raspi-config
   ```
   Arayüz Seçenekleri → Kamera → Etkinleştir  
2. **Şerit kablosunu kontrol edin:** Kamera kablosunun düzgün takıldığından emin olun  
   - Pi Zero’da mavi yüzey USB portlarına bakar  
   - Pi 4’te mavi yüzey USB portlarının tersine bakar  
3. **Firmware güncelleyin:**  
   ```bash
   sudo apt update
   sudo apt full-upgrade
   sudo reboot
   ```
4. **Kamerayı test edin:**  
   ```bash
   raspistill -o test.jpg
   ```
  
#### Problem: Kamera görüntüleri düşük kalite  
**Belirtiler:** Bulanık, karanlık veya soluk görüntüler

**Çözüm:**  
1. **Odak:** Lensin koruyucu filmini çıkarın, ayarlanabiliyorsa odağı ayarlayın  
2. **Aydınlatma:** Yeterli ışık olduğundan emin olun  
3. **Kamera ayarları:** Kodda pozlama, ISO, beyaz dengesi ayarlarını yapın  
4. **Stabilite:** Kamerayı sabit tutun, gerekirse tripot kullanın  
5. **Çözünürlük:** Kameranın maksimum çözünürlüğünü aşmayın

### Mikrofon ve Hoparlör

#### Problem: Ses giriş/çıkışı yok  
**Belirtiler:** Mikrofon kayıt yapmıyor, hoparlör ses vermiyor

**Çözüm:**  
1. **Bağlantıları kontrol edin:** Ses cihazlarının doğru bağlandığını doğrulayın  
2. **Donanımı test edin:**  
   - Hoparlör: `speaker-test -t wav -c 2`  
   - Mikrofon: `arecord -l` listeleme, `arecord test.wav` kayıt  
3. **Ses düzeyi ayarları:** Kontrol edin ve ayarlayın:  
   ```bash
   alsamixer
   ```
4. **Ses cihazını seçin:** Kodda doğru cihazı belirtin  
5. **Sürücü sorunları:** ALSA güncelleyin veya ses sürücülerini yeniden yükleyin

#### Problem: ReSpeaker hat çalışmıyor  
**Belirtiler:** Ses cihazı algılanmıyor

**Çözüm:**  
1. **Sürücüleri kurun:**  
   ```bash
   git clone https://github.com/HinTak/seeed-voicecard
   cd seeed-voicecard
   sudo ./install.sh
   sudo reboot
   ```
2. **Kurulumu kontrol edin:** `arecord -l` ReSpeaker’ı listeli  
3. **Firmware güncellemesi:** Bazı Pi OS sürümleri sürücü güncellemesi ister  
4. **Yerleşimi kontrol edin:** Hattın GPIO pinlerine tam oturduğundan emin olun

---

## Geliştirme Ortamı Sorunları

### VS Code

#### Problem: Terminal sanal ortamı otomatik etkinleştirmiyor  
**Belirtiler:** Terminal açılıyor ama venv etkin değil

**Çözüm:**  
1. **Python yorumlayıcısını ayarlayın:** Komut Paleti → "Python: Select Interpreter" → venv seçin  
2. **VS Code’u yeniden başlatın** yorumlayıcı seçtikten sonra  
3. **Ayarları kontrol edin:** `settings.json` içine şu satırı ekleyin:  
   ```json
   "python.terminal.activateEnvironment": true
   ```
  
#### Problem: Cihazda kod çalışmıyor  
**Belirtiler:** Kod çalışıyor ama cihazda hiçbir şey olmuyor

**Çözüm:**  
1. **Kodun kaydedildiğini doğrulayın** (dosya sekmesinde nokta kontrolü)  
2. **Hangi Python’un çalıştığını kontrol edin:** `which python` veya `where python`  
3. **Wio Terminal için:** Kodun PlatformIO ile yüklendiğinden emin olun (yükle butonu)  
4. **Raspberry Pi için:** Pi’ya SSH ile bağlanarak orada çalıştırın  
5. **Çıkış penceresini kontrol edin** hata için

#### Problem: IntelliSense kütüphane fonksiyonlarını göstermiyor  
**Belirtiler:** İçe aktarılan modüllerde otomatik tamamlama yok

**Çözüm:**  
1. Kütüphanenin mevcut ortamda yüklü olduğundan emin olun  
2. VS Code penceresini yeniden yükleyin  
3. Python yorumlayıcısının doğru olduğunu kontrol edin  
4. Tür tanımları varsa yükleyin: `pip install types-<kütüphane-ismi>`

### Python Sanal Ortamlar

#### Problem: Sanal ortam oluşturulamıyor  
**Hata:** `The virtual environment was not created successfully`

**Çözüm:**  
1. **venv modülünü kurun:**  
   - Ubuntu/Debian: `sudo apt install python3-venv`  
   - macOS: Python ile birlikte gelir  
   - Windows: Python’u tüm bileşenlerle yeniden yükleyin  
2. **Python kurulumunu kontrol edin:** Python’un doğru yüklendiğinden emin olun  
3. **Tam yol kullanın:** `python3 -m venv .venv` diye explicit python3 çağırın

#### Problem: Paketler yanlış yere kuruluyor  
**Belirtiler:** Paket kurulumundan sonra import hatası alınıyor

**Çözüm:**  
1. **venv’nin etkin olduğu doğrula:** Komut isteminde `(.venv)` görünüyor olmalı  
2. **pip konumunu kontrol et:** `which pip` `.venv/bin/pip` olmalı  
3. **venv içinde yeniden yükle:** venv’yi aktif edin sonra `pip install <paket>`  
4. Sanal ortamda pip’i sudo ile kullanmayın

#### Problem: Sanal ortam taşınabilir değil  
**Belirtiler:** venv taşındıktan sonra veya başka bilgisayarda çalışmıyor

**Çözüm:**  
1. **venv’leri taşımayın:** Yeni yerde silip baştan oluşturun  
2. **requirements.txt kullanın:**  
   ```bash
   pip freeze > requirements.txt
   pip install -r requirements.txt
   ```
3. **venv’yi yeniden oluştur:**  
   ```bash
   python3 -m venv .venv
   source .venv/bin/activate  # veya Windows'ta activate.bat
   pip install -r requirements.txt
   ```
  
### Bağımlılıklar

#### Problem: Paket kurulumu başarısız  
**Hata:** Kurulum sırasında çeşitli pip hataları

**Çözüm:**  
1. **pip’i güncelleyin:**  
   ```bash
   pip install --upgrade pip
   ```
2. **Derleme araçlarını yükleyin:**  
   - Ubuntu/Debian: `sudo apt install build-essential python3-dev`  
   - macOS: `xcode-select --install`  
   - Windows: Visual Studio Build Tools’u kurun  
3. İnternet bağlantısını kontrol edin  
4. Farklı paket indeksi deneyin: `pip install --index-url https://pypi.org/simple/ <paket>`  
5. Belirli sürümü yükleyin: `pip install <paket>==<versiyon>`

#### Problem: Bağımlılık çakışmaları  
**Hata:** `ERROR: pip's dependency resolver does not currently take into account all the packages that are installed`

**Çözüm:**  
1. Her proje için temiz sanal ortam kullanın  
2. Paketleri güncelleyin: `pip install --upgrade <paket>`  
3. Gereksinimleri kontrol edin: `pip check` ile çakışma bulun  
4. Uyumlu sürümleri yükleyin: requirements.txt de sürüm aralıkları belirtin

---

## Performans Sorunları

### Problem: Kod yavaş çalışıyor  
**Belirtiler:** Gecikmeler, zaman aşımı, tepkisizlik

**Çözüm:**  
1. Sensör okuma sıklığını azaltın  
2. Döngüleri optimize edin: yoğun bekleme yapmayın, sleep() veya gecikme kullanın  
3. Bellek sorunları:  
   - Gereksiz uygulamaları kapatın  
   - Depolama alanı boşaltın  
   - Pi üzerinde `top` veya `htop` ile izleyin  
4. SD kart hızı: Raspberry Pi için daha hızlı SD kart veya SSD kullanın  
5. Ağ gecikmeleri: Ağ çağrıları için asenkron işlemler kullanın

### Problem: Bellek yetersizliği hataları  
**Hata:** `MemoryError` veya sistemin donması

**Çözüm:**  
1. Raspberry Pi için:  
   - Gereksiz uygulamaları kapatın  
   - Swap alanını artırın  
   - Hafif OS (Lite sürümü) kullanın  
   - RAM yükseltin (Pi 4 için 2/4/8GB seçenekleri var)  
2. Wio Terminal için:  
   - Tampon boyutlarını küçültün  
   - Daha küçük resimler kullanın  
   - String kullanımını optimize edin  
   - Bellek sızıntısı yok mu kontrol edin (serbest bırakılmamış bellek)

### Problem: Veri kaybı veya bozulması  
**Belirtiler:** Eksik mesajlar, bozuk dosyalar

**Çözüm:**  
1. SD kart sorunları:  
   - Kaliteli SD kart kullanın (ucuz/sahte kartlardan kaçının)  
   - Düzenli yedek alın  
   - Temiz kapanış yapın (gücü çekmeyin)  
2. Tampon taşması: Kodda tampon boyutlarını artırın  
3. Ağ güvenilirliği: Tekrar deneme ve hata yönetimi uygulayın  
4. Hizmet Kalitesi: Önemli mesajlar için MQTT QoS 1 veya 2 kullanın

---

## Yaygın Hata Mesajları

### `ModuleNotFoundError: No module named 'X'`  
**Neden:** Paket yüklü değil veya sanal ortam etkin değil

**Çözüm:**  
```bash
pip install X
```
Öncelikle sanal ortamın etkin olduğundan emin olun.

### `Permission denied` Linux/macOS’ta  
**Neden:** Yükseltilmiş izinler gerekli veya dosya izin sorunu

**Çözüm:**  
- Sistem işlemleri için: `sudo` kullanın  
- pip için: venv etkinleştirin, sudo kullanmayın  
- Seri port için: Kullanıcıyı dialout grubuna ekleyin: `sudo usermod -a -G dialout $USER`, sonra çıkış yapıp yeniden giriş yapın

### `OSError: [Errno 98] Address already in use`  
**Neden:** Port başka bir işlem tarafından kullanılıyor

**Çözüm:**  
1. Portu kullanan işlemi bulun: `lsof -i :<port>` veya `netstat -ano | findstr :<port>`  
2. İşlemi sonlandırın veya kodda farklı port kullanın

### `SSL: CERTIFICATE_VERIFY_FAILED`  
**Neden:** SSL sertifikası doğrulaması başarısız

**Çözüm:**  
1. Sertifikaları güncelleyin: `pip install --upgrade certifi`  
2. Sistem saatini kontrol edin: `date`  
3. Sadece geliştirme için (üretimde değil): Kodda doğrulamayı devre dışı bırakın

### `IndentationError: unexpected indent`  
**Neden:** Python girinti problemleri (sekme ve boşluk karışımı)

**Çözüm:**  
1. Tutarlı girinti kullanın (Python standardı 4 boşluk)  
2. Editörü sekme yerine boşluk kullanacak şekilde ayarlayın  
3. VS Code’da `"editor.insertSpaces": true` ve `"editor.tabSize": 4` ayarlarını yapın

### `UnicodeDecodeError` veya `UnicodeEncodeError`  
**Neden:** Karakter kodlaması sorunları

**Çözüm:**  
```python
# Dosya okunurken
with open('file.txt', 'r', encoding='utf-8') as f:
    content = f.read()

# Dosya yazılırken
with open('file.txt', 'w', encoding='utf-8') as f:
    f.write(content)
```
  
---

## Yardım Alma

Bu sorun giderme adımlarını denediniz ama hala sorun yaşıyorsanız:

### 1. Mevcut Kaynakları Kontrol Edin  
- **Dokümantasyon:** [README](README.md) ve ders talimatlarını inceleyin  
- **Donanım rehberleri:** [hardware.md](hardware.md) dosyasına bakın  
- **Seeed Studio Wiki:** Grove bileşenler için [Seeed Studio Wiki](https://wiki.seeedstudio.com/)

### 2. Benzer Sorunları Araştırın  
- **GitHub Sorunları:** [mevcut sorunları](https://github.com/microsoft/IoT-For-Beginners/issues) arayın  
- **Stack Overflow:** Hata mesajlarını arayın  
- **Cihaz forumları:** Raspberry Pi veya Arduino forumlarını kontrol edin

### 3. GitHub Sorunu Oluşturun  
Çözüm bulamazsanız:  
1. [GitHub Issues](https://github.com/microsoft/IoT-For-Beginners/issues) sayfasına gidin  
2. "New Issue" tıklayın  
3. Şu bilgileri sağlayın:  
   - Problemin açık açıklaması  
   - Tekrarlanma adımları  
   - Hata mesajları (tam metin)  
   - Donanım/yazılım sürümleri  
   - Zaten denedikleriniz  
   - İlgili ekran görüntüleri

### 4. Topluluğa Katılın  
- **Discord:** [Microsoft Foundry Discord](https://discord.gg/nTYy5BXMWG)  
- **Microsoft Learn:** [Microsoft Learn IoT](https://docs.microsoft.com/learn/browse/?products=azure-iot)

### 5. İyi Hata Raporları Sağlayın  
İyi bir hata raporu şunları içerir:
- **Ortam:** İşletim sistemi, Python sürümü, kullanılan donanım
- **Çoğaltma adımları:** Soruna yol açan tam adımlar
- **Beklenen davranış:** Ne olması bekleniyor
- **Gerçek davranış:** Gerçekte olan şey
- **Hata mesajları:** Ekran görüntüsü değil, tam hata metni
- **Kod:** Sorunu çoğaltan minimal kod örneği

---

## Önleme İpuçları

### Genel En İyi Uygulamalar
1. **Yedek tutun:** Çalışan SD kartların/kodların düzenli yedekleri
2. **Değişiklikleri belgeleyin:** Ne işe yaradığını yorumlarla not alın
3. **Sürüm kontrolü:** Kod değişikliklerini izlemek için git kullanın
4. **Parça parça test edin:** Küçük değişiklikleri birleştirmeden test edin
5. **Hata mesajlarını okuyun:** Çoğunlukla tam olarak neyin yanlış olduğunu söylerler
6. **Düzenli güncelleme:** Yazılım/firmware güncel tutun
7. **Kaliteli bileşenler kullanın:** Ucuz kablo/güç kaynaklarından kaçının
8. **Kararlı güç kaynağı:** Uygun güç kaynağı kullanın (özellikle Pi için)

### Geliştirme İş Akışı
1. **Basit başlayın:** Çalışan örnek kodla başlayın
2. **Bir seferde bir değişiklik:** Neyin bozulduğunu bulmak daha kolaydır
3. **Sık test edin:** Sorunları erken yakalayın
4. **Düzenli tutun:** Dosyaları ve kodu mantıklı şekilde organize edin
5. **Kodu yorumlayın:** Gelecekte kendiniz bunu takdir edeceksiniz

---

*Bu sorun giderme kılavuzu topluluk tarafından sürdürülebilmektedir. Burada listelenmeyen bir soruna çözüm bulursanız, başkalarına yardımcı olmak için [katkıda bulunmayı](CONTRIBUTING.md) düşünebilirsiniz!*

---

<!-- CO-OP TRANSLATOR DISCLAIMER START -->
**Feragatname**:  
Bu belge, yapay zeka çeviri hizmeti [Co-op Translator](https://github.com/Azure/co-op-translator) kullanılarak çevrilmiştir. Doğruluk için çaba göstersek de, otomatik çevirilerin hatalar veya yanlışlıklar içerebileceğini lütfen unutmayın. Orijinal belge, kendi ana dilinde yetkili kaynak olarak kabul edilmelidir. Kritik bilgiler için profesyonel insan çevirisi önerilir. Bu çevirinin kullanımı sonucunda ortaya çıkabilecek yanlış anlamalar veya yorumlamalar için sorumluluk kabul edilmemektedir.
<!-- CO-OP TRANSLATOR DISCLAIMER END -->