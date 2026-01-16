<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "52b4de6144b2efdced7797a5339d6035",
  "translation_date": "2026-01-07T02:47:44+00:00",
  "source_file": "1-getting-started/lessons/1-introduction-to-iot/virtual-device.md",
  "language_code": "kn"
}
-->
# ವರ್ಚುವಲ್ ಸಿಂಗಲ್-ಬೋರ್ಡ್ ಕಂಪ್ಯೂಟರ್

ಒಂದು ಐಒಟಿ ಉಪಕರಣವನ್ನು ಖರೀದಿಸುವ ಬದಲು, ಸೆನ್ಸಾರ್ಗಳು ಮತ್ತು ಚಾಲಕಗಳ ಜೊತೆಗೆ, ನೀವು ನಿಮ್ಮ ಕಂಪ್ಯೂಟರ್ ಅನ್ನು ಐಒಟಿ ಹಾರ್ಡ್‌ವೇರ್ ಅನ್ನು ಅನುಕರಿಸಲು ಬಳಸಬಹುದು. [CounterFit project](https://github.com/CounterFit-IoT/CounterFit) ನಿಮಗೆ ಲೊಕಲ್‌ನಲ್ಲಿ ಐಒಟಿ ಹಾರ್ಡ್‌ವೇರ್ ಅನ್ನು ಅನುಕರಿಸುವ ಅಪ್ಲಿಕೇಶನ್ ಅನ್ನು ರನ್ ಮಾಡಲು ಅನುಮತಿಸುತ್ತದೆ, ಸೆನ್ಸಾರ್ಗಳು ಮತ್ತು ಚಾಲಕಗಳನ್ನು ಪೈಥಾನ್ ಕೋಡ್‌ನಿಂದ ಪ್ರವೇಶಿಸಲು, ಮತ್ತು ಆ ಕೋಡ್ ಅನ್ನು ನೀವು ರಾಸ್ಪ್ಬೆರ್ರಿ ಪೈ ಮೇಲೆ ಭೌತಿಕ ಹಾರ್ಡ್‌ವೇರ್ ಬಳಸಿ ಬರೆಯುವ ರೀತಿಯಲ್ಲೇ ಬರೆಯಬಹುದು.

## ಸೆಟ್‌ಅಪ್

CounterFit ಬಳಸಲು, ನಿಮಗೆ ನಿಮ್ಮ ಕಂಪ್ಯೂಟರ್‌ನಲ್ಲಿ ಕೆಲವು ಉಚಿತ ಸಾಫ್ಟ್‌ವೇರ್ ಗಳನ್ನು ಇನ್‌ಸ್ಟಾಲ್ ಮಾಡಬೇಕಾಗುತ್ತದೆ.

### ಕಾರ್ಯ

ಅಗತ್ಯವಿರುವ ಸಾಫ್ಟ್‌ವೇರ್ ಅನ್ನು инಸ್ತಾಲ್ ಮಾಡಿ.

1. ಪೈಥಾನ್ ಅನ್ನು ಇನ್‌ಸ್ಟಾಲ್ ಮಾಡಿ. ಅತ್ಯಂತ ಹೊಸ ಪೈಥಾನ್ ಆವೃತ್ತಿಯನ್ನು ಇನ್‌ಸ್ಟಾಲ್ ಮಾಡುವ ನಿರ್ದೇಶನಗಳಿಗಾಗಿ [Python downloads page](https://www.python.org/downloads/) ಅನ್ನು ನೋಡಿ.

1. Visual Studio Code (VS Code) ಅನ್ನು ಇನ್‌ಸ್ಟಾಲ್ ಮಾಡಿ. ಇದು ನೀವು ಪೈಥಾನ್‌ನಲ್ಲಿ ನಿಮ್ಮ ವರ್ಚುವಲ್ ಉಪಕರಣದ ಕೋಡ್ ಬರೆಯಲು ಬಳಸುವ ಎಡಿಟರ್. VS Code ಅನ್ನು ಇನ್‌ಸ್ಟಾಲ್ ಮಾಡುವ ಸೂಚನೆಗಳಿಗಾಗಿ [VS Code documentation](https://code.visualstudio.com?WT.mc_id=academic-17441-jabenn) ಅನ್ನು ನೋಡಿ.

    > 💁 ನೀವು ಈ ಪಾಠಗಳನ್ನು ಮಾಡಲು ನಿಮ್ಮ ಪ್ರಿಯ Python IDE ಅಥವಾ ಎಡಿಟರ್ ಯಾವುದೇ ಒಳ್ಳೆಯದು, ಆದರೆ ಪಾಠಗಳು VS Code ಆಧಾರವಾಗಿ ಸೂಚನೆಗಳನ್ನು ನೀಡುತ್ತವೆ.

1. VS Code ಪೈಲಾನ್ಸೆ ವಿಸ್ತರಣೆ (Pylance extension) ಅನ್ನು ಇನ್‌ಸ್ಟಾಲ್ ಮಾಡಿ. ಇದು VS Code ಗೆ ಪೈಥಾನ್ ಭಾಷಾ ಬೆಂಬಲ ಒದಗಿಸುವ ವಿಸ್ತರಣೆ. ಈ ವಿಸ್ತರಣೆಯನ್ನು VS Code ನಲ್ಲಿ ಇನ್‌ಸ್ಟಾಲ್ ಮಾಡುವುದಕ್ಕೆ [Pylance extension documentation](https://marketplace.visualstudio.com/items?WT.mc_id=academic-17441-jabenn&itemName=ms-python.vscode-pylance) ನೋಡಿ.

CounterFit ಅಪ್ಲಿಕೇಶನ್ ಇನ್‌ಸ್ಟಾಲ್ ಮತ್ತು ಸಂರಚನೆಗಾಗಿ ಸೂಚನೆಗಳು ಪ್ರಾಜೆಕ್ಟ್ ಆಧಾರಿತವಾಗಿ ಅನುವಯವಾಗಿ ನೀಡಲಾಗುತ್ತದೆ.

## हेल्लो ವರ್ಲ್ಡ್

ಹೊಸ ಪ್ರೋಗ್ರಾಮಿಂಗ್ ಭಾಷೆ ಅಥವಾ ತಂತ್ರಜ್ಞಾನದೊಂದಿಗೆ ಪ್ರಾರಂಭಿಸುವಾಗ, "Hello World" ಅಪ್ಲಿಕೇಶನ್ ಮಾಡುವುದು ಪದ್ಧತಿಯಾಗಿದೆ — ಒಂದು ಚಿಕ್ಕ ಅಪ್ಲಿಕೇಶನ್ ಅದು `"Hello World"` ಎಂಬ ಪಠ್ಯವನ್ನು ಔಟ್‌ಪುಟ್ ಮಾಡುತ್ತದೆ, ಎಲ್ಲ ಸಾಧನಗಳು ಸರಿಯಾಗಿ ಸಂರಚಿತವಾಗಿವೆ ಎಂಬುದನ್ನು ತೋರಿಸಲು.

ವರ್ಚುವಲ್ ಐಒಟಿ ಹಾರ್ಡ್‌ವೇರ್ ಗಾಗಿ Hello World ಅಪ್ಲಿಕೇಶನ್ ಪೈಥಾನ್ ಮತ್ತು Visual Studio Code ಸರಿಯಾಗಿ ಇನ್‌ಸ್ಟಾಲ್ ಆಗಿರುವುದನ್ನು ಖಚಿತಪಡಿಸುತ್ತದೆ. ಇದು CounterFit ಗೆ ಸಂಪರ್ಕ ಮಾಡುತ್ತದೆ ಆದರೆ ಯಾವುದೇ ಭೌತಿಕ ಉಪಕರಣ ಬಳಸುವುದಿಲ್ಲ, ಕೇವಲ ಎಲ್ಲವೂ ಕೆಲಸ ಮಾಡುತ್ತಿದ್ದೆನ್ನಿಸಬೇಕು ಎಂದು ತೋರಿಸುತ್ತದೆ.

ಈ ಅಪ್ಲಿಕೇಶನ್ `nightlight` ಎಂಬ ಫೋಲ್ಡರ್‌ನಲ್ಲಿ ಇರುತ್ತದೆ, ಮತ್ತು ಈ ಅಸೈನ್ಮೆಂಟ್‌ನ ಮುಂದಿನ ಭಾಗಗಳಲ್ಲಿ ವಿಭಿನ್ನ ಕೋಡ್‌‌ಗಳೊಂದಿಗೆ ಪುನಃ ಉಪಯೋಗಿಸಲಾಗುತ್ತದೆ.

### ಪೈಥಾನ್ ವರ್ಚುವಲ್ ಪರಿಸರವನ್ನು ಸಂರಚಿಸಿ

ಪೈಥಾನ್‌ನ ಶಕ್ತಿಯ ಒಂದು ವೈಶಿಷ್ಟ್ಯವೆಂದರೆ [Pip packages](https://pypi.org) ಅನ್ನು ಇನ್‌ಸ್ಟಾಲ್ ಮಾಡಿಕೊಳ್ಳಬಲ್ಲದು - ಇವು ಇಂಟರ್ನೆಟ್‌ನಲ್ಲಿ ಪ್ರಕಟಿಸಲಾದ ಇತರರಿಂದ ರಚಿಸಲಾದ ಕೋಡ್ ಪ್ಯಾಕೇಜ್‌ಗಳು. ನೀವು ಪ್ಯಾಕೇಜ್ ಅನ್ನು ಸಿಂಪಲ್ ಕಮಾಂ autistic one command gives 大发彩票;Then ಮೊದಲು ಉತ್ತಮ ಸ್ಟೇಟ್ ಡಿ ಮೂಲ ಆರಂಭಿಸಲು ಒಂದು ವಾಸ್ತವದಲ್ಲಿ ನೀವು ಪೈಥಾನ್ ‌ನಲ್ಲಿ ಪ್ಯಾಕೇಜ್‌ಗಳನ್ನು ಇನ್‌ಸ್ಟಾಲ್ ಮಾಡಬಹುದು. ನೀವು CounterFit ಜೊತೆಗೆ ಸಂಭಾಷಿಸಲು Pip ಪ್ಯಾಕೇಜ್ ಅನ್ನು ಇನ್‌ಸ್ಟಾಲ್ ಮಾಡಲಿದ್ದೀರಿ.

ನೀವು ಸಾಮಾನ್ಯವಾಗಿ package ಅನ್ನು ಇನ್‌ಸ್ಟಾಲ್ ಮಾಡುತ್ತಿದ್ದಾಗ അത് ನಿಮ್ಮ ಕಂಪ್ಯೂಟರ್‍ನ ಎಲ್ಲೆಡೆ ಲಭ್ಯವಿರುತ್ತದೆ, ಇದರಿಂದ package ಆವೃತ್ತಿ ಸಮ್ಮಿಶ್ರಣಗಳ ಸಮಸ್ಯೆಗಳು ಎದುರಾಗಬಹುದು. ಏನಂದರೆ ಒಂದೊಂದು ಅಪ್ಲಿಕೇಶನ್ જુಟಾದ ಆವೃತ್ತಿಯ package ಅನ್ನು ಅವಲಂಬಿಸುವಾಗ ಇನ್ನೊಂದು ಅಪ್ಲಿಕೇಶನ್‌ಗಾಗಿ ಹೊಸದನ್ನು ಇನ್‌ಸ್ಟಾಲ್ ಮಾಡಿದಾಗ ಮುರಿದುಬಿದ್ದುಕೊಳ್ಳಬಹುದು. ಈ ಸಮಸ್ಯೆಯನ್ನು ನೀವು [Python virtual environment](https://docs.python.org/3/library/venv.html) ಎಂಬ ಒಂದು Python ನ ನಕಲಿರುವ ನಿಗದಿತ ಫೋಲ್ಡರ್‌ನಲ್ಲಿ ನಿರ್ವಹಿಸುವ ಮೂಲಕ ಸಮಸ್ಯೆಯನ್ನು ಸರಿಪಡಿಸಬಹುದು. ಈ virtual environment ನಲ್ಲಿ ನೀವು ಯಾರು ಪ್ಯಾಕೇಜ್ಗಳನ್ನು ಇನ್‌ಸ್ಟಾಲ್ ಮಾಡಿದರೆ, ಆ ಪ್ಯಾಕೇಜ್ಗಳು ಆ ಫೋಲ್ಡರ್‌ನಲ್ಲಿ ಮಾತ್ರ ಇರುತ್ತವೆ.

> 💁 ನೀವು Raspberry Pi ಬಳಸುತ್ತಿದ್ದರೆ, Grove packages ಗ್ಲೋಮಲ್ ಆಗ ಇನ್‌ಸ್ಟಾಲ್ ಆಗಿವೆ, ಹಾಗೂ ನೀವು Pip ಗಾಗಿ virtual environment ಅನ್ನು ರಚಿಸಿರಲಿಲ್ಲ.

#### ಕಾರ್ಯ - ಪೈಥಾನ್ ವರ್ಚುವಲ್ ಪರಿಸರವನ್ನು ಸಂರಚಿಸಿ

Python virtual environment ಅನ್ನು ಸಂರಚಿಸಿ ಮತ್ತು CounterFit ಗಾಗಿ Pip packages ಅನ್ನು ಇನ್‌ಸ್ಟಾಲ್ ಮಾಡಿ.

1. ನಿಮ್ಮ ಟರ್ಮಿನಲ್ ಅಥವಾ ಕಮಾಂಡ್ ಲೈನ್ನಿಂದ, ನಿಮ್ಮ ಆಯ್ಕೆಳ ಸ್ಥಳದಲ್ಲಿ ಈ ಕೆಳಗಿನ ಕಮಾಂಡ್ ಚಾಲನೆಯಲ್ಲಿಟ್ಟಿ ಹೊಸ ಡೈರೆಕ್ಟರಿಯನ್ನು ರಚಿಸಿ ಮತ್ತು ಅಲ್ಲಿ ಹೋಗಿ:

    ```sh
    mkdir nightlight
    cd nightlight
    ```

1. ಈಗ ಕೆಳಗಿನ ಕಮಾಂಡ್ ಅನ್ನು `.venv` ಫೋಲ್ಡರ್‌ನಲ್ಲಿ virtual environment ರಚಿಸಲು ನಡಿಸಿ:

    ```sh
    python3 -m venv .venv
    ```

    > 💁 ನೀವು `python3` ಅನ್ನೋದು ಸ್ಪಷ್ಟವಾಗಿ ಕರೆಸಬೇಕು, ಏಕೆಂದರೆ ನೀವು Python 2 ಕೂಡ ನೀವು ಹೊಂದಿದ್ದರೆ (Python 3 ನವೀಕರಣದ ಜೊತೆಗೆ). Python 2 ಹೊಂದಿದ್ದರೆ `python` ಕಮಾಂಡ್ Python 2 ಅನ್ನು ಟಿಗೆ ಮಾಡುತ್ತದೆ.

1. virtual environment ಅನ್ನು ಸಕ್ರಿಯಗೊಳಿಸಿ:

    * ವಿಂಡೋಸ್ ನಲ್ಲಿ:
        * Command Prompt ಅಥವಾ Windows Terminal ಮೂಲಕ Command Prompt ಬಳಸುತ್ತಿದ್ದರೆ, ಈ ಕೆಳಗಿನಂತೆ:

            ```cmd
            .venv\Scripts\activate.bat
            ```

        * PowerShell ಬಳಸುತ್ತಿದ್ದರೆ, ಚಾಲನೆ ಮೂಲಕ:

            ```powershell
            .\.venv\Scripts\Activate.ps1
            ```

            > ನಿಮ್ಮ ಸಿಸ್ಟಮ್‌ನಲ್ಲಿ ಸ್ಕ್ರಿಪ್ಟ್ ರನ್ ಮಾಡುವುದನ್ನು ನಿಷಿದ್ಧಿಸಿದ್ದು ಎಂದು ದೋಷ ಬರುತ್ತದೆ ಎಂದರೆ, ನಿಮಗೆ ಸ್ಕ್ರಿಪ್ಟ್‌ಗಳನ್ನು ಚಾಲನೆ ಮಾಡಲು ಅನುಮತಿಸುವ ಪಾಲಿಸಿಯನ್ನು ಸಕ್ರಿಯಗೊಳಿಸಬೇಕಾಗುತ್ತದೆ. ಇದಕ್ಕಾಗಿ PowerShell ಅನ್ನು ನಿರ್ವಾಹಕ (ಅಡ್ಮಿನಿಸ್ಟ್ರೇಟರ್) ಆಗಿ ತೆರೆಯಿರಿ ಮತ್ತು ಕೆಳಗಿನ ಕಮಾಂಡ್ ಅನ್ನು ನಡೆಸಿ:

            ```powershell
            Set-ExecutionPolicy -ExecutionPolicy Unrestricted
            ```

            ದೃಢೀಕರಣಕ್ಕಾಗಿ `Y` ನಮೂದಿಸಿ. ನಂತರ PowerShell ಅನ್ನು ಮರುಪ್ರಾರಂಭಿಸಿ ಮತ್ತೆ ಪ್ರಯತ್ನಿಸಿ.

            ಈ ಕಾರ್ಯನೀತಿಯನ್ನು ನಾವು ಬೇಲೆಯಾದಾಗ ಮರುಸೇರಿಸಬಹುದು. ಇದರ ಬಗ್ಗೆ ಹೆಚ್ಚಿನ ಮಾಹಿತಿಗಾಗಿ [Execution Policies page on Microsoft Docs](https://docs.microsoft.com/powershell/module/microsoft.powershell.core/about/about_execution_policies?WT.mc_id=academic-17441-jabenn) ನೋಡಿ.

    * macOS ಅಥವಾ Linux ನಲ್ಲಿ, ಈ ಕಮಾಂಡ್ ಅನ್ನು ಚಾಲನೆ ಮಾಡಿ:

        ```cmd
        source ./.venv/bin/activate
        ```


    > 💁 ನೀವು virtual environment ರಚಿಸಿದ ಫೋಲ್ಡರ್‌ನಲ್ಲಿಯೇ ಇದನ್ನು ನಡಿಸುವುದು ಸೂಕ್ತ. `.venv` ಫೋಲ್ಡರ್‌ಗೆ ಪ್ರವೇಶಿಸುವ ಅಗತ್ಯವಿಲ್ಲ, ಸದಾ virtual environment ಅನ್ನು ಸಕ್ರಿಯಗೊಳಿಸುವ ಕಮಾಂಡ್ ಅನ್ನು ನೀವು ಇದ್ದ ಫೋಲ್ಡರ್ನಿಂದಲೇ ಚಲಾಯಿಸಬೇಕು.

1. virtual environment ಸಕ್ರಿಯಗೊಂಡಾದ ನಂತರ, ಸಂಪರ್ಕಿತ `python` ಕಮಾಂಡ್ ಆ virtual environment ರಚಿಸಲು ಬಳಸಿದ Python ಆವೃತ್ತಿಯನ್ನು ನಡೆಸುತ್ತದೆ. ಆವೃತ್ತಿ ತಿಳಿಯಲು ಕೆಳಗಿನ ಕಮಾಂಡ್ ಚಲಾಯಿಸಿ:

    ```sh
    python --version
    ```

    ಔಟ್‌ಪುಟ್ ಈ ಕೆಳಗಿನಂತಿರಬೇಕು:

    ```output
    (.venv) ➜  nightlight python --version
    Python 3.9.1
    ```

    > 💁 ನಿಮ್ಮ Python ಆವೃತ್ತಿ ಬೇರೆ ಆಗಿರಬಹುದು - ಆದರೆ ಆವೃತ್ತಿ 3.6 ಅಥವಾ ಅದಕ್ಕಿಂತ ಹೆಚ್ಚಿನದು ಇದ್ದರೆ ಸಾಕು. ಇಲ್ಲಾದರೆ ಈ ಫೋಲ್ಡರ್ ಅನ್ನು ಅಳಿಸಿ, ಪೈಥಾನ್ ನ ಹೊಸ ಆವೃತ್ತಿಯನ್ನು ಇನ್‌ಸ್ಟಾಲ್ ಮಾಡಿ ಮತ್ತೆ ಪ್ರಯತ್ನಿಸಿ.

1. CounterFit ಗಾಗಿ Pip packages ಅನ್ನು ಇನ್‌ಸ್ಟಾಲ್ ಮಾಡಲು ಕೆಳಗಿನ ಕಮಾಂಡ್‌ಗಳನ್ನು ಚಲಾಯಿಸಿ. ಈ ಪ್ಯಾಕೇಜ್ಗಳಲ್ಲಿ ಮುಖ್ಯ CounterFit ಅಪ್ಲಿಕೇಶನ್ ಜೊತೆಗೆ Grove ಹಾರ್ಡ್‌ವೇರ್‌ಗಾಗಿ ಶಿಮ್‌ಗಳು ಸೇರಿವೆ. Grove ಇಕೋಸಿಸ್ಟಮ್‌ನ ಭೌತಿಕ ಸೆನ್ಸಾರ್ ಮತ್ತು ಚಾಲಕಗಳನ್ನು ಬಳಸಿ ಪ್ರೋಗ್ರಾಮ್ ಬರೆಯುತ್ತಿರುವಂತೆ ಇಲ್ಲಿಯ ಶಿಮ್‌ಗಳು ನಿಮಗೆ ವೆರ್ಚುವಲ್ ಐಒಟಿ ಉಪಕರಣಗಳಿಗೆ ಸಂಪರ್ಕ ಮಾಡುತ್ತವೆ.

    ```sh
    pip install CounterFit
    pip install counterfit-connection
    pip install counterfit-shims-grove
    ```

    ಈ pip packages‌ಗಳು ಕೇವಲ virtual environment ಒಳಗೆ ಇನ್‌ಸ್ಟಾಲಾಗುತ್ತವೆ ಮತ್ತು ಅದರ ಹೊರಗೆ ಲಭ್ಯವಿರವುದು.

### ಕೋಡ್ ಬರೆಯಿರಿ

Python virtual environment ಸಿದ್ಧವಾದ ನಂತರ, 'Hello World' ಅಪ್ಲಿಕೇಶನ್‌ನ ಕೋಡ್ ಬರೆದು ನೋಡಬಹುದು.

#### ಕಾರ್ಯ - ಕೋಡ್ ಬರೆಯಿರಿ

ಕನ್ಸೋಲ್‌ನಲ್ಲಿ `"Hello World"` ಅನ್ನು ಮುದ್ರಣ ಮಾಡುವ Python ಅಪ್ಲಿಕೇಶನ್ ಅನ್ನು ರಚಿಸಿ.

1. ನಿಮ್ಮ ಟರ್ಮಿನಲ್ ಅಥವಾ ಕಮಾಂಡ್ ಲೈನಿಂದ, virtual environment ಒಳಗೆ ಈ ಕೆಳಗಿನಂತೆ `app.py` ಫೈಲ್ ರಚಿಸಲು ಈ ಕಮಾಂಡ್ ಅನ್ನು ಚಲಾಯಿಸಿ:

    * ವಿಂಡೋಸ್‌ನಲ್ಲಿ:

        ```cmd
        type nul > app.py
        ```

    * macOS ಅಥವಾ Linux ನಲ್ಲಿ:

        ```cmd
        touch app.py
        ```

1. ಪ್ರಸ್ತುತ ಫೋಲ್ಡರ್ ಅನ್ನು VS Code ನಲ್ಲಿ ತೆರೆಯಿರಿ:

    ```sh
    code .
    ```

    > 💁 ನಿಮ್ಮ ಟರ್ಮಿನಲ್ macOS ನಲ್ಲಿ `command not found` ಹೇಳಿದರೆ, VS Code ನಿಮ್ಮ PATH ಗೆ ಸೇರಿಲ್ಲ. VS Code ಅನ್ನು PATHಗೆ ಸೇರಿಸಲು [VS Code ಡಾಕ್ಯುಮೆಂಟೇಶನ್](https://code.visualstudio.com/docs/setup/mac?WT.mc_id=academic-17441-jabenn#_launching-from-the-command-line)ನ "Launching from the command line" ವಿಭಾಗದ ಸೂಚನೆಗಳನ್ನು ಅನುಸರಿಸಿ, ನಂತರ ಕಮಾಂಡ್ ಒಮ್ಮೆ ಮರುಚಲಾಯಿಸಿ. ವಿಂಡೋಸ್ ಮತ್ತು ಲಿನಕ್ಸ್ ನಲ್ಲಿ VS Code ಅನ್ನು डಿಫಾಲ್ಟ್ ಆಗಿ PATH ಗೆ ಸೇರಿಸಲಾಗುತ್ತದೆ.

1. VS Code ಪ್ರಾರಂಭವಾದಾಗ, ಅದು Python virtual environment ಅನ್ನು ಸಕ್ರಿಯಗೊಳಿಸುತ್ತದೆ. ಆಯ್ದ virtual environment VS Code ನಿಧಾನಸ್ಥಿತಿ ಬಾರ್‍ನಲ್ಲಿಇರುತ್ತದೆ:

    ![VS Code showing the selected virtual environment](../../../../../translated_images/kn/vscode-virtual-env.8ba42e04c3d533cf.png)

1. VS Code ಟರ್ಮಿನಲ್ ಈಗಾಗಲೇ ರನ್ ಆಗಿ ಇದ್ದರೆ, virtual environment ಅದರಲ್ಲಿ ಸಕ್ರಿಯವಾಗಿಲ್ಲ. terminal ಅನ್ನು ಕಾಯ್ದು ಕೊಲ್ಲುವುದು ಸಾಧ್ಯವಾಗುತ್ತದೆ **Kill the active terminal instance** ಬಟನ್ ಬಳಸಿ:

    ![VS Code Kill the active terminal instance button](../../../../../translated_images/kn/vscode-kill-terminal.1cc4de7c6f25ee08.png)

    ನೀವು terminal prompt ನಲ್ಲಿ virtual environment ಹೆಸರು ಪ್ರೀಫಿಕ್ಸ್ ಆಗಿದೆಯೇ ಎಂದು ನೋಡಿ ಗುರುತಿಸಬಹುದು. ಉದಾಹರಣೆಗೆ:

    ```sh
    (.venv) ➜  nightlight
    ```

    prompt ನಲ್ಲಿ `.venv` ಇಲ್ಲದಿದ್ದರೆ virtual environment ಸಕ್ರಿಯವಾಗಿಲ್ಲ.

1. ಹೊಸ VS Code ಟರ್ಮಿನಲ್ ಆರಂಭಿಸಿ: *Terminal -> New Terminal* ಆಯ್ಕೆಮಾಡಿ ಅಥವಾ `` CTRL+` `` ಒತ್ತಿ. ಹೊಸ ಟರ್ಮಿನಲ್ ನಲ್ಲಿ virtual environment ಲೋಡ್ ಆಗುತ್ತದೆ, ಮತ್ತು ಟರ್ಮಿನಲ್ ನಲ್ಲಿ ಇದರ ಸಕ್ರಿಯತೆಗೆ ಸೂಚನೆ ಕಾಣುತ್ತದೆ. ಪ್ರಾಂಪ್ಟ್ ಮೇಲಾಭಿವೃದ್ಧಿಯಾದ virtual environment ಹೆಸರು (`.venv`) ಕಾಣಿಸುತ್ತದೆ:

    ```output
    ➜  nightlight source .venv/bin/activate
    (.venv) ➜  nightlight 
    ```

1. VS Code ಎಕ್ಸ್‌ಪ್ಲೋರರ್ ನಲ್ಲಿ `app.py` ಫೈಲ್ ತೆರೆಯಿರಿ ಮತ್ತು ಕೆಳಗಿನ ಕೋಡ್ ಸೇರಿಸಿ:

    ```python
    print('Hello World!')
    ```

    `print` ಫಂಕ್ಷನ್ ಯಾವುದೇ ಪರಿಬಂಧಿತ ವಿಷಯವನ್ನು ಕನ್ಸೋಲ್‌ಗೆ ಮುದ್ರಿಸುತ್ತದೆ.

1. VS Code ಟರ್ಮಿನಲ್ ನಲ್ಲಿ ಈ ಕೆಳಗಿನಂತೆ Python ಅಪ್ಲಿಕೇಶನ್ ಅನ್ನು ಚಲಾಯಿಸಿ:

    ```sh
    python app.py
    ```

    ಔಟ್‌ಪುಟ್‌ನಲ್ಲಿ ಈ ಕೆಳಗಿನ ಅಂಶಗಳಿರಬೇಕು:

    ```output
    (.venv) ➜  nightlight python app.py 
    Hello World!
    ```

😀 ನಿಮ್ಮ 'Hello World' ಪ್ರೋಗ್ರಾಂ ಯಶಸ್ವಿಯಾಯಿತು!

### 'ಹಾರ್ಡ್‌ವೇರ್' ಸಂಪರ್ಕಿಸಿ

ಎರಡನೇ 'Hello World' ಹಂತವಾಗಿ, ನೀವು CounterFit ಅಪ್ಲಿಕೇಶನ್ ಚಾಲನೆ ಮಾಡಿ ನಿಮ್ಮ ಕೋಡ್ ಅದಕ್ಕೆ ಸಂಪರ್ಕ ಮಾಡಬೇಕು. ಇದು ಐಒಟಿ ಹಾರ್ಡ್‌ವೇರ್ ಅನ್ನು ಡೆವ್ ಕಿಟ್‌ಗೆ ಜೋಡಿಸುವ ವರ್ಚುವಲ್ ಸಮಾನವಾಗಿ.

#### ಕಾರ್ಯ - 'ಹಾರ್ಡ್‌ವೇರ್' ಸಂಪರ್ಕಿಸು

1. VS Code ಟರ್ಮಿನಲ್ ಮೂಲಕ ಕೆಳಗಿನಂತೆ CounterFit ಅಪ್ಲಿಕೇಶನ್ ಚಾಲನೆ ಮಾಡಿರಿ:

    ```sh
    counterfit
    ```

    ಅಪ್ಲಿಕೇಶನ್ ಆರಂಭವಾಗುತ್ತದೆ ಮತ್ತು ನಿಮ್ಮ ವೆಬ್ ಬ್ರೌಸರ್‌ನಲ್ಲಿ ತೆರೆದುಕೊಳ್ಳುತ್ತದೆ:

    ![The Counter Fit app running in a browser](../../../../../translated_images/kn/counterfit-first-run.433326358b669b31.png)

    ಅದು *Disconnected* ಎಂದು ಗುರುತಿಸಲಾಗುತ್ತದೆ, ಮೇಲ್ಭಾಗದ ಬಲಗಡ Cris LED ಆನ್ ಆಗಿಲ್ಲ.

1. `app.py` ಗಾಗಿ ಕೆಳಗಿನ ಕೋಡ್ ಮೇಲೆ ಸೇರಿಸಿ:

    ```python
    from counterfit_connection import CounterFitConnection
    CounterFitConnection.init('127.0.0.1', 5000)
    ```

    ಈ ಕೋಡ್ `counterfit-connection` pip ಪ್ಯಾಕೇಜ್‌ನಿಂದ ಲಭಿಸುವ `counterfit_connection` ಮಾಯಾಜಾಲದಿಂದ `CounterFitConnection` ಕ್ಲಾಸ್ ಅನ್ನು ಆಮದು ಮಾಡುತ್ತದೆ. ಇದು `127.0.0.1` (ಸ್ಥಳೀಯ ಕಂಪ್ಯೂಟರ್ ಅನ್ನು ಉಲ್ಲೇಖಿಸುವ IP ವಿಳಾಸ, *localhost* ಎಂದು ಕರೆಯಲಾಗುತ್ತದೆ) ನಲ್ಲಿ 5000 ಪೋರ್ಟ್‌ನಲ್ಲಿ ನಡುತ್ತಿರುವ CounterFit ಅಪ್ಲಿಕೇಶನ್‌ಗೆ ಸಂಪರ್ಕ ಸ್ಥಾಪಿಸುತ್ತದೆ.

    > 💁 ನೀವು 5000 ಪೋರ್ಟ್ ಬಳಸುತ್ತಿರುವ ಇತರ ಅಪ್ಲಿಕೇಶನ್ಗಳಿದ್ದರೆ, ನೀವು ಕೋಡ್‌ನಲ್ಲಿ ಪೋರ್ಟ್ ಬದಲಾಯಿಸಬಹುದು ಮತ್ತು CounterFit ಅನ್ನು `CounterFit --port <port_number>` ಬಳಸಿ ಪ್ರಾರಂಭಿಸಿ, ಇಲ್ಲಿ `<port_number>` ಬದಲಾಗಿ ನಿಮ್ಮ ಇಚ್ಛಿತ ಪೋರ್ಟ್ ಅನ್ನು ಉಪಯೋಗಿಸಿ.

1. CounterFit ಅಪ್ಲಿಕೇಶನ್ ಲಭ್ಯವಿರುವೂ ಟರ್ಮಿನಲ್ ಲಾಕ್ ಮಾಡಲಾಗಿದೆ ಆದ್ದರಿಂದ, ಹೊಸ VS Code ಟರ್ಮಿನಲ್ ಅನ್ನು ತೆರೆಯಿರಿ: **Create a new integrated terminal** ಬಟನ್ ಬಳಸಿರಿ.

    ![VS Code Create a new integrated terminal button](../../../../../translated_images/kn/vscode-new-terminal.77db8fc0f9cd3182.png)

1. ಹೊಸ ಟರ್ಮಿನಲ್‌ನಲ್ಲಿ, `app.py` ಫೈಲ್ ಅನ್ನು ಮತ್ತೆ ರನ್ ಮಾಡಿ. CounterFit ಸ್ಥಿತಿ **Connected** ಆಗಿ LED ಬೆಳಗುತ್ತದೆ.

    ![Counter Fit showing as connected](../../../../../translated_images/kn/counterfit-connected.ed30b46d8f79b092.png)

> 💁 ಈ ಕೋಡ್ ಅನ್ನು ನೀವು [code/virtual-device](../../../../../1-getting-started/lessons/1-introduction-to-iot/code/virtual-device) ಫೋಲ್ಡರ್‌ನಲ್ಲಿ ಹುಡುಕಬಹುದು.

😀 ಹಾರ್ಡ್‌ವೇರ್‌ಗೆ ನಿಮ್ಮ ಸಂಪರ್ಕ ಯಶಸ್ವಿಯಾಯಿತು!

---

<!-- CO-OP TRANSLATOR DISCLAIMER START -->
**ಅस्वೀಕರಣ**:
ಈ ದಸ್ತಾವೇಜು AI ಭಾಷಾಂತರ ಸೇವೆ [Co-op Translator](https://github.com/Azure/co-op-translator) ಬಳಸಿ ಭಾಷಾಂತರಿಸಲಾಗಿದೆ. ನಾವು ನಿಖರತೆಗಾಗಿ ಪ್ರಯತ್ನಿಸುತ್ತಿದ್ದರೂ, ಸ್ವಯಂಚಾಲಿತ ಭಾಷಾಂತರಗಳಲ್ಲಿ ತಪ್ಪುಗಳು ಅಥವಾ ಅಸೂಕ್ತತೆಗಳು ಇರಬಹುದು ಎಂದು ದಯವಿಟ್ಟು ಗಮನಿಸಿ. ಮೂಲ ಭಾಷೆಯ המקוריದ ದಸ್ತಾವೇಜನ್ನು ಪ್ರಾಮಾಣಿಕ ಮೂಲವೆಂದು ಪರಿಗಣಿಸಬೇಕು. ಮಹತ್ವಪೂರ್ಣ ಮಾಹಿತಿಗಾಗಿ, ವೃತ್ತಿಪರ ಮಾನವ ಭಾಷಾಂತರವನ್ನು ಶಿಫಾರಸು ಮಾಡಲಾಗುತ್ತದೆ. ಈ ಭಾಷಾಂತರದ ಬಳಕೆಯಿಂದ ಉಂಟಾಗುವ ಯಾವುದೇ ತಪ್ಪು ಅರ್ಥಮಾಡಿಕೊಳ್ಳುವುದಕ್ಕೆ ಅಥವಾ ತಪ್ಪು ವಿವರಣೆಗಳಿಗೆ ನಾವು ಜವಾಬ್ದಾರರಾಗುವುದಿಲ್ಲ.
<!-- CO-OP TRANSLATOR DISCLAIMER END -->