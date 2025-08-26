<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "fbbcf96a9b63ccd661db98bbf854bb06",
  "translation_date": "2025-08-26T07:33:26+00:00",
  "source_file": "3-transport/lessons/1-location-tracking/wio-terminal-gps-decode.md",
  "language_code": "pl"
}
-->
# Dekodowanie danych GPS - Wio Terminal

W tej części lekcji zdekodujesz wiadomości NMEA odczytane z czujnika GPS przez Wio Terminal i wyodrębnisz szerokość oraz długość geograficzną.

## Dekodowanie danych GPS

Po odczytaniu surowych danych NMEA z portu szeregowego można je zdekodować za pomocą otwartoźródłowej biblioteki NMEA.

### Zadanie - dekodowanie danych GPS

Zaprogramuj urządzenie do dekodowania danych GPS.

1. Otwórz projekt aplikacji `gps-sensor`, jeśli nie jest jeszcze otwarty.

1. Dodaj zależność biblioteki [TinyGPSPlus](https://github.com/mikalhart/TinyGPSPlus) do pliku `platformio.ini` projektu. Ta biblioteka zawiera kod do dekodowania danych NMEA.

    ```ini
    lib_deps =
        mikalhart/TinyGPSPlus @ 1.0.2
    ```

1. W pliku `main.cpp` dodaj dyrektywę include dla biblioteki TinyGPSPlus:

    ```cpp
    #include <TinyGPS++.h>
    ```

1. Poniżej deklaracji `Serial3` zadeklaruj obiekt TinyGPSPlus do przetwarzania zdań NMEA:

    ```cpp
    TinyGPSPlus gps;
    ```

1. Zmień zawartość funkcji `printGPSData` na następującą:

    ```cpp
    if (gps.encode(Serial3.read()))
    {
        if (gps.location.isValid())
        {
            Serial.print(gps.location.lat(), 6);
            Serial.print(F(","));
            Serial.print(gps.location.lng(), 6);
            Serial.print(" - from ");
            Serial.print(gps.satellites.value());
            Serial.println(" satellites");
        }
    }
    ```

    Ten kod odczytuje kolejny znak z portu szeregowego UART do dekodera NMEA `gps`. Po każdym znaku sprawdza, czy dekoder odczytał poprawne zdanie, a następnie sprawdza, czy odczytał poprawną lokalizację. Jeśli lokalizacja jest poprawna, wysyła ją do monitora szeregowego wraz z liczbą satelitów, które przyczyniły się do tego ustalenia.

1. Zbuduj i wgraj kod na Wio Terminal.

1. Po wgraniu możesz monitorować dane lokalizacji GPS za pomocą monitora szeregowego.

    ```output
    > Executing task: platformio device monitor <
    
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1201  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    47.6423109,-122.1390293 - from 3 satellites
    ```

> 💁 Ten kod znajdziesz w folderze [code-gps-decode/wio-terminal](../../../../../3-transport/lessons/1-location-tracking/code-gps-decode/wio-terminal).

😀 Twój program czujnika GPS z dekodowaniem danych zakończył się sukcesem!

**Zastrzeżenie**:  
Ten dokument został przetłumaczony za pomocą usługi tłumaczenia AI [Co-op Translator](https://github.com/Azure/co-op-translator). Chociaż dokładamy wszelkich starań, aby tłumaczenie było precyzyjne, prosimy pamiętać, że automatyczne tłumaczenia mogą zawierać błędy lub nieścisłości. Oryginalny dokument w jego rodzimym języku powinien być uznawany za autorytatywne źródło. W przypadku informacji o kluczowym znaczeniu zaleca się skorzystanie z profesjonalnego tłumaczenia przez człowieka. Nie ponosimy odpowiedzialności za jakiekolwiek nieporozumienia lub błędne interpretacje wynikające z użycia tego tłumaczenia.