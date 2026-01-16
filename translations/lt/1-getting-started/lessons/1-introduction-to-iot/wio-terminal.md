<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "a4f0c166010e31fd7b6ca20bc88dec6d",
  "translation_date": "2025-08-28T20:04:48+00:00",
  "source_file": "1-getting-started/lessons/1-introduction-to-iot/wio-terminal.md",
  "language_code": "lt"
}
-->
# Wio Terminal

[Wio Terminal iš Seeed Studios](https://www.seeedstudio.com/Wio-Terminal-p-4509.html) yra Arduino suderinamas mikrovaldiklis su integruotu WiFi, kai kuriais jutikliais ir aktuatoriais, taip pat jungtimis papildomiems jutikliams ir aktuatoriams prijungti, naudojant aparatūros ekosistemą, vadinamą [Grove](https://www.seeedstudio.com/category/Grove-c-1003.html).

![Seeed Studios Wio Terminal](../../../../../translated_images/lt/wio-terminal.b8299ee16587db9a.png)

## Paruošimas

Norėdami naudoti savo Wio Terminal, turėsite įdiegti nemokamą programinę įrangą savo kompiuteryje. Taip pat reikės atnaujinti Wio Terminal programinę įrangą prieš prijungiant jį prie WiFi.

### Užduotis - paruošimas

Įdiekite reikiamą programinę įrangą ir atnaujinkite programinę įrangą.

1. Įdiekite Visual Studio Code (VS Code). Tai redaktorius, kurį naudosite rašydami įrenginio kodą C/C++ kalba. Diegimo instrukcijas rasite [VS Code dokumentacijoje](https://code.visualstudio.com?WT.mc_id=academic-17441-jabenn).

    > 💁 Kitas populiarus IDE Arduino kūrimui yra [Arduino IDE](https://www.arduino.cc/en/software). Jei jau esate susipažinę su šiuo įrankiu, galite jį naudoti vietoj VS Code ir PlatformIO, tačiau pamokose bus pateiktos instrukcijos, pagrįstos VS Code naudojimu.

1. Įdiekite VS Code PlatformIO plėtinį. Tai yra VS Code plėtinys, palaikantis mikrovaldiklių programavimą C/C++ kalba. Diegimo instrukcijas rasite [PlatformIO plėtinio dokumentacijoje](https://marketplace.visualstudio.com/items?WT.mc_id=academic-17441-jabenn&itemName=platformio.platformio-ide). Šis plėtinys priklauso nuo Microsoft C/C++ plėtinio, kuris automatiškai įdiegiama kartu su PlatformIO.

1. Prijunkite savo Wio Terminal prie kompiuterio. Wio Terminal turi USB-C jungtį apačioje, kurią reikia prijungti prie USB jungties jūsų kompiuteryje. Wio Terminal komplektuojamas su USB-C į USB-A kabeliu, tačiau jei jūsų kompiuteryje yra tik USB-C jungtys, jums reikės USB-C kabelio arba USB-A į USB-C adapterio.

1. Vadovaukitės [Wio Terminal Wiki WiFi apžvalgos dokumentacijos](https://wiki.seeedstudio.com/Wio-Terminal-Network-Overview/) instrukcijomis, kad nustatytumėte savo Wio Terminal ir atnaujintumėte programinę įrangą.

## Hello World

Pradėjus dirbti su nauja programavimo kalba ar technologija, tradiciškai sukuriama „Hello World“ programa – maža programa, kuri išveda tekstą, pvz., `"Hello World"`, kad parodytų, jog visi įrankiai tinkamai sukonfigūruoti.

„Hello World“ programa Wio Terminal užtikrins, kad Visual Studio Code su PlatformIO būtų tinkamai įdiegta ir paruošta mikrovaldiklių kūrimui.

### Sukurkite PlatformIO projektą

Pirmasis žingsnis – sukurti naują projektą naudojant PlatformIO, sukonfigūruotą Wio Terminal.

#### Užduotis - sukurkite PlatformIO projektą

Sukurkite PlatformIO projektą.

1. Prijunkite Wio Terminal prie savo kompiuterio.

1. Paleiskite VS Code.

1. PlatformIO piktograma bus šoniniame meniu:

    ![PlatformIO meniu parinktis](../../../../../translated_images/lt/vscode-platformio-menu.297be26b9733e5c4.png)

    Pasirinkite šią meniu parinktį, tada pasirinkite *PIO Home -> Open*.

    ![PlatformIO atidarymo parinktis](../../../../../translated_images/lt/vscode-platformio-home-open.3f9a41bfd3f4da1c.png)

1. Iš pasveikinimo ekrano pasirinkite mygtuką **+ New Project**.

    ![Naujo projekto mygtukas](../../../../../translated_images/lt/vscode-platformio-welcome-new-button.ba6fc8a4c7b78cc8.png)

1. Sujunkite projektą *Project Wizard*:

    1. Pavadinkite savo projektą `nightlight`.

    1. Iš *Board* išskleidžiamojo meniu įveskite `WIO`, kad filtruotumėte plokštes, ir pasirinkite *Seeeduino Wio Terminal*.

    1. Palikite *Framework* kaip *Arduino*.

    1. Palikite pažymėtą *Use default location* žymimąjį laukelį arba atžymėkite jį ir pasirinkite vietą savo projektui.

    1. Pasirinkite mygtuką **Finish**.

    ![Užpildytas projekto vedlys](../../../../../translated_images/lt/vscode-platformio-nightlight-project-wizard.5c64db4da6037420.png)

    PlatformIO atsisiųs komponentus, reikalingus Wio Terminal kodo kompiliavimui, ir sukurs jūsų projektą. Tai gali užtrukti kelias minutes.

### Išnagrinėkite PlatformIO projektą

VS Code naršyklėje bus rodomi PlatformIO vedlio sukurti failai ir aplankai.

#### Aplankai

* `.pio` - šiame aplanke yra laikini PlatformIO duomenys, tokie kaip bibliotekos ar sukompiliuotas kodas. Jei jis ištrinamas, jis automatiškai atkuriamas, ir jums nereikia jo pridėti prie šaltinio kodo valdymo, jei dalijatės savo projektu tokiose svetainėse kaip GitHub.
* `.vscode` - šiame aplanke yra PlatformIO ir VS Code naudojama konfigūracija. Jei jis ištrinamas, jis automatiškai atkuriamas, ir jums nereikia jo pridėti prie šaltinio kodo valdymo, jei dalijatės savo projektu tokiose svetainėse kaip GitHub.
* `include` - šis aplankas skirtas išoriniams antraštės failams, reikalingiems pridedant papildomas bibliotekas į jūsų kodą. Šiame kurse šio aplanko nenaudosite.
* `lib` - šis aplankas skirtas išorinėms bibliotekoms, kurias norite naudoti savo kode. Šiame kurse šio aplanko nenaudosite.
* `src` - šiame aplanke yra pagrindinis jūsų programos šaltinio kodas. Iš pradžių jame bus tik vienas failas - `main.cpp`.
* `test` - šiame aplanke galite įdėti vienetinius savo kodo testus.

#### Failai

* `main.cpp` - šis failas `src` aplanke yra jūsų programos įėjimo taškas. Atidarykite šį failą, ir jame bus toks kodas:

    ```cpp
    #include <Arduino.h>
    
    void setup() {
      // put your setup code here, to run once:
    }
    
    void loop() {
      // put your main code here, to run repeatedly:
    }
    ```

    Kai įrenginys paleidžiamas, Arduino karkasas vieną kartą paleidžia `setup` funkciją, o tada nuolat kartoja `loop` funkciją, kol įrenginys išjungiamas.

* `.gitignore` - šiame faile nurodomi failai ir katalogai, kurių nereikia įtraukti į git šaltinio kodo valdymą, pvz., įkeliant į GitHub saugyklą.

* `platformio.ini` - šiame faile yra jūsų įrenginio ir programos konfigūracija. Atidarykite šį failą, ir jame bus toks kodas:

    ```ini
    [env:seeed_wio_terminal]
    platform = atmelsam
    board = seeed_wio_terminal
    framework = arduino
    ```

    `[env:seeed_wio_terminal]` skyriuje yra Wio Terminal konfigūracija. Galite turėti kelis `env` skyrius, kad jūsų kodas būtų sukompiliuotas kelioms plokštėms.

    Kitos reikšmės atitinka projekto vedlio konfigūraciją:

  * `platform = atmelsam` apibrėžia aparatūrą, kurią naudoja Wio Terminal (ATSAMD51 pagrindu sukurtas mikrovaldiklis).
  * `board = seeed_wio_terminal` apibrėžia mikrovaldiklio plokštės tipą (Wio Terminal).
  * `framework = arduino` apibrėžia, kad šis projektas naudoja Arduino karkasą.

### Parašykite Hello World programą

Dabar esate pasiruošę parašyti Hello World programą.

#### Užduotis - parašykite Hello World programą

Parašykite Hello World programą.

1. Atidarykite `main.cpp` failą VS Code.

1. Pakeiskite kodą taip, kad jis atitiktų šį:

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

    `setup` funkcija inicijuoja ryšį su serijiniu prievadu – šiuo atveju USB prievadu, kuris naudojamas Wio Terminal prijungti prie jūsų kompiuterio. Parametras `9600` yra [baudų dažnis](https://wikipedia.org/wiki/Symbol_rate) (dar vadinamas simbolių dažniu) arba duomenų perdavimo greitis serijiniu prievadu bitais per sekundę. Šis nustatymas reiškia, kad per sekundę perduodama 9 600 bitų (0 ir 1). Tada jis laukia, kol serijinis prievadas bus paruoštas.

    `loop` funkcija siunčia eilutę `Hello World!` į serijinį prievadą, kartu su naujos eilutės simboliu. Tada ji užmiega 5 000 milisekundžių arba 5 sekundes. Kai `loop` baigiasi, ji vėl paleidžiama, ir taip toliau, kol mikrovaldiklis yra įjungtas.

1. Įjunkite Wio Terminal į įkėlimo režimą. Tai reikės padaryti kiekvieną kartą, kai įkeliate naują kodą į įrenginį:

    1. Du kartus greitai patraukite maitinimo jungiklį žemyn – jis kiekvieną kartą grįš į įjungtą padėtį.

    1. Patikrinkite mėlyną būsenos LED šviesą dešinėje USB prievado pusėje. Ji turėtų pulsuoti.
    
    [![Vaizdo įrašas, kaip įjungti Wio Terminal į įkėlimo režimą](https://img.youtube.com/vi/LeKU_7zLRrQ/0.jpg)](https://youtu.be/LeKU_7zLRrQ)
    
    Spustelėkite aukščiau esantį vaizdą, kad pamatytumėte, kaip tai padaryti.

1. Sukurkite ir įkelkite kodą į Wio Terminal.

    1. Atidarykite VS Code komandų paletę.

    1. Įveskite `PlatformIO Upload`, kad ieškotumėte įkėlimo parinkties, ir pasirinkite *PlatformIO: Upload*.

        ![PlatformIO įkėlimo parinktis komandų paletėje](../../../../../translated_images/lt/vscode-platformio-upload-command-palette.9e0f49cf80d1f1c3.png)

        PlatformIO automatiškai sukurs kodą, jei reikia, prieš įkeliant.

    1. Kodas bus sukompiliuotas ir įkeltas į Wio Terminal.

        > 💁 Jei naudojate macOS, pasirodys pranešimas apie *DISK NOT EJECTED PROPERLY*. Taip yra todėl, kad Wio Terminal yra prijungiamas kaip diskas dalyvaujant mirksėjimo procese, ir jis atjungiamas, kai sukompiliuotas kodas įrašomas į įrenginį. Galite ignoruoti šį pranešimą.

    ⚠️ Jei gaunate klaidų apie neprieinamą įkėlimo prievadą, pirmiausia įsitikinkite, kad Wio Terminal yra prijungtas prie jūsų kompiuterio, įjungtas naudojant jungiklį kairėje ekrano pusėje ir nustatytas į įkėlimo režimą. Žalia šviesa apačioje turėtų būti įjungta, o mėlyna šviesa turėtų pulsuoti. Jei vis dar gaunate klaidą, dar kartą greitai du kartus patraukite įjungimo/išjungimo jungiklį žemyn, kad priverstumėte Wio Terminal į įkėlimo režimą, ir bandykite įkelti dar kartą.

PlatformIO turi Serijinį Monitorių, kuris gali stebėti duomenis, siunčiamus per USB kabelį iš Wio Terminal. Tai leidžia stebėti duomenis, siunčiamus `Serial.println("Hello World");` komanda.

1. Atidarykite VS Code komandų paletę.

1. Įveskite `PlatformIO Serial`, kad ieškotumėte Serijinio Monitoriaus parinkties, ir pasirinkite *PlatformIO: Serial Monitor*.

    ![PlatformIO Serijinio Monitoriaus parinktis komandų paletėje](../../../../../translated_images/lt/vscode-platformio-serial-monitor-command-palette.b348ec841b8a1c14.png)

    Atsidarys naujas terminalas, ir duomenys, siunčiami per serijinį prievadą, bus rodomi šiame terminale:

    ```output
    > Executing task: platformio device monitor <
    
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem101  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Hello World
    Hello World
    ```

    `Hello World` bus spausdinama serijiniame monitoriuje kas 5 sekundes.

> 💁 Šį kodą galite rasti [code/wio-terminal](../../../../../1-getting-started/lessons/1-introduction-to-iot/code/wio-terminal) aplanke.

😀 Jūsų „Hello World“ programa pavyko!

---

**Atsakomybės apribojimas**:  
Šis dokumentas buvo išverstas naudojant AI vertimo paslaugą [Co-op Translator](https://github.com/Azure/co-op-translator). Nors siekiame tikslumo, prašome atkreipti dėmesį, kad automatiniai vertimai gali turėti klaidų ar netikslumų. Originalus dokumentas jo gimtąja kalba turėtų būti laikomas autoritetingu šaltiniu. Kritinei informacijai rekomenduojama naudoti profesionalų žmogaus vertimą. Mes neprisiimame atsakomybės už nesusipratimus ar klaidingus interpretavimus, atsiradusius dėl šio vertimo naudojimo.