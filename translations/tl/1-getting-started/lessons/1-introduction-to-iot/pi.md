<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "8ff0d0a1d29832bb896b9c103b69a452",
  "translation_date": "2025-08-27T22:45:28+00:00",
  "source_file": "1-getting-started/lessons/1-introduction-to-iot/pi.md",
  "language_code": "tl"
}
-->
# Raspberry Pi

Ang [Raspberry Pi](https://raspberrypi.org) ay isang single-board computer. Maaari kang magdagdag ng mga sensor at actuator gamit ang iba't ibang mga device at ecosystem, at para sa mga araling ito gagamit tayo ng hardware ecosystem na tinatawag na [Grove](https://www.seeedstudio.com/category/Grove-c-1003.html). Gagamitin mo ang Python upang mag-code sa iyong Pi at ma-access ang mga Grove sensor.

![Isang Raspberry Pi 4](../../../../../translated_images/tl/raspberry-pi-4.fd4590d308c3d456.webp)

## Setup

Kung gagamit ka ng Raspberry Pi bilang iyong IoT hardware, may dalawang opsyon ka - maaari mong gawin ang lahat ng mga araling ito at mag-code nang direkta sa Pi, o maaari kang kumonekta nang remote sa isang 'headless' Pi at mag-code mula sa iyong computer.

Bago ka magsimula, kailangan mo ring ikonekta ang Grove Base Hat sa iyong Pi.

### Gawain - setup

I-install ang Grove base hat sa iyong Pi at i-configure ang Pi.

1. Ikonekta ang Grove base hat sa iyong Pi. Ang socket sa hat ay akma sa lahat ng GPIO pins sa Pi, na dumudulas pababa sa mga pin upang maayos na maupo sa base. Nakapatong ito sa Pi, tinatakpan ito.

    ![Pagkabit ng grove hat](../../../../../images/pi-grove-hat-fitting.gif)

1. Magpasya kung paano mo gustong i-program ang iyong Pi, at pumunta sa kaukulang seksyon sa ibaba:

    * [Magtrabaho nang direkta sa iyong Pi](../../../../../1-getting-started/lessons/1-introduction-to-iot)
    * [Remote access para mag-code sa Pi](../../../../../1-getting-started/lessons/1-introduction-to-iot)

### Magtrabaho nang direkta sa iyong Pi

Kung nais mong magtrabaho nang direkta sa iyong Pi, maaari mong gamitin ang desktop na bersyon ng Raspberry Pi OS at i-install ang lahat ng mga tool na kailangan mo.

#### Gawain - magtrabaho nang direkta sa iyong Pi

I-set up ang iyong Pi para sa development.

1. Sundin ang mga tagubilin sa [Raspberry Pi setup guide](https://projects.raspberrypi.org/en/projects/raspberry-pi-setting-up) upang i-set up ang iyong Pi, ikonekta ito sa keyboard/mouse/monitor, ikonekta ito sa iyong WiFi o ethernet network, at i-update ang software.

Upang mag-program sa Pi gamit ang Grove sensors at actuators, kailangan mong mag-install ng editor upang makapagsulat ng device code, at iba't ibang mga library at tool na nakikipag-ugnayan sa Grove hardware.

1. Kapag nag-reboot na ang iyong Pi, buksan ang Terminal sa pamamagitan ng pag-click sa **Terminal** icon sa top menu bar, o piliin ang *Menu -> Accessories -> Terminal*

1. Patakbuhin ang sumusunod na command upang matiyak na ang OS at ang naka-install na software ay up-to-date:

    ```sh
    sudo apt update && sudo apt full-upgrade --yes
    ```

1. Patakbuhin ang mga sumusunod na command upang i-install ang lahat ng kinakailangang library para sa Grove hardware:

    ```sh
    sudo apt install git python3-dev python3-pip --yes

    git clone https://github.com/Seeed-Studio/grove.py
    cd grove.py
    sudo pip3 install .

    sudo raspi-config nonint do_i2c 0
    ```

    Nagsisimula ito sa pag-install ng Git, kasama ang Pip para mag-install ng mga Python package.

    Isa sa mga makapangyarihang tampok ng Python ay ang kakayahang mag-install ng [Pip packages](https://pypi.org) - ito ay mga package ng code na isinulat ng ibang tao at inilathala sa Internet. Maaari kang mag-install ng Pip package sa iyong computer gamit ang isang command, pagkatapos ay gamitin ang package na iyon sa iyong code.

    Ang Seeed Grove Python packages ay kailangang i-install mula sa source. Ang mga command na ito ay magka-clone ng repo na naglalaman ng source code para sa package na ito, pagkatapos ay i-install ito nang lokal.

    > 💁 Sa default, kapag nag-install ka ng package, ito ay magagamit saanman sa iyong computer, at maaari itong magdulot ng mga problema sa mga bersyon ng package - tulad ng isang application na umaasa sa isang bersyon ng package na nasisira kapag nag-install ka ng bagong bersyon para sa ibang application. Upang maiwasan ang problemang ito, maaari kang gumamit ng [Python virtual environment](https://docs.python.org/3/library/venv.html), na mahalagang isang kopya ng Python sa isang dedikadong folder, at kapag nag-install ka ng Pip packages, sila ay mai-install lamang sa folder na iyon. Hindi ka gagamit ng virtual environments kapag ginagamit ang iyong Pi. Ang Grove install script ay nag-i-install ng Grove Python packages globally, kaya kung gagamit ka ng virtual environment, kailangan mong mag-set up ng virtual environment pagkatapos ay manu-manong i-reinstall ang Grove packages sa loob ng environment na iyon. Mas madali ang paggamit ng global packages, lalo na't maraming Pi developers ang nagre-reflash ng malinis na SD card para sa bawat proyekto.

    Sa wakas, pinapagana nito ang I<sup>2</sup>C interface.

1. I-reboot ang Pi gamit ang menu o patakbuhin ang sumusunod na command sa Terminal:

    ```sh
    sudo reboot
    ```

1. Kapag nag-reboot na ang Pi, muling buksan ang Terminal at patakbuhin ang sumusunod na command upang i-install ang [Visual Studio Code (VS Code)](https://code.visualstudio.com?WT.mc_id=academic-17441-jabenn) - ito ang editor na gagamitin mo upang magsulat ng device code sa Python.

    ```sh
    sudo apt install code
    ```

    Kapag na-install na ito, ang VS Code ay magiging available mula sa top menu.

    > 💁 Malaya kang gumamit ng anumang Python IDE o editor para sa mga araling ito kung mayroon kang preferred na tool, ngunit ang mga aralin ay magbibigay ng mga tagubilin batay sa paggamit ng VS Code.

1. I-install ang Pylance. Ito ay isang extension para sa VS Code na nagbibigay ng Python language support. Tingnan ang [Pylance extension documentation](https://marketplace.visualstudio.com/items?WT.mc_id=academic-17441-jabenn&itemName=ms-python.vscode-pylance) para sa mga tagubilin sa pag-install ng extension na ito sa VS Code.

### Remote access para mag-code sa Pi

Sa halip na mag-code nang direkta sa Pi, maaari itong patakbuhin bilang 'headless', ibig sabihin ay hindi nakakonekta sa keyboard/mouse/monitor, at i-configure at mag-code dito mula sa iyong computer gamit ang Visual Studio Code.

#### I-set up ang Pi OS

Upang mag-code nang remote, kailangang i-install ang Pi OS sa isang SD Card.

##### Gawain - i-set up ang Pi OS

I-set up ang headless Pi OS.

1. I-download ang **Raspberry Pi Imager** mula sa [Raspberry Pi OS software page](https://www.raspberrypi.org/software/) at i-install ito.

1. Ipasok ang SD card sa iyong computer, gamit ang adapter kung kinakailangan.

1. Buksan ang Raspberry Pi Imager.

1. Mula sa Raspberry Pi Imager, piliin ang **CHOOSE OS** button, pagkatapos ay piliin ang *Raspberry Pi OS (Other)*, kasunod ng *Raspberry Pi OS Lite (32-bit)*.

    ![Ang Raspberry Pi Imager na may Raspberry Pi OS Lite na napili](../../../../../translated_images/tl/raspberry-pi-imager.24aedeab9e233d84.webp)

    > 💁 Ang Raspberry Pi OS Lite ay isang bersyon ng Raspberry Pi OS na walang desktop UI o UI-based tools. Hindi ito kailangan para sa isang headless Pi at ginagawang mas maliit ang install at mas mabilis ang boot up time.

1. Piliin ang **CHOOSE STORAGE** button, pagkatapos ay piliin ang iyong SD card.

1. Buksan ang **Advanced Options** sa pamamagitan ng pagpindot sa `Ctrl+Shift+X`. Ang mga opsyon na ito ay nagbibigay-daan sa ilang pre-configuration ng Raspberry Pi OS bago ito i-image sa SD card.

    1. I-check ang **Enable SSH** check box, at mag-set ng password para sa `pi` user. Ito ang password na gagamitin mo upang mag-log in sa Pi mamaya.

    1. Kung plano mong kumonekta sa Pi gamit ang WiFi, i-check ang **Configure WiFi** check box, at ilagay ang iyong WiFi SSID at password, pati na rin ang pagpili ng iyong WiFi country. Hindi mo kailangang gawin ito kung gagamit ka ng ethernet cable. Siguraduhin na ang network na iyong kinokonekta ay pareho sa network ng iyong computer.

    1. I-check ang **Set locale settings** check box, at i-set ang iyong bansa at timezone.

    1. Piliin ang **SAVE** button.

1. Piliin ang **WRITE** button upang isulat ang OS sa SD card. Kung gumagamit ka ng macOS, hihilingin sa iyo na ilagay ang iyong password dahil ang underlying tool na nagsusulat ng disk images ay nangangailangan ng privileged access.

Ang OS ay isusulat sa SD card, at kapag natapos na, ang card ay awtomatikong aalisin ng OS, at ikaw ay aabisuhan. Alisin ang SD card mula sa iyong computer, ipasok ito sa Pi, i-power up ang Pi at maghintay ng mga 2 minuto para ito ay maayos na mag-boot.

#### Kumonekta sa Pi

Ang susunod na hakbang ay ang pag-access sa Pi nang remote. Maaari mo itong gawin gamit ang `ssh`, na available sa macOS, Linux, at mga kamakailang bersyon ng Windows.

##### Gawain - kumonekta sa Pi

Mag-access sa Pi nang remote.

1. Buksan ang Terminal o Command Prompt, at ilagay ang sumusunod na command upang kumonekta sa Pi:

    ```sh
    ssh pi@raspberrypi.local
    ```

    Kung ikaw ay nasa Windows gamit ang mas lumang bersyon na walang `ssh` na naka-install, maaari mong gamitin ang OpenSSH. Makikita mo ang mga tagubilin sa pag-install sa [OpenSSH installation documentation](https://docs.microsoft.com//windows-server/administration/openssh/openssh_install_firstuse?WT.mc_id=academic-17441-jabenn).

1. Dapat itong kumonekta sa iyong Pi at hilingin ang password.

    Ang kakayahang mahanap ang mga computer sa iyong network gamit ang `<hostname>.local` ay isang medyo kamakailang karagdagan sa Linux at Windows. Kung ikaw ay gumagamit ng Linux o Windows at nakakaranas ng anumang error tungkol sa Hostname na hindi natagpuan, kakailanganin mong mag-install ng karagdagang software upang paganahin ang ZeroConf networking (tinatawag din ng Apple bilang Bonjour):

    1. Kung ikaw ay gumagamit ng Linux, i-install ang Avahi gamit ang sumusunod na command:

        ```sh
        sudo apt-get install avahi-daemon
        ```

    1. Kung ikaw ay gumagamit ng Windows, ang pinakamadaling paraan upang paganahin ang ZeroConf ay ang pag-install ng [Bonjour Print Services for Windows](http://support.apple.com/kb/DL999). Maaari ka ring mag-install ng [iTunes for Windows](https://www.apple.com/itunes/download/) upang makakuha ng mas bagong bersyon ng utility (na hindi available nang standalone).

    > 💁 Kung hindi ka makakonekta gamit ang `raspberrypi.local`, maaari mong gamitin ang IP address ng iyong Pi. Tingnan ang [Raspberry Pi IP address documentation](https://www.raspberrypi.org/documentation/remote-access/ip-address.md) para sa mga tagubilin sa iba't ibang paraan upang makuha ang IP address.

1. Ilagay ang password na iyong itinakda sa Raspberry Pi Imager Advanced Options.

#### I-configure ang software sa Pi

Kapag nakakonekta ka na sa Pi, kailangan mong tiyakin na ang OS ay up-to-date, at mag-install ng iba't ibang library at tool na nakikipag-ugnayan sa Grove hardware.

##### Gawain - i-configure ang software sa Pi

I-configure ang naka-install na Pi software at i-install ang Grove libraries.

1. Mula sa iyong `ssh` session, patakbuhin ang sumusunod na command upang i-update at pagkatapos ay i-reboot ang Pi:

    ```sh
    sudo apt update && sudo apt full-upgrade --yes && sudo reboot
    ```

    Ang Pi ay maa-update at magre-reboot. Ang `ssh` session ay magtatapos kapag nag-reboot ang Pi, kaya maghintay ng mga 30 segundo pagkatapos ay muling kumonekta.

1. Mula sa muling nakakonektang `ssh` session, patakbuhin ang mga sumusunod na command upang i-install ang lahat ng kinakailangang library para sa Grove hardware:

    ```sh
    sudo apt install git python3-dev python3-pip --yes

    git clone https://github.com/Seeed-Studio/grove.py
    cd grove.py
    sudo pip3 install .

    sudo raspi-config nonint do_i2c 0
    ```

    Nagsisimula ito sa pag-install ng Git, kasama ang Pip para mag-install ng mga Python package.

    Isa sa mga makapangyarihang tampok ng Python ay ang kakayahang mag-install ng [Pip packages](https://pypi.org) - ito ay mga package ng code na isinulat ng ibang tao at inilathala sa Internet. Maaari kang mag-install ng Pip package sa iyong computer gamit ang isang command, pagkatapos ay gamitin ang package na iyon sa iyong code.

    Ang Seeed Grove Python packages ay kailangang i-install mula sa source. Ang mga command na ito ay magka-clone ng repo na naglalaman ng source code para sa package na ito, pagkatapos ay i-install ito nang lokal.

    > 💁 Sa default, kapag nag-install ka ng package, ito ay magagamit saanman sa iyong computer, at maaari itong magdulot ng mga problema sa mga bersyon ng package - tulad ng isang application na umaasa sa isang bersyon ng package na nasisira kapag nag-install ka ng bagong bersyon para sa ibang application. Upang maiwasan ang problemang ito, maaari kang gumamit ng [Python virtual environment](https://docs.python.org/3/library/venv.html), na mahalagang isang kopya ng Python sa isang dedikadong folder, at kapag nag-install ka ng Pip packages, sila ay mai-install lamang sa folder na iyon. Hindi ka gagamit ng virtual environments kapag ginagamit ang iyong Pi. Ang Grove install script ay nag-i-install ng Grove Python packages globally, kaya kung gagamit ka ng virtual environment, kailangan mong mag-set up ng virtual environment pagkatapos ay manu-manong i-reinstall ang Grove packages sa loob ng environment na iyon. Mas madali ang paggamit ng global packages, lalo na't maraming Pi developers ang nagre-reflash ng malinis na SD card para sa bawat proyekto.

    Sa wakas, pinapagana nito ang I<sup>2</sup>C interface.

1. I-reboot ang Pi sa pamamagitan ng pagpapatakbo ng sumusunod na command:

    ```sh
    sudo reboot
    ```

    Ang `ssh` session ay magtatapos kapag nag-reboot ang Pi. Hindi na kailangang muling kumonekta.

#### I-configure ang VS Code para sa remote access

Kapag na-configure na ang Pi, maaari kang kumonekta dito gamit ang Visual Studio Code (VS Code) mula sa iyong computer - ito ay isang libreng developer text editor na gagamitin mo upang magsulat ng device code sa Python.

##### Gawain - i-configure ang VS Code para sa remote access

I-install ang kinakailangang software at kumonekta nang remote sa iyong Pi.

1. I-install ang VS Code sa iyong computer sa pamamagitan ng pagsunod sa [VS Code documentation](https://code.visualstudio.com?WT.mc_id=academic-17441-jabenn).

1. Sundin ang mga tagubilin sa [VS Code Remote Development using SSH documentation](https://code.visualstudio.com/docs/remote/ssh?WT.mc_id=academic-17441-jabenn) upang i-install ang mga kinakailangang component.

1. Sundin ang parehong mga tagubilin upang ikonekta ang VS Code sa Pi.

1. Kapag nakakonekta na, sundin ang [managing extensions](https://code.visualstudio.com/docs/remote/ssh#_managing-extensions?WT.mc_id=academic-17441-jabenn) na mga tagubilin upang i-install ang [Pylance extension](https://marketplace.visualstudio.com/items?WT.mc_id=academic-17441-jabenn&itemName=ms-python.vscode-pylance) nang remote sa Pi.

## Hello world
Karaniwan kapag nagsisimula sa isang bagong programming language o teknolohiya, gumagawa ng isang 'Hello World' na application - isang maliit na application na nagpapakita ng teksto tulad ng `"Hello World"` upang ipakita na tama ang pagkaka-configure ng lahat ng tools.

Ang Hello World app para sa Pi ay titiyakin na tama ang pagkaka-install ng Python at Visual Studio Code.

Ang app na ito ay ilalagay sa isang folder na tinatawag na `nightlight`, at gagamitin muli gamit ang iba't ibang code sa mga susunod na bahagi ng gawaing ito upang mabuo ang nightlight application.

### Gawain - hello world

Gumawa ng Hello World app.

1. Buksan ang VS Code, alinman direkta sa Pi, o sa iyong computer at konektado sa Pi gamit ang Remote SSH extension.

1. Buksan ang VS Code Terminal sa pamamagitan ng pagpili sa *Terminal -> New Terminal*, o pindutin ang `` CTRL+` ``. Bubuksan nito ang terminal sa home directory ng user na `pi`.

1. Patakbuhin ang mga sumusunod na command upang gumawa ng direktoryo para sa iyong code, at gumawa ng Python file na tinatawag na `app.py` sa loob ng direktoryong iyon:

    ```sh
    mkdir nightlight
    cd nightlight
    touch app.py
    ```

1. Buksan ang folder na ito sa VS Code sa pamamagitan ng pagpili sa *File -> Open...* at piliin ang *nightlight* na folder, pagkatapos ay piliin ang **OK**.

    ![Ang VS Code open dialog na nagpapakita ng nightlight folder](../../../../../translated_images/tl/vscode-open-nightlight-remote.d3d2a4011e30d535.webp)

1. Buksan ang file na `app.py` mula sa VS Code explorer at idagdag ang sumusunod na code:

    ```python
    print('Hello World!')
    ```

    Ang `print` function ay nagpapakita ng anumang ipinasok dito sa console.

1. Mula sa VS Code Terminal, patakbuhin ang sumusunod upang patakbuhin ang iyong Python app:

    ```sh
    python app.py
    ```

    > 💁 Maaaring kailanganin mong tahasang tawagin ang `python3` upang patakbuhin ang code na ito kung mayroon kang naka-install na Python 2 bukod sa Python 3 (ang pinakabagong bersyon). Kung naka-install ang Python 2, ang pagtawag sa `python` ay gagamit ng Python 2 sa halip na Python 3. Sa default, ang pinakabagong mga bersyon ng Raspberry Pi OS ay may naka-install na Python 3 lamang.

    Ang sumusunod na output ay lalabas sa terminal:

    ```output
    pi@raspberrypi:~/nightlight $ python3 app.py
    Hello World!
    ```

> 💁 Maaari mong makita ang code na ito sa [code/pi](../../../../../1-getting-started/lessons/1-introduction-to-iot/code/pi) na folder.

😀 Tagumpay ang iyong 'Hello World' na programa!

---

**Paunawa**:  
Ang dokumentong ito ay isinalin gamit ang AI translation service na [Co-op Translator](https://github.com/Azure/co-op-translator). Bagama't sinisikap naming maging tumpak, tandaan na ang mga awtomatikong pagsasalin ay maaaring maglaman ng mga pagkakamali o hindi pagkakatugma. Ang orihinal na dokumento sa kanyang katutubong wika ang dapat ituring na opisyal na pinagmulan. Para sa mahalagang impormasyon, inirerekomenda ang propesyonal na pagsasalin ng tao. Hindi kami mananagot sa anumang hindi pagkakaunawaan o maling interpretasyon na maaaring magmula sa paggamit ng pagsasaling ito.