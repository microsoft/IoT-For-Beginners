# Sterowanie przekaźnikiem - Raspberry Pi

W tej części lekcji dodasz przekaźnik do swojego Raspberry Pi, oprócz czujnika wilgotności gleby, i będziesz nim sterować na podstawie poziomu wilgotności gleby.

## Sprzęt

Raspberry Pi potrzebuje przekaźnika.

Przekaźnik, którego użyjesz, to [Grove relay](https://www.seeedstudio.com/Grove-Relay.html), przekaźnik normalnie otwarty (oznacza to, że obwód wyjściowy jest otwarty lub odłączony, gdy nie jest wysyłany sygnał do przekaźnika), który obsługuje obwody wyjściowe do 250V i 10A.

Jest to cyfrowy aktuator, więc podłącza się go do cyfrowego pinu na Grove Base Hat.

### Podłącz przekaźnik

Przekaźnik Grove można podłączyć do Raspberry Pi.

#### Zadanie

Podłącz przekaźnik.

![Przekaźnik Grove](../../../../../translated_images/pl/grove-relay.d426958ca210fbd0.webp)

1. Włóż jeden koniec kabla Grove do gniazda w przekaźniku. Kabel wejdzie tylko w jednym kierunku.

1. Przy wyłączonym Raspberry Pi podłącz drugi koniec kabla Grove do cyfrowego gniazda oznaczonego **D5** na Grove Base Hat zamontowanym na Pi. To gniazdo znajduje się drugie od lewej, w rzędzie gniazd obok pinów GPIO. Pozostaw czujnik wilgotności gleby podłączony do gniazda **A0**.

![Przekaźnik Grove podłączony do gniazda D5, a czujnik wilgotności gleby podłączony do gniazda A0](../../../../../translated_images/pl/pi-relay-and-soil-moisture-sensor.02f3198975b8c53e.webp)

1. Włóż czujnik wilgotności gleby do gleby, jeśli nie jest już tam z poprzedniej lekcji.

## Programowanie przekaźnika

Raspberry Pi można teraz zaprogramować do obsługi podłączonego przekaźnika.

### Zadanie

Zaprogramuj urządzenie.

1. Włącz Raspberry Pi i poczekaj, aż się uruchomi.

1. Otwórz projekt `soil-moisture-sensor` z poprzedniej lekcji w VS Code, jeśli nie jest już otwarty. Będziesz dodawać kod do tego projektu.

1. Dodaj poniższy kod do pliku `app.py` poniżej istniejących importów:

    ```python
    from grove.grove_relay import GroveRelay
    ```

    Ten kod importuje `GroveRelay` z bibliotek Python Grove, aby umożliwić interakcję z przekaźnikiem Grove.

1. Dodaj poniższy kod poniżej deklaracji klasy `ADC`, aby utworzyć instancję `GroveRelay`:

    ```python
    relay = GroveRelay(5)
    ```

    Ten kod tworzy przekaźnik używając pinu **D5**, cyfrowego pinu, do którego podłączyłeś przekaźnik.

1. Aby przetestować działanie przekaźnika, dodaj poniższy kod do pętli `while True:`:

    ```python
    relay.on()
    time.sleep(.5)
    relay.off()
    ```

    Kod włącza przekaźnik, czeka 0,5 sekundy, a następnie wyłącza przekaźnik.

1. Uruchom aplikację w Pythonie. Przekaźnik będzie włączał się i wyłączał co 10 sekund, z półsekundowym opóźnieniem między włączeniem a wyłączeniem. Usłyszysz kliknięcie przekaźnika przy włączaniu i wyłączaniu. Dioda LED na płytce Grove zapali się, gdy przekaźnik jest włączony, a zgaśnie, gdy jest wyłączony.

    ![Przekaźnik włączający się i wyłączający](../../../../../images/relay-turn-on-off.gif)

## Sterowanie przekaźnikiem na podstawie wilgotności gleby

Teraz, gdy przekaźnik działa, można nim sterować w odpowiedzi na odczyty wilgotności gleby.

### Zadanie

Steruj przekaźnikiem.

1. Usuń 3 linie kodu, które dodałeś do testowania przekaźnika. Zastąp je poniższym kodem:

    ```python
    if soil_moisture > 450:
        print("Soil Moisture is too low, turning relay on.")
        relay.on()
    else:
        print("Soil Moisture is ok, turning relay off.")
        relay.off()
    ```

    Ten kod sprawdza poziom wilgotności gleby z czujnika wilgotności gleby. Jeśli poziom wilgotności jest powyżej 450, włącza przekaźnik, a wyłącza go, gdy poziom spada poniżej 450.

    > 💁 Pamiętaj, że pojemnościowy czujnik wilgotności gleby odczytuje: im niższy poziom wilgotności gleby, tym więcej wilgoci znajduje się w glebie i odwrotnie.

1. Uruchom aplikację w Pythonie. Zobaczysz, jak przekaźnik włącza się lub wyłącza w zależności od poziomu wilgotności gleby. Wypróbuj w suchej glebie, a następnie dodaj wodę.

    ```output
    Soil Moisture: 638
    Soil Moisture is too low, turning relay on.
    Soil Moisture: 452
    Soil Moisture is too low, turning relay on.
    Soil Moisture: 347
    Soil Moisture is ok, turning relay off.
    ```

> 💁 Ten kod znajdziesz w folderze [code-relay/pi](../../../../../2-farm/lessons/3-automated-plant-watering/code-relay/pi).

😀 Twój program sterujący przekaźnikiem na podstawie czujnika wilgotności gleby zakończył się sukcesem!

**Zastrzeżenie**:  
Ten dokument został przetłumaczony za pomocą usługi tłumaczeniowej AI [Co-op Translator](https://github.com/Azure/co-op-translator). Chociaż dokładamy wszelkich starań, aby zapewnić poprawność tłumaczenia, prosimy pamiętać, że automatyczne tłumaczenia mogą zawierać błędy lub nieścisłości. Oryginalny dokument w jego rodzimym języku powinien być uznawany za wiarygodne źródło. W przypadku informacji o kluczowym znaczeniu zaleca się skorzystanie z profesjonalnego tłumaczenia przez człowieka. Nie ponosimy odpowiedzialności za jakiekolwiek nieporozumienia lub błędne interpretacje wynikające z użycia tego tłumaczenia.