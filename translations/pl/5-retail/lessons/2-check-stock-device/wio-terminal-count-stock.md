<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "0b2ae20b0fc8e73c9598dea937cac038",
  "translation_date": "2025-08-26T06:27:37+00:00",
  "source_file": "5-retail/lessons/2-check-stock-device/wio-terminal-count-stock.md",
  "language_code": "pl"
}
-->
# Liczenie zapasów za pomocą urządzenia IoT - Wio Terminal

Połączenie przewidywań i ich ramki ograniczającej może być użyte do liczenia zapasów na obrazie.

## Liczenie zapasów

![4 puszki koncentratu pomidorowego z ramkami ograniczającymi wokół każdej puszki](../../../../../translated_images/pl/rpi-stock-with-bounding-boxes.b5540e2ecb7cd49f.jpg)

Na powyższym obrazie ramki ograniczające mają niewielkie nakładanie się. Jeśli to nakładanie byłoby znacznie większe, ramki mogłyby wskazywać na ten sam obiekt. Aby poprawnie policzyć obiekty, należy ignorować ramki z istotnym nakładaniem się.

### Zadanie - liczenie zapasów ignorując nakładanie się

1. Otwórz swój projekt `stock-counter`, jeśli nie jest już otwarty.

1. Nad funkcją `processPredictions` dodaj następujący kod:

    ```cpp
    const float overlap_threshold = 0.20f;
    ```

    Ten kod definiuje procent nakładania się, który jest akceptowalny, zanim ramki ograniczające zostaną uznane za ten sam obiekt. 0.20 oznacza 20% nakładania się.

1. Poniżej tego, ale nadal nad funkcją `processPredictions`, dodaj następujący kod do obliczenia nakładania się między dwoma prostokątami:

    ```cpp
    struct Point {
        float x, y;
    };

    struct Rect {
        Point topLeft, bottomRight;
    };

    float area(Rect rect)
    {
        return abs(rect.bottomRight.x - rect.topLeft.x) * abs(rect.bottomRight.y - rect.topLeft.y);
    }
     
    float overlappingArea(Rect rect1, Rect rect2)
    {
        float left = max(rect1.topLeft.x, rect2.topLeft.x);
        float right = min(rect1.bottomRight.x, rect2.bottomRight.x);
        float top = max(rect1.topLeft.y, rect2.topLeft.y);
        float bottom = min(rect1.bottomRight.y, rect2.bottomRight.y);
    
    
        if ( right > left && bottom > top )
        {
            return (right-left)*(bottom-top);
        }
        
        return 0.0f;
    }
    ```

    Ten kod definiuje strukturę `Point` do przechowywania punktów na obrazie oraz strukturę `Rect` do definiowania prostokąta za pomocą współrzędnych górnego lewego i dolnego prawego rogu. Następnie definiuje funkcję `area`, która oblicza powierzchnię prostokąta na podstawie współrzędnych górnego lewego i dolnego prawego rogu.

    Kolejno definiuje funkcję `overlappingArea`, która oblicza powierzchnię nakładania się dwóch prostokątów. Jeśli się nie nakładają, zwraca 0.

1. Poniżej funkcji `overlappingArea` zadeklaruj funkcję do konwersji ramki ograniczającej na `Rect`:

    ```cpp
    Rect rectFromBoundingBox(JsonVariant prediction)
    {
        JsonObject bounding_box = prediction["boundingBox"].as<JsonObject>();
    
        float left = bounding_box["left"].as<float>();
        float top = bounding_box["top"].as<float>();
        float width = bounding_box["width"].as<float>();
        float height = bounding_box["height"].as<float>();
    
        Point topLeft = {left, top};
        Point bottomRight = {left + width, top + height};
    
        return {topLeft, bottomRight};
    }
    ```

    Funkcja ta pobiera przewidywanie z detektora obiektów, wyodrębnia ramkę ograniczającą i używa wartości z ramki do zdefiniowania prostokąta. Prawa strona jest obliczana jako lewa plus szerokość. Dolna jako górna plus wysokość.

1. Przewidywania muszą być porównane ze sobą, a jeśli dwa przewidywania mają nakładanie się większe niż próg, jedno z nich musi zostać usunięte. Próg nakładania się jest procentem, więc musi być pomnożony przez rozmiar najmniejszej ramki ograniczającej, aby sprawdzić, czy nakładanie się przekracza określony procent ramki, a nie procent całego obrazu. Zacznij od usunięcia zawartości funkcji `processPredictions`.

1. Dodaj następujący kod do pustej funkcji `processPredictions`:

    ```cpp
    std::vector<JsonVariant> passed_predictions;

    for (int i = 0; i < predictions.size(); ++i)
    {
        Rect prediction_1_rect = rectFromBoundingBox(predictions[i]);
        float prediction_1_area = area(prediction_1_rect);
        bool passed = true;

        for (int j = i + 1; j < predictions.size(); ++j)
        {
            Rect prediction_2_rect = rectFromBoundingBox(predictions[j]);
            float prediction_2_area = area(prediction_2_rect);

            float overlap = overlappingArea(prediction_1_rect, prediction_2_rect);
            float smallest_area = min(prediction_1_area, prediction_2_area);

            if (overlap > (overlap_threshold * smallest_area))
            {
                passed = false;
                break;
            }
        }

        if (passed)
        {
            passed_predictions.push_back(predictions[i]);
        }
    }
    ```

    Ten kod deklaruje wektor do przechowywania przewidywań, które się nie nakładają. Następnie przechodzi przez wszystkie przewidywania, tworząc `Rect` z ramki ograniczającej.

    Następnie kod przechodzi przez pozostałe przewidywania, zaczynając od tego, które jest po bieżącym przewidywaniu. Zapobiega to wielokrotnemu porównywaniu przewidywań - gdy 1 i 2 zostały porównane, nie ma potrzeby porównywania 2 z 1, tylko z 3, 4 itd.

    Dla każdej pary przewidywań obliczana jest powierzchnia nakładania się. Następnie jest ona porównywana z powierzchnią najmniejszej ramki ograniczającej - jeśli nakładanie się przekracza próg procentowy najmniejszej ramki, przewidywanie jest oznaczane jako niezaliczone. Jeśli po porównaniu wszystkich nakładań przewidywanie przechodzi testy, jest dodawane do kolekcji `passed_predictions`.

    > 💁 To bardzo uproszczony sposób usuwania nakładań, po prostu usuwając pierwsze z pary nakładających się. W kodzie produkcyjnym warto dodać więcej logiki, na przykład uwzględniając nakładania się między wieloma obiektami lub sytuację, gdy jedna ramka ograniczająca jest zawarta w innej.

1. Po tym dodaj następujący kod do wysyłania szczegółów zaliczonych przewidywań do monitora szeregowego:

    ```cpp
    for(JsonVariant prediction : passed_predictions)
    {
        String boundingBox = prediction["boundingBox"].as<String>();
        String tag = prediction["tagName"].as<String>();
        float probability = prediction["probability"].as<float>();

        char buff[32];
        sprintf(buff, "%s:\t%.2f%%\t%s", tag.c_str(), probability * 100.0, boundingBox.c_str());
        Serial.println(buff);
    }
    ```

    Ten kod przechodzi przez zaliczone przewidywania i drukuje ich szczegóły na monitorze szeregowym.

1. Poniżej tego dodaj kod do drukowania liczby policzonych przedmiotów na monitorze szeregowym:

    ```cpp
    Serial.print("Counted ");
    Serial.print(passed_predictions.size());
    Serial.println(" stock items.");
    ```

    Liczba ta może być następnie wysłana do usługi IoT, aby ostrzec, jeśli poziomy zapasów są niskie.

1. Prześlij i uruchom swój kod. Skieruj kamerę na przedmioty na półce i naciśnij przycisk C. Spróbuj dostosować wartość `overlap_threshold`, aby zobaczyć ignorowane przewidywania.

    ```output
    Connecting to WiFi..
    Connected!
    Image captured
    Image read to buffer with length 17416
    tomato paste:   35.84%  {"left":0.395631,"top":0.215897,"width":0.180768,"height":0.359364}
    tomato paste:   35.87%  {"left":0.378554,"top":0.583012,"width":0.14824,"height":0.359382}
    tomato paste:   34.11%  {"left":0.699024,"top":0.592617,"width":0.124411,"height":0.350456}
    tomato paste:   35.16%  {"left":0.513006,"top":0.647853,"width":0.187472,"height":0.325817}
    Counted 4 stock items.
    ```

> 💁 Ten kod znajdziesz w folderze [code-count/wio-terminal](../../../../../5-retail/lessons/2-check-stock-device/code-count/wio-terminal).

😀 Twój program do liczenia zapasów zakończył się sukcesem!

**Zastrzeżenie**:  
Ten dokument został przetłumaczony za pomocą usługi tłumaczenia AI [Co-op Translator](https://github.com/Azure/co-op-translator). Chociaż dokładamy wszelkich starań, aby tłumaczenie było precyzyjne, prosimy pamiętać, że automatyczne tłumaczenia mogą zawierać błędy lub nieścisłości. Oryginalny dokument w jego rodzimym języku powinien być uznawany za wiarygodne źródło. W przypadku informacji o kluczowym znaczeniu zaleca się skorzystanie z profesjonalnego tłumaczenia wykonanego przez człowieka. Nie ponosimy odpowiedzialności za jakiekolwiek nieporozumienia lub błędne interpretacje wynikające z użycia tego tłumaczenia.