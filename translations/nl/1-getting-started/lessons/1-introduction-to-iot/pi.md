<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "8ff0d0a1d29832bb896b9c103b69a452",
  "translation_date": "2025-08-27T22:04:20+00:00",
  "source_file": "1-getting-started/lessons/1-introduction-to-iot/pi.md",
  "language_code": "nl"
}
-->
# Raspberry Pi

De [Raspberry Pi](https://raspberrypi.org) is een single-board computer. Je kunt sensoren en actuatoren toevoegen met behulp van een breed scala aan apparaten en ecosystemen, en voor deze lessen gebruik je een hardware-ecosysteem genaamd [Grove](https://www.seeedstudio.com/category/Grove-c-1003.html). Je programmeert je Pi en hebt toegang tot de Grove-sensoren met Python.

![Een Raspberry Pi 4](../../../../../translated_images/raspberry-pi-4.fd4590d308c3d456.nl.jpg)

## Installatie

Als je een Raspberry Pi gebruikt als je IoT-hardware, heb je twee keuzes: je kunt alle lessen doorlopen en rechtstreeks op de Pi programmeren, of je kunt op afstand verbinding maken met een 'headless' Pi en vanaf je computer programmeren.

Voordat je begint, moet je ook de Grove Base Hat aansluiten op je Pi.

### Taak - installatie

Installeer de Grove Base Hat op je Pi en configureer de Pi.

1. Sluit de Grove Base Hat aan op je Pi. De socket op de hat past over alle GPIO-pinnen van de Pi en schuift helemaal naar beneden om stevig op de basis te zitten. Het bedekt de Pi volledig.

    ![De Grove Hat aansluiten](../../../../../images/pi-grove-hat-fitting.gif)

1. Bepaal hoe je je Pi wilt programmeren en ga naar het relevante gedeelte hieronder:

    * [Rechtstreeks werken op je Pi](../../../../../1-getting-started/lessons/1-introduction-to-iot)
    * [Op afstand toegang krijgen om de Pi te programmeren](../../../../../1-getting-started/lessons/1-introduction-to-iot)

### Rechtstreeks werken op je Pi

Als je rechtstreeks op je Pi wilt werken, kun je de desktopversie van Raspberry Pi OS gebruiken en alle benodigde tools installeren.

#### Taak - rechtstreeks werken op je Pi

Configureer je Pi voor ontwikkeling.

1. Volg de instructies in de [Raspberry Pi installatiehandleiding](https://projects.raspberrypi.org/en/projects/raspberry-pi-setting-up) om je Pi in te stellen, aan te sluiten op een toetsenbord/muis/monitor, verbinding te maken met je WiFi- of ethernetnetwerk en de software bij te werken.

Om de Pi te programmeren met de Grove-sensoren en actuatoren, moet je een editor installeren om de apparaatcode te schrijven, evenals verschillende bibliotheken en tools die samenwerken met de Grove-hardware.

1. Zodra je Pi opnieuw is opgestart, start je de Terminal door op het **Terminal**-pictogram in de bovenste menubalk te klikken, of kies *Menu -> Accessoires -> Terminal*.

1. Voer de volgende opdracht uit om ervoor te zorgen dat het besturingssysteem en de geïnstalleerde software up-to-date zijn:

    ```sh
    sudo apt update && sudo apt full-upgrade --yes
    ```

1. Voer de volgende opdrachten uit om alle benodigde bibliotheken voor de Grove-hardware te installeren:

    ```sh
    sudo apt install git python3-dev python3-pip --yes

    git clone https://github.com/Seeed-Studio/grove.py
    cd grove.py
    sudo pip3 install .

    sudo raspi-config nonint do_i2c 0
    ```

    Dit begint met het installeren van Git, samen met Pip om Python-pakketten te installeren.

    Een van de krachtige functies van Python is de mogelijkheid om [Pip-pakketten](https://pypi.org) te installeren - dit zijn pakketten met code geschreven door andere mensen en gepubliceerd op het internet. Je kunt een Pip-pakket op je computer installeren met één opdracht en dat pakket vervolgens in je code gebruiken.

    De Seeed Grove Python-pakketten moeten vanaf de bron worden geïnstalleerd. Deze opdrachten klonen de repository met de broncode voor dit pakket en installeren het vervolgens lokaal.

    > 💁 Standaard is een geïnstalleerd pakket overal op je computer beschikbaar, wat kan leiden tot problemen met pakketversies - zoals een applicatie die afhankelijk is van een bepaalde versie van een pakket die breekt wanneer je een nieuwe versie installeert voor een andere applicatie. Om dit probleem te omzeilen, kun je een [Python virtuele omgeving](https://docs.python.org/3/library/venv.html) gebruiken, in feite een kopie van Python in een speciale map, en wanneer je Pip-pakketten installeert, worden ze alleen in die map geïnstalleerd. Je zult geen virtuele omgevingen gebruiken bij het werken met je Pi. Het Grove-installatiescript installeert de Grove Python-pakketten globaal, dus om een virtuele omgeving te gebruiken, zou je een virtuele omgeving moeten instellen en vervolgens handmatig de Grove-pakketten opnieuw installeren in die omgeving. Het is eenvoudiger om gewoon globale pakketten te gebruiken, vooral omdat veel Pi-ontwikkelaars een schone SD-kaart opnieuw flashen voor elk project.

    Ten slotte wordt hiermee de I<sup>2</sup>C-interface ingeschakeld.

1. Start de Pi opnieuw op via het menu of door de volgende opdracht in de Terminal uit te voeren:

    ```sh
    sudo reboot
    ```

1. Zodra de Pi opnieuw is opgestart, start je de Terminal opnieuw en voer je de volgende opdracht uit om [Visual Studio Code (VS Code)](https://code.visualstudio.com?WT.mc_id=academic-17441-jabenn) te installeren - dit is de editor die je zult gebruiken om je apparaatcode in Python te schrijven.

    ```sh
    sudo apt install code
    ```

    Zodra dit is geïnstalleerd, is VS Code beschikbaar in de bovenste menubalk.

    > 💁 Je bent vrij om elke Python IDE of editor te gebruiken voor deze lessen als je een voorkeursprogramma hebt, maar de lessen geven instructies gebaseerd op het gebruik van VS Code.

1. Installeer Pylance. Dit is een extensie voor VS Code die ondersteuning biedt voor de Python-taal. Raadpleeg de [Pylance extensiedocumentatie](https://marketplace.visualstudio.com/items?WT.mc_id=academic-17441-jabenn&itemName=ms-python.vscode-pylance) voor instructies over het installeren van deze extensie in VS Code.

### Op afstand toegang krijgen om de Pi te programmeren

In plaats van rechtstreeks op de Pi te programmeren, kan deze 'headless' draaien, dat wil zeggen niet aangesloten op een toetsenbord/muis/monitor, en kun je deze configureren en programmeren vanaf je computer met Visual Studio Code.

#### Stel het Pi OS in

Om op afstand te programmeren, moet het Pi OS worden geïnstalleerd op een SD-kaart.

##### Taak - stel het Pi OS in

Configureer het headless Pi OS.

1. Download de **Raspberry Pi Imager** van de [Raspberry Pi OS softwarepagina](https://www.raspberrypi.org/software/) en installeer deze.

1. Plaats een SD-kaart in je computer, eventueel met behulp van een adapter.

1. Start de Raspberry Pi Imager.

1. Selecteer in de Raspberry Pi Imager de knop **CHOOSE OS** en kies vervolgens *Raspberry Pi OS (Other)*, gevolgd door *Raspberry Pi OS Lite (32-bit)*.

    ![De Raspberry Pi Imager met Raspberry Pi OS Lite geselecteerd](../../../../../translated_images/raspberry-pi-imager.24aedeab9e233d84.nl.png)

    > 💁 Raspberry Pi OS Lite is een versie van Raspberry Pi OS zonder de desktop-UI of UI-gebaseerde tools. Deze zijn niet nodig voor een headless Pi en maken de installatie kleiner en de opstarttijd sneller.

1. Selecteer de knop **CHOOSE STORAGE** en kies je SD-kaart.

1. Start de **Advanced Options** door `Ctrl+Shift+X` in te drukken. Met deze opties kun je enkele instellingen van het Raspberry Pi OS vooraf configureren voordat het naar de SD-kaart wordt geschreven.

    1. Vink het vakje **Enable SSH** aan en stel een wachtwoord in voor de gebruiker `pi`. Dit is het wachtwoord dat je later gebruikt om in te loggen op de Pi.

    1. Als je van plan bent om verbinding te maken met de Pi via WiFi, vink het vakje **Configure WiFi** aan en voer je WiFi SSID en wachtwoord in, evenals je WiFi-land. Dit is niet nodig als je een ethernetkabel gebruikt. Zorg ervoor dat het netwerk waarmee je verbinding maakt hetzelfde is als dat van je computer.

    1. Vink het vakje **Set locale settings** aan en stel je land en tijdzone in.

    1. Selecteer de knop **SAVE**.

1. Selecteer de knop **WRITE** om het OS naar de SD-kaart te schrijven. Als je macOS gebruikt, wordt je gevraagd je wachtwoord in te voeren, omdat de onderliggende tool die schijfimages schrijft toegang met verhoogde rechten nodig heeft.

Het OS wordt naar de SD-kaart geschreven en zodra dit is voltooid, wordt de kaart door het besturingssysteem uitgeworpen en krijg je een melding. Verwijder de SD-kaart uit je computer, plaats deze in de Pi, zet de Pi aan en wacht ongeveer 2 minuten totdat deze volledig is opgestart.

#### Verbinden met de Pi

De volgende stap is om op afstand toegang te krijgen tot de Pi. Dit kan met `ssh`, dat beschikbaar is op macOS, Linux en recente versies van Windows.

##### Taak - verbinden met de Pi

Verbind op afstand met de Pi.

1. Start een Terminal of Command Prompt en voer de volgende opdracht in om verbinding te maken met de Pi:

    ```sh
    ssh pi@raspberrypi.local
    ```

    Als je Windows gebruikt en een oudere versie hebt waarop `ssh` niet is geïnstalleerd, kun je OpenSSH gebruiken. Je kunt de installatie-instructies vinden in de [OpenSSH installatiedocumentatie](https://docs.microsoft.com//windows-server/administration/openssh/openssh_install_firstuse?WT.mc_id=academic-17441-jabenn).

1. Dit zou verbinding moeten maken met je Pi en om het wachtwoord moeten vragen.

    Het kunnen vinden van computers op je netwerk met `<hostname>.local` is een vrij recente toevoeging aan Linux en Windows. Als je Linux of Windows gebruikt en foutmeldingen krijgt over de hostnaam die niet wordt gevonden, moet je extra software installeren om ZeroConf-netwerken (ook wel Bonjour genoemd door Apple) in te schakelen:

    1. Als je Linux gebruikt, installeer Avahi met de volgende opdracht:

        ```sh
        sudo apt-get install avahi-daemon
        ```

    1. Als je Windows gebruikt, is de eenvoudigste manier om ZeroConf in te schakelen het installeren van [Bonjour Print Services voor Windows](http://support.apple.com/kb/DL999). Je kunt ook [iTunes voor Windows](https://www.apple.com/itunes/download/) installeren om een nieuwere versie van de utility te krijgen (die niet afzonderlijk beschikbaar is).

    > 💁 Als je geen verbinding kunt maken met `raspberrypi.local`, kun je het IP-adres van je Pi gebruiken. Raadpleeg de [Raspberry Pi IP-adresdocumentatie](https://www.raspberrypi.org/documentation/remote-access/ip-address.md) voor instructies over verschillende manieren om het IP-adres te achterhalen.

1. Voer het wachtwoord in dat je hebt ingesteld in de Advanced Options van de Raspberry Pi Imager.

#### Software configureren op de Pi

Zodra je verbonden bent met de Pi, moet je ervoor zorgen dat het besturingssysteem up-to-date is en verschillende bibliotheken en tools installeren die samenwerken met de Grove-hardware.

##### Taak - software configureren op de Pi

Configureer de geïnstalleerde Pi-software en installeer de Grove-bibliotheken.

1. Voer vanuit je `ssh`-sessie de volgende opdracht uit om de Pi bij te werken en opnieuw op te starten:

    ```sh
    sudo apt update && sudo apt full-upgrade --yes && sudo reboot
    ```

    De Pi wordt bijgewerkt en opnieuw opgestart. De `ssh`-sessie wordt beëindigd wanneer de Pi opnieuw wordt opgestart, dus wacht ongeveer 30 seconden en maak opnieuw verbinding.

1. Voer vanuit de opnieuw verbonden `ssh`-sessie de volgende opdrachten uit om alle benodigde bibliotheken voor de Grove-hardware te installeren:

    ```sh
    sudo apt install git python3-dev python3-pip --yes

    git clone https://github.com/Seeed-Studio/grove.py
    cd grove.py
    sudo pip3 install .

    sudo raspi-config nonint do_i2c 0
    ```

    Dit begint met het installeren van Git, samen met Pip om Python-pakketten te installeren.

    Een van de krachtige functies van Python is de mogelijkheid om [Pip-pakketten](https://pypi.org) te installeren - dit zijn pakketten met code geschreven door andere mensen en gepubliceerd op het internet. Je kunt een Pip-pakket op je computer installeren met één opdracht en dat pakket vervolgens in je code gebruiken.

    De Seeed Grove Python-pakketten moeten vanaf de bron worden geïnstalleerd. Deze opdrachten klonen de repository met de broncode voor dit pakket en installeren het vervolgens lokaal.

    > 💁 Standaard is een geïnstalleerd pakket overal op je computer beschikbaar, wat kan leiden tot problemen met pakketversies - zoals een applicatie die afhankelijk is van een bepaalde versie van een pakket die breekt wanneer je een nieuwe versie installeert voor een andere applicatie. Om dit probleem te omzeilen, kun je een [Python virtuele omgeving](https://docs.python.org/3/library/venv.html) gebruiken, in feite een kopie van Python in een speciale map, en wanneer je Pip-pakketten installeert, worden ze alleen in die map geïnstalleerd. Je zult geen virtuele omgevingen gebruiken bij het werken met je Pi. Het Grove-installatiescript installeert de Grove Python-pakketten globaal, dus om een virtuele omgeving te gebruiken, zou je een virtuele omgeving moeten instellen en vervolgens handmatig de Grove-pakketten opnieuw installeren in die omgeving. Het is eenvoudiger om gewoon globale pakketten te gebruiken, vooral omdat veel Pi-ontwikkelaars een schone SD-kaart opnieuw flashen voor elk project.

    Ten slotte wordt hiermee de I<sup>2</sup>C-interface ingeschakeld.

1. Start de Pi opnieuw op door de volgende opdracht uit te voeren:

    ```sh
    sudo reboot
    ```

    De `ssh`-sessie wordt beëindigd wanneer de Pi opnieuw wordt opgestart. Er is geen noodzaak om opnieuw verbinding te maken.

#### VS Code configureren voor toegang op afstand

Zodra de Pi is geconfigureerd, kun je verbinding maken met Visual Studio Code (VS Code) vanaf je computer - dit is een gratis ontwikkelaarsteksteditor die je zult gebruiken om je apparaatcode in Python te schrijven.

##### Taak - VS Code configureren voor toegang op afstand

Installeer de benodigde software en maak op afstand verbinding met je Pi.

1. Installeer VS Code op je computer door de [VS Code documentatie](https://code.visualstudio.com?WT.mc_id=academic-17441-jabenn) te volgen.

1. Volg de instructies in de [VS Code Remote Development using SSH documentatie](https://code.visualstudio.com/docs/remote/ssh?WT.mc_id=academic-17441-jabenn) om de benodigde componenten te installeren.

1. Volg dezelfde instructies om VS Code te verbinden met de Pi.

1. Zodra je verbonden bent, volg de [beheer extensies](https://code.visualstudio.com/docs/remote/ssh#_managing-extensions?WT.mc_id=academic-17441-jabenn) instructies om de [Pylance extensie](https://marketplace.visualstudio.com/items?WT.mc_id=academic-17441-jabenn&itemName=ms-python.vscode-pylance) op afstand op de Pi te installeren.

## Hallo wereld
Het is gebruikelijk om bij het beginnen met een nieuwe programmeertaal of technologie een 'Hello World'-applicatie te maken - een kleine applicatie die iets als de tekst `"Hello World"` uitvoert om te laten zien dat alle tools correct zijn geconfigureerd.

De Hello World-app voor de Pi zorgt ervoor dat je Python en Visual Studio Code correct hebt geïnstalleerd.

Deze app zal zich bevinden in een map genaamd `nightlight`, en zal later in deze opdracht opnieuw worden gebruikt met andere code om de nightlight-applicatie te bouwen.

### Taak - hello world

Maak de Hello World-app.

1. Start VS Code, direct op de Pi of op je computer en verbind met de Pi via de Remote SSH-extensie.

1. Open de VS Code Terminal door *Terminal -> New Terminal* te selecteren, of door `` CTRL+` `` in te drukken. De terminal opent in de home-directory van de `pi` gebruiker.

1. Voer de volgende commando's uit om een map voor je code te maken en een Python-bestand genaamd `app.py` in die map te creëren:

    ```sh
    mkdir nightlight
    cd nightlight
    touch app.py
    ```

1. Open deze map in VS Code door *File -> Open...* te selecteren en de *nightlight* map te kiezen, klik vervolgens op **OK**.

    ![De VS Code open dialoog toont de nightlight map](../../../../../translated_images/vscode-open-nightlight-remote.d3d2a4011e30d535.nl.png)

1. Open het bestand `app.py` vanuit de VS Code explorer en voeg de volgende code toe:

    ```python
    print('Hello World!')
    ```

    De `print`-functie print alles wat eraan wordt doorgegeven naar de console.

1. Voer vanuit de VS Code Terminal het volgende uit om je Python-app te starten:

    ```sh
    python app.py
    ```

    > 💁 Het kan nodig zijn om expliciet `python3` aan te roepen om deze code uit te voeren als je Python 2 naast Python 3 hebt geïnstalleerd (de nieuwste versie). Als je Python 2 hebt geïnstalleerd, zal het aanroepen van `python` Python 2 gebruiken in plaats van Python 3. Standaard hebben de nieuwste versies van Raspberry Pi OS alleen Python 3 geïnstalleerd.

    De volgende uitvoer verschijnt in de terminal:

    ```output
    pi@raspberrypi:~/nightlight $ python3 app.py
    Hello World!
    ```

> 💁 Je kunt deze code vinden in de [code/pi](../../../../../1-getting-started/lessons/1-introduction-to-iot/code/pi) map.

😀 Je 'Hello World'-programma is een succes!

---

**Disclaimer**:  
Dit document is vertaald met behulp van de AI-vertalingsservice [Co-op Translator](https://github.com/Azure/co-op-translator). Hoewel we streven naar nauwkeurigheid, dient u zich ervan bewust te zijn dat geautomatiseerde vertalingen fouten of onnauwkeurigheden kunnen bevatten. Het originele document in zijn oorspronkelijke taal moet worden beschouwd als de gezaghebbende bron. Voor cruciale informatie wordt professionele menselijke vertaling aanbevolen. Wij zijn niet aansprakelijk voor eventuele misverstanden of verkeerde interpretaties die voortvloeien uit het gebruik van deze vertaling.