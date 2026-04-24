# Zrób zdjęcie - Raspberry Pi

W tej części lekcji dodasz czujnik kamery do swojego Raspberry Pi i odczytasz z niego obrazy.

## Sprzęt

Raspberry Pi potrzebuje kamery.

Kamera, której użyjesz, to [Raspberry Pi Camera Module](https://www.raspberrypi.org/products/camera-module-v2/). Ta kamera została zaprojektowana do współpracy z Raspberry Pi i łączy się za pomocą dedykowanego złącza na płytce.

> 💁 Ta kamera korzysta z [Camera Serial Interface, protokołu opracowanego przez Mobile Industry Processor Interface Alliance](https://wikipedia.org/wiki/Camera_Serial_Interface), znanego jako MIPI-CSI. Jest to dedykowany protokół do przesyłania obrazów.

## Podłącz kamerę

Kamera może być podłączona do Raspberry Pi za pomocą taśmy.

### Zadanie - podłącz kamerę

![Kamera Raspberry Pi](../../../../../translated_images/pl/pi-camera-module.4278753c31bd6e75.webp)

1. Wyłącz zasilanie Raspberry Pi.

1. Podłącz taśmę, która jest dostarczona z kamerą, do modułu kamery. Aby to zrobić, delikatnie pociągnij czarny plastikowy klips w uchwycie, aby lekko się wysunął, następnie wsun taśmę do gniazda, tak aby niebieska strona była skierowana od obiektywu, a metalowe paski pinów w stronę obiektywu. Gdy taśma będzie całkowicie wsunięta, wciśnij czarny klips z powrotem na miejsce.

   Możesz znaleźć animację pokazującą, jak otworzyć klips i włożyć taśmę w [dokumentacji Raspberry Pi dotyczącej rozpoczęcia pracy z modułem kamery](https://projects.raspberrypi.org/en/projects/getting-started-with-picamera/2).

   ![Taśma włożona do modułu kamery](../../../../../translated_images/pl/pi-camera-ribbon-cable.0bf82acd251611c2.webp)

1. Zdejmij Grove Base Hat z Raspberry Pi.

1. Przełóż taśmę przez otwór na kamerę w Grove Base Hat. Upewnij się, że niebieska strona taśmy jest skierowana w stronę portów analogowych oznaczonych jako **A0**, **A1** itd.

   ![Taśma przechodząca przez Grove Base Hat](../../../../../translated_images/pl/grove-base-hat-ribbon-cable.501fed202fcf73b1.webp)

1. Włóż taśmę do portu kamery na Raspberry Pi. Ponownie, podnieś czarny plastikowy klips, włóż taśmę, a następnie wciśnij klips z powrotem. Niebieska strona taśmy powinna być skierowana w stronę portów USB i Ethernet.

   ![Taśma podłączona do gniazda kamery na Raspberry Pi](../../../../../translated_images/pl/pi-camera-socket-ribbon-cable.a18309920b118009.webp)

1. Załóż ponownie Grove Base Hat.

## Programowanie kamery

Raspberry Pi można teraz zaprogramować do obsługi kamery za pomocą biblioteki Python [PiCamera](https://pypi.org/project/picamera/).

### Zadanie - włącz tryb kamery legacy

Niestety, wraz z wydaniem Raspberry Pi OS Bullseye, oprogramowanie kamery dostarczane z systemem operacyjnym zostało zmienione, co oznacza, że domyślnie PiCamera już nie działa. Trwają prace nad zamiennikiem, o nazwie PiCamera2, ale nie jest on jeszcze gotowy do użycia.

Na razie możesz przełączyć Raspberry Pi w tryb kamery legacy, aby umożliwić działanie PiCamera. Gniazdo kamery jest również domyślnie wyłączone, ale włączenie oprogramowania kamery legacy automatycznie je aktywuje.

1. Włącz Raspberry Pi i poczekaj, aż się uruchomi.

1. Uruchom VS Code, bezpośrednio na Raspberry Pi lub łącząc się za pomocą rozszerzenia Remote SSH.

1. Wykonaj następujące polecenia w terminalu:

    ```sh
    sudo raspi-config nonint do_legacy 0
    sudo reboot
    ```

    To polecenie przełączy ustawienie, aby włączyć oprogramowanie kamery legacy, a następnie zrestartuje Raspberry Pi, aby zmiana zaczęła działać.

1. Poczekaj, aż Raspberry Pi się zrestartuje, a następnie ponownie uruchom VS Code.

### Zadanie - zaprogramuj kamerę

Zaprogramuj urządzenie.

1. W terminalu utwórz nowy folder w katalogu domowym użytkownika `pi` o nazwie `fruit-quality-detector`. W tym folderze utwórz plik o nazwie `app.py`.

1. Otwórz ten folder w VS Code.

1. Aby korzystać z kamery, możesz użyć biblioteki Python PiCamera. Zainstaluj pakiet Pip dla tej biblioteki za pomocą następującego polecenia:

    ```sh
    pip3 install picamera
    ```

1. Dodaj następujący kod do swojego pliku `app.py`:

    ```python
    import io
    import time
    from picamera import PiCamera
    ```

    Ten kod importuje potrzebne biblioteki, w tym bibliotekę `PiCamera`.

1. Dodaj poniższy kod, aby zainicjalizować kamerę:

    ```python
    camera = PiCamera()
    camera.resolution = (640, 480)
    camera.rotation = 0
    
    time.sleep(2)
    ```

    Ten kod tworzy obiekt PiCamera i ustawia rozdzielczość na 640x480. Chociaż obsługiwane są wyższe rozdzielczości (do 3280x2464), klasyfikator obrazu działa na znacznie mniejszych obrazach (227x227), więc nie ma potrzeby przechwytywania i przesyłania większych obrazów.

    Linia `camera.rotation = 0` ustawia obrót obrazu. Taśma wchodzi do dolnej części kamery, ale jeśli kamera została obrócona, aby łatwiej skierować ją na obiekt, który chcesz sklasyfikować, możesz zmienić tę linię na liczbę stopni obrotu.

    ![Kamera zawieszona nad puszką napoju](../../../../../translated_images/pl/pi-camera-upside-down.5376961ba3145988.webp)

    Na przykład, jeśli zawiesisz taśmę nad czymś, tak że znajduje się na górze kamery, ustaw obrót na 180:

    ```python
    camera.rotation = 180
    ```

    Kamera potrzebuje kilku sekund na uruchomienie, stąd linia `time.sleep(2)`.

1. Dodaj poniższy kod, aby przechwycić obraz jako dane binarne:

    ```python
    image = io.BytesIO()
    camera.capture(image, 'jpeg')
    image.seek(0)
    ```

    Ten kod tworzy obiekt `BytesIO` do przechowywania danych binarnych. Obraz jest odczytywany z kamery jako plik JPEG i przechowywany w tym obiekcie. Obiekt ten ma wskaźnik pozycji, który określa, gdzie znajduje się w danych, aby można było zapisać więcej danych na końcu, jeśli to konieczne, więc linia `image.seek(0)` przesuwa ten wskaźnik z powrotem na początek, aby później można było odczytać wszystkie dane.

1. Poniżej tego dodaj kod do zapisania obrazu do pliku:

    ```python
    with open('image.jpg', 'wb') as image_file:
        image_file.write(image.read())
    ```

    Ten kod otwiera plik o nazwie `image.jpg` do zapisu, a następnie odczytuje wszystkie dane z obiektu `BytesIO` i zapisuje je do pliku.

    > 💁 Możesz przechwycić obraz bezpośrednio do pliku zamiast do obiektu `BytesIO`, podając nazwę pliku w wywołaniu `camera.capture`. Powodem użycia obiektu `BytesIO` jest to, że później w tej lekcji będziesz mógł wysłać obraz do swojego klasyfikatora obrazów.

1. Skieruj kamerę na coś i uruchom ten kod.

1. Obraz zostanie przechwycony i zapisany jako `image.jpg` w bieżącym folderze. Zobaczysz ten plik w eksploratorze VS Code. Wybierz plik, aby wyświetlić obraz. Jeśli wymaga obrotu, zaktualizuj linię `camera.rotation = 0` i zrób kolejne zdjęcie.

> 💁 Ten kod znajdziesz w folderze [code-camera/pi](../../../../../4-manufacturing/lessons/2-check-fruit-from-device/code-camera/pi).

😀 Twój program obsługujący kamerę działa poprawnie!

**Zastrzeżenie**:  
Ten dokument został przetłumaczony za pomocą usługi tłumaczeniowej AI [Co-op Translator](https://github.com/Azure/co-op-translator). Chociaż dokładamy wszelkich starań, aby zapewnić dokładność, prosimy pamiętać, że automatyczne tłumaczenia mogą zawierać błędy lub nieścisłości. Oryginalny dokument w jego rodzimym języku powinien być uznawany za autorytatywne źródło. W przypadku informacji o kluczowym znaczeniu zaleca się skorzystanie z profesjonalnego tłumaczenia przez człowieka. Nie ponosimy odpowiedzialności za jakiekolwiek nieporozumienia lub błędne interpretacje wynikające z użycia tego tłumaczenia.