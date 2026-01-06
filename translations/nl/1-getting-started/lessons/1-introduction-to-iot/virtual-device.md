<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "52b4de6144b2efdced7797a5339d6035",
  "translation_date": "2025-08-27T22:01:43+00:00",
  "source_file": "1-getting-started/lessons/1-introduction-to-iot/virtual-device.md",
  "language_code": "nl"
}
-->
# Virtuele single-board computer

In plaats van een IoT-apparaat te kopen, samen met sensoren en actuatoren, kun je je computer gebruiken om IoT-hardware te simuleren. Het [CounterFit-project](https://github.com/CounterFit-IoT/CounterFit) stelt je in staat om lokaal een app uit te voeren die IoT-hardware zoals sensoren en actuatoren simuleert. Je kunt vervolgens toegang krijgen tot deze sensoren en actuatoren vanuit lokale Python-code, geschreven op dezelfde manier als je zou doen op een Raspberry Pi met fysieke hardware.

## Installatie

Om CounterFit te gebruiken, moet je enkele gratis softwareprogramma's op je computer installeren.

### Taak

Installeer de benodigde software.

1. Installeer Python. Raadpleeg de [Python-downloadpagina](https://www.python.org/downloads/) voor instructies over het installeren van de nieuwste versie van Python.

1. Installeer Visual Studio Code (VS Code). Dit is de editor die je zult gebruiken om je virtuele apparaatcode in Python te schrijven. Raadpleeg de [VS Code-documentatie](https://code.visualstudio.com?WT.mc_id=academic-17441-jabenn) voor instructies over het installeren van VS Code.

    > 💁 Je bent vrij om een andere Python-IDE of editor te gebruiken als je een voorkeur hebt, maar de lessen geven instructies op basis van het gebruik van VS Code.

1. Installeer de VS Code Pylance-extensie. Dit is een extensie voor VS Code die ondersteuning biedt voor de Python-taal. Raadpleeg de [Pylance-extensiedocumentatie](https://marketplace.visualstudio.com/items?WT.mc_id=academic-17441-jabenn&itemName=ms-python.vscode-pylance) voor instructies over het installeren van deze extensie in VS Code.

De instructies voor het installeren en configureren van de CounterFit-app worden gegeven op het relevante moment in de opdrachtinstructies, omdat deze per project wordt geïnstalleerd.

## Hello World

Het is gebruikelijk om bij het starten met een nieuwe programmeertaal of technologie een 'Hello World'-applicatie te maken - een kleine applicatie die iets als de tekst `"Hello World"` uitvoert om te laten zien dat alle tools correct zijn geconfigureerd.

De Hello World-app voor de virtuele IoT-hardware zorgt ervoor dat je Python en Visual Studio Code correct hebt geïnstalleerd. Het zal ook verbinding maken met CounterFit voor de virtuele IoT-sensoren en -actuatoren. Het gebruikt geen hardware, maar maakt alleen verbinding om te bewijzen dat alles werkt.

Deze app wordt opgeslagen in een map genaamd `nightlight` en zal later in deze opdracht opnieuw worden gebruikt met andere code om de nightlight-applicatie te bouwen.

### Een Python virtuele omgeving configureren

Een van de krachtige functies van Python is de mogelijkheid om [Pip-pakketten](https://pypi.org) te installeren - dit zijn pakketten met code die door anderen zijn geschreven en op internet zijn gepubliceerd. Je kunt een Pip-pakket met één opdracht op je computer installeren en dat pakket vervolgens in je code gebruiken. Je zult Pip gebruiken om een pakket te installeren om met CounterFit te communiceren.

Standaard is een geïnstalleerd pakket overal op je computer beschikbaar, wat kan leiden tot problemen met pakketversies - bijvoorbeeld wanneer een applicatie afhankelijk is van een bepaalde versie van een pakket die niet werkt met een nieuwere versie die je voor een andere applicatie hebt geïnstalleerd. Om dit probleem te omzeilen, kun je een [Python virtuele omgeving](https://docs.python.org/3/library/venv.html) gebruiken, in feite een kopie van Python in een specifieke map. Wanneer je Pip-pakketten installeert, worden deze alleen in die map geïnstalleerd.

> 💁 Als je een Raspberry Pi gebruikt, heb je geen virtuele omgeving ingesteld op dat apparaat om Pip-pakketten te beheren. In plaats daarvan gebruik je globale pakketten, omdat de Grove-pakketten globaal worden geïnstalleerd door het installatiescript.

#### Taak - een Python virtuele omgeving configureren

Configureer een Python virtuele omgeving en installeer de Pip-pakketten voor CounterFit.

1. Voer vanuit je terminal of opdrachtregel het volgende uit op een locatie naar keuze om een nieuwe map te maken en ernaartoe te navigeren:

    ```sh
    mkdir nightlight
    cd nightlight
    ```

1. Voer nu het volgende uit om een virtuele omgeving te maken in de map `.venv`:

    ```sh
    python3 -m venv .venv
    ```

    > 💁 Je moet expliciet `python3` aanroepen om de virtuele omgeving te maken, voor het geval je Python 2 naast Python 3 (de nieuwste versie) hebt geïnstalleerd. Als je Python 2 hebt geïnstalleerd, zal het aanroepen van `python` Python 2 gebruiken in plaats van Python 3.

1. Activeer de virtuele omgeving:

    * Op Windows:
        * Als je de Command Prompt of de Command Prompt via Windows Terminal gebruikt, voer dan het volgende uit:

            ```cmd
            .venv\Scripts\activate.bat
            ```

        * Als je PowerShell gebruikt, voer dan het volgende uit:

            ```powershell
            .\.venv\Scripts\Activate.ps1
            ```

            > Als je een foutmelding krijgt over het uitschakelen van scripts op dit systeem, moet je het uitvoeren van scripts inschakelen door een geschikte uitvoeringsbeleid in te stellen. Dit kun je doen door PowerShell als beheerder te starten en het volgende commando uit te voeren:

            ```powershell
            Set-ExecutionPolicy -ExecutionPolicy Unrestricted
            ```

            Voer `Y` in wanneer je wordt gevraagd om te bevestigen. Start vervolgens PowerShell opnieuw en probeer het opnieuw.

            Je kunt dit uitvoeringsbeleid later opnieuw instellen als dat nodig is. Meer informatie hierover vind je op de [pagina over uitvoeringsbeleid op Microsoft Docs](https://docs.microsoft.com/powershell/module/microsoft.powershell.core/about/about_execution_policies?WT.mc_id=academic-17441-jabenn).

    * Op macOS of Linux, voer het volgende uit:

        ```cmd
        source ./.venv/bin/activate
        ```

    > 💁 Deze opdrachten moeten worden uitgevoerd vanuit dezelfde locatie waar je de opdracht hebt uitgevoerd om de virtuele omgeving te maken. Je hoeft nooit naar de `.venv`-map te navigeren. Je moet altijd de activeringsopdracht en eventuele opdrachten om pakketten te installeren of code uit te voeren uitvoeren vanuit de map waar je de virtuele omgeving hebt gemaakt.

1. Zodra de virtuele omgeving is geactiveerd, zal de standaard `python`-opdracht de versie van Python uitvoeren die is gebruikt om de virtuele omgeving te maken. Voer het volgende uit om de versie te controleren:

    ```sh
    python --version
    ```

    De uitvoer moet het volgende bevatten:

    ```output
    (.venv) ➜  nightlight python --version
    Python 3.9.1
    ```

    > 💁 Je Python-versie kan anders zijn - zolang het versie 3.6 of hoger is, zit je goed. Zo niet, verwijder dan deze map, installeer een nieuwere versie van Python en probeer het opnieuw.

1. Voer de volgende opdrachten uit om de Pip-pakketten voor CounterFit te installeren. Deze pakketten omvatten de hoofdapp CounterFit en shims voor Grove-hardware. Deze shims stellen je in staat om code te schrijven alsof je fysieke sensoren en actuatoren uit het Grove-ecosysteem programmeert, maar dan verbonden met virtuele IoT-apparaten.

    ```sh
    pip install CounterFit
    pip install counterfit-connection
    pip install counterfit-shims-grove
    ```

    Deze Pip-pakketten worden alleen in de virtuele omgeving geïnstalleerd en zijn niet beschikbaar buiten deze omgeving.

### Schrijf de code

Zodra de Python virtuele omgeving klaar is, kun je de code schrijven voor de 'Hello World'-applicatie.

#### Taak - schrijf de code

Maak een Python-applicatie om `"Hello World"` naar de console te printen.

1. Voer vanuit je terminal of opdrachtregel het volgende uit binnen de virtuele omgeving om een Python-bestand genaamd `app.py` te maken:

    * Op Windows voer je uit:

        ```cmd
        type nul > app.py
        ```

    * Op macOS of Linux voer je uit:

        ```cmd
        touch app.py
        ```

1. Open de huidige map in VS Code:

    ```sh
    code .
    ```

    > 💁 Als je terminal `command not found` retourneert op macOS, betekent dit dat VS Code niet aan je PATH is toegevoegd. Je kunt VS Code aan je PATH toevoegen door de instructies te volgen in de [sectie over starten vanaf de opdrachtregel in de VS Code-documentatie](https://code.visualstudio.com/docs/setup/mac?WT.mc_id=academic-17441-jabenn#_launching-from-the-command-line) en daarna het commando opnieuw uit te voeren. Op Windows en Linux wordt VS Code standaard aan je PATH toegevoegd.

1. Wanneer VS Code wordt gestart, activeert het de Python virtuele omgeving. De geselecteerde virtuele omgeving verschijnt in de onderste statusbalk:

    ![VS Code toont de geselecteerde virtuele omgeving](../../../../../translated_images/vscode-virtual-env.8ba42e04c3d533cf.nl.png)

1. Als de VS Code Terminal al actief is wanneer VS Code wordt gestart, zal de virtuele omgeving niet geactiveerd zijn in de terminal. Het eenvoudigste is om de terminal te sluiten met de knop **Kill the active terminal instance**:

    ![VS Code Kill the active terminal instance-knop](../../../../../translated_images/vscode-kill-terminal.1cc4de7c6f25ee08.nl.png)

    Je kunt zien of de terminal de virtuele omgeving heeft geactiveerd, omdat de naam van de virtuele omgeving een prefix is op de terminalprompt. Bijvoorbeeld, het kan zijn:

    ```sh
    (.venv) ➜  nightlight
    ```

    Als je geen `.venv` als prefix op de prompt hebt, is de virtuele omgeving niet actief in de terminal.

1. Start een nieuwe VS Code Terminal door *Terminal -> New Terminal* te selecteren of door `` CTRL+` `` in te drukken. De nieuwe terminal zal de virtuele omgeving laden en de activeringsopdracht zal in de terminal verschijnen. De prompt zal ook de naam van de virtuele omgeving (`.venv`) bevatten:

    ```output
    ➜  nightlight source .venv/bin/activate
    (.venv) ➜  nightlight 
    ```

1. Open het bestand `app.py` vanuit de VS Code-verkenner en voeg de volgende code toe:

    ```python
    print('Hello World!')
    ```

    De functie `print` print alles wat eraan wordt doorgegeven naar de console.

1. Voer vanuit de VS Code-terminal het volgende uit om je Python-app uit te voeren:

    ```sh
    python app.py
    ```

    De volgende uitvoer zal verschijnen:

    ```output
    (.venv) ➜  nightlight python app.py 
    Hello World!
    ```

😀 Je 'Hello World'-programma is een succes!

### Verbind de 'hardware'

Als een tweede 'Hello World'-stap ga je de CounterFit-app uitvoeren en je code ermee verbinden. Dit is het virtuele equivalent van het aansluiten van IoT-hardware op een ontwikkelkit.

#### Taak - verbind de 'hardware'

1. Start vanuit de VS Code-terminal de CounterFit-app met het volgende commando:

    ```sh
    counterfit
    ```

    De app zal starten en openen in je webbrowser:

    ![De CounterFit-app draait in een browser](../../../../../translated_images/counterfit-first-run.433326358b669b31d0e99c3513cb01bfbb13724d162c99cdcc8f51ecf5f9c779.nl.png)

    Het zal worden gemarkeerd als *Disconnected*, met de LED in de rechterbovenhoek uitgeschakeld.

1. Voeg de volgende code toe aan het begin van `app.py`:

    ```python
    from counterfit_connection import CounterFitConnection
    CounterFitConnection.init('127.0.0.1', 5000)
    ```

    Deze code importeert de `CounterFitConnection`-klasse uit de `counterfit_connection`-module, die afkomstig is uit het eerder geïnstalleerde `counterfit-connection` Pip-pakket. Vervolgens initialiseert het een verbinding met de CounterFit-app die draait op `127.0.0.1`, een IP-adres dat altijd kan worden gebruikt om toegang te krijgen tot je lokale computer (vaak aangeduid als *localhost*), op poort 5000.

    > 💁 Als je andere apps hebt die draaien op poort 5000, kun je dit wijzigen door de poort in de code bij te werken en CounterFit uit te voeren met `CounterFit --port <port_number>`, waarbij `<port_number>` wordt vervangen door de gewenste poort.

1. Je moet een nieuwe VS Code-terminal starten door de knop **Create a new integrated terminal** te selecteren. Dit komt omdat de CounterFit-app draait in de huidige terminal.

    ![VS Code Create a new integrated terminal-knop](../../../../../translated_images/vscode-new-terminal.77db8fc0f9cd3182.nl.png)

1. Voer in deze nieuwe terminal het bestand `app.py` uit zoals eerder. De status van CounterFit zal veranderen naar **Connected** en de LED zal oplichten.

    ![CounterFit toont als verbonden](../../../../../translated_images/counterfit-connected.ed30b46d8f79b0921f3fc70be10366e596a89dca3f80c2224a9d9fc98fccf884.nl.png)

> 💁 Je kunt deze code vinden in de [code/virtual-device](../../../../../1-getting-started/lessons/1-introduction-to-iot/code/virtual-device)-map.

😀 Je verbinding met de hardware is een succes!

---

**Disclaimer**:  
Dit document is vertaald met behulp van de AI-vertalingsservice [Co-op Translator](https://github.com/Azure/co-op-translator). Hoewel we streven naar nauwkeurigheid, dient u zich ervan bewust te zijn dat geautomatiseerde vertalingen fouten of onnauwkeurigheden kunnen bevatten. Het originele document in zijn oorspronkelijke taal moet worden beschouwd als de gezaghebbende bron. Voor cruciale informatie wordt professionele menselijke vertaling aanbevolen. Wij zijn niet aansprakelijk voor eventuele misverstanden of verkeerde interpretaties die voortvloeien uit het gebruik van deze vertaling.