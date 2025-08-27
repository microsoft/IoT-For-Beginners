<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "af249a24d4fe4f4de4806adbc3bc9d86",
  "translation_date": "2025-08-27T21:08:14+00:00",
  "source_file": "6-consumer/lessons/1-speech-recognition/pi-speech-to-text.md",
  "language_code": "no"
}
-->
# Tale til tekst - Raspberry Pi

I denne delen av leksjonen skal du skrive kode for å konvertere tale i det innspilte lydopptaket til tekst ved hjelp av tale-tjenesten.

## Send lyden til tale-tjenesten

Lyden kan sendes til tale-tjenesten ved hjelp av REST API. For å bruke tale-tjenesten må du først be om en tilgangstoken, og deretter bruke denne tokenen for å få tilgang til REST API. Disse tilgangstokenene utløper etter 10 minutter, så koden din bør be om dem regelmessig for å sikre at de alltid er oppdaterte.

### Oppgave - få en tilgangstoken

1. Åpne `smart-timer`-prosjektet på din Pi.

1. Fjern funksjonen `play_audio`. Denne er ikke lenger nødvendig siden du ikke ønsker at smart-timeren skal gjenta det du sa.

1. Legg til følgende import øverst i filen `app.py`:

    ```python
    import requests
    ```

1. Legg til følgende kode over `while True`-løkken for å deklarere noen innstillinger for tale-tjenesten:

    ```python
    speech_api_key = '<key>'
    location = '<location>'
    language = '<language>'
    ```

    Erstatt `<key>` med API-nøkkelen for ressursen din i tale-tjenesten. Erstatt `<location>` med plasseringen du brukte da du opprettet ressursen i tale-tjenesten.

    Erstatt `<language>` med lokalitetsnavnet for språket du skal snakke på, for eksempel `en-GB` for engelsk eller `zn-HK` for kantonesisk. Du finner en liste over støttede språk og deres lokalitetsnavn i [dokumentasjonen for språk- og stemmestøtte på Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text).

1. Under dette, legg til følgende funksjon for å få en tilgangstoken:

    ```python
    def get_access_token():
        headers = {
            'Ocp-Apim-Subscription-Key': speech_api_key
        }
    
        token_endpoint = f'https://{location}.api.cognitive.microsoft.com/sts/v1.0/issuetoken'
        response = requests.post(token_endpoint, headers=headers)
        return str(response.text)
    ```

    Denne kaller et token-utstedelsesendepunkt og sender API-nøkkelen som en header. Kallet returnerer en tilgangstoken som kan brukes til å kalle tale-tjenestene.

1. Under dette, deklarer en funksjon for å konvertere tale i det innspilte lydopptaket til tekst ved hjelp av REST API:

    ```python
    def convert_speech_to_text(buffer):
    ```

1. Inne i denne funksjonen, sett opp REST API-URL-en og headere:

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

    Dette bygger en URL ved å bruke plasseringen til ressursen i tale-tjenesten. Deretter fyller den inn headerne med tilgangstokenen fra funksjonen `get_access_token`, samt samplingsfrekvensen som ble brukt til å ta opp lyden. Til slutt definerer den noen parametere som skal sendes med URL-en og som inneholder språket i lyden.

1. Under dette, legg til følgende kode for å kalle REST API og få tilbake teksten:

    ```python
    response = requests.post(url, headers=headers, params=params, data=buffer)
    response_json = response.json()

    if response_json['RecognitionStatus'] == 'Success':
        return response_json['DisplayText']
    else:
        return ''
    ```

    Denne kaller URL-en og dekoder JSON-verdien som kommer i responsen. Verdien `RecognitionStatus` i responsen indikerer om kallet klarte å trekke ut tale til tekst vellykket, og hvis denne er `Success`, returneres teksten fra funksjonen. Ellers returneres en tom streng.

1. Over `while True:`-løkken, definer en funksjon for å behandle teksten som returneres fra tale-til-tekst-tjenesten. Denne funksjonen vil bare skrive ut teksten til konsollen foreløpig.

    ```python
    def process_text(text):
        print(text)
    ```

1. Til slutt, erstatt kallet til `play_audio` i `while True`-løkken med et kall til funksjonen `convert_speech_to_text`, og send teksten til funksjonen `process_text`:

    ```python
    text = convert_speech_to_text(buffer)
    process_text(text)
    ```

1. Kjør koden. Trykk på knappen og snakk inn i mikrofonen. Slipp knappen når du er ferdig, og lyden vil bli konvertert til tekst og skrevet ut i konsollen.

    ```output
    pi@raspberrypi:~/smart-timer $ python3 app.py 
    Hello world.
    Welcome to IoT for beginners.
    ```

    Prøv forskjellige typer setninger, samt setninger der ord høres like ut, men har forskjellige betydninger. For eksempel, hvis du snakker engelsk, si "I want to buy two bananas and an apple too", og legg merke til hvordan den bruker riktig "to", "two" og "too" basert på konteksten til ordet, ikke bare lyden.

> 💁 Du finner denne koden i [code-speech-to-text/pi](../../../../../6-consumer/lessons/1-speech-recognition/code-speech-to-text/pi)-mappen.

😀 Programmet ditt for tale til tekst var en suksess!

---

**Ansvarsfraskrivelse**:  
Dette dokumentet er oversatt ved hjelp av AI-oversettelsestjenesten [Co-op Translator](https://github.com/Azure/co-op-translator). Selv om vi streber etter nøyaktighet, vær oppmerksom på at automatiske oversettelser kan inneholde feil eller unøyaktigheter. Det originale dokumentet på sitt opprinnelige språk bør anses som den autoritative kilden. For kritisk informasjon anbefales profesjonell menneskelig oversettelse. Vi er ikke ansvarlige for misforståelser eller feiltolkninger som oppstår ved bruk av denne oversettelsen.