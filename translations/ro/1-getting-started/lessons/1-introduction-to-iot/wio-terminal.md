<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "a4f0c166010e31fd7b6ca20bc88dec6d",
  "translation_date": "2025-08-28T10:27:29+00:00",
  "source_file": "1-getting-started/lessons/1-introduction-to-iot/wio-terminal.md",
  "language_code": "ro"
}
-->
# Wio Terminal

[Wio Terminal de la Seeed Studios](https://www.seeedstudio.com/Wio-Terminal-p-4509.html) este un microcontroller compatibil cu Arduino, care include WiFi, câțiva senzori și actuatori, precum și porturi pentru a adăuga mai mulți senzori și actuatori, utilizând un ecosistem hardware numit [Grove](https://www.seeedstudio.com/category/Grove-c-1003.html).

![Un Wio Terminal de la Seeed Studios](../../../../../translated_images/ro/wio-terminal.b8299ee16587db9a.png)

## Configurare

Pentru a utiliza Wio Terminal, va trebui să instalați câteva programe gratuite pe computerul dvs. De asemenea, va trebui să actualizați firmware-ul Wio Terminal înainte de a-l conecta la WiFi.

### Sarcină - configurare

Instalați software-ul necesar și actualizați firmware-ul.

1. Instalați Visual Studio Code (VS Code). Acesta este editorul pe care îl veți folosi pentru a scrie codul dispozitivului în C/C++. Consultați [documentația VS Code](https://code.visualstudio.com?WT.mc_id=academic-17441-jabenn) pentru instrucțiuni despre instalarea VS Code.

    > 💁 Un alt IDE popular pentru dezvoltarea Arduino este [Arduino IDE](https://www.arduino.cc/en/software). Dacă sunteți deja familiarizat cu acest instrument, îl puteți folosi în loc de VS Code și PlatformIO, dar lecțiile vor oferi instrucțiuni bazate pe utilizarea VS Code.

1. Instalați extensia PlatformIO pentru VS Code. Aceasta este o extensie pentru VS Code care permite programarea microcontrollerelor în C/C++. Consultați [documentația extensiei PlatformIO](https://marketplace.visualstudio.com/items?WT.mc_id=academic-17441-jabenn&itemName=platformio.platformio-ide) pentru instrucțiuni despre instalarea acestei extensii în VS Code. Această extensie depinde de extensia Microsoft C/C++ pentru a lucra cu codul C și C++, iar extensia C/C++ este instalată automat odată cu PlatformIO.

1. Conectați Wio Terminal la computerul dvs. Wio Terminal are un port USB-C în partea de jos, care trebuie conectat la un port USB de pe computerul dvs. Wio Terminal vine cu un cablu USB-C la USB-A, dar dacă computerul dvs. are doar porturi USB-C, veți avea nevoie fie de un cablu USB-C, fie de un adaptor USB-A la USB-C.

1. Urmați instrucțiunile din [documentația Wiki WiFi Overview pentru Wio Terminal](https://wiki.seeedstudio.com/Wio-Terminal-Network-Overview/) pentru a configura Wio Terminal și a actualiza firmware-ul.

## Hello world

Este tradițional ca atunci când începeți să lucrați cu un nou limbaj de programare sau tehnologie să creați o aplicație 'Hello World' - o aplicație mică care afișează textul `"Hello World"` pentru a demonstra că toate instrumentele sunt configurate corect.

Aplicația Hello World pentru Wio Terminal va asigura că aveți Visual Studio Code instalat corect cu PlatformIO și configurat pentru dezvoltarea microcontrollerelor.

### Crearea unui proiect PlatformIO

Primul pas este să creați un nou proiect folosind PlatformIO configurat pentru Wio Terminal.

#### Sarcină - crearea unui proiect PlatformIO

Creați proiectul PlatformIO.

1. Conectați Wio Terminal la computerul dvs.

1. Lansați VS Code.

1. Iconița PlatformIO va fi pe bara de meniu laterală:

    ![Opțiunea de meniu PlatformIO](../../../../../translated_images/ro/vscode-platformio-menu.297be26b9733e5c4.png)

    Selectați această opțiune de meniu, apoi selectați *PIO Home -> Open*.

    ![Opțiunea de deschidere PlatformIO](../../../../../translated_images/ro/vscode-platformio-home-open.3f9a41bfd3f4da1c.png)

1. Din ecranul de bun venit, selectați butonul **+ New Project**.

    ![Butonul pentru proiect nou](../../../../../translated_images/ro/vscode-platformio-welcome-new-button.ba6fc8a4c7b78cc8.png)

1. Configurați proiectul în *Project Wizard*:

    1. Denumiți proiectul `nightlight`.

    1. Din meniul derulant *Board*, tastați `WIO` pentru a filtra plăcile și selectați *Seeeduino Wio Terminal*.

    1. Lăsați *Framework* ca *Arduino*.

    1. Fie lăsați bifată caseta *Use default location*, fie debifați-o și selectați o locație pentru proiectul dvs.

    1. Selectați butonul **Finish**.

    ![Asistentul de configurare completat](../../../../../translated_images/ro/vscode-platformio-nightlight-project-wizard.5c64db4da6037420.png)

    PlatformIO va descărca componentele necesare pentru a compila codul pentru Wio Terminal și va crea proiectul dvs. Acest proces poate dura câteva minute.

### Investigarea proiectului PlatformIO

Explorer-ul din VS Code va afișa o serie de fișiere și foldere create de asistentul PlatformIO.

#### Foldere

* `.pio` - acest folder conține date temporare necesare PlatformIO, cum ar fi biblioteci sau cod compilat. Este recreat automat dacă este șters și nu trebuie să-l adăugați la controlul sursei dacă partajați proiectul pe site-uri precum GitHub.
* `.vscode` - acest folder conține configurația utilizată de PlatformIO și VS Code. Este recreat automat dacă este șters și nu trebuie să-l adăugați la controlul sursei dacă partajați proiectul pe site-uri precum GitHub.
* `include` - acest folder este pentru fișierele header externe necesare atunci când adăugați biblioteci suplimentare în codul dvs. Nu veți folosi acest folder în aceste lecții.
* `lib` - acest folder este pentru bibliotecile externe pe care doriți să le apelați din codul dvs. Nu veți folosi acest folder în aceste lecții.
* `src` - acest folder conține codul sursă principal pentru aplicația dvs. Inițial, va conține un singur fișier - `main.cpp`.
* `test` - acest folder este locul unde ați pune orice teste unitare pentru codul dvs.

#### Fișiere

* `main.cpp` - acest fișier din folderul `src` conține punctul de intrare pentru aplicația dvs. Deschideți acest fișier, și va conține următorul cod:

    ```cpp
    #include <Arduino.h>
    
    void setup() {
      // put your setup code here, to run once:
    }
    
    void loop() {
      // put your main code here, to run repeatedly:
    }
    ```

    Când dispozitivul pornește, cadrul Arduino va rula funcția `setup` o dată, apoi va rula funcția `loop` în mod repetat până când dispozitivul este oprit.

* `.gitignore` - acest fișier listează fișierele și directoarele care trebuie ignorate atunci când adăugați codul la controlul sursei git, cum ar fi încărcarea într-un depozit pe GitHub.

* `platformio.ini` - acest fișier conține configurația pentru dispozitivul și aplicația dvs. Deschideți acest fișier, și va conține următorul cod:

    ```ini
    [env:seeed_wio_terminal]
    platform = atmelsam
    board = seeed_wio_terminal
    framework = arduino
    ```

    Secțiunea `[env:seeed_wio_terminal]` are configurația pentru Wio Terminal. Puteți avea mai multe secțiuni `env` astfel încât codul dvs. să poată fi compilat pentru mai multe plăci.

    Celelalte valori corespund configurației din asistentul de proiect:

  * `platform = atmelsam` definește hardware-ul pe care îl folosește Wio Terminal (un microcontroller bazat pe ATSAMD51).
  * `board = seeed_wio_terminal` definește tipul de placă microcontroller (Wio Terminal).
  * `framework = arduino` definește că acest proiect folosește cadrul Arduino.

### Scrierea aplicației Hello World

Acum sunteți gata să scrieți aplicația Hello World.

#### Sarcină - scrierea aplicației Hello World

Scrieți aplicația Hello World.

1. Deschideți fișierul `main.cpp` în VS Code.

1. Modificați codul astfel încât să corespundă următorului:

    ```cpp
    #include <Arduino.h>

    void setup()
    {
        Serial.begin(9600);

        while (!Serial)
            ; // Wait for Serial to be ready
    
        delay(1000);
    }
    
    void loop()
    {
        Serial.println("Hello World");
        delay(5000);
    }
    ```

    Funcția `setup` inițializează o conexiune la portul serial - în acest caz, portul USB utilizat pentru a conecta Wio Terminal la computerul dvs. Parametrul `9600` este [baud rate](https://wikipedia.org/wiki/Symbol_rate) (cunoscut și ca rată de simboluri), sau viteza cu care datele vor fi trimise prin portul serial în biți pe secundă. Această setare înseamnă 9.600 biți (0 și 1) de date trimise pe secundă. Apoi așteaptă ca portul serial să fie gata.

    Funcția `loop` trimite linia `Hello World!` la portul serial, astfel încât caracterele `Hello World!` împreună cu un caracter de linie nouă. Apoi doarme timp de 5.000 de milisecunde sau 5 secunde. După ce `loop` se termină, este rulat din nou, și din nou, și așa mai departe, cât timp microcontrollerul este alimentat.

1. Puneți Wio Terminal în modul de încărcare. Va trebui să faceți acest lucru de fiecare dată când încărcați cod nou pe dispozitiv:

    1. Trageți de două ori rapid comutatorul de alimentare în jos - acesta va reveni automat la poziția pornit de fiecare dată.

    1. Verificați LED-ul albastru de stare din partea dreaptă a portului USB. Ar trebui să pulseze.
    
    [![Un videoclip care arată cum să puneți Wio Terminal în modul de încărcare](https://img.youtube.com/vi/LeKU_7zLRrQ/0.jpg)](https://youtu.be/LeKU_7zLRrQ)
    
    Faceți clic pe imaginea de mai sus pentru un videoclip care arată cum să faceți acest lucru.

1. Compilați și încărcați codul pe Wio Terminal.

    1. Deschideți paleta de comenzi din VS Code.

    1. Tastați `PlatformIO Upload` pentru a căuta opțiunea de încărcare și selectați *PlatformIO: Upload*.

        ![Opțiunea de încărcare PlatformIO în paleta de comenzi](../../../../../translated_images/ro/vscode-platformio-upload-command-palette.9e0f49cf80d1f1c3.png)

        PlatformIO va compila automat codul dacă este necesar înainte de a-l încărca.

    1. Codul va fi compilat și încărcat pe Wio Terminal.

        > 💁 Dacă utilizați macOS, va apărea o notificare despre *DISK NOT EJECTED PROPERLY*. Acest lucru se întâmplă deoarece Wio Terminal este montat ca un drive ca parte a procesului de flash și este deconectat când codul compilat este scris pe dispozitiv. Puteți ignora această notificare.

    ⚠️ Dacă primiți erori despre portul de încărcare indisponibil, asigurați-vă mai întâi că aveți Wio Terminal conectat la computerul dvs., pornit folosind comutatorul din partea stângă a ecranului și setat în modul de încărcare. Lumina verde de jos ar trebui să fie aprinsă, iar lumina albastră ar trebui să pulseze. Dacă încă primiți eroarea, trageți comutatorul de pornire/oprit de două ori rapid din nou pentru a forța Wio Terminal în modul de încărcare și încercați din nou încărcarea.

PlatformIO are un Serial Monitor care poate monitoriza datele trimise prin cablul USB de la Wio Terminal. Acest lucru vă permite să monitorizați datele trimise de comanda `Serial.println("Hello World");`.

1. Deschideți paleta de comenzi din VS Code.

1. Tastați `PlatformIO Serial` pentru a căuta opțiunea Serial Monitor și selectați *PlatformIO: Serial Monitor*.

    ![Opțiunea PlatformIO Serial Monitor în paleta de comenzi](../../../../../translated_images/ro/vscode-platformio-serial-monitor-command-palette.b348ec841b8a1c14.png)

    Se va deschide un nou terminal, iar datele trimise prin portul serial vor fi transmise în acest terminal:

    ```output
    > Executing task: platformio device monitor <
    
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem101  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Hello World
    Hello World
    ```

    `Hello World` va fi afișat în monitorul serial la fiecare 5 secunde.

> 💁 Puteți găsi acest cod în folderul [code/wio-terminal](../../../../../1-getting-started/lessons/1-introduction-to-iot/code/wio-terminal).

😀 Programul dvs. 'Hello World' a fost un succes!

---

**Declinare de responsabilitate**:  
Acest document a fost tradus folosind serviciul de traducere AI [Co-op Translator](https://github.com/Azure/co-op-translator). Deși ne străduim să asigurăm acuratețea, vă rugăm să rețineți că traducerile automate pot conține erori sau inexactități. Documentul original în limba sa natală ar trebui considerat sursa autoritară. Pentru informații critice, se recomandă traducerea profesională realizată de un specialist uman. Nu ne asumăm responsabilitatea pentru eventualele neînțelegeri sau interpretări greșite care pot apărea din utilizarea acestei traduceri.