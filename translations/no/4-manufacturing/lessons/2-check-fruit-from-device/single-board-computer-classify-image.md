# Klassifiser et bilde - Virtuell IoT-maskinvare og Raspberry Pi

I denne delen av leksjonen skal du sende bildet som kameraet har tatt til Custom Vision-tjenesten for å klassifisere det.

## Send bilder til Custom Vision

Custom Vision-tjenesten har et Python SDK som du kan bruke til å klassifisere bilder.

### Oppgave - send bilder til Custom Vision

1. Åpne mappen `fruit-quality-detector` i VS Code. Hvis du bruker en virtuell IoT-enhet, sørg for at det virtuelle miljøet kjører i terminalen.

1. Python SDK-en for å sende bilder til Custom Vision er tilgjengelig som en Pip-pakke. Installer den med følgende kommando:

    ```sh
    pip3 install azure-cognitiveservices-vision-customvision
    ```

1. Legg til følgende import-setninger øverst i filen `app.py`:

    ```python
    from msrest.authentication import ApiKeyCredentials
    from azure.cognitiveservices.vision.customvision.prediction import CustomVisionPredictionClient
    ```

    Dette importerer noen moduler fra Custom Vision-bibliotekene, én for å autentisere med prediksjonsnøkkelen, og én for å tilby en prediksjonsklientklasse som kan kalle Custom Vision.

1. Legg til følgende kode på slutten av filen:

    ```python
    prediction_url = '<prediction_url>'
    prediction_key = '<prediction key>'
    ```

    Erstatt `<prediction_url>` med URL-en du kopierte fra *Prediction URL*-dialogen tidligere i denne leksjonen. Erstatt `<prediction key>` med prediksjonsnøkkelen du kopierte fra samme dialog.

1. Prediksjons-URL-en som ble gitt av *Prediction URL*-dialogen er designet for å brukes når du kaller REST-endepunktet direkte. Python SDK-en bruker deler av URL-en på forskjellige steder. Legg til følgende kode for å dele opp denne URL-en i de nødvendige delene:

    ```python
    parts = prediction_url.split('/')
    endpoint = 'https://' + parts[2]
    project_id = parts[6]
    iteration_name = parts[9]
    ```

    Dette deler opp URL-en og trekker ut endepunktet `https://<location>.api.cognitive.microsoft.com`, prosjekt-ID-en og navnet på den publiserte iterasjonen.

1. Opprett et prediktorobjekt for å utføre prediksjonen med følgende kode:

    ```python
    prediction_credentials = ApiKeyCredentials(in_headers={"Prediction-key": prediction_key})
    predictor = CustomVisionPredictionClient(endpoint, prediction_credentials)
    ```

    `prediction_credentials` pakker inn prediksjonsnøkkelen. Disse brukes deretter til å opprette et prediksjonsklientobjekt som peker på endepunktet.

1. Send bildet til Custom Vision ved hjelp av følgende kode:

    ```python
    image.seek(0)
    results = predictor.classify_image(project_id, iteration_name, image)
    ```

    Dette spoler bildet tilbake til starten, og sender det deretter til prediksjonsklienten.

1. Til slutt, vis resultatene med følgende kode:

    ```python
    for prediction in results.predictions:
        print(f'{prediction.tag_name}:\t{prediction.probability * 100:.2f}%')
    ```

    Dette vil gå gjennom alle prediksjonene som er returnert og vise dem i terminalen. Sannsynlighetene som returneres er flyttall fra 0-1, der 0 er 0 % sjanse for å matche taggen, og 1 er 100 % sjanse.

    > 💁 Bildeklassifiserere vil returnere prosentene for alle tagger som har blitt brukt. Hver tag vil ha en sannsynlighet for at bildet matcher den taggen.

1. Kjør koden din, med kameraet rettet mot noe frukt, et passende bildesett, eller frukt synlig på webkameraet ditt hvis du bruker virtuell IoT-maskinvare. Du vil se utdataene i konsollen:

    ```output
    (.venv) ➜  fruit-quality-detector python app.py
    ripe:   56.84%
    unripe: 43.16%
    ```

    Du vil kunne se bildet som ble tatt, og disse verdiene i **Predictions**-fanen i Custom Vision.

    ![En banan i Custom Vision forutsagt som moden med 56,8 % og umoden med 43,1 %](../../../../../translated_images/no/custom-vision-banana-prediction.30cdff4e1d72db5d.webp)

> 💁 Du finner denne koden i mappen [code-classify/pi](../../../../../4-manufacturing/lessons/2-check-fruit-from-device/code-classify/pi) eller [code-classify/virtual-iot-device](../../../../../4-manufacturing/lessons/2-check-fruit-from-device/code-classify/virtual-iot-device).

😀 Programmet ditt for å klassifisere fruktkvalitet var en suksess!

---

**Ansvarsfraskrivelse**:  
Dette dokumentet er oversatt ved hjelp av AI-oversettelsestjenesten [Co-op Translator](https://github.com/Azure/co-op-translator). Selv om vi streber etter nøyaktighet, vær oppmerksom på at automatiserte oversettelser kan inneholde feil eller unøyaktigheter. Det originale dokumentet på sitt opprinnelige språk bør anses som den autoritative kilden. For kritisk informasjon anbefales profesjonell menneskelig oversettelse. Vi er ikke ansvarlige for misforståelser eller feiltolkninger som oppstår ved bruk av denne oversettelsen.