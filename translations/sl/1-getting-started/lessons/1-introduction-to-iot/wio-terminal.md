<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "a4f0c166010e31fd7b6ca20bc88dec6d",
  "translation_date": "2025-08-28T14:07:39+00:00",
  "source_file": "1-getting-started/lessons/1-introduction-to-iot/wio-terminal.md",
  "language_code": "sl"
}
-->
# Wio Terminal

[Wio Terminal podjetja Seeed Studios](https://www.seeedstudio.com/Wio-Terminal-p-4509.html) je mikrokrmilnik, združljiv z Arduino, ki ima vgrajen WiFi, nekaj senzorjev in aktuatorjev ter priključke za dodajanje dodatnih senzorjev in aktuatorjev prek strojne ekosisteme, imenovane [Grove](https://www.seeedstudio.com/category/Grove-c-1003.html).

![Wio Terminal podjetja Seeed Studios](../../../../../translated_images/sl/wio-terminal.b8299ee16587db9a.png)

## Namestitev

Za uporabo Wio Terminala boste morali na svoj računalnik namestiti nekaj brezplačne programske opreme. Prav tako boste morali posodobiti vdelano programsko opremo Wio Terminala, preden ga povežete z WiFi.

### Naloga - namestitev

Namestite potrebno programsko opremo in posodobite vdelano programsko opremo.

1. Namestite Visual Studio Code (VS Code). To je urejevalnik, ki ga boste uporabljali za pisanje kode za napravo v jeziku C/C++. Za navodila o namestitvi VS Code si oglejte [dokumentacijo VS Code](https://code.visualstudio.com?WT.mc_id=academic-17441-jabenn).

    > 💁 Drug priljubljen IDE za razvoj Arduino je [Arduino IDE](https://www.arduino.cc/en/software). Če ste že seznanjeni s tem orodjem, ga lahko uporabite namesto VS Code in PlatformIO, vendar bodo lekcije podale navodila na podlagi uporabe VS Code.

1. Namestite razširitev PlatformIO za VS Code. To je razširitev za VS Code, ki podpira programiranje mikrokrmilnikov v jeziku C/C++. Za navodila o namestitvi te razširitve v VS Code si oglejte [dokumentacijo razširitve PlatformIO](https://marketplace.visualstudio.com/items?WT.mc_id=academic-17441-jabenn&itemName=platformio.platformio-ide). Ta razširitev je odvisna od razširitve Microsoft C/C++, ki se samodejno namesti ob namestitvi PlatformIO.

1. Povežite Wio Terminal z računalnikom. Wio Terminal ima USB-C priključek na spodnji strani, ki ga je treba povezati z USB priključkom na vašem računalniku. Wio Terminal je priložen z USB-C na USB-A kablom, vendar če vaš računalnik ima samo USB-C priključke, boste potrebovali USB-C kabel ali adapter USB-A na USB-C.

1. Sledite navodilom v [dokumentaciji Wiki WiFi Overview za Wio Terminal](https://wiki.seeedstudio.com/Wio-Terminal-Network-Overview/) za nastavitev Wio Terminala in posodobitev vdelane programske opreme.

## Hello world

Običajno je, da ob začetku uporabe novega programskega jezika ali tehnologije ustvarite aplikacijo 'Hello World' - majhno aplikacijo, ki izpiše nekaj, kot je besedilo `"Hello World"`, da preverite, ali so vsa orodja pravilno nastavljena.

Aplikacija Hello World za Wio Terminal bo zagotovila, da imate pravilno nameščen Visual Studio Code z PlatformIO in nastavljen za razvoj mikrokrmilnikov.

### Ustvarite projekt PlatformIO

Prvi korak je ustvariti nov projekt z uporabo PlatformIO, konfiguriran za Wio Terminal.

#### Naloga - ustvarite projekt PlatformIO

Ustvarite projekt PlatformIO.

1. Povežite Wio Terminal z računalnikom

1. Zaženite VS Code

1. Ikona PlatformIO bo na stranskem meniju:

    ![Možnost menija PlatformIO](../../../../../translated_images/sl/vscode-platformio-menu.297be26b9733e5c4.png)

    Izberite to možnost menija, nato izberite *PIO Home -> Open*

    ![Možnost odpiranja PlatformIO](../../../../../translated_images/sl/vscode-platformio-home-open.3f9a41bfd3f4da1c.png)

1. Na zaslonu dobrodošlice izberite gumb **+ New Project**

    ![Gumb za nov projekt](../../../../../translated_images/sl/vscode-platformio-welcome-new-button.ba6fc8a4c7b78cc8.png)

1. Konfigurirajte projekt v *Project Wizard*:

    1. Poimenujte svoj projekt `nightlight`

    1. V spustnem meniju *Board* vnesite `WIO`, da filtrirate plošče, in izberite *Seeeduino Wio Terminal*

    1. Pustite *Framework* kot *Arduino*

    1. Pustite potrditveno polje *Use default location* označeno ali ga odznačite in izberite lokacijo za svoj projekt

    1. Izberite gumb **Finish**

    ![Dokončan čarovnik za projekt](../../../../../translated_images/sl/vscode-platformio-nightlight-project-wizard.5c64db4da6037420.png)

    PlatformIO bo prenesel komponente, ki jih potrebuje za prevajanje kode za Wio Terminal, in ustvaril vaš projekt. To lahko traja nekaj minut.

### Raziskovanje projekta PlatformIO

Raziskovalec v VS Code bo prikazal več datotek in map, ki jih je ustvaril čarovnik PlatformIO.

#### Mape

* `.pio` - ta mapa vsebuje začasne podatke, ki jih potrebuje PlatformIO, kot so knjižnice ali prevedena koda. Samodejno se ponovno ustvari, če je izbrisana, in je ni treba dodajati v nadzor izvorne kode, če delite svoj projekt na mestih, kot je GitHub.
* `.vscode` - ta mapa vsebuje konfiguracijo, ki jo uporabljata PlatformIO in VS Code. Samodejno se ponovno ustvari, če je izbrisana, in je ni treba dodajati v nadzor izvorne kode, če delite svoj projekt na mestih, kot je GitHub.
* `include` - ta mapa je namenjena zunanjim glavnimi datotekami, ki jih potrebujete pri dodajanju dodatnih knjižnic v svojo kodo. Te mape ne boste uporabljali v teh lekcijah.
* `lib` - ta mapa je namenjena zunanjim knjižnicam, ki jih želite klicati iz svoje kode. Te mape ne boste uporabljali v teh lekcijah.
* `src` - ta mapa vsebuje glavno izvorno kodo za vašo aplikacijo. Sprva bo vsebovala eno datoteko - `main.cpp`.
* `test` - ta mapa je namenjena enotnim testom za vašo kodo.

#### Datoteke

* `main.cpp` - ta datoteka v mapi `src` vsebuje vstopno točko za vašo aplikacijo. Odprite to datoteko, ki bo vsebovala naslednjo kodo:

    ```cpp
    #include <Arduino.h>
    
    void setup() {
      // put your setup code here, to run once:
    }
    
    void loop() {
      // put your main code here, to run repeatedly:
    }
    ```

    Ko se naprava zažene, bo Arduino okvir enkrat izvedel funkcijo `setup`, nato pa funkcijo `loop` izvajal večkrat, dokler naprava ne bo izklopljena.

* `.gitignore` - ta datoteka navaja datoteke in mape, ki jih je treba prezreti pri dodajanju kode v nadzor izvorne kode, kot je nalaganje v repozitorij na GitHub.

* `platformio.ini` - ta datoteka vsebuje konfiguracijo za vašo napravo in aplikacijo. Odprite to datoteko, ki bo vsebovala naslednjo kodo:

    ```ini
    [env:seeed_wio_terminal]
    platform = atmelsam
    board = seeed_wio_terminal
    framework = arduino
    ```

    Odsek `[env:seeed_wio_terminal]` vsebuje konfiguracijo za Wio Terminal. Lahko imate več odsekov `env`, da lahko vaša koda prevaja za več plošč.

    Druge vrednosti ustrezajo konfiguraciji iz čarovnika za projekt:

  * `platform = atmelsam` določa strojno opremo, ki jo uporablja Wio Terminal (mikrokrmilnik, ki temelji na ATSAMD51)
  * `board = seeed_wio_terminal` določa vrsto mikrokrmilniške plošče (Wio Terminal)
  * `framework = arduino` določa, da ta projekt uporablja Arduino okvir.

### Napišite aplikacijo Hello World

Zdaj ste pripravljeni napisati aplikacijo Hello World.

#### Naloga - napišite aplikacijo Hello World

Napišite aplikacijo Hello World.

1. Odprite datoteko `main.cpp` v VS Code

1. Spremenite kodo, da ustreza naslednjemu:

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

    Funkcija `setup` inicializira povezavo s serijskim priključkom - v tem primeru USB priključek, ki se uporablja za povezavo Wio Terminala z vašim računalnikom. Parameter `9600` je [baud rate](https://wikipedia.org/wiki/Symbol_rate) (znan tudi kot simbolna hitrost), ali hitrost, s katero se podatki pošiljajo prek serijskega priključka v bitih na sekundo. Ta nastavitev pomeni, da se pošlje 9.600 bitov (0 in 1) podatkov na sekundo. Nato počaka, da je serijski priključek pripravljen.

    Funkcija `loop` pošlje vrstico `Hello World!` na serijski priključek, skupaj z znakom za novo vrstico. Nato počiva 5.000 milisekund ali 5 sekund. Ko se funkcija `loop` konča, se ponovno zažene, in tako naprej, ves čas, ko je mikrokrmilnik vklopljen.

1. Nastavite Wio Terminal v način nalaganja. To boste morali storiti vsakič, ko naložite novo kodo na napravo:

    1. Dvakrat hitro potegnite navzdol stikalo za vklop - vsakič se bo vrnilo v položaj za vklop.

    1. Preverite modro statusno LED lučko na desni strani USB priključka. Morala bi utripati.
    
    [![Video, ki prikazuje, kako nastaviti Wio Terminal v način nalaganja](https://img.youtube.com/vi/LeKU_7zLRrQ/0.jpg)](https://youtu.be/LeKU_7zLRrQ)
    
    Kliknite zgornjo sliko za video, ki prikazuje, kako to storiti.

1. Sestavite in naložite kodo na Wio Terminal

    1. Odprite ukazno paleto VS Code

    1. Vnesite `PlatformIO Upload`, da poiščete možnost nalaganja, in izberite *PlatformIO: Upload*

        ![Možnost nalaganja PlatformIO v ukazni paleti](../../../../../translated_images/sl/vscode-platformio-upload-command-palette.9e0f49cf80d1f1c3.png)

        PlatformIO bo samodejno sestavil kodo, če je potrebno, preden jo naloži.

    1. Koda bo prevedena in naložena na Wio Terminal

        > 💁 Če uporabljate macOS, se bo pojavilo obvestilo o *DISK NOT EJECTED PROPERLY*. To je zato, ker se Wio Terminal med postopkom nalaganja priklopi kot disk, nato pa se odklopi, ko se prevedena koda zapiše na napravo. To obvestilo lahko prezrete.

    ⚠️ Če dobite napake o nedostopnosti nalagalnega priključka, najprej preverite, ali imate Wio Terminal povezan z računalnikom, vklopljen s stikalom na levi strani zaslona in nastavljen v način nalaganja. Zelena lučka na spodnji strani mora biti prižgana, modra lučka pa mora utripati. Če še vedno dobite napako, dvakrat hitro potegnite stikalo za vklop navzdol, da prisilite Wio Terminal v način nalaganja, in poskusite ponovno naložiti.

PlatformIO ima serijski monitor, ki lahko spremlja podatke, poslane prek USB kabla iz Wio Terminala. To vam omogoča spremljanje podatkov, ki jih pošlje ukaz `Serial.println("Hello World");`.

1. Odprite ukazno paleto VS Code

1. Vnesite `PlatformIO Serial`, da poiščete možnost serijskega monitorja, in izberite *PlatformIO: Serial Monitor*

    ![Možnost serijskega monitorja PlatformIO v ukazni paleti](../../../../../translated_images/sl/vscode-platformio-serial-monitor-command-palette.b348ec841b8a1c14.png)

    Odprl se bo nov terminal, v katerega se bodo pretakali podatki, poslani prek serijskega priključka:

    ```output
    > Executing task: platformio device monitor <
    
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem101  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Hello World
    Hello World
    ```

    `Hello World` se bo natisnil na serijski monitor vsakih 5 sekund.

> 💁 To kodo lahko najdete v mapi [code/wio-terminal](../../../../../1-getting-started/lessons/1-introduction-to-iot/code/wio-terminal).

😀 Vaš program 'Hello World' je bil uspešen!

---

**Omejitev odgovornosti**:  
Ta dokument je bil preveden z uporabo storitve za prevajanje z umetno inteligenco [Co-op Translator](https://github.com/Azure/co-op-translator). Čeprav si prizadevamo za natančnost, vas prosimo, da upoštevate, da lahko avtomatizirani prevodi vsebujejo napake ali netočnosti. Izvirni dokument v njegovem maternem jeziku je treba obravnavati kot avtoritativni vir. Za ključne informacije priporočamo profesionalni človeški prevod. Ne prevzemamo odgovornosti za morebitna nesporazume ali napačne razlage, ki bi nastale zaradi uporabe tega prevoda.