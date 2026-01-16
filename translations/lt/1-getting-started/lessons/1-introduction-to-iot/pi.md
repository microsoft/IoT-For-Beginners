<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "8ff0d0a1d29832bb896b9c103b69a452",
  "translation_date": "2025-08-28T20:03:01+00:00",
  "source_file": "1-getting-started/lessons/1-introduction-to-iot/pi.md",
  "language_code": "lt"
}
-->
# Raspberry Pi

[Raspberry Pi](https://raspberrypi.org) yra vienos plokštės kompiuteris. Naudodami įvairius įrenginius ir ekosistemas galite pridėti jutiklius ir pavaras, o šiose pamokose naudosime aparatinės įrangos ekosistemą, vadinamą [Grove](https://www.seeedstudio.com/category/Grove-c-1003.html). Jūs programuosite savo Pi ir pasieksite Grove jutiklius naudodami Python.

![Raspberry Pi 4](../../../../../translated_images/lt/raspberry-pi-4.fd4590d308c3d456.jpg)

## Paruošimas

Jei naudojate Raspberry Pi kaip savo IoT aparatinę įrangą, turite dvi galimybes – galite atlikti visas šias pamokas ir programuoti tiesiogiai Pi arba prisijungti nuotoliniu būdu prie „be galvos“ Pi ir programuoti iš savo kompiuterio.

Prieš pradėdami, taip pat turite prijungti Grove bazinę plokštę prie savo Pi.

### Užduotis – paruošimas

Įdiekite Grove bazinę plokštę ant savo Pi ir sukonfigūruokite Pi.

1. Prijunkite Grove bazinę plokštę prie savo Pi. Plokštės lizdas uždengia visas GPIO jungtis ant Pi, slysta žemyn per jungtis ir tvirtai priglunda prie pagrindo. Ji uždengia Pi, visiškai jį apgaubdama.

    ![Grove plokštės montavimas](../../../../../images/pi-grove-hat-fitting.gif)

1. Nuspręskite, kaip norite programuoti savo Pi, ir pereikite prie atitinkamo skyriaus žemiau:

    * [Dirbti tiesiogiai su savo Pi](../../../../../1-getting-started/lessons/1-introduction-to-iot)
    * [Nuotolinis prisijungimas prie Pi programavimo](../../../../../1-getting-started/lessons/1-introduction-to-iot)

### Dirbti tiesiogiai su savo Pi

Jei norite dirbti tiesiogiai su savo Pi, galite naudoti Raspberry Pi OS darbalaukio versiją ir įdiegti visas reikalingas priemones.

#### Užduotis – dirbti tiesiogiai su savo Pi

Paruoškite savo Pi programavimui.

1. Vadovaukitės instrukcijomis [Raspberry Pi paruošimo vadove](https://projects.raspberrypi.org/en/projects/raspberry-pi-setting-up), kad nustatytumėte savo Pi, prijungtumėte jį prie klaviatūros/pelės/monitoriaus, prijungtumėte prie WiFi arba Ethernet tinklo ir atnaujintumėte programinę įrangą.

Norėdami programuoti Pi naudodami Grove jutiklius ir pavaras, turėsite įdiegti redaktorių, kuris leis rašyti įrenginio kodą, ir įvairias bibliotekas bei įrankius, kurie sąveikauja su Grove aparatine įranga.

1. Kai jūsų Pi bus paleistas iš naujo, paleiskite Terminalą spustelėdami **Terminal** piktogramą viršutiniame meniu juostoje arba pasirinkite *Menu -> Accessories -> Terminal*.

1. Paleiskite šią komandą, kad užtikrintumėte, jog OS ir įdiegta programinė įranga yra atnaujinta:

    ```sh
    sudo apt update && sudo apt full-upgrade --yes
    ```

1. Paleiskite šias komandas, kad įdiegtumėte visas reikalingas bibliotekas Grove aparatinės įrangos naudojimui:

    ```sh
    sudo apt install git python3-dev python3-pip --yes

    git clone https://github.com/Seeed-Studio/grove.py
    cd grove.py
    sudo pip3 install .

    sudo raspi-config nonint do_i2c 0
    ```

    Tai prasideda Git ir Pip diegimu Python paketams įdiegti.

    Viena iš galingų Python savybių yra galimybė įdiegti [Pip paketus](https://pypi.org) – tai kitų žmonių parašyti ir internete paskelbti kodų paketai. Galite įdiegti Pip paketą į savo kompiuterį viena komanda ir naudoti tą paketą savo kode.

    Seeed Grove Python paketai turi būti įdiegti iš šaltinio. Šios komandos klonuoja saugyklą, kurioje yra šio paketo šaltinio kodas, ir tada įdiegia jį lokaliai.

    > 💁 Pagal numatymą, kai įdiegiate paketą, jis tampa prieinamas visame jūsų kompiuteryje, o tai gali sukelti problemų su paketų versijomis – pavyzdžiui, viena programa priklauso nuo vienos paketo versijos, kuri sugenda, kai įdiegiate naują versiją kitai programai. Norėdami išspręsti šią problemą, galite naudoti [Python virtualią aplinką](https://docs.python.org/3/library/venv.html), kuri iš esmės yra Python kopija specialiame aplanke, ir kai įdiegiate Pip paketus, jie įdiegiami tik tame aplanke. Naudodami Pi nenaudosite virtualių aplinkų. Grove diegimo scenarijus įdiegia Grove Python paketus globaliai, todėl norėdami naudoti virtualią aplinką turėtumėte ją nustatyti ir tada rankiniu būdu iš naujo įdiegti Grove paketus toje aplinkoje. Paprasčiau naudoti globalius paketus, ypač todėl, kad daugelis Pi kūrėjų kiekvienam projektui iš naujo įrašo švarų SD kortelės vaizdą.

    Galiausiai, tai įgalina I<sup>2</sup>C sąsają.

1. Paleiskite Pi iš naujo naudodami meniu arba paleisdami šią komandą Terminale:

    ```sh
    sudo reboot
    ```

1. Kai Pi bus paleistas iš naujo, vėl paleiskite Terminalą ir paleiskite šią komandą, kad įdiegtumėte [Visual Studio Code (VS Code)](https://code.visualstudio.com?WT.mc_id=academic-17441-jabenn) – tai redaktorius, kurį naudosite rašydami savo įrenginio kodą Python kalba.

    ```sh
    sudo apt install code
    ```

    Kai tai bus įdiegta, VS Code bus pasiekiamas iš viršutinio meniu.

    > 💁 Galite naudoti bet kurį Python IDE ar redaktorių šioms pamokoms, jei turite mėgstamą įrankį, tačiau pamokose bus pateiktos instrukcijos, pagrįstos VS Code naudojimu.

1. Įdiekite Pylance. Tai yra VS Code plėtinys, kuris suteikia Python kalbos palaikymą. Peržiūrėkite [Pylance plėtinio dokumentaciją](https://marketplace.visualstudio.com/items?WT.mc_id=academic-17441-jabenn&itemName=ms-python.vscode-pylance), kad sužinotumėte, kaip įdiegti šį plėtinį VS Code.

### Nuotolinis prisijungimas prie Pi programavimo

Vietoj programavimo tiesiogiai Pi, jis gali veikti „be galvos“, tai yra, neprijungtas prie klaviatūros/pelės/monitoriaus, ir jį galima konfigūruoti bei programuoti iš jūsų kompiuterio, naudojant Visual Studio Code.

#### Nustatyti Pi OS

Norint programuoti nuotoliniu būdu, Pi OS turi būti įdiegta į SD kortelę.

##### Užduotis – nustatyti Pi OS

Nustatykite „be galvos“ Pi OS.

1. Atsisiųskite **Raspberry Pi Imager** iš [Raspberry Pi OS programinės įrangos puslapio](https://www.raspberrypi.org/software/) ir įdiekite jį.

1. Įdėkite SD kortelę į savo kompiuterį, jei reikia, naudodami adapterį.

1. Paleiskite Raspberry Pi Imager.

1. Raspberry Pi Imager pasirinkite mygtuką **CHOOSE OS**, tada pasirinkite *Raspberry Pi OS (Other)*, po to *Raspberry Pi OS Lite (32-bit)*.

    ![Raspberry Pi Imager su pasirinktu Raspberry Pi OS Lite](../../../../../translated_images/lt/raspberry-pi-imager.24aedeab9e233d84.png)

    > 💁 Raspberry Pi OS Lite yra Raspberry Pi OS versija, kuri neturi darbalaukio vartotojo sąsajos ar vartotojo sąsajos pagrįstų įrankių. Jie nėra reikalingi „be galvos“ Pi ir sumažina diegimo dydį bei pagreitina paleidimo laiką.

1. Pasirinkite mygtuką **CHOOSE STORAGE**, tada pasirinkite savo SD kortelę.

1. Paleiskite **Advanced Options** paspausdami `Ctrl+Shift+X`. Šios parinktys leidžia iš anksto sukonfigūruoti Raspberry Pi OS prieš ją įrašant į SD kortelę.

    1. Pažymėkite **Enable SSH** žymės langelį ir nustatykite slaptažodį `pi` naudotojui. Tai bus slaptažodis, kurį naudosite prisijungdami prie Pi vėliau.

    1. Jei planuojate prisijungti prie Pi per WiFi, pažymėkite **Configure WiFi** žymės langelį ir įveskite savo WiFi SSID ir slaptažodį, taip pat pasirinkite savo WiFi šalį. Jei naudosite Ethernet kabelį, to daryti nereikia. Įsitikinkite, kad tinklas, prie kurio jungiatės, yra tas pats, kuriame yra jūsų kompiuteris.

    1. Pažymėkite **Set locale settings** žymės langelį ir nustatykite savo šalį bei laiko juostą.

    1. Pasirinkite mygtuką **SAVE**.

1. Pasirinkite mygtuką **WRITE**, kad įrašytumėte OS į SD kortelę. Jei naudojate macOS, būsite paprašyti įvesti savo slaptažodį, nes pagrindinis įrankis, kuris rašo disko vaizdus, reikalauja privilegijuotos prieigos.

OS bus įrašyta į SD kortelę, o kai procesas bus baigtas, kortelė bus išimta iš OS, ir jūs būsite informuoti. Išimkite SD kortelę iš savo kompiuterio, įdėkite ją į Pi, įjunkite Pi ir palaukite apie 2 minutes, kol jis tinkamai paleis.

#### Prisijungimas prie Pi

Kitas žingsnis yra nuotolinis prisijungimas prie Pi. Tai galite padaryti naudodami `ssh`, kuris yra prieinamas macOS, Linux ir naujesnėse Windows versijose.

##### Užduotis – prisijungti prie Pi

Nuotoliniu būdu prisijunkite prie Pi.

1. Paleiskite Terminalą arba Komandinę eilutę ir įveskite šią komandą, kad prisijungtumėte prie Pi:

    ```sh
    ssh pi@raspberrypi.local
    ```

    Jei naudojate senesnę Windows versiją, kurioje nėra įdiegto `ssh`, galite naudoti OpenSSH. Diegimo instrukcijas rasite [OpenSSH diegimo dokumentacijoje](https://docs.microsoft.com//windows-server/administration/openssh/openssh_install_firstuse?WT.mc_id=academic-17441-jabenn).

1. Tai turėtų prisijungti prie jūsų Pi ir paprašyti slaptažodžio.

    Galimybė rasti kompiuterius jūsų tinkle naudojant `<hostname>.local` yra gana nauja funkcija Linux ir Windows. Jei naudojate Linux arba Windows ir gaunate klaidų apie nerastą pagrindinį kompiuterį, turėsite įdiegti papildomą programinę įrangą, kad įgalintumėte ZeroConf tinklą (taip pat vadinamą Apple Bonjour):

    1. Jei naudojate Linux, įdiekite Avahi naudodami šią komandą:

        ```sh
        sudo apt-get install avahi-daemon
        ```

    1. Jei naudojate Windows, paprasčiausias būdas įgalinti ZeroConf yra įdiegti [Bonjour Print Services for Windows](http://support.apple.com/kb/DL999). Taip pat galite įdiegti [iTunes for Windows](https://www.apple.com/itunes/download/), kad gautumėte naujesnę šio įrankio versiją (kuri nėra prieinama atskirai).

    > 💁 Jei negalite prisijungti naudodami `raspberrypi.local`, galite naudoti savo Pi IP adresą. Peržiūrėkite [Raspberry Pi IP adreso dokumentaciją](https://www.raspberrypi.org/documentation/remote-access/ip-address.md), kur rasite instrukcijas apie įvairius būdus, kaip gauti IP adresą.

1. Įveskite slaptažodį, kurį nustatėte Raspberry Pi Imager Advanced Options.

#### Programinės įrangos konfigūravimas Pi

Kai prisijungsite prie Pi, turite užtikrinti, kad OS būtų atnaujinta, ir įdiegti įvairias bibliotekas bei įrankius, kurie sąveikauja su Grove aparatine įranga.

##### Užduotis – konfigūruoti programinę įrangą Pi

Konfigūruokite įdiegtą Pi programinę įrangą ir įdiekite Grove bibliotekas.

1. Iš savo `ssh` sesijos paleiskite šią komandą, kad atnaujintumėte ir paleistumėte Pi iš naujo:

    ```sh
    sudo apt update && sudo apt full-upgrade --yes && sudo reboot
    ```

    Pi bus atnaujintas ir paleistas iš naujo. `ssh` sesija baigsis, kai Pi bus paleistas iš naujo, todėl palaukite apie 30 sekundžių ir vėl prisijunkite.

1. Iš naujai prisijungtos `ssh` sesijos paleiskite šias komandas, kad įdiegtumėte visas reikalingas bibliotekas Grove aparatinės įrangos naudojimui:

    ```sh
    sudo apt install git python3-dev python3-pip --yes

    git clone https://github.com/Seeed-Studio/grove.py
    cd grove.py
    sudo pip3 install .

    sudo raspi-config nonint do_i2c 0
    ```

    Tai prasideda Git ir Pip diegimu Python paketams įdiegti.

    Viena iš galingų Python savybių yra galimybė įdiegti [Pip paketus](https://pypi.org) – tai kitų žmonių parašyti ir internete paskelbti kodų paketai. Galite įdiegti Pip paketą į savo kompiuterį viena komanda ir naudoti tą paketą savo kode.

    Seeed Grove Python paketai turi būti įdiegti iš šaltinio. Šios komandos klonuoja saugyklą, kurioje yra šio paketo šaltinio kodas, ir tada įdiegia jį lokaliai.

    > 💁 Pagal numatymą, kai įdiegiate paketą, jis tampa prieinamas visame jūsų kompiuteryje, o tai gali sukelti problemų su paketų versijomis – pavyzdžiui, viena programa priklauso nuo vienos paketo versijos, kuri sugenda, kai įdiegiate naują versiją kitai programai. Norėdami išspręsti šią problemą, galite naudoti [Python virtualią aplinką](https://docs.python.org/3/library/venv.html), kuri iš esmės yra Python kopija specialiame aplanke, ir kai įdiegiate Pip paketus, jie įdiegiami tik tame aplanke. Naudodami Pi nenaudosite virtualių aplinkų. Grove diegimo scenarijus įdiegia Grove Python paketus globaliai, todėl norėdami naudoti virtualią aplinką turėtumėte ją nustatyti ir tada rankiniu būdu iš naujo įdiegti Grove paketus toje aplinkoje. Paprasčiau naudoti globalius paketus, ypač todėl, kad daugelis Pi kūrėjų kiekvienam projektui iš naujo įrašo švarų SD kortelės vaizdą.

    Galiausiai, tai įgalina I<sup>2</sup>C sąsają.

1. Paleiskite Pi iš naujo paleisdami šią komandą:

    ```sh
    sudo reboot
    ```

    `ssh` sesija baigsis, kai Pi bus paleistas iš naujo. Nereikia vėl prisijungti.

#### VS Code konfigūravimas nuotoliniam prisijungimui

Kai Pi bus sukonfigūruotas, galėsite prisijungti prie jo naudodami Visual Studio Code (VS Code) iš savo kompiuterio – tai nemokamas kūrėjų teksto redaktorius, kurį naudosite rašydami savo įrenginio kodą Python kalba.

##### Užduotis – konfigūruoti VS Code nuotoliniam prisijungimui

Įdiekite reikiamą programinę įrangą ir prisijunkite nuotoliniu būdu prie savo Pi.

1. Įdiekite VS Code savo kompiuteryje, vadovaudamiesi [VS Code dokumentacija](https://code.visualstudio.com?WT.mc_id=academic-17441-jabenn).

1. Vadovaukitės instrukcijomis [VS Code nuotolinio programavimo naudojant SSH dokumentacijoje](https://code.visualstudio.com/docs/remote/ssh?WT.mc_id=academic-17441-jabenn), kad įdiegtumėte reikalingus komponentus.

1. Vadovaujantis tomis pačiomis instrukcijomis, prisijunkite prie Pi naudodami VS Code.

1. Kai prisijungsite, vadovaukitės [plėtinių valdymo instrukcijomis](https://code.visualstudio.com/docs/remote/ssh#_managing-extensions?WT.mc_id=academic-17441-jabenn), kad nuotoliniu būdu įdiegtumėte [Pylance plėtinį](https://marketplace.visualstudio.com/items?WT.mc_id=academic-17441-jabenn&itemName=
Pradėjus mokytis naujos programavimo kalbos ar technologijos, įprasta sukurti „Hello World“ programėlę – mažą programą, kuri išveda tekstą, pvz., `"Hello World"`, kad įsitikintumėte, jog visi įrankiai yra tinkamai sukonfigūruoti.

„Hello World“ programėlė, skirta Pi, užtikrins, kad Python ir Visual Studio Code būtų tinkamai įdiegti.

Ši programėlė bus aplanke, pavadintame `nightlight`, ir vėlesnėse šios užduoties dalyse ji bus naudojama su skirtingu kodu kuriant naktinę lemputę.

### Užduotis – hello world

Sukurkite „Hello World“ programėlę.

1. Paleiskite VS Code tiesiogiai Pi įrenginyje arba savo kompiuteryje, prisijungę prie Pi naudodami Remote SSH plėtinį.

1. Atidarykite VS Code terminalą pasirinkdami *Terminal -> New Terminal* arba paspausdami `` CTRL+` ``. Terminalas atsidarys `pi` naudotojo pagrindiniame kataloge.

1. Paleiskite šias komandas, kad sukurtumėte katalogą savo kodui ir sukurtumėte Python failą, pavadintą `app.py`, tame kataloge:

    ```sh
    mkdir nightlight
    cd nightlight
    touch app.py
    ```

1. Atidarykite šį aplanką VS Code programoje pasirinkdami *File -> Open...* ir pasirinkdami *nightlight* aplanką, tada spustelėkite **OK**.

    ![VS Code atidarymo dialogas, rodantis nightlight aplanką](../../../../../translated_images/lt/vscode-open-nightlight-remote.d3d2a4011e30d535.png)

1. Atidarykite `app.py` failą iš VS Code naršyklės ir pridėkite šį kodą:

    ```python
    print('Hello World!')
    ```

    Funkcija `print` išveda į konsolę viską, kas jai perduodama.

1. Iš VS Code terminalo paleiskite šią komandą, kad paleistumėte savo Python programą:

    ```sh
    python app.py
    ```

    > 💁 Jei turite įdiegtą Python 2 kartu su Python 3 (naujausia versija), gali reikėti aiškiai nurodyti `python3`, kad paleistumėte šį kodą. Jei turite Python 2, komanda `python` naudos Python 2 vietoj Python 3. Pagal numatytuosius nustatymus naujausios Raspberry Pi OS versijos turi tik Python 3.

    Terminale pasirodys toks išvesties tekstas:

    ```output
    pi@raspberrypi:~/nightlight $ python3 app.py
    Hello World!
    ```

> 💁 Šį kodą galite rasti [code/pi](../../../../../1-getting-started/lessons/1-introduction-to-iot/code/pi) aplanke.

😀 Jūsų „Hello World“ programa pavyko!

---

**Atsakomybės apribojimas**:  
Šis dokumentas buvo išverstas naudojant AI vertimo paslaugą [Co-op Translator](https://github.com/Azure/co-op-translator). Nors siekiame tikslumo, prašome atkreipti dėmesį, kad automatiniai vertimai gali turėti klaidų ar netikslumų. Originalus dokumentas jo gimtąja kalba turėtų būti laikomas autoritetingu šaltiniu. Kritinei informacijai rekomenduojama naudoti profesionalų žmogaus vertimą. Mes neprisiimame atsakomybės už nesusipratimus ar klaidingus interpretavimus, atsiradusius dėl šio vertimo naudojimo.