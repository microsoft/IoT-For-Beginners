# Klasyfikacja obrazu - Wirtualny sprzęt IoT i Raspberry Pi

W tej części lekcji wyślesz obraz uchwycony przez kamerę do usługi Custom Vision, aby go sklasyfikować.

## Wysyłanie obrazów do Custom Vision

Usługa Custom Vision posiada bibliotekę SDK dla Pythona, której możesz użyć do klasyfikacji obrazów.

### Zadanie - wysyłanie obrazów do Custom Vision

1. Otwórz folder `fruit-quality-detector` w VS Code. Jeśli korzystasz z wirtualnego urządzenia IoT, upewnij się, że środowisko wirtualne działa w terminalu.

1. Biblioteka SDK dla Pythona do wysyłania obrazów do Custom Vision jest dostępna jako pakiet Pip. Zainstaluj ją za pomocą następującego polecenia:

    ```sh
    pip3 install azure-cognitiveservices-vision-customvision
    ```

1. Dodaj następujące instrukcje importu na początku pliku `app.py`:

    ```python
    from msrest.authentication import ApiKeyCredentials
    from azure.cognitiveservices.vision.customvision.prediction import CustomVisionPredictionClient
    ```

    Dzięki temu zaimportujesz moduły z bibliotek Custom Vision: jeden do uwierzytelniania za pomocą klucza predykcji, a drugi do dostarczenia klasy klienta predykcji, która może wywoływać Custom Vision.

1. Dodaj następujący kod na końcu pliku:

    ```python
    prediction_url = '<prediction_url>'
    prediction_key = '<prediction key>'
    ```

    Zamień `<prediction_url>` na adres URL, który skopiowałeś z okna dialogowego *Prediction URL* wcześniej w tej lekcji. Zamień `<prediction key>` na klucz predykcji, który również skopiowałeś z tego samego okna dialogowego.

1. Adres URL predykcji, który został dostarczony w oknie dialogowym *Prediction URL*, jest przeznaczony do użycia podczas bezpośredniego wywoływania punktu końcowego REST. Biblioteka SDK dla Pythona używa części tego adresu URL w różnych miejscach. Dodaj następujący kod, aby podzielić ten adres URL na potrzebne części:

    ```python
    parts = prediction_url.split('/')
    endpoint = 'https://' + parts[2]
    project_id = parts[6]
    iteration_name = parts[9]
    ```

    Kod ten dzieli adres URL, wyodrębniając punkt końcowy `https://<location>.api.cognitive.microsoft.com`, identyfikator projektu oraz nazwę opublikowanej iteracji.

1. Utwórz obiekt predyktora, aby przeprowadzić predykcję za pomocą następującego kodu:

    ```python
    prediction_credentials = ApiKeyCredentials(in_headers={"Prediction-key": prediction_key})
    predictor = CustomVisionPredictionClient(endpoint, prediction_credentials)
    ```

    `prediction_credentials` zawiera klucz predykcji. Są one następnie używane do utworzenia obiektu klienta predykcji wskazującego na punkt końcowy.

1. Wyślij obraz do Custom Vision za pomocą następującego kodu:

    ```python
    image.seek(0)
    results = predictor.classify_image(project_id, iteration_name, image)
    ```

    Kod ten przewija obraz na początek, a następnie wysyła go do klienta predykcji.

1. Na koniec wyświetl wyniki za pomocą następującego kodu:

    ```python
    for prediction in results.predictions:
        print(f'{prediction.tag_name}:\t{prediction.probability * 100:.2f}%')
    ```

    Kod ten przechodzi przez wszystkie zwrócone predykcje i wyświetla je w terminalu. Zwracane prawdopodobieństwa to liczby zmiennoprzecinkowe w zakresie od 0 do 1, gdzie 0 oznacza 0% szans na dopasowanie do tagu, a 1 oznacza 100% szans.

    > 💁 Klasyfikatory obrazów zwracają procenty dla wszystkich użytych tagów. Każdy tag będzie miał przypisane prawdopodobieństwo, że obraz pasuje do tego tagu.

1. Uruchom swój kod, kierując kamerę na jakiś owoc, odpowiedni zestaw obrazów lub owoc widoczny na kamerze internetowej, jeśli korzystasz z wirtualnego sprzętu IoT. Wyniki zobaczysz w konsoli:

    ```output
    (.venv) ➜  fruit-quality-detector python app.py
    ripe:   56.84%
    unripe: 43.16%
    ```

    Będziesz mógł zobaczyć uchwycony obraz, a także te wartości w zakładce **Predictions** w Custom Vision.

    ![Banana w Custom Vision przewidziany jako dojrzały w 56,8% i niedojrzały w 43,1%](../../../../../translated_images/pl/custom-vision-banana-prediction.30cdff4e1d72db5d.webp)

> 💁 Kod ten znajdziesz w folderze [code-classify/pi](../../../../../4-manufacturing/lessons/2-check-fruit-from-device/code-classify/pi) lub [code-classify/virtual-iot-device](../../../../../4-manufacturing/lessons/2-check-fruit-from-device/code-classify/virtual-iot-device).

😀 Twój program do klasyfikacji jakości owoców zakończył się sukcesem!

**Zastrzeżenie**:  
Ten dokument został przetłumaczony za pomocą usługi tłumaczenia AI [Co-op Translator](https://github.com/Azure/co-op-translator). Chociaż dokładamy wszelkich starań, aby tłumaczenie było precyzyjne, prosimy pamiętać, że automatyczne tłumaczenia mogą zawierać błędy lub nieścisłości. Oryginalny dokument w jego rodzimym języku powinien być uznawany za autorytatywne źródło. W przypadku informacji o kluczowym znaczeniu zaleca się skorzystanie z profesjonalnego tłumaczenia przez człowieka. Nie ponosimy odpowiedzialności za jakiekolwiek nieporozumienia lub błędne interpretacje wynikające z użycia tego tłumaczenia.