# Læs GPS-data - Raspberry Pi

I denne del af lektionen vil du tilføje en GPS-sensor til din Raspberry Pi og læse værdier fra den.

## Hardware

Raspberry Pi'en har brug for en GPS-sensor.

Den sensor, du skal bruge, er en [Grove GPS Air530 sensor](https://www.seeedstudio.com/Grove-GPS-Air530-p-4584.html). Denne sensor kan forbinde til flere GPS-systemer for en hurtig og præcis positionering. Sensoren består af to dele - sensorens kerneelektronik og en ekstern antenne, der er forbundet med en tynd ledning for at opfange radiosignaler fra satellitterne.

Dette er en UART-sensor, så den sender GPS-data via UART.

## Tilslut GPS-sensoren

Grove GPS-sensoren kan tilsluttes Raspberry Pi'en.

### Opgave - tilslut GPS-sensoren

Tilslut GPS-sensoren.

![En Grove GPS-sensor](../../../../../translated_images/da/grove-gps-sensor.247943bf69b03f0d.webp)

1. Sæt den ene ende af et Grove-kabel i stikket på GPS-sensoren. Det kan kun sættes i på én måde.

1. Med Raspberry Pi'en slukket, tilslut den anden ende af Grove-kablet til UART-stikket markeret **UART** på Grove Base-hatten, der er tilsluttet Pi'en. Dette stik er placeret på den midterste række, på siden tættest på SD-kortslottet, i den modsatte ende af USB-portene og ethernet-stikket.

    ![Grove GPS-sensoren tilsluttet UART-stikket](../../../../../translated_images/da/pi-gps-sensor.1f99ee2b2f652891.webp)

1. Placer GPS-sensoren, så den tilkoblede antenne har udsyn til himlen - ideelt set ved et åbent vindue eller udenfor. Det er lettere at få et klart signal uden forhindringer foran antennen.

## Programmer GPS-sensoren

Raspberry Pi'en kan nu programmeres til at bruge den tilsluttede GPS-sensor.

### Opgave - programmer GPS-sensoren

Programmer enheden.

1. Tænd for Pi'en og vent, indtil den er startet op.

1. GPS-sensoren har 2 LED'er - en blå LED, der blinker, når data overføres, og en grøn LED, der blinker hvert sekund, når den modtager data fra satellitter. Sørg for, at den blå LED blinker, når du tænder Pi'en. Efter et par minutter vil den grønne LED begynde at blinke - hvis ikke, kan det være nødvendigt at flytte antennen.

1. Start VS Code, enten direkte på Pi'en eller ved at forbinde via Remote SSH-udvidelsen.

    > ⚠️ Du kan finde [instruktionerne til opsætning og start af VS Code i lektion 1, hvis det er nødvendigt](../../../1-getting-started/lessons/1-introduction-to-iot/pi.md).

1. Med nyere versioner af Raspberry Pi, der understøtter Bluetooth, er der en konflikt mellem den serielle port, der bruges til Bluetooth, og den, der bruges af Grove UART-porten. For at løse dette skal du gøre følgende:

    1. Fra VS Code-terminalen skal du redigere filen `/boot/config.txt` ved hjælp af `nano`, en indbygget terminalteksteditor, med følgende kommando:

        ```sh
        sudo nano /boot/config.txt
        ```

        > Denne fil kan ikke redigeres i VS Code, da du skal bruge `sudo`-rettigheder, en forhøjet tilladelse. VS Code kører ikke med denne tilladelse.

    1. Brug piletasterne til at navigere til slutningen af filen, og kopier derefter koden nedenfor og indsæt den i slutningen af filen:

        ```ini
        dtoverlay=pi3-miniuart-bt
        dtoverlay=pi3-disable-bt
        enable_uart=1
        ```

        Du kan indsætte ved at bruge de normale tastaturgenveje for din enhed (`Ctrl+v` på Windows, Linux eller Raspberry Pi OS, `Cmd+v` på macOS).

    1. Gem filen og afslut nano ved at trykke på `Ctrl+x`. Tryk på `y`, når du bliver spurgt, om du vil gemme den ændrede buffer, og tryk derefter på `enter` for at bekræfte, at du vil overskrive `/boot/config.txt`.

        > Hvis du laver en fejl, kan du afslutte uden at gemme og derefter gentage disse trin.

    1. Rediger filen `/boot/cmdline.txt` i nano med følgende kommando:

        ```sh
        sudo nano /boot/cmdline.txt
        ```

    1. Denne fil indeholder en række nøgle/værdi-par adskilt af mellemrum. Fjern eventuelle nøgle/værdi-par for nøglen `console`. De vil sandsynligvis se sådan ud:

        ```output
        console=serial0,115200 console=tty1 
        ```

        Du kan navigere til disse poster ved hjælp af piletasterne og derefter slette dem ved hjælp af de normale `del`- eller `backspace`-taster.

        For eksempel, hvis din oprindelige fil ser sådan ud:

        ```output
        console=serial0,115200 console=tty1 root=PARTUUID=058e2867-02 rootfstype=ext4 elevator=deadline fsck.repair=yes rootwait
        ```

        Den nye version vil være:

        ```output
        root=PARTUUID=058e2867-02 rootfstype=ext4 elevator=deadline fsck.repair=yes rootwait
        ```

    1. Følg ovenstående trin for at gemme denne fil og afslutte nano.

    1. Genstart din Pi, og forbind derefter igen i VS Code, når Pi'en er genstartet.

1. Fra terminalen skal du oprette en ny mappe i `pi`-brugerens hjemmemappe kaldet `gps-sensor`. Opret en fil i denne mappe kaldet `app.py`.

1. Åbn denne mappe i VS Code.

1. GPS-modulet sender UART-data via en seriel port. Installer `pyserial` Pip-pakken for at kommunikere med den serielle port fra din Python-kode:

    ```sh
    pip3 install pyserial
    ```

1. Tilføj følgende kode til din `app.py`-fil:

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

    Denne kode importerer `serial`-modulet fra `pyserial` Pip-pakken. Den opretter derefter forbindelse til den serielle port `/dev/ttyAMA0` - dette er adressen på den serielle port, som Grove Pi Base Hat bruger til sin UART-port. Den rydder derefter eventuelle eksisterende data fra denne serielle forbindelse.

    Derefter defineres en funktion kaldet `print_gps_data`, der udskriver den linje, der sendes til den, til konsollen.

    Dernæst kører koden i en uendelig løkke, hvor den læser så mange tekstlinjer som muligt fra den serielle port i hver iteration. Den kalder funktionen `print_gps_data` for hver linje.

    Når alle data er læst, sover løkken i 1 sekund og prøver derefter igen.

1. Kør denne kode. Du vil se rå output fra GPS-sensoren, noget i stil med følgende:

    ```output
    $GNGGA,020604.001,4738.538654,N,12208.341758,W,1,3,,164.7,M,-17.1,M,,*67
    $GPGSA,A,1,,,,,,,,,,,,,,,*1E
    $BDGSA,A,1,,,,,,,,,,,,,,,*0F
    $GPGSV,1,1,00*79
    $BDGSV,1,1,00*68
    ```

    > Hvis du får en af følgende fejl, når du stopper og genstarter din kode, skal du tilføje en `try - except`-blok til din while-løkke.

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

> 💁 Du kan finde denne kode i [code-gps/pi](../../../../../3-transport/lessons/1-location-tracking/code-gps/pi)-mappen.

😀 Dit GPS-sensorprogram var en succes!

---

**Ansvarsfraskrivelse**:  
Dette dokument er blevet oversat ved hjælp af AI-oversættelsestjenesten [Co-op Translator](https://github.com/Azure/co-op-translator). Selvom vi bestræber os på nøjagtighed, skal du være opmærksom på, at automatiserede oversættelser kan indeholde fejl eller unøjagtigheder. Det originale dokument på dets oprindelige sprog bør betragtes som den autoritative kilde. For kritisk information anbefales professionel menneskelig oversættelse. Vi er ikke ansvarlige for eventuelle misforståelser eller fejltolkninger, der opstår som følge af brugen af denne oversættelse.