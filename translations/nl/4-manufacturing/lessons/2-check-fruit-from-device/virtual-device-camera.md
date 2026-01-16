<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "3ba7150ffc4a6999f6c3cfb4906ec7df",
  "translation_date": "2025-08-27T20:44:05+00:00",
  "source_file": "4-manufacturing/lessons/2-check-fruit-from-device/virtual-device-camera.md",
  "language_code": "nl"
}
-->
# Maak een foto - Virtuele IoT-hardware

In dit deel van de les voeg je een camerasensor toe aan je virtuele IoT-apparaat en lees je afbeeldingen ervan uit.

## Hardware

Het virtuele IoT-apparaat gebruikt een gesimuleerde camera die afbeeldingen verzendt vanuit bestanden of vanaf je webcam.

### Voeg de camera toe aan CounterFit

Om een virtuele camera te gebruiken, moet je er een toevoegen aan de CounterFit-app.

#### Taak - voeg de camera toe aan CounterFit

Voeg de camera toe aan de CounterFit-app.

1. Maak een nieuwe Python-app op je computer in een map genaamd `fruit-quality-detector` met een enkel bestand genaamd `app.py` en een Python-virtuele omgeving, en voeg de CounterFit pip-pakketten toe.

    > ⚠️ Je kunt [de instructies voor het maken en instellen van een CounterFit Python-project in les 1 raadplegen indien nodig](../../../1-getting-started/lessons/1-introduction-to-iot/virtual-device.md).

1. Installeer een extra Pip-pakket om een CounterFit shim te installeren die kan communiceren met camerasensoren door enkele functies van het [Picamera Pip-pakket](https://pypi.org/project/picamera/) te simuleren. Zorg ervoor dat je dit installeert vanuit een terminal met de virtuele omgeving geactiveerd.

    ```sh
    pip install counterfit-shims-picamera
    ```

1. Zorg ervoor dat de CounterFit-webapp actief is.

1. Maak een camera aan:

    1. In het *Create sensor*-vak in het *Sensors*-paneel, open het dropdownmenu *Sensor type* en selecteer *Camera*.

    1. Stel de *Name* in op `Picamera`.

    1. Selecteer de knop **Add** om de camera aan te maken.

    ![De camera-instellingen](../../../../../translated_images/nl/counterfit-create-camera.a5de97f59c0bd3cbe0416d7e89a3cfe86d19fbae05c641c53a91286412af0a34.png)

    De camera wordt aangemaakt en verschijnt in de sensorenlijst.

    ![De aangemaakte camera](../../../../../translated_images/nl/counterfit-camera.001ec52194c8ee5d3f617173da2c79e1df903d10882adc625cbfc493525125d4.png)

## Programmeer de camera

Het virtuele IoT-apparaat kan nu worden geprogrammeerd om de virtuele camera te gebruiken.

### Taak - programmeer de camera

Programmeur het apparaat.

1. Zorg ervoor dat de `fruit-quality-detector`-app geopend is in VS Code.

1. Open het bestand `app.py`.

1. Voeg de volgende code toe aan het begin van `app.py` om de app te verbinden met CounterFit:

    ```python
    from counterfit_connection import CounterFitConnection
    CounterFitConnection.init('127.0.0.1', 5000)
    ```

1. Voeg de volgende code toe aan je `app.py`-bestand:

    ```python
    import io
    from counterfit_shims_picamera import PiCamera
    ```

    Deze code importeert enkele benodigde bibliotheken, waaronder de `PiCamera`-klasse uit de counterfit_shims_picamera-bibliotheek.

1. Voeg de volgende code hieronder toe om de camera te initialiseren:

    ```python
    camera = PiCamera()
    camera.resolution = (640, 480)
    camera.rotation = 0
    ```

    Deze code maakt een PiCamera-object aan en stelt de resolutie in op 640x480. Hoewel hogere resoluties worden ondersteund, werkt de beeldclassificator met veel kleinere afbeeldingen (227x227), dus het is niet nodig om grotere afbeeldingen vast te leggen en te verzenden.

    De regel `camera.rotation = 0` stelt de rotatie van de afbeelding in graden in. Als je de afbeelding van de webcam of het bestand moet draaien, stel dit dan dienovereenkomstig in. Bijvoorbeeld, als je een afbeelding van een banaan op een webcam in liggende modus wilt veranderen naar staande modus, stel dan `camera.rotation = 90` in.

1. Voeg de volgende code hieronder toe om de afbeelding vast te leggen als binaire gegevens:

    ```python
    image = io.BytesIO()
    camera.capture(image, 'jpeg')
    image.seek(0)
    ```

    Deze code maakt een `BytesIO`-object aan om binaire gegevens op te slaan. De afbeelding wordt gelezen van de camera als een JPEG-bestand en opgeslagen in dit object. Dit object heeft een positie-indicator om te weten waar het zich in de gegevens bevindt, zodat er indien nodig meer gegevens aan het einde kunnen worden toegevoegd. De regel `image.seek(0)` verplaatst deze positie terug naar het begin, zodat alle gegevens later kunnen worden gelezen.

1. Voeg hieronder het volgende toe om de afbeelding op te slaan in een bestand:

    ```python
    with open('image.jpg', 'wb') as image_file:
        image_file.write(image.read())
    ```

    Deze code opent een bestand genaamd `image.jpg` om te schrijven, leest vervolgens alle gegevens uit het `BytesIO`-object en schrijft deze naar het bestand.

    > 💁 Je kunt de afbeelding direct vastleggen in een bestand in plaats van in een `BytesIO`-object door de bestandsnaam door te geven aan de `camera.capture`-aanroep. De reden om het `BytesIO`-object te gebruiken is zodat je later in deze les de afbeelding naar je beeldclassificator kunt sturen.

1. Stel de afbeelding in die de camera in CounterFit zal vastleggen. Je kunt de *Source* instellen op *File* en vervolgens een afbeeldingsbestand uploaden, of de *Source* instellen op *WebCam*, waarna afbeeldingen worden vastgelegd vanaf je webcam. Zorg ervoor dat je op de knop **Set** klikt nadat je een afbeelding hebt geselecteerd of je webcam hebt ingesteld.

    ![CounterFit met een bestand ingesteld als afbeeldingsbron en een webcam ingesteld die een persoon toont die een banaan vasthoudt in een voorbeeldweergave van de webcam](../../../../../translated_images/nl/counterfit-camera-options.eb3bd5150a8e7dffbf24bc5bcaba0cf2cdef95fbe6bbe393695d173817d6b8df.png)

1. Een afbeelding wordt vastgelegd en opgeslagen als `image.jpg` in de huidige map. Je ziet dit bestand in de VS Code-verkenner. Selecteer het bestand om de afbeelding te bekijken. Als het moet worden gedraaid, pas dan de regel `camera.rotation = 0` aan en maak opnieuw een foto.

> 💁 Je kunt deze code vinden in de map [code-camera/virtual-iot-device](../../../../../4-manufacturing/lessons/2-check-fruit-from-device/code-camera/virtual-iot-device).

😀 Je camera-programma is een succes!

---

**Disclaimer**:  
Dit document is vertaald met behulp van de AI-vertalingsservice [Co-op Translator](https://github.com/Azure/co-op-translator). Hoewel we streven naar nauwkeurigheid, dient u zich ervan bewust te zijn dat geautomatiseerde vertalingen fouten of onnauwkeurigheden kunnen bevatten. Het originele document in zijn oorspronkelijke taal moet worden beschouwd als de gezaghebbende bron. Voor cruciale informatie wordt professionele menselijke vertaling aanbevolen. Wij zijn niet aansprakelijk voor eventuele misverstanden of verkeerde interpretaties die voortvloeien uit het gebruik van deze vertaling.