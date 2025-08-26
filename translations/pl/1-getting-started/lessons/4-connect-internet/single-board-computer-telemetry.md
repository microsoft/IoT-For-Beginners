<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "1226517aae5f5b6f904434670394c688",
  "translation_date": "2025-08-26T06:58:07+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/single-board-computer-telemetry.md",
  "language_code": "pl"
}
-->
# Steruj swoją lampką nocną przez Internet - Wirtualny sprzęt IoT i Raspberry Pi

W tej części lekcji wyślesz dane telemetryczne dotyczące poziomu światła z Raspberry Pi lub wirtualnego urządzenia IoT do brokera MQTT.

## Wysyłanie danych telemetrycznych

Kolejnym krokiem jest utworzenie dokumentu JSON z danymi telemetrycznymi i wysłanie go do brokera MQTT.

### Zadanie

Wyślij dane telemetryczne do brokera MQTT.

1. Otwórz projekt lampki nocnej w VS Code.

1. Jeśli korzystasz z wirtualnego urządzenia IoT, upewnij się, że terminal działa w środowisku wirtualnym. Jeśli używasz Raspberry Pi, nie będziesz korzystać ze środowiska wirtualnego.

1. Dodaj następujący import na początku pliku `app.py`:

    ```python
    import json
    ```

    Biblioteka `json` jest używana do kodowania danych telemetrycznych jako dokument JSON.

1. Dodaj poniższy kod po deklaracji `client_name`:

    ```python
    client_telemetry_topic = id + '/telemetry'
    ```

    Zmienna `client_telemetry_topic` to temat MQTT, na który urządzenie będzie wysyłać poziomy światła.

1. Zamień zawartość pętli `while True:` na końcu pliku na poniższą:

    ```python
    while True:
        light = light_sensor.light
        telemetry = json.dumps({'light' : light})

        print("Sending telemetry ", telemetry)
    
        mqtt_client.publish(client_telemetry_topic, telemetry)
    
        time.sleep(5)
    ```

    Ten kod pakuje poziom światła w dokument JSON i publikuje go do brokera MQTT. Następnie wprowadza opóźnienie, aby zmniejszyć częstotliwość wysyłania wiadomości.

1. Uruchom kod w taki sam sposób, jak uruchamiałeś kod z poprzedniej części zadania. Jeśli korzystasz z wirtualnego urządzenia IoT, upewnij się, że aplikacja CounterFit jest uruchomiona, a czujnik światła i dioda LED zostały utworzone na odpowiednich pinach.

    ```output
    (.venv) ➜  nightlight python app.py 
    MQTT connected!
    Sending telemetry  {"light": 0}
    Sending telemetry  {"light": 0}
    ```

> 💁 Ten kod znajdziesz w folderze [code-telemetry/virtual-device](../../../../../1-getting-started/lessons/4-connect-internet/code-telemetry/virtual-device) lub [code-telemetry/pi](../../../../../1-getting-started/lessons/4-connect-internet/code-telemetry/pi).

😀 Udało Ci się pomyślnie wysłać dane telemetryczne z Twojego urządzenia.

**Zastrzeżenie**:  
Ten dokument został przetłumaczony za pomocą usługi tłumaczenia AI [Co-op Translator](https://github.com/Azure/co-op-translator). Chociaż dokładamy wszelkich starań, aby tłumaczenie było precyzyjne, prosimy pamiętać, że automatyczne tłumaczenia mogą zawierać błędy lub nieścisłości. Oryginalny dokument w jego rodzimym języku powinien być uznawany za wiarygodne źródło. W przypadku informacji o kluczowym znaczeniu zaleca się skorzystanie z profesjonalnego tłumaczenia przez człowieka. Nie ponosimy odpowiedzialności za jakiekolwiek nieporozumienia lub błędne interpretacje wynikające z użycia tego tłumaczenia.