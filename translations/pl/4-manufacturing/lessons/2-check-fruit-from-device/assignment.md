<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "022e21f8629b721424c1de25195fff67",
  "translation_date": "2025-08-26T06:32:51+00:00",
  "source_file": "4-manufacturing/lessons/2-check-fruit-from-device/assignment.md",
  "language_code": "pl"
}
-->
# Reagowanie na wyniki klasyfikacji

## Instrukcje

Twoje urządzenie sklasyfikowało obrazy i posiada wartości dla przewidywań. Urządzenie może wykorzystać te informacje w dowolny sposób - może wysłać je do IoT Hub w celu przetworzenia przez inne systemy lub może sterować elementem wykonawczym, takim jak dioda LED, która zapala się, gdy owoc jest niedojrzały.

Dodaj kod do swojego urządzenia, aby reagowało w wybrany przez Ciebie sposób - na przykład wysyłając dane do IoT Hub, sterując elementem wykonawczym lub łącząc oba podejścia, wysyłając dane do IoT Hub z użyciem bezserwerowego kodu, który określa, czy owoc jest dojrzały, a następnie wysyła polecenie sterujące elementem wykonawczym.

## Kryteria oceny

| Kryterium | Wzorowe | Zadowalające | Wymaga poprawy |
| --------- | ------- | ------------ | -------------- |
| Reakcja na przewidywania | Udało się zaimplementować reakcję na przewidywania, która działa konsekwentnie dla przewidywań o tej samej wartości. | Udało się zaimplementować reakcję, która nie zależy od przewidywań, na przykład wysyłanie surowych danych do IoT Hub. | Nie udało się zaprogramować urządzenia, aby reagowało na przewidywania. |

**Zastrzeżenie**:  
Ten dokument został przetłumaczony za pomocą usługi tłumaczenia AI [Co-op Translator](https://github.com/Azure/co-op-translator). Chociaż dokładamy wszelkich starań, aby tłumaczenie było precyzyjne, prosimy pamiętać, że automatyczne tłumaczenia mogą zawierać błędy lub nieścisłości. Oryginalny dokument w jego rodzimym języku powinien być uznawany za wiarygodne źródło. W przypadku informacji o kluczowym znaczeniu zaleca się skorzystanie z profesjonalnego tłumaczenia przez człowieka. Nie ponosimy odpowiedzialności za jakiekolwiek nieporozumienia lub błędne interpretacje wynikające z użycia tego tłumaczenia.