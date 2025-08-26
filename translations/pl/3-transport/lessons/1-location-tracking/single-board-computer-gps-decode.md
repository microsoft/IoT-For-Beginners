<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "cbb8c285bc64c5192fae3368fb5077d2",
  "translation_date": "2025-08-26T07:32:36+00:00",
  "source_file": "3-transport/lessons/1-location-tracking/single-board-computer-gps-decode.md",
  "language_code": "pl"
}
-->
# Dekodowanie danych GPS - Wirtualny sprzęt IoT i Raspberry Pi

W tej części lekcji będziesz dekodować wiadomości NMEA odczytane z czujnika GPS przez Raspberry Pi lub Wirtualne Urządzenie IoT, aby wyodrębnić szerokość i długość geograficzną.

## Dekodowanie danych GPS

Po odczytaniu surowych danych NMEA z portu szeregowego można je zdekodować za pomocą biblioteki NMEA typu open source.

### Zadanie - dekodowanie danych GPS

Zaprogramuj urządzenie do dekodowania danych GPS.

1. Otwórz projekt aplikacji `gps-sensor`, jeśli nie jest jeszcze otwarty.

1. Zainstaluj pakiet Pip `pynmea2`. Ten pakiet zawiera kod do dekodowania wiadomości NMEA.

    ```sh
    pip3 install pynmea2
    ```

1. Dodaj poniższy kod do sekcji importów w pliku `app.py`, aby zaimportować moduł `pynmea2`:

    ```python
    import pynmea2
    ```

1. Zastąp zawartość funkcji `print_gps_data` następującym kodem:

    ```python
    msg = pynmea2.parse(line)
    if msg.sentence_type == 'GGA':
        lat = pynmea2.dm_to_sd(msg.lat)
        lon = pynmea2.dm_to_sd(msg.lon)

        if msg.lat_dir == 'S':
            lat = lat * -1

        if msg.lon_dir == 'W':
            lon = lon * -1

        print(f'{lat},{lon} - from {msg.num_sats} satellites')
    ```

    Ten kod użyje biblioteki `pynmea2` do parsowania linii odczytanej z portu szeregowego UART.

    Jeśli typ zdania wiadomości to `GGA`, oznacza to wiadomość o ustaleniu pozycji, która zostanie przetworzona. Wartości szerokości i długości geograficznej są odczytywane z wiadomości i konwertowane na stopnie dziesiętne z formatu NMEA `(d)ddmm.mmmm`. Funkcja `dm_to_sd` wykonuje tę konwersję.

    Następnie sprawdzany jest kierunek szerokości geograficznej, a jeśli szerokość geograficzna jest południowa, wartość zostaje przekształcona na liczbę ujemną. Podobnie w przypadku długości geograficznej, jeśli jest zachodnia, zostaje przekształcona na liczbę ujemną.

    Na koniec współrzędne są drukowane na konsoli, wraz z liczbą satelitów użytych do ustalenia lokalizacji.

1. Uruchom kod. Jeśli używasz wirtualnego urządzenia IoT, upewnij się, że aplikacja CounterFit działa i dane GPS są wysyłane.

    ```output
    pi@raspberrypi:~/gps-sensor $ python3 app.py 
    47.6423109,-122.1390293 - from 3 satellites
    ```

> 💁 Ten kod znajdziesz w folderze [code-gps-decode/virtual-device](../../../../../3-transport/lessons/1-location-tracking/code-gps-decode/virtual-device) lub [code-gps-decode/pi](../../../../../3-transport/lessons/1-location-tracking/code-gps-decode/pi).

😀 Twój program czujnika GPS z dekodowaniem danych zakończył się sukcesem!

**Zastrzeżenie**:  
Ten dokument został przetłumaczony za pomocą usługi tłumaczenia AI [Co-op Translator](https://github.com/Azure/co-op-translator). Chociaż dokładamy wszelkich starań, aby zapewnić poprawność tłumaczenia, prosimy pamiętać, że automatyczne tłumaczenia mogą zawierać błędy lub nieścisłości. Oryginalny dokument w jego rodzimym języku powinien być uznawany za autorytatywne źródło. W przypadku informacji o kluczowym znaczeniu zaleca się skorzystanie z profesjonalnego tłumaczenia przez człowieka. Nie ponosimy odpowiedzialności za jakiekolwiek nieporozumienia lub błędne interpretacje wynikające z użycia tego tłumaczenia.