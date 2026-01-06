<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "52b4de6144b2efdced7797a5339d6035",
  "translation_date": "2025-08-27T22:20:25+00:00",
  "source_file": "1-getting-started/lessons/1-introduction-to-iot/virtual-device.md",
  "language_code": "cs"
}
-->
# Virtuální jednodeskový počítač

Místo nákupu IoT zařízení spolu se senzory a akčními členy můžete použít svůj počítač k simulaci IoT hardwaru. Projekt [CounterFit](https://github.com/CounterFit-IoT/CounterFit) vám umožňuje spustit aplikaci lokálně, která simuluje IoT hardware, jako jsou senzory a akční členy, a přistupovat k těmto senzorům a akčním členům z lokálního Python kódu napsaného stejným způsobem, jako byste psali kód pro Raspberry Pi s fyzickým hardwarem.

## Nastavení

Pro použití CounterFit budete muset na svém počítači nainstalovat několik bezplatných softwarů.

### Úkol

Nainstalujte požadovaný software.

1. Nainstalujte Python. Pokyny k instalaci nejnovější verze Pythonu naleznete na [stránce ke stažení Pythonu](https://www.python.org/downloads/).

1. Nainstalujte Visual Studio Code (VS Code). To je editor, který budete používat k psaní kódu pro váš virtuální hardware v Pythonu. Pokyny k instalaci VS Code naleznete v [dokumentaci k VS Code](https://code.visualstudio.com?WT.mc_id=academic-17441-jabenn).

    > 💁 Můžete použít jakékoli IDE nebo editor pro Python, pokud máte preferovaný nástroj, ale pokyny v lekcích budou vycházet z používání VS Code.

1. Nainstalujte rozšíření Pylance pro VS Code. Toto rozšíření poskytuje podporu pro jazyk Python. Pokyny k instalaci tohoto rozšíření naleznete v [dokumentaci k rozšíření Pylance](https://marketplace.visualstudio.com/items?WT.mc_id=academic-17441-jabenn&itemName=ms-python.vscode-pylance).

Pokyny k instalaci a konfiguraci aplikace CounterFit budou uvedeny v příslušné části zadání, protože se instalují pro každý projekt zvlášť.

## Hello world

Je tradicí při začátcích s novým programovacím jazykem nebo technologií vytvořit aplikaci 'Hello World' – malou aplikaci, která vypíše například text `"Hello World"`, aby se ověřilo, že všechny nástroje jsou správně nastaveny.

Aplikace Hello World pro virtuální IoT hardware zajistí, že máte správně nainstalovaný Python a Visual Studio Code. Také se připojí k CounterFit pro virtuální IoT senzory a akční členy. Nebude používat žádný hardware, pouze se připojí, aby ověřila, že vše funguje.

Tato aplikace bude ve složce `nightlight` a bude znovu použita s jiným kódem v dalších částech tohoto zadání pro vytvoření aplikace nočního světla.

### Konfigurace virtuálního prostředí Pythonu

Jednou z výkonných funkcí Pythonu je možnost instalace [Pip balíčků](https://pypi.org) – to jsou balíčky kódu napsané jinými lidmi a publikované na internetu. Pip balíček můžete nainstalovat na svůj počítač jedním příkazem a poté jej použít ve svém kódu. Pip budete používat k instalaci balíčku pro komunikaci s CounterFit.

Ve výchozím nastavení, když nainstalujete balíček, je dostupný všude na vašem počítači, což může vést k problémům s verzemi balíčků – například jedna aplikace závisí na jedné verzi balíčku, která přestane fungovat, když nainstalujete novou verzi pro jinou aplikaci. Aby se tento problém obešel, můžete použít [virtuální prostředí Pythonu](https://docs.python.org/3/library/venv.html), což je v podstatě kopie Pythonu v dedikované složce, a když nainstalujete Pip balíčky, nainstalují se pouze do této složky.

> 💁 Pokud používáte Raspberry Pi, pak jste na tomto zařízení nenastavili virtuální prostředí pro správu Pip balíčků, místo toho používáte globální balíčky, protože balíčky Grove jsou globálně nainstalovány instalačním skriptem.

#### Úkol – konfigurace virtuálního prostředí Pythonu

Nakonfigurujte virtuální prostředí Pythonu a nainstalujte Pip balíčky pro CounterFit.

1. Z terminálu nebo příkazového řádku spusťte následující příkaz na místě dle vašeho výběru pro vytvoření a přechod do nové složky:

    ```sh
    mkdir nightlight
    cd nightlight
    ```

1. Nyní spusťte následující příkaz pro vytvoření virtuálního prostředí ve složce `.venv`:

    ```sh
    python3 -m venv .venv
    ```

    > 💁 Musíte explicitně zavolat `python3` pro vytvoření virtuálního prostředí, protože můžete mít nainstalovaný Python 2 vedle Pythonu 3 (nejnovější verze). Pokud máte nainstalovaný Python 2, pak volání `python` použije Python 2 místo Pythonu 3.

1. Aktivujte virtuální prostředí:

    * Na Windows:
        * Pokud používáte příkazový řádek nebo příkazový řádek přes Windows Terminal, spusťte:

            ```cmd
            .venv\Scripts\activate.bat
            ```

        * Pokud používáte PowerShell, spusťte:

            ```powershell
            .\.venv\Scripts\Activate.ps1
            ```

            > Pokud se zobrazí chyba o tom, že spouštění skriptů je na tomto systému zakázáno, budete muset povolit spouštění skriptů nastavením vhodné politiky provádění. To můžete udělat spuštěním PowerShellu jako správce a následným spuštěním následujícího příkazu:

            ```powershell
            Set-ExecutionPolicy -ExecutionPolicy Unrestricted
            ```

            Zadejte `Y`, když budete požádáni o potvrzení. Poté znovu spusťte PowerShell a zkuste to znovu.

            Tuto politiku provádění můžete později resetovat, pokud to bude potřeba. Více si o tom můžete přečíst na [stránce o politikách provádění na Microsoft Docs](https://docs.microsoft.com/powershell/module/microsoft.powershell.core/about/about_execution_policies?WT.mc_id=academic-17441-jabenn).

    * Na macOS nebo Linuxu spusťte:

        ```cmd
        source ./.venv/bin/activate
        ```

    > 💁 Tyto příkazy by měly být spuštěny ze stejného místa, kde jste spustili příkaz pro vytvoření virtuálního prostředí. Nikdy nebudete muset přejít do složky `.venv`, vždy byste měli spustit aktivační příkaz a jakékoli příkazy pro instalaci balíčků nebo spuštění kódu ze složky, ve které jste byli při vytváření virtuálního prostředí.

1. Jakmile je virtuální prostředí aktivováno, výchozí příkaz `python` spustí verzi Pythonu, která byla použita k vytvoření virtuálního prostředí. Spusťte následující příkaz pro zjištění verze:

    ```sh
    python --version
    ```

    Výstup by měl obsahovat následující:

    ```output
    (.venv) ➜  nightlight python --version
    Python 3.9.1
    ```

    > 💁 Vaše verze Pythonu může být jiná – pokud je to verze 3.6 nebo vyšší, je to v pořádku. Pokud ne, smažte tuto složku, nainstalujte novější verzi Pythonu a zkuste to znovu.

1. Spusťte následující příkazy pro instalaci Pip balíčků pro CounterFit. Tyto balíčky zahrnují hlavní aplikaci CounterFit a také shims pro hardware Grove. Tyto shims vám umožňují psát kód, jako byste programovali s fyzickými senzory a akčními členy z ekosystému Grove, ale připojenými k virtuálním IoT zařízením.

    ```sh
    pip install CounterFit
    pip install counterfit-connection
    pip install counterfit-shims-grove
    ```

    Tyto Pip balíčky budou nainstalovány pouze ve virtuálním prostředí a nebudou dostupné mimo něj.

### Napište kód

Jakmile je virtuální prostředí Pythonu připraveno, můžete napsat kód pro aplikaci 'Hello World'.

#### Úkol – napište kód

Vytvořte Python aplikaci, která vypíše `"Hello World"` do konzole.

1. Z terminálu nebo příkazového řádku spusťte následující příkaz uvnitř virtuálního prostředí pro vytvoření Python souboru s názvem `app.py`:

    * Na Windows spusťte:

        ```cmd
        type nul > app.py
        ```

    * Na macOS nebo Linuxu spusťte:

        ```cmd
        touch app.py
        ```

1. Otevřete aktuální složku ve VS Code:

    ```sh
    code .
    ```

    > 💁 Pokud váš terminál na macOS vrátí `command not found`, znamená to, že VS Code nebyl přidán do PATH. Můžete přidat VS Code do PATH podle pokynů v [sekci Spuštění z příkazového řádku v dokumentaci k VS Code](https://code.visualstudio.com/docs/setup/mac?WT.mc_id=academic-17441-jabenn#_launching-from-the-command-line) a poté příkaz znovu spustit. Na Windows a Linuxu je VS Code ve výchozím nastavení přidán do PATH.

1. Když se VS Code spustí, aktivuje virtuální prostředí Pythonu. Vybrané virtuální prostředí se zobrazí ve spodním stavovém řádku:

    ![VS Code zobrazující vybrané virtuální prostředí](../../../../../translated_images/vscode-virtual-env.8ba42e04c3d533cf.cs.png)

1. Pokud je terminál VS Code již spuštěn při spuštění VS Code, nebude mít aktivované virtuální prostředí. Nejjednodušší je ukončit terminál pomocí tlačítka **Kill the active terminal instance**:

    ![VS Code tlačítko Kill the active terminal instance](../../../../../translated_images/vscode-kill-terminal.1cc4de7c6f25ee08.cs.png)

    Můžete zjistit, zda má terminál aktivované virtuální prostředí, protože název virtuálního prostředí bude předponou na výzvě terminálu. Například to může být:

    ```sh
    (.venv) ➜  nightlight
    ```

    Pokud nemáte `.venv` jako předponu na výzvě, virtuální prostředí není v terminálu aktivní.

1. Spusťte nový terminál VS Code výběrem *Terminal -> New Terminal* nebo stisknutím `` CTRL+` ``. Nový terminál načte virtuální prostředí a volání pro jeho aktivaci se objeví v terminálu. Výzva bude také obsahovat název virtuálního prostředí (`.venv`):

    ```output
    ➜  nightlight source .venv/bin/activate
    (.venv) ➜  nightlight 
    ```

1. Otevřete soubor `app.py` z průzkumníka VS Code a přidejte následující kód:

    ```python
    print('Hello World!')
    ```

    Funkce `print` vypíše do konzole vše, co jí předáte.

1. Z terminálu VS Code spusťte následující příkaz pro spuštění vaší Python aplikace:

    ```sh
    python app.py
    ```

    Ve výstupu bude následující:

    ```output
    (.venv) ➜  nightlight python app.py 
    Hello World!
    ```

😀 Vaše aplikace 'Hello World' byla úspěšná!

### Připojte 'hardware'

Jako druhý krok 'Hello World' spustíte aplikaci CounterFit a připojíte k ní svůj kód. To je virtuální ekvivalent připojení IoT hardwaru k vývojové desce.

#### Úkol – připojte 'hardware'

1. Z terminálu VS Code spusťte aplikaci CounterFit následujícím příkazem:

    ```sh
    counterfit
    ```

    Aplikace se spustí a otevře ve vašem webovém prohlížeči:

    ![Aplikace Counter Fit spuštěná v prohlížeči](../../../../../translated_images/counterfit-first-run.433326358b669b31d0e99c3513cb01bfbb13724d162c99cdcc8f51ecf5f9c779.cs.png)

    Bude označena jako *Disconnected* a LED v pravém horním rohu bude vypnutá.

1. Přidejte následující kód na začátek souboru `app.py`:

    ```python
    from counterfit_connection import CounterFitConnection
    CounterFitConnection.init('127.0.0.1', 5000)
    ```

    Tento kód importuje třídu `CounterFitConnection` z modulu `counterfit_connection`, který pochází z Pip balíčku `counterfit-connection`, který jste nainstalovali dříve. Poté inicializuje připojení k aplikaci CounterFit běžící na `127.0.0.1`, což je IP adresa, kterou můžete vždy použít pro přístup k vašemu lokálnímu počítači (často označovanému jako *localhost*), na portu 5000.

    > 💁 Pokud máte jiné aplikace běžící na portu 5000, můžete to změnit aktualizací portu v kódu a spuštěním CounterFit pomocí `CounterFit --port <port_number>`, kde `<port_number>` nahradíte požadovaným portem.

1. Budete muset spustit nový terminál VS Code výběrem tlačítka **Create a new integrated terminal**. To proto, že aplikace CounterFit běží v aktuálním terminálu.

    ![VS Code tlačítko Create a new integrated terminal](../../../../../translated_images/vscode-new-terminal.77db8fc0f9cd3182.cs.png)

1. V tomto novém terminálu spusťte soubor `app.py` jako dříve. Stav CounterFit se změní na **Connected** a LED se rozsvítí.

    ![Counter Fit zobrazený jako připojený](../../../../../translated_images/counterfit-connected.ed30b46d8f79b0921f3fc70be10366e596a89dca3f80c2224a9d9fc98fccf884.cs.png)

> 💁 Tento kód najdete ve složce [code/virtual-device](../../../../../1-getting-started/lessons/1-introduction-to-iot/code/virtual-device).

😀 Vaše připojení k hardwaru bylo úspěšné!

---

**Upozornění**:  
Tento dokument byl přeložen pomocí služby pro automatický překlad [Co-op Translator](https://github.com/Azure/co-op-translator). I když se snažíme o co největší přesnost, mějte prosím na paměti, že automatické překlady mohou obsahovat chyby nebo nepřesnosti. Původní dokument v jeho původním jazyce by měl být považován za závazný zdroj. Pro důležité informace doporučujeme profesionální lidský překlad. Neodpovídáme za žádná nedorozumění nebo nesprávné výklady vyplývající z použití tohoto překladu.