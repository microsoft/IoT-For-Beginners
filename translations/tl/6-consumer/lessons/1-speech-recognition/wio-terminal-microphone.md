<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "93d352de36526b8990e41dd538100324",
  "translation_date": "2025-08-27T23:30:57+00:00",
  "source_file": "6-consumer/lessons/1-speech-recognition/wio-terminal-microphone.md",
  "language_code": "tl"
}
-->
# I-configure ang iyong mikropono at mga speaker - Wio Terminal

Sa bahaging ito ng aralin, magdadagdag ka ng mga speaker sa iyong Wio Terminal. Ang Wio Terminal ay may built-in na mikropono na maaaring gamitin upang makuha ang boses.

## Hardware

Ang Wio Terminal ay may built-in na mikropono na maaaring gamitin upang makuha ang audio para sa speech recognition.

![Ang mikropono sa Wio Terminal](../../../../../translated_images/wio-mic.3f8c843dbe8ad917.tl.png)

Upang magdagdag ng speaker, maaari mong gamitin ang [ReSpeaker 2-Mics Pi Hat](https://www.seeedstudio.com/ReSpeaker-2-Mics-Pi-HAT.html). Isa itong external na board na may 2 MEMS microphones, pati na rin ang konektor para sa speaker at headphone socket.

![Ang ReSpeaker 2-Mics Pi Hat](../../../../../translated_images/respeaker.f5d19d1c6b14ab16.tl.png)

Kakailanganin mo ng headphones, isang speaker na may 3.5mm jack, o isang speaker na may JST connection tulad ng [Mono Enclosed Speaker - 2W 6 Ohm](https://www.seeedstudio.com/Mono-Enclosed-Speaker-2W-6-Ohm-p-2832.html).

Upang ikonekta ang ReSpeaker 2-Mics Pi Hat, kakailanganin mo ng 40 pin-to-pin (tinatawag ding male-to-male) jumper cables.

> 💁 Kung komportable kang mag-solder, maaari mong gamitin ang [40 Pin Raspberry Pi Hat Adapter Board For Wio Terminal](https://www.seeedstudio.com/40-Pin-Raspberry-Pi-Hat-Adapter-Board-For-Wio-Terminal-p-4730.html) upang ikonekta ang ReSpeaker.

Kakailanganin mo rin ng SD card upang mag-download at mag-playback ng audio. Ang Wio Terminal ay sumusuporta lamang sa mga SD Card na hanggang 16GB ang laki, at kailangang naka-format ito bilang FAT32 o exFAT.

### Gawain - ikonekta ang ReSpeaker Pi Hat

1. Kapag naka-off ang Wio Terminal, ikonekta ang ReSpeaker 2-Mics Pi Hat sa Wio Terminal gamit ang jumper leads at ang GPIO sockets sa likod ng Wio Terminal:

    Kailangang ikonekta ang mga pin sa ganitong paraan:

    ![Isang diagram ng mga pin](../../../../../translated_images/wio-respeaker-wiring-0.767f80aa65081038.tl.png)

1. Iposisyon ang ReSpeaker at Wio Terminal na ang GPIO sockets ay nakaharap pataas, at nasa kaliwang bahagi.

1. Magsimula sa socket sa itaas na kaliwa ng GPIO socket sa ReSpeaker. Ikonekta ang isang pin-to-pin jumper cable mula sa itaas na kaliwang socket ng ReSpeaker papunta sa itaas na kaliwang socket ng Wio Terminal.

1. Ulitin ito pababa sa GPIO sockets sa kaliwang bahagi. Siguraduhing maayos ang pagkakakabit ng mga pin.

    ![Isang ReSpeaker na ang kaliwang mga pin ay nakakonekta sa kaliwang mga pin ng Wio Terminal](../../../../../translated_images/wio-respeaker-wiring-1.8d894727f2ba2400.tl.png)

    ![Isang ReSpeaker na ang kaliwang mga pin ay nakakonekta sa kaliwang mga pin ng Wio Terminal](../../../../../translated_images/wio-respeaker-wiring-2.329e1cbd306e754f.tl.png)

    > 💁 Kung ang iyong jumper cables ay magkakadikit bilang ribbons, panatilihin silang magkasama - mas madali itong masigurado na lahat ng cables ay nakakonekta nang maayos.

1. Ulitin ang proseso gamit ang mga GPIO sockets sa kanang bahagi ng ReSpeaker at Wio Terminal. Kailangang dumaan ang mga cable na ito sa paligid ng mga cable na nakakonekta na.

    ![Isang ReSpeaker na ang kanang mga pin ay nakakonekta sa kanang mga pin ng Wio Terminal](../../../../../translated_images/wio-respeaker-wiring-3.75b0be447e2fa930.tl.png)

    ![Isang ReSpeaker na ang kanang mga pin ay nakakonekta sa kanang mga pin ng Wio Terminal](../../../../../translated_images/wio-respeaker-wiring-4.aa9cd434d8779437.tl.png)

    > 💁 Kung ang iyong jumper cables ay magkakadikit bilang ribbons, hatiin ito sa dalawang ribbons. Ipaikot ang isa sa bawat gilid ng mga existing cables.

    > 💁 Maaari kang gumamit ng sticky tape upang hawakan ang mga pin sa isang block upang maiwasang matanggal habang ikinakabit ang lahat ng ito.
    >
    > ![Ang mga pin na naka-fix gamit ang tape](../../../../../translated_images/wio-respeaker-wiring-5.af117c20acf622f3.tl.png)

1. Kakailanganin mong magdagdag ng speaker.

    * Kung gumagamit ka ng speaker na may JST cable, ikonekta ito sa JST port ng ReSpeaker.

      ![Isang speaker na nakakonekta sa ReSpeaker gamit ang JST cable](../../../../../translated_images/respeaker-jst-speaker.a441d177809df945.tl.png)

    * Kung gumagamit ka ng speaker na may 3.5mm jack, o headphones, isaksak ito sa 3.5mm jack socket.

      ![Isang speaker na nakakonekta sa ReSpeaker gamit ang 3.5mm jack socket](../../../../../translated_images/respeaker-35mm-speaker.ad79ef4f128c7751.tl.png)

### Gawain - i-setup ang SD card

1. Ikonekta ang SD Card sa iyong computer, gamit ang external reader kung wala kang SD Card slot.

1. I-format ang SD Card gamit ang angkop na tool sa iyong computer, siguraduhing gumamit ng FAT32 o exFAT file system.

1. Ipasok ang SD card sa SD Card slot sa kaliwang bahagi ng Wio Terminal, sa ibaba lamang ng power button. Siguraduhing maipasok ito nang buo at mag-click - maaaring kailanganin mo ng manipis na tool o isa pang SD Card upang maitulak ito nang buo.

    ![Pagpasok ng SD card sa SD card slot sa ibaba ng power switch](../../../../../translated_images/wio-sd-card.acdcbe322fa4ee7f.tl.png)

    > 💁 Upang alisin ang SD Card, kailangan mo itong bahagyang itulak papasok at ito ay lalabas. Kakailanganin mo ng manipis na tool tulad ng flat-head screwdriver o isa pang SD Card.

---

**Paunawa**:  
Ang dokumentong ito ay isinalin gamit ang AI translation service na [Co-op Translator](https://github.com/Azure/co-op-translator). Bagama't sinisikap naming maging tumpak, pakitandaan na ang mga awtomatikong pagsasalin ay maaaring maglaman ng mga pagkakamali o hindi pagkakatugma. Ang orihinal na dokumento sa kanyang katutubong wika ang dapat ituring na opisyal na pinagmulan. Para sa mahalagang impormasyon, inirerekomenda ang propesyonal na pagsasalin ng tao. Hindi kami mananagot sa anumang hindi pagkakaunawaan o maling interpretasyon na dulot ng paggamit ng pagsasaling ito.