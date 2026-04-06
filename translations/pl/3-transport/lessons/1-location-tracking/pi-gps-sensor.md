# Odczyt danych GPS - Raspberry Pi

W tej części lekcji dodasz czujnik GPS do swojego Raspberry Pi i odczytasz z niego dane.

## Sprzęt

Raspberry Pi potrzebuje czujnika GPS.

Czujnik, którego użyjesz, to [Grove GPS Air530 sensor](https://www.seeedstudio.com/Grove-GPS-Air530-p-4584.html). Ten czujnik może łączyć się z wieloma systemami GPS, aby szybko i dokładnie określić pozycję. Składa się z dwóch części - głównej elektroniki czujnika oraz zewnętrznej anteny podłączonej cienkim przewodem, która odbiera fale radiowe z satelitów.

Jest to czujnik UART, więc przesyła dane GPS przez UART.

## Podłącz czujnik GPS

Czujnik Grove GPS można podłączyć do Raspberry Pi.

### Zadanie - podłącz czujnik GPS

Podłącz czujnik GPS.

![Czujnik Grove GPS](../../../../../translated_images/pl/grove-gps-sensor.247943bf69b03f0d.webp)

1. Włóż jeden koniec kabla Grove do gniazda w czujniku GPS. Kabel pasuje tylko w jedną stronę.

1. Gdy Raspberry Pi jest wyłączone, podłącz drugi koniec kabla Grove do gniazda UART oznaczonego jako **UART** na nakładce Grove Base przymocowanej do Raspberry Pi. Gniazdo to znajduje się w środkowym rzędzie, po stronie najbliższej gniazda karty SD, na przeciwległym końcu od portów USB i gniazda Ethernet.

    ![Czujnik Grove GPS podłączony do gniazda UART](../../../../../translated_images/pl/pi-gps-sensor.1f99ee2b2f652891.webp)

1. Ustaw czujnik GPS tak, aby podłączona antena miała widoczność na niebo - najlepiej w pobliżu otwartego okna lub na zewnątrz. Łatwiej uzyskać wyraźny sygnał, gdy nic nie zasłania anteny.

## Programowanie czujnika GPS

Teraz Raspberry Pi można zaprogramować do obsługi podłączonego czujnika GPS.

### Zadanie - zaprogramuj czujnik GPS

Zaprogramuj urządzenie.

1. Włącz Raspberry Pi i poczekaj, aż się uruchomi.

1. Czujnik GPS ma dwie diody LED - niebieską, która miga podczas przesyłania danych, oraz zieloną, która miga co sekundę, gdy odbiera dane z satelitów. Upewnij się, że niebieska dioda LED miga po włączeniu Raspberry Pi. Po kilku minutach powinna zacząć migać zielona dioda LED - jeśli nie, może być konieczne przestawienie anteny.

1. Uruchom VS Code, bezpośrednio na Raspberry Pi lub za pomocą rozszerzenia Remote SSH.

    > ⚠️ Możesz odwołać się do [instrukcji konfiguracji i uruchamiania VS Code w lekcji 1, jeśli to konieczne](../../../1-getting-started/lessons/1-introduction-to-iot/pi.md).

1. W nowszych wersjach Raspberry Pi obsługujących Bluetooth występuje konflikt między portem szeregowym używanym przez Bluetooth a tym używanym przez port UART Grove. Aby to naprawić, wykonaj następujące kroki:

    1. W terminalu VS Code edytuj plik `/boot/config.txt` za pomocą `nano`, wbudowanego edytora tekstu w terminalu, używając następującego polecenia:

        ```sh
        sudo nano /boot/config.txt
        ```

        > Tego pliku nie można edytować w VS Code, ponieważ wymaga on uprawnień `sudo`, czyli podwyższonych uprawnień. VS Code nie działa z tymi uprawnieniami.

    1. Użyj klawiszy kursora, aby przejść na koniec pliku, a następnie skopiuj poniższy kod i wklej go na końcu pliku:

        ```ini
        dtoverlay=pi3-miniuart-bt
        dtoverlay=pi3-disable-bt
        enable_uart=1
        ```

        Możesz wkleić, używając standardowych skrótów klawiaturowych dla swojego urządzenia (`Ctrl+v` na Windows, Linux lub Raspberry Pi OS, `Cmd+v` na macOS).

    1. Zapisz plik i wyjdź z `nano`, naciskając `Ctrl+x`. Naciśnij `y`, gdy zostaniesz zapytany, czy chcesz zapisać zmodyfikowany bufor, a następnie naciśnij `enter`, aby potwierdzić nadpisanie `/boot/config.txt`.

        > Jeśli popełnisz błąd, możesz wyjść bez zapisywania, a następnie powtórzyć te kroki.

    1. Edytuj plik `/boot/cmdline.txt` w `nano`, używając następującego polecenia:

        ```sh
        sudo nano /boot/cmdline.txt
        ```

    1. Ten plik zawiera kilka par klucz/wartość oddzielonych spacjami. Usuń wszystkie pary klucz/wartość dla klucza `console`. Prawdopodobnie będą wyglądać tak:

        ```output
        console=serial0,115200 console=tty1 
        ```

        Możesz przejść do tych wpisów za pomocą klawiszy kursora, a następnie usunąć je za pomocą klawiszy `del` lub `backspace`.

        Na przykład, jeśli Twój oryginalny plik wygląda tak:

        ```output
        console=serial0,115200 console=tty1 root=PARTUUID=058e2867-02 rootfstype=ext4 elevator=deadline fsck.repair=yes rootwait
        ```

        Nowa wersja będzie wyglądać tak:

        ```output
        root=PARTUUID=058e2867-02 rootfstype=ext4 elevator=deadline fsck.repair=yes rootwait
        ```

    1. Wykonaj powyższe kroki, aby zapisać ten plik i wyjść z `nano`.

    1. Uruchom ponownie Raspberry Pi, a następnie połącz się ponownie w VS Code po ponownym uruchomieniu Pi.

1. W terminalu utwórz nowy folder w katalogu domowym użytkownika `pi` o nazwie `gps-sensor`. Utwórz plik w tym folderze o nazwie `app.py`.

1. Otwórz ten folder w VS Code.

1. Moduł GPS przesyła dane UART przez port szeregowy. Zainstaluj pakiet Pip `pyserial`, aby komunikować się z portem szeregowym w kodzie Pythona:

    ```sh
    pip3 install pyserial
    ```

1. Dodaj poniższy kod do swojego pliku `app.py`:

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

    Ten kod importuje moduł `serial` z pakietu Pip `pyserial`. Następnie łączy się z portem szeregowym `/dev/ttyAMA0` - to adres portu szeregowego, którego używa nakładka Grove Pi Base Hat dla swojego portu UART. Następnie czyści wszelkie istniejące dane z tego połączenia szeregowego.

    Następnie definiowana jest funkcja `print_gps_data`, która wypisuje na konsolę linię przekazaną do niej jako argument.

    Kolejny fragment kodu działa w nieskończonej pętli, odczytując tyle linii tekstu, ile może z portu szeregowego w każdej iteracji. Wywołuje funkcję `print_gps_data` dla każdej linii.

    Po odczytaniu wszystkich danych pętla usypia na 1 sekundę, a następnie próbuje ponownie.

1. Uruchom ten kod. Zobaczysz surowe dane wyjściowe z czujnika GPS, coś w rodzaju:

    ```output
    $GNGGA,020604.001,4738.538654,N,12208.341758,W,1,3,,164.7,M,-17.1,M,,*67
    $GPGSA,A,1,,,,,,,,,,,,,,,*1E
    $BDGSA,A,1,,,,,,,,,,,,,,,*0F
    $GPGSV,1,1,00*79
    $BDGSV,1,1,00*68
    ```

    > Jeśli napotkasz jeden z poniższych błędów podczas zatrzymywania i ponownego uruchamiania kodu, dodaj blok `try - except` do swojej pętli `while`.

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

> 💁 Ten kod znajdziesz w folderze [code-gps/pi](../../../../../3-transport/lessons/1-location-tracking/code-gps/pi).

😀 Twój program obsługujący czujnik GPS działa poprawnie!

**Zastrzeżenie**:  
Ten dokument został przetłumaczony za pomocą usługi tłumaczeniowej AI [Co-op Translator](https://github.com/Azure/co-op-translator). Chociaż dokładamy wszelkich starań, aby zapewnić dokładność, prosimy pamiętać, że automatyczne tłumaczenia mogą zawierać błędy lub nieścisłości. Oryginalny dokument w jego rodzimym języku powinien być uznawany za wiarygodne źródło. W przypadku informacji krytycznych zaleca się skorzystanie z profesjonalnego tłumaczenia przez człowieka. Nie ponosimy odpowiedzialności za jakiekolwiek nieporozumienia lub błędne interpretacje wynikające z korzystania z tego tłumaczenia.