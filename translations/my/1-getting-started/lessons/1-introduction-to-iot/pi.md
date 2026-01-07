<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "8ff0d0a1d29832bb896b9c103b69a452",
  "translation_date": "2025-08-28T17:19:41+00:00",
  "source_file": "1-getting-started/lessons/1-introduction-to-iot/pi.md",
  "language_code": "my"
}
-->
# Raspberry Pi

[Raspberry Pi](https://raspberrypi.org) သည် single-board computer တစ်ခုဖြစ်သည်။ သင်သည် sensor များနှင့် actuator များကို device များနှင့် ecosystem များစွာကို အသုံးပြု၍ ထည့်သွင်းနိုင်ပြီး၊ ဤသင်ခန်းစာများအတွက် [Grove](https://www.seeedstudio.com/category/Grove-c-1003.html) ဟုခေါ်သော hardware ecosystem ကို အသုံးပြုမည်ဖြစ်သည်။ သင်၏ Pi ကို Python ဖြင့် code ရေးပြီး Grove sensor များကို access ပြုလုပ်နိုင်ပါသည်။

![A Raspberry Pi 4](../../../../../translated_images/raspberry-pi-4.fd4590d308c3d456.my.jpg)

## Setup

Raspberry Pi ကို သင်၏ IoT hardware အဖြစ် အသုံးပြုမည်ဆိုပါက၊ သင်တွင် ရွေးချယ်စရာနှစ်ခုရှိသည် - ဤသင်ခန်းစာများအားလုံးကို Pi ပေါ်တွင် တိုက်ရိုက် code ရေးနိုင်သည်၊ သို့မဟုတ် 'headless' Pi ကို remote ဖြင့် ချိတ်ဆက်ပြီး သင်၏ computer မှ code ရေးနိုင်သည်။

စတင်ရန်မတိုင်မီ၊ Grove Base Hat ကို သင်၏ Pi နှင့် ချိတ်ဆက်ရန် လိုအပ်ပါသည်။

### Task - setup

Grove base hat ကို သင်၏ Pi တွင် တပ်ဆင်ပြီး Pi ကို configure လုပ်ပါ

1. Grove base hat ကို သင်၏ Pi နှင့် ချိတ်ဆက်ပါ။ Hat ပေါ်ရှိ socket သည် Pi ရှိ GPIO pin အားလုံးကို အပြည့်အဝ fitting ဖြစ်ပြီး base ပေါ်တွင် ခိုင်ခိုင်မာမာ ထိုင်နေပါသည်။ ၎င်းသည် Pi ကို ဖုံးအုပ်ထားသည်။

    ![Fitting the grove hat](../../../../../images/pi-grove-hat-fitting.gif)

1. သင်၏ Pi ကို program ရေးရန် ရွေးချယ်ပြီး အောက်ပါ အပိုင်းသို့ သွားပါ:

    * [Work directly on your Pi](../../../../../1-getting-started/lessons/1-introduction-to-iot)
    * [Remote access to code the Pi](../../../../../1-getting-started/lessons/1-introduction-to-iot)

### Work directly on your Pi

သင်သည် Pi ပေါ်တွင် တိုက်ရိုက် အလုပ်လုပ်လိုပါက၊ Raspberry Pi OS ၏ desktop version ကို အသုံးပြု၍ လိုအပ်သော tool များအားလုံးကို install လုပ်နိုင်သည်။

#### Task - work directly on your Pi

Development အတွက် သင်၏ Pi ကို setup လုပ်ပါ။

1. [Raspberry Pi setup guide](https://projects.raspberrypi.org/en/projects/raspberry-pi-setting-up) တွင်ပါရှိသော လမ်းညွှန်ချက်များကို လိုက်နာပြီး သင်၏ Pi ကို setup လုပ်ပါ၊ keyboard/mouse/monitor နှင့် ချိတ်ဆက်ပါ၊ WiFi သို့မဟုတ် ethernet network နှင့် ချိတ်ဆက်ပါ၊ software ကို update လုပ်ပါ။

Pi ကို Grove sensor များနှင့် actuator များဖြင့် program ရေးရန် device code ရေးရန် editor တစ်ခုနှင့် Grove hardware နှင့် အပြန်အလှန်လုပ်ဆောင်နိုင်သော library များနှင့် tool များကို install လုပ်ရန် လိုအပ်ပါသည်။

1. သင်၏ Pi ကို reboot ပြုလုပ်ပြီးနောက်၊ Terminal ကို launch လုပ်ပါ။ **Terminal** icon ကို အပေါ် menu bar တွင် click လုပ်ပါ၊ သို့မဟုတ် *Menu -> Accessories -> Terminal* ကို ရွေးပါ။

1. OS နှင့် install လုပ်ထားသော software ကို up-to-date ဖြစ်စေရန် အောက်ပါ command ကို run လုပ်ပါ:

    ```sh
    sudo apt update && sudo apt full-upgrade --yes
    ```

1. Grove hardware အတွက် လိုအပ်သော library များအား install လုပ်ရန် အောက်ပါ command များကို run လုပ်ပါ:

    ```sh
    sudo apt install git python3-dev python3-pip --yes

    git clone https://github.com/Seeed-Studio/grove.py
    cd grove.py
    sudo pip3 install .

    sudo raspi-config nonint do_i2c 0
    ```

    ဤသည်မှာ Git ကို install လုပ်ခြင်းဖြင့် စတင်ပြီး Python package များကို install လုပ်ရန် Pip ကို install လုပ်ပါသည်။

    Python ၏ အားသာချက်တစ်ခုမှာ [Pip packages](https://pypi.org) ကို install လုပ်နိုင်ခြင်းဖြစ်သည် - ၎င်းသည် အခြားသူများရေးသားပြီး အင်တာနက်တွင် publish လုပ်ထားသော code package များဖြစ်သည်။ သင်သည် command တစ်ခုဖြင့် Pip package ကို သင်၏ computer ပေါ်တွင် install လုပ်ပြီး သင်၏ code တွင် အသုံးပြုနိုင်ပါသည်။

    Seeed Grove Python package များကို source မှ install လုပ်ရန် လိုအပ်သည်။ ဤ command များသည် ဤ package ၏ source code ပါဝင်သော repo ကို clone လုပ်ပြီး local တွင် install လုပ်ပါသည်။

    > 💁 Package တစ်ခုကို install လုပ်သောအခါ၊ ၎င်းသည် သင်၏ computer ပေါ်ရှိနေရာအားလုံးတွင် အသုံးပြုနိုင်သည်။ သို့သော် package version များနှင့် ပတ်သက်သော ပြဿနာများ ဖြစ်ပေါ်နိုင်သည် - ဥပမာ application တစ်ခုသည် package version တစ်ခုကို မူတည်ပြီး application တစ်ခုအတွက် version အသစ် install လုပ်သောအခါ ပြဿနာဖြစ်ပေါ်နိုင်သည်။ ဤပြဿနာကို ဖြေရှင်းရန် [Python virtual environment](https://docs.python.org/3/library/venv.html) ကို အသုံးပြုနိုင်သည်။ ၎င်းသည် Python ၏ copy တစ်ခုကို dedicated folder တွင်ထားပြီး Pip package များကို folder ထဲတွင်သာ install လုပ်သည်။ သင်၏ Pi ကို အသုံးပြုသောအခါ virtual environment များကို အသုံးမပြုပါ။ Grove install script သည် Grove Python package များကို global အဖြစ် install လုပ်သည်၊ ထို့ကြောင့် virtual environment ကို setup လုပ်ပြီး Grove package များကို ထို environment ထဲတွင် manually ပြန် install လုပ်ရန် လိုအပ်ပါသည်။ Global package များကို အသုံးပြုခြင်းသည် ပိုမိုလွယ်ကူသည်၊ အထူးသဖြင့် Pi developer များသည် project တစ်ခုစီအတွက် SD card ကို clean ပြန် flash လုပ်လေ့ရှိသည်။

    နောက်ဆုံးတွင်၊ I<sup>2</sup>C interface ကို enable လုပ်ပါသည်။

1. Menu ကို အသုံးပြု၍ သို့မဟုတ် Terminal တွင် အောက်ပါ command ကို run လုပ်၍ Pi ကို reboot ပြုလုပ်ပါ:

    ```sh
    sudo reboot
    ```

1. Pi ကို reboot ပြုလုပ်ပြီးနောက်၊ Terminal ကို ပြန်လည် launch လုပ်ပြီး Python language support ဖြင့် device code ရေးရန် အသုံးပြုမည့် [Visual Studio Code (VS Code)](https://code.visualstudio.com?WT.mc_id=academic-17441-jabenn) ကို install လုပ်ရန် အောက်ပါ command ကို run လုပ်ပါ:

    ```sh
    sudo apt install code
    ```

    Install ပြီးပါက၊ VS Code သည် အပေါ် menu မှ အသုံးပြုနိုင်ပါသည်။

    > 💁 သင်သည် Python IDE သို့မဟုတ် editor တစ်ခုကို သင်နှစ်သက်သော tool အဖြစ် အသုံးပြုနိုင်ပါသည်၊ သို့သော် ဤသင်ခန်းစာများသည် VS Code ကို အသုံးပြုခြင်းအပေါ် အခြေခံထားသော လမ်းညွှန်ချက်များပေးမည်ဖြစ်သည်။

1. Pylance ကို install လုပ်ပါ။ ၎င်းသည် Python language support ပေးသော VS Code အတွက် extension တစ်ခုဖြစ်သည်။ VS Code တွင် extension ကို install လုပ်ရန် [Pylance extension documentation](https://marketplace.visualstudio.com/items?WT.mc_id=academic-17441-jabenn&itemName=ms-python.vscode-pylance) ကို ရည်ညွှန်းပါ။

### Remote access to code the Pi

Pi ပေါ်တွင် တိုက်ရိုက် code ရေးခြင်းမဟုတ်ဘဲ၊ ၎င်းကို 'headless' အဖြစ် run လုပ်နိုင်ပြီး keyboard/mouse/monitor မပါဘဲ သင်၏ computer မှ configure လုပ်ပြီး code ရေးနိုင်သည်။

#### Set up the Pi OS

Remote ဖြင့် code ရေးရန် Pi OS ကို SD Card ပေါ်တွင် install လုပ်ရန် လိုအပ်သည်။

##### Task - set up the Pi OS

Headless Pi OS ကို setup လုပ်ပါ။

1. **Raspberry Pi Imager** ကို [Raspberry Pi OS software page](https://www.raspberrypi.org/software/) မှ download လုပ်ပြီး install လုပ်ပါ

1. SD card ကို သင်၏ computer တွင် ထည့်ပါ၊ adapter လိုအပ်ပါက အသုံးပြုပါ

1. Raspberry Pi Imager ကို launch လုပ်ပါ

1. Raspberry Pi Imager မှ **CHOOSE OS** button ကို ရွေးပါ၊ *Raspberry Pi OS (Other)* ကို ရွေးပြီး *Raspberry Pi OS Lite (32-bit)* ကို ရွေးပါ

    ![The Raspberry Pi Imager with Raspberry Pi OS Lite selected](../../../../../translated_images/raspberry-pi-imager.24aedeab9e233d84.my.png)

    > 💁 Raspberry Pi OS Lite သည် desktop UI သို့မဟုတ် UI based tool မပါသော Raspberry Pi OS version ဖြစ်သည်။ ၎င်းသည် headless Pi အတွက် မလိုအပ်သော UI များကို ဖယ်ရှားထားပြီး install size ကို သေးငယ်စေပြီး boot up time ကို မြန်စေသည်။

1. **CHOOSE STORAGE** button ကို ရွေးပြီး သင်၏ SD card ကို ရွေးပါ

1. **Advanced Options** ကို `Ctrl+Shift+X` ကို နှိပ်၍ launch လုပ်ပါ။ ဤ options များသည် Raspberry Pi OS ကို SD card ပေါ်တွင် image လုပ်မည်မတိုင်မီ pre-configuration ပြုလုပ်ရန် ခွင့်ပြုသည်။

    1. **Enable SSH** check box ကို check လုပ်ပြီး `pi` user အတွက် password တစ်ခုကို သတ်မှတ်ပါ။ ဤသည်မှာ Pi ကို later တွင် log in ပြုလုပ်ရန် သင်အသုံးပြုမည့် password ဖြစ်သည်။

    1. သင်သည် Pi ကို WiFi ဖြင့် ချိတ်ဆက်ရန် စီစဉ်ပါက **Configure WiFi** check box ကို check လုပ်ပြီး သင်၏ WiFi SSID နှင့် password ကို ထည့်သွင်းပါ၊ သင်၏ WiFi country ကို ရွေးပါ။ သင်သည် ethernet cable ကို အသုံးပြုမည်ဆိုပါက ဤအချက်များကို မလုပ်ရပါ။ သင်၏ computer ရှိ network နှင့် တူညီသော network ကို ချိတ်ဆက်ထားသည်ကို သေချာပါစေ။

    1. **Set locale settings** check box ကို check လုပ်ပြီး သင်၏ country နှင့် timezone ကို သတ်မှတ်ပါ

    1. **SAVE** button ကို ရွေးပါ

1. **WRITE** button ကို ရွေး၍ OS ကို SD card ပေါ်တွင် ရေးပါ။ macOS ကို အသုံးပြုပါက disk image ရေးရန် privileged access လိုအပ်သော tool ကို အသုံးပြုရန် သင်၏ password ကို ထည့်သွင်းရန် တောင်းဆိုမည်ဖြစ်သည်။

OS ကို SD card ပေါ်တွင် ရေးပြီးပြီးနောက် SD card ကို OS မှ eject လုပ်ပြီး သတိပေးမည်။ SD card ကို သင်၏ computer မှ ဖယ်ရှားပြီး Pi ထဲသို့ ထည့်ပါ၊ Pi ကို power up လုပ်ပြီး boot ပြုလုပ်ရန် ၂ မိနစ်ခန့် စောင့်ပါ။

#### Connect to the Pi

နောက်တစ်ဆင့်မှာ Pi ကို remote access ပြုလုပ်ရန် ဖြစ်သည်။ ၎င်းကို macOS, Linux နှင့် Windows ၏ နောက်ဆုံး version များတွင် ရရှိနိုင်သော `ssh` ကို အသုံးပြု၍ ပြုလုပ်နိုင်သည်။

##### Task - connect to the Pi

Pi ကို remote access ပြုလုပ်ပါ။

1. Terminal သို့မဟုတ် Command Prompt ကို launch လုပ်ပြီး Pi ကို ချိတ်ဆက်ရန် အောက်ပါ command ကို ထည့်သွင်းပါ:

    ```sh
    ssh pi@raspberrypi.local
    ```

    သင်သည် Windows ၏ နောက်ဆုံး version မဟုတ်သော version ကို အသုံးပြုပြီး `ssh` install မရှိပါက OpenSSH ကို အသုံးပြုနိုင်သည်။ [OpenSSH installation documentation](https://docs.microsoft.com//windows-server/administration/openssh/openssh_install_firstuse?WT.mc_id=academic-17441-jabenn) တွင် installation လမ်းညွှန်ချက်များကို ရှာနိုင်သည်။

1. ဤသည် Pi နှင့် ချိတ်ဆက်ပြီး password ကို တောင်းဆိုမည်။

    `<hostname>.local` ကို သင်၏ network ပေါ်တွင် computer များကို ရှာဖွေရန် အသုံးပြုနိုင်ခြင်းသည် Linux နှင့် Windows ၏ နောက်ဆုံး version များတွင် fairly recent ဖြစ်သည်။ Linux သို့မဟုတ် Windows ကို အသုံးပြုပြီး Hostname ကို မတွေ့နိုင်သော error များရရှိပါက ZeroConf networking (Apple မှ Bonjour ဟုလည်း ခေါ်သည်) ကို enable လုပ်ရန် additional software ကို install လုပ်ရန် လိုအပ်ပါသည်:

    1. Linux ကို အသုံးပြုပါက အောက်ပါ command ကို အသုံးပြု၍ Avahi ကို install လုပ်ပါ:

        ```sh
        sudo apt-get install avahi-daemon
        ```

    1. Windows ကို အသုံးပြုပါက ZeroConf ကို enable လုပ်ရန် အလွယ်ဆုံးနည်းလမ်းမှာ [Bonjour Print Services for Windows](http://support.apple.com/kb/DL999) ကို install လုပ်ခြင်းဖြစ်သည်။ [iTunes for Windows](https://www.apple.com/itunes/download/) ကို install လုပ်၍ utility ၏ နောက်ဆုံး version ကို ရယူနိုင်သည် (standalone အနေဖြင့် ရရှိနိုင်မည်မဟုတ်ပါ)။

    > 💁 သင်သည် `raspberrypi.local` ကို အသုံးပြု၍ ချိတ်ဆက်မရပါက၊ Pi ၏ IP address ကို အသုံးပြုနိုင်သည်။ [Raspberry Pi IP address documentation](https://www.raspberrypi.org/documentation/remote-access/ip-address.md) တွင် IP address ရယူရန် နည်းလမ်းများစွာကို ရှာနိုင်သည်။

1. Raspberry Pi Imager Advanced Options တွင် သတ်မှတ်ထားသော password ကို ထည့်သွင်းပါ

#### Configure software on the Pi

Pi ကို ချိတ်ဆက်ပြီးနောက်၊ OS ကို up-to-date ဖြစ်စေရန် သေချာစွာ ပြုလုပ်ပြီး Grove hardware နှင့် အပြန်အလှန်လုပ်ဆောင်နိုင်သော library များနှင့် tool များကို install လုပ်ရန် လိုအပ်သည်။

##### Task - configure software on the Pi

Install လုပ်ထားသော Pi software ကို configure လုပ်ပြီး Grove library များကို install လုပ်ပါ။

1. သင်၏ `ssh` session မှ Pi ကို update ပြုလုပ်ပြီး reboot ပြုလုပ်ရန် အောက်ပါ command ကို run လုပ်ပါ:

    ```sh
    sudo apt update && sudo apt full-upgrade --yes && sudo reboot
    ```

    Pi ကို update ပြုလုပ်ပြီး reboot လုပ်မည်။ Pi ကို reboot ပြုလုပ်သောအခါ `ssh` session သည် အဆုံးသတ်မည်ဖြစ်သည်၊ ထို့ကြောင့် ၃၀ စက္ကန့်ခန့် စောင့်ပြီး ပြန်လည်ချိတ်ဆက်ပါ။

1. ပြန်လည်ချိတ်ဆက်ထားသော `ssh` session မှ Grove hardware အတွက် လိုအပ်သော library များအား install လုပ်ရန် အောက်ပါ command များကို run လုပ်ပါ:

    ```sh
    sudo apt install git python3-dev python3-pip --yes

    git clone https://github.com/Seeed-Studio/grove.py
    cd grove.py
    sudo pip3 install .

    sudo raspi-config nonint do_i2c 0
    ```

    ဤသည်မှာ Git ကို install လုပ်ခြင်းဖြင့် စတင်ပြီး Python package များကို install လုပ်ရန် Pip ကို install လုပ်ပါသည်။

    Python ၏ အားသာချက်တစ်ခုမှာ [Pip packages](https://pypi.org) ကို install လုပ်နိုင်ခြင်းဖြစ်သည် - ၎င်းသည် အခြားသူများရေးသားပြီး အင်တာနက်တွင် publish လုပ်ထားသော code package များဖြစ်သည်။ သင်သည် command တစ်ခုဖြင့် Pip package ကို သင်၏ computer ပေါ်တွင် install လုပ်ပြီး သင်၏ code တွင် အသုံးပြုနိုင်ပါသည်။

    Seeed Grove Python package များကို source မှ install လုပ်ရန် လိုအပ်သည်။ ဤ command များသည် ဤ package ၏ source code ပါဝင်သော repo ကို clone လုပ်ပြီး local တွင် install လုပ်ပါသည်။

    > 💁 Package တစ်ခုကို install လုပ်သောအခါ၊ ၎င်းသည် သင်၏ computer ပေါ်ရှိနေရာအားလုံးတွင် အသုံးပြုနိုင်သည်။ သို့သော် package version များနှင့် ပတ်သက်သော ပြဿနာများ ဖြစ်ပေါ်နိုင်သည် - ဥပမာ application တစ်ခုသည် package version တစ်ခုကို မူတည်ပြီး application တစ်ခုအတွက် version အသစ် install လုပ်သောအခါ ပြဿနာဖြစ်ပေါ်နိုင်သည်။ ဤပြဿနာကို ဖြေရှင်းရန် [Python virtual environment](https://docs.python.org/3/library/venv.html) ကို အသုံးပြုနိုင်သည်။ ၎င်းသည် Python ၏ copy တစ်ခုကို dedicated folder တွင်ထားပြီး Pip package များကို folder ထဲတွင်သာ install လုပ်သည်။ သင်၏ Pi ကို အသုံးပြုသောအခါ virtual environment များကို အသုံးမပြုပါ။ Grove install script သည် Grove Python package များကို global အဖြစ် install လုပ်သည်၊ ထို့ကြောင့် virtual environment ကို setup လုပ်ပြီး Grove package များကို ထို environment ထဲတွင် manually ပြန် install လုပ်ရန် လိုအပ်ပါသည်။ Global package များကို အသုံးပြုခြင်းသည် ပိုမိုလွယ်ကူသည်၊ အထူးသဖြင့် Pi developer များသည် project တစ်ခုစီအတွက် SD card ကို clean ပြန် flash လုပ်လေ့ရှိသည်။

    နောက်ဆုံးတွင်၊ I<sup>2</sup>C interface ကို enable လုပ်ပါသည်။

1. Pi ကို အောက်ပါ command ကို run လုပ်၍ reboot ပြုလုပ်ပါ:

    ```sh
    sudo reboot
    ```

    Pi ကို reboot ပြုလုပ်သောအ
အသစ်တစ်ခုသော programming language သို့မဟုတ် နည်းပညာတစ်ခုကို စတင်လေ့လာရာတွင် `"Hello World"` ဟု အမည်ရသော အသေးစား application တစ်ခုကို ဖန်တီးခြင်းသည် ရိုးရာအဖြစ်ကျင့်သုံးကြသည်။ ဤ application သည် `"Hello World"` စာသားကို output အဖြစ် ပြသပြီး သင့် tools များအားလုံးမှန်ကန်စွာ တပ်ဆင်ပြီးဖြစ်ကြောင်း သက်သေပြသည်။

Pi အတွက် Hello World app သည် Python နှင့် Visual Studio Code ကို မှန်ကန်စွာ တပ်ဆင်ထားကြောင်း သေချာစေမည်ဖြစ်သည်။

ဤ app ကို `nightlight` ဟု အမည်ရသော folder အတွင်းတွင် ထည့်သွင်းထားမည်ဖြစ်ပြီး၊ ဤအလုပ်မှာ နောက်ပိုင်းအပိုင်းများတွင် နောက်ထပ် code များဖြင့် ပြန်လည်အသုံးပြုကာ nightlight application ကို တည်ဆောက်သွားမည်ဖြစ်သည်။

### လုပ်ငန်း - hello world

Hello World app ကို ဖန်တီးပါ။

1. VS Code ကို Pi ပေါ်တွင် တိုက်ရိုက်ဖွင့်ပါ၊ သို့မဟုတ် သင့်ကွန်ပျူတာပေါ်မှ Remote SSH extension ကို အသုံးပြုကာ Pi နှင့် ချိတ်ဆက်ပြီး ဖွင့်ပါ။

1. VS Code Terminal ကို ဖွင့်ရန် *Terminal -> New Terminal* ကို ရွေးပါ၊ သို့မဟုတ် `` CTRL+` `` ကို နှိပ်ပါ။ ၎င်းသည် `pi` အသုံးပြုသူ၏ home directory တွင် ဖွင့်လှစ်မည်ဖြစ်သည်။

1. သင့် code အတွက် directory တစ်ခု ဖန်တီးရန်နှင့် ထို directory အတွင်း `app.py` ဟု အမည်ရသော Python ဖိုင်တစ်ခု ဖန်တီးရန် အောက်ပါ command များကို run ပါ။

    ```sh
    mkdir nightlight
    cd nightlight
    touch app.py
    ```

1. *File -> Open...* ကို ရွေးပြီး *nightlight* folder ကို ရွေးပါ၊ ထို့နောက် **OK** ကို နှိပ်ပါ။ 

    ![VS Code open dialog တွင် nightlight folder ကို ပြသထားသည်](../../../../../translated_images/vscode-open-nightlight-remote.d3d2a4011e30d535.my.png)

1. VS Code explorer မှ `app.py` ဖိုင်ကို ဖွင့်ပြီး အောက်ပါ code ကို ထည့်သွင်းပါ။

    ```python
    print('Hello World!')
    ```

    `print` function သည် ထည့်သွင်းထားသော အရာကို console တွင် ပြသပေးသည်။

1. VS Code Terminal မှ အောက်ပါ command ကို run ကာ သင့် Python app ကို run ပါ။

    ```sh
    python app.py
    ```

    > 💁 သင့် Pi တွင် Python 2 နှင့် Python 3 နှစ်မျိုးလုံး တပ်ဆင်ထားပါက၊ ဤ code ကို run ရန် `python3` ကို သီးသန့်ခေါ်ရန် လိုအပ်နိုင်သည်။ Python 2 တပ်ဆင်ထားပါက `python` ဟု ခေါ်သည့်အခါ Python 2 ကို အသုံးပြုမည်ဖြစ်သည်။ သို့သော်၊ နောက်ဆုံးထွက်ရှိသော Raspberry Pi OS များတွင် Python 3 သာ တပ်ဆင်ထားသည်။

    Terminal တွင် အောက်ပါ output ကို တွေ့ရမည်။

    ```output
    pi@raspberrypi:~/nightlight $ python3 app.py
    Hello World!
    ```

> 💁 ဤ code ကို [code/pi](../../../../../1-getting-started/lessons/1-introduction-to-iot/code/pi) folder တွင် ရှာနိုင်ပါသည်။

😀 သင့် 'Hello World' program အောင်မြင်စွာ ပြီးစီးခဲ့ပါပြီ!

---

**အကြောင်းကြားချက်**:  
ဤစာရွက်စာတမ်းကို AI ဘာသာပြန်ဝန်ဆောင်မှု [Co-op Translator](https://github.com/Azure/co-op-translator) ကို အသုံးပြု၍ ဘာသာပြန်ထားပါသည်။ ကျွန်ုပ်တို့သည် တိကျမှုအတွက် ကြိုးစားနေသော်လည်း၊ အလိုအလျောက် ဘာသာပြန်မှုများတွင် အမှားများ သို့မဟုတ် မတိကျမှုများ ပါဝင်နိုင်သည်ကို သတိပြုပါ။ မူရင်းဘာသာစကားဖြင့် ရေးသားထားသော စာရွက်စာတမ်းကို အာဏာရှိသော ရင်းမြစ်အဖြစ် သတ်မှတ်သင့်ပါသည်။ အရေးကြီးသော အချက်အလက်များအတွက် လူ့ဘာသာပြန်ပညာရှင်များမှ ပရော်ဖက်ရှင်နယ် ဘာသာပြန်မှုကို အကြံပြုပါသည်။ ဤဘာသာပြန်မှုကို အသုံးပြုခြင်းမှ ဖြစ်ပေါ်လာသော အလွဲအလွဲအချော်များ သို့မဟုတ် အနားလွဲမှုများအတွက် ကျွန်ုပ်တို့သည် တာဝန်မယူပါ။