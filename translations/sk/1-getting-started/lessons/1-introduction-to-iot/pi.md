<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "8ff0d0a1d29832bb896b9c103b69a452",
  "translation_date": "2025-08-28T10:23:10+00:00",
  "source_file": "1-getting-started/lessons/1-introduction-to-iot/pi.md",
  "language_code": "sk"
}
-->
# Raspberry Pi

[Raspberry Pi](https://raspberrypi.org) je jednodeskový počítač. Môžete k nemu pripojiť senzory a akčné členy pomocou širokej škály zariadení a ekosystémov. Pre tieto lekcie budete používať hardvérový ekosystém nazývaný [Grove](https://www.seeedstudio.com/category/Grove-c-1003.html). Raspberry Pi budete programovať a pristupovať k senzorom Grove pomocou jazyka Python.

![Raspberry Pi 4](../../../../../translated_images/sk/raspberry-pi-4.fd4590d308c3d456.jpg)

## Nastavenie

Ak používate Raspberry Pi ako svoje IoT zariadenie, máte dve možnosti – môžete prejsť všetkými týmito lekciami a programovať priamo na Pi, alebo sa môžete pripojiť na „headless“ Pi a programovať z vášho počítača.

Predtým, než začnete, musíte pripojiť základný modul Grove Base Hat k vášmu Pi.

### Úloha - nastavenie

Nainštalujte základný modul Grove Base Hat na vaše Pi a nakonfigurujte ho.

1. Pripojte základný modul Grove Base Hat k vášmu Pi. Konektor na module sa nasadí na všetky GPIO piny na Pi, pričom sa zasunie až na doraz. Modul sedí na Pi a zakrýva ho.

    ![Pripojenie modulu Grove Hat](../../../../../images/pi-grove-hat-fitting.gif)

1. Rozhodnite sa, ako chcete programovať svoje Pi, a prejdite na príslušnú sekciu nižšie:

    * [Práca priamo na vašom Pi](../../../../../1-getting-started/lessons/1-introduction-to-iot)
    * [Vzdialený prístup na programovanie Pi](../../../../../1-getting-started/lessons/1-introduction-to-iot)

### Práca priamo na vašom Pi

Ak chcete pracovať priamo na vašom Pi, môžete použiť desktopovú verziu Raspberry Pi OS a nainštalovať všetky potrebné nástroje.

#### Úloha - práca priamo na vašom Pi

Nastavte svoje Pi na vývoj.

1. Postupujte podľa pokynov v [návode na nastavenie Raspberry Pi](https://projects.raspberrypi.org/en/projects/raspberry-pi-setting-up), aby ste nastavili svoje Pi, pripojili ho k klávesnici/myši/monitoru, pripojili ho k WiFi alebo ethernetovej sieti a aktualizovali softvér.

Na programovanie Pi pomocou senzorov a akčných členov Grove budete potrebovať nainštalovať editor na písanie kódu pre zariadenie a rôzne knižnice a nástroje na interakciu s hardvérom Grove.

1. Po reštartovaní Pi spustite Terminál kliknutím na ikonu **Terminal** v hornom menu alebo vyberte *Menu -> Accessories -> Terminal*.

1. Spustite nasledujúci príkaz, aby ste sa uistili, že operačný systém a nainštalovaný softvér sú aktuálne:

    ```sh
    sudo apt update && sudo apt full-upgrade --yes
    ```

1. Spustite nasledujúce príkazy na inštaláciu všetkých potrebných knižníc pre hardvér Grove:

    ```sh
    sudo apt install git python3-dev python3-pip --yes

    git clone https://github.com/Seeed-Studio/grove.py
    cd grove.py
    sudo pip3 install .

    sudo raspi-config nonint do_i2c 0
    ```

    Tento proces začína inštaláciou Git a Pip na inštaláciu Python balíčkov.

    Jednou z výhod Pythonu je možnosť inštalovať [Pip balíčky](https://pypi.org) – ide o balíčky kódu napísané inými ľuďmi a zverejnené na internete. Pip balíček môžete nainštalovať na svoj počítač jedným príkazom a následne ho použiť vo svojom kóde.

    Python balíčky Seeed Grove je potrebné nainštalovať zo zdrojového kódu. Tieto príkazy klonujú repozitár obsahujúci zdrojový kód pre tento balíček a následne ho lokálne nainštalujú.

    > 💁 Štandardne, keď nainštalujete balíček, je dostupný všade na vašom počítači, čo môže viesť k problémom s verziami balíčkov – napríklad jedna aplikácia závisí od jednej verzie balíčka, ktorá prestane fungovať, keď nainštalujete novú verziu pre inú aplikáciu. Na riešenie tohto problému môžete použiť [Python virtuálne prostredie](https://docs.python.org/3/library/venv.html), čo je v podstate kópia Pythonu v dedikovanom priečinku, a keď inštalujete Pip balíčky, inštalujú sa len do tohto priečinka. Pri používaní Pi však virtuálne prostredia používať nebudete. Inštalačný skript Grove nainštaluje Python balíčky Grove globálne, takže ak by ste chceli použiť virtuálne prostredie, museli by ste ho nastaviť a následne manuálne preinštalovať balíčky Grove v tomto prostredí. Je jednoduchšie používať globálne balíčky, najmä preto, že veľa vývojárov pre Pi pre každý projekt preinštaluje čistú SD kartu.

    Nakoniec sa povolí rozhranie I<sup>2</sup>C.

1. Reštartujte Pi buď pomocou menu, alebo spustením nasledujúceho príkazu v Termináli:

    ```sh
    sudo reboot
    ```

1. Po reštartovaní Pi znova spustite Terminál a spustite nasledujúci príkaz na inštaláciu [Visual Studio Code (VS Code)](https://code.visualstudio.com?WT.mc_id=academic-17441-jabenn) – to je editor, ktorý budete používať na písanie kódu pre zariadenie v Pythone.

    ```sh
    sudo apt install code
    ```

    Po nainštalovaní bude VS Code dostupný z horného menu.

    > 💁 Môžete použiť akýkoľvek Python IDE alebo editor pre tieto lekcie, ak máte preferovaný nástroj, ale pokyny v lekciách budú založené na používaní VS Code.

1. Nainštalujte Pylance. Ide o rozšírenie pre VS Code, ktoré poskytuje podporu pre jazyk Python. Pozrite si [dokumentáciu k rozšíreniu Pylance](https://marketplace.visualstudio.com/items?WT.mc_id=academic-17441-jabenn&itemName=ms-python.vscode-pylance) pre pokyny na inštaláciu tohto rozšírenia vo VS Code.

### Vzdialený prístup na programovanie Pi

Namiesto programovania priamo na Pi môže bežať „headless“, teda bez pripojenia klávesnice/myši/monitora, a môžete ho konfigurovať a programovať z vášho počítača pomocou Visual Studio Code.

#### Nastavenie Pi OS

Na vzdialené programovanie je potrebné nainštalovať Pi OS na SD kartu.

##### Úloha - nastavenie Pi OS

Nastavte „headless“ Pi OS.

1. Stiahnite si **Raspberry Pi Imager** z [stránky so softvérom Raspberry Pi OS](https://www.raspberrypi.org/software/) a nainštalujte ho.

1. Vložte SD kartu do vášho počítača, prípadne použite adaptér.

1. Spustite Raspberry Pi Imager.

1. V Raspberry Pi Imager vyberte tlačidlo **CHOOSE OS**, potom vyberte *Raspberry Pi OS (Other)* a následne *Raspberry Pi OS Lite (32-bit)*.

    ![Raspberry Pi Imager s vybraným Raspberry Pi OS Lite](../../../../../translated_images/sk/raspberry-pi-imager.24aedeab9e233d84.png)

    > 💁 Raspberry Pi OS Lite je verzia Raspberry Pi OS, ktorá neobsahuje desktopové používateľské rozhranie ani nástroje založené na rozhraní. Tieto nie sú potrebné pre „headless“ Pi, čo robí inštaláciu menšou a rýchlejšou pri spustení.

1. Vyberte tlačidlo **CHOOSE STORAGE** a zvoľte svoju SD kartu.

1. Spustite **Advanced Options** stlačením `Ctrl+Shift+X`. Tieto možnosti umožňujú predkonfiguráciu Raspberry Pi OS pred jeho zápisom na SD kartu.

    1. Zaškrtnite políčko **Enable SSH** a nastavte heslo pre používateľa `pi`. Toto heslo budete používať na prihlásenie do Pi neskôr.

    1. Ak plánujete pripojiť Pi cez WiFi, zaškrtnite políčko **Configure WiFi** a zadajte svoj WiFi SSID a heslo, ako aj vyberte svoju WiFi krajinu. Toto nie je potrebné, ak budete používať ethernetový kábel. Uistite sa, že sieť, ku ktorej sa pripájate, je rovnaká ako tá, na ktorej je váš počítač.

    1. Zaškrtnite políčko **Set locale settings** a nastavte svoju krajinu a časové pásmo.

    1. Vyberte tlačidlo **SAVE**.

1. Vyberte tlačidlo **WRITE**, aby ste zapísali OS na SD kartu. Ak používate macOS, budete požiadaní o zadanie hesla, pretože nástroj na zápis diskových obrazov vyžaduje oprávnený prístup.

OS bude zapísaný na SD kartu a po dokončení bude karta operačným systémom vysunutá a budete o tom informovaní. Vyberte SD kartu z vášho počítača, vložte ju do Pi, zapnite Pi a počkajte približne 2 minúty, kým sa správne spustí.

#### Pripojenie k Pi

Ďalším krokom je vzdialený prístup k Pi. To môžete urobiť pomocou `ssh`, ktorý je dostupný na macOS, Linuxe a novších verziách Windows.

##### Úloha - pripojenie k Pi

Vzdialene sa pripojte k Pi.

1. Spustite Terminál alebo Príkazový riadok a zadajte nasledujúci príkaz na pripojenie k Pi:

    ```sh
    ssh pi@raspberrypi.local
    ```

    Ak používate staršiu verziu Windows, ktorá nemá nainštalovaný `ssh`, môžete použiť OpenSSH. Inštalačné pokyny nájdete v [dokumentácii k inštalácii OpenSSH](https://docs.microsoft.com//windows-server/administration/openssh/openssh_install_firstuse?WT.mc_id=academic-17441-jabenn).

1. Tento príkaz by vás mal pripojiť k vášmu Pi a požiadať o heslo.

    Možnosť nájsť počítače vo vašej sieti pomocou `<hostname>.local` je pomerne nová funkcia v Linuxe a Windows. Ak používate Linux alebo Windows a dostanete chyby o tom, že Hostname nebol nájdený, budete musieť nainštalovať dodatočný softvér na povolenie ZeroConf siete (tiež označovanej spoločnosťou Apple ako Bonjour):

    1. Ak používate Linux, nainštalujte Avahi pomocou nasledujúceho príkazu:

        ```sh
        sudo apt-get install avahi-daemon
        ```

    1. Ak používate Windows, najjednoduchší spôsob, ako povoliť ZeroConf, je nainštalovať [Bonjour Print Services for Windows](http://support.apple.com/kb/DL999). Môžete tiež nainštalovať [iTunes for Windows](https://www.apple.com/itunes/download/), aby ste získali novšiu verziu utility (ktorá nie je dostupná samostatne).

    > 💁 Ak sa nemôžete pripojiť pomocou `raspberrypi.local`, môžete použiť IP adresu vášho Pi. Pozrite si [dokumentáciu k IP adrese Raspberry Pi](https://www.raspberrypi.org/documentation/remote-access/ip-address.md) pre pokyny na rôzne spôsoby získania IP adresy.

1. Zadajte heslo, ktoré ste nastavili v Advanced Options Raspberry Pi Imager.

#### Konfigurácia softvéru na Pi

Keď ste pripojení k Pi, musíte sa uistiť, že operačný systém je aktuálny, a nainštalovať rôzne knižnice a nástroje na interakciu s hardvérom Grove.

##### Úloha - konfigurácia softvéru na Pi

Nakonfigurujte nainštalovaný softvér na Pi a nainštalujte knižnice Grove.

1. Zo svojej `ssh` relácie spustite nasledujúci príkaz na aktualizáciu a následný reštart Pi:

    ```sh
    sudo apt update && sudo apt full-upgrade --yes && sudo reboot
    ```

    Pi sa aktualizuje a reštartuje. `ssh` relácia sa ukončí, keď sa Pi reštartuje, takže počkajte približne 30 sekúnd a potom sa znova pripojte.

1. Zo znova pripojenej `ssh` relácie spustite nasledujúce príkazy na inštaláciu všetkých potrebných knižníc pre hardvér Grove:

    ```sh
    sudo apt install git python3-dev python3-pip --yes

    git clone https://github.com/Seeed-Studio/grove.py
    cd grove.py
    sudo pip3 install .

    sudo raspi-config nonint do_i2c 0
    ```

    Tento proces začína inštaláciou Git a Pip na inštaláciu Python balíčkov.

    Jednou z výhod Pythonu je možnosť inštalovať [Pip balíčky](https://pypi.org) – ide o balíčky kódu napísané inými ľuďmi a zverejnené na internete. Pip balíček môžete nainštalovať na svoj počítač jedným príkazom a následne ho použiť vo svojom kóde.

    Python balíčky Seeed Grove je potrebné nainštalovať zo zdrojového kódu. Tieto príkazy klonujú repozitár obsahujúci zdrojový kód pre tento balíček a následne ho lokálne nainštalujú.

    > 💁 Štandardne, keď nainštalujete balíček, je dostupný všade na vašom počítači, čo môže viesť k problémom s verziami balíčkov – napríklad jedna aplikácia závisí od jednej verzie balíčka, ktorá prestane fungovať, keď nainštalujete novú verziu pre inú aplikáciu. Na riešenie tohto problému môžete použiť [Python virtuálne prostredie](https://docs.python.org/3/library/venv.html), čo je v podstate kópia Pythonu v dedikovanom priečinku, a keď inštalujete Pip balíčky, inštalujú sa len do tohto priečinka. Pri používaní Pi však virtuálne prostredia používať nebudete. Inštalačný skript Grove nainštaluje Python balíčky Grove globálne, takže ak by ste chceli použiť virtuálne prostredie, museli by ste ho nastaviť a následne manuálne preinštalovať balíčky Grove v tomto prostredí. Je jednoduchšie používať globálne balíčky, najmä preto, že veľa vývojárov pre Pi pre každý projekt preinštaluje čistú SD kartu.

    Nakoniec sa povolí rozhranie I<sup>2</sup>C.

1. Reštartujte Pi spustením nasledujúceho príkazu:

    ```sh
    sudo reboot
    ```

    `ssh` relácia sa ukončí, keď sa Pi reštartuje. Nie je potrebné sa znova pripojiť.

#### Konfigurácia VS Code pre vzdialený prístup

Keď je Pi nakonfigurované, môžete sa k nemu pripojiť pomocou Visual Studio Code (VS Code) z vášho počítača – ide o bezplatný vývojársky textový editor, ktorý budete používať na písanie kódu pre zariadenie v Pythone.

##### Úloha - konfigurácia VS Code pre vzdialený prístup

Nainštalujte potrebný softvér a pripojte sa vzdialene k vášmu Pi.

1. Nainštalujte VS Code na váš počítač podľa [dokumentácie k VS Code](https://code.visualstudio.com?WT.mc_id=academic-17441-jabenn).

1. Postupujte podľa pokynov v [dokumentácii k vzdialenému vývoju pomocou SSH vo VS Code](https://code.visualstudio.com/docs/remote/ssh?WT.mc_id=academic-17441-jabenn) na inštaláciu potrebných komponentov.

1. Podľa rovnakých pokynov sa pripojte k Pi pomocou VS Code.

1. Po pripojení postupujte podľa [pokynov na správu rozšírení](https://code.visualstudio.com/docs/remote/ssh#_managing-extensions?WT.mc_id=academic-17441-jabenn) a nainštalujte [rozšírenie Pylance](https://marketplace.visualstudio.com/items?WT.mc_id=academic-17441-jabenn&itemName=ms-python.vscode-pylance) vzdialene na Pi.

## Hello world
Je tradičné, keď začínate s novým programovacím jazykom alebo technológiou, vytvoriť aplikáciu 'Hello World' – malú aplikáciu, ktorá vypíše niečo ako text `"Hello World"`, aby ste overili, že všetky nástroje sú správne nakonfigurované.

Aplikácia Hello World pre Raspberry Pi zabezpečí, že máte správne nainštalovaný Python a Visual Studio Code.

Táto aplikácia bude umiestnená v priečinku s názvom `nightlight` a neskôr v rámci tejto úlohy bude použitá s rôznym kódom na vytvorenie aplikácie nočného svetla.

### Úloha - hello world

Vytvorte aplikáciu Hello World.

1. Spustite VS Code, buď priamo na Raspberry Pi, alebo na vašom počítači a pripojte sa k Raspberry Pi pomocou rozšírenia Remote SSH.

1. Spustite terminál vo VS Code výberom *Terminal -> New Terminal* alebo stlačením `` CTRL+` ``. Terminál sa otvorí v domovskom adresári používateľa `pi`.

1. Spustite nasledujúce príkazy na vytvorenie adresára pre váš kód a vytvorte Python súbor s názvom `app.py` v tomto adresári:

    ```sh
    mkdir nightlight
    cd nightlight
    touch app.py
    ```

1. Otvorte tento priečinok vo VS Code výberom *File -> Open...* a výberom priečinka *nightlight*, potom kliknite na **OK**.

    ![Dialógové okno VS Code zobrazujúce priečinok nightlight](../../../../../translated_images/sk/vscode-open-nightlight-remote.d3d2a4011e30d535.png)

1. Otvorte súbor `app.py` v prieskumníkovi VS Code a pridajte nasledujúci kód:

    ```python
    print('Hello World!')
    ```

    Funkcia `print` vypíše na konzolu čokoľvek, čo jej odovzdáte.

1. Z terminálu vo VS Code spustite nasledujúci príkaz na spustenie vašej Python aplikácie:

    ```sh
    python app.py
    ```

    > 💁 Možno budete musieť explicitne zavolať `python3`, aby ste spustili tento kód, ak máte nainštalovaný Python 2 spolu s Pythonom 3 (najnovšou verziou). Ak máte nainštalovaný Python 2, volanie `python` použije Python 2 namiesto Pythonu 3. Predvolene majú najnovšie verzie Raspberry Pi OS nainštalovaný iba Python 3.

    Nasledujúci výstup sa zobrazí v termináli:

    ```output
    pi@raspberrypi:~/nightlight $ python3 app.py
    Hello World!
    ```

> 💁 Tento kód nájdete v priečinku [code/pi](../../../../../1-getting-started/lessons/1-introduction-to-iot/code/pi).

😀 Vaša aplikácia 'Hello World' bola úspešná!

---

**Upozornenie**:  
Tento dokument bol preložený pomocou služby AI prekladu [Co-op Translator](https://github.com/Azure/co-op-translator). Aj keď sa snažíme o presnosť, prosím, berte na vedomie, že automatizované preklady môžu obsahovať chyby alebo nepresnosti. Pôvodný dokument v jeho rodnom jazyku by mal byť považovaný za autoritatívny zdroj. Pre kritické informácie sa odporúča profesionálny ľudský preklad. Nie sme zodpovední za akékoľvek nedorozumenia alebo nesprávne interpretácie vyplývajúce z použitia tohto prekladu.