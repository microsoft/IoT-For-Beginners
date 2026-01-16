<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "52b4de6144b2efdced7797a5339d6035",
  "translation_date": "2025-08-28T10:20:52+00:00",
  "source_file": "1-getting-started/lessons/1-introduction-to-iot/virtual-device.md",
  "language_code": "sk"
}
-->
# Virtuálny jednodeskový počítač

Namiesto nákupu IoT zariadenia spolu so senzormi a akčnými členmi môžete použiť svoj počítač na simuláciu IoT hardvéru. Projekt [CounterFit](https://github.com/CounterFit-IoT/CounterFit) vám umožňuje spustiť aplikáciu lokálne, ktorá simuluje IoT hardvér, ako sú senzory a akčné členy, a pristupovať k týmto senzorom a akčným členom z lokálneho Python kódu, ktorý je napísaný rovnakým spôsobom, ako by ste písali kód na Raspberry Pi s použitím fyzického hardvéru.

## Nastavenie

Na používanie CounterFit budete potrebovať nainštalovať niekoľko bezplatných softvérov na svojom počítači.

### Úloha

Nainštalujte potrebný softvér.

1. Nainštalujte Python. Pozrite si [stránku na stiahnutie Pythonu](https://www.python.org/downloads/) pre pokyny na inštaláciu najnovšej verzie Pythonu.

1. Nainštalujte Visual Studio Code (VS Code). Toto je editor, ktorý budete používať na písanie kódu pre virtuálne zariadenie v Pythone. Pozrite si [dokumentáciu VS Code](https://code.visualstudio.com?WT.mc_id=academic-17441-jabenn) pre pokyny na inštaláciu VS Code.

    > 💁 Môžete použiť akékoľvek IDE alebo editor pre Python, ak máte preferovaný nástroj, ale lekcie budú obsahovať pokyny založené na používaní VS Code.

1. Nainštalujte rozšírenie Pylance pre VS Code. Toto je rozšírenie pre VS Code, ktoré poskytuje podporu pre jazyk Python. Pozrite si [dokumentáciu k rozšíreniu Pylance](https://marketplace.visualstudio.com/items?WT.mc_id=academic-17441-jabenn&itemName=ms-python.vscode-pylance) pre pokyny na inštaláciu tohto rozšírenia vo VS Code.

Pokyny na inštaláciu a konfiguráciu aplikácie CounterFit budú uvedené v príslušnom čase v zadaniach, pretože sa inštaluje na báze jednotlivých projektov.

## Hello world

Je tradičné, keď začínate s novým programovacím jazykom alebo technológiou, vytvoriť aplikáciu 'Hello World' - malú aplikáciu, ktorá vypíše niečo ako text `"Hello World"`, aby ste overili, že všetky nástroje sú správne nakonfigurované.

Aplikácia Hello World pre virtuálny IoT hardvér zabezpečí, že máte správne nainštalovaný Python a Visual Studio Code. Tiež sa pripojí k CounterFit pre virtuálne IoT senzory a akčné členy. Nepoužije žiadny hardvér, iba sa pripojí, aby dokázala, že všetko funguje.

Táto aplikácia bude v priečinku s názvom `nightlight` a bude sa opakovane používať s rôznym kódom v neskorších častiach tohto zadania na vytvorenie aplikácie nočného svetla.

### Konfigurácia virtuálneho prostredia Pythonu

Jednou z výkonných funkcií Pythonu je možnosť inštalovať [Pip balíčky](https://pypi.org) - to sú balíčky kódu napísané inými ľuďmi a publikované na internete. Môžete nainštalovať Pip balíček na svoj počítač jedným príkazom a potom tento balíček použiť vo svojom kóde. Budete používať Pip na inštaláciu balíčka na komunikáciu s CounterFit.

Štandardne, keď nainštalujete balíček, je dostupný všade na vašom počítači, čo môže viesť k problémom s verziami balíčkov - napríklad jedna aplikácia závisí na jednej verzii balíčka, ktorá prestane fungovať, keď nainštalujete novú verziu pre inú aplikáciu. Na vyriešenie tohto problému môžete použiť [virtuálne prostredie Pythonu](https://docs.python.org/3/library/venv.html), v podstate kópiu Pythonu v dedikovanom priečinku, a keď nainštalujete Pip balíčky, nainštalujú sa iba do tohto priečinka.

> 💁 Ak používate Raspberry Pi, potom ste na tomto zariadení nenastavili virtuálne prostredie na správu Pip balíčkov, namiesto toho používate globálne balíčky, pretože Grove balíčky sú nainštalované globálne inštalačným skriptom.

#### Úloha - konfigurácia virtuálneho prostredia Pythonu

Nakonfigurujte virtuálne prostredie Pythonu a nainštalujte Pip balíčky pre CounterFit.

1. Z terminálu alebo príkazového riadku spustite nasledujúce príkazy na vytvorenie a navigáciu do nového adresára:

    ```sh
    mkdir nightlight
    cd nightlight
    ```

1. Teraz spustite nasledujúci príkaz na vytvorenie virtuálneho prostredia v priečinku `.venv`:

    ```sh
    python3 -m venv .venv
    ```

    > 💁 Musíte explicitne zavolať `python3` na vytvorenie virtuálneho prostredia, pre prípad, že máte nainštalovaný Python 2 okrem Pythonu 3 (najnovšia verzia). Ak máte nainštalovaný Python 2, volanie `python` použije Python 2 namiesto Pythonu 3.

1. Aktivujte virtuálne prostredie:

    * Na Windows:
        * Ak používate Command Prompt alebo Command Prompt cez Windows Terminal, spustite:

            ```cmd
            .venv\Scripts\activate.bat
            ```

        * Ak používate PowerShell, spustite:

            ```powershell
            .\.venv\Scripts\Activate.ps1
            ```

            > Ak dostanete chybu o tom, že spúšťanie skriptov je na tomto systéme zakázané, budete musieť povoliť spúšťanie skriptov nastavením vhodnej politiky vykonávania. Môžete to urobiť spustením PowerShellu ako administrátor a následným spustením nasledujúceho príkazu:

            ```powershell
            Set-ExecutionPolicy -ExecutionPolicy Unrestricted
            ```

            Zadajte `Y`, keď budete požiadaní o potvrdenie. Potom znova spustite PowerShell a skúste to znova.

            Túto politiku vykonávania môžete neskôr resetovať, ak to bude potrebné. Viac o tom si môžete prečítať na [stránke o politikách vykonávania na Microsoft Docs](https://docs.microsoft.com/powershell/module/microsoft.powershell.core/about/about_execution_policies?WT.mc_id=academic-17441-jabenn).

    * Na macOS alebo Linux spustite:

        ```cmd
        source ./.venv/bin/activate
        ```

    > 💁 Tieto príkazy by sa mali spustiť z rovnakého miesta, kde ste spustili príkaz na vytvorenie virtuálneho prostredia. Nikdy nebudete musieť navigovať do priečinka `.venv`, vždy by ste mali spustiť aktivačný príkaz a akékoľvek príkazy na inštaláciu balíčkov alebo spustenie kódu z priečinka, v ktorom ste boli, keď ste vytvorili virtuálne prostredie.

1. Po aktivácii virtuálneho prostredia bude predvolený príkaz `python` spúšťať verziu Pythonu, ktorá bola použitá na vytvorenie virtuálneho prostredia. Spustite nasledujúci príkaz na získanie verzie:

    ```sh
    python --version
    ```

    Výstup by mal obsahovať nasledujúce:

    ```output
    (.venv) ➜  nightlight python --version
    Python 3.9.1
    ```

    > 💁 Vaša verzia Pythonu môže byť iná - pokiaľ je to verzia 3.6 alebo vyššia, je to v poriadku. Ak nie, odstráňte tento priečinok, nainštalujte novšiu verziu Pythonu a skúste to znova.

1. Spustite nasledujúce príkazy na inštaláciu Pip balíčkov pre CounterFit. Tieto balíčky zahŕňajú hlavnú aplikáciu CounterFit, ako aj shimy pre Grove hardvér. Tieto shimy vám umožňujú písať kód, akoby ste programovali s použitím fyzických senzorov a akčných členov z ekosystému Grove, ale pripojených k virtuálnym IoT zariadeniam.

    ```sh
    pip install CounterFit
    pip install counterfit-connection
    pip install counterfit-shims-grove
    ```

    Tieto Pip balíčky budú nainštalované iba vo virtuálnom prostredí a nebudú dostupné mimo neho.

### Napíšte kód

Keď je virtuálne prostredie Pythonu pripravené, môžete napísať kód pre aplikáciu 'Hello World'.

#### Úloha - napíšte kód

Vytvorte Python aplikáciu, ktorá vypíše `"Hello World"` do konzoly.

1. Z terminálu alebo príkazového riadku spustite nasledujúce príkazy vo vnútri virtuálneho prostredia na vytvorenie Python súboru s názvom `app.py`:

    * Na Windows spustite:

        ```cmd
        type nul > app.py
        ```

    * Na macOS alebo Linux spustite:

        ```cmd
        touch app.py
        ```

1. Otvorte aktuálny priečinok vo VS Code:

    ```sh
    code .
    ```

    > 💁 Ak váš terminál na macOS vráti `command not found`, znamená to, že VS Code nebol pridaný do vášho PATH. Môžete pridať VS Code do PATH podľa pokynov v [časti Spustenie z príkazového riadku v dokumentácii VS Code](https://code.visualstudio.com/docs/setup/mac?WT.mc_id=academic-17441-jabenn#_launching-from-the-command-line) a potom spustiť príkaz znova. Na Windows a Linux je VS Code predvolene pridaný do PATH.

1. Keď sa VS Code spustí, aktivuje virtuálne prostredie Pythonu. Vybrané virtuálne prostredie sa zobrazí v dolnom stavovom riadku:

    ![VS Code zobrazujúci vybrané virtuálne prostredie](../../../../../translated_images/sk/vscode-virtual-env.8ba42e04c3d533cf.webp)

1. Ak je terminál VS Code už spustený, keď sa VS Code spustí, virtuálne prostredie v ňom nebude aktivované. Najjednoduchšie je zabiť terminál pomocou tlačidla **Kill the active terminal instance**:

    ![Tlačidlo VS Code Kill the active terminal instance](../../../../../translated_images/sk/vscode-kill-terminal.1cc4de7c6f25ee08.webp)

    Môžete zistiť, či je virtuálne prostredie aktivované v termináli, pretože názov virtuálneho prostredia bude predponou na výzve terminálu. Napríklad to môže byť:

    ```sh
    (.venv) ➜  nightlight
    ```

    Ak nemáte `.venv` ako predponu na výzve, virtuálne prostredie nie je aktivované v termináli.

1. Spustite nový terminál VS Code výberom *Terminal -> New Terminal* alebo stlačením `` CTRL+` ``. Nový terminál načíta virtuálne prostredie a volanie na jeho aktiváciu sa zobrazí v termináli. Výzva bude mať tiež názov virtuálneho prostredia (`.venv`):

    ```output
    ➜  nightlight source .venv/bin/activate
    (.venv) ➜  nightlight 
    ```

1. Otvorte súbor `app.py` z prieskumníka VS Code a pridajte nasledujúci kód:

    ```python
    print('Hello World!')
    ```

    Funkcia `print` vypíše čokoľvek, čo jej odovzdáte, do konzoly.

1. Z terminálu VS Code spustite nasledujúci príkaz na spustenie vašej Python aplikácie:

    ```sh
    python app.py
    ```

    Vo výstupe sa zobrazí nasledujúce:

    ```output
    (.venv) ➜  nightlight python app.py 
    Hello World!
    ```

😀 Vaša 'Hello World' aplikácia bola úspešná!

### Pripojte 'hardvér'

Ako druhý krok 'Hello World' spustíte aplikáciu CounterFit a pripojíte k nej svoj kód. Toto je virtuálny ekvivalent pripojenia IoT hardvéru k vývojovej sade.

#### Úloha - pripojte 'hardvér'

1. Z terminálu VS Code spustite aplikáciu CounterFit nasledujúcim príkazom:

    ```sh
    counterfit
    ```

    Aplikácia sa spustí a otvorí vo vašom webovom prehliadači:

    ![Aplikácia Counter Fit spustená v prehliadači](../../../../../translated_images/sk/counterfit-first-run.433326358b669b31d0e99c3513cb01bfbb13724d162c99cdcc8f51ecf5f9c779.png)

    Bude označená ako *Disconnected* a LED v pravom hornom rohu bude vypnutá.

1. Pridajte nasledujúci kód na začiatok súboru `app.py`:

    ```python
    from counterfit_connection import CounterFitConnection
    CounterFitConnection.init('127.0.0.1', 5000)
    ```

    Tento kód importuje triedu `CounterFitConnection` z modulu `counterfit_connection`, ktorý pochádza z Pip balíčka `counterfit-connection`, ktorý ste nainštalovali skôr. Potom inicializuje pripojenie k aplikácii CounterFit bežiacej na `127.0.0.1`, čo je IP adresa, ktorú môžete vždy použiť na prístup k svojmu lokálnemu počítaču (často označovaná ako *localhost*), na porte 5000.

    > 💁 Ak máte iné aplikácie bežiace na porte 5000, môžete to zmeniť aktualizáciou portu v kóde a spustením CounterFit pomocou `CounterFit --port <port_number>`, kde `<port_number>` nahradíte číslom portu, ktorý chcete použiť.

1. Budete musieť spustiť nový terminál VS Code výberom tlačidla **Create a new integrated terminal**. Je to preto, že aplikácia CounterFit beží v aktuálnom termináli.

    ![Tlačidlo VS Code Create a new integrated terminal](../../../../../translated_images/sk/vscode-new-terminal.77db8fc0f9cd3182.webp)

1. V tomto novom termináli spustite súbor `app.py` ako predtým. Stav CounterFit sa zmení na **Connected** a LED sa rozsvieti.

    ![Counter Fit zobrazuje stav Connected](../../../../../translated_images/sk/counterfit-connected.ed30b46d8f79b0921f3fc70be10366e596a89dca3f80c2224a9d9fc98fccf884.png)

> 💁 Tento kód nájdete v priečinku [code/virtual-device](../../../../../1-getting-started/lessons/1-introduction-to-iot/code/virtual-device).

😀 Vaše pripojenie k hardvéru bolo úspešné!

---

**Upozornenie**:  
Tento dokument bol preložený pomocou služby AI prekladu [Co-op Translator](https://github.com/Azure/co-op-translator). Aj keď sa snažíme o presnosť, prosím, berte na vedomie, že automatizované preklady môžu obsahovať chyby alebo nepresnosti. Pôvodný dokument v jeho rodnom jazyku by mal byť považovaný za autoritatívny zdroj. Pre kritické informácie sa odporúča profesionálny ľudský preklad. Nenesieme zodpovednosť za akékoľvek nedorozumenia alebo nesprávne interpretácie vyplývajúce z použitia tohto prekladu.