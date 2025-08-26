<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "90fb93446e03c38f3c0e4009c2471906",
  "translation_date": "2025-08-26T07:00:43+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/single-board-computer-mqtt.md",
  "language_code": "pl"
}
-->
# Steruj swoją lampką nocną przez Internet - Wirtualny sprzęt IoT i Raspberry Pi

Urządzenie IoT musi zostać zaprogramowane tak, aby komunikowało się z *test.mosquitto.org* za pomocą MQTT, wysyłając dane telemetryczne z odczytem czujnika światła oraz odbierając polecenia do sterowania diodą LED.

W tej części lekcji połączysz swoje Raspberry Pi lub wirtualne urządzenie IoT z brokerem MQTT.

## Zainstaluj pakiet klienta MQTT

Aby komunikować się z brokerem MQTT, musisz zainstalować bibliotekę MQTT jako pakiet pip, albo na swoim Raspberry Pi, albo w środowisku wirtualnym, jeśli korzystasz z wirtualnego urządzenia.

### Zadanie

Zainstaluj pakiet pip

1. Otwórz projekt lampki nocnej w VS Code.

1. Jeśli korzystasz z wirtualnego urządzenia IoT, upewnij się, że terminal działa w środowisku wirtualnym. Jeśli używasz Raspberry Pi, nie będziesz korzystać ze środowiska wirtualnego.

1. Uruchom następujące polecenie, aby zainstalować pakiet pip MQTT:

    ```sh
    pip3 install paho-mqtt
    ```

## Programowanie urządzenia

Urządzenie jest gotowe do zaprogramowania.

### Zadanie

Napisz kod urządzenia.

1. Dodaj następujący import na początku pliku `app.py`:

    ```python
    import paho.mqtt.client as mqtt
    ```

    Biblioteka `paho.mqtt.client` pozwala Twojej aplikacji komunikować się za pomocą MQTT.

1. Dodaj następujący kod po definicjach czujnika światła i diody LED:

    ```python
    id = '<ID>'

    client_name = id + 'nightlight_client'
    ```

    Zamień `<ID>` na unikalny identyfikator, który będzie używany jako nazwa tego klienta urządzenia, a później jako nazwa tematów, które to urządzenie publikuje i subskrybuje. Broker *test.mosquitto.org* jest publiczny i używany przez wiele osób, w tym innych uczniów realizujących to zadanie. Posiadanie unikalnej nazwy klienta MQTT i nazw tematów zapewnia, że Twój kod nie będzie kolidował z kodem innych osób. Będziesz również potrzebować tego identyfikatora podczas tworzenia kodu serwera w dalszej części tego zadania.

    > 💁 Możesz użyć strony internetowej, takiej jak [GUIDGen](https://www.guidgen.com), aby wygenerować unikalny identyfikator.

    `client_name` to unikalna nazwa tego klienta MQTT na brokerze.

1. Dodaj następujący kod poniżej nowego kodu, aby utworzyć obiekt klienta MQTT i połączyć się z brokerem MQTT:

    ```python
    mqtt_client = mqtt.Client(client_name)
    mqtt_client.connect('test.mosquitto.org')
    
    mqtt_client.loop_start()

    print("MQTT connected!")
    ```

    Ten kod tworzy obiekt klienta, łączy się z publicznym brokerem MQTT i uruchamia pętlę przetwarzania, która działa w tle, nasłuchując wiadomości na dowolnych subskrybowanych tematach.

1. Uruchom kod w taki sam sposób, jak uruchamiałeś kod z poprzedniej części zadania. Jeśli korzystasz z wirtualnego urządzenia IoT, upewnij się, że aplikacja CounterFit jest uruchomiona, a czujnik światła i dioda LED zostały utworzone na odpowiednich pinach.

    ```output
    (.venv) ➜  nightlight python app.py 
    MQTT connected!
    Light level: 0
    Light level: 0
    ```

> 💁 Ten kod znajdziesz w folderze [code-mqtt/virtual-device](../../../../../1-getting-started/lessons/4-connect-internet/code-mqtt/virtual-device) lub [code-mqtt/pi](../../../../../1-getting-started/lessons/4-connect-internet/code-mqtt/pi).

😀 Udało Ci się pomyślnie połączyć swoje urządzenie z brokerem MQTT.

**Zastrzeżenie**:  
Ten dokument został przetłumaczony za pomocą usługi tłumaczenia AI [Co-op Translator](https://github.com/Azure/co-op-translator). Chociaż dokładamy wszelkich starań, aby tłumaczenie było precyzyjne, prosimy pamiętać, że automatyczne tłumaczenia mogą zawierać błędy lub nieścisłości. Oryginalny dokument w jego rodzimym języku powinien być uznawany za wiarygodne źródło. W przypadku informacji o kluczowym znaczeniu zaleca się skorzystanie z profesjonalnego tłumaczenia przez człowieka. Nie ponosimy odpowiedzialności za jakiekolwiek nieporozumienia lub błędne interpretacje wynikające z użycia tego tłumaczenia.