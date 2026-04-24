# Ta et bilde - Virtuell IoT-maskinvare

I denne delen av leksjonen skal du legge til en kamerasensor til din virtuelle IoT-enhet og lese bilder fra den.

## Maskinvare

Den virtuelle IoT-enheten vil bruke et simulert kamera som sender bilder enten fra filer eller fra webkameraet ditt.

### Legg til kameraet i CounterFit

For å bruke et virtuelt kamera, må du legge til ett i CounterFit-appen.

#### Oppgave - legg til kameraet i CounterFit

Legg til kameraet i CounterFit-appen.

1. Opprett en ny Python-app på datamaskinen din i en mappe kalt `fruit-quality-detector` med en enkelt fil kalt `app.py` og et Python-virtuelt miljø, og legg til CounterFit pip-pakkene.

    > ⚠️ Du kan se [instruksjonene for å opprette og sette opp et CounterFit Python-prosjekt i leksjon 1 hvis nødvendig](../../../1-getting-started/lessons/1-introduction-to-iot/virtual-device.md).

1. Installer en ekstra Pip-pakke for å installere en CounterFit shim som kan kommunisere med kamerasensorer ved å simulere noe av [Picamera Pip-pakken](https://pypi.org/project/picamera/). Sørg for at du installerer dette fra en terminal med det virtuelle miljøet aktivert.

    ```sh
    pip install counterfit-shims-picamera
    ```

1. Sørg for at CounterFit-nettappen kjører.

1. Opprett et kamera:

    1. I boksen *Create sensor* i *Sensors*-panelet, åpne rullegardinmenyen *Sensor type* og velg *Camera*.

    1. Sett *Name* til `Picamera`.

    1. Velg **Add**-knappen for å opprette kameraet.

    ![Kameraoppsett](../../../../../translated_images/no/counterfit-create-camera.a5de97f59c0bd3cb.webp)

    Kameraet vil bli opprettet og vises i sensorlisten.

    ![Kamera opprettet](../../../../../translated_images/no/counterfit-camera.001ec52194c8ee5d.webp)

## Programmer kameraet

Den virtuelle IoT-enheten kan nå programmeres til å bruke det virtuelle kameraet.

### Oppgave - programmer kameraet

Programmer enheten.

1. Sørg for at `fruit-quality-detector`-appen er åpen i VS Code.

1. Åpne filen `app.py`.

1. Legg til følgende kode øverst i `app.py` for å koble appen til CounterFit:

    ```python
    from counterfit_connection import CounterFitConnection
    CounterFitConnection.init('127.0.0.1', 5000)
    ```

1. Legg til følgende kode i `app.py`-filen din:

    ```python
    import io
    from counterfit_shims_picamera import PiCamera
    ```

    Denne koden importerer noen nødvendige biblioteker, inkludert `PiCamera`-klassen fra counterfit_shims_picamera-biblioteket.

1. Legg til følgende kode under dette for å initialisere kameraet:

    ```python
    camera = PiCamera()
    camera.resolution = (640, 480)
    camera.rotation = 0
    ```

    Denne koden oppretter et PiCamera-objekt og setter oppløsningen til 640x480. Selv om høyere oppløsninger støttes, fungerer bildegjenkjenneren med mye mindre bilder (227x227), så det er ikke nødvendig å ta og sende større bilder.

    Linjen `camera.rotation = 0` setter rotasjonen av bildet i grader. Hvis du trenger å rotere bildet fra webkameraet eller filen, kan du justere dette etter behov. For eksempel, hvis du vil endre bildet av en banan på et webkamera i liggende modus til stående, sett `camera.rotation = 90`.

1. Legg til følgende kode under dette for å fange bildet som binære data:

    ```python
    image = io.BytesIO()
    camera.capture(image, 'jpeg')
    image.seek(0)
    ```

    Denne koden oppretter et `BytesIO`-objekt for å lagre binære data. Bildet leses fra kameraet som en JPEG-fil og lagres i dette objektet. Dette objektet har en posisjonsindikator for å vite hvor det er i dataene slik at mer data kan skrives til slutten om nødvendig, så linjen `image.seek(0)` flytter denne posisjonen tilbake til starten slik at alle dataene kan leses senere.

1. Under dette, legg til følgende for å lagre bildet til en fil:

    ```python
    with open('image.jpg', 'wb') as image_file:
        image_file.write(image.read())
    ```

    Denne koden åpner en fil kalt `image.jpg` for skriving, deretter leser den alle dataene fra `BytesIO`-objektet og skriver dem til filen.

    > 💁 Du kan fange bildet direkte til en fil i stedet for et `BytesIO`-objekt ved å sende filnavnet til `camera.capture`-kallet. Grunnen til å bruke `BytesIO`-objektet er at du senere i denne leksjonen kan sende bildet til bildegjenkjenneren din.

1. Konfigurer bildet som kameraet i CounterFit vil fange. Du kan enten sette *Source* til *File*, deretter laste opp en bildefil, eller sette *Source* til *WebCam*, og bilder vil bli tatt fra webkameraet ditt. Sørg for at du velger **Set**-knappen etter å ha valgt et bilde eller webkameraet ditt.

    ![CounterFit med en fil satt som bildekilde, og et webkamera som viser en person som holder en banan i en forhåndsvisning av webkameraet](../../../../../translated_images/no/counterfit-camera-options.eb3bd5150a8e7dff.webp)

1. Et bilde vil bli tatt og lagret som `image.jpg` i den gjeldende mappen. Du vil se denne filen i VS Code-utforskeren. Velg filen for å se bildet. Hvis det trenger rotasjon, oppdater linjen `camera.rotation = 0` etter behov og ta et nytt bilde.

> 💁 Du finner denne koden i [code-camera/virtual-iot-device](../../../../../4-manufacturing/lessons/2-check-fruit-from-device/code-camera/virtual-iot-device)-mappen.

😀 Kameraet ditt ble programmert med suksess!

---

**Ansvarsfraskrivelse**:  
Dette dokumentet er oversatt ved hjelp av AI-oversettelsestjenesten [Co-op Translator](https://github.com/Azure/co-op-translator). Selv om vi streber etter nøyaktighet, vær oppmerksom på at automatiske oversettelser kan inneholde feil eller unøyaktigheter. Det originale dokumentet på sitt opprinnelige språk bør anses som den autoritative kilden. For kritisk informasjon anbefales profesjonell menneskelig oversettelse. Vi er ikke ansvarlige for misforståelser eller feiltolkninger som oppstår ved bruk av denne oversettelsen.