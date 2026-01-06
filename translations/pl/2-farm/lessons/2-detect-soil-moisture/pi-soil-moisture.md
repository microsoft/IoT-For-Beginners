<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "9d4d00a47d5d0f3e6ce42c0d1020064a",
  "translation_date": "2025-08-26T06:52:28+00:00",
  "source_file": "2-farm/lessons/2-detect-soil-moisture/pi-soil-moisture.md",
  "language_code": "pl"
}
-->
# Pomiar wilgotności gleby - Raspberry Pi

W tej części lekcji dodasz pojemnościowy czujnik wilgotności gleby do swojego Raspberry Pi i odczytasz z niego wartości.

## Sprzęt

Do Raspberry Pi potrzebny jest pojemnościowy czujnik wilgotności gleby.

Czujnik, którego użyjesz, to [Pojemnościowy Czujnik Wilgotności Gleby](https://www.seeedstudio.com/Grove-Capacitive-Moisture-Sensor-Corrosion-Resistant.html), który mierzy wilgotność gleby poprzez wykrywanie jej pojemności, właściwości zmieniającej się wraz ze zmianą wilgotności gleby. Wraz ze wzrostem wilgotności gleby napięcie maleje.

Jest to czujnik analogowy, który korzysta z analogowego pinu oraz 10-bitowego przetwornika ADC w Grove Base Hat na Raspberry Pi, aby przekształcić napięcie na sygnał cyfrowy w zakresie od 1 do 1 023. Następnie sygnał ten jest przesyłany przez I²C za pomocą pinów GPIO na Raspberry Pi.

### Podłączanie czujnika wilgotności gleby

Czujnik wilgotności gleby Grove można podłączyć do Raspberry Pi.

#### Zadanie - podłącz czujnik wilgotności gleby

Podłącz czujnik wilgotności gleby.

![Czujnik wilgotności gleby Grove](../../../../../translated_images/grove-capacitive-soil-moisture-sensor.e7f0776cce30e78be5cc5a07839385fd6718857f31b5bf5ad3d0c73c83b2f0ef.pl.png)

1. Włóż jeden koniec kabla Grove do gniazda na czujniku wilgotności gleby. Kabel można włożyć tylko w jeden sposób.

1. Przy wyłączonym Raspberry Pi podłącz drugi koniec kabla Grove do gniazda analogowego oznaczonego **A0** na Grove Base Hat przymocowanym do Raspberry Pi. To gniazdo znajduje się drugie od prawej strony w rzędzie gniazd obok pinów GPIO.

![Czujnik wilgotności gleby Grove podłączony do gniazda A0](../../../../../translated_images/pi-soil-moisture-sensor.fdd7eb2393792cf6739cacf1985d9f55beda16d372f30d0b5a51d586f978a870.pl.png)

1. Włóż czujnik wilgotności gleby do gleby. Na czujniku znajduje się linia oznaczająca "najwyższy poziom" - biała linia przecinająca czujnik. Włóż czujnik do gleby do tej linii, ale nie głębiej.

![Czujnik wilgotności gleby Grove w glebie](../../../../../translated_images/soil-moisture-sensor-in-soil.bfad91002bda5e96.pl.png)

## Programowanie czujnika wilgotności gleby

Teraz Raspberry Pi można zaprogramować do obsługi podłączonego czujnika wilgotności gleby.

### Zadanie - zaprogramuj czujnik wilgotności gleby

Zaprogramuj urządzenie.

1. Włącz Raspberry Pi i poczekaj, aż się uruchomi.

1. Uruchom VS Code, bezpośrednio na Raspberry Pi lub za pomocą rozszerzenia Remote SSH.

    > ⚠️ Możesz odwołać się do [instrukcji dotyczących konfiguracji i uruchamiania VS Code w lekcji 1 - nightlight, jeśli to konieczne](../../../1-getting-started/lessons/1-introduction-to-iot/pi.md).

1. W terminalu utwórz nowy folder w katalogu domowym użytkownika `pi` o nazwie `soil-moisture-sensor`. W tym folderze utwórz plik o nazwie `app.py`.

1. Otwórz ten folder w VS Code.

1. Dodaj poniższy kod do pliku `app.py`, aby zaimportować wymagane biblioteki:

    ```python
    import time
    from grove.adc import ADC
    ```

    Instrukcja `import time` importuje moduł `time`, który będzie używany później w tym zadaniu.

    Instrukcja `from grove.adc import ADC` importuje `ADC` z bibliotek Python Grove. Ta biblioteka zawiera kod do obsługi przetwornika analogowo-cyfrowego na Grove Base Hat i odczytu napięć z czujników analogowych.

1. Dodaj poniższy kod, aby utworzyć instancję klasy `ADC`:

    ```python
    adc = ADC()
    ```

1. Dodaj nieskończoną pętlę, która odczytuje dane z ADC na pinie A0 i zapisuje wynik w konsoli. Pętla ta może następnie usypiać na 10 sekund między odczytami.

    ```python
    while True:
        soil_moisture = adc.read(0)
        print("Soil moisture:", soil_moisture)

        time.sleep(10)
    ```

1. Uruchom aplikację w Pythonie. Zobaczysz pomiary wilgotności gleby wyświetlane w konsoli. Dodaj wodę do gleby lub wyjmij czujnik z gleby i obserwuj zmieniające się wartości.

    ```output
    pi@raspberrypi:~/soil-moisture-sensor $ python3 app.py 
    Soil moisture: 615
    Soil moisture: 612
    Soil moisture: 498
    Soil moisture: 493
    Soil moisture: 490
    Soil Moisture: 388
    ```

    W powyższym przykładzie wyjścia widać, jak napięcie spada po dodaniu wody.

> 💁 Kod ten znajdziesz w folderze [code/pi](../../../../../2-farm/lessons/2-detect-soil-moisture/code/pi).

😀 Twój program do obsługi czujnika wilgotności gleby działa poprawnie!

**Zastrzeżenie**:  
Ten dokument został przetłumaczony za pomocą usługi tłumaczeniowej AI [Co-op Translator](https://github.com/Azure/co-op-translator). Chociaż dokładamy wszelkich starań, aby zapewnić poprawność tłumaczenia, prosimy pamiętać, że automatyczne tłumaczenia mogą zawierać błędy lub nieścisłości. Oryginalny dokument w jego rodzimym języku powinien być uznawany za autorytatywne źródło. W przypadku informacji o kluczowym znaczeniu zaleca się skorzystanie z profesjonalnego tłumaczenia przez człowieka. Nie ponosimy odpowiedzialności za jakiekolwiek nieporozumienia lub błędne interpretacje wynikające z korzystania z tego tłumaczenia.