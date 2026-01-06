<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "6f4ba69d77f16c4a5110623a96a215c3",
  "translation_date": "2025-08-26T07:15:34+00:00",
  "source_file": "6-consumer/lessons/2-language-understanding/README.md",
  "language_code": "pl"
}
-->
# Zrozumienie języka

![Szkicowy przegląd tej lekcji](../../../../../translated_images/lesson-22.6148ea28500d9e00c396aaa2649935fb6641362c8f03d8e5e90a676977ab01dd.pl.jpg)

> Szkic autorstwa [Nitya Narasimhan](https://github.com/nitya). Kliknij obrazek, aby zobaczyć większą wersję.

## Quiz przed wykładem

[Quiz przed wykładem](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/43)

## Wprowadzenie

W poprzedniej lekcji przekształciłeś mowę na tekst. Aby użyć tego do zaprogramowania inteligentnego timera, Twój kod musi zrozumieć, co zostało powiedziane. Możesz założyć, że użytkownik wypowie ustaloną frazę, taką jak „Ustaw timer na 3 minuty”, i przeanalizować to wyrażenie, aby określić, jak długo timer powinien działać, ale to nie jest zbyt przyjazne dla użytkownika. Jeśli użytkownik powie „Ustaw timer na 3 minuty”, Ty lub ja zrozumiemy, co ma na myśli, ale Twój kod nie, ponieważ oczekuje ustalonej frazy.

Tutaj wkracza zrozumienie języka, wykorzystując modele AI do interpretacji tekstu i zwracania potrzebnych szczegółów, na przykład zdolność do zrozumienia zarówno „Ustaw timer na 3 minuty”, jak i „Ustaw timer na 3 minuty”, że wymagany jest timer na 3 minuty.

W tej lekcji dowiesz się o modelach zrozumienia języka, jak je tworzyć, trenować i używać w swoim kodzie.

W tej lekcji omówimy:

* [Zrozumienie języka](../../../../../6-consumer/lessons/2-language-understanding)
* [Tworzenie modelu zrozumienia języka](../../../../../6-consumer/lessons/2-language-understanding)
* [Intencje i jednostki](../../../../../6-consumer/lessons/2-language-understanding)
* [Użycie modelu zrozumienia języka](../../../../../6-consumer/lessons/2-language-understanding)

## Zrozumienie języka

Ludzie używają języka do komunikacji od setek tysięcy lat. Komunikujemy się za pomocą słów, dźwięków lub działań i rozumiemy, co zostało powiedziane, zarówno znaczenie słów, dźwięków czy działań, jak i ich kontekst. Rozumiemy szczerość i sarkazm, pozwalając tym samym słowom oznaczać różne rzeczy w zależności od tonu naszego głosu.

✅ Pomyśl o niektórych rozmowach, które prowadziłeś ostatnio. Jak wiele z tych rozmów byłoby trudnych do zrozumienia dla komputera, ponieważ wymagałyby kontekstu?

Zrozumienie języka, zwane również zrozumieniem języka naturalnego, jest częścią dziedziny sztucznej inteligencji zwanej przetwarzaniem języka naturalnego (NLP) i dotyczy rozumienia tekstu, próbując zrozumieć szczegóły słów lub zdań. Jeśli używasz asystenta głosowego, takiego jak Alexa czy Siri, korzystasz z usług zrozumienia języka. Są to usługi AI działające w tle, które przekształcają „Alexa, odtwórz najnowszy album Taylor Swift” w moją córkę tańczącą po salonie do swoich ulubionych utworów.

> 💁 Komputery, mimo wszystkich swoich postępów, wciąż mają przed sobą długą drogę, aby naprawdę zrozumieć tekst. Kiedy mówimy o zrozumieniu języka przez komputery, nie mamy na myśli niczego nawet zbliżonego do zaawansowanej komunikacji międzyludzkiej, lecz raczej wyciąganie kluczowych szczegółów z tekstu.

Jako ludzie rozumiemy język bez większego zastanowienia. Jeśli poproszę innego człowieka, aby „odtworzył najnowszy album Taylor Swift”, instynktownie zrozumie, co mam na myśli. Dla komputera jest to trudniejsze. Musiałby wziąć słowa, przekształcone z mowy na tekst, i wyodrębnić następujące informacje:

* Muzyka musi zostać odtworzona
* Muzyka pochodzi od artystki Taylor Swift
* Konkretna muzyka to cały album składający się z wielu utworów w określonej kolejności
* Taylor Swift ma wiele albumów, więc trzeba je posortować chronologicznie, a najnowszy jest tym, który jest wymagany

✅ Pomyśl o innych zdaniach, które wypowiadałeś, składając prośby, na przykład zamawiając kawę lub prosząc członka rodziny o podanie czegoś. Spróbuj rozłożyć je na części informacji, które komputer musiałby wyodrębnić, aby zrozumieć zdanie.

Modele zrozumienia języka to modele AI, które są trenowane do wyodrębniania określonych szczegółów z języka, a następnie są trenowane do konkretnych zadań za pomocą transferu uczenia, w taki sam sposób, w jaki trenowałeś model Custom Vision za pomocą małego zestawu obrazów. Możesz wziąć model, a następnie trenować go za pomocą tekstu, który chcesz, aby rozumiał.

## Tworzenie modelu zrozumienia języka

![Logo LUIS](../../../../../translated_images/luis-logo.5cb4f3e88c020ee6df4f614e8831f4a4b6809a7247bf52085fb48d629ef9be52.pl.png)

Możesz tworzyć modele zrozumienia języka za pomocą LUIS, usługi zrozumienia języka od Microsoftu, która jest częścią Cognitive Services.

### Zadanie - utwórz zasób autorski

Aby korzystać z LUIS, musisz utworzyć zasób autorski.

1. Użyj następującego polecenia, aby utworzyć zasób autorski w swojej grupie zasobów `smart-timer`:

    ```python
    az cognitiveservices account create --name smart-timer-luis-authoring \
                                        --resource-group smart-timer \
                                        --kind LUIS.Authoring \
                                        --sku F0 \
                                        --yes \
                                        --location <location>
    ```

    Zamień `<location>` na lokalizację, którą użyłeś podczas tworzenia grupy zasobów.

    > ⚠️ LUIS nie jest dostępny we wszystkich regionach, więc jeśli otrzymasz następujący błąd:
    >
    > ```output
    > InvalidApiSetId: The account type 'LUIS.Authoring' is either invalid or unavailable in given region.
    > ```
    >
    > wybierz inny region.

    To utworzy zasób autorski LUIS w wersji darmowej.

### Zadanie - utwórz aplikację zrozumienia języka

1. Otwórz portal LUIS pod adresem [luis.ai](https://luis.ai?WT.mc_id=academic-17441-jabenn) w swojej przeglądarce i zaloguj się na to samo konto, którego używasz w Azure.

1. Postępuj zgodnie z instrukcjami w oknie dialogowym, aby wybrać swoją subskrypcję Azure, a następnie wybierz zasób `smart-timer-luis-authoring`, który właśnie utworzyłeś.

1. Z listy *Conversation apps* wybierz przycisk **New app**, aby utworzyć nową aplikację. Nazwij nową aplikację `smart-timer` i ustaw *Culture* na swój język.

    > 💁 Istnieje pole dla zasobu predykcji. Możesz utworzyć drugi zasób tylko do predykcji, ale darmowy zasób autorski pozwala na 1000 predykcji miesięcznie, co powinno wystarczyć na potrzeby rozwoju, więc możesz pozostawić to pole puste.

1. Przeczytaj przewodnik, który pojawi się po utworzeniu aplikacji, aby zrozumieć kroki potrzebne do trenowania modelu zrozumienia języka. Zamknij ten przewodnik, gdy skończysz.

## Intencje i jednostki

Zrozumienie języka opiera się na *intencjach* i *jednostkach*. Intencje to cel wypowiedzianych słów, na przykład odtwarzanie muzyki, ustawianie timera czy zamawianie jedzenia. Jednostki to to, do czego odnosi się intencja, na przykład album, długość timera czy rodzaj jedzenia. Każde zdanie interpretowane przez model powinno mieć co najmniej jedną intencję i opcjonalnie jedną lub więcej jednostek.

Kilka przykładów:

| Zdanie                                              | Intencja         | Jednostki                                   |
| --------------------------------------------------- | ---------------- | ------------------------------------------ |
| „Odtwórz najnowszy album Taylor Swift”              | *odtwórz muzykę* | *najnowszy album Taylor Swift*             |
| „Ustaw timer na 3 minuty”                           | *ustaw timer*    | *3 minuty*                                 |
| „Anuluj mój timer”                                  | *anuluj timer*   | Brak                                       |
| „Zamów 3 duże pizze z ananasem i sałatkę cezar”     | *zamów jedzenie* | *3 duże pizze z ananasem*, *sałatka cezar* |

✅ Z zastanowionymi wcześniej zdaniami, jaka byłaby intencja i jakie jednostki w tych zdaniach?

Aby trenować LUIS, najpierw ustawiasz jednostki. Mogą to być ustalone listy terminów lub wyuczone z tekstu. Na przykład możesz dostarczyć ustaloną listę jedzenia dostępnego w menu, z wariantami (lub synonimami) każdego słowa, takimi jak *bakłażan* i *oberżyna* jako warianty *oberżyny*. LUIS ma również wbudowane jednostki, które można wykorzystać, takie jak liczby i lokalizacje.

Dla ustawiania timera możesz mieć jedną jednostkę korzystającą z wbudowanych jednostek liczbowych dla czasu i drugą dla jednostek, takich jak minuty i sekundy. Każda jednostka miałaby wiele wariantów, aby uwzględnić formy pojedyncze i mnogie - takie jak minuta i minuty.

Po zdefiniowaniu jednostek tworzysz intencje. Są one wyuczone przez model na podstawie przykładów zdań, które dostarczasz (znanych jako wypowiedzi). Na przykład dla intencji *ustaw timer* możesz dostarczyć następujące zdania:

* `ustaw timer na 1 sekundę`
* `ustaw timer na 1 minutę i 12 sekund`
* `ustaw timer na 3 minuty`
* `ustaw timer na 9 minut i 30 sekund`

Następnie informujesz LUIS, które części tych zdań odpowiadają jednostkom:

![Zdanie ustaw timer na 1 minutę i 12 sekund rozbite na jednostki](../../../../../translated_images/sentence-as-intent-entities.301401696f992259.pl.png)

Zdanie `ustaw timer na 1 minutę i 12 sekund` ma intencję `ustaw timer`. Ma również 2 jednostki z 2 wartościami każda:

|            | czas | jednostka |
| ---------- | ---: | --------- |
| 1 minuta   | 1    | minuta    |
| 12 sekund  | 12   | sekunda   |

Aby wytrenować dobry model, potrzebujesz różnych przykładów zdań, aby uwzględnić wiele różnych sposobów, w jakie ktoś może poprosić o to samo.

> 💁 Jak w przypadku każdego modelu AI, im więcej danych i im bardziej dokładne dane użyjesz do trenowania, tym lepszy będzie model.

✅ Pomyśl o różnych sposobach, w jakie możesz poprosić o to samo i oczekiwać, że człowiek to zrozumie.

### Zadanie - dodaj jednostki do modeli zrozumienia języka

Dla timera musisz dodać 2 jednostki - jedną dla jednostki czasu (minuty lub sekundy) i jedną dla liczby minut lub sekund.

Instrukcje dotyczące korzystania z portalu LUIS znajdziesz w [Quickstart: Build your app in LUIS portal documentation on Microsoft docs](https://docs.microsoft.com/azure/cognitive-services/luis/luis-get-started-create-app?WT.mc_id=academic-17441-jabenn).

1. Z portalu LUIS wybierz zakładkę *Entities* i dodaj wbudowaną jednostkę *number*, wybierając przycisk **Add prebuilt entity**, a następnie wybierając *number* z listy.

1. Utwórz nową jednostkę dla jednostki czasu, używając przycisku **Create**. Nazwij jednostkę `time unit` i ustaw typ na *List*. Dodaj wartości dla `minute` i `second` do listy *Normalized values*, dodając formy pojedyncze i mnogie do listy *synonyms*. Naciśnij `return` po dodaniu każdego synonimu, aby dodać go do listy.

    | Wartość znormalizowana | Synonimy        |
    | ---------------------- | --------------- |
    | minuta                 | minuta, minuty  |
    | sekunda                | sekunda, sekundy|

### Zadanie - dodaj intencje do modeli zrozumienia języka

1. Z zakładki *Intents* wybierz przycisk **Create**, aby utworzyć nową intencję. Nazwij tę intencję `set timer`.

1. W przykładach wpisz różne sposoby ustawiania timera, używając zarówno minut, sekund, jak i kombinacji minut i sekund. Przykłady mogą być:

    * `ustaw timer na 1 sekundę`
    * `ustaw timer na 4 minuty`
    * `ustaw timer na cztery minuty i sześć sekund`
    * `ustaw timer na 9 minut i 30 sekund`
    * `ustaw timer na 1 minutę i 12 sekund`
    * `ustaw timer na 3 minuty`
    * `ustaw timer na 3 minuty i 1 sekundę`
    * `ustaw timer na trzy minuty i jedną sekundę`
    * `ustaw timer na 1 minutę i 1 sekundę`
    * `ustaw timer na 30 sekund`
    * `ustaw timer na 1 sekundę`

    Wymieszaj liczby jako słowa i cyfry, aby model nauczył się obsługiwać oba.

1. Podczas wpisywania każdego przykładu LUIS zacznie wykrywać jednostki i podkreślać oraz oznaczać te, które znajdzie.

    ![Przykłady z podkreślonymi liczbami i jednostkami czasu przez LUIS](../../../../../translated_images/luis-intent-examples.25716580b2d2723cf1bafdf277d015c7f046d8cfa20f27bddf3a0873ec45fab7.pl.png)

### Zadanie - wytrenuj i przetestuj model

1. Gdy jednostki i intencje są skonfigurowane, możesz wytrenować model, używając przycisku **Train** w górnym menu. Wybierz ten przycisk, a model powinien wytrenować się w ciągu kilku sekund. Przycisk będzie wyszarzony podczas trenowania i ponownie aktywowany po zakończeniu.

1. Wybierz przycisk **Test** z górnego menu, aby przetestować model zrozumienia języka. Wpisz tekst, taki jak `ustaw timer na 5 minut i 4 sekundy`, i naciśnij enter. Zdanie pojawi się w polu poniżej pola tekstowego, w które je wpisałeś, a poniżej będzie *top intent*, czyli intencja wykryta z najwyższym prawdopodobieństwem. Powinna to być `set timer`. Nazwa intencji będzie poprzedzona prawdopodobieństwem, że wykryta intencja była właściwa.

1. Wybierz opcję **Inspect**, aby zobaczyć szczegółowy podział wyników. Zobaczysz najwyżej ocenioną intencję z jej procentowym prawdopodobieństwem, wraz z listami wykrytych jednostek.

1. Zamknij panel *Test*, gdy skończysz testowanie.

### Zadanie - opublikuj model

Aby używać tego modelu w kodzie, musisz go opublikować. Podczas publikowania z LUIS możesz publikować do środowiska testowego (staging) lub produkcyjnego. W tej lekcji środowisko testowe jest wystarczające.

1. Z portalu LUIS wybierz przycisk **Publish** z górnego menu.

1. Upewnij się, że wybrano *Staging slot*, a następnie wybierz **Done**. Zobaczysz powiadomienie, gdy aplikacja zostanie opublikowana.

1. Możesz to przetestować za pomocą curl. Aby zbudować polecenie curl, potrzebujesz trzech wartości - punktu końcowego, identyfikatora aplikacji (App ID) i klucza API. Można je znaleźć w zakładce **MANAGE**, którą można wybrać z górnego menu.

    1. Z sekcji *Settings* skopiuj App ID.
1. W sekcji *Azure Resources* wybierz *Authoring Resource* i skopiuj *Primary Key* oraz *Endpoint URL*.

1. Uruchom następujące polecenie curl w wierszu poleceń lub terminalu:

    ```sh
    curl "<endpoint url>/luis/prediction/v3.0/apps/<app id>/slots/staging/predict" \
          --request GET \
          --get \
          --data "subscription-key=<primary key>" \
          --data "verbose=false" \
          --data "show-all-intents=true" \
          --data-urlencode "query=<sentence>"
    ```

    Zamień `<endpoint url>` na Endpoint URL z sekcji *Azure Resources*.

    Zamień `<app id>` na App ID z sekcji *Settings*.

    Zamień `<primary key>` na Primary Key z sekcji *Azure Resources*.

    Zamień `<sentence>` na zdanie, które chcesz przetestować.

1. Wynik tego wywołania będzie dokumentem JSON, który zawiera szczegóły zapytania, główną intencję oraz listę jednostek podzielonych według typów.

    ```JSON
    {
        "query": "set a timer for 45 minutes and 12 seconds",
        "prediction": {
            "topIntent": "set timer",
            "intents": {
                "set timer": {
                    "score": 0.97031575
                },
                "None": {
                    "score": 0.02205793
                }
            },
            "entities": {
                "number": [
                    45,
                    12
                ],
                "time-unit": [
                    [
                        "minute"
                    ],
                    [
                        "second"
                    ]
                ]
            }
        }
    }
    ```

    Powyższy JSON pochodzi z zapytania o `set a timer for 45 minutes and 12 seconds`:

    * `set timer` było główną intencją z prawdopodobieństwem 97%.
    * Wykryto dwie jednostki typu *number*: `45` i `12`.
    * Wykryto dwie jednostki typu *time-unit*: `minute` i `second`.

## Użycie modelu rozumienia języka

Po opublikowaniu model LUIS można wywoływać z poziomu kodu. W poprzednich lekcjach używałeś IoT Hub do obsługi komunikacji z usługami w chmurze, wysyłania telemetrii i nasłuchiwania poleceń. Jest to bardzo asynchroniczne – po wysłaniu telemetrii Twój kod nie czeka na odpowiedź, a jeśli usługa w chmurze jest niedostępna, nie będziesz o tym wiedział.

W przypadku inteligentnego timera chcemy uzyskać odpowiedź natychmiast, aby poinformować użytkownika, że timer został ustawiony, lub ostrzec go, że usługi w chmurze są niedostępne. Aby to zrobić, nasze urządzenie IoT będzie wywoływać bezpośrednio punkt końcowy sieciowy, zamiast polegać na IoT Hub.

Zamiast wywoływać LUIS bezpośrednio z urządzenia IoT, możesz użyć kodu bezserwerowego z innym typem wyzwalacza – wyzwalaczem HTTP. Pozwala to aplikacji funkcji nasłuchiwać żądań REST i na nie odpowiadać. Ta funkcja będzie punktem końcowym REST, który Twoje urządzenie może wywoływać.

> 💁 Chociaż możesz wywoływać LUIS bezpośrednio z urządzenia IoT, lepiej jest użyć czegoś takiego jak kod bezserwerowy. Dzięki temu, gdy chcesz zmienić aplikację LUIS, którą wywołujesz, na przykład po przeszkoleniu lepszego modelu lub modelu w innym języku, musisz zaktualizować tylko kod w chmurze, a nie wdrażać ponownie kod na potencjalnie tysiącach lub milionach urządzeń IoT.

### Zadanie – utwórz aplikację funkcji bezserwerowych

1. Utwórz aplikację Azure Functions o nazwie `smart-timer-trigger` i otwórz ją w VS Code.

1. Dodaj wyzwalacz HTTP do tej aplikacji o nazwie `speech-trigger`, używając następującego polecenia w terminalu VS Code:

    ```sh
    func new --name text-to-timer --template "HTTP trigger"
    ```

    To utworzy wyzwalacz HTTP o nazwie `text-to-timer`.

1. Przetestuj wyzwalacz HTTP, uruchamiając aplikację funkcji. Po uruchomieniu zobaczysz punkt końcowy wymieniony w wynikach:

    ```output
    Functions:
    
            text-to-timer: [GET,POST] http://localhost:7071/api/text-to-timer
    ```

    Przetestuj to, ładując URL [http://localhost:7071/api/text-to-timer](http://localhost:7071/api/text-to-timer) w przeglądarce.

    ```output
    This HTTP triggered function executed successfully. Pass a name in the query string or in the request body for a personalized response.
    ```

### Zadanie – użyj modelu rozumienia języka

1. SDK dla LUIS jest dostępne jako pakiet Pip. Dodaj następującą linię do pliku `requirements.txt`, aby dodać zależność od tego pakietu:

    ```sh
    azure-cognitiveservices-language-luis
    ```

1. Upewnij się, że terminal VS Code ma aktywowane środowisko wirtualne, i uruchom następujące polecenie, aby zainstalować pakiety Pip:

    ```sh
    pip install -r requirements.txt
    ```

    > 💁 Jeśli pojawią się błędy, może być konieczna aktualizacja pip za pomocą następującego polecenia:
    >
    > ```sh
    > pip install --upgrade pip
    > ```

1. Dodaj nowe wpisy do pliku `local.settings.json` dla swojego klucza API LUIS, Endpoint URL i App ID z zakładki **MANAGE** w portalu LUIS:

    ```JSON
    "LUIS_KEY": "<primary key>",
    "LUIS_ENDPOINT_URL": "<endpoint url>",
    "LUIS_APP_ID": "<app id>"
    ```

    Zamień `<endpoint url>` na Endpoint URL z sekcji *Azure Resources* w zakładce **MANAGE**. Będzie to `https://<location>.api.cognitive.microsoft.com/`.

    Zamień `<app id>` na App ID z sekcji *Settings* w zakładce **MANAGE**.

    Zamień `<primary key>` na Primary Key z sekcji *Azure Resources* w zakładce **MANAGE**.

1. Dodaj następujące importy do pliku `__init__.py`:

    ```python
    import json
    import os
    from azure.cognitiveservices.language.luis.runtime import LUISRuntimeClient
    from msrest.authentication import CognitiveServicesCredentials
    ```

    To importuje niektóre biblioteki systemowe oraz biblioteki do interakcji z LUIS.

1. Usuń zawartość metody `main` i dodaj następujący kod:

    ```python
    luis_key = os.environ['LUIS_KEY']
    endpoint_url = os.environ['LUIS_ENDPOINT_URL']
    app_id = os.environ['LUIS_APP_ID']
    
    credentials = CognitiveServicesCredentials(luis_key)
    client = LUISRuntimeClient(endpoint=endpoint_url, credentials=credentials)
    ```

    Ten kod ładuje wartości, które dodałeś do pliku `local.settings.json` dla swojej aplikacji LUIS, tworzy obiekt poświadczeń z Twoim kluczem API, a następnie tworzy obiekt klienta LUIS do interakcji z Twoją aplikacją LUIS.

1. Wyzwalacz HTTP będzie wywoływany z tekstem do zrozumienia przesłanym jako JSON, z tekstem w właściwości `text`. Następujący kod wyodrębnia wartość z treści żądania HTTP i loguje ją do konsoli. Dodaj ten kod do funkcji `main`:

    ```python
    req_body = req.get_json()
    text = req_body['text']
    logging.info(f'Request - {text}')
    ```

1. Prognozy są żądane od LUIS przez wysłanie żądania prognozy – dokumentu JSON zawierającego tekst do przewidzenia. Utwórz to za pomocą następującego kodu:

    ```python
    prediction_request = { 'query' : text }
    ```

1. To żądanie można następnie wysłać do LUIS, używając slotu staging, na który Twoja aplikacja została opublikowana:

    ```python
    prediction_response = client.prediction.get_slot_prediction(app_id, 'Staging', prediction_request)
    ```

1. Odpowiedź prognozy zawiera główną intencję – intencję z najwyższym wynikiem prognozy, wraz z jednostkami. Jeśli główną intencją jest `set timer`, jednostki można odczytać, aby uzyskać czas potrzebny na timer:

    ```python
    if prediction_response.prediction.top_intent == 'set timer':
        numbers = prediction_response.prediction.entities['number']
        time_units = prediction_response.prediction.entities['time unit']
        total_seconds = 0
    ```

    Jednostki typu `number` będą tablicą liczb. Na przykład, jeśli powiesz *"Set a four minute 17 second timer."*, tablica `number` będzie zawierać 2 liczby całkowite – 4 i 17.

    Jednostki typu `time unit` będą tablicą tablic ciągów znaków, z każdą jednostką czasu jako tablicą ciągów znaków wewnątrz tablicy. Na przykład, jeśli powiesz *"Set a four minute 17 second timer."*, tablica `time unit` będzie zawierać 2 tablice z pojedynczymi wartościami – `['minute']` i `['second']`.

    Wersja JSON tych jednostek dla *"Set a four minute 17 second timer."* wygląda następująco:

    ```json
    {
        "number": [4, 17],
        "time unit": [
            ["minute"],
            ["second"]
        ]
    }
    ```

    Ten kod definiuje również licznik dla całkowitego czasu timera w sekundach. Zostanie on wypełniony wartościami z jednostek.

1. Jednostki nie są powiązane, ale możemy przyjąć pewne założenia na ich temat. Będą w kolejności wypowiedzianej, więc pozycja w tablicy może być użyta do określenia, która liczba odpowiada której jednostce czasu. Na przykład:

    * *"Set a 30 second timer"* – będzie miało jedną liczbę, `30`, i jedną jednostkę czasu, `second`, więc pojedyncza liczba będzie odpowiadać pojedynczej jednostce czasu.
    * *"Set a 2 minute and 30 second timer"* – będzie miało dwie liczby, `2` i `30`, oraz dwie jednostki czasu, `minute` i `second`, więc pierwsza liczba będzie dla pierwszej jednostki czasu (2 minuty), a druga liczba dla drugiej jednostki czasu (30 sekund).

    Następujący kod pobiera liczbę elementów w jednostkach typu `number` i używa jej do wyodrębnienia pierwszego elementu z każdej tablicy, następnie drugiego i tak dalej. Dodaj to wewnątrz bloku `if`.

    ```python
    for i in range(0, len(numbers)):
        number = numbers[i]
        time_unit = time_units[i][0]
    ```

    Dla *"Set a four minute 17 second timer."* pętla wykona się dwa razy, dając następujące wartości:

    | licznik pętli | `number` | `time_unit` |
    | -------------:| --------:| ----------- |
    | 0             | 4        | minute      |
    | 1             | 17       | second      |

1. Wewnątrz tej pętli użyj liczby i jednostki czasu, aby obliczyć całkowity czas timera, dodając 60 sekund dla każdej minuty i liczbę sekund dla każdej sekundy.

    ```python
    if time_unit == 'minute':
        total_seconds += number * 60
    else:
        total_seconds += number
    ```

1. Poza tą pętlą przez jednostki, zaloguj całkowity czas timera:

    ```python
    logging.info(f'Timer required for {total_seconds} seconds')
    ```

1. Liczba sekund musi zostać zwrócona z funkcji jako odpowiedź HTTP. Na końcu bloku `if` dodaj następujący kod:

    ```python
    payload = {
        'seconds': total_seconds
    }
    return func.HttpResponse(json.dumps(payload), status_code=200)
    ```

    Ten kod tworzy ładunek zawierający całkowitą liczbę sekund dla timera, konwertuje go na ciąg JSON i zwraca jako wynik HTTP z kodem statusu 200, co oznacza, że wywołanie zakończyło się sukcesem.

1. Na koniec, poza blokiem `if`, obsłuż sytuację, gdy intencja nie została rozpoznana, zwracając kod błędu:

    ```python
    return func.HttpResponse(status_code=404)
    ```

    404 to kod statusu dla *not found*.

1. Uruchom aplikację funkcji i przetestuj ją za pomocą curl.

    ```sh
    curl --request POST 'http://localhost:7071/api/text-to-timer' \
         --header 'Content-Type: application/json' \
         --include \
         --data '{"text":"<text>"}'
    ```

    Zamień `<text>` na tekst swojego żądania, na przykład `set a 2 minutes 27 second timer`.

    Zobaczysz następujący wynik z aplikacji funkcji:

    ```output
    Functions:

            text-to-timer: [GET,POST] http://localhost:7071/api/text-to-timer
    
    For detailed output, run func with --verbose flag.
    [2021-06-26T19:45:14.502Z] Worker process started and initialized.
    [2021-06-26T19:45:19.338Z] Host lock lease acquired by instance ID '000000000000000000000000951CAE4E'.
    [2021-06-26T19:45:52.059Z] Executing 'Functions.text-to-timer' (Reason='This function was programmatically called via the host APIs.', Id=f68bfb90-30e4-47a5-99da-126b66218e81)
    [2021-06-26T19:45:53.577Z] Timer required for 147 seconds
    [2021-06-26T19:45:53.746Z] Executed 'Functions.text-to-timer' (Succeeded, Id=f68bfb90-30e4-47a5-99da-126b66218e81, Duration=1750ms)
    ```

    Wywołanie curl zwróci następujące dane:

    ```output
    HTTP/1.1 200 OK
    Date: Tue, 29 Jun 2021 01:14:11 GMT
    Content-Type: text/plain; charset=utf-8
    Server: Kestrel
    Transfer-Encoding: chunked
    
    {"seconds": 147}
    ```

    Liczba sekund dla timera znajduje się w wartości `"seconds"`.

> 💁 Kod ten znajdziesz w folderze [code/functions](../../../../../6-consumer/lessons/2-language-understanding/code/functions).

### Zadanie – udostępnij swoją funkcję urządzeniu IoT

1. Aby Twoje urządzenie IoT mogło wywołać Twój punkt końcowy REST, będzie musiało znać URL. Kiedy uzyskałeś do niego dostęp wcześniej, używałeś `localhost`, który jest skrótem do dostępu do punktów końcowych REST na Twoim lokalnym komputerze. Aby umożliwić dostęp urządzeniu IoT, musisz albo opublikować aplikację w chmurze, albo uzyskać swój adres IP, aby uzyskać dostęp lokalnie.

    > ⚠️ Jeśli używasz Wio Terminal, łatwiej jest uruchomić aplikację funkcji lokalnie, ponieważ będą zależności od bibliotek, które uniemożliwią wdrożenie aplikacji funkcji w taki sam sposób, jak wcześniej. Uruchom aplikację funkcji lokalnie i uzyskaj do niej dostęp za pomocą adresu IP swojego komputera. Jeśli chcesz wdrożyć w chmurze, informacje na temat tego, jak to zrobić, zostaną podane w późniejszej lekcji.

    * Opublikuj aplikację Functions – postępuj zgodnie z instrukcjami z wcześniejszych lekcji, aby opublikować swoją aplikację funkcji w chmurze. Po opublikowaniu URL będzie miał postać `https://<APP_NAME>.azurewebsites.net/api/text-to-timer`, gdzie `<APP_NAME>` to nazwa Twojej aplikacji funkcji. Upewnij się, że opublikowałeś również swoje ustawienia lokalne.

      Podczas pracy z wyzwalaczami HTTP są one domyślnie zabezpieczone kluczem aplikacji funkcji. Aby uzyskać ten klucz, uruchom następujące polecenie:

      ```sh
      az functionapp keys list --resource-group smart-timer \
                               --name <APP_NAME>                               
      ```

      Skopiuj wartość wpisu `default` z sekcji `functionKeys`.

      ```output
      {
        "functionKeys": {
          "default": "sQO1LQaeK9N1qYD6SXeb/TctCmwQEkToLJU6Dw8TthNeUH8VA45hlA=="
        },
        "masterKey": "RSKOAIlyvvQEQt9dfpabJT018scaLpQu9p1poHIMCxx5LYrIQZyQ/g==",
        "systemKeys": {}
      }
      ```

      Ten klucz musi zostać dodany jako parametr zapytania do URL, więc ostateczny URL będzie miał postać `https://<APP_NAME>.azurewebsites.net/api/text-to-timer?code=<FUNCTION_KEY>`, gdzie `<APP_NAME>` to nazwa Twojej aplikacji funkcji, a `<FUNCTION_KEY>` to Twój domyślny klucz funkcji.

      > 💁 Możesz zmienić typ autoryzacji wyzwalacza HTTP, używając ustawienia `authlevel` w pliku `function.json`. Więcej na ten temat możesz przeczytać w [sekcji konfiguracji dokumentacji wyzwalacza HTTP w Azure Functions na Microsoft Docs](https://docs.microsoft.com/azure/azure-functions/functions-bindings-http-webhook-trigger?WT.mc_id=academic-17441-jabenn&tabs=python#configuration).

    * Uruchom aplikację funkcji lokalnie i uzyskaj dostęp za pomocą adresu IP – możesz uzyskać adres IP swojego komputera w lokalnej sieci i użyć go do zbudowania URL.

      Znajdź swój adres IP:

      * Na Windows 10, postępuj zgodnie z [przewodnikiem znajdowania adresu IP](https://support.microsoft.com/windows/find-your-ip-address-f21a9bbc-c582-55cd-35e0-73431160a1b9?WT.mc_id=academic-17441-jabenn)
      * Na macOS, postępuj zgodnie z [przewodnikiem znajdowania adresu IP na Macu](https://www.hellotech.com/guide/for/how-to-find-ip-address-on-mac)
      * Na Linux, postępuj zgodnie z sekcją znajdowania prywatnego adresu IP w [przewodniku znajdowania adresu IP w Linux](https://opensource.com/article/18/5/how-find-ip-address-linux)

      Po uzyskaniu adresu IP będziesz mógł uzyskać dostęp do funkcji pod adresem `http://`.

:7071/api/text-to-timer`, gdzie `<IP_ADDRESS>` to Twój adres IP, na przykład `http://192.168.1.10:7071/api/text-to-timer`.

      > 💁 Zwróć uwagę, że używany jest port 7071, więc po adresie IP musisz dodać `:7071`.

      > 💁 To będzie działać tylko wtedy, gdy Twoje urządzenie IoT znajduje się w tej samej sieci co Twój komputer.

1. Przetestuj endpoint, uzyskując do niego dostęp za pomocą curl.

---

## 🚀 Wyzwanie

Istnieje wiele sposobów na złożenie tej samej prośby, na przykład ustawienie timera. Pomyśl o różnych sposobach, aby to zrobić, i użyj ich jako przykładów w swojej aplikacji LUIS. Przetestuj je, aby zobaczyć, jak dobrze Twój model radzi sobie z różnymi sposobami składania prośby o timer.

## Quiz po wykładzie

[Quiz po wykładzie](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/44)

## Przegląd i samodzielna nauka

* Przeczytaj więcej o LUIS i jego możliwościach na [stronie dokumentacji Language Understanding (LUIS) na Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/luis/?WT.mc_id=academic-17441-jabenn)
* Dowiedz się więcej o rozumieniu języka na [stronie o naturalnym rozumieniu języka na Wikipedii](https://wikipedia.org/wiki/Natural-language_understanding)
* Przeczytaj więcej o wyzwalaczach HTTP w [dokumentacji wyzwalaczy HTTP dla Azure Functions na Microsoft Docs](https://docs.microsoft.com/azure/azure-functions/functions-bindings-http-webhook-trigger?WT.mc_id=academic-17441-jabenn&tabs=python)

## Zadanie

[Anuluj timer](assignment.md)

**Zastrzeżenie**:  
Ten dokument został przetłumaczony za pomocą usługi tłumaczenia AI [Co-op Translator](https://github.com/Azure/co-op-translator). Chociaż dokładamy wszelkich starań, aby tłumaczenie było precyzyjne, prosimy pamiętać, że automatyczne tłumaczenia mogą zawierać błędy lub nieścisłości. Oryginalny dokument w jego rodzimym języku powinien być uznawany za wiarygodne źródło. W przypadku informacji o kluczowym znaczeniu zaleca się skorzystanie z profesjonalnego tłumaczenia przez człowieka. Nie ponosimy odpowiedzialności za jakiekolwiek nieporozumienia lub błędne interpretacje wynikające z użycia tego tłumaczenia.