<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "da5d9360fe02fdcc1e91a725016c846d",
  "translation_date": "2025-08-26T07:19:01+00:00",
  "source_file": "6-consumer/lessons/3-spoken-feedback/assignment.md",
  "language_code": "pl"
}
-->
# Anulowanie timera

## Instrukcje

W zadaniu z ostatniej lekcji dodałeś intencję anulowania timera do LUIS. W tym zadaniu musisz obsłużyć tę intencję w kodzie serverless, wysłać polecenie do urządzenia IoT, a następnie anulować timer.

## Kryteria oceny

| Kryteria | Wzorowe | Zadowalające | Wymaga poprawy |
| -------- | ------- | ------------ | -------------- |
| Obsługa intencji w kodzie serverless i wysłanie polecenia | Udało się obsłużyć intencję i wysłać polecenie do urządzenia | Udało się obsłużyć intencję, ale nie udało się wysłać polecenia do urządzenia | Nie udało się obsłużyć intencji |
| Anulowanie timera na urządzeniu | Udało się odebrać polecenie i anulować timer | Udało się odebrać polecenie, ale nie anulować timera | Nie udało się odebrać polecenia |

**Zastrzeżenie**:  
Ten dokument został przetłumaczony za pomocą usługi tłumaczenia AI [Co-op Translator](https://github.com/Azure/co-op-translator). Chociaż dokładamy wszelkich starań, aby tłumaczenie było precyzyjne, prosimy pamiętać, że automatyczne tłumaczenia mogą zawierać błędy lub nieścisłości. Oryginalny dokument w jego rodzimym języku powinien być uznawany za wiarygodne źródło. W przypadku informacji o kluczowym znaczeniu zaleca się skorzystanie z profesjonalnego tłumaczenia przez człowieka. Nie ponosimy odpowiedzialności za jakiekolwiek nieporozumienia lub błędne interpretacje wynikające z użycia tego tłumaczenia.