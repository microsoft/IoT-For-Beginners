<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "9aea84bcc7520222b0e1c50469d62d6a",
  "translation_date": "2025-08-26T06:57:15+00:00",
  "source_file": "2-farm/lessons/6-keep-your-plant-secure/single-board-computer-x509.md",
  "language_code": "pl"
}
-->
# Użyj certyfikatu X.509 w kodzie urządzenia - Wirtualny sprzęt IoT i Raspberry Pi

W tej części lekcji połączysz swoje wirtualne urządzenie IoT lub Raspberry Pi z IoT Hub, używając certyfikatu X.509.

## Połącz swoje urządzenie z IoT Hub

Kolejnym krokiem jest połączenie urządzenia z IoT Hub za pomocą certyfikatów X.509.

### Zadanie - połącz z IoT Hub

1. Skopiuj pliki klucza i certyfikatu do folderu zawierającego kod Twojego urządzenia IoT. Jeśli korzystasz z Raspberry Pi przez VS Code Remote SSH i utworzyłeś klucze na swoim komputerze PC lub Mac, możesz przeciągnąć i upuścić pliki do eksploratora w VS Code, aby je skopiować.

1. Otwórz plik `app.py`.

1. Aby połączyć się za pomocą certyfikatu X.509, będziesz potrzebować nazwy hosta IoT Hub oraz certyfikatu X.509. Zacznij od utworzenia zmiennej zawierającej nazwę hosta, dodając poniższy kod przed utworzeniem klienta urządzenia:

    ```python
    host_name = "<host_name>"
    ```

    Zamień `<host_name>` na nazwę hosta Twojego IoT Hub. Możesz ją znaleźć w sekcji `HostName` w `connection_string`. Będzie to nazwa Twojego IoT Hub, kończąca się na `.azure-devices.net`.

1. Poniżej zadeklaruj zmienną z identyfikatorem urządzenia:

    ```python
    device_id = "soil-moisture-sensor-x509"
    ```

1. Będziesz potrzebować instancji klasy `X509`, która zawiera pliki certyfikatu X.509. Dodaj `X509` do listy klas importowanych z modułu `azure.iot.device`:

    ```python
    from azure.iot.device import IoTHubDeviceClient, Message, MethodResponse, X509
    ```

1. Utwórz instancję klasy `X509`, używając swoich plików certyfikatu i klucza, dodając ten kod poniżej deklaracji `host_name`:

    ```python
    x509 = X509("./soil-moisture-sensor-x509-cert.pem", "./soil-moisture-sensor-x509-key.pem")
    ```

    To utworzy klasę `X509`, używając plików `soil-moisture-sensor-x509-cert.pem` i `soil-moisture-sensor-x509-key.pem`, które zostały utworzone wcześniej.

1. Zamień linię kodu, która tworzy `device_client` z connection string, na następującą:

    ```python
    device_client = IoTHubDeviceClient.create_from_x509_certificate(x509, host_name, device_id)
    ```

    To połączy urządzenie za pomocą certyfikatu X.509 zamiast connection string.

1. Usuń linię z zmienną `connection_string`.

1. Uruchom swój kod. Monitoruj wiadomości wysyłane do IoT Hub i wysyłaj żądania metod bezpośrednich, jak wcześniej. Zobaczysz, jak urządzenie łączy się, wysyła odczyty wilgotności gleby oraz odbiera żądania metod bezpośrednich.

> 💁 Ten kod znajdziesz w folderze [code/pi](../../../../../2-farm/lessons/6-keep-your-plant-secure/code/pi) lub [code/virtual-device](../../../../../2-farm/lessons/6-keep-your-plant-secure/code/virtual-device).

😀 Twój program czujnika wilgotności gleby jest połączony z IoT Hub za pomocą certyfikatu X.509!

**Zastrzeżenie**:  
Ten dokument został przetłumaczony za pomocą usługi tłumaczenia AI [Co-op Translator](https://github.com/Azure/co-op-translator). Chociaż dokładamy wszelkich starań, aby tłumaczenie było precyzyjne, prosimy pamiętać, że automatyczne tłumaczenia mogą zawierać błędy lub nieścisłości. Oryginalny dokument w jego rodzimym języku powinien być uznawany za autorytatywne źródło. W przypadku informacji o kluczowym znaczeniu zaleca się skorzystanie z profesjonalnego tłumaczenia przez człowieka. Nie ponosimy odpowiedzialności za jakiekolwiek nieporozumienia lub błędne interpretacje wynikające z użycia tego tłumaczenia.