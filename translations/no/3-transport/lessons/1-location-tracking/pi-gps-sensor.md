# Les GPS-data - Raspberry Pi

I denne delen av leksjonen skal du legge til en GPS-sensor på din Raspberry Pi og lese verdier fra den.

## Maskinvare

Raspberry Pi trenger en GPS-sensor.

Sensoren du skal bruke er en [Grove GPS Air530-sensor](https://www.seeedstudio.com/Grove-GPS-Air530-p-4584.html). Denne sensoren kan koble seg til flere GPS-systemer for en rask og nøyaktig posisjonering. Sensoren består av to deler - selve elektronikken i sensoren og en ekstern antenne som er koblet til med en tynn ledning for å fange opp radiosignaler fra satellittene.

Dette er en UART-sensor, så den sender GPS-data over UART.

## Koble til GPS-sensoren

Grove GPS-sensoren kan kobles til Raspberry Pi.

### Oppgave - koble til GPS-sensoren

Koble til GPS-sensoren.

![En Grove GPS-sensor](../../../../../translated_images/no/grove-gps-sensor.247943bf69b03f0d.webp)

1. Sett den ene enden av en Grove-kabel inn i kontakten på GPS-sensoren. Den kan bare settes inn på én måte.

1. Med Raspberry Pi slått av, koble den andre enden av Grove-kabelen til UART-kontakten merket **UART** på Grove Base-hatten som er festet til Pi-en. Denne kontakten er på midtre rad, på siden nærmest SD-kortsporet, motsatt ende av USB-portene og Ethernet-kontakten.

    ![Grove GPS-sensoren koblet til UART-kontakten](../../../../../translated_images/no/pi-gps-sensor.1f99ee2b2f652891.webp)

1. Plasser GPS-sensoren slik at den tilkoblede antennen har fri sikt til himmelen - helst ved et åpent vindu eller utendørs. Det er lettere å få et klart signal uten hindringer foran antennen.

## Programmer GPS-sensoren

Raspberry Pi kan nå programmeres til å bruke den tilkoblede GPS-sensoren.

### Oppgave - programmer GPS-sensoren

Programmer enheten.

1. Slå på Pi-en og vent til den starter opp.

1. GPS-sensoren har to LED-lys - en blå LED som blinker når data overføres, og en grønn LED som blinker hvert sekund når den mottar data fra satellitter. Sørg for at den blå LED-en blinker når du slår på Pi-en. Etter noen minutter vil den grønne LED-en begynne å blinke - hvis ikke, kan det hende du må flytte antennen.

1. Start VS Code, enten direkte på Pi-en eller ved å koble til via Remote SSH-utvidelsen.

    > ⚠️ Du kan se [instruksjonene for å sette opp og starte VS Code i leksjon 1 hvis nødvendig](../../../1-getting-started/lessons/1-introduction-to-iot/pi.md).

1. Med nyere versjoner av Raspberry Pi som støtter Bluetooth, er det en konflikt mellom seriellporten som brukes til Bluetooth og den som brukes av Grove UART-porten. For å løse dette, gjør følgende:

    1. Fra VS Code-terminalen, rediger filen `/boot/config.txt` ved hjelp av `nano`, en innebygd terminaltekstredigerer, med følgende kommando:

        ```sh
        sudo nano /boot/config.txt
        ```

        > Denne filen kan ikke redigeres i VS Code fordi du må bruke `sudo`-tillatelser, altså forhøyede tillatelser. VS Code kjører ikke med disse tillatelsene.

    1. Bruk piltastene for å navigere til slutten av filen, og kopier deretter koden nedenfor og lim den inn på slutten av filen:

        ```ini
        dtoverlay=pi3-miniuart-bt
        dtoverlay=pi3-disable-bt
        enable_uart=1
        ```

        Du kan lime inn ved å bruke de vanlige hurtigtastene for enheten din (`Ctrl+v` på Windows, Linux eller Raspberry Pi OS, `Cmd+v` på macOS).

    1. Lagre filen og avslutt nano ved å trykke `Ctrl+x`. Trykk `y` når du blir spurt om du vil lagre den endrede bufferen, og trykk deretter `enter` for å bekrefte at du vil overskrive `/boot/config.txt`.

        > Hvis du gjør en feil, kan du avslutte uten å lagre og deretter gjenta disse trinnene.

    1. Rediger filen `/boot/cmdline.txt` i nano med følgende kommando:

        ```sh
        sudo nano /boot/cmdline.txt
        ```

    1. Denne filen har en rekke nøkkel/verdi-par separert med mellomrom. Fjern eventuelle nøkkel/verdi-par for nøkkelen `console`. De vil sannsynligvis se slik ut:

        ```output
        console=serial0,115200 console=tty1 
        ```

        Du kan navigere til disse oppføringene med piltastene og deretter slette dem med de vanlige `del`- eller `backspace`-tastene.

        For eksempel, hvis den opprinnelige filen din ser slik ut:

        ```output
        console=serial0,115200 console=tty1 root=PARTUUID=058e2867-02 rootfstype=ext4 elevator=deadline fsck.repair=yes rootwait
        ```

        Den nye versjonen vil være:

        ```output
        root=PARTUUID=058e2867-02 rootfstype=ext4 elevator=deadline fsck.repair=yes rootwait
        ```

    1. Følg trinnene ovenfor for å lagre denne filen og avslutte nano.

    1. Start Pi-en på nytt, og koble deretter til igjen i VS Code når Pi-en har startet opp.

1. Fra terminalen, opprett en ny mappe i hjemmekatalogen til brukeren `pi` kalt `gps-sensor`. Opprett en fil i denne mappen kalt `app.py`.

1. Åpne denne mappen i VS Code.

1. GPS-modulen sender UART-data over en seriell port. Installer `pyserial` Pip-pakken for å kommunisere med den serielle porten fra Python-koden din:

    ```sh
    pip3 install pyserial
    ```

1. Legg til følgende kode i filen `app.py`:

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

    Denne koden importerer `serial`-modulen fra `pyserial` Pip-pakken. Den kobler deretter til den serielle porten `/dev/ttyAMA0` - dette er adressen til den serielle porten som Grove Pi Base Hat bruker for sin UART-port. Den tømmer deretter eventuelle eksisterende data fra denne serielle forbindelsen.

    Deretter defineres en funksjon kalt `print_gps_data` som skriver ut linjen som sendes til den i konsollen.

    Deretter går koden i en evig løkke, leser så mange linjer med tekst som mulig fra den serielle porten i hver iterasjon. Den kaller funksjonen `print_gps_data` for hver linje.

    Etter at alle dataene er lest, sover løkken i 1 sekund før den prøver igjen.

1. Kjør denne koden. Du vil se råutdata fra GPS-sensoren, noe som kan se slik ut:

    ```output
    $GNGGA,020604.001,4738.538654,N,12208.341758,W,1,3,,164.7,M,-17.1,M,,*67
    $GPGSA,A,1,,,,,,,,,,,,,,,*1E
    $BDGSA,A,1,,,,,,,,,,,,,,,*0F
    $GPGSV,1,1,00*79
    $BDGSV,1,1,00*68
    ```

    > Hvis du får en av følgende feil når du stopper og starter koden på nytt, legg til en `try - except`-blokk i while-løkken din.

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

> 💁 Du finner denne koden i mappen [code-gps/pi](../../../../../3-transport/lessons/1-location-tracking/code-gps/pi).

😀 Programmet for GPS-sensoren din var en suksess!

---

**Ansvarsfraskrivelse**:  
Dette dokumentet er oversatt ved hjelp av AI-oversettelsestjenesten [Co-op Translator](https://github.com/Azure/co-op-translator). Selv om vi streber etter nøyaktighet, vær oppmerksom på at automatiske oversettelser kan inneholde feil eller unøyaktigheter. Det originale dokumentet på sitt opprinnelige språk bør anses som den autoritative kilden. For kritisk informasjon anbefales profesjonell menneskelig oversettelse. Vi er ikke ansvarlige for misforståelser eller feiltolkninger som oppstår ved bruk av denne oversettelsen.