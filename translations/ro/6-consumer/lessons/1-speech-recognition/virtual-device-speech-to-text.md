<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "c0550b254b9ba2539baf1e6bb5fc05f8",
  "translation_date": "2025-08-28T09:13:24+00:00",
  "source_file": "6-consumer/lessons/1-speech-recognition/virtual-device-speech-to-text.md",
  "language_code": "ro"
}
-->
# Conversie vorbire în text - Dispozitiv IoT virtual

În această parte a lecției, vei scrie cod pentru a converti vorbirea captată de microfonul tău în text folosind serviciul de vorbire.

## Conversie vorbire în text

Pe Windows, Linux și macOS, SDK-ul Python pentru serviciile de vorbire poate fi utilizat pentru a asculta microfonul și a converti orice vorbire detectată în text. Acesta va asculta continuu, detectând nivelurile audio și trimițând vorbirea pentru conversie în text atunci când nivelul audio scade, cum ar fi la sfârșitul unui bloc de vorbire.

### Sarcină - conversie vorbire în text

1. Creează o nouă aplicație Python pe computerul tău într-un folder numit `smart-timer` cu un singur fișier numit `app.py` și un mediu virtual Python.

1. Instalează pachetul Pip pentru serviciile de vorbire. Asigură-te că faci acest lucru dintr-un terminal cu mediul virtual activat.

    ```sh
    pip install azure-cognitiveservices-speech
    ```

    > ⚠️ Dacă primești următoarea eroare:
    >
    > ```output
    > ERROR: Could not find a version that satisfies the requirement azure-cognitiveservices-speech (from versions: none)
    > ERROR: No matching distribution found for azure-cognitiveservices-speech
    > ```
    >
    > Va trebui să actualizezi Pip. Fă acest lucru cu următoarea comandă, apoi încearcă să instalezi din nou pachetul.
    >
    > ```sh
    > pip install --upgrade pip
    > ```

1. Adaugă următoarele importuri în fișierul `app.py`:

    ```python
    import requests
    import time
    from azure.cognitiveservices.speech import SpeechConfig, SpeechRecognizer
    ```

    Acestea importă câteva clase utilizate pentru recunoașterea vorbirii.

1. Adaugă următorul cod pentru a declara câteva configurații:

    ```python
    speech_api_key = '<key>'
    location = '<location>'
    language = '<language>'

    recognizer_config = SpeechConfig(subscription=speech_api_key,
                                     region=location,
                                     speech_recognition_language=language)
    ```

    Înlocuiește `<key>` cu cheia API pentru serviciul de vorbire. Înlocuiește `<location>` cu locația pe care ai utilizat-o când ai creat resursa pentru serviciul de vorbire.

    Înlocuiește `<language>` cu numele localizării pentru limba în care vei vorbi, de exemplu `en-GB` pentru engleză sau `zn-HK` pentru cantoneză. Poți găsi o listă a limbilor suportate și a numelor lor de localizare în [documentația despre suportul pentru limbă și voce pe Microsoft docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text).

    Această configurație este apoi utilizată pentru a crea un obiect `SpeechConfig` care va fi folosit pentru configurarea serviciilor de vorbire.

1. Adaugă următorul cod pentru a crea un recunoașter de vorbire:

    ```python
    recognizer = SpeechRecognizer(speech_config=recognizer_config)
    ```

1. Recunoașterul de vorbire rulează pe un fir de execuție în fundal, ascultând audio și convertind orice vorbire detectată în text. Poți obține textul utilizând o funcție de callback - o funcție pe care o definești și o transmiți recunoașterului. De fiecare dată când vorbirea este detectată, funcția de callback este apelată. Adaugă următorul cod pentru a defini o funcție de callback și pentru a o transmite recunoașterului, precum și pentru a defini o funcție care procesează textul, scriindu-l în consolă:

    ```python
    def process_text(text):
        print(text)

    def recognized(args):
        process_text(args.result.text)
    
    recognizer.recognized.connect(recognized)
    ```

1. Recunoașterul începe să asculte doar atunci când îl pornești explicit. Adaugă următorul cod pentru a începe recunoașterea. Acesta rulează în fundal, astfel încât aplicația ta va avea nevoie de un ciclu infinit care doarme pentru a menține aplicația activă.

    ```python
    recognizer.start_continuous_recognition()

    while True:
        time.sleep(1)
    ```

1. Rulează această aplicație. Vorbește în microfonul tău și audio-ul convertit în text va fi afișat în consolă.

    ```output
    (.venv) ➜  smart-timer python3 app.py
    Hello world.
    Welcome to IoT for beginners.
    ```

    Încearcă diferite tipuri de propoziții, împreună cu propoziții în care cuvintele sună la fel, dar au semnificații diferite. De exemplu, dacă vorbești în engleză, spune „I want to buy two bananas and an apple too” și observă cum va folosi corect „to”, „two” și „too” pe baza contextului cuvântului, nu doar a sunetului său.

> 💁 Poți găsi acest cod în folderul [code-speech-to-text/virtual-iot-device](../../../../../6-consumer/lessons/1-speech-recognition/code-speech-to-text/virtual-iot-device).

😀 Programul tău de conversie vorbire în text a fost un succes!

---

**Declinarea responsabilității**:  
Acest document a fost tradus folosind serviciul de traducere AI [Co-op Translator](https://github.com/Azure/co-op-translator). Deși depunem eforturi pentru a asigura acuratețea, vă rugăm să rețineți că traducerile automate pot conține erori sau inexactități. Documentul original în limba sa nativă ar trebui considerat sursa autoritară. Pentru informații critice, se recomandă traducerea profesională realizată de un specialist uman. Nu ne asumăm răspunderea pentru eventualele neînțelegeri sau interpretări greșite care pot apărea din utilizarea acestei traduceri.