<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "52b4de6144b2efdced7797a5339d6035",
  "translation_date": "2025-08-27T21:58:04+00:00",
  "source_file": "1-getting-started/lessons/1-introduction-to-iot/virtual-device.md",
  "language_code": "da"
}
-->
# Virtuel single-board computer

I stedet for at købe en IoT-enhed sammen med sensorer og aktuatorer, kan du bruge din computer til at simulere IoT-hardware. [CounterFit-projektet](https://github.com/CounterFit-IoT/CounterFit) giver dig mulighed for at køre en app lokalt, der simulerer IoT-hardware såsom sensorer og aktuatorer, og få adgang til sensorer og aktuatorer fra lokal Python-kode, som er skrevet på samme måde som den kode, du ville skrive på en Raspberry Pi med fysisk hardware.

## Opsætning

For at bruge CounterFit skal du installere noget gratis software på din computer.

### Opgave

Installer den nødvendige software.

1. Installer Python. Se [Python downloads-siden](https://www.python.org/downloads/) for instruktioner om, hvordan du installerer den nyeste version af Python.

1. Installer Visual Studio Code (VS Code). Dette er den editor, du vil bruge til at skrive din virtuelle enhedskode i Python. Se [VS Code-dokumentationen](https://code.visualstudio.com?WT.mc_id=academic-17441-jabenn) for instruktioner om, hvordan du installerer VS Code.

    > 💁 Du er fri til at bruge enhver Python IDE eller editor til disse lektioner, hvis du har et foretrukket værktøj, men lektionerne vil give instruktioner baseret på brugen af VS Code.

1. Installer VS Code Pylance-udvidelsen. Dette er en udvidelse til VS Code, der giver understøttelse af Python-sproget. Se [Pylance-udvidelsesdokumentationen](https://marketplace.visualstudio.com/items?WT.mc_id=academic-17441-jabenn&itemName=ms-python.vscode-pylance) for instruktioner om, hvordan du installerer denne udvidelse i VS Code.

Instruktionerne til at installere og konfigurere CounterFit-appen vil blive givet på det relevante tidspunkt i opgaveinstruktionerne, da den installeres på projektbasis.

## Hello world

Det er traditionelt, når man starter med et nyt programmeringssprog eller en ny teknologi, at lave en 'Hello World'-applikation - en lille applikation, der viser noget som teksten `"Hello World"` for at demonstrere, at alle værktøjer er korrekt konfigureret.

Hello World-appen for den virtuelle IoT-hardware vil sikre, at du har Python og Visual Studio Code korrekt installeret. Den vil også oprette forbindelse til CounterFit for de virtuelle IoT-sensorer og aktuatorer. Den vil ikke bruge nogen hardware, den vil blot oprette forbindelse for at bevise, at alt fungerer.

Denne app vil være i en mappe kaldet `nightlight`, og den vil blive genbrugt med forskellig kode i senere dele af denne opgave for at bygge natlampe-applikationen.

### Konfigurer et Python-virtuelt miljø

En af de kraftfulde funktioner i Python er muligheden for at installere [Pip-pakker](https://pypi.org) - dette er pakker med kode skrevet af andre og offentliggjort på internettet. Du kan installere en Pip-pakke på din computer med én kommando og derefter bruge den pakke i din kode. Du vil bruge Pip til at installere en pakke til at kommunikere med CounterFit.

Som standard, når du installerer en pakke, er den tilgængelig overalt på din computer, og dette kan føre til problemer med pakkeversioner - såsom en applikation, der afhænger af én version af en pakke, som bryder, når du installerer en ny version til en anden applikation. For at omgå dette problem kan du bruge et [Python-virtuelt miljø](https://docs.python.org/3/library/venv.html), som i bund og grund er en kopi af Python i en dedikeret mappe, og når du installerer Pip-pakker, bliver de kun installeret i den mappe.

> 💁 Hvis du bruger en Raspberry Pi, har du ikke oprettet et virtuelt miljø på den enhed til at administrere Pip-pakker, i stedet bruger du globale pakker, da Grove-pakkerne er installeret globalt af installationsscriptet.

#### Opgave - konfigurer et Python-virtuelt miljø

Konfigurer et Python-virtuelt miljø og installer Pip-pakkerne til CounterFit.

1. Fra din terminal eller kommandolinje skal du køre følgende på et sted efter eget valg for at oprette og navigere til en ny mappe:

    ```sh
    mkdir nightlight
    cd nightlight
    ```

1. Kør nu følgende for at oprette et virtuelt miljø i `.venv`-mappen:

    ```sh
    python3 -m venv .venv
    ```

    > 💁 Du skal eksplicit kalde `python3` for at oprette det virtuelle miljø, i tilfælde af at du har Python 2 installeret ud over Python 3 (den nyeste version). Hvis du har Python 2 installeret, vil kaldet `python` bruge Python 2 i stedet for Python 3.

1. Aktiver det virtuelle miljø:

    * På Windows:
        * Hvis du bruger Command Prompt eller Command Prompt gennem Windows Terminal, skal du køre:

            ```cmd
            .venv\Scripts\activate.bat
            ```

        * Hvis du bruger PowerShell, skal du køre:

            ```powershell
            .\.venv\Scripts\Activate.ps1
            ```

            > Hvis du får en fejl om, at kørsel af scripts er deaktiveret på dette system, skal du aktivere kørsel af scripts ved at indstille en passende eksekveringspolitik. Du kan gøre dette ved at starte PowerShell som administrator og derefter køre følgende kommando:

            ```powershell
            Set-ExecutionPolicy -ExecutionPolicy Unrestricted
            ```

            Indtast `Y`, når du bliver bedt om at bekræfte. Genstart derefter PowerShell og prøv igen.

            Du kan nulstille denne eksekveringspolitik på et senere tidspunkt, hvis det er nødvendigt. Du kan læse mere om dette på [Execution Policies-siden på Microsoft Docs](https://docs.microsoft.com/powershell/module/microsoft.powershell.core/about/about_execution_policies?WT.mc_id=academic-17441-jabenn).

    * På macOS eller Linux skal du køre:

        ```cmd
        source ./.venv/bin/activate
        ```

    > 💁 Disse kommandoer skal køres fra samme placering, som du kørte kommandoen for at oprette det virtuelle miljø. Du behøver aldrig navigere ind i `.venv`-mappen, du skal altid køre aktiveringskommandoen og eventuelle kommandoer for at installere pakker eller køre kode fra den mappe, du var i, da du oprettede det virtuelle miljø.

1. Når det virtuelle miljø er aktiveret, vil standardkommandoen `python` køre den version af Python, der blev brugt til at oprette det virtuelle miljø. Kør følgende for at få versionen:

    ```sh
    python --version
    ```

    Outputtet skal indeholde følgende:

    ```output
    (.venv) ➜  nightlight python --version
    Python 3.9.1
    ```

    > 💁 Din Python-version kan være anderledes - så længe det er version 3.6 eller højere, er du godt kørende. Hvis ikke, skal du slette denne mappe, installere en nyere version af Python og prøve igen.

1. Kør følgende kommandoer for at installere Pip-pakkerne til CounterFit. Disse pakker inkluderer hovedappen CounterFit samt shims til Grove-hardware. Disse shims giver dig mulighed for at skrive kode, som om du programmerede med fysiske sensorer og aktuatorer fra Grove-økosystemet, men forbundet til virtuelle IoT-enheder.

    ```sh
    pip install CounterFit
    pip install counterfit-connection
    pip install counterfit-shims-grove
    ```

    Disse Pip-pakker vil kun blive installeret i det virtuelle miljø og vil ikke være tilgængelige uden for dette.

### Skriv koden

Når det virtuelle Python-miljø er klar, kan du skrive koden til 'Hello World'-applikationen.

#### Opgave - skriv koden

Opret en Python-applikation, der udskriver `"Hello World"` til konsollen.

1. Fra din terminal eller kommandolinje skal du køre følgende inde i det virtuelle miljø for at oprette en Python-fil kaldet `app.py`:

    * Fra Windows skal du køre:

        ```cmd
        type nul > app.py
        ```

    * På macOS eller Linux skal du køre:

        ```cmd
        touch app.py
        ```

1. Åbn den aktuelle mappe i VS Code:

    ```sh
    code .
    ```

    > 💁 Hvis din terminal returnerer `command not found` på macOS, betyder det, at VS Code ikke er blevet tilføjet til din PATH. Du kan tilføje VS Code til din PATH ved at følge instruktionerne i [Launching from the command line-sektionen i VS Code-dokumentationen](https://code.visualstudio.com/docs/setup/mac?WT.mc_id=academic-17441-jabenn#_launching-from-the-command-line) og derefter køre kommandoen igen. VS Code tilføjes som standard til din PATH på Windows og Linux.

1. Når VS Code starter, vil det aktivere det virtuelle Python-miljø. Det valgte virtuelle miljø vil vises i den nederste statuslinje:

    ![VS Code viser det valgte virtuelle miljø](../../../../../translated_images/da/vscode-virtual-env.8ba42e04c3d533cf.webp)

1. Hvis VS Code-terminalen allerede kører, når VS Code starter op, vil den ikke have det virtuelle miljø aktiveret i sig. Det nemmeste er at lukke terminalen ved at bruge knappen **Kill the active terminal instance**:

    ![VS Code Kill the active terminal instance-knap](../../../../../translated_images/da/vscode-kill-terminal.1cc4de7c6f25ee08.webp)

    Du kan se, om terminalen har det virtuelle miljø aktiveret, da navnet på det virtuelle miljø vil være et præfiks på terminalprompten. For eksempel kan det være:

    ```sh
    (.venv) ➜  nightlight
    ```

    Hvis du ikke har `.venv` som præfiks på prompten, er det virtuelle miljø ikke aktivt i terminalen.

1. Start en ny VS Code-terminal ved at vælge *Terminal -> New Terminal*, eller ved at trykke på `` CTRL+` ``. Den nye terminal vil indlæse det virtuelle miljø, og kaldet til at aktivere dette vil vises i terminalen. Prompten vil også have navnet på det virtuelle miljø (`.venv`):

    ```output
    ➜  nightlight source .venv/bin/activate
    (.venv) ➜  nightlight 
    ```

1. Åbn `app.py`-filen fra VS Code-udforskeren og tilføj følgende kode:

    ```python
    print('Hello World!')
    ```

    `print`-funktionen udskriver det, der bliver sendt til den, til konsollen.

1. Fra VS Code-terminalen skal du køre følgende for at køre din Python-app:

    ```sh
    python app.py
    ```

    Følgende vil være i outputtet:

    ```output
    (.venv) ➜  nightlight python app.py 
    Hello World!
    ```

😀 Dit 'Hello World'-program var en succes!

### Tilslut 'hardwaren'

Som et andet 'Hello World'-trin vil du køre CounterFit-appen og forbinde din kode til den. Dette er den virtuelle ækvivalent til at tilslutte noget IoT-hardware til et udviklingskit.

#### Opgave - tilslut 'hardwaren'

1. Fra VS Code-terminalen skal du starte CounterFit-appen med følgende kommando:

    ```sh
    counterfit
    ```

    Appen vil begynde at køre og åbne i din webbrowser:

    ![CounterFit-appen kører i en browser](../../../../../translated_images/da/counterfit-first-run.433326358b669b31d0e99c3513cb01bfbb13724d162c99cdcc8f51ecf5f9c779.png)

    Den vil være markeret som *Disconnected*, med LED'en i øverste højre hjørne slukket.

1. Tilføj følgende kode til toppen af `app.py`:

    ```python
    from counterfit_connection import CounterFitConnection
    CounterFitConnection.init('127.0.0.1', 5000)
    ```

    Denne kode importerer `CounterFitConnection`-klassen fra modulet `counterfit_connection`, som kommer fra Pip-pakken `counterfit-connection`, du installerede tidligere. Den initialiserer derefter en forbindelse til CounterFit-appen, der kører på `127.0.0.1`, som er en IP-adresse, du altid kan bruge til at få adgang til din lokale computer (ofte kaldet *localhost*), på port 5000.

    > 💁 Hvis du har andre apps, der kører på port 5000, kan du ændre dette ved at opdatere porten i koden og køre CounterFit ved hjælp af `CounterFit --port <port_number>`, hvor `<port_number>` erstattes med den port, du vil bruge.

1. Du skal starte en ny VS Code-terminal ved at vælge knappen **Create a new integrated terminal**. Dette skyldes, at CounterFit-appen kører i den aktuelle terminal.

    ![VS Code Create a new integrated terminal-knap](../../../../../translated_images/da/vscode-new-terminal.77db8fc0f9cd3182.webp)

1. I denne nye terminal skal du køre `app.py`-filen som før. Status for CounterFit vil ændre sig til **Connected**, og LED'en vil lyse op.

    ![CounterFit viser som connected](../../../../../translated_images/da/counterfit-connected.ed30b46d8f79b0921f3fc70be10366e596a89dca3f80c2224a9d9fc98fccf884.png)

> 💁 Du kan finde denne kode i [code/virtual-device](../../../../../1-getting-started/lessons/1-introduction-to-iot/code/virtual-device)-mappen.

😀 Din forbindelse til hardwaren var en succes!

---

**Ansvarsfraskrivelse**:  
Dette dokument er blevet oversat ved hjælp af AI-oversættelsestjenesten [Co-op Translator](https://github.com/Azure/co-op-translator). Selvom vi bestræber os på nøjagtighed, skal du være opmærksom på, at automatiserede oversættelser kan indeholde fejl eller unøjagtigheder. Det originale dokument på dets oprindelige sprog bør betragtes som den autoritative kilde. For kritisk information anbefales professionel menneskelig oversættelse. Vi påtager os ikke ansvar for eventuelle misforståelser eller fejltolkninger, der måtte opstå som følge af brugen af denne oversættelse.