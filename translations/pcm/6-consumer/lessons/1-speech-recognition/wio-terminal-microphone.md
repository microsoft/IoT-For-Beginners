<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "93d352de36526b8990e41dd538100324",
  "translation_date": "2025-11-18T19:25:57+00:00",
  "source_file": "6-consumer/lessons/1-speech-recognition/wio-terminal-microphone.md",
  "language_code": "pcm"
}
-->
# Configure your microphone and speakers - Wio Terminal

For dis part of di lesson, you go add speaker to your Wio Terminal. Di Wio Terminal don already get microphone wey dem build inside, and you fit use am to capture talk.

## Hardware

Di Wio Terminal don already get mic inside, and you fit use am to capture sound for talk recognition.

![Di mic wey dey Wio Terminal](../../../../../translated_images/wio-mic.3f8c843dbe8ad917.pcm.png)

To add speaker, you fit use di [ReSpeaker 2-Mics Pi Hat](https://www.seeedstudio.com/ReSpeaker-2-Mics-Pi-HAT.html). Dis na external board wey get 2 MEMS microphones, plus speaker connector and headphone socket.

![Di ReSpeaker 2-Mics Pi Hat](../../../../../translated_images/respeaker.f5d19d1c6b14ab16.pcm.png)

You go need add either headphone, speaker wey get 3.5mm jack, or speaker wey get JST connection like di [Mono Enclosed Speaker - 2W 6 Ohm](https://www.seeedstudio.com/Mono-Enclosed-Speaker-2W-6-Ohm-p-2832.html).

To connect di ReSpeaker 2-Mics Pi Hat, you go need 40 pin-to-pin (dem dey call am male-to-male too) jumper cables.

> 💁 If you sabi solder, you fit use di [40 Pin Raspberry Pi Hat Adapter Board For Wio Terminal](https://www.seeedstudio.com/40-Pin-Raspberry-Pi-Hat-Adapter-Board-For-Wio-Terminal-p-4730.html) to connect di ReSpeaker.

You go also need SD card to download and play sound. Di Wio Terminal dey support SD Cards wey no pass 16GB, and dem need to dey formatted as FAT32 or exFAT.

### Task - connect di ReSpeaker Pi Hat

1. When di Wio Terminal dey off, connect di ReSpeaker 2-Mics Pi Hat to di Wio Terminal using di jumper cables and di GPIO sockets wey dey back of di Wio Terminal:

    Di pins go need connect like dis:

    ![Pin diagram](../../../../../translated_images/wio-respeaker-wiring-0.767f80aa65081038.pcm.png)

1. Arrange di ReSpeaker and Wio Terminal make di GPIO sockets dey face up, and dey left-hand side.

1. Start from di socket wey dey top left of di GPIO socket for di ReSpeaker. Connect pin-to-pin jumper cable from di top left socket of di ReSpeaker to di top left socket of di Wio Terminal.

1. Do am like dat go reach di bottom for di GPIO sockets wey dey left-hand side. Make sure say di pins dey enter well.

    ![ReSpeaker wey di left-hand pins don connect to di left-hand pins of di Wio Terminal](../../../../../translated_images/wio-respeaker-wiring-1.8d894727f2ba2400.pcm.png)

    ![ReSpeaker wey di left-hand pins don connect to di left-hand pins of di Wio Terminal](../../../../../translated_images/wio-respeaker-wiring-2.329e1cbd306e754f.pcm.png)

    > 💁 If your jumper cables dey together as ribbon, leave dem like dat - e go make am easy to confirm say you don connect all di cables well.

1. Do di same process for di right-hand GPIO sockets for di ReSpeaker and Wio Terminal. Di cables go need pass around di cables wey don dey already.

    ![ReSpeaker wey di right-hand pins don connect to di right-hand pins of di Wio Terminal](../../../../../translated_images/wio-respeaker-wiring-3.75b0be447e2fa930.pcm.png)

    ![ReSpeaker wey di right-hand pins don connect to di right-hand pins of di Wio Terminal](../../../../../translated_images/wio-respeaker-wiring-4.aa9cd434d8779437.pcm.png)

    > 💁 If your jumper cables dey as ribbon, divide dem into two ribbons. Pass one each side of di cables wey don dey already.

    > 💁 You fit use sticky tape to hold di pins together make dem no commot as you dey connect dem.
    >
    > ![Di pins wey dem don hold with tape](../../../../../translated_images/wio-respeaker-wiring-5.af117c20acf622f3.pcm.png)

1. You go need add speaker.

    * If you dey use speaker wey get JST cable, connect am to di JST port for di ReSpeaker.

      ![Speaker wey dem connect to di ReSpeaker with JST cable](../../../../../translated_images/respeaker-jst-speaker.a441d177809df945.pcm.png)

    * If you dey use speaker wey get 3.5mm jack, or headphone, put am inside di 3.5mm jack socket.

      ![Speaker wey dem connect to di ReSpeaker through di 3.5mm jack socket](../../../../../translated_images/respeaker-35mm-speaker.ad79ef4f128c7751.pcm.png)

### Task - set up di SD card

1. Connect di SD Card to your computer, use external reader if your computer no get SD Card slot.

1. Format di SD Card with di correct tool for your computer, make sure say you use FAT32 or exFAT file system.

1. Put di SD card inside di SD Card slot wey dey left-hand side of di Wio Terminal, just under di power button. Make sure say di card enter well and click - you fit need thin tool or another SD Card to help push am enter.

    ![Di SD card wey dem dey put inside di SD card slot under di power switch](../../../../../translated_images/wio-sd-card.acdcbe322fa4ee7f.pcm.png)

    > 💁 To commot di SD Card, you go need push am small and e go commot. You go need thin tool like flat-head screwdriver or another SD Card to do dis.

---

<!-- CO-OP TRANSLATOR DISCLAIMER START -->
**Disclaimer**:  
Dis docu don dey translate wit AI translation service [Co-op Translator](https://github.com/Azure/co-op-translator). Even though we dey try make sure say e correct, abeg no forget say automatic translation fit get mistake or no dey accurate well. Di original docu for di language wey dem write am first na di main correct one. For important information, e good make una use professional human translation. We no go fit take blame for any misunderstanding or wrong interpretation wey fit happen because of dis translation.
<!-- CO-OP TRANSLATOR DISCLAIMER END -->