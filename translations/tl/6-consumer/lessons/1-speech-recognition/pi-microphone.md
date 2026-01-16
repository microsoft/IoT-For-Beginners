<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "7e45d884493c5222348b43fbc4481b6a",
  "translation_date": "2025-08-27T23:29:50+00:00",
  "source_file": "6-consumer/lessons/1-speech-recognition/pi-microphone.md",
  "language_code": "tl"
}
-->
# I-configure ang iyong mikropono at mga speaker - Raspberry Pi

Sa bahaging ito ng aralin, magdadagdag ka ng mikropono at mga speaker sa iyong Raspberry Pi.

## Kagamitan

Kailangan ng Raspberry Pi ng mikropono.

Walang built-in na mikropono ang Pi, kaya kailangan mong magdagdag ng panlabas na mikropono. Maraming paraan para gawin ito:

* USB mikropono
* USB headset
* USB all-in-one speakerphone
* USB audio adapter at mikropono na may 3.5mm jack
* [ReSpeaker 2-Mics Pi HAT](https://www.seeedstudio.com/ReSpeaker-2-Mics-Pi-HAT.html)

> 💁 Hindi lahat ng Bluetooth mikropono ay suportado sa Raspberry Pi, kaya kung mayroon kang Bluetooth mikropono o headset, maaaring magkaroon ka ng problema sa pag-pair o pagkuha ng audio.

Ang Raspberry Pi ay may 3.5mm headphone jack. Maaari mong gamitin ito para ikonekta ang headphones, headset, o speaker. Maaari ka ring magdagdag ng mga speaker gamit ang:

* HDMI audio sa pamamagitan ng monitor o TV
* USB speakers
* USB headset
* USB all-in-one speakerphone
* [ReSpeaker 2-Mics Pi HAT](https://www.seeedstudio.com/ReSpeaker-2-Mics-Pi-HAT.html) na may nakakabit na speaker, alinman sa 3.5mm jack o sa JST port

## Ikonekta at i-configure ang mikropono at mga speaker

Kailangan ikonekta at i-configure ang mikropono at mga speaker.

### Gawain - ikonekta at i-configure ang mikropono

1. Ikonekta ang mikropono gamit ang tamang paraan. Halimbawa, ikonekta ito sa isa sa mga USB port.

1. Kung ginagamit mo ang ReSpeaker 2-Mics Pi HAT, maaari mong tanggalin ang Grove base hat, pagkatapos ay ilagay ang ReSpeaker hat sa lugar nito.

    ![Isang Raspberry Pi na may ReSpeaker hat](../../../../../translated_images/tl/pi-respeaker-hat.f00fabe7dd039a93e2e0aa0fc946c9af0c6a9eb17c32fa1ca097fb4e384f69f0.png)

    Kakailanganin mo ng Grove button sa susunod na bahagi ng aralin, ngunit mayroon nang built-in na button sa hat na ito, kaya hindi na kailangan ang Grove base hat.

    Kapag nailagay na ang hat, kakailanganin mong mag-install ng ilang driver. Tingnan ang [Seeed getting started instructions](https://wiki.seeedstudio.com/ReSpeaker_2_Mics_Pi_HAT_Raspberry/#getting-started) para sa mga tagubilin sa pag-install ng driver.

    > ⚠️ Ginagamit ng mga tagubilin ang `git` para mag-clone ng repository. Kung wala kang `git` na naka-install sa iyong Pi, maaari mo itong i-install sa pamamagitan ng pagtakbo ng sumusunod na command:
    >
    > ```sh
    > sudo apt install git --yes
    > ```

1. Patakbuhin ang sumusunod na command sa iyong Terminal, alinman sa Pi o konektado gamit ang VS Code at isang remote SSH session, upang makita ang impormasyon tungkol sa nakakonektang mikropono:

    ```sh
    arecord -l
    ```

    Makikita mo ang listahan ng mga nakakonektang mikropono. Magiging ganito ang itsura:

    ```output
    pi@raspberrypi:~ $ arecord -l
    **** List of CAPTURE Hardware Devices ****
    card 1: M0 [eMeet M0], device 0: USB Audio [USB Audio]
      Subdevices: 1/1
      Subdevice #0: subdevice #0
    ```

    Kung mayroon ka lamang isang mikropono, dapat isa lang ang entry na makikita mo. Ang pag-configure ng mga mikropono ay maaaring maging mahirap sa Linux, kaya pinakamadaling gumamit ng isang mikropono lamang at tanggalin ang iba pang nakakonekta.

    Tandaan ang card number, dahil kakailanganin mo ito mamaya. Sa output sa itaas, ang card number ay 1.

### Gawain - ikonekta at i-configure ang speaker

1. Ikonekta ang mga speaker gamit ang tamang paraan.

1. Patakbuhin ang sumusunod na command sa iyong Terminal, alinman sa Pi o konektado gamit ang VS Code at isang remote SSH session, upang makita ang impormasyon tungkol sa nakakonektang mga speaker:

    ```sh
    aplay -l
    ```

    Makikita mo ang listahan ng mga nakakonektang speaker. Magiging ganito ang itsura:

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

    Palaging makikita ang `card 0: Headphones` dahil ito ang built-in headphone jack. Kung nagdagdag ka ng karagdagang speaker, tulad ng USB speaker, makikita rin ito sa listahan.

1. Kung gumagamit ka ng karagdagang speaker, at hindi speaker o headphones na nakakonekta sa built-in headphone jack, kailangan mo itong i-configure bilang default. Para gawin ito, patakbuhin ang sumusunod na command:

    ```sh
    sudo nano /usr/share/alsa/alsa.conf
    ```

    Bubuksan nito ang configuration file sa `nano`, isang terminal-based text editor. Mag-scroll pababa gamit ang arrow keys sa iyong keyboard hanggang makita mo ang sumusunod na linya:

    ```output
    defaults.pcm.card 0
    ```

    Palitan ang value mula `0` sa card number ng card na gusto mong gamitin mula sa listahan na bumalik mula sa tawag sa `aplay -l`. Halimbawa, sa output sa itaas, mayroong pangalawang sound card na tinatawag na `card 1: M0 [eMeet M0], device 0: USB Audio [USB Audio]`, gamit ang card 1. Para gamitin ito, ia-update ko ang linya upang maging:

    ```output
    defaults.pcm.card 1
    ```

    Itakda ang value na ito sa tamang card number. Maaari kang mag-navigate sa numero gamit ang arrow keys sa iyong keyboard, pagkatapos ay i-delete at i-type ang bagong numero tulad ng normal na pag-edit ng text files.

1. I-save ang mga pagbabago at isara ang file sa pamamagitan ng pagpindot sa `Ctrl+x`. Pindutin ang `y` para i-save ang file, pagkatapos ay `return` para piliin ang pangalan ng file.

### Gawain - subukan ang mikropono at speaker

1. Patakbuhin ang sumusunod na command para mag-record ng 5 segundo ng audio gamit ang mikropono:

    ```sh
    arecord --format=S16_LE --duration=5 --rate=16000 --file-type=wav out.wav
    ```

    Habang tumatakbo ang command na ito, gumawa ng ingay sa mikropono tulad ng pagsasalita, pag-awit, beat boxing, pagtugtog ng instrumento, o kahit ano na gusto mo.

1. Pagkatapos ng 5 segundo, titigil ang pag-record. Patakbuhin ang sumusunod na command para i-play ang audio:

    ```sh
    aplay --format=S16_LE --rate=16000 out.wav
    ```

    Maririnig mo ang audio na pinapatugtog sa pamamagitan ng mga speaker. Ayusin ang output volume sa iyong speaker kung kinakailangan.

1. Kung kailangan mong ayusin ang volume ng built-in microphone port, o ayusin ang gain ng mikropono, maaari mong gamitin ang `alsamixer` utility. Maaari kang magbasa pa tungkol sa utility na ito sa [Linux alsamixer man page](https://linux.die.net/man/1/alsamixer).

1. Kung makakakuha ka ng mga error sa pag-playback ng audio, suriin ang card na itinakda mo bilang `defaults.pcm.card` sa `alsa.conf` file.

---

**Paunawa**:  
Ang dokumentong ito ay isinalin gamit ang AI translation service na [Co-op Translator](https://github.com/Azure/co-op-translator). Bagama't sinisikap naming maging tumpak, pakitandaan na ang mga awtomatikong pagsasalin ay maaaring maglaman ng mga pagkakamali o hindi pagkakatugma. Ang orihinal na dokumento sa orihinal nitong wika ang dapat ituring na opisyal na sanggunian. Para sa mahalagang impormasyon, inirerekomenda ang propesyonal na pagsasalin ng tao. Hindi kami mananagot sa anumang hindi pagkakaunawaan o maling interpretasyon na maaaring magmula sa paggamit ng pagsasaling ito.