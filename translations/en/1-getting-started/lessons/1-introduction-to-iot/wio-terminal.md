<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "a4f0c166010e31fd7b6ca20bc88dec6d",
  "translation_date": "2025-08-28T20:04:24+00:00",
  "source_file": "1-getting-started/lessons/1-introduction-to-iot/wio-terminal.md",
  "language_code": "en"
}
-->
# Wio Terminal

The [Wio Terminal from Seeed Studios](https://www.seeedstudio.com/Wio-Terminal-p-4509.html) is an Arduino-compatible microcontroller that comes with built-in WiFi, sensors, and actuators. It also has ports to connect additional sensors and actuators using a hardware ecosystem called [Grove](https://www.seeedstudio.com/category/Grove-c-1003.html).

![A Seeed studios Wio Terminal](../../../../../translated_images/en/wio-terminal.b8299ee16587db9a.webp)

## Setup

To start using your Wio Terminal, you need to install some free software on your computer. Additionally, you'll need to update the Wio Terminal firmware before connecting it to WiFi.

### Task - setup

Install the necessary software and update the firmware.

1. Install Visual Studio Code (VS Code), the editor you'll use to write your device code in C/C++. Follow the [VS Code documentation](https://code.visualstudio.com?WT.mc_id=academic-17441-jabenn) for installation instructions.

    > 💁 Another popular IDE for Arduino development is the [Arduino IDE](https://www.arduino.cc/en/software). If you're already familiar with this tool, you can use it instead of VS Code and PlatformIO. However, the lessons will provide instructions based on using VS Code.

1. Install the VS Code PlatformIO extension, which supports programming microcontrollers in C/C++. Refer to the [PlatformIO extension documentation](https://marketplace.visualstudio.com/items?WT.mc_id=academic-17441-jabenn&itemName=platformio.platformio-ide) for installation instructions. This extension automatically installs the Microsoft C/C++ extension required for working with C and C++ code.

1. Connect your Wio Terminal to your computer. Use the USB-C port located at the bottom of the device to connect it to a USB port on your computer. The Wio Terminal comes with a USB-C to USB-A cable, but if your computer only has USB-C ports, you'll need a USB-C cable or a USB-A to USB-C adapter.

1. Follow the instructions in the [Wio Terminal Wiki WiFi Overview documentation](https://wiki.seeedstudio.com/Wio-Terminal-Network-Overview/) to set up your Wio Terminal and update the firmware.

## Hello World

When learning a new programming language or technology, it's common to start with a 'Hello World' application—a simple program that outputs text like `"Hello World"` to confirm that everything is set up correctly.

The Hello World app for the Wio Terminal will ensure that Visual Studio Code is installed properly with PlatformIO and configured for microcontroller development.

### Create a PlatformIO project

The first step is to create a new project in PlatformIO configured for the Wio Terminal.

#### Task - create a PlatformIO project

Create the PlatformIO project.

1. Connect the Wio Terminal to your computer.

1. Launch VS Code.

1. Locate the PlatformIO icon in the side menu bar:

    ![The Platform IO menu option](../../../../../translated_images/en/vscode-platformio-menu.297be26b9733e5c4.webp)

    Click this icon, then select *PIO Home -> Open*.

    ![The Platform IO open option](../../../../../translated_images/en/vscode-platformio-home-open.3f9a41bfd3f4da1c.webp)

1. From the welcome screen, click the **+ New Project** button.

    ![The new project button](../../../../../translated_images/en/vscode-platformio-welcome-new-button.ba6fc8a4c7b78cc8.webp)

1. Configure the project in the *Project Wizard*:

    1. Name your project `nightlight`.

    1. In the *Board* dropdown, type `WIO` to filter the boards, and select *Seeeduino Wio Terminal*.

    1. Leave the *Framework* as *Arduino*.

    1. Either keep the *Use default location* checkbox checked or uncheck it and choose a location for your project.

    1. Click the **Finish** button.

    ![The completed project wizard](../../../../../translated_images/en/vscode-platformio-nightlight-project-wizard.5c64db4da6037420.webp)

    PlatformIO will download the necessary components to compile code for the Wio Terminal and create your project. This process may take a few minutes.

### Investigate the PlatformIO project

The VS Code explorer will display several files and folders created by the PlatformIO wizard.

#### Folders

* `.pio` - Contains temporary data needed by PlatformIO, such as libraries or compiled code. This folder is automatically recreated if deleted and doesn't need to be added to source code control (e.g., GitHub).
* `.vscode` - Contains configuration files for PlatformIO and VS Code. This folder is also automatically recreated if deleted and doesn't need to be added to source code control.
* `include` - Used for external header files when adding additional libraries to your code. This folder won't be used in these lessons.
* `lib` - Used for external libraries that your code calls. This folder won't be used in these lessons.
* `src` - Contains the main source code for your application. Initially, it includes a single file: `main.cpp`.
* `test` - Used for unit tests for your code.

#### Files

* `main.cpp` - Located in the `src` folder, this file contains the entry point for your application. Open it, and you'll see the following code:

    ```cpp
    #include <Arduino.h>
    
    void setup() {
      // put your setup code here, to run once:
    }
    
    void loop() {
      // put your main code here, to run repeatedly:
    }
    ```

    When the device starts, the Arduino framework runs the `setup` function once, followed by the `loop` function repeatedly until the device is turned off.

* `.gitignore` - Specifies files and directories to be ignored when adding your code to git source control, such as when uploading to GitHub.

* `platformio.ini` - Contains configuration for your device and app. Open it, and you'll see the following code:

    ```ini
    [env:seeed_wio_terminal]
    platform = atmelsam
    board = seeed_wio_terminal
    framework = arduino
    ```

    The `[env:seeed_wio_terminal]` section contains configuration for the Wio Terminal. You can have multiple `env` sections to compile your code for different boards.

    The other values match the settings from the project wizard:

  * `platform = atmelsam` specifies the hardware used by the Wio Terminal (an ATSAMD51-based microcontroller).
  * `board = seeed_wio_terminal` specifies the type of microcontroller board (the Wio Terminal).
  * `framework = arduino` indicates that the project uses the Arduino framework.

### Write the Hello World app

Now you're ready to write the Hello World app.

#### Task - write the Hello World app

Write the Hello World app.

1. Open the `main.cpp` file in VS Code.

1. Replace the code with the following:

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

    The `setup` function initializes a connection to the serial port (in this case, the USB port connecting the Wio Terminal to your computer). The parameter `9600` specifies the [baud rate](https://wikipedia.org/wiki/Symbol_rate), or the speed at which data is sent over the serial port in bits per second. This setting means 9,600 bits of data are sent each second. The function then waits for the serial port to be ready.

    The `loop` function sends the line `Hello World!` to the serial port, followed by a new line character. It then pauses for 5,000 milliseconds (5 seconds). After the `loop` ends, it runs again repeatedly as long as the microcontroller is powered on.

1. Put your Wio Terminal into upload mode. You'll need to do this every time you upload new code to the device:

    1. Quickly pull down the power switch twice—it will spring back to the on position each time.

    1. Check the blue status LED to the right of the USB port. It should be pulsing.

    [![A video showing how to put the Wio Terminal into upload mode](https://img.youtube.com/vi/LeKU_7zLRrQ/0.jpg)](https://youtu.be/LeKU_7zLRrQ)

    Click the image above to watch a video demonstration.

1. Build and upload the code to the Wio Terminal:

    1. Open the VS Code command palette.

    1. Type `PlatformIO Upload` to search for the upload option, and select *PlatformIO: Upload*.

        ![The PlatformIO upload option in the command palette](../../../../../translated_images/en/vscode-platformio-upload-command-palette.9e0f49cf80d1f1c3.webp)

        PlatformIO will automatically build the code if necessary before uploading.

    1. The code will be compiled and uploaded to the Wio Terminal.

        > 💁 If you're using macOS, you may see a notification about a *DISK NOT EJECTED PROPERLY*. This happens because the Wio Terminal is mounted as a drive during the flashing process and disconnected when the compiled code is written to the device. You can ignore this notification.

    ⚠️ If you encounter errors about the upload port being unavailable, ensure the Wio Terminal is connected to your computer, switched on using the power switch on the left side of the screen, and set to upload mode. The green light at the bottom should be on, and the blue light should be pulsing. If the error persists, pull the power switch down twice quickly again to force the Wio Terminal into upload mode and retry the upload.

PlatformIO includes a Serial Monitor that lets you view data sent over the USB cable from the Wio Terminal. This allows you to see the output of the `Serial.println("Hello World");` command.

1. Open the VS Code command palette.

1. Type `PlatformIO Serial` to search for the Serial Monitor option, and select *PlatformIO: Serial Monitor*.

    ![The PlatformIO Serial Monitor option in the command palette](../../../../../translated_images/en/vscode-platformio-serial-monitor-command-palette.b348ec841b8a1c14.webp)

    A new terminal will open, displaying the data sent over the serial port:

    ```output
    > Executing task: platformio device monitor <
    
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem101  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Hello World
    Hello World
    ```

    `Hello World` will appear in the serial monitor every 5 seconds.

> 💁 You can find this code in the [code/wio-terminal](../../../../../1-getting-started/lessons/1-introduction-to-iot/code/wio-terminal) folder.

😀 Congratulations! Your 'Hello World' program is working successfully!

---

**Disclaimer**:  
This document has been translated using the AI translation service [Co-op Translator](https://github.com/Azure/co-op-translator). While we aim for accuracy, please note that automated translations may include errors or inaccuracies. The original document in its native language should be regarded as the authoritative source. For critical information, professional human translation is advised. We are not responsible for any misunderstandings or misinterpretations resulting from the use of this translation.