<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "e74eb2fc7cc3b81916b52e957802f182",
  "translation_date": "2025-08-26T06:31:40+00:00",
  "source_file": "4-manufacturing/lessons/1-train-fruit-detector/assignment.md",
  "language_code": "pl"
}
-->
# Trenuj swój klasyfikator dla wielu owoców i warzyw

## Instrukcje

W tej lekcji nauczyłeś się trenować klasyfikator obrazów, aby rozróżniać między dojrzałymi a niedojrzałymi owocami, ale tylko dla jednego rodzaju owocu. Klasyfikator można wytrenować tak, aby rozpoznawał wiele owoców, z różnym poziomem skuteczności w zależności od rodzaju owocu i różnicy między dojrzałym a niedojrzałym.

Na przykład, w przypadku owoców, które zmieniają kolor podczas dojrzewania, klasyfikatory obrazów mogą być mniej skuteczne niż czujnik koloru, ponieważ zazwyczaj działają na obrazach w skali szarości zamiast w pełnym kolorze.

Wytrenuj swój klasyfikator z innymi owocami, aby zobaczyć, jak dobrze działa, zwłaszcza gdy owoce wyglądają podobnie. Na przykład jabłka i pomidory.

## Kryteria oceny

| Kryterium | Wzorowe | Wystarczające | Wymaga poprawy |
| --------- | ------- | ------------- | -------------- |
| Wytrenowanie klasyfikatora dla wielu owoców | Udało się wytrenować klasyfikator dla wielu owoców | Udało się wytrenować klasyfikator dla jednego dodatkowego owocu | Nie udało się wytrenować klasyfikatora dla większej liczby owoców |
| Określenie skuteczności klasyfikatora | Udało się poprawnie skomentować, jak dobrze klasyfikator działał z różnymi owocami | Udało się zaobserwować i zaproponować sugestie dotyczące jego działania | Nie udało się skomentować, jak dobrze klasyfikator działał |

**Zastrzeżenie**:  
Ten dokument został przetłumaczony za pomocą usługi tłumaczenia AI [Co-op Translator](https://github.com/Azure/co-op-translator). Chociaż dokładamy wszelkich starań, aby zapewnić poprawność tłumaczenia, prosimy pamiętać, że automatyczne tłumaczenia mogą zawierać błędy lub nieścisłości. Oryginalny dokument w jego rodzimym języku powinien być uznawany za autorytatywne źródło. W przypadku informacji o kluczowym znaczeniu zaleca się skorzystanie z profesjonalnego tłumaczenia przez człowieka. Nie ponosimy odpowiedzialności za jakiekolwiek nieporozumienia lub błędne interpretacje wynikające z użycia tego tłumaczenia.