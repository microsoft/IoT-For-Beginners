<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "4efc74299e19f5d08f2f3f34451a11ba",
  "translation_date": "2025-08-26T06:42:27+00:00",
  "source_file": "2-farm/lessons/1-predict-plant-growth/single-board-computer-temp-publish.md",
  "language_code": "pl"
}
-->
# Publikowanie temperatury - Wirtualny sprzęt IoT i Raspberry Pi

W tej części lekcji opublikujesz wartości temperatury wykryte przez Raspberry Pi lub Wirtualne Urządzenie IoT za pomocą MQTT, aby mogły być później wykorzystane do obliczenia GDD.

## Publikowanie temperatury

Po odczytaniu temperatury można ją opublikować za pomocą MQTT do kodu 'serwera', który odczyta wartości i zapisze je, aby mogły być użyte do obliczeń GDD.

### Zadanie - publikowanie temperatury

Zaprogramuj urządzenie, aby publikowało dane o temperaturze.

1. Otwórz projekt aplikacji `temperature-sensor`, jeśli nie jest jeszcze otwarty.

1. Powtórz kroki, które wykonałeś w lekcji 4, aby połączyć się z MQTT i wysłać dane telemetryczne. Będziesz korzystać z tego samego publicznego brokera Mosquitto.

    Kroki te obejmują:

    - Dodanie pakietu pip dla MQTT
    - Dodanie kodu do połączenia z brokerem MQTT
    - Dodanie kodu do publikowania danych telemetrycznych

    > ⚠️ Zapoznaj się z [instrukcjami dotyczącymi łączenia się z MQTT](../../../1-getting-started/lessons/4-connect-internet/single-board-computer-mqtt.md) oraz [instrukcjami dotyczącymi wysyłania danych telemetrycznych](../../../1-getting-started/lessons/4-connect-internet/single-board-computer-telemetry.md) z lekcji 4, jeśli zajdzie taka potrzeba.

1. Upewnij się, że `client_name` odzwierciedla nazwę tego projektu:

    ```python
    client_name = id + 'temperature_sensor_client'
    ```

1. W przypadku danych telemetrycznych, zamiast wysyłać wartość światła, wyślij wartość temperatury odczytaną z czujnika DHT w właściwości dokumentu JSON o nazwie `temperature`:

    ```python
    _, temp = sensor.read()
    telemetry = json.dumps({'temperature' : temp})
    ```

1. Wartość temperatury nie musi być odczytywana zbyt często - nie zmienia się znacząco w krótkim czasie, więc ustaw `time.sleep` na 10 minut:

    ```cpp
    time.sleep(10 * 60);
    ```

    > 💁 Funkcja `sleep` przyjmuje czas w sekundach, więc aby ułatwić odczyt, wartość jest przekazywana jako wynik obliczenia. 60 sekund w minucie, więc 10 x (60 sekund w minucie) daje 10-minutowe opóźnienie.

1. Uruchom kod w taki sam sposób, jak uruchamiałeś kod z poprzedniej części zadania. Jeśli korzystasz z wirtualnego urządzenia IoT, upewnij się, że aplikacja CounterFit jest uruchomiona, a czujniki wilgotności i temperatury zostały utworzone na odpowiednich pinach.

    ```output
    pi@raspberrypi:~/temperature-sensor $ python3 app.py
    MQTT connected!
    Sending telemetry  {"temperature": 25}
    Sending telemetry  {"temperature": 25}
    ```

> 💁 Kod ten znajdziesz w folderze [code-publish-temperature/virtual-device](../../../../../2-farm/lessons/1-predict-plant-growth/code-publish-temperature/virtual-device) lub [code-publish-temperature/pi](../../../../../2-farm/lessons/1-predict-plant-growth/code-publish-temperature/pi).

😀 Pomyślnie opublikowałeś temperaturę jako dane telemetryczne z Twojego urządzenia.

**Zastrzeżenie**:  
Ten dokument został przetłumaczony za pomocą usługi tłumaczeniowej AI [Co-op Translator](https://github.com/Azure/co-op-translator). Chociaż dokładamy wszelkich starań, aby tłumaczenie było precyzyjne, prosimy pamiętać, że automatyczne tłumaczenia mogą zawierać błędy lub nieścisłości. Oryginalny dokument w jego rodzimym języku powinien być uznawany za autorytatywne źródło. W przypadku informacji o kluczowym znaczeniu zaleca się skorzystanie z profesjonalnego tłumaczenia przez człowieka. Nie ponosimy odpowiedzialności za jakiekolwiek nieporozumienia lub błędne interpretacje wynikające z użycia tego tłumaczenia.