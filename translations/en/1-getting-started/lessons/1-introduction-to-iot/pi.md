<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "8ff0d0a1d29832bb896b9c103b69a452",
  "translation_date": "2025-08-28T20:02:22+00:00",
  "source_file": "1-getting-started/lessons/1-introduction-to-iot/pi.md",
  "language_code": "en"
}
-->
# Raspberry Pi

The [Raspberry Pi](https://raspberrypi.org) is a single-board computer. You can connect sensors and actuators using a variety of devices and ecosystems. For these lessons, you'll use a hardware ecosystem called [Grove](https://www.seeedstudio.com/category/Grove-c-1003.html). You'll program your Pi and interact with the Grove sensors using Python.

![A Raspberry Pi 4](../../../../../translated_images/raspberry-pi-4.fd4590d308c3d456.en.jpg)

## Setup

If you're using a Raspberry Pi as your IoT hardware, you have two options: you can either work through these lessons and code directly on the Pi, or you can connect remotely to a 'headless' Pi and code from your computer.

Before starting, you'll also need to attach the Grove Base Hat to your Pi.

### Task - setup

Install the Grove Base Hat on your Pi and configure the Pi.

1. Attach the Grove Base Hat to your Pi. The socket on the hat fits over all the GPIO pins on the Pi, sliding down the pins to sit securely on the base. It will cover the Pi.

    ![Fitting the grove hat](../../../../../images/pi-grove-hat-fitting.gif)

1. Decide how you want to program your Pi, and go to the relevant section below:

    * [Work directly on your Pi](../../../../../1-getting-started/lessons/1-introduction-to-iot)
    * [Remote access to code the Pi](../../../../../1-getting-started/lessons/1-introduction-to-iot)

### Work directly on your Pi

If you prefer to work directly on your Pi, you can use the desktop version of Raspberry Pi OS and install all the necessary tools.

#### Task - work directly on your Pi

Prepare your Pi for development.

1. Follow the instructions in the [Raspberry Pi setup guide](https://projects.raspberrypi.org/en/projects/raspberry-pi-setting-up) to set up your Pi, connect it to a keyboard/mouse/monitor, connect it to your WiFi or Ethernet network, and update the software.

To program the Pi with the Grove sensors and actuators, you'll need to install an editor for writing device code, as well as various libraries and tools to interact with the Grove hardware.

1. Once your Pi has rebooted, open the Terminal by clicking the **Terminal** icon on the top menu bar, or go to *Menu -> Accessories -> Terminal*.

1. Run the following command to ensure the OS and installed software are up to date:

    ```sh
    sudo apt update && sudo apt full-upgrade --yes
    ```

1. Run the following commands to install all the required libraries for the Grove hardware:

    ```sh
    sudo apt install git python3-dev python3-pip --yes

    git clone https://github.com/Seeed-Studio/grove.py
    cd grove.py
    sudo pip3 install .

    sudo raspi-config nonint do_i2c 0
    ```

    This starts by installing Git, along with Pip for managing Python packages.

    One of Python's strengths is the ability to install [Pip packages](https://pypi.org)—these are code packages created by others and shared online. You can install a Pip package on your computer with a single command and use it in your code.

    The Seeed Grove Python packages need to be installed from source. These commands will clone the repository containing the source code for this package and install it locally.

    > 💁 By default, when you install a package, it becomes available system-wide, which can sometimes cause version conflicts—e.g., one application might require a specific version of a package that breaks when you install a newer version for another application. To avoid this, you can use a [Python virtual environment](https://docs.python.org/3/library/venv.html), which is essentially a dedicated folder containing a copy of Python. Any Pip packages you install will only be available in that folder. However, for this project, you won't be using virtual environments. The Grove installation script installs the Grove Python packages globally. If you wanted to use a virtual environment, you'd need to set it up and manually reinstall the Grove packages within it. Using global packages is simpler, especially since many Pi developers re-flash a clean SD card for each project.

    Finally, this enables the I<sup>2</sup>C interface.

1. Reboot the Pi using the menu or by running the following command in the Terminal:

    ```sh
    sudo reboot
    ```

1. After the Pi reboots, reopen the Terminal and run the following command to install [Visual Studio Code (VS Code)](https://code.visualstudio.com?WT.mc_id=academic-17441-jabenn), the editor you'll use to write your Python device code.

    ```sh
    sudo apt install code
    ```

    Once installed, VS Code will be accessible from the top menu.

    > 💁 You can use any Python IDE or editor you prefer for these lessons, but the instructions provided will be based on VS Code.

1. Install Pylance, an extension for VS Code that provides Python language support. Refer to the [Pylance extension documentation](https://marketplace.visualstudio.com/items?WT.mc_id=academic-17441-jabenn&itemName=ms-python.vscode-pylance) for installation instructions.

### Remote access to code the Pi

Instead of coding directly on the Pi, you can run it 'headless' (without a keyboard/mouse/monitor) and configure and code on it from your computer using Visual Studio Code.

#### Set up the Pi OS

To code remotely, you'll need to install the Pi OS on an SD card.

##### Task - set up the Pi OS

Prepare the headless Pi OS.

1. Download the **Raspberry Pi Imager** from the [Raspberry Pi OS software page](https://www.raspberrypi.org/software/) and install it.

1. Insert an SD card into your computer, using an adapter if needed.

1. Open the Raspberry Pi Imager.

1. In the Raspberry Pi Imager, click the **CHOOSE OS** button, then select *Raspberry Pi OS (Other)*, followed by *Raspberry Pi OS Lite (32-bit)*.

    ![The Raspberry Pi Imager with Raspberry Pi OS Lite selected](../../../../../translated_images/raspberry-pi-imager.24aedeab9e233d84.en.png)

    > 💁 Raspberry Pi OS Lite is a version of Raspberry Pi OS without the desktop UI or graphical tools. These aren't necessary for a headless Pi, making the installation smaller and boot times faster.

1. Click the **CHOOSE STORAGE** button, then select your SD card.

1. Open the **Advanced Options** by pressing `Ctrl+Shift+X`. These options allow you to pre-configure the Raspberry Pi OS before writing it to the SD card.

    1. Check the **Enable SSH** box and set a password for the `pi` user. You'll use this password to log in to the Pi later.

    1. If you plan to connect to the Pi via WiFi, check the **Configure WiFi** box and enter your WiFi SSID and password, as well as selecting your WiFi country. If you're using an Ethernet cable, you can skip this step. Ensure the network you connect to is the same as your computer's.

    1. Check the **Set locale settings** box and set your country and timezone.

    1. Click the **SAVE** button.

1. Click the **WRITE** button to write the OS to the SD card. If you're using macOS, you'll be prompted to enter your password, as the tool that writes disk images requires elevated permissions.

The OS will be written to the SD card. Once complete, the card will be ejected, and you'll be notified. Remove the SD card from your computer, insert it into the Pi, power it on, and wait about 2 minutes for it to boot.

#### Connect to the Pi

Next, you'll remotely access the Pi using `ssh`, which is available on macOS, Linux, and recent versions of Windows.

##### Task - connect to the Pi

Remotely access the Pi.

1. Open a Terminal or Command Prompt and enter the following command to connect to the Pi:

    ```sh
    ssh pi@raspberrypi.local
    ```

    If you're using an older version of Windows without `ssh`, you can install OpenSSH. Follow the [OpenSSH installation documentation](https://docs.microsoft.com//windows-server/administration/openssh/openssh_install_firstuse?WT.mc_id=academic-17441-jabenn) for instructions.

1. This should connect to your Pi and prompt you for the password.

    The ability to find computers on your network using `<hostname>.local` is a relatively recent feature in Linux and Windows. If you're using Linux or Windows and encounter errors about the hostname not being found, you'll need to install additional software to enable ZeroConf networking (also called Bonjour by Apple):

    1. On Linux, install Avahi with the following command:

        ```sh
        sudo apt-get install avahi-daemon
        ```

    1. On Windows, the easiest way to enable ZeroConf is to install [Bonjour Print Services for Windows](http://support.apple.com/kb/DL999). Alternatively, you can install [iTunes for Windows](https://www.apple.com/itunes/download/) to get a newer version of the utility.

    > 💁 If you can't connect using `raspberrypi.local`, you can use the Pi's IP address. Refer to the [Raspberry Pi IP address documentation](https://www.raspberrypi.org/documentation/remote-access/ip-address.md) for instructions on finding the IP address.

1. Enter the password you set in the Raspberry Pi Imager Advanced Options.

#### Configure software on the Pi

Once connected to the Pi, you'll need to update the OS and install the necessary libraries and tools for the Grove hardware.

##### Task - configure software on the Pi

Set up the Pi software and install the Grove libraries.

1. From your `ssh` session, run the following command to update and reboot the Pi:

    ```sh
    sudo apt update && sudo apt full-upgrade --yes && sudo reboot
    ```

    The Pi will update and reboot. The `ssh` session will disconnect during the reboot, so wait about 30 seconds before reconnecting.

1. After reconnecting via `ssh`, run the following commands to install the required libraries for the Grove hardware:

    ```sh
    sudo apt install git python3-dev python3-pip --yes

    git clone https://github.com/Seeed-Studio/grove.py
    cd grove.py
    sudo pip3 install .

    sudo raspi-config nonint do_i2c 0
    ```

    This starts by installing Git and Pip for managing Python packages.

    The Seeed Grove Python packages need to be installed from source. These commands will clone the repository containing the source code and install it locally.

    > 💁 By default, packages are installed globally, which can sometimes cause version conflicts. To avoid this, you can use a [Python virtual environment](https://docs.python.org/3/library/venv.html). However, for simplicity, you'll use global packages for this project.

    Finally, this enables the I<sup>2</sup>C interface.

1. Reboot the Pi with the following command:

    ```sh
    sudo reboot
    ```

    The `ssh` session will disconnect during the reboot. There's no need to reconnect.

#### Configure VS Code for remote access

Once the Pi is set up, you can connect to it using Visual Studio Code (VS Code) from your computer. VS Code is a free developer text editor you'll use to write your Python device code.

##### Task - configure VS Code for remote access

Install the necessary software and connect to your Pi remotely.

1. Install VS Code on your computer by following the [VS Code documentation](https://code.visualstudio.com?WT.mc_id=academic-17441-jabenn).

1. Follow the instructions in the [VS Code Remote Development using SSH documentation](https://code.visualstudio.com/docs/remote/ssh?WT.mc_id=academic-17441-jabenn) to install the required components.

1. Using the same instructions, connect VS Code to the Pi.

1. Once connected, follow the [managing extensions](https://code.visualstudio.com/docs/remote/ssh#_managing-extensions?WT.mc_id=academic-17441-jabenn) guide to install the [Pylance extension](https://marketplace.visualstudio.com/items?WT.mc_id=academic-17441-jabenn&itemName=ms-python.vscode-pylance) remotely on the Pi.

## Hello world
It is customary when learning a new programming language or technology to start by creating a 'Hello World' application—a simple program that outputs text like `"Hello World"` to confirm that all tools are set up correctly.

The Hello World app for the Pi will help ensure that Python and Visual Studio Code are installed properly.

This app will be stored in a folder named `nightlight`, and later in this assignment, the folder will be reused with different code to develop the nightlight application.

### Task - Hello World

Create the Hello World app.

1. Open VS Code, either directly on the Pi or on your computer, connected to the Pi using the Remote SSH extension.

1. Open the VS Code Terminal by selecting *Terminal -> New Terminal* or pressing `` CTRL+` ``. The terminal will open in the home directory of the `pi` user.

1. Execute the following commands to create a directory for your code and a Python file named `app.py` within that directory:

    ```sh
    mkdir nightlight
    cd nightlight
    touch app.py
    ```

1. Open this folder in VS Code by selecting *File -> Open...* and choosing the *nightlight* folder, then click **OK**.

    ![The VS Code open dialog showing the nightlight folder](../../../../../translated_images/vscode-open-nightlight-remote.d3d2a4011e30d535.en.png)

1. Open the `app.py` file from the VS Code explorer and insert the following code:

    ```python
    print('Hello World!')
    ```

    The `print` function outputs whatever is passed to it in the console.

1. From the VS Code Terminal, run the following command to execute your Python app:

    ```sh
    python app.py
    ```

    > 💁 You might need to explicitly use `python3` to run this code if Python 2 is installed alongside Python 3 (the latest version). If Python 2 is installed, running `python` will default to Python 2 instead of Python 3. By default, the latest Raspberry Pi OS versions only come with Python 3 installed.

    The terminal will display the following output:

    ```output
    pi@raspberrypi:~/nightlight $ python3 app.py
    Hello World!
    ```

> 💁 You can find this code in the [code/pi](../../../../../1-getting-started/lessons/1-introduction-to-iot/code/pi) folder.

😀 Congratulations! Your 'Hello World' program worked successfully!

---

**Disclaimer**:  
This document has been translated using the AI translation service [Co-op Translator](https://github.com/Azure/co-op-translator). While we aim for accuracy, please note that automated translations may include errors or inaccuracies. The original document in its native language should be regarded as the authoritative source. For critical information, professional human translation is advised. We are not responsible for any misunderstandings or misinterpretations resulting from the use of this translation.