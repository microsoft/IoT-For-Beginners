# Wio Terminal

The [Wio Terminal from Seeed Studios](https://www.seeedstudio.com/Wio-Terminal-p-4509.html) is an Arduino-compatible microcontroller, with WiFi and some sensors and actuators built in, as well as ports to add more sensors and actuators, using a hardware ecosystem called [Grove](https://www.seeedstudio.com/category/Grove-c-1003.html).

![A Seeed studios Wio Terminal](../../../images/wio-terminal.png)

## Setup

To use your Wio Terminal, you will need to install some free software on your computer. You will also need to update the Wio Terminal firmware before you can connect it to WiFi.

### Task

Install the required software and update the firmware.

1. Install Visual Studio Code (VS Code). This is the editor you will be using to write your device code in C/C++. Refer to the [VS Code documentation](https://code.visualstudio.com?WT.mc_id=academic-17441-jabenn) for instructions on installing VS Code.

    > 💁 Another popular IDE for Arduino development is the [Arduino IDE](https://www.arduino.cc/en/software). If you are already familiar with this tool, then you can use it instead of VS Code and PlatformIO, but the lessons will give instructions based off using VS Code.

1. Install the VS Code PlatformIO extension. This is an extension for VS Code that supports programming microcontrollers in C/C++. Refer to the [PlatformIO extension documentation](https://marketplace.visualstudio.com/items?itemName=platformio.platformio-ide&WT.mc_id=academic-17441-jabenn) for instructions on installing this extension in VS Code. This extension depends on the Microsoft C/C++ extension to work with C and C++ code, and the C/C++ extension is installed automatically when you install PlatformIO.

1. Connect your Wio Terminal to your computer. The Wio Terminal has a USB-C port on the bottom, and this needs to be connected to a USB port on your computer. The Wio Terminal comes with a USB-C to USB-A cable, but if your computer only has USB-C ports then you will either need a USB-C cable, or a USB-A to USB-C adapter.

1. Follow the instructions in the [Wio Terminal Wiki WiFi Overview documentation](https://wiki.seeedstudio.com/Wio-Terminal-Network-Overview/) to set up your Wio Terminal and update the firmware.

## Hello world

It is traditional when starting out with a new programming language or technology to create a 'Hello World' application - a small application that outputs something like the text `"Hello World"` to show that all the tools are correctly configured.

The Hello World app for the Wio Terminal will ensure that you have Visual Studio code installed correctly with PlatformIO and set up for microcontroller development.

### Create a PlatformIO project

The first step is to create a new project using PlatformIO configured for the Wio Terminal.

#### Task

Create the PlatformIO project.

1. Connect the Wio Terminal to your computer

1. Launch VS Code

1. You should see the PlatformIO icon on the side menu bar:

    ![The Platform IO menu option](../../../images/vscode-platformio-menu.png)

    Select this menu item, then select *PIO Home -> Open*

    ![The Platform IO open option](../../../images/vscode-platformio-home-open.png)

1. From the welcome screen, select the **+ New Project** button

    ![The new project button](../../../images/vscode-platformio-welcome-new-button.png)

1. Configure the project in the *Project Wizard*:

    1. Name your project `nightlight`

    1. From the *Board* dropdown, type in `WIO` to filter the boards, and select *Seeeduino Wio Terminal*

    1. Leave the *Framework* as *Arduino*

    1. Either leave the *Use default location* checkbox checked, or uncheck it and select a location for your project

    1. Select the **Finish** button

    ![The completed project wizard](../../../images/vscode-platformio-nightlight-project-wizard.png)

    PlatformIO will download the components it needs to compile code for the Wio Terminal and create your project. This may take a few minutes.

### Investigate the PlatformIO project

The VS Code explorer will show a number of files and folders created by the PlatformIO wizard.

#### Folders

* `.pio` - this folder contains temporary data needed by PlatformIO such as libraries or compiled code. It is recreated automatically if deleted, and you don't need to add this to source code control if you are sharing your project on sites such as GitHub.
* `.vscode` - this folder contains configuration used by PlatformIO and VS Code. It is recreated automatically if deleted, and you don't need to add this to source code control if you are sharing your project on sites such as GitHub.
* `include` - this folder is for external header files needed when adding additional libraries to your code. You won't be using this folder in any of these lessons.
* `lib` - this folder is for external libraries that you want to call from your code. You won't be using this folder in any of these lessons.
* `src` - this folder contains the main source code for your application. Initially it will contain a single file - `main.cpp`.
* `test` - this folder is where you would put any unit tests for your code

#### Files

* `main.cpp` - this file in the `src` folder contains the entry point for your application. If you open the file, you will see the following:

    ```cpp
    #include <Arduino.h>
    
    void setup() {
      // put your setup code here, to run once:
    }
    
    void loop() {
      // put your main code here, to run repeatedly:
    }
    ```

    When the device starts up, the Arduino framework will run the `setup` function once, then run the `loop` function repeatedly until the device is turned off.

* `.gitignore` - this file lists the files an directories to be ignored when adding your code to git source code control, such as uploading to a repository on GitHub.

* `platformio.ini` - this file contains configuration for your device and app. If you open this file, you will see the following:

    ```ini
    [env:seeed_wio_terminal]
    platform = atmelsam
    board = seeed_wio_terminal
    framework = arduino
    ```

    The `[env:seeed_wio_terminal]` section has configuration for the Wio Terminal. You can have multiple `env` sections so your code can be compiled for multiple boards.

    The other values match the configuration from the project wizard:

  * `platform = atmelsam` defines the hardware that the Wio Terminal uses (an ATSAMD51-based microcontroller)
  * `board = seeed_wio_terminal` defines the type of microcontroller board (the Wio Terminal)
  * `framework = arduino` defines that this project is using the Arduino framework.

### Write the Hello World app

You're now ready to write the Hello World app.

#### Task

Write the Hello World app.

1. Open the `main.cpp` file in VS Code

1. Change the code to match the following:

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

    The `setup` function initializes a connection to the serial port - in this case the USB port that is used to connect the Wio Terminal to your computer. The parameter `9600` is the [baud rate](https://wikipedia.org/wiki/Symbol_rate) (also known as Symbol rate), or speed that data will be sent over the serial port in bits per second. This setting means 9,600 bits (0s and 1s) of data are sent each second. It then waits for the serial port to be ready.

    The `loop` function sends the line `Hello World!` to the serial port, so the characters of `Hello World!` along with a new line character. It then sleeps for 5,000 milliseconds, or 5 seconds. After the `loop` ends, it is run again, and again, and so on all the time the microcontroller is powered on.

1. Build and upload the code to the Wio Terminal

    1. Open the VS Code command palette

    1. Type `PlatformIO Upload` to search for the upload option, and select *PlatformIO: Upload*

        ![The PlatformIO upload option in the command palette](../../../images/vscode-platformio-upload-command-palette.png)

        PlatformIO will automatically build the code if needed before uploading.

    1. The code will be compiled, and uploaded to the Wio Terminal

        > 💁 If you are using macOS you will see a notification about a *DISK NOT EJECTED PROPERLY*. This is because the Wio Terminal gets mounted as a drive as part of the flashing process, and it is disconnected when the compiled code is written to the device. You can ignore this notification.

    ⚠️ If you get errors about the upload port being unavailable, first make sure you have the Wio Terminal connected to your computer, and switched on using the switch on the left hand side of the screen. The green light on the bottom should be on. If you still get the error, pull the on/off switch down twice in quick succession to force the Wio Terminal into bootloader mode and try the upload again.

PlatformIO has a Serial Monitor that can monitor data sent over the USB cable from the Wio Terminal. This allows you to monitor the data sent by the `Serial.println("Hello World");` command.

1. Open the VS Code command palette

1. Type `PlatformIO Serial` to search for the Serial Monitor option, and select *PlatformIO: Serial Monitor*

    ![The PlatformIO Serial Monitor option in the command palette](../../../images/vscode-platformio-serial-monitor-command-palette.png)

    A new terminal will open, and the data sent over the serial port will be streamed into this terminal:

    ```output
    > Executing task: platformio device monitor <
    
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem101  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Hello World
    Hello World
    ```

    You will see `Hello World` appear every 5 seconds.

> 💁 You can find this code in the [code/wio-terminal](code/wio-terminal) folder.

😀 Your 'Hello World' program was a success!
