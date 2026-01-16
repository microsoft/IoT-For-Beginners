<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "8ff0d0a1d29832bb896b9c103b69a452",
  "translation_date": "2025-08-28T14:03:48+00:00",
  "source_file": "1-getting-started/lessons/1-introduction-to-iot/pi.md",
  "language_code": "hr"
}
-->
# Raspberry Pi

[Raspberry Pi](https://raspberrypi.org) je računalo na jednoj ploči. Možete dodati senzore i aktuatore koristeći širok raspon uređaja i ekosustava, a za ove lekcije koristit ćemo hardverski ekosustav nazvan [Grove](https://www.seeedstudio.com/category/Grove-c-1003.html). Kodirat ćete svoj Pi i pristupati Grove senzorima koristeći Python.

![Raspberry Pi 4](../../../../../translated_images/hr/raspberry-pi-4.fd4590d308c3d456.jpg)

## Postavljanje

Ako koristite Raspberry Pi kao svoj IoT hardver, imate dvije opcije - možete proći kroz sve ove lekcije i kodirati direktno na Pi-u, ili se možete povezati na 'headless' Pi i kodirati s vašeg računala.

Prije nego što počnete, također trebate spojiti Grove Base Hat na svoj Pi.

### Zadatak - postavljanje

Instalirajte Grove Base Hat na svoj Pi i konfigurirajte Pi.

1. Spojite Grove Base Hat na svoj Pi. Utor na hatu odgovara svim GPIO pinovima na Pi-u, klizi niz pinove dok čvrsto ne sjedne na bazu. Hat prekriva Pi.

    ![Postavljanje Grove Hata](../../../../../images/pi-grove-hat-fitting.gif)

1. Odlučite kako želite programirati svoj Pi i idite na odgovarajući odjeljak u nastavku:

    * [Rad direktno na Pi-u](../../../../../1-getting-started/lessons/1-introduction-to-iot)
    * [Daljinski pristup za kodiranje Pi-a](../../../../../1-getting-started/lessons/1-introduction-to-iot)

### Rad direktno na Pi-u

Ako želite raditi direktno na Pi-u, možete koristiti desktop verziju Raspberry Pi OS-a i instalirati sve potrebne alate.

#### Zadatak - rad direktno na Pi-u

Postavite svoj Pi za razvoj.

1. Slijedite upute u [vodiču za postavljanje Raspberry Pi-a](https://projects.raspberrypi.org/en/projects/raspberry-pi-setting-up) kako biste postavili svoj Pi, spojili ga na tipkovnicu/miš/monitor, povezali ga na WiFi ili ethernet mrežu i ažurirali softver.

Za programiranje Pi-a koristeći Grove senzore i aktuatore, trebat ćete instalirati editor za pisanje koda za uređaje, kao i razne biblioteke i alate koji komuniciraju s Grove hardverom.

1. Nakon što se Pi ponovno pokrene, pokrenite Terminal klikom na ikonu **Terminal** na gornjoj traci izbornika ili odaberite *Menu -> Accessories -> Terminal*.

1. Pokrenite sljedeću naredbu kako biste osigurali da su OS i instalirani softver ažurirani:

    ```sh
    sudo apt update && sudo apt full-upgrade --yes
    ```

1. Pokrenite sljedeće naredbe za instalaciju svih potrebnih biblioteka za Grove hardver:

    ```sh
    sudo apt install git python3-dev python3-pip --yes

    git clone https://github.com/Seeed-Studio/grove.py
    cd grove.py
    sudo pip3 install .

    sudo raspi-config nonint do_i2c 0
    ```

    Ovo započinje instalacijom Git-a, zajedno s Pip-om za instalaciju Python paketa.

    Jedna od moćnih značajki Pythona je mogućnost instalacije [Pip paketa](https://pypi.org) - to su paketi koda koje su napisali drugi ljudi i objavili na internetu. Možete instalirati Pip paket na svoje računalo jednom naredbom, a zatim koristiti taj paket u svom kodu.

    Seeed Grove Python paketi trebaju biti instalirani iz izvornog koda. Ove naredbe klonirat će repozitorij koji sadrži izvorni kod za ovaj paket, a zatim ga instalirati lokalno.

    > 💁 Po defaultu, kada instalirate paket, on je dostupan svugdje na vašem računalu, što može dovesti do problema s verzijama paketa - na primjer, jedna aplikacija ovisi o jednoj verziji paketa koja se može pokvariti kada instalirate novu verziju za drugu aplikaciju. Kako biste zaobišli ovaj problem, možete koristiti [Python virtualno okruženje](https://docs.python.org/3/library/venv.html), što je zapravo kopija Pythona u posvećenom folderu, a kada instalirate Pip pakete, oni se instaliraju samo u taj folder. Nećete koristiti virtualna okruženja kada koristite svoj Pi. Grove instalacijski skript instalira Grove Python pakete globalno, tako da biste za korištenje virtualnog okruženja trebali postaviti virtualno okruženje, a zatim ručno ponovno instalirati Grove pakete unutar tog okruženja. Lakše je jednostavno koristiti globalne pakete, pogotovo jer mnogi Pi developeri ponovno flashaju čistu SD karticu za svaki projekt.

    Na kraju, ovo omogućuje I<sup>2</sup>C sučelje.

1. Ponovno pokrenite Pi koristeći izbornik ili pokretanjem sljedeće naredbe u Terminalu:

    ```sh
    sudo reboot
    ```

1. Nakon što se Pi ponovno pokrene, ponovno pokrenite Terminal i pokrenite sljedeću naredbu za instalaciju [Visual Studio Code (VS Code)](https://code.visualstudio.com?WT.mc_id=academic-17441-jabenn) - ovo je editor koji ćete koristiti za pisanje koda za uređaje u Pythonu.

    ```sh
    sudo apt install code
    ```

    Nakon što je instaliran, VS Code će biti dostupan s gornjeg izbornika.

    > 💁 Slobodni ste koristiti bilo koji Python IDE ili editor za ove lekcije ako imate preferirani alat, ali lekcije će davati upute na temelju korištenja VS Code-a.

1. Instalirajte Pylance. Ovo je ekstenzija za VS Code koja pruža podršku za Python jezik. Pogledajte [dokumentaciju za Pylance ekstenziju](https://marketplace.visualstudio.com/items?WT.mc_id=academic-17441-jabenn&itemName=ms-python.vscode-pylance) za upute o instalaciji ove ekstenzije u VS Code-u.

### Daljinski pristup za kodiranje Pi-a

Umjesto kodiranja direktno na Pi-u, on može raditi 'headless', tj. bez povezivanja na tipkovnicu/miš/monitor, a vi ga možete konfigurirati i kodirati s vašeg računala koristeći Visual Studio Code.

#### Postavljanje Pi OS-a

Za daljinsko kodiranje, Pi OS treba biti instaliran na SD kartici.

##### Zadatak - postavljanje Pi OS-a

Postavite headless Pi OS.

1. Preuzmite **Raspberry Pi Imager** sa [stranice za Raspberry Pi OS softver](https://www.raspberrypi.org/software/) i instalirajte ga.

1. Umetnite SD karticu u svoje računalo, koristeći adapter ako je potrebno.

1. Pokrenite Raspberry Pi Imager.

1. U Raspberry Pi Imageru odaberite gumb **CHOOSE OS**, zatim odaberite *Raspberry Pi OS (Other)*, a potom *Raspberry Pi OS Lite (32-bit)*.

    ![Raspberry Pi Imager s odabranim Raspberry Pi OS Lite](../../../../../translated_images/hr/raspberry-pi-imager.24aedeab9e233d84.png)

    > 💁 Raspberry Pi OS Lite je verzija Raspberry Pi OS-a koja nema desktop UI ili alate bazirane na UI-u. Ovi nisu potrebni za headless Pi i čine instalaciju manjom i vrijeme pokretanja bržim.

1. Odaberite gumb **CHOOSE STORAGE**, zatim odaberite svoju SD karticu.

1. Pokrenite **Advanced Options** pritiskom na `Ctrl+Shift+X`. Ove opcije omogućuju neku predkonfiguraciju Raspberry Pi OS-a prije nego što se snimi na SD karticu.

    1. Označite kućicu **Enable SSH** i postavite lozinku za korisnika `pi`. Ovo je lozinka koju ćete koristiti za prijavu na Pi kasnije.

    1. Ako planirate povezivanje na Pi putem WiFi-a, označite kućicu **Configure WiFi** i unesite svoj WiFi SSID i lozinku, kao i odaberite svoju WiFi zemlju. Ovo nije potrebno ako ćete koristiti ethernet kabel. Pobrinite se da je mreža na koju se povezujete ista ona na kojoj je vaše računalo.

    1. Označite kućicu **Set locale settings** i postavite svoju zemlju i vremensku zonu.

    1. Odaberite gumb **SAVE**.

1. Odaberite gumb **WRITE** za snimanje OS-a na SD karticu. Ako koristite macOS, bit ćete zamoljeni da unesete svoju lozinku jer alat koji snima slike diska zahtijeva privilegirani pristup.

OS će biti snimljen na SD karticu, a nakon završetka kartica će biti izbačena od strane OS-a, te ćete biti obaviješteni. Izvadite SD karticu iz svog računala, umetnite je u Pi, uključite Pi i pričekajte oko 2 minute da se pravilno pokrene.

#### Povezivanje na Pi

Sljedeći korak je daljinski pristup Pi-u. To možete učiniti koristeći `ssh`, koji je dostupan na macOS-u, Linuxu i novijim verzijama Windowsa.

##### Zadatak - povezivanje na Pi

Daljinski pristupite Pi-u.

1. Pokrenite Terminal ili Command Prompt i unesite sljedeću naredbu za povezivanje na Pi:

    ```sh
    ssh pi@raspberrypi.local
    ```

    Ako koristite Windows starije verzije koje nemaju instaliran `ssh`, možete koristiti OpenSSH. Upute za instalaciju možete pronaći u [dokumentaciji za instalaciju OpenSSH-a](https://docs.microsoft.com//windows-server/administration/openssh/openssh_install_firstuse?WT.mc_id=academic-17441-jabenn).

1. Ovo bi vas trebalo povezati na vaš Pi i zatražiti lozinku.

    Mogućnost pronalaženja računala na vašoj mreži koristeći `<hostname>.local` je prilično nedavna dodatna značajka za Linux i Windows. Ako koristite Linux ili Windows i dobijete bilo kakve greške o tome da Hostname nije pronađen, trebat ćete instalirati dodatni softver za omogućavanje ZeroConf mrežnog povezivanja (također poznatog od strane Apple-a kao Bonjour):

    1. Ako koristite Linux, instalirajte Avahi koristeći sljedeću naredbu:

        ```sh
        sudo apt-get install avahi-daemon
        ```

    1. Ako koristite Windows, najlakši način za omogućavanje ZeroConf-a je instalacija [Bonjour Print Services za Windows](http://support.apple.com/kb/DL999). Također možete instalirati [iTunes za Windows](https://www.apple.com/itunes/download/) kako biste dobili noviju verziju alata (koja nije dostupna samostalno).

    > 💁 Ako se ne možete povezati koristeći `raspberrypi.local`, možete koristiti IP adresu vašeg Pi-a. Pogledajte [dokumentaciju za IP adresu Raspberry Pi-a](https://www.raspberrypi.org/documentation/remote-access/ip-address.md) za upute o nekoliko načina kako dobiti IP adresu.

1. Unesite lozinku koju ste postavili u Advanced Options Raspberry Pi Imager-a.

#### Konfiguracija softvera na Pi-u

Nakon što ste povezani na Pi, trebate osigurati da je OS ažuriran i instalirati razne biblioteke i alate koji komuniciraju s Grove hardverom.

##### Zadatak - konfiguracija softvera na Pi-u

Konfigurirajte instalirani softver na Pi-u i instalirajte Grove biblioteke.

1. Iz vaše `ssh` sesije, pokrenite sljedeću naredbu za ažuriranje, a zatim ponovno pokrenite Pi:

    ```sh
    sudo apt update && sudo apt full-upgrade --yes && sudo reboot
    ```

    Pi će biti ažuriran i ponovno pokrenut. `ssh` sesija će završiti kada se Pi ponovno pokrene, pa pričekajte oko 30 sekundi, a zatim se ponovno povežite.

1. Iz ponovno povezane `ssh` sesije, pokrenite sljedeće naredbe za instalaciju svih potrebnih biblioteka za Grove hardver:

    ```sh
    sudo apt install git python3-dev python3-pip --yes

    git clone https://github.com/Seeed-Studio/grove.py
    cd grove.py
    sudo pip3 install .

    sudo raspi-config nonint do_i2c 0
    ```

    Ovo započinje instalacijom Git-a, zajedno s Pip-om za instalaciju Python paketa.

    Jedna od moćnih značajki Pythona je mogućnost instalacije [Pip paketa](https://pypi.org) - to su paketi koda koje su napisali drugi ljudi i objavili na internetu. Možete instalirati Pip paket na svoje računalo jednom naredbom, a zatim koristiti taj paket u svom kodu.

    Seeed Grove Python paketi trebaju biti instalirani iz izvornog koda. Ove naredbe klonirat će repozitorij koji sadrži izvorni kod za ovaj paket, a zatim ga instalirati lokalno.

    > 💁 Po defaultu, kada instalirate paket, on je dostupan svugdje na vašem računalu, što može dovesti do problema s verzijama paketa - na primjer, jedna aplikacija ovisi o jednoj verziji paketa koja se može pokvariti kada instalirate novu verziju za drugu aplikaciju. Kako biste zaobišli ovaj problem, možete koristiti [Python virtualno okruženje](https://docs.python.org/3/library/venv.html), što je zapravo kopija Pythona u posvećenom folderu, a kada instalirate Pip pakete, oni se instaliraju samo u taj folder. Nećete koristiti virtualna okruženja kada koristite svoj Pi. Grove instalacijski skript instalira Grove Python pakete globalno, tako da biste za korištenje virtualnog okruženja trebali postaviti virtualno okruženje, a zatim ručno ponovno instalirati Grove pakete unutar tog okruženja. Lakše je jednostavno koristiti globalne pakete, pogotovo jer mnogi Pi developeri ponovno flashaju čistu SD karticu za svaki projekt.

    Na kraju, ovo omogućuje I<sup>2</sup>C sučelje.

1. Ponovno pokrenite Pi pokretanjem sljedeće naredbe:

    ```sh
    sudo reboot
    ```

    `ssh` sesija će završiti kada se Pi ponovno pokrene. Nema potrebe za ponovnim povezivanjem.

#### Konfiguracija VS Code-a za daljinski pristup

Nakon što je Pi konfiguriran, možete se povezati na njega koristeći Visual Studio Code (VS Code) sa svog računala - ovo je besplatni tekstualni editor za razvoj koji ćete koristiti za pisanje koda za uređaje u Pythonu.

##### Zadatak - konfiguracija VS Code-a za daljinski pristup

Instalirajte potrebni softver i povežite se daljinski na svoj Pi.

1. Instalirajte VS Code na svoje računalo slijedeći [dokumentaciju za VS Code](https://code.visualstudio.com?WT.mc_id=academic-17441-jabenn).

1. Slijedite upute u [dokumentaciji za daljinski razvoj VS Code-a koristeći SSH](https://code.visualstudio.com/docs/remote/ssh?WT.mc_id=academic-17441-jabenn) za instalaciju potrebnih komponenti.

1. Slijedeći iste upute, povežite VS Code na Pi.

1. Nakon povezivanja, slijedite upute za [upravljanje ekstenzijama](https://code.visualstudio.com/docs/remote/ssh#_managing-extensions?WT.mc_id=academic-17441-jabenn) kako biste instalirali [Pylance ekstenziju](https://marketplace.visualstudio.com/items?WT.mc_id=academic-17441-jabenn&itemName=ms-python.vscode-pylance) daljinski na Pi.

## Hello world
Tradicionalno je, kada započinjete s novim programskim jezikom ili tehnologijom, kreirati aplikaciju 'Hello World' - malu aplikaciju koja ispisuje tekst poput `"Hello World"` kako bi se pokazalo da su svi alati ispravno konfigurirani.

Hello World aplikacija za Pi osigurat će da imate ispravno instalirane Python i Visual Studio Code.

Ova aplikacija bit će smještena u mapu pod nazivom `nightlight`, a kasnije će se ponovno koristiti s različitim kodom u drugim dijelovima ovog zadatka za izradu aplikacije noćnog svjetla.

### Zadatak - hello world

Kreirajte Hello World aplikaciju.

1. Pokrenite VS Code, bilo direktno na Pi-ju, ili na vašem računalu povezanom s Pi-jem koristeći Remote SSH ekstenziju.

1. Pokrenite VS Code Terminal odabirom *Terminal -> New Terminal*, ili pritiskom na `` CTRL+` ``. Otvorit će se u početnom direktoriju korisnika `pi`.

1. Pokrenite sljedeće naredbe kako biste kreirali direktorij za vaš kod i kreirali Python datoteku pod nazivom `app.py` unutar tog direktorija:

    ```sh
    mkdir nightlight
    cd nightlight
    touch app.py
    ```

1. Otvorite ovu mapu u VS Code odabirom *File -> Open...* i odabirom mape *nightlight*, zatim odaberite **OK**.

    ![Dijalog za otvaranje u VS Code prikazuje mapu nightlight](../../../../../translated_images/hr/vscode-open-nightlight-remote.d3d2a4011e30d535.png)

1. Otvorite datoteku `app.py` iz VS Code explorer-a i dodajte sljedeći kod:

    ```python
    print('Hello World!')
    ```

    Funkcija `print` ispisuje na konzolu sve što joj se proslijedi.

1. Iz VS Code Terminala pokrenite sljedeće kako biste pokrenuli vašu Python aplikaciju:

    ```sh
    python app.py
    ```

    > 💁 Možda ćete morati eksplicitno pozvati `python3` kako biste pokrenuli ovaj kod ako imate instaliran Python 2 uz Python 3 (najnoviju verziju). Ako imate instaliran Python 2, poziv `python` koristit će Python 2 umjesto Python 3. Prema zadanim postavkama, najnovije verzije Raspberry Pi OS-a imaju instaliran samo Python 3.

    Sljedeći izlaz pojavit će se u terminalu:

    ```output
    pi@raspberrypi:~/nightlight $ python3 app.py
    Hello World!
    ```

> 💁 Ovaj kod možete pronaći u mapi [code/pi](../../../../../1-getting-started/lessons/1-introduction-to-iot/code/pi).

😀 Vaš 'Hello World' program je uspješno pokrenut!

---

**Odricanje od odgovornosti**:  
Ovaj dokument je preveden pomoću AI usluge za prevođenje [Co-op Translator](https://github.com/Azure/co-op-translator). Iako nastojimo osigurati točnost, imajte na umu da automatski prijevodi mogu sadržavati pogreške ili netočnosti. Izvorni dokument na izvornom jeziku treba smatrati autoritativnim izvorom. Za ključne informacije preporučuje se profesionalni prijevod od strane ljudskog prevoditelja. Ne preuzimamo odgovornost za bilo kakva nesporazuma ili pogrešna tumačenja koja proizlaze iz korištenja ovog prijevoda.