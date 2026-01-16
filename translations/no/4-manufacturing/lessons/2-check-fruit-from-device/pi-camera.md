<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "c677667095f6133eee418c7e53615d05",
  "translation_date": "2025-08-27T20:42:23+00:00",
  "source_file": "4-manufacturing/lessons/2-check-fruit-from-device/pi-camera.md",
  "language_code": "no"
}
-->
# Ta et bilde - Raspberry Pi

I denne delen av leksjonen skal du legge til en kamerasensor på din Raspberry Pi og lese bilder fra den.

## Maskinvare

Raspberry Pi trenger et kamera.

Kameraet du skal bruke er et [Raspberry Pi Camera Module](https://www.raspberrypi.org/products/camera-module-v2/). Dette kameraet er designet for å fungere med Raspberry Pi og kobles til via en dedikert kontakt på Pi.

> 💁 Dette kameraet bruker [Camera Serial Interface, en protokoll fra Mobile Industry Processor Interface Alliance](https://wikipedia.org/wiki/Camera_Serial_Interface), kjent som MIPI-CSI. Dette er en dedikert protokoll for å sende bilder.

## Koble til kameraet

Kameraet kan kobles til Raspberry Pi ved hjelp av en flatkabel.

### Oppgave - koble til kameraet

![Et Raspberry Pi-kamera](../../../../../translated_images/no/pi-camera-module.4278753c31bd6e757aa2b858be97d72049f71616278cefe4fb5abb485b40a078.png)

1. Slå av Pi.

1. Koble flatkabelen som følger med kameraet til kameraet. For å gjøre dette, trekk forsiktig i den svarte plastklipsen i holderen slik at den kommer litt ut, og skyv deretter kabelen inn i kontakten med den blå siden vendt bort fra linsen og metallstripene vendt mot linsen. Når kabelen er helt inne, skyv den svarte plastklipsen tilbake på plass.

    Du kan finne en animasjon som viser hvordan du åpner klipsen og setter inn kabelen i [Raspberry Pi Getting Started with the Camera module documentation](https://projects.raspberrypi.org/en/projects/getting-started-with-picamera/2).

    ![Flatkabelen satt inn i kameramodulen](../../../../../translated_images/no/pi-camera-ribbon-cable.0bf82acd251611c21ac616f082849413e2b322a261d0e4f8fec344248083b07e.png)

1. Fjern Grove Base Hat fra Pi.

1. Før flatkabelen gjennom kamerasporet i Grove Base Hat. Sørg for at den blå siden av kabelen vender mot de analoge portene merket **A0**, **A1** osv.

    ![Flatkabelen føres gjennom Grove Base Hat](../../../../../translated_images/no/grove-base-hat-ribbon-cable.501fed202fcf73b11b2b68f6d246189f7d15d3e4423c572ddee79d77b4632b47.png)

1. Sett flatkabelen inn i kamerakontakten på Pi. Igjen, trekk den svarte plastklipsen opp, sett inn kabelen, og skyv klipsen tilbake. Den blå siden av kabelen skal vende mot USB- og Ethernet-portene.

    ![Flatkabelen koblet til kamerakontakten på Pi](../../../../../translated_images/no/pi-camera-socket-ribbon-cable.a18309920b11800911082ed7aa6fb28e6d9be3a022e4079ff990016cae3fca10.png)

1. Sett Grove Base Hat tilbake på plass.

## Programmer kameraet

Raspberry Pi kan nå programmeres til å bruke kameraet ved hjelp av Python-biblioteket [PiCamera](https://pypi.org/project/picamera/).

### Oppgave - aktiver legacy kameramodus

Dessverre, med utgivelsen av Raspberry Pi OS Bullseye, endret kameraprogramvaren som fulgte med operativsystemet, noe som betyr at PiCamera ikke fungerer som standard. Det er en erstatning under utvikling, kalt PiCamera2, men denne er ikke klar til bruk ennå.

Foreløpig kan du sette Pi i legacy kameramodus for å tillate PiCamera å fungere. Kamerakontakten er også deaktivert som standard, men aktivering av legacy kameramodus aktiverer automatisk kontakten.

1. Slå på Pi og vent til den starter opp.

1. Start VS Code, enten direkte på Pi eller koble til via Remote SSH-utvidelsen.

1. Kjør følgende kommandoer fra terminalen:

    ```sh
    sudo raspi-config nonint do_legacy 0
    sudo reboot
    ```

    Dette vil endre en innstilling for å aktivere legacy kameramodus, og deretter starte Pi på nytt for at innstillingen skal tre i kraft.

1. Vent til Pi har startet på nytt, og start deretter VS Code på nytt.

### Oppgave - programmer kameraet

Programmer enheten.

1. Fra terminalen, opprett en ny mappe i hjemmekatalogen til brukeren `pi` kalt `fruit-quality-detector`. Opprett en fil i denne mappen kalt `app.py`.

1. Åpne denne mappen i VS Code.

1. For å samhandle med kameraet kan du bruke Python-biblioteket PiCamera. Installer Pip-pakken for dette med følgende kommando:

    ```sh
    pip3 install picamera
    ```

1. Legg til følgende kode i filen `app.py`:

    ```python
    import io
    import time
    from picamera import PiCamera
    ```

    Denne koden importerer noen nødvendige biblioteker, inkludert `PiCamera`-biblioteket.

1. Legg til følgende kode under dette for å initialisere kameraet:

    ```python
    camera = PiCamera()
    camera.resolution = (640, 480)
    camera.rotation = 0
    
    time.sleep(2)
    ```

    Denne koden oppretter et PiCamera-objekt og setter oppløsningen til 640x480. Selv om høyere oppløsninger støttes (opptil 3280x2464), fungerer bildekvalitetsklassifiseringen på mye mindre bilder (227x227), så det er ikke nødvendig å ta opp og sende større bilder.

    Linjen `camera.rotation = 0` setter rotasjonen til bildet. Flatkabelen kommer inn i bunnen av kameraet, men hvis kameraet ditt er rotert for å gjøre det lettere å peke på objektet du vil klassifisere, kan du endre denne linjen til antall grader rotasjon.

    ![Kameraet henger ned over en brusboks](../../../../../translated_images/no/pi-camera-upside-down.5376961ba31459883362124152ad6b823d5ac5fc14e85f317e22903bd681c2b6.png)

    For eksempel, hvis du henger flatkabelen over noe slik at den er på toppen av kameraet, sett rotasjonen til 180:

    ```python
    camera.rotation = 180
    ```

    Kameraet tar noen sekunder å starte opp, derfor linjen `time.sleep(2)`.

1. Legg til følgende kode under dette for å ta opp bildet som binære data:

    ```python
    image = io.BytesIO()
    camera.capture(image, 'jpeg')
    image.seek(0)
    ```

    Denne koden oppretter et `BytesIO`-objekt for å lagre binære data. Bildet leses fra kameraet som en JPEG-fil og lagres i dette objektet. Dette objektet har en posisjonsindikator for å vite hvor det er i dataene slik at mer data kan skrives til slutten hvis nødvendig, så linjen `image.seek(0)` flytter denne posisjonen tilbake til starten slik at alle dataene kan leses senere.

1. Under dette, legg til følgende for å lagre bildet til en fil:

    ```python
    with open('image.jpg', 'wb') as image_file:
        image_file.write(image.read())
    ```

    Denne koden åpner en fil kalt `image.jpg` for skriving, leser deretter alle dataene fra `BytesIO`-objektet og skriver det til filen.

    > 💁 Du kan ta opp bildet direkte til en fil i stedet for et `BytesIO`-objekt ved å sende filnavnet til `camera.capture`-kallet. Grunnen til å bruke `BytesIO`-objektet er at du senere i denne leksjonen kan sende bildet til bildekvalitetsklassifiseringen.

1. Pek kameraet mot noe og kjør denne koden.

1. Et bilde vil bli tatt opp og lagret som `image.jpg` i den gjeldende mappen. Du vil se denne filen i VS Code explorer. Velg filen for å se bildet. Hvis det trenger rotasjon, oppdater linjen `camera.rotation = 0` etter behov og ta et nytt bilde.

> 💁 Du finner denne koden i mappen [code-camera/pi](../../../../../4-manufacturing/lessons/2-check-fruit-from-device/code-camera/pi).

😀 Kameraet ditt fungerer!

---

**Ansvarsfraskrivelse**:  
Dette dokumentet er oversatt ved hjelp av AI-oversettelsestjenesten [Co-op Translator](https://github.com/Azure/co-op-translator). Selv om vi streber etter nøyaktighet, vær oppmerksom på at automatiserte oversettelser kan inneholde feil eller unøyaktigheter. Det originale dokumentet på sitt opprinnelige språk bør anses som den autoritative kilden. For kritisk informasjon anbefales profesjonell menneskelig oversettelse. Vi er ikke ansvarlige for misforståelser eller feiltolkninger som oppstår ved bruk av denne oversettelsen.