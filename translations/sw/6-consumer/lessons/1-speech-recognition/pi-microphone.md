<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "7e45d884493c5222348b43fbc4481b6a",
  "translation_date": "2025-08-27T21:22:45+00:00",
  "source_file": "6-consumer/lessons/1-speech-recognition/pi-microphone.md",
  "language_code": "sw"
}
-->
# Sanidi kipaza sauti na spika - Raspberry Pi

Katika sehemu hii ya somo, utaongeza kipaza sauti na spika kwenye Raspberry Pi yako.

## Vifaa

Raspberry Pi inahitaji kipaza sauti.

Pi haina kipaza sauti kilichojengwa ndani, utahitaji kuongeza kipaza sauti cha nje. Kuna njia kadhaa za kufanya hivyo:

* Kipaza sauti cha USB  
* Headset ya USB  
* Spika ya USB yenye kipaza sauti  
* Adapta ya sauti ya USB na kipaza sauti chenye jack ya 3.5mm  
* [ReSpeaker 2-Mics Pi HAT](https://www.seeedstudio.com/ReSpeaker-2-Mics-Pi-HAT.html)  

> 💁 Vipaza sauti vya Bluetooth havina msaada kamili kwenye Raspberry Pi, kwa hivyo ikiwa una kipaza sauti au headset ya Bluetooth, unaweza kukumbana na changamoto za kuunganisha au kurekodi sauti.

Raspberry Pi ina jack ya headphone ya 3.5mm. Unaweza kutumia hii kuunganisha headphones, headset au spika. Pia unaweza kuongeza spika kwa kutumia:

* Sauti ya HDMI kupitia monitor au TV  
* Spika za USB  
* Headset ya USB  
* Spika ya USB yenye kipaza sauti  
* [ReSpeaker 2-Mics Pi HAT](https://www.seeedstudio.com/ReSpeaker-2-Mics-Pi-HAT.html) na spika iliyounganishwa, ama kupitia jack ya 3.5mm au port ya JST  

## Unganisha na sanidi kipaza sauti na spika

Kipaza sauti na spika vinahitaji kuunganishwa na kusanidiwa.

### Kazi - Unganisha na sanidi kipaza sauti

1. Unganisha kipaza sauti kwa kutumia njia inayofaa. Kwa mfano, unganisha kupitia moja ya port za USB.

1. Ikiwa unatumia ReSpeaker 2-Mics Pi HAT, unaweza kuondoa Grove base hat, kisha kuweka ReSpeaker hat mahali pake.

    ![Raspberry Pi na ReSpeaker hat](../../../../../translated_images/sw/pi-respeaker-hat.f00fabe7dd039a93e2e0aa0fc946c9af0c6a9eb17c32fa1ca097fb4e384f69f0.png)

    Utahitaji kitufe cha Grove baadaye katika somo hili, lakini kimoja kimejengwa ndani ya hat hii, kwa hivyo Grove base hat haitahitajika.

    Mara hat inapowekwa, utahitaji kusakinisha madereva. Rejelea [maelekezo ya kuanza ya Seeed](https://wiki.seeedstudio.com/ReSpeaker_2_Mics_Pi_HAT_Raspberry/#getting-started) kwa maelekezo ya usakinishaji wa madereva.

    > ⚠️ Maelekezo yanatumia `git` kuiga hifadhi. Ikiwa huna `git` iliyosakinishwa kwenye Pi yako, unaweza kuisakinisha kwa kuendesha amri ifuatayo:
    >
    > ```sh
    > sudo apt install git --yes
    > ```

1. Endesha amri ifuatayo kwenye Terminal yako, ama kwenye Pi, au ukiwa umeunganishwa kwa kutumia VS Code na session ya mbali ya SSH ili kuona taarifa kuhusu kipaza sauti kilichounganishwa:

    ```sh
    arecord -l
    ```

    Utaona orodha ya vipaza sauti vilivyounganishwa. Itakuwa kitu kama ifuatavyo:

    ```output
    pi@raspberrypi:~ $ arecord -l
    **** List of CAPTURE Hardware Devices ****
    card 1: M0 [eMeet M0], device 0: USB Audio [USB Audio]
      Subdevices: 1/1
      Subdevice #0: subdevice #0
    ```

    Ukizingatia una kipaza sauti kimoja tu, unapaswa kuona kiingilio kimoja tu. Usanidi wa vipaza sauti unaweza kuwa mgumu kwenye Linux, kwa hivyo ni rahisi kutumia kipaza sauti kimoja tu na kuondoa vingine.

    Kumbuka namba ya kadi, kwani utahitaji hii baadaye. Katika matokeo hapo juu, namba ya kadi ni 1.

### Kazi - Unganisha na sanidi spika

1. Unganisha spika kwa kutumia njia inayofaa.

1. Endesha amri ifuatayo kwenye Terminal yako, ama kwenye Pi, au ukiwa umeunganishwa kwa kutumia VS Code na session ya mbali ya SSH ili kuona taarifa kuhusu spika zilizounganishwa:

    ```sh
    aplay -l
    ```

    Utaona orodha ya spika zilizounganishwa. Itakuwa kitu kama ifuatavyo:

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

    Daima utaona `card 0: Headphones` kwani hii ni jack ya headphone iliyojengwa ndani. Ikiwa umeongeza spika za ziada, kama spika ya USB, utaona hii pia kwenye orodha.

1. Ikiwa unatumia spika ya ziada, na si spika au headphones zilizounganishwa kwenye jack ya headphone iliyojengwa ndani, unahitaji kuisanidi kama chaguo-msingi. Ili kufanya hivyo, endesha amri ifuatayo:

    ```sh
    sudo nano /usr/share/alsa/alsa.conf
    ```

    Hii itafungua faili ya usanidi kwenye `nano`, mhariri wa maandishi unaotegemea terminal. Shuka chini kwa kutumia funguo za mshale kwenye kibodi yako hadi uone mstari ufuatao:

    ```output
    defaults.pcm.card 0
    ```

    Badilisha thamani kutoka `0` hadi namba ya kadi unayotaka kutumia kutoka kwenye orodha iliyotolewa na wito wa `aplay -l`. Kwa mfano, katika matokeo hapo juu kuna kadi ya pili ya sauti inayoitwa `card 1: M0 [eMeet M0], device 0: USB Audio [USB Audio]`, ikitumia kadi 1. Ili kutumia hii, ningesasisha mstari kuwa:

    ```output
    defaults.pcm.card 1
    ```

    Weka thamani hii kwa namba sahihi ya kadi. Unaweza kuhamia kwenye namba kwa kutumia funguo za mshale kwenye kibodi yako, kisha kufuta na kuandika namba mpya kama kawaida unavyohariri faili za maandishi.

1. Hifadhi mabadiliko na funga faili kwa kubonyeza `Ctrl+x`. Bonyeza `y` kuhifadhi faili, kisha `return` kuchagua jina la faili.

### Kazi - Jaribu kipaza sauti na spika

1. Endesha amri ifuatayo kurekodi sekunde 5 za sauti kupitia kipaza sauti:

    ```sh
    arecord --format=S16_LE --duration=5 --rate=16000 --file-type=wav out.wav
    ```

    Wakati amri hii inaendelea, toa sauti kwenye kipaza sauti kama vile kuzungumza, kuimba, beat boxing, kucheza ala au chochote unachopenda.

1. Baada ya sekunde 5, kurekodi kutasimama. Endesha amri ifuatayo kucheza sauti:

    ```sh
    aplay --format=S16_LE --rate=16000 out.wav
    ```

    Utasikia sauti ikichezwa kupitia spika. Rekebisha sauti ya spika yako kama inavyohitajika.

1. Ikiwa unahitaji kurekebisha sauti ya port ya kipaza sauti iliyojengwa ndani, au kurekebisha gain ya kipaza sauti, unaweza kutumia zana ya `alsamixer`. Unaweza kusoma zaidi kuhusu zana hii kwenye [ukurasa wa Linux alsamixer man](https://linux.die.net/man/1/alsamixer).

1. Ikiwa unapata makosa wakati wa kucheza sauti, angalia kadi uliyoweka kama `defaults.pcm.card` kwenye faili ya `alsa.conf`.

---

**Kanusho**:  
Hati hii imetafsiriwa kwa kutumia huduma ya tafsiri ya AI [Co-op Translator](https://github.com/Azure/co-op-translator). Ingawa tunajitahidi kuhakikisha usahihi, tafsiri za kiotomatiki zinaweza kuwa na makosa au kutokuwa sahihi. Hati ya asili katika lugha yake ya awali inapaswa kuchukuliwa kama chanzo cha mamlaka. Kwa taarifa muhimu, tafsiri ya kitaalamu ya binadamu inapendekezwa. Hatutawajibika kwa kutokuelewana au tafsiri zisizo sahihi zinazotokana na matumizi ya tafsiri hii.