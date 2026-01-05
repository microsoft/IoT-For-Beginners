<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "52b4de6144b2efdced7797a5339d6035",
  "translation_date": "2025-08-28T20:01:15+00:00",
  "source_file": "1-getting-started/lessons/1-introduction-to-iot/virtual-device.md",
  "language_code": "en"
}
-->
# Virtual single-board computer

Instead of buying an IoT device along with sensors and actuators, you can use your computer to simulate IoT hardware. The [CounterFit project](https://github.com/CounterFit-IoT/CounterFit) allows you to run an app locally that simulates IoT hardware like sensors and actuators, and access them from local Python code written in the same way as you would on a Raspberry Pi with physical hardware.

## Setup

To use CounterFit, you need to install some free software on your computer.

### Task

Install the required software.

1. Install Python. Follow the instructions on the [Python downloads page](https://www.python.org/downloads/) to install the latest version of Python.

1. Install Visual Studio Code (VS Code). This is the editor you will use to write your virtual device code in Python. Refer to the [VS Code documentation](https://code.visualstudio.com?WT.mc_id=academic-17441-jabenn) for installation instructions.

    > 💁 You can use any Python IDE or editor for these lessons if you prefer, but the instructions will be based on using VS Code.

1. Install the VS Code Pylance extension. This extension provides Python language support in VS Code. Refer to the [Pylance extension documentation](https://marketplace.visualstudio.com/items?WT.mc_id=academic-17441-jabenn&itemName=ms-python.vscode-pylance) for installation instructions.

Instructions for installing and configuring the CounterFit app will be provided later in the assignment, as it is installed on a per-project basis.

## Hello world

When starting with a new programming language or technology, it’s traditional to create a 'Hello World' application—a small program that outputs something like `"Hello World"` to confirm that all tools are set up correctly.

The Hello World app for the virtual IoT hardware will ensure that Python and Visual Studio Code are installed correctly. It will also connect to CounterFit for the virtual IoT sensors and actuators. No hardware will be used; the app will simply connect to verify everything is working.

This app will be created in a folder called `nightlight` and will be reused with different code in later parts of this assignment to build the nightlight application.

### Configure a Python virtual environment

One of Python's strengths is the ability to install [Pip packages](https://pypi.org)—packages of code written by others and shared online. You can install a Pip package with a single command and use it in your code. You’ll use Pip to install a package to interact with CounterFit.

By default, installed packages are available system-wide, which can lead to version conflicts—one application might require a specific version of a package that breaks when another application installs a newer version. To avoid this, you can use a [Python virtual environment](https://docs.python.org/3/library/venv.html), which is essentially a copy of Python in a dedicated folder. Pip packages installed in this environment are isolated to that folder.

> 💁 If you are using a Raspberry Pi, you didn’t set up a virtual environment on that device to manage Pip packages. Instead, you are using global packages, as the Grove packages are installed globally by the installer script.

#### Task - configure a Python virtual environment

Set up a Python virtual environment and install the Pip packages for CounterFit.

1. From your terminal or command line, run the following commands to create and navigate to a new directory:

    ```sh
    mkdir nightlight
    cd nightlight
    ```

1. Create a virtual environment in the `.venv` folder:

    ```sh
    python3 -m venv .venv
    ```

    > 💁 Use `python3` explicitly to create the virtual environment, as `python` might refer to Python 2 if it’s installed on your system.

1. Activate the virtual environment:

    * On Windows:
        * If using the Command Prompt or Command Prompt in Windows Terminal, run:

            ```cmd
            .venv\Scripts\activate.bat
            ```

        * If using PowerShell, run:

            ```powershell
            .\.venv\Scripts\Activate.ps1
            ```

            > If you encounter an error about running scripts being disabled, enable script execution by launching PowerShell as an administrator and running:

            ```powershell
            Set-ExecutionPolicy -ExecutionPolicy Unrestricted
            ```

            Confirm with `Y` when prompted. Then restart PowerShell and try again.

            You can reset this execution policy later if needed. For more details, see the [Execution Policies page on Microsoft Docs](https://docs.microsoft.com/powershell/module/microsoft.powershell.core/about/about_execution_policies?WT.mc_id=academic-17441-jabenn).

    * On macOS or Linux, run:

        ```cmd
        source ./.venv/bin/activate
        ```

    > 💁 Run these commands from the same location where you created the virtual environment. You don’t need to navigate into the `.venv` folder; always activate the environment and run commands from the folder where the virtual environment was created.

1. Once the virtual environment is activated, the `python` command will use the version of Python that created the environment. Check the version by running:

    ```sh
    python --version
    ```

    The output should include:

    ```output
    (.venv) ➜  nightlight python --version
    Python 3.9.1
    ```

    > 💁 Your Python version may differ. As long as it’s 3.6 or higher, you’re good. If not, delete the folder, install a newer Python version, and try again.

1. Install the Pip packages for CounterFit:

    ```sh
    pip install CounterFit
    pip install counterfit-connection
    pip install counterfit-shims-grove
    ```

    These packages will only be available in the virtual environment.

### Write the code

Once the Python virtual environment is ready, you can write the 'Hello World' application.

#### Task - write the code

Create a Python application to print `"Hello World"` to the console.

1. From the terminal or command line, create a Python file called `app.py`:

    * On Windows:

        ```cmd
        type nul > app.py
        ```

    * On macOS or Linux:

        ```cmd
        touch app.py
        ```

1. Open the current folder in VS Code:

    ```sh
    code .
    ```

    > 💁 If you see `command not found` on macOS, it means VS Code isn’t in your PATH. Follow the [VS Code documentation](https://code.visualstudio.com/docs/setup/mac?WT.mc_id=academic-17441-jabenn#_launching-from-the-command-line) to add it to your PATH.

1. When VS Code launches, it will activate the Python virtual environment. The selected environment will appear in the bottom status bar:

    ![VS Code showing the selected virtual environment](../../../../../translated_images/vscode-virtual-env.8ba42e04c3d533cf.en.png)

1. If the VS Code Terminal is already running, it won’t have the virtual environment activated. Kill the terminal using the **Kill the active terminal instance** button:

    ![VS Code Kill the active terminal instance button](../../../../../translated_images/vscode-kill-terminal.1cc4de7c6f25ee08.en.png)

    The terminal prompt should include `.venv` when the virtual environment is active.

1. Launch a new terminal in VS Code by selecting *Terminal -> New Terminal* or pressing `` CTRL+` ``. The new terminal will activate the virtual environment:

    ```output
    ➜  nightlight source .venv/bin/activate
    (.venv) ➜  nightlight 
    ```

1. Open `app.py` in VS Code and add the following code:

    ```python
    print('Hello World!')
    ```

    The `print` function outputs the provided text to the console.

1. Run the Python app from the VS Code terminal:

    ```sh
    python app.py
    ```

    The output will be:

    ```output
    (.venv) ➜  nightlight python app.py 
    Hello World!
    ```

😀 Your 'Hello World' program works!

### Connect the 'hardware'

As a second 'Hello World' step, you’ll run the CounterFit app and connect your code to it. This simulates plugging IoT hardware into a development kit.

#### Task - connect the 'hardware'

1. Launch the CounterFit app from the VS Code terminal:

    ```sh
    counterfit
    ```

    The app will open in your browser:

    ![The Counter Fit app running in a browser](../../../../../translated_images/counterfit-first-run.433326358b669b31d0e99c3513cb01bfbb13724d162c99cdcc8f51ecf5f9c779.en.png)

    It will show as *Disconnected*, with the LED in the top-right corner turned off.

1. Add the following code to the top of `app.py`:

    ```python
    from counterfit_connection import CounterFitConnection
    CounterFitConnection.init('127.0.0.1', 5000)
    ```

    This imports the `CounterFitConnection` class and initializes a connection to the CounterFit app running on `127.0.0.1` (localhost) on port 5000.

    > 💁 If port 5000 is in use, change the port in the code and run CounterFit with `CounterFit --port <port_number>`.

1. Open a new VS Code terminal, as the current one is running the CounterFit app:

    ![VS Code Create a new integrated terminal button](../../../../../translated_images/vscode-new-terminal.77db8fc0f9cd3182.en.png)

1. Run `app.py` in the new terminal. The CounterFit app will show as **Connected**, and the LED will light up.

    ![Counter Fit showing as connected](../../../../../translated_images/counterfit-connected.ed30b46d8f79b0921f3fc70be10366e596a89dca3f80c2224a9d9fc98fccf884.en.png)

> 💁 You can find this code in the [code/virtual-device](../../../../../1-getting-started/lessons/1-introduction-to-iot/code/virtual-device) folder.

😀 Your connection to the hardware was successful!

---

**Disclaimer**:  
This document has been translated using the AI translation service [Co-op Translator](https://github.com/Azure/co-op-translator). While we aim for accuracy, please note that automated translations may include errors or inaccuracies. The original document in its native language should be regarded as the authoritative source. For critical information, professional human translation is advised. We are not responsible for any misunderstandings or misinterpretations resulting from the use of this translation.