<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "c24b6e4d90501c9199f2ceb6a648a337",
  "translation_date": "2025-08-26T06:49:12+00:00",
  "source_file": "2-farm/lessons/5-migrate-application-to-the-cloud/assignment.md",
  "language_code": "pl"
}
-->
# Dodaj ręczne sterowanie przekaźnikiem

## Instrukcje

Kod bezserwerowy może być uruchamiany przez różne zdarzenia, w tym żądania HTTP. Możesz użyć wyzwalaczy HTTP, aby dodać ręczne sterowanie przekaźnikiem, umożliwiając komuś włączenie lub wyłączenie przekaźnika za pomocą żądania internetowego.

W ramach tego zadania musisz dodać dwa wyzwalacze HTTP do swojej aplikacji Functions App, aby włączyć i wyłączyć przekaźnik, wykorzystując wiedzę zdobytą w tej lekcji do wysyłania poleceń do urządzenia.

Kilka wskazówek:

* Możesz dodać wyzwalacz HTTP do swojej istniejącej aplikacji Functions App za pomocą następującego polecenia:

    ```sh
    func new --name <trigger name> --template "HTTP trigger"
    ```

    Zamień `<trigger name>` na nazwę dla swojego wyzwalacza HTTP. Użyj czegoś w rodzaju `relay_on` i `relay_off`.

* Wyzwalacze HTTP mogą mieć kontrolę dostępu. Domyślnie wymagają klucza API specyficznego dla funkcji, który musi być przekazany w URL, aby uruchomić funkcję. W ramach tego zadania możesz usunąć to ograniczenie, aby każdy mógł uruchomić funkcję. Aby to zrobić, zaktualizuj ustawienie `authLevel` w pliku `function.json` dla wyzwalaczy HTTP do następującej wartości:

    ```json
    "authLevel": "anonymous"
    ```

    > 💁 Więcej informacji o tej kontroli dostępu znajdziesz w [dokumentacji kluczy dostępu funkcji](https://docs.microsoft.com/azure/azure-functions/functions-bindings-http-webhook-trigger?WT.mc_id=academic-17441-jabenn#authorization-keys).

* Wyzwalacze HTTP domyślnie obsługują żądania GET i POST. Oznacza to, że możesz je wywoływać za pomocą swojej przeglądarki internetowej - przeglądarki internetowe wykonują żądania GET.

    Kiedy uruchomisz swoją aplikację Functions App lokalnie, zobaczysz URL wyzwalacza:

    ```output
    Functions:

        relay_off: [GET,POST] http://localhost:7071/api/relay_off

        relay_on: [GET,POST] http://localhost:7071/api/relay_on

        iot-hub-trigger: eventHubTrigger
    ```

    Wklej URL do swojej przeglądarki i naciśnij `Enter`, lub `Ctrl+kliknij` (`Cmd+kliknij` na macOS) link w oknie terminala w VS Code, aby otworzyć go w domyślnej przeglądarce. To uruchomi wyzwalacz.

    > 💁 Zauważ, że URL zawiera `/api` - wyzwalacze HTTP są domyślnie w subdomenie `api`.

* Po wdrożeniu aplikacji Functions App, URL wyzwalacza HTTP będzie wyglądał następująco:

    `https://<functions app name>.azurewebsites.net/api/<trigger name>`

    Gdzie `<functions app name>` to nazwa Twojej aplikacji Functions App, a `<trigger name>` to nazwa Twojego wyzwalacza.

## Kryteria oceny

| Kryterium | Wzorowe | Zadowalające | Wymaga poprawy |
| --------- | ------- | ------------ | -------------- |
| Tworzenie wyzwalaczy HTTP | Utworzono 2 wyzwalacze do włączania i wyłączania przekaźnika, z odpowiednimi nazwami | Utworzono jeden wyzwalacz z odpowiednią nazwą | Nie udało się utworzyć żadnych wyzwalaczy |
| Sterowanie przekaźnikiem za pomocą wyzwalaczy HTTP | Udało się połączyć oba wyzwalacze z IoT Hub i odpowiednio sterować przekaźnikiem | Udało się połączyć jeden wyzwalacz z IoT Hub i odpowiednio sterować przekaźnikiem | Nie udało się połączyć wyzwalaczy z IoT Hub |

**Zastrzeżenie**:  
Ten dokument został przetłumaczony za pomocą usługi tłumaczenia AI [Co-op Translator](https://github.com/Azure/co-op-translator). Chociaż staramy się zapewnić dokładność, prosimy pamiętać, że automatyczne tłumaczenia mogą zawierać błędy lub nieścisłości. Oryginalny dokument w jego rodzimym języku powinien być uznawany za autorytatywne źródło. W przypadku informacji krytycznych zaleca się skorzystanie z profesjonalnego tłumaczenia przez człowieka. Nie ponosimy odpowiedzialności za jakiekolwiek nieporozumienia lub błędne interpretacje wynikające z użycia tego tłumaczenia.