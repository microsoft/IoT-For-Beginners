# Configure your microphone and speakers - Raspberry Pi

In this part of the lesson, you will add a microphone and speakers to your Raspberry Pi.

## Hardware

The Raspberry Pi needs a microphone.

The Pi doesn't have a microphone built in, you will need to add an external microphone. There are multiple ways to do this:

* USB microphone
* USB headset
* USB all in one speakerphone
* USB audio adapter and microphone with a 3.5mm jack
* [ReSpeaker 2-Mics Pi HAT](https://www.seeedstudio.com/ReSpeaker-2-Mics-Pi-HAT.html)

> 💁 Bluetooth microphones are not all supported on the Raspberry Pi, so if you have a bluetooth microphone or headset, you may have issues pairing or capturing audio.

Raspberry Pis come with a 3.5mm headphone jack. You can use this to connect headphones, a headset or a speaker. You can also add speakers using:

* HDMI audio through a monitor or TV
* USB speakers
* USB headset
* USB all in one speakerphone
* [ReSpeaker 2-Mics Pi HAT](https://www.seeedstudio.com/ReSpeaker-2-Mics-Pi-HAT.html) with a speaker attached, either to the 3.5mm jack or to the JST port

## Connect and configure the microphone and speakers

The microphone and speakers need to be connected, and configured.

### Task - connect and configure the microphone

1. Connect the microphone using the appropriate method. For example, connect it via one of the USB ports.

1. If you are using the ReSpeaker 2-Mics Pi HAT, you can remove the Grove base hat, then fit the ReSpeaker hat in it's place.

    ![A raspberry pi with a ReSpeaker hat](../../../images/pi-respeaker-hat.png)

    You will need a Grove button later in this lesson, but one is built into this hat, so the Grove base hat is not needed.

    Once the hat is fitted, you will need to install some drivers. Refer to the [Seeed getting started instructions](https://wiki.seeedstudio.com/ReSpeaker_2_Mics_Pi_HAT_Raspberry/#getting-started) for driver installation instructions.

    > ⚠️ The instructions use `git` to clone a repository. If you don't have `git` installed on your Pi, you can install it by running the following command:
    >
    > ```sh
    > sudo apt install git --yes
    > ```

1. Run the following command in your Terminal either on the Pi, or connected using VS Code and a remote SSH session to see information about the connected microphone:

    ```sh
    arecord -l
    ```

    You will see a list of connected microphones. It will be something like the following:

    ```output
    pi@raspberrypi:~ $ arecord -l
    **** List of CAPTURE Hardware Devices ****
    card 1: M0 [eMeet M0], device 0: USB Audio [USB Audio]
      Subdevices: 1/1
      Subdevice #0: subdevice #0
    ```

    Assuming you only have one microphone, you should only see one entry. Configuration of mics can be tricky on Linux, so it is easiest to only use one microphone and unplug any others.

    Note down the card number, as you will need this later. In the output above the card number is 1.

### Task - connect and configure the speaker

1. Connect the speakers using the appropriate method.

1. Run the following command in your Terminal either on the Pi, or connected using VS Code and a remote SSH session to see information about the connected speakers:

    ```sh
    aplay -l
    ```

    You will see a list of connected speakers. It will be something like the following:

    ```output
    pi@raspberrypi:~ $ aplay -l
    **** List of PLAYBACK Hardware Devices ****
    card 0: Headphones [bcm2835 Headphones], device 0: bcm2835 Headphones [bcm2835 Headphones]
      Subdevices: 8/8
      Subdevice #0: subdevice #0
      Subdevice #1: subdevice #1
      Subdevice #2: subdevice #2
      Subdevice #3: subdevice #3
      Subdevice #4: subdevice #4
      Subdevice #5: subdevice #5
      Subdevice #6: subdevice #6
      Subdevice #7: subdevice #7
    card 1: M0 [eMeet M0], device 0: USB Audio [USB Audio]
      Subdevices: 1/1
      Subdevice #0: subdevice #0
    ```

    You will always see `card 0: Headphones` as this is the built-in headphone jack. If you have added additional speakers, such as a USB speaker, you will see this listed as well.

1. If you are using an additional speaker, and not a speaker or headphones connected to the built-in headphone jack, you need to configure it as the default. To do this run the following command:

    ```sh
    sudo nano /usr/share/alsa/alsa.conf
    ```

    This will open a configuration file in `nano`, a terminal-based text editor. Scroll down using the arrow keys on your keyboard until you find the following line:

    ```output
    defaults.pcm.card 0
    ```

    Change the value from `0` to the card number of the card you want to use from the list that came back from the call to `aplay -l`. For example, in the output above there is a second sound card called `card 1: M0 [eMeet M0], device 0: USB Audio [USB Audio]`, using card 1. To use this, I would update the line to be:

    ```output
    defaults.pcm.card 1
    ```

    Set this value to the appropriate card number. You can navigate to the number using the arrow keys on your keyboard, then delete and type the new number as normal when editing text files.

1. Save the changes and close the file by pressing `Ctrl+x`. Press `y` to save the file, then `return` to select the file name.

### Task - test the microphone and speaker

1. Run the following command to record 5 seconds of audio through the microphone:

    ```sh
    arecord --format=S16_LE --duration=5 --rate=16000 --file-type=wav out.wav
    ```

    Whilst this command is running, make noise into the microphone such as by speaking, singing, beat boxing, playing an instrument or whatever takes your fancy.

1. After 5 seconds, the recording will stop. Run the following command to play back the audio:

    ```sh
    aplay --format=S16_LE --rate=16000 out.wav
    ```

    You will hear the audio bing played back through the speakers. Adjust the output volume on your speaker as necessary.

1. If you need to adjust the volume of the built-in microphone port, or adjust the gain of the microphone, you can use the `alsamixer` utility. You can read more on this utility on thw [Linux alsamixer man page](https://linux.die.net/man/1/alsamixer)

1. If you get errors playing back the audio, check the card you set as the `defaults.pcm.card` in the `alsa.conf` file.
