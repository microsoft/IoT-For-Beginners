# Virtualno računalo s jednom pločom

Umjesto kupnje IoT uređaja, zajedno sa senzorima i aktuatorima, možete koristiti svoje računalo za simulaciju IoT hardvera. [CounterFit projekt](https://github.com/CounterFit-IoT/CounterFit) omogućuje vam pokretanje aplikacije lokalno koja simulira IoT hardver poput senzora i aktuatora te pristup tim senzorima i aktuatorima iz lokalnog Python koda napisanog na isti način kao što biste pisali na Raspberry Pi-ju koristeći fizički hardver.

## Postavljanje

Za korištenje CounterFit-a, potrebno je instalirati besplatan softver na svoje računalo.

### Zadatak

Instalirajte potreban softver.

1. Instalirajte Python. Pogledajte [stranicu za preuzimanje Pythona](https://www.python.org/downloads/) za upute o instalaciji najnovije verzije Pythona.

1. Instalirajte Visual Studio Code (VS Code). Ovo je uređivač koji ćete koristiti za pisanje koda za vaš virtualni uređaj u Pythonu. Pogledajte [dokumentaciju za VS Code](https://code.visualstudio.com?WT.mc_id=academic-17441-jabenn) za upute o instalaciji VS Code-a.

    > 💁 Slobodno koristite bilo koji Python IDE ili uređivač za ove lekcije ako imate omiljeni alat, ali upute u lekcijama će se temeljiti na korištenju VS Code-a.

1. Instalirajte Pylance ekstenziju za VS Code. Ovo je ekstenzija za VS Code koja pruža podršku za Python jezik. Pogledajte [dokumentaciju za Pylance ekstenziju](https://marketplace.visualstudio.com/items?WT.mc_id=academic-17441-jabenn&itemName=ms-python.vscode-pylance) za upute o instalaciji ove ekstenzije u VS Code-u.

Upute za instalaciju i konfiguraciju CounterFit aplikacije bit će dane u odgovarajućem trenutku u uputama za zadatak jer se instalira za svaki projekt zasebno.

## Hello world

Tradicionalno je, kada započinjete s novim programskim jezikom ili tehnologijom, stvoriti aplikaciju 'Hello World' - malu aplikaciju koja ispisuje tekst poput `"Hello World"` kako bi pokazala da su svi alati ispravno konfigurirani.

Hello World aplikacija za virtualni IoT hardver osigurat će da su Python i Visual Studio Code ispravno instalirani. Također će se povezati s CounterFit-om za virtualne IoT senzore i aktuatore. Neće koristiti nikakav hardver, samo će se povezati kako bi dokazala da sve radi.

Ova aplikacija bit će u mapi pod nazivom `nightlight`, a ponovno će se koristiti s različitim kodom u kasnijim dijelovima ovog zadatka za izradu aplikacije za noćno svjetlo.

### Konfiguriranje Python virtualnog okruženja

Jedna od snažnih značajki Pythona je mogućnost instalacije [Pip paketa](https://pypi.org) - to su paketi koda koje su napisali drugi ljudi i objavili na internetu. Možete instalirati Pip paket na svoje računalo jednim naredbom, a zatim koristiti taj paket u svom kodu. Koristit ćete Pip za instalaciju paketa za komunikaciju s CounterFit-om.

Po zadanim postavkama, kada instalirate paket, on je dostupan svugdje na vašem računalu, što može dovesti do problema s verzijama paketa - na primjer, jedna aplikacija ovisi o jednoj verziji paketa koja prestaje raditi kada instalirate novu verziju za drugu aplikaciju. Kako biste zaobišli ovaj problem, možete koristiti [Python virtualno okruženje](https://docs.python.org/3/library/venv.html), što je u osnovi kopija Pythona u namjenskoj mapi, a kada instalirate Pip pakete, oni se instaliraju samo u tu mapu.

> 💁 Ako koristite Raspberry Pi, tada niste postavili virtualno okruženje na tom uređaju za upravljanje Pip paketima, već koristite globalne pakete jer su Grove paketi globalno instalirani pomoću instalacijskog skripta.

#### Zadatak - konfiguriranje Python virtualnog okruženja

Konfigurirajte Python virtualno okruženje i instalirajte Pip pakete za CounterFit.

1. Iz svog terminala ili naredbenog retka pokrenite sljedeće na lokaciji po vašem izboru kako biste stvorili i prešli u novi direktorij:

    ```sh
    mkdir nightlight
    cd nightlight
    ```

1. Sada pokrenite sljedeće kako biste stvorili virtualno okruženje u mapi `.venv`:

    ```sh
    python3 -m venv .venv
    ```

    > 💁 Morate eksplicitno pozvati `python3` kako biste stvorili virtualno okruženje za slučaj da imate instaliran Python 2 uz Python 3 (najnoviju verziju). Ako imate instaliran Python 2, pozivanje `python` koristit će Python 2 umjesto Pythona 3.

1. Aktivirajte virtualno okruženje:

    * Na Windowsu:
        * Ako koristite Command Prompt ili Command Prompt kroz Windows Terminal, pokrenite:

            ```cmd
            .venv\Scripts\activate.bat
            ```

        * Ako koristite PowerShell, pokrenite:

            ```powershell
            .\.venv\Scripts\Activate.ps1
            ```

            > Ako dobijete grešku o tome da je pokretanje skripti onemogućeno na ovom sustavu, morat ćete omogućiti pokretanje skripti postavljanjem odgovarajuće politike izvršavanja. To možete učiniti pokretanjem PowerShell-a kao administrator, a zatim pokretanjem sljedeće naredbe:

            ```powershell
            Set-ExecutionPolicy -ExecutionPolicy Unrestricted
            ```

            Unesite `Y` kada se zatraži potvrda. Zatim ponovno pokrenite PowerShell i pokušajte ponovno.

            Možete resetirati ovu politiku izvršavanja kasnije ako je potrebno. Više o tome možete pročitati na [stranici o politikama izvršavanja na Microsoft Docs](https://docs.microsoft.com/powershell/module/microsoft.powershell.core/about/about_execution_policies?WT.mc_id=academic-17441-jabenn).

    * Na macOS-u ili Linuxu, pokrenite:

        ```cmd
        source ./.venv/bin/activate
        ```

    > 💁 Ove naredbe trebaju se pokrenuti s iste lokacije na kojoj ste pokrenuli naredbu za stvaranje virtualnog okruženja. Nikada nećete trebati navigirati u mapu `.venv`, uvijek biste trebali pokrenuti naredbu za aktivaciju i bilo koje naredbe za instalaciju paketa ili pokretanje koda iz mape u kojoj ste bili kada ste stvorili virtualno okruženje.

1. Kada je virtualno okruženje aktivirano, zadana naredba `python` pokrenut će verziju Pythona koja je korištena za stvaranje virtualnog okruženja. Pokrenite sljedeće kako biste dobili verziju:

    ```sh
    python --version
    ```

    Izlaz bi trebao sadržavati sljedeće:

    ```output
    (.venv) ➜  nightlight python --version
    Python 3.9.1
    ```

    > 💁 Vaša verzija Pythona može biti drugačija - sve dok je verzija 3.6 ili novija, sve je u redu. Ako nije, izbrišite ovu mapu, instalirajte noviju verziju Pythona i pokušajte ponovno.

1. Pokrenite sljedeće naredbe za instalaciju Pip paketa za CounterFit. Ovi paketi uključuju glavnu CounterFit aplikaciju kao i shims za Grove hardver. Ovi shims omogućuju vam pisanje koda kao da programirate koristeći fizičke senzore i aktuatore iz Grove ekosustava, ali povezane s virtualnim IoT uređajima.

    ```sh
    pip install CounterFit
    pip install counterfit-connection
    pip install counterfit-shims-grove
    ```

    Ovi Pip paketi bit će instalirani samo u virtualnom okruženju i neće biti dostupni izvan njega.

### Pisanje koda

Kada je Python virtualno okruženje spremno, možete napisati kod za aplikaciju 'Hello World'.

#### Zadatak - pisanje koda

Stvorite Python aplikaciju koja ispisuje `"Hello World"` na konzolu.

1. Iz svog terminala ili naredbenog retka pokrenite sljedeće unutar virtualnog okruženja kako biste stvorili Python datoteku pod nazivom `app.py`:

    * Na Windowsu pokrenite:

        ```cmd
        type nul > app.py
        ```

    * Na macOS-u ili Linuxu pokrenite:

        ```cmd
        touch app.py
        ```

1. Otvorite trenutnu mapu u VS Code-u:

    ```sh
    code .
    ```

    > 💁 Ako vaš terminal vrati `command not found` na macOS-u, to znači da VS Code nije dodan u vaš PATH. Možete dodati VS Code u svoj PATH slijedeći upute u [odjeljku Pokretanje iz naredbenog retka u dokumentaciji za VS Code](https://code.visualstudio.com/docs/setup/mac?WT.mc_id=academic-17441-jabenn#_launching-from-the-command-line) i zatim pokrenuti naredbu. VS Code je prema zadanim postavkama dodan u PATH na Windowsu i Linuxu.

1. Kada se VS Code pokrene, aktivirat će Python virtualno okruženje. Odabrano virtualno okruženje pojavit će se u donjoj statusnoj traci:

    ![VS Code prikazuje odabrano virtualno okruženje](../../../../../translated_images/hr/vscode-virtual-env.8ba42e04c3d533cf.webp)

1. Ako je VS Code Terminal već pokrenut kada se VS Code pokrene, neće imati aktivirano virtualno okruženje u njemu. Najlakše je zatvoriti terminal pomoću gumba **Kill the active terminal instance**:

    ![VS Code gumb za zatvaranje aktivnog terminala](../../../../../translated_images/hr/vscode-kill-terminal.1cc4de7c6f25ee08.webp)

    Možete prepoznati je li terminal aktivirao virtualno okruženje jer će ime virtualnog okruženja biti prefiks na terminalskom promptu. Na primjer, moglo bi biti:

    ```sh
    (.venv) ➜  nightlight
    ```

    Ako nemate `.venv` kao prefiks na promptu, virtualno okruženje nije aktivno u terminalu.

1. Pokrenite novi VS Code Terminal odabirom *Terminal -> New Terminal* ili pritiskom na `` CTRL+` ``. Novi terminal učitat će virtualno okruženje, a poziv za aktivaciju pojavit će se u terminalu. Prompt će također imati ime virtualnog okruženja (`.venv`):

    ```output
    ➜  nightlight source .venv/bin/activate
    (.venv) ➜  nightlight 
    ```

1. Otvorite datoteku `app.py` iz VS Code explorera i dodajte sljedeći kod:

    ```python
    print('Hello World!')
    ```

    Funkcija `print` ispisuje sve što joj se proslijedi na konzolu.

1. Iz VS Code terminala pokrenite sljedeće kako biste pokrenuli svoju Python aplikaciju:

    ```sh
    python app.py
    ```

    Sljedeće će biti u izlazu:

    ```output
    (.venv) ➜  nightlight python app.py 
    Hello World!
    ```

😀 Vaš 'Hello World' program je uspješno pokrenut!

### Povezivanje 'hardvera'

Kao drugi korak 'Hello World', pokrenut ćete CounterFit aplikaciju i povezati svoj kod s njom. Ovo je virtualni ekvivalent priključivanja IoT hardvera na razvojni komplet.

#### Zadatak - povezivanje 'hardvera'

1. Iz VS Code terminala pokrenite CounterFit aplikaciju sljedećom naredbom:

    ```sh
    counterfit
    ```

    Aplikacija će se pokrenuti i otvoriti u vašem web pregledniku:

    ![Counter Fit aplikacija pokrenuta u pregledniku](../../../../../translated_images/hr/counterfit-first-run.433326358b669b31.webp)

    Bit će označena kao *Disconnected*, s LED-icom u gornjem desnom kutu isključenom.

1. Dodajte sljedeći kod na vrh `app.py`:

    ```python
    from counterfit_connection import CounterFitConnection
    CounterFitConnection.init('127.0.0.1', 5000)
    ```

    Ovaj kod uvozi klasu `CounterFitConnection` iz modula `counterfit_connection`, koji dolazi iz `counterfit-connection` pip paketa koji ste ranije instalirali. Zatim inicijalizira vezu s CounterFit aplikacijom koja radi na `127.0.0.1`, što je IP adresa koju uvijek možete koristiti za pristup svom lokalnom računalu (često se naziva *localhost*), na portu 5000.

    > 💁 Ako imate druge aplikacije koje rade na portu 5000, možete to promijeniti ažuriranjem porta u kodu i pokretanjem CounterFit-a pomoću `CounterFit --port <port_number>`, zamjenjujući `<port_number>` s portom koji želite koristiti.

1. Morat ćete pokrenuti novi VS Code terminal odabirom gumba **Create a new integrated terminal**. To je zato što CounterFit aplikacija radi u trenutnom terminalu.

    ![VS Code gumb za stvaranje novog integriranog terminala](../../../../../translated_images/hr/vscode-new-terminal.77db8fc0f9cd3182.webp)

1. U ovom novom terminalu pokrenite datoteku `app.py` kao i prije. Status CounterFit-a promijenit će se u **Connected** i LED-ica će se upaliti.

    ![Counter Fit prikazuje status povezan](../../../../../translated_images/hr/counterfit-connected.ed30b46d8f79b092.webp)

> 💁 Ovaj kod možete pronaći u mapi [code/virtual-device](../../../../../1-getting-started/lessons/1-introduction-to-iot/code/virtual-device).

😀 Vaša veza s hardverom je uspješno uspostavljena!

---

**Odricanje od odgovornosti**:  
Ovaj dokument je preveden pomoću AI usluge za prevođenje [Co-op Translator](https://github.com/Azure/co-op-translator). Iako nastojimo osigurati točnost, imajte na umu da automatski prijevodi mogu sadržavati pogreške ili netočnosti. Izvorni dokument na izvornom jeziku treba smatrati autoritativnim izvorom. Za ključne informacije preporučuje se profesionalni prijevod od strane čovjeka. Ne preuzimamo odgovornost za nesporazume ili pogrešna tumačenja koja mogu proizaći iz korištenja ovog prijevoda.