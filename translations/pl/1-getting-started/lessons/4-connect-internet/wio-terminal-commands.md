<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "6754c915dae64ba70fcd5e52c37f3adf",
  "translation_date": "2025-08-26T07:01:28+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/wio-terminal-commands.md",
  "language_code": "pl"
}
-->
# Steruj swoją lampką nocną przez Internet - Wio Terminal

W tej części lekcji zasubskrybujesz polecenia wysyłane z brokera MQTT do Twojego Wio Terminal.

## Subskrybowanie poleceń

Kolejnym krokiem jest subskrybowanie poleceń wysyłanych z brokera MQTT i odpowiednie reagowanie na nie.

### Zadanie

Zasubskrybuj polecenia.

1. Otwórz projekt lampki nocnej w VS Code.

1. Dodaj poniższy kod na końcu pliku `config.h`, aby zdefiniować nazwę tematu dla poleceń:

    ```cpp
    const string SERVER_COMMAND_TOPIC = ID + "/commands";
    ```

    `SERVER_COMMAND_TOPIC` to temat, który urządzenie zasubskrybuje, aby odbierać polecenia dotyczące LED.

1. Dodaj poniższą linię na końcu funkcji `reconnectMQTTClient`, aby zasubskrybować temat poleceń, gdy klient MQTT zostanie ponownie połączony:

    ```cpp
    client.subscribe(SERVER_COMMAND_TOPIC.c_str());
    ```

1. Dodaj poniższy kod poniżej funkcji `reconnectMQTTClient`.

    ```cpp
    void clientCallback(char *topic, uint8_t *payload, unsigned int length)
    {
        char buff[length + 1];
        for (int i = 0; i < length; i++)
        {
            buff[i] = (char)payload[i];
        }
        buff[length] = '\0';
    
        Serial.print("Message received:");
        Serial.println(buff);
    
        DynamicJsonDocument doc(1024);
        deserializeJson(doc, buff);
        JsonObject obj = doc.as<JsonObject>();
    
        bool led_on = obj["led_on"];
    
        if (led_on)
            digitalWrite(D0, HIGH);
        else
            digitalWrite(D0, LOW);
    }
    ```

    Ta funkcja będzie wywoływana jako callback przez klienta MQTT, gdy otrzyma wiadomość z serwera.

    Wiadomość jest odbierana jako tablica 8-bitowych liczb całkowitych bez znaku, więc musi zostać przekonwertowana na tablicę znaków, aby mogła być traktowana jako tekst.

    Wiadomość zawiera dokument JSON, który jest dekodowany za pomocą biblioteki ArduinoJson. Właściwość `led_on` dokumentu JSON jest odczytywana, a w zależności od jej wartości dioda LED jest włączana lub wyłączana.

1. Dodaj poniższy kod do funkcji `createMQTTClient`:

    ```cpp
    client.setCallback(clientCallback);
    ```

    Ten kod ustawia `clientCallback` jako callback, który będzie wywoływany, gdy klient MQTT otrzyma wiadomość od brokera.

    > 💁 Handler `clientCallback` jest wywoływany dla wszystkich zasubskrybowanych tematów. Jeśli później napiszesz kod nasłuchujący wielu tematów, możesz uzyskać temat, na który została wysłana wiadomość, z parametru `topic` przekazanego do funkcji callback.

1. Wgraj kod na swój Wio Terminal i użyj Monitora Szeregowego, aby zobaczyć poziomy światła wysyłane do brokera MQTT.

1. Dostosuj poziomy światła wykrywane przez swoje fizyczne lub wirtualne urządzenie. Zobaczysz wiadomości odbierane i polecenia wysyłane w terminalu. Zobaczysz również, jak dioda LED włącza się i wyłącza w zależności od poziomu światła.

> 💁 Ten kod znajdziesz w folderze [code-commands/wio-terminal](../../../../../1-getting-started/lessons/4-connect-internet/code-commands/wio-terminal).

😀 Udało Ci się zaprogramować swoje urządzenie tak, aby reagowało na polecenia z brokera MQTT.

**Zastrzeżenie**:  
Ten dokument został przetłumaczony za pomocą usługi tłumaczenia AI [Co-op Translator](https://github.com/Azure/co-op-translator). Chociaż dokładamy wszelkich starań, aby zapewnić poprawność tłumaczenia, prosimy pamiętać, że automatyczne tłumaczenia mogą zawierać błędy lub nieścisłości. Oryginalny dokument w jego rodzimym języku powinien być uznawany za autorytatywne źródło. W przypadku informacji krytycznych zaleca się skorzystanie z profesjonalnego tłumaczenia przez człowieka. Nie ponosimy odpowiedzialności za jakiekolwiek nieporozumienia lub błędne interpretacje wynikające z użycia tego tłumaczenia.