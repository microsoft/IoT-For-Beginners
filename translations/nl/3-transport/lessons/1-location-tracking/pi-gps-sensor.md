<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "3b2448c7ab4e9673e77e35a50c5e350d",
  "translation_date": "2025-08-27T22:55:25+00:00",
  "source_file": "3-transport/lessons/1-location-tracking/pi-gps-sensor.md",
  "language_code": "nl"
}
-->
# Lees GPS-gegevens - Raspberry Pi

In dit deel van de les voeg je een GPS-sensor toe aan je Raspberry Pi en lees je waarden ervan uit.

## Hardware

De Raspberry Pi heeft een GPS-sensor nodig.

De sensor die je zult gebruiken is een [Grove GPS Air530 sensor](https://www.seeedstudio.com/Grove-GPS-Air530-p-4584.html). Deze sensor kan verbinding maken met meerdere GPS-systemen voor een snelle en nauwkeurige locatiebepaling. De sensor bestaat uit twee onderdelen: de kern elektronica van de sensor en een externe antenne die via een dunne draad is verbonden om radiogolven van satellieten op te vangen.

Dit is een UART-sensor, dus hij verzendt GPS-gegevens via UART.

## Verbind de GPS-sensor

De Grove GPS-sensor kan worden aangesloten op de Raspberry Pi.

### Taak - verbind de GPS-sensor

Verbind de GPS-sensor.

![Een Grove GPS-sensor](../../../../../translated_images/nl/grove-gps-sensor.247943bf69b03f0d1820ef6ed10c587f9b650e8db55b936851c92412180bd3e2.png)

1. Steek één uiteinde van een Grove-kabel in de aansluiting op de GPS-sensor. De kabel past maar op één manier.

1. Met de Raspberry Pi uitgeschakeld, verbind je het andere uiteinde van de Grove-kabel met de UART-aansluiting gemarkeerd als **UART** op de Grove Base Hat die op de Pi is bevestigd. Deze aansluiting bevindt zich op de middelste rij, aan de kant die het dichtst bij de SD-kaartsleuf ligt, tegenover de USB-poorten en ethernet-aansluiting.

    ![De Grove GPS-sensor verbonden met de UART-aansluiting](../../../../../translated_images/nl/pi-gps-sensor.1f99ee2b2f6528915047ec78967bd362e0e4ee0ed594368a3837b9cf9cdaca64.png)

1. Plaats de GPS-sensor zo dat de aangesloten antenne zicht heeft op de lucht - bij voorkeur naast een open raam of buiten. Het is gemakkelijker om een duidelijker signaal te krijgen zonder obstakels voor de antenne.

## Programmeer de GPS-sensor

De Raspberry Pi kan nu worden geprogrammeerd om de aangesloten GPS-sensor te gebruiken.

### Taak - programmeer de GPS-sensor

Programmeer het apparaat.

1. Zet de Pi aan en wacht tot deze is opgestart.

1. De GPS-sensor heeft twee LED's: een blauwe LED die knippert wanneer gegevens worden verzonden, en een groene LED die elke seconde knippert wanneer gegevens van satellieten worden ontvangen. Zorg ervoor dat de blauwe LED knippert wanneer je de Pi aanzet. Na een paar minuten zal de groene LED knipperen - als dat niet gebeurt, moet je mogelijk de antenne opnieuw positioneren.

1. Start VS Code, direct op de Pi of via de Remote SSH-extensie.

    > ⚠️ Je kunt [de instructies voor het instellen en starten van VS Code in les 1 indien nodig](../../../1-getting-started/lessons/1-introduction-to-iot/pi.md) raadplegen.

1. Bij nieuwere versies van de Raspberry Pi die Bluetooth ondersteunen, is er een conflict tussen de seriële poort die wordt gebruikt voor Bluetooth en die wordt gebruikt door de Grove UART-poort. Om dit op te lossen, doe je het volgende:

    1. Open vanuit de VS Code-terminal het bestand `/boot/config.txt` met `nano`, een ingebouwde terminalteksteditor, met het volgende commando:

        ```sh
        sudo nano /boot/config.txt
        ```

        > Dit bestand kan niet worden bewerkt met VS Code omdat je `sudo`-rechten nodig hebt, verhoogde rechten. VS Code werkt niet met deze rechten.

    1. Gebruik de pijltjestoetsen om naar het einde van het bestand te navigeren. Kopieer vervolgens de onderstaande code en plak deze aan het einde van het bestand:

        ```ini
        dtoverlay=pi3-miniuart-bt
        dtoverlay=pi3-disable-bt
        enable_uart=1
        ```

        Je kunt plakken met de normale sneltoetsen voor je apparaat (`Ctrl+v` op Windows, Linux of Raspberry Pi OS, `Cmd+v` op macOS).

    1. Sla dit bestand op en sluit nano door op `Ctrl+x` te drukken. Druk op `y` wanneer je wordt gevraagd of je de gewijzigde buffer wilt opslaan, en druk vervolgens op `enter` om te bevestigen dat je `/boot/config.txt` wilt overschrijven.

        > Als je een fout maakt, kun je afsluiten zonder op te slaan en de stappen opnieuw uitvoeren.

    1. Bewerk het bestand `/boot/cmdline.txt` in nano met het volgende commando:

        ```sh
        sudo nano /boot/cmdline.txt
        ```

    1. Dit bestand bevat een aantal sleutel/waarde-paren gescheiden door spaties. Verwijder eventuele sleutel/waarde-paren voor de sleutel `console`. Ze zien er waarschijnlijk ongeveer zo uit:

        ```output
        console=serial0,115200 console=tty1 
        ```

        Je kunt naar deze items navigeren met de pijltjestoetsen en vervolgens verwijderen met de normale `del`- of `backspace`-toetsen.

        Als je oorspronkelijke bestand er bijvoorbeeld zo uitziet:

        ```output
        console=serial0,115200 console=tty1 root=PARTUUID=058e2867-02 rootfstype=ext4 elevator=deadline fsck.repair=yes rootwait
        ```

        Ziet de nieuwe versie er zo uit:

        ```output
        root=PARTUUID=058e2867-02 rootfstype=ext4 elevator=deadline fsck.repair=yes rootwait
        ```

    1. Volg de bovenstaande stappen om dit bestand op te slaan en nano te sluiten.

    1. Start je Pi opnieuw op en maak opnieuw verbinding in VS Code zodra de Pi opnieuw is opgestart.

1. Maak vanuit de terminal een nieuwe map in de home-directory van de gebruiker `pi` genaamd `gps-sensor`. Maak een bestand in deze map genaamd `app.py`.

1. Open deze map in VS Code.

1. De GPS-module verzendt UART-gegevens via een seriële poort. Installeer het `pyserial` Pip-pakket om via je Python-code met de seriële poort te communiceren:

    ```sh
    pip3 install pyserial
    ```

1. Voeg de volgende code toe aan je `app.py`-bestand:

    ```python
    import time
    import serial
    
    serial = serial.Serial('/dev/ttyAMA0', 9600, timeout=1)
    serial.reset_input_buffer()
    serial.flush()
    
    def print_gps_data(line):
        print(line.rstrip())
    
    while True:
        line = serial.readline().decode('utf-8')
    
        while len(line) > 0:
            print_gps_data(line)
            line = serial.readline().decode('utf-8')
    
        time.sleep(1)
    ```

    Deze code importeert de `serial`-module van het `pyserial` Pip-pakket. Vervolgens maakt het verbinding met de seriële poort `/dev/ttyAMA0` - dit is het adres van de seriële poort die de Grove Pi Base Hat gebruikt voor zijn UART-poort. Daarna worden eventuele bestaande gegevens van deze seriële verbinding gewist.

    Vervolgens wordt een functie genaamd `print_gps_data` gedefinieerd die de lijn die eraan wordt doorgegeven naar de console print.

    Daarna loopt de code oneindig door, waarbij zoveel mogelijk tekstregels van de seriële poort worden gelezen in elke lus. Voor elke regel wordt de functie `print_gps_data` aangeroepen.

    Nadat alle gegevens zijn gelezen, slaapt de lus 1 seconde en probeert het opnieuw.

1. Voer deze code uit. Je zult de ruwe uitvoer van de GPS-sensor zien, iets zoals het volgende:

    ```output
    $GNGGA,020604.001,4738.538654,N,12208.341758,W,1,3,,164.7,M,-17.1,M,,*67
    $GPGSA,A,1,,,,,,,,,,,,,,,*1E
    $BDGSA,A,1,,,,,,,,,,,,,,,*0F
    $GPGSV,1,1,00*79
    $BDGSV,1,1,00*68
    ```

    > Als je een van de volgende fouten krijgt bij het stoppen en opnieuw starten van je code, voeg dan een `try - except`-blok toe aan je while-lus.

      ```output
      UnicodeDecodeError: 'utf-8' codec can't decode byte 0x93 in position 0: invalid start byte
      UnicodeDecodeError: 'utf-8' codec can't decode byte 0xf1 in position 0: invalid continuation byte
      ```

    ```python
    while True:
        try:
            line = serial.readline().decode('utf-8')
              
            while len(line) > 0:
                print_gps_data()
                line = serial.readline().decode('utf-8')
      
        # There's a random chance the first byte being read is part way through a character.
        # Read another full line and continue.

        except UnicodeDecodeError:
            line = serial.readline().decode('utf-8')

    time.sleep(1)
    ```

> 💁 Je kunt deze code vinden in de map [code-gps/pi](../../../../../3-transport/lessons/1-location-tracking/code-gps/pi).

😀 Je GPS-sensorprogramma is een succes!

---

**Disclaimer**:  
Dit document is vertaald met behulp van de AI-vertalingsservice [Co-op Translator](https://github.com/Azure/co-op-translator). Hoewel we streven naar nauwkeurigheid, dient u zich ervan bewust te zijn dat geautomatiseerde vertalingen fouten of onnauwkeurigheden kunnen bevatten. Het originele document in zijn oorspronkelijke taal moet worden beschouwd als de gezaghebbende bron. Voor cruciale informatie wordt professionele menselijke vertaling aanbevolen. Wij zijn niet aansprakelijk voor eventuele misverstanden of verkeerde interpretaties die voortvloeien uit het gebruik van deze vertaling.