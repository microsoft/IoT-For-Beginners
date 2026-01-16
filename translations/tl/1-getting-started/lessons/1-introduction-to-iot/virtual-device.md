<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "52b4de6144b2efdced7797a5339d6035",
  "translation_date": "2025-08-27T22:42:32+00:00",
  "source_file": "1-getting-started/lessons/1-introduction-to-iot/virtual-device.md",
  "language_code": "tl"
}
-->
# Virtual single-board computer

Sa halip na bumili ng IoT device kasama ang mga sensor at actuator, maaari mong gamitin ang iyong computer upang i-simulate ang IoT hardware. Ang [CounterFit project](https://github.com/CounterFit-IoT/CounterFit) ay nagbibigay-daan sa iyo na magpatakbo ng isang app nang lokal na nagsi-simulate ng IoT hardware tulad ng mga sensor at actuator, at ma-access ang mga ito mula sa lokal na Python code na isinulat sa parehong paraan tulad ng gagawin mo sa isang Raspberry Pi gamit ang pisikal na hardware.

## Setup

Upang magamit ang CounterFit, kailangan mong mag-install ng ilang libreng software sa iyong computer.

### Gawain

I-install ang kinakailangang software.

1. I-install ang Python. Tingnan ang [Python downloads page](https://www.python.org/downloads/) para sa mga tagubilin kung paano i-install ang pinakabagong bersyon ng Python.

1. I-install ang Visual Studio Code (VS Code). Ito ang editor na gagamitin mo upang magsulat ng virtual device code sa Python. Tingnan ang [VS Code documentation](https://code.visualstudio.com?WT.mc_id=academic-17441-jabenn) para sa mga tagubilin kung paano i-install ang VS Code.

    > 💁 Malaya kang gumamit ng anumang Python IDE o editor para sa mga araling ito kung mayroon kang paboritong tool, ngunit ang mga aralin ay magbibigay ng mga tagubilin batay sa paggamit ng VS Code.

1. I-install ang VS Code Pylance extension. Ito ay isang extension para sa VS Code na nagbibigay ng suporta sa Python language. Tingnan ang [Pylance extension documentation](https://marketplace.visualstudio.com/items?WT.mc_id=academic-17441-jabenn&itemName=ms-python.vscode-pylance) para sa mga tagubilin kung paano i-install ang extension na ito sa VS Code.

Ang mga tagubilin para sa pag-install at pag-configure ng CounterFit app ay ibibigay sa tamang oras sa mga tagubilin ng assignment dahil ito ay ini-install sa bawat proyekto.

## Hello world

Karaniwan kapag nagsisimula sa isang bagong programming language o teknolohiya, gumagawa ng isang 'Hello World' application - isang maliit na application na naglalabas ng text tulad ng `"Hello World"` upang ipakita na ang lahat ng mga tool ay maayos na naka-configure.

Ang Hello World app para sa virtual IoT hardware ay titiyakin na ang Python at Visual Studio Code ay maayos na na-install. Ikokonekta rin nito ang CounterFit para sa virtual IoT sensors at actuators. Hindi ito gagamit ng anumang hardware, ikokonekta lamang ito upang patunayan na gumagana ang lahat.

Ang app na ito ay ilalagay sa isang folder na tinatawag na `nightlight`, at ito ay muling gagamitin gamit ang iba't ibang code sa mga susunod na bahagi ng assignment upang bumuo ng nightlight application.

### I-configure ang Python virtual environment

Isa sa mga makapangyarihang tampok ng Python ay ang kakayahang mag-install ng [Pip packages](https://pypi.org) - mga package ng code na isinulat ng ibang tao at inilathala sa Internet. Maaari kang mag-install ng Pip package sa iyong computer gamit ang isang command, pagkatapos ay gamitin ang package na iyon sa iyong code. Gagamitin mo ang Pip upang mag-install ng isang package para makipag-usap sa CounterFit.

Sa default, kapag nag-install ka ng isang package, ito ay magagamit kahit saan sa iyong computer, at maaari itong magdulot ng mga problema sa mga bersyon ng package - tulad ng isang application na umaasa sa isang bersyon ng package na nasisira kapag nag-install ka ng bagong bersyon para sa ibang application. Upang maiwasan ang problemang ito, maaari kang gumamit ng [Python virtual environment](https://docs.python.org/3/library/venv.html), na mahalagang isang kopya ng Python sa isang dedikadong folder, at kapag nag-install ka ng Pip packages, ang mga ito ay mai-install lamang sa folder na iyon.

> 💁 Kung gumagamit ka ng Raspberry Pi, hindi ka nag-set up ng virtual environment sa device na iyon upang pamahalaan ang Pip packages, sa halip ay gumagamit ka ng global packages, dahil ang Grove packages ay naka-install nang globally ng installer script.

#### Gawain - i-configure ang Python virtual environment

I-configure ang Python virtual environment at i-install ang Pip packages para sa CounterFit.

1. Mula sa iyong terminal o command line, patakbuhin ang sumusunod sa isang lokasyon ng iyong pinili upang lumikha at mag-navigate sa isang bagong direktoryo:

    ```sh
    mkdir nightlight
    cd nightlight
    ```

1. Ngayon, patakbuhin ang sumusunod upang lumikha ng virtual environment sa `.venv` folder:

    ```sh
    python3 -m venv .venv
    ```

    > 💁 Kailangan mong tahasang tawagin ang `python3` upang lumikha ng virtual environment sakaling mayroon kang naka-install na Python 2 bukod sa Python 3 (ang pinakabagong bersyon). Kung mayroon kang naka-install na Python 2, ang pagtawag sa `python` ay gagamit ng Python 2 sa halip na Python 3.

1. I-activate ang virtual environment:

    * Sa Windows:
        * Kung gumagamit ka ng Command Prompt, o Command Prompt sa pamamagitan ng Windows Terminal, patakbuhin:

            ```cmd
            .venv\Scripts\activate.bat
            ```

        * Kung gumagamit ka ng PowerShell, patakbuhin:

            ```powershell
            .\.venv\Scripts\Activate.ps1
            ```

            > Kung makakakita ka ng error tungkol sa hindi pinapayagang pagtakbo ng mga script sa sistemang ito, kakailanganin mong paganahin ang pagtakbo ng mga script sa pamamagitan ng pagtatakda ng angkop na execution policy. Magagawa mo ito sa pamamagitan ng paglulunsad ng PowerShell bilang administrator, pagkatapos ay patakbuhin ang sumusunod na command:

            ```powershell
            Set-ExecutionPolicy -ExecutionPolicy Unrestricted
            ```

            I-type ang `Y` kapag tinanong upang kumpirmahin. Pagkatapos, i-relaunch ang PowerShell at subukang muli.

            Maaari mong i-reset ang execution policy na ito sa ibang pagkakataon kung kinakailangan. Maaari kang magbasa pa tungkol dito sa [Execution Policies page on Microsoft Docs](https://docs.microsoft.com/powershell/module/microsoft.powershell.core/about/about_execution_policies?WT.mc_id=academic-17441-jabenn).

    * Sa macOS o Linux, patakbuhin:

        ```cmd
        source ./.venv/bin/activate
        ```

    > 💁 Ang mga command na ito ay dapat patakbuhin mula sa parehong lokasyon kung saan mo pinatakbo ang command upang lumikha ng virtual environment. Hindi mo kailangang mag-navigate sa `.venv` folder, dapat mong palaging patakbuhin ang activate command at anumang mga command upang mag-install ng mga package o magpatakbo ng code mula sa folder kung saan ka naroroon nang nilikha mo ang virtual environment.

1. Kapag na-activate na ang virtual environment, ang default na `python` command ay tatakbo gamit ang bersyon ng Python na ginamit upang lumikha ng virtual environment. Patakbuhin ang sumusunod upang makuha ang bersyon:

    ```sh
    python --version
    ```

    Ang output ay dapat maglaman ng sumusunod:

    ```output
    (.venv) ➜  nightlight python --version
    Python 3.9.1
    ```

    > 💁 Maaaring iba ang bersyon ng iyong Python - hangga't ito ay bersyon 3.6 o mas mataas, ayos na. Kung hindi, tanggalin ang folder na ito, mag-install ng mas bagong bersyon ng Python, at subukang muli.

1. Patakbuhin ang sumusunod na mga command upang i-install ang Pip packages para sa CounterFit. Kasama sa mga package na ito ang pangunahing CounterFit app pati na rin ang mga shims para sa Grove hardware. Ang mga shims na ito ay nagbibigay-daan sa iyong magsulat ng code na parang nagpo-program ka gamit ang mga pisikal na sensor at actuator mula sa Grove ecosystem ngunit konektado sa virtual IoT devices.

    ```sh
    pip install CounterFit
    pip install counterfit-connection
    pip install counterfit-shims-grove
    ```

    Ang mga Pip packages na ito ay mai-install lamang sa virtual environment, at hindi magagamit sa labas nito.

### Isulat ang code

Kapag handa na ang Python virtual environment, maaari mo nang isulat ang code para sa 'Hello World' application.

#### Gawain - isulat ang code

Gumawa ng Python application upang i-print ang `"Hello World"` sa console.

1. Mula sa iyong terminal o command line, patakbuhin ang sumusunod sa loob ng virtual environment upang lumikha ng Python file na tinatawag na `app.py`:

    * Sa Windows, patakbuhin:

        ```cmd
        type nul > app.py
        ```

    * Sa macOS o Linux, patakbuhin:

        ```cmd
        touch app.py
        ```

1. Buksan ang kasalukuyang folder sa VS Code:

    ```sh
    code .
    ```

    > 💁 Kung ang iyong terminal ay nagbalik ng `command not found` sa macOS, nangangahulugan ito na ang VS Code ay hindi naidagdag sa iyong PATH. Maaari mong idagdag ang VS Code sa iyong PATH sa pamamagitan ng pagsunod sa mga tagubilin sa [Launching from the command line section of the VS Code documentation](https://code.visualstudio.com/docs/setup/mac?WT.mc_id=academic-17441-jabenn#_launching-from-the-command-line) at patakbuhin ang command pagkatapos. Ang VS Code ay awtomatikong naidagdag sa iyong PATH sa Windows at Linux.

1. Kapag nag-launch ang VS Code, i-aactivate nito ang Python virtual environment. Ang napiling virtual environment ay lilitaw sa ibabang status bar:

    ![VS Code na nagpapakita ng napiling virtual environment](../../../../../translated_images/tl/vscode-virtual-env.8ba42e04c3d533cf.webp)

1. Kung ang VS Code Terminal ay tumatakbo na kapag nag-launch ang VS Code, hindi nito maa-activate ang virtual environment dito. Ang pinakamadaling gawin ay patayin ang terminal gamit ang **Kill the active terminal instance** button:

    ![VS Code Kill the active terminal instance button](../../../../../translated_images/tl/vscode-kill-terminal.1cc4de7c6f25ee08.webp)

    Malalaman mo kung ang terminal ay may naka-activate na virtual environment dahil ang pangalan ng virtual environment ay magiging prefix sa terminal prompt. Halimbawa, maaaring ito ay:

    ```sh
    (.venv) ➜  nightlight
    ```

    Kung wala kang `.venv` bilang prefix sa prompt, ang virtual environment ay hindi naka-activate sa terminal.

1. Mag-launch ng bagong VS Code Terminal sa pamamagitan ng pagpili sa *Terminal -> New Terminal*, o sa pagpindot sa `` CTRL+` ``. Ang bagong terminal ay maglo-load ng virtual environment, at ang tawag upang i-activate ito ay lilitaw sa terminal. Ang prompt ay magkakaroon din ng pangalan ng virtual environment (`.venv`):

    ```output
    ➜  nightlight source .venv/bin/activate
    (.venv) ➜  nightlight 
    ```

1. Buksan ang `app.py` file mula sa VS Code explorer at idagdag ang sumusunod na code:

    ```python
    print('Hello World!')
    ```

    Ang `print` function ay nagpi-print ng anumang ipinasok dito sa console.

1. Mula sa VS Code terminal, patakbuhin ang sumusunod upang patakbuhin ang iyong Python app:

    ```sh
    python app.py
    ```

    Ang sumusunod ay lilitaw sa output:

    ```output
    (.venv) ➜  nightlight python app.py 
    Hello World!
    ```

😀 Tagumpay ang iyong 'Hello World' program!

### Ikonekta ang 'hardware'

Bilang pangalawang hakbang ng 'Hello World', patakbuhin mo ang CounterFit app at ikonekta ang iyong code dito. Ito ang virtual na katumbas ng pag-plug in ng ilang IoT hardware sa isang dev kit.

#### Gawain - ikonekta ang 'hardware'

1. Mula sa VS Code terminal, ilunsad ang CounterFit app gamit ang sumusunod na command:

    ```sh
    counterfit
    ```

    Ang app ay magsisimulang tumakbo at magbubukas sa iyong web browser:

    ![Ang Counter Fit app na tumatakbo sa browser](../../../../../translated_images/tl/counterfit-first-run.433326358b669b31d0e99c3513cb01bfbb13724d162c99cdcc8f51ecf5f9c779.png)

    Ito ay mamarkahan bilang *Disconnected*, na may LED sa kanang-itaas na sulok na naka-off.

1. Idagdag ang sumusunod na code sa itaas ng `app.py`:

    ```python
    from counterfit_connection import CounterFitConnection
    CounterFitConnection.init('127.0.0.1', 5000)
    ```

    Ang code na ito ay nag-i-import ng `CounterFitConnection` class mula sa `counterfit_connection` module, na galing sa `counterfit-connection` pip package na na-install mo kanina. Pagkatapos, ini-initialize nito ang koneksyon sa CounterFit app na tumatakbo sa `127.0.0.1`, na isang IP address na palaging magagamit upang ma-access ang iyong lokal na computer (madalas na tinatawag na *localhost*), sa port 5000.

    > 💁 Kung may iba kang apps na tumatakbo sa port 5000, maaari mong baguhin ito sa pamamagitan ng pag-update ng port sa code, at pagpapatakbo ng CounterFit gamit ang `CounterFit --port <port_number>`, palitan ang `<port_number>` ng port na nais mong gamitin.

1. Kakailanganin mong mag-launch ng bagong VS Code terminal sa pamamagitan ng pagpili sa **Create a new integrated terminal** button. Ito ay dahil ang CounterFit app ay tumatakbo sa kasalukuyang terminal.

    ![VS Code Create a new integrated terminal button](../../../../../translated_images/tl/vscode-new-terminal.77db8fc0f9cd3182.webp)

1. Sa bagong terminal na ito, patakbuhin ang `app.py` file tulad ng dati. Ang status ng CounterFit ay magbabago sa **Connected** at ang LED ay iilaw.

    ![Counter Fit na nagpapakita ng konektado](../../../../../translated_images/tl/counterfit-connected.ed30b46d8f79b0921f3fc70be10366e596a89dca3f80c2224a9d9fc98fccf884.png)

> 💁 Maaari mong mahanap ang code na ito sa [code/virtual-device](../../../../../1-getting-started/lessons/1-introduction-to-iot/code/virtual-device) folder.

😀 Tagumpay ang iyong koneksyon sa hardware!

---

**Paunawa**:  
Ang dokumentong ito ay isinalin gamit ang AI translation service na [Co-op Translator](https://github.com/Azure/co-op-translator). Bagama't sinisikap naming maging tumpak, tandaan na ang mga awtomatikong pagsasalin ay maaaring maglaman ng mga pagkakamali o hindi pagkakatugma. Ang orihinal na dokumento sa kanyang katutubong wika ang dapat ituring na opisyal na sanggunian. Para sa mahalagang impormasyon, inirerekomenda ang propesyonal na pagsasalin ng tao. Hindi kami mananagot sa anumang hindi pagkakaunawaan o maling interpretasyon na dulot ng paggamit ng pagsasaling ito.