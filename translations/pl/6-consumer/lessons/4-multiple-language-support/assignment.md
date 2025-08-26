<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "701f4a4466f9309b6e1d863077df0c06",
  "translation_date": "2025-08-26T07:14:05+00:00",
  "source_file": "6-consumer/lessons/4-multiple-language-support/assignment.md",
  "language_code": "pl"
}
-->
# Stwórz uniwersalny translator

## Instrukcje

Uniwersalny translator to urządzenie, które potrafi tłumaczyć między wieloma językami, umożliwiając komunikację osobom mówiącym w różnych językach. Wykorzystaj wiedzę zdobytą w ostatnich lekcjach, aby stworzyć uniwersalny translator przy użyciu 2 urządzeń IoT.

> Jeśli nie masz 2 urządzeń, postępuj zgodnie z krokami opisanymi w poprzednich lekcjach, aby skonfigurować wirtualne urządzenie IoT jako jedno z urządzeń IoT.

Powinieneś skonfigurować jedno urządzenie dla jednego języka, a drugie dla innego. Każde urządzenie powinno przyjmować mowę, konwertować ją na tekst, wysyłać do drugiego urządzenia za pośrednictwem IoT Hub i aplikacji Functions, a następnie tłumaczyć i odtwarzać przetłumaczoną mowę.

> 💁 Wskazówka: Wysyłając mowę z jednego urządzenia do drugiego, prześlij również informację o języku, w którym została wypowiedziana, co ułatwi tłumaczenie. Możesz nawet sprawić, aby każde urządzenie rejestrowało się najpierw w IoT Hub i aplikacji Functions, przekazując obsługiwany język do zapisania w Azure Storage. Następnie możesz użyć aplikacji Functions do tłumaczenia, przesyłając przetłumaczony tekst do urządzenia IoT.

## Kryteria oceny

| Kryterium | Wzorowe | Zadowalające | Wymaga poprawy |
| --------- | ------- | ------------ | -------------- |
| Stworzenie uniwersalnego translatora | Udało się stworzyć uniwersalny translator, który konwertuje mowę wykrytą przez jedno urządzenie na mowę odtwarzaną przez drugie urządzenie w innym języku | Udało się uruchomić niektóre komponenty, takie jak przechwytywanie mowy lub tłumaczenie, ale nie udało się zbudować kompletnego rozwiązania | Nie udało się stworzyć żadnej części działającego uniwersalnego translatora |

**Zastrzeżenie**:  
Ten dokument został przetłumaczony za pomocą usługi tłumaczenia AI [Co-op Translator](https://github.com/Azure/co-op-translator). Chociaż dokładamy wszelkich starań, aby tłumaczenie było precyzyjne, prosimy pamiętać, że automatyczne tłumaczenia mogą zawierać błędy lub nieścisłości. Oryginalny dokument w jego rodzimym języku powinien być uznawany za wiarygodne źródło. W przypadku informacji o kluczowym znaczeniu zaleca się skorzystanie z profesjonalnego tłumaczenia przez człowieka. Nie ponosimy odpowiedzialności za jakiekolwiek nieporozumienia lub błędne interpretacje wynikające z użycia tego tłumaczenia.