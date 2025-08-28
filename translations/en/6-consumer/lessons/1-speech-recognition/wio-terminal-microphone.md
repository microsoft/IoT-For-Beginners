<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "93d352de36526b8990e41dd538100324",
  "translation_date": "2025-08-28T19:26:01+00:00",
  "source_file": "6-consumer/lessons/1-speech-recognition/wio-terminal-microphone.md",
  "language_code": "en"
}
-->
# Configure your microphone and speakers - Wio Terminal

In this section of the lesson, you will add speakers to your Wio Terminal. The Wio Terminal already has a built-in microphone, which can be used to capture speech.

## Hardware

The Wio Terminal comes with a built-in microphone that can be used to capture audio for speech recognition.

![The mic on the Wio Terminal](../../../../../translated_images/wio-mic.3f8c843dbe8ad917424037a93e3d25c62634add00a04dd8e091317b5a7a90088.en.png)

To add a speaker, you can use the [ReSpeaker 2-Mics Pi Hat](https://www.seeedstudio.com/ReSpeaker-2-Mics-Pi-HAT.html). This is an external board equipped with 2 MEMS microphones, a speaker connector, and a headphone jack.

![The ReSpeaker 2-Mics Pi Hat](../../../../../translated_images/respeaker.f5d19d1c6b14ab1676d24ac2764e64fac5339046ae07be8b45ce07633d61b79b.en.png)

You will need to connect either headphones, a speaker with a 3.5mm jack, or a speaker with a JST connection, such as the [Mono Enclosed Speaker - 2W 6 Ohm](https://www.seeedstudio.com/Mono-Enclosed-Speaker-2W-6-Ohm-p-2832.html).

To connect the ReSpeaker 2-Mics Pi Hat, you will need 40 pin-to-pin (also known as male-to-male) jumper cables.

> 💁 If you are comfortable with soldering, you can use the [40 Pin Raspberry Pi Hat Adapter Board For Wio Terminal](https://www.seeedstudio.com/40-Pin-Raspberry-Pi-Hat-Adapter-Board-For-Wio-Terminal-p-4730.html) to connect the ReSpeaker.

Additionally, you will need an SD card to download and play back audio. The Wio Terminal supports SD cards up to 16GB in size, which must be formatted as FAT32 or exFAT.

### Task - Connect the ReSpeaker Pi Hat

1. With the Wio Terminal powered off, connect the ReSpeaker 2-Mics Pi Hat to the Wio Terminal using jumper cables and the GPIO sockets on the back of the Wio Terminal:

    The pins should be connected as shown below:

    ![A pin diagram](../../../../../translated_images/wio-respeaker-wiring-0.767f80aa6508103880d256cdf99ee7219e190db257c7261e4aec219759dc67b9.en.png)

1. Position the ReSpeaker and Wio Terminal with the GPIO sockets facing upward and on the left-hand side.

1. Starting from the top-left socket of the GPIO socket on the ReSpeaker, connect a pin-to-pin jumper cable from the top-left socket of the ReSpeaker to the top-left socket of the Wio Terminal.

1. Continue this process down the GPIO sockets on the left-hand side. Ensure the pins are securely connected.

    ![A ReSpeaker with the left-hand pins wired to the left-hand pins of the Wio Terminal](../../../../../translated_images/wio-respeaker-wiring-1.8d894727f2ba24004824ee5e06b83b6d10952550003a3efb603182121521b0ef.en.png)

    ![A ReSpeaker with the left-hand pins wired to the left-hand pins of the Wio Terminal](../../../../../translated_images/wio-respeaker-wiring-2.329e1cbd306e754f8ffe56f9294794f4a8fa123860d76067a79e9ea385d1bf56.en.png)

    > 💁 If your jumper cables are bundled into ribbons, keep them together—it makes it easier to ensure all cables are connected in order.

1. Repeat the process for the right-hand GPIO sockets on the ReSpeaker and Wio Terminal. These cables will need to go around the already connected cables.

    ![A ReSpeaker with the right-hand pins wired to the right-hand pins of the Wio Terminal](../../../../../translated_images/wio-respeaker-wiring-3.75b0be447e2fa9307a6a954f9ae8a71b77e39ada6a5ef1a059d341dc850fd90c.en.png)

    ![A ReSpeaker with the right-hand pins wired to the right-hand pins of the Wio Terminal](../../../../../translated_images/wio-respeaker-wiring-4.aa9cd434d8779437de720cba2719d83992413caed1b620b6148f6c8924889afb.en.png)

    > 💁 If your jumper cables are bundled into ribbons, split them into two groups. Pass one group on each side of the existing cables.

    > 💁 You can use sticky tape to hold the pins together in a block to prevent them from coming loose while connecting them.
    >
    > ![The pins fixed with tape](../../../../../translated_images/wio-respeaker-wiring-5.af117c20acf622f3cd656ccd8f4053f8845d6aaa3af164d24cb7dbd54a4bb470.en.png)

1. You will need to connect a speaker.

    * If you are using a speaker with a JST cable, connect it to the JST port on the ReSpeaker.

      ![A speaker connected to the ReSpeaker with a JST cable](../../../../../translated_images/respeaker-jst-speaker.a441d177809df9458041a2012dd336dbb22c00a5c9642647109d2940a50d6fcc.en.png)

    * If you are using a speaker with a 3.5mm jack or headphones, plug them into the 3.5mm jack socket.

      ![A speaker connected to the ReSpeaker via the 3.5mm jack socket](../../../../../translated_images/respeaker-35mm-speaker.ad79ef4f128c7751f0abf854869b6b779c90c12ae3e48909944a7e48aeee3c7e.en.png)

### Task - Set up the SD card

1. Connect the SD card to your computer using an external reader if your computer does not have an SD card slot.

1. Format the SD card using the appropriate tool on your computer, ensuring it is formatted as FAT32 or exFAT.

1. Insert the SD card into the SD card slot on the left-hand side of the Wio Terminal, just below the power button. Push the card all the way in until it clicks—you may need a thin tool or another SD card to help push it in completely.

    ![Inserting the SD card into the SD card slot below the power switch](../../../../../translated_images/wio-sd-card.acdcbe322fa4ee7f8f9c8cc015b3263964bb26ab5c7e25b41747988cc5280d64.en.png)

    > 💁 To eject the SD card, push it in slightly, and it will pop out. You may need a thin tool, such as a flat-head screwdriver or another SD card, to do this.

---

**Disclaimer**:  
This document has been translated using the AI translation service [Co-op Translator](https://github.com/Azure/co-op-translator). While we aim for accuracy, please note that automated translations may include errors or inaccuracies. The original document in its native language should be regarded as the authoritative source. For critical information, professional human translation is advised. We are not responsible for any misunderstandings or misinterpretations resulting from the use of this translation.