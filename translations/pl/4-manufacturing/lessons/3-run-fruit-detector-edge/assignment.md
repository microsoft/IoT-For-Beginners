<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "cc7ad255517f5f618f9c8899e6ff6783",
  "translation_date": "2025-08-26T06:37:14+00:00",
  "source_file": "4-manufacturing/lessons/3-run-fruit-detector-edge/assignment.md",
  "language_code": "pl"
}
-->
# Uruchamianie innych usług na urządzeniach brzegowych

## Instrukcje

Na urządzeniach brzegowych można uruchamiać nie tylko klasyfikatory obrazów – wszystko, co można zapakować w kontener, może zostać wdrożone na urządzeniu IoT Edge. Bezserwerowy kod działający jako Azure Functions, na przykład wyzwalacze, które stworzyłeś w poprzednich lekcjach, może być uruchamiany w kontenerach, a tym samym na IoT Edge.

Wybierz jedną z poprzednich lekcji i spróbuj uruchomić aplikację Azure Functions w kontenerze IoT Edge. Możesz znaleźć przewodnik pokazujący, jak to zrobić, używając innego projektu aplikacji Functions w [Samouczek: Wdrażanie Azure Functions jako modułów IoT Edge w dokumentacji Microsoft](https://docs.microsoft.com/azure/iot-edge/tutorial-deploy-function?WT.mc_id=academic-17441-jabenn&view=iotedge-2020-11).

## Kryteria oceny

| Kryterium | Wzorowe | Zadowalające | Wymaga poprawy |
| --------- | -------- | ------------ | -------------- |
| Wdrożenie aplikacji Azure Functions na IoT Edge | Udało się wdrożyć aplikację Azure Functions na IoT Edge i użyć jej z urządzeniem IoT do uruchomienia wyzwalacza na podstawie danych IoT | Udało się wdrożyć aplikację Functions na IoT Edge, ale nie udało się uruchomić wyzwalacza | Nie udało się wdrożyć aplikacji Functions na IoT Edge |

**Zastrzeżenie**:  
Ten dokument został przetłumaczony za pomocą usługi tłumaczenia AI [Co-op Translator](https://github.com/Azure/co-op-translator). Chociaż dokładamy wszelkich starań, aby zapewnić poprawność tłumaczenia, prosimy pamiętać, że automatyczne tłumaczenia mogą zawierać błędy lub nieścisłości. Oryginalny dokument w jego rodzimym języku powinien być uznawany za autorytatywne źródło. W przypadku informacji o kluczowym znaczeniu zaleca się skorzystanie z profesjonalnego tłumaczenia przez człowieka. Nie ponosimy odpowiedzialności za jakiekolwiek nieporozumienia lub błędne interpretacje wynikające z użycia tego tłumaczenia.