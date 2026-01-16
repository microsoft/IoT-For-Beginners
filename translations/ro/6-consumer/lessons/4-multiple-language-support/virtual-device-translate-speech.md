<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "d620a470d9dd8614d99824832978360a",
  "translation_date": "2025-08-28T09:29:45+00:00",
  "source_file": "6-consumer/lessons/4-multiple-language-support/virtual-device-translate-speech.md",
  "language_code": "ro"
}
-->
# Traducerea vorbirii - Dispozitiv IoT Virtual

În această parte a lecției, vei scrie cod pentru a traduce vorbirea atunci când este convertită în text folosind serviciul de vorbire, apoi vei traduce textul utilizând serviciul Translator înainte de a genera un răspuns vocal.

## Utilizarea serviciului de vorbire pentru a traduce vorbirea

Serviciul de vorbire poate prelua vorbirea și nu doar să o convertească în text în aceeași limbă, ci și să traducă rezultatul în alte limbi.

### Sarcină - utilizarea serviciului de vorbire pentru a traduce vorbirea

1. Deschide proiectul `smart-timer` în VS Code și asigură-te că mediul virtual este încărcat în terminal.

1. Adaugă următoarele declarații de import sub cele existente:

    ```python
    from azure.cognitiveservices import speech
    from azure.cognitiveservices.speech.translation import SpeechTranslationConfig, TranslationRecognizer
    import requests
    ```

    Acestea importă clase utilizate pentru a traduce vorbirea și o bibliotecă `requests` care va fi utilizată pentru a face un apel către serviciul Translator mai târziu în această lecție.

1. Cronometrul inteligent va avea setate 2 limbi - limba serverului care a fost utilizată pentru a antrena LUIS (aceeași limbă este utilizată și pentru a construi mesajele adresate utilizatorului) și limba vorbită de utilizator. Actualizează variabila `language` pentru a fi limba care va fi vorbită de utilizator și adaugă o nouă variabilă numită `server_language` pentru limba utilizată pentru a antrena LUIS:

    ```python
    language = '<user language>'
    server_language = '<server language>'
    ```

    Înlocuiește `<user language>` cu numele localizării pentru limba în care vei vorbi, de exemplu `fr-FR` pentru franceză sau `zn-HK` pentru cantoneză.

    Înlocuiește `<server language>` cu numele localizării pentru limba utilizată pentru a antrena LUIS.

    Poți găsi o listă a limbilor suportate și a numelor lor de localizare în [documentația despre suportul pentru limbă și voce pe Microsoft docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text).

    > 💁 Dacă nu vorbești mai multe limbi, poți utiliza un serviciu precum [Bing Translate](https://www.bing.com/translator) sau [Google Translate](https://translate.google.com) pentru a traduce din limba ta preferată într-o limbă la alegere. Aceste servicii pot reda audio al textului tradus. Fii conștient că recunoașterea vorbirii va ignora unele ieșiri audio de pe dispozitivul tău, așa că poate fi necesar să folosești un dispozitiv suplimentar pentru a reda textul tradus.
    >
    > De exemplu, dacă antrenezi LUIS în engleză, dar vrei să folosești franceza ca limbă a utilizatorului, poți traduce propoziții precum „set a 2 minute and 27 second timer” din engleză în franceză folosind Bing Translate, apoi folosește butonul **Listen translation** pentru a rosti traducerea în microfonul tău.
    >
    > ![Butonul de ascultare a traducerii pe Bing Translate](../../../../../translated_images/ro/bing-translate.348aa796d6efe2a92f41ea74a5cf42bb4c63d6faaa08e7f46924e072a35daa48.png)

1. Înlocuiește declarațiile `recognizer_config` și `recognizer` cu următoarele:

    ```python
    translation_config = SpeechTranslationConfig(subscription=speech_api_key,
                                                 region=location,
                                                 speech_recognition_language=language,
                                                 target_languages=(language, server_language))
    
    recognizer = TranslationRecognizer(translation_config=translation_config)
    ```

    Acest lucru creează o configurație de traducere pentru a recunoaște vorbirea în limba utilizatorului și pentru a crea traduceri în limba utilizatorului și a serverului. Apoi folosește această configurație pentru a crea un recognizer de traducere - un recognizer de vorbire care poate traduce rezultatul recunoașterii vorbirii în mai multe limbi.

    > 💁 Limba originală trebuie specificată în `target_languages`, altfel nu vei obține nicio traducere.

1. Actualizează funcția `recognized`, înlocuind întregul conținut al funcției cu următorul:

    ```python
    if args.result.reason == speech.ResultReason.TranslatedSpeech:
        language_match = next(l for l in args.result.translations if server_language.lower().startswith(l.lower()))
        text = args.result.translations[language_match]
        if (len(text) > 0):
            print(f'Translated text: {text}')
    
            message = Message(json.dumps({ 'speech': text }))
            device_client.send_message(message)
    ```

    Acest cod verifică dacă evenimentul de recunoaștere a fost declanșat deoarece vorbirea a fost tradusă (acest eveniment poate fi declanșat în alte momente, cum ar fi atunci când vorbirea este recunoscută, dar nu tradusă). Dacă vorbirea a fost tradusă, găsește traducerea în dicționarul `args.result.translations` care corespunde limbii serverului.

    Dicționarul `args.result.translations` este indexat pe baza părții de limbă a setării de localizare, nu pe întreaga setare. De exemplu, dacă soliciți o traducere în `fr-FR` pentru franceză, dicționarul va conține o intrare pentru `fr`, nu pentru `fr-FR`.

    Textul tradus este apoi trimis către IoT Hub.

1. Rulează acest cod pentru a testa traducerile. Asigură-te că aplicația funcțională este activă și solicită un cronometru în limba utilizatorului, fie vorbind în acea limbă, fie utilizând o aplicație de traducere.

    ```output
    (.venv) ➜  smart-timer python app.py
    Connecting
    Connected
    Translated text: Set a timer of 2 minutes and 27 seconds.
    ```

## Traducerea textului folosind serviciul Translator

Serviciul de vorbire nu suportă traducerea textului înapoi în vorbire, în schimb poți utiliza serviciul Translator pentru a traduce textul. Acest serviciu are o API REST pe care o poți folosi pentru a traduce textul.

### Sarcină - utilizarea resursei Translator pentru a traduce textul

1. Adaugă cheia API a Translator sub `speech_api_key`:

    ```python
    translator_api_key = '<key>'
    ```

    Înlocuiește `<key>` cu cheia API pentru resursa serviciului Translator.

1. Deasupra funcției `say`, definește o funcție `translate_text` care va traduce textul din limba serverului în limba utilizatorului:

    ```python
    def translate_text(text):
    ```

1. În interiorul acestei funcții, definește URL-ul și anteturile pentru apelul API REST:

    ```python
    url = f'https://api.cognitive.microsofttranslator.com/translate?api-version=3.0'

    headers = {
        'Ocp-Apim-Subscription-Key': translator_api_key,
        'Ocp-Apim-Subscription-Region': location,
        'Content-type': 'application/json'
    }
    ```

    URL-ul pentru această API nu este specific locației, în schimb locația este transmisă ca un antet. Cheia API este utilizată direct, așa că, spre deosebire de serviciul de vorbire, nu este nevoie să obții un token de acces de la API-ul de emitere a tokenului.

1. Sub aceasta, definește parametrii și corpul apelului:

    ```python
    params = {
        'from': server_language,
        'to': language
    }

    body = [{
        'text' : text
    }]
    ```

    `params` definește parametrii care vor fi transmiși apelului API, specificând limbile de la și către care se va traduce. Acest apel va traduce textul din limba `from` în limba `to`.

    `body` conține textul de tradus. Acesta este un array, deoarece mai multe blocuri de text pot fi traduse în același apel.

1. Realizează apelul către API-ul REST și obține răspunsul:

    ```python
    response = requests.post(url, headers=headers, params=params, json=body)
    ```

    Răspunsul care vine înapoi este un array JSON, cu un element care conține traducerile. Acest element are un array pentru traducerile tuturor elementelor transmise în corp.

    ```json
    [
        {
            "translations": [
                {
                    "text": "Chronométrant votre minuterie de 2 minutes 27 secondes.",
                    "to": "fr"
                }
            ]
        }
    ]
    ```

1. Returnează proprietatea `text` din prima traducere din primul element al array-ului:

    ```python
    return response.json()[0]['translations'][0]['text']
    ```

1. Actualizează funcția `say` pentru a traduce textul înainte ca SSML să fie generat:

    ```python
    print('Original:', text)
    text = translate_text(text)
    print('Translated:', text)
    ```

    Acest cod imprimă, de asemenea, versiunile originale și traduse ale textului în consolă.

1. Rulează codul. Asigură-te că aplicația funcțională este activă și solicită un cronometru în limba utilizatorului, fie vorbind în acea limbă, fie utilizând o aplicație de traducere.

    ```output
    (.venv) ➜  smart-timer python app.py
    Connecting
    Connected
    Translated text: Set a timer of 2 minutes and 27 seconds.
    Original: 2 minute 27 second timer started.
    Translated: 2 minute 27 seconde minute a commencé.
    Original: Times up on your 2 minute 27 second timer.
    Translated: Chronométrant votre minuterie de 2 minutes 27 secondes.
    ```

    > 💁 Datorită modurilor diferite de exprimare în diferite limbi, este posibil să obții traduceri care sunt ușor diferite de exemplele pe care le-ai oferit lui LUIS. Dacă acesta este cazul, adaugă mai multe exemple în LUIS, reantrenează și apoi republică modelul.

> 💁 Poți găsi acest cod în folderul [code/virtual-iot-device](../../../../../6-consumer/lessons/4-multiple-language-support/code/virtual-iot-device).

😀 Programul tău de cronometru multilingv a fost un succes!

---

**Declinare de responsabilitate**:  
Acest document a fost tradus folosind serviciul de traducere AI [Co-op Translator](https://github.com/Azure/co-op-translator). Deși ne străduim să asigurăm acuratețea, vă rugăm să rețineți că traducerile automate pot conține erori sau inexactități. Documentul original în limba sa maternă ar trebui considerat sursa autoritară. Pentru informații critice, se recomandă traducerea profesională realizată de un specialist uman. Nu ne asumăm responsabilitatea pentru eventualele neînțelegeri sau interpretări greșite care pot apărea din utilizarea acestei traduceri.