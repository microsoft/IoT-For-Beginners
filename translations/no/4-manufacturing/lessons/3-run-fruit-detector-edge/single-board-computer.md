<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "50151d9f9dce2801348a93880ef16d86",
  "translation_date": "2025-08-27T20:39:20+00:00",
  "source_file": "4-manufacturing/lessons/3-run-fruit-detector-edge/single-board-computer.md",
  "language_code": "no"
}
-->
# Klassifiser et bilde ved hjelp av en IoT Edge-basert bildekategoriserer - Virtuell IoT-maskinvare og Raspberry Pi

I denne delen av leksjonen skal du bruke bildekategorisereren som kjører på IoT Edge-enheten.

## Bruk IoT Edge-kategorisereren

IoT-enheten kan omdirigeres til å bruke bildekategorisereren på IoT Edge. URL-en for bildekategorisereren er `http://<IP-adresse eller navn>/image`, der `<IP-adresse eller navn>` erstattes med IP-adressen eller vertsnavnet til datamaskinen som kjører IoT Edge.

Python-biblioteket for Custom Vision fungerer kun med modeller som er vert på skyen, ikke med modeller som er vert på IoT Edge. Dette betyr at du må bruke REST API for å kalle kategorisereren.

### Oppgave - bruk IoT Edge-kategorisereren

1. Åpne prosjektet `fruit-quality-detector` i VS Code hvis det ikke allerede er åpent. Hvis du bruker en virtuell IoT-enhet, må du sørge for at det virtuelle miljøet er aktivert.

1. Åpne filen `app.py`, og fjern importsetningene fra `azure.cognitiveservices.vision.customvision.prediction` og `msrest.authentication`.

1. Legg til følgende import øverst i filen:

    ```python
    import requests
    ```

1. Slett all kode etter at bildet er lagret i en fil, fra `image_file.write(image.read())` til slutten av filen.

1. Legg til følgende kode på slutten av filen:

    ```python
    prediction_url = '<URL>'
    headers = {
        'Content-Type' : 'application/octet-stream'
    }
    image.seek(0)
    response = requests.post(prediction_url, headers=headers, data=image)
    results = response.json()
    
    for prediction in results['predictions']:
        print(f'{prediction["tagName"]}:\t{prediction["probability"] * 100:.2f}%')
    ```

    Erstatt `<URL>` med URL-en til din kategoriserer.

    Denne koden gjør en REST POST-forespørsel til kategorisereren, og sender bildet som innholdet i forespørselen. Resultatene kommer tilbake som JSON, og dette dekodes for å skrive ut sannsynlighetene.

1. Kjør koden din, med kameraet ditt rettet mot noe frukt, eller et passende bildesett, eller frukt synlig på webkameraet ditt hvis du bruker virtuell IoT-maskinvare. Du vil se resultatet i konsollen:

    ```output
    (.venv) ➜  fruit-quality-detector python app.py
    ripe:   56.84%
    unripe: 43.16%
    ```

> 💁 Du finner denne koden i mappen [code-classify/pi](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge/code-classify/pi) eller [code-classify/virtual-iot-device](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge/code-classify/virtual-iot-device).

😀 Programmet ditt for klassifisering av fruktkvalitet var en suksess!

---

**Ansvarsfraskrivelse**:  
Dette dokumentet er oversatt ved hjelp av AI-oversettelsestjenesten [Co-op Translator](https://github.com/Azure/co-op-translator). Selv om vi streber etter nøyaktighet, vær oppmerksom på at automatiserte oversettelser kan inneholde feil eller unøyaktigheter. Det originale dokumentet på sitt opprinnelige språk bør anses som den autoritative kilden. For kritisk informasjon anbefales profesjonell menneskelig oversettelse. Vi er ikke ansvarlige for misforståelser eller feiltolkninger som oppstår ved bruk av denne oversettelsen.