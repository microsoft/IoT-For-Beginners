<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "a4f0c166010e31fd7b6ca20bc88dec6d",
  "translation_date": "2025-08-28T14:06:59+00:00",
  "source_file": "1-getting-started/lessons/1-introduction-to-iot/wio-terminal.md",
  "language_code": "hr"
}
-->
# Wio Terminal

[Wio Terminal od Seeed Studios](https://www.seeedstudio.com/Wio-Terminal-p-4509.html) je mikrokontroler kompatibilan s Arduinom, s ugrađenim WiFi-jem, senzorima i aktuatorima, kao i priključcima za dodavanje dodatnih senzora i aktuatora koristeći hardverski ekosustav nazvan [Grove](https://www.seeedstudio.com/category/Grove-c-1003.html).

![Wio Terminal od Seeed Studios](../../../../../translated_images/hr/wio-terminal.b8299ee16587db9a.png)

## Postavljanje

Za korištenje Wio Terminala, potrebno je instalirati besplatan softver na vaše računalo. Također, potrebno je ažurirati firmware Wio Terminala prije nego što ga povežete s WiFi-jem.

### Zadatak - postavljanje

Instalirajte potrebni softver i ažurirajte firmware.

1. Instalirajte Visual Studio Code (VS Code). Ovo je editor koji ćete koristiti za pisanje koda za uređaj u C/C++. Pogledajte [dokumentaciju za VS Code](https://code.visualstudio.com?WT.mc_id=academic-17441-jabenn) za upute o instalaciji.

    > 💁 Drugi popularni IDE za razvoj s Arduinom je [Arduino IDE](https://www.arduino.cc/en/software). Ako ste već upoznati s ovim alatom, možete ga koristiti umjesto VS Code-a i PlatformIO-a, ali lekcije će se temeljiti na korištenju VS Code-a.

1. Instalirajte PlatformIO ekstenziju za VS Code. Ovo je ekstenzija za VS Code koja podržava programiranje mikrokontrolera u C/C++. Pogledajte [dokumentaciju za PlatformIO ekstenziju](https://marketplace.visualstudio.com/items?WT.mc_id=academic-17441-jabenn&itemName=platformio.platformio-ide) za upute o instalaciji ove ekstenzije u VS Code. Ova ekstenzija ovisi o Microsoft C/C++ ekstenziji koja se automatski instalira prilikom instalacije PlatformIO-a.

1. Povežite Wio Terminal s vašim računalom. Wio Terminal ima USB-C priključak na dnu, koji treba povezati s USB priključkom na vašem računalu. Wio Terminal dolazi s USB-C na USB-A kabelom, ali ako vaše računalo ima samo USB-C priključke, trebat će vam USB-C kabel ili USB-A na USB-C adapter.

1. Slijedite upute u [Wio Terminal Wiki WiFi Overview dokumentaciji](https://wiki.seeedstudio.com/Wio-Terminal-Network-Overview/) za postavljanje vašeg Wio Terminala i ažuriranje firmware-a.

## Hello world

Tradicionalno je, kada započinjete s novim programskim jezikom ili tehnologijom, kreirati aplikaciju 'Hello World' - malu aplikaciju koja ispisuje tekst poput `"Hello World"` kako bi se pokazalo da su svi alati ispravno konfigurirani.

Hello World aplikacija za Wio Terminal osigurat će da imate ispravno instaliran Visual Studio Code s PlatformIO-om i postavljen za razvoj mikrokontrolera.

### Kreiranje PlatformIO projekta

Prvi korak je kreiranje novog projekta koristeći PlatformIO konfiguriranog za Wio Terminal.

#### Zadatak - kreiranje PlatformIO projekta

Kreirajte PlatformIO projekt.

1. Povežite Wio Terminal s vašim računalom.

1. Pokrenite VS Code.

1. Ikona PlatformIO-a bit će na bočnoj traci izbornika:

    ![Opcija PlatformIO izbornika](../../../../../translated_images/hr/vscode-platformio-menu.297be26b9733e5c4.png)

    Odaberite ovu opciju izbornika, zatim odaberite *PIO Home -> Open*.

    ![Opcija PlatformIO otvaranja](../../../../../translated_images/hr/vscode-platformio-home-open.3f9a41bfd3f4da1c.png)

1. Na početnom zaslonu odaberite gumb **+ New Project**.

    ![Gumb za novi projekt](../../../../../translated_images/hr/vscode-platformio-welcome-new-button.ba6fc8a4c7b78cc8.png)

1. Konfigurirajte projekt u *Project Wizard*-u:

    1. Nazovite svoj projekt `nightlight`.

    1. U padajućem izborniku *Board* upišite `WIO` kako biste filtrirali ploče i odaberite *Seeeduino Wio Terminal*.

    1. Ostavite *Framework* kao *Arduino*.

    1. Ostavite označen *Use default location* ili ga odznačite i odaberite lokaciju za vaš projekt.

    1. Odaberite gumb **Finish**.

    ![Dovršeni čarobnjak za projekt](../../../../../translated_images/hr/vscode-platformio-nightlight-project-wizard.5c64db4da6037420.png)

    PlatformIO će preuzeti komponente potrebne za kompajliranje koda za Wio Terminal i kreirati vaš projekt. Ovo može potrajati nekoliko minuta.

### Istraživanje PlatformIO projekta

VS Code explorer prikazat će niz datoteka i mapa koje je kreirao PlatformIO čarobnjak.

#### Mape

* `.pio` - ova mapa sadrži privremene podatke potrebne PlatformIO-u, poput biblioteka ili kompajliranog koda. Automatski se ponovno kreira ako se izbriše, i ne trebate je dodavati u kontrolu izvornog koda ako dijelite svoj projekt na stranicama poput GitHuba.
* `.vscode` - ova mapa sadrži konfiguraciju koju koriste PlatformIO i VS Code. Automatski se ponovno kreira ako se izbriše, i ne trebate je dodavati u kontrolu izvornog koda ako dijelite svoj projekt na stranicama poput GitHuba.
* `include` - ova mapa je za vanjske header datoteke potrebne prilikom dodavanja dodatnih biblioteka u vaš kod. Nećete koristiti ovu mapu u ovim lekcijama.
* `lib` - ova mapa je za vanjske biblioteke koje želite pozvati iz vašeg koda. Nećete koristiti ovu mapu u ovim lekcijama.
* `src` - ova mapa sadrži glavni izvorni kod za vašu aplikaciju. U početku će sadržavati jednu datoteku - `main.cpp`.
* `test` - ova mapa je mjesto gdje biste stavili sve unit testove za vaš kod.

#### Datoteke

* `main.cpp` - ova datoteka u mapi `src` sadrži ulaznu točku za vašu aplikaciju. Otvorite ovu datoteku, i sadržavat će sljedeći kod:

    ```cpp
    #include <Arduino.h>
    
    void setup() {
      // put your setup code here, to run once:
    }
    
    void loop() {
      // put your main code here, to run repeatedly:
    }
    ```

    Kada se uređaj pokrene, Arduino framework će jednom pokrenuti funkciju `setup`, a zatim će funkciju `loop` pokretati opetovano dok se uređaj ne isključi.

* `.gitignore` - ova datoteka navodi datoteke i direktorije koje treba ignorirati prilikom dodavanja vašeg koda u git kontrolu izvornog koda, poput učitavanja u repozitorij na GitHubu.

* `platformio.ini` - ova datoteka sadrži konfiguraciju za vaš uređaj i aplikaciju. Otvorite ovu datoteku, i sadržavat će sljedeći kod:

    ```ini
    [env:seeed_wio_terminal]
    platform = atmelsam
    board = seeed_wio_terminal
    framework = arduino
    ```

    Sekcija `[env:seeed_wio_terminal]` ima konfiguraciju za Wio Terminal. Možete imati više `env` sekcija kako bi vaš kod mogao biti kompajliran za više ploča.

    Ostale vrijednosti odgovaraju konfiguraciji iz čarobnjaka za projekt:

  * `platform = atmelsam` definira hardver koji koristi Wio Terminal (mikrokontroler baziran na ATSAMD51).
  * `board = seeed_wio_terminal` definira tip mikrokontrolerske ploče (Wio Terminal).
  * `framework = arduino` definira da ovaj projekt koristi Arduino framework.

### Pisanje Hello World aplikacije

Sada ste spremni napisati Hello World aplikaciju.

#### Zadatak - pisanje Hello World aplikacije

Napišite Hello World aplikaciju.

1. Otvorite datoteku `main.cpp` u VS Code-u.

1. Promijenite kod tako da odgovara sljedećem:

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

    Funkcija `setup` inicijalizira vezu s serijskim portom - u ovom slučaju, USB port koji se koristi za povezivanje Wio Terminala s vašim računalom. Parametar `9600` je [baud rate](https://wikipedia.org/wiki/Symbol_rate) (poznat i kao simbolička brzina), odnosno brzina kojom će se podaci slati preko serijskog porta u bitovima po sekundi. Ova postavka znači da se 9,600 bitova (0 i 1) podataka šalje svake sekunde. Zatim čeka da serijski port bude spreman.

    Funkcija `loop` šalje liniju `Hello World!` na serijski port, zajedno s novim znakom za red. Zatim spava 5,000 milisekundi ili 5 sekundi. Nakon što funkcija `loop` završi, ponovno se pokreće, i tako dalje sve dok je mikrokontroler uključen.

1. Stavite Wio Terminal u način za učitavanje. Ovo ćete morati učiniti svaki put kada učitavate novi kod na uređaj:

    1. Dvaput brzo povucite prekidač za napajanje prema dolje - on će se svaki put vratiti u uključeni položaj.

    1. Provjerite plavu statusnu LED diodu s desne strane USB priključka. Trebala bi pulsirati.
    
    [![Video koji pokazuje kako staviti Wio Terminal u način za učitavanje](https://img.youtube.com/vi/LeKU_7zLRrQ/0.jpg)](https://youtu.be/LeKU_7zLRrQ)
    
    Kliknite na sliku iznad za video koji pokazuje kako to učiniti.

1. Kompajlirajte i učitajte kod na Wio Terminal.

    1. Otvorite VS Code naredbeni izbornik.

    1. Upišite `PlatformIO Upload` kako biste pretražili opciju za učitavanje i odaberite *PlatformIO: Upload*.

        ![Opcija PlatformIO učitavanja u naredbenom izborniku](../../../../../translated_images/hr/vscode-platformio-upload-command-palette.9e0f49cf80d1f1c3.png)

        PlatformIO će automatski kompajlirati kod ako je potrebno prije učitavanja.

    1. Kod će biti kompajliran i učitan na Wio Terminal.

        > 💁 Ako koristite macOS, pojavit će se obavijest o *DISK NOT EJECTED PROPERLY*. To je zato što se Wio Terminal montira kao disk tijekom procesa učitavanja, i odspaja se kada se kompajlirani kod zapisuje na uređaj. Možete ignorirati ovu obavijest.

    ⚠️ Ako dobijete greške o nedostupnosti porta za učitavanje, prvo provjerite imate li Wio Terminal povezan s vašim računalom, uključen pomoću prekidača na lijevoj strani zaslona i postavljen u način za učitavanje. Zelena svjetlost na dnu trebala bi biti uključena, a plava svjetlost trebala bi pulsirati. Ako i dalje dobijete grešku, povucite prekidač za uključivanje/isključivanje dvaput brzo kako biste prisilili Wio Terminal u način za učitavanje i pokušajte ponovno učitati kod.

PlatformIO ima Serijski Monitor koji može pratiti podatke poslane preko USB kabela s Wio Terminala. Ovo vam omogućuje praćenje podataka koje šalje naredba `Serial.println("Hello World");`.

1. Otvorite VS Code naredbeni izbornik.

1. Upišite `PlatformIO Serial` kako biste pretražili opciju za Serijski Monitor i odaberite *PlatformIO: Serial Monitor*.

    ![Opcija PlatformIO Serijskog Monitora u naredbenom izborniku](../../../../../translated_images/hr/vscode-platformio-serial-monitor-command-palette.b348ec841b8a1c14.png)

    Otvorit će se novi terminal, i podaci poslani preko serijskog porta bit će prikazani u ovom terminalu:

    ```output
    > Executing task: platformio device monitor <
    
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem101  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Hello World
    Hello World
    ```

    `Hello World` će se ispisivati na serijskom monitoru svakih 5 sekundi.

> 💁 Ovaj kod možete pronaći u mapi [code/wio-terminal](../../../../../1-getting-started/lessons/1-introduction-to-iot/code/wio-terminal).

😀 Vaš 'Hello World' program je uspješno pokrenut!

---

**Odricanje od odgovornosti**:  
Ovaj dokument je preveden pomoću AI usluge za prevođenje [Co-op Translator](https://github.com/Azure/co-op-translator). Iako nastojimo osigurati točnost, imajte na umu da automatski prijevodi mogu sadržavati pogreške ili netočnosti. Izvorni dokument na izvornom jeziku treba smatrati autoritativnim izvorom. Za ključne informacije preporučuje se profesionalni prijevod od strane čovjeka. Ne preuzimamo odgovornost za nesporazume ili pogrešna tumačenja koja mogu proizaći iz korištenja ovog prijevoda.