# Odczyt danych GPS - Wio Terminal

W tej części lekcji dodasz czujnik GPS do swojego Wio Terminal i odczytasz z niego wartości.

## Sprzęt

Wio Terminal potrzebuje czujnika GPS.

Czujnik, którego użyjesz, to [Grove GPS Air530 sensor](https://www.seeedstudio.com/Grove-GPS-Air530-p-4584.html). Ten czujnik może łączyć się z wieloma systemami GPS, aby szybko i dokładnie ustalić pozycję. Czujnik składa się z dwóch części - głównej elektroniki czujnika oraz zewnętrznej anteny podłączonej cienkim przewodem, która odbiera fale radiowe z satelitów.

Jest to czujnik UART, więc przesyła dane GPS za pomocą UART.

### Podłącz czujnik GPS

Czujnik Grove GPS można podłączyć do Wio Terminal.

#### Zadanie - podłącz czujnik GPS

Podłącz czujnik GPS.

![Czujnik Grove GPS](../../../../../translated_images/pl/grove-gps-sensor.247943bf69b03f0d.webp)

1. Włóż jeden koniec kabla Grove do gniazda w czujniku GPS. Kabel wejdzie tylko w jednym kierunku.

1. Gdy Wio Terminal jest odłączony od komputera lub innego źródła zasilania, podłącz drugi koniec kabla Grove do gniazda Grove po lewej stronie Wio Terminal, patrząc na ekran. Jest to gniazdo najbliżej przycisku zasilania.

    ![Czujnik Grove GPS podłączony do lewego gniazda](../../../../../translated_images/pl/wio-gps-sensor.19fd52b81ce58095.webp)

1. Umieść czujnik GPS tak, aby podłączona antena miała widoczność na niebo - najlepiej obok otwartego okna lub na zewnątrz. Łatwiej uzyskać wyraźny sygnał, gdy nic nie zasłania anteny.

1. Teraz możesz podłączyć Wio Terminal do komputera.

1. Czujnik GPS ma 2 diody LED - niebieską, która miga podczas przesyłania danych, oraz zieloną, która miga co sekundę podczas odbierania danych z satelitów. Upewnij się, że niebieska dioda LED miga po włączeniu Wio Terminal. Po kilku minutach zielona dioda LED zacznie migać - jeśli nie, może być konieczne przestawienie anteny.

## Programowanie czujnika GPS

Teraz możesz zaprogramować Wio Terminal, aby korzystał z podłączonego czujnika GPS.

### Zadanie - zaprogramuj czujnik GPS

Zaprogramuj urządzenie.

1. Utwórz nowy projekt dla Wio Terminal w PlatformIO. Nazwij ten projekt `gps-sensor`. Dodaj kod w funkcji `setup`, aby skonfigurować port szeregowy.

1. Dodaj następującą dyrektywę `include` na początku pliku `main.cpp`. Zawiera ona plik nagłówkowy z funkcjami do konfiguracji lewego gniazda Grove dla UART.

    ```cpp
    #include <wiring_private.h>
    ```

1. Poniżej dodaj następującą linię kodu, aby zadeklarować połączenie portu szeregowego z portem UART:

    ```cpp
    static Uart Serial3(&sercom3, PIN_WIRE_SCL, PIN_WIRE_SDA, SERCOM_RX_PAD_1, UART_TX_PAD_0);
    ```

1. Musisz dodać kod, aby przekierować niektóre wewnętrzne obsługiwacze sygnałów do tego portu szeregowego. Dodaj następujący kod poniżej deklaracji `Serial3`:

    ```cpp
    void SERCOM3_0_Handler()
    {
        Serial3.IrqHandler();
    }
    
    void SERCOM3_1_Handler()
    {
        Serial3.IrqHandler();
    }
    
    void SERCOM3_2_Handler()
    {
        Serial3.IrqHandler();
    }
    
    void SERCOM3_3_Handler()
    {
        Serial3.IrqHandler();
    }
    ```

1. W funkcji `setup`, poniżej konfiguracji portu `Serial`, skonfiguruj port szeregowy UART za pomocą następującego kodu:

    ```cpp
    Serial3.begin(9600);

    while (!Serial3)
        ; // Wait for Serial3 to be ready

    delay(1000);
    ```

1. Poniżej tego kodu w funkcji `setup` dodaj następujący kod, aby połączyć pin Grove z portem szeregowym:

    ```cpp
    pinPeripheral(PIN_WIRE_SCL, PIO_SERCOM_ALT);
    ```

1. Dodaj następującą funkcję przed funkcją `loop`, aby wysyłać dane GPS do monitora szeregowego:

    ```cpp
    void printGPSData()
    {
        Serial.println(Serial3.readStringUntil('\n'));
    }
    ```

1. W funkcji `loop` dodaj następujący kod, aby odczytać dane z portu szeregowego UART i wyświetlić je w monitorze szeregowym:

    ```cpp
    while (Serial3.available() > 0)
    {
        printGPSData();
    }
    
    delay(1000);
    ```

    Ten kod odczytuje dane z portu szeregowego UART. Funkcja `readStringUntil` odczytuje dane aż do znaku kończącego, w tym przypadku nowej linii. Odczytuje całe zdanie NMEA (zdania NMEA są zakończone znakiem nowej linii). Dopóki dane mogą być odczytane z portu szeregowego UART, są odczytywane i wysyłane do monitora szeregowego za pomocą funkcji `printGPSData`. Gdy nie można już odczytać więcej danych, funkcja `loop` wstrzymuje działanie na 1 sekundę (1,000ms).

1. Zbuduj i wgraj kod na Wio Terminal.

1. Po wgraniu możesz monitorować dane GPS za pomocą monitora szeregowego.

    ```output
    > Executing task: platformio device monitor <
    
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1201  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    $GNGGA,020604.001,4738.538654,N,12208.341758,W,1,3,,164.7,M,-17.1,M,,*67
    $GPGSA,A,1,,,,,,,,,,,,,,,*1E
    $BDGSA,A,1,,,,,,,,,,,,,,,*0F
    $GPGSV,1,1,00*79
    $BDGSV,1,1,00*68
    ```

> 💁 Ten kod znajdziesz w folderze [code-gps/wio-terminal](../../../../../3-transport/lessons/1-location-tracking/code-gps/wio-terminal).

😀 Twój program czujnika GPS działa poprawnie!

**Zastrzeżenie**:  
Ten dokument został przetłumaczony za pomocą usługi tłumaczenia AI [Co-op Translator](https://github.com/Azure/co-op-translator). Chociaż dokładamy wszelkich starań, aby zapewnić poprawność tłumaczenia, prosimy pamiętać, że automatyczne tłumaczenia mogą zawierać błędy lub nieścisłości. Oryginalny dokument w jego rodzimym języku powinien być uznawany za autorytatywne źródło. W przypadku informacji o kluczowym znaczeniu zaleca się skorzystanie z profesjonalnego tłumaczenia przez człowieka. Nie ponosimy odpowiedzialności za jakiekolwiek nieporozumienia lub błędne interpretacje wynikające z korzystania z tego tłumaczenia.