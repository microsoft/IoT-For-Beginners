<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "c24b6e4d90501c9199f2ceb6a648a337",
  "translation_date": "2025-08-28T11:12:30+00:00",
  "source_file": "2-farm/lessons/5-migrate-application-to-the-cloud/assignment.md",
  "language_code": "ro"
}
-->
# Adaugă control manual pentru releu

## Instrucțiuni

Codul serverless poate fi declanșat de diverse evenimente, inclusiv cereri HTTP. Poți utiliza declanșatoare HTTP pentru a adăuga o opțiune de control manual al releului, permițând cuiva să pornească sau să oprească releul printr-o cerere web.

Pentru această sarcină, trebuie să adaugi două declanșatoare HTTP în aplicația ta Functions pentru a porni și opri releul, reutilizând ceea ce ai învățat în această lecție pentru a trimite comenzi către dispozitiv.

Câteva sugestii:

* Poți adăuga un declanșator HTTP în aplicația ta Functions existentă folosind următoarea comandă:

    ```sh
    func new --name <trigger name> --template "HTTP trigger"
    ```

    Înlocuiește `<trigger name>` cu numele declanșatorului HTTP. Folosește ceva de genul `relay_on` și `relay_off`.

* Declanșatoarele HTTP pot avea control de acces. Implicit, acestea necesită o cheie API specifică funcției pentru a fi transmisă împreună cu URL-ul pentru a rula. Pentru această sarcină, poți elimina această restricție astfel încât oricine să poată rula funcția. Pentru a face acest lucru, actualizează setarea `authLevel` din fișierul `function.json` pentru declanșatoarele HTTP la următoarea valoare:

    ```json
    "authLevel": "anonymous"
    ```

    > 💁 Poți citi mai multe despre acest control de acces în [documentația despre cheile de acces ale funcțiilor](https://docs.microsoft.com/azure/azure-functions/functions-bindings-http-webhook-trigger?WT.mc_id=academic-17441-jabenn#authorization-keys).

* Declanșatoarele HTTP acceptă implicit cereri GET și POST. Aceasta înseamnă că le poți apela folosind browserul web - browserele web fac cereri GET.

    Când rulezi local aplicația Functions, vei vedea URL-ul declanșatorului:

    ```output
    Functions:

        relay_off: [GET,POST] http://localhost:7071/api/relay_off

        relay_on: [GET,POST] http://localhost:7071/api/relay_on

        iot-hub-trigger: eventHubTrigger
    ```

    Copiază URL-ul în browser și apasă `return`, sau `Ctrl+click` (`Cmd+click` pe macOS) pe linkul din fereastra terminalului din VS Code pentru a-l deschide în browserul tău implicit. Acest lucru va rula declanșatorul.

    > 💁 Observă că URL-ul conține `/api` - declanșatoarele HTTP sunt implicit în subdomeniul `api`.

* Când publici aplicația Functions, URL-ul declanșatorului HTTP va fi:

    `https://<functions app name>.azurewebsites.net/api/<trigger name>`

    Unde `<functions app name>` este numele aplicației tale Functions, iar `<trigger name>` este numele declanșatorului.

## Criterii de evaluare

| Criterii | Exemplu | Adecvat | Necesită îmbunătățiri |
| -------- | ------- | ------- | --------------------- |
| Crearea declanșatoarelor HTTP | Au fost create 2 declanșatoare pentru a porni și opri releul, cu nume corespunzătoare | A fost creat un declanșator cu un nume corespunzător | Nu s-a reușit crearea niciunui declanșator |
| Controlul releului din declanșatoarele HTTP | Ambele declanșatoare au fost conectate la IoT Hub și controlează releul corespunzător | Un declanșator a fost conectat la IoT Hub și controlează releul corespunzător | Nu s-a reușit conectarea declanșatoarelor la IoT Hub |

---

**Declinare de responsabilitate**:  
Acest document a fost tradus folosind serviciul de traducere AI [Co-op Translator](https://github.com/Azure/co-op-translator). Deși ne străduim să asigurăm acuratețea, vă rugăm să fiți conștienți că traducerile automate pot conține erori sau inexactități. Documentul original în limba sa natală ar trebui considerat sursa autoritară. Pentru informații critice, se recomandă traducerea profesională realizată de un specialist uman. Nu ne asumăm responsabilitatea pentru eventualele neînțelegeri sau interpretări greșite care pot apărea din utilizarea acestei traduceri.