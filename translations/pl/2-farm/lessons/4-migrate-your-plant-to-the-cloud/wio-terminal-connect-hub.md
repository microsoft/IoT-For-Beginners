<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "28320305a35ea3bc59c41fe146a2e6ed",
  "translation_date": "2025-08-26T06:54:59+00:00",
  "source_file": "2-farm/lessons/4-migrate-your-plant-to-the-cloud/wio-terminal-connect-hub.md",
  "language_code": "pl"
}
-->
# Podłącz swoje urządzenie IoT do chmury - Wio Terminal

W tej części lekcji podłączysz swój Wio Terminal do IoT Hub, aby wysyłać dane telemetryczne i odbierać polecenia.

## Podłącz swoje urządzenie do IoT Hub

Kolejnym krokiem jest podłączenie urządzenia do IoT Hub.

### Zadanie - podłącz do IoT Hub

1. Otwórz projekt `soil-moisture-sensor` w VS Code.

1. Otwórz plik `platformio.ini`. Usuń zależność od biblioteki `knolleary/PubSubClient`. Była ona używana do połączenia z publicznym brokerem MQTT, ale nie jest potrzebna do połączenia z IoT Hub.

1. Dodaj następujące zależności bibliotek:

    ```ini
    seeed-studio/Seeed Arduino RTC @ 2.0.0
    arduino-libraries/AzureIoTHub @ 1.6.0
    azure/AzureIoTUtility @ 1.6.1
    azure/AzureIoTProtocol_MQTT @ 1.6.0
    azure/AzureIoTProtocol_HTTP @ 1.6.0
    azure/AzureIoTSocket_WiFi @ 1.0.2
    ```

    Biblioteka `Seeed Arduino RTC` dostarcza kod do obsługi zegara czasu rzeczywistego w Wio Terminal, który jest używany do śledzenia czasu. Pozostałe biblioteki umożliwiają Twojemu urządzeniu IoT połączenie z IoT Hub.

1. Dodaj następujący wpis na końcu pliku `platformio.ini`:

    ```ini
    build_flags =
        -DDONT_USE_UPLOADTOBLOB
    ```

    Ustawia to flagę kompilatora, która jest wymagana podczas kompilacji kodu Arduino IoT Hub.

1. Otwórz plik nagłówkowy `config.h`. Usuń wszystkie ustawienia MQTT i dodaj następującą stałą dla ciągu połączenia urządzenia:

    ```cpp
    // IoT Hub settings
    const char *CONNECTION_STRING = "<connection string>";
    ```

    Zamień `<connection string>` na ciąg połączenia dla Twojego urządzenia, który skopiowałeś wcześniej.

1. Połączenie z IoT Hub wykorzystuje token oparty na czasie. Oznacza to, że urządzenie IoT musi znać aktualny czas. W przeciwieństwie do systemów operacyjnych takich jak Windows, macOS czy Linux, mikrokontrolery nie synchronizują automatycznie aktualnego czasu przez Internet. Oznacza to, że musisz dodać kod do pobrania aktualnego czasu z serwera [NTP](https://wikipedia.org/wiki/Network_Time_Protocol). Po pobraniu czasu można go zapisać w zegarze czasu rzeczywistego w Wio Terminal, co pozwala na uzyskanie poprawnego czasu w późniejszym terminie, o ile urządzenie nie straci zasilania. Dodaj nowy plik o nazwie `ntp.h` z następującym kodem:

    ```cpp
    #pragma once
    
    #include "DateTime.h"
    #include <time.h>
    #include "samd/NTPClientAz.h"
    #include <sys/time.h>

    static void initTime()
    {
        WiFiUDP _udp;
        time_t epochTime = (time_t)-1;
        NTPClientAz ntpClient;

        ntpClient.begin();

        while (true)
        {
            epochTime = ntpClient.getEpochTime("0.pool.ntp.org");

            if (epochTime == (time_t)-1)
            {
                Serial.println("Fetching NTP epoch time failed! Waiting 2 seconds to retry.");
                delay(2000);
            }
            else
            {
                Serial.print("Fetched NTP epoch time is: ");

                char buff[32];
                sprintf(buff, "%.f", difftime(epochTime, (time_t)0));
                Serial.println(buff);
                break;
            }
        }

        ntpClient.end();

        struct timeval tv;
        tv.tv_sec = epochTime;
        tv.tv_usec = 0;

        settimeofday(&tv, NULL);
    }
    ```

    Szczegóły tego kodu wykraczają poza zakres tej lekcji. Definiuje on funkcję `initTime`, która pobiera aktualny czas z serwera NTP i ustawia zegar w Wio Terminal.

1. Otwórz plik `main.cpp` i usuń cały kod MQTT, w tym nagłówek `PubSubClient.h`, deklarację zmiennej `PubSubClient`, metody `reconnectMQTTClient` i `createMQTTClient`, oraz wszelkie wywołania tych zmiennych i metod. Plik ten powinien zawierać jedynie kod do połączenia z WiFi, pobrania wilgotności gleby i utworzenia dokumentu JSON z tymi danymi.

1. Dodaj następujące dyrektywy `#include` na początku pliku `main.cpp`, aby dołączyć nagłówki bibliotek IoT Hub oraz ustawiania czasu:

    ```cpp
    #include <AzureIoTHub.h>
    #include <AzureIoTProtocol_MQTT.h>
    #include <iothubtransportmqtt.h>
    #include "ntp.h"
    ```

1. Dodaj następujące wywołanie na końcu funkcji `setup`, aby ustawić aktualny czas:

    ```cpp
    initTime();
    ```

1. Dodaj następującą deklarację zmiennej na początku pliku, tuż poniżej dyrektyw include:

    ```cpp
    IOTHUB_DEVICE_CLIENT_LL_HANDLE _device_ll_handle;
    ```

    Deklaruje to `IOTHUB_DEVICE_CLIENT_LL_HANDLE`, uchwyt do połączenia z IoT Hub.

1. Poniżej tego dodaj następujący kod:

    ```cpp
    static void connectionStatusCallback(IOTHUB_CLIENT_CONNECTION_STATUS result, IOTHUB_CLIENT_CONNECTION_STATUS_REASON reason, void *user_context)
    {
        if (result == IOTHUB_CLIENT_CONNECTION_AUTHENTICATED)
        {
            Serial.println("The device client is connected to iothub");
        }
        else
        {
            Serial.println("The device client has been disconnected");
        }
    }
    ```

    Deklaruje to funkcję zwrotną, która będzie wywoływana, gdy status połączenia z IoT Hub ulegnie zmianie, np. po połączeniu lub rozłączeniu. Status jest wysyłany na port szeregowy.

1. Poniżej tego dodaj funkcję do połączenia z IoT Hub:

    ```cpp
    void connectIoTHub()
    {
        IoTHub_Init();
    
        _device_ll_handle = IoTHubDeviceClient_LL_CreateFromConnectionString(CONNECTION_STRING, MQTT_Protocol);
        
        if (_device_ll_handle == NULL)
        {
            Serial.println("Failure creating Iothub device. Hint: Check your connection string.");
            return;
        }
    
        IoTHubDeviceClient_LL_SetConnectionStatusCallback(_device_ll_handle, connectionStatusCallback, NULL);
    }
    ```

    Kod ten inicjalizuje bibliotekę IoT Hub, a następnie tworzy połączenie przy użyciu ciągu połączenia zdefiniowanego w pliku nagłówkowym `config.h`. Połączenie to opiera się na MQTT. Jeśli połączenie się nie powiedzie, informacja o tym zostanie wysłana na port szeregowy - jeśli zobaczysz to w wyjściu, sprawdź ciąg połączenia. Na końcu ustawiana jest funkcja zwrotna statusu połączenia.

1. Wywołaj tę funkcję w funkcji `setup` poniżej wywołania `initTime`:

    ```cpp
    connectIoTHub();
    ```

1. Podobnie jak w przypadku klienta MQTT, ten kod działa na jednym wątku, więc potrzebuje czasu na przetwarzanie wiadomości wysyłanych przez hub i do huba. Dodaj następujący kod na początku funkcji `loop`, aby to zrobić:

    ```cpp
    IoTHubDeviceClient_LL_DoWork(_device_ll_handle);
    ```

1. Zbuduj i wgraj ten kod. Zobaczysz połączenie w monitorze szeregowym:

    ```output
    Connecting to WiFi..
    Connected!
    Fetched NTP epoch time is: 1619983687
    Sending telemetry {"soil_moisture":391}
    The device client is connected to iothub
    ```

    W wyjściu zobaczysz pobieranie czasu NTP, a następnie łączenie klienta urządzenia. Połączenie może zająć kilka sekund, więc możesz zobaczyć wilgotność gleby w wyjściu, podczas gdy urządzenie się łączy.

    > 💁 Możesz przekonwertować czas UNIX z NTP na bardziej czytelną wersję, korzystając z witryny internetowej, takiej jak [unixtimestamp.com](https://www.unixtimestamp.com)

## Wysyłanie telemetrii

Teraz, gdy Twoje urządzenie jest podłączone, możesz wysyłać dane telemetryczne do IoT Hub zamiast do brokera MQTT.

### Zadanie - wysyłanie telemetrii

1. Dodaj następującą funkcję powyżej funkcji `setup`:

    ```cpp
    void sendTelemetry(const char *telemetry)
    {
        IOTHUB_MESSAGE_HANDLE message_handle = IoTHubMessage_CreateFromString(telemetry);
        IoTHubDeviceClient_LL_SendEventAsync(_device_ll_handle, message_handle, NULL, NULL);
        IoTHubMessage_Destroy(message_handle);
    }
    ```

    Kod ten tworzy wiadomość IoT Hub z ciągu przekazanego jako parametr, wysyła ją do huba, a następnie czyści obiekt wiadomości.

1. Wywołaj ten kod w funkcji `loop`, zaraz po linii, w której telemetria jest wysyłana na port szeregowy:

    ```cpp
    sendTelemetry(telemetry.c_str());
    ```

## Obsługa poleceń

Twoje urządzenie musi obsługiwać polecenie z kodu serwera do sterowania przekaźnikiem. Jest ono wysyłane jako żądanie metody bezpośredniej.

## Zadanie - obsługa żądania metody bezpośredniej

1. Dodaj następujący kod przed funkcją `connectIoTHub`:

    ```cpp
    int directMethodCallback(const char *method_name, const unsigned char *payload, size_t size, unsigned char **response, size_t *response_size, void *userContextCallback)
    {
        Serial.printf("Direct method received %s\r\n", method_name);
    
        if (strcmp(method_name, "relay_on") == 0)
        {
            digitalWrite(PIN_WIRE_SCL, HIGH);
        }
        else if (strcmp(method_name, "relay_off") == 0)
        {
            digitalWrite(PIN_WIRE_SCL, LOW);
        }
    }
    ```

    Kod ten definiuje metodę zwrotną, którą biblioteka IoT Hub może wywołać, gdy otrzyma żądanie metody bezpośredniej. Metoda, która jest żądana, jest przesyłana w parametrze `method_name`. Funkcja ta wypisuje wywołaną metodę na port szeregowy, a następnie włącza lub wyłącza przekaźnik w zależności od nazwy metody.

    > 💁 Można to również zaimplementować w ramach jednej metody bezpośredniej, przekazując pożądany stan przekaźnika w ładunku, który można przesłać z żądaniem metody i który jest dostępny w parametrze `payload`.

1. Dodaj następujący kod na końcu funkcji `directMethodCallback`:

    ```cpp
    char resultBuff[16];
    sprintf(resultBuff, "{\"Result\":\"\"}");
    *response_size = strlen(resultBuff);
    *response = (unsigned char *)malloc(*response_size);
    memcpy(*response, resultBuff, *response_size);

    return IOTHUB_CLIENT_OK;
    ```

    Żądania metod bezpośrednich wymagają odpowiedzi, która składa się z dwóch części - odpowiedzi w formie tekstu oraz kodu zwrotnego. Kod ten utworzy wynik w postaci następującego dokumentu JSON:

    ```JSON
    {
        "Result": ""
    }
    ```

    Następnie jest on kopiowany do parametru `response`, a rozmiar tej odpowiedzi jest ustawiany w parametrze `response_size`. Kod ten zwraca `IOTHUB_CLIENT_OK`, aby pokazać, że metoda została obsłużona poprawnie.

1. Podłącz funkcję zwrotną, dodając następujący kod na końcu funkcji `connectIoTHub`:

    ```cpp
    IoTHubClient_LL_SetDeviceMethodCallback(_device_ll_handle, directMethodCallback, NULL);
    ```

1. Funkcja `loop` wywoła funkcję `IoTHubDeviceClient_LL_DoWork`, aby przetwarzać zdarzenia wysyłane przez IoT Hub. Funkcja ta jest wywoływana co 10 sekund z powodu `delay`, co oznacza, że metody bezpośrednie są przetwarzane tylko co 10 sekund. Aby to usprawnić, 10-sekundowe opóźnienie można zaimplementować jako wiele krótszych opóźnień, wywołując `IoTHubDeviceClient_LL_DoWork` za każdym razem. Aby to zrobić, dodaj następujący kod powyżej funkcji `loop`:

    ```cpp
    void work_delay(int delay_time)
    {
        int current = 0;
        do
        {
            IoTHubDeviceClient_LL_DoWork(_device_ll_handle);
            delay(100);
            current += 100;
        } while (current < delay_time);
    }
    ```

    Kod ten będzie wielokrotnie wywoływał `IoTHubDeviceClient_LL_DoWork` i opóźniał o 100 ms za każdym razem. Będzie to robił tyle razy, ile potrzeba, aby opóźnić o czas podany w parametrze `delay_time`. Oznacza to, że urządzenie czeka maksymalnie 100 ms na przetworzenie żądań metod bezpośrednich.

1. W funkcji `loop` usuń wywołanie `IoTHubDeviceClient_LL_DoWork` i zastąp wywołanie `delay(10000)` następującym kodem, aby wywołać nową funkcję:

    ```cpp
    work_delay(10000);
    ```

> 💁 Kod ten znajdziesz w folderze [code/wio-terminal](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud/code/wio-terminal).

😀 Twój program czujnika wilgotności gleby jest podłączony do IoT Hub!

**Zastrzeżenie**:  
Ten dokument został przetłumaczony za pomocą usługi tłumaczenia AI [Co-op Translator](https://github.com/Azure/co-op-translator). Chociaż dokładamy wszelkich starań, aby tłumaczenie było precyzyjne, prosimy pamiętać, że automatyczne tłumaczenia mogą zawierać błędy lub nieścisłości. Oryginalny dokument w jego języku źródłowym powinien być uznawany za autorytatywne źródło. W przypadku informacji o kluczowym znaczeniu zaleca się skorzystanie z profesjonalnego tłumaczenia przez człowieka. Nie ponosimy odpowiedzialności za jakiekolwiek nieporozumienia lub błędne interpretacje wynikające z użycia tego tłumaczenia.