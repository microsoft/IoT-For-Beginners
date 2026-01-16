<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "7e45d884493c5222348b43fbc4481b6a",
  "translation_date": "2025-08-27T21:23:32+00:00",
  "source_file": "6-consumer/lessons/1-speech-recognition/pi-microphone.md",
  "language_code": "cs"
}
-->
# Nastavení mikrofonu a reproduktorů - Raspberry Pi

V této části lekce přidáte k Raspberry Pi mikrofon a reproduktory.

## Hardware

Raspberry Pi potřebuje mikrofon.

Pi nemá vestavěný mikrofon, takže budete muset přidat externí mikrofon. Existuje několik způsobů, jak to udělat:

* USB mikrofon
* USB headset
* USB reproduktor s mikrofonem
* USB audio adaptér a mikrofon s 3,5mm jackem
* [ReSpeaker 2-Mics Pi HAT](https://www.seeedstudio.com/ReSpeaker-2-Mics-Pi-HAT.html)

> 💁 Bluetooth mikrofony nejsou na Raspberry Pi plně podporovány, takže pokud máte bluetooth mikrofon nebo headset, můžete mít problémy s párováním nebo nahráváním zvuku.

Raspberry Pi má 3,5mm sluchátkový výstup. Tento výstup můžete použít k připojení sluchátek, headsetu nebo reproduktoru. Reproduktory můžete také připojit pomocí:

* HDMI zvuku přes monitor nebo TV
* USB reproduktorů
* USB headsetu
* USB reproduktoru s mikrofonem
* [ReSpeaker 2-Mics Pi HAT](https://www.seeedstudio.com/ReSpeaker-2-Mics-Pi-HAT.html) s připojeným reproduktorem, buď přes 3,5mm jack, nebo přes JST port

## Připojení a konfigurace mikrofonu a reproduktorů

Mikrofon a reproduktory je třeba připojit a nakonfigurovat.

### Úkol - připojení a konfigurace mikrofonu

1. Připojte mikrofon vhodným způsobem. Například jej připojte přes jeden z USB portů.

1. Pokud používáte ReSpeaker 2-Mics Pi HAT, můžete odstranit Grove základní hat a nasadit místo něj ReSpeaker hat.

    ![Raspberry Pi s ReSpeaker hat](../../../../../translated_images/cs/pi-respeaker-hat.f00fabe7dd039a93e2e0aa0fc946c9af0c6a9eb17c32fa1ca097fb4e384f69f0.png)

    Později v této lekci budete potřebovat Grove tlačítko, ale jedno je již zabudováno v tomto hatu, takže Grove základní hat není potřeba.

    Jakmile je hat nasazen, budete muset nainstalovat ovladače. Podívejte se na [návod k použití od Seeed](https://wiki.seeedstudio.com/ReSpeaker_2_Mics_Pi_HAT_Raspberry/#getting-started) pro pokyny k instalaci ovladačů.

    > ⚠️ Pokyny používají `git` k naklonování repozitáře. Pokud nemáte `git` nainstalovaný na svém Pi, můžete jej nainstalovat spuštěním následujícího příkazu:
    >
    > ```sh
    > sudo apt install git --yes
    > ```

1. Spusťte následující příkaz v Terminálu na Pi nebo připojeném přes VS Code a vzdálenou SSH relaci, abyste zjistili informace o připojeném mikrofonu:

    ```sh
    arecord -l
    ```

    Zobrazí se seznam připojených mikrofonů. Bude to vypadat například takto:

    ```output
    pi@raspberrypi:~ $ arecord -l
    **** List of CAPTURE Hardware Devices ****
    card 1: M0 [eMeet M0], device 0: USB Audio [USB Audio]
      Subdevices: 1/1
      Subdevice #0: subdevice #0
    ```

    Pokud máte pouze jeden mikrofon, měli byste vidět pouze jeden záznam. Konfigurace mikrofonů může být na Linuxu složitá, takže je nejjednodušší používat pouze jeden mikrofon a odpojit ostatní.

    Poznamenejte si číslo karty, protože ho budete potřebovat později. V uvedeném výstupu je číslo karty 1.

### Úkol - připojení a konfigurace reproduktoru

1. Připojte reproduktory vhodným způsobem.

1. Spusťte následující příkaz v Terminálu na Pi nebo připojeném přes VS Code a vzdálenou SSH relaci, abyste zjistili informace o připojených reproduktorech:

    ```sh
    aplay -l
    ```

    Zobrazí se seznam připojených reproduktorů. Bude to vypadat například takto:

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

    Vždy uvidíte `card 0: Headphones`, což je vestavěný sluchátkový výstup. Pokud jste přidali další reproduktory, například USB reproduktor, uvidíte je také v seznamu.

1. Pokud používáte další reproduktor, a ne reproduktor nebo sluchátka připojená k vestavěnému sluchátkovému výstupu, musíte jej nastavit jako výchozí. Proveďte to spuštěním následujícího příkazu:

    ```sh
    sudo nano /usr/share/alsa/alsa.conf
    ```

    Tím se otevře konfigurační soubor v `nano`, textovém editoru v terminálu. Pomocí šipek na klávesnici sjeďte dolů, dokud nenajdete následující řádek:

    ```output
    defaults.pcm.card 0
    ```

    Změňte hodnotu z `0` na číslo karty, kterou chcete použít, podle seznamu, který se zobrazil po volání `aplay -l`. Například ve výstupu výše je druhá zvuková karta označena jako `card 1: M0 [eMeet M0], device 0: USB Audio [USB Audio]`, což odpovídá kartě 1. Pro použití této karty bych aktualizoval řádek na:

    ```output
    defaults.pcm.card 1
    ```

    Nastavte tuto hodnotu na odpovídající číslo karty. Pomocí šipek na klávesnici se přesuňte na číslo, poté jej smažte a napište nové číslo jako při běžné úpravě textových souborů.

1. Uložte změny a zavřete soubor stisknutím `Ctrl+x`. Stiskněte `y` pro uložení souboru a poté `Enter` pro potvrzení názvu souboru.

### Úkol - testování mikrofonu a reproduktoru

1. Spusťte následující příkaz pro nahrání 5 sekund zvuku přes mikrofon:

    ```sh
    arecord --format=S16_LE --duration=5 --rate=16000 --file-type=wav out.wav
    ```

    Během běhu tohoto příkazu vydávejte zvuky do mikrofonu, například mluvte, zpívejte, beatboxujte, hrajte na nástroj nebo cokoliv jiného, co vás napadne.

1. Po 5 sekundách se nahrávání zastaví. Spusťte následující příkaz pro přehrání zvuku:

    ```sh
    aplay --format=S16_LE --rate=16000 out.wav
    ```

    Zvuk se přehraje přes reproduktory. Podle potřeby upravte hlasitost výstupu na reproduktoru.

1. Pokud potřebujete upravit hlasitost vestavěného mikrofonního portu nebo zesílení mikrofonu, můžete použít nástroj `alsamixer`. Více o tomto nástroji si můžete přečíst na [man stránce Linux alsamixer](https://linux.die.net/man/1/alsamixer).

1. Pokud při přehrávání zvuku narazíte na chyby, zkontrolujte kartu, kterou jste nastavili jako `defaults.pcm.card` v souboru `alsa.conf`.

---

**Prohlášení**:  
Tento dokument byl přeložen pomocí služby pro automatický překlad [Co-op Translator](https://github.com/Azure/co-op-translator). Ačkoli se snažíme o přesnost, mějte prosím na paměti, že automatické překlady mohou obsahovat chyby nebo nepřesnosti. Původní dokument v jeho původním jazyce by měl být považován za autoritativní zdroj. Pro důležité informace doporučujeme profesionální lidský překlad. Neodpovídáme za žádné nedorozumění nebo nesprávné interpretace vyplývající z použití tohoto překladu.