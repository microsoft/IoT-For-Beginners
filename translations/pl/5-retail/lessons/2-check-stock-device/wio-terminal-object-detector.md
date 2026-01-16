<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "4cf1421420a6fab9ab4f2c391bd523b7",
  "translation_date": "2025-08-26T06:28:27+00:00",
  "source_file": "5-retail/lessons/2-check-stock-device/wio-terminal-object-detector.md",
  "language_code": "pl"
}
-->
# Wywołaj detektor obiektów z urządzenia IoT - Wio Terminal

Po opublikowaniu detektora obiektów, można go używać z urządzenia IoT.

## Skopiuj projekt klasyfikatora obrazów

Większość kodu detektora obiektów jest taka sama jak kod klasyfikatora obrazów, który stworzyłeś w poprzedniej lekcji.

### Zadanie - skopiuj projekt klasyfikatora obrazów

1. Podłącz ArduCam do Wio Terminal, postępując zgodnie z krokami z [lekcji 2 projektu produkcyjnego](../../../4-manufacturing/lessons/2-check-fruit-from-device/wio-terminal-camera.md#task---connect-the-camera).

    Możesz również ustabilizować kamerę w jednej pozycji, na przykład zawieszając kabel nad pudełkiem lub puszką, albo przymocowując kamerę do pudełka za pomocą taśmy dwustronnej.

1. Utwórz nowy projekt Wio Terminal za pomocą PlatformIO. Nazwij ten projekt `stock-counter`.

1. Powtórz kroki z [lekcji 2 projektu produkcyjnego](../../../4-manufacturing/lessons/2-check-fruit-from-device/README.md#task---capture-an-image-using-an-iot-device), aby przechwycić obrazy z kamery.

1. Powtórz kroki z [lekcji 2 projektu produkcyjnego](../../../4-manufacturing/lessons/2-check-fruit-from-device/README.md#task---classify-images-from-your-iot-device), aby wywołać klasyfikator obrazów. Większość tego kodu zostanie ponownie użyta do wykrywania obiektów.

## Zmień kod z klasyfikatora na detektor obrazów

Kod używany do klasyfikacji obrazów jest bardzo podobny do kodu do wykrywania obiektów. Główna różnica polega na adresie URL, który uzyskałeś z Custom Vision, oraz wynikach wywołania.

### Zadanie - zmień kod z klasyfikatora na detektor obrazów

1. Dodaj następującą dyrektywę include na początku pliku `main.cpp`:

    ```cpp
    #include <vector>
    ```

1. Zmień nazwę funkcji `classifyImage` na `detectStock`, zarówno nazwę funkcji, jak i wywołanie w funkcji `buttonPressed`.

1. Nad funkcją `detectStock` zadeklaruj próg, aby odfiltrować wykrycia o niskim prawdopodobieństwie:

    ```cpp
    const float threshold = 0.3f;
    ```

    W przeciwieństwie do klasyfikatora obrazów, który zwraca tylko jeden wynik na tag, detektor obiektów zwraca wiele wyników, więc te o niskim prawdopodobieństwie muszą zostać odfiltrowane.

1. Nad funkcją `detectStock` zadeklaruj funkcję do przetwarzania przewidywań:

    ```cpp
    void processPredictions(std::vector<JsonVariant> &predictions)
    {
        for(JsonVariant prediction : predictions)
        {
            String tag = prediction["tagName"].as<String>();
            float probability = prediction["probability"].as<float>();
    
            char buff[32];
            sprintf(buff, "%s:\t%.2f%%", tag.c_str(), probability * 100.0);
            Serial.println(buff);
        }
    }
    ```

    Funkcja ta przyjmuje listę przewidywań i drukuje je na monitorze szeregowym.

1. W funkcji `detectStock` zastąp zawartość pętli `for`, która przechodzi przez przewidywania, następującym kodem:

    ```cpp
    std::vector<JsonVariant> passed_predictions;

    for(JsonVariant prediction : predictions) 
    {
        float probability = prediction["probability"].as<float>();
        if (probability > threshold)
        {
            passed_predictions.push_back(prediction);
        }
    }

    processPredictions(passed_predictions);
    ```

    Pętla przechodzi przez przewidywania, porównując prawdopodobieństwo z progiem. Wszystkie przewidywania o prawdopodobieństwie wyższym niż próg są dodawane do `list` i przekazywane do funkcji `processPredictions`.

1. Wgraj i uruchom kod. Skieruj kamerę na obiekty na półce i naciśnij przycisk C. Zobaczysz wynik na monitorze szeregowym:

    ```output
    Connecting to WiFi..
    Connected!
    Image captured
    Image read to buffer with length 17416
    tomato paste:   35.84%
    tomato paste:   35.87%
    tomato paste:   34.11%
    tomato paste:   35.16%
    ```

    > 💁 Może być konieczne dostosowanie wartości `threshold` do odpowiedniego poziomu dla Twoich obrazów.

    Będziesz mógł zobaczyć obraz, który został zrobiony, oraz te wartości w zakładce **Predictions** w Custom Vision.

    ![4 puszki koncentratu pomidorowego na półce z przewidywaniami dla 4 wykryć: 35.8%, 33.5%, 25.7% i 16.6%](../../../../../translated_images/pl/custom-vision-stock-prediction.942266ab1bcca3410ecdf23643b9f5f570cfab2345235074e24c51f285777613.png)

> 💁 Kod ten znajdziesz w folderze [code-detect/wio-terminal](../../../../../5-retail/lessons/2-check-stock-device/code-detect/wio-terminal).

😀 Twój program liczący zapasy zakończył się sukcesem!

**Zastrzeżenie**:  
Ten dokument został przetłumaczony za pomocą usługi tłumaczenia AI [Co-op Translator](https://github.com/Azure/co-op-translator). Chociaż dokładamy wszelkich starań, aby tłumaczenie było precyzyjne, prosimy pamiętać, że automatyczne tłumaczenia mogą zawierać błędy lub nieścisłości. Oryginalny dokument w jego rodzimym języku powinien być uznawany za wiarygodne źródło. W przypadku informacji o kluczowym znaczeniu zaleca się skorzystanie z profesjonalnego tłumaczenia przez człowieka. Nie ponosimy odpowiedzialności za jakiekolwiek nieporozumienia lub błędne interpretacje wynikające z użycia tego tłumaczenia.