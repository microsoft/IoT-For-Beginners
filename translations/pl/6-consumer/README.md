<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "5de7dc1e2ddc402d415473bb795568d4",
  "translation_date": "2025-08-26T07:12:18+00:00",
  "source_file": "6-consumer/README.md",
  "language_code": "pl"
}
-->
# Consumer IoT - budowa inteligentnego asystenta głosowego

Jedzenie zostało wyhodowane, przewiezione do zakładu przetwórczego, posortowane pod kątem jakości, sprzedane w sklepie, a teraz czas na gotowanie! Jednym z podstawowych elementów każdej kuchni jest minutnik. Na początku były to klepsydry – jedzenie było gotowe, gdy cały piasek przesypał się do dolnej bańki. Potem pojawiły się minutniki mechaniczne, a następnie elektryczne.

Najnowocześniejsze wersje są teraz częścią naszych inteligentnych urządzeń. W kuchniach na całym świecie można usłyszeć kucharzy wołających: „Hej Siri – ustaw minutnik na 10 minut” albo „Alexa – anuluj minutnik do chleba”. Już nie musisz wracać do kuchni, żeby sprawdzić minutnik – możesz to zrobić z telefonu albo po prostu wykrzykując polecenie w pokoju.

W tych 4 lekcjach nauczysz się, jak zbudować inteligentny minutnik, wykorzystując AI do rozpoznawania głosu, zrozumienia, o co prosisz, i odpowiedzi z informacjami o minutniku. Dodasz także obsługę wielu języków.

> ⚠️ Praca z danymi mowy i mikrofonu zużywa dużo pamięci, co oznacza, że łatwo osiągnąć limity na mikrokontrolerach. Projekt tutaj omija te problemy, ale pamiętaj, że laboratoria z Wio Terminal są złożone i mogą zająć więcej czasu niż inne laboratoria w tym kursie.

> 💁 Te lekcje wykorzystują pewne zasoby w chmurze. Jeśli nie ukończysz wszystkich lekcji w tym projekcie, upewnij się, że [posprzątasz swój projekt](../clean-up.md).

## Tematy

1. [Rozpoznawanie mowy za pomocą urządzenia IoT](./lessons/1-speech-recognition/README.md)
1. [Zrozumienie języka](./lessons/2-language-understanding/README.md)
1. [Ustawianie minutnika i udzielanie odpowiedzi głosowych](./lessons/3-spoken-feedback/README.md)
1. [Obsługa wielu języków](./lessons/4-multiple-language-support/README.md)

## Podziękowania

Wszystkie lekcje zostały napisane z ♥️ przez [Jim Bennett](https://GitHub.com/JimBobBennett)

**Zastrzeżenie**:  
Ten dokument został przetłumaczony za pomocą usługi tłumaczenia AI [Co-op Translator](https://github.com/Azure/co-op-translator). Chociaż dokładamy wszelkich starań, aby zapewnić precyzję, prosimy pamiętać, że automatyczne tłumaczenia mogą zawierać błędy lub nieścisłości. Oryginalny dokument w jego rodzimym języku powinien być uznawany za autorytatywne źródło. W przypadku informacji o kluczowym znaczeniu zaleca się skorzystanie z profesjonalnego tłumaczenia przez człowieka. Nie ponosimy odpowiedzialności za jakiekolwiek nieporozumienia lub błędne interpretacje wynikające z użycia tego tłumaczenia.