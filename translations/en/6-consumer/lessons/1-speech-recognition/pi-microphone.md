<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "7e45d884493c5222348b43fbc4481b6a",
  "translation_date": "2025-08-28T19:26:40+00:00",
  "source_file": "6-consumer/lessons/1-speech-recognition/pi-microphone.md",
  "language_code": "en"
}
-->
# Configure your microphone and speakers - Raspberry Pi

In this part of the lesson, you will set up a microphone and speakers for your Raspberry Pi.

## Hardware

The Raspberry Pi requires a microphone.

Since the Pi doesn't have a built-in microphone, you'll need to connect an external one. There are several options for this:

* USB microphone
* USB headset
* USB all-in-one speakerphone
* USB audio adapter with a microphone that uses a 3.5mm jack
* [ReSpeaker 2-Mics Pi HAT](https://www.seeedstudio.com/ReSpeaker-2-Mics-Pi-HAT.html)

> 💁 Bluetooth microphones are not fully supported on the Raspberry Pi. If you have a Bluetooth microphone or headset, you may encounter issues with pairing or recording audio.

Raspberry Pis come with a 3.5mm headphone jack, which can be used to connect headphones, a headset, or a speaker. Alternatively, you can add speakers using:

* HDMI audio through a monitor or TV
* USB speakers
* USB headset
* USB all-in-one speakerphone
* [ReSpeaker 2-Mics Pi HAT](https://www.seeedstudio.com/ReSpeaker-2-Mics-Pi-HAT.html) with a speaker connected either to the 3.5mm jack or the JST port

## Connect and configure the microphone and speakers

You'll need to connect and configure both the microphone and speakers.

### Task - Connect and configure the microphone

1. Connect the microphone using the appropriate method, such as plugging it into one of the USB ports.

1. If you're using the ReSpeaker 2-Mics Pi HAT, remove the Grove base hat and attach the ReSpeaker hat in its place.

    ![A Raspberry Pi with a ReSpeaker hat](../../../../../translated_images/en/pi-respeaker-hat.f00fabe7dd039a93e2e0aa0fc946c9af0c6a9eb17c32fa1ca097fb4e384f69f0.png)

    You'll need a Grove button later in this lesson, but since the ReSpeaker hat has a built-in Grove button, the Grove base hat is unnecessary.

    After attaching the hat, you'll need to install some drivers. Follow the [Seeed getting started instructions](https://wiki.seeedstudio.com/ReSpeaker_2_Mics_Pi_HAT_Raspberry/#getting-started) for driver installation.

    > ⚠️ The instructions use `git` to clone a repository. If `git` isn't installed on your Pi, you can install it by running the following command:
    >
    > ```sh
    > sudo apt install git --yes
    > ```

1. Run the following command in your Terminal (either directly on the Pi or via VS Code with a remote SSH session) to view information about the connected microphone:

    ```sh
    arecord -l
    ```

    This will display a list of connected microphones, similar to the following:

    ```output
    pi@raspberrypi:~ $ arecord -l
    **** List of CAPTURE Hardware Devices ****
    card 1: M0 [eMeet M0], device 0: USB Audio [USB Audio]
      Subdevices: 1/1
      Subdevice #0: subdevice #0
    ```

    If you only have one microphone connected, you should see just one entry. Configuring microphones on Linux can be challenging, so it's best to use only one microphone and disconnect any others.

    Note down the card number, as you'll need it later. In the example above, the card number is 1.

### Task - Connect and configure the speaker

1. Connect the speakers using the appropriate method.

1. Run the following command in your Terminal (either directly on the Pi or via VS Code with a remote SSH session) to view information about the connected speakers:

    ```sh
    aplay -l
    ```

    This will display a list of connected speakers, similar to the following:

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

    You'll always see `card 0: Headphones`, which corresponds to the built-in headphone jack. If you've added additional speakers, such as a USB speaker, they will also appear in the list.

1. If you're using an external speaker (not connected to the built-in headphone jack), you'll need to set it as the default. To do this, run the following command:

    ```sh
    sudo nano /usr/share/alsa/alsa.conf
    ```

    This will open a configuration file in `nano`, a terminal-based text editor. Use the arrow keys on your keyboard to scroll down until you find the following line:

    ```output
    defaults.pcm.card 0
    ```

    Change the value from `0` to the card number of the speaker you want to use, as shown in the output from the `aplay -l` command. For example, in the output above, there's a second sound card labeled `card 1: M0 [eMeet M0], device 0: USB Audio [USB Audio]`. To use this card, update the line to:

    ```output
    defaults.pcm.card 1
    ```

    Replace the value with the appropriate card number. Use the arrow keys to navigate, then delete and type the new number as you would in any text editor.

1. Save the changes and close the file by pressing `Ctrl+x`. Press `y` to confirm saving, then `return` to finalize the file name.

### Task - Test the microphone and speaker

1. Run the following command to record 5 seconds of audio using the microphone:

    ```sh
    arecord --format=S16_LE --duration=5 --rate=16000 --file-type=wav out.wav
    ```

    While the command is running, make noise into the microphone—speak, sing, beatbox, play an instrument, or anything else you'd like.

1. After 5 seconds, the recording will stop. Run the following command to play back the audio:

    ```sh
    aplay --format=S16_LE --rate=16000 out.wav
    ```

    You should hear the audio played back through the speakers. Adjust the speaker's volume as needed.

1. If you need to adjust the volume of the built-in microphone port or the microphone's gain, you can use the `alsamixer` utility. Learn more about this tool on the [Linux alsamixer man page](https://linux.die.net/man/1/alsamixer).

1. If you encounter errors during playback, double-check the card number you set as `defaults.pcm.card` in the `alsa.conf` file.

---

**Disclaimer**:  
This document has been translated using the AI translation service [Co-op Translator](https://github.com/Azure/co-op-translator). While we aim for accuracy, please note that automated translations may include errors or inaccuracies. The original document in its native language should be regarded as the authoritative source. For critical information, professional human translation is advised. We are not responsible for any misunderstandings or misinterpretations resulting from the use of this translation.