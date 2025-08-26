<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "3ac42e284a7222c0e83d2d43231a364f",
  "translation_date": "2025-08-26T06:54:38+00:00",
  "source_file": "2-farm/lessons/4-migrate-your-plant-to-the-cloud/single-board-computer-connect-hub.md",
  "language_code": "pl"
}
-->
# Podłącz swoje urządzenie IoT do chmury - Wirtualny sprzęt IoT i Raspberry Pi

W tej części lekcji podłączysz swoje wirtualne urządzenie IoT lub Raspberry Pi do IoT Hub, aby wysyłać dane telemetryczne i odbierać polecenia.

## Podłącz swoje urządzenie do IoT Hub

Kolejnym krokiem jest podłączenie urządzenia do IoT Hub.

### Zadanie - podłączenie do IoT Hub

1. Otwórz folder `soil-moisture-sensor` w VS Code. Upewnij się, że środowisko wirtualne działa w terminalu, jeśli używasz wirtualnego urządzenia IoT.

1. Zainstaluj dodatkowe pakiety Pip:

    ```sh
    pip3 install azure-iot-device
    ```

    `azure-iot-device` to biblioteka umożliwiająca komunikację z IoT Hub.

1. Dodaj następujące importy na początku pliku `app.py`, poniżej istniejących importów:

    ```python
    from azure.iot.device import IoTHubDeviceClient, Message, MethodResponse
    ```

    Ten kod importuje SDK do komunikacji z IoT Hub.

1. Usuń linię `import paho.mqtt.client as mqtt`, ponieważ ta biblioteka nie jest już potrzebna. Usuń cały kod MQTT, w tym nazwy tematów, cały kod używający `mqtt_client` oraz `handle_command`. Zachowaj pętlę `while True:`, ale usuń linię `mqtt_client.publish` z tej pętli.

1. Dodaj następujący kod poniżej sekcji importów:

    ```python
    connection_string = "<connection string>"
    ```

    Zamień `<connection string>` na ciąg połączenia, który pobrałeś dla urządzenia wcześniej w tej lekcji.

    > 💁 To nie jest najlepsza praktyka. Ciągi połączenia nigdy nie powinny być przechowywane w kodzie źródłowym, ponieważ mogą zostać zapisane w systemie kontroli wersji i znalezione przez innych. Robimy to tutaj dla uproszczenia. Idealnie powinno się używać czegoś takiego jak zmienne środowiskowe i narzędzia takie jak [`python-dotenv`](https://pypi.org/project/python-dotenv/). Dowiesz się więcej na ten temat w kolejnej lekcji.

1. Poniżej tego kodu dodaj następujący fragment, aby utworzyć obiekt klienta urządzenia, który może komunikować się z IoT Hub, i połącz go:

    ```python
    device_client = IoTHubDeviceClient.create_from_connection_string(connection_string)

    print('Connecting')
    device_client.connect()
    print('Connected')
    ```

1. Uruchom ten kod. Zobaczysz, że Twoje urządzenie się połączy.

    ```output
    pi@raspberrypi:~/soil-moisture-sensor $ python3 app.py 
    Connecting
    Connected
    Soil moisture: 379
    ```

## Wysyłanie danych telemetrycznych

Teraz, gdy Twoje urządzenie jest podłączone, możesz wysyłać dane telemetryczne do IoT Hub zamiast do brokera MQTT.

### Zadanie - wysyłanie danych telemetrycznych

1. Dodaj następujący kod wewnątrz pętli `while True`, tuż przed funkcją sleep:

    ```python
    message = Message(json.dumps({ 'soil_moisture': soil_moisture }))
    device_client.send_message(message)
    ```

    Ten kod tworzy `Message` IoT Hub zawierający odczyt wilgotności gleby jako ciąg JSON, a następnie wysyła go do IoT Hub jako wiadomość od urządzenia do chmury.

## Obsługa poleceń

Twoje urządzenie musi obsługiwać polecenie z kodu serwera, aby sterować przekaźnikiem. Polecenie to jest wysyłane jako żądanie metody bezpośredniej.

## Zadanie - obsługa żądania metody bezpośredniej

1. Dodaj następujący kod przed pętlą `while True`:

    ```python
    def handle_method_request(request):
        print("Direct method received - ", request.name)
    
        if request.name == "relay_on":
            relay.on()
        elif request.name == "relay_off":
            relay.off()    
    ```

    Ten kod definiuje metodę `handle_method_request`, która zostanie wywołana, gdy IoT Hub wyśle żądanie metody bezpośredniej. Każda metoda bezpośrednia ma nazwę, a ten kod oczekuje metody o nazwie `relay_on`, aby włączyć przekaźnik, oraz `relay_off`, aby go wyłączyć.

    > 💁 Można to również zaimplementować w jednej metodzie bezpośredniej, przekazując pożądany stan przekaźnika w ładunku, który można przesłać z żądaniem metody i który będzie dostępny z obiektu `request`.

1. Metody bezpośrednie wymagają odpowiedzi, aby poinformować kod wywołujący, że zostały obsłużone. Dodaj następujący kod na końcu funkcji `handle_method_request`, aby utworzyć odpowiedź na żądanie:

    ```python
    method_response = MethodResponse.create_from_method_request(request, 200)
    device_client.send_method_response(method_response)
    ```

    Ten kod wysyła odpowiedź na żądanie metody bezpośredniej z kodem statusu HTTP 200 i przesyła ją z powrotem do IoT Hub.

1. Dodaj następujący kod poniżej definicji tej funkcji:

    ```python
    device_client.on_method_request_received = handle_method_request
    ```

    Ten kod informuje klienta IoT Hub, aby wywołał funkcję `handle_method_request`, gdy zostanie wywołana metoda bezpośrednia.

> 💁 Ten kod znajdziesz w folderze [code/pi](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud/code/pi) lub [code/virtual-device](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud/code/virtual-device).

😀 Twój program czujnika wilgotności gleby jest podłączony do IoT Hub!

**Zastrzeżenie**:  
Ten dokument został przetłumaczony za pomocą usługi tłumaczenia AI [Co-op Translator](https://github.com/Azure/co-op-translator). Chociaż dokładamy wszelkich starań, aby tłumaczenie było precyzyjne, prosimy pamiętać, że automatyczne tłumaczenia mogą zawierać błędy lub nieścisłości. Oryginalny dokument w jego rodzimym języku powinien być uznawany za autorytatywne źródło. W przypadku informacji o kluczowym znaczeniu zaleca się skorzystanie z profesjonalnego tłumaczenia przez człowieka. Nie ponosimy odpowiedzialności za jakiekolwiek nieporozumienia lub błędne interpretacje wynikające z użycia tego tłumaczenia.