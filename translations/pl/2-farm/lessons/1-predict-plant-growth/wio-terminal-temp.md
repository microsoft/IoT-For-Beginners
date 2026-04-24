# Mierzenie temperatury - Wio Terminal

W tej części lekcji dodasz czujnik temperatury do swojego Wio Terminal i odczytasz z niego wartości temperatury.

## Sprzęt

Wio Terminal potrzebuje czujnika temperatury.

Czujnik, którego użyjesz, to [czujnik wilgotności i temperatury DHT11](https://www.seeedstudio.com/Grove-Temperature-Humidity-Sensor-DHT11.html), który łączy dwa czujniki w jednym urządzeniu. Jest to dość popularne rozwiązanie, a wiele dostępnych na rynku czujników łączy pomiar temperatury, wilgotności, a czasem także ciśnienia atmosferycznego. Komponent czujnika temperatury to termistor o ujemnym współczynniku temperaturowym (NTC), czyli termistor, którego opór maleje wraz ze wzrostem temperatury.

Jest to czujnik cyfrowy, więc posiada wbudowany przetwornik ADC, który generuje sygnał cyfrowy zawierający dane o temperaturze i wilgotności, które mikroprocesor może odczytać.

### Podłącz czujnik temperatury

Czujnik temperatury Grove można podłączyć do cyfrowego portu Wio Terminal.

#### Zadanie - podłącz czujnik temperatury

Podłącz czujnik temperatury.

![Czujnik temperatury Grove](../../../../../translated_images/pl/grove-dht11.07f8eafceee17004.webp)

1. Włóż jeden koniec kabla Grove do gniazda w czujniku wilgotności i temperatury. Kabel pasuje tylko w jednym kierunku.

1. Gdy Wio Terminal jest odłączony od komputera lub innego źródła zasilania, podłącz drugi koniec kabla Grove do prawego gniazda Grove w Wio Terminal, patrząc na ekran. Jest to gniazdo najbardziej oddalone od przycisku zasilania.

![Czujnik temperatury Grove podłączony do prawego gniazda](../../../../../translated_images/pl/wio-temperature-sensor.2934928f38c7f79a.webp)

## Programowanie czujnika temperatury

Teraz możesz zaprogramować Wio Terminal, aby korzystał z podłączonego czujnika temperatury.

### Zadanie - zaprogramuj czujnik temperatury

Zaprogramuj urządzenie.

1. Utwórz nowy projekt Wio Terminal w PlatformIO. Nazwij ten projekt `temperature-sensor`. Dodaj kod w funkcji `setup`, aby skonfigurować port szeregowy.

    > ⚠️ Możesz odwołać się do [instrukcji tworzenia projektu PlatformIO w projekcie 1, lekcji 1, jeśli potrzebujesz](../../../1-getting-started/lessons/1-introduction-to-iot/wio-terminal.md#create-a-platformio-project).

1. Dodaj zależność biblioteki dla biblioteki Seeed Grove Humidity and Temperature sensor do pliku `platformio.ini` projektu:

    ```ini
    lib_deps =
        seeed-studio/Grove Temperature And Humidity Sensor @ 1.0.1
    ```

    > ⚠️ Możesz odwołać się do [instrukcji dodawania bibliotek do projektu PlatformIO w projekcie 1, lekcji 4, jeśli potrzebujesz](../../../1-getting-started/lessons/4-connect-internet/wio-terminal-mqtt.md#install-the-wifi-and-mqtt-arduino-libraries).

1. Dodaj następujące dyrektywy `#include` na początku pliku, pod istniejącym `#include <Arduino.h>`:

    ```cpp
    #include <DHT.h>
    #include <SPI.h>
    ```

    Importuje to pliki potrzebne do interakcji z czujnikiem. Plik nagłówkowy `DHT.h` zawiera kod dla samego czujnika, a dodanie nagłówka `SPI.h` zapewnia, że kod potrzebny do komunikacji z czujnikiem zostanie uwzględniony podczas kompilacji aplikacji.

1. Przed funkcją `setup` zadeklaruj czujnik DHT:

    ```cpp
    DHT dht(D0, DHT11);
    ```

    Deklaruje to instancję klasy `DHT`, która zarządza **D**igitalnym **H**umidity i **T**emperature sensorem. Czujnik jest podłączony do portu `D0`, prawego gniazda Grove w Wio Terminal. Drugi parametr informuje kod, że używany czujnik to *DHT11* - biblioteka, której używasz, obsługuje inne warianty tego czujnika.

1. W funkcji `setup` dodaj kod do konfiguracji połączenia szeregowego:

    ```cpp
    void setup()
    {
        Serial.begin(9600);
    
        while (!Serial)
            ; // Wait for Serial to be ready
    
        delay(1000);
    }
    ```

1. Na końcu funkcji `setup`, po ostatnim `delay`, dodaj wywołanie uruchamiające czujnik DHT:

    ```cpp
    dht.begin();
    ```

1. W funkcji `loop` dodaj kod wywołujący czujnik i drukujący temperaturę na port szeregowy:

    ```cpp
    void loop()
    {
        float temp_hum_val[2] = {0};
        dht.readTempAndHumidity(temp_hum_val);
        Serial.print("Temperature: ");
        Serial.print(temp_hum_val[1]);
        Serial.println ("°C");
    
        delay(10000);
    }
    ```

    Ten kod deklaruje pustą tablicę z 2 liczbami zmiennoprzecinkowymi i przekazuje ją do wywołania `readTempAndHumidity` na instancji `DHT`. Wywołanie to wypełnia tablicę dwoma wartościami - wilgotność trafia do pierwszego elementu tablicy (0), a temperatura do drugiego elementu (1).

    Temperatura jest odczytywana z drugiego elementu tablicy i drukowana na port szeregowy.

    > 🇺🇸 Temperatura jest odczytywana w stopniach Celsjusza. Dla Amerykanów, aby przeliczyć ją na stopnie Fahrenheita, podziel wartość w Celsjuszach przez 5, pomnóż przez 9, a następnie dodaj 32. Na przykład odczyt temperatury 20°C przelicza się na ((20/5)*9) + 32 = 68°F.

1. Zbuduj i wgraj kod na Wio Terminal.

    > ⚠️ Możesz odwołać się do [instrukcji tworzenia projektu PlatformIO w projekcie 1, lekcji 1, jeśli potrzebujesz](../../../1-getting-started/lessons/1-introduction-to-iot/wio-terminal.md#write-the-hello-world-app).

1. Po wgraniu możesz monitorować temperaturę za pomocą monitora szeregowego:

    ```output
    > Executing task: platformio device monitor <
    
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1201  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Temperature: 25.00°C
    Temperature: 25.00°C
    Temperature: 25.00°C
    Temperature: 24.00°C
    ```

> 💁 Ten kod znajdziesz w folderze [code-temperature/wio-terminal](../../../../../2-farm/lessons/1-predict-plant-growth/code-temperature/wio-terminal).

😀 Twój program do obsługi czujnika temperatury działa poprawnie!

**Zastrzeżenie**:  
Ten dokument został przetłumaczony za pomocą usługi tłumaczenia AI [Co-op Translator](https://github.com/Azure/co-op-translator). Chociaż dokładamy wszelkich starań, aby zapewnić poprawność tłumaczenia, prosimy pamiętać, że automatyczne tłumaczenia mogą zawierać błędy lub nieścisłości. Oryginalny dokument w jego rodzimym języku powinien być uznawany za autorytatywne źródło. W przypadku informacji o kluczowym znaczeniu zaleca się skorzystanie z profesjonalnego tłumaczenia przez człowieka. Nie ponosimy odpowiedzialności za jakiekolwiek nieporozumienia lub błędne interpretacje wynikające z użycia tego tłumaczenia.