<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "34010c663d96d5f419eda6ac2366a78d",
  "translation_date": "2025-08-26T06:57:05+00:00",
  "source_file": "2-farm/lessons/6-keep-your-plant-secure/assignment.md",
  "language_code": "pl"
}
-->
# Zbuduj nowe urządzenie IoT

## Instrukcje

W ciągu ostatnich 6 lekcji nauczyłeś się o cyfrowym rolnictwie oraz o tym, jak używać urządzeń IoT do zbierania danych w celu przewidywania wzrostu roślin i automatyzacji podlewania na podstawie odczytów wilgotności gleby.

Wykorzystaj zdobytą wiedzę, aby zbudować nowe urządzenie IoT, używając wybranego sensora i aktuatora. Wyślij dane telemetryczne do IoT Hub i użyj ich do sterowania aktuatorami za pomocą kodu bezserwerowego. Możesz użyć sensora i aktuatora, które już były używane w tym lub poprzednim projekcie, albo, jeśli masz inne komponenty, spróbuj czegoś nowego.

## Kryteria oceny

| Kryterium | Wzorowe | Wystarczające | Wymaga poprawy |
| --------- | ------- | ------------- | -------------- |
| Zaprogramowanie urządzenia IoT do użycia sensora i aktuatora | Zaprogramowano urządzenie IoT, które działa z sensorem i aktuatorem | Zaprogramowano urządzenie IoT, które działa z sensorem lub aktuatorem | Nie udało się zaprogramować urządzenia IoT do użycia sensora lub aktuatora |
| Połączenie urządzenia IoT z IoT Hub | Udało się wdrożyć IoT Hub, wysyłać do niego dane telemetryczne i odbierać polecenia | Udało się wdrożyć IoT Hub i wysyłać dane telemetryczne lub odbierać polecenia | Nie udało się wdrożyć IoT Hub ani nawiązać komunikacji z urządzeniem IoT |
| Sterowanie aktuatorami za pomocą kodu bezserwerowego | Udało się wdrożyć funkcję Azure do sterowania urządzeniem wyzwalaną przez zdarzenia telemetryczne | Udało się wdrożyć funkcję Azure wyzwalaną przez zdarzenia telemetryczne, ale nie udało się sterować aktuatorami | Nie udało się wdrożyć funkcji Azure |

**Zastrzeżenie**:  
Ten dokument został przetłumaczony za pomocą usługi tłumaczenia AI [Co-op Translator](https://github.com/Azure/co-op-translator). Chociaż dokładamy wszelkich starań, aby tłumaczenie było precyzyjne, prosimy pamiętać, że automatyczne tłumaczenia mogą zawierać błędy lub nieścisłości. Oryginalny dokument w jego rodzimym języku powinien być uznawany za wiarygodne źródło. W przypadku informacji o kluczowym znaczeniu zaleca się skorzystanie z profesjonalnego tłumaczenia przez człowieka. Nie ponosimy odpowiedzialności za jakiekolwiek nieporozumienia lub błędne interpretacje wynikające z użycia tego tłumaczenia.