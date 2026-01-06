<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "9713e21a309662f6fcb271b573d47848",
  "translation_date": "2026-01-06T03:59:45+00:00",
  "source_file": "TROUBLESHOOTING.md",
  "language_code": "pl"
}
-->
# Przewodnik rozwiązywania problemów

Ten przewodnik pomoże Ci rozwiązać typowe problemy podczas pracy z kursem IoT for Beginners. Problemy są uporządkowane według kategorii, aby ułatwić nawigację.

## Spis treści

- [Problemy z instalacją](../..)
  - [Instalacja Pythona](../..)
  - [VS Code i rozszerzenia](../..)
  - [PlatformIO (Wio Terminal)](../..)
  - [Biblioteki Grove](../..)
- [Problemy sprzętowe](../..)
  - [Raspberry Pi](../..)
  - [Wio Terminal](../..)
  - [Wirtualne urządzenie (CounterFit)](../..)
- [Problemy z łącznością](../..)
  - [Połączenie WiFi](../..)
  - [Usługi w chmurze](../..)
  - [MQTT](../..)
- [Problemy z czujnikami i siłownikami](../..)
  - [Czujniki Grove](../..)
  - [Kamera](../..)
  - [Mikrofon i głośnik](../..)
- [Problemy ze środowiskiem programistycznym](../..)
  - [VS Code](../..)
  - [Wirtualne środowiska Pythona](../..)
  - [Zależności](../..)
- [Problemy z wydajnością](../..)
- [Typowe komunikaty o błędach](../..)
- [Uzyskiwanie pomocy](../..)

---

## Problemy z instalacją

### Instalacja Pythona

#### Problem: Wersja Pythona jest zbyt stara
**Błąd:** `Python 3.6 lub wyższy jest wymagany`

**Rozwiązanie:**
1. Pobierz najnowszą wersję Pythona 3 z [python.org](https://www.python.org/downloads/)
2. Podczas instalacji na Windows zaznacz opcję „Add Python to PATH”
3. Zweryfikuj instalację:
   ```bash
   python3 --version
   ```

#### Problem: Konflikty związane z wieloma wersjami Pythona
**Objawy:** Uruchamiana jest niewłaściwa wersja Pythona, pakiety instalują się w złym miejscu

**Rozwiązanie:**
- **Windows:** Używaj `py -3` zamiast `python` aby jawnie wywołać Python 3
- **macOS/Linux:** Używaj `python3` zamiast `python`
- Zawsze twórz i używaj wirtualnych środowisk dla projektów

#### Problem: Nie znaleziono polecenia pip
**Błąd:** `'pip' nie jest rozpoznawany jako polecenie wewnętrzne lub zewnętrzne`

**Rozwiązanie:**
1. Spróbuj zamiast `pip` użyć `pip3`
2. Lub użyj `python -m pip` albo `python3 -m pip`
3. Upewnij się, że Python został dodany do PATH (przeinstaluj Pythona i zaznacz tę opcję)

### VS Code i rozszerzenia

#### Problem: Rozszerzenie Pylance nie działa
**Objawy:** Brak IntelliSense, uzupełniania kodu lub sprawdzania typów w Pythonie

**Rozwiązanie:**
1. Otwórz paletę poleceń VS Code (`Ctrl+Shift+P` lub `Cmd+Shift+P`)
2. Wpisz „Python: Select Interpreter”
3. Wybierz właściwy interpreter Pythona (wirtualne środowisko jeśli używasz)
4. Przeładuj okno VS Code

#### Problem: VS Code nie wykrywa wirtualnego środowiska
**Objawy:** Wybrano niewłaściwy interpreter Pythona

**Rozwiązanie:**
1. Upewnij się, że aktywowałeś wirtualne środowisko w terminalu
2. Otwórz paletę poleceń i uruchom „Python: Select Interpreter”
3. Wybierz interpreter z folderu `.venv`
4. Sprawdź, czy pasek stanu (lewy dolny róg) pokazuje właściwą wersję Pythona

### PlatformIO (Wio Terminal)

#### Problem: Instalacja PlatformIO nie powiodła się
**Błąd:** Różne błędy podczas instalacji PlatformIO

**Rozwiązanie:**
1. Upewnij się, że VS Code jest aktualny
2. Najpierw zainstaluj rozszerzenie C/C++
3. Uruchom ponownie VS Code po instalacji PlatformIO
4. Sprawdź połączenie internetowe (PlatformIO pobiera duże pliki)

#### Problem: PlatformIO nie wykrywa płytki
**Objawy:** Nie można wgrać kodu do Wio Terminal

**Rozwiązanie:**
1. Wypróbuj inny kabel USB (niektóre kable służą tylko do ładowania)
2. Sprawdź Menedżera urządzeń (Windows) lub `ls /dev/tty*` (macOS/Linux)
3. Zainstaluj lub zaktualizuj sterowniki USB
4. Wypróbuj inny port USB
5. Przesuń przełącznik zasilania na Wio Terminal szybko dwa razy, aby wejść w tryb bootloadera

#### Problem: Błędy kompilacji w PlatformIO
**Błąd:** `fatal error: Arduino.h: No such file or directory`

**Rozwiązanie:**
1. Usuń folder `.pio` w projekcie
2. Uruchom „PlatformIO: Rebuild” z palety poleceń
3. Upewnij się, że plik `platformio.ini` zawiera poprawną konfigurację płyty:
   ```ini
   [env:seeed_wio_terminal]
   platform = atmelsam
   board = seeed_wio_terminal
   framework = arduino
   ```

### Biblioteki Grove

#### Problem: Import biblioteki Grove nie działa na Raspberry Pi
**Błąd:** `ModuleNotFoundError: No module named 'grove'`

**Rozwiązanie:**
1. Ponownie zainstaluj biblioteki Grove:
   ```bash
   cd ~
   git clone https://github.com/Seeed-Studio/grove.py
   cd grove.py
   sudo pip3 install .
   ```
2. Jeśli używasz wirtualnego środowiska, może być konieczna globalna instalacja lub skopiowanie bibliotek
3. Sprawdź, czy I2C jest włączone: `sudo raspi-config nonint do_i2c 0`

#### Problem: Czujnik Grove nie jest wykrywany
**Błąd:** `IOError: [Errno 121] Remote I/O error`

**Rozwiązanie:**
1. Sprawdź połączenia fizyczne (upewnij się, że kabel Grove jest całkowicie wsunięty)
2. Zweryfikuj, czy czujnik podłączony jest do właściwego portu (analogowy, cyfrowy, I2C, UART)
3. Uruchom `i2cdetect -y 1` aby zobaczyć, czy urządzenie pojawia się na magistrali I2C
4. Wypróbuj inny kabel Grove
5. Upewnij się, że Grove Base Hat jest poprawnie osadzony na pinach GPIO Raspberry Pi

---

## Problemy sprzętowe

### Raspberry Pi

#### Problem: Raspberry Pi nie uruchamia się
**Objawy:** Brak obrazu, brak aktywności diod LED lub wyświetla się tęczowy ekran

**Rozwiązanie:**
1. **Sprawdź zasilacz:** Użyj oficjalnego zasilacza 5V 3A USB-C dla Pi 4
2. **Problemy z kartą SD:** 
   - Sformatuj kartę SD i ponownie zainstaluj Raspberry Pi OS
   - Wypróbuj inną kartę SD (używaj polecanych marek)
   - Upewnij się, że karta SD jest prawidłowo włożona
3. **Sprawdź połączenie HDMI:** Spróbuj obu portów HDMI na Pi 4, użyj portu HDMI bliższego zasilaniu

#### Problem: Nie można połączyć się z Raspberry Pi przez SSH
**Objawy:** Połączenie odrzucone lub brak odpowiedzi

**Rozwiązanie:**
1. Włącz SSH:
   - Podczas nagrywania SD karti za pomocą Raspberry Pi Imager, skonfiguruj SSH w zaawansowanych opcjach
   - Lub utwórz pusty plik o nazwie `ssh` (bez rozszerzenia) w partycji boot
2. Znajdź adres IP Pi:
   - Sprawdź urządzenia podłączone do routera
   - Użyj `ping raspberrypi.local` (jeśli działa mDNS)
   - Użyj narzędzi do skanowania sieci, takich jak `nmap` lub Angry IP Scanner
3. Sprawdź sieć:
   - Upewnij się, że Pi jest w tej samej sieci co komputer
   - Spróbuj połączenia przez Ethernet zamiast WiFi
4. Zweryfikuj nazwę użytkownika/hasło (domyślnie: użytkownik `pi`, hasło `raspberry`)

#### Problem: Grove Base Hat nie jest rozpoznany
**Objawy:** Czujniki nie działają, błędy I2C

**Rozwiązanie:**
1. Upewnij się, że Base Hat jest poprawnie osadzony na wszystkich pinach GPIO
2. Sprawdź, czy nie ma wygiętych pinów na Pi lub Base Hat
3. Włącz interfejs I2C:
   ```bash
   sudo raspi-config nonint do_i2c 0
   sudo reboot
   ```
4. Zweryfikuj działanie I2C: `i2cdetect -y 1`

#### Problem: Raspberry Pi działa wolno
**Objawy:** Interfejs opóźnia się, powolna reakcja

**Rozwiązanie:**
1. Sprawdź szybkość karty SD (używaj klasy 10 lub lepszej, lub SSD przez USB)
2. Zwolnij miejsce na dysku: `df -h` do sprawdzenia, usuń niepotrzebne pliki
3. Zmniejsz pamięć GPU w `raspi-config`, jeśli nie używasz intensywnie kamery/wyświetlacza
4. Zamknij zbędne aplikacje
5. Rozważ aktualizację do Pi 4 z większą ilością RAM, jeśli masz Pi 3 lub starszy

### Wio Terminal

#### Problem: Ekran Wio Terminal pozostaje czarny
**Objawy:** Brak wyświetlania po wgraniu kodu

**Rozwiązanie:**
1. Sprawdź, czy kod inicjalizuje wyświetlacz (biblioteka TFT_eSPI)
2. Zaktualizuj firmware Wio Terminal z [Seeed Wiki](https://wiki.seeedstudio.com/Wio-Terminal-Getting-Started/)
3. Dodaj kod inicjalizujący wyświetlacz:
   ```cpp
   #include <TFT_eSPI.h>
   TFT_eSPI tft;
   tft.begin();
   tft.fillScreen(TFT_BLACK);
   ```
4. Spróbuj wgrać przykładowy szkic z PlatformIO, aby przetestować sprzęt

#### Problem: WiFi nie działa na Wio Terminal
**Objawy:** Nie można połączyć się z WiFi, błędy sieciowe

**Rozwiązanie:**
1. **Zaktualizuj firmware WiFi:** Postępuj według [instrukcji aktualizacji WiFi Wio Terminal](https://wiki.seeedstudio.com/Wio-Terminal-Network-Overview/)
2. **Sprawdź dane uwierzytelniające WiFi:** Upewnij się, że SSID i hasło są poprawne
3. **Pasmo WiFi:** Wio Terminal obsługuje tylko WiFi 2.4GHz (nie 5GHz)
4. **Siła sygnału:** Przesuń urządzenie bliżej routera
5. **Ustawienia routera:** Niektóre sieci enterprise/WPA-Enterprise mogą nie działać

#### Problem: Wio Terminal nie jest rozpoznawany przez komputer
**Objawy:** Urządzenie USB nie jest wykrywane

**Rozwiązanie:**
1. **Wypróbuj inny kabel USB:** Używaj kabla danych, a nie tylko do ładowania
2. **Wejdź w tryb bootloadera:** Przesuń wyłącznik zasilania dwa razy szybko w dół
   - Niechbieska dioda LED powinna pulsować, urządzenie pojawi się jako „Arduino” w Menedżerze urządzeń
3. **Zainstaluj sterowniki (Windows):**
   - Pobierz i zainstaluj [sterownik USB Seeed](https://wiki.seeedstudio.com/Driver_for_Seeeduino/)
4. **Wypróbuj inny port USB:** Unikaj hubów USB, używaj bezpośredniego połączenia
5. **Zaktualizuj sterowniki USB systemu**

#### Problem: Czujniki nie działają na Wio Terminal
**Objawy:** Czujniki Grove nie odczytują danych

**Rozwiązanie:**
1. Sprawdź połączenia kabla Grove
2. Zweryfikuj, że używasz właściwego portu Grove (lewy lub prawy)
3. Dołącz odpowiednie biblioteki dla czujnika
4. Sprawdź wymagania zasilania czujnika
5. Przetestuj czujnik przykładowym kodem z biblioteki

### Wirtualne urządzenie (CounterFit)

#### Problem: Aplikacja CounterFit nie uruchamia się
**Błąd:** Różne błędy Pythona podczas uruchamiania CounterFit

**Rozwiązanie:**
1. Upewnij się, że wirtualne środowisko jest aktywne
2. Zainstaluj/ponownie zainstaluj CounterFit:
   ```bash
   pip install CounterFit
   ```
3. Sprawdź, czy port 5000 nie jest już zajęty:
   - Windows: `netstat -ano | findstr :5000`
   - macOS/Linux: `lsof -i :5000`
4. Zakończ proces korzystający z portu 5000 lub użyj innego portu:
   ```bash
   counterfit --port 5001
   ```

#### Problem: Nie można połączyć się z CounterFit z kodu
**Błąd:** Połączenie odrzucone lub brak odpowiedzi

**Rozwiązanie:**
1. Zweryfikuj, że CounterFit działa: otwórz przeglądarkę i wpisz `http://127.0.0.1:5000`
2. Sprawdź, czy adres URL połączenia w kodzie odpowiada adresowi CounterFit
3. Upewnij się, że zapora sieciowa nie blokuje połączenia
4. Spróbuj ponownie uruchomić zarówno aplikację CounterFit, jak i swój kod

#### Problem: Czujniki nie pojawiają się w CounterFit
**Objawy:** Utworzone czujniki nie wyświetlają się w interfejsie CounterFit

**Rozwiązanie:**
1. Utwórz czujniki w interfejsie CounterFit przed uruchomieniem kodu
2. Odśwież stronę w przeglądarce
3. Sprawdź, czy typ czujnika odpowiada temu, czego oczekuje kod
4. Wyczyść pamięć podręczną przeglądarki

---

## Problemy z łącznością

### Połączenie WiFi

#### Problem: Urządzenie nie może połączyć się z WiFi
**Objawy:** Przekroczenie czasu oczekiwania, uwierzytelnienie nie powiodło się

**Rozwiązanie:**
1. **Sprawdź SSID i hasło:** Zweryfikuj, czy dane uwierzytelniające są poprawne
2. **Pasmo WiFi:** Większość urządzeń IoT obsługuje tylko 2.4GHz (nie 5GHz)
3. **Ustawienia routera:**
   - Wyłącz izolację AP, jeśli jest włączona
   - Używaj zabezpieczeń WPA2-PSK (unikaj WPA3, WEP lub otwartych sieci)
   - Upewnij się, że DHCP jest włączone
4. **Ukryte sieci:** Jeśli SSID jest ukryte, być może trzeba je jawnie skonfigurować
5. **Siła sygnału:** Przesuń urządzenie bliżej routera
6. **Zakłócenia:** Inne urządzenia, kuchenka mikrofalowa lub ściany mogą powodować zakłócenia

#### Problem: Połączenie WiFi często zanika
**Objawy:** Przerywane połączenie

**Rozwiązanie:**
1. Sprawdź stabilność routera i rozważ jego restart
2. Zaktualizuj firmware urządzenia
3. Użyj statycznego adresu IP zamiast DHCP
4. Zmniejsz odległość od routera lub dodaj wzmacniacz sygnału WiFi
5. Sprawdź zakłócenia od innych urządzeń
6. Zweryfikuj, czy zasilanie jest wystarczające (zwłaszcza dla Raspberry Pi)

### Usługi w chmurze

#### Problem: Nie można połączyć się z Azure IoT Hub
**Błąd:** Uwierzytelnianie nie powiodło się, połączenie odrzucone

**Rozwiązanie:**
1. **Zweryfikuj dane uwierzytelniające:**
   - Sprawdź, czy ciąg połączeniowy jest poprawny
   - Upewnij się, że nie ma dodatkowych spacji lub znaków nowej linii w ciągu połączeniowym
2. **Sprawdź rejestrację urządzenia:** Urządzenie musi być zarejestrowane w IoT Hub
3. **Zapora/proxy:** Upewnij się, że dostęp wychodzący na MQTT (port 8883) lub HTTPS (port 443) jest dozwolony
4. **Region IoT Hub:** Upewnij się, że IoT Hub działa i nie jest w innym regionie powodującym opóźnienia
5. **Limity kwot:** Sprawdź, czy limity darmowego planu nie zostały przekroczone
6. **Testuj połączenie:**
   ```bash
   az iot hub device-identity show-connection-string --hub-name YourIoTHub --device-id YourDevice
   ```

#### Problem: Funkcje Azure nie są wywoływane
**Objawy:** Wiadomości są wysyłane, ale funkcja nie jest uruchamiana

**Rozwiązanie:**
1. Sprawdź, czy aplikacja funkcji działa (nie jest zatrzymana)
2. Zweryfikuj ciąg połączeniowy w ustawieniach aplikacji funkcji
3. Sprawdź logi funkcji w portalu Azure
4. Upewnij się, że punkt końcowy kompatybilny z Event Hub jest poprawnie skonfigurowany
5. Zweryfikuj, czy format wiadomości odpowiada oczekiwaniom funkcji
6. Sprawdź plan usługi aplikacji funkcji (konsumpcyjny vs dedykowany)

### MQTT
#### Problem: Połączenie MQTT nie powiodło się
**Błąd:** Połączenie odmówione, uwierzytelnianie nie powiodło się

**Rozwiązanie:**
1. **Adres brokera:** Sprawdź, czy adres URL/IP brokera jest poprawny
2. **Port:** Sprawdź numer portu (1883 dla nieszyfrowanego, 8883 dla TLS)
3. **Uwierzytelnianie:** Zweryfikuj nazwę użytkownika/hasło, jeśli wymagane
4. **TLS/SSL:** Upewnij się, że certyfikaty są ważne i zaufane
5. **Firewall:** Sprawdź, czy port nie jest zablokowany
6. **Test za pomocą klienta MQTT:** Użyj MQTT Explorer lub mosquitto_pub/sub do testu

#### Problem: Wiadomości MQTT nie są odbierane
**Objawy:** Wiadomości są publikowane, ale nie są odbierane przez subskrybentów

**Rozwiązanie:**
1. **Nazwy tematów:** Zweryfikuj, czy temat subskrybenta dokładnie pasuje do tematu wydawcy
2. **Poziom QoS:** Spróbuj QoS 1 lub 2 zamiast 0
3. **Wildcardy:** Sprawdź, czy symbole wieloznaczne tematów są używane poprawnie (`+` dla pojedynczego poziomu, `#` dla wielopoziomowego)
4. **Zachowane wiadomości:** Wydawca może ustawić flagę retain, aby zachować ostatnią wiadomość
5. **Czas połączenia:** Upewnij się, że subskrybent łączy się przed publikacją wiadomości

---

## Problemy z czujnikami i aktuatorami

### Czujniki Grove

#### Problem: Czujnik zwraca niepoprawne wartości
**Objawy:** Odczyty wynoszą 0, -1 lub są bezsensowne

**Rozwiązanie:**
1. **Sprawdź połączenia:** Upewnij się, że czujnik jest poprawnie podłączony
2. **Prawidłowy port:** Zweryfikuj, czy czujnik jest podłączony do odpowiedniego typu portu:
   - Czujniki analogowe → porty analogowe (A0, A2, A4)
   - Czujniki cyfrowe → porty cyfrowe (D5, D16, D18 itd.)
   - Czujniki I2C → porty I2C
3. **Kalibracja:** Niektóre czujniki wymagają kalibracji (wilgotność gleby, światło)
4. **Restart:** Odłącz i ponownie podłącz czujnik
5. **Karta katalogowa czujnika:** Sprawdź specyfikacje i wymagania czujnika

#### Problem: Pojemnościowy czujnik wilgotności gleby zawsze wskazuje wilgotność
**Objawy:** Czujnik odczytuje wysoką wilgotność, nawet gdy gleba jest sucha

**Rozwiązanie:**
1. **Wymagana kalibracja:** Czujniki gleby wymagają kalibracji:
   - Odczyt wartości na powietrzu (sucha baza)
   - Odczyt wartości w wodzie (mokra baza)
   - Mapuj odczyty pomiędzy tymi wartościami
2. **Sprawdź powłokę czujnika:** Czujniki wilgotności mogą się pogorszyć, jeśli powłoka jest uszkodzona
3. **Miejsce instalacji:** Upewnij się, że czujnik jest całkowicie umieszczony w glebie

#### Problem: Niepoprawne odczyty czujnika temperatury/wilgotności
**Objawy:** DHT11/DHT22 pokazuje błędną temperaturę lub wilgotność

**Rozwiązanie:**
1. **Umieszczenie czujnika:** Unikaj bezpośredniego światła słonecznego, źródeł ciepła lub przepływu powietrza
2. **Czas rozgrzewania:** Pozwól czujnikowi 2 sekundy po włączeniu zasilania przed odczytem
3. **Częstotliwość odczytu:** Czujniki DHT potrzebują czasu pomiędzy odczytami (co najmniej 2 sekundy)
4. **Sprawdź kondensację:** Może wpływać na odczyty
5. **Jakość czujnika:** DHT11 jest mniej dokładny niż DHT22

### Kamera

#### Problem: Kamera nie jest wykrywana na Raspberry Pi
**Błąd:** `mmal: mmal_vc_component_create: failed to create component 'vc.ril.camera'`

**Rozwiązanie:**
1. **Włącz interfejs kamery:**
   ```bash
   sudo raspi-config
   ```
   Przejdź do Interface Options → Camera → Włącz
2. **Sprawdź taśmę:** Upewnij się, że taśma kamery jest poprawnie włożona
   - Niebieska strona skierowana w stronę portów USB na Pi Zero
   - Niebieska strona skierowana od portów USB na Pi 4
3. **Aktualizacja firmware:**
   ```bash
   sudo apt update
   sudo apt full-upgrade
   sudo reboot
   ```
4. **Test kamery:**
   ```bash
   raspistill -o test.jpg
   ```

#### Problem: Zdjęcia z kamery są złej jakości
**Objawy:** Nieostre, ciemne lub wyblakłe obrazy

**Rozwiązanie:**
1. **Ostrość:** Usuń ochronną folię z obiektywu, wyreguluj ostrość, jeśli jest regulowana
2. **Oświetlenie:** Zapewnij odpowiednie oświetlenie
3. **Ustawienia kamery:** Dostosuj ekspozycję, ISO, balans bieli w kodzie
4. **Stabilność:** Trzymaj kamerę nieruchomo, użyj statywu jeśli potrzeba
5. **Rozdzielczość:** Nie przekraczaj maksymalnej rozdzielczości kamery

### Mikrofon i Głośnik

#### Problem: Brak dźwięku wejściowego/wyjściowego
**Objawy:** Mikrofon nie nagrywa, głośnik nie odtwarza dźwięku

**Rozwiązanie:**
1. **Sprawdź połączenia:** Zweryfikuj, czy urządzenia audio są poprawnie podłączone
2. **Test sprzętu:**
   - Głośnik: `speaker-test -t wav -c 2`
   - Mikrofon: `arecord -l` do listy, `arecord test.wav` do nagrania
3. **Ustawienia głośności:** Sprawdź i dostosuj głośność:
   ```bash
   alsamixer
   ```
4. **Wybierz urządzenie audio:** Określ poprawne urządzenie audio w kodzie
5. **Problemy ze sterownikami:** Zaktualizuj ALSA lub ponownie zainstaluj sterowniki audio

#### Problem: Nakładka ReSpeaker nie działa
**Objawy:** Urządzenie audio nie jest wykrywane

**Rozwiązanie:**
1. **Zainstaluj sterowniki:**
   ```bash
   git clone https://github.com/HinTak/seeed-voicecard
   cd seeed-voicecard
   sudo ./install.sh
   sudo reboot
   ```
2. **Sprawdź instalację:** `arecord -l` powinno wykazać ReSpeaker
3. **Aktualizacja firmware:** Niektóre wersje Pi OS wymagają aktualizacji sterowników
4. **Sprawdź montaże:** Upewnij się, że nakładka jest poprawnie podłączona do pinów GPIO

---

## Problemy z środowiskiem programistycznym

### VS Code

#### Problem: Terminal nie aktywuje automatycznie środowiska wirtualnego
**Objawy:** Terminal się otwiera, ale venv nie jest aktywowany

**Rozwiązanie:**
1. **Ustaw interpreter Pythona:** Paleta poleceń → "Python: Select Interpreter" → Wybierz venv
2. **Uruchom ponownie VS Code** po wybraniu interpretera
3. **Sprawdź ustawienia:** W `settings.json` dodaj:
   ```json
   "python.terminal.activateEnvironment": true
   ```

#### Problem: Kod nie działa na urządzeniu
**Objawy:** Kod działa, ale nic się nie dzieje na urządzeniu

**Rozwiązanie:**
1. **Zweryfikuj, czy kod jest zapisany** (sprawdź kropkę na zakładce pliku)
2. **Sprawdź, który Python działa:** `which python` lub `where python`
3. **Dla Wio Terminal:** Upewnij się, że kod jest przesłany przez PlatformIO (kliknij przycisk upload)
4. **Dla Raspberry Pi:** Połącz się przez SSH i uruchom kod tam
5. **Sprawdź okno wyjścia** pod kątem błędów

#### Problem: IntelliSense nie pokazuje funkcji biblioteki
**Objawy:** Brak autouzupełniania dla importowanych modułów

**Rozwiązanie:**
1. Upewnij się, że biblioteka jest zainstalowana w bieżącym środowisku
2. Przeładuj okno VS Code
3. Sprawdź, czy interpreter Pythona jest poprawny
4. Zainstaluj typy (type stubs), jeśli są dostępne: `pip install types-<library-name>`

### Środowiska wirtualne Pythona

#### Problem: Nie można utworzyć środowiska wirtualnego
**Błąd:** `The virtual environment was not created successfully`

**Rozwiązanie:**
1. **Zainstaluj moduł venv:**
   - Ubuntu/Debian: `sudo apt install python3-venv`
   - macOS: Powinien być dołączony do Pythona
   - Windows: Zainstaluj ponownie Pythona ze wszystkimi składnikami
2. **Sprawdź instalację Pythona:** Zweryfikuj, czy Python jest poprawnie zainstalowany
3. **Użyj pełnej ścieżki:** Spróbuj `python3 -m venv .venv` z explicite wywołaniem python3

#### Problem: Pakiety instalowane w niewłaściwej lokalizacji
**Objawy:** Błąd importu po instalacji pakietu

**Rozwiązanie:**
1. **Zweryfikuj, czy venv jest aktywowany:** Wiersz poleceń powinien pokazywać `(.venv)`
2. **Sprawdź lokalizację pip:** `which pip` powinno wskazywać `.venv/bin/pip`
3. **Zainstaluj ponownie w venv:** Aktywuj venv, następnie `pip install <package>`
4. **Nie używaj sudo z pip** w środowisku wirtualnym

#### Problem: Środowisko wirtualne nie jest przenośne
**Objawy:** Venv nie działa po przeniesieniu lub na innym komputerze

**Rozwiązanie:**
1. **Nie przenoś venv:** Usuń i utwórz ponownie w nowym miejscu
2. **Używaj requirements.txt:**
   ```bash
   pip freeze > requirements.txt
   pip install -r requirements.txt
   ```
3. **Utwórz ponownie venv:**
   ```bash
   python3 -m venv .venv
   source .venv/bin/activate  # lub activate.bat w systemie Windows
   pip install -r requirements.txt
   ```

### Zależności

#### Problem: Błąd instalacji pakietu
**Błąd:** Różne błędy pip podczas instalacji

**Rozwiązanie:**
1. **Zaktualizuj pip:**
   ```bash
   pip install --upgrade pip
   ```
2. **Zainstaluj narzędzia build:**
   - Ubuntu/Debian: `sudo apt install build-essential python3-dev`
   - macOS: `xcode-select --install`
   - Windows: Zainstaluj Visual Studio Build Tools
3. **Sprawdź połączenie internetowe**
4. **Próbuj innego indeksu pakietów:** `pip install --index-url https://pypi.org/simple/ <package>`
5. **Zainstaluj konkretną wersję:** `pip install <package>==<version>`

#### Problem: Konflikty zależności
**Błąd:** `ERROR: pip's dependency resolver does not currently take into account all the packages that are installed`

**Rozwiązanie:**
1. **Używaj świeżego środowiska wirtualnego** dla każdego projektu
2. **Aktualizuj pakiety:** `pip install --upgrade <package>`
3. **Sprawdź wymagania:** Użyj `pip check` do wykrywania konfliktów
4. **Instaluj zgodne wersje:** Określ zakres wersji w requirements.txt

---

## Problemy z wydajnością

### Problem: Kod działa wolno
**Objawy:** Opóźnienia, timeouty, brak reakcji

**Rozwiązanie:**
1. **Zmniejsz częstotliwość odczytów czujników:** Nie odczytuj czujników zbyt często
2. **Optymalizuj pętle:** Unikaj aktywnego oczekiwania, używaj sleep() lub opóźnień
3. **Problemy z pamięcią:**
   - Zamknij niepotrzebne aplikacje
   - Zwolnij miejsce na dysku
   - Monitoruj za pomocą `top` lub `htop` na Pi
4. **Szybkość karty SD:** Użyj szybszej karty SD lub SSD dla Raspberry Pi
5. **Opóźnienia sieciowe:** Używaj operacji asynchronicznych dla wywołań sieciowych

### Problem: Błędy braku pamięci
**Błąd:** `MemoryError` lub zawieszanie się systemu

**Rozwiązanie:**
1. **Dla Raspberry Pi:**
   - Zamknij niepotrzebne aplikacje
   - Zwiększ przestrzeń wymiany (swap)
   - Używaj lżejszego systemu (wersja Lite)
   - Zwiększ RAM (Pi 4 ma opcje 2/4/8GB)
2. **Dla Wio Terminal:**
   - Zmniejsz rozmiary buforów
   - Używaj mniejszych obrazów
   - Optymalizuj użycie łańcuchów znaków
   - Sprawdź wycieki pamięci (niezwolniona pamięć)

### Problem: Utrata lub uszkodzenie danych
**Objawy:** Brakujące wiadomości, uszkodzone pliki

**Rozwiązanie:**
1. **Problemy z kartą SD:**
   - Używaj jakościowych kart SD (unikaj tanich/podróbek)
   - Regularne kopie zapasowe
   - Bezpieczne wyłączanie (nie odcinaj zasilania)
2. **Przepełnienie bufora:** Zwiększ rozmiary buforów w kodzie
3. **Niezawodność sieci:** Wprowadź logikę powtórzeń i obsługę błędów
4. **Jakość usług:** Używaj MQTT QoS 1 lub 2 dla ważnych wiadomości

---

## Najczęstsze komunikaty błędów

### `ModuleNotFoundError: No module named 'X'`
**Przyczyna:** Pakiet nie jest zainstalowany lub środowisko wirtualne nie jest aktywowane

**Rozwiązanie:**
```bash
pip install X
```
Najpierw upewnij się, że środowisko wirtualne jest aktywowane.

### `Permission denied` na Linux/macOS
**Przyczyna:** Wymagane są podwyższone uprawnienia lub problem z uprawnieniami do pliku

**Rozwiązanie:**
- Dla operacji systemowych: Użyj `sudo`
- Dla pip: NIE używaj sudo z venv, najpierw aktywuj venv
- Dla portu szeregowego: Dodaj użytkownika do grupy dialout: `sudo usermod -a -G dialout $USER`, potem wyloguj się i zaloguj ponownie

### `OSError: [Errno 98] Address already in use`
**Przyczyna:** Port jest już używany przez inny proces

**Rozwiązanie:**
1. Znajdź proces korzystający z portu: `lsof -i :<port>` lub `netstat -ano | findstr :<port>`
2. Zabij proces lub użyj innego portu w swoim kodzie

### `SSL: CERTIFICATE_VERIFY_FAILED`
**Przyczyna:** Błąd walidacji certyfikatu SSL

**Rozwiązanie:**
1. Zaktualizuj certyfikaty: `pip install --upgrade certifi`
2. Sprawdź, czy czas systemowy jest poprawny: `date`
3. Tylko do celów rozwojowych (nie produkcyjnych): Wyłącz weryfikację w kodzie

### `IndentationError: unexpected indent`
**Przyczyna:** Problemy z wcięciami w Pythonie (mieszanie tabulatorów i spacji)

**Rozwiązanie:**
1. Używaj spójnych wcięć (standardem jest 4 spacje)
2. Skonfiguruj edytor, aby używał spacji zamiast tabulatorów
3. VS Code: Ustaw `"editor.insertSpaces": true` oraz `"editor.tabSize": 4`

### `UnicodeDecodeError` lub `UnicodeEncodeError`
**Przyczyna:** Problemy z kodowaniem znaków

**Rozwiązanie:**
```python
# Podczas odczytu plików
with open('file.txt', 'r', encoding='utf-8') as f:
    content = f.read()

# Podczas zapisywania plików
with open('file.txt', 'w', encoding='utf-8') as f:
    f.write(content)
```

---

## Uzyskiwanie pomocy

Jeśli wypróbowałeś te kroki rozwiązywania problemów i nadal masz problemy:

### 1. Sprawdź istniejące zasoby
- **Dokumentacja:** Przejrzyj [README](README.md) i instrukcje lekcji
- **Przewodniki sprzętowe:** Sprawdź [hardware.md](hardware.md) dla informacji specyficznych dla sprzętu
- **Seeed Studio Wiki:** [Seeed Studio Wiki](https://wiki.seeedstudio.com/) dla komponentów Grove

### 2. Szukaj podobnych problemów
- **GitHub Issues:** Szukaj [istniejących zgłoszeń](https://github.com/microsoft/IoT-For-Beginners/issues)
- **Stack Overflow:** Szukaj komunikatów błędów
- **Fora urządzeń:** Sprawdź fora Raspberry Pi lub Arduino

### 3. Utwórz zgłoszenie na GitHub
Jeśli nie możesz znaleźć rozwiązania:
1. Wejdź na [GitHub Issues](https://github.com/microsoft/IoT-For-Beginners/issues)
2. Kliknij "New Issue"
3. Podaj:
   - Jasny opis problemu
   - Kroki do odtworzenia
   - Komunikaty błędów (pełny tekst)
   - Wersje sprzętu/oprogramowania
   - Co już próbowałeś
   - Zrzuty ekranu, jeśli są istotne

### 4. Dołącz do społeczności
- **Discord:** [Microsoft Foundry Discord](https://discord.gg/nTYy5BXMWG)
- **Microsoft Learn:** [Microsoft Learn IoT](https://docs.microsoft.com/learn/browse/?products=azure-iot)

### 5. Dostarczaj dobre raporty błędów
Dobry raport błędu zawiera:
- **Środowisko:** system operacyjny, wersja Pythona, używany sprzęt  
- **Kroki do odtworzenia:** dokładne kroki wywołujące problem  
- **Oczekiwane zachowanie:** co powinno się zdarzyć  
- **Rzeczywiste zachowanie:** co faktycznie się dzieje  
- **Komunikaty o błędach:** pełny tekst błędu, nie zrzuty ekranu  
- **Kod:** minimalny przykład kodu reprodukujący problem  

---

## Wskazówki dotyczące zapobiegania

### Ogólne najlepsze praktyki
1. **Rób kopie zapasowe:** regularne kopie zapasowe działających kart SD/kodu  
2. **Dokumentuj zmiany:** zanotuj, co działa w komentarzach  
3. **Kontrola wersji:** używaj gita do śledzenia zmian w kodzie  
4. **Testuj stopniowo:** testuj małe zmiany przed połączeniem  
5. **Czytaj komunikaty błędów:** często mówią dokładnie, co jest źle  
6. **Aktualizuj regularnie:** utrzymuj oprogramowanie/firmware na bieżąco  
7. **Używaj komponentów dobrej jakości:** unikaj tanich kabli/zasilaczy  
8. **Stabilne zasilanie:** używaj odpowiedniego zasilacza (szczególnie Pi)  

### Przebieg pracy programisty
1. **Zacznij od prostego:** rozpocznij od działającego przykładowego kodu  
2. **Jedna zmiana na raz:** łatwiej znaleźć, co psuje  
3. **Testuj często:** wykrywaj problemy wcześnie  
4. **Utrzymuj porządek:** organizuj pliki i kod logicznie  
5. **Komentuj kod:** przyszły ty będzie ci wdzięczny  

---

*Ten przewodnik rozwiązywania problemów jest utrzymywany przez społeczność. Jeśli znajdziesz rozwiązanie problemu, które tutaj nie zostało wymienione, rozważ [wkład](CONTRIBUTING.md), aby pomóc innym!*

---

<!-- CO-OP TRANSLATOR DISCLAIMER START -->
**Zastrzeżenie**:  
Niniejszy dokument został przetłumaczony za pomocą automatycznego tłumacza AI [Co-op Translator](https://github.com/Azure/co-op-translator). Mimo że dokładamy wszelkich starań, aby tłumaczenie było jak najdokładniejsze, prosimy mieć na uwadze, że tłumaczenia automatyczne mogą zawierać błędy lub niedokładności. Oryginalny dokument w języku źródłowym powinien być uważany za źródło autorytatywne. W przypadku informacji kluczowych zalecamy skorzystanie z profesjonalnego tłumaczenia wykonanego przez człowieka. Nie ponosimy odpowiedzialności za jakiekolwiek nieporozumienia lub błędne interpretacje wynikające z korzystania z tego tłumaczenia.
<!-- CO-OP TRANSLATOR DISCLAIMER END -->