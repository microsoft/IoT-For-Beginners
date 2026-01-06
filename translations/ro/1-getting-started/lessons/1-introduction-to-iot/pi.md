<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "8ff0d0a1d29832bb896b9c103b69a452",
  "translation_date": "2025-08-28T10:24:24+00:00",
  "source_file": "1-getting-started/lessons/1-introduction-to-iot/pi.md",
  "language_code": "ro"
}
-->
# Raspberry Pi

[Raspberry Pi](https://raspberrypi.org) este un computer pe o singură placă. Poți adăuga senzori și actuatori folosind o gamă largă de dispozitive și ecosisteme, iar pentru aceste lecții vei folosi un ecosistem hardware numit [Grove](https://www.seeedstudio.com/category/Grove-c-1003.html). Vei programa Pi-ul și vei accesa senzorii Grove folosind Python.

![Un Raspberry Pi 4](../../../../../translated_images/raspberry-pi-4.fd4590d308c3d456.ro.jpg)

## Configurare

Dacă folosești un Raspberry Pi ca hardware IoT, ai două opțiuni - poți parcurge toate aceste lecții și programa direct pe Pi sau te poți conecta de la distanță la un Pi 'headless' și programa de pe computerul tău.

Înainte de a începe, trebuie să conectezi Grove Base Hat la Pi-ul tău.

### Sarcină - configurare

Instalează Grove Base Hat pe Pi-ul tău și configurează-l.

1. Conectează Grove Base Hat la Pi-ul tău. Soclul de pe hat se potrivește peste toate pinii GPIO de pe Pi, alunecând complet pe pini pentru a se fixa ferm pe bază. Acesta acoperă Pi-ul.

    ![Montarea Grove Hat](../../../../../images/pi-grove-hat-fitting.gif)

1. Decide cum vrei să programezi Pi-ul și mergi la secțiunea relevantă de mai jos:

    * [Lucrează direct pe Pi-ul tău](../../../../../1-getting-started/lessons/1-introduction-to-iot)
    * [Acces de la distanță pentru a programa Pi-ul](../../../../../1-getting-started/lessons/1-introduction-to-iot)

### Lucrează direct pe Pi-ul tău

Dacă vrei să lucrezi direct pe Pi-ul tău, poți folosi versiunea desktop a Raspberry Pi OS și să instalezi toate instrumentele necesare.

#### Sarcină - lucrează direct pe Pi-ul tău

Configurează Pi-ul pentru dezvoltare.

1. Urmează instrucțiunile din [ghidul de configurare Raspberry Pi](https://projects.raspberrypi.org/en/projects/raspberry-pi-setting-up) pentru a configura Pi-ul, a-l conecta la o tastatură/mouse/monitor, a-l conecta la rețeaua WiFi sau ethernet și a actualiza software-ul.

Pentru a programa Pi-ul folosind senzorii și actuatorii Grove, va trebui să instalezi un editor pentru a scrie codul dispozitivului și diverse biblioteci și instrumente care interacționează cu hardware-ul Grove.

1. După ce Pi-ul s-a repornit, lansează Terminalul făcând clic pe pictograma **Terminal** din bara de meniu de sus sau alege *Menu -> Accessories -> Terminal*

1. Rulează următoarea comandă pentru a te asigura că sistemul de operare și software-ul instalat sunt actualizate:

    ```sh
    sudo apt update && sudo apt full-upgrade --yes
    ```

1. Rulează următoarele comenzi pentru a instala toate bibliotecile necesare pentru hardware-ul Grove:

    ```sh
    sudo apt install git python3-dev python3-pip --yes

    git clone https://github.com/Seeed-Studio/grove.py
    cd grove.py
    sudo pip3 install .

    sudo raspi-config nonint do_i2c 0
    ```

    Acest proces începe prin instalarea Git, împreună cu Pip pentru instalarea pachetelor Python.

    Una dintre caracteristicile puternice ale Python este abilitatea de a instala [pachete Pip](https://pypi.org) - acestea sunt pachete de cod scrise de alte persoane și publicate pe Internet. Poți instala un pachet Pip pe computerul tău cu o singură comandă, apoi să folosești acel pachet în codul tău.

    Pachetele Python Grove de la Seeed trebuie instalate din sursă. Aceste comenzi vor clona repo-ul care conține codul sursă pentru acest pachet, apoi îl vor instala local.

    > 💁 În mod implicit, atunci când instalezi un pachet, acesta este disponibil peste tot pe computerul tău, ceea ce poate duce la probleme cu versiunile pachetelor - cum ar fi o aplicație care depinde de o versiune a unui pachet care se strică atunci când instalezi o versiune nouă pentru o altă aplicație. Pentru a evita această problemă, poți folosi un [mediu virtual Python](https://docs.python.org/3/library/venv.html), practic o copie a Python într-un folder dedicat, iar când instalezi pachete Pip, acestea sunt instalate doar în acel folder. Nu vei folosi medii virtuale când folosești Pi-ul tău. Scriptul de instalare Grove instalează pachetele Python Grove global, așa că pentru a folosi un mediu virtual ar trebui să configurezi un mediu virtual și apoi să reinstalezi manual pachetele Grove în acel mediu. Este mai simplu să folosești pachete globale, mai ales că mulți dezvoltatori Pi vor re-flasha un card SD curat pentru fiecare proiect.

    În final, aceasta activează interfața I<sup>2</sup>C.

1. Repornește Pi-ul fie folosind meniul, fie rulând următoarea comandă în Terminal:

    ```sh
    sudo reboot
    ```

1. După ce Pi-ul s-a repornit, relansează Terminalul și rulează următoarea comandă pentru a instala [Visual Studio Code (VS Code)](https://code.visualstudio.com?WT.mc_id=academic-17441-jabenn) - acesta este editorul pe care îl vei folosi pentru a scrie codul dispozitivului în Python.

    ```sh
    sudo apt install code
    ```

    După ce este instalat, VS Code va fi disponibil din bara de meniu de sus.

    > 💁 Ești liber să folosești orice IDE sau editor Python pentru aceste lecții dacă ai un instrument preferat, dar lecțiile vor oferi instrucțiuni bazate pe utilizarea VS Code.

1. Instalează Pylance. Acesta este o extensie pentru VS Code care oferă suport pentru limbajul Python. Consultă [documentația extensiei Pylance](https://marketplace.visualstudio.com/items?WT.mc_id=academic-17441-jabenn&itemName=ms-python.vscode-pylance) pentru instrucțiuni despre instalarea acestei extensii în VS Code.

### Acces de la distanță pentru a programa Pi-ul

În loc să programezi direct pe Pi, acesta poate funcționa 'headless', adică fără a fi conectat la o tastatură/mouse/monitor, și să fie configurat și programat de pe computerul tău, folosind Visual Studio Code.

#### Configurează sistemul de operare Pi

Pentru a programa de la distanță, sistemul de operare Pi trebuie să fie instalat pe un card SD.

##### Sarcină - configurează sistemul de operare Pi

Configurează sistemul de operare Pi 'headless'.

1. Descarcă **Raspberry Pi Imager** de pe [pagina software Raspberry Pi OS](https://www.raspberrypi.org/software/) și instalează-l.

1. Introdu un card SD în computerul tău, folosind un adaptor dacă este necesar.

1. Lansează Raspberry Pi Imager.

1. Din Raspberry Pi Imager, selectează butonul **CHOOSE OS**, apoi selectează *Raspberry Pi OS (Other)*, urmat de *Raspberry Pi OS Lite (32-bit)*.

    ![Raspberry Pi Imager cu Raspberry Pi OS Lite selectat](../../../../../translated_images/raspberry-pi-imager.24aedeab9e233d84.ro.png)

    > 💁 Raspberry Pi OS Lite este o versiune a Raspberry Pi OS care nu are interfața desktop sau instrumentele bazate pe interfață grafică. Acestea nu sunt necesare pentru un Pi 'headless' și fac instalarea mai mică și timpul de pornire mai rapid.

1. Selectează butonul **CHOOSE STORAGE**, apoi selectează cardul SD.

1. Lansează **Advanced Options** apăsând `Ctrl+Shift+X`. Aceste opțiuni permit o pre-configurare a Raspberry Pi OS înainte de a fi scris pe cardul SD.

    1. Bifează caseta **Enable SSH** și setează o parolă pentru utilizatorul `pi`. Aceasta este parola pe care o vei folosi pentru a te conecta la Pi mai târziu.

    1. Dacă intenționezi să te conectezi la Pi prin WiFi, bifează caseta **Configure WiFi** și introdu SSID-ul și parola WiFi, precum și selectează țara WiFi. Nu este necesar să faci acest lucru dacă vei folosi un cablu ethernet. Asigură-te că rețeaua la care te conectezi este aceeași cu cea pe care se află computerul tău.

    1. Bifează caseta **Set locale settings** și setează țara și fusul orar.

    1. Selectează butonul **SAVE**.

1. Selectează butonul **WRITE** pentru a scrie sistemul de operare pe cardul SD. Dacă folosești macOS, ți se va cere să introduci parola, deoarece instrumentul care scrie imaginile de disc necesită acces privilegiat.

Sistemul de operare va fi scris pe cardul SD, iar după finalizare cardul va fi ejectat de sistemul de operare, iar tu vei fi notificat. Scoate cardul SD din computer, introdu-l în Pi, pornește Pi-ul și așteaptă aproximativ 2 minute pentru a se porni complet.

#### Conectează-te la Pi

Următorul pas este să accesezi Pi-ul de la distanță. Poți face acest lucru folosind `ssh`, care este disponibil pe macOS, Linux și versiunile recente de Windows.

##### Sarcină - conectează-te la Pi

Accesează Pi-ul de la distanță.

1. Lansează un Terminal sau Command Prompt și introdu următoarea comandă pentru a te conecta la Pi:

    ```sh
    ssh pi@raspberrypi.local
    ```

    Dacă folosești Windows într-o versiune mai veche care nu are `ssh` instalat, poți folosi OpenSSH. Poți găsi instrucțiunile de instalare în [documentația de instalare OpenSSH](https://docs.microsoft.com//windows-server/administration/openssh/openssh_install_firstuse?WT.mc_id=academic-17441-jabenn).

1. Aceasta ar trebui să te conecteze la Pi și să îți ceară parola.

    Posibilitatea de a găsi computerele din rețeaua ta folosind `<hostname>.local` este o adăugare relativ recentă pentru Linux și Windows. Dacă folosești Linux sau Windows și primești erori legate de faptul că Hostname-ul nu a fost găsit, va trebui să instalezi software suplimentar pentru a activa rețelele ZeroConf (denumite de Apple Bonjour):

    1. Dacă folosești Linux, instalează Avahi folosind următoarea comandă:

        ```sh
        sudo apt-get install avahi-daemon
        ```

    1. Dacă folosești Windows, cea mai simplă metodă de a activa ZeroConf este să instalezi [Bonjour Print Services for Windows](http://support.apple.com/kb/DL999). De asemenea, poți instala [iTunes pentru Windows](https://www.apple.com/itunes/download/) pentru a obține o versiune mai nouă a utilitarului (care nu este disponibilă separat).

    > 💁 Dacă nu te poți conecta folosind `raspberrypi.local`, atunci poți folosi adresa IP a Pi-ului. Consultă [documentația despre adresa IP Raspberry Pi](https://www.raspberrypi.org/documentation/remote-access/ip-address.md) pentru instrucțiuni despre mai multe metode de a obține adresa IP.

1. Introdu parola pe care ai setat-o în Advanced Options din Raspberry Pi Imager.

#### Configurează software-ul pe Pi

După ce te-ai conectat la Pi, trebuie să te asiguri că sistemul de operare este actualizat și să instalezi diverse biblioteci și instrumente care interacționează cu hardware-ul Grove.

##### Sarcină - configurează software-ul pe Pi

Configurează software-ul instalat pe Pi și instalează bibliotecile Grove.

1. Din sesiunea `ssh`, rulează următoarea comandă pentru a actualiza și apoi a reporni Pi-ul:

    ```sh
    sudo apt update && sudo apt full-upgrade --yes && sudo reboot
    ```

    Pi-ul va fi actualizat și repornit. Sesiunea `ssh` se va încheia când Pi-ul se repornește, așa că așteaptă aproximativ 30 de secunde și apoi reconectează-te.

1. Din sesiunea `ssh` reconectată, rulează următoarele comenzi pentru a instala toate bibliotecile necesare pentru hardware-ul Grove:

    ```sh
    sudo apt install git python3-dev python3-pip --yes

    git clone https://github.com/Seeed-Studio/grove.py
    cd grove.py
    sudo pip3 install .

    sudo raspi-config nonint do_i2c 0
    ```

    Acest proces începe prin instalarea Git, împreună cu Pip pentru instalarea pachetelor Python.

    Una dintre caracteristicile puternice ale Python este abilitatea de a instala [pachete Pip](https://pypi.org) - acestea sunt pachete de cod scrise de alte persoane și publicate pe Internet. Poți instala un pachet Pip pe computerul tău cu o singură comandă, apoi să folosești acel pachet în codul tău.

    Pachetele Python Grove de la Seeed trebuie instalate din sursă. Aceste comenzi vor clona repo-ul care conține codul sursă pentru acest pachet, apoi îl vor instala local.

    > 💁 În mod implicit, atunci când instalezi un pachet, acesta este disponibil peste tot pe computerul tău, ceea ce poate duce la probleme cu versiunile pachetelor - cum ar fi o aplicație care depinde de o versiune a unui pachet care se strică atunci când instalezi o versiune nouă pentru o altă aplicație. Pentru a evita această problemă, poți folosi un [mediu virtual Python](https://docs.python.org/3/library/venv.html), practic o copie a Python într-un folder dedicat, iar când instalezi pachete Pip, acestea sunt instalate doar în acel folder. Nu vei folosi medii virtuale când folosești Pi-ul tău. Scriptul de instalare Grove instalează pachetele Python Grove global, așa că pentru a folosi un mediu virtual ar trebui să configurezi un mediu virtual și apoi să reinstalezi manual pachetele Grove în acel mediu. Este mai simplu să folosești pachete globale, mai ales că mulți dezvoltatori Pi vor re-flasha un card SD curat pentru fiecare proiect.

    În final, aceasta activează interfața I<sup>2</sup>C.

1. Repornește Pi-ul rulând următoarea comandă:

    ```sh
    sudo reboot
    ```

    Sesiunea `ssh` se va încheia când Pi-ul se repornește. Nu este nevoie să te reconectezi.

#### Configurează VS Code pentru acces de la distanță

După ce Pi-ul este configurat, te poți conecta la el folosind Visual Studio Code (VS Code) de pe computerul tău - acesta este un editor de text gratuit pentru dezvoltatori pe care îl vei folosi pentru a scrie codul dispozitivului în Python.

##### Sarcină - configurează VS Code pentru acces de la distanță

Instalează software-ul necesar și conectează-te de la distanță la Pi-ul tău.

1. Instalează VS Code pe computerul tău urmând [documentația VS Code](https://code.visualstudio.com?WT.mc_id=academic-17441-jabenn).

1. Urmează instrucțiunile din [documentația VS Code Remote Development folosind SSH](https://code.visualstudio.com/docs/remote/ssh?WT.mc_id=academic-17441-jabenn) pentru a instala componentele necesare.

1. Urmând aceleași instrucțiuni, conectează VS Code la Pi.

1. După ce te-ai conectat, urmează instrucțiunile din [gestionarea extensiilor](https://code.visualstudio.com/docs/remote/ssh#_managing-extensions?WT.mc_id=academic-17441-jabenn) pentru a instala extensia [Pylance](https://marketplace.visualstudio.com/items?WT.mc_id=academic-17441-jabenn&itemName=ms-python.vscode-pylance) de la distanță pe Pi.

## Hello world
Este tradițional ca atunci când începi să lucrezi cu un nou limbaj de programare sau o tehnologie să creezi o aplicație 'Hello World' - o aplicație mică care afișează ceva de genul textului `"Hello World"` pentru a demonstra că toate instrumentele sunt configurate corect.

Aplicația Hello World pentru Pi va asigura că ai instalat corect Python și Visual Studio Code.

Această aplicație va fi într-un folder numit `nightlight`, și va fi reutilizată cu cod diferit în părțile ulterioare ale acestui proiect pentru a construi aplicația nightlight.

### Sarcină - hello world

Creează aplicația Hello World.

1. Lansează VS Code, fie direct pe Pi, fie pe computerul tău conectat la Pi folosind extensia Remote SSH.

1. Deschide terminalul VS Code selectând *Terminal -> New Terminal*, sau apăsând `` CTRL+` ``. Acesta se va deschide în directorul de acasă al utilizatorului `pi`.

1. Rulează următoarele comenzi pentru a crea un director pentru codul tău și un fișier Python numit `app.py` în acel director:

    ```sh
    mkdir nightlight
    cd nightlight
    touch app.py
    ```

1. Deschide acest folder în VS Code selectând *File -> Open...* și alegând folderul *nightlight*, apoi selectează **OK**.

    ![Dialogul de deschidere din VS Code care arată folderul nightlight](../../../../../translated_images/vscode-open-nightlight-remote.d3d2a4011e30d535.ro.png)

1. Deschide fișierul `app.py` din explorer-ul VS Code și adaugă următorul cod:

    ```python
    print('Hello World!')
    ```

    Funcția `print` afișează în consolă orice îi este transmis.

1. Din terminalul VS Code, rulează următoarele comenzi pentru a rula aplicația Python:

    ```sh
    python app.py
    ```

    > 💁 Este posibil să fie nevoie să apelezi explicit `python3` pentru a rula acest cod dacă ai instalat Python 2 pe lângă Python 3 (cea mai recentă versiune). Dacă ai instalat Python 2, atunci apelarea `python` va folosi Python 2 în loc de Python 3. În mod implicit, cele mai recente versiuni ale Raspberry Pi OS au instalat doar Python 3.

    Următorul output va apărea în terminal:

    ```output
    pi@raspberrypi:~/nightlight $ python3 app.py
    Hello World!
    ```

> 💁 Poți găsi acest cod în folderul [code/pi](../../../../../1-getting-started/lessons/1-introduction-to-iot/code/pi).

😀 Programul tău 'Hello World' a fost un succes!

---

**Declinare de responsabilitate**:  
Acest document a fost tradus folosind serviciul de traducere AI [Co-op Translator](https://github.com/Azure/co-op-translator). Deși ne străduim să asigurăm acuratețea, vă rugăm să rețineți că traducerile automate pot conține erori sau inexactități. Documentul original în limba sa maternă ar trebui considerat sursa autoritară. Pentru informații critice, se recomandă traducerea profesională realizată de un specialist uman. Nu ne asumăm responsabilitatea pentru eventualele neînțelegeri sau interpretări greșite care pot apărea din utilizarea acestei traduceri.