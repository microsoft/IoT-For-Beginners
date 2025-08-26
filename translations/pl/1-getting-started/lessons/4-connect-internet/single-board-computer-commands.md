<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "c527ce85d69b1a3875366ec61cbed8aa",
  "translation_date": "2025-08-26T06:57:54+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/single-board-computer-commands.md",
  "language_code": "pl"
}
-->
# Steruj swoją lampką nocną przez Internet - Wirtualny sprzęt IoT i Raspberry Pi

W tej części lekcji zasubskrybujesz polecenia wysyłane z brokera MQTT do Twojego Raspberry Pi lub wirtualnego urządzenia IoT.

## Subskrybuj polecenia

Kolejnym krokiem jest subskrybowanie poleceń wysyłanych z brokera MQTT i reagowanie na nie.

### Zadanie

Zasubskrybuj polecenia.

1. Otwórz projekt lampki nocnej w VS Code.

1. Jeśli używasz wirtualnego urządzenia IoT, upewnij się, że terminal działa w środowisku wirtualnym. Jeśli korzystasz z Raspberry Pi, nie będziesz używać środowiska wirtualnego.

1. Dodaj poniższy kod po definicjach `client_telemetry_topic`:

    ```python
    server_command_topic = id + '/commands'
    ```

    `server_command_topic` to temat MQTT, który urządzenie zasubskrybuje, aby odbierać polecenia dotyczące LED.

1. Dodaj poniższy kod tuż nad główną pętlą, po linii `mqtt_client.loop_start()`:

    ```python
    def handle_command(client, userdata, message):
        payload = json.loads(message.payload.decode())
        print("Message received:", payload)
    
        if payload['led_on']:
            led.on()
        else:
            led.off()
    
    mqtt_client.subscribe(server_command_topic)
    mqtt_client.on_message = handle_command
    ```

    Ten kod definiuje funkcję `handle_command`, która odczytuje wiadomość jako dokument JSON i sprawdza wartość właściwości `led_on`. Jeśli jest ustawiona na `True`, dioda LED zostaje włączona, w przeciwnym razie zostaje wyłączona.

    Klient MQTT subskrybuje temat, na który serwer będzie wysyłał wiadomości, i ustawia funkcję `handle_command`, aby była wywoływana, gdy wiadomość zostanie odebrana.

    > 💁 Handler `on_message` jest wywoływany dla wszystkich subskrybowanych tematów. Jeśli później napiszesz kod nasłuchujący wielu tematów, możesz uzyskać temat, na który wiadomość została wysłana, z obiektu `message` przekazanego do funkcji obsługującej.

1. Uruchom kod w taki sam sposób, jak uruchamiałeś kod z poprzedniej części zadania. Jeśli używasz wirtualnego urządzenia IoT, upewnij się, że aplikacja CounterFit jest uruchomiona, a czujnik światła i dioda LED zostały utworzone na odpowiednich pinach.

1. Dostosuj poziomy światła wykrywane przez swoje fizyczne lub wirtualne urządzenie. Wiadomości odbierane i polecenia wysyłane będą zapisywane w terminalu. Dioda LED będzie również włączana i wyłączana w zależności od poziomu światła.

> 💁 Ten kod znajdziesz w folderze [code-commands/virtual-device](../../../../../1-getting-started/lessons/4-connect-internet/code-commands/virtual-device) lub [code-commands/pi](../../../../../1-getting-started/lessons/4-connect-internet/code-commands/pi).

😀 Udało Ci się zaprogramować swoje urządzenie tak, aby reagowało na polecenia z brokera MQTT.

**Zastrzeżenie**:  
Ten dokument został przetłumaczony za pomocą usługi tłumaczeniowej AI [Co-op Translator](https://github.com/Azure/co-op-translator). Chociaż dokładamy wszelkich starań, aby zapewnić dokładność, prosimy pamiętać, że automatyczne tłumaczenia mogą zawierać błędy lub nieścisłości. Oryginalny dokument w jego rodzimym języku powinien być uznawany za wiarygodne źródło. W przypadku informacji krytycznych zaleca się skorzystanie z profesjonalnego tłumaczenia wykonanego przez człowieka. Nie ponosimy odpowiedzialności za jakiekolwiek nieporozumienia lub błędne interpretacje wynikające z korzystania z tego tłumaczenia.