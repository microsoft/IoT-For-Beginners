<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "8ff0d0a1d29832bb896b9c103b69a452",
  "translation_date": "2025-08-27T22:21:08+00:00",
  "source_file": "1-getting-started/lessons/1-introduction-to-iot/pi.md",
  "language_code": "sw"
}
-->
# Raspberry Pi

[Raspberry Pi](https://raspberrypi.org) ni kompyuta ya bodi moja. Unaweza kuongeza vihisi na vihisishi kwa kutumia vifaa na mifumo mbalimbali, na kwa masomo haya utatumia mfumo wa vifaa unaoitwa [Grove](https://www.seeedstudio.com/category/Grove-c-1003.html). Utatumia Python kuandika programu yako ya Pi na kufikia vihisi vya Grove.

![Raspberry Pi 4](../../../../../translated_images/sw/raspberry-pi-4.fd4590d308c3d456.webp)

## Usanidi

Ikiwa unatumia Raspberry Pi kama vifaa vyako vya IoT, una chaguo mbili - unaweza kufanya masomo haya yote na kuandika programu moja kwa moja kwenye Pi, au unaweza kuunganishwa kwa mbali na Pi isiyo na kichwa ('headless') na kuandika programu kutoka kwa kompyuta yako.

Kabla ya kuanza, unahitaji pia kuunganisha Grove Base Hat kwenye Pi yako.

### Kazi - usanidi

Sanidi Grove Base Hat kwenye Pi yako na uconfigure Pi.

1. Unganisha Grove Base Hat kwenye Pi yako. Soketi kwenye hat inafaa juu ya pini zote za GPIO kwenye Pi, ikiteleza hadi chini kabisa ya pini ili kukaa vizuri kwenye msingi. Inakaa juu ya Pi, ikifunika.

    ![Kufunga Grove Hat](../../../../../images/pi-grove-hat-fitting.gif)

1. Amua jinsi unavyotaka kuandika programu yako ya Pi, na nenda kwenye sehemu husika hapa chini:

    * [Fanya kazi moja kwa moja kwenye Pi yako](../../../../../1-getting-started/lessons/1-introduction-to-iot)
    * [Ufikiaji wa mbali kuandika programu ya Pi](../../../../../1-getting-started/lessons/1-introduction-to-iot)

### Fanya kazi moja kwa moja kwenye Pi yako

Ikiwa unataka kufanya kazi moja kwa moja kwenye Pi yako, unaweza kutumia toleo la desktop la Raspberry Pi OS na kusakinisha zana zote unazohitaji.

#### Kazi - fanya kazi moja kwa moja kwenye Pi yako

Sanidi Pi yako kwa maendeleo.

1. Fuata maelekezo katika [Mwongozo wa usanidi wa Raspberry Pi](https://projects.raspberrypi.org/en/projects/raspberry-pi-setting-up) ili kusanidi Pi yako, kuiunganisha na kibodi/panya/monita, kuiunganisha na mtandao wa WiFi au ethernet, na kusasisha programu.

Ili kuandika programu ya Pi kwa kutumia vihisi na vihisishi vya Grove, utahitaji kusakinisha mhariri wa kukuruhusu kuandika programu ya kifaa, na maktaba mbalimbali na zana zinazoshirikiana na vifaa vya Grove.

1. Mara tu Pi yako itakapowashwa upya, fungua Terminal kwa kubofya ikoni ya **Terminal** kwenye upau wa menyu ya juu, au chagua *Menu -> Accessories -> Terminal*

1. Endesha amri ifuatayo ili kuhakikisha OS na programu iliyosakinishwa imesasishwa:

    ```sh
    sudo apt update && sudo apt full-upgrade --yes
    ```

1. Endesha amri zifuatazo ili kusakinisha maktaba zote zinazohitajika kwa vifaa vya Grove:

    ```sh
    sudo apt install git python3-dev python3-pip --yes

    git clone https://github.com/Seeed-Studio/grove.py
    cd grove.py
    sudo pip3 install .

    sudo raspi-config nonint do_i2c 0
    ```

    Hii huanza kwa kusakinisha Git, pamoja na Pip ya kusakinisha pakiti za Python.

    Mojawapo ya vipengele vyenye nguvu vya Python ni uwezo wa kusakinisha [Pakiti za Pip](https://pypi.org) - hizi ni pakiti za programu zilizoandikwa na watu wengine na kuchapishwa mtandaoni. Unaweza kusakinisha pakiti ya Pip kwenye kompyuta yako kwa amri moja, kisha kutumia pakiti hiyo katika programu yako.

    Pakiti za Python za Seeed Grove zinahitaji kusakinishwa kutoka kwa chanzo. Amri hizi zitaklon repo inayoshikilia msimbo wa chanzo wa pakiti hii, kisha kuisakinisha kwa ndani.

    > 💁 Kwa kawaida unapoweka pakiti, inapatikana kila mahali kwenye kompyuta yako, na hii inaweza kusababisha matatizo na matoleo ya pakiti - kama vile programu moja kutegemea toleo moja la pakiti ambalo linavunjika unapoweka toleo jipya kwa programu tofauti. Ili kuepuka tatizo hili, unaweza kutumia [mazingira ya Python ya kawaida](https://docs.python.org/3/library/venv.html), kimsingi nakala ya Python katika folda maalum, na unapoweka pakiti za Pip zinapatikana tu kwa folda hiyo. Hutatumia mazingira ya kawaida unapotumia Pi yako. Script ya usakinishaji ya Grove husakinisha pakiti za Python za Grove kimataifa, kwa hivyo kutumia mazingira ya kawaida ungetakiwa kusanidi mazingira ya kawaida kisha kusakinisha tena pakiti za Grove ndani ya mazingira hayo. Ni rahisi kutumia pakiti za kimataifa, hasa kwa kuwa watengenezaji wengi wa Pi watafanya flash upya SD kadi safi kwa kila mradi.

    Hatimaye, hii inawezesha kiolesura cha I<sup>2</sup>C.

1. Washa upya Pi kwa kutumia menyu au kwa kuendesha amri ifuatayo kwenye Terminal:

    ```sh
    sudo reboot
    ```

1. Mara tu Pi itakapowashwa upya, fungua tena Terminal na endesha amri ifuatayo ili kusakinisha [Visual Studio Code (VS Code)](https://code.visualstudio.com?WT.mc_id=academic-17441-jabenn) - hii ni mhariri utakaotumia kuandika programu yako ya kifaa kwa Python.

    ```sh
    sudo apt install code
    ```

    Mara tu hii itakapowekwa, VS Code itapatikana kutoka kwenye menyu ya juu.

    > 💁 Una uhuru wa kutumia IDE au mhariri wowote wa Python kwa masomo haya ikiwa una zana unayopendelea, lakini masomo yatatoa maelekezo kulingana na kutumia VS Code.

1. Sakinisha Pylance. Hii ni kiendelezi cha VS Code kinachotoa msaada wa lugha ya Python. Rejelea [Nyaraka za kiendelezi cha Pylance](https://marketplace.visualstudio.com/items?WT.mc_id=academic-17441-jabenn&itemName=ms-python.vscode-pylance) kwa maelekezo ya kusakinisha kiendelezi hiki katika VS Code.

### Ufikiaji wa mbali kuandika programu ya Pi

Badala ya kuandika programu moja kwa moja kwenye Pi, inaweza kuendeshwa 'headless', yaani bila kuunganishwa na kibodi/panya/monita, na kuisakinisha na kuandika programu kutoka kwa kompyuta yako, kwa kutumia Visual Studio Code.

#### Sanidi Pi OS

Ili kuandika programu kwa mbali, Pi OS inahitaji kusakinishwa kwenye SD Card.

##### Kazi - sanidi Pi OS

Sanidi Pi OS isiyo na kichwa.

1. Pakua **Raspberry Pi Imager** kutoka [ukurasa wa programu wa Raspberry Pi OS](https://www.raspberrypi.org/software/) na usakinishe

1. Ingiza kadi ya SD kwenye kompyuta yako, ukitumia adapta ikiwa ni lazima

1. Fungua Raspberry Pi Imager

1. Kutoka Raspberry Pi Imager, chagua kitufe cha **CHOOSE OS**, kisha chagua *Raspberry Pi OS (Other)*, ikifuatiwa na *Raspberry Pi OS Lite (32-bit)*

    ![Raspberry Pi Imager na Raspberry Pi OS Lite iliyochaguliwa](../../../../../translated_images/sw/raspberry-pi-imager.24aedeab9e233d84.webp)

    > 💁 Raspberry Pi OS Lite ni toleo la Raspberry Pi OS ambalo halina UI ya desktop au zana za UI. Hizi hazihitajiki kwa Pi isiyo na kichwa na hufanya usakinishaji kuwa mdogo na muda wa kuwasha haraka.

1. Chagua kitufe cha **CHOOSE STORAGE**, kisha chagua kadi yako ya SD

1. Fungua **Advanced Options** kwa kubonyeza `Ctrl+Shift+X`. Chaguo hizi huruhusu usanidi wa awali wa Raspberry Pi OS kabla ya kuandikwa kwenye kadi ya SD.

    1. Angalia kisanduku cha **Enable SSH**, na weka nenosiri kwa mtumiaji `pi`. Hili ndilo nenosiri utakayotumia kuingia kwenye Pi baadaye.

    1. Ikiwa unapanga kuunganishwa na Pi kupitia WiFi, angalia kisanduku cha **Configure WiFi**, na ingiza SSID ya WiFi yako na nenosiri, pamoja na kuchagua nchi yako ya WiFi. Huna haja ya kufanya hivi ikiwa utatumia kebo ya ethernet. Hakikisha mtandao unaounganishwa nao ni sawa na ule kompyuta yako iko.

    1. Angalia kisanduku cha **Set locale settings**, na weka nchi yako na eneo la saa

    1. Chagua kitufe cha **SAVE**

1. Chagua kitufe cha **WRITE** ili kuandika OS kwenye kadi ya SD. Ikiwa unatumia macOS, utaulizwa kuingiza nenosiri lako kwani zana ya msingi inayosakinisha picha za diski inahitaji ufikiaji wa kipekee.

OS itaandikwa kwenye kadi ya SD, na mara tu itakapokamilika kadi itatolewa na OS, na utajulishwa. Ondoa kadi ya SD kutoka kwa kompyuta yako, ingiza kwenye Pi, washa Pi na subiri kwa takriban dakika 2 ili kuwasha vizuri.

#### Unganisha na Pi

Hatua inayofuata ni kufikia Pi kwa mbali. Unaweza kufanya hivi kwa kutumia `ssh`, ambayo inapatikana kwenye macOS, Linux na matoleo ya hivi karibuni ya Windows.

##### Kazi - unganisha na Pi

Fikia Pi kwa mbali.

1. Fungua Terminal au Command Prompt, na ingiza amri ifuatayo ili kuunganishwa na Pi:

    ```sh
    ssh pi@raspberrypi.local
    ```

    Ikiwa uko kwenye Windows ukitumia toleo la zamani ambalo halina `ssh` iliyosakinishwa, unaweza kutumia OpenSSH. Unaweza kupata maelekezo ya usakinishaji katika [Nyaraka za usakinishaji wa OpenSSH](https://docs.microsoft.com//windows-server/administration/openssh/openssh_install_firstuse?WT.mc_id=academic-17441-jabenn).

1. Hii inapaswa kuunganishwa na Pi yako na kukuuliza nenosiri.

    Uwezo wa kupata kompyuta kwenye mtandao wako kwa kutumia `<hostname>.local` ni nyongeza ya hivi karibuni kwa Linux na Windows. Ikiwa unatumia Linux au Windows na unapata makosa yoyote kuhusu Jina la mwenyeji kutopatikana, utahitaji kusakinisha programu ya ziada ili kuwezesha ZeroConf networking (pia inajulikana na Apple kama Bonjour):

    1. Ikiwa unatumia Linux, sakinisha Avahi kwa kutumia amri ifuatayo:

        ```sh
        sudo apt-get install avahi-daemon
        ```

    1. Ikiwa unatumia Windows, njia rahisi ya kuwezesha ZeroConf ni kusakinisha [Bonjour Print Services for Windows](http://support.apple.com/kb/DL999). Unaweza pia kusakinisha [iTunes for Windows](https://www.apple.com/itunes/download/) kupata toleo jipya la zana hiyo (ambayo haipatikani pekee).

    > 💁 Ikiwa huwezi kuunganishwa kwa kutumia `raspberrypi.local`, basi unaweza kutumia anwani ya IP ya Pi yako. Rejelea [Nyaraka za anwani ya IP ya Raspberry Pi](https://www.raspberrypi.org/documentation/remote-access/ip-address.md) kwa maelekezo juu ya njia kadhaa za kupata anwani ya IP.

1. Ingiza nenosiri uliloweka katika Raspberry Pi Imager Advanced Options.

#### Sanidi programu kwenye Pi

Mara tu umeunganishwa na Pi, unahitaji kuhakikisha OS imesasishwa, na kusakinisha maktaba mbalimbali na zana zinazoshirikiana na vifaa vya Grove.

##### Kazi - sanidi programu kwenye Pi

Sanidi programu iliyosakinishwa ya Pi na usakinishe maktaba za Grove.

1. Kutoka kwa kikao chako cha `ssh`, endesha amri ifuatayo ili kusasisha kisha kuwasha upya Pi:

    ```sh
    sudo apt update && sudo apt full-upgrade --yes && sudo reboot
    ```

    Pi itasasishwa na kuwasha upya. Kikao cha `ssh` kitaisha wakati Pi inawasha upya, kwa hivyo subiri kwa takriban sekunde 30 kisha unganisha tena.

1. Kutoka kwa kikao cha `ssh` kilichounganishwa tena, endesha amri zifuatazo ili kusakinisha maktaba zote zinazohitajika kwa vifaa vya Grove:

    ```sh
    sudo apt install git python3-dev python3-pip --yes

    git clone https://github.com/Seeed-Studio/grove.py
    cd grove.py
    sudo pip3 install .

    sudo raspi-config nonint do_i2c 0
    ```

    Hii huanza kwa kusakinisha Git, pamoja na Pip ya kusakinisha pakiti za Python.

    Mojawapo ya vipengele vyenye nguvu vya Python ni uwezo wa kusakinisha [Pakiti za Pip](https://pypi.org) - hizi ni pakiti za programu zilizoandikwa na watu wengine na kuchapishwa mtandaoni. Unaweza kusakinisha pakiti ya Pip kwenye kompyuta yako kwa amri moja, kisha kutumia pakiti hiyo katika programu yako.

    Pakiti za Python za Seeed Grove zinahitaji kusakinishwa kutoka kwa chanzo. Amri hizi zitaklon repo inayoshikilia msimbo wa chanzo wa pakiti hii, kisha kuisakinisha kwa ndani.

    > 💁 Kwa kawaida unapoweka pakiti, inapatikana kila mahali kwenye kompyuta yako, na hii inaweza kusababisha matatizo na matoleo ya pakiti - kama vile programu moja kutegemea toleo moja la pakiti ambalo linavunjika unapoweka toleo jipya kwa programu tofauti. Ili kuepuka tatizo hili, unaweza kutumia [mazingira ya Python ya kawaida](https://docs.python.org/3/library/venv.html), kimsingi nakala ya Python katika folda maalum, na unapoweka pakiti za Pip zinapatikana tu kwa folda hiyo. Hutatumia mazingira ya kawaida unapotumia Pi yako. Script ya usakinishaji ya Grove husakinisha pakiti za Python za Grove kimataifa, kwa hivyo kutumia mazingira ya kawaida ungetakiwa kusanidi mazingira ya kawaida kisha kusakinisha tena pakiti za Grove ndani ya mazingira hayo. Ni rahisi kutumia pakiti za kimataifa, hasa kwa kuwa watengenezaji wengi wa Pi watafanya flash upya SD kadi safi kwa kila mradi.

    Hatimaye, hii inawezesha kiolesura cha I<sup>2</sup>C.

1. Washa upya Pi kwa kuendesha amri ifuatayo:

    ```sh
    sudo reboot
    ```

    Kikao cha `ssh` kitaisha wakati Pi inawasha upya. Hakuna haja ya kuunganishwa tena.

#### Sanidi VS Code kwa ufikiaji wa mbali

Mara tu Pi imewekwa, unaweza kuunganishwa nayo kwa kutumia Visual Studio Code (VS Code) kutoka kwa kompyuta yako - hii ni mhariri wa maandishi wa watengenezaji wa bure utakaotumia kuandika programu yako ya kifaa kwa Python.

##### Kazi - sanidi VS Code kwa ufikiaji wa mbali

Sakinisha programu inayohitajika na uunganishwe kwa mbali na Pi yako.

1. Sakinisha VS Code kwenye kompyuta yako kwa kufuata [Nyaraka za VS Code](https://code.visualstudio.com?WT.mc_id=academic-17441-jabenn)

1. Fuata maelekezo katika [Nyaraka za Maendeleo ya VS Code kwa kutumia SSH](https://code.visualstudio.com/docs/remote/ssh?WT.mc_id=academic-17441-jabenn) kusakinisha vipengele vinavyohitajika

1. Ukifuata maelekezo hayo hayo, unganisha VS Code na Pi

1. Mara tu umeunganishwa, fuata maelekezo ya [kusimamia viendelezi](https://code.visualstudio.com/docs/remote/ssh#_managing-extensions?WT.mc_id=academic-17441-jabenn) kusakinisha kiendelezi cha [Pylance](https://marketplace.visualstudio.com/items?WT.mc_id=academic-17441-jabenn&itemName=ms-python.vscode-pylance) kwa mbali kwenye Pi

## Hello world
Ni kawaida kuanza na lugha mpya ya programu au teknolojia kwa kuunda programu ya 'Hello World' - programu ndogo inayochapisha kitu kama maandishi `"Hello World"` ili kuonyesha kuwa zana zote zimewekwa vizuri.

Programu ya Hello World kwa Pi itahakikisha kuwa una Python na Visual Studio Code zimesakinishwa kwa usahihi.

Programu hii itakuwa kwenye folda inayoitwa `nightlight`, na itatumika tena na msimbo tofauti katika sehemu za baadaye za kazi hii ili kujenga programu ya nightlight.

### Kazi - hello world

Unda programu ya Hello World.

1. Fungua VS Code, moja kwa moja kwenye Pi, au kwenye kompyuta yako na umeunganishwa na Pi ukitumia kiendelezi cha Remote SSH.

1. Fungua Terminal ya VS Code kwa kuchagua *Terminal -> New Terminal*, au kwa kubonyeza `` CTRL+` ``. Itafunguka kwenye folda ya nyumbani ya mtumiaji `pi`.

1. Endesha amri zifuatazo ili kuunda folda kwa ajili ya msimbo wako, na kuunda faili ya Python inayoitwa `app.py` ndani ya folda hiyo:

    ```sh
    mkdir nightlight
    cd nightlight
    touch app.py
    ```

1. Fungua folda hii kwenye VS Code kwa kuchagua *File -> Open...* na kuchagua folda *nightlight*, kisha chagua **OK**.

    ![Kidirisha cha kufungua cha VS Code kinachoonyesha folda ya nightlight](../../../../../translated_images/sw/vscode-open-nightlight-remote.d3d2a4011e30d535.webp)

1. Fungua faili `app.py` kutoka kwa kivinjari cha VS Code na ongeza msimbo ufuatao:

    ```python
    print('Hello World!')
    ```

    Kazi ya `print` inachapisha chochote kinachopitishwa kwake kwenye koni.

1. Kutoka kwenye Terminal ya VS Code, endesha yafuatayo ili kuendesha programu yako ya Python:

    ```sh
    python app.py
    ```

    > 💁 Huenda ukahitaji kuita `python3` moja kwa moja ili kuendesha msimbo huu ikiwa una Python 2 iliyosakinishwa pamoja na Python 3 (toleo jipya zaidi). Ikiwa una Python 2 iliyosakinishwa basi ukitumia `python` itatumia Python 2 badala ya Python 3. Kwa chaguo-msingi, matoleo ya hivi karibuni ya Raspberry Pi OS yana Python 3 pekee iliyosakinishwa.

    Matokeo yafuatayo yataonekana kwenye terminal:

    ```output
    pi@raspberrypi:~/nightlight $ python3 app.py
    Hello World!
    ```

> 💁 Unaweza kupata msimbo huu kwenye folda [code/pi](../../../../../1-getting-started/lessons/1-introduction-to-iot/code/pi).

😀 Programu yako ya 'Hello World' imefanikiwa!

---

**Kanusho**:  
Hati hii imetafsiriwa kwa kutumia huduma ya kutafsiri ya AI [Co-op Translator](https://github.com/Azure/co-op-translator). Ingawa tunajitahidi kuhakikisha usahihi, tafadhali fahamu kuwa tafsiri za kiotomatiki zinaweza kuwa na makosa au kutokuwa sahihi. Hati ya asili katika lugha yake ya awali inapaswa kuzingatiwa kama chanzo cha mamlaka. Kwa taarifa muhimu, tafsiri ya kitaalamu ya binadamu inapendekezwa. Hatutawajibika kwa kutoelewana au tafsiri zisizo sahihi zinazotokana na matumizi ya tafsiri hii.