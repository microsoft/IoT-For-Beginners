<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "3ba7150ffc4a6999f6c3cfb4906ec7df",
  "translation_date": "2025-08-27T20:43:00+00:00",
  "source_file": "4-manufacturing/lessons/2-check-fruit-from-device/virtual-device-camera.md",
  "language_code": "da"
}
-->
# Tag et billede - Virtuel IoT-hardware

I denne del af lektionen vil du tilføje en kamerasensor til din virtuelle IoT-enhed og læse billeder fra den.

## Hardware

Den virtuelle IoT-enhed vil bruge et simuleret kamera, der sender enten billeder fra filer eller fra dit webcam.

### Tilføj kameraet til CounterFit

For at bruge et virtuelt kamera skal du tilføje et til CounterFit-appen.

#### Opgave - tilføj kameraet til CounterFit

Tilføj kameraet til CounterFit-appen.

1. Opret en ny Python-app på din computer i en mappe kaldet `fruit-quality-detector` med en enkelt fil kaldet `app.py` og et Python-virtuelt miljø, og tilføj CounterFit pip-pakkerne.

    > ⚠️ Du kan finde [instruktionerne til oprettelse og opsætning af et CounterFit Python-projekt i lektion 1, hvis nødvendigt](../../../1-getting-started/lessons/1-introduction-to-iot/virtual-device.md).

1. Installer en ekstra Pip-pakke for at installere en CounterFit shim, der kan kommunikere med kamerasensorer ved at simulere nogle af [Picamera Pip-pakken](https://pypi.org/project/picamera/). Sørg for, at du installerer dette fra en terminal med det virtuelle miljø aktiveret.

    ```sh
    pip install counterfit-shims-picamera
    ```

1. Sørg for, at CounterFit-webappen kører.

1. Opret et kamera:

    1. I *Create sensor*-boksen i *Sensors*-panelet skal du vælge *Sensor type*-boksen og vælge *Camera*.

    1. Sæt *Name* til `Picamera`.

    1. Vælg knappen **Add** for at oprette kameraet.

    ![Kameraindstillingerne](../../../../../translated_images/da/counterfit-create-camera.a5de97f59c0bd3cbe0416d7e89a3cfe86d19fbae05c641c53a91286412af0a34.png)

    Kameraet vil blive oprettet og vises i sensorlisten.

    ![Kameraet oprettet](../../../../../translated_images/da/counterfit-camera.001ec52194c8ee5d3f617173da2c79e1df903d10882adc625cbfc493525125d4.png)

## Programmer kameraet

Den virtuelle IoT-enhed kan nu programmeres til at bruge det virtuelle kamera.

### Opgave - programmer kameraet

Programmer enheden.

1. Sørg for, at `fruit-quality-detector`-appen er åben i VS Code.

1. Åbn filen `app.py`.

1. Tilføj følgende kode øverst i `app.py` for at forbinde appen til CounterFit:

    ```python
    from counterfit_connection import CounterFitConnection
    CounterFitConnection.init('127.0.0.1', 5000)
    ```

1. Tilføj følgende kode til din `app.py`-fil:

    ```python
    import io
    from counterfit_shims_picamera import PiCamera
    ```

    Denne kode importerer nogle nødvendige biblioteker, inklusive klassen `PiCamera` fra biblioteket counterfit_shims_picamera.

1. Tilføj følgende kode nedenunder for at initialisere kameraet:

    ```python
    camera = PiCamera()
    camera.resolution = (640, 480)
    camera.rotation = 0
    ```

    Denne kode opretter et PiCamera-objekt og sætter opløsningen til 640x480. Selvom højere opløsninger understøttes, arbejder billedklassificeringen med meget mindre billeder (227x227), så der er ingen grund til at fange og sende større billeder.

    Linjen `camera.rotation = 0` angiver rotationen af billedet i grader. Hvis du har brug for at rotere billedet fra webcam eller filen, skal du indstille dette som passende. For eksempel, hvis du vil ændre billedet af en banan på et webcam i landskabsformat til portrætformat, skal du sætte `camera.rotation = 90`.

1. Tilføj følgende kode nedenunder for at fange billedet som binære data:

    ```python
    image = io.BytesIO()
    camera.capture(image, 'jpeg')
    image.seek(0)
    ```

    Denne kode opretter et `BytesIO`-objekt til at gemme binære data. Billedet læses fra kameraet som en JPEG-fil og gemmes i dette objekt. Dette objekt har en positionsindikator for at vide, hvor det er i dataene, så der kan skrives mere data til slutningen, hvis nødvendigt. Linjen `image.seek(0)` flytter denne position tilbage til starten, så alle data kan læses senere.

1. Tilføj nedenunder følgende for at gemme billedet i en fil:

    ```python
    with open('image.jpg', 'wb') as image_file:
        image_file.write(image.read())
    ```

    Denne kode åbner en fil kaldet `image.jpg` til skrivning, læser derefter alle data fra `BytesIO`-objektet og skriver dem til filen.

    > 💁 Du kan fange billedet direkte til en fil i stedet for et `BytesIO`-objekt ved at angive filnavnet til `camera.capture`-kaldet. Årsagen til at bruge `BytesIO`-objektet er, at du senere i denne lektion kan sende billedet til din billedklassificering.

1. Konfigurer billedet, som kameraet i CounterFit vil fange. Du kan enten sætte *Source* til *File* og derefter uploade en billedfil, eller sætte *Source* til *WebCam*, og billeder vil blive fanget fra dit webcam. Sørg for at vælge knappen **Set** efter at have valgt et billede eller dit webcam.

    ![CounterFit med en fil sat som billedkilde og et webcam, der viser en person, der holder en banan i en forhåndsvisning af webcammet](../../../../../translated_images/da/counterfit-camera-options.eb3bd5150a8e7dffbf24bc5bcaba0cf2cdef95fbe6bbe393695d173817d6b8df.png)

1. Et billede vil blive fanget og gemt som `image.jpg` i den aktuelle mappe. Du vil se denne fil i VS Code-udforskeren. Vælg filen for at se billedet. Hvis det skal roteres, opdater linjen `camera.rotation = 0` som nødvendigt og tag et nyt billede.

> 💁 Du kan finde denne kode i mappen [code-camera/virtual-iot-device](../../../../../4-manufacturing/lessons/2-check-fruit-from-device/code-camera/virtual-iot-device).

😀 Dit kameraprogram var en succes!

---

**Ansvarsfraskrivelse**:  
Dette dokument er blevet oversat ved hjælp af AI-oversættelsestjenesten [Co-op Translator](https://github.com/Azure/co-op-translator). Selvom vi bestræber os på nøjagtighed, skal du være opmærksom på, at automatiserede oversættelser kan indeholde fejl eller unøjagtigheder. Det originale dokument på dets oprindelige sprog bør betragtes som den autoritative kilde. For kritisk information anbefales professionel menneskelig oversættelse. Vi påtager os intet ansvar for misforståelser eller fejltolkninger, der måtte opstå som følge af brugen af denne oversættelse.