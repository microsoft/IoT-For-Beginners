<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "52b4de6144b2efdced7797a5339d6035",
  "translation_date": "2025-08-28T10:21:41+00:00",
  "source_file": "1-getting-started/lessons/1-introduction-to-iot/virtual-device.md",
  "language_code": "ro"
}
-->
# Computer virtual cu o singură placă

În loc să achiziționați un dispozitiv IoT, împreună cu senzori și actuatori, puteți utiliza computerul pentru a simula hardware-ul IoT. Proiectul [CounterFit](https://github.com/CounterFit-IoT/CounterFit) vă permite să rulați o aplicație locală care simulează hardware-ul IoT, cum ar fi senzori și actuatori, și să accesați acești senzori și actuatori din cod Python local, scris în același mod în care ați scrie cod pe un Raspberry Pi folosind hardware fizic.

## Configurare

Pentru a utiliza CounterFit, va trebui să instalați câteva programe gratuite pe computerul dvs.

### Sarcină

Instalați software-ul necesar.

1. Instalați Python. Consultați [pagina de descărcări Python](https://www.python.org/downloads/) pentru instrucțiuni despre instalarea celei mai recente versiuni de Python.

1. Instalați Visual Studio Code (VS Code). Acesta este editorul pe care îl veți folosi pentru a scrie codul dispozitivului virtual în Python. Consultați [documentația VS Code](https://code.visualstudio.com?WT.mc_id=academic-17441-jabenn) pentru instrucțiuni despre instalarea VS Code.

    > 💁 Sunteți liber să utilizați orice IDE sau editor Python pentru aceste lecții dacă aveți un instrument preferat, dar lecțiile vor oferi instrucțiuni bazate pe utilizarea VS Code.

1. Instalați extensia VS Code Pylance. Aceasta este o extensie pentru VS Code care oferă suport pentru limbajul Python. Consultați [documentația extensiei Pylance](https://marketplace.visualstudio.com/items?WT.mc_id=academic-17441-jabenn&itemName=ms-python.vscode-pylance) pentru instrucțiuni despre instalarea acestei extensii în VS Code.

Instrucțiunile pentru instalarea și configurarea aplicației CounterFit vor fi oferite la momentul relevant în instrucțiunile de sarcină, deoarece aceasta este instalată pe baza fiecărui proiect.

## Hello world

Este tradițional ca atunci când începeți să lucrați cu un nou limbaj de programare sau tehnologie să creați o aplicație 'Hello World' - o mică aplicație care afișează textul `"Hello World"` pentru a demonstra că toate instrumentele sunt configurate corect.

Aplicația Hello World pentru hardware-ul IoT virtual va asigura că aveți Python și Visual Studio Code instalate corect. De asemenea, se va conecta la CounterFit pentru senzorii și actuatorii IoT virtuali. Nu va folosi niciun hardware, ci doar se va conecta pentru a demonstra că totul funcționează.

Această aplicație va fi într-un folder numit `nightlight`, și va fi reutilizată cu cod diferit în părțile ulterioare ale acestei sarcini pentru a construi aplicația nightlight.

### Configurarea unui mediu virtual Python

Una dintre caracteristicile puternice ale Python este abilitatea de a instala [pachete Pip](https://pypi.org) - acestea sunt pachete de cod scrise de alte persoane și publicate pe Internet. Puteți instala un pachet Pip pe computerul dvs. cu o singură comandă, apoi utilizați acel pachet în codul dvs. Veți folosi Pip pentru a instala un pachet care să comunice cu CounterFit.

În mod implicit, atunci când instalați un pachet, acesta este disponibil peste tot pe computerul dvs., iar acest lucru poate duce la probleme cu versiunile pachetelor - cum ar fi o aplicație care depinde de o versiune a unui pachet care se strică atunci când instalați o versiune nouă pentru o altă aplicație. Pentru a evita această problemă, puteți utiliza un [mediu virtual Python](https://docs.python.org/3/library/venv.html), practic o copie a Python într-un folder dedicat, iar când instalați pachete Pip, acestea sunt instalate doar în acel folder.

> 💁 Dacă utilizați un Raspberry Pi, atunci nu ați configurat un mediu virtual pe acel dispozitiv pentru a gestiona pachetele Pip, ci utilizați pachete globale, deoarece pachetele Grove sunt instalate global de scriptul de instalare.

#### Sarcină - configurarea unui mediu virtual Python

Configurați un mediu virtual Python și instalați pachetele Pip pentru CounterFit.

1. Din terminalul sau linia de comandă, rulați următoarele într-o locație la alegerea dvs. pentru a crea și naviga într-un nou director:

    ```sh
    mkdir nightlight
    cd nightlight
    ```

1. Acum rulați următoarele pentru a crea un mediu virtual în folderul `.venv`:

    ```sh
    python3 -m venv .venv
    ```

    > 💁 Trebuie să apelați explicit `python3` pentru a crea mediul virtual, în cazul în care aveți instalat Python 2 pe lângă Python 3 (cea mai recentă versiune). Dacă aveți instalat Python 2, atunci apelarea `python` va folosi Python 2 în loc de Python 3.

1. Activați mediul virtual:

    * Pe Windows:
        * Dacă utilizați Command Prompt sau Command Prompt prin Windows Terminal, rulați:

            ```cmd
            .venv\Scripts\activate.bat
            ```

        * Dacă utilizați PowerShell, rulați:

            ```powershell
            .\.venv\Scripts\Activate.ps1
            ```

            > Dacă primiți o eroare despre faptul că rularea scripturilor este dezactivată pe acest sistem, va trebui să activați rularea scripturilor prin setarea unei politici de execuție adecvate. Puteți face acest lucru lansând PowerShell ca administrator, apoi rulând următoarea comandă:

            ```powershell
            Set-ExecutionPolicy -ExecutionPolicy Unrestricted
            ```

            Introduceți `Y` când vi se cere să confirmați. Apoi relansați PowerShell și încercați din nou.

            Puteți reseta această politică de execuție la o dată ulterioară, dacă este necesar. Puteți citi mai multe despre acest lucru în [pagina despre politici de execuție pe Microsoft Docs](https://docs.microsoft.com/powershell/module/microsoft.powershell.core/about/about_execution_policies?WT.mc_id=academic-17441-jabenn).

    * Pe macOS sau Linux, rulați:

        ```cmd
        source ./.venv/bin/activate
        ```

    > 💁 Aceste comenzi ar trebui să fie rulate din aceeași locație în care ați rulat comanda pentru a crea mediul virtual. Nu va trebui niciodată să navigați în folderul `.venv`, ar trebui să rulați întotdeauna comanda de activare și orice comenzi pentru instalarea pachetelor sau rularea codului din folderul în care ați fost când ați creat mediul virtual.

1. Odată ce mediul virtual a fost activat, comanda implicită `python` va rula versiunea de Python care a fost utilizată pentru a crea mediul virtual. Rulați următoarea comandă pentru a obține versiunea:

    ```sh
    python --version
    ```

    Rezultatul ar trebui să conțină următoarele:

    ```output
    (.venv) ➜  nightlight python --version
    Python 3.9.1
    ```

    > 💁 Versiunea dvs. de Python poate fi diferită - atâta timp cât este versiunea 3.6 sau mai mare, este în regulă. Dacă nu, ștergeți acest folder, instalați o versiune mai nouă de Python și încercați din nou.

1. Rulați următoarele comenzi pentru a instala pachetele Pip pentru CounterFit. Aceste pachete includ aplicația principală CounterFit, precum și shims pentru hardware-ul Grove. Aceste shims vă permit să scrieți cod ca și cum ați programa folosind senzori și actuatori fizici din ecosistemul Grove, dar conectați la dispozitive IoT virtuale.

    ```sh
    pip install CounterFit
    pip install counterfit-connection
    pip install counterfit-shims-grove
    ```

    Aceste pachete Pip vor fi instalate doar în mediul virtual și nu vor fi disponibile în afara acestuia.

### Scrieți codul

Odată ce mediul virtual Python este pregătit, puteți scrie codul pentru aplicația 'Hello World'.

#### Sarcină - scrieți codul

Creați o aplicație Python pentru a afișa `"Hello World"` în consolă.

1. Din terminalul sau linia de comandă, rulați următoarele în mediul virtual pentru a crea un fișier Python numit `app.py`:

    * Pe Windows, rulați:

        ```cmd
        type nul > app.py
        ```

    * Pe macOS sau Linux, rulați:

        ```cmd
        touch app.py
        ```

1. Deschideți folderul curent în VS Code:

    ```sh
    code .
    ```

    > 💁 Dacă terminalul dvs. returnează `command not found` pe macOS, înseamnă că VS Code nu a fost adăugat la PATH-ul dvs. Puteți adăuga VS Code la PATH urmând instrucțiunile din [secțiunea despre lansarea din linia de comandă din documentația VS Code](https://code.visualstudio.com/docs/setup/mac?WT.mc_id=academic-17441-jabenn#_launching-from-the-command-line) și rulați comanda ulterior. VS Code este instalat în mod implicit în PATH pe Windows și Linux.

1. Când VS Code se lansează, va activa mediul virtual Python. Mediul virtual selectat va apărea în bara de stare de jos:

    ![VS Code arătând mediul virtual selectat](../../../../../translated_images/ro/vscode-virtual-env.8ba42e04c3d533cf.webp)

1. Dacă terminalul VS Code este deja activ când VS Code pornește, acesta nu va avea mediul virtual activat. Cel mai simplu lucru de făcut este să închideți terminalul folosind butonul **Kill the active terminal instance**:

    ![Butonul VS Code Kill the active terminal instance](../../../../../translated_images/ro/vscode-kill-terminal.1cc4de7c6f25ee08.webp)

    Puteți spune dacă terminalul are mediul virtual activat, deoarece numele mediului virtual va fi un prefix pe promptul terminalului. De exemplu, ar putea fi:

    ```sh
    (.venv) ➜  nightlight
    ```

    Dacă nu aveți `.venv` ca prefix pe prompt, mediul virtual nu este activ în terminal.

1. Lansați un nou terminal VS Code selectând *Terminal -> New Terminal*, sau apăsând `` CTRL+` ``. Noul terminal va încărca mediul virtual, iar apelul pentru activarea acestuia va apărea în terminal. Promptul va avea, de asemenea, numele mediului virtual (`.venv`):

    ```output
    ➜  nightlight source .venv/bin/activate
    (.venv) ➜  nightlight 
    ```

1. Deschideți fișierul `app.py` din exploratorul VS Code și adăugați următorul cod:

    ```python
    print('Hello World!')
    ```

    Funcția `print` afișează în consolă ceea ce este transmis către ea.

1. Din terminalul VS Code, rulați următoarea comandă pentru a rula aplicația Python:

    ```sh
    python app.py
    ```

    Următorul text va fi în output:

    ```output
    (.venv) ➜  nightlight python app.py 
    Hello World!
    ```

😀 Programul dvs. 'Hello World' a fost un succes!

### Conectați 'hardware-ul'

Ca un al doilea pas 'Hello World', veți rula aplicația CounterFit și veți conecta codul dvs. la aceasta. Acesta este echivalentul virtual al conectării unui hardware IoT la un kit de dezvoltare.

#### Sarcină - conectați 'hardware-ul'

1. Din terminalul VS Code, lansați aplicația CounterFit cu următoarea comandă:

    ```sh
    counterfit
    ```

    Aplicația va începe să ruleze și se va deschide în browserul dvs. web:

    ![Aplicația Counter Fit rulând într-un browser](../../../../../translated_images/ro/counterfit-first-run.433326358b669b31d0e99c3513cb01bfbb13724d162c99cdcc8f51ecf5f9c779.png)

    Va fi marcată ca *Disconnected*, cu LED-ul din colțul din dreapta sus stins.

1. Adăugați următorul cod în partea de sus a fișierului `app.py`:

    ```python
    from counterfit_connection import CounterFitConnection
    CounterFitConnection.init('127.0.0.1', 5000)
    ```

    Acest cod importă clasa `CounterFitConnection` din modulul `counterfit_connection`, care provine din pachetul pip `counterfit-connection` pe care l-ați instalat anterior. Apoi inițializează o conexiune la aplicația CounterFit care rulează pe `127.0.0.1`, care este o adresă IP pe care o puteți folosi întotdeauna pentru a accesa computerul local (adesea denumit *localhost*), pe portul 5000.

    > 💁 Dacă aveți alte aplicații care rulează pe portul 5000, puteți schimba acest lucru actualizând portul în cod și rulând CounterFit folosind `CounterFit --port <port_number>`, înlocuind `<port_number>` cu portul pe care doriți să îl utilizați.

1. Va trebui să lansați un nou terminal VS Code selectând butonul **Create a new integrated terminal**. Acest lucru se datorează faptului că aplicația CounterFit rulează în terminalul curent.

    ![Butonul VS Code Create a new integrated terminal](../../../../../translated_images/ro/vscode-new-terminal.77db8fc0f9cd3182.webp)

1. În acest nou terminal, rulați fișierul `app.py` ca înainte. Statusul CounterFit se va schimba la **Connected**, iar LED-ul se va aprinde.

    ![Counter Fit arătând ca fiind conectat](../../../../../translated_images/ro/counterfit-connected.ed30b46d8f79b0921f3fc70be10366e596a89dca3f80c2224a9d9fc98fccf884.png)

> 💁 Puteți găsi acest cod în folderul [code/virtual-device](../../../../../1-getting-started/lessons/1-introduction-to-iot/code/virtual-device).

😀 Conexiunea dvs. la hardware a fost un succes!

---

**Declinare de responsabilitate**:  
Acest document a fost tradus folosind serviciul de traducere AI [Co-op Translator](https://github.com/Azure/co-op-translator). Deși ne străduim să asigurăm acuratețea, vă rugăm să rețineți că traducerile automate pot conține erori sau inexactități. Documentul original în limba sa natală ar trebui considerat sursa autoritară. Pentru informații critice, se recomandă traducerea profesională realizată de un specialist uman. Nu ne asumăm responsabilitatea pentru eventualele neînțelegeri sau interpretări greșite care pot apărea din utilizarea acestei traduceri.