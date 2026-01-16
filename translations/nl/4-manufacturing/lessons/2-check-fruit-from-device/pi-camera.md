<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "c677667095f6133eee418c7e53615d05",
  "translation_date": "2025-08-27T20:41:17+00:00",
  "source_file": "4-manufacturing/lessons/2-check-fruit-from-device/pi-camera.md",
  "language_code": "nl"
}
-->
# Een afbeelding vastleggen - Raspberry Pi

In dit deel van de les voeg je een camerasensor toe aan je Raspberry Pi en lees je afbeeldingen ervan uit.

## Hardware

De Raspberry Pi heeft een camera nodig.

De camera die je gaat gebruiken is een [Raspberry Pi Camera Module](https://www.raspberrypi.org/products/camera-module-v2/). Deze camera is ontworpen om met de Raspberry Pi te werken en wordt aangesloten via een speciale connector op de Pi.

> 💁 Deze camera maakt gebruik van de [Camera Serial Interface, een protocol van de Mobile Industry Processor Interface Alliance](https://wikipedia.org/wiki/Camera_Serial_Interface), bekend als MIPI-CSI. Dit is een speciaal protocol voor het verzenden van afbeeldingen.

## Sluit de camera aan

De camera kan met een lintkabel op de Raspberry Pi worden aangesloten.

### Taak - sluit de camera aan

![Een Raspberry Pi Camera](../../../../../translated_images/nl/pi-camera-module.4278753c31bd6e757aa2b858be97d72049f71616278cefe4fb5abb485b40a078.png)

1. Zet de Pi uit.

1. Sluit de lintkabel die bij de camera wordt geleverd aan op de camera. Trek hiervoor voorzichtig aan het zwarte plastic clipje in de houder zodat het een beetje loskomt, schuif vervolgens de kabel in de aansluiting met de blauwe zijde van de kabel van de lens af gericht en de metalen pinnen naar de lens gericht. Zodra de kabel volledig is ingevoerd, duw je het zwarte plastic clipje weer terug op zijn plaats.

    Je kunt een animatie bekijken over hoe je de clip opent en de kabel invoert in de [Raspberry Pi Getting Started with the Camera module documentation](https://projects.raspberrypi.org/en/projects/getting-started-with-picamera/2).

    ![De lintkabel ingevoerd in de cameramodule](../../../../../translated_images/nl/pi-camera-ribbon-cable.0bf82acd251611c21ac616f082849413e2b322a261d0e4f8fec344248083b07e.png)

1. Verwijder de Grove Base Hat van de Pi.

1. Leid de lintkabel door de camerasleuf in de Grove Base Hat. Zorg ervoor dat de blauwe zijde van de kabel naar de analoge poorten gericht is, gemarkeerd met **A0**, **A1**, enz.

    ![De lintkabel door de Grove Base Hat geleid](../../../../../translated_images/nl/grove-base-hat-ribbon-cable.501fed202fcf73b11b2b68f6d246189f7d15d3e4423c572ddee79d77b4632b47.png)

1. Steek de lintkabel in de camera-aansluiting op de Pi. Trek opnieuw het zwarte plastic clipje omhoog, steek de kabel in de aansluiting en duw het clipje weer terug. De blauwe zijde van de kabel moet naar de USB- en ethernetpoorten gericht zijn.

    ![De lintkabel aangesloten op de camera-aansluiting van de Pi](../../../../../translated_images/nl/pi-camera-socket-ribbon-cable.a18309920b11800911082ed7aa6fb28e6d9be3a022e4079ff990016cae3fca10.png)

1. Plaats de Grove Base Hat terug.

## Programmeer de camera

De Raspberry Pi kan nu worden geprogrammeerd om de camera te gebruiken met behulp van de [PiCamera](https://pypi.org/project/picamera/) Python-bibliotheek.

### Taak - schakel legacy cameramodus in

Helaas is met de release van Raspberry Pi OS Bullseye de camerasoftware die bij het besturingssysteem werd geleverd veranderd, waardoor PiCamera standaard niet meer werkt. Er wordt gewerkt aan een vervanger, genaamd PiCamera2, maar deze is nog niet klaar voor gebruik.

Voor nu kun je je Pi in de legacy cameramodus zetten om PiCamera te laten werken. De camera-aansluiting is standaard ook uitgeschakeld, maar het inschakelen van de legacy camerasoftware schakelt de aansluiting automatisch in.

1. Zet de Pi aan en wacht tot deze is opgestart.

1. Start VS Code, direct op de Pi of via de Remote SSH-extensie.

1. Voer de volgende opdrachten uit in je terminal:

    ```sh
    sudo raspi-config nonint do_legacy 0
    sudo reboot
    ```

    Hiermee wordt een instelling gewijzigd om de legacy camerasoftware in te schakelen, waarna de Pi opnieuw wordt opgestart om de wijziging door te voeren.

1. Wacht tot de Pi opnieuw is opgestart en start vervolgens VS Code opnieuw.

### Taak - programmeer de camera

Programmeur het apparaat.

1. Maak vanuit de terminal een nieuwe map aan in de thuismap van de gebruiker `pi` genaamd `fruit-quality-detector`. Maak in deze map een bestand aan genaamd `app.py`.

1. Open deze map in VS Code.

1. Om met de camera te communiceren, kun je de PiCamera Python-bibliotheek gebruiken. Installeer het Pip-pakket hiervoor met het volgende commando:

    ```sh
    pip3 install picamera
    ```

1. Voeg de volgende code toe aan je `app.py`-bestand:

    ```python
    import io
    import time
    from picamera import PiCamera
    ```

    Deze code importeert enkele benodigde bibliotheken, waaronder de `PiCamera`-bibliotheek.

1. Voeg de volgende code hieronder toe om de camera te initialiseren:

    ```python
    camera = PiCamera()
    camera.resolution = (640, 480)
    camera.rotation = 0
    
    time.sleep(2)
    ```

    Deze code maakt een PiCamera-object aan en stelt de resolutie in op 640x480. Hoewel hogere resoluties worden ondersteund (tot 3280x2464), werkt de beeldclassificator met veel kleinere afbeeldingen (227x227), dus het is niet nodig om grotere afbeeldingen vast te leggen en te verzenden.

    De regel `camera.rotation = 0` stelt de rotatie van de afbeelding in. De lintkabel komt aan de onderkant van de camera binnen, maar als je de camera hebt gedraaid om deze gemakkelijker te richten op het object dat je wilt classificeren, kun je deze regel aanpassen aan het aantal graden van rotatie.

    ![De camera hangt naar beneden over een frisdrankblikje](../../../../../translated_images/nl/pi-camera-upside-down.5376961ba31459883362124152ad6b823d5ac5fc14e85f317e22903bd681c2b6.png)

    Als je bijvoorbeeld de lintkabel over iets heen hangt zodat deze aan de bovenkant van de camera zit, stel dan de rotatie in op 180:

    ```python
    camera.rotation = 180
    ```

    De camera heeft een paar seconden nodig om op te starten, vandaar de `time.sleep(2)`.

1. Voeg de volgende code hieronder toe om de afbeelding vast te leggen als binaire gegevens:

    ```python
    image = io.BytesIO()
    camera.capture(image, 'jpeg')
    image.seek(0)
    ```

    Deze code maakt een `BytesIO`-object aan om binaire gegevens op te slaan. De afbeelding wordt als een JPEG-bestand van de camera gelezen en in dit object opgeslagen. Dit object heeft een positie-indicator om bij te houden waar het zich in de gegevens bevindt, zodat er indien nodig meer gegevens aan het einde kunnen worden toegevoegd. De regel `image.seek(0)` verplaatst deze positie terug naar het begin, zodat alle gegevens later kunnen worden gelezen.

1. Voeg hieronder de volgende code toe om de afbeelding op te slaan in een bestand:

    ```python
    with open('image.jpg', 'wb') as image_file:
        image_file.write(image.read())
    ```

    Deze code opent een bestand genaamd `image.jpg` om te schrijven, leest vervolgens alle gegevens uit het `BytesIO`-object en schrijft deze naar het bestand.

    > 💁 Je kunt de afbeelding rechtstreeks in een bestand vastleggen in plaats van in een `BytesIO`-object door de bestandsnaam door te geven aan de `camera.capture`-aanroep. De reden om het `BytesIO`-object te gebruiken is zodat je later in deze les de afbeelding naar je beeldclassificator kunt sturen.

1. Richt de camera op iets en voer deze code uit.

1. Een afbeelding wordt vastgelegd en opgeslagen als `image.jpg` in de huidige map. Je ziet dit bestand in de VS Code-verkenner. Selecteer het bestand om de afbeelding te bekijken. Als de afbeelding moet worden gedraaid, pas dan de regel `camera.rotation = 0` aan en maak een nieuwe foto.

> 💁 Je kunt deze code vinden in de [code-camera/pi](../../../../../4-manufacturing/lessons/2-check-fruit-from-device/code-camera/pi) map.

😀 Je cameraprogramma is een succes!

---

**Disclaimer**:  
Dit document is vertaald met behulp van de AI-vertalingsservice [Co-op Translator](https://github.com/Azure/co-op-translator). Hoewel we streven naar nauwkeurigheid, dient u zich ervan bewust te zijn dat geautomatiseerde vertalingen fouten of onnauwkeurigheden kunnen bevatten. Het originele document in zijn oorspronkelijke taal moet worden beschouwd als de gezaghebbende bron. Voor cruciale informatie wordt professionele menselijke vertaling aanbevolen. Wij zijn niet aansprakelijk voor eventuele misverstanden of verkeerde interpretaties die voortvloeien uit het gebruik van deze vertaling.