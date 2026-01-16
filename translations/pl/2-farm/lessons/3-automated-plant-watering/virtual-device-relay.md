<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "f8f541ee945545017a51aaf309aa37c3",
  "translation_date": "2025-08-26T06:46:34+00:00",
  "source_file": "2-farm/lessons/3-automated-plant-watering/virtual-device-relay.md",
  "language_code": "pl"
}
-->
# Sterowanie przekaźnikiem - Wirtualny sprzęt IoT

W tej części lekcji dodasz przekaźnik do swojego wirtualnego urządzenia IoT, oprócz czujnika wilgotności gleby, i będziesz nim sterować w zależności od poziomu wilgotności gleby.

## Wirtualny sprzęt

Wirtualne urządzenie IoT będzie korzystać z symulowanego przekaźnika Grove. Dzięki temu laboratorium pozostaje takie samo, jak w przypadku użycia Raspberry Pi z fizycznym przekaźnikiem Grove.

W fizycznym urządzeniu IoT przekaźnik byłby przekaźnikiem normalnie otwartym (co oznacza, że obwód wyjściowy jest otwarty lub rozłączony, gdy nie jest wysyłany sygnał do przekaźnika). Taki przekaźnik może obsługiwać obwody wyjściowe do 250V i 10A.

### Dodanie przekaźnika do CounterFit

Aby użyć wirtualnego przekaźnika, musisz dodać go do aplikacji CounterFit.

#### Zadanie

Dodaj przekaźnik do aplikacji CounterFit.

1. Otwórz projekt `soil-moisture-sensor` z poprzedniej lekcji w VS Code, jeśli nie jest jeszcze otwarty. Będziesz dodawać do tego projektu.

1. Upewnij się, że aplikacja webowa CounterFit jest uruchomiona.

1. Utwórz przekaźnik:

    1. W polu *Create actuator* w panelu *Actuators* rozwiń pole *Actuator type* i wybierz *Relay*.

    1. Ustaw *Pin* na *5*.

    1. Wybierz przycisk **Add**, aby utworzyć przekaźnik na Pinie 5.

    ![Ustawienia przekaźnika](../../../../../translated_images/pl/counterfit-create-relay.fa7c40fd0f2f6afc33b35ea94fcb235085be4861e14e3fe6b9b7bcfc82d1c888.png)

    Przekaźnik zostanie utworzony i pojawi się na liście aktuatorów.

    ![Utworzony przekaźnik](../../../../../translated_images/pl/counterfit-relay.bbf74c1dbdc8b9acd983367fcbd06703a402aefef6af54ddb28e11307ba8a12c.png)

## Programowanie przekaźnika

Aplikacja czujnika wilgotności gleby może teraz zostać zaprogramowana do korzystania z wirtualnego przekaźnika.

### Zadanie

Zaprogramuj wirtualne urządzenie.

1. Otwórz projekt `soil-moisture-sensor` z poprzedniej lekcji w VS Code, jeśli nie jest jeszcze otwarty. Będziesz dodawać do tego projektu.

1. Dodaj poniższy kod do pliku `app.py` poniżej istniejących importów:

    ```python
    from counterfit_shims_grove.grove_relay import GroveRelay
    ```

    Ten kod importuje `GroveRelay` z bibliotek Grove Python shim, aby umożliwić interakcję z wirtualnym przekaźnikiem Grove.

1. Dodaj poniższy kod poniżej deklaracji klasy `ADC`, aby utworzyć instancję `GroveRelay`:

    ```python
    relay = GroveRelay(5)
    ```

    Tworzy to przekaźnik używający pinu **5**, do którego podłączyłeś przekaźnik.

1. Aby przetestować działanie przekaźnika, dodaj poniższy kod do pętli `while True:`:

    ```python
    relay.on()
    time.sleep(.5)
    relay.off()
    ```

    Kod włącza przekaźnik, czeka 0,5 sekundy, a następnie wyłącza przekaźnik.

1. Uruchom aplikację w Pythonie. Przekaźnik będzie włączał się i wyłączał co 10 sekund, z półsekundowym opóźnieniem między włączeniem a wyłączeniem. Zobaczysz, jak wirtualny przekaźnik w aplikacji CounterFit zamyka się i otwiera, gdy przekaźnik jest włączany i wyłączany.

    ![Wirtualny przekaźnik włączający się i wyłączający](../../../../../images/virtual-relay-turn-on-off.gif)

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

    Ten kod sprawdza poziom wilgotności gleby z czujnika wilgotności. Jeśli poziom jest powyżej 450, włącza przekaźnik, a jeśli spada poniżej 450, wyłącza go.

    > 💁 Pamiętaj, że pojemnościowy czujnik wilgotności gleby odczytuje: im niższy poziom wilgotności gleby, tym więcej wilgoci znajduje się w glebie i odwrotnie.

1. Uruchom aplikację w Pythonie. Zobaczysz, jak przekaźnik włącza się lub wyłącza w zależności od poziomów wilgotności gleby. Zmień ustawienia *Value* lub *Random* dla czujnika wilgotności gleby, aby zobaczyć zmiany wartości.

    ```output
    Soil Moisture: 638
    Soil Moisture is too low, turning relay on.
    Soil Moisture: 452
    Soil Moisture is too low, turning relay on.
    Soil Moisture: 347
    Soil Moisture is ok, turning relay off.
    ```

> 💁 Ten kod znajdziesz w folderze [code-relay/virtual-device](../../../../../2-farm/lessons/3-automated-plant-watering/code-relay/virtual-device).

😀 Twój program wirtualnego czujnika wilgotności gleby sterujący przekaźnikiem zakończył się sukcesem!

**Zastrzeżenie**:  
Ten dokument został przetłumaczony za pomocą usługi tłumaczeniowej AI [Co-op Translator](https://github.com/Azure/co-op-translator). Chociaż dokładamy wszelkich starań, aby zapewnić dokładność, prosimy pamiętać, że automatyczne tłumaczenia mogą zawierać błędy lub nieścisłości. Oryginalny dokument w jego rodzimym języku powinien być uznawany za wiarygodne źródło. W przypadku informacji krytycznych zaleca się skorzystanie z profesjonalnego tłumaczenia wykonanego przez człowieka. Nie ponosimy odpowiedzialności za jakiekolwiek nieporozumienia lub błędne interpretacje wynikające z korzystania z tego tłumaczenia.