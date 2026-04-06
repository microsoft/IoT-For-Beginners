# Sprzęt

**T** w IoT oznacza **Things** (Rzeczy) i odnosi się do urządzeń, które wchodzą w interakcję ze światem wokół nas. Każdy projekt opiera się na rzeczywistym sprzęcie dostępnym dla studentów i hobbystów. Mamy dwie opcje sprzętu IoT do wyboru, w zależności od osobistych preferencji, znajomości języków programowania, celów nauki i dostępności. Dla tych, którzy nie mają dostępu do sprzętu lub chcą dowiedzieć się więcej przed zakupem, udostępniliśmy również wersję "wirtualnego sprzętu".

> 💁 Nie musisz kupować żadnego sprzętu IoT, aby ukończyć zadania. Wszystko możesz zrobić, korzystając z wirtualnego sprzętu IoT.

Fizyczne opcje sprzętowe to Arduino lub Raspberry Pi. Każda platforma ma swoje zalety i wady, które omówiono w jednej z początkowych lekcji. Jeśli jeszcze nie zdecydowałeś, którą platformę sprzętową wybrać, możesz zapoznać się z [lekcją drugą pierwszego projektu](./1-getting-started/lessons/2-deeper-dive/README.md), aby dowiedzieć się, która platforma najbardziej Cię interesuje.

Wybrany sprzęt został dobrany tak, aby zminimalizować złożoność lekcji i zadań. Chociaż inne urządzenia mogą działać, nie możemy zagwarantować, że wszystkie zadania będą obsługiwane na Twoim urządzeniu bez dodatkowego sprzętu. Na przykład wiele urządzeń Arduino nie ma WiFi, które jest potrzebne do połączenia z chmurą – wybraliśmy terminal Wio, ponieważ ma wbudowane WiFi.

Będziesz także potrzebować kilku nietechnicznych przedmiotów, takich jak ziemia lub roślina doniczkowa oraz owoce lub warzywa.

## Kup zestawy

![Logo Seeed Studios](../../translated_images/pl/seeed-logo.74732b6b482b6e8e.webp)

Seeed Studios uprzejmie udostępniło cały sprzęt w formie łatwych do zakupu zestawów:

### Arduino - Wio Terminal

**[IoT dla początkujących z Seeed i Microsoft - Zestaw startowy Wio Terminal](https://www.seeedstudio.com/IoT-for-beginners-with-Seeed-and-Microsoft-Wio-Terminal-Starter-Kit-p-5006.html)**

[![Zestaw sprzętowy Wio Terminal](../../translated_images/pl/wio-hardware-kit.4c70c48b85e4283a.webp)](https://www.seeedstudio.com/IoT-for-beginners-with-Seeed-and-Microsoft-Wio-Terminal-Starter-Kit-p-5006.html)

### Raspberry Pi

**[IoT dla początkujących z Seeed i Microsoft - Zestaw startowy Raspberry Pi 4](https://www.seeedstudio.com/IoT-for-beginners-with-Seeed-and-Microsoft-Raspberry-Pi-Starter-Kit-p-5004.html)**

[![Zestaw sprzętowy Raspberry Pi Terminal](../../translated_images/pl/pi-hardware-kit.26dbadaedb7dd44c.webp)](https://www.seeedstudio.com/IoT-for-beginners-with-Seeed-and-Microsoft-Raspberry-Pi-Starter-Kit-p-5004.html)

## Arduino

Cały kod urządzenia dla Arduino jest napisany w C++. Aby ukończyć wszystkie zadania, będziesz potrzebować następujących elementów:

### Sprzęt Arduino

* [Wio Terminal](https://www.seeedstudio.com/Wio-Terminal-p-4509.html)
* *Opcjonalnie* - kabel USB-C lub adapter USB-A do USB-C. Terminal Wio ma port USB-C i jest dostarczany z kablem USB-C do USB-A. Jeśli Twój komputer lub Mac ma tylko porty USB-C, będziesz potrzebować kabla USB-C lub adaptera USB-A do USB-C.

### Specyficzne czujniki i elementy wykonawcze dla Arduino

Te elementy są specyficzne dla urządzenia Arduino Wio Terminal i nie są istotne dla Raspberry Pi.

* [ArduCam Mini 2MP Plus - OV2640](https://www.arducam.com/product/arducam-2mp-spi-camera-b0067-arduino/)
* [ReSpeaker 2-Mics Pi HAT](https://www.seeedstudio.com/ReSpeaker-2-Mics-Pi-HAT.html)
* [Przewody do płytki stykowej](https://www.seeedstudio.com/Breadboard-Jumper-Wire-Pack-241mm-200mm-160mm-117m-p-234.html)
* Słuchawki lub inny głośnik z wtykiem 3,5 mm, lub głośnik JST, taki jak:
  * [Mono Enclosed Speaker - 2W 6 Ohm](https://www.seeedstudio.com/Mono-Enclosed-Speaker-2W-6-Ohm-p-2832.html)
* Karta microSD 16GB lub mniejsza, wraz z adapterem do użycia karty SD z komputerem, jeśli nie masz wbudowanego czytnika. **UWAGA** - Terminal Wio obsługuje tylko karty SD do 16GB, nie obsługuje większych pojemności.

## Raspberry Pi

Cały kod urządzenia dla Raspberry Pi jest napisany w Pythonie. Aby ukończyć wszystkie zadania, będziesz potrzebować następujących elementów:

### Sprzęt Raspberry Pi

* [Raspberry Pi](https://www.raspberrypi.org/products/raspberry-pi-4-model-b/)
  > 💁 Wersje od Pi 2B wzwyż powinny działać z zadaniami w tych lekcjach. Jeśli planujesz uruchamiać VS Code bezpośrednio na Pi, potrzebujesz Pi 4 z co najmniej 2GB RAM. Jeśli zamierzasz uzyskiwać dostęp do Pi zdalnie, każda wersja od Pi 2B wzwyż będzie odpowiednia.
* Karta microSD (możesz kupić zestawy Raspberry Pi, które zawierają kartę microSD), wraz z adapterem do użycia karty SD z komputerem, jeśli nie masz wbudowanego czytnika.
* Zasilacz USB (możesz kupić zestawy Raspberry Pi 4, które zawierają zasilacz). Jeśli używasz Raspberry Pi 4, potrzebujesz zasilacza USB-C, wcześniejsze urządzenia wymagają zasilacza micro-USB.

### Specyficzne czujniki i elementy wykonawcze dla Raspberry Pi

Te elementy są specyficzne dla Raspberry Pi i nie są istotne dla urządzenia Arduino.

* [Grove Pi base hat](https://www.seeedstudio.com/Grove-Base-Hat-for-Raspberry-Pi.html)
* [Moduł kamery Raspberry Pi](https://www.raspberrypi.org/products/camera-module-v2/)
* Mikrofon i głośnik:

  Użyj jednego z poniższych (lub równoważnego):
  * Dowolny mikrofon USB z dowolnym głośnikiem USB, głośnikiem z kablem 3,5 mm lub wyjściem audio HDMI, jeśli Raspberry Pi jest podłączony do monitora lub telewizora z głośnikami
  * Dowolny zestaw słuchawkowy USB z wbudowanym mikrofonem
  * [ReSpeaker 2-Mics Pi HAT](https://www.seeedstudio.com/ReSpeaker-2-Mics-Pi-HAT.html) z
    * Słuchawkami lub innym głośnikiem z wtykiem 3,5 mm, lub głośnikiem JST, takim jak:
    * [Mono Enclosed Speaker - 2W 6 Ohm](https://www.seeedstudio.com/Mono-Enclosed-Speaker-2W-6-Ohm-p-2832.html)
  * [Głośnik konferencyjny USB](https://www.amazon.com/USB-Speakerphone-Conference-Business-Microphones/dp/B07Q3D7F8S/ref=sr_1_1?dchild=1&keywords=m0&qid=1614647389&sr=8-1)
* [Czujnik światła Grove](https://www.seeedstudio.com/Grove-Light-Sensor-v1-2-LS06-S-phototransistor.html)
* [Przycisk Grove](https://www.seeedstudio.com/Grove-Button.html)

## Czujniki i elementy wykonawcze

Większość potrzebnych czujników i elementów wykonawczych jest używana zarówno w ścieżkach nauki Arduino, jak i Raspberry Pi:

* [Dioda LED Grove](https://www.seeedstudio.com/Grove-LED-Pack-p-4364.html) x 2
* [Czujnik wilgotności i temperatury Grove](https://www.seeedstudio.com/Grove-Temperature-Humidity-Sensor-DHT11.html)
* [Pojemnościowy czujnik wilgotności gleby Grove](https://www.seeedstudio.com/Grove-Capacitive-Moisture-Sensor-Corrosion-Resistant.html)
* [Przekaźnik Grove](https://www.seeedstudio.com/Grove-Relay.html)
* [Moduł GPS Grove (Air530)](https://www.seeedstudio.com/Grove-GPS-Air530-p-4584.html)
* [Czujnik odległości Grove Time of Flight](https://www.seeedstudio.com/Grove-Time-of-Flight-Distance-Sensor-VL53L0X.html)

## Opcjonalny sprzęt

Lekcje dotyczące automatycznego podlewania działają przy użyciu przekaźnika. Opcjonalnie możesz podłączyć ten przekaźnik do pompy wodnej zasilanej przez USB, korzystając z poniższego sprzętu.

* [Pompa wodna 6V](https://www.seeedstudio.com/6V-Mini-Water-Pump-p-1945.html)
* [Terminal USB](https://www.adafruit.com/product/3628)
* Rurki silikonowe
* Czerwone i czarne przewody
* Mały śrubokręt płaski

## Wirtualny sprzęt

Wirtualna ścieżka sprzętowa zapewni symulatory czujników i elementów wykonawczych, zaimplementowane w Pythonie. W zależności od dostępności sprzętu możesz uruchomić to na swoim normalnym urządzeniu deweloperskim, takim jak Mac, PC, lub na Raspberry Pi, symulując tylko sprzęt, którego nie posiadasz. Na przykład, jeśli masz kamerę Raspberry Pi, ale nie masz czujników Grove, będziesz mógł uruchomić kod wirtualnego urządzenia na swoim Pi i symulować czujniki Grove, ale używać fizycznej kamery.

Wirtualny sprzęt będzie korzystał z projektu [CounterFit](https://github.com/CounterFit-IoT/CounterFit).

Aby ukończyć te lekcje, będziesz potrzebować kamery internetowej, mikrofonu i wyjścia audio, takiego jak głośniki lub słuchawki. Mogą być one wbudowane lub zewnętrzne i muszą być skonfigurowane do pracy z Twoim systemem operacyjnym oraz dostępne dla wszystkich aplikacji.

**Zastrzeżenie**:  
Ten dokument został przetłumaczony za pomocą usługi tłumaczenia AI [Co-op Translator](https://github.com/Azure/co-op-translator). Chociaż dokładamy wszelkich starań, aby tłumaczenie było precyzyjne, prosimy pamiętać, że automatyczne tłumaczenia mogą zawierać błędy lub nieścisłości. Oryginalny dokument w jego rodzimym języku powinien być uznawany za autorytatywne źródło. W przypadku informacji o kluczowym znaczeniu zaleca się skorzystanie z profesjonalnego tłumaczenia przez człowieka. Nie ponosimy odpowiedzialności za jakiekolwiek nieporozumienia lub błędne interpretacje wynikające z użycia tego tłumaczenia.