<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "ed0fbd6aed084bfba7d5e2f206968c50",
  "translation_date": "2025-08-26T06:45:48+00:00",
  "source_file": "2-farm/lessons/3-automated-plant-watering/assignment.md",
  "language_code": "pl"
}
-->
# Stwórz bardziej efektywny cykl nawadniania

## Instrukcje

W tej lekcji omówiono, jak sterować przekaźnikiem za pomocą danych z czujnika, a ten przekaźnik może z kolei sterować pompą w systemie nawadniania. Dla określonej objętości gleby uruchomienie pompy na ustalony czas powinno zawsze mieć taki sam wpływ na wilgotność gleby. Oznacza to, że możesz oszacować, ile sekund nawadniania odpowiada określonemu spadkowi odczytu wilgotności gleby. Korzystając z tych danych, możesz zbudować bardziej kontrolowany system nawadniania.

W tym zadaniu obliczysz, jak długo pompa powinna działać, aby osiągnąć określony wzrost wilgotności gleby.

> ⚠️ Jeśli używasz wirtualnego sprzętu IoT, możesz przejść przez ten proces, ale zasymuluj wyniki, ręcznie zwiększając odczyt wilgotności gleby o stałą wartość na sekundę, gdy przekaźnik jest włączony.

1. Zacznij od suchej gleby. Zmierz wilgotność gleby.

1. Dodaj stałą ilość wody, albo uruchamiając pompę na 1 sekundę, albo wlewając określoną ilość wody.

    > Pompa powinna zawsze działać z stałą wydajnością, więc każda sekunda jej pracy powinna dostarczać taką samą ilość wody.

1. Poczekaj, aż poziom wilgotności gleby się ustabilizuje, i wykonaj odczyt.

1. Powtórz ten proces kilkukrotnie i stwórz tabelę wyników. Przykład takiej tabeli znajduje się poniżej.

    | Całkowity czas pracy pompy | Wilgotność gleby | Spadek |
    | --- | --: | -: |
    | Sucha | 643 |  0 |
    | 1s  | 621 | 22 |
    | 2s  | 601 | 20 |
    | 3s  | 579 | 22 |
    | 4s  | 560 | 19 |
    | 5s  | 539 | 21 |
    | 6s  | 521 | 18 |

1. Oblicz średni wzrost wilgotności gleby na sekundę pracy pompy. W powyższym przykładzie każda sekunda pracy pompy zmniejsza odczyt średnio o 20,3.

1. Wykorzystaj te dane, aby poprawić efektywność kodu serwera, uruchamiając pompę na wymagany czas, aby osiągnąć potrzebny poziom wilgotności gleby.

## Kryteria oceny

| Kryteria | Wzorowe | Wystarczające | Wymaga poprawy |
| -------- | --------- | -------- | ----------------- |
| Zbieranie danych o wilgotności gleby | Potrafi zebrać wiele odczytów po dodaniu stałych ilości wody | Potrafi zebrać kilka odczytów przy użyciu stałych ilości wody | Potrafi zebrać tylko jeden lub dwa odczyty albo nie potrafi użyć stałych ilości wody |
| Kalibracja kodu serwera | Potrafi obliczyć średni spadek odczytu wilgotności gleby i zaktualizować kod serwera, aby to uwzględnić | Potrafi obliczyć średni spadek, ale nie potrafi zaktualizować kodu serwera, lub nie potrafi poprawnie obliczyć średniej, ale używa tej wartości do poprawnej aktualizacji kodu serwera | Nie potrafi obliczyć średniej ani zaktualizować kodu serwera |

**Zastrzeżenie**:  
Ten dokument został przetłumaczony za pomocą usługi tłumaczenia AI [Co-op Translator](https://github.com/Azure/co-op-translator). Chociaż dokładamy wszelkich starań, aby tłumaczenie było precyzyjne, prosimy pamiętać, że automatyczne tłumaczenia mogą zawierać błędy lub nieścisłości. Oryginalny dokument w jego rodzimym języku powinien być uznawany za wiarygodne źródło. W przypadku informacji o kluczowym znaczeniu zaleca się skorzystanie z profesjonalnego tłumaczenia przez człowieka. Nie ponosimy odpowiedzialności za jakiekolwiek nieporozumienia lub błędne interpretacje wynikające z użycia tego tłumaczenia.