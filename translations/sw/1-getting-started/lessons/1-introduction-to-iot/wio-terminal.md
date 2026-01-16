<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "a4f0c166010e31fd7b6ca20bc88dec6d",
  "translation_date": "2025-08-27T22:24:07+00:00",
  "source_file": "1-getting-started/lessons/1-introduction-to-iot/wio-terminal.md",
  "language_code": "sw"
}
-->
# Wio Terminal

[Wio Terminal kutoka Seeed Studios](https://www.seeedstudio.com/Wio-Terminal-p-4509.html) ni microcontroller inayofanana na Arduino, yenye WiFi na sensa kadhaa pamoja na actuators zilizojengwa ndani, pamoja na sehemu za kuongezea sensa na actuators zaidi, kwa kutumia mfumo wa vifaa unaoitwa [Grove](https://www.seeedstudio.com/category/Grove-c-1003.html).

![A Seeed studios Wio Terminal](../../../../../translated_images/sw/wio-terminal.b8299ee16587db9a.webp)

## Usanidi

Ili kutumia Wio Terminal yako, utahitaji kusakinisha programu fulani ya bure kwenye kompyuta yako. Pia utahitaji kusasisha firmware ya Wio Terminal kabla ya kuweza kuunganisha kwenye WiFi.

### Kazi - usanidi

Sakinisha programu inayohitajika na sasisha firmware.

1. Sakinisha Visual Studio Code (VS Code). Hii ni mhariri utakaotumia kuandika msimbo wa kifaa chako kwa C/C++. Rejelea [VS Code documentation](https://code.visualstudio.com?WT.mc_id=academic-17441-jabenn) kwa maelekezo ya kusakinisha VS Code.

    > 💁 IDE nyingine maarufu kwa maendeleo ya Arduino ni [Arduino IDE](https://www.arduino.cc/en/software). Ikiwa tayari unafahamu zana hii, basi unaweza kuitumia badala ya VS Code na PlatformIO, lakini masomo yatatoa maelekezo kwa kutumia VS Code.

1. Sakinisha kiendelezi cha VS Code PlatformIO. Hiki ni kiendelezi cha VS Code kinachosaidia programu za microcontroller kwa C/C++. Rejelea [PlatformIO extension documentation](https://marketplace.visualstudio.com/items?WT.mc_id=academic-17441-jabenn&itemName=platformio.platformio-ide) kwa maelekezo ya kusakinisha kiendelezi hiki kwenye VS Code. Kiendelezi hiki kinategemea kiendelezi cha Microsoft C/C++ ili kufanya kazi na msimbo wa C na C++, na kiendelezi cha C/C++ kinasakinishwa kiotomatiki unapoweka PlatformIO.

1. Unganisha Wio Terminal yako kwenye kompyuta. Wio Terminal ina bandari ya USB-C chini, na hii inahitaji kuunganishwa kwenye bandari ya USB kwenye kompyuta yako. Wio Terminal inakuja na kebo ya USB-C hadi USB-A, lakini ikiwa kompyuta yako ina bandari za USB-C pekee basi utahitaji kebo ya USB-C au adapta ya USB-A hadi USB-C.

1. Fuata maelekezo katika [Wio Terminal Wiki WiFi Overview documentation](https://wiki.seeedstudio.com/Wio-Terminal-Network-Overview/) ili kusanidi Wio Terminal yako na kusasisha firmware.

## Hello World

Ni jadi kuanza na lugha mpya ya programu au teknolojia kwa kuunda programu ya 'Hello World' - programu ndogo inayotoa matokeo kama maandishi `"Hello World"` ili kuonyesha kuwa zana zote zimesanidiwa vizuri.

Programu ya Hello World kwa Wio Terminal itahakikisha kuwa Visual Studio Code imewekwa vizuri na PlatformIO na imesanidiwa kwa maendeleo ya microcontroller.

### Unda mradi wa PlatformIO

Hatua ya kwanza ni kuunda mradi mpya kwa kutumia PlatformIO uliosanidiwa kwa Wio Terminal.

#### Kazi - unda mradi wa PlatformIO

Unda mradi wa PlatformIO.

1. Unganisha Wio Terminal kwenye kompyuta yako

1. Fungua VS Code

1. Ikoni ya PlatformIO itakuwa kwenye menyu ya upande:

    ![The Platform IO menu option](../../../../../translated_images/sw/vscode-platformio-menu.297be26b9733e5c4.webp)

    Chagua kipengele hiki cha menyu, kisha chagua *PIO Home -> Open*

    ![The Platform IO open option](../../../../../translated_images/sw/vscode-platformio-home-open.3f9a41bfd3f4da1c.webp)

1. Kutoka skrini ya kukaribisha, chagua kitufe cha **+ New Project**

    ![The new project button](../../../../../translated_images/sw/vscode-platformio-welcome-new-button.ba6fc8a4c7b78cc8.webp)

1. Sanidi mradi katika *Project Wizard*:

    1. Peana jina la mradi wako `nightlight`

    1. Kutoka kwenye menyu ya *Board*, andika `WIO` ili kuchuja bodi, na chagua *Seeeduino Wio Terminal*

    1. Acha *Framework* kama *Arduino*

    1. Ama acha kisanduku cha *Use default location* kikiwa kimechaguliwa, au kiondoe na uchague eneo la mradi wako

    1. Chagua kitufe cha **Finish**

    ![The completed project wizard](../../../../../translated_images/sw/vscode-platformio-nightlight-project-wizard.5c64db4da6037420.webp)

    PlatformIO itapakua vipengele vinavyohitajika kuunda msimbo kwa Wio Terminal na kuunda mradi wako. Hii inaweza kuchukua dakika chache.

### Chunguza mradi wa PlatformIO

Kichunguzi cha VS Code kitaonyesha faili na folda kadhaa zilizoundwa na PlatformIO wizard.

#### Folda

* `.pio` - folda hii ina data ya muda inayohitajika na PlatformIO kama maktaba au msimbo uliotengenezwa. Inaundwa upya kiotomatiki ikiwa imefutwa, na huhitaji kuongeza hii kwenye udhibiti wa msimbo wa chanzo ikiwa unashiriki mradi wako kwenye tovuti kama GitHub.
* `.vscode` - folda hii ina usanidi unaotumiwa na PlatformIO na VS Code. Inaundwa upya kiotomatiki ikiwa imefutwa, na huhitaji kuongeza hii kwenye udhibiti wa msimbo wa chanzo ikiwa unashiriki mradi wako kwenye tovuti kama GitHub.
* `include` - folda hii ni kwa faili za kichwa za nje zinazohitajika unapoongeza maktaba za ziada kwenye msimbo wako. Hautatumia folda hii katika masomo haya.
* `lib` - folda hii ni kwa maktaba za nje unazotaka kuita kutoka msimbo wako. Hautatumia folda hii katika masomo haya.
* `src` - folda hii ina msimbo wa chanzo kuu wa programu yako. Awali, itakuwa na faili moja - `main.cpp`.
* `test` - folda hii ni mahali ungeweka majaribio ya kitengo kwa msimbo wako.

#### Faili

* `main.cpp` - faili hii katika folda ya `src` ina sehemu ya kuingilia kwa programu yako. Fungua faili hii, na itakuwa na msimbo ufuatao:

    ```cpp
    #include <Arduino.h>
    
    void setup() {
      // put your setup code here, to run once:
    }
    
    void loop() {
      // put your main code here, to run repeatedly:
    }
    ```

    Wakati kifaa kinawashwa, mfumo wa Arduino utaendesha kazi ya `setup` mara moja, kisha kuendesha kazi ya `loop` mara kwa mara hadi kifaa kizimwe.

* `.gitignore` - faili hii inaorodhesha faili na folda za kupuuzwa wakati wa kuongeza msimbo wako kwenye udhibiti wa chanzo cha git, kama vile kupakia kwenye hifadhi kwenye GitHub.

* `platformio.ini` - faili hii ina usanidi wa kifaa chako na programu. Fungua faili hii, na itakuwa na msimbo ufuatao:

    ```ini
    [env:seeed_wio_terminal]
    platform = atmelsam
    board = seeed_wio_terminal
    framework = arduino
    ```

    Sehemu ya `[env:seeed_wio_terminal]` ina usanidi wa Wio Terminal. Unaweza kuwa na sehemu nyingi za `env` ili msimbo wako uweze kutengenezwa kwa bodi nyingi.

    Thamani nyingine zinafanana na usanidi kutoka kwa wizard ya mradi:

  * `platform = atmelsam` inaelezea vifaa ambavyo Wio Terminal inatumia (microcontroller ya ATSAMD51)
  * `board = seeed_wio_terminal` inaelezea aina ya bodi ya microcontroller (Wio Terminal)
  * `framework = arduino` inaelezea kuwa mradi huu unatumia mfumo wa Arduino.

### Andika programu ya Hello World

Sasa uko tayari kuandika programu ya Hello World.

#### Kazi - andika programu ya Hello World

Andika programu ya Hello World.

1. Fungua faili ya `main.cpp` katika VS Code

1. Badilisha msimbo ili ufanane na ufuatao:

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

    Kazi ya `setup` inaanzisha muunganisho kwenye bandari ya serial - katika kesi hii, bandari ya USB inayotumika kuunganisha Wio Terminal kwenye kompyuta yako. Kigezo `9600` ni [baud rate](https://wikipedia.org/wiki/Symbol_rate) (pia inajulikana kama Symbol rate), au kasi ambayo data itatumwa kupitia bandari ya serial kwa bits kwa sekunde. Mpangilio huu unamaanisha bits 9,600 (0s na 1s) za data zinatumwa kila sekunde. Kisha inasubiri bandari ya serial iwe tayari.

    Kazi ya `loop` inatuma mstari `Hello World!` kwenye bandari ya serial, hivyo herufi za `Hello World!` pamoja na tabia mpya ya mstari. Kisha inalala kwa milisekunde 5,000 au sekunde 5. Baada ya `loop` kumalizika, inaendeshwa tena, tena, na tena wakati wote microcontroller imewashwa.

1. Weka Wio Terminal yako katika hali ya kupakia. Utahitaji kufanya hivi kila wakati unapopakia msimbo mpya kwenye kifaa:

    1. Vuta chini mara mbili haraka kwenye swichi ya nguvu - itarudi kwenye nafasi ya kuwasha kila wakati.

    1. Angalia LED ya hali ya bluu upande wa kulia wa bandari ya USB. Inapaswa kuwa inawaka.

    [![Video inayoonyesha jinsi ya kuweka Wio Terminal katika hali ya kupakia](https://img.youtube.com/vi/LeKU_7zLRrQ/0.jpg)](https://youtu.be/LeKU_7zLRrQ)

    Bofya picha hapo juu kwa video inayoonyesha jinsi ya kufanya hivi.

1. Tengeneza na pakia msimbo kwenye Wio Terminal

    1. Fungua paleti ya amri ya VS Code

    1. Andika `PlatformIO Upload` kutafuta chaguo la kupakia, na uchague *PlatformIO: Upload*

        ![The PlatformIO upload option in the command palette](../../../../../translated_images/sw/vscode-platformio-upload-command-palette.9e0f49cf80d1f1c3.webp)

        PlatformIO itatengeneza msimbo kiotomatiki ikiwa inahitajika kabla ya kupakia.

    1. Msimbo utatengenezwa na kupakiwa kwenye Wio Terminal

        > 💁 Ikiwa unatumia macOS, arifa kuhusu *DISK NOT EJECTED PROPERLY* itaonekana. Hii ni kwa sababu Wio Terminal inakuwa imeunganishwa kama diski kama sehemu ya mchakato wa kuandika msimbo, na inatenganishwa wakati msimbo uliotengenezwa unaandikwa kwenye kifaa. Unaweza kupuuza arifa hii.

    ⚠️ Ikiwa unapata makosa kuhusu bandari ya kupakia kutopatikana, hakikisha kwanza kuwa umeunganisha Wio Terminal kwenye kompyuta yako, na kuwasha kwa kutumia swichi upande wa kushoto wa skrini, na kuweka katika hali ya kupakia. Taa ya kijani chini inapaswa kuwaka, na taa ya bluu inapaswa kuwa inawaka. Ikiwa bado unapata kosa, vuta swichi ya kuwasha/kuzima mara mbili haraka tena ili kulazimisha Wio Terminal katika hali ya kupakia na jaribu kupakia tena.

PlatformIO ina Serial Monitor inayoweza kufuatilia data inayotumwa kupitia kebo ya USB kutoka Wio Terminal. Hii inakuwezesha kufuatilia data inayotumwa na amri ya `Serial.println("Hello World");`.

1. Fungua paleti ya amri ya VS Code

1. Andika `PlatformIO Serial` kutafuta chaguo la Serial Monitor, na uchague *PlatformIO: Serial Monitor*

    ![The PlatformIO Serial Monitor option in the command palette](../../../../../translated_images/sw/vscode-platformio-serial-monitor-command-palette.b348ec841b8a1c14.webp)

    Terminal mpya itafunguka, na data inayotumwa kupitia bandari ya serial itatiririka kwenye terminal hii:

    ```output
    > Executing task: platformio device monitor <
    
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem101  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Hello World
    Hello World
    ```

    `Hello World` itachapishwa kwenye serial monitor kila sekunde 5.

> 💁 Unaweza kupata msimbo huu katika folda ya [code/wio-terminal](../../../../../1-getting-started/lessons/1-introduction-to-iot/code/wio-terminal).

😀 Programu yako ya 'Hello World' imefanikiwa!

---

**Kanusho**:  
Hati hii imetafsiriwa kwa kutumia huduma ya tafsiri ya AI [Co-op Translator](https://github.com/Azure/co-op-translator). Ingawa tunajitahidi kuhakikisha usahihi, tafsiri za kiotomatiki zinaweza kuwa na makosa au kutokuwa sahihi. Hati ya asili katika lugha yake ya awali inapaswa kuchukuliwa kama chanzo cha mamlaka. Kwa taarifa muhimu, tafsiri ya kitaalamu ya binadamu inapendekezwa. Hatutawajibika kwa kutoelewana au tafsiri zisizo sahihi zinazotokana na matumizi ya tafsiri hii.