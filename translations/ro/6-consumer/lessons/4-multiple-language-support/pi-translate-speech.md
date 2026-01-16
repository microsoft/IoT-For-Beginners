<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "bbb5aa34221fe129dd3ce4d9ec33831a",
  "translation_date": "2025-08-28T09:28:31+00:00",
  "source_file": "6-consumer/lessons/4-multiple-language-support/pi-translate-speech.md",
  "language_code": "ro"
}
-->
# Traduce discursul - Raspberry Pi

În această parte a lecției, vei scrie cod pentru a traduce text folosind serviciul de traducere.

## Convertește textul în vorbire folosind serviciul de traducere

API-ul REST al serviciului de vorbire nu suportă traduceri directe, însă poți folosi serviciul Translator pentru a traduce textul generat de serviciul de conversie vorbire în text și textul răspunsului vorbit. Acest serviciu are un API REST pe care îl poți folosi pentru a traduce textul.

### Sarcină - folosește resursa Translator pentru a traduce text

1. Cronometrul inteligent va avea setate 2 limbi - limba serverului care a fost folosit pentru antrenarea LUIS (aceeași limbă este folosită și pentru a construi mesajele adresate utilizatorului) și limba vorbită de utilizator. Actualizează variabila `language` pentru a fi limba vorbită de utilizator și adaugă o nouă variabilă numită `server_language` pentru limba folosită la antrenarea LUIS:

    ```python
    language = '<user language>'
    server_language = '<server language>'
    ```

    Înlocuiește `<user language>` cu numele localizării pentru limba în care vei vorbi, de exemplu `fr-FR` pentru franceză sau `zn-HK` pentru cantoneză.

    Înlocuiește `<server language>` cu numele localizării pentru limba folosită la antrenarea LUIS.

    Poți găsi o listă a limbilor suportate și numele lor de localizare în [documentația despre suportul pentru limbă și voce pe Microsoft docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text).

    > 💁 Dacă nu vorbești mai multe limbi, poți folosi un serviciu precum [Bing Translate](https://www.bing.com/translator) sau [Google Translate](https://translate.google.com) pentru a traduce din limba ta preferată într-o limbă la alegere. Aceste servicii pot reda audio textul tradus.
    >
    > De exemplu, dacă antrenezi LUIS în engleză, dar vrei să folosești franceza ca limbă a utilizatorului, poți traduce propoziții precum „set a 2 minute and 27 second timer” din engleză în franceză folosind Bing Translate, apoi folosește butonul **Listen translation** pentru a rosti traducerea în microfon.
    >
    > ![Butonul de ascultare a traducerii pe Bing Translate](../../../../../translated_images/ro/bing-translate.348aa796d6efe2a92f41ea74a5cf42bb4c63d6faaa08e7f46924e072a35daa48.png)

1. Adaugă cheia API a serviciului Translator sub `speech_api_key`:

    ```python
    translator_api_key = '<key>'
    ```

    Înlocuiește `<key>` cu cheia API pentru resursa serviciului Translator.

1. Deasupra funcției `say`, definește o funcție `translate_text` care va traduce textul din limba serverului în limba utilizatorului:

    ```python
    def translate_text(text, from_language, to_language):
    ```

    Limbile de la și către care se face traducerea sunt transmise acestei funcții - aplicația ta trebuie să convertească din limba utilizatorului în limba serverului când recunoaște vorbirea și din limba serverului în limba utilizatorului când oferă feedback vorbit.

1. În interiorul acestei funcții, definește URL-ul și anteturile pentru apelul API REST:

    ```python
    url = f'https://api.cognitive.microsofttranslator.com/translate?api-version=3.0'

    headers = {
        'Ocp-Apim-Subscription-Key': translator_api_key,
        'Ocp-Apim-Subscription-Region': location,
        'Content-type': 'application/json'
    }
    ```

    URL-ul acestui API nu este specific locației, în schimb locația este transmisă ca un antet. Cheia API este folosită direct, astfel încât, spre deosebire de serviciul de vorbire, nu este nevoie să obții un token de acces de la API-ul emitent de tokenuri.

1. Sub aceasta, definește parametrii și corpul apelului:

    ```python
    params = {
        'from': from_language,
        'to': to_language
    }

    body = [{
        'text' : text
    }]
    ```

    `params` definește parametrii care vor fi transmiși apelului API, specificând limbile de la și către care se face traducerea. Acest apel va traduce textul din limba `from` în limba `to`.

    `body` conține textul de tradus. Acesta este un array, deoarece mai multe blocuri de text pot fi traduse în același apel.

1. Realizează apelul API REST și obține răspunsul:

    ```python
    response = requests.post(url, headers=headers, params=params, json=body)
    ```

    Răspunsul primit este un array JSON, cu un element care conține traducerile. Acest element are un array pentru traducerile tuturor elementelor transmise în corp.

    ```json
    [
        {
            "translations": [
                {
                    "text": "Set a 2 minute 27 second timer.",
                    "to": "en"
                }
            ]
        }
    ]
    ```

1. Returnează proprietatea `test` din prima traducere a primului element din array:

    ```python
    return response.json()[0]['translations'][0]['text']
    ```

1. Actualizează bucla `while True` pentru a traduce textul din apelul către `convert_speech_to_text` din limba utilizatorului în limba serverului:

    ```python
    if len(text) > 0:
        print('Original:', text)
        text = translate_text(text, language, server_language)
        print('Translated:', text)

        message = Message(json.dumps({ 'speech': text }))
        device_client.send_message(message)
    ```

    Acest cod afișează, de asemenea, versiunile originale și traduse ale textului în consolă.

1. Actualizează funcția `say` pentru a traduce textul de spus din limba serverului în limba utilizatorului:

    ```python
    def say(text):
        print('Original:', text)
        text = translate_text(text, server_language, language)
        print('Translated:', text)
        speech = get_speech(text)
        play_speech(speech)
    ```

    Acest cod afișează, de asemenea, versiunile originale și traduse ale textului în consolă.

1. Rulează codul. Asigură-te că aplicația funcționează și solicită un cronometru în limba utilizatorului, fie vorbind în acea limbă, fie folosind o aplicație de traducere.

    ```output
    pi@raspberrypi:~/smart-timer $ python3 app.py
    Connecting
    Connected
    Using voice fr-FR-DeniseNeural
    Original: Définir une minuterie de 2 minutes et 27 secondes.
    Translated: Set a timer of 2 minutes and 27 seconds.
    Original: 2 minute 27 second timer started.
    Translated: 2 minute 27 seconde minute a commencé.
    Original: Times up on your 2 minute 27 second timer.
    Translated: Chronométrant votre minuterie de 2 minutes 27 secondes.
    ```

    > 💁 Datorită modurilor diferite de a spune ceva în diferite limbi, este posibil să obții traduceri care sunt ușor diferite de exemplele pe care le-ai oferit lui LUIS. Dacă acesta este cazul, adaugă mai multe exemple în LUIS, reantrenează și republică modelul.

> 💁 Poți găsi acest cod în folderul [code/pi](../../../../../6-consumer/lessons/4-multiple-language-support/code/pi).

😀 Programul tău de cronometru multilingv a fost un succes!

---

**Declinare de responsabilitate**:  
Acest document a fost tradus folosind serviciul de traducere AI [Co-op Translator](https://github.com/Azure/co-op-translator). Deși ne străduim să asigurăm acuratețea, vă rugăm să fiți conștienți că traducerile automate pot conține erori sau inexactități. Documentul original în limba sa maternă ar trebui considerat sursa autoritară. Pentru informații critice, se recomandă traducerea profesională realizată de un specialist uman. Nu ne asumăm responsabilitatea pentru eventualele neînțelegeri sau interpretări greșite care pot apărea din utilizarea acestei traduceri.