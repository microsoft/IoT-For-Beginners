<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "f3c5d8afa2ef6a0b425ef8ff20615cb4",
  "translation_date": "2025-08-26T06:46:10+00:00",
  "source_file": "2-farm/lessons/3-automated-plant-watering/wio-terminal-relay.md",
  "language_code": "pl"
}
-->
# Sterowanie przekaźnikiem - Wio Terminal

W tej części lekcji dodasz przekaźnik do swojego Wio Terminal, oprócz czujnika wilgotności gleby, i będziesz nim sterować na podstawie poziomu wilgotności gleby.

## Sprzęt

Wio Terminal potrzebuje przekaźnika.

Przekaźnik, którego użyjesz, to [Grove relay](https://www.seeedstudio.com/Grove-Relay.html), przekaźnik normalnie otwarty (oznacza to, że obwód wyjściowy jest otwarty lub odłączony, gdy nie jest wysyłany sygnał do przekaźnika), który obsługuje obwody wyjściowe do 250V i 10A.

Jest to cyfrowy aktuator, więc podłącza się go do cyfrowych pinów w Wio Terminal. Połączony port analogowo-cyfrowy jest już używany przez czujnik wilgotności gleby, więc przekaźnik podłącza się do drugiego portu, który jest połączonym portem I

**Zastrzeżenie**:  
Ten dokument został przetłumaczony za pomocą usługi tłumaczenia AI [Co-op Translator](https://github.com/Azure/co-op-translator). Chociaż dokładamy wszelkich starań, aby tłumaczenie było precyzyjne, prosimy pamiętać, że automatyczne tłumaczenia mogą zawierać błędy lub nieścisłości. Oryginalny dokument w jego rodzimym języku powinien być uznawany za wiarygodne źródło. W przypadku informacji o kluczowym znaczeniu zaleca się skorzystanie z profesjonalnego tłumaczenia przez człowieka. Nie ponosimy odpowiedzialności za jakiekolwiek nieporozumienia lub błędne interpretacje wynikające z użycia tego tłumaczenia.