# Înțelegerea limbajului

![O prezentare generală a lecției sub formă de schiță](../../../../../translated_images/ro/lesson-22.6148ea28500d9e00.webp)

> Schiță realizată de [Nitya Narasimhan](https://github.com/nitya). Faceți clic pe imagine pentru o versiune mai mare.

## Chestionar înainte de lecție

[Chestionar înainte de lecție](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/43)

## Introducere

În lecția anterioară, ați convertit vorbirea în text. Pentru ca acest lucru să fie utilizat pentru a programa un cronometru inteligent, codul dvs. va trebui să înțeleagă ce s-a spus. Ați putea presupune că utilizatorul va rosti o frază fixă, cum ar fi „Setează un cronometru de 3 minute” și să analizați acea expresie pentru a determina durata cronometrului, dar acest lucru nu este foarte prietenos pentru utilizator. Dacă un utilizator ar spune „Setează un cronometru pentru 3 minute”, dvs. sau eu am înțelege ce înseamnă, dar codul dvs. nu ar înțelege, deoarece ar aștepta o frază fixă.

Aici intervine înțelegerea limbajului, utilizând modele de inteligență artificială pentru a interpreta textul și a returna detaliile necesare, de exemplu, fiind capabil să înțeleagă atât „Setează un cronometru de 3 minute”, cât și „Setează un cronometru pentru 3 minute” și să deducă că este necesar un cronometru pentru 3 minute.

În această lecție veți învăța despre modelele de înțelegere a limbajului, cum să le creați, să le antrenați și să le utilizați în codul dvs.

În această lecție vom acoperi:

* [Înțelegerea limbajului](../../../../../6-consumer/lessons/2-language-understanding)
* [Crearea unui model de înțelegere a limbajului](../../../../../6-consumer/lessons/2-language-understanding)
* [Intenții și entități](../../../../../6-consumer/lessons/2-language-understanding)
* [Utilizarea modelului de înțelegere a limbajului](../../../../../6-consumer/lessons/2-language-understanding)

## Înțelegerea limbajului

Oamenii folosesc limbajul pentru a comunica de sute de mii de ani. Comunicăm prin cuvinte, sunete sau acțiuni și înțelegem ce se spune, atât sensul cuvintelor, sunetelor sau acțiunilor, cât și contextul lor. Înțelegem sinceritatea și sarcasmul, permițând acelorași cuvinte să însemne lucruri diferite în funcție de tonul vocii.

✅ Gândiți-vă la unele dintre conversațiile pe care le-ați avut recent. Cât de mult din conversație ar fi dificil pentru un computer să înțeleagă din cauza necesității contextului?

Înțelegerea limbajului, numită și înțelegerea limbajului natural, face parte dintr-un domeniu al inteligenței artificiale numit procesarea limbajului natural (sau NLP) și se ocupă de înțelegerea detaliilor cuvintelor sau propozițiilor. Dacă utilizați un asistent vocal precum Alexa sau Siri, ați folosit servicii de înțelegere a limbajului. Acestea sunt serviciile AI din spatele scenei care transformă „Alexa, pune cel mai recent album al lui Taylor Swift” în fiica mea dansând prin sufragerie pe melodiile ei preferate.

> 💁 Calculatoarele, în ciuda tuturor progreselor lor, mai au un drum lung de parcurs pentru a înțelege cu adevărat textul. Când ne referim la înțelegerea limbajului cu ajutorul calculatoarelor, nu ne referim la ceva nici pe departe la fel de avansat ca comunicarea umană, ci mai degrabă la preluarea unor cuvinte și extragerea detaliilor esențiale.

Ca oameni, înțelegem limbajul fără să ne gândim prea mult la asta. Dacă aș cere unui alt om să „pune cel mai recent album al lui Taylor Swift”, acesta ar ști instinctiv ce vreau să spun. Pentru un computer, acest lucru este mai dificil. Ar trebui să ia cuvintele, convertite din vorbire în text, și să determine următoarele informații:

* Trebuie redată muzică
* Muzica este a artistei Taylor Swift
* Muzica specifică este un album întreg cu mai multe piese în ordine
* Taylor Swift are multe albume, așa că trebuie sortate în ordine cronologică, iar cel mai recent publicat este cel dorit

✅ Gândiți-vă la alte propoziții pe care le-ați rostit atunci când ați făcut cereri, cum ar fi comandarea unei cafele sau cererea unui membru al familiei să vă dea ceva. Încercați să le descompuneți în informațiile pe care un computer ar trebui să le extragă pentru a înțelege propoziția.

Modelele de înțelegere a limbajului sunt modele AI care sunt antrenate să extragă anumite detalii din limbaj și apoi sunt antrenate pentru sarcini specifice folosind învățarea transferului, în același mod în care ați antrenat un model Custom Vision folosind un set mic de imagini. Puteți lua un model, apoi să-l antrenați folosind textul pe care doriți să-l înțeleagă.

## Crearea unui model de înțelegere a limbajului

![Logo-ul LUIS](../../../../../translated_images/ro/luis-logo.5cb4f3e88c020ee6.webp)

Puteți crea modele de înțelegere a limbajului folosind LUIS, un serviciu de înțelegere a limbajului de la Microsoft, care face parte din Cognitive Services.

### Sarcină - creați o resursă de autor

Pentru a utiliza LUIS, trebuie să creați o resursă de autor.

1. Utilizați următoarea comandă pentru a crea o resursă de autor în grupul dvs. de resurse `smart-timer`:

    ```python
    az cognitiveservices account create --name smart-timer-luis-authoring \
                                        --resource-group smart-timer \
                                        --kind LUIS.Authoring \
                                        --sku F0 \
                                        --yes \
                                        --location <location>
    ```

    Înlocuiți `<location>` cu locația pe care ați utilizat-o atunci când ați creat grupul de resurse.

    > ⚠️ LUIS nu este disponibil în toate regiunile, așa că dacă primiți următoarea eroare:
    >
    > ```output
    > InvalidApiSetId: The account type 'LUIS.Authoring' is either invalid or unavailable in given region.
    > ```
    >
    > alegeți o altă regiune.

    Aceasta va crea o resursă de autor LUIS de nivel gratuit.

### Sarcină - creați o aplicație de înțelegere a limbajului

1. Deschideți portalul LUIS la [luis.ai](https://luis.ai?WT.mc_id=academic-17441-jabenn) în browserul dvs. și conectați-vă cu același cont pe care l-ați utilizat pentru Azure.

1. Urmați instrucțiunile din dialog pentru a selecta abonamentul dvs. Azure, apoi selectați resursa `smart-timer-luis-authoring` pe care tocmai ați creat-o.

1. Din lista *Conversation apps*, selectați butonul **New app** pentru a crea o nouă aplicație. Denumiți noua aplicație `smart-timer` și setați *Culture* la limba dvs.

    > 💁 Există un câmp pentru o resursă de predicție. Puteți crea o a doua resursă doar pentru predicție, dar resursa gratuită de autor permite 1.000 de predicții pe lună, ceea ce ar trebui să fie suficient pentru dezvoltare, așa că puteți lăsa acest câmp necompletat.

1. Citiți ghidul care apare odată ce creați aplicația pentru a înțelege pașii pe care trebuie să îi urmați pentru a antrena modelul de înțelegere a limbajului. Închideți acest ghid când ați terminat.

## Intenții și entități

Înțelegerea limbajului se bazează pe *intenții* și *entități*. Intențiile reprezintă scopul cuvintelor, de exemplu redarea muzicii, setarea unui cronometru sau comandarea mâncării. Entitățile reprezintă ceea ce intenția face referire, cum ar fi albumul, durata cronometrului sau tipul de mâncare. Fiecare propoziție interpretată de model ar trebui să aibă cel puțin o intenție și, opțional, una sau mai multe entități.

Câteva exemple:

| Propoziție                                          | Intenție         | Entități                                   |
| --------------------------------------------------- | ---------------- | ------------------------------------------ |
| „Redă cel mai recent album al lui Taylor Swift”    | *redă muzică*    | *cel mai recent album al lui Taylor Swift* |
| „Setează un cronometru de 3 minute”                | *setează cronometru* | *3 minute*                                |
| „Anulează cronometrul meu”                         | *anulează cronometru* | Niciuna                                   |
| „Comandă 3 pizza mari cu ananas și o salată Caesar”| *comandă mâncare* | *3 pizza mari cu ananas*, *salată Caesar* |

✅ Cu propozițiile la care v-ați gândit mai devreme, care ar fi intenția și entitățile din acea propoziție?

Pentru a antrena LUIS, mai întâi setați entitățile. Acestea pot fi o listă fixă de termeni sau învățate din text. De exemplu, puteți furniza o listă fixă de mâncăruri disponibile din meniul dvs., cu variații (sau sinonime) pentru fiecare cuvânt, cum ar fi *vânătă* și *aubergine* ca variații pentru *vânătă*. LUIS are, de asemenea, entități predefinite care pot fi utilizate, cum ar fi numerele și locațiile.

Pentru setarea unui cronometru, ați putea avea o entitate folosind entitățile predefinite pentru numere pentru timp și alta pentru unități, cum ar fi minute și secunde. Fiecare unitate ar avea mai multe variații pentru a acoperi formele singular și plural - cum ar fi minut și minute.

Odată ce entitățile sunt definite, creați intențiile. Acestea sunt învățate de model pe baza propozițiilor exemplu pe care le furnizați (cunoscute sub numele de enunțuri). De exemplu, pentru o intenție *setează cronometru*, ați putea furniza următoarele propoziții:

* `setează un cronometru de 1 secundă`
* `setează un cronometru pentru 1 minut și 12 secunde`
* `setează un cronometru pentru 3 minute`
* `setează un cronometru de 9 minute și 30 de secunde`

Apoi spuneți LUIS ce părți ale acestor propoziții corespund entităților:

![Propoziția „setează un cronometru pentru 1 minut și 12 secunde” împărțită în entități](../../../../../translated_images/ro/sentence-as-intent-entities.301401696f992259.webp)

Propoziția `setează un cronometru pentru 1 minut și 12 secunde` are intenția `setează cronometru`. De asemenea, are 2 entități cu câte 2 valori fiecare:

|            | timp | unitate   |
| ---------- | ---: | --------- |
| 1 minut    | 1    | minut     |
| 12 secunde | 12   | secundă   |

Pentru a antrena un model bun, aveți nevoie de o gamă variată de propoziții exemplu pentru a acoperi numeroasele moduri în care cineva ar putea cere același lucru.

> 💁 Ca în cazul oricărui model AI, cu cât datele sunt mai multe și mai precise, cu atât modelul va fi mai bun.

✅ Gândiți-vă la diferitele moduri în care ați putea cere același lucru și v-ați aștepta ca un om să înțeleagă.

### Sarcină - adăugați entități la modelele de înțelegere a limbajului

Pentru cronometru, trebuie să adăugați 2 entități - una pentru unitatea de timp (minute sau secunde) și alta pentru numărul de minute sau secunde.

Puteți găsi instrucțiuni pentru utilizarea portalului LUIS în documentația [Quickstart: Build your app in LUIS portal](https://docs.microsoft.com/azure/cognitive-services/luis/luis-get-started-create-app?WT.mc_id=academic-17441-jabenn).

1. Din portalul LUIS, selectați fila *Entities* și adăugați entitatea predefinită *number* selectând butonul **Add prebuilt entity**, apoi selectând *number* din listă.

1. Creați o nouă entitate pentru unitatea de timp utilizând butonul **Create**. Denumiți entitatea `time unit` și setați tipul la *List*. Adăugați valori pentru `minute` și `second` în lista *Normalized values*, adăugând formele singular și plural în lista *synonyms*. Apăsați `return` după adăugarea fiecărui sinonim pentru a-l adăuga în listă.

    | Valoare normalizată | Sinonime        |
    | ------------------- | --------------- |
    | minute              | minut, minute   |
    | second              | secundă, secunde |

### Sarcină - adăugați intenții la modelele de înțelegere a limbajului

1. Din fila *Intents*, selectați butonul **Create** pentru a crea o nouă intenție. Denumiți această intenție `set timer`.

1. În exemple, introduceți diferite moduri de a seta un cronometru folosind atât minute, secunde, cât și combinații de minute și secunde. Exemplele ar putea fi:

    * `setează un cronometru de 1 secundă`
    * `setează un cronometru de 4 minute`
    * `setează un cronometru de patru minute și șase secunde`
    * `setează un cronometru de 9 minute și 30 de secunde`
    * `setează un cronometru pentru 1 minut și 12 secunde`
    * `setează un cronometru pentru 3 minute`
    * `setează un cronometru pentru 3 minute și 1 secundă`
    * `setează un cronometru pentru trei minute și o secundă`
    * `setează un cronometru pentru 1 minut și 1 secundă`
    * `setează un cronometru pentru 30 de secunde`
    * `setează un cronometru pentru 1 secundă`

    Amestecați numerele scrise în cuvinte și cele numerice, astfel încât modelul să învețe să le gestioneze pe ambele.

1. Pe măsură ce introduceți fiecare exemplu, LUIS va începe să detecteze entități și va sublinia și eticheta orice găsește.

    ![Exemplele cu numerele și unitățile de timp subliniate de LUIS](../../../../../translated_images/ro/luis-intent-examples.25716580b2d2723c.webp)

### Sarcină - antrenați și testați modelul

1. Odată ce entitățile și intențiile sunt configurate, puteți antrena modelul utilizând butonul **Train** din meniul de sus. Selectați acest buton, iar modelul ar trebui să se antreneze în câteva secunde. Butonul va fi dezactivat în timpul antrenării și va fi reactivat odată ce procesul este finalizat.

1. Selectați butonul **Test** din meniul de sus pentru a testa modelul de înțelegere a limbajului. Introduceți text, cum ar fi `setează un cronometru pentru 5 minute și 4 secunde`, și apăsați return. Propoziția va apărea într-o casetă sub caseta de text în care ați tastat, iar sub aceasta va fi afișată *intenția principală*, sau intenția detectată cu cea mai mare probabilitate. Aceasta ar trebui să fie `set timer`. Numele intenției va fi urmat de probabilitatea ca intenția detectată să fie cea corectă.

1. Selectați opțiunea **Inspect** pentru a vedea o defalcare a rezultatelor. Veți vedea intenția cu cel mai mare scor și procentajul probabilității sale, împreună cu listele entităților detectate.

1. Închideți panoul *Test* când ați terminat testarea.

### Sarcină - publicați modelul

Pentru a utiliza acest model din cod, trebuie să îl publicați. Când publicați din LUIS, puteți publica fie într-un mediu de testare, fie într-un mediu de producție pentru o lansare completă. În această lecție, un mediu de testare este suficient.

1. Din portalul LUIS, selectați butonul **Publish** din meniul de sus.

1. Asigurați-vă că este selectată opțiunea *Staging slot*, apoi selectați **Done**. Veți vedea o notificare când aplicația este publicată.

1. Puteți testa acest lucru utilizând curl. Pentru a construi comanda curl, aveți nevoie de trei valori - endpoint-ul, ID-ul aplicației (App ID) și o cheie API. Acestea pot fi accesate din fila **MANAGE**, care poate fi selectată din meniul de sus.

    1. Din secțiunea *Settings*, copiați App ID.
1. Din secțiunea *Azure Resources*, selectează *Authoring Resource* și copiază *Primary Key* și *Endpoint URL*.

1. Rulează următoarea comandă curl în promptul de comandă sau terminal:

    ```sh
    curl "<endpoint url>/luis/prediction/v3.0/apps/<app id>/slots/staging/predict" \
          --request GET \
          --get \
          --data "subscription-key=<primary key>" \
          --data "verbose=false" \
          --data "show-all-intents=true" \
          --data-urlencode "query=<sentence>"
    ```

    Înlocuiește `<endpoint url>` cu Endpoint URL din secțiunea *Azure Resources*.

    Înlocuiește `<app id>` cu App ID din secțiunea *Settings*.

    Înlocuiește `<primary key>` cu Primary Key din secțiunea *Azure Resources*.

    Înlocuiește `<sentence>` cu propoziția pe care vrei să o testezi.

1. Rezultatul acestui apel va fi un document JSON care detaliază interogarea, intenția principală și o listă de entități clasificate pe tipuri.

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

    JSON-ul de mai sus provine din interogarea cu `set a timer for 45 minutes and 12 seconds`:

    * `set timer` a fost intenția principală cu o probabilitate de 97%.
    * Au fost detectate două entități de tip *number*, `45` și `12`.
    * Au fost detectate două entități de tip *time-unit*, `minute` și `second`.

## Utilizarea modelului de înțelegere a limbajului

Odată publicat, modelul LUIS poate fi apelat din cod. În lecțiile anterioare, ai folosit un IoT Hub pentru a gestiona comunicarea cu serviciile cloud, trimițând telemetrie și ascultând comenzile. Acest proces este foarte asincron - odată ce telemetria este trimisă, codul tău nu așteaptă un răspuns, iar dacă serviciul cloud este indisponibil, nu vei ști.

Pentru un cronometru inteligent, dorim un răspuns imediat, astfel încât să putem informa utilizatorul că un cronometru a fost setat sau să-l alertăm că serviciile cloud nu sunt disponibile. Pentru a face acest lucru, dispozitivul nostru IoT va apela direct un endpoint web, în loc să se bazeze pe un IoT Hub.

În loc să apelezi LUIS direct de pe dispozitivul IoT, poți utiliza cod serverless cu un alt tip de trigger - un trigger HTTP. Acesta permite aplicației tale de funcții să asculte cereri REST și să răspundă la ele. Această funcție va fi un endpoint REST pe care dispozitivul tău îl poate apela.

> 💁 Deși poți apela LUIS direct de pe dispozitivul IoT, este mai bine să folosești ceva precum cod serverless. Astfel, când dorești să schimbi aplicația LUIS pe care o apelezi, de exemplu, când antrenezi un model mai bun sau un model într-o altă limbă, trebuie doar să actualizezi codul din cloud, fără să redeploiezi codul pe potențial mii sau milioane de dispozitive IoT.

### Sarcină - creează o aplicație de funcții serverless

1. Creează o aplicație Azure Functions numită `smart-timer-trigger` și deschide-o în VS Code.

1. Adaugă un trigger HTTP la această aplicație numit `speech-trigger` folosind următoarea comandă din terminalul VS Code:

    ```sh
    func new --name text-to-timer --template "HTTP trigger"
    ```

    Aceasta va crea un trigger HTTP numit `text-to-timer`.

1. Testează trigger-ul HTTP rulând aplicația de funcții. Când rulează, vei vedea endpoint-ul listat în output:

    ```output
    Functions:
    
            text-to-timer: [GET,POST] http://localhost:7071/api/text-to-timer
    ```

    Testează acest lucru încărcând URL-ul [http://localhost:7071/api/text-to-timer](http://localhost:7071/api/text-to-timer) în browserul tău.

    ```output
    This HTTP triggered function executed successfully. Pass a name in the query string or in the request body for a personalized response.
    ```

### Sarcină - utilizează modelul de înțelegere a limbajului

1. SDK-ul pentru LUIS este disponibil printr-un pachet Pip. Adaugă următoarea linie în fișierul `requirements.txt` pentru a adăuga dependența de acest pachet:

    ```sh
    azure-cognitiveservices-language-luis
    ```

1. Asigură-te că terminalul VS Code are activat mediul virtual și rulează următoarea comandă pentru a instala pachetele Pip:

    ```sh
    pip install -r requirements.txt
    ```

    > 💁 Dacă întâmpini erori, poate fi necesar să actualizezi pip cu următoarea comandă:
    >
    > ```sh
    > pip install --upgrade pip
    > ```

1. Adaugă noi intrări în fișierul `local.settings.json` pentru LUIS API Key, Endpoint URL și App ID din fila **MANAGE** a portalului LUIS:

    ```JSON
    "LUIS_KEY": "<primary key>",
    "LUIS_ENDPOINT_URL": "<endpoint url>",
    "LUIS_APP_ID": "<app id>"
    ```

    Înlocuiește `<endpoint url>` cu Endpoint URL din secțiunea *Azure Resources* a filei **MANAGE**. Acesta va fi `https://<location>.api.cognitive.microsoft.com/`.

    Înlocuiește `<app id>` cu App ID din secțiunea *Settings* a filei **MANAGE**.

    Înlocuiește `<primary key>` cu Primary Key din secțiunea *Azure Resources* a filei **MANAGE**.

1. Adaugă următoarele importuri în fișierul `__init__.py`:

    ```python
    import json
    import os
    from azure.cognitiveservices.language.luis.runtime import LUISRuntimeClient
    from msrest.authentication import CognitiveServicesCredentials
    ```

    Acestea importă câteva biblioteci de sistem, precum și bibliotecile pentru a interacționa cu LUIS.

1. Șterge conținutul metodei `main` și adaugă următorul cod:

    ```python
    luis_key = os.environ['LUIS_KEY']
    endpoint_url = os.environ['LUIS_ENDPOINT_URL']
    app_id = os.environ['LUIS_APP_ID']
    
    credentials = CognitiveServicesCredentials(luis_key)
    client = LUISRuntimeClient(endpoint=endpoint_url, credentials=credentials)
    ```

    Acest cod încarcă valorile pe care le-ai adăugat în fișierul `local.settings.json` pentru aplicația LUIS, creează un obiect de acreditive cu cheia API, apoi creează un obiect client LUIS pentru a interacționa cu aplicația LUIS.

1. Acest trigger HTTP va fi apelat trimițând textul de înțeles ca JSON, cu textul într-o proprietate numită `text`. Următorul cod extrage valoarea din corpul cererii HTTP și o înregistrează în consolă. Adaugă acest cod în funcția `main`:

    ```python
    req_body = req.get_json()
    text = req_body['text']
    logging.info(f'Request - {text}')
    ```

1. Predicțiile sunt solicitate de la LUIS prin trimiterea unei cereri de predicție - un document JSON care conține textul de prezis. Creează acest lucru cu următorul cod:

    ```python
    prediction_request = { 'query' : text }
    ```

1. Această cerere poate fi apoi trimisă către LUIS, utilizând slotul de staging în care aplicația ta a fost publicată:

    ```python
    prediction_response = client.prediction.get_slot_prediction(app_id, 'Staging', prediction_request)
    ```

1. Răspunsul predicției conține intenția principală - intenția cu cel mai mare scor de predicție, împreună cu entitățile. Dacă intenția principală este `set timer`, atunci entitățile pot fi citite pentru a obține timpul necesar pentru cronometru:

    ```python
    if prediction_response.prediction.top_intent == 'set timer':
        numbers = prediction_response.prediction.entities['number']
        time_units = prediction_response.prediction.entities['time unit']
        total_seconds = 0
    ```

    Entitățile de tip `number` vor fi un array de numere. De exemplu, dacă ai spus *"Set a four minute 17 second timer."*, atunci array-ul `number` va conține 2 numere întregi - 4 și 17.

    Entitățile de tip `time unit` vor fi un array de array-uri de șiruri de caractere, fiecare unitate de timp fiind un array de șiruri în interiorul array-ului. De exemplu, dacă ai spus *"Set a four minute 17 second timer."*, atunci array-ul `time unit` va conține 2 array-uri cu câte o valoare fiecare - `['minute']` și `['second']`.

    Versiunea JSON a acestor entități pentru *"Set a four minute 17 second timer."* este:

    ```json
    {
        "number": [4, 17],
        "time unit": [
            ["minute"],
            ["second"]
        ]
    }
    ```

    Acest cod definește, de asemenea, un contor pentru timpul total al cronometrului în secunde. Acesta va fi populat cu valorile din entități.

1. Entitățile nu sunt legate, dar putem face câteva presupuneri despre ele. Ele vor fi în ordinea în care au fost rostite, astfel încât poziția în array poate fi utilizată pentru a determina care număr corespunde cu care unitate de timp. De exemplu:

    * *"Set a 30 second timer"* - aceasta va avea un singur număr, `30`, și o singură unitate de timp, `second`, astfel încât numărul unic va corespunde unității de timp unice.
    * *"Set a 2 minute and 30 second timer"* - aceasta va avea două numere, `2` și `30`, și două unități de timp, `minute` și `second`, astfel încât primul număr va fi pentru prima unitate de timp (2 minute), iar al doilea număr pentru a doua unitate de timp (30 secunde).

    Următorul cod obține numărul de elemente din entitățile de tip număr și folosește acest lucru pentru a extrage primul element din fiecare array, apoi al doilea și așa mai departe. Adaugă acest lucru în interiorul blocului `if`.

    ```python
    for i in range(0, len(numbers)):
        number = numbers[i]
        time_unit = time_units[i][0]
    ```

    Pentru *"Set a four minute 17 second timer."*, acest cod va itera de două ori, oferind următoarele valori:

    | număr iterație | `number` | `time_unit` |
    | -------------: | -------: | ----------- |
    | 0              | 4        | minute      |
    | 1              | 17       | second      |

1. În interiorul acestui loop, folosește numărul și unitatea de timp pentru a calcula timpul total pentru cronometru, adăugând 60 de secunde pentru fiecare minut și numărul de secunde pentru orice secunde.

    ```python
    if time_unit == 'minute':
        total_seconds += number * 60
    else:
        total_seconds += number
    ```

1. În afara acestui loop prin entități, înregistrează timpul total pentru cronometru:

    ```python
    logging.info(f'Timer required for {total_seconds} seconds')
    ```

1. Numărul de secunde trebuie returnat din funcție ca răspuns HTTP. La sfârșitul blocului `if`, adaugă următorul cod:

    ```python
    payload = {
        'seconds': total_seconds
    }
    return func.HttpResponse(json.dumps(payload), status_code=200)
    ```

    Acest cod creează o sarcină utilă care conține numărul total de secunde pentru cronometru, o convertește într-un șir JSON și o returnează ca rezultat HTTP cu un cod de stare 200, ceea ce înseamnă că apelul a fost realizat cu succes.

1. În cele din urmă, în afara blocului `if`, gestionează cazul în care intenția nu a fost recunoscută, returnând un cod de eroare:

    ```python
    return func.HttpResponse(status_code=404)
    ```

    404 este codul de stare pentru *not found*.

1. Rulează aplicația de funcții și testeaz-o folosind curl.

    ```sh
    curl --request POST 'http://localhost:7071/api/text-to-timer' \
         --header 'Content-Type: application/json' \
         --include \
         --data '{"text":"<text>"}'
    ```

    Înlocuiește `<text>` cu textul cererii tale, de exemplu `set a 2 minutes 27 second timer`.

    Vei vedea următorul output din aplicația de funcții:

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

    Apelul curl va returna următorul rezultat:

    ```output
    HTTP/1.1 200 OK
    Date: Tue, 29 Jun 2021 01:14:11 GMT
    Content-Type: text/plain; charset=utf-8
    Server: Kestrel
    Transfer-Encoding: chunked
    
    {"seconds": 147}
    ```

    Numărul de secunde pentru cronometru este în valoarea `"seconds"`.

> 💁 Poți găsi acest cod în folderul [code/functions](../../../../../6-consumer/lessons/2-language-understanding/code/functions).

### Sarcină - fă funcția ta disponibilă pentru dispozitivul IoT

1. Pentru ca dispozitivul IoT să apeleze endpoint-ul REST, va trebui să cunoască URL-ul. Când l-ai accesat mai devreme, ai folosit `localhost`, care este un shortcut pentru a accesa endpoint-uri REST pe mașina ta locală. Pentru a permite dispozitivului IoT să obțină acces, trebuie fie să publici în cloud, fie să obții adresa IP pentru a accesa local.

    > ⚠️ Dacă folosești un Wio Terminal, este mai ușor să rulezi aplicația de funcții local, deoarece va exista o dependență de biblioteci care înseamnă că nu poți implementa aplicația de funcții în același mod ca înainte. Rulează aplicația de funcții local și acceseaz-o prin adresa IP a computerului tău. Dacă dorești să implementezi în cloud, informațiile vor fi furnizate într-o lecție ulterioară despre cum să faci acest lucru.

    * Publică aplicația de funcții - urmează instrucțiunile din lecțiile anterioare pentru a publica aplicația de funcții în cloud. Odată publicată, URL-ul va fi `https://<APP_NAME>.azurewebsites.net/api/text-to-timer`, unde `<APP_NAME>` va fi numele aplicației tale de funcții. Asigură-te că publici și setările locale.

      Când lucrezi cu trigger-uri HTTP, acestea sunt securizate implicit cu o cheie a aplicației de funcții. Pentru a obține această cheie, rulează următoarea comandă:

      ```sh
      az functionapp keys list --resource-group smart-timer \
                               --name <APP_NAME>                               
      ```

      Copiază valoarea intrării `default` din secțiunea `functionKeys`.

      ```output
      {
        "functionKeys": {
          "default": "sQO1LQaeK9N1qYD6SXeb/TctCmwQEkToLJU6Dw8TthNeUH8VA45hlA=="
        },
        "masterKey": "RSKOAIlyvvQEQt9dfpabJT018scaLpQu9p1poHIMCxx5LYrIQZyQ/g==",
        "systemKeys": {}
      }
      ```

      Această cheie va trebui adăugată ca parametru de interogare la URL, astfel încât URL-ul final va fi `https://<APP_NAME>.azurewebsites.net/api/text-to-timer?code=<FUNCTION_KEY>`, unde `<APP_NAME>` va fi numele aplicației tale de funcții, iar `<FUNCTION_KEY>` va fi cheia ta implicită a funcției.

      > 💁 Poți schimba tipul de autorizare al trigger-ului HTTP utilizând setarea `authlevel` din fișierul `function.json`. Poți citi mai multe despre acest lucru în [secțiunea de configurare a documentației Azure Functions HTTP trigger pe Microsoft docs](https://docs.microsoft.com/azure/azure-functions/functions-bindings-http-webhook-trigger?WT.mc_id=academic-17441-jabenn&tabs=python#configuration).

    * Rulează aplicația de funcții local și acceseaz-o utilizând adresa IP - poți obține adresa IP a computerului tău în rețeaua locală și o poți folosi pentru a construi URL-ul.

      Găsește adresa ta IP:

      * Pe Windows 10, urmează ghidul [găsește adresa ta IP](https://support.microsoft.com/windows/find-your-ip-address-f21a9bbc-c582-55cd-35e0-73431160a1b9?WT.mc_id=academic-17441-jabenn).
      * Pe macOS, urmează ghidul [cum să găsești adresa IP pe un Mac](https://www.hellotech.com/guide/for/how-to-find-ip-address-on-mac).
      * Pe Linux, urmează secțiunea despre găsirea adresei IP private din [ghidul cum să găsești adresa IP în Linux](https://opensource.com/article/18/5/how-find-ip-address-linux).

      Odată ce ai adresa IP, vei putea accesa funcția la `http://`.

:7071/api/text-to-timer`, unde `<IP_ADDRESS>` va fi adresa ta IP, de exemplu `http://192.168.1.10:7071/api/text-to-timer`.

      > 💁 Reține că se folosește portul 7071, așa că după adresa IP va trebui să adaugi `:7071`.

      > 💁 Acest lucru va funcționa doar dacă dispozitivul tău IoT este pe aceeași rețea cu computerul tău.

1. Testează endpoint-ul accesându-l folosind curl.

---

## 🚀 Provocare

Există multe moduri de a solicita același lucru, cum ar fi setarea unui cronometru. Gândește-te la diferite moduri de a face acest lucru și folosește-le ca exemple în aplicația ta LUIS. Testează-le pentru a vedea cât de bine poate modelul tău să gestioneze multiple moduri de a solicita un cronometru.

## Chestionar post-lectură

[Chestionar post-lectură](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/44)

## Recapitulare și studiu individual

* Citește mai multe despre LUIS și capacitățile sale pe [pagina de documentație Language Understanding (LUIS) de pe Microsoft docs](https://docs.microsoft.com/azure/cognitive-services/luis/?WT.mc_id=academic-17441-jabenn)
* Citește mai multe despre înțelegerea limbajului pe [pagina despre înțelegerea limbajului natural de pe Wikipedia](https://wikipedia.org/wiki/Natural-language_understanding)
* Citește mai multe despre trigger-ele HTTP în [documentația despre Azure Functions HTTP trigger de pe Microsoft docs](https://docs.microsoft.com/azure/azure-functions/functions-bindings-http-webhook-trigger?WT.mc_id=academic-17441-jabenn&tabs=python)

## Temă

[Anulează cronometrul](assignment.md)

---

**Declinare de responsabilitate**:  
Acest document a fost tradus folosind serviciul de traducere AI [Co-op Translator](https://github.com/Azure/co-op-translator). Deși ne străduim să asigurăm acuratețea, vă rugăm să fiți conștienți că traducerile automate pot conține erori sau inexactități. Documentul original în limba sa maternă ar trebui considerat sursa autoritară. Pentru informații critice, se recomandă traducerea profesională realizată de un specialist uman. Nu ne asumăm responsabilitatea pentru eventualele neînțelegeri sau interpretări greșite care pot apărea din utilizarea acestei traduceri.