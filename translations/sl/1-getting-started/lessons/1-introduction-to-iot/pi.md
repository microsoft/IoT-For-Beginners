<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "8ff0d0a1d29832bb896b9c103b69a452",
  "translation_date": "2025-08-28T14:04:40+00:00",
  "source_file": "1-getting-started/lessons/1-introduction-to-iot/pi.md",
  "language_code": "sl"
}
-->
# Raspberry Pi

[Raspberry Pi](https://raspberrypi.org) je enokartični računalnik. Senzorje in aktuatorje lahko dodate z uporabo širokega nabora naprav in ekosistemov, za te lekcije pa bomo uporabili strojni ekosistem, imenovan [Grove](https://www.seeedstudio.com/category/Grove-c-1003.html). Raspberry Pi boste programirali in dostopali do Grove senzorjev z uporabo Pythona.

![Raspberry Pi 4](../../../../../translated_images/sl/raspberry-pi-4.fd4590d308c3d456.jpg)

## Nastavitev

Če uporabljate Raspberry Pi kot svojo IoT strojno opremo, imate dve možnosti - lahko opravite vse te lekcije in programirate neposredno na Pi-ju ali pa se povežete na "brezglavi" Pi in programirate iz svojega računalnika.

Preden začnete, morate na svoj Pi priključiti Grove Base Hat.

### Naloga - nastavitev

Namestite Grove Base Hat na svoj Pi in konfigurirajte Pi.

1. Povežite Grove Base Hat z vašim Pi-jem. Priključek na hatu se prilega vsem GPIO pinom na Pi-ju, tako da zdrsne čez pine in se trdno usede na osnovo. Hat pokrije Pi.

    ![Namestitev Grove Hata](../../../../../images/pi-grove-hat-fitting.gif)

1. Odločite se, kako želite programirati svoj Pi, in pojdite na ustrezen razdelek spodaj:

    * [Delo neposredno na vašem Pi-ju](../../../../../1-getting-started/lessons/1-introduction-to-iot)
    * [Oddaljen dostop za programiranje Pi-ja](../../../../../1-getting-started/lessons/1-introduction-to-iot)

### Delo neposredno na vašem Pi-ju

Če želite delati neposredno na svojem Pi-ju, lahko uporabite namizno različico Raspberry Pi OS in namestite vsa potrebna orodja.

#### Naloga - delo neposredno na vašem Pi-ju

Pripravite svoj Pi za razvoj.

1. Sledite navodilom v [vodniku za nastavitev Raspberry Pi](https://projects.raspberrypi.org/en/projects/raspberry-pi-setting-up), da nastavite svoj Pi, ga povežete s tipkovnico/miško/monitorjem, povežete na WiFi ali ethernet omrežje in posodobite programsko opremo.

Za programiranje Pi-ja z uporabo Grove senzorjev in aktuatorjev boste morali namestiti urejevalnik za pisanje kode za naprave ter različne knjižnice in orodja za interakcijo z Grove strojno opremo.

1. Ko se vaš Pi ponovno zažene, zaženite Terminal s klikom na ikono **Terminal** v zgornji menijski vrstici ali izberite *Menu -> Accessories -> Terminal*.

1. Zaženite naslednji ukaz, da zagotovite, da sta OS in nameščena programska oprema posodobljena:

    ```sh
    sudo apt update && sudo apt full-upgrade --yes
    ```

1. Zaženite naslednje ukaze za namestitev vseh potrebnih knjižnic za Grove strojno opremo:

    ```sh
    sudo apt install git python3-dev python3-pip --yes

    git clone https://github.com/Seeed-Studio/grove.py
    cd grove.py
    sudo pip3 install .

    sudo raspi-config nonint do_i2c 0
    ```

    To se začne z namestitvijo Git-a in Pipa za namestitev Python paketov.

    Ena od močnih lastnosti Pythona je možnost namestitve [Pip paketov](https://pypi.org) - to so paketi kode, ki so jih napisali drugi in objavili na internetu. Pip paket lahko namestite na svoj računalnik z enim ukazom in nato uporabite ta paket v svoji kodi.

    Seeed Grove Python pakete je treba namestiti iz izvorne kode. Ti ukazi bodo klonirali repozitorij, ki vsebuje izvorno kodo za ta paket, nato pa ga lokalno namestili.

    > 💁 Privzeto, ko namestite paket, je ta na voljo povsod na vašem računalniku, kar lahko povzroči težave z različicami paketov - na primer ena aplikacija je odvisna od ene različice paketa, ki se zlomi, ko namestite novo različico za drugo aplikacijo. Da bi se izognili tej težavi, lahko uporabite [Python virtualno okolje](https://docs.python.org/3/library/venv.html), kar je v bistvu kopija Pythona v namenski mapi, in ko namestite Pip pakete, se ti namestijo samo v to mapo. Na svojem Pi-ju ne boste uporabljali virtualnih okolij. Namestitveni skript za Grove knjižnice jih namesti globalno, zato bi morali za uporabo virtualnega okolja nastaviti virtualno okolje in nato ročno ponovno namestiti Grove knjižnice znotraj tega okolja. Lažje je preprosto uporabljati globalne pakete, še posebej, ker veliko razvijalcev za vsak projekt ponovno naloži čisto SD kartico.

    Na koncu to omogoči I<sup>2</sup>C vmesnik.

1. Ponovno zaženite Pi bodisi z uporabo menija bodisi z zagonom naslednjega ukaza v Terminalu:

    ```sh
    sudo reboot
    ```

1. Ko se Pi ponovno zažene, ponovno zaženite Terminal in zaženite naslednji ukaz za namestitev [Visual Studio Code (VS Code)](https://code.visualstudio.com?WT.mc_id=academic-17441-jabenn) - to je urejevalnik, ki ga boste uporabljali za pisanje kode za naprave v Pythonu.

    ```sh
    sudo apt install code
    ```

    Ko je to nameščeno, bo VS Code na voljo v zgornjem meniju.

    > 💁 Lahko uporabite katerikoli Python IDE ali urejevalnik za te lekcije, če imate raje drugo orodje, vendar bodo navodila v lekcijah temeljila na uporabi VS Code.

1. Namestite Pylance. To je razširitev za VS Code, ki zagotavlja podporo za Python jezik. Oglejte si [dokumentacijo za razširitev Pylance](https://marketplace.visualstudio.com/items?WT.mc_id=academic-17441-jabenn&itemName=ms-python.vscode-pylance) za navodila o namestitvi te razširitve v VS Code.

### Oddaljen dostop za programiranje Pi-ja

Namesto da programirate neposredno na Pi-ju, lahko ta deluje "brezglavo", torej brez povezave s tipkovnico/miško/monitorjem, in ga konfigurirate ter programirate iz svojega računalnika z uporabo Visual Studio Code.

#### Nastavitev Pi OS

Za oddaljeno programiranje mora biti Pi OS nameščen na SD kartici.

##### Naloga - nastavitev Pi OS

Nastavite brezglavi Pi OS.

1. Prenesite **Raspberry Pi Imager** s [strani z Raspberry Pi OS programsko opremo](https://www.raspberrypi.org/software/) in ga namestite.

1. Vstavite SD kartico v računalnik, po potrebi uporabite adapter.

1. Zaženite Raspberry Pi Imager.

1. V Raspberry Pi Imagerju izberite gumb **CHOOSE OS**, nato izberite *Raspberry Pi OS (Other)*, sledi *Raspberry Pi OS Lite (32-bit)*.

    ![Raspberry Pi Imager z izbranim Raspberry Pi OS Lite](../../../../../translated_images/sl/raspberry-pi-imager.24aedeab9e233d84.png)

    > 💁 Raspberry Pi OS Lite je različica Raspberry Pi OS brez namiznega uporabniškega vmesnika ali orodij na osnovi uporabniškega vmesnika. Ta niso potrebna za brezglavi Pi, kar naredi namestitev manjšo in hitrejši zagon.

1. Izberite gumb **CHOOSE STORAGE**, nato izberite svojo SD kartico.

1. Zaženite **Napredne možnosti** s pritiskom na `Ctrl+Shift+X`. Te možnosti omogočajo nekaj predkonfiguracije Raspberry Pi OS, preden je zapisana na SD kartico.

    1. Označite potrditveno polje **Enable SSH** in nastavite geslo za uporabnika `pi`. To je geslo, ki ga boste uporabili za prijavo na Pi kasneje.

    1. Če načrtujete povezavo s Pi-jem prek WiFi, označite potrditveno polje **Configure WiFi** in vnesite svoj WiFi SSID in geslo ter izberite svojo WiFi državo. Tega vam ni treba storiti, če boste uporabljali ethernet kabel. Prepričajte se, da je omrežje, na katerega se povežete, isto kot omrežje vašega računalnika.

    1. Označite potrditveno polje **Set locale settings** in nastavite svojo državo in časovni pas.

    1. Izberite gumb **SAVE**.

1. Izberite gumb **WRITE**, da zapišete OS na SD kartico. Če uporabljate macOS, boste morali vnesti svoje geslo, saj orodje za zapisovanje diskovnih slik potrebuje privilegiran dostop.

OS bo zapisan na SD kartico, in ko bo končano, bo kartica izločena iz sistema, vi pa boste obveščeni. Odstranite SD kartico iz računalnika, jo vstavite v Pi, vklopite Pi in počakajte približno 2 minuti, da se pravilno zažene.

#### Povezava s Pi-jem

Naslednji korak je oddaljen dostop do Pi-ja. To lahko storite z uporabo `ssh`, ki je na voljo na macOS, Linux in novejših različicah Windows.

##### Naloga - povezava s Pi-jem

Oddaljeno dostopajte do Pi-ja.

1. Zaženite Terminal ali Command Prompt in vnesite naslednji ukaz za povezavo s Pi-jem:

    ```sh
    ssh pi@raspberrypi.local
    ```

    Če uporabljate Windows v starejši različici, ki nima nameščenega `ssh`, lahko uporabite OpenSSH. Navodila za namestitev najdete v [dokumentaciji za namestitev OpenSSH](https://docs.microsoft.com//windows-server/administration/openssh/openssh_install_firstuse?WT.mc_id=academic-17441-jabenn).

1. To bi vas moralo povezati s Pi-jem in vas vprašati za geslo.

    Možnost iskanja računalnikov v vašem omrežju z uporabo `<hostname>.local` je dokaj nova funkcija v Linuxu in Windows. Če uporabljate Linux ali Windows in dobite napake o tem, da gostitelja ni mogoče najti, boste morali namestiti dodatno programsko opremo za omogočanje ZeroConf omrežja (ki ga Apple imenuje Bonjour):

    1. Če uporabljate Linux, namestite Avahi z naslednjim ukazom:

        ```sh
        sudo apt-get install avahi-daemon
        ```

    1. Če uporabljate Windows, je najlažji način za omogočanje ZeroConf namestitev [Bonjour Print Services za Windows](http://support.apple.com/kb/DL999). Lahko pa namestite tudi [iTunes za Windows](https://www.apple.com/itunes/download/), da dobite novejšo različico pripomočka (ki ni na voljo samostojno).

    > 💁 Če se ne morete povezati z uporabo `raspberrypi.local`, lahko uporabite IP naslov vašega Pi-ja. Oglejte si [dokumentacijo o IP naslovu Raspberry Pi](https://www.raspberrypi.org/documentation/remote-access/ip-address.md) za navodila o številnih načinih pridobivanja IP naslova.

1. Vnesite geslo, ki ste ga nastavili v Naprednih možnostih Raspberry Pi Imagerja.

#### Konfiguracija programske opreme na Pi-ju

Ko ste povezani s Pi-jem, morate zagotoviti, da je OS posodobljen, in namestiti različne knjižnice ter orodja za interakcijo z Grove strojno opremo.

##### Naloga - konfiguracija programske opreme na Pi-ju

Konfigurirajte nameščeno programsko opremo na Pi-ju in namestite Grove knjižnice.

1. Iz vaše `ssh` seje zaženite naslednji ukaz za posodobitev in nato ponovno zaženite Pi:

    ```sh
    sudo apt update && sudo apt full-upgrade --yes && sudo reboot
    ```

    Pi bo posodobljen in ponovno zagnan. `ssh` seja se bo končala, ko se Pi ponovno zažene, zato počakajte približno 30 sekund in se nato ponovno povežite.

1. Iz ponovno povezane `ssh` seje zaženite naslednje ukaze za namestitev vseh potrebnih knjižnic za Grove strojno opremo:

    ```sh
    sudo apt install git python3-dev python3-pip --yes

    git clone https://github.com/Seeed-Studio/grove.py
    cd grove.py
    sudo pip3 install .

    sudo raspi-config nonint do_i2c 0
    ```

    To se začne z namestitvijo Git-a in Pipa za namestitev Python paketov.

    Ena od močnih lastnosti Pythona je možnost namestitve [Pip paketov](https://pypi.org) - to so paketi kode, ki so jih napisali drugi in objavili na internetu. Pip paket lahko namestite na svoj računalnik z enim ukazom in nato uporabite ta paket v svoji kodi.

    Seeed Grove Python pakete je treba namestiti iz izvorne kode. Ti ukazi bodo klonirali repozitorij, ki vsebuje izvorno kodo za ta paket, nato pa ga lokalno namestili.

    > 💁 Privzeto, ko namestite paket, je ta na voljo povsod na vašem računalniku, kar lahko povzroči težave z različicami paketov - na primer ena aplikacija je odvisna od ene različice paketa, ki se zlomi, ko namestite novo različico za drugo aplikacijo. Da bi se izognili tej težavi, lahko uporabite [Python virtualno okolje](https://docs.python.org/3/library/venv.html), kar je v bistvu kopija Pythona v namenski mapi, in ko namestite Pip pakete, se ti namestijo samo v to mapo. Na svojem Pi-ju ne boste uporabljali virtualnih okolij. Namestitveni skript za Grove knjižnice jih namesti globalno, zato bi morali za uporabo virtualnega okolja nastaviti virtualno okolje in nato ročno ponovno namestiti Grove knjižnice znotraj tega okolja. Lažje je preprosto uporabljati globalne pakete, še posebej, ker veliko razvijalcev za vsak projekt ponovno naloži čisto SD kartico.

    Na koncu to omogoči I<sup>2</sup>C vmesnik.

1. Ponovno zaženite Pi z zagonom naslednjega ukaza:

    ```sh
    sudo reboot
    ```

    `ssh` seja se bo končala, ko se Pi ponovno zažene. Ponovna povezava ni potrebna.

#### Konfiguracija VS Code za oddaljen dostop

Ko je Pi konfiguriran, se lahko povežete z njim z uporabo Visual Studio Code (VS Code) iz vašega računalnika - to je brezplačen urejevalnik besedila za razvijalce, ki ga boste uporabljali za pisanje kode za naprave v Pythonu.

##### Naloga - konfiguracija VS Code za oddaljen dostop

Namestite potrebno programsko opremo in se oddaljeno povežite s svojim Pi-jem.

1. Namestite VS Code na svoj računalnik, tako da sledite [dokumentaciji za VS Code](https://code.visualstudio.com?WT.mc_id=academic-17441-jabenn).

1. Sledite navodilom v [dokumentaciji za oddaljeni razvoj z uporabo SSH v VS Code](https://code.visualstudio.com/docs/remote/ssh?WT.mc_id=academic-17441-jabenn), da namestite potrebne komponente.

1. Po istih navodilih povežite VS Code s Pi-jem.

1. Ko ste povezani, sledite [navodilom za upravljanje razširitev](https://code.visualstudio.com/docs/remote/ssh#_managing-extensions?WT.mc_id=academic-17441-jabenn), da oddaljeno namestite razširitev [Pylance](https://marketplace.visualstudio.com/items?WT.mc_id=academic-17441-jabenn&itemName=ms-python.vscode-pylance) na Pi.

## Hello world
Običajno je, da ob začetku učenja novega programskega jezika ali tehnologije ustvarite aplikacijo 'Hello World' – majhno aplikacijo, ki izpiše nekaj podobnega kot besedilo `"Hello World"`, da preverite, ali so vsa orodja pravilno nastavljena.

Aplikacija Hello World za Pi bo zagotovila, da imate pravilno nameščena Python in Visual Studio Code.

Ta aplikacija bo v mapi z imenom `nightlight`, ki jo boste kasneje v tej nalogi ponovno uporabili z drugačno kodo za izdelavo aplikacije nočne lučke.

### Naloga - hello world

Ustvarite aplikacijo Hello World.

1. Zaženite VS Code, bodisi neposredno na Pi-ju ali na svojem računalniku, povezanem s Pi-jem prek razširitve Remote SSH.

1. Odprite terminal v VS Code tako, da izberete *Terminal -> New Terminal* ali pritisnete `` CTRL+` ``. Terminal se bo odprl v domačem imeniku uporabnika `pi`.

1. Zaženite naslednje ukaze, da ustvarite mapo za svojo kodo in v tej mapi ustvarite Python datoteko z imenom `app.py`:

    ```sh
    mkdir nightlight
    cd nightlight
    touch app.py
    ```

1. Odprite to mapo v VS Code tako, da izberete *File -> Open...* in izberete mapo *nightlight*, nato kliknite **OK**.

    ![Pogovorno okno za odpiranje v VS Code, ki prikazuje mapo nightlight](../../../../../translated_images/sl/vscode-open-nightlight-remote.d3d2a4011e30d535.png)

1. Odprite datoteko `app.py` iz raziskovalca v VS Code in dodajte naslednjo kodo:

    ```python
    print('Hello World!')
    ```

    Funkcija `print` izpiše vse, kar ji posredujete, v konzolo.

1. V terminalu VS Code zaženite naslednji ukaz, da zaženete svojo Python aplikacijo:

    ```sh
    python app.py
    ```

    > 💁 Morda boste morali izrecno poklicati `python3`, da zaženete to kodo, če imate nameščen Python 2 poleg Pythona 3 (zadnje različice). Če imate nameščen Python 2, bo ukaz `python` uporabil Python 2 namesto Pythona 3. Privzeto imajo najnovejše različice Raspberry Pi OS nameščen samo Python 3.

    V terminalu se bo prikazal naslednji izpis:

    ```output
    pi@raspberrypi:~/nightlight $ python3 app.py
    Hello World!
    ```

> 💁 To kodo lahko najdete v mapi [code/pi](../../../../../1-getting-started/lessons/1-introduction-to-iot/code/pi).

😀 Vaš program 'Hello World' je bil uspešen!

---

**Omejitev odgovornosti**:  
Ta dokument je bil preveden z uporabo storitve za prevajanje z umetno inteligenco [Co-op Translator](https://github.com/Azure/co-op-translator). Čeprav si prizadevamo za natančnost, vas prosimo, da upoštevate, da lahko avtomatizirani prevodi vsebujejo napake ali netočnosti. Izvirni dokument v njegovem izvirnem jeziku je treba obravnavati kot avtoritativni vir. Za ključne informacije priporočamo profesionalni človeški prevod. Ne prevzemamo odgovornosti za morebitna nesporazumevanja ali napačne razlage, ki bi nastale zaradi uporabe tega prevoda.