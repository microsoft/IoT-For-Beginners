<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "52b4de6144b2efdced7797a5339d6035",
  "translation_date": "2025-08-28T14:01:29+00:00",
  "source_file": "1-getting-started/lessons/1-introduction-to-iot/virtual-device.md",
  "language_code": "sl"
}
-->
# Virtualni enojni računalnik

Namesto nakupa IoT naprave, skupaj s senzorji in aktuatorji, lahko uporabite svoj računalnik za simulacijo IoT strojne opreme. Projekt [CounterFit](https://github.com/CounterFit-IoT/CounterFit) vam omogoča, da lokalno zaženete aplikacijo, ki simulira IoT strojno opremo, kot so senzorji in aktuatorji, ter dostopate do teh senzorjev in aktuatorjev iz lokalne Python kode, napisane na enak način, kot bi jo napisali na Raspberry Pi z uporabo fizične strojne opreme.

## Namestitev

Za uporabo CounterFit boste morali na svoj računalnik namestiti nekaj brezplačne programske opreme.

### Naloga

Namestite potrebno programsko opremo.

1. Namestite Python. Za navodila o namestitvi najnovejše različice Pythona si oglejte [stran za prenose Pythona](https://www.python.org/downloads/).

1. Namestite Visual Studio Code (VS Code). To je urejevalnik, ki ga boste uporabljali za pisanje kode za virtualno napravo v Pythonu. Za navodila o namestitvi VS Code si oglejte [dokumentacijo VS Code](https://code.visualstudio.com?WT.mc_id=academic-17441-jabenn).

    > 💁 Prosto lahko uporabljate katerikoli Python IDE ali urejevalnik za te lekcije, če imate raje kakšno drugo orodje, vendar bodo navodila v lekcijah temeljila na uporabi VS Code.

1. Namestite razširitev VS Code Pylance. To je razširitev za VS Code, ki zagotavlja podporo za Python. Za navodila o namestitvi te razširitve v VS Code si oglejte [dokumentacijo razširitve Pylance](https://marketplace.visualstudio.com/items?WT.mc_id=academic-17441-jabenn&itemName=ms-python.vscode-pylance).

Navodila za namestitev in konfiguracijo aplikacije CounterFit bodo podana ob ustreznem času v navodilih za nalogo, saj se aplikacija namesti za vsak projekt posebej.

## Hello world

Običajno je, da ob začetku uporabe novega programskega jezika ali tehnologije ustvarite aplikacijo 'Hello World' - majhno aplikacijo, ki izpiše besedilo, kot je `"Hello World"`, da preverite, ali so vsa orodja pravilno konfigurirana.

Aplikacija Hello World za virtualno IoT strojno opremo bo zagotovila, da imate pravilno nameščen Python in Visual Studio Code. Prav tako se bo povezala s CounterFit za virtualne IoT senzorje in aktuatorje. Ne bo uporabljala nobene strojne opreme, le povezala se bo, da dokaže, da vse deluje.

Ta aplikacija bo v mapi z imenom `nightlight`, ki bo ponovno uporabljena z različnimi kodami v kasnejših delih te naloge za izdelavo aplikacije nočne lučke.

### Konfiguracija virtualnega okolja za Python

Ena od zmogljivih funkcij Pythona je možnost namestitve [Pip paketov](https://pypi.org) - to so paketi kode, ki jih napišejo drugi ljudje in objavijo na internetu. Pip paket lahko namestite na svoj računalnik z enim ukazom, nato pa ta paket uporabite v svoji kodi. Pip boste uporabljali za namestitev paketa za komunikacijo s CounterFit.

Privzeto, ko namestite paket, je ta na voljo povsod na vašem računalniku, kar lahko povzroči težave z različicami paketov - na primer, ena aplikacija je odvisna od ene različice paketa, ki pa se pokvari, ko namestite novo različico za drugo aplikacijo. Da bi se izognili tej težavi, lahko uporabite [virtualno okolje za Python](https://docs.python.org/3/library/venv.html), ki je v bistvu kopija Pythona v namenski mapi, in ko namestite Pip pakete, se ti namestijo samo v to mapo.

> 💁 Če uporabljate Raspberry Pi, potem na tej napravi niste nastavili virtualnega okolja za upravljanje Pip paketov, ampak uporabljate globalne pakete, saj so Grove paketi globalno nameščeni s skripto za namestitev.

#### Naloga - konfiguracija virtualnega okolja za Python

Konfigurirajte virtualno okolje za Python in namestite Pip pakete za CounterFit.

1. V terminalu ali ukazni vrstici zaženite naslednje na lokaciji po vaši izbiri, da ustvarite in se premaknete v novo mapo:

    ```sh
    mkdir nightlight
    cd nightlight
    ```

1. Zdaj zaženite naslednje, da ustvarite virtualno okolje v mapi `.venv`:

    ```sh
    python3 -m venv .venv
    ```

    > 💁 Izrecno morate poklicati `python3`, da ustvarite virtualno okolje, za primer, če imate nameščen Python 2 poleg Pythona 3 (najnovejše različice). Če imate nameščen Python 2, bo klic `python` uporabil Python 2 namesto Pythona 3.

1. Aktivirajte virtualno okolje:

    * Na Windows:
        * Če uporabljate Command Prompt ali Command Prompt prek Windows Terminala, zaženite:

            ```cmd
            .venv\Scripts\activate.bat
            ```

        * Če uporabljate PowerShell, zaženite:

            ```powershell
            .\.venv\Scripts\Activate.ps1
            ```

            > Če dobite napako o tem, da je izvajanje skriptov onemogočeno na tem sistemu, boste morali omogočiti izvajanje skriptov z nastavitvijo ustrezne politike izvajanja. To lahko storite tako, da zaženete PowerShell kot skrbnik in nato zaženete naslednji ukaz:

            ```powershell
            Set-ExecutionPolicy -ExecutionPolicy Unrestricted
            ```

            Vnesite `Y`, ko vas pozove k potrditvi. Nato ponovno zaženite PowerShell in poskusite znova.

            Politiko izvajanja lahko po potrebi pozneje ponastavite. Več o tem si lahko preberete na [strani o politikah izvajanja v Microsoft Docs](https://docs.microsoft.com/powershell/module/microsoft.powershell.core/about/about_execution_policies?WT.mc_id=academic-17441-jabenn).

    * Na macOS ali Linux zaženite:

        ```cmd
        source ./.venv/bin/activate
        ```

    > 💁 Te ukaze je treba zagnati z iste lokacije, kjer ste zagnali ukaz za ustvarjanje virtualnega okolja. Nikoli vam ne bo treba navigirati v mapo `.venv`, vedno morate zagnati ukaz za aktivacijo in ukaze za namestitev paketov ali zagon kode iz mape, v kateri ste bili, ko ste ustvarili virtualno okolje.

1. Ko je virtualno okolje aktivirano, bo privzeti ukaz `python` zagnal različico Pythona, ki je bila uporabljena za ustvarjanje virtualnega okolja. Zaženite naslednje, da preverite različico:

    ```sh
    python --version
    ```

    Izhod bi moral vsebovati naslednje:

    ```output
    (.venv) ➜  nightlight python --version
    Python 3.9.1
    ```

    > 💁 Vaša različica Pythona je lahko drugačna - dokler je različica 3.6 ali višja, je vse v redu. Če ni, izbrišite to mapo, namestite novejšo različico Pythona in poskusite znova.

1. Zaženite naslednje ukaze za namestitev Pip paketov za CounterFit. Ti paketi vključujejo glavno aplikacijo CounterFit ter shime za strojno opremo Grove. Ti shimi vam omogočajo pisanje kode, kot da bi programirali z uporabo fizičnih senzorjev in aktuatorjev iz ekosistema Grove, vendar povezanih z virtualnimi IoT napravami.

    ```sh
    pip install CounterFit
    pip install counterfit-connection
    pip install counterfit-shims-grove
    ```

    Ti Pip paketi bodo nameščeni samo v virtualnem okolju in ne bodo na voljo zunaj njega.

### Napišite kodo

Ko je virtualno okolje za Python pripravljeno, lahko napišete kodo za aplikacijo 'Hello World'.

#### Naloga - napišite kodo

Ustvarite Python aplikacijo, ki izpiše `"Hello World"` v konzolo.

1. V terminalu ali ukazni vrstici zaženite naslednje znotraj virtualnega okolja, da ustvarite Python datoteko z imenom `app.py`:

    * Na Windows zaženite:

        ```cmd
        type nul > app.py
        ```

    * Na macOS ali Linux zaženite:

        ```cmd
        touch app.py
        ```

1. Odprite trenutno mapo v VS Code:

    ```sh
    code .
    ```

    > 💁 Če vaš terminal na macOS vrne `command not found`, to pomeni, da VS Code ni bil dodan v vaš PATH. VS Code lahko dodate v PATH tako, da sledite navodilom v [razdelku o zagonu iz ukazne vrstice v dokumentaciji VS Code](https://code.visualstudio.com/docs/setup/mac?WT.mc_id=academic-17441-jabenn#_launching-from-the-command-line) in nato zaženete ukaz. VS Code je privzeto dodan v PATH na Windows in Linux.

1. Ko se VS Code zažene, bo aktiviral virtualno okolje za Python. Izbrano virtualno okolje bo prikazano v spodnji vrstici stanja:

    ![VS Code prikazuje izbrano virtualno okolje](../../../../../translated_images/sl/vscode-virtual-env.8ba42e04c3d533cf.webp)

1. Če je terminal VS Code že aktiven, ko se VS Code zažene, virtualno okolje v njem ne bo aktivirano. Najlažje je ubiti terminal z gumbom **Kill the active terminal instance**:

    ![Gumb za ubijanje aktivnega terminala v VS Code](../../../../../translated_images/sl/vscode-kill-terminal.1cc4de7c6f25ee08.webp)

    Prepoznate lahko, ali je terminal aktiviral virtualno okolje, saj bo ime virtualnega okolja predpona na ukaznem pozivu terminala. Na primer, lahko je:

    ```sh
    (.venv) ➜  nightlight
    ```

    Če na pozivu ni `.venv` kot predpone, virtualno okolje ni aktivno v terminalu.

1. Zaženite nov terminal v VS Code z izbiro *Terminal -> New Terminal* ali s pritiskom na `` CTRL+` ``. Nov terminal bo naložil virtualno okolje, klic za aktivacijo pa se bo pojavil v terminalu. Poziv bo imel tudi ime virtualnega okolja (`.venv`):

    ```output
    ➜  nightlight source .venv/bin/activate
    (.venv) ➜  nightlight 
    ```

1. Odprite datoteko `app.py` iz raziskovalca VS Code in dodajte naslednjo kodo:

    ```python
    print('Hello World!')
    ```

    Funkcija `print` izpiše karkoli ji je podano v konzolo.

1. V terminalu VS Code zaženite naslednje, da zaženete svojo Python aplikacijo:

    ```sh
    python app.py
    ```

    Izhod bo vseboval naslednje:

    ```output
    (.venv) ➜  nightlight python app.py 
    Hello World!
    ```

😀 Vaš program 'Hello World' je bil uspešen!

### Povežite 'strojno opremo'

Kot drugi korak 'Hello World' boste zagnali aplikacijo CounterFit in jo povezali s svojo kodo. To je virtualni ekvivalent priklopa IoT strojne opreme na razvojni komplet.

#### Naloga - povežite 'strojno opremo'

1. V terminalu VS Code zaženite aplikacijo CounterFit z naslednjim ukazom:

    ```sh
    counterfit
    ```

    Aplikacija se bo začela izvajati in odprla v vašem spletnem brskalniku:

    ![Aplikacija CounterFit, ki se izvaja v brskalniku](../../../../../translated_images/sl/counterfit-first-run.433326358b669b31d0e99c3513cb01bfbb13724d162c99cdcc8f51ecf5f9c779.png)

    Označena bo kot *Disconnected*, z LED lučko v zgornjem desnem kotu, ki bo ugasnjena.

1. Dodajte naslednjo kodo na vrh datoteke `app.py`:

    ```python
    from counterfit_connection import CounterFitConnection
    CounterFitConnection.init('127.0.0.1', 5000)
    ```

    Ta koda uvozi razred `CounterFitConnection` iz modula `counterfit_connection`, ki prihaja iz Pip paketa `counterfit-connection`, ki ste ga prej namestili. Nato inicializira povezavo z aplikacijo CounterFit, ki se izvaja na `127.0.0.1`, kar je IP naslov, ki ga lahko vedno uporabite za dostop do svojega lokalnega računalnika (pogosto imenovan *localhost*), na vratih 5000.

    > 💁 Če imate druge aplikacije, ki se izvajajo na vratih 5000, lahko to spremenite tako, da posodobite vrata v kodi in zaženete CounterFit z ukazom `CounterFit --port <port_number>`, pri čemer `<port_number>` zamenjate s številko vrat, ki jih želite uporabiti.

1. Morali boste zagnati nov terminal v VS Code z izbiro gumba **Create a new integrated terminal**. To je zato, ker se aplikacija CounterFit izvaja v trenutnem terminalu.

    ![Gumb za ustvarjanje novega integriranega terminala v VS Code](../../../../../translated_images/sl/vscode-new-terminal.77db8fc0f9cd3182.webp)

1. V tem novem terminalu zaženite datoteko `app.py` kot prej. Status CounterFit se bo spremenil v **Connected**, LED lučka pa se bo prižgala.

    ![CounterFit prikazuje status Connected](../../../../../translated_images/sl/counterfit-connected.ed30b46d8f79b0921f3fc70be10366e596a89dca3f80c2224a9d9fc98fccf884.png)

> 💁 To kodo lahko najdete v mapi [code/virtual-device](../../../../../1-getting-started/lessons/1-introduction-to-iot/code/virtual-device).

😀 Vaša povezava s strojno opremo je bila uspešna!

---

**Omejitev odgovornosti**:  
Ta dokument je bil preveden z uporabo storitve za prevajanje z umetno inteligenco [Co-op Translator](https://github.com/Azure/co-op-translator). Čeprav si prizadevamo za natančnost, vas prosimo, da upoštevate, da lahko avtomatizirani prevodi vsebujejo napake ali netočnosti. Izvirni dokument v njegovem maternem jeziku je treba obravnavati kot avtoritativni vir. Za ključne informacije priporočamo profesionalni človeški prevod. Ne prevzemamo odgovornosti za morebitna nesporazumevanja ali napačne razlage, ki bi nastale zaradi uporabe tega prevoda.