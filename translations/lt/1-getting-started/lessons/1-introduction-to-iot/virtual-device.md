<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "52b4de6144b2efdced7797a5339d6035",
  "translation_date": "2025-08-28T20:01:43+00:00",
  "source_file": "1-getting-started/lessons/1-introduction-to-iot/virtual-device.md",
  "language_code": "lt"
}
-->
# Virtualus vieno plokštės kompiuteris

Užuot pirkę IoT įrenginį kartu su jutikliais ir aktuatoriais, galite naudoti savo kompiuterį, kad simuliuotumėte IoT techninę įrangą. [CounterFit projektas](https://github.com/CounterFit-IoT/CounterFit) leidžia paleisti programą lokaliai, kuri simuliuoja IoT techninę įrangą, tokią kaip jutikliai ir aktuatoriai, ir pasiekti juos iš vietinio Python kodo, parašyto taip pat, kaip rašytumėte kodą Raspberry Pi naudojant fizinę techninę įrangą.

## Paruošimas

Norėdami naudoti CounterFit, turėsite įdiegti nemokamą programinę įrangą savo kompiuteryje.

### Užduotis

Įdiekite reikiamą programinę įrangą.

1. Įdiekite Python. Instrukcijas, kaip įdiegti naujausią Python versiją, rasite [Python atsisiuntimų puslapyje](https://www.python.org/downloads/).

1. Įdiekite Visual Studio Code (VS Code). Tai redaktorius, kurį naudosite rašydami virtualaus įrenginio kodą Python kalba. Instrukcijas, kaip įdiegti VS Code, rasite [VS Code dokumentacijoje](https://code.visualstudio.com?WT.mc_id=academic-17441-jabenn).

    > 💁 Galite naudoti bet kurį Python IDE ar redaktorių, jei turite mėgstamą įrankį, tačiau pamokose bus pateiktos instrukcijos, pagrįstos VS Code naudojimu.

1. Įdiekite VS Code Pylance plėtinį. Tai VS Code plėtinys, kuris suteikia Python kalbos palaikymą. Instrukcijas, kaip įdiegti šį plėtinį VS Code, rasite [Pylance plėtinio dokumentacijoje](https://marketplace.visualstudio.com/items?WT.mc_id=academic-17441-jabenn&itemName=ms-python.vscode-pylance).

Instrukcijos, kaip įdiegti ir sukonfigūruoti CounterFit programą, bus pateiktos atitinkamu metu užduočių instrukcijose, nes ji įdiegiama kiekvienam projektui atskirai.

## Sveikas pasauli!

Pradėjus naudoti naują programavimo kalbą ar technologiją, tradiciškai sukuriama „Sveikas pasauli!“ programa – nedidelė programa, kuri išveda tekstą, pvz., `"Sveikas pasauli!"`, kad parodytų, jog visi įrankiai yra tinkamai sukonfigūruoti.

„Sveikas pasauli!“ programa virtualiai IoT techninei įrangai užtikrins, kad Python ir Visual Studio Code būtų tinkamai įdiegti. Ji taip pat prisijungs prie CounterFit, kad galėtų naudoti virtualius IoT jutiklius ir aktuatorius. Ji nenaudos jokios techninės įrangos, tiesiog prisijungs, kad įrodytų, jog viskas veikia.

Ši programa bus aplanke, pavadintame `nightlight`, ir ji bus naudojama su skirtingu kodu vėlesnėse šios užduoties dalyse, kad būtų sukurta naktinė lemputė.

### Konfigūruokite Python virtualią aplinką

Viena iš galingų Python funkcijų yra galimybė įdiegti [Pip paketus](https://pypi.org) – tai kitų žmonių parašyti ir internete publikuoti kodų paketai. Galite įdiegti Pip paketą savo kompiuteryje vienu komandu ir naudoti tą paketą savo kode. Naudosite Pip, kad įdiegtumėte paketą, skirtą bendrauti su CounterFit.

Pagal numatymą, kai įdiegiate paketą, jis tampa prieinamas visur jūsų kompiuteryje, ir tai gali sukelti problemų su paketų versijomis – pavyzdžiui, viena programa priklauso nuo vienos paketo versijos, kuri sugenda, kai įdiegiate naują versiją kitai programai. Norėdami išspręsti šią problemą, galite naudoti [Python virtualią aplinką](https://docs.python.org/3/library/venv.html), iš esmės Python kopiją dedikuotame aplanke, ir kai įdiegiate Pip paketus, jie įdiegiami tik tame aplanke.

> 💁 Jei naudojate Raspberry Pi, tuomet nesukūrėte virtualios aplinkos tam įrenginiui valdyti Pip paketus, vietoj to naudojate globalius paketus, nes Grove paketai yra įdiegti globaliai per diegimo scenarijų.

#### Užduotis – konfigūruokite Python virtualią aplinką

Konfigūruokite Python virtualią aplinką ir įdiekite Pip paketus, skirtus CounterFit.

1. Terminale arba komandų eilutėje paleiskite šiuos veiksmus pasirinktoje vietoje, kad sukurtumėte ir pereitumėte į naują katalogą:

    ```sh
    mkdir nightlight
    cd nightlight
    ```

1. Dabar paleiskite šiuos veiksmus, kad sukurtumėte virtualią aplinką `.venv` aplanke:

    ```sh
    python3 -m venv .venv
    ```

    > 💁 Turite aiškiai nurodyti `python3`, kad sukurtumėte virtualią aplinką, jei turite įdiegtą Python 2 be Python 3 (naujausia versija). Jei turite įdiegtą Python 2, tada paleidus `python` bus naudojamas Python 2 vietoj Python 3.

1. Aktyvuokite virtualią aplinką:

    * Windows sistemoje:
        * Jei naudojate Command Prompt arba Command Prompt per Windows Terminal, paleiskite:

            ```cmd
            .venv\Scripts\activate.bat
            ```

        * Jei naudojate PowerShell, paleiskite:

            ```powershell
            .\.venv\Scripts\Activate.ps1
            ```

            > Jei gaunate klaidą apie tai, kad scenarijų paleidimas yra išjungtas šioje sistemoje, turėsite įjungti scenarijų paleidimą nustatydami tinkamą vykdymo politiką. Tai galite padaryti paleisdami PowerShell kaip administratorius, tada paleisdami šią komandą:

            ```powershell
            Set-ExecutionPolicy -ExecutionPolicy Unrestricted
            ```

            Patvirtinimui įveskite `Y`. Tada iš naujo paleiskite PowerShell ir bandykite dar kartą.

            Jei reikia, vėliau galite atstatyti šią vykdymo politiką. Daugiau apie tai galite perskaityti [Microsoft Docs puslapyje apie vykdymo politiką](https://docs.microsoft.com/powershell/module/microsoft.powershell.core/about/about_execution_policies?WT.mc_id=academic-17441-jabenn).

    * macOS arba Linux sistemoje paleiskite:

        ```cmd
        source ./.venv/bin/activate
        ```

    > 💁 Šios komandos turėtų būti paleistos iš tos pačios vietos, kur paleidote komandą, kad sukurtumėte virtualią aplinką. Jums niekada nereikės pereiti į `.venv` aplanką, visada turėtumėte paleisti aktyvavimo komandą ir bet kokias komandas, skirtas paketų įdiegimui ar kodo paleidimui, iš aplanko, kuriame buvote, kai sukūrėte virtualią aplinką.

1. Kai virtuali aplinka bus aktyvuota, numatytoji `python` komanda paleis Python versiją, kuri buvo naudojama kuriant virtualią aplinką. Paleiskite šią komandą, kad gautumėte versiją:

    ```sh
    python --version
    ```

    Rezultate turėtų būti:

    ```output
    (.venv) ➜  nightlight python --version
    Python 3.9.1
    ```

    > 💁 Jūsų Python versija gali būti kitokia – jei ji yra 3.6 ar naujesnė, viskas gerai. Jei ne, ištrinkite šį aplanką, įdiekite naujesnę Python versiją ir bandykite dar kartą.

1. Paleiskite šias komandas, kad įdiegtumėte Pip paketus, skirtus CounterFit. Šie paketai apima pagrindinę CounterFit programą, taip pat Grove techninės įrangos šimus. Šimai leidžia rašyti kodą taip, tarsi programuotumėte naudodami fizinius jutiklius ir aktuatorius iš Grove ekosistemos, bet prijungtus prie virtualių IoT įrenginių.

    ```sh
    pip install CounterFit
    pip install counterfit-connection
    pip install counterfit-shims-grove
    ```

    Šie Pip paketai bus įdiegti tik virtualioje aplinkoje ir nebus prieinami už jos ribų.

### Parašykite kodą

Kai Python virtuali aplinka bus paruošta, galite parašyti kodą „Sveikas pasauli!“ programai.

#### Užduotis – parašykite kodą

Sukurkite Python programą, kuri išveda `"Sveikas pasauli!"` į konsolę.

1. Terminale arba komandų eilutėje paleiskite šiuos veiksmus virtualioje aplinkoje, kad sukurtumėte Python failą, pavadintą `app.py`:

    * Windows sistemoje paleiskite:

        ```cmd
        type nul > app.py
        ```

    * macOS arba Linux sistemoje paleiskite:

        ```cmd
        touch app.py
        ```

1. Atidarykite dabartinį aplanką VS Code:

    ```sh
    code .
    ```

    > 💁 Jei jūsų terminalas macOS sistemoje grąžina `command not found`, tai reiškia, kad VS Code nebuvo pridėtas prie jūsų PATH. Galite pridėti VS Code prie PATH, vadovaudamiesi instrukcijomis [VS Code dokumentacijos skyriuje apie paleidimą iš komandų eilutės](https://code.visualstudio.com/docs/setup/mac?WT.mc_id=academic-17441-jabenn#_launching-from-the-command-line) ir paleisti komandą vėliau. VS Code pagal numatymą pridedamas prie PATH Windows ir Linux sistemose.

1. Kai VS Code paleidžiamas, jis aktyvuoja Python virtualią aplinką. Pasirinkta virtuali aplinka bus rodoma apatiniame būsenos juostoje:

    ![VS Code rodoma pasirinkta virtuali aplinka](../../../../../translated_images/lt/vscode-virtual-env.8ba42e04c3d533cf.webp)

1. Jei VS Code terminalas jau veikia, kai VS Code paleidžiamas, jis neturės aktyvuotos virtualios aplinkos. Lengviausias būdas yra uždaryti terminalą naudojant **Kill the active terminal instance** mygtuką:

    ![VS Code Kill the active terminal instance mygtukas](../../../../../translated_images/lt/vscode-kill-terminal.1cc4de7c6f25ee08.webp)

    Galite pasakyti, ar terminalas turi aktyvuotą virtualią aplinką, nes terminalo raginime bus virtualios aplinkos pavadinimas kaip prefiksas. Pavyzdžiui, tai gali būti:

    ```sh
    (.venv) ➜  nightlight
    ```

    Jei neturite `.venv` kaip prefikso raginime, virtuali aplinka nėra aktyvuota terminale.

1. Paleiskite naują VS Code terminalą pasirinkdami *Terminal -> New Terminal* arba paspausdami `` CTRL+` ``. Naujas terminalas įkels virtualią aplinką, o aktyvavimo komanda pasirodys terminale. Raginime taip pat bus virtualios aplinkos pavadinimas (`.venv`):

    ```output
    ➜  nightlight source .venv/bin/activate
    (.venv) ➜  nightlight 
    ```

1. Atidarykite `app.py` failą iš VS Code naršyklės ir pridėkite šį kodą:

    ```python
    print('Hello World!')
    ```

    `print` funkcija išveda tai, kas perduodama jai, į konsolę.

1. Iš VS Code terminalo paleiskite šią komandą, kad paleistumėte savo Python programą:

    ```sh
    python app.py
    ```

    Rezultate bus:

    ```output
    (.venv) ➜  nightlight python app.py 
    Hello World!
    ```

😀 Jūsų „Sveikas pasauli!“ programa buvo sėkminga!

### Prijunkite „techninę įrangą“

Kaip antrą „Sveikas pasauli!“ žingsnį, paleisite CounterFit programą ir prijungsite savo kodą prie jos. Tai yra virtualus ekvivalentas prijungti IoT techninę įrangą prie kūrimo rinkinio.

#### Užduotis – prijunkite „techninę įrangą“

1. Iš VS Code terminalo paleiskite CounterFit programą naudodami šią komandą:

    ```sh
    counterfit
    ```

    Programa pradės veikti ir atsidarys jūsų interneto naršyklėje:

    ![Counter Fit programa veikia naršyklėje](../../../../../translated_images/lt/counterfit-first-run.433326358b669b31d0e99c3513cb01bfbb13724d162c99cdcc8f51ecf5f9c779.png)

    Ji bus pažymėta kaip *Disconnected*, o LED viršutiniame dešiniajame kampe bus išjungtas.

1. Pridėkite šį kodą į `app.py` failo viršų:

    ```python
    from counterfit_connection import CounterFitConnection
    CounterFitConnection.init('127.0.0.1', 5000)
    ```

    Šis kodas importuoja `CounterFitConnection` klasę iš `counterfit_connection` modulio, kuris yra iš `counterfit-connection` pip paketo, kurį įdiegėte anksčiau. Tada jis inicializuoja ryšį su CounterFit programa, veikiančia `127.0.0.1`, tai yra IP adresas, kurį visada galite naudoti norėdami pasiekti savo vietinį kompiuterį (dažnai vadinamą *localhost*), per 5000 prievadą.

    > 💁 Jei turite kitų programų, veikiančių per 5000 prievadą, galite tai pakeisti atnaujindami prievadą kode ir paleisdami CounterFit naudodami `CounterFit --port <port_number>`, pakeisdami `<port_number>` į norimą prievadą.

1. Turėsite paleisti naują VS Code terminalą pasirinkdami **Create a new integrated terminal** mygtuką. Taip yra todėl, kad CounterFit programa veikia dabartiniame terminale.

    ![VS Code Create a new integrated terminal mygtukas](../../../../../translated_images/lt/vscode-new-terminal.77db8fc0f9cd3182.webp)

1. Šiame naujame terminale paleiskite `app.py` failą kaip anksčiau. CounterFit būsena pasikeis į **Connected**, o LED užsidegs.

    ![Counter Fit rodo kaip prijungtą](../../../../../translated_images/lt/counterfit-connected.ed30b46d8f79b0921f3fc70be10366e596a89dca3f80c2224a9d9fc98fccf884.png)

> 💁 Šį kodą galite rasti [code/virtual-device](../../../../../1-getting-started/lessons/1-introduction-to-iot/code/virtual-device) aplanke.

😀 Jūsų ryšys su technine įranga buvo sėkmingas!

---

**Atsakomybės apribojimas**:  
Šis dokumentas buvo išverstas naudojant AI vertimo paslaugą [Co-op Translator](https://github.com/Azure/co-op-translator). Nors siekiame tikslumo, prašome atkreipti dėmesį, kad automatiniai vertimai gali turėti klaidų ar netikslumų. Originalus dokumentas jo gimtąja kalba turėtų būti laikomas autoritetingu šaltiniu. Kritinei informacijai rekomenduojama naudoti profesionalų žmogaus vertimą. Mes neprisiimame atsakomybės už nesusipratimus ar klaidingus interpretavimus, atsiradusius dėl šio vertimo naudojimo.