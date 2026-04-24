# Wywołaj detektor obiektów z urządzenia IoT - Wirtualny sprzęt IoT i Raspberry Pi

Gdy Twój detektor obiektów zostanie opublikowany, możesz go używać z urządzenia IoT.

## Skopiuj projekt klasyfikatora obrazów

Większość Twojego detektora zapasów jest taka sama jak klasyfikator obrazów, który stworzyłeś w poprzedniej lekcji.

### Zadanie - skopiuj projekt klasyfikatora obrazów

1. Utwórz folder o nazwie `stock-counter` na swoim komputerze, jeśli używasz wirtualnego urządzenia IoT, lub na Raspberry Pi. Jeśli korzystasz z wirtualnego urządzenia IoT, upewnij się, że skonfigurowałeś wirtualne środowisko.

1. Skonfiguruj sprzęt kamery.

    * Jeśli używasz Raspberry Pi, będziesz musiał zamontować PiCamera. Możesz również ustawić kamerę w jednej pozycji, na przykład zawieszając kabel nad pudełkiem lub puszką, albo przymocowując kamerę do pudełka za pomocą taśmy dwustronnej.
    * Jeśli używasz wirtualnego urządzenia IoT, musisz zainstalować CounterFit oraz CounterFit PyCamera shim. Jeśli zamierzasz używać zdjęć statycznych, zrób kilka zdjęć, których Twój detektor obiektów jeszcze nie widział. Jeśli zamierzasz używać kamery internetowej, upewnij się, że jest ustawiona w taki sposób, aby mogła widzieć zapasy, które wykrywasz.

1. Powtórz kroki z [lekcji 2 projektu produkcyjnego](../../../4-manufacturing/lessons/2-check-fruit-from-device/README.md#task---capture-an-image-using-an-iot-device), aby przechwycić obrazy z kamery.

1. Powtórz kroki z [lekcji 2 projektu produkcyjnego](../../../4-manufacturing/lessons/2-check-fruit-from-device/README.md#task---classify-images-from-your-iot-device), aby wywołać klasyfikator obrazów. Większość tego kodu zostanie ponownie użyta do wykrywania obiektów.

## Zmień kod z klasyfikatora na detektor obrazów

Kod, którego używałeś do klasyfikacji obrazów, jest bardzo podobny do kodu do wykrywania obiektów. Główna różnica polega na metodzie wywoływanej w Custom Vision SDK oraz wynikach wywołania.

### Zadanie - zmień kod z klasyfikatora na detektor obrazów

1. Usuń trzy linie kodu, które klasyfikują obraz i przetwarzają przewidywania:

    ```python
    results = predictor.classify_image(project_id, iteration_name, image)
    
    for prediction in results.predictions:
        print(f'{prediction.tag_name}:\t{prediction.probability * 100:.2f}%')
    ```

    Usuń te trzy linie.

1. Dodaj poniższy kod, aby wykrywać obiekty na obrazie:

    ```python
    results = predictor.detect_image(project_id, iteration_name, image)

    threshold = 0.3
    
    predictions = list(prediction for prediction in results.predictions if prediction.probability > threshold)
    
    for prediction in predictions:
        print(f'{prediction.tag_name}:\t{prediction.probability * 100:.2f}%')
    ```

    Ten kod wywołuje metodę `detect_image` na predyktorze, aby uruchomić detektor obiektów. Następnie zbiera wszystkie przewidywania z prawdopodobieństwem powyżej ustalonego progu i wypisuje je na konsolę.

    W przeciwieństwie do klasyfikatora obrazów, który zwraca tylko jeden wynik na tag, detektor obiektów zwróci wiele wyników, więc te z niskim prawdopodobieństwem muszą zostać odfiltrowane.

1. Uruchom ten kod, a przechwyci on obraz, wyśle go do detektora obiektów i wypisze wykryte obiekty. Jeśli używasz wirtualnego urządzenia IoT, upewnij się, że masz odpowiedni obraz ustawiony w CounterFit lub wybrana jest kamera internetowa. Jeśli używasz Raspberry Pi, upewnij się, że Twoja kamera jest skierowana na obiekty na półce.

    ```output
    pi@raspberrypi:~/stock-counter $ python3 app.py 
    tomato paste:   34.13%
    tomato paste:   33.95%
    tomato paste:   35.05%
    tomato paste:   32.80%
    ```

    > 💁 Może być konieczne dostosowanie wartości `threshold` do odpowiedniego poziomu dla Twoich obrazów.

    Będziesz mógł zobaczyć obraz, który został zrobiony, oraz te wartości w zakładce **Predictions** w Custom Vision.

    ![4 puszki koncentratu pomidorowego na półce z przewidywaniami dla 4 wykryć: 35.8%, 33.5%, 25.7% i 16.6%](../../../../../translated_images/pl/custom-vision-stock-prediction.942266ab1bcca341.webp)

> 💁 Ten kod znajdziesz w folderze [code-detect/pi](../../../../../5-retail/lessons/2-check-stock-device/code-detect/pi) lub [code-detect/virtual-iot-device](../../../../../5-retail/lessons/2-check-stock-device/code-detect/virtual-iot-device).

😀 Twój program liczący zapasy zakończył się sukcesem!

**Zastrzeżenie**:  
Ten dokument został przetłumaczony za pomocą usługi tłumaczenia AI [Co-op Translator](https://github.com/Azure/co-op-translator). Chociaż dokładamy wszelkich starań, aby tłumaczenie było precyzyjne, prosimy pamiętać, że automatyczne tłumaczenia mogą zawierać błędy lub nieścisłości. Oryginalny dokument w jego rodzimym języku powinien być uznawany za wiarygodne źródło. W przypadku informacji o kluczowym znaczeniu zaleca się skorzystanie z profesjonalnego tłumaczenia przez człowieka. Nie ponosimy odpowiedzialności za jakiekolwiek nieporozumienia lub błędne interpretacje wynikające z użycia tego tłumaczenia.