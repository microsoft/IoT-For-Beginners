<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "af249a24d4fe4f4de4806adbc3bc9d86",
  "translation_date": "2025-08-28T09:17:11+00:00",
  "source_file": "6-consumer/lessons/1-speech-recognition/pi-speech-to-text.md",
  "language_code": "ro"
}
-->
# Conversie vorbire în text - Raspberry Pi

În această parte a lecției, vei scrie cod pentru a converti vorbirea din audio-ul capturat în text folosind serviciul de recunoaștere vocală.

## Trimite audio-ul către serviciul de recunoaștere vocală

Audio-ul poate fi trimis către serviciul de recunoaștere vocală utilizând API-ul REST. Pentru a folosi serviciul de recunoaștere vocală, mai întâi trebuie să soliciți un token de acces, apoi să folosești acel token pentru a accesa API-ul REST. Aceste tokenuri de acces expiră după 10 minute, așa că codul tău ar trebui să le solicite în mod regulat pentru a se asigura că sunt mereu actualizate.

### Sarcină - obține un token de acces

1. Deschide proiectul `smart-timer` pe Raspberry Pi-ul tău.

1. Elimină funcția `play_audio`. Aceasta nu mai este necesară, deoarece nu dorești ca timerul inteligent să îți repete ceea ce ai spus.

1. Adaugă următorul import în partea de sus a fișierului `app.py`:

    ```python
    import requests
    ```

1. Adaugă următorul cod deasupra buclei `while True` pentru a declara câteva setări pentru serviciul de recunoaștere vocală:

    ```python
    speech_api_key = '<key>'
    location = '<location>'
    language = '<language>'
    ```

    Înlocuiește `<key>` cu cheia API pentru resursa serviciului de recunoaștere vocală. Înlocuiește `<location>` cu locația pe care ai utilizat-o când ai creat resursa serviciului de recunoaștere vocală.

    Înlocuiește `<language>` cu numele localizării pentru limba în care vei vorbi, de exemplu `en-GB` pentru engleză sau `zn-HK` pentru cantoneză. Poți găsi o listă a limbilor suportate și a numelor lor de localizare în [documentația despre suportul pentru limbă și voce pe Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text).

1. Sub acest cod, adaugă următoarea funcție pentru a obține un token de acces:

    ```python
    def get_access_token():
        headers = {
            'Ocp-Apim-Subscription-Key': speech_api_key
        }
    
        token_endpoint = f'https://{location}.api.cognitive.microsoft.com/sts/v1.0/issuetoken'
        response = requests.post(token_endpoint, headers=headers)
        return str(response.text)
    ```

    Aceasta apelează un endpoint pentru emiterea tokenurilor, trimițând cheia API ca header. Apelul returnează un token de acces care poate fi utilizat pentru a apela serviciile de recunoaștere vocală.

1. Sub acest cod, declară o funcție pentru a converti vorbirea din audio-ul capturat în text folosind API-ul REST:

    ```python
    def convert_speech_to_text(buffer):
    ```

1. În interiorul acestei funcții, configurează URL-ul API-ului REST și headerele:

    ```python
    url = f'https://{location}.stt.speech.microsoft.com/speech/recognition/conversation/cognitiveservices/v1'

    headers = {
        'Authorization': 'Bearer ' + get_access_token(),
        'Content-Type': f'audio/wav; codecs=audio/pcm; samplerate={rate}',
        'Accept': 'application/json;text/xml'
    }

    params = {
        'language': language
    }
    ```

    Acest cod construiește un URL folosind locația resursei serviciilor de recunoaștere vocală. Apoi completează headerele cu tokenul de acces obținut din funcția `get_access_token`, precum și rata de eșantionare utilizată pentru capturarea audio-ului. În final, definește câțiva parametri care vor fi trimiși cu URL-ul, conținând limba audio-ului.

1. Sub acest cod, adaugă următorul cod pentru a apela API-ul REST și a obține textul:

    ```python
    response = requests.post(url, headers=headers, params=params, data=buffer)
    response_json = response.json()

    if response_json['RecognitionStatus'] == 'Success':
        return response_json['DisplayText']
    else:
        return ''
    ```

    Acest cod apelează URL-ul și decodează valoarea JSON care vine în răspuns. Valoarea `RecognitionStatus` din răspuns indică dacă apelul a reușit să extragă vorbirea în text cu succes, iar dacă aceasta este `Success`, textul este returnat din funcție, altfel se returnează un șir gol.

1. Deasupra buclei `while True:`, definește o funcție pentru a procesa textul returnat de serviciul de conversie vorbire în text. Această funcție va afișa textul în consolă pentru moment.

    ```python
    def process_text(text):
        print(text)
    ```

1. În final, înlocuiește apelul către `play_audio` din bucla `while True` cu un apel către funcția `convert_speech_to_text`, trimițând textul către funcția `process_text`:

    ```python
    text = convert_speech_to_text(buffer)
    process_text(text)
    ```

1. Rulează codul. Apasă butonul și vorbește în microfon. Eliberează butonul când ai terminat, iar audio-ul va fi convertit în text și afișat în consolă.

    ```output
    pi@raspberrypi:~/smart-timer $ python3 app.py 
    Hello world.
    Welcome to IoT for beginners.
    ```

    Încearcă diferite tipuri de propoziții, împreună cu propoziții în care cuvintele sună la fel, dar au sensuri diferite. De exemplu, dacă vorbești în engleză, spune „I want to buy two bananas and an apple too” și observă cum va folosi corect „to”, „two” și „too” pe baza contextului cuvântului, nu doar a sunetului său.

> 💁 Poți găsi acest cod în folderul [code-speech-to-text/pi](../../../../../6-consumer/lessons/1-speech-recognition/code-speech-to-text/pi).

😀 Programul tău de conversie vorbire în text a fost un succes!

---

**Declinare de responsabilitate**:  
Acest document a fost tradus folosind serviciul de traducere AI [Co-op Translator](https://github.com/Azure/co-op-translator). Deși ne străduim să asigurăm acuratețea, vă rugăm să fiți conștienți că traducerile automate pot conține erori sau inexactități. Documentul original în limba sa natală ar trebui considerat sursa autoritară. Pentru informații critice, se recomandă traducerea profesională realizată de un specialist uman. Nu ne asumăm responsabilitatea pentru eventualele neînțelegeri sau interpretări greșite care pot apărea din utilizarea acestei traduceri.