# Læs GPS-data - Virtuel IoT-hardware

I denne del af lektionen vil du tilføje en GPS-sensor til din virtuelle IoT-enhed og læse værdier fra den.

## Virtuel hardware

Den virtuelle IoT-enhed vil bruge en simuleret GPS-sensor, der er tilgængelig via UART gennem en seriel port.

En fysisk GPS-sensor har en antenne til at opfange radiobølger fra GPS-satellitter og konvertere GPS-signaler til GPS-data. Den virtuelle version simulerer dette ved at lade dig enten indstille en bredde- og længdegrad, sende rå NMEA-sætninger eller uploade en GPX-fil med flere lokationer, der kan returneres sekventielt.

> 🎓 NMEA-sætninger vil blive gennemgået senere i denne lektion

### Tilføj sensoren til CounterFit

For at bruge en virtuel GPS-sensor skal du tilføje en til CounterFit-appen.

#### Opgave - tilføj sensoren til CounterFit

Tilføj GPS-sensoren til CounterFit-appen.

1. Opret en ny Python-app på din computer i en mappe kaldet `gps-sensor` med en enkelt fil kaldet `app.py` og et Python-virtuelt miljø, og tilføj CounterFit pip-pakkerne.

    > ⚠️ Du kan henvise til [instruktionerne for at oprette og opsætte et CounterFit Python-projekt i lektion 1, hvis nødvendigt](../../../1-getting-started/lessons/1-introduction-to-iot/virtual-device.md).

1. Installer en ekstra Pip-pakke for at installere en CounterFit shim, der kan kommunikere med UART-baserede sensorer via en seriel forbindelse. Sørg for, at du installerer dette fra en terminal med det virtuelle miljø aktiveret.

    ```sh
    pip install counterfit-shims-serial
    ```

1. Sørg for, at CounterFit-webappen kører.

1. Opret en GPS-sensor:

    1. I boksen *Create sensor* i panelet *Sensors*, vælg *Sensor type* og vælg *UART GPS*.

    1. Lad *Port* være indstillet til */dev/ttyAMA0*.

    1. Vælg knappen **Add** for at oprette GPS-sensoren på porten `/dev/ttyAMA0`.

    ![Indstillinger for GPS-sensoren](../../../../../translated_images/da/counterfit-create-gps-sensor.6385dc9357d85ad1.webp)

    GPS-sensoren vil blive oprettet og vises i sensorlisten.

    ![Den oprettede GPS-sensor](../../../../../translated_images/da/counterfit-gps-sensor.3fbb15af0a536756.webp)

## Programmer GPS-sensoren

Den virtuelle IoT-enhed kan nu programmeres til at bruge den virtuelle GPS-sensor.

### Opgave - programmer GPS-sensoren

Programmer GPS-sensor-appen.

1. Sørg for, at `gps-sensor`-appen er åben i VS Code.

1. Åbn filen `app.py`.

1. Tilføj følgende kode øverst i `app.py` for at forbinde appen til CounterFit:

    ```python
    from counterfit_connection import CounterFitConnection
    CounterFitConnection.init('127.0.0.1', 5000)
    ```

1. Tilføj følgende kode nedenunder for at importere nogle nødvendige biblioteker, inklusive biblioteket til CounterFit-seriel port:

    ```python
    import time
    import counterfit_shims_serial
    
    serial = counterfit_shims_serial.Serial('/dev/ttyAMA0')
    ```

    Denne kode importerer `serial`-modulet fra Pip-pakken `counterfit_shims_serial`. Den forbinder derefter til den serielle port `/dev/ttyAMA0` - dette er adressen på den serielle port, som den virtuelle GPS-sensor bruger til sin UART-port.

1. Tilføj følgende kode nedenunder for at læse fra den serielle port og udskrive værdierne til konsollen:

    ```python
    def print_gps_data(line):
        print(line.rstrip())
    
    while True:
        line = serial.readline().decode('utf-8')
    
        while len(line) > 0:
            print_gps_data(line)
            line = serial.readline().decode('utf-8')
    
        time.sleep(1)
    ```

    En funktion kaldet `print_gps_data` defineres, som udskriver den linje, der sendes til den, til konsollen.

    Derefter kører koden i en uendelig løkke, hvor den læser så mange tekstlinjer som muligt fra den serielle port i hver iteration. Den kalder funktionen `print_gps_data` for hver linje.

    Når alle data er læst, sover løkken i 1 sekund og prøver derefter igen.

1. Kør denne kode, og sørg for, at du bruger en anden terminal end den, hvor CounterFit-appen kører, så CounterFit-appen forbliver aktiv.

1. Fra CounterFit-appen kan du ændre værdien af GPS-sensoren. Du kan gøre dette på en af følgende måder:

    * Indstil **Source** til `Lat/Lon`, og angiv en specifik breddegrad, længdegrad og antal satellitter, der bruges til at få GPS-fix. Denne værdi sendes kun én gang, så marker **Repeat**-boksen for at få dataene til at gentage hvert sekund.

      ![GPS-sensoren med lat/lon valgt](../../../../../translated_images/da/counterfit-gps-sensor-latlon.008c867d75464fbe.webp)

    * Indstil **Source** til `NMEA`, og tilføj nogle NMEA-sætninger i tekstboksen. Alle disse værdier sendes med en forsinkelse på 1 sekund, før hver ny GGA (positionsfix)-sætning kan læses.

      ![GPS-sensoren med NMEA-sætninger indstillet](../../../../../translated_images/da/counterfit-gps-sensor-nmea.c62eea442171e17e.webp)

      Du kan bruge et værktøj som [nmeagen.org](https://www.nmeagen.org) til at generere disse sætninger ved at tegne på et kort. Disse værdier sendes kun én gang, så marker **Repeat**-boksen for at få dataene til at gentage 1 sekund efter, at de alle er sendt.

    * Indstil **Source** til GPX-fil, og upload en GPX-fil med spor-lokationer. Du kan downloade GPX-filer fra en række populære kort- og vandresider, såsom [AllTrails](https://www.alltrails.com/). Disse filer indeholder flere GPS-lokationer som en rute, og GPS-sensoren returnerer hver ny lokation med 1 sekunds interval.

      ![GPS-sensoren med en GPX-fil indstillet](../../../../../translated_images/da/counterfit-gps-sensor-gpxfile.8310b063ce8a425c.webp)

      Disse værdier sendes kun én gang, så marker **Repeat**-boksen for at få dataene til at gentage 1 sekund efter, at de alle er sendt.

    Når du har konfigureret GPS-indstillingerne, skal du vælge knappen **Set** for at gemme disse værdier på sensoren.

1. Du vil se rå output fra GPS-sensoren, noget i stil med følgende:

    ```output
    $GNGGA,020604.001,4738.538654,N,12208.341758,W,1,3,,164.7,M,-17.1,M,,*67
    $GNGGA,020604.001,4738.538654,N,12208.341758,W,1,3,,164.7,M,-17.1,M,,*67
    ```

> 💁 Du kan finde denne kode i mappen [code-gps/virtual-device](../../../../../3-transport/lessons/1-location-tracking/code-gps/virtual-device).

😀 Dit GPS-sensorprogram var en succes!

---

**Ansvarsfraskrivelse**:  
Dette dokument er blevet oversat ved hjælp af AI-oversættelsestjenesten [Co-op Translator](https://github.com/Azure/co-op-translator). Selvom vi bestræber os på at opnå nøjagtighed, skal du være opmærksom på, at automatiserede oversættelser kan indeholde fejl eller unøjagtigheder. Det originale dokument på dets oprindelige sprog bør betragtes som den autoritative kilde. For kritisk information anbefales professionel menneskelig oversættelse. Vi påtager os ikke ansvar for eventuelle misforståelser eller fejltolkninger, der måtte opstå som følge af brugen af denne oversættelse.