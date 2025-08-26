<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "5a7262a0c48dfacdfe1ff91b20bf16fd",
  "translation_date": "2025-08-26T07:17:54+00:00",
  "source_file": "6-consumer/lessons/2-language-understanding/assignment.md",
  "language_code": "pl"
}
-->
# Anulowanie timera

## Instrukcje

Do tej pory w tej lekcji nauczyłeś model rozpoznawania ustawiania timera. Kolejną przydatną funkcją jest anulowanie timera - na przykład, gdy chleb jest już gotowy i można go wyjąć z piekarnika przed upływem czasu.

Dodaj nową intencję do swojej aplikacji LUIS, aby anulować timer. Nie będzie wymagała żadnych encji, ale potrzebne będą przykładowe zdania. Obsłuż to w swoim kodzie serverless, jeśli jest to najważniejsza intencja, logując, że intencja została rozpoznana i zwracając odpowiednią odpowiedź.

## Kryteria oceny

| Kryterium | Wzorowe | Wystarczające | Wymaga poprawy |
| --------- | ------- | ------------- | -------------- |
| Dodanie intencji anulowania timera do aplikacji LUIS | Udało się dodać intencję i wytrenować model | Udało się dodać intencję, ale nie wytrenować modelu | Nie udało się dodać intencji ani wytrenować modelu |
| Obsługa intencji w aplikacji serverless | Udało się wykryć intencję jako najważniejszą i zalogować ją | Udało się wykryć intencję jako najważniejszą | Nie udało się wykryć intencji jako najważniejszej |

**Zastrzeżenie**:  
Ten dokument został przetłumaczony za pomocą usługi tłumaczenia AI [Co-op Translator](https://github.com/Azure/co-op-translator). Chociaż staramy się zapewnić dokładność, prosimy pamiętać, że automatyczne tłumaczenia mogą zawierać błędy lub nieścisłości. Oryginalny dokument w jego rodzimym języku powinien być uznawany za autorytatywne źródło. W przypadku informacji krytycznych zaleca się skorzystanie z profesjonalnego tłumaczenia przez człowieka. Nie ponosimy odpowiedzialności za jakiekolwiek nieporozumienia lub błędne interpretacje wynikające z użycia tego tłumaczenia.