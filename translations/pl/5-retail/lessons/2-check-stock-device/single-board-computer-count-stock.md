<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "9c4320311c0f2c1884a6a21265d98a51",
  "translation_date": "2025-08-26T06:27:57+00:00",
  "source_file": "5-retail/lessons/2-check-stock-device/single-board-computer-count-stock.md",
  "language_code": "pl"
}
-->
# Liczenie zapasów za pomocą urządzenia IoT - Wirtualny sprzęt IoT i Raspberry Pi

Kombinacja przewidywań i ich ramki ograniczającej może być użyta do liczenia zapasów na obrazie.

## Wyświetlanie ramek ograniczających

Jako pomocny krok debugowania możesz nie tylko wypisać ramki ograniczające, ale także narysować je na obrazie zapisanym na dysku w momencie przechwycenia obrazu.

### Zadanie - wypisz ramki ograniczające

1. Upewnij się, że projekt `stock-counter` jest otwarty w VS Code, a środowisko wirtualne jest aktywowane, jeśli używasz wirtualnego urządzenia IoT.

1. Zmień instrukcję `print` w pętli `for` na następującą, aby wypisać ramki ograniczające w konsoli:

    ```python
    print(f'{prediction.tag_name}:\t{prediction.probability * 100:.2f}%\t{prediction.bounding_box}')
    ```

1. Uruchom aplikację, kierując kamerę na zapasy na półce. Ramki ograniczające zostaną wypisane w konsoli, z wartościami left, top, width i height w zakresie od 0 do 1.

    ```output
    pi@raspberrypi:~/stock-counter $ python3 app.py 
    tomato paste:   33.42%  {'additional_properties': {}, 'left': 0.3455171, 'top': 0.09916268, 'width': 0.14175442, 'height': 0.29405564}
    tomato paste:   34.41%  {'additional_properties': {}, 'left': 0.48283678, 'top': 0.10242918, 'width': 0.11782813, 'height': 0.27467814}
    tomato paste:   31.25%  {'additional_properties': {}, 'left': 0.4923783, 'top': 0.35007596, 'width': 0.13668466, 'height': 0.28304994}
    tomato paste:   31.05%  {'additional_properties': {}, 'left': 0.36416405, 'top': 0.37494493, 'width': 0.14024884, 'height': 0.26880276}
    ```

### Zadanie - narysuj ramki ograniczające na obrazie

1. Pakiet Pip [Pillow](https://pypi.org/project/Pillow/) może być użyty do rysowania na obrazach. Zainstaluj go za pomocą następującego polecenia:

    ```sh
    pip3 install pillow
    ```

    Jeśli używasz wirtualnego urządzenia IoT, upewnij się, że uruchamiasz to polecenie w aktywowanym środowisku wirtualnym.

1. Dodaj następujący import na początku pliku `app.py`:

    ```python
    from PIL import Image, ImageDraw, ImageColor
    ```

    Importuje to kod potrzebny do edycji obrazu.

1. Dodaj następujący kod na końcu pliku `app.py`:

    ```python
    with Image.open('image.jpg') as im:
        draw = ImageDraw.Draw(im)
    
        for prediction in predictions:
            scale_left = prediction.bounding_box.left
            scale_top = prediction.bounding_box.top
            scale_right = prediction.bounding_box.left + prediction.bounding_box.width
            scale_bottom = prediction.bounding_box.top + prediction.bounding_box.height
            
            left = scale_left * im.width
            top = scale_top * im.height
            right = scale_right * im.width
            bottom = scale_bottom * im.height
    
            draw.rectangle([left, top, right, bottom], outline=ImageColor.getrgb('red'), width=2)
    
        im.save('image.jpg')
    ```

    Kod ten otwiera wcześniej zapisany obraz do edycji. Następnie przechodzi przez przewidywania, pobierając ramki ograniczające, i oblicza współrzędne dolnego prawego rogu, używając wartości ramki ograniczającej w zakresie od 0 do 1. Wartości te są następnie przekształcane na współrzędne obrazu przez pomnożenie przez odpowiedni wymiar obrazu. Na przykład, jeśli wartość left wynosiła 0.5 na obrazie o szerokości 600 pikseli, zostanie przekształcona na 300 (0.5 x 600 = 300).

    Każda ramka ograniczająca jest rysowana na obrazie za pomocą czerwonej linii. Na koniec edytowany obraz jest zapisywany, zastępując oryginalny obraz.

1. Uruchom aplikację, kierując kamerę na zapasy na półce. W eksploratorze VS Code zobaczysz plik `image.jpg` i będziesz mógł go wybrać, aby zobaczyć ramki ograniczające.

    ![4 puszki koncentratu pomidorowego z ramkami ograniczającymi wokół każdej puszki](../../../../../translated_images/rpi-stock-with-bounding-boxes.b5540e2ecb7cd49f.pl.jpg)

## Liczenie zapasów

Na powyższym obrazie ramki ograniczające mają niewielkie nakładanie się. Jeśli to nakładanie byłoby znacznie większe, ramki ograniczające mogłyby wskazywać ten sam obiekt. Aby poprawnie policzyć obiekty, musisz ignorować ramki z istotnym nakładaniem się.

### Zadanie - liczenie zapasów ignorując nakładanie się

1. Pakiet Pip [Shapely](https://pypi.org/project/Shapely/) może być użyty do obliczania przecięcia. Jeśli używasz Raspberry Pi, najpierw musisz zainstalować zależność biblioteki:

    ```sh
    sudo apt install libgeos-dev
    ```

1. Zainstaluj pakiet Pip Shapely:

    ```sh
    pip3 install shapely
    ```

    Jeśli używasz wirtualnego urządzenia IoT, upewnij się, że uruchamiasz to polecenie w aktywowanym środowisku wirtualnym.

1. Dodaj następujący import na początku pliku `app.py`:

    ```python
    from shapely.geometry import Polygon
    ```

    Importuje to kod potrzebny do tworzenia wielokątów w celu obliczania nakładania się.

1. Powyżej kodu rysującego ramki ograniczające dodaj następujący kod:

    ```python
    overlap_threshold = 0.20
    ```

    Definiuje to procent nakładania się, który jest akceptowalny, zanim ramki ograniczające zostaną uznane za ten sam obiekt. 0.20 oznacza 20% nakładania się.

1. Aby obliczyć nakładanie się za pomocą Shapely, ramki ograniczające muszą zostać przekształcone w wielokąty Shapely. Dodaj następującą funkcję, aby to zrobić:

    ```python
    def create_polygon(prediction):
        scale_left = prediction.bounding_box.left
        scale_top = prediction.bounding_box.top
        scale_right = prediction.bounding_box.left + prediction.bounding_box.width
        scale_bottom = prediction.bounding_box.top + prediction.bounding_box.height
    
        return Polygon([(scale_left, scale_top), (scale_right, scale_top), (scale_right, scale_bottom), (scale_left, scale_bottom)])
    ```

    Funkcja ta tworzy wielokąt, używając ramki ograniczającej przewidywania.

1. Logika usuwania nakładających się obiektów polega na porównywaniu wszystkich ramek ograniczających i, jeśli jakiekolwiek pary przewidywań mają ramki ograniczające, które nakładają się bardziej niż próg, jedno z przewidywań jest usuwane. Aby porównać wszystkie przewidywania, porównujesz przewidywanie 1 z 2, 3, 4 itd., następnie 2 z 3, 4 itd. Następujący kod to realizuje:

    ```python
    to_delete = []

    for i in range(0, len(predictions)):
        polygon_1 = create_polygon(predictions[i])
    
        for j in range(i+1, len(predictions)):
            polygon_2 = create_polygon(predictions[j])
            overlap = polygon_1.intersection(polygon_2).area

            smallest_area = min(polygon_1.area, polygon_2.area)
    
            if overlap > (overlap_threshold * smallest_area):
                to_delete.append(predictions[i])
                break
    
    for d in to_delete:
        predictions.remove(d)

    print(f'Counted {len(predictions)} stock items')
    ```

    Nakładanie się jest obliczane za pomocą metody Shapely `Polygon.intersection`, która zwraca wielokąt reprezentujący nakładanie się. Obliczana jest następnie powierzchnia tego wielokąta. Próg nakładania się nie jest wartością absolutną, ale musi być procentem ramki ograniczającej, więc najmniejsza ramka ograniczająca jest znajdowana, a próg nakładania się jest używany do obliczenia, jaka powierzchnia nakładania się może być, aby nie przekroczyć procentowego progu najmniejszej ramki ograniczającej. Jeśli nakładanie się przekracza ten próg, przewidywanie jest oznaczane do usunięcia.

    Gdy przewidywanie zostanie oznaczone do usunięcia, nie musi być ponownie sprawdzane, więc wewnętrzna pętla przerywa, aby sprawdzić kolejne przewidywanie. Nie można usuwać elementów z listy podczas iteracji przez nią, więc ramki ograniczające, które nakładają się bardziej niż próg, są dodawane do listy `to_delete`, a następnie usuwane na końcu.

    Na koniec liczba zapasów jest wypisywana w konsoli. Można ją następnie wysłać do usługi IoT, aby ostrzec o niskim poziomie zapasów. Cały ten kod znajduje się przed rysowaniem ramek ograniczających, więc na wygenerowanych obrazach zobaczysz przewidywania zapasów bez nakładań.

    > 💁 Jest to bardzo uproszczony sposób usuwania nakładań, po prostu usuwając pierwszy element w parze nakładających się ramek. W kodzie produkcyjnym warto byłoby dodać więcej logiki, na przykład uwzględniając nakładania się między wieloma obiektami lub sytuacje, gdy jedna ramka ograniczająca jest zawarta w innej.

1. Uruchom aplikację, kierując kamerę na zapasy na półce. Wynik wskaże liczbę ramek ograniczających bez nakładań przekraczających próg. Spróbuj dostosować wartość `overlap_threshold`, aby zobaczyć ignorowane przewidywania.

> 💁 Kod ten znajdziesz w folderze [code-count/pi](../../../../../5-retail/lessons/2-check-stock-device/code-count/pi) lub [code-count/virtual-iot-device](../../../../../5-retail/lessons/2-check-stock-device/code-count/virtual-iot-device).

😀 Twój program do liczenia zapasów zakończył się sukcesem!

**Zastrzeżenie**:  
Ten dokument został przetłumaczony za pomocą usługi tłumaczenia AI [Co-op Translator](https://github.com/Azure/co-op-translator). Chociaż dokładamy wszelkich starań, aby zapewnić precyzję, prosimy pamiętać, że automatyczne tłumaczenia mogą zawierać błędy lub nieścisłości. Oryginalny dokument w jego rodzimym języku powinien być uznawany za wiarygodne źródło. W przypadku informacji o kluczowym znaczeniu zaleca się skorzystanie z profesjonalnego tłumaczenia przez człowieka. Nie ponosimy odpowiedzialności za jakiekolwiek nieporozumienia lub błędne interpretacje wynikające z użycia tego tłumaczenia.