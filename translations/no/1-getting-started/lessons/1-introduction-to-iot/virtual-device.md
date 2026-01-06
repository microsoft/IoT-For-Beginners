<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "52b4de6144b2efdced7797a5339d6035",
  "translation_date": "2025-08-27T21:58:35+00:00",
  "source_file": "1-getting-started/lessons/1-introduction-to-iot/virtual-device.md",
  "language_code": "no"
}
-->
# Virtuell en-kort datamaskin

I stedet for å kjøpe en IoT-enhet sammen med sensorer og aktuatorer, kan du bruke datamaskinen din til å simulere IoT-maskinvare. [CounterFit-prosjektet](https://github.com/CounterFit-IoT/CounterFit) lar deg kjøre en app lokalt som simulerer IoT-maskinvare som sensorer og aktuatorer, og gir deg tilgang til sensorene og aktuatorene fra lokal Python-kode skrevet på samme måte som du ville gjort på en Raspberry Pi med fysisk maskinvare.

## Oppsett

For å bruke CounterFit må du installere gratis programvare på datamaskinen din.

### Oppgave

Installer nødvendig programvare.

1. Installer Python. Se [Python nedlastingssiden](https://www.python.org/downloads/) for instruksjoner om hvordan du installerer den nyeste versjonen av Python.

1. Installer Visual Studio Code (VS Code). Dette er editoren du vil bruke til å skrive kode for den virtuelle enheten i Python. Se [VS Code-dokumentasjonen](https://code.visualstudio.com?WT.mc_id=academic-17441-jabenn) for instruksjoner om hvordan du installerer VS Code.

    > 💁 Du står fritt til å bruke hvilken som helst Python IDE eller editor for disse leksjonene hvis du har et foretrukket verktøy, men leksjonene vil gi instruksjoner basert på bruk av VS Code.

1. Installer VS Code Pylance-utvidelsen. Dette er en utvidelse for VS Code som gir støtte for Python-språket. Se [Pylance-utvidelsesdokumentasjonen](https://marketplace.visualstudio.com/items?WT.mc_id=academic-17441-jabenn&itemName=ms-python.vscode-pylance) for instruksjoner om hvordan du installerer denne utvidelsen i VS Code.

Instruksjonene for å installere og konfigurere CounterFit-appen vil bli gitt på det relevante tidspunktet i oppgaveinstruksjonene, da den installeres per prosjekt.

## Hello world

Det er tradisjonelt når man starter med et nytt programmeringsspråk eller teknologi å lage en 'Hello World'-applikasjon - en liten applikasjon som viser tekst som `"Hello World"` for å bekrefte at alle verktøyene er riktig konfigurert.

Hello World-appen for den virtuelle IoT-maskinvaren vil sikre at du har Python og Visual Studio Code installert riktig. Den vil også koble til CounterFit for de virtuelle IoT-sensorene og aktuatorene. Den vil ikke bruke noen maskinvare, den vil bare koble til for å bekrefte at alt fungerer.

Denne appen vil ligge i en mappe kalt `nightlight`, og den vil bli gjenbrukt med forskjellig kode i senere deler av denne oppgaven for å bygge nattlys-applikasjonen.

### Konfigurer et virtuelt Python-miljø

En av de kraftige funksjonene i Python er muligheten til å installere [Pip-pakker](https://pypi.org) - dette er pakker med kode skrevet av andre og publisert på Internett. Du kan installere en Pip-pakke på datamaskinen din med én kommando, og deretter bruke den pakken i koden din. Du vil bruke Pip til å installere en pakke for å kommunisere med CounterFit.

Som standard, når du installerer en pakke, er den tilgjengelig overalt på datamaskinen din, og dette kan føre til problemer med pakkeversjoner - for eksempel at én applikasjon avhenger av én versjon av en pakke som slutter å fungere når du installerer en ny versjon for en annen applikasjon. For å unngå dette problemet kan du bruke et [virtuelt Python-miljø](https://docs.python.org/3/library/venv.html), som i hovedsak er en kopi av Python i en dedikert mappe, og når du installerer Pip-pakker, blir de kun installert i den mappen.

> 💁 Hvis du bruker en Raspberry Pi, har du ikke satt opp et virtuelt miljø på den enheten for å administrere Pip-pakker, i stedet bruker du globale pakker, da Grove-pakkene er installert globalt av installasjonsskriptet.

#### Oppgave - konfigurer et virtuelt Python-miljø

Konfigurer et virtuelt Python-miljø og installer Pip-pakkene for CounterFit.

1. Fra terminalen eller kommandolinjen, kjør følgende på et sted du velger for å opprette og navigere til en ny katalog:

    ```sh
    mkdir nightlight
    cd nightlight
    ```

1. Kjør deretter følgende for å opprette et virtuelt miljø i `.venv`-mappen:

    ```sh
    python3 -m venv .venv
    ```

    > 💁 Du må eksplisitt kalle `python3` for å opprette det virtuelle miljøet, i tilfelle du har Python 2 installert i tillegg til Python 3 (den nyeste versjonen). Hvis du har Python 2 installert, vil kall til `python` bruke Python 2 i stedet for Python 3.

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

            > Hvis du får en feil om at kjøring av skript er deaktivert på dette systemet, må du aktivere kjøring av skript ved å sette en passende kjøringspolicy. Du kan gjøre dette ved å starte PowerShell som administrator, og deretter kjøre følgende kommando:

            ```powershell
            Set-ExecutionPolicy -ExecutionPolicy Unrestricted
            ```

            Skriv `Y` når du blir bedt om å bekrefte. Start deretter PowerShell på nytt og prøv igjen.

            Du kan tilbakestille denne kjøringspolicyen på et senere tidspunkt hvis nødvendig. Du kan lese mer om dette på [Execution Policies-siden på Microsoft Docs](https://docs.microsoft.com/powershell/module/microsoft.powershell.core/about/about_execution_policies?WT.mc_id=academic-17441-jabenn).

    * På macOS eller Linux, kjør:

        ```cmd
        source ./.venv/bin/activate
        ```

    > 💁 Disse kommandoene bør kjøres fra samme sted som du kjørte kommandoen for å opprette det virtuelle miljøet. Du trenger aldri å navigere inn i `.venv`-mappen, du bør alltid kjøre aktiveringskommandoen og eventuelle kommandoer for å installere pakker eller kjøre kode fra mappen du var i da du opprettet det virtuelle miljøet.

1. Når det virtuelle miljøet er aktivert, vil standard `python`-kommandoen kjøre versjonen av Python som ble brukt til å opprette det virtuelle miljøet. Kjør følgende for å få versjonen:

    ```sh
    python --version
    ```

    Utdataene bør inneholde følgende:

    ```output
    (.venv) ➜  nightlight python --version
    Python 3.9.1
    ```

    > 💁 Python-versjonen din kan være annerledes - så lenge den er versjon 3.6 eller høyere er du klar. Hvis ikke, slett denne mappen, installer en nyere versjon av Python og prøv igjen.

1. Kjør følgende kommandoer for å installere Pip-pakkene for CounterFit. Disse pakkene inkluderer hovedappen CounterFit samt shims for Grove-maskinvare. Disse shimsene lar deg skrive kode som om du programmerte med fysiske sensorer og aktuatorer fra Grove-økosystemet, men koblet til virtuelle IoT-enheter.

    ```sh
    pip install CounterFit
    pip install counterfit-connection
    pip install counterfit-shims-grove
    ```

    Disse Pip-pakkene vil kun bli installert i det virtuelle miljøet, og vil ikke være tilgjengelige utenfor dette.

### Skriv koden

Når det virtuelle Python-miljøet er klart, kan du skrive koden for 'Hello World'-applikasjonen.

#### Oppgave - skriv koden

Opprett en Python-applikasjon for å skrive `"Hello World"` til konsollen.

1. Fra terminalen eller kommandolinjen, kjør følgende inne i det virtuelle miljøet for å opprette en Python-fil kalt `app.py`:

    * Fra Windows, kjør:

        ```cmd
        type nul > app.py
        ```

    * På macOS eller Linux, kjør:

        ```cmd
        touch app.py
        ```

1. Åpne den nåværende mappen i VS Code:

    ```sh
    code .
    ```

    > 💁 Hvis terminalen din returnerer `command not found` på macOS, betyr det at VS Code ikke har blitt lagt til PATH. Du kan legge til VS Code i PATH ved å følge instruksjonene i [Launching from the command line-delen av VS Code-dokumentasjonen](https://code.visualstudio.com/docs/setup/mac?WT.mc_id=academic-17441-jabenn#_launching-from-the-command-line) og kjøre kommandoen etterpå. VS Code legges til PATH som standard på Windows og Linux.

1. Når VS Code starter, vil det aktivere det virtuelle Python-miljøet. Det valgte virtuelle miljøet vil vises i statuslinjen nederst:

    ![VS Code viser det valgte virtuelle miljøet](../../../../../translated_images/vscode-virtual-env.8ba42e04c3d533cf.no.png)

1. Hvis VS Code-terminalen allerede kjører når VS Code starter opp, vil den ikke ha det virtuelle miljøet aktivert i seg. Det enkleste er å avslutte terminalen ved å bruke **Kill the active terminal instance**-knappen:

    ![VS Code Kill the active terminal instance-knappen](../../../../../translated_images/vscode-kill-terminal.1cc4de7c6f25ee08.no.png)

    Du kan se om terminalen har det virtuelle miljøet aktivert, da navnet på det virtuelle miljøet vil være et prefiks på terminalprompten. For eksempel kan det være:

    ```sh
    (.venv) ➜  nightlight
    ```

    Hvis du ikke har `.venv` som prefiks på prompten, er det virtuelle miljøet ikke aktivert i terminalen.

1. Start en ny VS Code-terminal ved å velge *Terminal -> New Terminal*, eller ved å trykke `` CTRL+` ``. Den nye terminalen vil laste det virtuelle miljøet, og kallet for å aktivere dette vil vises i terminalen. Prompten vil også ha navnet på det virtuelle miljøet (`.venv`):

    ```output
    ➜  nightlight source .venv/bin/activate
    (.venv) ➜  nightlight 
    ```

1. Åpne `app.py`-filen fra VS Code-utforskeren og legg til følgende kode:

    ```python
    print('Hello World!')
    ```

    `print`-funksjonen skriver det som sendes til den til konsollen.

1. Fra VS Code-terminalen, kjør følgende for å kjøre Python-appen din:

    ```sh
    python app.py
    ```

    Følgende vil være i utdataene:

    ```output
    (.venv) ➜  nightlight python app.py 
    Hello World!
    ```

😀 'Hello World'-programmet ditt var en suksess!

### Koble til 'maskinvaren'

Som et andre 'Hello World'-steg, vil du kjøre CounterFit-appen og koble koden din til den. Dette er den virtuelle ekvivalenten til å koble til IoT-maskinvare til et utviklingskort.

#### Oppgave - koble til 'maskinvaren'

1. Fra VS Code-terminalen, start CounterFit-appen med følgende kommando:

    ```sh
    counterfit
    ```

    Appen vil starte og åpne i nettleseren din:

    ![CounterFit-appen kjører i en nettleser](../../../../../translated_images/counterfit-first-run.433326358b669b31d0e99c3513cb01bfbb13724d162c99cdcc8f51ecf5f9c779.no.png)

    Den vil være merket som *Disconnected*, med LED-en øverst til høyre slått av.

1. Legg til følgende kode øverst i `app.py`:

    ```python
    from counterfit_connection import CounterFitConnection
    CounterFitConnection.init('127.0.0.1', 5000)
    ```

    Denne koden importerer `CounterFitConnection`-klassen fra `counterfit_connection`-modulen, som kommer fra `counterfit-connection` Pip-pakken du installerte tidligere. Den initialiserer deretter en tilkobling til CounterFit-appen som kjører på `127.0.0.1`, som er en IP-adresse du alltid kan bruke for å få tilgang til din lokale datamaskin (ofte referert til som *localhost*), på port 5000.

    > 💁 Hvis du har andre apper som kjører på port 5000, kan du endre dette ved å oppdatere porten i koden og kjøre CounterFit ved å bruke `CounterFit --port <port_number>`, der `<port_number>` erstattes med porten du vil bruke.

1. Du må starte en ny VS Code-terminal ved å velge **Create a new integrated terminal**-knappen. Dette er fordi CounterFit-appen kjører i den nåværende terminalen.

    ![VS Code Create a new integrated terminal-knappen](../../../../../translated_images/vscode-new-terminal.77db8fc0f9cd3182.no.png)

1. I denne nye terminalen, kjør `app.py`-filen som før. Statusen til CounterFit vil endres til **Connected**, og LED-en vil lyse opp.

    ![CounterFit viser som tilkoblet](../../../../../translated_images/counterfit-connected.ed30b46d8f79b0921f3fc70be10366e596a89dca3f80c2224a9d9fc98fccf884.no.png)

> 💁 Du kan finne denne koden i [code/virtual-device](../../../../../1-getting-started/lessons/1-introduction-to-iot/code/virtual-device)-mappen.

😀 Tilkoblingen til maskinvaren var en suksess!

---

**Ansvarsfraskrivelse**:  
Dette dokumentet er oversatt ved hjelp av AI-oversettelsestjenesten [Co-op Translator](https://github.com/Azure/co-op-translator). Selv om vi streber etter nøyaktighet, vær oppmerksom på at automatiserte oversettelser kan inneholde feil eller unøyaktigheter. Det originale dokumentet på sitt opprinnelige språk bør anses som den autoritative kilden. For kritisk informasjon anbefales profesjonell menneskelig oversettelse. Vi er ikke ansvarlige for misforståelser eller feiltolkninger som oppstår ved bruk av denne oversettelsen.