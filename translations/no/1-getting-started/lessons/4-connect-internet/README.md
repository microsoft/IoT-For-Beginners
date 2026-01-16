<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "71b5040e0b3472f1c0949c9b55f224c0",
  "translation_date": "2025-08-27T21:48:37+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/README.md",
  "language_code": "no"
}
-->
# Koble enheten din til Internett

![En sketchnote-oversikt over denne leksjonen](../../../../../translated_images/no/lesson-4.7344e074ea68fa545fd320b12dce36d72dd62d28c3b4596cb26cf315f434b98f.jpg)

> Sketchnote av [Nitya Narasimhan](https://github.com/nitya). Klikk på bildet for en større versjon.

Denne leksjonen ble undervist som en del av [Hello IoT-serien](https://youtube.com/playlist?list=PLmsFUfdnGr3xRts0TIwyaHyQuHaNQcb6-) fra [Microsoft Reactor](https://developer.microsoft.com/reactor/?WT.mc_id=academic-17441-jabenn). Leksjonen ble presentert i to videoer - en én times leksjon og en én times kontortid for å gå dypere inn i deler av leksjonen og svare på spørsmål.

[![Leksjon 4: Koble enheten din til Internett](https://img.youtube.com/vi/O4dd172mZhs/0.jpg)](https://youtu.be/O4dd172mZhs)

[![Leksjon 4: Koble enheten din til Internett - Kontortid](https://img.youtube.com/vi/j-cVCzRDE2Q/0.jpg)](https://youtu.be/j-cVCzRDE2Q)

> 🎥 Klikk på bildene ovenfor for å se videoene

## Quiz før leksjonen

[Quiz før leksjonen](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/7)

## Introduksjon

**I** i IoT står for **Internett** - skytilkoblingen og tjenestene som muliggjør mange av funksjonene til IoT-enheter, fra å samle inn målinger fra sensorer koblet til enheten, til å sende meldinger for å kontrollere aktuatorer. IoT-enheter kobler seg vanligvis til én skybasert IoT-tjeneste ved hjelp av en standard kommunikasjonsprotokoll, og denne tjenesten er koblet til resten av IoT-applikasjonen din, fra AI-tjenester for å ta smarte beslutninger basert på dataene, til webapplikasjoner for kontroll eller rapportering.

> 🎓 Data samlet inn fra sensorer og sendt til skyen kalles telemetri.

IoT-enheter kan motta meldinger fra skyen. Ofte inneholder meldingene kommandoer - instruksjoner for å utføre en handling enten internt (som å starte på nytt eller oppdatere firmware), eller ved hjelp av en aktuator (som å slå på et lys).

Denne leksjonen introduserer noen av kommunikasjonsprotokollene IoT-enheter kan bruke for å koble seg til skyen, og typene data de kan sende eller motta. Du vil også få praktisk erfaring med begge deler, ved å legge til internettkontroll til nattlampen din og flytte LED-kontrolllogikken til 'server'-kode som kjører lokalt.

I denne leksjonen skal vi dekke:

* [Kommunikasjonsprotokoller](../../../../../1-getting-started/lessons/4-connect-internet)
* [Message Queueing Telemetry Transport (MQTT)](../../../../../1-getting-started/lessons/4-connect-internet)
* [Telemetri](../../../../../1-getting-started/lessons/4-connect-internet)
* [Kommandoer](../../../../../1-getting-started/lessons/4-connect-internet)

## Kommunikasjonsprotokoller

Det finnes flere populære kommunikasjonsprotokoller som IoT-enheter bruker for å kommunisere med Internett. De mest populære er basert på publiser/abonner-meldinger via en form for megler. IoT-enhetene kobler seg til megleren og publiserer telemetri og abonnerer på kommandoer. Sky-tjenestene kobler seg også til megleren og abonnerer på alle telemetrimeldinger og publiserer kommandoer enten til spesifikke enheter eller til grupper av enheter.

![IoT-enheter kobler seg til en megler og publiserer telemetri og abonnerer på kommandoer. Sky-tjenester kobler seg til megleren og abonnerer på all telemetri og sender kommandoer til spesifikke enheter.](../../../../../translated_images/no/pub-sub.7c7ed43fe9fd15d4.webp)

MQTT er den mest populære kommunikasjonsprotokollen for IoT-enheter og dekkes i denne leksjonen. Andre protokoller inkluderer AMQP og HTTP/HTTPS.

## Message Queueing Telemetry Transport (MQTT)

[MQTT](http://mqtt.org) er en lettvekts, åpen standard meldingsprotokoll som kan sende meldinger mellom enheter. Den ble designet i 1999 for å overvåke oljerørledninger, før den ble utgitt som en åpen standard 15 år senere av IBM.

MQTT har én megler og flere klienter. Alle klienter kobler seg til megleren, og megleren ruter meldinger til relevante klienter. Meldinger rutes ved hjelp av navngitte emner, i stedet for å bli sendt direkte til en individuell klient. En klient kan publisere til et emne, og alle klienter som abonnerer på det emnet vil motta meldingen.

![IoT-enhet publiserer telemetri på /telemetry-emnet, og sky-tjenesten abonnerer på det emnet](../../../../../translated_images/no/mqtt.cbf7f21d9adc3e17548b359444cc11bb4bf2010543e32ece9a47becf54438c23.png)

✅ Gjør litt research. Hvis du har mange IoT-enheter, hvordan kan du sikre at MQTT-megleren din kan håndtere alle meldingene?

### Koble IoT-enheten din til MQTT

Den første delen av å legge til internettkontroll til nattlampen din er å koble den til en MQTT-megler.

#### Oppgave

Koble enheten din til en MQTT-megler.

I denne delen av leksjonen vil du koble IoT-nattlampen din til internett for å gjøre det mulig å kontrollere den eksternt. Senere i leksjonen vil IoT-enheten din sende en telemetrimelding over MQTT til en offentlig MQTT-megler med lysnivået, hvor den vil bli plukket opp av serverkode som du skal skrive. Denne koden vil sjekke lysnivået og sende en kommandomelding tilbake til enheten som instruerer den om å slå LED-en på eller av.

Et reelt bruksområde for en slik oppsett kan være å samle data fra flere lyssensorer før man bestemmer seg for å slå på lysene, i et område med mange lys, som en stadion. Dette kan forhindre at lysene blir slått på hvis bare én sensor er dekket av skyer eller en fugl, men de andre sensorene registrerer nok lys.

✅ Hvilke andre situasjoner kan kreve at data fra flere sensorer evalueres før kommandoer sendes?

I stedet for å håndtere kompleksiteten ved å sette opp en MQTT-megler som en del av denne oppgaven, kan du bruke en offentlig testserver som kjører [Eclipse Mosquitto](https://www.mosquitto.org), en åpen kildekode MQTT-megler. Denne testmegleren er offentlig tilgjengelig på [test.mosquitto.org](https://test.mosquitto.org), og krever ikke at du oppretter en konto, noe som gjør den til et flott verktøy for testing av MQTT-klienter og -servere.

> 💁 Denne testmegleren er offentlig og ikke sikker. Alle kan lytte til det du publiserer, så den bør ikke brukes med data som må holdes privat.

![Et flytskjema for oppgaven som viser lysnivåer som leses og sjekkes, og LED-en som kontrolleres](../../../../../translated_images/no/assignment-1-internet-flow.3256feab5f052fd273bf4e331157c574c2c3fa42e479836fc9c3586f41db35a5.png)

Følg relevant steg nedenfor for å koble enheten din til MQTT-megleren:

* [Arduino - Wio Terminal](wio-terminal-mqtt.md)
* [Enkeltkortdatamaskin - Raspberry Pi/Virtual IoT-enhet](single-board-computer-mqtt.md)

### En dypere titt på MQTT

Emner kan ha en hierarki, og klienter kan abonnere på forskjellige nivåer i hierarkiet ved hjelp av jokertegn. For eksempel kan du sende temperaturtelemetrimeldinger til `/telemetry/temperature`-emnet og fuktighetsmeldinger til `/telemetry/humidity`-emnet, og deretter i skyapplikasjonen din abonnere på `/telemetry/*`-emnet for å motta både temperatur- og fuktighetstelemetrimeldinger.

Meldinger kan sendes med en kvalitet på tjenesten (QoS), som bestemmer garantien for at meldingen blir mottatt.

* Maksimalt én gang - meldingen sendes kun én gang, og klienten og megleren tar ingen ekstra steg for å bekrefte levering (send og glem).
* Minst én gang - meldingen blir sendt på nytt av avsenderen flere ganger til bekreftelse er mottatt (bekreftet levering).
* Nøyaktig én gang - avsenderen og mottakeren gjennomfører en to-nivå håndtrykk for å sikre at kun én kopi av meldingen blir mottatt (sikret levering).

✅ Hvilke situasjoner kan kreve en sikret leveringsmelding over en send og glem-melding?

Selv om navnet er Message Queueing (MQTT), støtter det faktisk ikke meldingskøer. Dette betyr at hvis en klient kobler fra og deretter kobler til igjen, vil den ikke motta meldinger sendt under frakoblingen, bortsett fra de meldingene den allerede har begynt å behandle ved hjelp av QoS-prosessen. Meldinger kan ha et beholdt flagg satt på dem. Hvis dette er satt, vil MQTT-megleren lagre den siste meldingen sendt på et emne med dette flagget, og sende dette til alle klienter som senere abonnerer på emnet. På denne måten vil klientene alltid få den nyeste meldingen.

MQTT støtter også en "keep alive"-funksjon som sjekker om tilkoblingen fortsatt er aktiv under lange pauser mellom meldinger.

> 🦟 [Mosquitto fra Eclipse Foundation](https://mosquitto.org) har en gratis MQTT-megler du kan kjøre selv for å eksperimentere med MQTT, sammen med en offentlig MQTT-megler du kan bruke til å teste koden din, hostet på [test.mosquitto.org](https://test.mosquitto.org).

MQTT-tilkoblinger kan være offentlige og åpne, eller krypterte og sikret med brukernavn og passord, eller sertifikater.

> 💁 MQTT kommuniserer over TCP/IP, det samme underliggende nettverksprotokollen som HTTP, men på en annen port. Du kan også bruke MQTT over websockets for å kommunisere med webapplikasjoner som kjører i en nettleser, eller i situasjoner der brannmurer eller andre nettverksregler blokkerer standard MQTT-tilkoblinger.

## Telemetri

Ordet telemetri er avledet fra greske røtter som betyr å måle eksternt. Telemetri er handlingen med å samle inn data fra sensorer og sende det til skyen.

> 💁 En av de tidligste telemetrianordningene ble oppfunnet i Frankrike i 1874 og sendte sanntids vær- og snødybder fra Mont Blanc til Paris. Den brukte fysiske ledninger siden trådløse teknologier ikke var tilgjengelige på den tiden.

La oss se tilbake på eksempelet med den smarte termostaten fra Leksjon 1.

![En Internett-tilkoblet termostat som bruker flere romsensorer](../../../../../translated_images/no/telemetry.21e5d8b97649d2eb.webp)

Termostaten har temperatursensorer for å samle telemetri. Den vil mest sannsynlig ha én innebygd temperatursensor, og den kan koble seg til flere eksterne temperatursensorer via en trådløs protokoll som [Bluetooth Low Energy](https://wikipedia.org/wiki/Bluetooth_Low_Energy) (BLE).

Et eksempel på telemetridata den kan sende kan være:

| Navn | Verdi | Beskrivelse |
| ---- | ----- | ----------- |
| `thermostat_temperature` | 18°C | Temperaturen målt av termostatens innebygde temperatursensor |
| `livingroom_temperature` | 19°C | Temperaturen målt av en ekstern temperatursensor som har blitt navngitt `livingroom` for å identifisere rommet den er i |
| `bedroom_temperature` | 21°C | Temperaturen målt av en ekstern temperatursensor som har blitt navngitt `bedroom` for å identifisere rommet den er i |

Sky-tjenesten kan deretter bruke disse telemetridataene til å ta beslutninger om hvilke kommandoer som skal sendes for å kontrollere oppvarmingen.

### Send telemetri fra IoT-enheten din

Neste del i å legge til internettkontroll til nattlampen din er å sende lysnivåtelemetri til MQTT-megleren på et telemetriemne.

#### Oppgave - send telemetri fra IoT-enheten din

Send lysnivåtelemetri til MQTT-megleren.

Data sendes kodet som JSON - kort for JavaScript Object Notation, en standard for å kode data i tekst ved hjelp av nøkkel/verdi-par.

✅ Hvis du ikke har kommet over JSON før, kan du lære mer om det på [JSON.org-dokumentasjonen](https://www.json.org/).

Følg relevant steg nedenfor for å sende telemetri fra enheten din til MQTT-megleren:

* [Arduino - Wio Terminal](wio-terminal-telemetry.md)
* [Enkeltkortdatamaskin - Raspberry Pi/Virtual IoT-enhet](single-board-computer-telemetry.md)

### Motta telemetri fra MQTT-megleren

Det er ingen vits i å sende telemetri hvis det ikke er noe på den andre enden som lytter etter det. Lysnivåtelemetrien trenger noe som lytter til den for å behandle dataene. Denne 'server'-koden er den typen kode du vil distribuere til en sky-tjeneste som en del av en større IoT-applikasjon, men her skal du kjøre denne koden lokalt på datamaskinen din (eller på Pi-en din hvis du koder direkte der). Serverkoden består av en Python-app som lytter til telemetrimeldinger over MQTT med lysnivåer. Senere i denne leksjonen vil du få den til å svare med en kommandomelding med instruksjoner om å slå LED-en på eller av.

✅ Gjør litt research: Hva skjer med MQTT-meldinger hvis det ikke er noen lytter?

#### Installer Python og VS Code

Hvis du ikke har Python og VS Code installert lokalt, må du installere begge deler for å kode serveren. Hvis du bruker en virtuell IoT-enhet, eller jobber på Raspberry Pi-en din, kan du hoppe over dette steget siden du allerede bør ha dette installert og konfigurert.

##### Oppgave - installer Python og VS Code

Installer Python og VS Code.

1. Installer Python. Se [Python nedlastingssiden](https://www.python.org/downloads/) for instruksjoner om hvordan du installerer den nyeste versjonen av Python.

1. Installer Visual Studio Code (VS Code). Dette er editoren du vil bruke til å skrive den virtuelle enhetskoden din i Python. Se [VS Code-dokumentasjonen](https://code.visualstudio.com?WT.mc_id=academic-17441-jabenn) for instruksjoner om hvordan du installerer VS Code.
💁 Du står fritt til å bruke hvilken som helst Python IDE eller editor for disse leksjonene hvis du har et foretrukket verktøy, men leksjonene vil gi instruksjoner basert på bruk av VS Code.
1. Installer VS Code Pylance-utvidelsen. Dette er en utvidelse for VS Code som gir støtte for Python-språket. Se [Pylance-utvidelsens dokumentasjon](https://marketplace.visualstudio.com/items?WT.mc_id=academic-17441-jabenn&itemName=ms-python.vscode-pylance) for instruksjoner om hvordan du installerer denne utvidelsen i VS Code.

#### Konfigurer et Python-virtuelt miljø

En av de kraftige funksjonene i Python er muligheten til å installere [pip-pakker](https://pypi.org) - dette er kodepakker skrevet av andre og publisert på Internett. Du kan installere en pip-pakke på datamaskinen din med én kommando, og deretter bruke den i koden din. Du vil bruke pip til å installere en pakke for kommunikasjon over MQTT.

Som standard, når du installerer en pakke, er den tilgjengelig overalt på datamaskinen din, og dette kan føre til problemer med pakkeversjoner - for eksempel at én applikasjon avhenger av én versjon av en pakke som slutter å fungere når du installerer en ny versjon for en annen applikasjon. For å unngå dette problemet kan du bruke et [Python-virtuelt miljø](https://docs.python.org/3/library/venv.html), som i hovedsak er en kopi av Python i en dedikert mappe, og når du installerer pip-pakker, blir de kun installert i den mappen.

##### Oppgave - konfigurer et Python-virtuelt miljø

Konfigurer et Python-virtuelt miljø og installer MQTT-pip-pakkene.

1. Fra terminalen eller kommandolinjen, kjør følgende på et sted du velger for å opprette og navigere til en ny mappe:

    ```sh
    mkdir nightlight-server
    cd nightlight-server
    ```

1. Kjør deretter følgende for å opprette et virtuelt miljø i `.venv`-mappen:

    ```sh
    python3 -m venv .venv
    ```

    > 💁 Du må eksplisitt kalle `python3` for å opprette det virtuelle miljøet, i tilfelle du har Python 2 installert i tillegg til Python 3 (den nyeste versjonen). Hvis du har Python 2 installert, vil det å kalle `python` bruke Python 2 i stedet for Python 3.

1. Aktiver det virtuelle miljøet:

    * På Windows:
        * Hvis du bruker Command Prompt, eller Command Prompt gjennom Windows Terminal, kjør:

            ```cmd
            .venv\Scripts\activate.bat
            ```

        * Hvis du bruker PowerShell, kjør:

            ```powershell
            .\.venv\Scripts\Activate.ps1
            ```

    * På macOS eller Linux, kjør:

        ```cmd
        source ./.venv/bin/activate
        ```

    > 💁 Disse kommandoene bør kjøres fra samme sted som du kjørte kommandoen for å opprette det virtuelle miljøet. Du trenger aldri å navigere inn i `.venv`-mappen, du bør alltid kjøre aktiveringskommandoen og eventuelle kommandoer for å installere pakker eller kjøre kode fra mappen du var i da du opprettet det virtuelle miljøet.

1. Når det virtuelle miljøet er aktivert, vil standardkommandoen `python` kjøre versjonen av Python som ble brukt til å opprette det virtuelle miljøet. Kjør følgende for å få versjonen:

    ```sh
    python --version
    ```

    Utdataene vil være lik følgende:

    ```output
    (.venv) ➜  nightlight-server python --version
    Python 3.9.1
    ```

    > 💁 Din Python-versjon kan være annerledes - så lenge den er versjon 3.6 eller høyere er du klar. Hvis ikke, slett denne mappen, installer en nyere versjon av Python og prøv igjen.

1. Kjør følgende kommandoer for å installere pip-pakken for [Paho-MQTT](https://pypi.org/project/paho-mqtt/), et populært MQTT-bibliotek.

    ```sh
    pip install paho-mqtt
    ```

    Denne pip-pakken vil kun bli installert i det virtuelle miljøet, og vil ikke være tilgjengelig utenfor dette.

#### Skriv serverkoden

Serverkoden kan nå skrives i Python.

##### Oppgave - skriv serverkoden

Skriv serverkoden.

1. Fra terminalen eller kommandolinjen, kjør følgende inne i det virtuelle miljøet for å opprette en Python-fil kalt `app.py`:

    * Fra Windows, kjør:

        ```cmd
        type nul > app.py
        ```

    * På macOS eller Linux, kjør:

        ```cmd
        touch app.py
        ```

1. Åpne den gjeldende mappen i VS Code:

    ```sh
    code .
    ```

1. Når VS Code starter, vil det aktivere det virtuelle Python-miljøet. Dette vil bli rapportert i den nederste statuslinjen:

    ![VS Code viser det valgte virtuelle miljøet](../../../../../translated_images/no/vscode-virtual-env.8ba42e04c3d533cf.webp)

1. Hvis VS Code-terminalen allerede kjører når VS Code starter opp, vil den ikke ha det virtuelle miljøet aktivert i seg. Det enkleste er å avslutte terminalen ved å bruke **Kill the active terminal instance**-knappen:

    ![VS Code Kill the active terminal instance-knapp](../../../../../translated_images/no/vscode-kill-terminal.1cc4de7c6f25ee08.webp)

1. Start en ny VS Code-terminal ved å velge *Terminal -> New Terminal*, eller ved å trykke `` CTRL+` ``. Den nye terminalen vil laste det virtuelle miljøet, med aktiveringskommandoen som vises i terminalen. Navnet på det virtuelle miljøet (`.venv`) vil også være i prompten:

    ```output
    ➜  nightlight-server source .venv/bin/activate
    (.venv) ➜  nightlight 
    ```

1. Åpne `app.py`-filen fra VS Code-utforskeren og legg til følgende kode:

    ```python
    import json
    import time
    
    import paho.mqtt.client as mqtt
    
    id = '<ID>'
    
    client_telemetry_topic = id + '/telemetry'
    client_name = id + 'nightlight_server'
    
    mqtt_client = mqtt.Client(client_name)
    mqtt_client.connect('test.mosquitto.org')
    
    mqtt_client.loop_start()
    
    def handle_telemetry(client, userdata, message):
        payload = json.loads(message.payload.decode())
        print("Message received:", payload)
    
    mqtt_client.subscribe(client_telemetry_topic)
    mqtt_client.on_message = handle_telemetry
    
    while True:
        time.sleep(2)
    ```

    Erstatt `<ID>` på linje 6 med den unike ID-en du brukte da du opprettet enhetskoden din.

    ⚠️ Dette **må** være den samme ID-en som du brukte på enheten din, ellers vil ikke serverkoden abonnere eller publisere til riktig emne.

    Denne koden oppretter en MQTT-klient med et unikt navn og kobler til *test.mosquitto.org*-megleren. Den starter deretter en behandlingssløyfe som kjører i en bakgrunnstråd og lytter etter meldinger på alle abonnerte emner.

    Klienten abonnerer deretter på meldinger på telemetriemnet og definerer en funksjon som kalles når en melding mottas. Når en telemetrimelding mottas, kalles `handle_telemetry`-funksjonen, som skriver ut den mottatte meldingen til konsollen.

    Til slutt holder en uendelig sløyfe applikasjonen i gang. MQTT-klienten lytter til meldinger i en bakgrunnstråd og kjører så lenge hovedapplikasjonen kjører.

1. Fra VS Code-terminalen, kjør følgende for å kjøre Python-appen din:

    ```sh
    python app.py
    ```

    Appen vil begynne å lytte til meldinger fra IoT-enheten.

1. Sørg for at enheten din kjører og sender telemetrimeldinger. Juster lysnivåene som oppdages av din fysiske eller virtuelle enhet. Mottatte meldinger vil bli skrevet ut til terminalen.

    ```output
    (.venv) ➜  nightlight-server python app.py
    Message received: {'light': 0}
    Message received: {'light': 400}
    ```

    `app.py`-filen i nattlys-virtuelle miljøet må kjøre for at `app.py`-filen i nattlys-server-virtuelle miljøet skal motta de sendte meldingene.

> 💁 Du finner denne koden i [code-server/server](../../../../../1-getting-started/lessons/4-connect-internet/code-server/server)-mappen.

### Hvor ofte bør telemetri sendes?

En viktig vurdering med telemetri er hvor ofte data skal måles og sendes. Svaret er - det kommer an på. Hvis du måler ofte, kan du reagere raskere på endringer i målingene, men du bruker mer strøm, mer båndbredde, genererer mer data og trenger flere skyressurser for å behandle det. Du må måle ofte nok, men ikke for ofte.

For en termostat er det sannsynligvis mer enn nok å måle hvert par minutter, siden temperaturer ikke endrer seg så ofte. Hvis du bare måler én gang om dagen, kan du ende opp med å varme opp huset for nattens temperaturer midt på en solrik dag, mens hvis du måler hvert sekund, vil du ha tusenvis av unødvendig dupliserte temperaturmålinger som vil spise opp brukerens internettfart og båndbredde (et problem for folk med begrensede båndbreddeplaner), bruke mer strøm, som kan være et problem for batteridrevne enheter som fjernsensorer, og øke kostnadene for leverandørens skyressurser for behandling og lagring.

Hvis du overvåker data rundt en maskin i en fabrikk som, hvis den svikter, kan forårsake katastrofale skader og millioner av dollar i tapt inntekt, kan det være nødvendig å måle flere ganger i sekundet. Det er bedre å kaste bort båndbredde enn å gå glipp av telemetri som indikerer at en maskin må stoppes og fikses før den går i stykker.

> 💁 I denne situasjonen kan du vurdere å ha en edge-enhet for å behandle telemetrien først for å redusere avhengigheten av Internett.

### Tap av tilkobling

Internett-tilkoblinger kan være upålitelige, med vanlige avbrudd. Hva bør en IoT-enhet gjøre under slike omstendigheter - bør den miste dataene, eller bør den lagre dem til tilkoblingen er gjenopprettet? Igjen, svaret er det kommer an på.

For en termostat kan dataene sannsynligvis gå tapt så snart en ny temperaturmåling er tatt. Oppvarmingssystemet bryr seg ikke om at det for 20 minutter siden var 20,5°C hvis temperaturen nå er 19°C, det er temperaturen nå som avgjør om oppvarmingen skal være på eller av.

For maskiner kan du kanskje ønske å beholde dataene, spesielt hvis de brukes til å se etter trender. Det finnes maskinlæringsmodeller som kan oppdage avvik i datastrømmer ved å se over data fra en definert tidsperiode (for eksempel den siste timen) og oppdage unormale data. Dette brukes ofte til prediktivt vedlikehold, for å se etter indikasjoner på at noe kan gå i stykker snart, slik at du kan reparere eller erstatte det før det skjer. Du kan ønske at hver bit av telemetri for en maskin sendes slik at den kan behandles for avviksdeteksjon, så når IoT-enheten kan koble til igjen, vil den sende all telemetri generert under Internett-avbruddet.

IoT-enhetsdesignere bør også vurdere om IoT-enheten kan brukes under et Internett-avbrudd eller tap av signal forårsaket av plassering. En smart termostat bør kunne ta noen begrensede beslutninger for å kontrollere oppvarming hvis den ikke kan sende telemetri til skyen på grunn av et avbrudd.

[![Denne Ferrari-en ble ubrukelig fordi noen prøvde å oppgradere den under bakken der det ikke er mobildekning](../../../../../translated_images/no/bricked-car.dc38f8efadc6c59d76211f981a521efb300939283dee468f79503aae3ec67615.png)](https://twitter.com/internetofshit/status/1315736960082808832)

For MQTT å håndtere tap av tilkobling, må enheten og serverkoden være ansvarlig for å sikre meldingsoverføring hvis det er nødvendig, for eksempel ved å kreve at alle meldinger som sendes, besvares med tilleggsmeldinger på et svar-emne, og hvis ikke, blir de manuelt køet for å bli sendt på nytt senere.

## Kommandoer

Kommandoer er meldinger sendt fra skyen til en enhet, som instruerer den til å gjøre noe. Ofte innebærer dette å gi en slags utgang via en aktuator, men det kan være en instruksjon for selve enheten, som å starte på nytt eller samle inn ekstra telemetri og returnere det som svar på kommandoen.

![En Internett-tilkoblet termostat som mottar en kommando om å slå på oppvarmingen](../../../../../translated_images/no/commands.d6c06bbbb3a02cce95f2831a1c331daf6dedd4e470c4aa2b0ae54f332016e504.png)

En termostat kan motta en kommando fra skyen om å slå på oppvarmingen. Basert på telemetridataene fra alle sensorene, hvis skytjenesten har bestemt at oppvarmingen skal være på, sender den den relevante kommandoen.

### Send kommandoer til MQTT-megleren

Neste steg for vårt Internett-styrte nattlys er at serverkoden sender en kommando tilbake til IoT-enheten for å kontrollere lyset basert på lysnivåene den registrerer.

1. Åpne serverkoden i VS Code

1. Legg til følgende linje etter deklarasjonen av `client_telemetry_topic` for å definere hvilket emne kommandoer skal sendes til:

    ```python
    server_command_topic = id + '/commands'
    ```

1. Legg til følgende kode på slutten av `handle_telemetry`-funksjonen:

    ```python
    command = { 'led_on' : payload['light'] < 300 }
    print("Sending message:", command)
    
    client.publish(server_command_topic, json.dumps(command))
    ```

    Dette sender en JSON-melding til kommandoemnet med verdien `led_on` satt til true eller false avhengig av om lyset er mindre enn 300 eller ikke. Hvis lyset er mindre enn 300, sendes true for å instruere enheten om å slå på LED-en.

1. Kjør koden som før

1. Juster lysnivåene som registreres av din fysiske eller virtuelle enhet. Mottatte meldinger og sendte kommandoer vil bli skrevet ut til terminalen:

    ```output
    (.venv) ➜  nightlight-server python app.py
    Message received: {'light': 0}
    Sending message: {'led_on': True}
    Message received: {'light': 400}
    Sending message: {'led_on': False}
    ```

> 💁 Telemetrien og kommandoene sendes på ett enkelt emne hver. Dette betyr at telemetri fra flere enheter vil vises på samme telemetriemne, og kommandoer til flere enheter vil vises på samme kommandoemne. Hvis du ønsket å sende en kommando til en spesifikk enhet, kunne du bruke flere emner, navngitt med en unik enhets-ID, som `/commands/device1`, `/commands/device2`. På den måten kan en enhet lytte til meldinger som bare er ment for den ene enheten.

> 💁 Du finner denne koden i [code-commands/server](../../../../../1-getting-started/lessons/4-connect-internet/code-commands/server)-mappen.

### Håndter kommandoer på IoT-enheten

Nå som kommandoer sendes fra serveren, kan du legge til kode på IoT-enheten for å håndtere dem og kontrollere LED-en.

Følg det relevante steget nedenfor for å lytte til kommandoer fra MQTT-megleren:

* [Arduino - Wio Terminal](wio-terminal-commands.md)
* [Enkeltkortdatamaskin - Raspberry Pi/Virtual IoT-enhet](single-board-computer-commands.md)

Når denne koden er skrevet og kjører, eksperimenter med å endre lysnivåer. Se på utdataene fra serveren og enheten, og se på LED-en mens du endrer lysnivåer.

### Tap av tilkobling

Hva bør en skytjeneste gjøre hvis den trenger å sende en kommando til en IoT-enhet som er offline? Igjen, svaret er det kommer an på.

Hvis den nyeste kommandoen overstyrer en tidligere, kan de tidligere sannsynligvis ignoreres. Hvis en skytjeneste sender en kommando for å slå på oppvarmingen, og deretter sender en kommando for å slå den av, kan på-kommandoen ignoreres og ikke sendes på nytt.

Hvis kommandoene må behandles i rekkefølge, som å flytte en robotarm opp, deretter lukke en gripemekanisme, må de sendes i rekkefølge når tilkoblingen er gjenopprettet.

✅ Hvordan kan enheten eller serverkoden sikre at kommandoer alltid sendes og håndteres i rekkefølge over MQTT hvis det er nødvendig?

---

## 🚀 Utfordring

Utfordringen i de siste tre leksjonene var å liste opp så mange IoT-enheter som du kan finne i hjemmet, skolen eller arbeidsplassen din, og avgjøre om de er bygget rundt mikrokontrollere eller enkeltkortdatamaskiner, eller til og med en blanding av begge, og tenke på hvilke sensorer og aktuatorer de bruker.
For disse enhetene, tenk på hvilke meldinger de kan sende eller motta. Hvilken telemetri sender de? Hvilke meldinger eller kommandoer kan de motta? Tror du de er sikre?

## Quiz etter forelesning

[Quiz etter forelesning](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/8)

## Gjennomgang og selvstudium

Les mer om MQTT på [MQTT Wikipedia-siden](https://wikipedia.org/wiki/MQTT).

Prøv å kjøre en MQTT-broker selv ved å bruke [Mosquitto](https://www.mosquitto.org) og koble til den fra IoT-enheten din og serverkoden.

> 💁 Tips - som standard tillater ikke Mosquitto anonyme tilkoblinger (det vil si tilkoblinger uten brukernavn og passord), og tillater heller ikke tilkoblinger fra andre datamaskiner enn den det kjører på.  
> Du kan løse dette med en [`mosquitto.conf` konfigurasjonsfil](https://www.mosquitto.org/man/mosquitto-conf-5.html) med følgende:  
>
> ```sh
> listener 1883 0.0.0.0
> allow_anonymous true
> ```

## Oppgave

[Sammenlign og kontraster MQTT med andre kommunikasjonsprotokoller](assignment.md)

---

**Ansvarsfraskrivelse**:  
Dette dokumentet er oversatt ved hjelp av AI-oversettelsestjenesten [Co-op Translator](https://github.com/Azure/co-op-translator). Selv om vi streber etter nøyaktighet, vær oppmerksom på at automatiske oversettelser kan inneholde feil eller unøyaktigheter. Det originale dokumentet på sitt opprinnelige språk bør anses som den autoritative kilden. For kritisk informasjon anbefales profesjonell menneskelig oversettelse. Vi er ikke ansvarlige for misforståelser eller feiltolkninger som oppstår ved bruk av denne oversettelsen.