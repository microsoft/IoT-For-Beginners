# Tłumaczenie mowy - Wio Terminal

W tej części lekcji napiszesz kod do tłumaczenia tekstu za pomocą usługi Translator.

## Konwersja tekstu na mowę za pomocą usługi Translator

REST API usługi mowy nie obsługuje bezpośrednich tłumaczeń. Możesz jednak użyć usługi Translator, aby przetłumaczyć tekst wygenerowany przez usługę zamiany mowy na tekst oraz tekst odpowiedzi mówionej. Usługa Translator posiada REST API, które możesz wykorzystać do tłumaczenia tekstu, ale aby ułatwić korzystanie z niej, zostanie ona opakowana w inny wyzwalacz HTTP w Twojej aplikacji funkcji.

### Zadanie - utwórz funkcję bezserwerową do tłumaczenia tekstu

1. Otwórz swój projekt `smart-timer-trigger` w VS Code i uruchom terminal, upewniając się, że środowisko wirtualne jest aktywne. Jeśli nie, zamknij i ponownie utwórz terminal.

1. Otwórz plik `local.settings.json` i dodaj ustawienia dla klucza API usługi Translator oraz lokalizacji:

    ```json
    "TRANSLATOR_KEY": "<key>",
    "TRANSLATOR_LOCATION": "<location>"
    ```

    Zamień `<key>` na klucz API dla zasobu usługi Translator. Zamień `<location>` na lokalizację, którą wybrałeś podczas tworzenia zasobu usługi Translator.

1. Dodaj nowy wyzwalacz HTTP do tej aplikacji o nazwie `translate-text`, używając następującego polecenia w terminalu VS Code w katalogu głównym projektu aplikacji funkcji:

    ```sh
    func new --name translate-text --template "HTTP trigger"
    ```

    To utworzy wyzwalacz HTTP o nazwie `translate-text`.

1. Zastąp zawartość pliku `__init__.py` w folderze `translate-text` następującym kodem:

    ```python
    import logging
    import os
    import requests
    
    import azure.functions as func
    
    location = os.environ['TRANSLATOR_LOCATION']
    translator_key = os.environ['TRANSLATOR_KEY']
    
    def main(req: func.HttpRequest) -> func.HttpResponse:
        req_body = req.get_json()
        from_language = req_body['from_language']
        to_language = req_body['to_language']
        text = req_body['text']
        
        logging.info(f'Translating {text} from {from_language} to {to_language}')
    
        url = f'https://api.cognitive.microsofttranslator.com/translate?api-version=3.0'
    
        headers = {
            'Ocp-Apim-Subscription-Key': translator_key,
            'Ocp-Apim-Subscription-Region': location,
            'Content-type': 'application/json'
        }
    
        params = {
            'from': from_language,
            'to': to_language
        }
    
        body = [{
            'text' : text
        }]
        
        response = requests.post(url, headers=headers, params=params, json=body)
        return func.HttpResponse(response.json()[0]['translations'][0]['text'])
    ```

    Ten kod pobiera tekst i języki z żądania HTTP. Następnie wysyła żądanie do REST API usługi Translator, przekazując języki jako parametry URL oraz tekst do przetłumaczenia jako treść żądania. Na końcu zwracane jest tłumaczenie.

1. Uruchom lokalnie swoją aplikację funkcji. Możesz ją wywołać za pomocą narzędzia takiego jak curl, w taki sam sposób, w jaki testowałeś wyzwalacz HTTP `text-to-timer`. Upewnij się, że przekazujesz tekst do przetłumaczenia oraz języki w treści JSON:

    ```json
    {
        "text": "Définir une minuterie de 30 secondes",
        "from_language": "fr-FR",
        "to_language": "en-US"
    }
    ```

    Ten przykład tłumaczy *Définir une minuterie de 30 secondes* z francuskiego na angielski amerykański. Zwróci *Set a 30-second timer*.

> 💁 Ten kod znajdziesz w folderze [code/functions](../../../../../6-consumer/lessons/4-multiple-language-support/code/functions).

### Zadanie - użyj funkcji Translator do tłumaczenia tekstu

1. Otwórz projekt `smart-timer` w VS Code, jeśli nie jest już otwarty.

1. Twój inteligentny timer będzie miał ustawione 2 języki - język serwera, który został użyty do trenowania LUIS (ten sam język jest również używany do budowania komunikatów mówionych do użytkownika) oraz język używany przez użytkownika. Zaktualizuj stałą `LANGUAGE` w pliku nagłówkowym `config.h`, aby odpowiadała językowi, w którym będzie mówił użytkownik, i dodaj nową stałą o nazwie `SERVER_LANGUAGE` dla języka użytego do trenowania LUIS:

    ```cpp
    const char *LANGUAGE = "<user language>";
    const char *SERVER_LANGUAGE = "<server language>";
    ```

    Zamień `<user language>` na nazwę lokalizacji dla języka, w którym będziesz mówić, na przykład `fr-FR` dla francuskiego lub `zn-HK` dla kantońskiego.

    Zamień `<server language>` na nazwę lokalizacji dla języka użytego do trenowania LUIS.

    Listę obsługiwanych języków i ich nazw lokalizacji znajdziesz w [dokumentacji wsparcia językowego i głosowego na Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text).

    > 💁 Jeśli nie mówisz w wielu językach, możesz użyć usługi takiej jak [Bing Translate](https://www.bing.com/translator) lub [Google Translate](https://translate.google.com), aby przetłumaczyć z preferowanego języka na wybrany język. Te usługi mogą również odtwarzać dźwięk przetłumaczonego tekstu.
    >
    > Na przykład, jeśli trenujesz LUIS w języku angielskim, ale chcesz używać francuskiego jako języka użytkownika, możesz przetłumaczyć zdania takie jak "set a 2 minute and 27 second timer" z angielskiego na francuski za pomocą Bing Translate, a następnie użyć przycisku **Listen translation**, aby wypowiedzieć tłumaczenie do mikrofonu.
    >
    > ![Przycisk Listen translation w Bing Translate](../../../../../translated_images/pl/bing-translate.348aa796d6efe2a9.webp)

1. Dodaj klucz API usługi Translator i lokalizację poniżej `SPEECH_LOCATION`:

    ```cpp
    const char *TRANSLATOR_API_KEY = "<KEY>";
    const char *TRANSLATOR_LOCATION = "<LOCATION>";
    ```

    Zamień `<KEY>` na klucz API dla zasobu usługi Translator. Zamień `<LOCATION>` na lokalizację, którą wybrałeś podczas tworzenia zasobu usługi Translator.

1. Dodaj URL wyzwalacza Translator poniżej `VOICE_URL`:

    ```cpp
    const char *TRANSLATE_FUNCTION_URL = "<URL>";
    ```

    Zamień `<URL>` na URL dla wyzwalacza HTTP `translate-text` w Twojej aplikacji funkcji. Będzie to ta sama wartość co `TEXT_TO_TIMER_FUNCTION_URL`, z wyjątkiem nazwy funkcji `translate-text` zamiast `text-to-timer`.

1. Dodaj nowy plik do folderu `src` o nazwie `text_translator.h`.

1. Ten nowy plik nagłówkowy `text_translator.h` będzie zawierał klasę do tłumaczenia tekstu. Dodaj do tego pliku następujący kod, aby zadeklarować tę klasę:

    ```cpp
    #pragma once
    
    #include <Arduino.h>
    #include <ArduinoJson.h>
    #include <HTTPClient.h>
    #include <WiFiClient.h>
    
    #include "config.h"
    
    class TextTranslator
    {
    public:   
    private:
        WiFiClient _client;
    };
    
    TextTranslator textTranslator;
    ```

    Deklaruje to klasę `TextTranslator` oraz jej instancję. Klasa ma jedno pole dla klienta WiFi.

1. W sekcji `public` tej klasy dodaj metodę do tłumaczenia tekstu:

    ```cpp
    String translateText(String text, String from_language, String to_language)
    {
    }
    ```

    Ta metoda przyjmuje język, z którego tłumaczymy, oraz język, na który tłumaczymy. Podczas obsługi mowy, mowa będzie tłumaczona z języka użytkownika na język serwera LUIS, a podczas udzielania odpowiedzi będzie tłumaczona z języka serwera LUIS na język użytkownika.

1. W tej metodzie dodaj kod do skonstruowania treści JSON zawierającej tekst do przetłumaczenia oraz języki:

    ```cpp
    DynamicJsonDocument doc(1024);
    doc["text"] = text;
    doc["from_language"] = from_language;
    doc["to_language"] = to_language;

    String body;
    serializeJson(doc, body);

    Serial.print("Translating ");
    Serial.print(text);
    Serial.print(" from ");
    Serial.print(from_language);
    Serial.print(" to ");
    Serial.print(to_language);
    ```

1. Poniżej tego kodu dodaj kod do wysłania treści do aplikacji funkcji bezserwerowej:

    ```cpp
    HTTPClient httpClient;
    httpClient.begin(_client, TRANSLATE_FUNCTION_URL);

    int httpResponseCode = httpClient.POST(body);
    ```

1. Następnie dodaj kod do pobrania odpowiedzi:

    ```cpp
    String translated_text = "";

    if (httpResponseCode == 200)
    {
        translated_text = httpClient.getString();
        Serial.print("Translated: ");
        Serial.println(translated_text);
    }
    else
    {
        Serial.print("Failed to translate text - error ");
        Serial.println(httpResponseCode);
    }
    ```

1. Na końcu dodaj kod do zamknięcia połączenia i zwrócenia przetłumaczonego tekstu:

    ```cpp
    httpClient.end();

    return translated_text;
    ```

### Zadanie - tłumaczenie rozpoznanej mowy i odpowiedzi

1. Otwórz plik `main.cpp`.

1. Dodaj dyrektywę include na początku pliku dla pliku nagłówkowego klasy `TextTranslator`:

    ```cpp
    #include "text_translator.h"
    ```

1. Tekst wypowiadany, gdy timer jest ustawiany lub wygasa, musi być przetłumaczony. Aby to zrobić, dodaj następujący kod jako pierwszą linię funkcji `say`:

    ```cpp
    text = textTranslator.translateText(text, LANGUAGE, SERVER_LANGUAGE);
    ```

    To przetłumaczy tekst na język użytkownika.

1. W funkcji `processAudio` tekst jest pobierany z przechwyconego dźwięku za pomocą wywołania `String text = speechToText.convertSpeechToText();`. Po tym wywołaniu przetłumacz tekst:

    ```cpp
    String text = speechToText.convertSpeechToText();
    text = textTranslator.translateText(text, LANGUAGE, SERVER_LANGUAGE);
    ```

    To przetłumaczy tekst z języka użytkownika na język używany na serwerze.

1. Zbuduj ten kod, wgraj go na swój Wio Terminal i przetestuj za pomocą monitora szeregowego. Gdy zobaczysz `Ready` w monitorze szeregowym, naciśnij przycisk C (ten po lewej stronie, najbliżej przełącznika zasilania) i mów. Upewnij się, że Twoja aplikacja funkcji działa, i zażądaj timera w języku użytkownika, mówiąc w tym języku samodzielnie lub używając aplikacji tłumaczącej.

    ```output
    Connecting to WiFi..
    Connected!
    Got access token.
    Ready.
    Starting recording...
    Finished recording
    Sending speech...
    Speech sent!
    {"RecognitionStatus":"Success","DisplayText":"Définir une minuterie de 2 minutes 27 secondes.","Offset":9600000,"Duration":40400000}
    Translating Définir une minuterie de 2 minutes 27 secondes. from fr-FR to en-US
    Translated: Set a timer of 2 minutes 27 seconds.
    Set a timer of 2 minutes 27 seconds.
    {"seconds": 147}
    Translating 2 minute 27 second timer started. from en-US to fr-FR
    Translated: 2 minute 27 seconde minute a commencé.
    2 minute 27 seconde minute a commencé.
    Translating Times up on your 2 minute 27 second timer. from en-US to fr-FR
    Translated: Chronométrant votre minuterie de 2 minutes 27 secondes.
    Chronométrant votre minuterie de 2 minutes 27 secondes.
    ```

> 💁 Ten kod znajdziesz w folderze [code/wio-terminal](../../../../../6-consumer/lessons/4-multiple-language-support/code/wio-terminal).

😀 Twój wielojęzyczny program timera zakończył się sukcesem!

**Zastrzeżenie**:  
Ten dokument został przetłumaczony za pomocą usługi tłumaczenia AI [Co-op Translator](https://github.com/Azure/co-op-translator). Chociaż dokładamy wszelkich starań, aby tłumaczenie było precyzyjne, prosimy pamiętać, że automatyczne tłumaczenia mogą zawierać błędy lub nieścisłości. Oryginalny dokument w jego rodzimym języku powinien być uznawany za wiarygodne źródło. W przypadku informacji o kluczowym znaczeniu zaleca się skorzystanie z profesjonalnego tłumaczenia przez człowieka. Nie ponosimy odpowiedzialności za jakiekolwiek nieporozumienia lub błędne interpretacje wynikające z użycia tego tłumaczenia.