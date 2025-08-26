<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "50151d9f9dce2801348a93880ef16d86",
  "translation_date": "2025-08-26T06:37:51+00:00",
  "source_file": "4-manufacturing/lessons/3-run-fruit-detector-edge/single-board-computer.md",
  "language_code": "pl"
}
-->
# Klasyfikacja obrazu za pomocą klasyfikatora obrazów opartego na IoT Edge - Wirtualny sprzęt IoT i Raspberry Pi

W tej części lekcji użyjesz klasyfikatora obrazów działającego na urządzeniu IoT Edge.

## Użyj klasyfikatora IoT Edge

Urządzenie IoT może zostać przekierowane do korzystania z klasyfikatora obrazów IoT Edge. Adres URL dla klasyfikatora obrazów to `http://<IP address or name>/image`, gdzie `<IP address or name>` należy zastąpić adresem IP lub nazwą hosta komputera, na którym działa IoT Edge.

Biblioteka Python dla Custom Vision działa tylko z modelami hostowanymi w chmurze, a nie z modelami hostowanymi na IoT Edge. Oznacza to, że będziesz musiał użyć REST API, aby wywołać klasyfikator.

### Zadanie - użyj klasyfikatora IoT Edge

1. Otwórz projekt `fruit-quality-detector` w VS Code, jeśli nie jest już otwarty. Jeśli korzystasz z wirtualnego urządzenia IoT, upewnij się, że środowisko wirtualne jest aktywowane.

1. Otwórz plik `app.py` i usuń instrukcje importu z `azure.cognitiveservices.vision.customvision.prediction` oraz `msrest.authentication`.

1. Dodaj następujący import na początku pliku:

    ```python
    import requests
    ```

1. Usuń cały kod po zapisaniu obrazu do pliku, od `image_file.write(image.read())` do końca pliku.

1. Dodaj następujący kod na końcu pliku:

    ```python
    prediction_url = '<URL>'
    headers = {
        'Content-Type' : 'application/octet-stream'
    }
    image.seek(0)
    response = requests.post(prediction_url, headers=headers, data=image)
    results = response.json()
    
    for prediction in results['predictions']:
        print(f'{prediction["tagName"]}:\t{prediction["probability"] * 100:.2f}%')
    ```

    Zamień `<URL>` na adres URL swojego klasyfikatora.

    Ten kod wykonuje żądanie REST POST do klasyfikatora, przesyłając obraz jako treść żądania. Wyniki są zwracane w formacie JSON, który jest dekodowany, aby wyświetlić prawdopodobieństwa.

1. Uruchom swój kod, kierując kamerę na jakiś owoc, odpowiedni zestaw obrazów lub widoczny owoc na kamerze internetowej, jeśli korzystasz z wirtualnego sprzętu IoT. Zobaczysz wynik w konsoli:

    ```output
    (.venv) ➜  fruit-quality-detector python app.py
    ripe:   56.84%
    unripe: 43.16%
    ```

> 💁 Ten kod znajdziesz w folderze [code-classify/pi](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge/code-classify/pi) lub [code-classify/virtual-iot-device](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge/code-classify/virtual-iot-device).

😀 Twój program klasyfikatora jakości owoców zakończył się sukcesem!

**Zastrzeżenie**:  
Ten dokument został przetłumaczony za pomocą usługi tłumaczenia AI [Co-op Translator](https://github.com/Azure/co-op-translator). Chociaż dokładamy wszelkich starań, aby tłumaczenie było precyzyjne, prosimy pamiętać, że automatyczne tłumaczenia mogą zawierać błędy lub nieścisłości. Oryginalny dokument w jego rodzimym języku powinien być uznawany za autorytatywne źródło. W przypadku informacji o kluczowym znaczeniu zaleca się skorzystanie z profesjonalnego tłumaczenia przez człowieka. Nie ponosimy odpowiedzialności za jakiekolwiek nieporozumienia lub błędne interpretacje wynikające z użycia tego tłumaczenia.