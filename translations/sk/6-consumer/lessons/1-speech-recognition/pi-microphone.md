<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "7e45d884493c5222348b43fbc4481b6a",
  "translation_date": "2025-08-28T09:15:30+00:00",
  "source_file": "6-consumer/lessons/1-speech-recognition/pi-microphone.md",
  "language_code": "sk"
}
-->
# Nastavenie mikrofónu a reproduktorov - Raspberry Pi

V tejto časti lekcie pridáte mikrofón a reproduktory k vášmu Raspberry Pi.

## Hardvér

Raspberry Pi potrebuje mikrofón.

Pi nemá zabudovaný mikrofón, takže budete musieť pridať externý mikrofón. Existuje niekoľko spôsobov, ako to urobiť:

* USB mikrofón
* USB headset
* USB reproduktor s mikrofónom
* USB audio adaptér a mikrofón s 3,5mm jackom
* [ReSpeaker 2-Mics Pi HAT](https://www.seeedstudio.com/ReSpeaker-2-Mics-Pi-HAT.html)

> 💁 Bluetooth mikrofóny nie sú všetky podporované na Raspberry Pi, takže ak máte bluetooth mikrofón alebo headset, môžete mať problémy s párovaním alebo nahrávaním zvuku.

Raspberry Pi má 3,5mm konektor na slúchadlá. Môžete ho použiť na pripojenie slúchadiel, headsetu alebo reproduktora. Reproduktory môžete pridať aj pomocou:

* HDMI audio cez monitor alebo TV
* USB reproduktory
* USB headset
* USB reproduktor s mikrofónom
* [ReSpeaker 2-Mics Pi HAT](https://www.seeedstudio.com/ReSpeaker-2-Mics-Pi-HAT.html) s pripojeným reproduktorom, buď cez 3,5mm jack alebo JST port

## Pripojenie a konfigurácia mikrofónu a reproduktorov

Mikrofón a reproduktory musia byť pripojené a nakonfigurované.

### Úloha - pripojenie a konfigurácia mikrofónu

1. Pripojte mikrofón pomocou vhodnej metódy. Napríklad ho pripojte cez jeden z USB portov.

1. Ak používate ReSpeaker 2-Mics Pi HAT, môžete odstrániť Grove základný HAT a potom nasadiť ReSpeaker HAT namiesto neho.

    ![Raspberry Pi s ReSpeaker HAT](../../../../../translated_images/sk/pi-respeaker-hat.f00fabe7dd039a93e2e0aa0fc946c9af0c6a9eb17c32fa1ca097fb4e384f69f0.png)

    Neskôr v tejto lekcii budete potrebovať tlačidlo Grove, ale jedno je zabudované v tomto HAT, takže Grove základný HAT nie je potrebný.

    Po nasadení HAT budete musieť nainštalovať niektoré ovládače. Pozrite si [návod na začiatok od Seeed](https://wiki.seeedstudio.com/ReSpeaker_2_Mics_Pi_HAT_Raspberry/#getting-started) pre inštrukcie na inštaláciu ovládačov.

    > ⚠️ Návod používa `git` na klonovanie repozitára. Ak nemáte `git` nainštalovaný na vašom Pi, môžete ho nainštalovať spustením nasledujúceho príkazu:
    >
    > ```sh
    > sudo apt install git --yes
    > ```

1. Spustite nasledujúci príkaz vo vašom Termináli buď na Pi, alebo pripojenom cez VS Code a vzdialenú SSH reláciu, aby ste videli informácie o pripojenom mikrofóne:

    ```sh
    arecord -l
    ```

    Zobrazí sa zoznam pripojených mikrofónov. Bude to niečo ako nasledujúce:

    ```output
    pi@raspberrypi:~ $ arecord -l
    **** List of CAPTURE Hardware Devices ****
    card 1: M0 [eMeet M0], device 0: USB Audio [USB Audio]
      Subdevices: 1/1
      Subdevice #0: subdevice #0
    ```

    Ak máte len jeden mikrofón, mali by ste vidieť len jeden záznam. Konfigurácia mikrofónov môže byť na Linuxe zložitá, takže je najjednoduchšie používať len jeden mikrofón a odpojiť ostatné.

    Poznačte si číslo karty, pretože ho budete potrebovať neskôr. V uvedenom výstupe je číslo karty 1.

### Úloha - pripojenie a konfigurácia reproduktora

1. Pripojte reproduktory pomocou vhodnej metódy.

1. Spustite nasledujúci príkaz vo vašom Termináli buď na Pi, alebo pripojenom cez VS Code a vzdialenú SSH reláciu, aby ste videli informácie o pripojených reproduktoroch:

    ```sh
    aplay -l
    ```

    Zobrazí sa zoznam pripojených reproduktorov. Bude to niečo ako nasledujúce:

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

    Vždy uvidíte `card 0: Headphones`, pretože ide o zabudovaný konektor na slúchadlá. Ak ste pridali ďalšie reproduktory, ako napríklad USB reproduktor, uvidíte ich tiež v zozname.

1. Ak používate ďalší reproduktor, a nie reproduktor alebo slúchadlá pripojené k zabudovanému konektoru na slúchadlá, musíte ho nastaviť ako predvolený. Na to spustite nasledujúci príkaz:

    ```sh
    sudo nano /usr/share/alsa/alsa.conf
    ```

    Týmto sa otvorí konfiguračný súbor v `nano`, terminálovom textovom editore. Posuňte sa nadol pomocou šípok na klávesnici, kým nenájdete nasledujúci riadok:

    ```output
    defaults.pcm.card 0
    ```

    Zmeňte hodnotu z `0` na číslo karty, ktorú chcete použiť zo zoznamu, ktorý sa vrátil z volania `aplay -l`. Napríklad, vo vyššie uvedenom výstupe je druhá zvuková karta označená ako `card 1: M0 [eMeet M0], device 0: USB Audio [USB Audio]`, používajúca kartu 1. Na použitie tejto karty by som aktualizoval riadok na:

    ```output
    defaults.pcm.card 1
    ```

    Nastavte túto hodnotu na príslušné číslo karty. Môžete sa k číslu navigovať pomocou šípok na klávesnici, potom ho vymazať a napísať nové číslo ako pri bežnej úprave textových súborov.

1. Uložte zmeny a zatvorte súbor stlačením `Ctrl+x`. Stlačte `y` na uloženie súboru, potom `return` na potvrdenie názvu súboru.

### Úloha - testovanie mikrofónu a reproduktora

1. Spustite nasledujúci príkaz na nahratie 5 sekúnd zvuku cez mikrofón:

    ```sh
    arecord --format=S16_LE --duration=5 --rate=16000 --file-type=wav out.wav
    ```

    Počas spúšťania tohto príkazu vydávajte zvuky do mikrofónu, napríklad hovorte, spievajte, beatboxujte, hrajte na nástroj alebo čokoľvek, čo vás napadne.

1. Po 5 sekundách sa nahrávanie zastaví. Spustite nasledujúci príkaz na prehratie zvuku:

    ```sh
    aplay --format=S16_LE --rate=16000 out.wav
    ```

    Zvuk sa prehrá cez reproduktory. Podľa potreby upravte výstupnú hlasitosť na reproduktore.

1. Ak potrebujete upraviť hlasitosť zabudovaného mikrofónového portu alebo zisk mikrofónu, môžete použiť nástroj `alsamixer`. Viac o tomto nástroji si môžete prečítať na [Linux alsamixer man stránke](https://linux.die.net/man/1/alsamixer).

1. Ak dostanete chyby pri prehrávaní zvuku, skontrolujte kartu, ktorú ste nastavili ako `defaults.pcm.card` v súbore `alsa.conf`.

---

**Upozornenie**:  
Tento dokument bol preložený pomocou služby AI prekladu [Co-op Translator](https://github.com/Azure/co-op-translator). Hoci sa snažíme o presnosť, prosím, berte na vedomie, že automatizované preklady môžu obsahovať chyby alebo nepresnosti. Pôvodný dokument v jeho rodnom jazyku by mal byť považovaný za autoritatívny zdroj. Pre kritické informácie sa odporúča profesionálny ľudský preklad. Nenesieme zodpovednosť za akékoľvek nedorozumenia alebo nesprávne interpretácie vyplývajúce z použitia tohto prekladu.