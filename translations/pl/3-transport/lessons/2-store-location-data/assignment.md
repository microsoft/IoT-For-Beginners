<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "b2e0a965723082b068f735aec0faf3f6",
  "translation_date": "2025-08-26T07:37:00+00:00",
  "source_file": "3-transport/lessons/2-store-location-data/assignment.md",
  "language_code": "pl"
}
-->
# Zbadaj powiązania funkcji

## Instrukcje

Powiązania funkcji pozwalają Twojemu kodowi zapisywać blobsy w magazynie blobów poprzez ich zwracanie z funkcji `main`. Konto Azure Storage, kolekcja i inne szczegóły są skonfigurowane w pliku `function.json`.

Pracując z Azure lub innymi technologiami Microsoftu, najlepszym źródłem informacji jest [dokumentacja Microsoftu na stronie docs.com](https://docs.microsoft.com/?WT.mc_id=academic-17441-jabenn). W tym zadaniu będziesz musiał zapoznać się z dokumentacją dotyczącą powiązań w Azure Functions, aby dowiedzieć się, jak skonfigurować powiązanie wyjściowe.

Kilka stron, od których warto zacząć:

* [Koncepcje wyzwalaczy i powiązań w Azure Functions](https://docs.microsoft.com/azure/azure-functions/functions-triggers-bindings?WT.mc_id=academic-17441-jabenn&tabs=python)
* [Przegląd powiązań magazynu blobów dla Azure Functions](https://docs.microsoft.com/azure/azure-functions/functions-bindings-storage-blob?WT.mc_id=academic-17441-jabenn)
* [Powiązanie wyjściowe magazynu blobów dla Azure Functions](https://docs.microsoft.com/azure/azure-functions/functions-bindings-storage-blob-output?WT.mc_id=academic-17441-jabenn&tabs=python)

## Kryteria oceny

| Kryterium | Wzorowe | Zadowalające | Wymaga poprawy |
| --------- | ------- | ------------ | -------------- |
| Konfiguracja powiązania wyjściowego magazynu blobów | Udało się skonfigurować powiązanie wyjściowe, zwrócić blob i pomyślnie zapisać go w magazynie blobów | Udało się skonfigurować powiązanie wyjściowe lub zwrócić blob, ale nie udało się zapisać go w magazynie blobów | Nie udało się skonfigurować powiązania wyjściowego |

**Zastrzeżenie**:  
Ten dokument został przetłumaczony za pomocą usługi tłumaczenia AI [Co-op Translator](https://github.com/Azure/co-op-translator). Chociaż dokładamy wszelkich starań, aby zapewnić poprawność tłumaczenia, prosimy pamiętać, że automatyczne tłumaczenia mogą zawierać błędy lub nieścisłości. Oryginalny dokument w jego rodzimym języku powinien być uznawany za autorytatywne źródło. W przypadku informacji o kluczowym znaczeniu zaleca się skorzystanie z profesjonalnego tłumaczenia przez człowieka. Nie ponosimy odpowiedzialności za jakiekolwiek nieporozumienia lub błędne interpretacje wynikające z korzystania z tego tłumaczenia.