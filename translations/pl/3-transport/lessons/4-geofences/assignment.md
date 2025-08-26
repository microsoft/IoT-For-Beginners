<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "5cb65a6ec4387ed177e145347e8e308e",
  "translation_date": "2025-08-26T07:29:34+00:00",
  "source_file": "3-transport/lessons/4-geofences/assignment.md",
  "language_code": "pl"
}
-->
# Wysyłanie powiadomień za pomocą Twilio

## Instrukcje

W swoim kodzie do tej pory logowałeś jedynie odległość od geofence. W tym zadaniu musisz dodać powiadomienie, na przykład wiadomość tekstową lub e-mail, gdy współrzędne GPS znajdują się wewnątrz geofence.

Azure Functions oferuje wiele opcji powiązań, w tym z usługami zewnętrznymi, takimi jak Twilio, platforma komunikacyjna.

* Zarejestruj się na darmowe konto na [Twilio.com](https://www.twilio.com)
* Przeczytaj dokumentację na temat powiązania Azure Functions z Twilio SMS na stronie [Microsoft docs Twilio binding for Azure Functions](https://docs.microsoft.com/azure/azure-functions/functions-bindings-twilio?WT.mc_id=academic-17441-jabenn&tabs=python).
* Przeczytaj dokumentację na temat powiązania Azure Functions z Twilio SendGrid w celu wysyłania e-maili na stronie [Microsoft docs Azure Functions SendGrid bindings](https://docs.microsoft.com/azure/azure-functions/functions-bindings-sendgrid?WT.mc_id=academic-17441-jabenn&tabs=python).
* Dodaj powiązanie do swojej aplikacji Functions, aby otrzymywać powiadomienia o współrzędnych GPS znajdujących się wewnątrz lub na zewnątrz geofence - ale nie w obu przypadkach.

## Kryteria oceny

| Kryteria | Wzorowe | Zadowalające | Wymaga poprawy |
| -------- | --------- | -------- | ----------------- |
| Konfiguracja powiązań funkcji i odbieranie e-maila lub SMS-a | Udało się skonfigurować powiązania funkcji i odebrać e-mail lub SMS, gdy współrzędne znajdowały się wewnątrz lub na zewnątrz geofence, ale nie w obu przypadkach | Udało się skonfigurować powiązania, ale nie udało się wysłać e-maila lub SMS-a, albo udało się wysłać tylko wtedy, gdy współrzędne znajdowały się zarówno wewnątrz, jak i na zewnątrz | Nie udało się skonfigurować powiązań ani wysłać e-maila lub SMS-a |

**Zastrzeżenie**:  
Ten dokument został przetłumaczony za pomocą usługi tłumaczenia AI [Co-op Translator](https://github.com/Azure/co-op-translator). Chociaż dokładamy wszelkich starań, aby tłumaczenie było precyzyjne, prosimy pamiętać, że automatyczne tłumaczenia mogą zawierać błędy lub nieścisłości. Oryginalny dokument w jego rodzimym języku powinien być uznawany za autorytatywne źródło. W przypadku informacji o kluczowym znaczeniu zaleca się skorzystanie z profesjonalnego tłumaczenia przez człowieka. Nie ponosimy odpowiedzialności za jakiekolwiek nieporozumienia lub błędne interpretacje wynikające z użycia tego tłumaczenia.