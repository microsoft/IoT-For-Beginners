# Pomiar wilgotności gleby - Wio Terminal

W tej części lekcji dodasz pojemnościowy czujnik wilgotności gleby do swojego Wio Terminal i odczytasz z niego wartości.

## Sprzęt

Wio Terminal potrzebuje pojemnościowego czujnika wilgotności gleby.

Czujnik, którego użyjesz, to [Pojemnościowy Czujnik Wilgotności Gleby](https://www.seeedstudio.com/Grove-Capacitive-Moisture-Sensor-Corrosion-Resistant.html), który mierzy wilgotność gleby poprzez wykrywanie jej pojemności, właściwości zmieniającej się wraz ze zmianą wilgotności gleby. Wraz ze wzrostem wilgotności gleby napięcie maleje.

Jest to czujnik analogowy, który łączy się z analogowymi pinami Wio Terminal, wykorzystując wbudowany przetwornik ADC do generowania wartości w zakresie od 0 do 1023.

### Podłącz czujnik wilgotności gleby

Czujnik wilgotności gleby Grove można podłączyć do konfigurowalnego portu analogowo-cyfrowego Wio Terminal.

#### Zadanie - podłącz czujnik wilgotności gleby

Podłącz czujnik wilgotności gleby.

![Czujnik wilgotności gleby Grove](../../../../../translated_images/pl/grove-capacitive-soil-moisture-sensor.e7f0776cce30e78b.webp)

1. Włóż jeden koniec kabla Grove do gniazda na czujniku wilgotności gleby. Kabel wejdzie tylko w jednym kierunku.

1. Przy odłączonym Wio Terminal od komputera lub innego źródła zasilania, podłącz drugi koniec kabla Grove do prawego gniazda Grove na Wio Terminal, patrząc na ekran. Jest to gniazdo najbardziej oddalone od przycisku zasilania.

![Czujnik wilgotności gleby Grove podłączony do prawego gniazda](../../../../../translated_images/pl/wio-soil-moisture-sensor.46919b61c3f6cb74.webp)

1. Włóż czujnik wilgotności gleby do gleby. Czujnik ma linię oznaczającą "najwyższą pozycję" - białą linię na czujniku. Włóż czujnik do gleby do tej linii, ale nie dalej.

![Czujnik wilgotności gleby Grove w glebie](../../../../../translated_images/pl/soil-moisture-sensor-in-soil.bfad91002bda5e96.webp)

1. Teraz możesz podłączyć Wio Terminal do komputera.

## Programowanie czujnika wilgotności gleby

Wio Terminal może teraz zostać zaprogramowany do korzystania z podłączonego czujnika wilgotności gleby.

### Zadanie - zaprogramuj czujnik wilgotności gleby

Zaprogramuj urządzenie.

1. Utwórz nowy projekt Wio Terminal za pomocą PlatformIO. Nazwij ten projekt `soil-moisture-sensor`. Dodaj kod w funkcji `setup`, aby skonfigurować port szeregowy.

    > ⚠️ Możesz odwołać się do [instrukcji tworzenia projektu PlatformIO w projekcie 1, lekcji 1, jeśli potrzebujesz](../../../1-getting-started/lessons/1-introduction-to-iot/wio-terminal.md#create-a-platformio-project).

1. Nie ma biblioteki dla tego czujnika, zamiast tego możesz odczytać dane z pinu analogowego za pomocą wbudowanej funkcji Arduino [`analogRead`](https://www.arduino.cc/reference/en/language/functions/analog-io/analogread/). Zacznij od skonfigurowania pinu analogowego jako wejścia, aby można było odczytywać z niego wartości, dodając poniższy kod do funkcji `setup`.

    ```cpp
    pinMode(A0, INPUT);
    ```

    Ten kod ustawia pin `A0`, połączony pin analogowo-cyfrowy, jako pin wejściowy, z którego można odczytywać napięcie.

1. Dodaj poniższy kod do funkcji `loop`, aby odczytać napięcie z tego pinu:

    ```cpp
    int soil_moisture = analogRead(A0);
    ```

1. Pod tym kodem dodaj poniższy kod, aby wydrukować wartość na port szeregowy:

    ```cpp
    Serial.print("Soil Moisture: ");
    Serial.println(soil_moisture);
    ```

1. Na końcu dodaj opóźnienie wynoszące 10 sekund:

    ```cpp
    delay(10000);
    ```

1. Zbuduj i wgraj kod na Wio Terminal.

    > ⚠️ Możesz odwołać się do [instrukcji tworzenia projektu PlatformIO w projekcie 1, lekcji 1, jeśli potrzebujesz](../../../1-getting-started/lessons/1-introduction-to-iot/wio-terminal.md#write-the-hello-world-app).

1. Po wgraniu kodu możesz monitorować wilgotność gleby za pomocą monitora szeregowego. Dodaj trochę wody do gleby lub wyjmij czujnik z gleby i zobacz, jak zmieniają się wartości.

    ```output
    > Executing task: platformio device monitor <
    
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1201  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Soil Moisture: 526
    Soil Moisture: 529
    Soil Moisture: 521
    Soil Moisture: 494
    Soil Moisture: 454
    Soil Moisture: 456
    Soil Moisture: 395
    Soil Moisture: 388
    Soil Moisture: 394
    Soil Moisture: 391
    ```

    W powyższym przykładzie wyjścia możesz zobaczyć, jak napięcie spada po dodaniu wody.

> 💁 Ten kod znajdziesz w folderze [code/wio-terminal](../../../../../2-farm/lessons/2-detect-soil-moisture/code/wio-terminal).

😀 Twój program do czujnika wilgotności gleby zakończył się sukcesem!

**Zastrzeżenie**:  
Ten dokument został przetłumaczony za pomocą usługi tłumaczenia AI [Co-op Translator](https://github.com/Azure/co-op-translator). Chociaż staramy się zapewnić dokładność, prosimy pamiętać, że automatyczne tłumaczenia mogą zawierać błędy lub nieścisłości. Oryginalny dokument w jego rodzimym języku powinien być uznawany za wiarygodne źródło. W przypadku informacji krytycznych zaleca się skorzystanie z profesjonalnego tłumaczenia przez człowieka. Nie ponosimy odpowiedzialności za jakiekolwiek nieporozumienia lub błędne interpretacje wynikające z użycia tego tłumaczenia.