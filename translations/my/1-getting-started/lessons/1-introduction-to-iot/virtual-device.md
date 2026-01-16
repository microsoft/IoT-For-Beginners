<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "52b4de6144b2efdced7797a5339d6035",
  "translation_date": "2025-08-28T17:18:12+00:00",
  "source_file": "1-getting-started/lessons/1-introduction-to-iot/virtual-device.md",
  "language_code": "my"
}
-->
# အတူတူတည်ဆောက်ထားသော single-board computer

IoT စက်ပစ္စည်းများ၊ sensor များနှင့် actuator များကို ဝယ်ယူရန်မလိုအပ်ဘဲ၊ သင်၏ကွန်ပျူတာကို အသုံးပြု၍ IoT hardware ကို simulation လုပ်နိုင်ပါသည်။ [CounterFit project](https://github.com/CounterFit-IoT/CounterFit) သည် sensor များနှင့် actuator များကဲ့သို့သော IoT hardware ကို simulation လုပ်နိုင်သော app ကို locally အလုပ်လုပ်စေပြီး၊ sensor များနှင့် actuator များကို local Python code မှတဆင့် access လုပ်နိုင်စေသည်။ ဒီ code သည် physical hardware အသုံးပြုသော Raspberry Pi ပေါ်တွင်ရေးသားသည့် code ကဲ့သို့ပင်ဖြစ်သည်။

## Setup

CounterFit ကို အသုံးပြုရန် သင်၏ကွန်ပျူတာတွင် အခမဲ့ software များကို install လုပ်ရန်လိုအပ်ပါသည်။

### Task

လိုအပ်သော software များကို install လုပ်ပါ။

1. Python ကို install လုပ်ပါ။ Python ၏နောက်ဆုံး version ကို install လုပ်ရန် [Python downloads page](https://www.python.org/downloads/) ကို ရှာဖွေပါ။

1. Visual Studio Code (VS Code) ကို install လုပ်ပါ။ Python ဖြင့် virtual device code ရေးရန် သင်အသုံးပြုမည့် editor ဖြစ်သည်။ VS Code ကို install လုပ်ရန် [VS Code documentation](https://code.visualstudio.com?WT.mc_id=academic-17441-jabenn) ကို ရှာဖွေပါ။

    > 💁 သင်နှစ်သက်သော Python IDE သို့မဟုတ် editor ကို lessons များတွင် အသုံးပြုနိုင်ပါသည်။ သို့သော် lessons များတွင် VS Code ကို အသုံးပြုခြင်းအပေါ် အညွှန်းများပေးထားပါသည်။

1. VS Code Pylance extension ကို install လုပ်ပါ။ Python language support ပေးသော VS Code extension ဖြစ်သည်။ VS Code တွင် extension ကို install လုပ်ရန် [Pylance extension documentation](https://marketplace.visualstudio.com/items?WT.mc_id=academic-17441-jabenn&itemName=ms-python.vscode-pylance) ကို ရှာဖွေပါ။

CounterFit app ကို install လုပ်ရန်နှင့် configure လုပ်ရန်အညွှန်းများကို assignment instructions တွင် သတ်မှတ်ထားသောအချိန်တွင်ပေးပါမည်။ ဒါဟာ project တစ်ခုချင်းစီအပေါ်မှာ install လုပ်ရမည့်အရာဖြစ်သည်။

## Hello world

Programming language သို့မဟုတ် technology အသစ်တစ်ခုကို စတင်အသုံးပြုသောအခါ "Hello World" application တစ်ခုကို ဖန်တီးခြင်းသည် ရိုးရာဖြစ်သည်။ ဒီ application သည် `"Hello World"` ကဲ့သို့သောစာသားကို output ပြုလုပ်ပြီး tools များအားလုံးကို မှန်ကန်စွာ configure လုပ်ထားကြောင်းပြသသည်။

Virtual IoT hardware အတွက် Hello World app သည် Python နှင့် Visual Studio Code ကို မှန်ကန်စွာ install လုပ်ထားကြောင်းသေချာစေပါမည်။ ဒါဟာ CounterFit ကို virtual IoT sensor များနှင့် actuator များအတွက် connect လုပ်ပါမည်။ Hardware များကို အသုံးမပြုပါဘဲ connect လုပ်ပြီး အားလုံးအလုပ်လုပ်နေကြောင်း သက်သေပြပါမည်။

ဒီ app ကို `nightlight` ဟုခေါ်သော folder တစ်ခုတွင်ရှိမည်ဖြစ်ပြီး၊ assignment ၏ နောက်ပိုင်းအပိုင်းများတွင် nightlight application ကို တည်ဆောက်ရန်အတွက် ကွဲပြားသော code များနှင့်အတူ ပြန်လည်အသုံးပြုမည်ဖြစ်သည်။

### Python virtual environment ကို configure လုပ်ပါ

Python ၏ အားသာချက်တစ်ခုမှာ [Pip packages](https://pypi.org) ကို install လုပ်နိုင်ခြင်းဖြစ်သည်။ Pip packages သည် အခြားသူများရေးသားပြီး အင်တာနက်ပေါ်တွင် publish လုပ်ထားသော code packages ဖြစ်သည်။ Command တစ်ခုဖြင့် Pip package ကို install လုပ်ပြီး သင်၏ code တွင် package ကို အသုံးပြုနိုင်ပါသည်။ CounterFit နှင့် ဆက်သွယ်ရန် package တစ်ခုကို install လုပ်ရန် သင် Pip ကို အသုံးပြုမည်ဖြစ်သည်။

ပုံမှန်အားဖြင့် package ကို install လုပ်သောအခါ package သည် သင်၏ကွန်ပျူတာတွင် အားလုံးအတွက်ရရှိနိုင်ပါသည်။ ဒါဟာ package version များနှင့်ပတ်သက်သောပြဿနာများကို ဖြစ်စေနိုင်သည်။ ဥပမာ - application တစ်ခုသည် package version တစ်ခုကို မူတည်ပြီး၊ application တစ်ခုအတွက် version အသစ်ကို install လုပ်သောအခါ ပြဿနာဖြစ်စေနိုင်သည်။ ဒီပြဿနာကို ဖြေရှင်းရန် [Python virtual environment](https://docs.python.org/3/library/venv.html) ကို အသုံးပြုနိုင်သည်။ ဒါဟာ Python ၏ copy တစ်ခုကို dedicated folder တစ်ခုတွင်ထားပြီး၊ Pip packages များကို install လုပ်သောအခါ folder ထဲတွင်သာ install လုပ်ပါမည်။

> 💁 သင် Raspberry Pi ကို အသုံးပြုနေပါက virtual environment ကို setup မလုပ်ပါဘဲ global packages ကို အသုံးပြုနေပါသည်။ Grove packages များကို installer script မှတဆင့် global အနေဖြင့် install လုပ်ထားသည်။

#### Task - Python virtual environment ကို configure လုပ်ပါ

Python virtual environment ကို configure လုပ်ပြီး CounterFit အတွက် Pip packages များကို install လုပ်ပါ။

1. Terminal သို့မဟုတ် command line မှာ အောက်ပါ command များကို run လုပ်ပြီး directory အသစ်တစ်ခုကို ဖန်တီးပြီး navigate လုပ်ပါ:

    ```sh
    mkdir nightlight
    cd nightlight
    ```

1. `.venv` folder တွင် virtual environment ကို ဖန်တီးရန် အောက်ပါ command ကို run လုပ်ပါ:

    ```sh
    python3 -m venv .venv
    ```

    > 💁 Python 2 ကို install လုပ်ထားပြီး Python 3 (နောက်ဆုံး version) ကို install လုပ်ထားပါက `python3` ကို explicitly call လုပ်ရန်လိုအပ်ပါသည်။ Python 2 ကို install လုပ်ထားပါက `python` ကို call လုပ်သောအခါ Python 2 ကို အသုံးပြုမည်ဖြစ်သည်။

1. Virtual environment ကို activate လုပ်ပါ:

    * Windows တွင်:
        * Command Prompt သို့မဟုတ် Windows Terminal မှ Command Prompt ကို အသုံးပြုပါက အောက်ပါ command ကို run လုပ်ပါ:

            ```cmd
            .venv\Scripts\activate.bat
            ```

        * PowerShell ကို အသုံးပြုပါက အောက်ပါ command ကို run လုပ်ပါ:

            ```powershell
            .\.venv\Scripts\Activate.ps1
            ```

            > Scripts များကို run လုပ်ခြင်းကို system တွင် disable လုပ်ထားသည်ဟု error message ရရှိပါက script များကို run လုပ်နိုင်ရန် execution policy ကို set လုပ်ရန်လိုအပ်ပါသည်။ PowerShell ကို administrator အနေဖြင့် launch လုပ်ပြီး အောက်ပါ command ကို run လုပ်ပါ:

            ```powershell
            Set-ExecutionPolicy -ExecutionPolicy Unrestricted
            ```

            Confirm ပြုလုပ်ရန် `Y` ကို ရိုက်ထည့်ပါ။ PowerShell ကို ပြန်လည် launch လုပ်ပြီး ထပ်မံကြိုးစားပါ။

            အနာဂတ်တွင်လိုအပ်ပါက execution policy ကို ပြန်လည် reset လုပ်နိုင်ပါသည်။ [Execution Policies page on Microsoft Docs](https://docs.microsoft.com/powershell/module/microsoft.powershell.core/about/about_execution_policies?WT.mc_id=academic-17441-jabenn) တွင်ပိုမိုသိရှိနိုင်ပါသည်။

    * macOS သို့မဟုတ် Linux တွင် အောက်ပါ command ကို run လုပ်ပါ:

        ```cmd
        source ./.venv/bin/activate
        ```

    > 💁 ဒီ command များကို virtual environment ကို ဖန်တီးသောနေရာတွင် run လုပ်ပါ။ `.venv` folder ထဲသို့ navigate လုပ်ရန်မလိုအပ်ပါ။ Activate command နှင့် package များကို install လုပ်ရန် command များကို virtual environment ကို ဖန်တီးသော folder မှ run လုပ်ပါ။

1. Virtual environment ကို activate လုပ်ပြီးနောက် default `python` command သည် virtual environment ကို ဖန်တီးရန် အသုံးပြုသော Python version ကို run လုပ်ပါမည်။ Version ကို ရှာဖွေရန် အောက်ပါ command ကို run လုပ်ပါ:

    ```sh
    python --version
    ```

    Output တွင် အောက်ပါအရာများပါဝင်ရမည်:

    ```output
    (.venv) ➜  nightlight python --version
    Python 3.9.1
    ```

    > 💁 သင်၏ Python version သည် ကွဲပြားနိုင်ပါသည် - version 3.6 သို့မဟုတ် အထက်ရှိပါက အဆင်ပြေပါသည်။ မဟုတ်ပါက folder ကို delete လုပ်ပြီး Python ၏ version အသစ်ကို install လုပ်ပြီး ထပ်မံကြိုးစားပါ။

1. CounterFit အတွက် Pip packages များကို install လုပ်ရန် အောက်ပါ command များကို run လုပ်ပါ။ ဒီ packages များတွင် Grove hardware အတွက် shims များပါဝင်သည်။ ဒီ shims များသည် Grove ecosystem မှ physical sensor များနှင့် actuator များကို အသုံးပြုသကဲ့သို့ virtual IoT devices များကို programming လုပ်ရန် code ရေးသားနိုင်စေသည်။

    ```sh
    pip install CounterFit
    pip install counterfit-connection
    pip install counterfit-shims-grove
    ```

    ဒီ Pip packages များသည် virtual environment တွင်သာ install လုပ်ထားပြီး အပြင်မှာရရှိနိုင်မည်မဟုတ်ပါ။

### Code ကိုရေးပါ

Python virtual environment ကို ပြင်ဆင်ပြီးနောက် 'Hello World' application အတွက် code ကိုရေးနိုင်ပါသည်။

#### Task - Code ကိုရေးပါ

Console တွင် `"Hello World"` ကို print လုပ်သော Python application တစ်ခုကို ဖန်တီးပါ။

1. Virtual environment အတွင်း terminal သို့မဟုတ် command line မှာ အောက်ပါ command ကို run လုပ်ပြီး `app.py` ဟုခေါ်သော Python file ကို ဖန်တီးပါ:

    * Windows မှ run လုပ်ပါ:

        ```cmd
        type nul > app.py
        ```

    * macOS သို့မဟုတ် Linux မှ run လုပ်ပါ:

        ```cmd
        touch app.py
        ```

1. လက်ရှိ folder ကို VS Code တွင် open လုပ်ပါ:

    ```sh
    code .
    ```

    > 💁 macOS တွင် terminal မှာ `command not found` message ရရှိပါက VS Code ကို PATH တွင် ထည့်သွင်းထားခြင်းမရှိပါ။ PATH တွင် VS Code ကို ထည့်သွင်းရန် [Launching from the command line section of the VS Code documentation](https://code.visualstudio.com/docs/setup/mac?WT.mc_id=academic-17441-jabenn#_launching-from-the-command-line) ကို လိုက်နာပြီး command ကို ထပ်မံ run လုပ်ပါ။ Windows နှင့် Linux တွင် VS Code သည် PATH တွင် default အနေဖြင့် install လုပ်ထားသည်။

1. VS Code ကို launch လုပ်သောအခါ Python virtual environment ကို activate လုပ်ပါမည်။ Virtual environment ကို select လုပ်ထားသည်ကို အောက်ခြေ status bar တွင် တွေ့နိုင်ပါမည်:

    ![VS Code showing the selected virtual environment](../../../../../translated_images/my/vscode-virtual-env.8ba42e04c3d533cf.webp)

1. VS Code Terminal သည် VS Code စတင်လုပ်ဆောင်သောအခါ run လုပ်နေပါက virtual environment ကို activate လုပ်ထားမည်မဟုတ်ပါ။ Terminal ကို **Kill the active terminal instance** button ဖြင့် ပိတ်လိုက်ပါ:

    ![VS Code Kill the active terminal instance button](../../../../../translated_images/my/vscode-kill-terminal.1cc4de7c6f25ee08.webp)

    Terminal prompt တွင် virtual environment ၏နာမည် `.venv` ဟု prefix အနေဖြင့်ပါဝင်ပါမည်။ ဥပမာ - prompt သည် အောက်ပါအတိုင်းဖြစ်နိုင်သည်:

    ```sh
    (.venv) ➜  nightlight
    ```

    Prompt တွင် `.venv` prefix မပါရှိပါက terminal တွင် virtual environment ကို activate လုပ်ထားခြင်းမရှိပါ။

1. VS Code Terminal အသစ်ကို *Terminal -> New Terminal* ကို select လုပ်ခြင်းဖြင့် သို့မဟုတ် `` CTRL+` `` ကို နှိပ်ခြင်းဖြင့် launch လုပ်ပါ။ Terminal အသစ်သည် virtual environment ကို load လုပ်ပြီး terminal တွင် activate command ကို ပြပါမည်။ Prompt တွင် virtual environment (`.venv`) ၏နာမည်ပါဝင်ပါမည်:

    ```output
    ➜  nightlight source .venv/bin/activate
    (.venv) ➜  nightlight 
    ```

1. VS Code explorer မှ `app.py` file ကို open လုပ်ပြီး အောက်ပါ code ကို ထည့်သွင်းပါ:

    ```python
    print('Hello World!')
    ```

    `print` function သည် console တွင် pass လုပ်ထားသောအရာကို print လုပ်ပါမည်။

1. VS Code terminal မှ Python app ကို run လုပ်ရန် အောက်ပါ command ကို run လုပ်ပါ:

    ```sh
    python app.py
    ```

    Output တွင် အောက်ပါအရာများပါဝင်ရမည်:

    ```output
    (.venv) ➜  nightlight python app.py 
    Hello World!
    ```

😀 သင်၏ 'Hello World' program အောင်မြင်ခဲ့ပါသည်!

### 'hardware' ကို connect လုပ်ပါ

'Hello World' ၏ ဒုတိယအဆင့်အနေဖြင့် CounterFit app ကို run လုပ်ပြီး သင်၏ code ကို connect လုပ်ပါမည်။ ဒါဟာ IoT hardware တစ်ခုကို dev kit တွင် plug လုပ်သကဲ့သို့ virtual အနေဖြင့်လုပ်ဆောင်ခြင်းဖြစ်သည်။

#### Task - 'hardware' ကို connect လုပ်ပါ

1. VS Code terminal မှ CounterFit app ကို အောက်ပါ command ဖြင့် launch လုပ်ပါ:

    ```sh
    counterfit
    ```

    App သည် run လုပ်ပြီး သင်၏ web browser တွင် open လုပ်ပါမည်:

    ![The Counter Fit app running in a browser](../../../../../translated_images/my/counterfit-first-run.433326358b669b31d0e99c3513cb01bfbb13724d162c99cdcc8f51ecf5f9c779.png)

    App သည် *Disconnected* ဟုပြထားပြီး LED သည် အပိတ်ထားသည်။

1. `app.py` file ၏ အပေါ်ပိုင်းတွင် အောက်ပါ code ကို ထည့်သွင်းပါ:

    ```python
    from counterfit_connection import CounterFitConnection
    CounterFitConnection.init('127.0.0.1', 5000)
    ```

    ဒီ code သည် `counterfit_connection` module မှ `CounterFitConnection` class ကို import လုပ်ပြီး၊ `127.0.0.1` (သင်၏ local computer ကို access လုပ်ရန်အမြဲအသုံးပြုနိုင်သော IP address) တွင် port 5000 ကို အသုံးပြု၍ CounterFit app ကို initialize လုပ်ပါမည်။

    > 💁 Port 5000 တွင် အခြား app များ run လုပ်နေပါက code တွင် port ကို update လုပ်ပြီး `CounterFit --port <port_number>` command ကို run လုပ်ပါ။ `<port_number>` ကို သင်အသုံးပြုလိုသော port ဖြင့် အစားထိုးပါ။

1. VS Code terminal အသစ်ကို **Create a new integrated terminal** button ကို select လုပ်ခြင်းဖြင့် launch လုပ်ပါ။ ဒါဟာ လက်ရှိ terminal တွင် CounterFit app run လုပ်နေသောကြောင့်ဖြစ်သည်။

    ![VS Code Create a new integrated terminal button](../../../../../translated_images/my/vscode-new-terminal.77db8fc0f9cd3182.webp)

1. Terminal အသစ်တွင် `app.py` file ကို အရင်ကအတိုင်း run လုပ်ပါ။ CounterFit ၏ status သည် **Connected** ဟုပြောင်းပြီး LED သည် အလင်းပေးပါမည်။

    ![Counter Fit showing as connected](../../../../../translated_images/my/counterfit-connected.ed30b46d8f79b0921f3fc70be10366e596a89dca3f80c2224a9d9fc98fccf884.png)

> 💁 ဒီ code ကို [code/virtual-device](../../../../../1-getting-started/lessons/1-introduction-to-iot/code/virtual-device) folder တွင် ရှာနိုင်ပါသည်။

😀 သင်၏ hardware နှင့် connection အောင်မြင်ခဲ့ပါသည်!

---

**အကြောင်းကြားချက်**:  
ဤစာရွက်စာတမ်းကို AI ဘာသာပြန်ဝန်ဆောင်မှု [Co-op Translator](https://github.com/Azure/co-op-translator) ကို အသုံးပြု၍ ဘာသာပြန်ထားပါသည်။ ကျွန်ုပ်တို့သည် တိကျမှုအတွက် ကြိုးစားနေသော်လည်း၊ အလိုအလျောက် ဘာသာပြန်မှုများတွင် အမှားများ သို့မဟုတ် မတိကျမှုများ ပါဝင်နိုင်သည်ကို သတိပြုပါ။ မူရင်းဘာသာစကားဖြင့် ရေးသားထားသော စာရွက်စာတမ်းကို အာဏာရှိသော ရင်းမြစ်အဖြစ် သတ်မှတ်သင့်ပါသည်။ အရေးကြီးသော အချက်အလက်များအတွက် လူ့ဘာသာပြန်ပညာရှင်များမှ ပရော်ဖက်ရှင်နယ် ဘာသာပြန်မှုကို အကြံပြုပါသည်။ ဤဘာသာပြန်မှုကို အသုံးပြုခြင်းမှ ဖြစ်ပေါ်လာသော အလွဲအမှားများ သို့မဟုတ် အနားလွဲမှုများအတွက် ကျွန်ုပ်တို့သည် တာဝန်မယူပါ။